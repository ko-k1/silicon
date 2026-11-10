"""Read-only Mach-O header and load-command inspection.

The parser reports structural metadata only. It does not validate code
signatures, evaluate trust, or execute the image. The initial target support is
64-bit little- and big-endian Mach-O; 32-bit images are rejected explicitly.
"""

from __future__ import annotations

import plistlib
import struct
import uuid as uuid_module
from typing import Any

MH_MAGIC_64 = 0xFEEDFACF
MH_CIGAM_64 = 0xCFFAEDFE
MH_MAGIC = 0xFEEDFACE
MH_CIGAM = 0xCEFAEDFE

CPU_ARCH_ABI64 = 0x01000000
CPU_TYPE_ARM = 12
CPU_TYPE_ARM64 = CPU_ARCH_ABI64 | CPU_TYPE_ARM
CPU_TYPE_X86 = 7
CPU_TYPE_X86_64 = CPU_ARCH_ABI64 | CPU_TYPE_X86

CPU_TYPE_NAMES = {
    CPU_TYPE_ARM: "ARM",
    CPU_TYPE_ARM64: "ARM64",
    CPU_TYPE_X86: "X86",
    CPU_TYPE_X86_64: "X86_64",
}

CPU_SUBTYPE_ARM64_NAMES = {
    0: "ARM64_ALL",
    1: "ARM64_V8",
    2: "ARM64E",
}

CPU_SUBTYPE_X86_64_NAMES = {
    3: "X86_64_ALL",
    8: "X86_64_H",
}

FILE_TYPE_NAMES = {
    1: "MH_OBJECT",
    2: "MH_EXECUTE",
    3: "MH_FVMLIB",
    4: "MH_CORE",
    5: "MH_PRELOAD",
    6: "MH_DYLIB",
    7: "MH_DYLINKER",
    8: "MH_BUNDLE",
    9: "MH_DYLIB_STUB",
    10: "MH_DSYM",
    11: "MH_KEXT_BUNDLE",
    12: "MH_FILESET",
}

FLAG_NAMES = {
    0x1: "MH_NOUNDEFS",
    0x2: "MH_INCRLINK",
    0x4: "MH_DYLDLINK",
    0x8: "MH_BINDATLOAD",
    0x10: "MH_PREBOUND",
    0x20: "MH_SPLIT_SEGS",
    0x40: "MH_LAZY_INIT",
    0x80: "MH_TWOLEVEL",
    0x100: "MH_FORCE_FLAT",
    0x200: "MH_NOMULTIDEFS",
    0x400: "MH_NOFIXPREBINDING",
    0x800: "MH_PREBINDABLE",
    0x1000: "MH_ALLMODSBOUND",
    0x2000: "MH_SUBSECTIONS_VIA_SYMBOLS",
    0x4000: "MH_CANONICAL",
    0x8000: "MH_WEAK_DEFINES",
    0x10000: "MH_BINDS_TO_WEAK",
    0x20000: "MH_ALLOW_STACK_EXECUTION",
    0x40000: "MH_ROOT_SAFE",
    0x80000: "MH_SETUID_SAFE",
    0x100000: "MH_NO_REEXPORTED_DYLIBS",
    0x200000: "MH_PIE",
    0x400000: "MH_DEAD_STRIPPABLE_DYLIB",
    0x800000: "MH_HAS_TLV_DESCRIPTORS",
    0x1000000: "MH_NO_HEAP_EXECUTION",
    0x02000000: "MH_APP_EXTENSION_SAFE",
    0x04000000: "MH_NLIST_OUTOFSYNC_WITH_DYLDINFO",
    0x08000000: "MH_SIM_SUPPORT",
}

LC_SEGMENT_64 = 0x19
LC_UUID = 0x1B
LC_SOURCE_VERSION = 0x2A

PPL_SEGMENT_NAMES = ("__PPLTEXT", "__PPLDATA", "__PPLDATA_CONST")
BOOT_EXEC_SEGMENT = "__TEXT_BOOT_EXEC"


class MachOError(ValueError):
    """Raised when a Mach-O image cannot be parsed safely."""


def _decode_name(raw: bytes) -> str:
    return raw.split(b"\0", 1)[0].decode("ascii", errors="replace")


def _decode_source_version(value: int) -> str:
    parts = [
        (value >> 40) & 0xFFFFFF,
        (value >> 30) & 0x3FF,
        (value >> 20) & 0x3FF,
        (value >> 10) & 0x3FF,
        value & 0x3FF,
    ]
    while len(parts) > 1 and parts[-1] == 0:
        parts.pop()
    return ".".join(str(part) for part in parts)


def _format_uuid(raw: bytes) -> str:
    return str(uuid_module.UUID(bytes=raw)).upper()


def _read_section_data(data: bytes, offset: int, size: int) -> bytes | None:
    if offset < 0 or size < 0 or offset + size > len(data):
        return None
    return data[offset : offset + size]


def parse_macho(data: bytes) -> dict[str, Any]:
    """Parse a 64-bit Mach-O image and return structural metadata."""
    if len(data) < 32:
        raise MachOError("image is shorter than the Mach-O 64-bit header")

    raw_magic = data[:4]
    if raw_magic == b"\xcf\xfa\xed\xfe":
        endian = "<"
        magic_name = "MH_MAGIC_64"
        byte_order = "little"
    elif raw_magic == b"\xfe\xed\xfa\xcf":
        endian = ">"
        magic_name = "MH_MAGIC_64"
        byte_order = "big"
    elif raw_magic in (b"\xce\xfa\xed\xfe", b"\xfe\xed\xfa\xce"):
        raise MachOError("32-bit Mach-O images are not supported")
    else:
        raise MachOError("input does not start with a Mach-O magic")

    (
        _magic,
        cputype,
        cpusubtype,
        filetype,
        ncmds,
        sizeofcmds,
        flags,
        _reserved,
    ) = struct.unpack_from(endian + "IIIIIIII", data, 0)

    if ncmds > 10000:
        raise MachOError(f"unreasonable load-command count: {ncmds}")
    if 32 + sizeofcmds > len(data):
        raise MachOError("load commands extend beyond the end of the image")

    cputype_name = CPU_TYPE_NAMES.get(cputype, f"0x{cputype:08x}")
    cpusubtype_base = cpusubtype & 0x00FFFFFF
    if cputype == CPU_TYPE_ARM64:
        cpusubtype_name = CPU_SUBTYPE_ARM64_NAMES.get(
            cpusubtype_base, f"0x{cpusubtype:08x}"
        )
    elif cputype == CPU_TYPE_X86_64:
        cpusubtype_name = CPU_SUBTYPE_X86_64_NAMES.get(
            cpusubtype_base, f"0x{cpusubtype:08x}"
        )
    else:
        cpusubtype_name = f"0x{cpusubtype:08x}"

    segments: list[dict[str, Any]] = []
    uuid_value: str | None = None
    source_version: str | None = None
    binname: str | None = None
    info_plist: dict[str, Any] | None = None
    offset = 32

    for _ in range(ncmds):
        if offset + 8 > len(data):
            raise MachOError("truncated load command header")
        cmd, cmdsize = struct.unpack_from(endian + "II", data, offset)
        if cmdsize < 8:
            raise MachOError(f"load command 0x{cmd:x} has invalid size {cmdsize}")
        if offset + cmdsize > len(data):
            raise MachOError(f"load command 0x{cmd:x} extends beyond the image")

        if cmd == LC_SEGMENT_64:
            if cmdsize < 72:
                raise MachOError("LC_SEGMENT_64 command is too small")
            (
                _cmd,
                _cmdsize,
                segment_name_raw,
                vmaddr,
                vmsize,
                fileoff,
                filesize,
                maxprot,
                initprot,
                nsects,
                segment_flags,
            ) = struct.unpack_from(endian + "II16sQQQQiiII", data, offset)
            expected_size = 72 + nsects * 80
            if cmdsize < expected_size:
                raise MachOError(
                    f"segment {_decode_name(segment_name_raw)!r} declares "
                    f"{nsects} sections but the command is too small"
                )

            segment_name = _decode_name(segment_name_raw)
            sections: list[dict[str, Any]] = []
            section_offset = offset + 72
            for _section_index in range(nsects):
                (
                    section_name_raw,
                    section_segment_raw,
                    address,
                    size,
                    data_offset,
                    align,
                    reloff,
                    nreloc,
                    section_flags,
                    _reserved1,
                    _reserved2,
                    _reserved3,
                ) = struct.unpack_from(
                    endian + "16s16sQQIIIIIIII", data, section_offset
                )
                section_name = _decode_name(section_name_raw)
                section = {
                    "name": section_name,
                    "segment": _decode_name(section_segment_raw),
                    "address": address,
                    "size": size,
                    "offset": data_offset,
                    "align": align,
                    "reloff": reloff,
                    "nreloc": nreloc,
                    "flags": section_flags,
                }
                sections.append(section)

                raw_section = _read_section_data(data, data_offset, size)
                if section_name == "__binname" and raw_section is not None:
                    binname = raw_section.split(b"\0", 1)[0].decode(
                        "utf-8", errors="replace"
                    )
                elif section_name == "__info_plist" and raw_section is not None:
                    try:
                        plist = plistlib.loads(raw_section)
                    except Exception:
                        info_plist = {"parsed": False, "identifier": None}
                    else:
                        identifier = plist.get("CFBundleIdentifier")
                        info_plist = {
                            "parsed": True,
                            "identifier": identifier
                            if isinstance(identifier, str)
                            else None,
                        }

                section_offset += 80

            segments.append(
                {
                    "name": segment_name,
                    "vmaddr": vmaddr,
                    "vmsize": vmsize,
                    "fileoff": fileoff,
                    "filesize": filesize,
                    "maxprot": maxprot,
                    "initprot": initprot,
                    "flags": segment_flags,
                    "sections": sections,
                }
            )

        elif cmd == LC_UUID:
            if cmdsize < 24:
                raise MachOError("LC_UUID command is too small")
            uuid_value = _format_uuid(data[offset + 8 : offset + 24])

        elif cmd == LC_SOURCE_VERSION:
            if cmdsize < 16:
                raise MachOError("LC_SOURCE_VERSION command is too small")
            (raw_version,) = struct.unpack_from(endian + "Q", data, offset + 8)
            source_version = _decode_source_version(raw_version)

        offset += cmdsize

    segment_names = [segment["name"] for segment in segments]
    ppl_segments = [
        name for name in segment_names if name in PPL_SEGMENT_NAMES
    ]
    boot_exec_sections = [
        section["name"]
        for segment in segments
        if segment["name"] == BOOT_EXEC_SEGMENT
        for section in segment["sections"]
    ]

    return {
        "magic": magic_name,
        "byte_order": byte_order,
        "cputype": cputype,
        "cputype_name": cputype_name,
        "cpusubtype": cpusubtype,
        "cpusubtype_base": cpusubtype_base,
        "cpusubtype_name": cpusubtype_name,
        "filetype": filetype,
        "filetype_name": FILE_TYPE_NAMES.get(filetype, f"0x{filetype:08x}"),
        "ncmds": ncmds,
        "sizeofcmds": sizeofcmds,
        "flags": flags,
        "flag_names": [
            name for bit, name in FLAG_NAMES.items() if flags & bit
        ],
        "uuid": uuid_value,
        "source_version": source_version,
        "segment_names": segment_names,
        "segments": segments,
        "ppl_segments": ppl_segments,
        "has_ppl_segments": bool(ppl_segments),
        "has_boot_exec": BOOT_EXEC_SEGMENT in segment_names,
        "boot_exec_sections": boot_exec_sections,
        "binname": binname,
        "info_plist": info_plist,
    }
