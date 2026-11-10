# Repository tests

Test schemas, parsers, deterministic outputs, and fixture handling. Tests should run without a connected iPhone and without changing device state.

## Running the tooling tests

```sh
python3 -m unittest discover -s tests/unit -t .
```

Fixtures live under `tests/unit/fixtures/`. Keep them synthetic and small; do not commit extracted firmware or device data.
