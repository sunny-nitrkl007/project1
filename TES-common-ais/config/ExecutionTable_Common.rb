# Mapping of Ruby config file to executable name
# This was formerly stored in Execution of each task's Ruby config file

if defined?(ExecutionTable_Common_rb)
  puts __FILE__ + ' already loaded, skipping'
else
  ExecutionTable_Common_rb = true

  ExecutionTable.update({
      "Acd2Task" => {             # instanceName (name of the Ruby config file)
        "executableName" => "Acd2Task",    # Mandatory Field
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
      "BmiCdl" => { "executableName" => "bmiCdl", },
      "BmiEthernet" => { "executableName" => "bmiEthernet", },
      "BmiJ1939" => { "executableName" => "bmiJ1939", },
      "CoachingTask" => { "executableName" => "CoachingTask", },
      "FileTransferBridgeApp" => { "executableName" => "FileTransferBridgeApp", },
      "OutputApp" => { "executableName" => "OutputApp", },
      "PwmInput" => { "executableName" => "PwmInput", },
      "RemotePrinterApp" => { "executableName" => "RemotePrinterApp", },
      "SerialPrinterApp" => { "executableName" => "SerialPrinterApp", },
      "SwitchInputApp" => { "executableName" => "SwitchInputApp", },
      "XcpServerTask" => { "executableName" => "aisXcpServer", },
  })
end