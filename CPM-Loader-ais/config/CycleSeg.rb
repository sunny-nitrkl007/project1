require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"
require "Robot.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update({
  "ShmClockInput" => InterfaceDefs::ShmClockInput,
  "WeighTxInput" => InterfaceDefs_Loaders::LpsSaWeighTxChannelInput,
  "DatalinkDataInput" => InterfaceDefs_CpmCommon::DataLinkDataInput,
  "VP3RecordOutput" => InterfaceDefs_CpmCommon::VP3RecordOutput,
  "TxOutput" => InterfaceDefs_Loaders::CycleSegTxChannelOutput,
  "AppRegInput" => InterfaceDefs_CpmCommon::AppRegInput,
  "AppRegOutput" => InterfaceDefs_CpmCommon::AppRegOutput,
  "AutonomyConditionDiagnosticsTxChannelInput"  => InterfaceDefs_Loaders::AutonomyConditionDiagnosticsTxInputChannel,
})

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update({
  "loggerThreshold" => "error", ##  All options listed in descending severity order
                                 ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
  "cycleRate_hz" => 1.0/0.120,
  "gpsDistanceThreshold" => 20,      # meters
  "gpsTimeThreshold"     => 60,      # seconds
})

Execution = {
  "executableName" => "CycleSeg"
}



