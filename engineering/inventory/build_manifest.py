"""Deterministic, read-only summary of an Apple BuildManifest.plist.

The summary answers a narrow packaging question: which build identities does a
restore manifest declare, and does each identity reference SPTM, TXM, and
kernelcache payloads, with which variant markers and payload digests?

This module does not fetch artifacts, verify signatures, or measure runtime
protection state. Missing components are reported as ``present: false`` rather
than inferred.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import plistlib
import sys
from pathlib import Path
from typing import Any, Sequence

# (summary label, BuildManifest key)
COMPONENTS = (
    ("installed_sptm", "Ap,SecurePageTableMonitor"),
    ("installed_txm", "Ap,TrustedExecutionMonitor"),
    ("restore_sptm", "Ap,RestoreSecurePageTableMonitor"),
    ("restore_txm", "Ap,RestoreTrustedExecutionMonitor"),
)

KERNELCACHE_COMPONENTS = (
    ("installed_kernelcache", "KernelCache"),
    ("restore_kernelcache", "RestoreKernelCache"),
)

VARIANT_MARKERS = (
    "InstalledSPTM",
    "RestoreSPTM",
    "InstalledKernelCache",
    "RestoreKernelCache",
)

INFO_FLAGS = ("Trusted", "IsLoadedByiBoot", "IsFUDFirmware", "Personalize")


def _as_dict(value: Any) -> dict[str, Any]:
    return value if isinstance(value, dict) else {}


def _component(identity: dict[str, Any], key: str) -> dict[str, Any]:
    entry = _as_dict(_as_dict(identity.get("Manifest")).get(key))
    if not entry:
        return {"key": key, "present": False}

    info = _as_dict(entry.get("Info"))
    digest = entry.get("Digest")
    flags = {flag: info[flag] for flag in INFO_FLAGS if flag in info}
    if "Trusted" in entry:
        flags["Trusted"] = entry["Trusted"]
    return {
        "key": key,
        "present": True,
        "path": info.get("Path"),
        "digest_hex": digest.hex() if isinstance(digest, bytes) else None,
        "info": flags,
    }


def summarize(
    manifest: dict[str, Any],
    *,
    artifact_sha256: str,
    artifact_bytes: int,
) -> dict[str, Any]:
    """Return a deterministic summary of the manifest's packaging metadata."""
    identities: list[dict[str, Any]] = []
    for identity in manifest.get("BuildIdentities") or []:
        if not isinstance(identity, dict):
            continue
        info = _as_dict(identity.get("Info"))
        variant_contents = _as_dict(info.get("VariantContents"))
        identities.append(
            {
                "variant": info.get("Variant"),
                "build_number": info.get("BuildNumber"),
                "device_class": info.get("DeviceClass"),
                "image_name": info.get("ImageName"),
                "variant_contents": {
                    key: variant_contents.get(key) for key in VARIANT_MARKERS
                },
                "components": {
                    label: _component(identity, key) for label, key in COMPONENTS
                },
                "kernelcache": {
                    label: _component(identity, key)
                    for label, key in KERNELCACHE_COMPONENTS
                },
            }
        )

    supported = manifest.get("SupportedProductTypes")
    return {
        "artifact": {"sha256": artifact_sha256, "bytes": artifact_bytes},
        "product_version": manifest.get("ProductVersion"),
        "product_build_version": manifest.get("ProductBuildVersion"),
        "supported_product_types": (
            list(supported) if isinstance(supported, list) else []
        ),
        "identity_count": len(identities),
        "identities": identities,
    }


def summarize_path(path: str | Path) -> dict[str, Any]:
    """Read a BuildManifest.plist and return its packaging summary."""
    data = Path(path).read_bytes()
    manifest = plistlib.loads(data)
    if not isinstance(manifest, dict):
        raise ValueError("BuildManifest root is not a dictionary")
    return summarize(
        manifest,
        artifact_sha256=hashlib.sha256(data).hexdigest(),
        artifact_bytes=len(data),
    )


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("manifest", type=Path, help="path to BuildManifest.plist")
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        help="write JSON to this path instead of stdout",
    )
    args = parser.parse_args(argv)

    try:
        summary = summarize_path(args.manifest)
    except (OSError, plistlib.InvalidFileException, ValueError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 2

    text = json.dumps(summary, indent=2, sort_keys=True) + "\n"
    if args.output:
        args.output.write_text(text, encoding="utf-8")
    else:
        sys.stdout.write(text)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
