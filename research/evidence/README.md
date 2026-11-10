# Evidence records

Create one YAML file per evidence record using `schemas/evidence-record.schema.json` as the contract. Use immutable IDs such as `EVD-0001`. Link evidence IDs from cases rather than duplicating claims.

## Index

| ID | Claim summary | Class | State |
|---|---|---|---|
| `EVD-0001` | iOS 27.0.1 build 24A446 release identity | primary | observed |
| `EVD-0002` | Apple documents SPTM for A15+/M2+ and replaces PPL | primary | observed |
| `EVD-0003` | Apple places A12-A14 in the PPL column | primary | observed |
| `EVD-0004` | iOS 27.0.1 has no published CVE entries | primary | observed |
| `EVD-0005` | Derived iOS 27 advisory counts (163 total, 25 Kernel) | derived | observed |
| `EVD-0006` | Apple Wiki reports iOS 27 SPTM on A13/A14/M1 | secondary | observed |
| `EVD-0007` | Public SPTM map places A13/A14/M1 at iOS 27.0 | secondary | observed |
| `EVD-0008` | Tooling note treats iOS 27 A13/A14/M1 as TXM | secondary | observed |
| `EVD-0009` | Survey repeats PPL on A12-A14/M1 (counter-evidence) | secondary | observed |
| `EVD-0010` | 24A446 iPhone13,1 BuildManifest contains SPTM/TXM | primary | observed |
| `EVD-0011` | Public tool compatibility ranges for A14/M1 | secondary | observed |
| `EVD-0012` | 24A446 iPhone13,1 kernelcache is an SPTM build | primary | observed |
| `EVD-0013` | Operating system integrity page not listed as updated after January 2026 | primary | observed |
| `EVD-0014` | iPhone13,4 24A446 BuildManifest also contains SPTM/TXM | primary | observed |
| `EVD-0015` | Community tracker frames A14/M1 as PPL (counter-evidence) | secondary | observed |
| `EVD-0016` | iPhone13,2/iPhone13,3 24A446 BuildManifest also contains SPTM/TXM | primary | observed |
| `EVD-0017` | 24A446 release kernelcache is byte-identical across four A14 product types | primary | observed |
| `EVD-0018` | iPhone13,1 SPTM payload matches manifest digest and is an arm64e Mach-O | primary | observed |
| `EVD-0019` | iPhone13,1 TXM payload matches manifest digest and is an arm64e Mach-O | primary | observed |
| `EVD-0020` | 24A446 restore SPTM/TXM digests match fourcc-only retags of the installed IM4P files | derived | observed |

`EVD-0010`, `EVD-0012`, `EVD-0014`, `EVD-0016`, and `EVD-0017` are the build-level mechanism evidence for the four iPhone 12-family A14 product types; `EVD-0018` and `EVD-0019` link the iPhone13,1 manifest declarations to the extracted installed payload bytes; `EVD-0020` resolves the restore-role digest difference as a fourcc retag at the IM4P level. They are not runtime measurements. `EVD-0002`, `EVD-0003`, and `EVD-0009` are retained as the pre-iOS 27/counter-evidence view.
