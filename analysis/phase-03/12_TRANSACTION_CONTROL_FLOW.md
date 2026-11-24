# Transaction Control Flow

## State loading

`FUN_140008fe0`:

- checks whether the state file exists,
- rejects C# JSON/mismatched size,
- validates size for v1-v4 layouts,
- verifies a 32-byte tail checksum,
- copies valid records into a larger in-memory layout,
- validates version and experimental fields,
- rejects unsafe combinations.

## State writing

`FUN_14000bb40`:

- derives the parent directory,
- creates directories,
- writes state to a `.tmp` file,
- writes 0x1750 bytes,
- hashes it with BCrypt,
- writes a 32-byte hash,
- flushes file buffers,
- closes it,
- calls `MoveFileExW(..., 9)` for replace semantics.

## State machine gap

Detailed unlock/widen/gen2/verify state transitions remain in `FUN_14002ba00`, `FUN_14003a820`, and related functions. Those call paths require focused graph/decompile work before implementation.
