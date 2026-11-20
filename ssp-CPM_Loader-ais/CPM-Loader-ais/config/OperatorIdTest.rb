require "commonLoad"
require "commonTaskParams.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
  #"LpsSaJobMgrTxChannelInput" => InterfaceDefs_Loaders::LpsSaJobMgrTxChannelInput,
  #"LpsSaJobMgrReqstChannelOutput" => InterfaceDefs_Loaders::LpsSaJobMgrReqstChannelOutput,
  #"SwitchInputScsOutput" => InterfaceDefs_CpmCommon::SwitchInputScsOutput,
  #"OutputChannelInput" => InterfaceDefs_CpmCommon::OutputChannelInput,
  "ListTxInput" => InterfaceDefs_Loaders::LpsSaListMgrTxInputChannel,

} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "loggerThreshold" => "notice",  ##  All options listed in descending severity order
                                 ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug
  "cycleRate_hz" => 10,
  "storageRoot" => "/media/sf_My_Shared_Folder",
} )

Execution = {
  "executableName" => "OperatorIdTest",
}

