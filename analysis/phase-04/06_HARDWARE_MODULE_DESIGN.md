# Hardware Module Design

## Discovery

HardwareDiscovery:

- enumerates PnP devices,
- records vendor/device/subsystem IDs,
- records bus/device/function,
- records boot identifier,
- reads public PCI topology.

PciDiagnostics separates:

- declared capability,
- negotiated link status,
- current generation,
- width,
- training state,
- upstream/root identity.

## Hardware abstraction

Only the following initial capability classes are exposed:

- read-only PCI identity,
- public PCI configuration read,
- public NVML/CUDA diagnostic,
- explicitly approved backend read,
- future authorized write interface.

The write interface must remain absent or disabled until:

- public or vendor specification is established,
- register semantics are confirmed,
- target allowlist exists,
- rollback is proven.

No unrestricted physical-memory or kernel-memory interface is exposed.
