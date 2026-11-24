# Automatic Startup Workflow

## Boot goals

At boot, the service must:

1. initialize configuration,
2. validate and preserve recovery state,
3. discover PnP devices,
4. identify NVIDIA hardware through public APIs,
5. classify supported, unsupported, missing, or blocked,
6. report health,
7. wait for delayed PnP readiness,
8. perform no implicit hardware modification.

## Missing hardware

No GPU or no eligible GPU means:

- healthy idle state,
- no modifying attempt,
- reason recorded,
- service remains running.

## Unsupported hardware

Unsupported hardware means:

- no private register or backend operation,
- no third-party driver install,
- explicit unsupported state.

## Driver unavailable

Driver unavailable means:

- report blocked,
- retain read-only discovery,
- do not fallback to another unsigned or unverified backend.

## Automatic modification policy

Only if all are true may an evaluator permit a future modification:

- configuration explicitly enables it,
- target is on the independently verified hardware allowlist,
- firmware/Windows condition is reproduced,
- identity and resource binding match,
- idle/precondition requirements pass,
- journal snapshot is complete,
- recovery command is available,
- target operation has a documented rollback path,
- no conflicting state exists.

Unknown or unverified operations remain unsupported.
