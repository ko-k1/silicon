"""Unit tests for the normalized kernel function diff."""

from __future__ import annotations

import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

from engineering.analyzers.kernel_function_diff import (
    build_functions,
    diff_paths,
    normalize_instruction,
    parse_disassembly,
    parse_function_starts,
)


class KernelFunctionDiffTests(unittest.TestCase):
    def setUp(self) -> None:
        self.temp_dir = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp_dir.cleanup)
        self.root = Path(self.temp_dir.name)

    def _write(self, name: str, text: str) -> Path:
        path = self.root / name
        path.write_text(text, encoding="utf-8")
        return path

    def test_parse_function_starts_sorts_and_deduplicates(self) -> None:
        path = self._write(
            "starts.txt",
            "\n0x2000\n0x1000\n\n0x2000\n0x1004\n",
        )
        self.assertEqual([0x1000, 0x1004, 0x2000], parse_function_starts(path))

    def test_parse_disassembly_ignores_labels_and_keeps_instructions(self) -> None:
        path = self._write(
            "dis.txt",
            "1000 <__text>:\n"
            "1000:      \tnop\n"
            "1004:      \tret\n",
        )
        self.assertEqual({0x1000: "nop", 0x1004: "ret"}, parse_disassembly(path))

    def test_exact_normalization_preserves_small_immediates(self) -> None:
        self.assertEqual(
            "add x0, x0, #0x10",
            normalize_instruction("add x0, x0, #0x10", shape=False, tainted=set()),
        )
        self.assertEqual(
            "bl ADDR",
            normalize_instruction(
                "bl 0xfffffff00a000000 <__text+0x10>",
                shape=False,
                tainted=set(),
            ),
        )

    def test_shape_normalization_masks_immediates(self) -> None:
        self.assertEqual(
            "mov w0, #IMM",
            normalize_instruction("mov w0, #0x20", shape=True, tainted=set()),
        )

    def test_page_offsets_are_normalized_after_adrp(self) -> None:
        tainted: set[str] = set()
        self.assertEqual(
            "adrp x0, PAGE",
            normalize_instruction(
                "adrp x0, 0xfffffff00ad36000", shape=False, tainted=tainted
            ),
        )
        self.assertEqual(
            "add x0, x0, #PAGEOFF",
            normalize_instruction("add x0, x0, #0xed8", shape=False, tainted=tainted),
        )

    def test_named_functions_are_classified_as_identical_constant_or_structural(
        self,
    ) -> None:
        old_dis = self._write(
            "old.dis",
            "1000:      \tmov w0, #0x1\n"
            "1004:      \tret\n"
            "1008:      \tnop\n"
            "100c:      \tret\n"
            "1010:      \tadd x0, x0, #1\n"
            "1014:      \tret\n",
        )
        new_dis = self._write(
            "new.dis",
            "2000:      \tmov w0, #0x2\n"
            "2004:      \tret\n"
            "2008:      \tnop\n"
            "200c:      \tret\n"
            "2010:      \tsub x0, x0, #1\n"
            "2014:      \tret\n",
        )
        old_starts = self._write("old.starts", "0x1000\n0x1008\n0x1010\n")
        new_starts = self._write("new.starts", "0x2000\n0x2008\n0x2010\n")
        old_syms = self._write(
            "old.syms.json",
            json.dumps({"4096": "constant", "4104": "identical", "4112": "structural"}),
        )
        new_syms = self._write(
            "new.syms.json",
            json.dumps({"8192": "constant", "8200": "identical", "8208": "structural"}),
        )

        result = diff_paths(
            old_dis, new_dis, old_starts, new_starts, old_syms, new_syms
        )
        summary = result["summary"]
        self.assertEqual(1, summary["named"]["counts"]["identical"])
        self.assertEqual(1, summary["named"]["counts"]["constant_only"])
        self.assertEqual(1, summary["named"]["counts"]["structural"])
        self.assertEqual(3, summary["named"]["common_names"])

    def test_symbols_are_matched_only_at_function_starts(self) -> None:
        functions = build_functions(
            [0x1000],
            {0x1000: "nop", 0x1004: "ret"},
            {0x1000: "start", 0x1004: "inside"},
        )
        self.assertEqual(["start"], functions[0]["names"])

    def test_cli_emits_the_same_summary(self) -> None:
        old_dis = self._write("old.dis", "1000:      \tnop\n1004:      \tret\n")
        new_dis = self._write("new.dis", "2000:      \tnop\n2004:      \tret\n")
        old_starts = self._write("old.starts", "0x1000\n")
        new_starts = self._write("new.starts", "0x2000\n")

        expected = diff_paths(old_dis, new_dis, old_starts, new_starts)
        completed = subprocess.run(
            [
                sys.executable,
                "-m",
                "engineering.analyzers.kernel_function_diff",
                "--old-dis",
                str(old_dis),
                "--new-dis",
                str(new_dis),
                "--old-starts",
                str(old_starts),
                "--new-starts",
                str(new_starts),
            ],
            check=False,
            capture_output=True,
            text=True,
        )
        self.assertEqual(0, completed.returncode, completed.stderr)
        self.assertEqual(expected["summary"], json.loads(completed.stdout))


if __name__ == "__main__":
    unittest.main()
