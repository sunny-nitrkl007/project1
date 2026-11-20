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
  

  # BmiCdl config file path, parameter and ecm configurations are given in this JSON file
  # Correct.rb file should have this path
  #"BMI_CDL_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiCdlCfg.json"

} )

Execution = {
  "executableName" => "bmiCdl",
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
