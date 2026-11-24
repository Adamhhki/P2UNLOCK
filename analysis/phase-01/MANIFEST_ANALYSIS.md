# Manifest Analysis

Source: `external-downloads/manifest.json`

## Declared metadata

- **OBSERVED-METADATA:** Release 4.5.
- **OBSERVED-METADATA:** Architecture x64.
- **OBSERVED-METADATA:** Language/native runtime is Native C++17 with static MSVC `/MT`.
- **OBSERVED-METADATA:** Executable SHA256 matches the downloaded PSeriesUnlock.exe.
- **OBSERVED-METADATA:** SV driver hash declared as `9ADE...`; it matches the downloaded SvIoCtrlx64.sys.
- **OBSERVED-METADATA:** Release is reported to have recovery v1/v2/v3/v4 support.
- **OBSERVED-METADATA:** Driver backends are `seavo`, `bsrcio`, and `mydrivers`.

## Supported IDs

- Mining GPU IDs: 10DE:1B07, 10DE:1B87, 10DE:1BC7, 10DE:1C07, 10DE:1C09.
- AutoPEG Intel controller IDs: 8086:0C01, 8086:1901, 8086:1601.
- P102 private AutoPEG controller IDs: 8086:0C01, 8086:1901.
- Target widths: 8 and 16.
- Default target width: 16.

## Declared capabilities

- AutoPEG available; default disabled.
- Experimental VBIOS width available but default disabled.
- Experimental P106 bit29 available but default disabled.
- `--allow-busy` available; default disabled.
- Native recovery v1-v4 supported.
- DotNet and VC++ redistributable not required.
- PowerShell not required at runtime.
- Hardware execution is false in the manifest.
- Research status read-only is true.
- Driver diagnostics read-only is true.

## Integrity differences

- **CONTRADICTORY:** Manifest declares `Broadwell1601HardwareUnlockVerified=true`, while README states this was user-reported and no successful post-operation log was supplied.
- **CONTRADICTORY:** Manifest declares `Broadwell1601ValidationSource=User reported successful unlock`, so `true` could only describe a reported claim, not independent hardware verification.
- **CONTRADICTORY:** Manifest declares `PythonDifferentialPassed=true`, `P102HardwareUnlockVerified=false`, and `AddedModelsHardwareVerified=false`.
- **CONTRADICTORY:** `DriverBinaryAbiEmulationPassed=false` contradicts no other field, but 27 ABI cases are reported by documentation. The field likely means overall declared pass status, not absence of the 27 emulation cases.
- **UNKNOWN:** Meaning of each manifest boolean if it differs from field names and release documentation.

No manifest values are validated hardware facts.
