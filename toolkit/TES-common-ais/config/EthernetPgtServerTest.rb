require "commonAutonomyTask.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
   "DataLinkDataReceiverInput" => InterfaceDefs_CpmCommon::DataLinkDataInput,
   "DataLinkDataPublisherOutput" => InterfaceDefs_CpmCommon::DataLinkDataOutput,
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
   "requireGPSTimeSynchronizationOnStart" => false, # ALLOW this process to start without synchronization
   "loggerThreshold" => "debug",
   "cycleRate_hz" => 10,
} )

EthernetPgtServer = {
  "enabled" => true,

  "serverFid" => 0x00050000,
  "jsonConfigFile" => "BmiEth_EthernetPgtServerTest.json",

  # csf_http_server
  "httpdNumConnections" => 1,
  "httpdTaskPeriodMs" => 100,  # Set to the same rate as the OEL task
}

EthernetPgtServerTestDataProducer = {
  "enabled" => true,

  # [Key] - Must start with "PID_", "SPN_", or "CAT_EXT_ID_".  The rest of the key is informational only
  # [Param ID] - ID of the parameter
  # [Value Type] - ENG values are in floating point, RAW are in hex, DSI sets the DSI to that value
  # [Value] - ENG/RAW/DSI value to be written

  # [Key]               =>  [Param ID]    [Value Type]  [Value]
  "PID_U8"              => [ "0xF08F",       "ENG",     "18", ],          # Ignition Key Switch Position
  "PID_U8_DSI"          => [ "0xF118",       "ENG",     "229", ],         # Percent Engine Load at Current Engine Speed
  "PID_U8_DSI_MAN"      => [ "0xF014",       "DSI",     "4", ],           # Cooldown Duration
  "PID_S8_POS"          => [ "0x21",         "ENG",     "55", ],          # Full Load Setting
  "PID_S8_NEG"          => [ "0x22",         "ENG",     "-48", ],         # Full Torque Setting
  "PID_S8_DSI"          => [ "0xF1A0",       "RAW",     "0x88", ],        # Governor Actuator High Speed Correction Factor
  "PID_S8_DSI_MAN"      => [ "0xF04C",       "DSI",     "3", ],           # Rear Hitch Lever Position
  "PID_U16"             => [ "0xF5B8",       "ENG",     "12.36", ],       # Body Position Angle
  "PID_U16_RAW"         => [ "0xF5D6",       "RAW",     "0x1234", ],      # Desired Gear
  "PID_U16_DSI"         => [ "0xF605",       "RAW",     "0xFFF2", ],      # Service Brake Status
  "PID_U16_DSI_RAW"     => [ "0xF5D7",       "RAW",     "0xFFE6", ],      # Operator Requested Gear
  "PID_U16_DSI_MAN"     => [ "0x46",         "DSI",     "6", ],           # Desired Engine RPM
  "PID_S16_POS"         => [ "0x40",         "ENG",     "815.5", ],       # Actual Engine RPM
  "PID_S16_NEG"         => [ "0xF48C",       "ENG",     "-10.5", ],       # Machine Articulation Angle
  "PID_S16_DSI_RAW"     => [ "0xF492",       "RAW",     "0x8009", ],      # Elevator Lever Position
  "PID_S16_DSI_MAN"     => [ "0x44",         "DSI",     "5", ],           # Engine Coolant Temperature
  "PID_U32"             => [ "0xFC2D",       "ENG",     "45135.2345", ],  # Total Operating Hours
  "PID_U32_RAW"         => [ "0xFC05",       "RAW",     "0x12345678", ],  # Load Count
  "PID_U32_DSI_RAW"     => [ "0xFC06",       "RAW",     "0xFFFFFFE7", ],  # Total Load Count
  "PID_U32_DSI_MAN"     => [ "0xFC04",       "DSI",     "8", ],           # Transmission Sync Valve Cycles
  "PID_S32_POS"         => [ "0xFC8C",       "ENG",     "87.456123", ],   # Longitude
  "PID_S32_NEG"         => [ "0xFC8D",       "ENG",     "-143.154654", ], # Latitude
  "PID_S32_DSI_RAW"     => [ "0xFC9F",       "RAW",     "0x080000012", ], # Altitude
  "PID_S32_DSI_MAN"     => [ "0xFC0F",       "DSI",     "7", ],           # Generator Total Real Power

  #### SPN and CAT_EXT_ID not yet supported  ####

  # "SPN_01" => [ "0x45", "33", ],       # Two Speed Axle Switch
  # "SPN_02" => [ "0xBE", "22.250", ],   # Engine Speed

  # CAT EXT ID data must be in hex format
  # "CAT_EXT_ID_01" => [ "0x00", "0x55", ],   # BMI_CDL_CAT_EXT_CHASSIS_00 Speed
}

Execution = {
  "executableName" => "ethernetPgtServerTest",
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
