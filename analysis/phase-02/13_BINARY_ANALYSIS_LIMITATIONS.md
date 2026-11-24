# Binary Analysis Limitations

## Input limitations

- Canonical ZIP unavailable.
- SHA256 of mirror files cannot establish ZIP provenance.
- Phase 2 may differ from files in the canonical ZIP.

## PE limitations

- No PDB or source symbols.
- Ghidra detected functions but most names are synthetic.
- Large C++ binaries require manual xref/decompile mapping.
- Import presence does not prove call reachability.
- String presence does not prove execution.

## Ghidra limitations

- Ghidra auto-analysis could not find external Windows libraries in Linux.
- Decompiler parameter analysis was successful for the executable but still requires manual confirmation.
- One decompiler read warning was observed at address `14004c810`.
- The driver analyses were separate and function counts are preliminary.

## Heuristic tool limitations

- Capa and FLOSS processes were stopped because they did not complete within the selected execution window.
- They produced no completed Phase 2 result and must not be presented as success.

## Runtime limitations

No binary or driver was executed or loaded.

No:

- IOCTL call,
- PCIe write,
- physical memory read/write,
- PnP operation,
- GPU reset,
- link-width change,
- VBIOS change,
- Windows service installation,
- Secure Boot/HVCI bypass,
- kernel signing bypass

was performed.
