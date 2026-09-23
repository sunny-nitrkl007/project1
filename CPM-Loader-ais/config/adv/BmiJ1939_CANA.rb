require "commonLoad"
require "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"
require "Robot.rb"

MachineSpecificConfig.update("BMI_J1939_CONFIG_JSON_FILE_PATH"=> ENV["CAT_CONFIG_DIR"] + "/BmiJ1939_MWL_ADV_CANA.json")

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

   # This affects how long cleanup() will wait for other apps to
   # unregister.  Longer than this and this app will shut down
   # even if there are other apps still registered with it.
   # This is set to 32 minutes because the maximum amount of time
   # the engine can run after the key is shut off is 30 minutes.
   # We would like to be able to stay alive until the engine shuts down.
   "BmiJ1939AppKeyoffTimeout" => 1920000,

} )

Execution = {
  "executableName" => "bmiJ1939_CANA",
}
