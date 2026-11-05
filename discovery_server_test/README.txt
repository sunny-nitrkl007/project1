Minimal change set for testing Fast DDS Discovery Server, isolated from
every other pending change in this repo (Ros2TaskWrapper.h, the SHM-only
transport profile, the monit-supervised discovery server, etc. all stay
untouched and uncommitted). Only these two files matter:

1. discovery_client_test.xml
   Copy to: /opt/CPM/config/discovery_client_test.xml

2. monit_start.sh
   Replace:  /opt/CPM/scripts/monit_start.sh
   (identical to the current deployed one, with one line added at the
   top: export FASTRTPS_DEFAULT_PROFILES_FILE=/opt/CPM/config/discovery_client_test.xml)

Then, on the target:

  fastdds discovery --server-id 0 --udp-port 11811 &

  monit restart LpsJobMgr
  monit restart LpsWeigh

Verify:

  export ROS_DISCOVERY_SERVER=127.0.0.1:11811
  ros2 node list
  ros2 topic list

LpsSaJobMgrApp / LpsSaWeighApp showing up there confirms they registered
with the discovery server.

This only works cleanly against the currently-deployed binaries (not yet
rebuilt from the current Ros2TaskWrapper.h, which would override
FASTRTPS_DEFAULT_PROFILES_FILE/ROS_DISCOVERY_SERVER on its own).
