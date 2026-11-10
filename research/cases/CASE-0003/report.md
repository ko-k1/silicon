# Report - CASE-0003

## Status

Analyzed. Public-source survey only; no bypass was reproduced, tested, or adapted. The conclusion is an inference from the reviewed public record and the 24A446 build metadata.

## Question

What public PPL/SPTM bypass research claims A14 coverage, and does any of it apply to iOS 27.0.1 build 24A446?

## Findings

1. The reviewed public reporting places the Titan PPL/SPTM bypass at iOS 16.1 through 17.4 beta 3, with A14-A17 SoC coverage (`EVD-0009`). Stable Dopamine 3.0 support lists A14/M1 at iOS 16.6 through 17.3.1 (`EVD-0011`).
2. The reviewed reporting places momentarius at A12/A13, covering iOS 16.6 through 18.7.1 and 26.0 through 26.0.1 (`EVD-0011`). The Apple Wiki lists momentarius for iOS 27, but the reviewed text does not state A14 support for that entry (`EVD-0006`).
3. The 24A446 BuildManifest for iPhone13,1 contains `Ap,SecurePageTableMonitor` (`Firmware/sptm.t8101.release.im4p`) and `Ap,TrustedExecutionMonitor` (`Firmware/txm.iphoneos.release.im4p`). `VariantContents` marks `InstalledSPTM` and `RestoreSPTM` as `Production` (`EVD-0010`).
4. The 24A446 kernelcache for iPhone13,1 contains `__DATA_SPTM` and `__TEXT_BOOT_EXEC` segments and no `__PPLTEXT`/`__PPLDATA` segment names (`EVD-0012`).
5. The 24A446 BuildManifest for iPhone13,4, a second A14 product type, independently contains the same SPTM/TXM entries and `Production` markers (`EVD-0014`).
6. A 2026-11-04 community tracker still frames A14/M1 as PPL and says A14+ needs an n-day SPTM bypass, but it provides no build-specific measurement (`EVD-0015`). It is retained as counter-evidence.
7. No reviewed source demonstrates an A14-specific PPL or SPTM bypass on 24A446. This is an evidence gap in the reviewed set, not a proof of impossibility.
8. The 24A446 A14 image family is SPTM/TXM-based at the build level, so an "A14 PPL bypass" is mis-scoped for this build. Historical A14 PPL research remains relevant to earlier iOS versions.

## Assessment

The public record supports a narrow conclusion: **for the reviewed sources, the Dopamine 3.0 release lists stable A14/M1 support through iOS 17.3.1 (Titan's own claimed range extends to 17.4 beta 3), and the 24A446 A14 image family packages SPTM/TXM with an SPTM-structured kernel rather than a PPL-only configuration.** No reviewed source establishes A14 applicability on 24A446.

**Current conclusion: inferred, medium confidence.** The confidence is limited by the community-maintained public record, missing SoC-level detail in some entries, and the absence of runtime measurement.

## What this establishes

- A dated map of public bypass names and claimed compatibility ranges.
- A clear distinction between historical A14 PPL research and the 24A446 SPTM/TXM build.
- A documented evidence gap for A14 on 24A446.

## What this does not establish

- That no private or unreleased A14/24A446 bypass exists.
- That any named bypass works on A14 or on 24A446.
- That SPTM/TXM is active, correctly configured, or enforcing on the exact target device.
- That any CVE in the iOS 27 advisory is a bypass primitive.
- Any technique, offset, primitive, or operational step.

## Limitations

- The public record is incomplete and changes over time.
- The Apple Wiki iOS 27 entry lacks SoC detail in the reviewed revision.
- A community tracker still frames A14/M1 as PPL without a build-specific measurement; it is retained as counter-evidence.
- Compatibility ranges describe public tools, not the entire bypass landscape.
- The 24A446 evidence is build packaging, not a runtime measurement.
- The second A14 product type check covers packaging only.
- The target device identity and installed build remain unverified; `VAL-0001` is `not-run`.

## Next steps

1. Re-check public sources for A14-specific 24A446 claims and record their exact scope and date.
2. If an owned device is available, verify product type, SoC, OS build, and non-invasive protection indicators; keep unobserved states `unknown`.
3. Cross-link any new claim to `CASE-0001` (mechanism) and `CASE-0002` (vulnerability register) rather than merging conclusions.
4. Keep exploit reproduction, bypass tooling, and device modification out of scope.
