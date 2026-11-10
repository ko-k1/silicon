"""Read-only Image4 (IM4P) and Mach-O inspection.

The tool parses the IM4P DER container, reports payload hashes and compression,
and parses a nested Mach-O when the payload is uncompressed. It does not
decompress Image4 payloads, verify signatures, evaluate trust, or execute code.

Usage:
    python3 -m engineering.parsers.image4 <artifact>
"""

from __future__ import annotations

import argparse
import hashlib
import json
import sys
from pathlib import Path
from typing import Any, Sequence

from engineering.parsers.macho import MachOError, parse_macho

IM4P_MAGIC = b"IM4P"
MACHO_MAGICS = (
    b"\xcf\xfa\xed\xfe",
    b"\xfe\xed\xfa\xcf",
    b"\xce\xfa\xed\xfe",
    b"\xfe\xed\xfa\xce",
)


class Image4Error(ValueError):
    """Raised when an Image4/IM4P container cannot be parsed safely."""


def _read_tlv(data: bytes, offset: int) -> tuple[int, bytes, int]:
    if offset >= len(data):
        raise Image4Error("truncated DER element")
    tag = data[offset]
    offset += 1
    if offset >= len(data):
        raise Image4Error("truncated DER length")
    first = data[offset]
    offset += 1
    if first < 0x80:
        length = first
    elif first == 0x80:
        raise Image4Error("indefinite DER lengths are not supported")
    else:
        count = first & 0x7F
        if count == 0 or count > 8:
            raise Image4Error(f"unsupported DER length width: {count}")
        if offset + count > len(data):
            raise Image4Error("truncated DER long-form length")
        length = int.from_bytes(data[offset : offset + count], "big")
        offset += count
    if offset + length > len(data):
        raise Image4Error("DER element extends beyond the input")
    return tag, data[offset : offset + length], offset + length


def _is_macho(data: bytes) -> bool:
    return len(data) >= 4 and data[:4] in MACHO_MAGICS


def _compression(payload: bytes) -> str:
    if _is_macho(payload):
        return "none"
    if payload.startswith(b"bvx2"):
        return "lzfse"
    if payload.startswith(b"complzss"):
        return "lzss"
    return "unknown"


def parse_im4p(data: bytes) -> dict[str, Any]:
    """Parse an IM4P DER container.

    The returned mapping includes the raw ``payload`` bytes. Callers should
    remove that key before serialising untrusted or bulky input.
    """
    tag, body, end = _read_tlv(data, 0)
    if tag != 0x30:
        raise Image4Error("IM4P outer element is not a DER SEQUENCE")

    elements: list[tuple[int, bytes]] = []
    offset = 0
    while offset < len(body):
        element_tag, value, offset = _read_tlv(body, offset)
        elements.append((element_tag, value))

    if len(elements) < 4:
        raise Image4Error("IM4P container has fewer than four elements")
    if elements[0][0] != 0x16 or elements[0][1] != IM4P_MAGIC:
        raise Image4Error("IM4P magic string is missing")
    if elements[1][0] != 0x16:
        raise Image4Error("IM4P payload type is not an IA5String")
    if elements[2][0] != 0x16:
        raise Image4Error("IM4P description is not an IA5String")
    if elements[3][0] != 0x04:
        raise Image4Error("IM4P payload is not an OCTET STRING")

    try:
        payload_type = elements[1][1].decode("ascii")
        description = elements[2][1].decode("ascii")
    except UnicodeDecodeError as exc:
        raise Image4Error(f"IM4P text element is not ASCII: {exc}") from exc

    payload = elements[3][1]
    return {
        "magic": IM4P_MAGIC.decode("ascii"),
        "type": payload_type,
        "description": description,
        "payload": payload,
        "payload_bytes": len(payload),
        "compression": _compression(payload),
        "extra_elements": [
            {"tag": f"0x{element_tag:02x}", "bytes": len(value)}
            for element_tag, value in elements[4:]
        ],
        "container_bytes": end,
    }


def inspect_bytes(data: bytes) -> dict[str, Any]:
    """Inspect one artifact and return a JSON-serialisable report."""
    if _is_macho(data):
        try:
            macho = parse_macho(data)
        except MachOError as exc:
            raise Image4Error(str(exc)) from exc
        return {"kind": "macho", "im4p": None, "macho": macho}

    try:
        im4p = parse_im4p(data)
    except Image4Error as exc:
        raise Image4Error(f"input is neither Mach-O nor IM4P: {exc}") from exc

    payload = im4p.pop("payload")
    im4p["payload_sha256"] = hashlib.sha256(payload).hexdigest()
    im4p["payload_sha384"] = hashlib.sha384(payload).hexdigest()

    macho = None
    if im4p["compression"] == "none":
        try:
            macho = parse_macho(payload)
        except MachOError as exc:
            raise Image4Error(f"nested Mach-O payload is invalid: {exc}") from exc

    return {"kind": "im4p", "im4p": im4p, "macho": macho}


def inspect_file(path: str | Path) -> dict[str, Any]:
    """Read one file, inspect it, and attach file-level hashes."""
    source = Path(path)
    data = source.read_bytes()
    report = inspect_bytes(data)
    return {
        "path": str(path),
        "file": {
            "bytes": len(data),
            "sha256": hashlib.sha256(data).hexdigest(),
            "sha384": hashlib.sha384(data).hexdigest(),
        },
        **report,
    }


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("path", type=Path, help="IM4P or Mach-O file to inspect")
    args = parser.parse_args(argv)

    if not args.path.is_file():
        print(f"error: {args.path} is not a file", file=sys.stderr)
        return 2

    try:
        report = inspect_file(args.path)
    except (OSError, Image4Error) as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 2

    sys.stdout.write(json.dumps(report, indent=2, sort_keys=True) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
