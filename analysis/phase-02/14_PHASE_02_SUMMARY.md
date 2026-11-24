# Phase 2 Summary

## Toolchain

- Official Ghidra 12.2 headless analyzer verified.
- Microsoft/OpenJDK 25 available.
- Python venv created with pefile, LIEF, Capstone, yara-python, and dnfile.
- Official capa 10.0.0 and FLOSS 3.2.0 downloaded and installed locally.
- LLVM and GNU PE tools used independently.

## Archive provenance

The canonical ZIP is unavailable.

The current evidence is a 24-file downloaded mirror. This mirror cannot be certified as the canonical archive despite matching individual hashes against Phase 1 data.

No mirror executable or driver was executed.

## Executable findings

- Native unmanaged PE32+ console x64.
- CLR directory absent.
- Entry RVA 0x4D120.
- Six sections.
- 1,887 Ghidra-detected functions.
- No resource directory.
- Static imports include:
  - SetupAPI/CfgMgr
  - SCM/service management
  - registry APIs
  - `CreateFileW`/`DeviceIoControl`
  - `WinVerifyTrust`
  - Event Log APIs
  - dynamic library resolution
- Strings confirm all 11 CLI command families and backend names.
- Address-level CLI dispatch mapping is incomplete.

## Driver findings

| Driver | Ghidra functions | Core static findings |
|---|---:|---|
| BS_RCIO64.sys | 36 | Native x64; device/symbolic-link, MMIO mapping, HAL bus APIs, packet/thread imports |
| SvIoCtrlx64.sys | 11 | Native x64; device/symbolic-link, MMIO mapping, HAL bus APIs |
| mydrivers.sys | 11 | Native x64; core same as SvIoCtrl; PDB path points to MyDrivers development source path |

## Backend relationship

Strings confirm names for all three backends and device objects:

- SvIo: `SvIoCtrlx64.sys`, `\\.\SvIoCtrl_1_0_0`
- BS_RCIO: `BS_RCIO64.sys`, `\\.\BS_RCIO`
- MyDrivers: `mydrivers.sys`

Exact executable IOCTL values and cross-references remain unknown.

## CLI progress

Command and option names are confirmed statically. Handler addresses and argument-validation call chains were not established in this phase.

## Important limitations

- Canonical archive provenance is blocked.
- No PDB/source symbols exist.
- Ghidra external Windows libraries could not be linked in Linux.
- Ghidra function names are mostly synthetic.
- capa and FLOSS did not complete in the analysis window and yielded no completed result.
- Static driver imports do not establish dispatch layouts or runtime exposure.
- No hardware, kernel, signing, or Windows runtime behavior was tested.

## Execution safety

No executable or driver was run.

No script was executed.

No service was created.

No PCIe, GPU, memory, firmware, or hardware operation occurred.

## Deliverables

- [00_TOOLCHAIN_SETUP.md](/workspaces/P2UNLOCK/analysis/phase-02/00_TOOLCHAIN_SETUP.md)
- [01_INPUT_PROVENANCE.md](/workspaces/P2UNLOCK/analysis/phase-02/01_INPUT_PROVENANCE.md)
- [02_EXE_PE_STRUCTURE.md](/workspaces/P2UNLOCK/analysis/phase-02/02_EXE_PE_STRUCTURE.md)
- [03_EXE_IMPORT_AND_API_ANALYSIS.md](/workspaces/P2UNLOCK/analysis/phase-02/03_EXE_IMPORT_AND_API_ANALYSIS.md)
- [04_EXE_FUNCTION_MAP.md](/workspaces/P2UNLOCK/analysis/phase-02/04_EXE_FUNCTION_MAP.md)
- [05_CLI_TO_FUNCTION_MAPPING.md](/workspaces/P2UNLOCK/analysis/phase-02/05_CLI_TO_FUNCTION_MAPPING.md)
- [06_DRIVER_BS_RCIO_ANALYSIS.md](/workspaces/P2UNLOCK/analysis/phase-02/06_DRIVER_BS_RCIO_ANALYSIS.md)
- [07_DRIVER_SEAVO_ANALYSIS.md](/workspaces/P2UNLOCK/analysis/phase-02/07_DRIVER_SEAVO_ANALYSIS.md)
- [08_DRIVER_MYDRIVERS_ANALYSIS.md](/workspaces/P2UNLOCK/analysis/phase-02/08_DRIVER_MYDRIVERS_ANALYSIS.md)
- [09_DRIVER_BACKEND_COMPARISON.md](/workspaces/P2UNLOCK/analysis/phase-02/09_DRIVER_BACKEND_COMPARISON.md)
- [10_STRING_AND_RESOURCE_ANALYSIS.md](/workspaces/P2UNLOCK/analysis/phase-02/10_STRING_AND_RESOURCE_ANALYSIS.md)
- [11_SERVICE_AND_DEVICE_LIFECYCLE.md](/workspaces/P2UNLOCK/analysis/phase-02/11_SERVICE_AND_DEVICE_LIFECYCLE.md)
- [12_STATIC_EVIDENCE_REGISTER.md](/workspaces/P2UNLOCK/analysis/phase-02/12_STATIC_EVIDENCE_REGISTER.md)
- [13_BINARY_ANALYSIS_LIMITATIONS.md](/workspaces/P2UNLOCK/analysis/phase-02/13_BINARY_ANALYSIS_LIMITATIONS.md)
- [14_PHASE_02_SUMMARY.md](/workspaces/P2UNLOCK/analysis/phase-02/14_PHASE_02_SUMMARY.md)

## Recommended Phase 3 work

Do not begin Phase 3 without user review.
