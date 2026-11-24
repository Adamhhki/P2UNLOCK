# BS_RCIO Dispatch Analysis

## Metadata

- SHA256: `d205286bffdf09bc033c09e95c519c1c267b40c2ee8bab703c6a2d86741ccd3e`
- Entry: `0001715c`
- Ghidra function count: 36

## Confirmed static imports

- Device object and symbolic-link APIs.
- Packet/IRP cancellation and completion APIs.
- `MmMapIoSpace` / `MmUnmapIoSpace`.
- HAL bus data APIs.

## Unresolved

- DriverEntry exact address already appears near entry.
- MajorFunction registration.
- IRP_MJ_CREATE/CLOSE/DEVICE_CONTROL mapping.
- IOCTL constants.
- Device and symbolic-link names.
- Access validation.

No file named in this report was executed or modified.
