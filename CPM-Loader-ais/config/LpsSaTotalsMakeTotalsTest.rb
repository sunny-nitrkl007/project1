require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update({
  "LoadRecordOutput" => InterfaceDefs_Loaders::LpsSaLoadRecordChannelOutput
})

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update({
  "loggerThreshold" => "info", ##  All options listed in descending severity order
                               ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
  "cycleRate_hz" => 1.0
})

Execution = {
  "executableName" => "LpsSaTotalsMakeTotalsTest"
}



