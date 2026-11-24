# Core Engine Architecture

## PSeriesCore layers

- Domain: hardware identity, link state, device eligibility, operation policy.
- Application: discovery, workflow, validation, verification.
- Transactions: prepare/commit/rollback state machine.
- Recovery: persistent journal and compensation.

## Module dependencies

```mermaid
flowchart LR
    Service[PSeriesService] --> App[Core Application]
    Installer[PSeriesInstaller] --> Status[Core Read-only Status API]
    App --> Domain[Core Domain]
    App --> HW[Hardware Abstraction]
    App --> Nvidia[NVIDIA Integration]
    App --> Tx[Transaction Manager]
    App --> Recovery[Recovery Manager]
    App --> Logger[Logging]
    Platform[Windows Platform] --> HW
    Platform --> Service
```

## Modules

- HardwareDiscovery
- PciTopology
- PciDiagnostics
- BackendManager
- NvidiaDiagnostics
- AutoPegEngine
- TransactionManager
- RecoveryManager
- Logger
- ConfigurationManager

Core logic must not depend on Win32 UI or installer code.
