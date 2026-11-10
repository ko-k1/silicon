"""Unit tests for the deterministic archive manifest tool."""

from __future__ import annotations

import hashlib
import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

from engineering.inventory.archive_manifest import (
    build_manifest,
    git_tracked_paths,
    hash_file,
    render_manifest,
)

REPO_ROOT = Path(__file__).resolve().parents[2]
EMPTY_SHA256 = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"


class ArchiveManifestTests(unittest.TestCase):
    def test_build_manifest_hashes_and_sorts(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "b.txt").write_bytes(b"beta")
            (root / "a.txt").write_bytes(b"alpha")

            manifest = build_manifest(root, ["b.txt", "a.txt", "a.txt"])

        self.assertEqual(1, manifest["manifest_version"])
        self.assertEqual("silicon", manifest["project"])
        self.assertEqual("silicon-repository", manifest["archive"])
        self.assertEqual("sha256", manifest["algorithm"])
        self.assertEqual(2, manifest["file_count"])
        self.assertEqual(["a.txt", "b.txt"], [item["path"] for item in manifest["files"]])
        self.assertEqual(5, manifest["files"][0]["bytes"])
        self.assertEqual(
            hashlib.sha256(b"alpha").hexdigest(),
            manifest["files"][0]["sha256"],
        )

    def test_empty_and_excluded_files(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "empty.bin").write_bytes(b"")
            (root / "skip.txt").write_bytes(b"skip")

            manifest = build_manifest(root, ["empty.bin", "skip.txt"], exclude=["skip.txt"])

        self.assertEqual(1, manifest["file_count"])
        self.assertEqual(EMPTY_SHA256, manifest["files"][0]["sha256"])
        self.assertEqual(0, manifest["files"][0]["bytes"])

    def test_escaping_and_absolute_paths_are_rejected(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "inside.txt").write_bytes(b"inside")

            with self.assertRaises(ValueError):
                build_manifest(root, ["../outside.txt"])
            with self.assertRaises(ValueError):
                build_manifest(root, [str(root / "inside.txt")])

    def test_missing_file_is_reported_not_invented(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            with self.assertRaises(FileNotFoundError):
                build_manifest(directory, ["missing.txt"])

    def test_symlink_is_rejected(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "target.txt").write_bytes(b"target")
            try:
                (root / "link.txt").symlink_to("target.txt")
            except OSError as exc:
                self.skipTest(f"symlinks are unavailable: {exc}")

            with self.assertRaises(ValueError):
                build_manifest(root, ["link.txt"])

    def test_hash_file_matches_hashlib(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "data.bin"
            path.write_bytes(b"payload")

            size, digest = hash_file(path)

        self.assertEqual(7, size)
        self.assertEqual(hashlib.sha256(b"payload").hexdigest(), digest)

    def test_git_tracked_paths_include_current_records(self) -> None:
        paths = git_tracked_paths(REPO_ROOT)

        self.assertIn("README.md", paths)
        self.assertIn("MANIFEST.json", paths)
        self.assertIn("engineering/inventory/archive_manifest.py", paths)

    def test_repository_manifest_matches_git_index(self) -> None:
        expected = build_manifest(
            REPO_ROOT,
            git_tracked_paths(REPO_ROOT),
            exclude=["MANIFEST.json"],
        )
        actual_text = (REPO_ROOT / "MANIFEST.json").read_text(encoding="utf-8")

        self.assertEqual(expected, json.loads(actual_text))
        self.assertEqual(render_manifest(expected), actual_text)

    def test_cli_writes_and_checks_a_manifest(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "a.txt").write_text("alpha", encoding="utf-8")
            subprocess.run(["git", "init", "-q"], cwd=root, check=True)
            subprocess.run(["git", "add", "a.txt"], cwd=root, check=True)
            output = root / "MANIFEST.json"
            command = [
                sys.executable,
                "-m",
                "engineering.inventory.archive_manifest",
                str(root),
            ]

            written = subprocess.run(
                command + ["--output", str(output)],
                cwd=REPO_ROOT,
                check=False,
                capture_output=True,
                text=True,
            )
            checked = subprocess.run(
                command + ["--check", str(output)],
                cwd=REPO_ROOT,
                check=False,
                capture_output=True,
                text=True,
            )

            self.assertEqual(0, written.returncode, written.stderr)
            self.assertTrue(output.is_file())
            self.assertEqual(0, checked.returncode, checked.stderr)

            (root / "a.txt").write_text("changed", encoding="utf-8")
            stale = subprocess.run(
                command + ["--check", str(output)],
                cwd=REPO_ROOT,
                check=False,
                capture_output=True,
                text=True,
            )

        self.assertEqual(1, stale.returncode)
        self.assertIn("stale", stale.stderr)


if __name__ == "__main__":
    unittest.main()
