"""Unit tests for repository record integrity checks."""

from __future__ import annotations

import copy
import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

from engineering.inventory.record_integrity import (
    Record,
    inspect_repository,
    validate_records,
)

REPO_ROOT = Path(__file__).resolve().parents[2]
MANIFEST = "targets/manifests/iphone12mini-ios27.0.1.yaml"


def make_evidence(
    record_id: str = "EVD-0001", *, related_cases: list[str] | None = None
) -> dict:
    return {
        "schema_version": 1,
        "id": record_id,
        "class": "primary",
        "state": "observed",
        "claim": "Synthetic test claim.",
        "source": {"type": "test"},
        "artifact": None,
        "limitations": [],
        "related_cases": ["CASE-0001"] if related_cases is None else related_cases,
    }


def make_source(record_id: str = "SRC-0001") -> dict:
    return {
        "schema_version": 1,
        "id": record_id,
        "title": "Synthetic source",
        "source_type": "test",
        "url": "https://example.invalid/source",
        "published_at": None,
        "accessed_at": "2026-11-10",
        "source_scope": {},
        "claims": [],
        "silicon_assessment": {
            "applicability": "unknown",
            "evidence_ids": ["EVD-0001"],
        },
        "license_or_terms": "test fixture",
    }


def make_validation(
    record_id: str = "VAL-0001", *, case_id: str = "CASE-0001"
) -> dict:
    return {
        "schema_version": 1,
        "id": record_id,
        "case_id": case_id,
        "target_manifest": MANIFEST,
        "timestamp": None,
        "environment": {"type": "offline"},
        "inputs": [],
        "expected_outcome": None,
        "observed_outcome": None,
        "result": {"status": "passed", "reproducible": "yes", "summary": None},
        "related_evidence": ["EVD-0001"],
        "limitations": [],
    }


def make_case(
    record_id: str = "CASE-0001",
    *,
    supporting: list[str] | None = None,
    validation_ids: list[str] | None = None,
) -> dict:
    return {
        "schema_version": 1,
        "id": record_id,
        "status": "analyzed",
        "target_manifest": MANIFEST,
        "objective": "Synthetic test case.",
        "kinds": ["test"],
        "evidence": {
            "supporting": ["EVD-0001"] if supporting is None else supporting,
            "counter": [],
        },
        "validation": {
            "validation_ids": ["VAL-0001"] if validation_ids is None else validation_ids
        },
        "references": ["SRC-0001"],
    }


def make_record(
    family: str,
    document: dict,
    *,
    filename_id: str | None = None,
) -> Record:
    record_id = document["id"]
    filename = filename_id or record_id
    return Record(
        family=family,
        record_id=record_id,
        filename_id=filename,
        path=Path(f"{family}/{filename}.yaml"),
        data=document,
    )


def valid_records() -> dict[str, list[Record]]:
    return {
        "evidence": [make_record("evidence", make_evidence())],
        "sources": [make_record("sources", make_source())],
        "validations": [make_record("validations", make_validation())],
        "cases": [make_record("cases", make_case())],
    }


class RecordIntegrityTests(unittest.TestCase):
    def codes(self, records: dict[str, list[Record]], **kwargs) -> set[str]:
        issues = validate_records(
            records,
            root=REPO_ROOT,
            check_indexes=False,
            check_manifest_links=False,
            **kwargs,
        )
        return {issue.code for issue in issues}

    def test_valid_record_set_has_no_issues(self) -> None:
        self.assertEqual(
            [],
            validate_records(
                valid_records(),
                root=REPO_ROOT,
                check_indexes=False,
                check_manifest_links=False,
            ),
        )

    def test_missing_cross_reference_is_reported(self) -> None:
        records = valid_records()
        records["cases"][0].data["evidence"]["supporting"] = ["EVD-9999"]

        issues = validate_records(
            records,
            root=REPO_ROOT,
            check_indexes=False,
            check_manifest_links=False,
        )

        self.assertIn(
            ("missing-reference", "CASE-0001"),
            {(issue.code, issue.record) for issue in issues},
        )

    def test_asymmetric_case_evidence_link_is_reported(self) -> None:
        records = valid_records()
        records["evidence"][0].data["related_cases"] = []

        self.assertIn("asymmetric-link", self.codes(records))

    def test_case_can_cite_evidence_that_lists_a_different_case(self) -> None:
        records = valid_records()
        records["evidence"][0].data["related_cases"] = ["CASE-0002"]

        self.assertIn("asymmetric-link", self.codes(records))

    def test_validation_case_mismatch_is_reported(self) -> None:
        records = valid_records()
        records["cases"].append(
            make_record(
                "cases", make_case("CASE-0002", supporting=[], validation_ids=[])
            )
        )
        records["validations"][0].data["case_id"] = "CASE-0002"

        self.assertIn("case-validation-mismatch", self.codes(records))

    def test_duplicate_identifier_is_reported(self) -> None:
        records = valid_records()
        records["evidence"].append(
            make_record("evidence", make_evidence(), filename_id="EVD-0002")
        )

        self.assertIn("duplicate-id", self.codes(records))

    def test_filename_identifier_mismatch_is_reported(self) -> None:
        records = valid_records()
        records["evidence"][0] = make_record(
            "evidence", make_evidence(), filename_id="EVD-0002"
        )

        self.assertIn("filename-id-mismatch", self.codes(records))

    def test_required_fields_and_enumerations_are_checked(self) -> None:
        records = valid_records()
        bad = copy.deepcopy(records["evidence"][0].data)
        del bad["claim"]
        bad["class"] = "bogus"
        records["evidence"][0] = make_record("evidence", bad)

        codes = self.codes(records)
        self.assertIn("missing-required-field", codes)
        self.assertIn("invalid-value", codes)

    def test_target_manifest_evidence_reference_is_checked(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            manifests = root / "targets/manifests"
            manifests.mkdir(parents=True)
            (manifests / "target.yaml").write_text(
                "hardware:\n  soc:\n    evidence: [EVD-9999]\n",
                encoding="utf-8",
            )
            records = {"evidence": [make_record("evidence", make_evidence())]}

            issues = validate_records(records, root=root, check_indexes=False)

        self.assertIn(
            ("missing-reference", "targets/manifests/target.yaml"),
            {(issue.code, issue.record) for issue in issues},
        )

    def test_index_drift_is_reported(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            evidence_dir = root / "research/evidence"
            evidence_dir.mkdir(parents=True)
            (evidence_dir / "README.md").write_text(
                "| `EVD-0001` | current |\n| `EVD-0002` | stale |\n",
                encoding="utf-8",
            )
            records = {"evidence": [make_record("evidence", make_evidence())]}

            issues = validate_records(
                records,
                root=root,
                check_indexes=True,
                check_manifest_links=False,
            )

        self.assertIn(
            ("index-unknown-id", "EVD-0002"),
            {(issue.code, issue.record) for issue in issues},
        )

    def test_repository_records_are_internally_consistent(self) -> None:
        report = inspect_repository(REPO_ROOT)

        self.assertTrue(report["ok"], report["issues"])
        self.assertEqual(
            len(list((REPO_ROOT / "research/evidence").glob("EVD-*.yaml"))),
            report["counts"]["evidence"],
        )
        self.assertEqual(
            len(list((REPO_ROOT / "validation/results").glob("VAL-*.yaml"))),
            report["counts"]["validations"],
        )

    def test_cli_returns_zero_for_a_consistent_repository(self) -> None:
        completed = subprocess.run(
            [sys.executable, "-m", "engineering.inventory.record_integrity", "."],
            cwd=REPO_ROOT,
            check=False,
            capture_output=True,
            text=True,
        )

        self.assertEqual(0, completed.returncode, completed.stderr)
        report = json.loads(completed.stdout)
        self.assertTrue(report["ok"])
        self.assertEqual([], report["issues"])


if __name__ == "__main__":
    unittest.main()
