# Report - CASE-0001

## Status

Analyzed at the build level. `VAL-0002` (offline BuildManifest inspection for iPhone13,1), `VAL-0003` (offline kernelcache segment inspection), and `VAL-0004` (offline BuildManifest inspection for iPhone13,4) passed; `VAL-0001` (device metadata check) remains `not-run`. No runtime protection measurement was performed.

## Question

Is PPL or SPTM/TXM the page-table protection boundary on an A14 device running iOS 27.0.1 build 24A446?

## Findings

1. Apple's release listing confirms iOS 27.0.1 build 24A446, released 2026-09-28 (`EVD-0001`).
2. Apple's 2026-01-28 platform-security guide places A12-A14/S4-S10 in the PPL column, documents SPTM for A15+/M2+, and describes SPTM as replacing PPL on supported platforms (`EVD-0002`, `EVD-0003`).
3. The 24A446 restore build manifest for iPhone13,1 contains SPTM and TXM payloads:
   - `Ap,SecurePageTableMonitor` -> `Firmware/sptm.t8101.release.im4p`
   - `Ap,TrustedExecutionMonitor` -> `Firmware/txm.iphoneos.release.im4p`
   - `InstalledSPTM`, `RestoreSPTM`, `InstalledKernelCache`, and `RestoreKernelCache` are marked `Production` in `VariantContents`.
   - The restore SPTM/TXM entries are marked `IsLoadedByiBoot: true`; the installed entries are marked `IsFUDFirmware: true` and `Personalize: true`.
   - The BuildManifest SHA-256 is `f929ea00c7846fa2960d9b8bceeafcc0a93572daf3b595b1ce3cc9f481d3734f` (`EVD-0010`, `VAL-0002`).
4. The decompressed 24A446 kernelcache for iPhone13,1 independently shows the SPTM build structure:
   - Top-level Mach-O segments include `__DATA_SPTM` and `__TEXT_BOOT_EXEC`.
   - `__PPLTEXT`, `__PPLDATA`, and `__PPLDATA_CONST` are absent from the top-level segment list and from a byte scan of the full decompressed image.
   - The decompressed Mach-O SHA-256 is `76e0da7892f11a1ff7265cf217306c1211434682a2f398f6bfd7a042d7611fd4` (`EVD-0012`, `VAL-0003`).
5. The 24A446 BuildManifest for iPhone13,4 (iPhone 12 Pro Max, A14/T8101) independently contains the same SPTM and TXM entries and the same `InstalledSPTM`/`RestoreSPTM` `Production` markers (`EVD-0014`, `VAL-0004`). The build-level finding is therefore not specific to iPhone13,1.
6. Multiple secondary sources dated September 2026 independently report that iOS 27 introduces SPTM/TXM on A13/A14/M1:
   - The Apple Wiki states that with iOS 27.0 beta, SPTM bypasses apply to A13-A14 and M1 (`EVD-0006`).
   - A public SPTM introduction map places A13/A14 and M1 SPTM at Darwin/iOS 27.0 (`EVD-0007`).
   - A tooling evidence note says iOS 27 TXM detection treats A13/A14/M1 devices as TXM, except A12X (`EVD-0008`).
7. A contemporaneous survey still describes PPL on A12-A14/M1 and SPTM on A15+ (`EVD-0009`). A 2026-11-04 community tracker likewise frames A14/M1 as PPL and says A14+ needs an n-day SPTM bypass, but provides no build-specific measurement (`EVD-0015`). Both are retained as counter-evidence; they are consistent with Apple's older published page but do not account for the build manifests or kernelcache.
8. The primary Apple page carries a January 2026 date and contains no build-specific statement for 24A446; the guide's revision history does not list that page as updated after January 2026 (`EVD-0013`). The build artifacts are newer and target-specific, so they take precedence for the build-level question.

## Assessment

The build-level evidence resolves the contradiction: **the A14 / 24A446 images for iPhone13,1 and iPhone13,4 package SPTM and TXM, mark installed SPTM as a production component, and the iPhone13,1 kernelcache is built with SPTM segments rather than PPL segments.** The relevant page-table protection boundary for this build is therefore SPTM/TXM, not PPL. Apple's January 2026 table remains accurate for the OS versions it describes; it does not describe the iOS 27 A14 build.

**Current conclusion: inferred, high confidence at the build level.** The target device's runtime state remains `unknown`. The manifest's SPTM and TXM states are `inferred`; PPL remains `unknown` rather than being declared absent without a runtime measurement.

## What this establishes

- The 24A446 A14 builds for iPhone13,1 and iPhone13,4 contain SPTM (`sptm.t8101`) and TXM (`txm.iphoneos`) as installed/restore components.
- The 24A446 A14 kernelcache for iPhone13,1 is structurally an SPTM build (`__DATA_SPTM`, `__TEXT_BOOT_EXEC`) and has no PPL segment names.
- An "A14 PPL bypass" is mis-scoped for 24A446; the build-level boundary is SPTM/TXM.
- The public September 2026 reports are corroborated by Apple build artifacts.

## What this does not establish

- That the target device is an A14 device or is running 24A446.
- That SPTM/TXM is active, correctly configured, or enforcing on the exact target.
- That every boot path loads the monitors or that no fallback exists.
- That any specific CVE or public bypass affects 24A446.
- Any bypass, exploit primitive, or protection-disablement method.

## Limitations

- No device was available for metadata or runtime observation.
- Build packaging and kernelcache structure are not runtime measurements.
- Segment naming is a structural indicator, not proof that no PPL-related code exists in any component.
- The second A14 product type check covers packaging only; the iPhone13,4 kernelcache was not inspected.
- No Apple source specific to 24A446 narrates the mechanism change; the finding is inferred from the build artifacts plus Apple's mechanism documentation.
- The supporting secondary sources are community/tooling reports; the contradictory Apple page carries a January 2026 date and is not listed as updated after that, and the contradictory survey and tracker may be imprecise.
- The A13/A14 grouping in public reports may hide device- or build-specific differences.

## Next steps

1. Verify product type, SoC, OS version, and build on the owned target device using non-invasive metadata.
2. If permitted non-invasive observation can establish SPTM/TXM presence, record it as a validation result; otherwise keep the runtime state `unknown`.
3. Look for an Apple security note or platform-security update specific to iOS 27.0.1 / 24A446.
4. Use `CASE-0003` for public bypass scope; keep bypass and exploitation work outside this repository.
