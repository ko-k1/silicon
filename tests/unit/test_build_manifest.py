"""Unit tests for the BuildManifest packaging summarizer."""

from __future__ import annotations

import hashlib
import json
import plistlib
import subprocess
import sys
import unittest
from pathlib import Path

from engineering.inventory.build_manifest import summarize, summarize_path

FIXTURE = Path(__file__).parent / "fixtures" / "BuildManifest.minimal.plist"
DIGEST_HEX = bytes(range(48)).hex()


class BuildManifestSummaryTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.summary = summarize_path(FIXTURE)

    def test_build_identity_and_variant_markers(self) -> None:
        self.assertEqual("27.0.1", self.summary["product_version"])
        self.assertEqual("24A446", self.summary["product_build_version"])
        self.assertEqual(["iPhone13,1"], self.summary["supported_product_types"])
        self.assertEqual(1, self.summary["identity_count"])

        identity = self.summary["identities"][0]
        self.assertEqual("Customer Erase Install (IPSW)", identity["variant"])
        self.assertEqual("24A446", identity["build_number"])
        self.assertEqual("d52gap", identity["device_class"])
        self.assertEqual("D52gRestoreIPSW", identity["image_name"])
        self.assertEqual(
            {
                "InstalledSPTM": "Production",
                "RestoreSPTM": "Production",
                "InstalledKernelCache": "Production",
                "RestoreKernelCache": "Production",
            },
            identity["variant_contents"],
        )

    def test_components_paths_digests_and_flags(self) -> None:
        components = self.summary["identities"][0]["components"]

        self.assertEqual(
            {
                "key": "Ap,SecurePageTableMonitor",
                "present": True,
                "path": "Firmware/sptm.t8101.release.im4p",
                "digest_hex": DIGEST_HEX,
                "info": {
                    "Trusted": True,
                    "IsLoadedByiBoot": False,
                    "IsFUDFirmware": True,
                    "Personalize": True,
                },
            },
            components["installed_sptm"],
        )
        self.assertEqual(
            "Firmware/txm.iphoneos.release.im4p",
            components["installed_txm"]["path"],
        )
        self.assertTrue(components["restore_sptm"]["info"]["IsLoadedByiBoot"])
        self.assertTrue(components["restore_txm"]["info"]["IsLoadedByiBoot"])
        self.assertEqual(
            {
                "Trusted": True,
                "IsLoadedByiBoot": True,
                "IsFUDFirmware": False,
                "Personalize": False,
            },
            components["restore_txm"]["info"],
        )

    def test_kernelcache_references(self) -> None:
        kernelcache = self.summary["identities"][0]["kernelcache"]

        self.assertEqual(
            {
                "key": "KernelCache",
                "present": True,
                "path": "kernelcache.release.iphone13",
                "digest_hex": DIGEST_HEX,
                "info": {"IsLoadedByiBoot": True},
            },
            kernelcache["installed_kernelcache"],
        )
        self.assertEqual(
            "kernelcache.release.iphone13",
            kernelcache["restore_kernelcache"]["path"],
        )

    def test_missing_component_is_reported_not_invented(self) -> None:
        manifest = plistlib.loads(FIXTURE.read_bytes())
        del manifest["BuildIdentities"][0]["Manifest"]["Ap,TrustedExecutionMonitor"]

        summary = summarize(manifest, artifact_sha256="0" * 64, artifact_bytes=0)

        self.assertEqual(
            {"key": "Ap,TrustedExecutionMonitor", "present": False},
            summary["identities"][0]["components"]["installed_txm"],
        )
        self.assertTrue(summary["identities"][0]["components"]["installed_sptm"]["present"])

    def test_artifact_identity_matches_input(self) -> None:
        data = FIXTURE.read_bytes()
        self.assertEqual(hashlib.sha256(data).hexdigest(), self.summary["artifact"]["sha256"])
        self.assertEqual(len(data), self.summary["artifact"]["bytes"])

    def test_cli_emits_the_same_summary(self) -> None:
        completed = subprocess.run(
            [
                sys.executable,
                "-m",
                "engineering.inventory.build_manifest",
                str(FIXTURE),
            ],
            check=False,
            capture_output=True,
            text=True,
        )
        self.assertEqual(0, completed.returncode, completed.stderr)
        self.assertEqual(self.summary, json.loads(completed.stdout))


if __name__ == "__main__":
    unittest.main()
