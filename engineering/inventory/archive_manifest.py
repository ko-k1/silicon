"""Deterministic archive manifest for tracked repository files.

The tool reads the Git index for the tracked path list, hashes each working-tree
file with SHA-256, and emits a stable JSON inventory. It does not hash untracked
files, follow symlinks, fetch artifacts, or modify source files.

Usage:
    python3 -m engineering.inventory.archive_manifest . --output MANIFEST.json
    python3 -m engineering.inventory.archive_manifest . --check MANIFEST.json

``--check`` exits 1 when the checked manifest is missing or stale.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable, Sequence

MANIFEST_VERSION = 1
DEFAULT_PROJECT = "silicon"
DEFAULT_ARCHIVE = "silicon-repository"
DEFAULT_ALGORITHM = "sha256"
CHUNK_SIZE = 1024 * 1024


@dataclass(frozen=True)
class FileEntry:
    """One hashed file in the archive manifest."""

    path: str
    bytes: int
    sha256: str

    def as_dict(self) -> dict[str, str | int]:
        return {"path": self.path, "bytes": self.bytes, "sha256": self.sha256}


def _normalise_relative(relative: str) -> str:
    path = Path(relative)
    if path.is_absolute():
        raise ValueError(f"path must be relative to the repository root: {relative!r}")
    if ".." in path.parts:
        raise ValueError(f"path escapes the repository root: {relative!r}")
    return path.as_posix()


def _resolved_file(root: Path, relative: str) -> Path:
    candidate = root / relative
    if candidate.is_symlink():
        raise ValueError(f"symlinks are not supported in the archive manifest: {relative!r}")
    resolved = candidate.resolve()
    try:
        resolved.relative_to(root)
    except ValueError as exc:
        raise ValueError(f"path escapes the repository root: {relative!r}") from exc
    if not resolved.is_file():
        raise FileNotFoundError(f"tracked file is missing: {relative}")
    return resolved


def hash_file(path: Path) -> tuple[int, str]:
    """Return ``(bytes, sha256_hex)`` for one file."""
    digest = hashlib.sha256()
    size = 0
    with path.open("rb") as handle:
        while chunk := handle.read(CHUNK_SIZE):
            size += len(chunk)
            digest.update(chunk)
    return size, digest.hexdigest()


def git_tracked_paths(root: str | Path) -> list[str]:
    """Return the repository-relative paths in the Git index."""
    base = Path(root).resolve()
    completed = subprocess.run(
        ["git", "-C", str(base), "ls-files", "-z"],
        check=False,
        capture_output=True,
    )
    if completed.returncode != 0:
        message = completed.stderr.decode("utf-8", errors="replace").strip()
        raise RuntimeError(f"git ls-files failed: {message or completed.returncode}")
    return [
        path
        for path in completed.stdout.decode("utf-8", errors="surrogateescape").split("\0")
        if path
    ]


def build_manifest(
    root: str | Path,
    relative_paths: Iterable[str],
    *,
    project: str = DEFAULT_PROJECT,
    archive: str = DEFAULT_ARCHIVE,
    exclude: Iterable[str] = (),
) -> dict:
    """Hash ``relative_paths`` under ``root`` and return a deterministic manifest."""
    base = Path(root).resolve()
    if not base.is_dir():
        raise NotADirectoryError(f"not a directory: {root}")

    excluded = {_normalise_relative(path) for path in exclude}
    entries: dict[str, FileEntry] = {}
    for raw in relative_paths:
        relative = _normalise_relative(raw)
        if relative in excluded or relative in entries:
            continue
        path = _resolved_file(base, relative)
        size, digest = hash_file(path)
        entries[relative] = FileEntry(relative, size, digest)

    ordered = [entries[path] for path in sorted(entries)]
    return {
        "manifest_version": MANIFEST_VERSION,
        "project": project,
        "archive": archive,
        "algorithm": DEFAULT_ALGORITHM,
        "file_count": len(ordered),
        "files": [entry.as_dict() for entry in ordered],
    }


def render_manifest(manifest: dict) -> str:
    """Render a manifest with stable formatting and a trailing newline."""
    return json.dumps(manifest, indent=2) + "\n"


def _excluded_target(root: Path, target: Path) -> list[str]:
    resolved = target.resolve()
    try:
        relative = resolved.relative_to(root.resolve())
    except ValueError:
        return []
    return [relative.as_posix()]


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "root",
        nargs="?",
        type=Path,
        default=Path("."),
        help="repository root to inspect (default: current directory)",
    )
    parser.add_argument(
        "--output",
        type=Path,
        help="write the manifest to this path instead of stdout",
    )
    parser.add_argument(
        "--check",
        type=Path,
        help="compare the generated manifest with this path; exit 1 if stale",
    )
    parser.add_argument("--project", default=DEFAULT_PROJECT, help="project label")
    parser.add_argument("--archive", default=DEFAULT_ARCHIVE, help="archive label")
    args = parser.parse_args(argv)

    if not args.root.is_dir():
        print(f"error: {args.root} is not a directory", file=sys.stderr)
        return 2
    if args.output is not None and args.check is not None:
        print("error: --output and --check are mutually exclusive", file=sys.stderr)
        return 2

    target = args.output if args.output is not None else args.check
    exclude = _excluded_target(args.root, target) if target is not None else []
    try:
        manifest = build_manifest(
            args.root,
            git_tracked_paths(args.root),
            project=args.project,
            archive=args.archive,
            exclude=exclude,
        )
    except (OSError, RuntimeError, ValueError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 2

    rendered = render_manifest(manifest)
    if args.check is not None:
        try:
            existing = args.check.read_text(encoding="utf-8")
        except OSError as exc:
            print(f"stale: cannot read {args.check}: {exc}", file=sys.stderr)
            return 1
        if existing == rendered:
            return 0
        print(f"stale: {args.check} does not match the Git index", file=sys.stderr)
        return 1

    if args.output is not None:
        try:
            args.output.write_text(rendered, encoding="utf-8")
        except OSError as exc:
            print(f"error: cannot write {args.output}: {exc}", file=sys.stderr)
            return 2
        print(
            f"wrote {args.output} ({manifest['file_count']} files)",
            file=sys.stderr,
        )
        return 0

    sys.stdout.write(rendered)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
