#!/bin/bash

# System Startup Script

source $CAT_DIR/scripts/ScriptUtils.sh  #<-- Load common script functions

basepath=$CAT_DIR/bin

pushd $basepath &> /dev/null

datestr=`date +%Y-%m-%d`

echo "Stopping $hostname on $datestr"

### stop any old processes
echo "Stopping any old processes..."

###  List of all processes we want to stop (not including scs - we kill that separately)
###  Active processes are only listed by the first 15 characters of the process name.
processes=(VP3FileCreationApp
	   LpsSaTotalsApp
	   aisJhm2DataServer
	   bmiJ1939
	   CycleSeg
	   autonomyConditionDiagnostics
	   FileTransferBridgeApp
	   LpsSaJobMgrApp
	   LpsSaListMgrApp
	   LpsSaWeighApp
	   machSerialNumTask
	   OutputApp
	   SerialPrinterApp
	   WorkOrderAssist	   	
  	   autonomyLogger
           productionLogger
           applanixLogger
           cameraInterface
           machineStateManager
           machineStateManager2
           machineControl
           stateEstimator
           pathPlayback
           timeSync
           intelligentDriver
           MineModelManager
           assignmentManager
           obiCommLogic
           offBoardI
           tmacServer
           obiMineMode
           scriptHandler
           ms990Proc
           tpm
           perceptionDiagnostics
           posDiagnostics
           diagnosticAgent
           eventAgent
           rtkServer
           rtkSerialClient
           vehicleHealthSupervisor
           radarRelay
           fpgaInterface
           getApplanixLogs
           lidarRelay
    	   vehicleSimulator
    	   pathfinderOCS
    	   pcm
    	   defaultPcm
           pcmremote
           velodyne
           ladarObstacleDetection
           taggedRadarToBin
           pathTracker
           pathTrackingEmbeddedTask
           obstacleSim
           playbackLog
	       laneMapTask
           configGUI
           cdc
           serviceRelay
           simCamera
           simMedusa
           simVelo
           simServiceRelay
           simRadar
           obstacleAccurac
           medusaMonitor
           laneMapPlayback
	       simpleRadarDet
	       truePositionPub
           gpsBroadcast
           vehicleObs
           retrieveApplxConfig
           calibrationServ
           onlineCalibrati
           obstacleDetecti
           baselineDeterministicObstacleDetecti
	       simMs990Proc
	       trackingSim
           targetUpdate
           SanityCheckerTask
           PBLTask
           generateReportTask
           PBLMapTask
           turnsignalManager
           infDiagnosticsEvents
           macomControllerTask
           dsrrInterface
           versionReportin
           mcmRxTask
           mcmTxTask
           vehicleObserver
           versionReportingTask
           ApplanixTimeSync
           configPlaybackGUI
           playbackDirector
           visibilityDiagnostics
           bDOD
           timedPlaybackLog
           logLogAgent
           machSerialNumTask
           statisticGround
           ODSimTask
           obstacleAggregatorTask
           FOD
           AbsIMU
           positionDriftAutoInjector
           bermDetectionTask
           hilInterface
           baseCANLogger
           ccpClientTask
           namInterface
           configManager
           jhm2DataServer
           planningCheckout
           logSnapshotBridge
           SimOBIRoute
           AggSimTask
           bermDetectionSimTask
           MOD2
           engineeringControlsTask
           fakeRangeImageInterface
	       )

# `ps` is different with and without BusyBox
addtnl_ps_params=""
if [ "$(isBusyBoxInstalled)" == 0 ]; then
  addtnl_ps_params="--no-headers -A"
fi

for pid in `ps ${addtnl_ps_params} -o pid,comm | grep -w "pcm"                | cut -c 1-5`; do 
  kill $pid; 
  echo "Stopping PCM"
  sleep 8  # PCM sometimes takes 7 seconds to shutdown
done

processRunning=0

### Try to shut down the processes "nicely"
for i in ${processes[*]}; do
    toshutdown=${i:0:15}  # only use the first 15 characters
    # try to shutdown nicely
    for pid in `ps ${addtnl_ps_params} -o pid,comm | grep $toshutdown | cut -c 1-5`; do 
      kill $pid; 
      echo "Shutting down $i [$toshutdown] "
      processRunning=1
    done
done

### wait for signal handlers to finish
if [ $processRunning != 0 ]; then
  sleep 2
fi

# first kill scs 3 times
for pid in `ps ${addtnl_ps_params} -o pid,comm | grep -w "scs"                | cut -c 1-5`; do 
  kill $pid; 
  kill $pid; 
  kill $pid; 
  echo "scs kill $pid"
done


###if still alive, really kill!
for i in ${processes[*]}; do
    toshutdown=${i:0:15}  # only use the first 15 characters
    for pid in `ps ${addtnl_ps_params} -o pid,comm | grep $toshutdown | cut -c 1-5`; do 
      kill -9 $pid; 
      echo "Killing $i [$toshutdown] "
    done
done


# first kill scs 3 times
for pid in `ps ${addtnl_ps_params} -o pid,comm | grep -w "scs"                | cut -c 1-5`; do 
  kill -9 $pid; 
  kill -9 $pid; 
  kill -9 $pid; 
  echo "scs kill -9 $pid"
done

### Make sure key switch override is released 
### in case PCM was force killed before it could release the key switch override.
if [ -f /dev/shm/AHS_GPIO/KeySwitchOverrideAHS ]; then
    echo 0 > /dev/shm/AHS_GPIO/KeySwitchOverrideAHS
fi

popd &> /dev/null

echo "done!"

