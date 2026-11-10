# Research lifecycle and state transitions

## Case states

`new` → `scoped` → `investigating` → `hypothesis` → `analyzed` → `validated` → `reported` → `archived`

A case may move to `rejected` from any investigative state when the hypothesis is falsified or the candidate is not a security issue. A case may remain `inconclusive` when evidence is insufficient; do not force a conclusion to close a milestone.

## Transition gates

| Transition | Required checks |
|---|---|
| new → scoped | Question, target, permitted methods, owner/reviewer |
| scoped → investigating | Baseline and source register started |
| investigating → hypothesis | Evidence and counter-evidence reviewed; falsifiable claim written |
| hypothesis → analyzed | Analysis method, tool versions, inputs, and limitations recorded |
| analyzed → validated | Safe validation design and expected outcomes documented |
| validated → reported | Results independently reviewed; impact and scope bounded |
| reported → archived | Report/disclosure state recorded; artifacts and regression references retained |

## IDs

- Research case: `CASE-####`
- Evidence record: `EVD-####`
- Validation run: `VAL-####`
- Public source: `SRC-####`

IDs are immutable. Do not recycle IDs after rejection or archival.
