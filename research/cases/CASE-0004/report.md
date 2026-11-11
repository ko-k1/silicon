# Case report - CASE-0004

## Summary

The iOS 27.2 (24B119) iPhone13,1 restore image is a materially different build from iOS 27.0.1 (24A446). At the manifest level, 57 of 95 component entries differ and 38 are identical, with no keys added or removed. The release kernelcache changes from `KernelManagement_host-514.2.2` to `514.40.8`, its decompressed image grows by 278,528 bytes, and 207 of 250 embedded kext UUIDs change. SPTM changes from source version 820.0.22 to 820.40.24; TXM keeps source version 217.0.2 but has a different UUID and decompressed hash. Both 24B119 monitor payloads match the manifest's installed-component SHA-384 digests.

Apple's `APPLE-SA-149230` advisory for 27.2 lists **163 CVEs**, including **15 Kernel** and **26 WebKit** entries, and its CVE set is **disjoint** from the 163 CVEs in the iOS 27 advisory. Apple released 27.2.1 on 2026-11-09 with nine further CVEs, so 24B119 is not the latest patch level as of 2026-11-11.

This report establishes a reproducible differential baseline. It does **not** map a CVE to a changed function, demonstrate exploitability, or claim a PPL/SPTM/TXM bypass.

## Target scope

- Device family: iPhone 12 mini (`iPhone13,1`), A14 (T8101)
- Baseline build: iOS 27.0.1, `24A446`
- Comparison build: iOS 27.2, `24B119`
- Artifacts: local restore IPSWs and their extracted BuildManifest and unencrypted firmware payloads
- Device runtime: not measured; no device was connected

## Question and hypothesis

The question is what changed between the two builds and which advisory components are plausible candidates for function-level analysis. The hypothesis is that security-relevant payloads differ and that the 27.2 advisory introduces a disjoint CVE set, making the pair a usable patch-diff baseline. The hypothesis is supported at the packaging and payload-identity level; the vulnerability-attribution part remains open.

## Method

1. Extract `BuildManifest.plist`, `SystemVersion.plist`, `kernelcache.release.iphone13`, `Firmware/sptm.t8101.release.im4p`, and `Firmware/txm.iphoneos.release.im4p` from both IPSWs.
2. Compare BuildManifest component paths, 48-byte digests, and selected flags with `engineering.analyzers.build_manifest_diff`.
3. Parse each IM4P with `engineering.parsers.image4`, decompress the LZFSE payload, and parse the Mach-O with `engineering.parsers.macho`.
4. Inventory the kernelcache `MH_FILESET`, compare `LC_UUID` values for the 250 kext entries, and decode `LC_FUNCTION_STARTS`.
5. Parse the Apple CSAF JSON for 27.2 and compare its CVE set with the previously recorded 27.0 advisory JSON.
6. Triage advisory components against unencrypted artifacts by name and observed change, without asserting a fix.

## Evidence and provenance

| Record | Observation |
|---|---|
| `EVD-0021` | 27.2 IPSW and BuildManifest hashes; build 24B119, ProductVersion 27.2 |
| `EVD-0022` | 57/95 BuildManifest entries differ; 38 identical; 56 digest changes and one path-only change |
| `EVD-0023` | Kernelcache build 514.40.8; 66,813,952 decompressed bytes; 207/250 kext UUIDs changed; 1,382 function starts |
| `EVD-0024` | SPTM 820.40.24 and TXM 217.0.2 payload hashes/UUIDs; manifest SHA-384 matches |
| `EVD-0025` | 27.2 advisory: 163 CVEs, 162 A14 in-scope, 15 Kernel, 26 WebKit, zero overlap with 27.0 |
| `EVD-0026` | 27.2.1 advisory: nine additional CVEs, disjoint from 27.2 |

Derived summaries are committed under `analysis/differential/`. Raw IPSWs, manifests, and extracted payloads are not committed.

## Observations

### Build identity and manifest

- 27.2 BuildManifest: 351,370 bytes, SHA-256 `2d13f3705cc346b8d282e2df5d53949c602cf9a6b24f1590e08d0124b6e431ec`.
- 27.0.1 BuildManifest: 351,384 bytes, SHA-256 `f929ea00c7846fa2960d9b8bceeafcc0a93572daf3b595b1ce3cc9f481d3734f`.
- 57 of 95 component entries differ; 38 are identical; no keys were added or removed.
- Changed entries include `KernelCache`, `Ap,SecurePageTableMonitor`, `Ap,TrustedExecutionMonitor`, `Ap,RestoreSecurePageTableMonitor`, `Ap,RestoreTrustedExecutionMonitor`, `SEP`, `iBoot`, `LLB`, `iBEC`, `iBSS`, `DeviceTree`, the OS/Cryptex volumes, and their trust-cache entries.

### Kernelcache

| Property | 24A446 | 24B119 |
|---|---|---|
| IM4P description | `KernelManagement_host-514.2.2` | `KernelManagement_host-514.40.8` |
| IM4P SHA-256 | `15549697...bb6ced` | `71b4bb5e...e0349a` |
| Decompressed bytes | 66,535,424 | 66,813,952 |
| Decompressed SHA-256 | `76e0da78...d7611fd4` | `5edba8ba...553f0f41` |
| Fileset entries | 250 | 250 |
| Kext UUID changed | - | 207 |
| Kext UUID unchanged | - | 43 |
| Function starts | 1,361 | 1,382 |

The 43 unchanged kexts include `com.apple.security.Image4`, `com.apple.iokit.IOHIDFamily`, `com.apple.iokit.IOStorageFamily`, `com.apple.iokit.IOSurface`, and most USB families. Many device-specific drivers also remain unchanged. This selectivity shows the diff is not simply a whole-image rebuild artifact.

### SPTM and TXM

| Payload | 24A446 | 24B119 |
|---|---|---|
| SPTM source version | 820.0.22 | 820.40.24 |
| SPTM Mach-O UUID | `1693386C-1F3A-346B-906D-804E7138B2F1` | `88CA33DC-BE08-313D-AF19-397E47C76983` |
| SPTM decompressed SHA-256 | `e531396c...bad81a` | `90f710d8...2d25539` |
| TXM source version | 217.0.2 | 217.0.2 |
| TXM Mach-O UUID | `9F80F5EC-09C8-3E9F-A196-13A6250C04E0` | `1EB0EB97-F667-3470-97B9-1CD95D26246F` |
| TXM decompressed SHA-256 | `e0589318...fbf04` | `664ec04c...75461e` |

The 24B119 SPTM IM4P SHA-384 `e35342da...10cd` and TXM IM4P SHA-384 `d1f47d55...0f3b` match the 27.2 BuildManifest installed-component digest fields. The check links bytes to declarations; it does not verify signatures or device acceptance.

### Advisory comparison

| Advisory | Build context | CVEs | Kernel | WebKit | Overlap with 27.0 |
|---|---|---:|---:|---:|---:|
| `APPLE-SA-149034` (iOS 27) | 24A437 | 163 | 25 | not recorded here | baseline |
| 27.0.1 | 24A446 | 0 published | 0 | 0 | none |
| `APPLE-SA-149230` (iOS 27.2) | 24B119 | 163 | 15 | 26 | **0** |
| `APPLE-SA-149715` (iOS 27.2.1) | not verified | 9 | 0 | 0 | 0 with 27.2 |

The 27.2 advisory has 162 CVEs in the iPhone 11-and-later range and one limited to iPhone 15 Pro and later. The 15 Kernel CVEs are mostly use-after-free, out-of-bounds, type-confusion, race, and memory-integrity issues. None is labelled by Apple as a PPL/SPTM/TXM bypass.

## Initial component triage

This table is a **candidate map**, not an attribution. A changed kext is not proof that a named CVE was fixed there.

| Advisory component | CVEs | Candidate artifact | Observed in 24B119 | Triage note |
|---|---:|---|---|---|
| Kernel | 15 | `kernelcache.release.iphone13`, `com.apple.kernel` | Changed | Highest-priority target for normalized function diff; 1,361 -> 1,382 function starts. |
| AVEVideoEncoder | 6 | `com.apple.driver.AppleAVE2` | UUID changed | Strong name-level candidate; needs function-level confirmation. |
| Apple Neural Engine | 2 | `com.apple.driver.AppleH11ANEInterface` | UUID changed | Strong name-level candidate. |
| WebKit, WebKit Canvas, Process Model, JS Bindings, WebRTC | 32 | WebKit binaries in the App cryptex | Not inspected | Encrypted cryptex; no binary conclusion. |
| ImageIO | 11 | ImageIO in the system cryptex | Not inspected | Encrypted cryptex; no binary conclusion. |
| IOHIDFamily | 1 | `com.apple.iokit.IOHIDFamily` | UUID unchanged | Do not map by name alone; fix may be in the kernel proper or userspace. |
| IOStorageFamily | 1 | `com.apple.iokit.IOStorageFamily` | UUID unchanged | Same caution. |
| IOSurface | 1 | `com.apple.iokit.IOSurface` | UUID unchanged | Same caution. |
| IOMobileFrameBuffer | 1 | No separate fileset entry observed | Kernel changed | Do not infer a specific location. |
| Security | 2 | `com.apple.security.sandbox`, `AppleImage4`, `Image4` | sandbox and AppleImage4 changed; Image4 unchanged | Ambiguous; requires function-level work. |
| USB | 1 | USB kext families | Unchanged | Fix may be elsewhere; no mapping. |
| Power Management | 1 | `AppleT8101PMGR`, `AppleT8101CLPCv3` | Changed | Many power-related changes; no CVE-level attribution. |

## Counter-evidence and alternative explanations

- 27.2 is a feature release; many binary changes are unrelated to security fixes.
- A digest change can reflect a version string, layout change, or non-security bug fix.
- An `LC_UUID` change does not prove a code change; a normalized instruction-level diff is still required.
- Advisory membership is not proof that 24A446 was vulnerable or that 24B119 fixes the issue on A14.
- An unchanged kext does not prove the named component is unaffected; the fix may be in the kernel proper or another image.
- The 27.2 advisory was published 2026-10-26; Apple may revise it. The CSAF SHA-256 is recorded so a revision is detectable.

## Result

The differential baseline is **observed** with high confidence for the narrow build-level claims. Vulnerability attribution is **not established**. The case remains `investigating`.

## Impact assessment

No vulnerability, exploitability, or protection-bypass impact is claimed. The practical value is a prioritized, reproducible target list: the kernel proper and the AVE/ANE kexts are the most accessible unencrypted candidates; WebKit and ImageIO require a different acquisition path.

## Reproducibility and limitations

- Validation records: `VAL-0009` (BuildManifest diff), `VAL-0010` (kernelcache inventory), `VAL-0011` (SPTM/TXM).
- Derived JSON: `analysis/differential/ios27.2-vs-27.0.1-buildmanifest.json`, `...-kernelcache.json`, `...-sptm-txm.json`.
- No device, no runtime measurement, no signature/trust evaluation.
- Kernel is stripped; no symbol-level or source-level attribution.
- Encrypted system-volume cryptexes were not inspected.
- Only iPhone13,1 customer restore identity was compared.
- 24B119 predates the nine 27.2.1 fixes.
- Raw artifacts are not committed; hashes identify the inputs.

## Disclosure status

No new vulnerability is claimed. All inputs are public Apple restore images and public security advisories. No disclosure is required at this stage. If function-level analysis later identifies a plausible unfixed issue, follow `docs/workflow/validation-policy.md` and the repository disclosure process before publishing.

## References

- `SRC-0003` - Apple security content of iOS 27 / iPadOS 27
- `SRC-0004` - Apple security releases index
- `SRC-0020` - Apple security content of iOS 27.2 / iPadOS 27.2
- `SRC-0021` - Apple security content of iOS 27.2.1 / iPadOS 27.2.1
- `EVD-0021` through `EVD-0026`
- `VAL-0009` through `VAL-0011`
