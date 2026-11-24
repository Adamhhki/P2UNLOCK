# Phase 3 Summary

## Provenance

All mirror hashes matched values reviewed before analysis:

| Target | SHA256 |
|---|---|
| PSeriesUnlock.exe | `875e0c7ce8ea4d732982eec1e44fd762d31014b16472e4161ec6df882c7ae249` |
| BS_RCIO64.sys | `d205286bffdf09bc033c09e95c519c1c267b40c2ee8bab703c6a2d86741ccd3e` |
| SvIoCtrlx64.sys | `9ade632e54c3f5e8c75eaf636f2910bad3a8a07d6f078e48c9641d3af1fe811c` |
| mydrivers.sys | `a2e11d0eec70bf0818aeef0a9676cc4157bb34e06fbe54631eb98b51fc8d92c8` |

The canonical ZIP remained unavailable.

## Deepest confirmed executable findings

- Entry RVA `0x4D120` decompiles to calls to `FUN_14004d3d0` and `FUN_14004cfa0`.
- `FUN_140044680` is the command dispatcher/help/option parser. Its string xrefs cover every documented command.
- `FUN_14000ed70` creates and manages temporary driver services.
- `FUN_140011210` stops and deletes temporary services.
- `FUN_140012c60` wraps `DeviceIoControl`, output-size validation, and failure reporting.
- `FUN_140008fe0` loads native recovery state, hashes it with BCrypt SHA-256-style `BCryptHash`, validates size/version/flags, and applies migration/validation rules.
- `FUN_14000bb40` writes state to a `.tmp` file, writes a 32-byte checksum, flushes, and atomically replaces the target.
- `FUN_14001b290` dynamically loads `nvcuda.dll` and resolves CUDA Driver API exports.
- `FUN_14001ab30` implements timed CUDA H2D/D2H transfer and buffer comparison.

## Command mapping

The command dispatcher is `FUN_140044680` at `140044680`. Command string evidence is cross-referenced for all documented commands.

Internal handler addresses are not fully reconstructed. This is explicit in `command_function_map.csv`.

## Driver dispatch

Static Ghidra inventory exists for all drivers, but direct MajorFunction/IRP/IOCTL dispatch maps remain unresolved.

No dispatch implementation is fabricated.

## Safety

No executable or driver was executed.

No command script was run.

No service was created.

No device I/O or hardware operation occurred.
