require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"

#load "Machines.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
     "VP3RecordOutput"  => InterfaceDefs_CpmCommon::VP3RecordOutput,
     "CreateFileRequestOutput"  => InterfaceDefs_CpmCommon::CreateFileRequestOutput,
     "AppRegOutput" => InterfaceDefs_CpmCommon::AppRegOutput
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "cycleRate_hz" => 2,
  "MaxRecordsToCreateFile" =>400,
} )

Execution = {
  "executableName" => "VP3FileCreationSimulatorApp",
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
