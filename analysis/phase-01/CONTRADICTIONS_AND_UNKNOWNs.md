# Contradictions and Unknowns

## Contradictions

### C-01 Broadwell 1601 hardware validation

- Manifest states `Broadwell1601HardwareUnlockVerified=true`.
- README says success was user-reported and no successful post-operation log was supplied.
- Classification: `CONTRADICTORY`.
- Resolution required: obtain the success log or change the manifest semantics to reported-only.

### C-02 P102/P106 support and verification

- Additional P102/P104/P105/P106 support is discussed, but P102 and Added Models are marked hardware not verified.
- Classification: `CONTRADICTORY` only where broad support wording could be read as validated success.
- Resolution: preserve a model matrix with reported, experimental, and verified labels.

### C-03 Driver compatibility

- Backends are described as statically checked, while other text warns static signatures do not prove target loading.
- Classification: `CONTRADICTORY` only if interpreted as end-to-end compatibility.
- Resolution: clearly distinguish static hash/signature state from target-machine kernel policy.

### C-04 Experimental success naming

- Directory names contain “experimental”, while some documents include successful target reports for related configurations.
- Classification: `CONTRADICTORY` if read as proof of generality.
- Resolution: tie each experiment to exact hardware and firmware evidence.

## Unknowns

1. Is the named ZIP still absent or was only the collection mirror downloaded?
2. What exact ZIP entries were never exposed?
3. Is there source code in the original ZIP?
4. What is the complete executable command parser and internal state machine?
5. What register fields and vendor algorithms have complete semantics?
6. How do private PEG writes interact with vendor firmware and different BIOS revisions?
7. Can P104/P106 reach actual x16 on the target machines described?
8. What target drivers are valid under Secure Boot/HVCI/WHQL policies?
9. Are the three `.sys` files signed for future target Windows installations?
10. Which reported success/failure logs correspond to which release binary?
11. What is the exact meaning of every manifest boolean?
12. Are source filenames named in documentation equal to actual source files in the ZIP?
13. Does the downloaded mirror differ from the ZIP manifest or archive contents?
14. Are the supplied scripts complete and untampered?
