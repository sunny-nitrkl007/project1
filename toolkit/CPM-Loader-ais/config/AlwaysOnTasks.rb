###################################################################
# config/AlwaysOnTasks.rb file:  Configure AlwaysOnTasks.  This file is
# loaded before the scenario is chosen, in order to launch scs and
# any other scenario specific alwaysOn or launchOnStartup tasks.
###################################################################

if defined?(AlwaysOnTasks_rb)
  puts __FILE__ + ' already loaded, skipping'
else

AlwaysOnTasks_rb = true

require "commonLoad.rb"
require "Machines.rb"

# Initialize the SystemTasks and AuxiliaryProcesses
#
# SystemTasks are AIS 'Tasks': The key is the task's instance name, the value is the machine that task should be run on
# Since each item refers to a unique instance of a task in the distributed system, only one
# machine can be specified per instanceThe key is the task's instance name, the value is the machine that task should be run on.
#
SystemTasks = {
    # A6N2-0
    # "Acd2Task_Template" => Machines::MachineMap["a6n2-0"],

    # A6N2-1
    # "ProductionLogger" => Machines::MachineMap["a6n2-1"], # note, that production logger by design should only run
                                                        # on one ecm

    # A6N1-0
    # "Examplewriter" => Machines::MachineMap["a6n1-0"],

    # D6CX-2
    # "ExampleReader" => Machines::MachineMap["d6cx-2"],

    # PL671-3
    # "ExampleReader" => Machines::MachineMap["pl671-3"],

    #OCS
    # "MachineOCS" => Machines::MachineMap["ocs"],
}

# AuxiliaryProcesses are either processes that are not AIS 'Tasks' (and support commmand line arguments)
# and/or use the same Ruby config file on multiple machines
AuxiliaryProcesses = {
    #    string taskName                     - The instance name of the task, empty if not a task
    #    string executableName               - The executable name of the process to launch (binary file name)
    #    list(string) machines               - The list of machines the process should run on
    #    string scsPath                      - The path to the local SCS daemon to connect to (relevant only if a task)
    #    bool autoRestart                    - True if the process should be restarted automatically if it shuts down unexpectedly
    #    unsigned int timeBetweenRestarts_s  - The amount of time to wait before automatically restarting a process -- autoRestart must be true for this parameter to be relevant
    #    bool task                           - True if it's a task, False otherwise
    #    list(string) arguments              - The arguments to add to the command line when launching a process
    #    bool alwaysOn                       - True if it's a daemon process that is "always on" and should not be killed when PCM receives a STOP command, e.g. SCS
    #    bool launchOnStartup                - true if the process needs to start initially
    #    unsigned int cycleRateThreshold_hz  - threshold for determining this process is falling behind its cycle rate
    #    double stalledProcessTimer_s        - amount of time to wait with no heartbeat before declaring this process as 'stalled"
    #    string outputRedirectPath           - The path where the output should be redirected
}

# Configure the following AuxilliaryTasks to run on all platforms:
#  - scs: configured to run with unicastSubscription disabled
#  - MachSerialNumTask: Manages robot file
#  - PlatformConfigTask: Configures CAN, CDA, keyswitch timings
#  - configManager: Writes configs to hlogs
#  - readLCTask: Configures IP Address & hostname based on location code
configureAlwaysOnTasks(49400, "scs", "", false)

# Remove any unwanted tasks
AuxiliaryProcesses.delete("PlatformConfigTask")
AuxiliaryProcesses.delete("readLCTask")
# AuxiliaryProcesses.delete("configManager")

end
