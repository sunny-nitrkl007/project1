require "ExecutionTable_Common.rb"

# Mapping of Ruby config file to executable name
# This was formerly stored in Execution of each task's Ruby config file
ExecutionTable.update({
    "Coaching_RealTime_Simulator" => {                      # instanceName (name of the Ruby config file)
      "executableName" => "Coaching_RealTime_Simulator",    # Name of the binary executable in /bin (Mandatory Field)
    # The following are optional, the default values are shown as placeholders
    #   "scsPath" => "",
    #   "autoRestart" => true,
    #   "timeBetweenRestarts_s" => 5.0,
    #   "alwaysOn" => false,
    #   "runOnceOnStartup" => false,
    #   "launchOnStartup" => false,
    #   "cycleRateThreshold_hz" => 10,
    #   "stalledProcessTimer_s" => 5.0
    },
    "EthernetPgtServerTest_992" => { "executableName" => "ethernetPgtServerTest", },
})
