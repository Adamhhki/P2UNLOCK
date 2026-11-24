# Recovery Architecture

## Separate states

Software state and physical hardware state are separate:

- journal state,
- resource snapshot,
- policy snapshot,
- actual PCI link state,
- CUDA validation state,
- completed/compensated/failed status.

## Journal requirements

- schema version,
- unique transaction ID,
- boot GUID,
- device identity,
- upstream identity,
- resource identity,
- before-state hash,
- intended compensation,
- phase,
- status,
- checksum,
- migration history.

## Transaction state machine

```mermaid
stateDiagram-v2
    [*] --> Validate
    Validate --> Prepare: eligible
    Validate --> Unsupported: evidence missing
    Prepare --> Commit: snapshot and journal complete
    Prepare --> Failed: snapshot fail
    Commit --> Verify: operation complete
    Commit --> Recovering: interruption
    Verify --> Completed: all success gates
    Verify --> Recovering: verification fail
    Recovering --> Recovered: compensation verified
    Recovering --> Blocked: compensation unverified
    Failed --> Blocked
    Completed --> [*]
    Blocked --> [*]
```

Restoring software state is not defined as physical restoration.
