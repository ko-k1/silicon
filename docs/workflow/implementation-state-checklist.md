# Implementation state checklist

- **Last verified:** 2026-11-10
- **Verified against commit:** `341dcce`
- **Target scope:** A14 / iPhone 12 mini / iOS 27.0.1 (24A446), plus repository-level implementation
- **Purpose:** give a human reviewer and an LLM agent the same view of what exists, what is proven, what is blocked, and how to verify it

This document is a status map, not a new evidence record. A checked box means the item exists and the verification command or linked record supports it. It does not upgrade a build-level observation into a runtime fact.

## How to use this document

### For human reviewers

1. Read the snapshot and claim-state matrix below.
2. Run the verification commands in section 6.
3. Open the linked evidence and validation records before accepting a status.
4. Check target scope, provenance, counter-evidence, and limitations, not only the conclusion.
5. Update a status only after adding or changing an evidence/validation record.

### For LLM agents

1. Read this file before planning work in the repository.
2. Use the state vocabulary exactly; do not replace `partial`, `blocked`, `not-run`, or `unknown` with a success claim.
3. Run the relevant verification command before reporting an item as `done`.
4. If a command cannot be run, say so and leave the existing state unchanged.
5. Cite `EVD-####`, `VAL-####`, `SRC-####`, or `CASE-####` records for material claims.
6. Do not infer runtime protection state from build packaging, payload structure, a SoC family, or a third-party summary.
7. Do not commit raw firmware, device identifiers, crash logs, or extracted payloads.

## State vocabulary

Checklist and phase states:

| State | Meaning |
|---|---|
| `done` | The item exists and its stated acceptance check passes with linked evidence. |
| `partial` | Some deliverables exist, but the acceptance check is incomplete or manually performed. |
| `blocked` | The next step requires an external input, currently a physical target device. |
| `not-started` | No substantive implementation exists. |
| `stale` | A record exists but is known not to describe the current repository state. |

Claim and evidence states use `unknown`, `observed`, `inferred`, `confirmed`, and `contradicted` as defined in `docs/research/evidence-model.md`.

Use `passed`, `failed`, `inconclusive`, and `not-run` only for validation results, matching `schemas/validation-result.schema.json`.

## Current snapshot

| Area | State | Implemented | Missing / next | Verify |
|---|---|---|---|---|
| Repository foundation (P0) | `done` | `AGENTS.md`, `VISION.md`, `ROADMAP.md`, schemas for all record families, case and target-manifest templates, evidence/source/validation indexes | Keep schemas and committed records synchronized as the repository grows | Section 6 commands 1-4 |
| Target identity (P1) | `blocked` | Target manifest with `pending`/`unknown` fields and build-level provenance | Physical ProductType, SoC, installed OS, and build are unverified | `VAL-0001`; `targets/manifests/iphone12mini-ios27.0.1.yaml` |
| Build artifact provenance (P1/P2) | `done` | Apple release listing; BuildManifests for iPhone13,1, iPhone13,4, and iPhone13,2/3; kernelcache; SPTM/TXM payloads; restore-role retag check | Device installation of the build is unverified | `EVD-0001`, `EVD-0010`, `EVD-0014`, `EVD-0016`, `EVD-0017`, `EVD-0018`, `EVD-0019`, `EVD-0020` |
| Build-level protection model (P2) | `done` | SPTM/TXM packaging, SPTM kernel structure, cross-product kernelcache identity, payload and restore-role digest matches, Mach-O identifiers | A14 iPad coverage remains open; runtime is not claimed | `CASE-0001/report.md`; `VAL-0002`-`VAL-0008` |
| Runtime protection state (P2/P5) | `blocked` | No runtime evidence | Requires a physical target device and non-invasive observation | `VAL-0001` |
| Public research register (P3) | `partial` | 19 dated `SRC` records covering Apple documentation, advisories, community reports, build artifacts, and restore implementations | No Apple security note specific to 24A446 was found; community claims need continued re-checking | `research/public-research/README.md` |
| Vulnerability baseline (P3) | `done` | iOS 27 advisory register and 27.0.1 CVE status | Register facts are not exploitability or bypass findings | `CASE-0002`; `ios27-vulnerability-register.yaml` |
| Public bypass scope (P3) | `partial` | Reviewed public compatibility ranges and counter-evidence | No reviewed source demonstrates an A14-specific bypass on 24A446 | `CASE-0003` |
| BuildManifest tooling (P4) | `done` | Read-only deterministic summarizer and 6 fixture tests | No fetching, signature verification, or runtime assertion by design | Section 6 commands 2-3 |
| Record integrity tooling (P4) | `done` | Read-only cross-reference validator for `EVD`/`SRC`/`VAL`/`CASE`, synthetic negative tests, and a repository integration test | Does not validate JSON Schema conformance or artifact hashes | Section 6 commands 2-6 |
| Schema validation tooling (P4) | `done` | Read-only JSON Schema validator for target manifests and all record families, with negative, malformed-input, template, and integration tests | Does not check cross-references or artifact hashes | Section 6 commands 2-6 |
| Repository archive manifest (P4) | `done` | Root `MANIFEST.json` is generated from the Git index by `archive_manifest.py` and checked by a unit test | Covers tracked files only; untracked and external artifacts are excluded by design | Section 6 commands 2-6 |
| Validation surface (P5) | `partial` | 7 offline validations passed; 1 device validation is `not-run` | No synthetic protection model; no device runtime measurement | `validation/README.md`; `VAL-0001`-`VAL-0008` |
| Closure/reporting (P6) | `partial` | Baseline and case reports exist | Independent review, closure report, and disclosure decision are not complete | `reports/technical/` |

## Claim-state matrix

Use this matrix to keep observations, build-level inferences, and runtime unknowns separate.

| Claim | State | Evidence | Does not establish |
|---|---|---|---|
| Apple released iOS 27.0.1 build 24A446 on 2026-09-28 | observed | `EVD-0001` | That the target device runs it |
| The 24A446 iPhone 12-family manifests package SPTM and TXM | observed | `EVD-0010`, `EVD-0014`, `EVD-0016` | Runtime activation |
| The iPhone13,1 installed SPTM/TXM payloads match the manifest digest fields | observed | `EVD-0018`, `EVD-0019`; `VAL-0007` | Signature validity or device acceptance |
| The restore-role `rspt`/`rtrx` digests match fourcc-only retags of the installed payloads | observed | `EVD-0020`; `VAL-0008` | Stitched IMG4/AP-ticket acceptance or runtime state |
| The 24A446 release kernelcache is structurally an SPTM build | observed | `EVD-0012`; `VAL-0003` | That every boot path loads it |
| The release kernelcache is byte-identical across the four product types | observed | `EVD-0017`; `VAL-0006` | A per-device runtime measurement |
| The A14 / 24A446 build-level mechanism is SPTM/TXM, not PPL (high confidence) | inferred | `CASE-0001` conclusion | PPL code or fallback absence |
| The exact target device is an iPhone13,1 running 24A446 | unknown | `VAL-0001` is `not-run` | Any runtime state |
| SPTM/TXM is active, configured, and enforcing on the target | unknown | No runtime evidence | Any bypass or exploitability claim |
| A public bypass applies to A14 / 24A446 | unknown | `CASE-0003` (evidence gap) | That no private bypass exists |

## Detailed checklist

### P0 - Foundation (`done`)

- [x] Repository structure and ownership map documented
- [x] `AGENTS.md`, `VISION.md`, and `ROADMAP.md` define scope and safety rules
- [x] JSON schemas exist for target manifests, evidence records, research cases, and validation results
- [x] Research case template exists under `research/cases/_template/`
- [x] Evidence, source, case, and validation indexes are maintained
- [x] Stable ID conventions are documented
- [x] Schema validation is automated in the test suite
- [x] A target-manifest template is provided alongside the initial manifest

### P1 - Target baseline (`blocked`)

- [x] Apple release identity recorded for 24A446
- [x] Build-level product-type coverage recorded for iPhone13,1, iPhone13,2, iPhone13,3, and iPhone13,4
- [x] BuildManifest, kernelcache, and SPTM/TXM payload hashes recorded
- [x] Target manifest explicitly separates `pending`, `unknown`, and `inferred` fields
- [ ] Physical device ProductType verified on hardware
- [ ] Physical device SoC and architecture verified on hardware
- [ ] Installed OS version and build verified on hardware
- [ ] Device installation of 24A446 confirmed

### P2 - Architecture model (`done` at build level; runtime `blocked`)

- [x] SPTM/TXM packaging documented for all four iPhone 12-family A14 product types
- [x] Kernelcache SPTM segment structure documented
- [x] Cross-product kernelcache byte identity documented
- [x] Extracted SPTM/TXM payloads linked to manifest digest fields
- [x] PPL treated as the historical A14 boundary for earlier OS versions
- [x] Runtime SPTM/TXM state kept `unknown`
- [x] Restore-specific `rspt`/`rtrx` digest difference resolved as a fourcc-only IM4P retag (`EVD-0020`, `VAL-0008`); stitched IMG4 path remains open
- [ ] A14 iPad product types checked, if they enter scope
- [ ] Every boot path and fallback configuration accounted for

### P3 - Public research (`partial`)

- [x] Dated source register with scope and provenance
- [x] Apple 27.0 advisory and 27.0.1 CVE status recorded
- [x] Public bypass claims catalogued with counter-evidence
- [x] Build-artifact sources distinguished from documentary sources
- [ ] Apple security note or platform-security update specific to 24A446 found
- [ ] A14 iPad or regional build claims checked, if they enter scope
- [ ] Independent source review completed

### P4 - Offline tooling (`partial`)

- [x] Read-only BuildManifest summarizer implemented
- [x] Synthetic BuildManifest fixture committed
- [x] Unit tests cover identity, components, digests, kernel references, CLI output, and missing components
- [x] Tool output is deterministic JSON
- [ ] Image4/Mach-O inspection automated inside the repository
- [ ] Artifact hashing/provenance inventory for external firmware implemented
- [x] Evidence index or cross-reference validator implemented
- [x] JSON Schema validation implemented for target manifests and all record families
- [x] Repository archive manifest generator implemented
- [x] Root `MANIFEST.json` regenerated or explicitly retired
- [ ] Negative and malformed-input fixtures expanded

### P5 - Safe validation (`partial`)

- [x] Validation result schema and result states documented
- [x] Offline BuildManifest checks passed for all four iPhone 12-family A14 product types
- [x] Offline kernelcache segment and byte checks passed
- [x] Offline cross-product digest check passed
- [x] Offline SPTM/TXM payload and manifest digest check passed
- [x] Offline restore-role `rspt`/`rtrx` digest reproduction passed (`VAL-0008`)
- [ ] Device metadata check executed (`VAL-0001` is `not-run`)
- [ ] Synthetic PPL/SPTM/TXM state model added
- [ ] Regression harness for parser fixtures added
- [ ] Runtime protection-state validation designed and authorized

### P6 - Closure (`partial`)

- [x] Consolidated baseline report exists
- [x] Case-level reports and limitations exist
- [ ] Independent review recorded
- [ ] Closure report with final scope and limitations
- [ ] Disclosure decision recorded
- [ ] Regression archive linked from the closure record

## Verification commands

Run from the repository root. Expected results are current as of the commit in the header.

```sh
# 1. Repository cleanliness and current commit
git status --short --branch
git log --oneline -3

# 2. BuildManifest tool smoke test
python3 -m engineering.inventory.build_manifest tests/unit/fixtures/BuildManifest.minimal.plist

# 3. Unit tests
python3 -m unittest discover -s tests/unit -t . -v
# expected: 36 tests, OK

# 4. JSON Schema validation
python3 -m engineering.inventory.schema_validation .
# expected: "ok": true with no issues

# 5. Archive manifest freshness
python3 -m engineering.inventory.archive_manifest . --check MANIFEST.json
# expected: exit status 0

# 6. Record cross-reference and index integrity
python3 -m engineering.inventory.record_integrity .
# expected: "ok": true with no issues

# 7. Record counts
find research/evidence -name 'EVD-*.yaml' | wc -l          # expected: 20
find research/public-research -name 'SRC-*.yaml' | wc -l   # expected: 19
find validation/results -name 'VAL-*.yaml' | wc -l         # expected: 8
find research/cases -maxdepth 2 -name 'case.yaml' | wc -l  # expected: 4 (3 cases + template)

# 8. Confirm the device check was not run
grep -n 'status: not-run' validation/results/VAL-0001.yaml
```

Schema validation is automated by `tests/unit/test_schema_validation.py` and by command 4. Install `PyYAML` and `jsonschema` from `requirements-dev.txt` first. The test also checks the committed record templates against their schemas.

## How to update this checklist

1. Change the status only with new evidence: add an `EVD`/`VAL` record or run the stated verification.
2. Update the snapshot row, the detailed checkbox, and `Last verified`.
3. Keep the claim-state matrix aligned with the new evidence.
4. If a command fails, record `failed` or `inconclusive` in the relevant validation record; do not hide the failure in prose.
5. If a check is still blocked, leave `blocked` or `not-run` and state the missing input.
6. Update `Verified against commit` after committing the change.

## Known stale or conflicting artifacts

- `silicon-a14-ios27-ppl-sptm-txm.md` - historical 2026-11-05 working note. It carries a superseded banner and obsolete local evidence numbering; use `research/cases/CASE-0001/report.md` instead.
- `validation/models/` - contains a policy README only; no synthetic protection model exists yet.
- `VAL-0001` - intentionally `not-run`; no target device was connected.
- `research/public-research/ios27-vulnerability-register.yaml` - register data, not an exploitability assessment.
