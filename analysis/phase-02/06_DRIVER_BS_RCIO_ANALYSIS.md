# BS_RCIO64.sys Static Analysis

## Confirmed metadata

- SHA256: `d205286bffdf09bc033c09e95c519c1c267b40c2ee8bab703c6a2d86741ccd3e`
- PE32+ native x86-64
- Subsystem 1, NT native
- Entry point RVA 0x715c
- Image base 0x10000
- Subsystem version 5.2
- Ghidra detected 36 functions

## Imports

Static imports include `ntoskrnl.exe` device/synchronization APIs and:

- `HalGetBusDataByOffset`
- `HalSetBusDataByOffset`
- `MmMapIoSpace`
- `MmUnmapIoSpace`
- `IoCreateDevice`
- `IoDeleteDevice`
- `IoCreateSymbolicLink`
- `IoDeleteSymbolicLink`
- `IofCompleteRequest`
- `PsCreateSystemThread`
- `PsTerminateSystemThread`
- `KeWaitForSingleObject`
- `IoStartPacket`
- `IoStartNextPacket`
- `IoAcquireCancelSpinLock`
- `IoReleaseCancelSpinLock`

## High-level static findings

- The driver has an NT native entry point and creates/deletes device objects and symbolic links.
- It imports HAL bus-data APIs and kernel physical-address mapping APIs.
- It imports packet and thread management APIs, suggesting an IRP/worker-oriented implementation.
- Ghidra and PE tools confirm code, init, pdata, and resource sections.

## Unknowns

- Exact dispatch routine and symbolic link names.
- Exact IOCTL values and input/output layouts.
- Whether every imported API is reachable from executable calls.
- Security/access rules and kernel-mode privilege assumptions.
- Target Windows compatibility and signing status.

No IOCTL was invoked and no driver was loaded.
