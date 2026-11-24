# Security Model

## Least privilege

The permanent service should begin with a dedicated, restricted service account or `LocalService`, selected after Windows API and hardware requirements are evaluated.

`LocalSystem` is the fallback only if a documented Windows kernel or hardware capability cannot operate under a less privileged account.

## Privileges

Only explicitly required privileges should be granted. Initial read-only discovery should not require hardware-administration privileges beyond normal PnP/API access.

Hardware modification later may require:

- administrator-run setup,
- service identity authorization,
- signed privileged component,
- separate device ACL,
- WDK-signing policy.

## IPC

No IPC is required for the minimal installer. Status should use SCM APIs and signed local service health files or Event Log.

If an optional local status channel is later added, it must use Named Pipes or RPC with:

- local-only endpoint,
- authenticated client identity,
- restrictive ACL,
- no privileged hardware request without elevation,
- protocol version and request IDs.

## Threat boundaries

- corrupted configuration,
- corrupted journal,
- malicious state file,
- service restart during transaction,
- DLL search-order attack,
- unsigned dependency,
- unauthorized SCM or executable replacement,
- service account escalation,
- hardware mismatch,
- third-party driver load.

## Prohibited actions

- disable Secure Boot,
- disable HVCI or Memory Integrity,
- bypass Authenticode,
- silently load unsigned drivers,
- use reference executable as backend,
- provide arbitrary kernel or physical-memory IOCTL,
- perform automatic boot hardware writes.
