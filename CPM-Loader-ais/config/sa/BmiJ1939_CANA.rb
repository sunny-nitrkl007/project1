require "commonLoad"
require "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"
require "Robot.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
   "DataLinkDataOutput" => InterfaceDefs_CpmCommon::DataLinkDataOutput,
   "AppRegInput" => InterfaceDefs_CpmCommon::AppRegInput,
   "AppRegOutput" => InterfaceDefs_CpmCommon::AppRegOutput,
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
   # AIS-required configuration
   "loggerThreshold" => "error",  ##  All options listed in descending severity order
                                   ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug
   "cycleRate_hz" => 5,
  # Valid values:
  #     0 - can0 or CAN1 or CAN A
  #     1 - can1 or CAN2 or CAN B

  "CAN_port" => 0,
  "J1939_Preferred_Address" => 0x84,
} )

# BmiJ1939 config JSON file paths, uncomment for testing
#MachineSpecificConfig = { 

#"BMI_J1939_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiJ1939Cfg_Example.json",
 
#}

Execution = {
  "executableName" => "bmiJ1939_CANA",
}

