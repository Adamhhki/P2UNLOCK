# Phase 1 Summary

## Workspace

- Workspace: `/workspaces/P2UNLOCK`
- OS: Linux
- Architecture: x86_64
- Disk: 32 GB volume, approximately 19 GB available
- Git: `main`, with initial customizations/download directory uncommitted
- ZIP extraction tools: `unzip`, `zipinfo`, `bsdtar`
- Named ZIP: not found

## Integrity

Because `PSeriesUnlock-Native-AutoPEG-v4.5-win-x64.zip` was absent, no original archive SHA256 or ZIP entry/path integrity could be calculated.

The mirror collection downloaded earlier is 24 files:

- 10 Markdown documentation files
- 1 PE32+ x64 executable
- 3 PE32+ x64 kernel drivers
- 6 CMD scripts
- 3 PowerShell scripts
- 1 JSON manifest

No small files or entries were omitted from the mirror inventory.

## Important discoveries

- The executable and scripts describe a native C++17 release.
- Supported GPU IDs are P102-100, P104-100/101, P106-100/090.
- Private PEG support is narrow and controller/firmware specific.
- Default unlock claims Gen2 x16; width and speed are separately measured.
- Native recovery uses a v4 state format and has temporary transaction semantics.
- Third-party drivers are separate selectable backends.
- No source files are present in the mirror collection.

## Script dependency findings

- All CMD files delegate to PowerShell scripts except direct launch patterns.
- `Collect-Z370.ps1` is the main orchestration script.
- It calls native `list`, `status`, `unlock`, `gen2`, and `verify` commands.
- `Collect-SplitPEG.ps1` is read-only collection.
- `Test-Bandwidth.ps1` calls native CUDA bandwidth testing.
- No script or executable was run.

## Feature map

Documented or visibly referenced command families include list, status, collect-peg, unlock, widen, gen2, verify, recover, bandwidth, driver-diagnose, and self-test.

Internal implementation remains unknown.

## Contradictions

The main contradiction is manifest-level `Broadwell1601HardwareUnlockVerified=true` versus the user-reported-only explanation and missing successful post-operation log.

Other contradictions require separating static signature checks, ABI emulation, offline parity, reported experiments, and real-hardware validation.

## No source-code finding

No C++, C, header, Python, C#, build script, project file, or original source archive was found in the mirror collection.

Documentation names source filenames but this does not establish that source files exist.

## Execution safety

No PSeriesUnlock executable, CMD script, PowerShell script, or SYS driver was executed, loaded, or installed.

No PCIe write or Windows service operation occurred.

## Deliverables

- [ARCHIVE_INVENTORY.md](/workspaces/P2UNLOCK/analysis/phase-01/ARCHIVE_INVENTORY.md)
- [DOCUMENTATION_CATALOG.md](/workspaces/P2UNLOCK/analysis/phase-01/DOCUMENTATION_CATALOG.md)
- [SCRIPT_CATALOG.md](/workspaces/P2UNLOCK/analysis/phase-01/SCRIPT_CATALOG.md)
- [MANIFEST_ANALYSIS.md](/workspaces/P2UNLOCK/analysis/phase-01/MANIFEST_ANALYSIS.md)
- [PRELIMINARY_FEATURE_MAP.md](/workspaces/P2UNLOCK/analysis/phase-01/PRELIMINARY_FEATURE_MAP.md)
- [EVIDENCE_REGISTER.md](/workspaces/P2UNLOCK/analysis/phase-01/EVIDENCE_REGISTER.md)
- [CONTRADICTIONS_AND_UNKNOWNs.md](/workspaces/P2UNLOCK/analysis/phase-01/CONTRADICTIONS_AND_UNKNOWNs.md)
- [PROJECT_REQUIREMENTS.md](/workspaces/P2UNLOCK/analysis/phase-01/PROJECT_REQUIREMENTS.md)
- [PHASE_01_SUMMARY.md](/workspaces/P2UNLOCK/analysis/phase-01/PHASE_01_SUMMARY.md)

## Next phase recommendation

Obtain and hash the actual ZIP. If the ZIP contains no source code, the next allowed phase is static binary metadata and clean-room reverse analysis on a separate Windows-only analysis environment.
