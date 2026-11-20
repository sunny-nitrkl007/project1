require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"

VerityDirectoryName = ENV["CAT_DIR"].split("/").last              # Last directory in the path
ThisAppName = File.basename( __FILE__, File.extname(__FILE__) )   # Script name without extension

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update({
  "RequestInput" => InterfaceDefs_CpmCommon::SerialPrinterRequestInputChannel,
  "FileTransferBridgeRequestOutput" => InterfaceDefs_CpmCommon::FileTransferBridgeRequestOutput,
})

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update({
  "loggerThreshold" => "error", ##  All options listed in descending severity order
                               ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
  "cycleRate_hz" => 2.0,
  "destinationFid" => 0x00580000,
  "tempRoot" => "/tmp/appdata/" + VerityDirectoryName + "/" + ThisAppName,
})

Execution = {
  "executableName" => ThisAppName
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
