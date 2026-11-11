"""Deterministic, read-only diff of two Apple BuildManifest.plist files.

The summary answers a narrow packaging question: which declared components
have different payload paths or 48-byte digests between two restore builds,
and which keys were added or removed? It does not decompress payloads, verify
signatures, prove that a digest change is a security fix, or rewrite either
input.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import plistlib
import sys
from pathlib import Path
from typing import Any, Sequence

INFO_FLAGS = ("Trusted", "IsLoadedByiBoot", "IsFUDFirmware", "Personalize")


def _as_dict(value: Any) -> dict[str, Any]:
    return value if isinstance(value, dict) else {}


def _component(identity: dict[str, Any], key: str) -> dict[str, Any]:
    entry = _as_dict(_as_dict(identity.get("Manifest")).get(key))
    if not entry:
        return {"present": False}

    info = _as_dict(entry.get("Info"))
    digest = entry.get("Digest")
    flags = {flag: info[flag] for flag in INFO_FLAGS if flag in info}
    if "Trusted" in entry:
        flags["Trusted"] = entry["Trusted"]
    return {
        "present": True,
        "path": info.get("Path"),
        "digest_hex": digest.hex() if isinstance(digest, bytes) else None,
        "info": flags,
    }


def _identity_key(identity: dict[str, Any], index: int) -> str:
    variant = _as_dict(identity.get("Info")).get("Variant")
    return variant if isinstance(variant, str) and variant else f"identity-{index}"


def _identities(manifest: dict[str, Any]) -> dict[str, dict[str, Any]]:
    result: dict[str, dict[str, Any]] = {}
    for index, identity in enumerate(manifest.get("BuildIdentities") or []):
        if isinstance(identity, dict):
            result[_identity_key(identity, index)] = identity
    return result


def _diff_identity(
    old_identity: dict[str, Any], new_identity: dict[str, Any]
) -> dict[str, Any]:
    old_manifest = _as_dict(old_identity.get("Manifest"))
    new_manifest = _as_dict(new_identity.get("Manifest"))
    old_keys = set(old_manifest)
    new_keys = set(new_manifest)

    changed: list[dict[str, Any]] = []
    same = 0
    for key in sorted(old_keys & new_keys):
        old_component = _component(old_identity, key)
        new_component = _component(new_identity, key)
        if (
            old_component.get("path") == new_component.get("path")
            and old_component.get("digest_hex") == new_component.get("digest_hex")
            and old_component.get("info") == new_component.get("info")
        ):
            same += 1
            continue
        changed.append(
            {
                "key": key,
                "path_old": old_component.get("path"),
                "path_new": new_component.get("path"),
                "digest_old": old_component.get("digest_hex"),
                "digest_new": new_component.get("digest_hex"),
                "info_old": old_component.get("info"),
                "info_new": new_component.get("info"),
                "info_changed": old_component.get("info") != new_component.get("info"),
            }
        )

    return {
        "components_compared": len(old_keys & new_keys),
        "same": same,
        "changed_count": len(changed),
        "added": sorted(new_keys - old_keys),
        "removed": sorted(old_keys - new_keys),
        "changed": changed,
    }


def _metadata(manifest: dict[str, Any], sha256: str, size: int) -> dict[str, Any]:
    supported = manifest.get("SupportedProductTypes")
    return {
        "artifact": {"sha256": sha256, "bytes": size},
        "product_version": manifest.get("ProductVersion"),
        "product_build_version": manifest.get("ProductBuildVersion"),
        "supported_product_types": list(supported) if isinstance(supported, list) else [],
    }


def diff_manifests(
    old: dict[str, Any],
    new: dict[str, Any],
    *,
    old_sha256: str,
    new_sha256: str,
    old_bytes: int,
    new_bytes: int,
) -> dict[str, Any]:
    """Return a deterministic diff of two parsed BuildManifest documents."""
    old_identities = _identities(old)
    new_identities = _identities(new)
    identity_diffs: dict[str, Any] = {}
    for key in sorted(set(old_identities) | set(new_identities)):
        if key in old_identities and key in new_identities:
            identity_diffs[key] = _diff_identity(old_identities[key], new_identities[key])
        else:
            identity_diffs[key] = {
                "status": "only-in-old" if key in old_identities else "only-in-new"
            }

    first_shared = next(
        (key for key in sorted(identity_diffs) if "status" not in identity_diffs[key]),
        None,
    )
    summary = identity_diffs[first_shared] if first_shared else {
        "components_compared": 0,
        "same": 0,
        "changed_count": 0,
        "added": [],
        "removed": [],
        "changed": [],
    }

    return {
        "schema_version": 1,
        "old": _metadata(old, old_sha256, old_bytes),
        "new": _metadata(new, new_sha256, new_bytes),
        "identity_count_old": len(old_identities),
        "identity_count_new": len(new_identities),
        "identities": identity_diffs,
        "summary": {
            "identity": first_shared,
            "components_compared": summary["components_compared"],
            "same": summary["same"],
            "changed_count": summary["changed_count"],
            "added": summary["added"],
            "removed": summary["removed"],
            "changed": summary["changed"],
        },
    }


def diff_paths(old_path: str | Path, new_path: str | Path) -> dict[str, Any]:
    """Read two BuildManifest.plist files and return their diff."""
    old_data = Path(old_path).read_bytes()
    new_data = Path(new_path).read_bytes()
    old = plistlib.loads(old_data)
    new = plistlib.loads(new_data)
    if not isinstance(old, dict) or not isinstance(new, dict):
        raise ValueError("BuildManifest root is not a dictionary")
    return diff_manifests(
        old,
        new,
        old_sha256=hashlib.sha256(old_data).hexdigest(),
        new_sha256=hashlib.sha256(new_data).hexdigest(),
        old_bytes=len(old_data),
        new_bytes=len(new_data),
    )


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("old", type=Path, help="older BuildManifest.plist")
    parser.add_argument("new", type=Path, help="newer BuildManifest.plist")
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        help="write JSON to this path instead of stdout",
    )
    args = parser.parse_args(argv)

    try:
        summary = diff_paths(args.old, args.new)
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
