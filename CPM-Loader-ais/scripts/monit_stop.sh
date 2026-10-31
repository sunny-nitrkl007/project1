#!/bin/sh

# Stop WeighApp
/sbin/start-stop-daemon \
    --stop \
    --pidfile /run/lps_weigh.pid \
    --retry=TERM/30/KILL/5

# Stop JobMgr
/sbin/start-stop-daemon \
    --stop \
    --pidfile /run/lps_job_mgr.pid \
    --retry=TERM/30/KILL/5
