require "commonLoad"
require "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"
load "Robot.rb"

Interfaces = CommonTaskParams::Interfaces.dup;

AppDataBase = "/opt/appdata"
VerityDirectoryName = ENV["CAT_DIR"].split("/").last              # Last directory in the path
ThisAppName = File.basename( __FILE__, File.extname(__FILE__) )   # Script name without extension
StorageRoot = AppDataBase + "/" + VerityDirectoryName + "/" + ThisAppName

Interfaces.update( {
"CoachingSummaryDataInput" => InterfaceDefs_CpmCommon::CoachingSummaryDataInput, 
"Coaching3x3DataInput" => InterfaceDefs_CpmCommon::Coaching3x3DataInput,
"DataLinkDataOutput" => InterfaceDefs_CpmCommon::DataLinkDataOutput,
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "cycleRate_hz" => 8.3333333333333334,
  "loggerThreshold" => "debug",  ##  All options listed in descending severity order
                                 ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
  "operatorName" => "Doug",
} )

Execution = {
  "executableName" => "CoachingTaskTest",
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
