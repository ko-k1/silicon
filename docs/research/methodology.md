# Research methodology

## Lifecycle

1. **Scope** — define a falsifiable question, target manifest, and permitted methods.
2. **Baseline** — record device/build identity, acquisition method, environment, and unknowns.
3. **Survey** — collect authoritative documentation and public research; preserve publication dates and exact target scopes.
4. **Hypothesize** — state the proposed behavior, expected normal behavior, preconditions, and rejection criteria.
5. **Analyze** — inspect permitted artifacts offline; preserve originals and record tool versions.
6. **Validate** — use fixture-based, synthetic, or non-invasive checks. Record negative and inconclusive outcomes.
7. **Review** — test alternative explanations, counter-evidence, target compatibility, and reproducibility.
8. **Report** — summarize impact, evidence, limitations, and disclosure status.
9. **Archive** — retain hashes, decisions, tool versions, and regression references.

## Evidence discipline

- Use one claim per evidence record where practical.
- Cite primary sources first (Apple platform security documentation, Apple security releases, source code or papers from the original authors).
- Record secondary-source claims as secondary; do not upgrade them through repetition.
- Separate a source's statement from the researcher's interpretation.
- For version-sensitive claims, record the publication date and exact OS/build scope.
- A result from another SoC or device is comparative evidence, not target confirmation.

## Hypothesis template

A hypothesis should include:

- Question: what observable property is being tested?
- Claim: what behavior is expected if the hypothesis is correct?
- Preconditions: exact target and environment constraints.
- Supporting evidence: linked evidence IDs.
- Counter-evidence: linked evidence IDs or an explicit search record.
- Rejection criteria: what result would disprove or materially weaken the claim?
- Safe validation method: offline, synthetic, or non-invasive observation.

## Confidence

Confidence is an evidence assessment, not a subjective feeling. Explain why a confidence level was selected and what would change it. Never use a numeric score without a documented rubric.
