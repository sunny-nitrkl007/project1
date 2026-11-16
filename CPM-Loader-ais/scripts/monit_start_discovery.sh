#!/bin/sh

# Start the Fast DDS Discovery Server that all CPM apps register with
# (see config/fastdds_profiles.xml / Ros2TaskWrapper.h for the client side).
#
# TODO confirm the actual installed path of the fastdds CLI on target
# (e.g. `which fastdds`) and replace the bare command below with an
# absolute path for --exec -- start-stop-daemon needs that to match
# the running process correctly.
/sbin/start-stop-daemon \
    --start \
    --background \
    --make-pidfile \
    --pidfile /run/lps_discovery_server.pid \
    --exec "$(command -v fastdds)" \
    -- \
    discovery \
    --server-id 0 \
    --udp-port 11811
