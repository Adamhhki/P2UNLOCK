# Service Lifecycle Validation

## Portable validation

Unit tests validate configuration and logging foundations.

## Windows validation required

- `sc query PSeriesService`
- start from stopped state,
- stop and wait,
- shutdown notification,
- restart after worker failure,
- SCM service status,
- checkpoint and wait hints,
- service account behavior.
