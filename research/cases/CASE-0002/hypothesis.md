# Hypothesis - CASE-0002

## Question

What does Apple's public vulnerability data establish about iOS 27 and iOS 27.0.1 for an A14 target, and what does it not establish?

## Claim

Apple's public iOS 27 advisory can be represented as a 163-CVE register. Of those, 161 are in the iPhone 11-and-later range that includes A14 devices, and 25 are in the `Kernel` component. iOS 27.0.1 build 24A446 has no published CVE entries.

## Target and preconditions

- Target manifest: `targets/manifests/iphone12mini-ios27.0.1.yaml`
- Target build: iOS 27.0.1, 24A446
- Advisory scope: iOS 27 / iPadOS 27, released 2026-09-14, last updated 2026-10-26
- Precondition: the advisory JSON matches the recorded SHA-256 and the scope rule treats "iPhone 11 and later" as including A14 iPhone 12 models

## Expected behavior

Re-parsing the recorded advisory JSON with the documented rules should reproduce the same totals and A14 scope counts. Apple's security-releases index should continue to show no published CVE entries for 27.0.1.

## Supporting evidence

- `EVD-0004` - Apple's security-releases index states iOS 27.0.1 has no published CVE entries.
- `EVD-0005` - Derived counts from Apple's CSAF advisory: 163 total, 25 Kernel, 0 mechanism-level PPL/SPTM/TXM labels.

## Counter-evidence and alternatives

- No contradictory source was found at the time of review.
- Alternative explanation: Apple could revise the advisory after the recorded date. The artifact hash and update date are recorded so a future revision is detectable.
- Alternative explanation: "iPhone 11 and later" is a device-family statement, not proof that every CVE is reachable on A14. The register therefore records scope, not exploitability.

## Rejection criteria

- Apple revises the advisory and the recorded counts no longer match the identified artifact.
- The scope rule incorrectly includes or excludes A14 devices.
- The 27.0.1 entry is replaced with one containing published CVE detail.

## Safe validation plan

1. Re-download the advisory JSON and verify the SHA-256.
2. Re-run the documented parsing and scope rules.
3. Compare totals, component counts, and A14 scope counts.
4. Do not attempt to reproduce any CVE, exploit, or bypass on a device.
