require "commonLoad"
load "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"


## Set appdata paths
AppDataBase = "/opt/appdata"
VerityDirectoryName = ENV["CAT_DIR"].split("/").last              # Last directory in the path
ThisAppName = File.basename( __FILE__, File.extname(__FILE__) )   # Script name without extension
AppDataPath = AppDataBase + "/" + VerityDirectoryName + "/" + ThisAppName
TxPath = AppDataPath + "/TxFiles/";
RxPath = AppDataPath + "/RxFiles/";
LogPath = AppDataPath + "/CDALog/";
unless File.directory? AppDataBase     # This is needed when running from VM (/opt/appdata should always exist in ECM)
  TxPath = RxPath = LogPath = "/tmp/";
end


## Define usable interfaces
Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
   "FileTransferBridgeRequestInput" => InterfaceDefs_CpmCommon::FileTransferBridgeRequestInput,
   "FileTransferBridgeResponseOutput" => InterfaceDefs_CpmCommon::FileTransferBridgeResponseOutput,
   "FileTransferBridgeIndicationOutput" => InterfaceDefs_CpmCommon::FileTransferBridgeIndicationOutput,
   "CreateFileRequestOutput" => InterfaceDefs_CpmCommon::CreateFileRequestOutput,
   "AppRegInput" => InterfaceDefs_CpmCommon::AppRegInput,
   "AppRegOutput" => InterfaceDefs_CpmCommon::AppRegOutput,
   "IoTHubInboundMessageOutput" => InterfaceDefs_CpmCommon::IoTHubCommsInboundMessageOutput,
   "IoTHubOutboundMessageInput" => InterfaceDefs_CpmCommon::IoTHubCommsOutboundMessageInput,
   "IoTHubOutboundReturnOutput" => InterfaceDefs_CpmCommon::IoTHubCommsOutboundReturnOutput,
} )


## Set configuration parameters
Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
   ## === AIS parameters ===
   "loggerThreshold" => "error",

   # This affects the following:
   # - How fast we check for Tx requests from other apps
   # - How frequently we try to reconnect to CDA server
   # It does not need to be 200ms, that is crazy fast.
   # However, the slower it is, the more delay we have
   # in delivering files to CDA server.  The printer
   # is a good use case where the operator expects the
   # printer to start printing shortly after hitting the
   # button.  I am settling on 2Hz (500ms) as a balance.
   # We could slow it down even further if the Tx requests
   # were handled via async callback instead of polling.
   "cycleRate_hz" => 2,

   # When a stall is detected, if the new option is set to
   # true, the process would be forcefully stopped by requesting
   # a sigkill.
   'stalledProcessTimer_s' => 120,
   'restartOnStall' => true,

   ## === App parameters ===
   "PathOutgoing" => TxPath,
   "PathIncoming" => RxPath,
   "PathAppLog" => LogPath,
   "NameAppLog" => "filetransferbridge_log",

   # This affects how long cleanup() will wait for other apps to
   # unregister.  Longer than this and this app will shut down
   # even if there are other apps still registered with it.
   # This is set to 32 minutes because the maximum amount of time
   # the engine can run after the key is shut off is 30 minutes.
   # We would like to be able to stay alive until the engine shuts down.
   "KeyOffTimeOutMSec" => 1920000,

   "SendWithoutScsRequests" => "NO",  ## YES or NO. If set to 'YES' then constantly checks the outgoing folder for files and sends them without requests from other apps

   ## === CDA parameters ===
"ClientConnModeSecure" => "YES",   ## YES or NO. Note: insecure mode only works when CDA Server and Client are running on the same host.
   "ServerIP" => "165.26.78.1",       ## IP address of the CDA server that we should be connecting to
   "CertChainFile" => ENV["CAT_DIR"] + "/certs/CommCAsAll.chain", ## The path to the Certificate Chain file

   ## === Transfer file type parameters ===
   "MaxDataFileSizeInBytes" => 500000,  ## Maximum size of each file; exercise caution with the small queue sizes below
   "FileTypes"=>[
                "FileTypeVp3",
                "FileTypeTruckListv2",
                "FileTypeMaterialListv2",
  		"FileTypeCustomList1",
                "FileTypeCustomList2",
                "FileTypeCustomList3",
                "FileTypeCustomList4",
                "FileTypeConfigFileHashResponse",
                "FileTypeCycleTMAC",
                "FileTypeDipperTMAC",
                "FileTypeLoadTMAC",
                "FileTypeModeTMAC",
                "FileTypePcsCycleTMAC",
                "FileTypePayloadPrint",
                "FileTypeApplicationLog",
                "FileTypeETicket",
                ],

   ## === FID parameters ===
   ## Reference https://datalinks.ecorp.cat.com/Ethernet/ for information about Functional Identifiers
   "FID_ThisApp" => 0x00160000,
   "FID_ProductLink" => 0x00580000,

   ## === IoTHub Comms Parameters ===
   "IoTHubOutboundQueueMaxSize" => 20,
   "IoTHubInboundFileTypes" => [
      10371, # Work Order Assist - GetSitesResponse
      10373, # Work Order Assist - SelectSiteResponse
      10374, # Work Order Assist - SendJobs
      10376, # Work Order Assist - UpdateJobResponse
   ],
} )


## Define all CDA nodes serviceable by the app
module Node
   # CDA/TTI nodes
   BackOffice = 1          # Same value as DestinationMessage_DESTINATION_TELEMATICS
   LocalSiteComms = 2      # Same value as DestinationMessage_DESTINATION_TELEMATICS_SITECOMMS

   # CDA/SFT nodes
   ThisApp = Parameters[ "FID_ThisApp" ]
   ProductLink = Parameters[ "FID_ProductLink" ]
end


## Template for any additional file types: (Note: there are [required] and [optional] fields)
##    "Telematics File Number (File Type)"    - [required] Telematics File Number associated with each file type,
##                                                         e.g. VP3 files have Telematics File Number of 10129
##    "Transmit Queue Size Limit (Bytes)"     - [required] Maximum size of the outgoing queue for this file type.
##                                                         When exceeded the oldest file in the queue gets deleted from the file system.
##    "Receive Queue Size Limit (Bytes)"      - [required] Maximum size of the incoming queue for this file type.
##                                                         When exceeded the oldest file in the queue gets deleted from the file system.
##    "Default Outgoing Traffic Destinations" - [opt/req]  For CDA/SFT this is [optional], for CDA/TTI this is [required]
##                                                         Specifies where the files need to be sent. Includes both CDA/SFT and CDA/TTI nodes.
##                                                         For CDA/SFT: This field can be over-ruled when FidDestination is specificed in SCS object.
##                                                         For CDA/SFT: Omit the field to prevent any default locations.
##                                                         For CDA/TTI files this is [required]
##    "CDA/TTI Server Incoming Traffic Accepted Sources" - [optional] Specifies CDA/TTI Server source nodes that we will accept files from.
##                                                                    Omit to prevent this file type to be received from CDA/TTI Server.
##    "CDA/SFT Incoming Traffic Intended Destinations"   - [optional] Specifies CDA/SFT node FIDs to be expecting incoming files FOR.
##                                                                    The list could include this app as well as other apps running on this system.
##                                                                    If omitted, then NO FILES WILL BE ACCEPTED over CDA/SFT.
##                                                                    If left empty (i.e. []), then the files over CDA/SFT will be accepted for ANY intended FID.
##    "CDA/SFT Incoming Traffic Accepted Sources"        - [optional] Specifies CDA/SFT node FIDs to be expecting incoming files FROM.
##                                                                    Omit to accept files from all sources.
##    "CDA/SFT Report Trigger Sources"                   - [optional] Specifies CDA/SFT node FIDs to be expecting incoming report triggers from.
##                                                                    If left empty (i.e. []), then accepts report triggers from all sources.
FileTypeExample = {
    "Telematics File Number (File Type)" => 12345,
    "Transmit Queue Size Limit (Bytes)" => 10000,
    "Receive Queue Size Limit (Bytes)" => 10000,
    "Default Outgoing Traffic Destinations" => [ Node::BackOffice, Node::LocalSiteComms, Node::ProductLink ],
    "CDA/TTI Server Incoming Traffic Accepted Sources" => [ Node::BackOffice ], ## LocalSiteComms would never send anything
    "CDA/SFT Incoming Traffic Intended Destinations" => [ ], ## Any destination FID on this (or other) ECMs
    "CDA/SFT Incoming Traffic Accepted Sources" => [ Node::ProductLink ],
    "CDA/SFT Report Trigger Sources" => [ Node::ProductLink ],
}

FileTypeVp3 = {
    "Telematics File Number (File Type)" => 10129,
    "Transmit Queue Size Limit (Bytes)" => 8000000,
    "Receive Queue Size Limit (Bytes)" => 0,
    "Default Outgoing Traffic Destinations" => [ Node::BackOffice, Node::LocalSiteComms ],
    "CDA/SFT Report Trigger Sources" => [ Node::ProductLink, 0x58 ], # A5N2 telematics software uses incorrect product link FID of 0x58
}

FileTypeETicket = {
    "Telematics File Number (File Type)" => 10688,
    "Transmit Queue Size Limit (Bytes)" => 262144,  # 256K limit
    "Receive Queue Size Limit (Bytes)" => 0,
    "Default Outgoing Traffic Destinations" => [ Node::BackOffice, Node::LocalSiteComms ],
    "CDA/SFT Report Trigger Sources" => [ Node::ProductLink, 0x58 ], # A5N2 telematics software uses incorrect product link FID of 0x58
}

FileTypeTruckListv2 = {
    "Telematics File Number (File Type)" => 10642,
    "Transmit Queue Size Limit (Bytes)" => 50000,
    "Receive Queue Size Limit (Bytes)" => 50000,
    "Default Outgoing Traffic Destinations" => [ Node::BackOffice ],
    "CDA/TTI Server Incoming Traffic Accepted Sources" => [ Node::BackOffice ],
}

FileTypeMaterialListv2 = {
    "Telematics File Number (File Type)" => 10643,
    "Transmit Queue Size Limit (Bytes)" => 50000,
    "Receive Queue Size Limit (Bytes)" => 50000,
    "Default Outgoing Traffic Destinations" => [ Node::BackOffice ],
    "CDA/TTI Server Incoming Traffic Accepted Sources" => [ Node::BackOffice ],
}

FileTypeCustomList1 = {
    "Telematics File Number (File Type)" => 10638,
    "Transmit Queue Size Limit (Bytes)" => 50000,
    "Receive Queue Size Limit (Bytes)" => 50000,
    "Default Outgoing Traffic Destinations" => [ Node::BackOffice ],
    "CDA/TTI Server Incoming Traffic Accepted Sources" => [ Node::BackOffice ],
}

FileTypeCustomList2 = {
    "Telematics File Number (File Type)" => 10639,
    "Transmit Queue Size Limit (Bytes)" => 50000,
    "Receive Queue Size Limit (Bytes)" => 50000,
    "Default Outgoing Traffic Destinations" => [ Node::BackOffice ],
    "CDA/TTI Server Incoming Traffic Accepted Sources" => [ Node::BackOffice ],
}

FileTypeCustomList3 = {
    "Telematics File Number (File Type)" => 10640,
    "Transmit Queue Size Limit (Bytes)" => 50000,
    "Receive Queue Size Limit (Bytes)" => 50000,
    "Default Outgoing Traffic Destinations" => [ Node::BackOffice ],
    "CDA/TTI Server Incoming Traffic Accepted Sources" => [ Node::BackOffice ],
}

FileTypeCustomList4 = {
    "Telematics File Number (File Type)" => 10641,
    "Transmit Queue Size Limit (Bytes)" => 50000,
    "Receive Queue Size Limit (Bytes)" => 50000,
    "Default Outgoing Traffic Destinations" => [ Node::BackOffice ],
    "CDA/TTI Server Incoming Traffic Accepted Sources" => [ Node::BackOffice ],
}

FileTypeConfigFileHashResponse = {
    "Telematics File Number (File Type)" => 10087,
    "Transmit Queue Size Limit (Bytes)" => 1000,
    "Receive Queue Size Limit (Bytes)" => 0,
    "Default Outgoing Traffic Destinations" => [ Node::BackOffice ],
    "CDA/TTI Server Incoming Traffic Accepted Sources" => [ Node::BackOffice ],
}

FileTypeCycleTMAC = {
    "Telematics File Number (File Type)" => 10354,
    "Transmit Queue Size Limit (Bytes)" => 1000,
    "Receive Queue Size Limit (Bytes)" => 0,
    "Default Outgoing Traffic Destinations" => [ Node::ProductLink ],
    
}

FileTypeDipperTMAC = {
    "Telematics File Number (File Type)" => 10355,
    "Transmit Queue Size Limit (Bytes)" => 1000,
    "Receive Queue Size Limit (Bytes)" => 0,
    "Default Outgoing Traffic Destinations" => [ Node::ProductLink  ],
    
}

FileTypeLoadTMAC = {
    "Telematics File Number (File Type)" => 10356,
    "Transmit Queue Size Limit (Bytes)" => 1000,
    "Receive Queue Size Limit (Bytes)" => 0,
    "Default Outgoing Traffic Destinations" => [ Node::ProductLink  ],
    
}

FileTypeModeTMAC = {
    "Telematics File Number (File Type)" => 10357,
    "Transmit Queue Size Limit (Bytes)" => 1000,
    "Receive Queue Size Limit (Bytes)" => 0,
    "Default Outgoing Traffic Destinations" => [ Node::ProductLink  ],
    
}

FileTypePcsCycleTMAC = {
    "Telematics File Number (File Type)" => 10358,
    "Transmit Queue Size Limit (Bytes)" => 1000,
    "Receive Queue Size Limit (Bytes)" => 0,
    "Default Outgoing Traffic Destinations" => [ Node::ProductLink ],
}

FileTypePayloadPrint = {
    "Telematics File Number (File Type)" => 10425, # Payload Print
    "Transmit Queue Size Limit (Bytes)" => 2097152, # 2MB
    "Receive Queue Size Limit (Bytes)" => 0,
    "Default Outgoing Traffic Destinations" => [ Node::ProductLink ], # Product Link
}

FileTypeApplicationLog = {
    "Telematics File Number (File Type)" => 10496, # Analysis Module Application Log
    "Transmit Queue Size Limit (Bytes)" => 1048576, # 1MB
    "Receive Queue Size Limit (Bytes)" => 0,
    "Default Outgoing Traffic Destinations" => [ Node::BackOffice ], # Back Office
}

Execution = {
   "executableName" => "FileTransferBridgeApp",
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
