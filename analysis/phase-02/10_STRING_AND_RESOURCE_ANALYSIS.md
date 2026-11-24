# String and Resource Analysis

## PE resources

The executable has no resource directory entries. Static resource extraction therefore found no icon, manifest, version resource, or embedded dialog resource.

## CLI and error strings

Confirmed static strings include command names, usage text, validation errors, recovery messages, and backend failures.

Representative evidence groups:

- Recovery: `Native v4 recovery version invalid`, `Incomplete transaction: run recover first`
- PCI: `PCI write outside whitelist`, `PCI write outside whitelist`
- MMIO: `MMIO read outside whitelist`, `MMIO write outside policy whitelist`
- Backend: `Backend must be seavo, bsrcio or mydrivers`
- Busy: `GPU has active clients`
- AutoPEG: `Z370 PEG group pattern differs from collected profile`
- Verification: `verify ... link/CUDA only, no reset or register writes`

## Backend and library strings

- `SvIoCtrlx64.sys`
- `\\.\SvIoCtrl_1_0_0`
- `BS_RCIO64.sys`
- `\\.\BS_RCIO`
- `mydrivers.sys`
- `nvml.dll`
- `nvcuda.dll`

## String limitations

A static string does not prove runtime use. String-address xrefs are required before a string can be assigned to a command handler or hardware operation.
