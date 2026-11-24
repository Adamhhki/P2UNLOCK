# Input Provenance

## Expected original archive

The Phase 2 request provides:

- Name: `PSeriesUnlock-Native-AutoPEG-v4.5-win-x64.zip`
- Expected SHA256: `62362008d0b050580b9aad02f39f87c81289d1040bbdbe6feb362df983621baa`
- Expected entries: 24

## Current finding

`CONFIRMED-METADATA`: the named archive was not found anywhere in `/workspaces` or `/tmp`.

Therefore:

- No original ZIP could be SHA256 verified.
- No ZIP entry list or extracted size can be authenticated.
- No archive-integrity or traversal check can establish that mirror files came from the canonical archive.
- No mirror file can be treated as the canonical 24-entry archive.

## Static mirror files

| File | SHA256 | Static type |
|---|---|---|
| PSeriesUnlock.exe | `875e0c7ce8ea4d732982eec1e44fd762d31014b16472e4161ec6df882c7ae249` | PE32+ console x86-64 |
| BS_RCIO64.sys | `d205286bffdf09bc033c09e95c519c1c267b40c2ee8bab703c6a2d86741ccd3e` | PE32+ native x86-64 |
| SvIoCtrlx64.sys | `9ade632e54c3f5e8c75eaf636f2910bad3a8a07d6f078e48c9641d3af1fe811c` | PE32+ native x86-64 |
| mydrivers.sys | `a2e11d0eec70bf0818aeef0a9676cc4157bb34e06fbe54631eb98b51fc8d92c8` | PE32+ native x86-64 |

These hashes match the Phase 1 inventory and manifest where applicable.
