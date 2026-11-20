require "commonLoad.rb"
load "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"

#load "Machines.rb"

AppDataBase = "/opt/appdata"
VerityDirectoryName = ENV["CAT_DIR"].split("/").last              # Last directory in the path
ThisAppName = File.basename( __FILE__, File.extname(__FILE__) )   # Script name without extension
BridgeAppName = "FileTransferBridgeApp"
BridgeAppDataPath = AppDataBase + "/" + VerityDirectoryName + "/" + BridgeAppName
TxPath = BridgeAppDataPath + "/TxFiles/";
StorageRoot = AppDataBase + "/" + VerityDirectoryName + "/" + ThisAppName + "/nvm/";

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
     "VP3RecordInput"  => InterfaceDefs_CpmCommon::VP3RecordInput,
     "CreateFileRequestInput"  => InterfaceDefs_CpmCommon::CreateFileRequestInput,
     "AppRegInput" => InterfaceDefs_CpmCommon::AppRegInput,
     "AppRegOutput" => InterfaceDefs_CpmCommon::AppRegOutput,
     "FileTransferBridgeRequestOutput" => InterfaceDefs_CpmCommon::FileTransferBridgeRequestOutput,
     "ShmClockInput" => InterfaceDefs::ShmClockInput,
     "PartNumbersInput" => InterfaceDefs_CpmCommon::PartNumbersInput,
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "cycleRate_hz" => 1,
  "loggerThreshold" => "error",
  "requireStatusRecord" => true, # true if a status record is required at the beginning of each file, otherwise false.
  "recordDataSizeTxTrigger" => 10240, # 10*2^10 = 10KB
  "recordCountTxTrigger" => 1000, # 1000 Records, out of the way
  "maxVP3StorageSize" => 8388608, # 8*2^20 = 8MB
  "maxVP3StorageFiles" => 2500, # Maximum number of files to keep in local storage 

  # This affects how long cleanup() will wait for other apps to
  # unregister.  Longer than this and this app will shut down
  # even if there are other apps still registered with it.
  # This is set to 32 minutes because the maximum amount of time
  # the engine can run after the key is shut off is 30 minutes.
  # We would like to be able to stay alive until the engine shuts down.
  "VP3KeyoffTimeout" => 1920000,

  "VP3TxPath" => TxPath,
  "storageRoot" => StorageRoot,
  "tempRoot" => "/tmp/appdata/" + VerityDirectoryName + "/" + ThisAppName,
} )

Execution = {
  "executableName" => "VP3FileCreationApp",
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
