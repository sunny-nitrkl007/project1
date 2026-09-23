# Already defined in Acd2Task_Base.rb, must be enabled for Acd2 to communicate with ET
SystemInfo.update({
  # Flag for enabling/disabling the plugin
  "enabled" => true,

  # CAT Electronic Technician (CAT ET) and ECM discovery settings
  "ServiceSupport" => {

    # Device ID (CAT EXT 0xF016) for J1939
    # Ref SE.COM.PresLayer.IRD00248
    "DeviceID_J1939" => {
      # Analysis  : 0x9601 0000 0600 (each field is LSB First)

      # Device ID can be copy/pasted directly from the Report Generator...
      "deviceId" => 0x960100000600,

      # or split up into separate fields (MSB First):
      # "MID"        => 0x0196,       # Module ID for ECM Function
      # "ST_chg_lvl" => 0x0000,       # Service Tool Support Change Level
      # "ST_app_num" => 0x0006,       # Application Code

      "deviceIDversion" => 0,         # 0 => Device ID Format, 1 => Device ID Format & Minimum Allowed Change Level Support. 2 => Functional ID. Defaults to 0 if not set
      # "ST_chg_lvl_min" => 0x0000,   # (deviceIDversion >= 1) Minimum Allowed Change Level Support.
      # "functionalID" => 0x0006FF00, # (deviceIDversion == 2) Functional ID (NOT YET SUPPORTED BY ET) (Ref SE.COM 10034)
      #                     ^^^^        Application Function
      #                         ^^      Application Function Instance
      #                           ^^    ECU Instance
    },

    # Device ID Code (PID $80) for CDL
    # Ref SE.COM.SessLayer.IRD00083
    "DeviceID_CDL" => {
      # Analysis  : 0x4A00 0000 0F00 (each field is LSB First)

      # Device ID can be copy/pasted directly from the Report Generator...
      # "deviceId" => 0x4A0000000F00,

      # or split up into separate fields (MSB First):
      "MID"        => 0x004A,       # Device ID Module ID
      "ST_chg_lvl" => 0x0000,       # Service Tool Support Change Level
      "ST_app_num" => 0x000F,       # Device ID Application ID
   },

    # Flag to support CAT Electronic Technician (CAT ET), ECM Discovery over J1939
    # Configures for Tx and automatically populates CAT EXT ID 0xF016, 0xF0A6, and 0xF01A
    # DatalinkManager => J1939 => serverEnabled must be set to true
    # Defaults to true if not set
    "j1939Enabled" => true,
  
    # Flag to support CAT Electronic Technician (CAT ET), ECM Discovery over CDL
    # Configures for Tx and automatically populates PIDs 0x80, 0xF811, and 0xF827
    # DatalinkManager => CDL => serverEnabled must be set to true
    # Defaults to false if not set
    "cdlEnabled" => false,
  
    # When set to true, sets ECM Serial Number PID 0xF811 to the same 16-bit value as
    # in CAT EXT ID 0xF01A. This does not adhere to the PID definition and is
    # a workaround for ET to identify an ECM with both J1939 and CDL as a single entity.
    # Defaults to false if not set
    "syncEcmSerialNumbers" => false,

    # Preferred CDL PID Read/Write Method (Byte 1) from ECM Communication Preference CAT EXT ID 0xF0A6
    # MAP or CDL_PID, defaults to MAP if not set
    # NOTE: CDL_PID is incompatible with the SEA/premium software library
    "j1939ReadWriteMethod" => SystemInfoWriteMethod::MAP,
  },

  # Configures for Tx and automatically populates CAT EXT ID 0xF019 if the J1939 server is enabled,
  # and/or PIDs 0xF849, 0xF84A, and 0xF84B if the CDL server is enabled.
  # Defaults to true
  "swGroupInfoTxEnabled" => true,

  # List of PIDs to support for Tx
  # Uncomment the desired PIDs
  "enabledPIDs" => [
    SystemInfoPID::ProductId,                       # $F82D
    # SystemInfoPID::ECMLocationCode,                 # $F2C4
    # SystemInfoPID::DesiredECMLocationCode,          # $F2C5
    # SystemInfoPID::MachineSystemVoltage,            # $F42A
    # SystemInfoPID::NumberOfAvailableEthernetPorts,  # $D0246C, Note that this is incompatible with DatalinkManager["Diagnostics"]["ethernetPortStatisticsBdtEnabled"]
  ],

  # Software Identification PGN 0xFEDA
  # Will be transmitted in an * delimited format, e.g. VER:5735401-06*<appSpecificFields>*
  # Where VER is software part number
  "SoftwareIdPGN" => {
    # Configure the PGN for Tx, defaults to false
    "enabled" => false,

    # Application speciic fields, multiple fields must be * delimited
    "appSpecificFields" => "PROT_VER:1.0.0",
  },

  # hostname to filter SystemHardwareHealth for providing "remote" ECM info to a client (ET).
  # If not specified, the local ECM info is provided
  # "ecmInfoHostName" => "A6N2-1",

  # Value to write to $F2C5, must be set if SystemInfoPID::DesiredECMLocationCode is enabled
  "desiredLocationCode" => 1,

  # Maximum size for ECM Part Number in CAT EXT ID 0xF01A. Defaults to 10 to resolve Telematics issue with zero padding
  "ecmPartNumberMaxSize" => 10,

  # Maximum size for ECM Serial Number CAT EXT ID in 0xF01A. Defaults to 16 to resolve truncation issue (A6/D6 max size is 16)
  "ecmSerialNumberMaxSize" => 16,

  # Flexible Parameters (ref SE.COM.PresLayer.IRD00005)
  "FlexibleParameters" => {

    # If disabled, all parameter configs are ignored
    "enabled" => false,

    # Parameter configs
    "parameters" => {

      # Key is the PID Name, for debugging only
      "Flex PID 1" => {

        # Parameter Identifier
        Datalink::Keys::ID => 0xF7F8,

        # Parameter Type
        Datalink::Keys::PARAMETER_TYPE => Datalink::ParameterType::PID,

        # Security settings
        Datalink::Keys::SECURITY_SETTINGS => {
            # The Read Security is the security level to which the device must be raised
            # before it allows reading of data associated with the information
            # identifier. The default Read Security is generally assumed to be one
            # (service tool access). 
            
            # Read Security is not supported by ET hence flexed in security value will
            # not be used by ET to raise the security level. If an application sets
            # read security level for a parameter higher than ET recognizes ET will
            # not be able to show the parameter since the read security level can not
            # be flexed in.
            Datalink::Keys::READ_SECURITY => Datalink::Flex::Security::NO_SECURITY,

            # The Write Security is the security level to which the device must be
            # raised before it allows programming of data associated with the
            # information identifier. The default Write Security is generally assumed to
            # be one (service tool access).
            # If not provided, defaults to 0xFF (NO_OP)
            Datalink::Keys::WRITE_SECURITY => Datalink::Flex::Security::NO_OP,

            # The Reason Code is a code used by the Factory Password System to allow
            # tracking and proper billing of security-enforced activities on a device. A
            # Reason Code need only be specified if security level 3 is required for
            # reading or writing of an information identifier. If security level 3 is
            # not required for any operations then the Reason Code field should be
            # filled with all binary 1s. The System Standards Facilitator maintains
            # the list of Reason Codes.
            # If not provided, defaults to 0xFF (NA)
            Datalink::Keys::REASON_CODE => Datalink::Flex::Security::NA,
        },

        # The label is a text description associated with an information identifier
        # that provides an end user with meaningful information to determine what
        # the identifier is attempting to convey. Only ASCII is currently supported.
        Datalink::Keys::LABEL => "Flex PID 1",

        # Miscellaneous characteristics that further describe the parameter.
        # An array of Flex::ParameterMisc.
        # If not included, scl_flex_add_pid will not be called
        Datalink::Keys::PARAMETER_MISC => [
            # Datalink::Flex::ParameterMisc::CONFIG_S,
            Datalink::Flex::ParameterMisc::STATUS_S,
            Datalink::Flex::ParameterMisc::DECIMAL_PRECISION_1
        ],

        # Communication Settings
        # The parameter communications data components are used to specify atypical or
        # non-default parameter communication mechanisms used by the ECM. These
        # mechanisms may be data link dependent or data link independent, and send only
        # a single parameter identifier.
        # An array of of Flex::CommSettings
        Datalink::Keys::COMM_SETTINGS => [
            Datalink::Flex::CommSettings::J1939_MA_RD_S
        ],
      },
    },
  },
})

# Populate Metadata and Tx Configs based on enabledPIDS
# Must be loaded after SystemInfo is defined
load "Acd2Task_SystemInfo_Post.rb"
