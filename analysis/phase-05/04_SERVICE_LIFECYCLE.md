# Service Lifecycle

Startup validates configuration and enters RUNNING.

Stop sets the stop event and transitions through STOP_PENDING to STOPPED.

Automatic/delayed startup remains installer configuration work.
