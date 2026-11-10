# Validation workspace

Validation definitions and results must use the schema in `schemas/validation-result.schema.json`. Default to offline fixtures and synthetic models. Do not encode a working privilege-escalation or protection-bypass implementation here.

## Current results

| ID | Case | Status | Scope |
|---|---|---|---|
| `VAL-0001` | `CASE-0001` | `not-run` | Planned non-invasive device metadata check |
| `VAL-0002` | `CASE-0001` | `passed` | Offline BuildManifest inspection for iPhone13,1 24A446 |
| `VAL-0003` | `CASE-0001` | `passed` | Offline kernelcache segment inspection for iPhone13,1 24A446 |
| `VAL-0004` | `CASE-0001` | `passed` | Offline BuildManifest inspection for iPhone13,4 24A446 |
| `VAL-0005` | `CASE-0001` | `passed` | Offline BuildManifest inspection for iPhone13,2/iPhone13,3 24A446 and cross-product digest comparison |
| `VAL-0006` | `CASE-0001` | `passed` | Offline byte comparison of the 24A446 release kernelcache across four A14 product types |
| `VAL-0007` | `CASE-0001` | `passed` | Offline SPTM/TXM Image4 payload and Mach-O inspection with manifest digest comparison |

`VAL-0002` through `VAL-0007` establish build packaging, payload structure, and kernel structure only. They do not measure runtime protection state.
