# Static Evidence Register

| Finding ID | Target | Evidence | Classification | Confidence | Limitation |
|---|---|---|---|---|---|
| P2-E001 | PSeriesUnlock.exe | Native PE32+ x64, CLR directory absent | CONFIRMED-METADATA | High | Mirror provenance unverified |
| P2-E002 | PSeriesUnlock.exe | Entry RVA 0x4D120, 1887 Ghidra functions | CONFIRMED-STATIC | High | No PDB/source |
| P2-E003 | PSeriesUnlock.exe | SCM, registry, SetupAPI, DeviceIoControl imports | CONFIRMED-STATIC | High | API presence not call proof |
| P2-E004 | PSeriesUnlock.exe | `nvml.dll` and `nvcuda.dll` static/dynamic strings | CONFIRMED-STATIC | High | No resolved call xrefs |
| P2-E005 | PSeriesUnlock.exe | CLI command strings | CONFIRMED-STATIC | High | No command handler mapping |
| P2-E006 | PSeriesUnlock.exe | All three backend names and device names | CONFIRMED-STATIC | High | Protocol unknown |
| P2-E007 | BS_RCIO64.sys | Native x64, entry 0x715c, 36 functions | CONFIRMED-STATIC | High | IRP/IOCTL pending |
| P2-E008 | BS_RCIO64.sys | MmMap/MmUnmap/HAL bus imports | CONFIRMED-STATIC | High | Imported API reachability unknown |
| P2-E009 | SvIoCtrlx64.sys | Native x64, 11 functions | CONFIRMED-STATIC | High | Dispatch unknown |
| P2-E010 | SvIoCtrlx64.sys | Device/symbolic-link/MMIO imports | CONFIRMED-STATIC | High | Symbolic link details unknown |
| P2-E011 | mydrivers.sys | Native x64, 11 functions | CONFIRMED-STATIC | High | Dispatch unknown |
| P2-E012 | mydrivers.sys | PDB path and Kingsoft certificate resources | CONFIRMED-METADATA | Medium | External ownership inference prohibited |
| P2-E013 | Archive | Canonical ZIP missing | UNKNOWN | High | Provenance blocked |
