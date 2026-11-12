# Public research register

Store one dated record per paper, repository, advisory, or technical write-up. Preserve the source's exact target scope and separate the author's claim from silicon's assessment. Use `source-record.template.yaml` as a starting point.

`SRC-0022` through `SRC-0025` are the 2026-11-12 additions to the A14 SPTM/PPL public-data set: a T8150 SPTM change analysis, an independent A14 SPTM emulator boot, and two tooling-level A13/A14/M1 TXM sources. Their claims are qualified in the records; none is a physical-device runtime measurement or a CVE attribution.

## Source index

| ID | Source | Date | Role |
|---|---|---|---|
| `SRC-0001` | Apple Platform Security - Operating system integrity | 2026-01-28 | Vendor PPL/SPTM applicability table |
| `SRC-0002` | Apple Developer - iOS 27.0.1 (24A446) release listing | 2026-09-28 | Build identity |
| `SRC-0003` | Apple security content of iOS 27 / iPadOS 27 | 2026-09-14 | Vulnerability advisory |
| `SRC-0004` | Apple security releases index | accessed 2026-11-05 | 27.0.1 CVE status |
| `SRC-0005` | The Apple Wiki - PPL/SPTM Bypasses | 2026-09-23 | Community bypass map |
| `SRC-0006` | SPTM introduction map (GitHub Gist) | accessed 2026-11-05 | Community SPTM timeline |
| `SRC-0007` | Exploit Reversing - iOS Security Research (part 01) | 2026-09-30 | Survey / counter-evidence |
| `SRC-0008` | Playport - StikDebug TXM detection note | 2026-09-28 | Tooling evidence |
| `SRC-0009` | Project Zero - The core of Apple is PPL | 2020-07-31 | Historical architecture |
| `SRC-0010` | Apple iOS 27.0.1 (24A446) BuildManifest for iPhone13,1 | 2026-09-28 | Primary build-packaging evidence |
| `SRC-0011` | iClarified - Dopamine 3.0 release coverage | 2026-08-07 | Public bypass compatibility ranges |
| `SRC-0012` | Apple iOS 27.0.1 (24A446) release kernelcache across four A14 product types | 2026-09-28 | Primary kernel-build evidence |
| `SRC-0013` | Apple Platform Security - Document revision history | accessed 2026-11-05 | Guide revision provenance |
| `SRC-0014` | Apple iOS 27.0.1 (24A446) BuildManifest for iPhone13,4 | 2026-09-28 | Second A14 build-packaging check |
| `SRC-0015` | iOS 27.0.1 jailbreak event fact-check and tracker | 2026-11-04 | Community counter-claim (A14/M1 as PPL) |
| `SRC-0016` | Apple iOS 27.0.1 (24A446) BuildManifest for iPhone13,2 and iPhone13,3 | 2026-09-28 | Remaining iPhone 12-family A14 build-packaging check |
| `SRC-0017` | Apple iOS 27.0.1 (24A446) SPTM and TXM payloads for iPhone13,1 | 2026-09-28 | Primary Image4 payload verification |
| `SRC-0018` | idevicerestore - restore component tag lookup and stitching | 2025-09-05 | Public restore-implementation source |
| `SRC-0019` | idevice crate - IMG4 restore component stitching (`img4.rs`) | 2026-07-11 | Public restore-implementation source |
| `SRC-0020` | Apple security content of iOS 27.2 / iPadOS 27.2 | 2026-10-26 | Vulnerability advisory |
| `SRC-0021` | Apple security content of iOS 27.2.1 / iPadOS 27.2.1 | 2026-11-09 | Follow-up vulnerability advisory |
| `SRC-0022` | IvanIVGrozny - SPTM TLB-invalidation race fix (iPhone Air/T8150) | 2026-10-21 | Public SPTM change analysis / comparison |
| `SRC-0023` | jprx/darwin-vm - SPTM/TXM-capable QEMU iOS/macOS emulator | 2026-10-05 | Independent A14 SPTM boot evidence (emulator) |
| `SRC-0024` | Crafttino21/ModStaller - iOS sideloading with TXM/SPTM JIT | 2026-10-24 | Tooling-level A13/A14/M1 TXM claim |
| `SRC-0025` | star-studios-official/azahar - iOS 27 A13/A14/M1 TXM detection | 2026-08-26 | Tooling-level A13/A14/M1 TXM claim |
