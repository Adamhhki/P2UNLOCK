---
name: windows-native-systems
description: Design, build, and review native Windows C++20 user-mode and OS-adjacent code. Activate for Win32 APIs, COM, Windows services, PE loading, cross-compilation, MSVC, WDK/NT concepts, or Windows error handling.
---

# Windows Native Systems

## Purpose
Apply safe, documented Windows systems patterns without assuming parity between Linux build hosts and Windows targets.

## Activation
Use for Win32, COM, Windows service, registry, SCM, WMI, ETW, PE, WDK, or MSVC/CMake work.

## Required expertise
- Windows x64 ABI, Win32 data types, handles, HRESULT/NTSTATUS, RAII, MSVC, CMake/toolchains, and service lifecycle.

## Workflow
1. Determine target: host analysis, Windows user mode, kernel mode, or firmware-adjacent.
2. Obtain primary Microsoft documentation for every API and data structure.
3. Separate synchronous and asynchronous resource lifetimes.
4. Wrap handles and scoped resources in RAII wrappers.
5. Use `std::error_code`, `HRESULT`, or `NTSTATUS` explicitly; retain diagnostic context.
6. Define secure defaults and privilege boundaries.
7. Cross-compile or analyze in Linux only where evidence permits.
8. Validate only on an appropriate Windows environment.

## Technical references
- Microsoft Win32 API, COM, PE/COFF, MSVC CMake, WDK, and Windows debugging documentation.

## Expected outputs
- Dependency map, API usage map, resource ownership design, error model, build matrix, and test plan.

## Validation
- Compiler diagnostics, static analysis, unit tests, Windows-specific integration tests, and crash/log review.

## Security restrictions
- No credential extraction, privilege escalation, unsigned-driver installation, or bypass of OS security controls.

## Known limitations
Linux cannot execute Win32 binaries or validate Windows kernel behavior. Final claims require Windows hardware/VM evidence.
