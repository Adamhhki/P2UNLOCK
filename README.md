# P2UNLOCK

# PSeries Native

PSeries Native is an independent C++20 foundation for a Windows background service. The planned user-facing installer is a small native setup executable; no MSI or GUI installer is currently built.

## Linux portable build

```bash
cmake -S . -B build/linux-core -DBUILD_TESTING=ON
cmake --build build/linux-core
ctest --test-dir build/linux-core --output-on-failure
```

## Windows build

Run on a real Windows x64 environment with MSVC and the Windows SDK:

```powershell
cmake --preset windows-msvc-x64
cmake --build build/windows-msvc-x64 --config Debug
cmake --build build/windows-msvc-x64 --config Release
ctest --test-dir build/windows-msvc-x64 -C Debug --output-on-failure
```

## Download a Windows CI build

The `Windows native build` workflow runs on pushes and pull requests. To start it
manually, open **Actions → Windows native build → Run workflow** on GitHub.
After a successful run, download the `PSeriesNative-windows-x64` artifact from
the run summary. It contains `PSeriesService.exe` and its SHA-256 checksum. This
is the service binary, not a setup installer. The current development build is
unsigned.

## Safety scope

The original executable and scripts are not used. The Windows source now has an
on-demand Seavo adapter that pins the external driver hash and relies on Windows
to enforce driver-signing policy; the third-party driver is not bundled. The
adapter is not yet connected to the service or an unlock engine. The portable
core includes a tested PCIe target planner, P-series selection, and read-only
AutoPEG profile-candidate checks. Hardware discovery, live layout and
width-map validation, device-health checks, transaction recovery, and CUDA
verification are not integrated. No hardware writes are performed.
