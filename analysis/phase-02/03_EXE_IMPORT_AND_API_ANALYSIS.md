# Executable Import and API Analysis

No import is considered evidence of runtime use unless a cross-reference or analyzed decompilation confirms it. The following APIs are confirmed to be statically imported.

## Service-control and temporary services

Imports include:

- `OpenSCManagerW`
- `CreateServiceW`
- `StartServiceW`
- `ControlService`
- `QueryServiceConfigW`
- `DeleteService`
- `CloseServiceHandle`
- `RegOpenKeyExW`, `RegQueryValueExW`, `RegSetValueExW`, `RegDeleteValueW`, `RegGetValueW`

Classification: `CONFIRMED-STATIC`.

Limitation: the import table does not prove a service is always created or which generated name is used. Generated names are visible in strings but call-site evidence remains a follow-up item.

## Device and resource discovery

Imports include SetupAPI and CfgMgr APIs:

- `SetupDiGetClassDevsW`
- `SetupDiEnumDeviceInfo`
- `SetupDiGetDeviceRegistryPropertyW`
- `SetupDiGetDeviceInstanceIdW`
- `SetupDiSetClassInstallParamsW`
- `SetupDiCallClassInstaller`
- `CM_Locate_DevNodeW`
- `CM_Get_Parent`
- `CM_Get_Device_IDW`
- `CM_Get_DevNode_Status`

Classification: `CONFIRMED-STATIC`.

## Device I/O

- `CreateFileW`
- `DeviceIoControl`
- `ReadFile`
- `WriteFile`
- `CloseHandle`

Classification: `CONFIRMED-STATIC`.

The executable can perform ordinary file/device handles and IOCTL calls, but the specific IOCTL values and call sites remain to be mapped.

## Signature and diagnostics

- `WinVerifyTrust`
- `BCryptHash`
- Event Log APIs (`EvtNext`, `EvtRender`, `EvtQuery`, `EvtClose`)

Classification: `CONFIRMED-STATIC`.

The presence of `WinVerifyTrust` and `BCryptHash` supports documented driver-hash/signature and log-hash behaviors; it does not prove successful verification or kernel-policy acceptance.

## Console and file I/O

The executable imports extensive KERNEL32 APIs for console output, mutexes, file operations, system firmware table access, dynamic library loading, and process/module metadata.

Notable dynamic-library imports:

- `LoadLibraryExW`
- `GetProcAddress`
- `GetModuleHandleW`

Strings confirm likely dynamic resolution of `nvml.dll` and `nvcuda.dll`, but dynamic resolution still requires call-site corroboration.
