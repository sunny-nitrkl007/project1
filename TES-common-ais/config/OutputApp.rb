require "commonLoad.rb"
load "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"


Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
"OutputChannelInput"  => InterfaceDefs_CpmCommon::OutputChannelInput,
} )


Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "loggerThreshold" => "error",  ##  All options listed in descending severity order
                                ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
   "cycleRate_hz" => 4, 

} )

Execution = {
  "executableName" => "OutputApp",
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
