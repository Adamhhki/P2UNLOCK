---
name: pcie-hardware-research
description: Research PCIe and GPU hardware interfaces using public specifications and observed evidence. Activate for BAR mapping, configuration space, enumeration, DMA, PCIe capabilities, vendor device behavior, or GPU diagnostics.
---

# PCIe Hardware Research

## Purpose
Create grounded PCIe and GPU integration designs from specifications and reproducible observations.

## Activation
Use for PCI configuration, BARs, device classes, capabilities, MSI/MSI-X, DMA, bus topology, GPU diagnostics, or vendor register questions.

## Required expertise
- PCIe enumeration, MMIO, DMA, interrupts, Windows device interfaces, and conservative hardware safety.

## Workflow
1. Record vendor ID, device ID, revision, subsystem IDs, bus location, link state, BAR layout, and firmware/tool versions.
2. Separate public base-spec facts from vendor-specific documentation.
3. Consult primary specifications and vendor documentation.
4. Map read/write effects: configuration, MMIO, DMA, and side effects.
5. Identify prerequisites and privilege requirements.
6. Propose guarded read-only discovery before writes.
7. Add transaction snapshots and rollback conditions.
8. Mark unknown register semantics as unknown.

## Technical references
- PCI-SIG architecture and base/specification documents, PCI Local Bus and Windows Driver Kit documentation, vendor public manuals.

## Expected outputs
- Evidence matrix, device topology, capability map, register evidence table, risk register, and hardware test plan.

## Validation
- Repeatable enumeration and read-only scans, Linux `lspci`/Windows PnP comparison, and written before/after snapshots.

## Security restrictions
- No blind register writes, memory clearing, firmware flashing, or high-risk hardware operations without explicit authority and rollback.

## Known limitations
Public specs do not establish undocumented vendor behavior or firmware-dependent register semantics.
