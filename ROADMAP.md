# ROADMAP

Roadmap items are goals, not claims of completed capability. Move an item only when its exit criteria are met and evidence is linked.

| Phase | Focus | Deliverables | Exit criteria |
|---|---|---|---|
| P0 | Foundation | Repository structure, conventions, schemas, templates | New target and research case can be added consistently |
| P1 | Target baseline | Exact device/build inventory, artifact provenance, protection-state record | Every target field has a source or is explicitly `unknown` |
| P2 | Architecture model | A14-scoped PPL/SPTM/TXM applicability matrix, build-payload evidence, and adjacent trust-boundary notes | Claims are scoped to source version, build, and target applicability |
| P3 | Public research survey | Dated source register, A14/24A446 compatibility matrix, candidate cases | Each relevant claim has provenance and confidence |
| P4 | Offline tooling | Inventory, hashing, metadata parsing, evidence indexing | Tool outputs are deterministic and tested against fixtures |
| P5 | Safe validation | Synthetic protection models, test cases, result schema | Tests are repeatable without bypassing protections on a live device |
| P6 | Closure | Technical report, limitations, regression archive | Findings are reviewed, reproducible, and appropriately disclosed |

## Current A14 baseline (2026-11-10)

- Target specification: A14 / iPhone 12 mini / iOS 27.0.1 build 24A446. The build is user-specified and corroborated by Apple's release listing (`EVD-0001`); physical device identity and installation are still pending.
- Build-level mechanism: the 24A446 restore BuildManifests for the four iPhone 12-family A14 product types contain SPTM (`Firmware/sptm.t8101.release.im4p`) and TXM (`Firmware/txm.iphoneos.release.im4p`) payloads and mark `InstalledSPTM`/`RestoreSPTM` as `Production` (`EVD-0010`, `EVD-0014`, `EVD-0016`, `VAL-0002`, `VAL-0004`, `VAL-0005`). The installed/restore SPTM, release TXM, and release kernelcache digests match across the manifests. The release kernelcache is byte-identical across all four product types (`EVD-0017`, `VAL-0006`), and its decompressed Mach-O has `__DATA_SPTM`/`__TEXT_BOOT_EXEC` segments and no PPL segment names (`EVD-0012`, `VAL-0003`). The extracted iPhone13,1 installed SPTM and TXM payloads match the manifest digest fields and decompress to arm64e Mach-O with SPTM/TXM identifiers (`EVD-0018`, `EVD-0019`, `VAL-0007`); the distinct restore-role `rspt`/`rtrx` digests are reproduced by a fourcc-only retag of the same IM4P payloads (`EVD-0020`, `VAL-0008`). The build is therefore modeled as SPTM/TXM-based, not PPL-based.
- Documentation conflict: Apple's 2026-01-28 Operating system integrity page places A12-A14 in the PPL column (`EVD-0002`, `EVD-0003`); the guide's revision history does not list that page as updated after January 2026 (`EVD-0013`). Secondary September 2026 reports corroborate the SPTM/TXM change (`EVD-0006`-`EVD-0008`); a contemporaneous survey and a 2026-11-04 community tracker repeat the older model and are retained as counter-evidence (`EVD-0009`, `EVD-0015`).
- Runtime state: PPL, SPTM, and TXM remain `unknown` for the exact target. `VAL-0001` is `not-run` because no device was available.
- Cases: `CASE-0001` records the mechanism finding across the four iPhone 12-family A14 product types; `CASE-0002` records the iOS 27 vulnerability baseline (`research/public-research/ios27-vulnerability-register.yaml`); `CASE-0003` records public bypass scope for A14.

## iOS 27.2 differential (2026-11-11)

- Comparison pair: iPhone13,1 iOS 27.0.1 (24A446) and iOS 27.2 (24B119). The 27.2 image is a local restore IPSW; its BuildManifest SHA-256 is `2d13f370...e431ec` (`EVD-0021`).
- Build-level diff: 57 of 95 BuildManifest component entries differ, 38 are identical, and no keys were added or removed (`EVD-0022`, `VAL-0009`).
- Kernel diff: `KernelManagement_host-514.2.2` to `514.40.8`; decompressed image 66,535,424 to 66,813,952 bytes; 207 of 250 kext UUIDs change, 43 remain identical; function starts 1,361 to 1,382 (`EVD-0023`, `VAL-0010`).
- Monitor diff: SPTM 820.0.22 to 820.40.24; TXM remains 217.0.2 but has a different UUID and decompressed hash; both 24B119 IM4P SHA-384 values match manifest digests (`EVD-0024`, `VAL-0011`).
- Advisory diff: 27.2 has 163 CVEs, disjoint from the 163 in 27.0, including 15 Kernel and 26 WebKit entries (`EVD-0025`, `SRC-0020`). 27.2.1 adds nine CVEs; 24B119 is not the latest patch level (`EVD-0026`, `SRC-0021`).
- Open work: no CVE-to-function attribution, no runtime measurement, no encrypted-cryptex inspection, no exploitability or bypass claim (`CASE-0004`).

## Immediate work queue

1. Verify the physical device identity and exact iOS build from the device itself using non-invasive metadata.
2. Complete P1 by linking device evidence in the target manifest; keep runtime protection states `unknown` until observed, and label build-level inferences separately.
3. Maintain the P2 A14 scope: model SPTM/TXM as packaged in 24A446, PPL as the historical A14 boundary for earlier iOS versions, and runtime state as unverified.
4. Expand P3 with dated third-party research and Apple security notes specific to build 24A446; the four iPhone 12-family A14 product types are build-level covered, so extend the check to A14 iPad product types only if they enter scope. Keep the vulnerability register (`CASE-0002`) and bypass scope survey (`CASE-0003`) separate.
5. Design the P5 non-invasive validation and keep `VAL-0001` `not-run` until it is executed; `VAL-0002` through `VAL-0008` record the completed offline build-artifact checks.
6. Keep bypass, exploitation, and protection-disablement work out of scope.
7. In `CASE-0004`, move from build-level diff to a normalized function-level diff of `com.apple.kernel` and the AVE/ANE kexts, then map changed functions to advisory descriptions only when the evidence supports it. Keep WebKit/ImageIO out unless a lawful source for those binaries is available.

## Completion rule

A phase is not complete because files exist. It is complete when its exit criteria are met, supporting evidence is linked, and unresolved limitations are documented.
