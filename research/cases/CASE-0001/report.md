# Report - CASE-0001

- Updated: 2026-11-10

## Status

Analyzed at the build level. `VAL-0002` (offline BuildManifest inspection for iPhone13,1), `VAL-0003` (offline kernelcache segment inspection), `VAL-0004` (offline BuildManifest inspection for iPhone13,4), `VAL-0005` (offline BuildManifest inspection for iPhone13,2/iPhone13,3 plus cross-product digest comparison), `VAL-0006` (offline byte comparison of the release kernelcache across all four product types), and `VAL-0007` (offline SPTM/TXM Image4 payload and Mach-O inspection) passed; `VAL-0001` (device metadata check) remains `not-run`. No runtime protection measurement was performed.

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
4. The decompressed 24A446 release kernelcache independently shows the SPTM build structure:
   - Top-level Mach-O segments include `__DATA_SPTM` and `__TEXT_BOOT_EXEC`.
   - `__PPLTEXT`, `__PPLDATA`, and `__PPLDATA_CONST` are absent from the top-level segment list and from a byte scan of the full decompressed image.
   - The decompressed Mach-O SHA-256 is `76e0da7892f11a1ff7265cf217306c1211434682a2f398f6bfd7a042d7611fd4` (`EVD-0012`, `VAL-0003`).
   - The same release kernelcache is byte-identical across the iPhone13,1, iPhone13,2/3, and iPhone13,4 images; all three IM4P copies hash to `15549697de8054b02321a224e3062861f46763256b28056d392b36b4bfbb6ced`, and all three decompressed Mach-O copies hash to `76e0da7892f11a1ff7265cf217306c1211434682a2f398f6bfd7a042d7611fd4` (`EVD-0017`, `VAL-0006`).
5. The installed SPTM and TXM payload files from the iPhone13,1 image link to the manifest at the byte level:
   - `Firmware/sptm.t8101.release.im4p` is 187,580 bytes with FourCC `sptm`, LZFSE compression, and no encryption flag. Its SHA-384 is `3d99f0041b42c5c5e70f97281533914231d0d1d2709a98f28117149c27523d0c388645e808dabd4597a532d4c090844f`, equal to the manifest's `Ap,SecurePageTableMonitor` Digest (`EVD-0018`, `VAL-0007`).
   - The SPTM payload decompresses to a 1,179,680-byte arm64e Mach-O with UUID `1693386C-1F3A-346B-906D-804E7138B2F1` and `LC_SOURCE_VERSION 820.0.22`; it contains `sptm.t8101.release` and embeds `SPTM-820.0.22|2026-08-08:13:24:32.076410|` (`EVD-0018`, `VAL-0007`).
   - `Firmware/txm.iphoneos.release.im4p` is 223,884 bytes with FourCC `trxm`, LZFSE compression, and no encryption flag. Its SHA-384 is `6b5c4cc10785a68743b80af7b5a7fc6846fef4fb12c197e85aa5709e199753c3a4e798c98ba5d3e938f974b40f28796f`, equal to the manifest's `Ap,TrustedExecutionMonitor` Digest (`EVD-0019`, `VAL-0007`).
   - The TXM payload decompresses to a 557,088-byte arm64e Mach-O with UUID `9F80F5EC-09C8-3E9F-A196-13A6250C04E0` and `LC_SOURCE_VERSION 217.0.2`; it contains `txm.iphoneos.release`, embeds `txm.iphoneos.release.TrustedExecutionMonitor_Guarded-217.0.2`, and has a `__TEXT_BOOT_EXEC` segment with a `__bootcode` section (`EVD-0019`, `VAL-0007`).
   - Neither payload has a top-level segment named `__PPLTEXT`, `__PPLDATA`, or `__PPLDATA_CONST`. The manifest's restore-specific `rspt`/`rtrx` entries carry different digests and were not resolved to wrapped payloads.
6. The 24A446 BuildManifest for iPhone13,4 (iPhone 12 Pro Max, A14/T8101) independently contains the same SPTM and TXM entries and the same `InstalledSPTM`/`RestoreSPTM` `Production` markers (`EVD-0014`, `VAL-0004`). The build-level finding is therefore not specific to iPhone13,1.
7. The combined 24A446 BuildManifest for iPhone13,2 (iPhone 12) and iPhone13,3 (iPhone 12 Pro) contains the same SPTM/TXM packaging and the same release payload digests (`EVD-0016`, `VAL-0005`). Across the iPhone13,1, iPhone13,2/3, and iPhone13,4 manifests, the installed/restore SPTM, release TXM, and release kernelcache digests are identical. The combined manifest also contains Research identities with a distinct research TXM payload; these are recorded separately and are not treated as the production configuration. Together the three manifests cover all four iPhone 12-family A14 product types.
8. Multiple secondary sources dated September 2026 independently report that iOS 27 introduces SPTM/TXM on A13/A14/M1:
   - The Apple Wiki states that with iOS 27.0 beta, SPTM bypasses apply to A13-A14 and M1 (`EVD-0006`).
   - A public SPTM introduction map places A13/A14 and M1 SPTM at Darwin/iOS 27.0 (`EVD-0007`).
   - A tooling evidence note says iOS 27 TXM detection treats A13/A14/M1 devices as TXM, except A12X (`EVD-0008`).
9. A contemporaneous survey still describes PPL on A12-A14/M1 and SPTM on A15+ (`EVD-0009`). A 2026-11-04 community tracker likewise frames A14/M1 as PPL and says A14+ needs an n-day SPTM bypass, but provides no build-specific measurement (`EVD-0015`). Both are retained as counter-evidence; they are consistent with Apple's older published page but do not account for the build manifests or kernelcache.
10. The primary Apple page carries a January 2026 date and contains no build-specific statement for 24A446; the guide's revision history does not list that page as updated after January 2026 (`EVD-0013`). The build artifacts are newer and target-specific, so they take precedence for the build-level question.

## Assessment

The build-level evidence resolves the contradiction: **the A14 / 24A446 images for all four iPhone 12-family product types package SPTM and TXM, mark installed SPTM as a production component, and share a byte-identical release kernelcache built with SPTM segments rather than PPL segments.** The same release SPTM, TXM, and kernelcache payload digests are referenced by the iPhone13,1, iPhone13,2/3, and iPhone13,4 manifests, and the release kernelcache bytes match across the images. For iPhone13,1, the extracted installed SPTM and TXM payload files themselves match the manifest digest fields and carry SPTM/TXM build identifiers, so the packaging claim is supported by the payload bytes and not only by manifest labels. The relevant page-table protection boundary for this build is therefore SPTM/TXM, not PPL. Apple's January 2026 table remains accurate for the OS versions it describes; it does not describe the iOS 27 A14 build.

**Current conclusion: inferred, high confidence at the build level.** The target device's runtime state remains `unknown`. The manifest's SPTM and TXM states are `inferred`; PPL remains `unknown` rather than being declared absent without a runtime measurement.

## What this establishes

- The 24A446 A14 builds for iPhone13,1, iPhone13,2, iPhone13,3, and iPhone13,4 contain SPTM (`sptm.t8101`) and TXM (`txm.iphoneos`) as installed/restore components, with matching release payload digests.
- The extracted iPhone13,1 installed SPTM and TXM payloads are valid Image4 containers whose SHA-384 values match the manifest digest fields; both decompress to arm64e Mach-O with SPTM/TXM build identifiers and no top-level PPL segment names.
- The 24A446 release kernelcache is byte-identical across all four product types and is structurally an SPTM build (`__DATA_SPTM`, `__TEXT_BOOT_EXEC`) with no PPL segment names.
- An "A14 PPL bypass" is mis-scoped for 24A446; the build-level boundary is SPTM/TXM.
- The public September 2026 reports are corroborated by Apple build artifacts.

## What this does not establish

- That the target device is an A14 device or is running 24A446.
- That SPTM/TXM is active, correctly configured, or enforcing on the exact target.
- That every boot path loads the monitors or that no fallback exists.
- That the extracted payloads are correctly signed or will be accepted by a device; no signature or trust evaluation was performed.
- That the restore-specific `rspt`/`rtrx` payload variants match the installed payloads; their manifest digests differ and they were not resolved.
- That the combined image's research kernelcache variant has the same structure as the release kernelcache.
- That any A14 iPad product type uses the same packaging.
- That any specific CVE or public bypass affects 24A446.
- Any bypass, exploit primitive, or protection-disablement method.

## Limitations

- No device was available for metadata or runtime observation.
- Build packaging, payload structure, and kernelcache structure are not runtime measurements.
- No code-signature or trust evaluation was performed; matching manifest digests link the extracted bytes to the manifest fields but do not establish device acceptance.
- The restore-specific `rspt`/`rtrx` entries carry different digests and were not resolved to wrapped payloads.
- Segment naming is a structural indicator, not proof that no PPL-related code exists in any component.
- The release kernelcache is byte-identical across all four product types; the combined image's research kernelcache variant was not compared.
- A14 iPad product types were not checked.
- No Apple source specific to 24A446 narrates the mechanism change; the finding is inferred from the build artifacts plus Apple's mechanism documentation.
- The supporting secondary sources are community/tooling reports; the contradictory Apple page carries a January 2026 date and is not listed as updated after that, and the contradictory survey and tracker may be imprecise.
- The A13/A14 grouping in public reports may hide device- or build-specific differences.

## Next steps

1. Verify product type, SoC, OS version, and build on the owned target device using non-invasive metadata.
2. If permitted non-invasive observation can establish SPTM/TXM presence, record it as a validation result; otherwise keep the runtime state `unknown`.
3. Look for an Apple security note or platform-security update specific to iOS 27.0.1 / 24A446.
4. Resolve the restore-specific `rspt`/`rtrx` payload variants if a restore-path question enters scope; they were not inspected.
5. If A14 iPad product types enter scope, extend the build-packaging and kernelcache-digest check beyond the iPhone 12 family.
6. Use `CASE-0003` for public bypass scope; keep bypass and exploitation work outside this repository.
