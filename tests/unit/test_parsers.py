"""Unit tests for Image4/Mach-O inspection parsers."""

from __future__ import annotations

import hashlib
import struct
import unittest

from engineering.parsers.image4 import Image4Error, inspect_bytes, parse_im4p
from engineering.parsers.macho import (
    LC_SEGMENT_64,
    LC_SOURCE_VERSION,
    LC_UUID,
    MH_CIGAM_64,
    MH_CIGAM,
    MH_MAGIC,
    MH_MAGIC_64,
    MachOError,
    parse_macho,
)

EMPTY_SHA256 = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"


def _der_length(length: int) -> bytes:
    if length < 0x80:
        return bytes([length])
    raw = length.to_bytes((length.bit_length() + 7) // 8, "big")
    return bytes([0x80 | len(raw)]) + raw


def _der_ia5(value: str) -> bytes:
    body = value.encode("ascii")
    return bytes([0x16]) + _der_length(len(body)) + body


def _der_octet(value: bytes) -> bytes:
    return bytes([0x04]) + _der_length(len(value)) + value


def _der_sequence(elements: bytes) -> bytes:
    return bytes([0x30]) + _der_length(len(elements)) + elements


def _der_uint64(tag: int, value: int) -> bytes:
    return bytes([tag]) + _der_length(8) + struct.pack("<Q", value)


def _im4p_container(payload: bytes, ptype: str = "test", description: str = "synthetic") -> bytes:
    return _der_sequence(
        _der_ia5("IM4P")
        + _der_ia5(ptype)
        + _der_ia5(description)
        + _der_octet(payload)
    )


def _section(name: str, segment: str, address: int, size: int, offset: int) -> bytes:
    return struct.pack(
        "<16s16sQQIIIIIIII",
        name.encode("ascii"),
        segment.encode("ascii"),
        address,
        size,
        offset,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    )


def build_macho(
    segments: list[tuple[str, int, int, int, int, int]],
    sections: list[tuple[str, str, int, int, int]],
    uuid: bytes | None = None,
    source_version: int | None = None,
    flags: int = 0x200001,
    cputype: int = 0x0100000C,
    cpusubtype: int = 2,
) -> bytes:
    """Build a minimal synthetic 64-bit little-endian Mach-O executable."""
    load_commands = bytearray()
    seg_count = len(segments)
    seg_cmd_sizes = []
    for name, vmaddr, vmsize, fileoff, filesize, segflags in segments:
        size = 72 + len(sections_for(seg_count, name, sections)) * 80
        seg_cmd_sizes.append(size)
        load_commands += struct.pack(
            "<II16sQQQQiiII",
            LC_SEGMENT_64,
            size,
            name.encode("ascii"),
            vmaddr,
            vmsize,
            fileoff,
            filesize,
            7,
            7,
            len(sections_for(seg_count, name, sections)),
            segflags,
        )
        for sname, seg, addr, size, off in sections_for(seg_count, name, sections):
            load_commands += _section(sname, seg, addr, size, off)

    uuid = uuid or bytes(range(16))
    load_commands += struct.pack("<II", LC_UUID, 24) + uuid

    if source_version is not None:
        load_commands += struct.pack("<IIQ", LC_SOURCE_VERSION, 16, source_version)

    sizeofcmds = len(load_commands)
    header = struct.pack(
        "<IIIIIIII",
        MH_MAGIC_64,
        cputype,
        cpusubtype,
        2,
        len(segments) + 1 + (1 if source_version is not None else 0),
        sizeofcmds,
        flags,
        0,
    )
    return header + bytes(load_commands)


def sections_for(seg_count: int, name: str, sections: list[tuple[str, str, int, int, int]]) -> list[tuple[str, str, int, int, int]]:
    return [s for s in sections if s[1] == name]


class MachoTests(unittest.TestCase):
    def test_parse_synthetic_macho(self) -> None:
        image = build_macho(
            segments=[("__TEXT", 0x1000, 0x1000, 0, 0x1000, 0)],
            sections=[("__text", "__TEXT", 0x1000, 0x100, 0x1000)],
            uuid=bytes(range(16)),
            source_version=(820 << 40) | (0 << 30) | (22 << 20) | (0 << 10) | 0,
        )
        result = parse_macho(image)

        self.assertEqual("MH_MAGIC_64", result["magic"])
        self.assertEqual("little", result["byte_order"])
        self.assertEqual("ARM64", result["cputype_name"])
        self.assertEqual("ARM64E", result["cpusubtype_name"])
        self.assertEqual("MH_EXECUTE", result["filetype_name"])
        self.assertIn("MH_PIE", result["flag_names"])
        self.assertEqual("00010203-0405-0607-0809-0A0B0C0D0E0F", result["uuid"])
        self.assertEqual("820.0.22", result["source_version"])
        self.assertEqual(["__TEXT"], result["segment_names"])
        self.assertFalse(result["has_ppl_segments"])
        self.assertFalse(result["has_boot_exec"])
        self.assertIsNone(result["binname"])

        seg = result["segments"][0]
        self.assertEqual("__TEXT", seg["name"])
        section = seg["sections"][0]
        self.assertEqual("__text", section["name"])
        self.assertEqual(0x100, section["size"])
        self.assertEqual(0x1000, section["offset"])

    def test_parse_ppl_segments_are_flagged(self) -> None:
        image = build_macho(
            segments=[("__PPLTEXT", 0x1000, 0x1000, 0, 0x1000, 0)],
            sections=[("__text", "__PPLTEXT", 0x1000, 0x100, 0x1000)],
        )
        result = parse_macho(image)

        self.assertTrue(result["has_ppl_segments"])
        self.assertEqual(["__PPLTEXT"], result["ppl_segments"])

    def test_parse_boot_exec_is_flagged(self) -> None:
        image = build_macho(
            segments=[("__TEXT_BOOT_EXEC", 0x1000, 0x1000, 0, 0x1000, 0)],
            sections=[("__bootcode", "__TEXT_BOOT_EXEC", 0x1000, 0x100, 0x1000)],
        )
        result = parse_macho(image)

        self.assertTrue(result["has_boot_exec"])
        self.assertEqual(["__bootcode"], result["boot_exec_sections"])

    def test_rejects_three_twenty_bit_macho(self) -> None:
        image = struct.pack("<IIIIIIII", MH_MAGIC, 0x100000C, 2, 2, 1, 32, 0x200001, 0)

        with self.assertRaises(MachOError):
            parse_macho(image)

    def test_rejects_bad_magic(self) -> None:
        with self.assertRaises(MachOError):
            parse_macho(b"\xca\xfe\xba\xbe" + b"\0" * 28)

    def test_rejects_truncated_header(self) -> None:
        with self.assertRaises(MachOError):
            parse_macho(b"\xfe\xed\xfa\xcf")

    def test_rejects_truncated_segment(self) -> None:
        image = build_macho(segments=[("__TEXT", 0x1000, 0x1000, 0, 0x1000, 0)], sections=[])
        truncated = image[: len(image) - 5]

        with self.assertRaises(MachOError):
            parse_macho(truncated)

    def test_big_endian_macho_is_parsed(self) -> None:
        segments = bytearray()
        segments += struct.pack(
            ">II16sQQQQiiII",
            LC_SEGMENT_64,
            72,
            b"__TEXT\0" * 3,
            0x1000,
            0x1000,
            0,
            0x1000,
            7,
            7,
            0,
            0,
        )
        uuid = bytes(range(16))
        segments += struct.pack(">II", LC_UUID, 24) + uuid
        header = struct.pack(
            ">IIIIIIII",
            MH_MAGIC_64,
            0x0100000C,
            2,
            2,
            2,
            len(segments),
            0x200001,
            0,
        )
        image = header + bytes(segments)

        result = parse_macho(image)

        self.assertEqual("big", result["byte_order"])
        self.assertEqual("ARM64E", result["cpusubtype_name"])
        self.assertEqual(str(__import__("uuid").UUID(bytes=uuid)).upper(), result["uuid"])

    def test_unknown_cpu_type_name(self) -> None:
        image = build_macho(segments=[], sections=[], cputype=0x0100000F)

        self.assertEqual("0x0100000f", parse_macho(image)["cputype_name"])


class Image4Tests(unittest.TestCase):
    def test_parse_im4p_container(self) -> None:
        payload = b"synthetic-payload-bytes"
        container = _im4p_container(payload, "sptm", "test description")

        result = parse_im4p(container)

        self.assertEqual("IM4P", result["magic"])
        self.assertEqual("sptm", result["type"])
        self.assertEqual("test description", result["description"])
        self.assertEqual(len(payload), result["payload_bytes"])
        self.assertEqual("unknown", result["compression"])
        self.assertEqual(result["container_bytes"], len(container))

    def test_im4p_rejects_bad_magic(self) -> None:
        bad = _der_sequence(_der_ia5("IM4X") + _der_ia5("sptm") + _der_ia5("d") + _der_octet(b"x"))

        with self.assertRaises(Image4Error):
            parse_im4p(bad)

    def test_im4p_rejects_non_der(self) -> None:
        with self.assertRaises(Image4Error):
            parse_im4p(b"not an im4p container")

    def test_im4p_extra_elements_are_reported(self) -> None:
        extra = _der_uint64(0xA0, 0x010203)
        container = _der_sequence(
            _der_ia5("IM4P")
            + _der_ia5("sptm")
            + _der_ia5("d")
            + _der_octet(b"payload")
            + extra
        )

        result = parse_im4p(container)

        self.assertEqual([{"tag": "0xa0", "bytes": 8}], result["extra_elements"])

    def test_im4p_payload_sha_matches_file_hash(self) -> None:
        payload = b"another-payload"
        container = _im4p_container(payload)

        report = inspect_bytes(container)

        self.assertEqual("im4p", report["kind"])
        self.assertEqual(
            hashlib.sha384(payload).hexdigest(),
            report["im4p"]["payload_sha384"],
        )
        self.assertIsNone(report["macho"])

    def test_im4p_nested_macho_when_uncompressed(self) -> None:
        macho = build_macho(
            segments=[("__TEXT", 0x1000, 0x1000, 0, 0x1000, 0)],
            sections=[("__text", "__TEXT", 0x1000, 0x100, 0x1000)],
        )
        container = _im4p_container(macho)

        report = inspect_bytes(container)

        self.assertEqual("im4p", report["kind"])
        self.assertEqual("none", report["im4p"]["compression"])
        self.assertIsNotNone(report["macho"])
        self.assertEqual("MH_EXECUTE", report["macho"]["filetype_name"])

    def test_inspect_bytes_plain_macho(self) -> None:
        macho = build_macho(
            segments=[("__TEXT_BOOT_EXEC", 0x1000, 0x1000, 0, 0x1000, 0)],
            sections=[("__bootcode", "__TEXT_BOOT_EXEC", 0x1000, 0x100, 0x1000)],
        )

        report = inspect_bytes(macho)

        self.assertEqual("macho", report["kind"])
        self.assertTrue(report["macho"]["has_boot_exec"])
        self.assertEqual(["__bootcode"], report["macho"]["boot_exec_sections"])

    def test_lzfse_payload_is_not_decompressed(self) -> None:
        compressed = b"bvx2" + b"\0" * 1000
        container = _im4p_container(compressed)

        report = inspect_bytes(container)

        self.assertEqual("lzfse", report["im4p"]["compression"])
        self.assertIsNone(report["macho"])

    def test_unknown_compression_is_reported(self) -> None:
        container = _im4p_container(b"\x00\x01\x02\x03")

        self.assertEqual("unknown", inspect_bytes(container)["im4p"]["compression"])

    def test_empty_input_rejected(self) -> None:
        with self.assertRaises(Image4Error):
            inspect_bytes(b"")


if __name__ == "__main__":
    unittest.main()
