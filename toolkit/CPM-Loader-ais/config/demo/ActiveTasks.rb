# CPM_DEMO_SCENARIO: staged bridge configuration uses this marker, not inherited SCENARIO.
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
require "commonTaskParams.rb"

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
      "executableName" => "/bin/sh",
      "arguments" => ["-c", <<-'DEMO_LAUNCH', "DemoApp", "--instanceName=DemoApp", CommonTaskParams::Parameters["scheduler"], CommonTaskParams::Parameters.fetch("schedulerPriority", 0).to_s],
set -eu
: "${CAT_DIR:?DemoApp requires CAT_DIR}"
[ "$#" -eq 3 ] && [ "$1" = "--instanceName=DemoApp" ] || exit 1
export CAT_CONFIG_DIR="${CAT_CONFIG_DIR:-$CAT_DIR/config}"
export LD_LIBRARY_PATH="$CAT_DIR/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
exec "$CAT_DIR/bin/DemoApp" "$1" --ros-args \
    -p cycle_rate_hz:=50.0 -p logger_threshold:=error \
    -p scheduler:="$2" -p scheduler_priority:="$3"
DEMO_LAUNCH
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },
})
