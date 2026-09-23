#
# These are the tasks that are common to every scenario
#
SystemTasks.update({
  # A6N2
  #"ProductionLogger" => Machines::MachineMap["ecm"],

  # OCS
  "MachineOCS" => Machines::MachineMap["ocs"],
})

AuxiliaryProcesses.update({
  "aisXcpServer" => {
      "machines" => [ 
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/aisXcpServer",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  "OutputApp" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/OutputApp",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  "LpsJobMgr" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/LpsSaJobMgrApp",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },
  
  "LpsWeighing" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/LpsSaWeighApp",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  # Restores the AIS-SCS leg of LpsSaJobMgrReqstChannel/LpsSaJobMgrRespChannel/
  # AisJhm2TxChannel, which LpsSaJobMgrApp made ROS2-only during its ROS2 port.
  # See porting_artefacts/plan.md and apps/ScsToRos2Bridge/README.md.
  "ScsToRos2Bridge" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/ScsToRos2Bridge",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  "LpsSaListMgrApp" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/LpsSaListMgrApp",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  "LpsSaTotalsApp" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/LpsSaTotalsApp",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  "SerialPrinterApp" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/SerialPrinterApp",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  "AISJhm2DataServer" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/aisJhm2DataServer",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  "AutonomyConditionDiagnostics" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/autonomyConditionDiagnostics",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  "VP3FileCreationApp" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/VP3FileCreationApp",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  "FileTransferBridgeApp" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/FileTransferBridgeApp",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  "WorkOrderAssist" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/WorkOrderAssist",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  "baseDiagManager" => {
      "machines" => [ 
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/baseDiagManager",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  # Run AllProcessMonitor on multiple machines
  "AllProcessMonitor" => {
      "machines" => [ 
                      Machines::MachineMap["ecm"],
                    ],
      "arguments" => ["--instanceName=AllProcessMonitor"],
      "executableName" => ENV['CAT_DIR'] + "/bin/allProcessMonitor",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

} )

