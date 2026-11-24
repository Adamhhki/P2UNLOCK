# MyDrivers Dispatch Analysis

## Metadata

- SHA256: `a2e11d0eec70bf0818aeef0a9676cc4157bb34e06fbe54631eb98b51fc8d92c8`
- Entry: `00015064`
- Ghidra function count: 11

## Confirmed

- Native x64 kernel driver.
- Core imports match Seavo for device/symbolic-link/MMIO/HAL operations.
- Executable strings reference `mydrivers.sys`.

## Unresolved

- Exact symbolic-link name.
- MajorFunction registration.
- IOCTL table.
- Vendor-specific access behavior.
