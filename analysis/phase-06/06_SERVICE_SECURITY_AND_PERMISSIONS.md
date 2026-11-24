# Service Security and Permissions

The service account is `NT AUTHORITY\LocalService`.

Reason:

- avoids LocalSystem,
- provides a restricted Windows service account,
- is appropriate only for read-only code with no demonstrated privilege requirement.

If hardware or a signed driver is later required, the service account and ACL must be re-evaluated.
