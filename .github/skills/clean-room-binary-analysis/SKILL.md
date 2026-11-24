---
name: clean-room-binary-analysis
description: Conduct evidence-based static binary analysis and clean-room reimplementation. Activate for binary triage, disassembly, decompilation, behavior hypotheses, or when reconstructing independent implementation requirements from executable artifacts.
---

# Clean-Room Binary Analysis

## Purpose
Preserve a strict separation between observed evidence and inferred behavior, enabling independent reimplementation without source or copyright copying.

## Activation
Use when supplied with a PE/COFF, ELF, firmware image, dump, trace, or public behavior description requiring static or controlled dynamic analysis.

## Required expertise
- Binary formats, calling conventions, data/control flow, decompilers, symbol recovery, and reproducible artifact handling.

## Workflow
1. Obtain hashes and provenance; record timestamps and tool versions.
2. Inventory sections, imports, exports, resources, debug data, and target architecture.
3. Map entry points and public behavior boundaries.
4. Document concrete observations with addresses and decompiler output.
5. Form hypotheses with confidence and falsification steps.
6. Create an independent behavioral specification; do not copy decompiled source text.
7. Compare at least two analysis tools or execution traces where possible.
8. Add focused tests for confirmed behavior and marked unknowns.

## Technical references
- PE/COFF specifications; calling-convention ABI documentation; Ghidra or IDA disassembly; objdump, llvm-readobj, and symbol/dump tools.

## Expected outputs
- Evidence ledger, artifact manifest, function index, hypothesis list, unknown register/protocol list, and clean-room requirement specification.

## Validation
- Reproduce observations with independent tools, verify address bases and bitness, and test generated requirements against additional binaries or traces.

## Security restrictions
- Do not run unknown binaries on production or shared systems. No secret or credential capture. Isolate samples and avoid destructive or networked analysis.

## Known limitations
This skill cannot establish semantics absent from evidence, and it cannot infer undocumented hardware behavior reliably.
