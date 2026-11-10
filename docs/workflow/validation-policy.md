# Validation policy

## Permitted default surfaces

1. Offline inspection of lawfully obtained artifacts.
2. Synthetic fixtures and simplified models that do not reproduce a working bypass.
3. Unit, integration, and regression tests for repository tooling.
4. Non-invasive observation and metadata collection from an owned or explicitly authorized device.

## Excluded from this foundation

- Operational exploit chains, privilege-escalation payloads, or code to bypass/disable PPL, SPTM, TXM, or other platform protections.
- Persistence, stealth, evasion, or unauthorized extraction of protected data.
- Automated destructive device actions or tests that alter security state.

## Validation record

Record the target manifest, validation ID, environment type, exact inputs and hashes, tool versions, timestamp, expected outcome, observed outcome, status, reproduction steps at a safe level, and limitations.

## Result states

- `passed`: the defined safe test met its expected condition.
- `failed`: the defined safe test did not meet its expected condition.
- `inconclusive`: evidence does not distinguish the outcomes.
- `not-run`: no execution occurred.

A `passed` result applies only to the test as defined. It does not prove the absence of other vulnerabilities or establish exploitability.

## Device safety

Read-only observation is the default. Any proposed state-changing action requires a separate risk review, explicit authorization, recovery plan, and manual operator decision. Do not include destructive steps in unattended workflows.
