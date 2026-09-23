require "Acd2Task_SEAManager_Base.rb"

module SEANvmKeys
  SEA_HMS = "SEA_Surround_Vision_System"
  SEA_TMS = "SEA_Tire_Monitoring_System"
  SEA_MWL_1 = "SEA_Production_Measurement"
  SEA_MWL_2 = "SEA_Production_Measurement_Level_2"
  SEA_CFU_1 = "SEA_Guidance_Assisted_Steering_System"
  SEA_CFU_2 = "SEA_Co-Pilot_System_2"
  SEA_CFU_3 = "SEA_Autopilot_System"
end

# TaskPlugin configuration
SEAManager = {
  # Flag for enabling/disabling the plugin
  "enabled" => true,

  # Publish rate of SEAStatus
  "cycleRate_hz" => 1,

  ### SEA (Premium Software Feature) Configuration ###
  # Key - Name of the feature, for debugging
  # NvmKey - Must exactly match a key in the NvmBLockConfig
  # ReasonCode - Reason Code
  # PermInstallPID - PID to indicate if the feature is Installed. Will be automatically registered for Tx/Wr MAP
  # PermEnablePID - (Optional) PID to indicate if the feature is Enabled. If not included, feature will be Enabled whenever it is Installed. Will be automatically registered for Tx/Wr MAP
  # SecurityLvl - Security Level, currently Level 2 is the highest supported
  # EncByte - Encoding Byte
  # EncBit - Encoding bit
  # TempInstallPID - (Optional) PID to indicate if the feature is temporarily Installed (Free Use). If included, TempCounterPID so mush TempCounterPID
  # TempCounterPID, TempCounterHrs - (Optional) PID to track how long the feature is temporarily Installed and the initial value of the PID in hours.
  # Tracking - (Optional) Flag to indicate if FPS from/to tracking featureis enabled. Defaults to false
  # TxEnabled - (Optional) SEA library only provides Tx with MAP. To support other protocols (ADT, PGB), set this to true. Defaults to false.
  # EnableDSIWhenNotInstalled - (Optional) When the feature is uninstalled at startup, set PermEnablePID to DSI, otherwise set as normal. Defaults to false.
  #                            NOTE: This will result in the PermEnablePID not being registered with scl_prmsw
  # RxPermInstallPID - (Optional) PID that is registerd for Rx in DatalinkManager. When this value is received as Installed, the reason code is installed, otherwise it is uninstalled
  # RxPermEnablePID - (Optional) PID that is registerd for Rx in DatalinkManager. When this value is received as Enabled, the reason code is enabled, otherwise it is disabled
  # ParentReasonCode - (Optional) If included, the feature will not be added to the SEA library unless the feature corresponding to ParentReasonCode is Installed & Enabled
  "SEAConfig" => {

    # Example from CPM HMS
    "<SEA> Surround Vision System" => {
      SEAKeys::NvmKey           => SEANvmKeys::SEA_HMS,
      SEAKeys::ReasonCode       => 272,
      SEAKeys::PermInstallPID   => 0xD11A32,
      SEAKeys::PermEnablePID    => 0xD11A33,
      SEAKeys::SecurityLvl      => 1,
      SEAKeys::EncByte          => 1,
      SEAKeys::EncBit           => 1,
      SEAKeys::TempInstallPID   => 0xD11A34,
      SEAKeys::TempCounterPID   => 0xD0289C,
      SEAKeys::TempCounterHrs   => 720,
      SEAKeys::TrackingEnabled  => true,
      SEAKeys::TxEnabled        => true,
    },

    # Example from TMS with EnableDSIWhenNotInstalled
    "<SEA> Tire Monitoring System" => {
      SEAKeys::NvmKey           => SEANvmKeys::SEA_TMS,
      SEAKeys::ReasonCode       => 160,
      SEAKeys::PermInstallPID   => 0xD10DBD,
      SEAKeys::PermEnablePID    => 0xD10DC3,
      SEAKeys::SecurityLvl      => 1,
      SEAKeys::EncByte          => 1,
      SEAKeys::EncBit           => 1,
      SEAKeys::EnableDSIWhenNotInstalled => true,
      SEAKeys::TxEnabled        => true,
      # SEAKeys::RxPermInstallPID => 0xD10DBD,  # Uncomment for debugging
    },

    # Example from CPM MWL with a single RxPermEnablePID tied to multiple reason codes
    "<SEA> Production Measurement Feature" => {
      SEAKeys::NvmKey           => SEANvmKeys::SEA_MWL_1,
      SEAKeys::ReasonCode       => 149,
      SEAKeys::PermInstallPID   => 0xD10DA0,
      SEAKeys::PermEnablePID    => 0xD10EE7,
      SEAKeys::SecurityLvl      => 1,
      SEAKeys::EncByte          => 1,
      SEAKeys::EncBit           => 1,
      SEAKeys::RxPermInstallPID => 0xD11884,
      SEAKeys::RxPermEnablePID  => 0xD10EE7,
    },

    "<SEA> Production Measurement Level 2 Feature" => {
      SEAKeys::NvmKey           => SEANvmKeys::SEA_MWL_2,
      SEAKeys::ReasonCode       => 245,
      SEAKeys::PermInstallPID   => 0xD11884,
      SEAKeys::SecurityLvl      => 1,
      SEAKeys::EncByte          => 1,
      SEAKeys::EncBit           => 2,
      SEAKeys::TempInstallPID   => 0xD11887,
      SEAKeys::TempCounterPID   => 0xD02654,
      SEAKeys::TempCounterHrs   => 250,
      SEAKeys::RxPermInstallPID => 0xD11884,
      SEAKeys::RxPermEnablePID  => 0xD10EE7,
    },

    # Examples from CFU with ParentReasonCode
    "<SEA> Guidance Assisted Steering System" => {
      SEAKeys::NvmKey           => SEANvmKeys::SEA_CFU_1,
      SEAKeys::ReasonCode       => 240,
      SEAKeys::PermInstallPID   => 0xD1182A,
      SEAKeys::PermEnablePID    => 0xD1182B,
      SEAKeys::SecurityLvl      => 0,
      SEAKeys::EncByte          => 1,
      SEAKeys::EncBit           => 1,
      # SEAKeys::RxPermInstallPID => 0xD1182A,  # Uncomment for debugging
    },

    "<SEA> Co-Pilot System" => {
      SEAKeys::NvmKey           => SEANvmKeys::SEA_CFU_2,
      SEAKeys::ReasonCode       => 241,
      SEAKeys::PermInstallPID   => 0xD1182D,
      SEAKeys::PermEnablePID    => 0xD1182E,
      SEAKeys::SecurityLvl      => 0,
      SEAKeys::EncByte          => 1,
      SEAKeys::EncBit           => 2,
      SEAKeys::ParentReasonCode => 240,
      # SEAKeys::RxPermInstallPID => 0xD1182D,  # Uncomment for debugging
    },

    "<SEA> Autopilot System" => {
      SEAKeys::NvmKey           => SEANvmKeys::SEA_CFU_3,
      SEAKeys::ReasonCode       => 242,
      SEAKeys::PermInstallPID   => 0xD11831,
      SEAKeys::PermEnablePID    => 0xD11832,
      SEAKeys::SecurityLvl      => 0,
      SEAKeys::EncByte          => 1,
      SEAKeys::EncBit           => 3,
      SEAKeys::ParentReasonCode => 241,
    },

  },
}

###################
### NVM Manager
###################

# The file will be save as "nvmPath"/<Key>".txt"
# Size - Size in bytes of the file. Optional for Diagnostics, BDT, NVM (will be calculated automatically if not included or set to 0)
# Type - Type of block, used to determine the Block ID (BID). NvmBlockType is defined in Acd2Task_NvmManager_Enums.rb
# Integrity - (Optional) How the data is stored in NVM, if not included RAW is used by default
NvmBlockConfig.update({
  # SEA suffixes must match keys from SEAManager::SEAConfig section
  SEANvmKeys::SEA_HMS                    => { "Type" => NvmBlockType::SEA, "Integrity" => NvmBlockIntegrity::RAW, },
  SEANvmKeys::SEA_TMS                    => { "Type" => NvmBlockType::SEA, "Integrity" => NvmBlockIntegrity::RAW, },
  SEANvmKeys::SEA_MWL_1                  => { "Type" => NvmBlockType::SEA, "Integrity" => NvmBlockIntegrity::RAW, },
  SEANvmKeys::SEA_MWL_2                  => { "Type" => NvmBlockType::SEA, "Integrity" => NvmBlockIntegrity::RAW, },
  SEANvmKeys::SEA_CFU_1                  => { "Type" => NvmBlockType::SEA, "Integrity" => NvmBlockIntegrity::RAW, },
  SEANvmKeys::SEA_CFU_2                  => { "Type" => NvmBlockType::SEA, "Integrity" => NvmBlockIntegrity::RAW, },
  SEANvmKeys::SEA_CFU_3                  => { "Type" => NvmBlockType::SEA, "Integrity" => NvmBlockIntegrity::RAW, },
})
