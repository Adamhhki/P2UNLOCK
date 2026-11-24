# Service Install/Uninstall Lifecycle

## Installation

1. Installer verifies elevated context.
2. Package validates signatures and file hashes.
3. MSI or equivalent creates an application directory.
4. Own binaries are copied.
5. PSeriesService.exe is registered with the local SCM.
6. Startup is Automatic Delayed Start.
7. Service failure recovery is configured.
8. Least-privilege account and access ACL are applied.
9. Service is started.
10. Installer waits for RUNNING and initial health.
11. Read-only health is reported.

## Uninstallation

1. Stop accepting hardware operations.
2. Request service stop.
3. Wait for in-process operations to reach a terminal or blocked state.
4. Block service shutdown from interrupting a journaled transaction except under an explicit compensation policy.
5. Remove or disable SCM registration.
6. Remove binaries.
7. Preserve a pending recovery journal.
8. Report preserved or removed artifacts.

## Upgrade

- preserve the service identity,
- migrate configuration,
- migrate only validated journals,
- stop before replacing binaries,
- perform start validation,
- roll back package files if service startup fails.

## Repair

Repair verifies:

- expected executable hash,
- service registration,
- startup configuration,
- permissions,
- configuration files,
- journal accessibility,
- service health.
