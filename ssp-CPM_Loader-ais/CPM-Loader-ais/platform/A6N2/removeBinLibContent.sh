#!/usr/bin/env bash

platform="${0%/*}"
echo    ""
echo    " removing unneeded ${platform##*/} content "
echo    ""

# rm    -f bin/bCamera*
# rm    -f bin/BCamera*
# rm    -f bin/template*
# rm -R -f bin/*test*
# rm -R -f bin/*Test*
# rm    -f bin/msnReader
# rm    -f bin/hlog*
# rm    -f bin/*Example*

# rm    -f bin/aisFactoryTutorial
# rm    -f bin/Sauron
# rm    -f bin/playback*

# rm    -f bin/inputOutputSimulator2
# rm    -f bin/camera*
# rm    -f bin/extractPcapLogs
# rm    -f bin/CANbridge
# rm    -f bin/IPCameraInterface
# rm    -f bin/mretInterface
# rm    -f bin/poseSimulatorRxTask
# rm    -f bin/SimulatorPositionTask
# rm    -f bin/AStopCANRxTask

# rm    -f lib/*TMAC*
# rm    -f lib/*Tmac*
# rm    -f lib/*Camera*
# rm    -f lib/libsats*
# rm    -f lib/*Example*

# rm    -f lib/*BaseCanCcpData*
# rm    -f lib/*BaseCANLoggerData*
# rm    -f lib/*BaseMachineLoggerStatus*
# rm    -f lib/*ChannelToLog*
#rm    -f lib/*DatumBookmark*
#rm    -f lib/*DeterministicPlaybackStatus*
#rm    -f lib/*DeterministicTaskInfo*
#rm    -f lib/*DeterministicTaskState*
# rm    -f lib/*Fl_Tree*
# rm    -f lib/*GenericDebug*
# rm    -f lib/*LogPause*
# rm    -f lib/*LogResume*
# rm    -f lib/*LogStart*
# rm    -f lib/*LogStop*
# rm    -f lib/*PlannerConfigRequest*
# rm    -f lib/*PlaybackLogCommands*
# rm    -f lib/*PlaybackLogDetails*
# rm    -f lib/*PlaybackLogOpen*
# rm    -f lib/*PlaybackLogStatus*
# rm    -f lib/*TextWritableRequest*
# rm    -f lib/*TextWritableResponse*
# rm    -f lib/*tmacComms*
# rm    -f lib/*tmacHandler*
# rm    -f lib/*VersionInfo*
# rm    -f lib/*VersionInfoRequest*

rm    -f lib/*.TypeTraits.so
rm    -f lib/*.Restorable.so

# rm    -f lib/libOcsAlert*
# rm    -f lib/libPlaybackDeterministicCommand*
# rm    -f lib/libSnapshotBridge*


#
# detectCommon content
#

# rm    -f lib/*Detect*
# rm    -f bin/*radar*

#
# machineCommon content
#


# Remove static libraries
rm -Rf lib/libaisJhm2RequestProc.a