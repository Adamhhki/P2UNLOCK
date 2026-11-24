# Windows CI Configuration

Created `.github/workflows/windows-build.yml`.

The workflow targets `windows-2022` and will:

- configure CMake,
- build Debug and Release,
- run CTest,
- verify PSeriesService.exe exists,
- upload app artifacts.

No GitHub Actions run is claimed here.
