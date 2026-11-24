# Installer Architecture

## Technology decision

Recommended initial installer:

- WiX Toolset MSI for install, uninstall, upgrade, repair, and SCM registration.
- PSeriesInstaller.exe as a small native Win32 status/elevation UI.

WiX is preferable to a custom installer for service registration, transaction rollback, MSI repair, upgrade codes, and uninstallation.

Native Win32 is preferable to Qt for the two-to-four installer actions.

## Installer actions

- Install
- Uninstall
- Repair
- Display status

## Elevation

The GUI requests elevation only for service installation/removal or repair.

Read-only status and version can be viewed without elevation.

## Flow

```mermaid
flowchart TD
    Start[Launch PSeriesInstaller] --> Admin{Elevation required?}
    Admin -->|No| Status[Query service status]
    Status --> Action{User action}
    Action -->|Install| Verify[Verify signed package]
    Verify --> Files[Copy own binaries]
    Files --> Register[Register service automatic/delayed]
    Register --> StartSvc[Start service]
    StartSvc --> Wait[Wait for Running]
    Wait --> Report[Show success/error]
    Action -->|Repair| Repair[Verify and replace own files]
    Action -->|Uninstall| Stop[Stop service safely]
    Stop --> Delete[Delete SCM registration]
    Delete --> Remove[Remove binaries]
    Remove --> Preserve[Preserve recovery journal]
```
