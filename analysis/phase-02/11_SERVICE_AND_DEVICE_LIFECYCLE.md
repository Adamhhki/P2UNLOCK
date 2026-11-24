# Service and Device Lifecycle

## Static evidence

The executable imports:

- `OpenSCManagerW`
- `CreateServiceW`
- `StartServiceW`
- `QueryServiceConfigW`
- `ControlService`
- `DeleteService`

This is `CONFIRMED-STATIC` evidence that executable code can create or manage services.

`CreateFileW` and `DeviceIoControl` establish that executable code can open or communicate with Windows device objects.

## Driver lifecycle indicated by imports

The executable likely:

1. Validates a selected driver file.
2. Creates or opens an SCM service.
3. Starts a temporary service.
4. Opens a named device object.
5. Uses IOCTL operations.
6. Stops and deletes a service.

This is `INFERRED`; no call-site decompilation proves this sequence.

## Cleanup

Strings mention temporary driver cleanup, service-name cleanup, and cleanup warnings. Exact cleanup order must be established by xref/decompile analysis.

## Persistent application service

No static evidence currently establishes a persistent PSeriesUnlock Windows background service. Temporary service APIs appear, but an application-service design is an unknown and must not be confused with temporary kernel-driver loading.
