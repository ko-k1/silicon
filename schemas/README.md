# Schemas

JSON Schema files define the machine-readable contract for target manifests, source records, evidence records, research cases, and validation results. Keep examples and schemas synchronized. The initial YAML files are human-authored instances of these schemas.

Validate the committed records with:

```sh
python3 -m engineering.inventory.schema_validation .
```

Schema validation checks structure, enums, identifier patterns, and required fields. It does not check cross-record references; use `engineering.inventory.record_integrity` for that.
