require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
  "DataLinkDataOutput" => InterfaceDefs_CpmCommon::DataLinkDataOutput,
  "DemoAppTxChannelInput"  => InterfaceDefs_Loaders::DemoAppTxChannelInput,
  "DemoAppTxChannelOutput" => InterfaceDefs_Loaders::DemoAppTxChannelOutput,
  "DemoAppReqstChannelInput" => InterfaceDefs_Loaders::DemoAppReqstChannelInput,
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update({
  "loggerThreshold" => "error", ##  All options listed in descending severity order
                               ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
  "cycleRate_hz" => 50.0,
  "tempRoot" => "/tmp/appdata/CPM/DemoApp"
})


Execution = {
  "executableName" => "DemoApp",
}
