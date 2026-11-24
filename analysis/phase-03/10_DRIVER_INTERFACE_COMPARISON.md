# Driver Interface Comparison

| Area | BS_RCIO | Seavo | MyDrivers |
|---|---|---|---|
| Entry | 0001715c | 00015064 | 00015064 |
| Ghidra functions | 36 | 11 | 11 |
| Physical mapping imports | Yes | Yes | Yes |
| HAL bus imports | Yes | Yes | Yes |
| Packet/thread APIs | BS_RCIO set is broader | Not observed | Not observed |
| Executable string | BS_RCIO64.sys/\\.\BS_RCIO | SvIoCtrlx64.sys/\\.\SvIoCtrl_1_0_0 | mydrivers.sys |
| Dispatch/IOCTL | UNKNOWN | UNKNOWN | UNKNOWN |
| Signing/runtime compatibility | UNKNOWN | UNKNOWN | UNKNOWN |
