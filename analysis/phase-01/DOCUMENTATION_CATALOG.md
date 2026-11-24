# Documentation Catalog

Evidence classification: `DOCUMENTED` means the statement appears explicitly in a supplied mirror document.

## README.zh.md

- **DOCUMENTED:** Release is Native C++ x64, MSVC C++17 `/MT`, release 4.5.
- **DOCUMENTED:** Target OS is Windows 10/11 x64 with a working NVIDIA driver.
- **DOCUMENTED:** Runtime does not require .NET, VC++ redistributable, Python, PowerShell, WMI/CIM, CUDA Toolkit, or nvidia-smi for the native executable.
- **DOCUMENTED:** Main commands include `list`, `status`, `unlock`, `widen`, `gen2`, `verify`, `recover`, `bandwidth`, `driver-diagnose`, and `self-test`.
- **DOCUMENTED:** Default unlock target is Gen2 x16; default widen target verifies actual x16; explicit `--target-width 8` requests x8.
- **DOCUMENTED:** Success requires actual negotiated width/speed and independent CUDA validation, not capability or target-register values alone.
- **DOCUMENTED:** `--allow-busy` permits active GPU work and is not guaranteed interruption-free.
- **DOCUMENTED:** Three backend drivers are named: Seavo, BS_RCIO, and MyDrivers.
- **DOCUMENTED:** Native state format is v4 and can read earlier v1/v2/v3 records.
- **DOCUMENTED:** Reported offline checks, Python differential cases, and driver ABI simulations are development evidence, not hardware evidence.
- **DOCUMENTED:** Linux/Codespaces source names include `engine.cpp`, `windows_io.cpp`, `platform.cpp`, `driver.cpp`, `driver_protocol.cpp`, `nvidia.cpp`, `tests.cpp`, and `verify_driver_abi.py`, but no source files with those names are present in the mirror collection.

## AUTO-PEG.zh.md

- **DOCUMENTED:** AutoPEG identifies Intel PEG controllers 8086:0C01, 8086:1901, and 8086:1601.
- **DOCUMENTED:** Fixed private channel-group offsets begin at 91C+n*20 for eight groups.
- **DOCUMENTED:** Controller-specific low-31-bit signatures are 6EF8AA78, 1D788838, and 2AFAD924.
- **DOCUMENTED:** 8086:1601 private support is limited to P104-100.
- **DOCUMENTED:** Private writes require exact platform, split-configuration, width, and signature conditions.
- **DOCUMENTED:** 8086:0C01 and 8086:1901 support P102/P104/P106 models as described in release notes.
- **REPORTED-EXPERIMENT:** Two platforms are reported to reach Gen2 x16 and pass independent CUDA testing.
- **REPORTED-EXPERIMENT:** H97/Broadwell P104 success is reported by the user, but no successful post-operation log was supplied.

## BACKENDS.zh.md

- **DOCUMENTED:** Seavo/SvIoCtrl is the default backend and uses 64-bit physical addresses.
- **DOCUMENTED:** BS_RCIO supports only physical addresses below 4 GiB.
- **DOCUMENTED:** MyDrivers is a 64-bit backend; the document warns that static signature checks do not prove target-machine loading.
- **DOCUMENTED:** BS_RCIO, Seavo, and MyDrivers have fixed or vendor-specific PCI/physical memory IOCTL interfaces.
- **DOCUMENTED:** Testing is read-only or synthetic for ABI emulation; target-machine load compatibility remains unverified.
- **DOCUMENTED:** X8 support is experimental and not established as an x8 repair across platforms.

## P104-X16-RESEARCH.zh.md

- **DOCUMENTED:** P104 test behavior and ROM/VBIOS observations are based on user logs and supplied binaries/text.
- **DOCUMENTED:** The VBIOS is reported to contain width and control routines, including a request-low-nibble value `2`.
- **INFERRED:** Request `2` and associated control actions are candidates for further isolated hardware experiments.
- **UNKNOWN:** Complete GP104 register semantics and a sufficient Win32 reconfiguration sequence.
- **DOCUMENTED:** Physical x16 lanes, PCB wiring, and slot configuration are not established solely by capability declarations.

## WIDTH-NEXT-EXPERIMENT.zh.md

- **DOCUMENTED:** `--diagnose` may add read-only status samples around temporary BAR/MEM and link-disable operations.
- **DOCUMENTED:** It does not add SBR, PnP, retraining, or register writes.
- **DOCUMENTED:** A real-time 88150 bit29 experiment remains an independently gated candidate.
- **REPORTED-EXPERIMENT:** EFI/VBIOS fixture work produced synthetic results; no real-hardware success is claimed.

## EXPERIMENT-HASWELL-PEG.zh.md

- **REPORTED-EXPERIMENT:** ASUS TROOPER B85 / i3-4170 / P104-100 is reported to reach Gen2 x16 and pass CUDA validation.
- **DOCUMENTED:** Private PEG changes are restricted to controller 8086:0C01 and P104-100 with VBIOS .47.
- **UNKNOWN:** Boot persistence and long-duration stability.

## EXPERIMENT-P106-BIT29.zh.md

- **DOCUMENTED:** P106-090 bit29 experiment is limited to PCI 10DE:1C09 and VBIOS 86.06.5B.00.0A.
- **DOCUMENTED:** It saves/restores bit29 and keeps a pending recovery record.
- **UNKNOWN:** Whether clearing or restoring bit29 affects actual width in target hardware.

## EXPERIMENT-VBIOS-WIDTH.zh.md

- **DOCUMENTED:** P104-100 VBIOS request2 experiment is limited to PCI 10DE:1B87 and VBIOS 86.04.7A.00.47.
- **DOCUMENTED:** `widen` verifies actual width and CUDA but does not activate Gen2.
- **UNKNOWN:** Real-hardware effect of the request and control sequence.

## PYTHON-PARITY.zh.md

- **DOCUMENTED:** It locates the Python original's width failure as being in `widen()`/`wait()` before Gen2 activation.
- **DOCUMENTED:** Reported parity compares write offsets, sizes, values, ordering, PnP, rebind, warmup, and policy operations.
- **REPORTED-EXPERIMENT:** Seven Python differential scenarios and 27 driver ABI cases are reported as passing.
- **UNKNOWN:** Whether these comparisons prove real Windows or physical-link behavior.

## LATEST-FINDINGS.zh.md

- **DOCUMENTED:** AMD 1022:15D3 examples previously reaching Gen2 x4 are distinguished from x16.
- **DOCUMENTED:** Win32 577 is documented as signature/image validation failure and not as evidence of an executable compatibility issue.
- **DOCUMENTED:** VBIOS ROM comparisons and offline EFI simulations are not hardware validation.
- **CONTRADICTORY:** V4.5/manifest claims Broadwell 1601 hardware verification are inconsistent with the explicit statement that no successful post-operation log exists.
