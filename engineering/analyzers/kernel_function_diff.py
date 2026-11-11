"""Normalized function-level diff for two disassembled Apple kernel images.

The analyzer consumes deterministic text produced by external inspection tools:

* a function-start list, one hexadecimal address per line (for example
  ``ipsw macho info -f``);
* an ``llvm-objdump -d --no-show-raw-insn`` disassembly;
* optional address-to-name JSON from ``ipsw kernel symbolicate --json``.

It groups instructions by function start, normalizes link-address-dependent
operands, and compares function bodies by exact-normalized and shape-normalized
hash. It does not disassemble binaries itself, verify signatures, infer source
semantics, or attribute a change to a vulnerability.
"""

from __future__ import annotations

import argparse
import collections
import difflib
import hashlib
import json
import re
import sys
from pathlib import Path
from typing import Any, Iterable, Sequence

ADDRESS_RE = re.compile(r"0x[0-9a-fA-F]+")
IMMEDIATE_RE = re.compile(r"#-?(?:0x[0-9a-fA-F]+|\d+)")
SYMBOL_ANNOTATION_RE = re.compile(r"<[^>]*>")
INSTRUCTION_RE = re.compile(r"^([0-9a-fA-F]+):\s+(.*)$")


def parse_function_starts(path: str | Path) -> list[int]:
    """Return sorted, unique hexadecimal function-start addresses."""
    starts: set[int] = set()
    for line in Path(path).read_text(encoding="utf-8").splitlines():
        value = line.strip()
        if value.startswith("0x"):
            starts.add(int(value, 16))
    return sorted(starts)


def parse_disassembly(path: str | Path) -> dict[int, str]:
    """Return ``address -> instruction text`` for one llvm-objdump dump."""
    instructions: dict[int, str] = {}
    for line in Path(path).read_text(errors="replace").splitlines():
        match = INSTRUCTION_RE.match(line)
        if match is None:
            continue
        text = match.group(2).strip()
        if text and not text.endswith(":"):
            instructions[int(match.group(1), 16)] = text
    return instructions


def load_symbols(path: str | Path | None) -> dict[int, str]:
    """Load an address-to-name JSON map, ignoring non-address keys."""
    if path is None:
        return {}
    raw = json.loads(Path(path).read_text(encoding="utf-8"))
    symbols: dict[int, str] = {}
    if not isinstance(raw, dict):
        return symbols
    for address, name in raw.items():
        try:
            symbols[int(address)] = str(name)
        except (TypeError, ValueError):
            continue
    return symbols


def normalize_instruction(text: str, *, shape: bool, tainted: set[str]) -> str:
    """Normalize one instruction for hashing.

    Exact-normalized mode masks absolute addresses and address-derived page
    offsets but retains small immediate values. Shape-normalized mode also masks
    every immediate, leaving opcode, register, and memory-operand structure.
    """
    text = text.split(";", 1)[0].strip()
    text = SYMBOL_ANNOTATION_RE.sub("", text)
    text = " ".join(text.split())

    match = re.match(r"^adrp\s+([a-z0-9]+),\s+0x[0-9a-fA-F]+$", text)
    if match:
        tainted.add(match.group(1))
        return f"adrp {match.group(1)}, PAGE"

    match = re.match(
        r"^(add|sub)\s+([a-z0-9]+),\s+([a-z0-9]+),\s+#-?(?:0x[0-9a-fA-F]+|\d+)$",
        text,
    )
    if match and match.group(3) in tainted:
        tainted.add(match.group(2))
        return f"{match.group(1)} {match.group(2)}, {match.group(3)}, #PAGEOFF"

    match = re.match(r"^mov\s+([a-z0-9]+),\s+([a-z0-9]+)$", text)
    if match and match.group(2) in tainted:
        tainted.add(match.group(1))

    if shape:
        text = IMMEDIATE_RE.sub("#IMM", text)
        return ADDRESS_RE.sub("ADDR", text)

    def replace_address(match: re.Match[str]) -> str:
        return "ADDR" if int(match.group(0), 16) >= 0x100000 else match.group(0)

    return ADDRESS_RE.sub(replace_address, text)


def _normalized_body(body: Iterable[str], *, shape: bool) -> list[str]:
    tainted: set[str] = set()
    return [
        normalize_instruction(text, shape=shape, tainted=tainted)
        for text in body
    ]


def _hash_instructions(instructions: Sequence[str]) -> str:
    return hashlib.sha256("\n".join(instructions).encode("utf-8")).hexdigest()


def build_functions(
    starts: Sequence[int],
    instructions: dict[int, str],
    symbols: dict[int, str] | None = None,
) -> list[dict[str, Any]]:
    """Group instructions into functions and compute normalized hashes."""
    symbols = symbols or {}
    functions: list[dict[str, Any]] = []
    if not starts:
        return functions

    addresses = sorted(instructions)
    index = 0
    while index < len(addresses) and addresses[index] < starts[0]:
        index += 1

    for position, start in enumerate(starts):
        end = (
            starts[position + 1]
            if position + 1 < len(starts)
            else addresses[-1] + 4
        )
        body: list[str] = []
        while index < len(addresses) and addresses[index] < end:
            body.append(instructions[addresses[index]])
            index += 1
        if not body:
            continue
        exact = _normalized_body(body, shape=False)
        shape = _normalized_body(body, shape=True)
        functions.append(
            {
                "start": start,
                "end": end,
                "insns": len(body),
                "body": body,
                "exact_sha256": _hash_instructions(exact),
                "shape_sha256": _hash_instructions(shape),
                "names": sorted(
                    name for address, name in symbols.items() if address == start
                ),
            }
        )
    return functions


def summarize_functions(
    old: Sequence[dict[str, Any]], new: Sequence[dict[str, Any]]
) -> dict[str, int]:
    """Return aggregate exact-normalized and shape-normalized match counts."""
    old_exact = collections.Counter(item["exact_sha256"] for item in old)
    new_exact = collections.Counter(item["exact_sha256"] for item in new)
    old_shape = collections.Counter(item["shape_sha256"] for item in old)
    new_shape = collections.Counter(item["shape_sha256"] for item in new)
    exact_matches = sum((old_exact & new_exact).values())
    shape_matches = sum((old_shape & new_shape).values())
    return {
        "old_functions": len(old),
        "new_functions": len(new),
        "exact_normalized_matches": exact_matches,
        "shape_normalized_matches": shape_matches,
        "old_unmatched_exact": len(old) - exact_matches,
        "new_unmatched_exact": len(new) - exact_matches,
    }


def _function_index(
    functions: Sequence[dict[str, Any]],
) -> dict[str, dict[str, Any]]:
    index: dict[str, dict[str, Any]] = {}
    for function in functions:
        for name in function["names"]:
            index.setdefault(name, function)
    return index


def named_changes(
    old: Sequence[dict[str, Any]],
    new: Sequence[dict[str, Any]],
    *,
    include_edits: bool = False,
) -> dict[str, Any]:
    """Compare functions that share an exact symbol name in both images."""
    old_index = _function_index(old)
    new_index = _function_index(new)
    common = sorted(set(old_index) & set(new_index))
    counts = collections.Counter[str]()
    changed: list[dict[str, Any]] = []

    for name in common:
        old_function = old_index[name]
        new_function = new_index[name]
        if old_function["exact_sha256"] == new_function["exact_sha256"]:
            counts["identical"] += 1
            continue
        if old_function["shape_sha256"] == new_function["shape_sha256"]:
            counts["constant_only"] += 1
            change_class = "constant_only"
        else:
            counts["structural"] += 1
            change_class = "structural"
        entry = {
            "name": name,
            "class": change_class,
            "old_start": hex(old_function["start"]),
            "new_start": hex(new_function["start"]),
            "old_insns": old_function["insns"],
            "new_insns": new_function["insns"],
        }
        if include_edits:
            entry["edit_summary"] = _instruction_edit_summary(
                _normalized_body(old_function["body"], shape=False),
                _normalized_body(new_function["body"], shape=False),
            )
        changed.append(entry)

    return {
        "common_names": len(common),
        "old_only_names": len(set(old_index) - set(new_index)),
        "new_only_names": len(set(new_index) - set(old_index)),
        "counts": dict(counts),
        "changed": changed,
    }


def _instruction_edit_summary(
    old: Sequence[str], new: Sequence[str], limit: int = 80
) -> dict[str, Any]:
    """Return a bounded, whitespace-insensitive edit summary for one function."""
    matcher = difflib.SequenceMatcher(a=old, b=new, autojunk=False)
    inserted = deleted = replaced = 0
    examples: list[dict[str, Any]] = []
    for tag, old_start, old_end, new_start, new_end in matcher.get_opcodes():
        if tag == "equal":
            continue
        if tag == "insert":
            inserted += new_end - new_start
        elif tag == "delete":
            deleted += old_end - old_start
        else:
            replaced += max(old_end - old_start, new_end - new_start)
        if len(examples) < limit:
            examples.append(
                {
                    "op": tag,
                    "old_start": old_start,
                    "old_end": old_end,
                    "new_start": new_start,
                    "new_end": new_end,
                    "old": list(old[old_start:old_end])[:8],
                    "new": list(new[new_start:new_end])[:8],
                }
            )
    return {
        "inserted": inserted,
        "deleted": deleted,
        "replaced": replaced,
        "examples": examples,
    }


def diff_paths(
    old_disassembly: str | Path,
    new_disassembly: str | Path,
    old_starts: str | Path,
    new_starts: str | Path,
    old_symbols: str | Path | None = None,
    new_symbols: str | Path | None = None,
    *,
    include_edits: bool = False,
) -> dict[str, Any]:
    """Compare two disassembly/start/symbol inputs and return a JSON summary."""
    old_functions = build_functions(
        parse_function_starts(old_starts),
        parse_disassembly(old_disassembly),
        load_symbols(old_symbols),
    )
    new_functions = build_functions(
        parse_function_starts(new_starts),
        parse_disassembly(new_disassembly),
        load_symbols(new_symbols),
    )
    summary = summarize_functions(old_functions, new_functions)
    named = named_changes(
        old_functions, new_functions, include_edits=include_edits
    )
    summary["named"] = {
        key: value for key, value in named.items() if key != "changed"
    }
    summary["changed_named_count"] = len(named["changed"])

    return {
        "summary": summary,
        "changed_named": named["changed"],
    }


def _write_tsv(path: Path, rows: Sequence[dict[str, Any]]) -> None:
    with path.open("w", encoding="utf-8") as handle:
        handle.write("name\tclass\told_start\tnew_start\told_insns\tnew_insns\n")
        for row in rows:
            handle.write(
                "\t".join(
                    str(row[key])
                    for key in (
                        "name",
                        "class",
                        "old_start",
                        "new_start",
                        "old_insns",
                        "new_insns",
                    )
                )
                + "\n"
            )


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--old-dis", type=Path, required=True)
    parser.add_argument("--new-dis", type=Path, required=True)
    parser.add_argument("--old-starts", type=Path, required=True)
    parser.add_argument("--new-starts", type=Path, required=True)
    parser.add_argument("--old-syms", type=Path)
    parser.add_argument("--new-syms", type=Path)
    parser.add_argument("--json-out", type=Path)
    parser.add_argument("--tsv-out", type=Path)
    parser.add_argument("--include-edits", action="store_true")
    args = parser.parse_args(argv)

    result = diff_paths(
        args.old_dis,
        args.new_dis,
        args.old_starts,
        args.new_starts,
        args.old_syms,
        args.new_syms,
        include_edits=args.include_edits,
    )
    if args.json_out:
        args.json_out.write_text(
            json.dumps(result, indent=2) + "\n", encoding="utf-8"
        )
    if args.tsv_out:
        _write_tsv(args.tsv_out, result["changed_named"])
    json.dump(result["summary"], sys.stdout, indent=2)
    sys.stdout.write("\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
