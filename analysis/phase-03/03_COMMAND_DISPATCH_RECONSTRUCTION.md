# Command Dispatch Reconstruction

## Dispatcher

`FUN_140044680` is confirmed by direct cross-reference to command and usage strings.

The function defaults to `help` when fewer than two arguments are supplied.

## Static dispatch branches

The following command strings reference the dispatcher:

`driver-diagnose`, `self-test`, `list`, `bandwidth`, `status`, `unlock`, `recover`, `widen`, `gen2`, `verify`, `collect-peg`.

## Options

Static cross-reference confirms:

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

## Limits

The dispatcher is mapped, but full argument normalization and internal handler-to-handler call chains remain incomplete.
