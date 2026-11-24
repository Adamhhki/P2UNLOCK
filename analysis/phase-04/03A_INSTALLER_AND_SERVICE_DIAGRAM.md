# Installer and Service Diagrams

## Entire application architecture

```mermaid
flowchart TD
    Installer[PSeriesInstaller.exe] -->|SCM/repair/status| Service[PSeriesService.exe]
    Service --> Core[PSeriesCore]
    Core --> Discovery[HardwareDiscovery]
    Core --> NVIDIA[NvidiaDiagnostics]
    Core --> Recovery[RecoveryManager]
    Core --> Transactions[TransactionManager]
    Core --> Platform[PSeriesPlatformWindows]
    Core --> Hardware[PSeriesHardware]
    Platform --> SCM[Windows SCM]
    Platform --> PnP[SetupAPI/CfgMgr]
    Platform --> Log[Event Log/File Log]
    Hardware --> Backend[Backend Abstraction]
    Backend --> Future[Future signed driver only]
```

## Service startup

```mermaid
stateDiagram-v2
    [*] --> Starting
    Starting --> LoadConfig
    LoadConfig --> ValidateJournal
    ValidateJournal --> RecoveryRequired: pending
    ValidateJournal --> DiscoverHardware: clean
    RecoveryRequired --> BlockedOrRecover
    DiscoverHardware --> Classify
    Classify --> ReadOnlyHealthy: supported/missing/unsupported
    ReadOnlyHealthy --> Running
    BlockedOrRecover --> Running
    Running --> [*]
```

## Automatic workflow

```mermaid
flowchart TD
    Boot[Boot/delayed start] --> Config[Load policy]
    Config --> Journal[Validate recovery journal]
    Journal -->|Pending| Recover[Attempt bounded recovery]
    Journal -->|Clean| Enumerate[Read-only discovery]
    Enumerate --> GPU[Check GPU]
    GPU --> Eligible{Eligible + modifying enabled?}
    Eligible -->|No| Idle[Log/status and remain running]
    Eligible -->|Yes| Pre[Preconditions]
    Pre --> Tx[Prepare journal]
    Tx --> Commit[Explicit authorized operation]
    Commit --> Verify[Verify link/CUDA]
    Verify -->|Pass| Complete[Complete journal]
    Verify -->|Fail| Rollback[Compensation]
```

## Uninstaller lifecycle

```mermaid
flowchart TD
    User[User action] --> Elevate[Administrator elevation]
    Elevate --> StopOps[Stop new hardware operations]
    StopOps --> Pending{Pending transaction?}
    Pending -->|Yes| Preserve[Preserve journal and report]
    Pending -->|No| StopSvc[Stop PSeriesService]
    StopSvc --> RemoveSvc[Delete service registration]
    RemoveSvc --> RemoveFiles[Remove binaries]
    RemoveFiles --> Done[Report completion]
    Preserve --> StopSvc
*** End Patch
