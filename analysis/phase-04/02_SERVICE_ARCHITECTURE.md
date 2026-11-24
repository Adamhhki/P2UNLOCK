# Service Architecture

## Executables

PSeriesService.exe is the application.

PSeriesInstaller.exe only controls installation lifecycle.

## Process model

The service runs:

- in Session 0,
- independently of desktop login,
- through SCM,
- at automatic or delayed-automatic startup,
- without a visible window.

## Recommended startup mode

Automatic Delayed Start is the initial recommendation.

Reason:

- boot hardware and NVIDIA drivers may not be ready during immediate service start,
- delayed startup provides initialization retries,
- read-only discovery remains safe,
- no hardware modification occurs during service start.

Automatic startup remains required, but hardware eligibility is rechecked after PnP settle-time or event-based device arrival.

## Startup sequence

```mermaid
sequenceDiagram
    participant SCM
    participant Service
    participant Core
    participant Platform
    participant Recovery
    SCM->>Service: StartService
    Service->>Platform: Initialize logging and configuration
    Service->>Recovery: Validate journal
    alt Interrupted transaction
        Recovery-->>Service: Recovery required
        Service->>Core: Enter recovery mode
    else No pending transaction
        Service->>Platform: Enumerate PnP devices
        Platform-->>Core: Device snapshot
        Core->>Core: Eligibility and configuration
        Core-->>Service: Read-only status
    end
    Service->>SCM: ReportRunning
```
