# Executable PE Structure

## Provenance

- Target: `PSeriesUnlock.exe`
- SHA256: `875e0c7ce8ea4d732982eec1e44fd762d31014b16472e4161ec6df882c7ae249`
- Classification: `CONFIRMED-METADATA`

## Header findings

| Field | Static result |
|---|---|
| Format | PE32+ / x86-64 |
| Subsystem | Console |
| Machine | 0x8664 |
| Entry RVA | 0x4D120 |
| Image base | 0x140000000 |
| Section count | 6 |
| PE timestamp | 2026-11-06 16:32:41 UTC |
| CLR RVA/size | 0 / 0 |
| Managed .NET headers | Not present |
| Export directory | Empty |
| Delay import directory | Empty |
| TLS directory | Empty |
| Resource directory | Empty |
| Size of image | 720896 |
| Checksum field | 0 |

This is a native, unmanaged x64 executable. It is not a mixed-mode managed binary.

## Section layout

| Section | Virtual address | Raw size | Entropy |
|---|---:|---:|---:|
| `.text` | 0x1000 | 481792 | 6.3686 |
| `.rdata` | 0x77000 | 169472 | 5.3459 |
| `.data` | 0xa1000 | 23552 | 4.4337 |
| `.pdata` | 0xa8000 | 19968 | 5.7206 |
| `.fptable` | 0xad000 | 512 | 0.0000 |
| `.reloc` | 0xae000 | 5120 | 5.2767 |

No section was found with an exceptionally high `.text` entropy. This metadata does not establish whether the executable is packed.

## Other static directories

- Exception data: present
- Load configuration: present
- Base relocations: present
- Debug: present at RVA 0x90df0, but no PDB information was accessible in the mirror
- Import table: present
- IAT: RVA 0x77000
