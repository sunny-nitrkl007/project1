require "commonLoad"
require "commonTaskParams.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
   "AutonomyConditionDiagnosticsTxInput" => InterfaceDefs_Loaders::AutonomyConditionDiagnosticsTxInputChannel,
   "SystemHardwareHealthInput" => InterfaceDefs::SystemHardwareHealthInput,
   "LpsSaWeighReqstChannelInput" => InterfaceDefs_Loaders::LpsSaWeighReqstChannelInput,
   "LpsSaWeighRespChannelInput" => InterfaceDefs_Loaders::LpsSaWeighRespChannelInput,
   "LpsSaWeighTxChannelInput" => InterfaceDefs_Loaders::LpsSaWeighTxChannelInput,
   "LpsSaWeighDebugChannelInput" => InterfaceDefs_Loaders::LpsSaWeighDebugChannelInput,
   "LpsSaNvmCalDataChannelInput" => InterfaceDefs_Loaders::LpsSaNvmCalDataChannelInput,
   "LpsSaNvmCalOnTheFlyDataChannelInput" => InterfaceDefs_Loaders::LpsSaNvmCalOnTheFlyDataChannelInput,
   "LpsSaWeighInitDebugChannelInput" => InterfaceDefs_Loaders::LpsSaWeighInitDebugChannelInput,
   "LpsSaJobMgrTxChannelInput" => InterfaceDefs_Loaders::LpsSaJobMgrTxChannelInput,	
   "PwmInputChannelsInput" => InterfaceDefs_CpmCommon::PwmInputChannelsInput,
   "MachineInput" => InterfaceDefs_Loaders::MachineInput,
   "LpsSaJobMgrReqstChannelInput" => InterfaceDefs_Loaders::LpsSaJobMgrReqstChannelInput,
   "LpsSaJobMgrRespChannelInput" => InterfaceDefs_Loaders::LpsSaJobMgrRespChannelInput,
   "LpsSaJobMgrDebugChannelInput" => InterfaceDefs_Loaders::LpsSaJobMgrDebugChannelInput,
   "SwitchInputScsInput" => InterfaceDefs_CpmCommon::SwitchInputScsInput,
   "WorkOrderAssistTxInput" => InterfaceDefs_Loaders::WorkOrderAssistTxInputChannel,
   "DisplayStateInput" => InterfaceDefs_Loaders::LpsSaUIDisplayStateInputChannel,
   "CycleSegTxChannelInput" => InterfaceDefs_Loaders::CycleSegTxChannelInput,
   "WidgetsDebugDataInput" => InterfaceDefs_Loaders::WidgetsDebugDataInput,
   "TipoffModelTestPointsInput" => InterfaceDefs_Loaders::TipoffModelTestPointsInput,
   "BEMSimStateInput" => InterfaceDefs_Loaders::LpsSaUIBEMSimStateInputChannel,
   "DataLinkDataInput" => InterfaceDefs_CpmCommon::DataLinkDataInput,
} )


ScsRxTimeouts = {
  "AutonomyConditionDiagnosticsTxInput_rxTimeout_sec" => 5.0,
  "SystemHardwareHealthInput_rxTimeout_sec" => 5.0,
  "LpsSaWeighReqstChannelInput_rxTimeout_sec" => 5.0, 
  "LpsSaWeighRespChannelInput_rxTimeout_sec" => 5.0, 
  "LpsSaWeighTxChannelInput_rxTimeout_sec" => 5.0, 
  "LpsSaWeighDebugChannelInput_rxTimeout_sec" => 5.0,
  "LpsSaNvmCalDataChannelInput_rxTimeout_sec" => 5.0,
  "LpsSaNvmCalOnTheFlyDataChannelInput_rxTimeout_sec" => 5.0,
  "LpsSaWeighInitDebugChannelInput_rxTimeout_sec" => 5.0, 
  "LpsSaJobMgrTxChannelInput_rxTimeout_sec" => 5.0, 
  "PwmInputChannelsInput_rxTimeout_sec" => 5.0, 
  "MachineInput_rxTimeout_sec" => 5.0, 
  "LpsSaJobMgrReqstChannelInput_rxTimeout_sec" => 5.0, 
  "LpsSaJobMgrRespChannelInput_rxTimeout_sec" => 5.0, 
  "LpsSaJobMgrDebugChannelInput_rxTimeout_sec" => 5.0, 
  "SwitchInputScsInput_rxTimeout_sec" => 5.0,
  "WorkOrderAssistTxInput_rxTimeout_sec" => 10.0,
  "DisplayStateInput_rxTimeout_sec" => 10.0,
  "CycleSegTxChannelInput_rxTimeout_sec" => 10.0,
  "WidgetsDebugDataInput_rxTimeout_sec" => 10.0,
  "TipoffModelTestPointsInput_rxTimeout_sec" => 10.0,
  "BEMSimStateInput_rxTimeout_sec" => 10.0,
}

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "cycleRate_hz" => 100,
  "loggerThreshold" => "error",
} )

Execution = {
  "executableName" => "aisXcpServer",
}

