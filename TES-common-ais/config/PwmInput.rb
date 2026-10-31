require "commonLoad"
require "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
"PwmInputChannelsOutput"  => InterfaceDefs_CpmCommon::PwmInputChannelsOutput,
 "AppRegInput" => InterfaceDefs_CpmCommon::AppRegInput,
 "AppRegOutput" => InterfaceDefs_CpmCommon::AppRegOutput,

} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
"loggerThreshold" => "error",  ##  All options listed in descending severity order
                                ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
"cycleRate_hz" => 50,
"schedulerPriority"=>50, 

} )

Execution = {
  "executableName" => "PwmInput",
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
