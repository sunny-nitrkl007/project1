###################################################################
# Unknown ActiveTasks.rb file:  Contains all of the processes
# that will run for an unsupported MSN.
###################################################################
load "ActiveTasks_Common.rb"

# The key is the task's instance name, the value is the machine that task should be run on
# Since each item refers to a unique instance of a task in the distributed system, only one
# machine can be specified per instance
SystemTasks.update ({

### A6N2
  "AbsIMU"                             => Machines::MachineMap["ecm"],
  "ATCalibrationApp"                   => Machines::MachineMap["ecm"],
  "ATWeighingApp"                      => Machines::MachineMap["ecm"],
  "AutonomyConditionDiagnostics"       => Machines::MachineMap["ecm"],
  "baseMachineInterface"               => Machines::MachineMap["ecm"],
  "BmiCdl"                             => Machines::MachineMap["ecm"],
  "FileTransferBridgeApp"              => Machines::MachineMap["ecm"],
  # "OutputApp"                          => Machines::MachineMap["ecm"],
  # "Tpms2CycleSegApp"                   => Machines::MachineMap["ecm"],
  # "VP3FileCreationApp"                 => Machines::MachineMap["ecm"],
  "XcpServerTask"                      => Machines::MachineMap["ecm"],
})
