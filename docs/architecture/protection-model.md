# Protection architecture model

## Purpose

This document models security boundaries. It separates platform-general descriptions, target-build evidence, and target-specific runtime observations so that one is not mistaken for another.

## A14 platform baseline

The current target specification is an A14-based device with iOS 27.0.1 build 24A446 (SoC and build user-specified; device identity and installation still pending verification).

Apple's *Apple Platform Security* guide's Operating system integrity page, published 2026-01-28, places A12-A14/S4-S10 in the PPL applicability column and documents SPTM for A15-or-later and M2-or-later SoCs, where it replaces PPL (`SRC-0001`, `EVD-0002`, `EVD-0003`). The guide's revision history does not list that page as updated after January 2026 (`EVD-0013`).

The 24A446 restore BuildManifests for iPhone13,1 and iPhone13,4 contain SPTM and TXM payloads and mark `InstalledSPTM`/`RestoreSPTM` as `Production` (`SRC-0010`, `SRC-0014`, `EVD-0010`, `EVD-0014`, `VAL-0002`, `VAL-0004`). The decompressed iPhone13,1 kernelcache has `__DATA_SPTM` and `__TEXT_BOOT_EXEC` segments and no PPL segment names (`SRC-0012`, `EVD-0012`, `VAL-0003`). For this build, the page-table protection boundary is therefore modeled as **SPTM/TXM**, not PPL. A community tracker still frames A14/M1 as PPL but provides no build-specific measurement (`EVD-0015`).

For A14 / 24A446:

- **PPL** is the historical A14 mechanism for earlier iOS versions. It is not expected to be the active boundary on 24A446 because the build packages SPTM/TXM, but runtime state is unverified.
- **SPTM** is present in the 24A446 builds for iPhone13,1 and iPhone13,4 as `Firmware/sptm.t8101.release.im4p`.
- **TXM** is present in the same builds as `Firmware/txm.iphoneos.release.im4p`.
- The runtime state of any mechanism on the exact target remains `unknown`.

This is a statement about build packaging and documented applicability, not a measurement of the target. See `CASE-0001` for the mechanism question, `CASE-0002` and `research/public-research/ios27-vulnerability-register.yaml` for the vulnerability register, `CASE-0003` for public bypass scope, and `analysis/architecture/page-table-protection.md` for the architecture notes.

## Components to track

| Component | Questions to document | 24A446 A14 build status | Target runtime state |
|---|---|---|---|
| Kernel | Build identity, image provenance, relevant documented interfaces | Build identity 24A446; kernelcache manifest present | unknown |
| PPL | Which memory/page-table integrity properties are documented for this platform and build? | Not expected to be the active boundary; SPTM/TXM packaged | unknown |
| SPTM | Is it present and active on this exact target? What evidence establishes this? | Present in the iPhone13,1 and iPhone13,4 BuildManifests (`sptm.t8101`); iPhone13,1 kernelcache has `__DATA_SPTM` | unknown; do not assume active |
| TXM | What policy boundary and responsibilities are documented? | Present in both checked BuildManifests (`txm.iphoneos`) | unknown |
| PAC | Which pointer-authentication capabilities are available and used? | Not separately verified for A14 in the reviewed sources | unknown |
| AMFI / code-signing | Which code-integrity policies apply to the target build? | Not established | unknown |
| Trust Cache | What is documented about trust-cache lifecycle and target applicability? | Not established | unknown |
| Secure Boot chain | What boot-chain properties can be established from authoritative sources? | Not established | unknown |

## Modeling requirements

For every component, record: source and publication date; source platform/version; target applicability; directly observed facts; inferred relationships; unresolved questions; and counter-evidence. A diagram must label unverified edges and must not imply an implementation detail that the sources do not establish.

For the 24A446 A14 target, label SPTM/TXM edges as **"packaged in build; runtime unverified"** rather than "active." Label PPL as **"historical/pre-iOS 27; not expected on 24A446"** rather than "present" or "absent."

## Terminology caution

PPL and SPTM are not interchangeable labels. Do not infer that one is active, absent, replaced, or bypassed solely from the presence of the other in a document. Describe the exact security property being discussed and scope it to the relevant hardware, software, and build.

On 24A446, a hypothesis framed as an "A14 PPL bypass" is mis-scoped: the checked A14 builds package SPTM/TXM. Conversely, packaging evidence does not establish that the exact target's SPTM/TXM is enabled, correctly configured, or enforcing. Historical PPL research remains relevant to earlier A14 iOS versions. Community claims that A14/M1 remains PPL should be recorded as counter-evidence until supported by a build-specific or runtime measurement.
