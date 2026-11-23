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

# Stop Output
/sbin/start-stop-daemon \
    --stop \
    --pidfile /run/output_app.pid \
    --retry=TERM/30/KILL/5

# Stop SerialPrinterApp
/sbin/start-stop-daemon \
    --stop \
    --pidfile /run/serial_printer.pid \
    --retry=TERM/30/KILL/5

# Stop VP3FileCreationApp
/sbin/start-stop-daemon \
    --stop \
    --pidfile /run/lps_vp3.pid \
    --retry=TERM/30/KILL/5  