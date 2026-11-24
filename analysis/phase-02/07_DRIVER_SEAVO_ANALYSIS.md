# SvIoCtrlx64.sys Static Analysis

## Confirmed metadata

- SHA256: `9ade632e54c3f5e8c75eaf636f2910bad3a8a07d6f078e48c9641d3af1fe811c`
- PE32+ native x86-64
- Subsystem 1, NT native
- Entry point RVA 0x5064
- Image base 0x10000
- Subsystem version 6.1
- Ghidra detected 11 functions
- PDB path string: `d:\_winrin0_ddk\driver\sys\lib\amd64\SvIoCtrlx64.pdb`

## Imports

- `MmMapIoSpace`
- `MmUnmapIoSpace`
- `IoCreateDevice`
- `IoDeleteDevice`
- `IoCreateSymbolicLink`
- `IoDeleteSymbolicLink`
- `IofCompleteRequest`
- `HalGetBusDataByOffset`
- `HalSetBusDataByOffset`
- `KeBugCheckEx`
- `RtlInitUnicodeString`

## Findings

- The executable strings name `\\.\SvIoCtrl_1_0_0`.
- The driver imports symbolic-link, device-object, and HAL/MMIO-related APIs.
- Static metadata confirms it is an old kernel-native driver, but exact dispatch and IOCTL layouts are not established.
- The presence of an Authenticode/signature record does not establish target-machine loading or HVCI acceptance.

## Unknowns

- Exact IRP dispatch handlers.
- Exact IOCTL codes.
- Security descriptors and access policy.
- Whether the executable opens and validates the named device.
- Runtime compatibility on Windows 10/11 target builds.
