"""Deterministic, read-only integrity checks for repository record families.

The checker answers a narrow question: do the evidence, source, validation, and
case records agree with each other? It verifies identifiers, required fields,
cross-references, case/evidence and case/validation symmetry, target-manifest
paths, and index coverage.

It does not validate JSON Schema conformance, fetch sources, verify artifact
hashes, or rewrite any record. Those checks remain separate so a passing run is
not mistaken for a stronger claim than the links support.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Iterable, Mapping, Sequence

import yaml

SCHEMA_VERSION = 1

ID_PATTERNS = {
    "evidence": re.compile(r"EVD-[0-9]{4}"),
    "sources": re.compile(r"SRC-[0-9]{4}"),
    "validations": re.compile(r"VAL-[0-9]{4}"),
    "cases": re.compile(r"CASE-[0-9]{4}"),
}

FAMILY_DIRECTORIES = {
    "evidence": ("research/evidence", "EVD-*.yaml"),
    "sources": ("research/public-research", "SRC-*.yaml"),
    "validations": ("validation/results", "VAL-*.yaml"),
}

INDEX_FILES = {
    "evidence": "research/evidence/README.md",
    "sources": "research/public-research/README.md",
    "validations": "validation/README.md",
    "cases": "research/cases/README.md",
}

REQUIRED_FIELDS = {
    "evidence": (
        "schema_version",
        "id",
        "class",
        "state",
        "claim",
        "source",
        "limitations",
    ),
    "sources": (
        "schema_version",
        "id",
        "title",
        "source_type",
        "url",
        "published_at",
        "accessed_at",
        "source_scope",
        "claims",
        "silicon_assessment",
        "license_or_terms",
    ),
    "validations": (
        "schema_version",
        "id",
        "case_id",
        "target_manifest",
        "environment",
        "result",
        "inputs",
        "limitations",
    ),
    "cases": (
        "schema_version",
        "id",
        "status",
        "target_manifest",
        "objective",
        "kinds",
        "evidence",
    ),
}

EVIDENCE_CLASSES = {"primary", "reproduced", "secondary", "anecdotal", "derived"}
EVIDENCE_STATES = {"unknown", "observed", "inferred", "confirmed", "contradicted"}
CASE_STATUSES = {
    "new",
    "scoped",
    "investigating",
    "hypothesis",
    "analyzed",
    "validated",
    "rejected",
    "inconclusive",
    "reported",
    "archived",
}
VALIDATION_STATUSES = {"passed", "failed", "inconclusive", "not-run"}
ENVIRONMENT_TYPES = {"offline", "synthetic", "device-observation"}
SOURCE_APPLICABILITY = {
    "confirmed",
    "partial",
    "comparative-only",
    "not-applicable",
    "unknown",
}

# (field path, referenced family, referenced prefix)
REFERENCE_FIELDS = {
    "evidence": (
        ("related_evidence", "evidence", "EVD"),
        ("related_cases", "cases", "CASE"),
    ),
    "sources": (
        ("silicon_assessment.evidence_ids", "evidence", "EVD"),
    ),
    "validations": (
        ("related_evidence", "evidence", "EVD"),
    ),
    "cases": (
        ("evidence.supporting", "evidence", "EVD"),
        ("evidence.counter", "evidence", "EVD"),
        ("validation.validation_ids", "validations", "VAL"),
        ("references", "sources", "SRC"),
    ),
}

TARGET_MANIFEST_FIELDS = {
    "cases": ("target_manifest",),
    "validations": ("target_manifest",),
}


@dataclass(frozen=True)
class Issue:
    """One integrity finding, keyed to a record or repository location."""

    severity: str
    code: str
    record: str
    message: str

    def as_dict(self) -> dict[str, str]:
        return {
            "severity": self.severity,
            "code": self.code,
            "record": self.record,
            "message": self.message,
        }


@dataclass(frozen=True)
class Record:
    """A YAML record plus the identifier implied by its filename."""

    family: str
    record_id: str
    filename_id: str
    path: Path
    data: Mapping[str, Any]
    error: str | None = None


def _issue(
    issues: list[Issue], code: str, record: str, message: str, *, severity: str = "error"
) -> None:
    issues.append(Issue(severity=severity, code=code, record=record, message=message))


def _as_mapping(value: Any) -> Mapping[str, Any]:
    return value if isinstance(value, Mapping) else {}


def _get(document: Mapping[str, Any], dotted: str) -> Any:
    current: Any = document
    for part in dotted.split("."):
        if not isinstance(current, Mapping):
            return None
        current = current.get(part)
    return current


def _strings(value: Any) -> list[str]:
    if not isinstance(value, list):
        return []
    return [item for item in value if isinstance(item, str)]


def _load_path(family: str, path: Path, root: Path) -> Record:
    filename_id = path.parent.name if family == "cases" else path.stem
    relative = path.relative_to(root)
    try:
        document = yaml.safe_load(path.read_text(encoding="utf-8"))
    except (OSError, UnicodeError, yaml.YAMLError) as exc:
        return Record(family, filename_id, filename_id, relative, {}, f"cannot parse: {exc}")
    if not isinstance(document, Mapping):
        return Record(
            family,
            filename_id,
            filename_id,
            relative,
            {},
            "record root is not a mapping",
        )
    declared = document.get("id")
    record_id = declared if isinstance(declared, str) and declared else filename_id
    return Record(family, record_id, filename_id, relative, document)


def load_records(root: str | Path) -> tuple[dict[str, list[Record]], list[Issue]]:
    """Load every record family under ``root`` without modifying it."""
    base = Path(root)
    records: dict[str, list[Record]] = defaultdict(list)
    issues: list[Issue] = []

    for family, (directory, pattern) in FAMILY_DIRECTORIES.items():
        path = base / directory
        if not path.is_dir():
            _issue(issues, "missing-record-directory", family, f"{directory} does not exist")
            continue
        for file_path in sorted(path.glob(pattern)):
            records[family].append(_load_path(family, file_path, base))

    cases_dir = base / "research/cases"
    if not cases_dir.is_dir():
        _issue(
            issues,
            "missing-record-directory",
            "cases",
            "research/cases does not exist",
        )
    else:
        for file_path in sorted(cases_dir.glob("CASE-*/case.yaml")):
            records["cases"].append(_load_path("cases", file_path, base))

    return dict(records), issues


def _check_identity(record: Record, issues: list[Issue]) -> None:
    if record.error:
        _issue(issues, "unreadable-record", record.record_id, record.error)
        return

    pattern = ID_PATTERNS[record.family]
    if record.record_id != record.filename_id:
        _issue(
            issues,
            "filename-id-mismatch",
            record.record_id,
            f"{record.path} declares {record.record_id} but the filename implies "
            f"{record.filename_id}",
        )
    if not pattern.fullmatch(record.record_id):
        _issue(
            issues,
            "invalid-id",
            record.record_id,
            f"identifier does not match {pattern.pattern}",
        )


def _check_required_fields(record: Record, issues: list[Issue]) -> None:
    for field in REQUIRED_FIELDS[record.family]:
        if field not in record.data:
            _issue(
                issues,
                "missing-required-field",
                record.record_id,
                f"missing required field {field!r}",
            )


def _check_values(record: Record, issues: list[Issue]) -> None:
    data = record.data
    if "schema_version" in data and data["schema_version"] != SCHEMA_VERSION:
        _issue(
            issues,
            "invalid-value",
            record.record_id,
            f"schema_version is {data['schema_version']!r}, expected {SCHEMA_VERSION}",
        )

    if record.family == "evidence":
        if "class" in data and data["class"] not in EVIDENCE_CLASSES:
            _issue(
                issues,
                "invalid-value",
                record.record_id,
                f"unknown evidence class {data['class']!r}",
            )
        if "state" in data and data["state"] not in EVIDENCE_STATES:
            _issue(
                issues,
                "invalid-value",
                record.record_id,
                f"unknown evidence state {data['state']!r}",
            )
        claim = data.get("claim")
        if "claim" in data and (not isinstance(claim, str) or not claim.strip()):
            _issue(issues, "invalid-value", record.record_id, "claim must be a non-empty string")

    elif record.family == "sources":
        assessment = _as_mapping(data.get("silicon_assessment"))
        applicability = assessment.get("applicability")
        if applicability is not None and applicability not in SOURCE_APPLICABILITY:
            _issue(
                issues,
                "invalid-value",
                record.record_id,
                f"unknown source applicability {applicability!r}",
            )
        if "claims" in data and not isinstance(data["claims"], list):
            _issue(issues, "invalid-value", record.record_id, "claims must be a list")

    elif record.family == "validations":
        if "case_id" in data:
            case_id = data.get("case_id")
            if not isinstance(case_id, str) or not ID_PATTERNS["cases"].fullmatch(case_id):
                _issue(
                    issues,
                    "invalid-reference",
                    record.record_id,
                    f"case_id {case_id!r} is not a CASE-#### identifier",
                )
        environment = _as_mapping(data.get("environment"))
        environment_type = environment.get("type")
        if "environment" in data and environment_type not in ENVIRONMENT_TYPES:
            _issue(
                issues,
                "invalid-value",
                record.record_id,
                f"unknown environment type {environment_type!r}",
            )
        result = _as_mapping(data.get("result"))
        status = result.get("status")
        if "result" in data and status not in VALIDATION_STATUSES:
            _issue(
                issues,
                "invalid-value",
                record.record_id,
                f"unknown validation status {status!r}",
            )
        if "inputs" in data and not isinstance(data["inputs"], list):
            _issue(issues, "invalid-value", record.record_id, "inputs must be a list")

    elif record.family == "cases":
        if "status" in data and data["status"] not in CASE_STATUSES:
            _issue(
                issues,
                "invalid-value",
                record.record_id,
                f"unknown case status {data['status']!r}",
            )
        kinds = data.get("kinds")
        if "kinds" in data and (not isinstance(kinds, list) or not kinds):
            _issue(issues, "invalid-value", record.record_id, "kinds must be a non-empty list")
        evidence = data.get("evidence")
        if "evidence" in data and not isinstance(evidence, Mapping):
            _issue(issues, "invalid-value", record.record_id, "evidence must be a mapping")


def _collect_reference_fields(record: Record, issues: list[Issue]) -> dict[str, list[str]]:
    found: dict[str, list[str]] = {}
    for field, family, prefix in REFERENCE_FIELDS[record.family]:
        value = _get(record.data, field)
        if value is None:
            continue
        if not isinstance(value, list):
            _issue(
                issues,
                "invalid-field-type",
                record.record_id,
                f"{field} must be a list of {prefix}-#### identifiers",
            )
            continue
        references: list[str] = []
        for item in value:
            if not isinstance(item, str) or not ID_PATTERNS[family].fullmatch(item):
                _issue(
                    issues,
                    "invalid-reference",
                    record.record_id,
                    f"{field} contains {item!r}, expected {prefix}-####",
                )
                continue
            references.append(item)
        found[field] = references
    return found


def _check_references(
    by_family: Mapping[str, Mapping[str, Record]],
    references: Mapping[str, Mapping[str, list[str]]],
    issues: list[Issue],
) -> None:
    for family, records in by_family.items():
        for record in records.values():
            for field, target_family, _prefix in REFERENCE_FIELDS[family]:
                for reference in (
                    references.get(family, {}).get(record.record_id, {}).get(field, [])
                ):
                    if reference not in by_family.get(target_family, {}):
                        _issue(
                            issues,
                            "missing-reference",
                            record.record_id,
                            f"{field} references {reference}, which does not exist",
                        )


def _check_target_manifests(
    by_family: Mapping[str, Mapping[str, Record]],
    root: Path,
    issues: list[Issue],
) -> None:
    for family, fields in TARGET_MANIFEST_FIELDS.items():
        for record in by_family.get(family, {}).values():
            for field in fields:
                value = record.data.get(field)
                if value is None:
                    continue
                if not isinstance(value, str) or not value:
                    _issue(
                        issues,
                        "invalid-field-type",
                        record.record_id,
                        f"{field} must be a repository-relative path",
                    )
                    continue
                candidate = root / value
                if not candidate.is_file():
                    _issue(
                        issues,
                        "missing-target-manifest",
                        record.record_id,
                        f"{field} points to {value}, which does not exist",
                    )


def _case_evidence(case: Record) -> set[str]:
    evidence = _as_mapping(case.data.get("evidence"))
    return set(_strings(evidence.get("supporting"))) | set(_strings(evidence.get("counter")))


def _check_case_symmetry(
    by_family: Mapping[str, Mapping[str, Record]], issues: list[Issue]
) -> None:
    evidence = by_family.get("evidence", {})
    cases = by_family.get("cases", {})

    for case in cases.values():
        for evidence_id in _case_evidence(case):
            related = evidence.get(evidence_id)
            if related is None:
                continue
            related_cases = set(_strings(related.data.get("related_cases")))
            if case.record_id not in related_cases:
                _issue(
                    issues,
                    "asymmetric-link",
                    related.record_id,
                    f"{case.record_id} cites this record but related_cases does not list it",
                )

    for record in evidence.values():
        for case_id in _strings(record.data.get("related_cases")):
            case = cases.get(case_id)
            if case is None:
                continue
            if record.record_id not in _case_evidence(case):
                _issue(
                    issues,
                    "asymmetric-link",
                    record.record_id,
                    f"related_cases lists {case_id} but that case does not cite this record",
                )


def _check_validation_symmetry(
    by_family: Mapping[str, Mapping[str, Record]], issues: list[Issue]
) -> None:
    validations = by_family.get("validations", {})
    cases = by_family.get("cases", {})

    for validation in validations.values():
        case_id = validation.data.get("case_id")
        if not isinstance(case_id, str):
            continue
        case = cases.get(case_id)
        if case is None:
            _issue(
                issues,
                "missing-reference",
                validation.record_id,
                f"case_id references {case_id}, which does not exist",
            )
            continue
        listed = set(_strings(_as_mapping(case.data.get("validation")).get("validation_ids")))
        if validation.record_id not in listed:
            _issue(
                issues,
                "asymmetric-link",
                validation.record_id,
                f"case_id is {case_id} but that case's validation_ids does not list it",
            )

    for case in cases.values():
        listed = _strings(_as_mapping(case.data.get("validation")).get("validation_ids"))
        for validation_id in listed:
            validation = validations.get(validation_id)
            if validation is not None and validation.data.get("case_id") != case.record_id:
                _issue(
                    issues,
                    "case-validation-mismatch",
                    case.record_id,
                    f"validation_ids lists {validation_id} but its case_id is "
                    f"{validation.data.get('case_id')!r}",
                )


def _manifest_evidence_refs(node: Any, location: str = "") -> Iterable[tuple[str, str]]:
    if isinstance(node, Mapping):
        for key, value in node.items():
            child = f"{location}.{key}" if location else str(key)
            if key == "evidence" and isinstance(value, list):
                for index, item in enumerate(value):
                    yield f"{child}[{index}]", item
            else:
                yield from _manifest_evidence_refs(value, child)
    elif isinstance(node, list):
        for index, item in enumerate(node):
            yield from _manifest_evidence_refs(item, f"{location}[{index}]")


def _check_target_manifest_links(
    by_family: Mapping[str, Mapping[str, Record]], root: Path, issues: list[Issue]
) -> None:
    evidence = by_family.get("evidence", {})
    manifests = root / "targets/manifests"
    if not manifests.is_dir():
        _issue(issues, "missing-target-directory", "targets/manifests", "directory does not exist")
        return
    for path in sorted(manifests.glob("*.yaml")):
        relative = path.relative_to(root)
        try:
            document = yaml.safe_load(path.read_text(encoding="utf-8"))
        except (OSError, UnicodeError, yaml.YAMLError) as exc:
            _issue(issues, "unreadable-target-manifest", str(relative), str(exc))
            continue
        for location, reference in _manifest_evidence_refs(document):
            if not isinstance(reference, str) or not ID_PATTERNS["evidence"].fullmatch(
                reference
            ):
                _issue(
                    issues,
                    "invalid-reference",
                    str(relative),
                    f"{location} contains {reference!r}, expected EVD-####",
                )
            elif reference not in evidence:
                _issue(
                    issues,
                    "missing-reference",
                    str(relative),
                    f"{location} references {reference}, which does not exist",
                )


def _check_indexes(
    by_family: Mapping[str, Mapping[str, Record]], root: Path, issues: list[Issue]
) -> None:
    for family, relative in INDEX_FILES.items():
        records = by_family.get(family, {})
        if not records:
            continue
        path = root / relative
        if not path.is_file():
            _issue(issues, "missing-index", family, f"{relative} does not exist")
            continue
        try:
            text = path.read_text(encoding="utf-8")
        except (OSError, UnicodeError) as exc:
            _issue(issues, "unreadable-index", str(relative), str(exc))
            continue
        pattern = ID_PATTERNS[family]
        mentioned = set(re.findall(rf"\b{pattern.pattern}\b", text))
        actual = set(records)
        for missing in sorted(actual - mentioned):
            _issue(
                issues,
                "index-missing-id",
                missing,
                f"{relative} does not list this record",
            )
        for unknown in sorted(mentioned - actual):
            _issue(
                issues,
                "index-unknown-id",
                unknown,
                f"{relative} lists this identifier but no record exists",
            )


def validate_records(
    records: Mapping[str, Sequence[Record]],
    *,
    root: str | Path,
    check_indexes: bool = True,
    check_manifest_links: bool = True,
) -> list[Issue]:
    """Validate a loaded record set. Pure with respect to the record files."""
    issues: list[Issue] = []
    by_family: dict[str, dict[str, Record]] = {}
    seen: dict[tuple[str, str], Record] = {}

    for family, family_records in records.items():
        by_family[family] = {}
        for record in family_records:
            _check_identity(record, issues)
            if record.error:
                continue
            _check_required_fields(record, issues)
            _check_values(record, issues)
            key = (family, record.record_id)
            if key in seen:
                _issue(
                    issues,
                    "duplicate-id",
                    record.record_id,
                    f"{record.path} and {seen[key].path} share this identifier",
                )
            else:
                seen[key] = record
                by_family[family][record.record_id] = record

    references = {
        family: {
            record_id: _collect_reference_fields(record, issues)
            for record_id, record in family_records.items()
        }
        for family, family_records in by_family.items()
    }

    _check_references(by_family, references, issues)
    _check_target_manifests(by_family, Path(root), issues)
    _check_case_symmetry(by_family, issues)
    _check_validation_symmetry(by_family, issues)
    if check_manifest_links:
        _check_target_manifest_links(by_family, Path(root), issues)
    if check_indexes:
        _check_indexes(by_family, Path(root), issues)

    return sorted(set(issues), key=lambda item: (item.record, item.code, item.message))


def inspect_repository(root: str | Path = ".") -> dict[str, Any]:
    """Load and validate the record families under ``root``."""
    base = Path(root)
    records, load_issues = load_records(base)
    issues = load_issues + validate_records(records, root=base)
    counts = {family: len(items) for family, items in sorted(records.items())}
    return {
        "ok": not any(issue.severity == "error" for issue in issues),
        "counts": counts,
        "issues": [issue.as_dict() for issue in issues],
    }


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "root",
        nargs="?",
        type=Path,
        default=Path("."),
        help="repository root to inspect (default: current directory)",
    )
    args = parser.parse_args(argv)

    if not args.root.is_dir():
        print(f"error: {args.root} is not a directory", file=sys.stderr)
        return 2

    report = inspect_repository(args.root)
    sys.stdout.write(json.dumps(report, indent=2, sort_keys=True) + "\n")
    return 0 if report["ok"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
