require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update({
  "RequestInput" => InterfaceDefs_CpmCommon::SerialPrinterRequestInputChannel
})

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update({
  "loggerThreshold" => "error", ##  All options listed in descending severity order
                               ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
  "cycleRate_hz" => 2.0,
  "devicePath" => "/dev/ttyS2", # empty string is std::cout
  "baudRate" => 9600,
  "stopBits" => 1,
  "dataBits" => 8,
  "parityBit" => "none",
  "secondsBetweenDocs" => 2.0 # Seconds to wait between printed documents
})

Execution = {
  "executableName" => "SerialPrinterApp"
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
