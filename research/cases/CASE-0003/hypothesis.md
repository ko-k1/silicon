# Hypothesis - CASE-0003

## Question

What public PPL/SPTM bypass research claims A14 coverage, and does any of it apply to iOS 27.0.1 build 24A446?

This case catalogs public claims by name, date, iOS range, and SoC range. It does not reproduce exploit code, offsets, primitives, or operational steps.

## Claim

The reviewed Dopamine 3.0 release lists stable A14/M1 support at iOS 16.6 through 17.3.1, and Titan's own claimed range extends to 17.4 beta 3. No reviewed source demonstrates an A14 bypass on iOS 27.0.1 build 24A446. The 24A446 A14 images are SPTM/TXM-based, so an A14 PPL bypass is not the correct boundary for that build.

## Target and preconditions

- Target manifest: `targets/manifests/iphone12mini-ios27.0.1.yaml`
- Target: A14 / iPhone 12 mini / iOS 27.0.1, build 24A446
- Build evidence: `EVD-0010`, `EVD-0014`, and `EVD-0016` show SPTM and TXM payloads in the 24A446 restore images for the four iPhone 12-family A14 product types
- Precondition: public compatibility ranges are treated as claims, not as target measurements
- Precondition: missing A14/24A446 coverage is an evidence gap, not proof that no bypass exists

## Public research map

| Name | Claimed iOS range | Claimed SoC scope | Relevance to A14 / 24A446 | Evidence |
|---|---|---|---|---|
| Titan | iOS 16.1-17.4 beta 3 (survey); 16.5.1-17.3.1 (Dopamine stable) | A14-A17 | Historical A14 coverage; does not cover 24A446 | `EVD-0009`, `EVD-0011` |
| momentarius | iOS 16.6-18.7.1 and 26.0-26.0.1 | A12/A13 | Not A14 in the reviewed tool reporting | `EVD-0011` |
| momentarius entry on Apple Wiki | iOS 27 list | Not stated in the reviewed text | The wiki does not establish A14 support for this entry | `EVD-0006` |
| Rocket | iOS 16 and 17 lists | Not stated in the reviewed text | Predecessor cited by Titan; historical, not 24A446 | `EVD-0006`, `EVD-0009` |
| sparrow | iOS 17 list | Not stated in the reviewed text | Insufficient scope detail for A14/24A446 | `EVD-0006` |
| gallium, tlbFail, dmaFail, quark | iOS 12-16 lists | Mostly pre-A14 or not A14-specific | Historical context only | `EVD-0006` |

The table is a scope summary, not a compatibility guarantee. A name appearing in a version list does not prove support for every SoC that can run that version.

## Why the target frame changed

Apple's 2026-01-28 Operating system integrity page places A12-A14 in the PPL column (`EVD-0002`, `EVD-0003`); the guide's revision history does not list that page as updated after January 2026 (`EVD-0013`). The 24A446 BuildManifest for iPhone13,1 contains:

- `Ap,SecurePageTableMonitor` -> `Firmware/sptm.t8101.release.im4p`
- `Ap,TrustedExecutionMonitor` -> `Firmware/txm.iphoneos.release.im4p`
- `InstalledSPTM` and `RestoreSPTM` marked `Production` in `VariantContents`

The decompressed release kernelcache independently contains `__DATA_SPTM` and `__TEXT_BOOT_EXEC` segments and no `__PPLTEXT`/`__PPLDATA` segment names (`EVD-0012`). The 24A446 BuildManifest for iPhone13,4, a second A14 product type, independently contains the same SPTM/TXM entries and `Production` markers (`EVD-0014`), and the combined iPhone13,2/iPhone13,3 manifest does too, with matching release payload digests (`EVD-0016`, `VAL-0005`). The release kernelcache is byte-identical across the iPhone13,1, iPhone13,2/3, and iPhone13,4 images (`EVD-0017`, `VAL-0006`). For iPhone13,1, the extracted installed SPTM/TXM payloads match the manifest digest fields and decompress to arm64e Mach-O with SPTM/TXM identifiers (`EVD-0018`, `EVD-0019`, `VAL-0007`), and the restore-role `rspt`/`rtrx` digests are fourcc-only retags of the same payloads (`EVD-0020`, `VAL-0008`). This is build-level evidence that the A14 24A446 image family, across all four iPhone 12-family product types, ships the SPTM/TXM mechanism family. It does not measure runtime enforcement.

## Expected behavior

If the claim is correct:

- The reviewed Dopamine 3.0 summary should show A14 support ending at iOS 17.3.1.
- iOS 27 entries should be limited to other SoCs or omit A14 support.
- The 24A446 A14 build should contain SPTM/TXM payloads.

If the claim is wrong:

- A public source should demonstrate an A14 bypass on 24A446.
- Or the 24A446 A14 build should be shown to use PPL rather than SPTM/TXM.

## Supporting evidence

- `EVD-0006` - Apple Wiki reports SPTM applicability expanding to A13-A14/M1 with iOS 27.0 beta and lists momentarius for iOS 27, without A14 detail in the reviewed text.
- `EVD-0009` - Survey describes Titan as a PPL/SPTM bypass for iOS 16.1 through 17.4 beta 3 on A14-A17.
- `EVD-0010` - 24A446 BuildManifest for iPhone13,1 contains SPTM/TXM payloads.
- `EVD-0011` - Dopamine 3.0 reporting places A14/M1 stable public support at iOS 16.6-17.3.1 and momentarius at A12/A13.
- `EVD-0012` - The 24A446 kernelcache is structurally an SPTM build (`__DATA_SPTM`, `__TEXT_BOOT_EXEC`) with no PPL segment names.
- `EVD-0014` - The 24A446 BuildManifest for iPhone13,4 also contains SPTM/TXM payloads and `Production` markers.
- `EVD-0016` - The combined 24A446 BuildManifest for iPhone13,2/iPhone13,3 contains the same packaging and release payload digests, covering the remaining iPhone 12-family A14 product types.
- `EVD-0017` - The release kernelcache is byte-identical across all four product types, so the SPTM segment finding applies to the same payload in each image.
- `EVD-0018` - The extracted iPhone13,1 SPTM payload matches the manifest's installed digest and is an arm64e Mach-O with SPTM identifiers.
- `EVD-0019` - The extracted iPhone13,1 TXM payload matches the manifest's installed digest and is an arm64e Mach-O with TXM identifiers.
- `EVD-0020` - The restore-role `rspt`/`rtrx` digests match fourcc-only retags of the same SPTM/TXM IM4P payloads, so the restore entries do not indicate a different payload body.

## Counter-evidence and alternatives

- `EVD-0015` - A 2026-11-04 community tracker still frames A14/M1 as PPL and says A14+ needs an n-day SPTM bypass, but provides no build-specific measurement; it is retained as counter-evidence.
- Alternative explanation: a public tool may support A14 on a newer iOS without a public write-up. The reviewed compatibility range would then be incomplete.
- Alternative explanation: the Apple Wiki's iOS 27 momentarius entry may include A14 even though the reviewed text does not say so.
- Alternative explanation: the 24A446 image may package SPTM/TXM while still retaining a PPL fallback for some boot path; build packaging does not settle runtime behavior.

## Rejection criteria

- A public source demonstrates an A14-specific PPL or SPTM bypass on 24A446.
- A build-specific source shows the 24A446 A14 image is PPL-based and does not use SPTM/TXM.
- The cited A14 compatibility range is shown to extend beyond iOS 17.3.x on a public tool.

## Safe validation plan

1. Re-check the cited source dates and exact compatibility wording.
2. Compare any new A14/24A446 claim with the build manifests for more than one A14 product type and, if available, a non-invasive device measurement.
3. Do not run, reproduce, or adapt any bypass; do not modify a device.
4. Keep the conclusion scoped to the reviewed public record and keep the evidence gap explicit.

## Research boundary

This case catalogs public bypass research at the level of source, date, claimed scope, and disclosure status. It does not contain exploit code, kernel read/write primitives, patch offsets, bypass steps, persistence, or protection-disablement procedures.
