# Hypothesis - CASE-0004

## Question

What changed between iOS 27.0.1 (24A446) and iOS 27.2 (24B119) for the iPhone13,1 A14 restore image, and which 27.2 advisory components are plausible candidates for binary-level vulnerability-fix analysis?

## Claim

The 24B119 image packages different security-relevant components than 24A446, and the 27.2 advisory's 163 CVEs are disjoint from the 163 CVEs in the 27.0 advisory. The build pair is therefore a usable offline patch-diff baseline for locating fixed vulnerabilities. This claim does not assert that any CVE is reachable, exploitable, or a protection-mechanism bypass.

## Target and preconditions

- Target manifest: `targets/manifests/iphone12mini-ios27.0.1.yaml`
- Comparison builds: iOS 27.0.1 (24A446) and iOS 27.2 (24B119), iPhone13,1
- Required artifacts: complete restore IPSWs, their BuildManifest.plist files, and the unencrypted firmware payloads used here
- Known limitations: no device; stripped kernel; encrypted system-volume cryptexes not inspected; advisory metadata is not exploitability evidence

## Expected behavior

If the claim is correct:

- Security-relevant BuildManifest entries such as `KernelCache`, `Ap,SecurePageTableMonitor`, `Ap,TrustedExecutionMonitor`, and `SEP` should have different payload digests.
- Some embedded images should remain identical, showing that the diff is selective rather than a blanket rebuild artifact.
- The 27.2 advisory should introduce a CVE set distinct from the 27.0 advisory, and should contain kernel and WebKit entries.
- A component whose candidate kext is unchanged should not be mapped to that kext without further evidence.

## Supporting evidence

- `EVD-0021` - 27.2 IPSW and BuildManifest identity.
- `EVD-0022` - 57 of 95 BuildManifest entries differ; 38 are identical.
- `EVD-0023` - 24B119 kernelcache is a different build; 207 of 250 kext UUIDs differ, 43 are unchanged.
- `EVD-0024` - SPTM and TXM payloads differ; SPTM source version changes from 820.0.22 to 820.40.24.
- `EVD-0025` - 27.2 advisory has 163 CVEs, disjoint from the 27.0 set, with 15 Kernel entries.
- `EVD-0026` - 27.2.1 adds nine CVEs; the 24B119 image is not the latest patch level.

## Counter-evidence and alternatives

- No contradictory source was found for the build identities or hashes.
- Alternative explanation: 27.2 is a feature release, so many binary differences are unrelated to security fixes. The manifest diff cannot separate feature work from security work.
- Alternative explanation: an LC_UUID change can result from metadata or layout changes, not necessarily a security-relevant code change.
- Alternative explanation: advisory CVE membership is not proof that 24A446 was vulnerable; Apple may have backported fixes or the issue may not be reachable on A14.
- Alternative explanation: the absence of a changed kext for a named component may mean the fix is in the kernel proper, in another image, or in userspace, not that the component was unaffected.

## Rejection criteria

- The two BuildManifests declare identical security-relevant payloads.
- The decompressed kernelcache, SPTM, and TXM payloads are byte-identical.
- The 27.2 advisory reuses the 27.0 CVE set rather than introducing a disjoint set.
- The observed differences are fully explained by metadata or packaging changes with no payload-byte changes.

## Safe validation plan

1. Verify the two restore-image hashes and extract the BuildManifests.
2. Re-run the deterministic BuildManifest diff.
3. Extract and decompress the kernelcache, SPTM, and TXM payloads; verify the recorded hashes, Mach-O headers, fileset entries, and UUIDs.
4. Re-parse the Apple CSAF JSON and verify the 163-CVE count and zero overlap with the 27.0 JSON.
5. Do not attempt to reproduce any CVE, exploit, or bypass on a device.
