# Engineering workspace

Reusable research-support tools belong here. Initial candidates: target inventory, artifact hashing/provenance, evidence indexing, metadata parsing, and report generation. Keep tools deterministic, fixture-tested, and read-only with respect to original inputs.

## Inventory

- `engineering/inventory/build_manifest.py` - read-only BuildManifest.plist summarizer for build identities, SPTM/TXM entries, kernelcache references, and 48-byte payload digests. It does not fetch artifacts or assert runtime state.
  - Run: `python3 -m engineering.inventory.build_manifest <BuildManifest.plist>`
  - Tests: `python3 -m unittest discover -s tests/unit -t .`
- `engineering/inventory/record_integrity.py` - read-only integrity checker for `EVD`, `SRC`, `VAL`, and `CASE` records. It checks identifiers, required fields, cross-references, case/evidence and case/validation symmetry, target-manifest paths, and index coverage. It does not validate JSON Schema conformance, verify artifact hashes, or rewrite records.
  - Run: `python3 -m engineering.inventory.record_integrity .`
  - Output: deterministic JSON with counts and sorted issues; exit status 1 when an error is found.
- `engineering/inventory/schema_validation.py` - read-only JSON Schema validator for target manifests and `EVD`, `SRC`, `VAL`, and `CASE` records. It checks structural conformance, enums, identifier patterns, and required fields. It does not check cross-references or artifact hashes.
  - Run: `python3 -m engineering.inventory.schema_validation .`
  - Output: deterministic JSON with counts and sorted issues; exit status 1 when a record violates its schema.
  - Requires: `PyYAML` and `jsonschema` (`python3 -m pip install -r requirements-dev.txt`).
- `engineering/inventory/archive_manifest.py` - deterministic SHA-256 inventory of Git-tracked working-tree files, used to generate the root `MANIFEST.json`. It does not include untracked, ignored, or external artifacts, and it does not follow symlinks.
  - Write: `python3 -m engineering.inventory.archive_manifest . --output MANIFEST.json`
  - Check: `python3 -m engineering.inventory.archive_manifest . --check MANIFEST.json`
  - Output: sorted JSON; `--check` exits 1 when the manifest is missing or stale.
- `engineering/parsers/image4.py` - read-only Image4 (IM4P) and Mach-O inspection for build artifacts. It reports container structure, payload hashes, compression, Mach-O segments/sections, UUID, source version, and PPL/`__TEXT_BOOT_EXEC` markers. It does not decompress Image4 payloads, verify signatures, evaluate trust, or execute code.
  - Run: `python3 -m engineering.parsers.image4 <artifact>`
  - Requires: Python standard library only.
- `engineering/analyzers/build_manifest_diff.py` - read-only differential summary of two BuildManifest.plist files. It compares component paths, 48-byte digests, and selected flags per build identity and reports added, removed, and changed entries. It does not decompress payloads, verify signatures, or claim that a change is a security fix.
  - Run: `python3 -m engineering.analyzers.build_manifest_diff <old.plist> <new.plist>`
  - Tests: `python3 -m unittest tests.unit.test_build_manifest_diff`
