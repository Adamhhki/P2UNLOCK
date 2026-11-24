# Windows Service Implementation

`apps/service/main.cpp` implements:

- `wWinMain`
- `StartServiceCtrlDispatcherW`
- `ServiceMain`
- `RegisterServiceCtrlHandlerExW`
- `START_PENDING`
- `RUNNING`
- `STOP_PENDING`
- `STOPPED`
- worker-thread stop event

No hardware operations are performed.
