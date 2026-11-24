# Release and Signing Strategy

No signing certificate or password is stored.

Development builds remain unsigned unless signed externally.

Before release:

- sign PSeriesService.exe,
- sign PSeries Native MSI,
- maintain release hashes,
- document certificate identity,
- document upgrade identity,
- use no original executable or SYS file.
