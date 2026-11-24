---
name: hardware-validation
description: Plan and execute safe, reproducible hardware validation for Windows GPU/PCIe work. Activate for hardware test matrices, instrumentation, pre/post snapshots, recovery, or differential target testing.
---

# Hardware Validation

## Purpose
Ensure that hardware claims are backed by actual observations and protected by recovery procedures.

## Activation
Use before or during target-system testing, GPU diagnostics, PCIe operations, or unstable native integration.

## Required expertise
- Windows event/log collection, GPU/PCI diagnostics, stop-at-failure discipline, snapshots, and rollback engineering.

## Workflow
1. Inventory exact hardware, firmware, driver, OS build, and power state.
2. Define success criteria and non-destructive read-only baselines.
3. Add a pre-test snapshot and post-test snapshot.
4. Use one-variable-at-a-time test matrices.
5. Require recovery media or known rollback for write operations.
6. Define timeouts, watchdog actions, and stop conditions.
7. Capture logs, bus state, temperatures/clock state only through supported tooling.
8. Report pass/fail per target and environment.

## Technical references
- Vendor diagnostics, Windows Event Viewer/ETW, WMI/PNP diagnostics, PCIe topology tools, and project test records.

## Expected outputs
- Hardware manifest, test matrix, execution log, snapshot diff, incident log, and capability/limitation report.

## Validation
- Re-run representative cases across independent boots and, where available, multiple target systems.

## Security restrictions
- No live testing on production systems without approval. No destructive flashing or stress tests without rollback and operator presence.

## Known limitations
A test on one board, firmware, or OS build is not evidence for every configuration.
