require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update({
  "TotalsInput" => InterfaceDefs_Loaders::LpsSaTotalsInputChannel,
  "RequestOutput" => InterfaceDefs_Loaders::LpsSaTotalsRequestOutputChannel,
  "ResponseInput" => InterfaceDefs_Loaders::LpsSaTotalsResponseInputChannel,
  "LoadRecordOutput" => InterfaceDefs_Loaders::LpsSaLoadRecordChannelOutput
})

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update({
  "loggerThreshold" => "info", ##  All options listed in descending severity order
                               ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
  "cycleRate_hz" => 1.0
})

Execution = {
  "executableName" => "LpsSaTotalsTestApp"
}



