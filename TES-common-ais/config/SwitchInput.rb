require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
     "SwitchInputScsOutput" => InterfaceDefs_CpmCommon::SwitchInputScsOutput,
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  	"loggerThreshold" => "error",  ##  All options listed in descending severity order
                                ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 

## Modify the values below according to machine requirements.
	"cycleRate_hz" => 50,        
    "DebounceCount" => 5,    
} )

Execution = {
  "executableName" => "SwitchInputApp",
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
