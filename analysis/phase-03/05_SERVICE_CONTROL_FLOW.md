# Service Control Flow

## Confirmed decompilation

`FUN_14000ed70`:

1. Builds service image configuration.
2. Creates the device file handle.
3. Checks an existing handle.
4. Opens SCM with `OpenSCManagerW`.
5. Creates a GUID.
6. Builds a name starting with `PSeriesNative_`.
7. Calls `CreateServiceW`.
8. Calls `StartServiceW`.
9. Opens the named device with `CreateFileW`.

## Cleanup

`FUN_140011210`:

- Closes the device handle.
- Calls `ControlService(..., 1, ...)`.
- Calls `DeleteService`.
- Closes service handles.

Temporary service cleanup is confirmed statically. Persistent application service behavior is unknown.
