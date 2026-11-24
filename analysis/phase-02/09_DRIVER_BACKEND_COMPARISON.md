# Driver Backend Comparison

| Property | BS_RCIO64.sys | SvIoCtrlx64.sys | mydrivers.sys |
|---|---|---|---|
| SHA256 | d205286b... | 9ade632e... | a2e11d0e... |
| PE subsystem | NT native | NT native | NT native |
| Architecture | x64 | x64 | x64 |
| Ghidra functions | 36 | 11 | 11 |
| Physical mapping | `MmMapIoSpace` | `MmMapIoSpace` | `MmMapIoSpace` |
| HAL bus data | Both imports | Both imports | Both imports |
| Packet/thread APIs | BS_RCIO only in current import set | Not in current set | Not in current set |
| Executable strings | `BS_RCIO64.sys`, `\\.\BS_RCIO` | `SvIoCtrlx64.sys`, `\\.\SvIoCtrl_1_0_0` | `mydrivers.sys`, `mydrivers` |
| Static signing evidence | Security directory present | Security directory present | Security directory present |

## Static relationships

The executable imports the Windows Service Control Manager and device I/O APIs and contains strings for all three backend names. This strongly supports that backend selection is implemented in executable code or data, but exact call-site selection is not yet established.

## Compatibility

The documentation declares:

- Seavo default.
- BS_RCIO below 4 GiB only.
- MyDrivers 64-bit physical address support.

These statements remain `CONFIRMED-DOCUMENTATION`, not hardware/runtime facts.
