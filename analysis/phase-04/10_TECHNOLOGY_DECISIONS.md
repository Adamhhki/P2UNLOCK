# Technology Decisions

| Decision | Selected direction | Reason | Alternative |
|---|---|---|---|
| Language | C++20 | Native Windows, existing evidence, maintainability | C++/CLI was rejected |
| Build | CMake + MSVC x64 | Reproducible native builds and cross-platform core | Direct Visual Studio projects |
| GUI | Native Win32 API | Minimal install/uninstall actions | Qt Widgets rejected as unnecessary |
| Service | Native SCM APIs | Direct lifecycle control | Third-party service wrapper |
| Installer | WiX Toolset MSI | Service lifecycle, repair, upgrade, uninstall | Inno Setup simpler but less standardized |
| JSON | nlohmann-json or equivalent pinned dependency | Configuration/journal | Custom parser rejected for schema safety |
| Logging | small structured sink + Windows Event Log | Simple and auditable | Heavy logging framework |
| Unit testing | GoogleTest or doctest | Existing C++ ecosystem | Custom test harness |
| NVIDIA | Optional dynamic loading | Missing DLL must not crash service | Static dependency rejected |
| Driver | Not selected in this phase | Signing and dispatch unresolved | Reuse original SYS rejected |

## Build separation

Portable core, domain, and mock tests can compile in Linux with no Windows SDK or hardware.

Windows-only code requires MSVC/Windows SDK:

- SCM,
- PnP,
- SetupAPI,
- named pipes,
- service host,
- Event Log,
- Win32 installer UI.

WDK or hardware testing requires a separate Windows signing/validation environment.
