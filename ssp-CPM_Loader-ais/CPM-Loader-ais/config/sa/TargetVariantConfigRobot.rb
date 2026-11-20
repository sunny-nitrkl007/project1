#######################################################################
# Contains target variant specific configurations for Robot for example;
# 	standalone(sa) vs advanced(adv)
#
#######################################################################

# The BMI J1939 configuration files
if (not(MachineSpecificConfig.key?("BMI_J1939_CONFIG_JSON_FILE_PATH")))
    # This is the default J1939 config
    MachineSpecificConfig["BMI_J1939_CONFIG_JSON_FILE_PATH"] = ENV["CAT_CONFIG_DIR"] + "/BmiJ1939_MWL_SA.json"
end

