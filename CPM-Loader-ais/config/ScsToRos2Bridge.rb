require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"

# Binds the same AIS SCS interface names other processes already bind
# independently (e.g. SwitchInputScsInput has multiple binders today) --
# see porting_artefacts/plan.md for why this is safe.
Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update({
  "LpsSaJobMgrReqstChannelInput" => InterfaceDefs_Loaders::LpsSaJobMgrReqstChannelInput,
  "LpsSaJobMgrRespChannelOutput" => InterfaceDefs_Loaders::LpsSaJobMgrRespChannelOutput,
  "AisJhm2TxChannelInput"        => InterfaceDefs_Loaders::AisJhm2TxChannelInput,
  "SwitchInputScsInput"          => InterfaceDefs_CpmCommon::SwitchInputScsInput,
  "LoadRecordOutput"             => InterfaceDefs_Loaders::LpsSaLoadRecordChannelOutput,
  "LpsSaWeighReqstChannelOutput" => InterfaceDefs_Loaders::LpsSaWeighReqstChannelOutput,
  "LpsSaWeighRespChannelInput" => InterfaceDefs_Loaders::LpsSaWeighRespChannelInput,
  "LpsSaWeighTxChannelInput" => InterfaceDefs_Loaders::LpsSaWeighTxChannelInput,
  "LpsSaWeighReqstChannelInput"  => InterfaceDefs_Loaders::LpsSaWeighReqstChannelInput,
  "LpsSaWeighRespChannelOutput"  => InterfaceDefs_Loaders::LpsSaWeighRespChannelOutput,
  "LpsSaWeighTxChannelOutput"  => InterfaceDefs_Loaders::LpsSaWeighTxChannelOutput,
  # Bridge owns the AIS SCS ShmClockInput and republishes it on ROS2 for WeighApp/JobMgr.
  "ShmClockInput" => InterfaceDefs::ShmClockInput,
  # Bridge owns the AIS SCS DisplayStateInput and republishes it on ROS2 for WeighApp/JobMgr.
  "DisplayStateInput" => InterfaceDefs_Loaders::LpsSaUIDisplayStateInputChannel,
  # Bridge owns the AIS SCS DataLinkDataInput and republishes it on ROS2 for WeighApp/JobMgr.
  "DataLinkDataInput" => InterfaceDefs_CpmCommon::DataLinkDataInput,
  "AutonomyConditionDiagnosticsTxChannelInput" => InterfaceDefs_Loaders::AutonomyConditionDiagnosticsTxInputChannel,
  "EventDiagnosticDataInput" => InterfaceDefs::EventDiagnosticDataInput,
  "LpsSaJobMgrTxChannelOutput" => InterfaceDefs_Loaders::LpsSaJobMgrTxChannelOutput,
  "LpsSaJobMgrDebugChannelOutput" => InterfaceDefs_Loaders::LpsSaJobMgrDebugChannelOutput,
  "OutputChannelOutput" => InterfaceDefs_CpmCommon::OutputChannelOutput,
  "LpsSaWeighInitDebugChannelOutput" => InterfaceDefs_Loaders::LpsSaWeighInitDebugChannelOutput,
  "DemoAppTxChannelInput" => InterfaceDefs_Loaders::DemoAppTxChannelInput,
  "PartNumbersInput" => InterfaceDefs_CpmCommon::PartNumbersInput,
  "SystemHardwareHealthInput" => InterfaceDefs::SystemHardwareHealthInput,
  "SystemHardwareHealthRequestOutput" => InterfaceDefs::SystemHardwareHealthRequestOutput,
  "ReadyToFlashStatusOutput" => InterfaceDefs::ReadyToFlashStatusOutput,
  "LpsSaWeighDebugChannelOutput" => InterfaceDefs_Loaders::LpsSaWeighDebugChannelOutput,
  "LpsSaNvmCalDataChannelOutput" => InterfaceDefs_Loaders::LpsSaNvmCalDataChannelOutput,
  "LpsSaNvmCalOnTheFlyDataChannelOutput" => InterfaceDefs_Loaders::LpsSaNvmCalOnTheFlyDataChannelOutput,
  "CalMgrCmdReqstInput" => InterfaceDefs_CpmCommon::CalMgrCmdReqstInput,
  "CalMgrCmdRespOutput" => InterfaceDefs_CpmCommon::CalMgrCmdRespOutput,
  "TipoffModelTestPointsOutput" => InterfaceDefs_Loaders::TipoffModelTestPointsOutput,
  "PrinterCnfgInput" => InterfaceDefs_Loaders::LpsSaTotalsPrinterCnfgInputChannel,
})

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update({
  "loggerThreshold" => "error",  ##  All options listed in descending severity order
                                 ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug

  "cycleRate_hz" => 20.0, # fast enough that operator-facing command/ack latency through this bridge is not user-visible
})

Execution = {
    "executableName" => "ScsToRos2Bridge",
}
