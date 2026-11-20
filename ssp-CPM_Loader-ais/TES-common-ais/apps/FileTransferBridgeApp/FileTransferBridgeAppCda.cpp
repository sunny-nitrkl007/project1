 ////////////////////////////////////////////////////////
 //
 // Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
 //
 //     Class: FileTransferBridgeAppCda
 //
 // File Name: FileTransferBridgeAppCda.cpp
 //
 //  Abstract: Implementation of the class that acts as
 //            a CDA Client layer between the CDA Server
 //            and (this) Bridge application
 //
 ////////////////////////////////////////////////////////
 
 #include <fstream>   // Needed for std::ifstream
 #include <chrono>
 #include <CDASecureConfigs.h>
 #include <CDADiagnosticsConsumer.grpc.pb.h>
 #include <GetCDAServerDns.h>
 #include "FileTransferBridgeAppCda.h"
 
 #ifdef DEBUG_FROM_VM
    // Local (VM) paths to the CA, the certificate, and the private key for debugging
    #define LOCAL_CERTIFICATE_AUTHORITY_PATH  "/home/pf/git/ssp-linux/ssp-cda/cda-a/tgt_gcc_5.1.0_a6n2/image/certs/CommCAsAll.chain"
    #define LOCAL_CERTIFICATE_PATH            "/home/pf/DownloadedFromA6N2/uik_public.cer"
    #define LOCAL_KEY_PATH                    "/home/pf/DownloadedFromA6N2/uik_private.pem"
    #define CDA_SERVER_NAME                   "000a750e664897db7f70863e7a9" // Peek at /etc/hosts file on A6N2
 #else
    // Paths to the CA, the certificate, and the private key on the ECM
    #define LOCAL_CERTIFICATE_AUTHORITY_PATH  m_CertificateChainFile
    #define LOCAL_CERTIFICATE_PATH            HARDWARE_PUBLIC_CERTIFICATE
    #define LOCAL_KEY_PATH                    HARDWARE_PRIVATE_KEY
 #endif
 
 using namespace FileTransferBridge;
 using namespace CDA::TelematicsTransfer;
 using namespace CDA::SystemFileTransfer;
 using namespace CAT::FileTransfer;
 using namespace grpc;
 
 static constexpr auto GRPC_TEST_CONNECT_DEADLINE_TIMEOUT = std::chrono::seconds(2);
 static constexpr auto GRPC_SEND_DEADLINE_TIMEOUT = std::chrono::minutes(1);
 
 ////////////////////////////////////////////////////////////////////////////
 // Function        : FileTransferBridgeAppCda::FileTransferBridgeAppCda
 // Description     : Class constructor
 // Return Type     : N/A
 // Argument [in]   : bool isConnectionSecure - Flag for a pre-set connection
 //                      type (secure/insecure); comes from the app configuration,
 //                   const std::string& certChain - The path and the file name
 //                      of the SSL certificate chain from the app configuration,
 //                   const std::string& newServerIP - CDA server IP from app config
 // Argument [out]  : None
 // Argument [I/O]  : None
 ////////////////////////////////////////////////////////////////////////////
 FileTransferBridgeAppCda::FileTransferBridgeAppCda( bool isConnectionSecure, const std::string& certChain, const std::string& newServerIP, const std::string& newServerPort):
                   m_ConnSecure( isConnectionSecure ),
                   m_CertificateChainFile( certChain ),
                   m_ServerIPAddress( newServerIP ),
				   m_ServerPort(newServerPort),
                   m_ServerOnline( false ),
                   m_SftAttributes(),
                   m_TtiAttributes(),
                   m_spCdaTtiServerStub( nullptr ),
                   m_spCdaSftServerStub( nullptr ),
                   m_spChannel( nullptr )
 {
 }
 
 ////////////////////////////////////////////////////////////////////////////
 // Function        : FileTransferBridgeAppCda::~FileTransferBridgeAppCda
 // Description     : Class destructor
 // Return Type     : N/A
 // Argument [in]   : N/A
 // Argument [out]  : N/A
 // Argument [I/O]  : N/A
 ////////////////////////////////////////////////////////////////////////////
 FileTransferBridgeAppCda::~FileTransferBridgeAppCda( void )
 {
    // Make sure we join with any pending connection threads before destroying them
    if ( nullptr != m_TtiAttributes.connectionThreadHandle )
    {
       BRIDGE_APP_LOG( "CDA/TTI connection was in progress. Waiting for connection thread to terminate...", AIS_LOG_NOTICE, false );
       m_TtiAttributes.connectionThreadHandle->join();
    }
    if ( nullptr != m_SftAttributes.connectionThreadHandle )
    {
       BRIDGE_APP_LOG( "CDA/SFT connection was in progress. Waiting for connection thread to terminate...", AIS_LOG_NOTICE, false );
       m_SftAttributes.connectionThreadHandle->join();
    }
 
    BRIDGE_APP_LOG( "CDA Client instance is shut down", AIS_LOG_DEBUG, false );
 }
 
 ////////////////////////////////////////////////////////////////////////////
 // Function        : FileTransferBridgeAppCda::ConnectToCDAServer
 // Description     : Attempts a connection with CDA server: sets up the
 //                   security if configured, opens the RPC channel, and
 //                   attempts a test send over TTI and SFT
 // Return Type     : bool - true if the connection was successful, otherwise false
 // Argument [in]   : None
 // Argument [out]  : None
 // Argument [I/O]  : None
 ////////////////////////////////////////////////////////////////////////////
 bool FileTransferBridgeAppCda::ConnectToCDAServer( void )
 {
     bool ttiConnecting = m_TtiAttributes.connectionInProgress;
     if (!ttiConnecting) {
         // Connection is not in process, clean up the thread
         if (nullptr != m_TtiAttributes.connectionThreadHandle) {
             m_TtiAttributes.connectionThreadHandle->join();
             m_TtiAttributes.connectionThreadHandle.reset();
         }
     }
 
     bool sftConnecting = m_SftAttributes.connectionInProgress;
     if (!sftConnecting) {
         // Connection is not in process, clean up the thread
         if (nullptr != m_SftAttributes.connectionThreadHandle) {
             m_SftAttributes.connectionThreadHandle->join();
             m_SftAttributes.connectionThreadHandle.reset();
         }
     }
 
     // If we don't have a gRPC stub, then we need to connect
     bool ttiConnectionNeeded = false;
     if ((nullptr == m_spCdaTtiServerStub) || !(m_TtiAttributes.connectionEstablished)) {
         ttiConnectionNeeded = true;
     }
 
     // If we don't have a gRPC stub, then we need to connect
     bool sftConnectionNeeded = false;
     if ((nullptr == m_spCdaSftServerStub) || !(m_SftAttributes.connectionEstablished)) {
         sftConnectionNeeded = true;
     }
 
     // If anything is in the process of connection, don't kick off a new connection process
     if (ttiConnecting || sftConnecting) {
         ttiConnectionNeeded = false;
         sftConnectionNeeded = false;
     }
 
     // If both TTI and SFT need a connection, tear it down and start over
     if (ttiConnectionNeeded && sftConnectionNeeded) {
         // This will reset the gRPC channel
         SetConnInactive();
     }
 
     // Try opening a new gRPC channel (or use existing)
     if (ConnectOpenChannel()) {
         if (ttiConnectionNeeded) {
             m_TtiAttributes.connectionThreadHandle.reset(new std::thread([this] { ConnectTtiThreadImplementation(); }));
         }
 
         if (sftConnectionNeeded) {
             m_SftAttributes.connectionThreadHandle.reset(new std::thread([this] { ConnectSftThreadImplementation(); }));
         }
     }
 
     return m_TtiAttributes.connectionEstablished || m_SftAttributes.connectionEstablished;
 }
 
 ////////////////////////////////////////////////////////////////////////////
 // Function        : FileTransferBridgeAppCda::IsConnActive
 // Description     : Checks if the connection was previously
 //                   successfully established for a specified CDA node (e.g. Back Office),
 //                   or for any node if the optional parameter is omitted
 // Return Type     : bool - true if the connection was established, otherwise false
 // Argument [in]   : const CdaNode_t node (optional) - CDA node to check the connection with
 // Argument [out]  : None
 // Argument [I/O]  : None
 ////////////////////////////////////////////////////////////////////////////
 bool FileTransferBridgeAppCda::IsConnActive( const CdaNode_t node )
 {
    bool connectionActive = false;
    if ( NO_NODE == node )
    {
       connectionActive = m_TtiAttributes.connectionEstablished || m_SftAttributes.connectionEstablished;
    }
    else if ( FileTransferBridgeAppUtil::IsSFTNode( node ) )
    {
       connectionActive = m_SftAttributes.connectionEstablished;
    }
    else
    {
       connectionActive = m_TtiAttributes.connectionEstablished;
    }
 
    return connectionActive;
 }
 
 FileTransferBridgeAppCda::SendDataFileReturnCode FileTransferBridgeAppCda::SendDataFileTti(const std::string& name, const TransferMessage& content, const CdaNode_t& destination) {
     SendDataFileReturnCode returnCode;
     DestinationMessage cdaMessage;
     TransferMessage* pMessageStorage = cdaMessage.mutable_messagecontents();
     if (nullptr != pMessageStorage) {
         if (IsConnActive(destination)) {
             // Send the message
             cdaMessage.set_destination( static_cast<DestinationMessage_DESTINATION>(destination));
             *pMessageStorage = content;
 
             grpc::Status txStatus;
             TRANSFER_RETURN txRetCode;
 
             { // Send the file
                 // Context for the client. It could be used to convey extra information to the server and/or tweak certain RPC behaviors
                 ClientContext context;
                 context.set_deadline(std::chrono::system_clock::now() + GRPC_SEND_DEADLINE_TIMEOUT);
 
                 TransferReturnMessage reply;
                 std::lock_guard<std::mutex> scopeLock(m_TtiAttributes.lockStub);
 
 #ifdef DEBUG_SIM_SERVER
                 txStatus = Status::OK;
                 reply.set_returncode(TRANSFER_RETURN::QUEUED_SUCCESS);
 #else
                 txStatus = m_spCdaTtiServerStub->SubmitFileToDestination(&context, cdaMessage, &reply);
 #endif
 
                 BRIDGE_APP_LOG("SubmitFileToDestination: gRPC status " << txStatus.error_code() << " " << txStatus.error_message(), AIS_LOG_DEBUG, false);
 
                 txRetCode = reply.returncode();
             }
 
             if (txStatus.ok()) {
                 // The grpc call was successful, was the file transfer successful?
                 BRIDGE_APP_LOG("SendDataFile " << name << " of size " << content.filecontents().size()
                     << " to node " << destination << ": SubmitFileToDestination returned: "
                     << TRANSFER_RETURN_Name(txRetCode), AIS_LOG_NOTICE, false);
 
                 switch (txRetCode) {
                 case (TRANSFER_RETURN::QUEUED_SUCCESS): {
                     returnCode = SendDataFileReturnCode::OK;
                     break;
                 }
 
                 case (TRANSFER_RETURN::FILE_TYPE_NOT_SUPPORTED): {
                     returnCode = SendDataFileReturnCode::FILE_TYPE_NOT_SUPPORTED;
                     break;
                 }
 
                 case (TRANSFER_RETURN::QUEUE_TIMEOUT): {
                     returnCode = SendDataFileReturnCode::SERVICE_ERROR;
                     break;
                 }
 
                 case (TRANSFER_RETURN::STATE_INVALID):
                 case (TRANSFER_RETURN::FILE_SIZE_EXCEEDED):
                 case (TRANSFER_RETURN::FATAL_ERROR):
                 case (TRANSFER_RETURN::INVALID_FILENAME_HINT):
                 default: {
                     returnCode = SendDataFileReturnCode::BAD_FILE;
                 }
                 }
             }
             else if (grpc::StatusCode::UNAVAILABLE == txStatus.error_code()) {
                 // Disconnected?
                 SetConnInactive(destination);
                 returnCode = SendDataFileReturnCode::SERVICE_ERROR;
                 BRIDGE_APP_LOG("Lost connection with CDA/TTI Server (" << txStatus.error_code() << ") " << txStatus.error_message(), AIS_LOG_NOTICE, false);
             }
             else if (grpc::StatusCode::INTERNAL == txStatus.error_code()) {
                 // We were getting this error when we had bad file names, in which case we should not retry
                 //  - like "Error parsing req/resp proto"
                 // Maybe there are other reasons that this error would occur where we should retry
                 //  - like "Flow-control protocol violation"
                 returnCode = SendDataFileReturnCode::SERVICE_ERROR;
                 BRIDGE_APP_LOG("Internal Error with CDA/TTI (" << txStatus.error_code() << ") " << txStatus.error_message(), AIS_LOG_ERROR, false);
             }
             else {
                 // Not ok, some other error
                 returnCode = SendDataFileReturnCode::SERVICE_ERROR;
                 BRIDGE_APP_LOG("Error with CDA/TTI Server (" << txStatus.error_code() << ") " << txStatus.error_message(), AIS_LOG_ERROR, false);
             }
         }
         else {
             returnCode = SendDataFileReturnCode::SERVICE_ERROR;
             BRIDGE_APP_LOG("Failed to stage file " << name << " for CDA node " << destination << " since there's no connection", AIS_LOG_NOTICE, false);
         }
     }
     else {
         returnCode = SendDataFileReturnCode::SERVICE_ERROR;
     }
 
     return returnCode;
 }
 
 FileTransferBridgeAppCda::SendDataFileReturnCode FileTransferBridgeAppCda::SendDataFileSft(const std::string& name, const SystemFile& content, const CdaNode_t& destination) {
     SendDataFileReturnCode returnCode;
     SystemFileDestination cdaMessage;
     SystemFile* pMessageStorage = cdaMessage.mutable_messagecontents();
     if (nullptr != pMessageStorage) {
         if (IsConnActive(destination)) {
             // Send the message
             cdaMessage.set_destinationfid(static_cast<google::protobuf::uint32>(destination));
             *pMessageStorage = content;
 
             grpc::Status txStatus;
             SystemFileReturn_SYSTEM_FILE_RETURN txRetCode;
 
             { // Send the file
                 // Context for the client. It could be used to convey extra information to the server and/or tweak certain RPC behaviors
                 ClientContext context;
                 context.set_deadline(std::chrono::system_clock::now() + GRPC_SEND_DEADLINE_TIMEOUT);
 
                 SystemFileReturn reply;
                 std::lock_guard<std::mutex> scopeLock(m_SftAttributes.lockStub);
 
 #ifdef DEBUG_SIM_SERVER
                 txStatus = Status::OK;
                 reply.set_returncode(SystemFileReturn_SYSTEM_FILE_RETURN_QUEUED_SUCCESS);
 #else
                 txStatus = m_spCdaSftServerStub->SubmitFileToSystem(&context, cdaMessage, &reply);
 #endif
 
                 BRIDGE_APP_LOG("SubmitFileToSystem: gRPC status " << txStatus.error_code() << " " << txStatus.error_message(), AIS_LOG_DEBUG, false);
 
                 txRetCode = reply.returncode();
             }
 
             if (txStatus.ok()) {
                 // The grpc call was successful, was the file transfer successful?
                 BRIDGE_APP_LOG("SendDataFile " << name << " of size " << content.filecontents().size()
                       << " to FID " << destination << " from FID " << content.sourcefid() << ": SubmitFileToSystem returned: "
                       << SystemFileReturn_SYSTEM_FILE_RETURN_Name(txRetCode), AIS_LOG_NOTICE, false);
 
                 switch (txRetCode) {
                 case (SystemFileReturn_SYSTEM_FILE_RETURN_QUEUED_SUCCESS): {
                     returnCode = SendDataFileReturnCode::OK;
                     break;
                 }
 
                 case (SystemFileReturn_SYSTEM_FILE_RETURN_STATE_INVALID):
                 case (SystemFileReturn_SYSTEM_FILE_RETURN_FATAL_ERROR):
                 default: {
                     returnCode = SendDataFileReturnCode::BAD_FILE;
                     break;
                 }
                 }
             }
             else if (grpc::StatusCode::UNAVAILABLE == txStatus.error_code()) {
                 // Disconnected?
                 SetConnInactive(destination);
                 returnCode = SendDataFileReturnCode::SERVICE_ERROR;
                 BRIDGE_APP_LOG("Lost connection with CDA/SFT Server", AIS_LOG_NOTICE, false);
             }
             else {
                 // Not ok, some other error
                 returnCode = SendDataFileReturnCode::SERVICE_ERROR;
                 BRIDGE_APP_LOG("Error with CDA/SFT Server", AIS_LOG_ERROR, false);
             }
         }
         else {
             returnCode = SendDataFileReturnCode::SERVICE_ERROR;
             BRIDGE_APP_LOG("Failed to stage file " << name << " for CDA node " << destination << " since there's no connection", AIS_LOG_NOTICE, false);
         }
     }
     else {
         returnCode = SendDataFileReturnCode::SERVICE_ERROR;
     }
 
     return returnCode;
 }
 
 ////////////////////////////////////////////////////////////////////////////
 // Function        : FileTransferBridgeAppCda::SendDataFile
 // Description     : Stages the file to be transferred to all its associated
 //                   CDA nodes
 // Return Type     : bool - 'true' if file was staged successfully to AT LEAST ONE
 //                   node, 'false' otherwise
 // Argument [in]   : const FileInfo_t& fileInfo - File attributes,
 //                   const std::string& fileContentBuf - Content of the file,
 //                   const CdaNodeList_t& nodes - Associated destination nodes,
 //                   const CdaNode_t& defaultFid - Default FID
 //                      for the source node (if unspecified).
 // Argument [out]  : None
 // Argument [I/O]  : None
 ////////////////////////////////////////////////////////////////////////////
 FileTransferBridgeAppCda::SendDataFileReturnCode FileTransferBridgeAppCda::SendDataFile(const FileInfo_t& fileInfo,
       const std::string& fileContentBuf,
       const CdaNodeList_t& nodes,
       const CdaNode_t& defaultFid) {
 
     SendDataFileReturnCode returnCode;
 
     // If the destination was specified in the request, then send only to that destination
     if (FileTransferBridgeAppUtil::IsSFTNode(fileInfo.DestinationFID)) {
         // Prepare the message
         SystemFile fileContent;
 
         fileContent.set_filetype(static_cast<google::protobuf::uint32>(fileInfo.TelematicsFileNumber));
 
         { // If the requesting app chose to specify its FID then use that, otherwise, use the FID of this Bridge app
             const CdaNode_t sourceFID = fileInfo.SourceFID != 0 ? fileInfo.SourceFID : defaultFid;
             fileContent.set_sourcefid(static_cast<google::protobuf::uint32>(sourceFID));
         }
 
         fileContent.set_filecontents(fileContentBuf);
 
         returnCode = SendDataFileSft(fileInfo.Name, fileContent, fileInfo.DestinationFID);
     }
     // Send to every node in the .rb configuration
     else {
         returnCode = SendDataFileReturnCode::UNKNOWN;
 
         for (auto& node : nodes) {
             if (FileTransferBridgeAppUtil::IsSFTNode(node)) {
                 // Prepare the message
                 SystemFile fileContent;
 
                 fileContent.set_filetype(static_cast<google::protobuf::uint32>(fileInfo.TelematicsFileNumber));
 
                 fileContent.set_sourcefid(static_cast<google::protobuf::uint32>(fileInfo.SourceFID));
 
                 fileContent.set_filecontents(fileContentBuf);
 
                 auto thisReturnCode = SendDataFileSft(fileInfo.Name, fileContent, node);
 
                 UpdateSendDataFileReturnCode(returnCode, thisReturnCode);
             }
             else {
                 // Prepare the message
                 TransferMessage fileContent;
 
                 fileContent.set_filetype(static_cast<google::protobuf::uint32>(fileInfo.TelematicsFileNumber));
 
                 bool badFileName = false;
 
                 // Check for printable ASCII characters
                 //  - filenamehint string can only accept ASCII
                 for (const auto& c : fileInfo.Name) {
                     if ((c > 0x1F) && (c < 0x7F)) {
                         // good character
                     }
                     else {
                         // bad character
                         BRIDGE_APP_LOG("Bad file name character: " << std::hex << c, AIS_LOG_ERROR, false);
                         badFileName = true;
                         break;
                     }
                 }
 
                 if (badFileName) {
                     BRIDGE_APP_LOG("Bad file name : " << fileInfo.Name, AIS_LOG_ERROR, false);
                     UpdateSendDataFileReturnCode(returnCode, SendDataFileReturnCode::BAD_FILE);
                 }
                 else {
                     // Set the filename hint
                     std::string tmReqFileName = fileInfo.Name;
 
                     { // Generating Telematics required file name, everything after the first underscore
                         uint32_t firstOccIndex = tmReqFileName.find("_");
                         if (std::string::npos != firstOccIndex) {
                             tmReqFileName.erase(0, firstOccIndex + 1);
                             BRIDGE_APP_LOG("File name submit to Telematics: " << tmReqFileName, AIS_LOG_INFO, false);
                         }
                         else {
                             BRIDGE_APP_LOG("Possible incorrect file name : " << tmReqFileName, AIS_LOG_ERROR, false);
                         }
                     }
 
                     fileContent.set_filenamehint(tmReqFileName);
 
                     fileContent.set_filecontents(fileContentBuf);
 
                     auto thisReturnCode = SendDataFileTti(fileInfo.Name, fileContent, node);
 
                     UpdateSendDataFileReturnCode(returnCode, thisReturnCode);
                 }
             }
         }
     }
 
     return returnCode;
 }
 
 ////////////////////////////////////////////////////////////////////////////
 // Function        : FileTransferBridgeAppCda::ReceiveDataFile
 // Description     : Invokes a blocking gRPC call to listen for CDA/TTI server
 //                   and to receive a file that the caller is registered for
 // Return Type     : bool - 'true' if file was received successfully, 'false' otherwise
 // Argument [in]   : const volatile bool& stopFlag - External indicator that the
 //                      thread should stop blocking and exit
 // Argument [out]  : std::string& fileContentBuf - Buffer for the content of the file,
 //                   CdaFileType_t& fileTypeBuf - Buffer for file type
 //                   std::string& filenameBuf - Buffer for the file name suggested by the server.
 // Argument [I/O]  : RxStreamAttributesTti_t& attrib - This stream's attributes
 ////////////////////////////////////////////////////////////////////////////
 bool FileTransferBridgeAppCda::ReceiveDataFile( const volatile bool& stopFlag,
       RxStreamAttributesTti_t& attrib,
       std::string& fileContentBuf,
       CdaFileType_t& fileTypeBuf,
       std::string& filenameBuf )
 {
    bool fileReceivedSuccessfully = false;
 
    while( !fileReceivedSuccessfully && !stopFlag )
    {
       // Block, waiting for a new file transaction to be queued up by the server
       DestinationMessage cdaMessage;
       if ( attrib.pCdaTransactionReader->Read( &cdaMessage ) )
       {
          // Ensure the contents are not garbage
          TransferMessage transaction = cdaMessage.messagecontents();
          if ( transaction.filecontents().size() > 0 )
          {
             fileContentBuf = transaction.filecontents();
             fileTypeBuf = transaction.filetype();
             filenameBuf = transaction.filenamehint();
             fileReceivedSuccessfully = true;
             BRIDGE_APP_LOG( "Rx thread " << THREAD_ID << " successfully received file " << filenameBuf, AIS_LOG_NOTICE, true );
          }
       }
       else
       {
          BRIDGE_APP_LOG( "Receive thread " << THREAD_ID << " got interrupted", AIS_LOG_NOTICE, false );
          break;
       }
    }
 
    return fileReceivedSuccessfully;
 }
 
 ////////////////////////////////////////////////////////////////////////////
 // Function        : FileTransferBridgeAppCda::ReceiveDataFile
 // Description     : Invokes a blocking gRPC call to listen for CDA/SFT server
 //                   and to receive a file that the caller is registered for
 // Return Type     : bool - 'true' if file was received successfully, 'false' otherwise
 // Argument [in]   : const volatile bool& stopFlag - External indicator that the
 //                      thread should stop blocking and exit,
 //                   const std::map<CdaFileType_t, CdaFileProperties_t>& mapFileTypeToProperties -
 //                      Map of the file types to their properties from the app config
 // Argument [out]  : std::string& fileContentBuf - Buffer for the content of the file,
 //                   CdaFileType_t& fileTypeBuf - Buffer for file type,
 //                   CdaNode_t& fileSourceBuf - Buffer for source FID,
 //                   CdaNode_t& fileDestBuf - Buffer for destination FID
 // Argument [I/O]  : RxStreamAttributesSft_t& attrib - This stream's attributes,
 //                   std::function< void( const Trigger_t& triggerProperties ) > triggerCallback -
 //                      Callback function that is to be invoked to initiate a report trigger
 ////////////////////////////////////////////////////////////////////////////
 bool FileTransferBridgeAppCda::ReceiveDataFile( const volatile bool& stopFlag,
       RxStreamAttributesSft_t& attrib,
       const std::map<CdaFileType_t, CdaFileProperties_t>& mapFileTypeToProperties,
       std::string& fileContentBuf,
       CdaFileType_t& fileTypeBuf,
       CdaNode_t& fileSourceBuf,
       CdaNode_t& fileDestBuf,
       std::function< bool( const Trigger_t& ) > triggerCallback )
 {
    bool fileReceivedSuccessfully = false;
 
    while( !fileReceivedSuccessfully && !stopFlag )
    {
       // Block, waiting for a new file transaction to be queued up by the server
       SystemFileDestination cdaMessage;
       if ( attrib.pCdaTransactionReader->Read( &cdaMessage ) )
       {
          // File stream pending. Get the contents
          SystemFile transaction = cdaMessage.messagecontents();
          if ( transaction.filecontents().size() > 0 )
          {
             // Check the message against our configuration map
             const CdaNode_t messageSource = static_cast<CdaNode_t>( transaction.sourcefid() );
             const CdaNode_t messageDestination = static_cast<CdaNode_t>( cdaMessage.destinationfid() );
             const CdaFileType_t messageFileType = static_cast<CdaFileType_t>( transaction.filetype() );
             if ( TRIGGER_TYPE == messageFileType )
             {
                // We appear to support a report trigger, let's try to convert this generic message to a report trigger message
                ReportTrigger trigger;
                if ( trigger.ParseFromString( transaction.filecontents() ) )
                {
                   // Check if this report trigger is supported
                   if ( !( mapFileTypeToProperties.find( trigger.file_type() ) == mapFileTypeToProperties.end() ) &&                             // File type appears in .rb config
                         ( mapFileTypeToProperties.at( trigger.file_type() ).CdaSftReportTriggerNodes.empty() ||                                 // Report trigger accepted from all sources
                           VECTOR_HAS_ELEMENT( messageSource, mapFileTypeToProperties.at( trigger.file_type() ).CdaSftReportTriggerNodes ) ) )   // Source of the report trigger is accepted
                   {
                      // Success! Generate a Report Trigger event (use the thread's callback function)
                      Trigger_t triggerProperties { messageSource, trigger.command(), trigger.file_type(), trigger.trigger() };
                      (void)triggerCallback(triggerProperties);
                   }
                   else
                   {
                      BRIDGE_APP_LOG( "Wrong file type " << trigger.file_type() << " requested with Report Trigger event from FID " << messageSource, AIS_LOG_WARN, false );
                   }
                }
                else
                {
                   BRIDGE_APP_LOG( "CDA/SFT RX Thread " << THREAD_ID << " is ignoring incoming message from FID " << messageSource
                         << " to FID " << messageDestination << " since it failed to convert to Report Trigger", AIS_LOG_ALERT, true );
                }
             }
             else if ( mapFileTypeToProperties.find( messageFileType ) == mapFileTypeToProperties.end() )
             {
                BRIDGE_APP_LOG( "CDA/SFT RX Thread " << THREAD_ID << " is ignoring incoming message since the file type "
                      << messageFileType << " is not supported", AIS_LOG_WARN, false );
             }
             else if ( !mapFileTypeToProperties.at( messageFileType ).CdaSftIntendedDestinationNodes.empty() &&
                       !VECTOR_HAS_ELEMENT( messageDestination, mapFileTypeToProperties.at( messageFileType ).CdaSftIntendedDestinationNodes ) )
             {
                BRIDGE_APP_LOG( "CDA/SFT RX Thread " << THREAD_ID << " is ignoring incoming message since the file type "
                      << messageFileType << " is not configured to work with local FID " << messageDestination, AIS_LOG_WARN, false );
             }
             else if ( mapFileTypeToProperties.at( messageFileType ).CdaSftSourceNodes.empty() ||
                       VECTOR_HAS_ELEMENT( messageSource, mapFileTypeToProperties.at( messageFileType ).CdaSftSourceNodes ) )
             {
                // Not expecting Report Trigger from this remote FID, but we do expect plain files
                fileContentBuf = transaction.filecontents();
                fileTypeBuf = transaction.filetype();
                fileSourceBuf = messageSource;
                fileDestBuf = messageDestination;
                fileReceivedSuccessfully = true;
                BRIDGE_APP_LOG( "CDA/SFT RX Thread " << THREAD_ID << " received a file of type " << messageFileType
                      << " from FID " << messageSource << " intended for FID " << messageDestination, AIS_LOG_NOTICE, true );
             }
             else
             {
                BRIDGE_APP_LOG( "CDA/SFT RX Thread " << THREAD_ID << " is ignoring incoming message since the file type "
                      << messageFileType << " is not configured to work with remote FID " << messageSource, AIS_LOG_WARN, false );
             }
          }
       }
       else
       {
          BRIDGE_APP_LOG( "Receive thread " << THREAD_ID << " got interrupted", AIS_LOG_NOTICE, false );
          break;
       }
    }
 
    return fileReceivedSuccessfully;
 }
 
 ////////////////////////////////////////////////////////////////////////////
 // Function        : FileTransferBridgeAppCda::RegisterForFileType
 // Description     : Register the calling thread with the CDA/TTI server
 //                   to be listening for the specified file type(s)
 // Return Type     : bool - 'true' if registration was successful, 'false' otherwise
 // Argument [in]   : None
 // Argument [out]  : None
 // Argument [I/O]  : RxStreamAttributesTti_t& attrib - stream attributes that
 //                   are used by the calling thread
 ////////////////////////////////////////////////////////////////////////////
 bool FileTransferBridgeAppCda::RegisterForFileType( RxStreamAttributesTti_t& attrib )
 {
    std::stringstream fileTypes;
    for ( int iter = 0; iter < attrib.fileFilter.filetypegroup_size(); iter++ )
    {
       if ( iter > 0 )
       {
          fileTypes << ", ";
       }
       fileTypes << attrib.fileFilter.filetypegroup( iter );
    }
 
 #ifndef DEBUG_SIM_SERVER
    if ( m_TtiAttributes.connectionEstablished )
    {
       attrib.pCdaTransactionReader = m_spCdaTtiServerStub->GetEventStreamDestination( &attrib.clientContext, attrib.fileFilter );
    }
 
    if ( nullptr == attrib.pCdaTransactionReader )
    {
       BRIDGE_APP_LOG( "Thread " << THREAD_ID << " failed to register with node " << attrib.node << " for receiving file types "
             << fileTypes.str(), AIS_LOG_ERROR, true );
       return false;
    }
    else
 #endif
    {
       BRIDGE_APP_LOG( "Thread " << THREAD_ID << " successfully registered with node " << attrib.node << " for receiving file types "
             << fileTypes.str(), AIS_LOG_NOTICE, true );
       return true;
    }
 }
 
 ////////////////////////////////////////////////////////////////////////////
 // Function        : FileTransferBridgeAppCda::RegisterForFileType
 // Description     : Register the calling thread with the CDA/SFT server
 //                   to be listening for the specified file type(s)
 // Return Type     : bool - 'true' if registration was successful, 'false' otherwise
 // Argument [in]   : None
 // Argument [out]  : None
 // Argument [I/O]  : RxStreamAttributesSft_t& attrib - stream attributes that
 //                   are used by the calling thread
 ////////////////////////////////////////////////////////////////////////////
 bool FileTransferBridgeAppCda::RegisterForFileType( RxStreamAttributesSft_t& attrib )
 {
    std::stringstream fileTypes;
    for ( int iter = 0; iter < attrib.fileFilter.filetypegroup_size(); iter++ )
    {
       if ( iter > 0 )
       {
          fileTypes << ", ";
       }
       fileTypes << attrib.fileFilter.filetypegroup( iter );
    }
 
 #ifndef DEBUG_SIM_SERVER
    if ( m_SftAttributes.connectionEstablished )
    {
       attrib.pCdaTransactionReader = m_spCdaSftServerStub->GetSystemFileStream( &attrib.clientContext, attrib.fileFilter );
    }
 
    if ( nullptr == attrib.pCdaTransactionReader )
    {
       BRIDGE_APP_LOG( "Thread " << THREAD_ID << " failed to register for receiving file types " << fileTypes.str(), AIS_LOG_ERROR, true );
       return false;
    }
    else
 #endif
    {
       BRIDGE_APP_LOG( "Thread " << THREAD_ID << " successfully registered for receiving file types " << fileTypes.str(), AIS_LOG_NOTICE, true );
       return true;
    }
 }
 
 ////////////////////////////////////////////////////////////////////////////
 // Function        : FileTransferBridgeAppCda::SetConnInactive
 // Description     : Resets the status of the connection with the CDA Server
 // Return Type     : None
 // Argument [in]   : const CdaNode_t node (optional) - Node
 //                      with which the connection has been lost
 // Argument [out]  : None
 // Argument [I/O]  : None
 ////////////////////////////////////////////////////////////////////////////
 void FileTransferBridgeAppCda::SetConnInactive( const CdaNode_t node )
 {
    std::lock_guard<std::mutex> scopeLockTti( m_TtiAttributes.lockStub );
    std::lock_guard<std::mutex> scopeLockSft( m_SftAttributes.lockStub );
    std::lock_guard<std::mutex> scopeLockChan( m_LockChannel );
 
    // Which server has the connection been lost with? CDA/SFT or CDA/TTI?
    if ( NO_NODE == node )
    {
       m_SftAttributes.connectionEstablished = false;
       m_spCdaSftServerStub.reset();
       m_TtiAttributes.connectionEstablished = false;
       m_spCdaTtiServerStub.reset();
    }
    else if ( FileTransferBridgeAppUtil::IsSFTNode( node ) )
    {
       m_SftAttributes.connectionEstablished = false;
       m_spCdaSftServerStub.reset();
    }
    else
    {
       m_TtiAttributes.connectionEstablished = false;
       m_spCdaTtiServerStub.reset();
    }
 
    // If there is no connection with either CDA/TTI or CDA/SFT then drop the gRPC channel as the link has likely been severed
    if ( ( nullptr != m_spChannel ) && ( nullptr == m_spCdaSftServerStub ) && ( nullptr == m_spCdaTtiServerStub ) )
    {
       m_spChannel.reset();
       m_ServerOnline = false;
    }
 }
 
 ////////////////////////////////////////////////////////////////////////////
 // Function        : FileTransferBridgeAppCda::ConnectOpenChannel
 // Description     : Helper function to ConnectToCDAServer() method that
 //                   tried to open gRPC channel
 // Return Type     : bool - 'true' if channel was opened successfully, 'false' otherwise
 // Argument [in]   : None
 // Argument [out]  : None
 // Argument [I/O]  : None
 ////////////////////////////////////////////////////////////////////////////
 bool FileTransferBridgeAppCda::ConnectOpenChannel( void )
 {
     std::lock_guard<std::mutex> scopeLockChan( m_LockChannel );
     bool failureChannelDisplayed = false;
 
     if (nullptr != m_spChannel) {
         // Check if the channel is shutdown
         // Also, don't let it go idle, and if it does, reconnect
         if (GRPC_CHANNEL_SHUTDOWN == m_spChannel->GetState(true)) {
 
             BRIDGE_APP_LOG("GRPC_CHANNEL_SHUTDOWN, set connection inactive and trigger reconnect", AIS_LOG_ERROR, true);
 
             { // Reset SFT
                 std::lock_guard<std::mutex> scopeLockSft(m_SftAttributes.lockStub);
                 m_SftAttributes.connectionEstablished = false;
                 m_spCdaSftServerStub.reset();
             }
 
             { // Reset TTI
                 std::lock_guard<std::mutex> scopeLockTti(m_TtiAttributes.lockStub);
                 m_TtiAttributes.connectionEstablished = false;
                 m_spCdaTtiServerStub.reset();
             }
 
             { // Reset the Channel
                 m_spChannel.reset();
                 m_ServerOnline = false;
             }
         }
     }
 
     if (nullptr == m_spChannel) {
         // Establish the chain of trust if expecting a secure connection and create a channel to the CDA Server
         if (m_ConnSecure) {
			 AIS_LOG_INFO("Attempting secure connection");
			 std::string dnsName;
             bool ret = m_ServerIPAddress.empty() ? (GetCDAServerDns(dnsName) == 0) : GetCDAServerDnsFromIP(m_ServerIPAddress, dnsName);
             if (ret) {
                 AIS_LOG_INFO("dnsName is %s", dnsName.c_str());
                 m_ServerOnline = true;
		     }
             else {
                     AIS_LOG_ERROR( "Unable to obtain CDA server name");
             }

            if (m_ServerOnline) {
                 // Obtain the hardware public certificate and private key as well as the CA
                 std::ifstream hwCert(LOCAL_CERTIFICATE_PATH);
                 std::ifstream hwKey(LOCAL_KEY_PATH);
                 std::ifstream trustedCAChain(LOCAL_CERTIFICATE_AUTHORITY_PATH);
                 if (hwCert.is_open() && hwKey.is_open() && trustedCAChain.is_open()) {
                     // Get the server name from the list of hosts
                         struct grpc::SslCredentialsOptions credentialOptions;
                         std::stringstream hwCertStream;
                         std::stringstream privateKeyStream;
                         std::stringstream trustedCAChainStream;
 
                         // Adding the secure port in which server listens to client in this platform
                         std::string cdaServerNameAndPort = dnsName + ":" + m_ServerPort;
 
                         hwCertStream << hwCert.rdbuf();
                         privateKeyStream << hwKey.rdbuf();
                         trustedCAChainStream << trustedCAChain.rdbuf();
 
                         // Create the chain of trust using the obtained information
                         credentialOptions.pem_root_certs=trustedCAChainStream.str();
                         credentialOptions.pem_private_key=privateKeyStream.str();
                         credentialOptions.pem_cert_chain=hwCertStream.str();
 
                         AIS_LOG_INFO("Creating channel to %s", dnsName.c_str());
                         m_spChannel = grpc::CreateChannel( cdaServerNameAndPort, grpc::SslCredentials( credentialOptions ) );
						 
						 if (m_spChannel == nullptr)
                         {
                             AIS_LOG_ERROR("Channel creation failed");
                         }
                         else
                         {
                            AIS_LOG_INFO("Channel creation successful");
                         }
                 }
                 else {
                     if (!failureChannelDisplayed) {
                         BRIDGE_APP_LOG("Unable to auth with server due to missing SSL files ["
                                 << static_cast<int>( hwCert.is_open() )
                                 << static_cast<int>( hwKey.is_open() )
                                 << static_cast<int>( trustedCAChain.is_open() ) << "]", AIS_LOG_FATAL, true);
                     }
                 }
             }
         }
         else {
             // For the following connection to work the CDA server must be in insecure mode.
             // The CDA Server and CDA Client must also either be on the same host, or the client's traffic must be forwarded to server's loopback address on port 50000
             //    (i.e. ssh -L50000:127.0.0.1:50000 root@<server_IP_addr>)
             m_spChannel = grpc::CreateChannel( "127.0.0.1:50000", grpc::InsecureChannelCredentials() ); // Localhost
         }
 
         if (nullptr == m_spChannel) {
             if (!failureChannelDisplayed) {
                 BRIDGE_APP_LOG("gRPC channel opening has failed!", AIS_LOG_ALERT, true);
                 failureChannelDisplayed = true;
             }
         }
         else {
             // If we have a channel defined, then reset the ability to print errors.
             failureChannelDisplayed = false;
         }
     }
 
     return (nullptr != m_spChannel);
 }
 
 ////////////////////////////////////////////////////////////////////////////
 // Function        : FileTransferBridgeAppCda::ConnectTtiThreadImplementation
 // Description     : Implementation of the thread that attempts to connect
 //                   with CDA/TTI servers
 // Return Type     : None
 // Argument [in]   : None
 // Argument [out]  : None
 // Argument [I/O]  : None
 ////////////////////////////////////////////////////////////////////////////
 void FileTransferBridgeAppCda::ConnectTtiThreadImplementation(void)
 {
     BRIDGE_APP_LOG("Connecting to CDA/TTI Server: "
             << FileTransferBridgeAppUtil::GetTimeSinceInMilliseconds(m_TtiAttributes.cdaClientStartupTime)
             << " ms since CDA Client startup", AIS_LOG_DEBUG, false);
     std::lock_guard<std::mutex> scopeLock( m_TtiAttributes.lockStub );
     m_TtiAttributes.connectionInProgress = true;
 
     // If the channel has been created successfully then created CDA/TTI stub and see if the server is alive
     if ((nullptr != m_spChannel) && (nullptr == m_spCdaTtiServerStub)) {
         // Create a stub. This stub will be used to invoke remote procedure calls (e.g. SubmitFileToDestination)
         m_spCdaTtiServerStub = TelematicsTransfer::NewStub( m_spChannel );
         if (nullptr != m_spCdaTtiServerStub) {
             // Try to send a test file
             ClientContext context;
             context.set_deadline(std::chrono::system_clock::now() + GRPC_TEST_CONNECT_DEADLINE_TIMEOUT);
 
             TransferReturnMessage reply;
             DestinationMessage cdaMessage;
             { // Set message contents
                 TransferMessage* pMessageStorage = cdaMessage.mutable_messagecontents();
                 pMessageStorage->set_filetype(10059);
                 pMessageStorage->set_filenamehint("connection_test");
                 pMessageStorage->set_filecontents("Connection Test");
             }
             cdaMessage.set_destination(DestinationMessage_DESTINATION_TELEMATICS);
 
             auto status = m_spCdaTtiServerStub->SubmitFileToDestination(&context, cdaMessage, &reply);
             if (!status.ok() || (QUEUED_SUCCESS != reply.returncode())) {
                     AIS_LOG_WARN("CdaTtiServerStub->SubmitFileToDestination reply not successful: (%s)", TRANSFER_RETURN_Name(reply.returncode()).c_str());
                     m_spCdaTtiServerStub.reset();
                 }
                 else {
                     m_TtiAttributes.connectionEstablished = true;
                     BRIDGE_APP_LOG("Successfully established connection with CDA/TTI server after "
                             << FileTransferBridgeAppUtil::GetTimeSinceInMilliseconds(m_TtiAttributes.cdaClientStartupTime)
                             << " ms of CDA Client startup", AIS_LOG_NOTICE, true);
             }
         }
     }
 
     BRIDGE_APP_LOG("Finished trying to connect to CDA/TTI Server: "
             << FileTransferBridgeAppUtil::GetTimeSinceInMilliseconds(m_TtiAttributes.cdaClientStartupTime)
              << " ms since CDA Client startup", AIS_LOG_DEBUG, false);
 
     m_TtiAttributes.connectionInProgress = false;
 }
 
 ////////////////////////////////////////////////////////////////////////////
 // Function        : FileTransferBridgeAppCda::ConnectSftThreadImplementation
 // Description     : Implementation of the thread that attempts to connect
 //                   with CDA/SFT servers
 // Return Type     : None
 // Argument [in]   : None
 // Argument [out]  : None
 // Argument [I/O]  : None
 ////////////////////////////////////////////////////////////////////////////
 void FileTransferBridgeAppCda::ConnectSftThreadImplementation( void )
 {
     BRIDGE_APP_LOG("Connecting to CDA/SFT Server: "
             << FileTransferBridgeAppUtil::GetTimeSinceInMilliseconds(m_SftAttributes.cdaClientStartupTime)
             << " ms since CDA Client startup", AIS_LOG_DEBUG, false);
     std::lock_guard<std::mutex> scopeLock(m_SftAttributes.lockStub);
     m_SftAttributes.connectionInProgress = true;
 
     // If the channel has been created successfully then created CDA/SFT stub and see if the server is alive
     if ((nullptr != m_spChannel) && (nullptr == m_spCdaSftServerStub)) {
         // Create a stub. This stub will be used to invoke remote procedure calls (e.g. SubmitFileToSystem)
         m_spCdaSftServerStub = SystemFileTransfer::NewStub( m_spChannel );
         if (nullptr != m_spCdaSftServerStub) {
             // Try to send a test file
             ClientContext context;
             context.set_deadline(std::chrono::system_clock::now() + GRPC_TEST_CONNECT_DEADLINE_TIMEOUT);
 
             SystemFileReturn reply;
             SystemFileDestination cdaMessage;
             { // Set message contents
                 SystemFile* pMessageStorage = cdaMessage.mutable_messagecontents();
                 pMessageStorage->set_filetype(10059);
                 pMessageStorage->set_sourcefid(0xFF);
                 pMessageStorage->set_filecontents("Connection Test");
             }
             cdaMessage.set_destinationfid(0xAA);
 
             auto status = m_spCdaSftServerStub->SubmitFileToSystem(&context, cdaMessage, &reply);
             if (!status.ok() || (SystemFileReturn::QUEUED_SUCCESS != reply.returncode())) {
                  AIS_LOG_WARN("CdaSftServerStub->SubmitFileToSystem reply not successful (%s)", SystemFileReturn_SYSTEM_FILE_RETURN_Name(reply.returncode()).c_str());
                  m_spCdaSftServerStub.reset();
                 }
            else {
                     // We have a connection
                     m_SftAttributes.connectionEstablished = true;
                     BRIDGE_APP_LOG("Successfully established connection with CDA/SFT server after "
                             << FileTransferBridgeAppUtil::GetTimeSinceInMilliseconds(m_SftAttributes.cdaClientStartupTime)
                             << " ms of CDA Client startup", AIS_LOG_NOTICE, true);
             }
         }
     }
 
    BRIDGE_APP_LOG("Finished trying to connect to CDA/SFT Server: "
            << FileTransferBridgeAppUtil::GetTimeSinceInMilliseconds(m_SftAttributes.cdaClientStartupTime)
            << " ms since CDA Client startup", AIS_LOG_DEBUG, false);
 
    m_SftAttributes.connectionInProgress = false;
 }
 
 void FileTransferBridgeAppCda::UpdateSendDataFileReturnCode(SendDataFileReturnCode& code, const SendDataFileReturnCode& newCode) {
     if (SendDataFileReturnCode::UNKNOWN == code) {
         code = newCode;
     }
     else if (newCode != code) {
         if ((SendDataFileReturnCode::OK == code) || (SendDataFileReturnCode::OK == newCode)) {
             // Current code is OK, or new code is OK, which means there has been some success.
             // To maintain existing functionality, and due to the fact that the
             // current design doesn't allow for destination node specific transmit queues,
             // we must consider this to still be a successful operation.
             code = SendDataFileReturnCode::OK;
         }
         else {
             // Both are not OK and are different, multiple different errors.
             code = SendDataFileReturnCode::MULTIPLE_ERRORS;
         }
     }
     else {
         // New code and current code are the same.
     }
 }
