require "commonLoad"
require "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"
require "IPAddresses.rb"

ThisAppName = File.basename( __FILE__, File.extname(__FILE__) )   # Script name without extension

Interfaces = CommonTaskParams::Interfaces.dup;

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "cycleRate_hz" => 50,
  "loggerThreshold" => "error",
  "IPAddress" => IPAddressMap.fetch("A6N2-0").to_s,                       # Change when using VM
} )

Execution = {
  "executableName" => "aisXcpServer",
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( ThisAppName )
