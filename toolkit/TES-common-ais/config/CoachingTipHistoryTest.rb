require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"
load "Robot.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
  "CoachingTipHistoryOutput" => InterfaceDefs_CpmCommon::CoachingTipHistoryOutput,
} )

AppDataBase = "/opt/appdata"
VerityDirectoryName = ENV["CAT_DIR"].split("/").last              # Last directory in the path
ThisAppName = File.basename( __FILE__, File.extname(__FILE__) )   # Script name without extension
StorageRoot = AppDataBase + "/" + VerityDirectoryName + "/" + ThisAppName

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "cycleRate_hz" => 1,
  "loggerThreshold" => "debug",  ##  All options listed in descending severity order
                                 ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
} )

Execution = {
  "executableName" => "CoachingTestHistoryTest",
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
