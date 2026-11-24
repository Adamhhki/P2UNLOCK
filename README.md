# P2UNLOCK

# PSeries Native

PSeries Native is an independent C++20 implementation intended to replace the reference tool with editable native source, not wrap or launch it. Current work is focused on the command-line hardware core; no installer or dashboard is being built now.

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
the run summary. It contains `PSeriesUnlockNative.exe`, `PSeriesService.exe`,
and their SHA-256 checksums. The current CLI supports a read-only PCI inventory
only; it is not an unlock build or setup installer. Development binaries are
unsigned.

## Safety scope

The original executable is not used. The native CLI currently enumerates present
PCI devices read-only and reports known P-series IDs. Its Windows location text
is not yet validated as a PCI BDF. The Seavo adapter pins the reviewed external
driver hash and relies on Windows driver-signing policy, but it is not yet
connected to the CLI or engine, and the third-party driver is not bundled. The
portable core includes a tested PCIe target planner, P-series selection, and
read-only AutoPEG profile-candidate checks. Live topology/layout validation,
transaction recovery, CUDA verification, unlock, and hardware writes are not
integrated.
