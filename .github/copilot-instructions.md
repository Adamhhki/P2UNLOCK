# P2UNLOCK Engineering Instructions

## Scope and evidence
- Treat this repository as a clean-room implementation project. Do not claim correspondence with unavailable source code; derive behavior only from supplied evidence or independently established public specifications.
- Separate confirmed facts, static-analysis findings, engineering inferences, and unknown behavior in every technical conclusion.
- Cite exact binary addresses, offsets, source locations, public specifications, or test records. Label dates and tool versions.
- Never claim hardware validation without execution on the named target hardware and a reproducible test record.

## Skill use
- Automatically apply relevant repository skills:
  - reverse engineering or binary analysis: `binary-triage`, `clean-room-binary-analysis`
  - C++20, CMake, debugging, or build engineering: `windows-native-systems`, `cmake`, `property-based-testing`
  - PCIe or GPU work: `pcie-hardware-research`, `hardware-validation`
  - recovery or rollback design: `transactional-recovery-engineering`
  - architecture and implementation synthesis: `evidence-driven-reimplementation`
  - technical writing: `documentation-writer`
- Consult external skills without exposing or persisting credentials.

## Implementation standards
- Produce maintainable C++20 code with target-explicit CMake projects.
- Prefer RAII, scoped handles, `std::span`, `std::expected` or repository-standard result types, and explicit error propagation.
- Prefer native Windows APIs and documented contracts. Never assume a register, driver protocol, undocumented PCIe behavior, or GPU behavior.
- Enable compiler warnings and appropriate static analysis. Use sanitizers for portable code and record that Windows kernel or hardware tests are not possible in Linux unless evidence says otherwise.
- Avoid unnecessary dependencies. Pin dependency baselines and preserve manifest-based reproducible builds.
- Use narrowly scoped changes and preserve existing behavior.

## Testing and verification
- Create unit, property, differential, and integration tests where the evidence supports each level.
- Test rollback and failure injection in a separate VM or guarded target environment before hardware use.
- Separate host analysis, Linux build verification, Windows user-mode validation, and Windows kernel/hardware validation.
- Never install a driver or access hardware directly on an untrusted or production system.
- For differential testing, define the oracle, input corpus, tolerances, environmental assumptions, and failure severity.
- Record builds, hashes, test commands, exit status, and hardware observations.

## Research and documentation
- Research public specifications before implementation. Prefer primary sources and vendor documentation.
- Record an evidence trail and important architectural decisions (ADR).
- Distinguish public/third-party facts from project-specific observations.
- Document unknowns, risks, mitigations, and rollback plans.
- Do not add or execute scripts merely because they are present in an external skill.
