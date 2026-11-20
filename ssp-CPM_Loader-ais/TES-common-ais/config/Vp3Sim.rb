require "commonLoad"
require "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"

## Set appdata paths
AppDataBase = "/opt/appdata"
VerityDirectoryName = ENV["CAT_DIR"].split("/").last              # Last directory in the path
BridgeAppName = "FileTransferBridgeApp"
BridgeAppDataPath = AppDataBase + "/" + VerityDirectoryName + "/" + BridgeAppName
TxPath = BridgeAppDataPath + "/TxFiles/";

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
   "FileTransferBridgeResponseInput" => InterfaceDefs_CpmCommon::FileTransferBridgeResponseInput,
   "FileTransferBridgeRequestOutput" => InterfaceDefs_CpmCommon::FileTransferBridgeRequestOutput,
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "loggerThreshold" => "notice",  ##  All options listed in descending severity order
                                 ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug
  "cycleRate_hz" => 1,

  "DataFileStorePath" => TxPath,

  "fileCount" => 1, # Number of files of each file type below

  "fileSize" => 2000,

  "runSftTest" => false,

  "fileTypes" => [ 10129 ],

} )

Execution = {
  "executableName" => "vp3Sim",
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
