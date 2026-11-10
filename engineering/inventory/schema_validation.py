"""Deterministic, read-only JSON Schema validation for repository records.

The validator answers a narrow question: does each committed target manifest,
evidence record, source record, validation result, and research case conform to
its schema in ``schemas/``? It checks structure, enums, identifier patterns, and
required fields only.

It does not check cross-references between records, verify artifact hashes, fetch
sources, or rewrite any record. Use ``record_integrity`` for cross-reference and
index checks.
"""

from __future__ import annotations

import argparse
import json
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Iterable, Sequence

import yaml
from jsonschema import Draft202012Validator
from jsonschema.exceptions import SchemaError


@dataclass(frozen=True)
class Family:
    """One record family and the schema that defines it."""

    name: str
    directory: str
    pattern: str
    schema_name: str


FAMILIES = (
    Family("evidence", "research/evidence", "EVD-*.yaml", "evidence-record.schema.json"),
    Family(
        "sources",
        "research/public-research",
        "SRC-*.yaml",
        "source-record.schema.json",
    ),
    Family(
        "validations",
        "validation/results",
        "VAL-*.yaml",
        "validation-result.schema.json",
    ),
    Family(
        "cases",
        "research/cases",
        "CASE-*/case.yaml",
        "research-case.schema.json",
    ),
    Family(
        "targets",
        "targets/manifests",
        "*.yaml",
        "target-manifest.schema.json",
    ),
)

FAMILY_BY_NAME = {family.name: family for family in FAMILIES}


@dataclass(frozen=True)
class Issue:
    """One schema finding, keyed to a repository record and JSON location."""

    code: str
    family: str
    record: str
    path: str
    schema: str
    location: str
    message: str

    def as_dict(self) -> dict[str, str]:
        return {
            "code": self.code,
            "family": self.family,
            "record": self.record,
            "path": self.path,
            "schema": self.schema,
            "location": self.location,
            "message": self.message,
        }


def load_validator(schema_path: str | Path) -> Draft202012Validator:
    """Load and check one JSON Schema document."""
    schema = json.loads(Path(schema_path).read_text(encoding="utf-8"))
    Draft202012Validator.check_schema(schema)
    return Draft202012Validator(schema)


def _pointer(parts: Iterable[Any]) -> str:
    encoded = [str(part).replace("~", "~0").replace("/", "~1") for part in parts]
    return "/" + "/".join(encoded) if encoded else ""


def validate_document(
    document: Any,
    validator: Draft202012Validator,
    *,
    family: str,
    record: str,
    path: str,
    schema_name: str,
) -> list[Issue]:
    """Validate one already-loaded document against a schema validator."""
    issues: list[Issue] = []
    errors = sorted(
        validator.iter_errors(document),
        key=lambda error: (
            tuple(str(part) for part in error.absolute_path),
            error.message,
        ),
    )
    for error in errors:
        issues.append(
            Issue(
                code="schema-violation",
                family=family,
                record=record,
                path=path,
                schema=schema_name,
                location=_pointer(error.absolute_path),
                message=error.message,
            )
        )
    return issues


def _record_label(family: Family, path: Path) -> str:
    if family.name == "cases":
        return path.parent.name
    return path.stem


def _select_families(names: Sequence[str] | None) -> tuple[Family, ...]:
    if names is None:
        return FAMILIES
    unknown = sorted(set(names) - set(FAMILY_BY_NAME))
    if unknown:
        raise ValueError(f"unknown record families: {', '.join(unknown)}")
    return tuple(family for family in FAMILIES if family.name in names)


def validate_repository(
    root: str | Path = ".", *, families: Sequence[str] | None = None
) -> dict[str, Any]:
    """Validate every record family under ``root`` without modifying it."""
    base = Path(root)
    selected = _select_families(families)
    counts: dict[str, int] = {}
    issues: list[Issue] = []

    for family in selected:
        schema_path = base / "schemas" / family.schema_name
        relative_schema = schema_path.relative_to(base)
        try:
            validator = load_validator(schema_path)
        except (OSError, UnicodeError, json.JSONDecodeError, SchemaError) as exc:
            issues.append(
                Issue(
                    code="invalid-schema",
                    family=family.name,
                    record=family.schema_name,
                    path=str(relative_schema),
                    schema=family.schema_name,
                    location="",
                    message=f"cannot load schema: {exc}",
                )
            )
            counts[family.name] = 0
            continue

        directory = base / family.directory
        if not directory.is_dir():
            issues.append(
                Issue(
                    code="missing-record-directory",
                    family=family.name,
                    record=family.directory,
                    path=family.directory,
                    schema=family.schema_name,
                    location="",
                    message="directory does not exist",
                )
            )
            counts[family.name] = 0
            continue

        paths = sorted(directory.glob(family.pattern))
        counts[family.name] = len(paths)
        for path in paths:
            relative = path.relative_to(base)
            record = _record_label(family, path)
            try:
                document = yaml.safe_load(path.read_text(encoding="utf-8"))
            except (OSError, UnicodeError, yaml.YAMLError) as exc:
                issues.append(
                    Issue(
                        code="unreadable-record",
                        family=family.name,
                        record=record,
                        path=str(relative),
                        schema=family.schema_name,
                        location="",
                        message=f"cannot parse: {exc}",
                    )
                )
                continue
            issues.extend(
                validate_document(
                    document,
                    validator,
                    family=family.name,
                    record=record,
                    path=str(relative),
                    schema_name=family.schema_name,
                )
            )

    sorted_issues = sorted(
        issues, key=lambda item: (item.path, item.location, item.message, item.code)
    )
    return {
        "ok": not sorted_issues,
        "counts": counts,
        "issues": [issue.as_dict() for issue in sorted_issues],
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

    report = validate_repository(args.root)
    sys.stdout.write(json.dumps(report, indent=2, sort_keys=True) + "\n")
    return 0 if report["ok"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
