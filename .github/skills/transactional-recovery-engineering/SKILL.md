---
name: transactional-recovery-engineering
description: Design transactional operations and reliable rollback for native software and hardware-adjacent workflows. Activate for state transitions, retries, partial failure, backups, restore points, or recovery automation.
---

# Transactional Recovery Engineering

## Purpose
Make state-changing workflows reversible or explicitly fail safe.

## Activation
Use for configuration writes, firmware-adjacent operations, driver installation, process changes, or multi-stage native transactions.

## Required expertise
- State machines, idempotency, compensation, journaling, atomic file replacement, Windows services, and failure injection.

## Workflow
1. Model states and transitions.
2. Capture a complete, integrity-checked before-state.
3. Identify irreversible and partially reversible operations.
4. Use staged operations: validate, prepare, commit, verify.
5. Define compensation actions and timeout behavior.
6. Make operations idempotent where possible.
7. Persist an audit journal with no secrets.
8. Add simulated power/process/crash faults.

## Technical references
- Windows transactional APIs where applicable, file and registry journaling, service control, and project ADRs.

## Expected outputs
- State machine, transaction journal format, rollback matrix, failure-injection cases, and recovery runbook.

## Validation
- Inject failures after each phase and verify exact or documented compensation state. Test interruption and restart.

## Security restrictions
- Never promise rollback for firmware or vendor hardware without verified vendor guidance and physical recovery capability.

## Known limitations
Rollback is only valid for state known to be captured and for operations with proven compensation semantics.
