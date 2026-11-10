# Artifact handling

## Acquisition record

Record source, acquisition time (UTC), target/build, operator or automation identity, tool/version, byte length, and SHA-256. Record whether the artifact is original, transformed, or derived.

## Storage

- Keep large firmware/kernel images and raw diagnostic bundles outside Git.
- Keep private device data out of public issues, commits, and CI logs.
- Commit small, redistributable fixtures only when their licensing and provenance are clear.
- Use sanitized excerpts for reports and examples.

## Processing

- Never modify the original artifact in place.
- Store derived artifacts separately and link them to parent hashes.
- Make parsers deterministic where possible; record parser version and configuration.
- Treat malformed or unexpected input as untrusted. Run parsers with least privilege and resource limits.
