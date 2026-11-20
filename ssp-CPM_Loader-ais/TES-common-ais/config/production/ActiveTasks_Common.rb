require "commonLoad.rb"
load "Machines.rb"

###################################################################
# Production ActiveTasks.rb file:  Contains all of the processes
# that will run on the live AHS vehicle.
###################################################################

#The key is the task's instance name, the value is the machine that task should be run on
#Since each item refers to a unique instance of a task in the distributed system, only one
#machine can be specified per instance
SystemTasks.update({

### A6N2-0
  "ProductionLogger" => Machines::MachineMap["ecm"], # note, that production logger by design should only run
                                                     # on one ecm

### OCS
  "MachineOCS"                         => Machines::MachineMap["ocs"],
  "LogSnapshotBridge"                  => Machines::MachineMap["ocs"],
})

#Processes to run that are not a 'Task'
#These may be specified to run on multiple machines
AuxiliaryProcesses.update({
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

  #### NOTE: Empty machines is now an error as of AIS_APP_TEMPLATE_4.3.0_ALPHA_02
  # Run SysLogBridge on multiple machines except the one running SysLogBridgeAggregator
  # "SysLogBridge" => {
  #     "machines" => [ 
  #                     # Machines::MachineMap["ecm"],
  #                   ],
  #     "arguments" => ["--instanceName=SyslogBridge"],
  #     "executableName" => ENV['CAT_DIR'] + "/bin/syslogBridge",
  #     "autoRestart" => true,
  #     "timeBetweenRestarts_s" => 2,
  #     "alwaysOn" => false,
  # },

  # Run SysLogBridgeAggregator on ecm1
  "SysLogBridgeAggregator" => {
      "machines" => [ 
                      Machines::MachineMap["ecm"],
                    ],
      "arguments" => ["--instanceName=SyslogBridgeAggregator"],
      "executableName" => ENV['CAT_DIR'] + "/bin/syslogBridge",
      "autoRestart" => true,
      "timeBetweenRestarts_s" => 2,
      "alwaysOn" => false,
  },

  # Run MachSerialNumTask on A6N2
  # "MachSerialNumTask" => {
  #   "machines" => [ 
  #                   Machines::MachineMap["ecm"],
  #                 ],
  #   "arguments" => ["--instanceName=MachSerialNumTask"],
  #   "executableName" => ENV['CAT_DIR'] + "/bin/machSerialNumTask",
  #   "autoRestart" => true,
  #   "timeBetweenRestarts_s" => 2,
  #   "alwaysOn" => false,
  # },

})
