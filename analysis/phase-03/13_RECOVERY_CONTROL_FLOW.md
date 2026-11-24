# Recovery Control Flow

## Confirmed behavior

- Recovery loading validates file existence and size.
- It rejects C# JSON.
- It supports native v1-v4 migration paths.
- It hashes and verifies 32-byte state checksum tails.
- It validates boot/device/resource/experimental fields.
- It refuses incomplete cross-binding or stale unresolved transactions.
- Atomic state replacement is implemented through temporary file plus `MoveFileExW`.

## Recovery limitation

Static evidence does not establish that cleanup restores:

- original hardware link state,
- original PCIe generation,
- original width,
- firmware state,
- GPU work state,
- complete pre-operation resource state.

The binary distinguishes temporary transaction recovery from full link rollback in strings.
