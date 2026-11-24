# Phase 4 Summary

## Product summary

PSeries Native is a permanently installed Windows service whose only user-facing component is a minimal installer/uninstaller GUI.

The GUI, PSeriesInstaller.exe, may install, uninstall, repair, report status, and request elevation. It is not a hardware dashboard or control application.

The actual application, PSeriesService.exe, performs:

- read-only hardware discovery at startup,
- recovery-journal validation,
- configured workflow evaluation,
- optional authorized hardware operations,
- structured local logging,
- interrupted-operation recovery.

## Architecture

- PSeriesInstaller.exe: native Win32 installer GUI.
- PSeriesService.exe: Windows service executable.
- PSeriesCore: platform-neutral domain/application/transaction logic.
- PSeriesPlatformWindows: SCM, SetupAPI, PnP, logging, and file integration.
- PSeriesHardware: PCI topology and backend abstraction.
- PSeriesNvidia: optional NVML/CUDA integration.
- PSeriesRecovery: journal, migration, validation, rollback.

## Startup policy

Automatic boot startup is read-only by default.

The service may:

- enumerate devices,
- validate configuration,
- inspect recovery journals,
- establish service health,
- report unsupported or missing hardware,
- defer hardware work.

It must not write PCI configuration, reset GPU, retrain links, load a modifying third-party driver, or perform unlock/widen operations without:

- enabled configuration,
- exact hardware eligibility,
- operator approval persisted as configuration,
- complete precondition checks,
- complete snapshot and rollback journal,
- Windows hardware validation.

## Evidence boundary

The architecture is based on Phase 1–3 evidence, but:

- the canonical ZIP is unavailable,
- mirror binaries are not canonical release binaries,
- PCIe register semantics remain unresolved,
- driver IOCTL and dispatch structures remain unresolved,
- real Windows/hardware behavior remains unvalidated.

## Deliverables

Sixteen design reports are created under `analysis/phase-04/`.
