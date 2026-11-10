# silicon

**A reproducible Apple-platform security research workspace.**

Initial research target: **A14 / iOS 27.0.1 (24A446)**. The repository is designed to keep target facts, public research, hypotheses, evidence, analysis artifacts, and validation results separate and traceable.

> Research status: foundation only. No vulnerability or protection-bypass claim is made by this repository. Target-specific runtime protection state remains `unknown` until supported by evidence collected from the exact device and build.
>
> Build-level finding: the iOS 27.0.1 (24A446) restore image for iPhone13,1 contains SPTM (`sptm.t8101`) and TXM (`txm.iphoneos`) payloads and marks installed/restore SPTM as `Production` (`EVD-0010`). The decompressed kernelcache independently has `__DATA_SPTM`/`__TEXT_BOOT_EXEC` segments and no PPL segment names (`EVD-0012`). The iPhone13,4 BuildManifest shows the same SPTM/TXM packaging (`EVD-0014`), and the combined iPhone13,2/iPhone13,3 BuildManifest does too, with matching release payload digests (`EVD-0016`). The release kernelcache is byte-identical across all four product types (`EVD-0017`). The extracted iPhone13,1 SPTM and TXM payloads themselves have SHA-384 values matching the manifest's installed-component digests and decompress to arm64e Mach-O with SPTM/TXM identifiers (`EVD-0018`, `EVD-0019`). Together these cover all four iPhone 12-family A14 product types. The A14 target build is therefore SPTM/TXM-based. Apple's 2026-01-28 page, which places A12-A14 in the PPL scope, was not listed as updated after January 2026 in the guide's revision history (`EVD-0013`) and does not describe this build. A community tracker still frames A14/M1 as PPL but provides no build-specific measurement (`EVD-0015`). See `research/cases/CASE-0001/`.

## Project principles

- Evidence before conclusions: distinguish observations, inferences, and hypotheses.
- Exact target identity: record SoC, product type, OS version, build, and artifact hashes together.
- Reproducibility: every result records its environment, inputs, tool versions, and limitations.
- Falsifiability: record counter-evidence and explicit rejection criteria, not only supporting observations.
- Separation of concerns: research records are not implementation code; analysis tools do not silently modify source artifacts.
- Safe validation: this foundation is for public-source research, offline analysis, synthetic models, and non-invasive observation. It does not provide exploit chains, privilege-escalation payloads, or instructions to disable platform protections.

## Start here

1. Read [VISION.md](VISION.md), [AGENTS.md](AGENTS.md), and [ROADMAP.md](ROADMAP.md).
2. Review `targets/manifests/iphone12mini-ios27.0.1.yaml`. Values not directly verified are deliberately marked `unknown`, `pending`, `inferred`, or `user-specified` with their evidence links.
3. Read `docs/research/methodology.md` and `docs/research/evidence-model.md` before opening a research case.
4. Review `research/cases/CASE-0001/` for the A14 PPL/SPTM applicability question, `CASE-0002/` and `research/public-research/ios27-vulnerability-register.yaml` for the iOS 27 vulnerability baseline, and `CASE-0003/` for public bypass scope.
5. Read `reports/technical/A14-iOS-27.0.1-baseline.md` for the consolidated baseline and its evidence map.
6. Copy `research/cases/_template/` to a new case ID only after defining a falsifiable question; do not edit the template in place.
7. Store bulky or sensitive raw artifacts outside Git. Commit metadata, hashes, provenance, and sanitized summaries instead.

## Repository map

| Path | Responsibility |
|---|---|
| `targets/` | Target manifests and reusable platform profiles |
| `research/` | Public research references, vulnerability candidates, and case records |
| `analysis/` | Architecture notes, artifact metadata, and static/differential analysis outputs |
| `engineering/` | Research-support tooling and its interfaces |
| `validation/` | Synthetic fixtures, validation models, test definitions, and result metadata |
| `lab/` | Host/device inventory and safe collection procedures |
| `reports/` | Technical findings and disclosure records |
| `tests/` | Quality tests for repository tooling and schemas |
| `schemas/` | Machine-readable schemas for records in this repository |

## Initial scope

The first milestone is to establish a trustworthy baseline for the requested A14 / iOS 27.0.1 target and document the relevant protection architecture. The 24A446 A14 build is SPTM/TXM-based at the packaging level; PPL is the historical A14 boundary for earlier iOS versions. Do not infer runtime state from a SoC family, OS version, build packaging, third-party summary, or a result from a different device.

## Status vocabulary

Use `unknown` when a property has not been established. Use `observed` for a directly recorded result, `inferred` for a reasoned interpretation, and `confirmed` only when the evidence and method justify that level of confidence. See `docs/research/evidence-model.md`.

## Licensing

No license is assigned in this foundation. Add one only after deciding how the repository and any future contributions should be licensed. Third-party references and artifacts retain their own licenses and terms.
