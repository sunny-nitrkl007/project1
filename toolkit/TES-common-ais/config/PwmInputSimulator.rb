require "commonLoad"
require "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
"PwmInputChannelsOutput"  => InterfaceDefs_CpmCommon::PwmInputChannelsOutput,

} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "loggerThreshold" => "error",  ##  All options listed in descending severity order
                                ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 

"CsvPath" => "../apps/PwmInputSimulatorApp/Test_Points_Log_4.csv",

  "cycleRate_hz" => 50,
} )

Execution = {
  "executableName" => "PwmInputSimulator",
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
