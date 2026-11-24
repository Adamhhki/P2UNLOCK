# Feature Traceability

| Original feature | Evidence | PSeries module | Behavior | Status |
|---|---|---|---|---|
| list | Documented and binary string | HardwareDiscovery | Read-only | READ-ONLY FIRST |
| status | Documented and binary string | PciDiagnostics/NvidiaDiagnostics | Read-only | READ-ONLY FIRST |
| collect-peg | Script and binary string | PciTopology | Read-only collection | REQUIRES MORE RESEARCH |
| unlock | Documented and binary xrefs | AutoPegEngine/TransactionManager | Modifying | BLOCKED BY MISSING EVIDENCE |
| widen | Documented and binary strings | Hardware operation interface | Modifying | BLOCKED BY MISSING EVIDENCE |
| gen2 | Documented and binary strings | Verification/AutoPegEngine | Modifying or verification | REQUIRES MORE RESEARCH |
| verify | Documented and binary strings | NvidiaDiagnostics/PciDiagnostics | Read-only and CUDA test | READ-ONLY FIRST |
| recover | State implementation in binary | RecoveryManager | Software and guarded compensation | REQUIRES HARDWARE VALIDATION |
| bandwidth | Decompiled CUDA function | NvidiaDiagnostics | CUDA memory transfer | READ-ONLY FIRST |
| driver-diagnose | Documented and binary string | Platform diagnostics | Read-only | READ-ONLY FIRST |
| self-test | Documented and binary string | Core test runner | Internal validation | PLANNED |
