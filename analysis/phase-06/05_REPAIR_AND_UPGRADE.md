# Repair and Upgrade

Repair is covered by the lifecycle integration script:

- MSI `/fa`
- verify executable restored
- verify service remains registered

Upgrade uses:

- stable UpgradeCode,
- package and package version replacement,
- MajorUpgrade,
- schedule after InstallExecute.

Upgrade persistence testing remains required.
