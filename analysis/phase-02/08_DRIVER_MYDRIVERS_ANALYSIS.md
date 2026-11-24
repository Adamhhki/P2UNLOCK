# mydrivers.sys Static Analysis

## Confirmed metadata

- SHA256: `a2e11d0eec70bf0818aeef0a9676cc4157bb34e06fbe54631eb98b51fc8d92c8`
- PE32+ native x86-64
- Subsystem 1, NT native
- Entry point RVA 0x5064
- Image base 0x10000
- Subsystem version 6.1
- Ghidra detected 11 functions
- PDB path string: `d:\drivergeniusdev\drivergenius\trunk\src\pnpservice\mydrivers\sys\lib\amd64\MyDrivers.pdb`

## Imports

The same core static import set as SvIoCtrl was found:

- `MmMapIoSpace`
- `MmUnmapIoSpace`
- `IoCreateDevice`
- `IoDeleteDevice`
- `IoCreateSymbolicLink`
- `IoDeleteSymbolicLink`
- `IofCompleteRequest`
- `HalGetBusDataByOffset`
- `HalSetBusDataByOffset`

## Findings

- The executable strings identify `mydrivers.sys` and likely device naming `MyDrivers0_0_1`.
- PDB path metadata identifies a Driver Genius development path.
- This is not evidence of vendor ownership or current signing policy; it is a string/path observation.

## Unknowns

- Exact symbolic link and IOCTL values.
- Driver dispatch function mapping.
- Runtime availability.
- Target signing compatibility.
