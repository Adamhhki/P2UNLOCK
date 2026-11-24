# Device Communication Flow

## Confirmed wrapper

`FUN_140012c60` calls `DeviceIoControl` with:

- a handle,
- IOCTL code,
- input buffer,
- input size,
- output buffer,
- output size,
- returned-byte output,
- no overlapped operation.

It validates returned output length and reports an IOCTL failure message.

## Existing handle flow

The service lifecycle function calls `CreateFileW` and passes the handle to service state or communication structures.

## Unknown

- Actual IOCTL constants.
- Backend-specific IOCTL semantics.
- Struct layouts.
- Security descriptor/access checks.
- Device names.
- Complete executable to device call graph.
