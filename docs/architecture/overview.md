# Architecture overview

## Logical layers

```text
Target Profile
    │ scopes
    ▼
Research Case ─────── references ─────── Public Sources
    │                                      │
    ├── Hypotheses                          └── Source Register
    ├── Evidence                            
    ├── Analysis Notes
    └── Validation Definition
             │
             ▼
       Validation Result
             │
             ▼
       Technical Report
```

## Current case map

- `CASE-0001` - A14 / 24A446 page-table protection mechanism (PPL vs SPTM/TXM).
- `CASE-0002` - iOS 27 / 27.0.1 public vulnerability baseline; the register is `research/public-research/ios27-vulnerability-register.yaml`.
- `CASE-0003` - Public PPL/SPTM bypass scope for A14.

Cases are linked by evidence and source IDs rather than by merging conclusions.

## Separation rules

- `targets/` defines what environment a statement applies to.
- `research/` records questions, hypotheses, sources, and case conclusions.
- `analysis/` stores interpretation and metadata derived from artifacts; preserve links to immutable originals.
- `engineering/` contains reusable tooling, not one-off conclusions.
- `validation/` defines repeatable checks and records results. A validation result is not automatically proof of exploitability or absence of a vulnerability.
- `reports/` contains reviewed summaries suitable for a technical audience or coordinated disclosure.

## Data flow

Raw inputs are acquired with provenance → hashed → stored outside Git when large or sensitive → analyzed in a reproducible environment → summarized with evidence IDs → validated using offline/synthetic/read-only methods → reviewed → reported.

Never overwrite an original input with a normalized or parsed version. Derived files must identify their parent artifact and transformation tool/version.
