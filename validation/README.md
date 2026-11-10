# Validation workspace

Validation definitions and results must use the schema in `schemas/validation-result.schema.json`. Default to offline fixtures and synthetic models. Do not encode a working privilege-escalation or protection-bypass implementation here.

## Current results

| ID | Case | Status | Scope |
|---|---|---|---|
| `VAL-0001` | `CASE-0001` | `not-run` | Planned non-invasive device metadata check |
| `VAL-0002` | `CASE-0001` | `passed` | Offline BuildManifest inspection for iPhone13,1 24A446 |
| `VAL-0003` | `CASE-0001` | `passed` | Offline kernelcache segment inspection for iPhone13,1 24A446 |
| `VAL-0004` | `CASE-0001` | `passed` | Offline BuildManifest inspection for iPhone13,4 24A446 |

`VAL-0002`, `VAL-0003`, and `VAL-0004` establish build packaging and kernel structure only. They do not measure runtime protection state.
