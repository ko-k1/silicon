# Engineering workspace

Reusable research-support tools belong here. Initial candidates: target inventory, artifact hashing/provenance, evidence indexing, metadata parsing, and report generation. Keep tools deterministic, fixture-tested, and read-only with respect to original inputs.

## Inventory

- `engineering/inventory/build_manifest.py` - read-only BuildManifest.plist summarizer for build identities, SPTM/TXM entries, kernelcache references, and 48-byte payload digests. It does not fetch artifacts or assert runtime state.
  - Run: `python3 -m engineering.inventory.build_manifest <BuildManifest.plist>`
  - Tests: `python3 -m unittest discover -s tests/unit -t .`
- `engineering/inventory/record_integrity.py` - read-only integrity checker for `EVD`, `SRC`, `VAL`, and `CASE` records. It checks identifiers, required fields, cross-references, case/evidence and case/validation symmetry, target-manifest paths, and index coverage. It does not validate JSON Schema conformance, verify artifact hashes, or rewrite records.
  - Run: `python3 -m engineering.inventory.record_integrity .`
  - Output: deterministic JSON with counts and sorted issues; exit status 1 when an error is found.
  - Requires: `PyYAML` (`python3 -m pip install -r requirements-dev.txt`).
