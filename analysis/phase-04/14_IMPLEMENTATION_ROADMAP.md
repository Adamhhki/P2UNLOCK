# Implementation Roadmap

## Milestone 1: architecture freeze

Deliverables: interface freeze, threat model, schemas.

Acceptance: no unresolved service startup write behavior.

Environment: Linux design tools.

## Milestone 2: portable core

Deliverables: domain models, configuration, validation, unit tests.

Acceptance: Linux unit suite passes.

## Milestone 3: Windows read-only discovery

Deliverables: SetupAPI/PnP enumeration and PCI status.

Acceptance: Windows integration tests with mock and approved hardware.

## Milestone 4: NVIDIA diagnostics

Deliverables: optional NVML/CUDA load and buffer diagnostics.

Acceptance: missing-library and GPU-loss tests pass.

## Milestone 5: Windows service

Deliverables: SCM host, automatic/delayed startup, logging.

Acceptance: boot, stop, restart, crash, and PnP removal tests pass.

## Milestone 6: recovery subsystem

Deliverables: journal, migration, checksum, transaction state.

Acceptance: every phase interruption is deterministically recoverable or blocked.

## Milestone 7: installer

Deliverables: native GUI plus MSI.

Acceptance: install/repair/upgrade/uninstall pass in Windows VM.

## Milestone 8: independent verification

Deliverables: hardware test matrix and release evidence.

Acceptance: target hardware approvals and rollback tests pass.

Hardware-modifying milestones remain blocked until evidence and authorization exist.
