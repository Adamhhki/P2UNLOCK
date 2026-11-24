# Evidence Register

## Evidence classes

- `DOCUMENTED`: explicit written statement.
- `OBSERVED-SCRIPT`: directly visible in script source.
- `OBSERVED-METADATA`: archive/mirror or file metadata.
- `INFERRED`: evidence-supported conclusion, not independently confirmed.
- `REPORTED-EXPERIMENT`: reported but not reproduced here.
- `UNKNOWN`: cannot be established from current evidence.
- `CONTRADICTORY`: supplied records disagree.

| ID | Classification | Finding | Evidence |
|---|---|---|---|
| E-001 | OBSERVED-METADATA | Mirror contains 24 files | Complete inventory |
| E-002 | OBSERVED-METADATA | PSeriesUnlock is PE32+ x86-64 | `file` static identification |
| E-003 | OBSERVED-METADATA | Three downloaded `.sys` files are PE32+ native x64 | `file` static identification |
| E-004 | OBSERVED-METADATA | Executable SHA256 matches manifest | SHA256 comparison |
| E-005 | OBSERVED-METADATA | SvIoCtrl SHA256 matches manifest | SHA256 comparison |
| E-006 | DOCUMENTED | Release version is 4.5 | README and manifest |
| E-007 | DOCUMENTED | Native executable uses C++17 `/MT` | README and manifest |
| E-008 | DOCUMENTED | Runtime avoids .NET and VC++ redistributable | README and manifest |
| E-009 | OBSERVED-SCRIPT | CMD launchers invoke PowerShell wrappers | CMD source |
| E-010 | OBSERVED-SCRIPT | AutoPEG script requires exactly one GPU when BDF is `auto` | Collect-Z370.ps1 |
| E-011 | OBSERVED-SCRIPT | `Collect-Z370.ps1` can invoke unlock, gen2, and verify | Script source |
| E-012 | OBSERVED-SCRIPT | Failure collections generate ZIP output | Script source |
| E-013 | DOCUMENTED | Success requires width, speed, CUDA, and health verification | README and scripts |
| E-014 | REPORTED-EXPERIMENT | B85, H97, Z370, and B150 reported platform success | Research documents |
| E-015 | REPORTED-EXPERIMENT | 232+ offline checks passed | README |
| E-016 | REPORTED-EXPERIMENT | Seven Python differential cases passed | README and parity document |
| E-017 | REPORTED-EXPERIMENT | 27 driver ABI emulation cases passed | Manifest and README |
| E-018 | DOCUMENTED | Private PEG operations are strictly controller/model constrained | AutoPEG and experiment documents |
| E-019 | INFERRED | Private PEG settings affect observed width on at least reported platforms | Supported only by reported logs and firmware reverse analysis |
| E-020 | UNKNOWN | Any general hardware root cause for x4 stays | P104 and width research |
| E-021 | CONTRADICTORY | Broadwell 1601 manifest verification vs absent success log | Manifest and README |
| E-022 | UNKNOWN | Whether any mirror `.sys` loads on this or another target Windows host | No driver load performed |
| E-023 | UNKNOWN | Source code correspondence to executable | No source files supplied |
| E-024 | UNKNOWN | Authenticity or integrity of the host-provided mirror beyond calculated hashes | No trusted signing/vendor chain supplied |
