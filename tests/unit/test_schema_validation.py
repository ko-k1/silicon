"""Unit tests for JSON Schema validation of repository records."""

from __future__ import annotations

import json
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

import yaml

from engineering.inventory.schema_validation import (
    FAMILIES,
    load_validator,
    validate_document,
    validate_repository,
)

REPO_ROOT = Path(__file__).resolve().parents[2]
SCHEMAS = REPO_ROOT / "schemas"


def load_yaml(relative: str) -> dict:
    return yaml.safe_load((REPO_ROOT / relative).read_text(encoding="utf-8"))


class SchemaValidationTests(unittest.TestCase):
    def issues(
        self,
        document: object,
        schema_name: str,
        *,
        family: str = "test",
        record: str = "TEST-0000",
    ) -> list:
        return validate_document(
            document,
            load_validator(SCHEMAS / schema_name),
            family=family,
            record=record,
            path=f"test/{record}.yaml",
            schema_name=schema_name,
        )

    def test_repository_records_validate(self) -> None:
        report = validate_repository(REPO_ROOT)

        self.assertTrue(report["ok"], report["issues"])
        self.assertEqual([], report["issues"])
        for family in FAMILIES:
            expected = len(
                list((REPO_ROOT / family.directory).glob(family.pattern))
            )
            self.assertEqual(expected, report["counts"][family.name])

    def test_committed_templates_validate(self) -> None:
        templates = (
            ("cases", "research/cases/_template/case.yaml", "research-case.schema.json"),
            (
                "sources",
                "research/public-research/source-record.template.yaml",
                "source-record.schema.json",
            ),
            (
                "validations",
                "validation/results/result.template.yaml",
                "validation-result.schema.json",
            ),
            (
                "targets",
                "targets/manifests/target-manifest.template.yaml",
                "target-manifest.schema.json",
            ),
        )

        for family, relative, schema_name in templates:
            with self.subTest(template=relative):
                issues = self.issues(
                    load_yaml(relative),
                    schema_name,
                    family=family,
                    record=Path(relative).stem,
                )
                self.assertEqual([], issues)

    def test_evidence_enum_and_required_field_are_reported(self) -> None:
        document = load_yaml("research/evidence/EVD-0001.yaml")
        document["state"] = "proven"
        del document["limitations"]

        issues = self.issues(
            document,
            "evidence-record.schema.json",
            family="evidence",
            record="EVD-0001",
        )

        self.assertEqual({"/state", ""}, {issue.location for issue in issues})
        messages = " ".join(issue.message for issue in issues)
        self.assertIn("'proven'", messages)
        self.assertIn("'limitations'", messages)

    def test_source_identifier_pattern_is_reported(self) -> None:
        document = load_yaml("research/public-research/SRC-0001.yaml")
        document["id"] = "SRC-1"

        issues = self.issues(
            document,
            "source-record.schema.json",
            family="sources",
            record="SRC-0001",
        )

        self.assertEqual(1, len(issues))
        self.assertEqual("/id", issues[0].location)
        self.assertIn("does not match", issues[0].message)

    def test_validation_status_enum_is_reported(self) -> None:
        document = load_yaml("validation/results/VAL-0002.yaml")
        document["result"]["status"] = "ok"

        issues = self.issues(
            document,
            "validation-result.schema.json",
            family="validations",
            record="VAL-0002",
        )

        self.assertEqual(["/result/status"], [issue.location for issue in issues])

    def test_case_kinds_minimum_is_reported(self) -> None:
        document = load_yaml("research/cases/CASE-0001/case.yaml")
        document["kinds"] = []

        issues = self.issues(
            document,
            "research-case.schema.json",
            family="cases",
            record="CASE-0001",
        )

        self.assertEqual(["/kinds"], [issue.location for issue in issues])

    def test_target_manifest_protection_enum_is_reported(self) -> None:
        document = load_yaml("targets/manifests/iphone12mini-ios27.0.1.yaml")
        document["protection"]["SPTM"]["state"] = "active"

        issues = self.issues(
            document,
            "target-manifest.schema.json",
            family="targets",
            record="iphone12mini-ios27.0.1",
        )

        self.assertEqual(
            ["/protection/SPTM/state"], [issue.location for issue in issues]
        )

    def test_malformed_yaml_is_reported_not_raised(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            shutil.copytree(SCHEMAS, root / "schemas")
            evidence = root / "research/evidence"
            evidence.mkdir(parents=True)
            (evidence / "EVD-9999.yaml").write_text(
                "id: [unclosed\n", encoding="utf-8"
            )

            report = validate_repository(root, families=["evidence"])

        self.assertFalse(report["ok"])
        self.assertEqual(1, report["counts"]["evidence"])
        self.assertEqual(["unreadable-record"], [item["code"] for item in report["issues"]])

    def test_cli_output_is_deterministic_and_zero(self) -> None:
        command = [
            sys.executable,
            "-m",
            "engineering.inventory.schema_validation",
            ".",
        ]
        first = subprocess.run(
            command, cwd=REPO_ROOT, check=False, capture_output=True, text=True
        )
        second = subprocess.run(
            command, cwd=REPO_ROOT, check=False, capture_output=True, text=True
        )

        self.assertEqual(0, first.returncode, first.stderr)
        self.assertEqual(first.stdout, second.stdout)
        report = json.loads(first.stdout)
        self.assertTrue(report["ok"])
        self.assertEqual(
            first.stdout,
            json.dumps(report, indent=2, sort_keys=True) + "\n",
        )


if __name__ == "__main__":
    unittest.main()
