# Engineering workspace

Reusable research-support tools belong here. Initial candidates: target inventory, artifact hashing/provenance, evidence indexing, metadata parsing, and report generation. Keep tools deterministic, fixture-tested, and read-only with respect to original inputs.

## Inventory

- `engineering/inventory/build_manifest.py` - read-only BuildManifest.plist summarizer for build identities, SPTM/TXM entries, kernelcache references, and 48-byte payload digests. It does not fetch artifacts or assert runtime state.
  - Run: `python3 -m engineering.inventory.build_manifest <BuildManifest.plist>`
  - Tests: `python3 -m unittest discover -s tests/unit -t .`
