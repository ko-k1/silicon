# Differential analysis outputs

Derived JSON summaries for `CASE-0004` (iPhone13,1 iOS 27.0.1 `24A446` vs iOS 27.2 `24B119`). Inputs are public Apple restore images; raw IPSWs, extracted BuildManifests, Image4 payloads, and decompressed Mach-O files are not committed.

## Files

| File | Inputs | Contents |
|---|---|---|
| `ios27.2-vs-27.0.1-buildmanifest.json` | `BuildManifest.plist` from both IPSWs | Per-identity component comparison: 95 keys compared, 38 identical, 57 different, no additions or removals; full changed list with paths, digests, and flags |
| `ios27.2-vs-27.0.1-kernelcache.json` | `kernelcache.release.iphone13` from both IPSWs | IM4P and decompressed Mach-O hashes, build descriptions, fileset entry count, kext UUID comparison, unchanged kext names, function-start counts |
| `ios27.2-vs-27.0.1-sptm-txm.json` | `Firmware/sptm.t8101.release.im4p` and `Firmware/txm.iphoneos.release.im4p` from both IPSWs | IM4P and decompressed hashes, Mach-O UUIDs, source versions, and `__TEXT_EXEC` hashes |
| `ios27.2-vs-27.0.1-kernel-functions.json` | `com.apple.kernel` from both kernelcaches | Normalized function matching, 222 structural named changes, and triage candidates |
| `ios27.2-vs-27.0.1-ave2-ane-functions.json` | `AppleAVE2` and `AppleH11ANEInterface` from both kernelcaches | Kext versions, function counts, exact/shape matches, vtable slot comparison, and new classes |
| `ios27.2-vs-27.0.1-targeted-findings.json` | Extracted kernel and kext images plus symbolication and Ghidra output | Exception-port and thread-state entitlement changes, AVE2 validation routines, ANE vtable qualification, and VM structural follow-up |
| `ghidra/old-kernel/`, `ghidra/new-kernel/`, `ghidra/ave2-new/` | Extracted `com.apple.kernel` and `AppleAVE2` | Ghidra 12.3_DEV decompilation excerpts for the reviewed routines, with metadata sidecars |

The targeted-findings file was extended on 2026-11-12 with `thread_set_state_internal` and the `vm_map_remap`/`vm_object_update` follow-up (`EVD-0032`, `EVD-0033`, `VAL-0015`). Those entries record observed code changes; they do not map a function to a CVE.

## Input hashes

| Artifact | 24A446 | 24B119 |
|---|---|---|
| `BuildManifest.plist` SHA-256 | `f929ea00c7846fa2960d9b8bceeafcc0a93572daf3b595b1ce3cc9f481d3734f` | `2d13f3705cc346b8d282e2df5d53949c602cf9a6b24f1590e08d0124b6e431ec` |
| `kernelcache.release.iphone13` IM4P SHA-256 | `15549697de8054b02321a224e3062861f46763256b28056d392b36b4bfbb6ced` | `71b4bb5e110710fa9cfe504ce9f9c750f512004840d016f1978a3f9dece0349a` |
| `kernelcache` decompressed SHA-256 | `76e0da7892f11a1ff7265cf217306c1211434682a2f398f6bfd7a042d7611fd4` | `5edba8bacade83ea29c67cc1b3e44793694a93ef2473d78ce610237b553f0f41` |
| `sptm.t8101.release.im4p` SHA-256 | `fd020710ee88becc1b3da1e8156e73fe69aaa094166d3705f811040c237503bb` | `a239ab942984c8251a94cc3f1353bb8e5911bd1aa967c61229bcf7b06a685c76` |
| `txm.iphoneos.release.im4p` SHA-256 | `b81fb0c2db25d77055639bfdf8d1dc4610f31cde914f77d873e757c7405c65ff` | `284e5413dfd447dc81c8840e92748dc8a390b474142f390c1fddee1ac1c716b6` |

## Reproduce

```sh
python3 -m engineering.analyzers.build_manifest_diff <24A446 BuildManifest.plist> <24B119 BuildManifest.plist>
```

The kernelcache and SPTM/TXM summaries were produced with Python 3.14.9, `lzfse` 0.4.2.post1, `engineering.parsers.image4`, and `engineering.parsers.macho`. See `VAL-0010` and `VAL-0011` for the step-by-step checks.

## Limitations

- The JSON files record derived observations, not vulnerability findings.
- A digest, UUID, or function-start change does not establish a security fix.
- No device, runtime measurement, signature/trust evaluation, or decrypted system-volume inspection was performed.
