require "commonLoad.rb"
require "interfaces_CpmCommon.rb"
require "Robot.rb"
load "commonTaskParams.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
    "DataLinkDataOutput" => InterfaceDefs_CpmCommon::DataLinkDataOutput,
    "AppRegInput" => InterfaceDefs_CpmCommon::AppRegInput,
    "AppRegOutput" => InterfaceDefs_CpmCommon::AppRegOutput,
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "loggerThreshold" => "error",  ##  All options listed in descending severity order
                                 ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug
  "cycleRate_hz" => 5,
  "PgtClientFid" => 0x00160000,
  "ClientSessionTimeOut" => 30,		# value in seconds
  # bmiEthernet config file path, parameter and ecm configurations are given in this JSON file
  # Correct.rb file should have this path
  #"BMI_ETH_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/EthernetPgtServerTest.json"

} )

Execution = {
  "executableName" => "bmiEthernet",
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
