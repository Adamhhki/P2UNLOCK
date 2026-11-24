# NVIDIA Runtime Control Flow

## Confirmed dynamic loading

`FUN_14001b290` calls `LoadLibraryExW(L"nvcuda.dll", ..., 0x800)` and resolves:

- `cuInit`
- `cuDeviceGetByPCIBusId`
- `cuDeviceGetName`
- `cuCtxCreate_v2`
- `cuCtxDestroy_v2`
- `cuMemAlloc_v2`
- `cuMemFree_v2`
- `cuMemAllocHost_v2`
- `cuMemFreeHost`
- `cuMemcpyHtoD_v2`
- `cuMemcpyDtoH_v2`
- `cuCtxSynchronize`

## Confirmed timed transfer behavior

`FUN_14001ab30`:

- synchronizes before and after timed transfer,
- uses `QueryPerformanceCounter`,
- calculates decimal GB/s,
- performs H2D or D2H transfer,
- validates transferred buffer content,
- reports each transfer sample.

## NVML

Static strings/import resolution confirm NVML export names, including initialization, PCI bus lookup, device utilization, process lists, VBIOS, driver version, and PCIe link values.

The exact NVML call graph remains incomplete.

## Unknown

- All runtime sequencing at implementation address level.
- GPU selection failure handling.
- Live CUDA context behavior.
- Hardware performance claims.
