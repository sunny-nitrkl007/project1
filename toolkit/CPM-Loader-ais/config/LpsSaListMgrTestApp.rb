require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update({
  "PostOutput" => InterfaceDefs_Loaders::LpsSaListMgrPostOutputChannel,
  "NotifyInput" => InterfaceDefs_Loaders::LpsSaListMgrNotifyInputChannel,
  "TxInput" => InterfaceDefs_Loaders::LpsSaListMgrTxInputChannel,
})

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update({
  "loggerThreshold" => "error", ##  All options listed in descending severity order
                               ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
  "cycleRate_hz" => 1.0,
  "tempRoot" => "/tmp/appdata/CPM/LpsSaListMgrTestApp"
})

Execution = {
  "executableName" => "LpsSaListMgrTestApp"
}

