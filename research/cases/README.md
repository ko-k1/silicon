# Research cases

Create each case by copying `_template/` and assigning the next unused `CASE-####` ID. Keep one primary question per case. Cross-link related cases rather than merging unrelated hypotheses.

## Active cases

- `CASE-0001` - Page-table protection mechanism for A14 / iOS 27.0.1 (24A446). Status: `analyzed`; build-level evidence supports SPTM/TXM for all four iPhone 12-family A14 product types. Device runtime validation is `not-run`.
- `CASE-0002` - iOS 27 / 27.0.1 public vulnerability baseline for A14. Status: `analyzed`; 163-CVE register, 27.0.1 has no published CVE entries.
- `CASE-0003` - Public PPL/SPTM bypass scope for A14. Status: `analyzed`; reviewed Dopamine 3.0 stable A14 support ends at iOS 17.3.1 (Titan claims to 17.4 beta 3), no reviewed A14/24A446 demonstration.

## Case map

`CASE-0001` establishes the build-level mechanism across the four iPhone 12-family A14 product types. `CASE-0002` records vulnerability metadata and does not assert exploitability. `CASE-0003` catalogs public bypass scope and does not assert target compatibility. Link claims to the narrowest applicable case.
