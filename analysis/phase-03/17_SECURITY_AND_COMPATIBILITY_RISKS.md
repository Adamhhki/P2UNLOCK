# Security and Compatibility Risks

## Confirmed static risks

- The executable can create and start temporary Windows kernel-driver services.
- It can open a device interface and issue `DeviceIoControl`.
- All three supplied drivers expose device/symbolic-link and HAL/MMIO-related imports.
- BS_RCIO has broader packet/thread and physical mapping imports.
- State files are bound to launch/device/resource fields, but hardware restoration remains unclear.

## Compatibility risks

- Canonical archive unavailable.
- HVCI/Secure Boot target acceptance unknown.
- Kernel signing and certification are not established by static metadata.
- Windows build compatibility is unknown.
- NVML/nvcuda availability or exports may vary.
- No runtime or hardware compatibility test is present.

## Security boundary

No IOCTL caller, physical-memory primitive, kernel exploit, signing bypass, or device harness was created.
