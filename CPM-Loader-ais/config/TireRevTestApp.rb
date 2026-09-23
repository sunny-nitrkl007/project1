require "commonLoad"
require "commonTaskParams.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
  "WidgetsDebugDataInput" => InterfaceDefs_Loaders::WidgetsDebugDataInput,
  "DataLinkDataInput" => InterfaceDefs_CpmCommon::DataLinkDataInput,
  "DataLinkDataOutput" => InterfaceDefs_CpmCommon::DataLinkDataOutput,
  "CycleSegTxInterfaceOutputChannel" => InterfaceDefs_Loaders::CycleSegTxChannelOutput,
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "loggerThreshold" => "error",  ##  All options listed in descending severity order
                                 ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug
  "cycleRate_hz" => 10,

} )

Execution = {
  "executableName" => "TireRevTestApp",
}

