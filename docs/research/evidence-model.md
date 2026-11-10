# Evidence model

## Evidence classes

| Class | Meaning | Example |
|---|---|---|
| `primary` | Direct authoritative source or direct measurement | Apple documentation; signed device-reported build metadata |
| `reproduced` | Result independently repeated under recorded conditions | Same offline parser output on a second clean environment |
| `secondary` | Reputable interpretation or reporting | Technical write-up citing an upstream source |
| `anecdotal` | Unverified report or informal claim | Forum post without reproducible artifacts |
| `derived` | Researcher-produced output based on identified inputs | Hash manifest, parsed metadata, comparison table |

## Epistemic states

- `unknown`: not established.
- `observed`: directly recorded, but scope may be narrow.
- `inferred`: interpretation supported by evidence but not directly measured.
- `confirmed`: sufficiently corroborated for the stated scope and method.
- `contradicted`: material evidence conflicts with the claim.

These states apply to claims, not to the credibility of a person or project.

## Evidence record requirements

Every evidence record should identify its ID, claim, class, epistemic state, source or acquisition method, timestamp, target scope, integrity hash where applicable, limitations, and related case IDs.

## Handling contradictions

Do not delete a conflicting record to make a conclusion cleaner. Preserve both records, describe the mismatch, compare their target scopes and methods, and narrow or withdraw the claim as needed.

## Artifact integrity

Hash an artifact before analysis. Keep the original immutable. Record the hash algorithm, digest, byte length, acquisition source, and transformation lineage. A hash proves identity relative to a recorded digest; it does not prove authenticity or correctness of the source.
