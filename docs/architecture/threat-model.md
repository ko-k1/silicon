# Threat model

## Assets

- Integrity of kernel and privileged execution state.
- Integrity of page tables and protected memory mappings.
- Code-signing and execution-policy enforcement.
- Research artifacts, device data, credentials, and unpublished findings.

## Trust boundaries

- User space ↔ kernel.
- Kernel ↔ page-table and code-execution protection components (the 24A446 A14 build packages SPTM/TXM; PPL is the historical A14 mechanism for earlier iOS versions).
- OS ↔ firmware / hardware interfaces.
- Research host ↔ physical test device.
- Raw artifacts ↔ derived analysis outputs.
- Public evidence ↔ researcher inference.

## Assumptions to validate

- The researcher has authorization to inspect the device and artifacts.
- The exact device and OS build can be identified.
- Public documentation may not describe every implementation detail.
- Similar builds or SoCs may differ in relevant behavior.
- Logs and artifacts may contain personal or device-identifying information.

## Out of scope

This threat model does not authorize exploitation of third-party devices, data extraction, persistence, evasion, or disabling security controls. Validation in this repository is limited to offline analysis, synthetic models, and non-invasive observation.
