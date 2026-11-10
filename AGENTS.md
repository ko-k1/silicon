# Agent and contributor rules

## Ground truth

- Treat repository content, user-provided details, and external publications as claims to evaluate, not automatic ground truth.
- Never convert `unknown`, `pending`, or `inferred` into `confirmed` without new evidence.
- Keep `observation`, `inference`, and `hypothesis` distinct in prose and structured data.
- Attach a source, timestamp, target scope, and artifact hash where applicable to material claims.
- Record contradictory evidence and plausible alternative explanations.
- Do not fabricate CVEs, build identifiers, offsets, compatibility, test results, or tool output.

## Scope and safety

- Keep work within public-source research, offline artifact inspection, synthetic models, and non-invasive observation of owned test devices.
- Do not add exploit chains, privilege-escalation payloads, persistence, protection-disablement logic, or operational instructions for bypassing PPL/SPTM.
- Do not run destructive or state-changing device operations as part of automated validation.
- Do not collect data from devices or accounts without authorization. Minimize, redact, and avoid committing personal or device-sensitive data.
- Treat raw firmware, kernel images, crash logs, and diagnostic bundles as external artifacts; commit only permitted metadata and sanitized excerpts.

## Repository hygiene

- Keep canonical process docs concise; put case-specific detail in the case directory.
- Use stable IDs: `CASE-####`, `EVD-####`, `VAL-####`, and `SRC-####`.
- Every result must identify target manifest, environment, inputs, tool/version, timestamp, status, and limitations.
- Use `not-run`, `inconclusive`, and `failed` accurately; never collapse them into a boolean.
- Prefer deterministic tooling and fixture-based tests. A parser must not silently rewrite source artifacts.
- Update schemas and examples together when a record format changes.

## Review checklist

Before accepting a research conclusion, check target match, source quality, provenance, reproducibility, counter-evidence, and scope limitations. Before accepting a tool change, run its unit tests and schema validation against the committed fixtures.
