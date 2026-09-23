require "commonLoad.rb"
load "Machines.rb"

###################################################################
# Demo ActiveTasks.rb file:  Contains all of the processes
# that will run on the live AHS vehicle.
###################################################################

#The key is the task's instance name, the value is the machine that task should be run on
#Since each item refers to a unique instance of a task in the distributed system, only one
#machine can be specified per instance
SystemTasks = {}

#Processes to run that are not a 'Task'
#These may be specified to run on multiple machines
AuxiliaryProcesses = {}

load "CommonTasks.rb"
load "TargetVariantConfigTasks.rb"

# Remove the apps that we don't want to in demo mode.
AuxiliaryProcesses.delete("BmiJ1939_CANA")
AuxiliaryProcesses.delete("BmiJ1939_CANB")
AuxiliaryProcesses.delete("WidgetApp")
AuxiliaryProcesses.delete("CycleSeg")

#
# Here we can add all tasks specific to this scenario
#
AuxiliaryProcesses.update({
  "DemoApp" => {
      "machines" => [
                      Machines::MachineMap.default,
                    ],
      "executableName" => ENV['CAT_DIR'] + "/bin/DemoApp",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },
})
