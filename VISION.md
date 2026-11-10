# VISION

## Purpose

`silicon` is a structured research workspace for understanding Apple-platform security mechanisms and evaluating security-relevant behavior with reproducible evidence.

The initial study focuses on the A14 / iOS 27.0.1 (24A446) environment and the boundary between kernel execution, page-table protection, code-execution policy, and related trust domains. The project must not assume in advance how protection mechanisms are configured on the exact target. Apple's 2026-01-28 platform documentation places A14 in the PPL scope, but the 24A446 BuildManifest for iPhone13,1 contains SPTM and TXM payloads (`EVD-0010`). The repository therefore treats the build as SPTM/TXM-based and keeps runtime state separate from build packaging.

## Desired outcome

A researcher should be able to answer, for every material conclusion:

1. Which exact device and software build does this apply to?
2. What was directly observed, and using which method?
3. Which artifacts support the statement, and can their integrity be checked?
4. What alternative explanation or counter-evidence was considered?
5. Can another researcher reproduce the non-invasive or synthetic validation?
6. What remains unknown?

## Non-goals for this foundation

- Shipping a jailbreak or a general-purpose privilege-escalation tool.
- Providing exploit chains, payloads, or operational instructions for bypassing PPL/SPTM.
- Treating a public claim as proof of compatibility with the target device/build.
- Keeping large firmware images, private logs, or device identifiers in the public Git history.

## Design principles

- **Target-scoped:** every result is bound to a target manifest.
- **Evidence-led:** claims have provenance and confidence.
- **Falsifiable:** counter-evidence and rejection conditions are first-class fields.
- **Composable:** research cases, tools, and validation models can be reused across targets.
- **Minimal context:** short canonical docs define process; detailed evidence lives with each case.
- **Safe by default:** offline analysis, synthetic fixtures, and read-only observation are the default validation surfaces.
