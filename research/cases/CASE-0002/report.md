# Report - CASE-0002

## Status

Analyzed. The register is derived from Apple's public CSAF advisory; no device testing or exploit validation was performed.

## Findings

- Apple's iOS 27 / iPadOS 27 advisory (`APPLE-SA-149034`) contains **163 CVEs**.
- **161** are in the iPhone 11-and-later range that includes A14-based iPhone 12 models; **2** are limited to iPhone 15 Pro and later.
- **25** entries are titled `Kernel`; **30** have a kernel-related impact or category.
- **10** entries are sandbox-related; **7** have a privilege-escalation-related category.
- **0** entries explicitly name PPL, SPTM, TXM, page tables, code signing, or trust cache. Apple does not label any iOS 27 CVE in this advisory as a page-table-monitor bypass.
- Apple's security-releases index states that **iOS 27.0.1 / iPadOS 27.0.1 (24A446) has no published CVE entries**.
- Build context: the 24A446 A14 image packages SPTM/TXM and has an SPTM-structured kernelcache (`EVD-0010`, `EVD-0012`, `VAL-0002`, `VAL-0003`); see `CASE-0001`. This register does not map any CVE to a PPL/SPTM/TXM bypass; it records vulnerability metadata only.

Full data: `research/public-research/ios27-vulnerability-register.yaml`
Summary tables: `research/public-research/ios27-vulnerability-register.md`

## Kernel component highlights

| CVE | Impact | A14 scope |
|---|---|---|
| `CVE-2026-86916` | An app may execute arbitrary code with kernel privileges (use-after-free) | in-scope |
| `CVE-2026-43689` | A malicious app may gain root privileges | in-scope |
| `CVE-2026-28968` | An app may cause system termination or corrupt kernel memory (out-of-bounds write) | in-scope |
| `CVE-2026-84561` | An app may cause system termination or corrupt kernel memory (double free) | in-scope |
| `CVE-2026-84566` | A local attacker may cause system termination or corrupt kernel memory | in-scope |
| `CVE-2026-65415` | A local user may cause system termination or read kernel memory (race) | in-scope |
| `CVE-2026-65398` | IOMobileFrameBuffer: system termination or kernel memory corruption | in-scope |

These are vulnerability descriptions, not proof of exploitability on 24A446 and not proof of a PPL/SPTM/TXM bypass.

## What this establishes

- A reproducible public baseline for iOS 27 vulnerabilities that Apple lists for the A14 device range.
- A clear distinction between vulnerability presence, component scope, and protection-mechanism bypass.
- The observation that 27.0.1 has no published CVE entries, while the earlier 27.0 advisory has substantial security content.

## What this does not establish

- That any listed CVE is exploitable on an A14 device running 24A446.
- That any CVE defeats PPL, SPTM, or TXM.
- That 27.0.1 contains no security-relevant changes simply because Apple published no CVEs.
- Anything about the runtime protection state of the target.

## Limitations

- The advisory covers iOS 27, not build 24A446 specifically.
- A14 scope comes from Apple's device-range wording, not per-build testing.
- Counts and categories are derived from component titles and note text.
- The register is a snapshot; Apple may revise the advisory.

## Next steps

1. Re-verify the artifact hash and counts if Apple updates the advisory.
2. Cross-check any CVE of interest against public research and Apple's build-specific notes before calling it a protection-bypass candidate.
3. Keep exploitability and weaponization work out of scope.
