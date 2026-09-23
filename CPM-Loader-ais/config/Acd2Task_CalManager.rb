# Enums are in a separate file in case needed by multiple plugins
require "Acd2Task_DatalinkManager_Enums.rb"

Interfaces.update({
  "CalManagerRequestOutput" => InterfaceDefs::CalManagerRequestOutput,
  "CalManagerResponseInput" => InterfaceDefs::CalManagerResponseInput,
  "CalibrationRequestUIInput" => InterfaceDefs::CalibrationRequestUIInput,
  "CalibrationResponseUIOutput" => InterfaceDefs::CalibrationResponseUIOutput,
})

# TaskPlugin configuration
CalManager = {
  # Flag for enabling/disabling the plugin
  "enabled" => true,

  # J1939 specific configuration settings
  "J1939" => {
    # Flag to enable/disable calibration over J1939
    "enabled" => true,

    # CAN ports to configure
    # Valid values: Datalink::Port::CAN1,2,3,4
    #
    "canPort" => Datalink::Port::CAN1,

  },

  # CDL specific configuration settings
  "CDL" => {
    # Flag to enable/disable calibration over CDL
    "enabled" => false,
  },

  # Calibration IDs
  # Key is the ID name, used for debugging only
  "CalibrationIDs" => {
    "TEST_CAL_ID_1" => 0x0355,
  },

  # Set to True to enable UI/Display Calibration
  # Defaults to false 
  "uiCalibrationEnabled" => true,

  # Module ID, currently only used for UI Calibration (cal_any_rx_hdlr)
  "MID" => 0xFA,

  # Qualified Data parameters with values known at compile time. These still must be added to the DatalinkManager config
  # If the values are calculated at runtime, they instead must be set by the application through DatalinkManagerInterface
  # Values are in engineering units
  # Key is the parameter name, used for debugging only
  # Key is the PID
  # Each desired Qualified Data Type is mapped to its default value
  "QualifiedDataValues" => {

    "Hydraulic Oil Temperature" => {
      Datalink::Keys::ID => 0x45,
      "Values" => { # Degrees C
        Datalink::QualifiedDataType::MIN_POSSIBLE => 40.0,
      }
    },

    "Lift Cylinder Velocity" => {
      Datalink::Keys::ID => 0xD01961,
      "Values" => { # mm/sec
        Datalink::QualifiedDataType::MIN_POSSIBLE => -25.0,
        Datalink::QualifiedDataType::CALIBRATION => 25.0,
      }
    },
  },
}
