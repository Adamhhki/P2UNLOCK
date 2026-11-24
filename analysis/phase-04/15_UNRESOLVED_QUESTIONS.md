# Unresolved Questions

1. Canonical ZIP and original release provenance.
2. Real PnP and Windows driver lifecycle for the proposed service account.
3. Public-specified or vendor-confirmed PCIe write registers.
4. Kernel driver requirement and signing strategy.
5. Driver IOCTL values and dispatch layouts.
6. Exact hardware allowlist and firmware matrix.
7. Safe idle/precondition policy.
8. Boot timing and PnP settle behavior.
9. Real Windows service account compatibility.
10. NVML/CUDA availability and cleanup semantics.
11. Permanent service failure recovery policy.
12. Recovery proof for physical link state.
13. Upgrade/journal migration compatibility.
14. Installer elevation and ACL requirements.

No unresolved item may be silently implemented as a hardware write.
