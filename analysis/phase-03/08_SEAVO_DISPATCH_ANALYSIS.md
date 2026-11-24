# Seavo Dispatch Analysis

## Metadata

- SHA256: `9ade632e54c3f5e8c75eaf636f2910bad3a8a07d6f078e48c9641d3af1fe811c`
- Entry: `00015064`
- Ghidra function count: 11

## Confirmed

- Native x64 kernel driver.
- Imports device/symbolic-link APIs.
- Imports physical MMIO mapping and HAL bus APIs.
- Executable static string names `SvIoCtrlx64.sys` and `\\.\SvIoCtrl_1_0_0`.

## Unresolved

- DriverEntry call details.
- MajorFunction table.
- Device create/close/control dispatch.
- IOCTL semantics.
- Access-control/SecurityDescriptor behavior.
