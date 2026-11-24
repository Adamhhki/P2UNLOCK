# Project Requirements and Separation

## A. Original reference product

The original PSeriesUnlock package is evidence only. It includes:

- proprietary executable,
- third-party `.sys` drivers,
- Windows launch scripts,
- machine-readable manifest,
- research documentation,
- reported experiments and validations.

The original executable must not be loaded or used as a runtime dependency of the future application.

## B. Independent replacement product

The future product must independently own:

- executable identity and build,
- original C++20 source,
- core engine,
- Windows GUI,
- Windows background service,
- IPC implementation,
- configuration system,
- logging and diagnostics,
- transaction and recovery implementation,
- installer/uninstaller,
- test suite and evidence ledger.

The future replacement must not wrap, shell out to, or directly invoke PSeriesUnlock.exe.

Temporary kernel-driver services described in reference scripts are not the future application’s persistent service.

The future persistent Windows service must have:

- an independent service name,
- independent signing/deployment metadata,
- explicit privilege boundaries,
- no hardware action solely by implicit startup,
- configuration and operator approval,
- audit logging,
- controlled IPC,
- start/stop and recovery behavior,
- separate uninstall and rollback.

## Phase 1 boundaries

No implementation source or architecture design is required or included in this phase.

Before implementation:

- obtain the authoritative ZIP or explicitly continue from the mirror collection,
- verify archive provenance,
- perform static binary analysis,
- establish supported hardware evidence,
- design transactions and recovery,
- create Windows build/test environments,
- validate only on approved target hardware.
