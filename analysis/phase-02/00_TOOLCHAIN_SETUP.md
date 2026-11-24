# Toolchain Setup

## Installed and verified

| Tool | Version | Method | Official source | Verification |
|---|---|---|---|---|
| Ghidra | 12.2 build 20261016 | Official ZIP download | https://github.com/NationalSecurityAgency/ghidra | `analyzeHeadless` started; SHA256 matched official release |
| Java/JDK | OpenJDK 25.0.5.0.2 Microsoft build | Preinstalled | Microsoft/OpenJDK | `java -version`, `javac -version` |
| pefile | 2024.8.26 | Python venv | https://pypi.org/project/pefile/ | Imported and parsed all four binaries |
| LIEF | 1.0.0 | Python venv | https://github.com/lief-project/LIEF | Parsed all four PE binaries |
| Capstone | 5.0.7 | Python venv | https://github.com/capstone-engine/capstone | Imported successfully |
| yara-python | 4.5.4 | Python venv | https://pypi.org/project/yara-python/ | Built and imported successfully |
| dnfile | 0.18.0 | Python venv | https://pypi.org/project/dnfile/ | Imported successfully |
| capa | 10.0.0 | Official Linux release ZIP | https://github.com/mandiant/capa | `capa --version` |
| FLOSS | 3.2.0 | Official Linux release ZIP | https://github.com/mandiant/flare-floss | `floss --help` |
| LLVM tools | 18.x | Preinstalled system package | Ubuntu LLVM package | `llvm-readobj`, `llvm-objdump` |
| GNU binutils | 2.42 | Preinstalled system package | Ubuntu binutils | `objdump`, `strings`, `readelf` |
| jq | 1.7.1 | Preinstalled | Ubuntu package | Available |
| file | 2.45.0 | Preinstalled | Ubuntu package | Used for PE classification |
| xxd | Preinstalled | Ubuntu package | Available |

## Isolated environment

- Virtual environment: `.venv-analysis/`
- Ghidra: `.analysis-tools/ghidra/ghidra_12.2_PUBLIC/`
- Ghidra project: `analysis/ghidra-project/PSeriesPhase02/`
- Raw tool output: `.analysis-output/`

## Official archive verification

- Ghidra ZIP SHA256: `2c2cd776db3c1f6a097ba418922378ac3649cadd5e844a6f5f088ae628a7be67`
- Official expected SHA256 was published with Ghidra 12.2 release metadata and matched.
- capa ZIP SHA256: `96cb5115f495024a478b0e9f9f77f9027058155589235fbd4c50e7382055fcca`
- FLOSS ZIP SHA256: `c449366960b688769b6510662cd6db6a3bf9edada4e8a8878056becd324df52c`

## Failed or unavailable

- Apt could not write `/var/lib/apt/lists/partial` without elevated package-manager permissions. It did not prevent static analysis.
- p7zip, YARA CLI, and Ninja were not installed because package installation requires unavailable apt write permission. `bsdtar` was available and extracted official archives, and `yara-python` was installed.
- Rizin was not installed because it was redundant to Ghidra plus LLVM/objdump.

## Execution restrictions

All binaries were imported or parsed statically. None was run, loaded, or used to issue hardware operations.
