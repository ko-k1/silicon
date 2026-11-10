# Repository tests

Test schemas, parsers, deterministic outputs, and fixture handling. Tests should run without a connected iPhone and without changing device state.

## Running the tooling tests

```sh
python3 -m pip install -r requirements-dev.txt
python3 -m unittest discover -s tests/unit -t .
```

The record integrity tests read the committed `EVD`, `SRC`, `VAL`, and `CASE` records and require `PyYAML`. The schema validation tests also require `jsonschema`. The archive manifest tests require the `git` CLI. Fixtures live under `tests/unit/fixtures/`. Keep them synthetic and small; do not commit extracted firmware or device data.
