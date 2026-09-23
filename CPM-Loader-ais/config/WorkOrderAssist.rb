require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update({
  "ShmClockInput" => InterfaceDefs::ShmClockInput,
  "AutonomyConditionDiagnosticsTxChannelInput"  => InterfaceDefs_Loaders::AutonomyConditionDiagnosticsTxInputChannel,
  "PartNumbersInput" => InterfaceDefs_CpmCommon::PartNumbersInput,
  "LoadRecordInput" => InterfaceDefs_Loaders::LpsSaLoadRecordChannelInput,
  "LpsSaJobMgrReqstChannelOutput"  => InterfaceDefs_Loaders::LpsSaJobMgrReqstChannelOutput,
  "IoTHubInboundMessageInput" => InterfaceDefs_CpmCommon::IoTHubCommsInboundMessageInput,
  "IoTHubOutboundMessageOutput" => InterfaceDefs_CpmCommon::IoTHubCommsOutboundMessageOutput,
  "IoTHubOutboundReturnInput" => InterfaceDefs_CpmCommon::IoTHubCommsOutboundReturnInput,
  "SettingsOutput" => InterfaceDefs_Loaders::WorkOrderAssistSettingsOutputChannel,
  "SettingsWrInput" => InterfaceDefs_Loaders::WorkOrderAssistSettingsWrInputChannel,
  "TxOutput" => InterfaceDefs_Loaders::WorkOrderAssistTxOutputChannel,
})

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update({
  "loggerThreshold" => "error", ##  All options listed in descending severity order
                               ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
  "cycleRate_hz" => 1.0,
  "serverPort" => 55555,
  "storageRoot" => "/opt/appdata/CPM/WorkOrderAssist/nvm",
})

Execution = {
  "executableName" => "WorkOrderAssist"
}



