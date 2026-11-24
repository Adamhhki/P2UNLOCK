# CLI to Function Mapping

## Confirmed command strings

Static strings confirm the following commands:

- `list`
- `status`
- `collect-peg`
- `unlock`
- `widen`
- `gen2`
- `verify`
- `recover`
- `bandwidth`
- `driver-diagnose`
- `self-test`

These are `CONFIRMED-STATIC` string evidence.

## Confirmed option strings

Static strings confirm:

- `--bdf`
- `--load-driver`
- `--backend`
- `--allow-busy`
- `--target-width`
- `--diagnose`
- `--research`
- `--state`
- `--driver`
- `--auto-peg`
- `--experimental-vbios-width`
- `--experimental-width-bit29`
- `--experimental-width-cycle`

## Usage text

Embedded usage text documents direct command syntax for bandwidth, collect-peg, verify, widen, gen2, status, unlock, and recover.

## Mapping limitations

- Strings do not prove dispatch address or argument parsing.
- No source PDB or source symbols are available.
- Ghidra functions are largely unnamed.
- The command parser and each command handler require cross-reference analysis with named code addresses in Phase 3.
