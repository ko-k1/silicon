# Page-table protection: PPL vs SPTM

## Scope

These notes compare Apple's published platform-security model with build-level evidence for the A14 / iOS 27.0.1 (24A446) target. They describe documented applicability and packaged components. They do not establish runtime protection state for a specific device.

Two evidence layers matter:

1. **Apple platform documentation** published 2026-01-28 (`SRC-0001`, `EVD-0002`, `EVD-0003`).
2. **The target build artifacts**: the 24A446 BuildManifests for iPhone13,1 and iPhone13,4 (`SRC-0010`, `SRC-0014`, `EVD-0010`, `EVD-0014`, `VAL-0002`, `VAL-0004`).

The first carries a 2026-01-28 published date and was not listed as updated after January 2026 in the guide's revision history (`EVD-0013`). The second is build-specific. When they conflict, the build artifact is stronger evidence for what the build contains; neither is a runtime measurement.

## Documented applicability (Apple, 2026-01-28)

| SoC generation | PPL | SPTM |
|---|---|---|
| A10 | not listed | not listed |
| A11, S3 | documented | not listed |
| A12-A14, S4-S10 | documented | not listed |
| A15-A18 | replaced by SPTM | documented |
| M1 | documented | not listed |
| M2-M4 | replaced by SPTM | documented |
| A19, M5 | replaced by SPTM | documented |

Apple states that SPTM is supported on A15 or later and M2 or later SoCs and replaces PPL on supported platforms. The same guide places A12-A14 in the PPL column. This is the vendor's published model, not a statement about the 24A446 build.

## Build-level evidence for 24A446

The iOS 27.0.1 (24A446) restore BuildManifest for iPhone13,1 (`T8101`, A14) contains:

- `Ap,SecurePageTableMonitor` -> `Firmware/sptm.t8101.release.im4p`
- `Ap,TrustedExecutionMonitor` -> `Firmware/txm.iphoneos.release.im4p`
- `Ap,RestoreSecurePageTableMonitor` and `Ap,RestoreTrustedExecutionMonitor`, both marked `IsLoadedByiBoot: true`
- `InstalledSPTM`, `RestoreSPTM`, `InstalledKernelCache`, and `RestoreKernelCache` marked `Production` in `VariantContents`

The BuildManifest SHA-256 is `f929ea00c7846fa2960d9b8bceeafcc0a93572daf3b595b1ce3cc9f481d3734f` (`EVD-0010`). The raw IPSW and BuildManifest are not committed.

The 24A446 BuildManifest for iPhone13,4 (iPhone 12 Pro Max, also A14/T8101) independently contains the same SPTM and TXM entries and the same `InstalledSPTM`/`RestoreSPTM` `Production` markers. Its BuildManifest SHA-256 is `342b8ea26ca5a940efd867ddc807d7cd9212554579f1a063d219b13ebf5d0392` (`EVD-0014`, `VAL-0004`).

The combined 24A446 BuildManifest for iPhone13,2 (iPhone 12) and iPhone13,3 (iPhone 12 Pro) contains the same SPTM and TXM entries and the same `InstalledSPTM`/`RestoreSPTM` `Production` markers for its customer identities. Its BuildManifest SHA-256 is `51827a7ebd3b9130d03acf200e269ba66768fa42e1569b246b053a1c22c29364` (`EVD-0016`, `VAL-0005`). Across the iPhone13,1, iPhone13,2/3, and iPhone13,4 manifests, the installed/restore SPTM, release TXM, and release kernelcache digests match. The combined manifest's Research identities reference a distinct `txm.iphoneos.research.im4p` and research kernelcache; those are recorded separately and are not treated as the production configuration. The three manifests cover all four iPhone 12-family A14 product types, so the build-level finding is not specific to iPhone13,1.

The decompressed 24A446 release kernelcache independently shows the same build structure:

- Top-level Mach-O segments include `__DATA_SPTM` and `__TEXT_BOOT_EXEC`.
- `__PPLTEXT`, `__PPLDATA`, and `__PPLDATA_CONST` are absent from the top-level segment list and from a byte scan of the full decompressed image.
- The decompressed Mach-O SHA-256 is `76e0da7892f11a1ff7265cf217306c1211434682a2f398f6bfd7a042d7611fd4` (`EVD-0012`, `VAL-0003`).
- The release kernelcache is byte-identical across the iPhone13,1, iPhone13,2/3, and iPhone13,4 images; all three IM4P copies hash to `15549697de8054b02321a224e3062861f46763256b28056d392b36b4bfbb6ced` (`EVD-0017`, `VAL-0006`).

This is primary evidence that the build packages SPTM/TXM and that its kernel is built with SPTM structure. It is not a runtime measurement.

## Secondary reports about iOS 27

Multiple public sources dated September 2026 report that iOS 27 moves A13/A14/M1 devices into the SPTM/TXM family:

- The Apple Wiki states that with iOS 27.0 beta, SPTM bypasses apply to A13-A14 and M1 (`EVD-0006`).
- A public SPTM introduction map places A13/A14 and M1 SPTM at Darwin/iOS 27.0 (`EVD-0007`).
- A tooling evidence note reports that iOS 27 TXM detection treats A13/A14/M1 devices as TXM, except A12X (`EVD-0008`).

A September 2026 survey still repeats the older PPL-on-A12-A14/M1 model (`EVD-0009`), and a 2026-11-04 community tracker still frames A14/M1 as PPL while saying A14+ needs an n-day SPTM bypass (`EVD-0015`). Both are retained as counter-evidence, but neither provides a build-specific A14/24A446 measurement; they are consistent with Apple's older documentation rather than with the 24A446 build artifacts.

## Mechanism notes

- **PPL** prevents user-space code from being modified after code-signature verification. It manages page-table permission overrides so that only PPL can alter protected pages containing user code and page tables. It builds on Kernel Integrity Protection and Fast Permission Restrictions.
- **SPTM** works with **TXM** to protect page tables for user and kernel processes, including against an attacker with kernel write capability. SPTM uses a privilege level higher than the kernel; TXM enforces code-execution policy at a lower privilege. Apple states that a TXM compromise is not intended to automatically yield an SPTM bypass.
- **TXM** is packaged with SPTM in the 24A446 A14 builds. Its runtime policy and configuration on the target are not established by the build manifests.

## Implication for A14 / 24A446

For the 24A446 A14 target, the build-level boundary is **SPTM/TXM**, not PPL, across all four iPhone 12-family product types. An "A14 PPL bypass" is therefore mis-scoped for this build. PPL remains relevant as the historical A14 mechanism for earlier iOS versions and as the subject of earlier public research.

This does not establish that SPTM/TXM is enabled, correctly configured, or enforcing on a particular device. It also does not establish that no PPL code or fallback exists; it establishes that the checked A14 builds package SPTM/TXM as production components and share a byte-identical SPTM-structured release kernelcache.

## Build 24A446

Apple's release listing confirms iOS 27.0.1 build 24A446 was released on 2026-09-28 (`SRC-0002`, `EVD-0001`). The build manifests for iPhone13,1, iPhone13,2/3, and iPhone13,4 confirm the SPTM/TXM payloads (`EVD-0010`, `EVD-0014`, `EVD-0016`), and the byte-identical release kernelcache confirms an SPTM-structured kernel (`EVD-0012`, `EVD-0017`) packaged for all four product types. No build-specific Apple security note describing the mechanism change was found in the reviewed material. The Operating system integrity page carries a January 2026 date, was not listed as updated after that in the guide's revision history (`EVD-0013`), and does not describe the 24A446 build contents.

## Open questions

1. Does the installed OS load SPTM/TXM on every boot path, or is there a fallback configuration?
2. How is TXM policy configured on the exact target build?
3. Is there a build-specific Apple security note or platform-security update for 24A446?
4. Can SPTM/TXM runtime state be established on an owned A14 device through permitted, non-invasive observation?
5. Does the target device actually match the manifest's A14 / iPhone 12 mini / 24A446 assumptions?
6. Do A14 iPad product types or regional builds package the same SPTM/TXM components?

## Boundaries

These notes support applicability analysis and evidence planning. They do not contain exploit chains, kernel read/write primitives, bypass techniques, persistence, or protection-disablement procedures. Runtime validation must remain non-invasive and within the repository's safety rules.
