# P2UNLOCK

# PSeries Native

PSeries Native is an independent C++20 foundation for a Windows background service and conventional MSI installer.

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
the run summary. It contains the MSI installer, service executable, and MSI
SHA-256 checksum. The current development build is unsigned.

## Safety scope

No original executable, script, driver, hardware operation, PCIe write, GPU reset, VBIOS change, or firmware operation is part of the current implementation.