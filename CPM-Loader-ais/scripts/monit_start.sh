#!/bin/sh

# Start JobMgr
/sbin/start-stop-daemon \
    --start \
    --background \
    --make-pidfile \
    --pidfile /run/lps_job_mgr.pid \
    --exec /opt/CPM/bin/LpsSaJobMgrApp \
    -- \
    --instance LpsSaJobMgrApp \
    --ros-args \
    --params-file /opt/appdata/CPM/tmp/stage/LpsSaJobMgrApp.yaml \
    --params-file /opt/appdata/CPM/tmp/stage/Robot_CAT_972_14A_STD_DEMO.yaml

# Allow JobMgr to initialize
sleep 2

# Start WeighApp
/sbin/start-stop-daemon \
    --start \
    --background \
    --make-pidfile \
    --pidfile /run/lps_weigh.pid \
    --exec /opt/CPM/bin/LpsSaWeighApp \
    -- \
    --instance LpsSaWeighApp \
    --ros-args \
    --params-file /opt/appdata/CPM/tmp/stage/LpsSaWeighApp.yaml \
    --params-file /opt/appdata/CPM/tmp/stage/Robot_CAT_972_14A_STD_DEMO.yaml
