# Repository Structure

```text
PSeriesNative/
  CMakeLists.txt
  CMakePresets.json
  apps/
    PSeriesService/
    PSeriesInstaller/
  core/
    domain/
    application/
    hardware/
    diagnostics/
    recovery/
    transactions/
    security/
  platform/
    windows/
      service/
      discovery/
      logging/
      installation/
  integrations/
    nvidia/
  installer/
    wix/
    resources/
  tests/
    unit/
    integration/
    mocks/
  docs/
    architecture/
    user/
    developer/
  analysis/
    phase-01/
    phase-02/
    phase-03/
    phase-04/
```

## Dependencies

- Apps depend on core/application interfaces.
- Core domain has no Windows SDK dependency.
- Windows platform implements PnP, SCM, logging, and file abstractions.
- Hardware backend implementations implement narrow read-only interfaces.
- NVIDIA integration is optional and dynamically loaded.
- Installer has no hardware engine dependency.
