# Executable Function Classification

Ghidra inventory contains 1,887 executable functions. Address-only inventory is in `function_inventory.csv`.

## High-confidence areas

| Area | Analyst function | Address | Classification |
|---|---|---:|---|
| Command dispatcher | `FUN_140044680` | `140044680` | CONFIRMED-STATIC |
| Temporary driver lifecycle | `FUN_14000ed70` | `14000ed70` | CONFIRMED-STATIC |
| Temporary service cleanup | `FUN_140011210` | `140011210` | CONFIRMED-STATIC |
| Device I/O wrapper | `FUN_140012c60` | `140012c60` | CONFIRMED-STATIC |
| Recovery state validation/loading | `FUN_140008fe0` | `140008fe0` | CONFIRMED-STATIC |
| Recovery state writing | `FUN_14000bb40` | `14000bb40` | CONFIRMED-STATIC |
| CUDA bandwidth setup | `FUN_14001b290` | `14001b290` | CONFIRMED-STATIC |
| CUDA timed transfer | `FUN_14001ab30` | `14001ab30` | CONFIRMED-STATIC |
| GPU/engine subsystem | `FUN_14002ba00`, `FUN_14003a820` | Various | INFERRED from string xrefs; implementation incomplete |

## Compiler/runtime functions

The binary contains CRT, exception, heap, and Microsoft-generated code. Synthetic Ghidra names do not establish application names or source functions.
