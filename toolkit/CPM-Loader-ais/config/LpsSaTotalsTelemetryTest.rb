require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update({
  "DataLinkDataOutput" => InterfaceDefs_CpmCommon::DataLinkDataOutput,
  "PartNumbersOutput" => InterfaceDefs_CpmCommon::PartNumbersOutput,
  "FileTransferBridgeRequestInput" => InterfaceDefs_CpmCommon::FileTransferBridgeRequestInput,
  "LpsSaLoadRecordChannelOutputChannel" => InterfaceDefs_Loaders::LpsSaLoadRecordChannelOutput
})

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update({
  "loggerThreshold" => "warn", ##  All options listed in descending severity order
                               ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
  "cycleRate_hz" => 1.0
})

Execution = {
  "executableName" => "LpsSaTotalsTelemetryTest"
}



