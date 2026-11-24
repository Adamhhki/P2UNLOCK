# Product Scope

## In scope

- Permanently registered PSeries Windows service.
- Automatic SCM startup.
- Read-only hardware discovery.
- Optional NVIDIA diagnostics.
- Recovery journal and interrupted-operation detection.
- Minimal installer and uninstaller.
- Independent C++20 source and builds.
- Structured local log and Event Log integration.

## Explicitly out of scope

- GPU dashboard.
- PCIe monitoring UI.
- Device selection UI.
- Hardware operation menu.
- System tray application.
- Wrapping PSeriesUnlock.exe.
- Running original CMD or PowerShell.
- Redistributing original SYS drivers.
- Automatic hardware writes.
- Driver signing or Secure Boot changes.

## Product identity

The installer and service do not depend on any original executable or script.

No original binary becomes a hidden backend.
