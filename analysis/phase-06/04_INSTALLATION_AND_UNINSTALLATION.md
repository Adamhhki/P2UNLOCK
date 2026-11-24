# Installation and Uninstallation

## Installation

WiX installs PSeriesService.exe, registers PSeriesService, starts it at install, and uses LocalService.

## Uninstallation

`ServiceControl` stops on both install/remove and removes the service on uninstall.

Windows Installer removes the component and executable.

Integration verification remains on a Windows runner.
