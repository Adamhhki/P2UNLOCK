# AI Skill Installation Report

## 1. Environment

- Repository: `/workspaces/P2UNLOCK`
- Git branch: `main`
- Operating system: Linux `6.8.0-1070-azure`
- Architecture: `x86_64`
- Node.js: `24.22.2`
- npm: `11.19.1`
- Git: `2.56.0`
- Disk: 32 GB volume, 12 GB used, 19 GB available
- Initial repository state: README only; no existing Copilot customizations, MCP configuration, project instructions, build manifest, or source tree
- Existing skills/customizations: none found in the repository or the searched user-level customization locations

The Linux environment is suitable for static analysis and cross-platform build design, but it cannot claim Windows user-mode, kernel, PCIe, or GPU hardware validation.

## 2. Node.js and CLI compatibility

Node.js 24.22.2 is compatible with the Skills CLI requirement. No base-image or temporary runtime changes were made.

The supported GitHub Copilot CLI identifier is `github-copilot`. An initial attempted identifier `github_copilot_vscode_agent` was rejected by the CLI.

## 3. Skills researched

The CLI searches covered reverse engineering, binary analysis, C++ development, Windows systems programming, CMake, security auditing, software testing, and technical documentation.

Additional candidates evaluated:

| Candidate | Repository | Outcome |
|---|---|---|
| `binary-triage` | `cyberkaida/reverse-engineering-assistant` | Installed |
| `cpp-pro` | `jeffallan/claude-skills` | Rejected: CLI marked critical risk and it was not needed due to original Windows/native guidance |
| `cmake` | `mohitmishra786/low-level-dev-skills` | Installed |
| `c-review` | `trailofbits/skills` | Rejected: standalone copy omitted workflow dependencies and the skill explicitly requires unsupported orchestration |
| `property-based-testing` | `trailofbits/skills` | Installed |
| `documentation-writer` | `github/awesome-copilot` | Installed |

## 4. Skills installed

External skills are available under both the CLI-managed `.agents/skills/` location and the repository's `.github/skills/` location.

| Skill | Source repository | Commit | Selection rationale |
|---|---|---|---|
| `binary-triage` | `cyberkaida/reverse-engineering-assistant` | `4bfae31a758639cab4d80704bc8884b508beacac` | Evidence-led binary survey, memory layout, imports, strings, xrefs, and controlled decompilation |
| `cmake` | `mohitmishra786/low-level-dev-skills` | `18f29518a47fda070e6ec1268cb577692fae9a10` | Target-first CMake, cross-compilation, presets, sanitizers, and out-of-source builds |
| `property-based-testing` | `trailofbits/skills` | `149d7b21f4067765b82e67029730b42d228ef4b4` | Property/invariant design and differential testing guidance |
| `documentation-writer` | `github/awesome-copilot` | `f10fdb8b2660ce85c98f220b2f1ca24653768a5c` | Diátaxis-based technical documentation and consistent structure |

## 5. Security audit

- External skill frontmatter was inspected.
- Candidate SKILL files and supporting references were inspected for shell commands and external dependencies.
- No skill containing explicit credential-exfiltration instructions was found.
- `binary-triage`, `cmake`, `property-based-testing`, and `documentation-writer` passed the CLI security assessment as Safe/Low Risk or equivalent.
- `cpp-pro` was rejected because the CLI security assessment reported a critical risk.
- `c-review` was rejected because its copied package depends on scripts and workflow agents absent from the standalone skill folder.
- No external skill scripts were executed during installation or auditing.
- External skills were not given permission to install system packages or modify credentials.
- Repositories may still change after pinning; use the recorded commit and lockfile when reproducing.

## 6. Project-specific skills created

| Skill | Coverage |
|---|---|
| `clean-room-binary-analysis` | Evidence ladder, clean-room requirements, hypothesis/falsification discipline |
| `windows-native-systems` | Windows APIs, Win32/COM/services, handles, error types, PE and WDK boundaries |
| `pcie-hardware-research` | PCIe configuration, topology, BAR/MMIO/DMA, MSI/MSI-X, vendor-document caution |
| `hardware-validation` | Hardware manifests, snapshots, test matrices, stop conditions, reproducibility |
| `transactional-recovery-engineering` | State machines, idempotency, journaling, staged commit, rollback and failure injection |
| `evidence-driven-reimplementation` | Traceable requirements, ADRs, confidence levels, independent implementation and differential validation |

## 7. Copilot configuration

Created:

- `.github/copilot-instructions.md`
- `.github/skills/<skill>/SKILL.md`

The instructions configure Copilot to:

- use the relevant skill by activation context,
- distinguish confirmed facts, findings, inferences, and unknowns,
- prefer evidence and primary specifications,
- write C++20 and target-explicit CMake,
- use RAII and explicit errors,
- create reproducible tests,
- document architectural decisions,
- avoid unnecessary dependencies,
- never claim hardware validation without hardware evidence.

No specialized agents were created because the repository is currently too small to justify agent-role duplication.

## 8. Verification

`npx skills list` successfully discovered four external project skills for the `github-copilot` agent.

Verification of `.github/skills/` found 10 skill folders and 10 valid `SKILL.md` files:

- 4 installed external skills
- 6 original project skills

All 10 SKILL files have valid `---` frontmatter containing `name` and `description`.

No duplicate names or missing descriptions were found.

No build manifest exists. Therefore, no build or source test was applicable:

- no `CMakeLists.txt`
- no `Makefile`
- no `package.json`

## 9. Capability matrix

| Area | Coverage | Primary skills |
|---|---|---|
| Static reverse engineering | Covered | `binary-triage`, `clean-room-binary-analysis` |
| Native C++20 | Covered by project rules plus CMake | `cmake`, `evidence-driven-reimplementation`, `windows-native-systems` |
| Windows API/OS internals | Covered by project-specific guidance | `windows-native-systems` |
| PCIe/hardware architecture | Covered | `pcie-hardware-research` |
| GPU diagnostics | Partial; hardware validation required | `pcie-hardware-research`, `hardware-validation` |
| Kernel/driver engineering | Guarded guidance only | `windows-native-systems`, `hardware-validation` |
| Security analysis | Partial native review guidance | `evidence-driven-reimplementation`, project instructions |
| Automated testing/debugging | Covered for properties and build/TDD workflows | `property-based-testing`, `cmake` |
| CMake/build engineering | Covered | `cmake` |
| Technical documentation | Covered | `documentation-writer`, `evidence-driven-reimplementation` |
| Transactional recovery | Covered | `transactional-recovery-engineering` |

## 10. Missing capabilities

- No source or binary artifacts exist yet, so reverse-engineering workflow validation cannot run.
- No Windows compiler/toolchain or WDK evidence environment exists in Codespaces.
- No target GPU or PCIe hardware is attached to this Linux environment.
- Kernel/driver execution and physical hardware testing remain outside this workspace.
- Security review lacks a project source tree and specialized installed native-review skill; future review must use an audited self-contained tool or a scoped independent review.

## 11. Recommended next steps

1. Add the project source or specified binary artifacts and a `CMakeLists.txt`.
2. Create Windows x64 cross-compilation and Windows host validation presets.
3. Add a hardware test manifest template and target-specific ADR directory.
4. Establish a clean-room evidence ledger before interpreting unavailable proprietary code.
5. Add only reproducible, reviewed test dependencies.
6. Perform no hardware writes or driver installation from Codespaces.
