require "commonLoad"
require "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
#"PwmInputChannelsOutput"  => InterfaceDefs_CpmCommon::PwmInputChannelsOutput,
"PwmInputChannelsInput"  => InterfaceDefs_CpmCommon::PwmInputChannelsInput,

} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
"loggerThreshold" => "error",  ##  All options listed in descending severity order
                                ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
"cycleRate_hz" => 50,
"schedulerPriority"=>50, 

} )

Execution = {
  "executableName" => "PWMInputReader",
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
