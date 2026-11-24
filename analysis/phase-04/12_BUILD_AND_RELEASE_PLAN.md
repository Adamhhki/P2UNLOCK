# Build and Release Plan

## Outputs

- PSeriesService.exe
- PSeriesInstaller.exe
- PSeries MSI package

Optional PSeriesCLI.exe is not required for the first release.

## Configurations

- Debug
- RelWithDebInfo
- Release

## Build targets

Codespaces may build portable mocks and unit tests only.

Windows GitHub Actions runners compile x64 MSVC artifacts and run Windows integration tests.

No claim of Windows build success is inferred from Linux compilation.

## Signing

- own executables signed,
- MSI signed,
- third-party dependencies pinned,
- any privileged driver signed and separately released,
- no unsigned SYS packaged automatically.

## Release requirements

- reproducible version metadata,
- immutable release manifest,
- checksum/SHA256,
- service upgrade codes,
- uninstaller verification,
- journal migration tests.
