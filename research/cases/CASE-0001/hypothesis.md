# Hypothesis - CASE-0001

## Question

Which page-table protection mechanism applies to an A14-based device running iOS 27.0.1 build 24A446: the legacy Page Protection Layer (PPL), or the Secure Page Table Monitor (SPTM) together with the Trusted Execution Monitor (TXM)?

This case resolves applicability and evidence requirements only. It does not investigate how to bypass, disable, or weaken any mechanism.

## Claim

The A14 / iOS 27.0.1 build 24A446 packages and uses SPTM with TXM for page-table and code-execution protection. Apple's 2026-01-28 platform documentation, which places A12-A14 in the PPL column, no longer describes the iOS 27 runtime.

## Why this was disputed

| Source | Date | Statement | Class |
|---|---|---|---|
| Apple Platform Security guide (`SRC-0001`) | 2026-01-28 | PPL applies to A12-A14; SPTM is A15+/M2+ and replaces PPL. | primary, pre-iOS 27 |
| Apple Platform Security revision history (`SRC-0013`) | accessed 2026-11-05 | Operating system integrity is listed as updated in January 2026 and is not listed in the August 2026 update. | primary, provenance |
| The Apple Wiki (`SRC-0005`) | 2026-09-23 | With iOS 27.0 beta, SPTM bypasses apply to A13-A14 and M1 as well as A15+. | secondary |
| SPTM introduction map (`SRC-0006`) | accessed 2026-11-05 | A13/A14 and M1 introduce SPTM in Darwin/iOS 27.0. | secondary |
| Playport/StikDebug note (`SRC-0008`) | 2026-09-28 | iOS 27 tooling treats A13/A14/M1 devices as TXM, except A12X. | secondary, tooling |
| Exploit Reversing survey (`SRC-0007`) | 2026-09-30 | PPL applies to A12-A14 and M1; SPTM to A15+. | secondary, counter-evidence |
| Apple 24A446 BuildManifest for iPhone13,1 (`SRC-0010`) | 2026-09-28 | The image contains `sptm.t8101` and `txm.iphoneos`; `InstalledSPTM`/`RestoreSPTM` are `Production`. | primary, build artifact |
| Apple 24A446 kernelcache for iPhone13,1 (`SRC-0012`) | 2026-09-28 | The Mach-O has `__DATA_SPTM` and `__TEXT_BOOT_EXEC` segments and no `__PPLTEXT`/`__PPLDATA` segment names. | primary, build artifact |
| Apple 24A446 BuildManifest for iPhone13,4 (`SRC-0014`) | 2026-09-28 | A second A14 product type contains the same `sptm.t8101` and `txm.iphoneos` entries, with `InstalledSPTM`/`RestoreSPTM` marked `Production`. | primary, build artifact |
| Community iOS 27.0.1 tracker (`SRC-0015`) | 2026-11-04 | Frames A14/M1 as PPL and says A14+ still needs an n-day SPTM bypass; no build-specific measurement. | secondary, counter-evidence |

The primary Apple guide and the September 2026 secondary reports could not both describe the shipping iOS 27 runtime. The contradiction was the core of this case.

## Target and preconditions

- Target manifest: `targets/manifests/iphone12mini-ios27.0.1.yaml`
- Exact build: iOS 27.0.1, build 24A446 (user-specified; Apple release listing in `EVD-0001`)
- SoC: A14 (user-specified; still `pending` in the manifest until device verification)
- Build artifact: iPhone13,1 24A446 restore image, BuildManifest SHA-256 `f929ea00c7846fa2960d9b8bceeafcc0a93572daf3b595b1ce3cc9f481d3734f` (`EVD-0010`)
- Cross-product artifact: iPhone13,4 24A446 restore image, BuildManifest SHA-256 `342b8ea26ca5a940efd867ddc807d7cd9212554579f1a063d219b13ebf5d0392` (`EVD-0014`)
- Required configuration: unmodified, owned target device if a metadata check is performed
- Known limitations: no device inspection; no build-specific Apple narrative describing the mechanism change

## Expected behavior

If the claim is correct, the A14 24A446 images should contain SPTM/TXM payloads across A14 product types, public compatibility and tooling reports should treat A14 iOS 27 devices as SPTM/TXM-capable, and Apple's pre-iOS 27 PPL table would remain accurate only for earlier OS versions on A14.

If the claim is wrong, the A14 24A446 image should not package SPTM/TXM as installed components, and the SPTM reports should be explained by beta-only behavior, tool fallback heuristics, or a different SoC scope.

## Supporting evidence

- `EVD-0001` - Apple lists iOS 27.0.1 build 24A446 with a 2026-09-28 release date.
- `EVD-0006` - Apple Wiki reports SPTM bypass applicability expanding to A13-A14/M1 with iOS 27.0 beta.
- `EVD-0007` - Public SPTM introduction map places A13/A14 and M1 SPTM at iOS 27.0.
- `EVD-0008` - Independent tooling note treats A13/A14/M1 iOS 27 devices as TXM.
- `EVD-0010` - Apple's 24A446 BuildManifest for iPhone13,1 includes SPTM and TXM payloads and marks installed/restore SPTM as `Production`.
- `EVD-0012` - The 24A446 kernelcache for iPhone13,1 has `__DATA_SPTM` and `__TEXT_BOOT_EXEC` segments and no `__PPLTEXT`/`__PPLDATA` segment names.
- `EVD-0014` - The 24A446 BuildManifest for iPhone13,4, a second A14 product type, contains the same SPTM/TXM payloads and `Production` markers.

## Build-level resolution

The BuildManifest is primary evidence for what the build packages. For iPhone13,1 / 24A446 it contains:

- `Ap,SecurePageTableMonitor` -> `Firmware/sptm.t8101.release.im4p`
- `Ap,TrustedExecutionMonitor` -> `Firmware/txm.iphoneos.release.im4p`
- `Ap,RestoreSecurePageTableMonitor` and `Ap,RestoreTrustedExecutionMonitor`, both `IsLoadedByiBoot: true`
- `InstalledSPTM` and `RestoreSPTM` marked `Production` in `VariantContents`

The decompressed kernelcache independently shows a top-level Mach-O segment set that includes `__DATA_SPTM` and `__TEXT_BOOT_EXEC`, and no `__PPLTEXT`, `__PPLDATA`, or `__PPLDATA_CONST` segment names (`EVD-0012`, `VAL-0003`). The iPhone13,4 / 24A446 BuildManifest independently contains the same SPTM and TXM entries and the same `InstalledSPTM`/`RestoreSPTM` `Production` markers (`EVD-0014`, `VAL-0004`), so the finding is not specific to iPhone13,1. `T8101` is the A14 SoC identifier in the SPTM payload name. This resolves the build-level mechanism in favor of SPTM/TXM and explains why the January 2026 guide is not sufficient for the 24A446 target; the guide's revision history does not list that page as updated after January 2026 (`EVD-0013`). It does not measure the runtime state of a specific device.

## Counter-evidence and alternatives

- `EVD-0002` - Apple documents SPTM as A15+/M2+ and replacing PPL on supported platforms.
- `EVD-0003` - Apple places A12-A14 in the PPL applicability column.
- `EVD-0009` - A September 2026 survey repeats PPL on A12-A14/M1 and SPTM on A15+.
- `EVD-0015` - A 2026-11-04 community tracker still frames A14/M1 as PPL and says A14+ needs an n-day SPTM bypass, but provides no build-specific measurement.
- Alternative explanation: Apple's January 2026 Operating system integrity page may be stale because iOS 27 introduced a mechanism change after that page was last updated (`EVD-0013`).
- Alternative explanation: the build may package SPTM/TXM for restore or update paths while using a different mechanism in the installed OS. The `InstalledSPTM` entry and the installed `Ap,SecurePageTableMonitor` entry argue against this, but a runtime measurement would be needed to settle it.
- Alternative explanation: A13 and A14 may not behave identically even though both appear in the same public SPTM map.

## Rejection criteria

- A build-specific Apple source states that A14 on iOS 27.0.1 uses PPL and not SPTM.
- Reproducible non-invasive evidence from the exact target shows PPL active and SPTM/TXM absent.
- The A14 iOS 27 SPTM reports are shown to describe only a beta-only configuration, a different SoC, or a tool fallback rather than shipping behavior.
- The target is shown not to be an A14 device or not to be running 24A446.

## Safe validation plan

1. Review Apple's build-specific security notes and platform-security documentation for iOS 27/27.0.1.
2. If an owned target device is available, read only non-invasive identity metadata (product type, build version) and compare it with the manifest.
3. Keep build-artifact checks offline: hash the artifact, inspect manifest entries and Mach-O segment names, compare a second A14 product type where practical, and do not modify the artifact in place.
4. Do not attempt kernel memory access, page-table modification, code-signing changes, SPTM/TXM patching, protection disablement, or persistence.
5. If runtime mechanism state cannot be established through permitted means, keep it `unknown`. Do not convert build packaging, kernelcache structure, or secondary reports into a runtime measurement.

## Research boundary

Public PPL/SPTM research is catalogued at the level of source, date, claimed scope, and disclosure status. This case does not reproduce exploit code, patch offsets, bypass steps, or device-modification procedures.
