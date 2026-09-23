require "Acd2Task_DatalinkManager_Enums.rb"

# TaskPlugin configuration
DatalinkManager = {
  # Flag for enabling/disabling the plugin
  "enabled" => true,

  # Timeout factor for all Rx parameters not covered by J1939 Read/Poll, e.g. PGN broadcast, PGB, Ethernet PGT
  # Multipied by the request rate of the parameter to calculate the timeout period
  # Defaults to 2.5
  "rxTimeoutFactor" => 2.5,

  # Maximum number of seconds after startup to let datalink discovery to run when multiple J1939 SAs are configured.
  # Discovery process might end sooner if all parameters are discovered.
  "discoveryPeriodSec" => 6,

  # J1939 specific configuration settings
  "J1939" => {
    # CAN ports to configure
    # Valid values: One or more of Datalink::Port::CAN1,2,3,4
    #
    "canPorts" => [
      Datalink::Port::CAN1,
      # Datalink::Port::CAN2,
      # Datalink::Port::CAN3,
      # Datalink::Port::CAN4,
    ],

    # CAN port for DM13
    # Valid values: Datalink::Port::CAN1,2,3,4
    # Defaults to the first entry in canPorts.
    "canPortDM13" => Datalink::Port::CAN1,

    # CAN port for EDDT (diagnostic) server
    # Valid values: Datalink::Port::CAN1/2/3/4
    # Defaults to the first entry in canPorts.
    "canPortEDDT" => Datalink::Port::CAN1,

    # CAN port for SEA/FPS (Software Enabled Feature/Feature Protection System)
    # Valid values: Datalink::Port::CAN1/2/3/4
    # Defaults to canPortEDDT.
    "canPortSEA" => Datalink::Port::CAN1,

    # List of Server Names or J1939 Source Addresses  from which to ignore DM13 suspend messages, to prevent inhibiting all diagnostics
    # This should only be typically used if no parameters are requested from this Server
    # "dm13AddressExclusion" => ["Telematics", "Productivity", ],
    # OR
    # "dm13AddressExclusion" => [0x25, 0x41, ],

    # Timeout period for CAT EXT ID/PGN read/poll, so a failed read does not block forever
    "readTimeoutPeriodMs" => 200,

    # This number will be added to the # of MAP parameters to determine the total number of MAP Handlers to configure
    "mapHandlerBufferSize" => 20,

    # Delay from startup before starting diagnostic/health monitoring, defaults to 30000 milliseconds if not specified
    "diagnosticsStartupDelayMs" => 30000,

    # J1939 Statistics AIS_LOG_INFO rate in milliseconds, if 0 nothing will be logged
    "statisticsLogRateMs" => 0,

    # J1939 Link Settings for each CAN port. Values below are the default if not included
    "LinkSettings" => {
      Datalink::Port::CAN1 => {
        "nodes" => 35,      # Maximum number of nodes on the network (including Virtual ECMs)
        "mbufs" => 100,     # Number of Message Buffer (MBuf) headers to be allocated for this link.
        "extensions" => 40, # Number of MBuf extensions (105 bytes each) to be allocated for this link.  Used only for messages with more than 8 bytes of data.
        "tpcbs" => 15,      # Number of Transport Protocol Control Blocks (TPCBs) to be allocated for this link.  A TPCB is used for each TP connection for which the link is engaged.
        "connections" => 10,  # The number of connections to preallocate and initialize.
        "servicesPerConnection" => 10, # The number of services to allocate per connection.
        "packetObjects" => 150, # The number of objects to pre-allocate in heap memory for packets.
        "packetReaderObjects" => 350, # The number of objects to pre-allocate in heap memory for the packet reader.
        # PGB Settings
        "pgbRxConnections" => 20, # The maximum number of client connection at any given time this ECM supports.
        "pgbTxConnections" => 40, # The maximum number of server connection at any given time this ECM supports.
        "pgbRxGroups" => 20, # The maximum number of received groups that will be used by all clients at any given time.
        "pgbTxGroups" => 80, # The maximum number of transmitted groups that will be used by all servers at any given time. If a client is reporting DSI 16, this value should be increased
        "pgbBroadcasts" => 80, # TThe maximum number of broadcast groups that will be supported by all servers at any given time.  A broadcast group is defined as a holder for all transmitted groups that occur at a particular broadcast rate.
      },
    },

    # The maximum number of MA sessions, should be the largest number of concurrent sessions expected for all virtual ECMs. Defaults to 4.
    # 1) RTC
    # 2) ET
    # 3) Any MAP parameters in the Rx pool
    # 4+) Any read/write requests from external ECMs
    "maxMASessions" => 6,
  },

  # CDL specific configuration settings
  "CDL" => {
    # Flag to enable/disable CDL Server. Client is enabled/disabled based on DatalinkManager_Rx config
    # NOTE: Due to a bug/limitation in a common services library, enabling the CDL ADT Server requires that 
    #       this ECM request at least one PID over CDL (i.e. there must be at least one entry in the DatalinkParameterRxConfig)
    "serverEnabled" => false,

    # Module Identifier (MID) of the ECM
    "mid" => 0xA2,
  },

  # Ethernet (PGT) specific configuration settings
  "Ethernet" => {
    # Flag to enable/disable Ethernet PGT Server. Client is enabled/disabled based on DatalinkManager_Rx config
    "serverEnabled" => false,

    # Network interface name, defaults to eth0.20
    "interfaceName" => "eth0.20",

    # Needed for PGT Server and Client Health. IP address is obtained through linux API
    "localFid" => 0x00050000,

    # Delay from startup before starting diagnostic/health monitoring, defaults to 30000 milliseconds if not specified
    "diagnosticsStartupDelayMs" => 30000,

    # Used for csf_http_server.
    # Defaults to 1
    "httpdNumConnections" => 1,

    # Argument for csf_eth_health_client_add_splv2, the amount of idle time in seconds before server closes the session
    # Setting this to a very high number (e.g. 30000) currently results in a server side overflow issue with intermittent FMI 9
    # Defaults to 30 per CSNS recommendation
    "clientSessionTimeoutSec" => 30,
  },

  # CDA settings
  "CDA" => {
    # Timeout value in milliseconds for connection to CDA server application. Defaults to 50
    # "serverTimeoutMs" => 50,

    ### IPAddress of server. Optional: if not included, discovery is used (assumes only a single server in the system)
    # "serverAddress" => IPAddressMap["localhost"],  # local
    # "serverAddress" => IPAddressMap["A6N2-0"],     # remote

    ### Port of server, not needed with latest CDA server (defaults to 50006)
    # "serverPort" => 50006,
  },

  # Block Data Transfer specific configuration settings
  "BDT" => {
    # Flag to enable/disable BDT. Defaults to true
    # Even when disabled, canPort must be set to a valid port.
    "enabled" => true,

    # CAN Port that BDT will be sent over
    "canPort" =>  Datalink::Port::CAN1,

    # bdt_init arguments
    "numRxCon" => 4,
    "rxBufSize" => 200,
    "numTxCon" => 4,
    "txBufSize" => 200,
    "numDataLinkCon" => 3,

    # bdt_set_callback_block_count arguments
    # IMPORTANT: Must account for all libraries that use BDT (Diagnostics, Flexible Paramters, etc...)
    "callbackBlockCount" => 4,

    # bdt_set_datatype_count arguments.
    # IMPORTANT: Must account for ALL supported BDTs (each library can use multiple BDTs)
    "datatypeCount" => 20,
  
    # bdt_action_init arguments
    "maxSimultaneousClients" => 2,

    # BDT Remote support
    "Remote" => {
      # DatalinkManager communicates with ET but requests BDTs from another source
      "consumerDataTypes" => [
        # Datalink::BdtDataType::DATALINK_DIAGNOSTICS,
      ],

      # DatalinkManager generates BDTs but does not communicate with ET
      "producerDataTypes" => [
        # Datalink::BdtDataType::DATALINK_DIAGNOSTICS,
      ],
    },

    # # (Optional) Application (i.e. non CSNS) BDT records
    # "records" => {
    #   # Name of the record, for debugging
    #   "Application History Record" => {
  
    #     # Datatype of the BDT, Application History Record in this example
    #     "datatype" => 0xCA11,
  
    #     # (Optional) Raw Byte array of the BDT that case be used for debugging, Operator Coaching Tip History (0x00000311) in this example
    #     "data" => [0xB1, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xCA, 0x11, 0x01, 0x04, 0x00, 0x00, 0x00, 0x01, 0xCA, 0x11, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0xEB, 0x00, 0x0F, 0x01, 0x00, 0x00, 0x03, 0x11, 0x00, 0x02, 0x40, 0x25, 0x00, 0x00, 0x48, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x4A, 0x26, 0x00, 0x09, 0x00, 0x00, 0x03, 0xFA, 0x00, 0x00, 0x00, 0x03, 0xF6, 0x00, 0x00, 0x00, 0x10, 0x3F, 0x00, 0x00, 0x00, 0x07, 0x2E, 0x00, 0x00, 0x00, 0x03, 0x16, 0x00, 0x00, 0x00, 0x00, 0x75, 0x00, 0x00, 0x00, 0x07, 0x2F, 0x00, 0x00, 0x00, 0x07, 0x30, 0x00, 0x00, 0x00, 0x05, 0xE2, 0x00, 0x40, 0x26, 0x00, 0x09, 0x00, 0x00, 0x03, 0xFA, 0x02, 0x08, 0xFF, 0xFF, 0x01, 0x01, 0x2A, 0x00, 0x00, 0x03, 0xF6, 0x02, 0x08, 0xFF, 0xFF, 0x01, 0x01, 0x2A, 0x00, 0x00, 0x10, 0x3F, 0x02, 0x08, 0x00, 0x10, 0x0A, 0x01, 0x05, 0x00, 0x00, 0x07, 0x2E, 0x02, 0x00, 0x00, 0x20, 0x03, 0x02, 0x00, 0x56, 0x00, 0x00, 0x03, 0x16, 0x02, 0x08, 0x00, 0x40, 0x11, 0x02, 0x01, 0x07, 0x00, 0x00, 0x00, 0x75, 0x02, 0x00, 0x00, 0x20, 0x03, 0x02, 0x16, 0x0F, 0x00, 0x00, 0x07, 0x2F, 0x02, 0x20, 0x00, 0x20, 0x05, 0x02, 0x1E, 0x0A, 0x00, 0x00, 0x07, 0x30, 0x02, 0x20, 0x00, 0x20, 0x05, 0x02, 0x1E, 0x0A, 0x00, 0x00, 0x05, 0xE2, 0x02, 0x08, 0x00, 0x10, 0x0A, 0x01, 0x05, 0x40, 0x21, 0x00, 0x01, 0x48, 0x65, 0x6E, 0x72, 0x79, 0x2A, 0x54, 0x69, 0x70, 0x6E, 0x75, 0x6D, 0x30, 0x31, 0x2A, 0x00, 0x0B, 0x08, 0x00, 0x00, 0x00, 0x07, 0xE4, 0x09, 0x18, 0x54, 0x09, 0x28, 0x1E, 0x88, 0xAF, 0x12, 0x01, 0x00, 0xE9, 0xA4, 0x35, 0x00, 0xD2, 0x49, 0x6B, 0x01, 0xAC, ]
    #   },
    # },
  },

  # Diagnostics specific configuration settings
  "Diagnostics" => {
    # Map CAN ports to Component ID for J1939 diagnostics (CAN# may not directly map to Datalink# in a system)
    # CAN1/2/3/4 => Datalink::DiagnosticId::J1939Datalink[2,3,4]
    "canComponentIds" => {
      Datalink::Port::CAN1 => Datalink::DiagnosticId::J1939Datalink,
      Datalink::Port::CAN2 => Datalink::DiagnosticId::J1939Datalink2,
      Datalink::Port::CAN3 => Datalink::DiagnosticId::J1939Datalink3,
      Datalink::Port::CAN4 => Datalink::DiagnosticId::J1939Datalink4,
    },

    # Component ID for Ethernet diagnostics
    "ethernetComponentId" => Datalink::DiagnosticId::Ethernet,

    # Flags for enabling Datalink Diagnostics BDTs
    # Note: If ACD2 is acting as a BDT remote consumer, these flags should both be false
    "ethernetDiagnosticsBdtEnabled" => false,
    "j1939DiagnosticsBdtEnabled" => true,

    # Flag for enabling Ethernet Port Statistics BDT
    "ethernetPortStatisticsBdtEnabled" => true,

    # Flag for enabling CDL diagnostics, defaults to true
    "cdlDiagnosticsEnabled" => true,
  },

  # CAN over UDP. This section can be removed or commented out if this protocol is not used
  "UDP_CAN" => {
    # Rx (receive) config
    "RxConfig" => {
      # Used by UdpInput::initialize
      "UDPRxPort" => "3753",

      # Map Message Name to CAN_ID
      "messages" => {
        "HmsPayloadInputs" => 0x480,
      },

      #Put Rx UDP Packet timeouts here. Prefix must match key from "messages"
      "rxTimeouts" => {
        "HmsPayloadInputs_rxTimeout_sec"                   => 5.0,   #480 (20ms txRate)
      },

      # Name of the AutonomyCondition for loss of comms (Abnormal Update Rate - FMI 9). Defaults to MachineControlModuleCommsLost
      "commsLostAutonomyCondition" => "MachineControlModuleCommsLost",

      # Name of the AutonomyCondition for parameter not supported (Special Instruction - FMI 14). Defaults to MachineControlModuleParamMissing
      "paramMissingAutonomyCondition" => "MachineControlModuleParamMissing",

      # (Optional) Used for diagnostics against the Ethernet Datalink, must exactly match a name in the DatalinkManager Server config
      "serverName" => "Engine",
    },

    # Tx (transmit) config
    "TxConfig" => {
      # Used by UdpOutput::initialize
      "UDPTxPort" => "3753",

      # TODO: Add option to automatically set this using ais::network::getIpAddressString()
      "HostName"   => "165.26.79.190",

      #valid range 0-6, see socket(7) man page
      "Priority" => 6,

      # Map Message Name to CAN_ID
      "messages" => {
        "HmsPayloadInputs" => 0x480,
      },

      #Put Tx UDP Packet rates here. Prefix must match key from "messages"
      "txRates" => {
        "HmsPayloadInputs_txRate_sec"                   => 1.0,   #480
      },
    },
  },
}

# ECM J1939 Name
Ecm_J1939_Name = {
  "Industry_Group"          => 3,
  "Vehicle_System"          => 0,
  "Vehicle_System_Instance" => 0,
  "Function"                => 130,
  "Function_Instance"       => 0,
  "ECU_Instance"            => 1,
  "Manufacturer_Code"       => 8,
  "Identity_Number"         => 0x230813,
  "Preferred_Address"       => 0x41,     # J1939 Source Address
  "Address_List"            => [0x9E, 0x9F, 0xA0, 0xA1,], # Maximum 5 entries supported; beyond ignored
}

# Application specific parameters
load "Acd2Task_DatalinkManager_Metadata.rb"   # Database of all needed parameters
load "Acd2Task_DatalinkManager_Servers.rb"    # Database of all external ECM/Servers
load "Acd2Task_DatalinkManager_Rx.rb"         # Application specific Rx configuration
load "Acd2Task_DatalinkManager_Tx.rb"         # Application specific Tx configuration
