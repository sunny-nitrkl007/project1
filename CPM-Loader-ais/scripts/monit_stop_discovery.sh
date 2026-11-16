#!/bin/sh

# Stop the Fast DDS Discovery Server started by monit_start_discovery.sh.
/sbin/start-stop-daemon \
    --stop \
    --pidfile /run/lps_discovery_server.pid \
    --retry=TERM/30/KILL/5
