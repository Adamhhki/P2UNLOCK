---
name: evidence-driven-reimplementation
description: Synthesize independent native implementations from evidence, public specifications, and measured behavior. Activate for architecture decisions, clean-room specifications, or reimplementing unavailable source.
---

# Evidence-Driven Reimplementation

## Purpose
Convert multiple evidence classes into a maintainable independent implementation plan without presenting inference as fact.

## Activation
Use after analysis findings exist or while designing a public-Specification-first implementation.

## Required expertise
- Technical architecture, C++20, Windows internals, differential testing, and uncertainty management.

## Workflow
1. Define the externally observable contract.
2. Build an evidence table: source, claim, address/spec section, confidence, contradictions.
3. Separate confirmed behavior from intentional interpretation.
4. Define module boundaries and interface ownership.
5. Choose public-standard algorithms before reverse-engineered shortcuts.
6. Create acceptance tests from confirmed behavior.
7. Create differential tests with an approved oracle.
8. Document all unsupported features as not implemented.

## Technical references
- Project evidence ledger, public standards, vendor documentation, CMake and C++ architecture guidance.

## Expected outputs
- Requirement specification, architecture diagram/description, ADR set, test plan, traceability matrix, and unknown list.

## Validation
- Trace each requirement to evidence and test; run independent code review and differential checks where legal and available.

## Security restrictions
- Do not reuse proprietary source text or recreate protected content without legal authority. Do not present inferred behavior as specification.

## Known limitations
The resulting implementation may differ where evidence is incomplete or target behavior is proprietary.
