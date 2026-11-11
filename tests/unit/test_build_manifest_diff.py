"""Unit tests for the BuildManifest differential summarizer."""

from __future__ import annotations

import hashlib
import json
import plistlib
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

from engineering.analyzers.build_manifest_diff import diff_paths

FIXTURE = Path(__file__).parent / "fixtures" / "BuildManifest.minimal.plist"


def _load() -> dict:
    return plistlib.loads(FIXTURE.read_bytes())


class BuildManifestDiffTests(unittest.TestCase):
    def setUp(self) -> None:
        self.temp_dir = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp_dir.cleanup)
        self.root = Path(self.temp_dir.name)

    def _write(self, name: str, manifest: dict) -> Path:
        path = self.root / name
        path.write_bytes(plistlib.dumps(manifest))
        return path

    def test_identical_manifests_have_no_changes(self) -> None:
        diff = diff_paths(FIXTURE, FIXTURE)

        self.assertEqual(1, diff["identity_count_old"])
        self.assertEqual(1, diff["identity_count_new"])
        self.assertEqual("27.0.1", diff["old"]["product_version"])
        self.assertEqual("24A446", diff["new"]["product_build_version"])
        self.assertEqual(6, diff["summary"]["components_compared"])
        self.assertEqual(6, diff["summary"]["same"])
        self.assertEqual(0, diff["summary"]["changed_count"])
        self.assertEqual([], diff["summary"]["added"])
        self.assertEqual([], diff["summary"]["removed"])
        self.assertEqual([], diff["summary"]["changed"])

    def test_changed_digest_path_and_flags_are_reported(self) -> None:
        changed = _load()
        identity = changed["BuildIdentities"][0]
        kernel = identity["Manifest"]["KernelCache"]
        kernel["Digest"] = b"\xff" * 48
        kernel["Info"]["Path"] = "kernelcache.release.changed"
        kernel["Info"]["Personalize"] = True
        changed_path = self._write("changed.plist", changed)

        diff = diff_paths(FIXTURE, changed_path)
        entry = next(
            item for item in diff["summary"]["changed"] if item["key"] == "KernelCache"
        )

        self.assertEqual("kernelcache.release.iphone13", entry["path_old"])
        self.assertEqual("kernelcache.release.changed", entry["path_new"])
        self.assertEqual(bytes(range(48)).hex(), entry["digest_old"])
        self.assertEqual("ff" * 48, entry["digest_new"])
        self.assertTrue(entry["info_changed"])
        self.assertTrue(entry["info_new"]["Personalize"])
        self.assertEqual(1, diff["summary"]["changed_count"])

    def test_added_and_removed_components_are_reported(self) -> None:
        new = _load()
        identity = new["BuildIdentities"][0]
        del identity["Manifest"]["Ap,TrustedExecutionMonitor"]
        identity["Manifest"]["Ap,NewComponent"] = {
            "Digest": b"\x11" * 48,
            "Info": {"Path": "Firmware/new.im4p", "Personalize": True},
        }
        new_path = self._write("new.plist", new)

        diff = diff_paths(FIXTURE, new_path)

        self.assertEqual(["Ap,NewComponent"], diff["summary"]["added"])
        self.assertEqual(["Ap,TrustedExecutionMonitor"], diff["summary"]["removed"])
        self.assertEqual(5, diff["summary"]["components_compared"])
        self.assertEqual(5, diff["summary"]["same"])
        self.assertEqual(0, diff["summary"]["changed_count"])

    def test_artifact_hashes_match_inputs(self) -> None:
        old_bytes = FIXTURE.read_bytes()
        new_path = self._write("copy.plist", _load())
        new_bytes = new_path.read_bytes()

        diff = diff_paths(FIXTURE, new_path)

        self.assertEqual(hashlib.sha256(old_bytes).hexdigest(), diff["old"]["artifact"]["sha256"])
        self.assertEqual(hashlib.sha256(new_bytes).hexdigest(), diff["new"]["artifact"]["sha256"])
        self.assertEqual(len(old_bytes), diff["old"]["artifact"]["bytes"])
        self.assertEqual(len(new_bytes), diff["new"]["artifact"]["bytes"])

    def test_cli_emits_the_same_summary(self) -> None:
        expected = diff_paths(FIXTURE, FIXTURE)
        completed = subprocess.run(
            [
                sys.executable,
                "-m",
                "engineering.analyzers.build_manifest_diff",
                str(FIXTURE),
                str(FIXTURE),
            ],
            check=False,
            capture_output=True,
            text=True,
        )
        self.assertEqual(0, completed.returncode, completed.stderr)
        self.assertEqual(expected, json.loads(completed.stdout))


if __name__ == "__main__":
    unittest.main()
