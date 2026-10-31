////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: FileTransferBridgeApp
//
// File Name: FileTransferBridgeApp.cpp
//
//  Abstract: CDA File Transfer Bridge application main class definitions:
//            the application receives data files
//            from other apps via SCS and transfers them to
//            Common Data Access server over Telematics Transfer Interface
//            or using the System File Transfer protocol
//
////////////////////////////////////////////////////////

#include <algorithm> // Needed for std::find

#include <interfaces/IoTHubCommsInboundMessage/InterfaceTypes.h>
#include <interfaces/IoTHubCommsOutboundMessage/InterfaceTypes.h>
#include <interfaces/IoTHubCommsOutboundReturn/InterfaceTypes.h>

#include "FileTransferBridgeApp.h"
#include "FileTransferBridgeAppLog.h"
#include "FileTransferBridgeAppUtil.h"

#define TIMEOUT_MS_RX_THREAD_HARDSTOP     4400 // Time since commanding a thread to stop after which it should be "killed"
#define TIMEOUT_MS_RX_THREAD_SOFTSTOP     400  // Time since commanding a thread to stop after which it should be interrupted

using namespace task;
using namespace FileTransferBridge;

////////////////////////////////////////////////////////////////////////////
// Function        : task::getTaskImplementation
// Description     : Wrapper that instantiates the Bridge app
// Return Type     : AbstractTaskCore* - Task attributes
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
AbstractTaskCore* task::getTaskImplementation(void)
{
   static FileTransferBridgeApp thisTask( "FileTransferBridgeApp" );
   return dynamic_cast<Task*>( &thisTask );
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeApp::FileTransferBridgeApp
// Description     : Class constructor
// Return Type     : N/A
// Argument [in]   : const std::string& taskName - Name of the task
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
FileTransferBridgeApp::FileTransferBridgeApp( const std::string& taskName ):
            Task( taskName ),
            m_CfgObject( ),
            m_AppInitialized( false ),
            m_ShutdownInProgress( false ),
            m_spCdaClient(),
            m_spCurrentChannel(),
            m_iotHubComms(),
            m_pFileTransferBridgeAppReqInput( nullptr ),
            m_pFileTransferBridgeAppRespOutput( nullptr ),
            m_pFileTransferBridgeAppRecvFileOutput( nullptr ),
            m_pFileTransferBridgeAppCreateReqOutput( nullptr ),
            m_pAppRegInput( nullptr ),
            m_pAppRegOutput( nullptr ),
            m_AppReg( taskName )
{
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeApp::initialize
// Description     : Initializes the application interfaces
// Return Type     : bool - true if the initialization was successful, otherwise false
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeApp::initialize( )
{
   BRIDGE_APP_LOG( getTaskName() << " initializing", AIS_LOG_DEBUG, false );
   m_AppInitialized = false;
   m_ShutdownInProgress = false;

   // Parse Ruby configuration first thing
   if ( m_CfgObject.ParseConfig( getTaskConfig(), getTaskParser() ) )
   {
      FileTransferBridgeAppCfg_t configTable = m_CfgObject.GetConfiguration();

      // Initialize log
      FileTransferBridgeAppLog::GetInst()->Init( configTable );

      // Configuration IoT Hub Comms
      m_iotHubComms.setOutboundMessageQueueMaxSize(configTable.IoTHubOutboundQueueMaxSize);
      m_iotHubComms.setInboundFileTypes(configTable.IoTHubInboundFileTypes.cbegin(),
              configTable.IoTHubInboundFileTypes.cend());

      // Create an instance of CDA Client
      m_spCdaClient.reset( new FileTransferBridgeAppCda( configTable.ClientConnModeSecure,
            configTable.CertChainFilePath,
            configTable.CDAServerIPAddress,
            configTable.CDAServerPort ) );
      if (nullptr == m_spCdaClient) {
         AIS_LOG_FATAL("Unable to create CDA Client.");
      }
      // Initialize the rest of the application
      else if (InitInterfaces()) {
         InitTxThread( configTable );
         InitRxThreads( configTable );
         m_AppInitialized = true;
      }
   }

   return m_AppInitialized;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeApp::executive
// Description     : Executive application loop
// Return Type     : bool - true if the loop pass was successful, otherwise false
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeApp::executive( )
{
   BRIDGE_APP_LOG( getTaskName() << " executing", AIS_LOG_DEBUG, false );

   //Update app registrations
   ExecUpdateAppRegState();

   // Go through every file transfer request that was received from peer applications
   FileTransferBridgeRequest cdaTxRequest;
   while ( m_pFileTransferBridgeAppReqInput->get( cdaTxRequest ) )
   {
      ExecProcessTxRequest( cdaTxRequest );
   }

   // Check for connection with the server and connect if necessary
   if ( ( !m_ShutdownInProgress && m_spCdaClient->ConnectToCDAServer() ) ||
        ( m_ShutdownInProgress && m_spCdaClient->IsConnActive() ) )
   {
      // Flag Transmit thread to start sending whatever is in its queue
      if ( m_CfgObject.GetConfiguration().RebuildQueueEveryCycle )
      {
         m_spTransmitThread->CheckForFilesToQueue();
      }
      m_spTransmitThread->UnblockThread();
      // Unblock receive threads if they were waiting for a connection
      for ( auto& thread : m_spReceiveThreads )
      {
         thread->UnblockThread();
      }

   }

   if (!m_ShutdownInProgress) {
       // If shutdown is not in progress
       // Check to see if the CDA client got a new grpc channel.
       // If it did, then start/re-start the IoTHubComms
       const auto& channel = m_spCdaClient->getChannel();
       if (channel != m_spCurrentChannel) {
           m_spCurrentChannel = channel;
           // Start IoTHub
           if (!m_iotHubComms.start(m_spCurrentChannel)) {
               AIS_LOG_ERROR("Could not start IoTHub comms.");
           }
       }
   }


   return true;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeApp::cleanup
// Description     : Runs cleaning routines during the application shutting down:
//                      - Immediately issues a stop to the threads listening to CDA server
//                      - During a key-off timeout specified in Ruby configuration file
//                        continues to process the files from other applications to be
//                        sent out to the CDA server
//                      - Issues a stop to all threads sending files to CDA server
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeApp::cleanup( )
{
   const auto timeStartOfCleanup = FileTransferBridgeAppUtil::GetTimeNow();
   BRIDGE_APP_LOG( getTaskName() << " clean up", AIS_LOG_DEBUG, false );
   m_ShutdownInProgress = true;

   m_iotHubComms.stop(); // Signal to stop without blocking

   if ( m_AppInitialized )
   {
      // ================== Step 1: Issue a request for the RX threads to stop ==================
      for ( auto& thread : m_spReceiveThreads )
      {
         thread->StopThread();
      }

      // ================== Step 2: Keep TX thread busy until the exit conditions ==================
      // Exit condition 1: All RX threads have been shut down AND no other app is registered with this one
      // Exit condition 2: key-off timeout is reached
      int32_t timeSinceStartOfCleanup = FileTransferBridgeAppUtil::GetTimeSinceInMilliseconds( timeStartOfCleanup );
      while ( ( CleanCheckRxThreads( timeSinceStartOfCleanup ) || !m_AppReg.IsAppRegListEmpty() ) &&
            static_cast<unsigned_32>( timeSinceStartOfCleanup ) < m_CfgObject.GetConfiguration().KeyOffTimeOutMSec )
      {
         // Act normal until the key off timeout (except we're not receiving anything from the CDA server anymore)
         usleep( ( 1.0 / m_CfgObject.GetConfiguration().CycleRateHz ) * 1000000 );
         (void)executive();

         // Get a new time difference
         timeSinceStartOfCleanup = FileTransferBridgeAppUtil::GetTimeSinceInMilliseconds( timeStartOfCleanup );

         //Update app registrations
         ExecUpdateAppRegState();
      }

      // ================== Step 3: Issue a request for TX thread to stop ==================
      m_spTransmitThread->StopThread();

      m_AppInitialized = false;
   }

   // ================== Step 4: Join all threads with this (main) thread and destroy them ==================
   BRIDGE_APP_LOG( "Destroying all threads and CDA client", AIS_LOG_DEBUG, false );
   m_spTransmitThread.reset();
   for ( auto& thread : m_spReceiveThreads )
   {
      thread.reset();
   }

   m_iotHubComms.stop(true); // Signal to stop with blocking

   // Also destroy the CDA Client
   m_spCdaClient.reset();

   BRIDGE_APP_LOG( "cleanup() complete", AIS_LOG_DEBUG, false );
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeApp::InitInterfaces
// Description     : initialize() helper method that initializes SCS interfaces
// Return Type     : bool - 'true' if successful, 'false' otherwise
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeApp::InitInterfaces( void )
{
   bool ret_val = false;

   // Fetch the interfaces
   m_pFileTransferBridgeAppReqInput = dynamic_cast<FileTransferBridgeRequestInput*>( InterfaceDb::fetch( "FileTransferBridgeRequestInput" ) );
   m_pFileTransferBridgeAppRespOutput = dynamic_cast<FileTransferBridgeResponseOutput*>( InterfaceDb::fetch( "FileTransferBridgeResponseOutput" ) );
   m_pFileTransferBridgeAppRecvFileOutput = dynamic_cast<FileTransferBridgeIndicationOutput*>( InterfaceDb::fetch( "FileTransferBridgeIndicationOutput" ) );
   m_pFileTransferBridgeAppCreateReqOutput = dynamic_cast<CreateFileRequestOutput*>( InterfaceDb::fetch( "CreateFileRequestOutput" ) );

   m_pAppRegInput = dynamic_cast<AppRegInput *>(InterfaceDb::fetch("AppRegInput"));
   m_pAppRegOutput = dynamic_cast<AppRegOutput*>( InterfaceDb::fetch("AppRegOutput") );

   bool iotHubCommsOk = true;
   { // Get IoTHub Communications Interfaces
       IoTHubCommsInboundMessageOutput* pInboundMessageOutput =
               dynamic_cast<IoTHubCommsInboundMessageOutput*>(InterfaceDb::fetch("IoTHubInboundMessageOutput"));
       if (nullptr == pInboundMessageOutput) {
           AIS_LOG_ERROR("No IoTHub inbound message output channel defined.");
           iotHubCommsOk = false;
       }

       IoTHubCommsOutboundMessageInput* pOutboundMessageInput =
               dynamic_cast<IoTHubCommsOutboundMessageInput*>(InterfaceDb::fetch("IoTHubOutboundMessageInput"));
       if (nullptr == pOutboundMessageInput) {
           AIS_LOG_ERROR("No IoTHub outbound message input channel defined.");
           iotHubCommsOk = false;
       }

       IoTHubCommsOutboundReturnOutput* pOutboundReturnOutput =
               dynamic_cast<IoTHubCommsOutboundReturnOutput*>(InterfaceDb::fetch("IoTHubOutboundReturnOutput"));
       if (nullptr == pOutboundReturnOutput) {
           AIS_LOG_ERROR("No IoTHub outbound return output channel defined.");
           iotHubCommsOk = false;
       }

       // Install interfaces to IoTHubComms.
       m_iotHubComms.installScsChannels(pInboundMessageOutput, pOutboundMessageInput, pOutboundReturnOutput);
   }

   if ( false == ( ret_val = ( nullptr != m_pFileTransferBridgeAppReqInput) &&
                             ( nullptr != m_pFileTransferBridgeAppRespOutput) &&
                             ( nullptr != m_pFileTransferBridgeAppRecvFileOutput) &&
                             ( nullptr != m_pFileTransferBridgeAppCreateReqOutput) &&
                             ( nullptr != m_pAppRegInput) &&
                             ( nullptr != m_pAppRegOutput ) &&
                             ( iotHubCommsOk ) ) )
   {
      BRIDGE_APP_LOG( getTaskName() << " failed to initialize its interfaces", AIS_LOG_FATAL, true );
   }

   return ret_val;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeApp::InitRxThread
// Description     : initialize() helper method that starts CDA receive thread
// Return Type     : None
// Argument [in]   : const FileTransferBridgeAppCfg_t& configTable -
//                      application configuration table containing essential info
//                      for the thread
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeApp::InitRxThreads( const FileTransferBridgeAppCfg_t& configTable )
{
   // First we drop all the previously received files
   FileTransferBridgeAppUtil::CleanDirectory( configTable.RecvDataFileStoreDirPath );

   // Generate a map of CDA/TTI nodes that we'll be expecting the files from
   std::map< CdaNode_t, std::vector<CdaFileType_t> > nodeMap;
   bool expectingSftFiles = false;
   for ( auto& fileTypeToProperties : configTable.MapFileTypes )
   {
      // Add all TTI nodes
      for ( auto& receiveNode : fileTypeToProperties.second.CdaTtiSourceNodes )
      {
         // Does the map contain this node already?
         if ( nodeMap.find( receiveNode ) == nodeMap.end() )
         {
            // It doesn't, so initialize with this file type
            nodeMap[receiveNode].push_back( fileTypeToProperties.first );
         }
         else if ( !VECTOR_HAS_ELEMENT( fileTypeToProperties.first, nodeMap[receiveNode] ) )
         {
            // Did not find the current file type in the list of file types supported by the node, so add it to the list
            nodeMap[receiveNode].push_back( fileTypeToProperties.first );
         }
      }

      expectingSftFiles |= fileTypeToProperties.second.AcceptCdaSftTraffic;
   }

   // Instantiate and start new threads [new] - one thread per CDA/TTI node
   for ( auto& node : nodeMap )
   {
      m_spReceiveThreads.push_back( std::unique_ptr<FileTransferBridgeAppThreadRx>( new FileTransferBridgeAppThreadRx(
            node.first,
            node.second,
            configTable,
            m_spCdaClient,
            m_pFileTransferBridgeAppRecvFileOutput,
            m_LockScsForReceiveThreads ) ) );
   }

   // Also instantiate and start a single thread for handling all CDA/SFT incoming traffic, including files and report trigger
   if ( expectingSftFiles || configTable.SupportReportTrigger )
   {
      m_spReceiveThreads.push_back( std::unique_ptr<FileTransferBridgeAppThreadRx>( new FileTransferBridgeAppThreadRx(
            configTable,
            m_spCdaClient,
            m_pFileTransferBridgeAppRecvFileOutput,
            m_pFileTransferBridgeAppCreateReqOutput,
            m_LockScsForReceiveThreads ) ) );
   }
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeApp::InitTxThread
// Description     : initialize() helper method that starts CDA transmit thread
// Return Type     : None
// Argument [in]   : const FileTransferBridgeAppCfg_t& configTable -
//                      application configuration table containing essential info
//                      for the thread
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeApp::InitTxThread( const FileTransferBridgeAppCfg_t& configTable )
{
   // Instantiate and start new thread [new]
   m_spTransmitThread.reset( new FileTransferBridgeAppThreadTx( configTable, m_spCdaClient ) );
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeApp::ExecProcessTxRequest
// Description     : executive() helper method that processes a request
//                   from another app to transfer a file over CDA
// Return Type     : None
// Argument [in]   : const FileTransferBridgeRequest& cdaTxRequest -
//                   SCS object containing the request
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeApp::ExecProcessTxRequest( const FileTransferBridgeRequest& cdaTxRequest )
{
   FileInfo_t fileInfo;
   FileTransferBridgeResponse cdaTxResponse;
   cdaTxResponse.Response.FileName = cdaTxRequest.fileAttr.DirPath + cdaTxRequest.fileAttr.Name;
   cdaTxResponse.Response.Msg = ""; // Nobody is interested in this

   // Check the file attributes first
   if ( !FileTransferBridgeAppUtil::GetFileAttributes( cdaTxRequest.fileAttr.DirPath, cdaTxRequest.fileAttr.Name, cdaTxRequest.fileAttr.FidSource, cdaTxRequest.fileAttr.FidDestination, fileInfo ) )
   {
      cdaTxResponse.Response.Ret = static_cast<FileTransferBridgeResponseStorage::Response_t>(SCS_CDA_TTI_BRIDGE_FILE_NOT_FOUND);
      BRIDGE_APP_LOG( getTaskName() << " received a request to transfer file " << cdaTxRequest.fileAttr.Name << ", but can't find it", AIS_LOG_ERROR, true );
   }
   else if ( cdaTxRequest.fileAttr.SizeInBytes != fileInfo.SizeInBytes )
   {
      cdaTxResponse.Response.Ret = static_cast<FileTransferBridgeResponseStorage::Response_t>(SCS_CDA_TTI_BRIDGE_FILE_SIZE_MISMATCH);
      BRIDGE_APP_LOG( getTaskName() << " received file " << fileInfo.Name << " to transfer, but its size does not match the size specified", AIS_LOG_ERROR, true );
   }
   else if ( cdaTxRequest.fileAttr.TelematicsFileNumber != fileInfo.TelematicsFileNumber )
   {
      cdaTxResponse.Response.Ret = static_cast<FileTransferBridgeResponseStorage::Response_t>(SCS_CDA_TTI_BRIDGE_FILE_TYPE_MISMATCH);
      BRIDGE_APP_LOG( getTaskName() << " received file " << fileInfo.Name << " to transfer, but its type does not match the type specified", AIS_LOG_ERROR, true );
   }
   else
   {
      // Now that the file attributes check out try to add this file to thread's queue
      cdaTxResponse.Response.Ret = static_cast<FileTransferBridgeResponseStorage::Response_t>(m_spTransmitThread->TryToQueue( fileInfo ));
      if ( static_cast<FileTransferBridgeResponseStorage::Response_t>(SCS_CDA_TTI_BRIDGE_FILE_TYPE_NOT_SUPPORTED) == cdaTxResponse.Response.Ret )
      {
         BRIDGE_APP_LOG( getTaskName() << " received file " << fileInfo.Name << " to transfer, but is not handling these file types", AIS_LOG_ERROR, true );
      }
   }

   m_pFileTransferBridgeAppRespOutput->publish( cdaTxResponse );
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeApp::CleanCheckRxThread
// Description     : cleanup() helper method that monitors the state
//                   of the Receive thread, since it requires more than just
//                   an issued stop due to the blocking gRPC call
// Return Type     : bool - 'true' when at least one Rx thread is not shut down, 'false' otherwise
// Argument [in]   : const int32_t& timeInCleanup - time (in ms) since the cleanup started
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeApp::CleanCheckRxThreads( const int32_t& timeInCleanup )
{
   bool atLeastOneThreadActive = false;

   for ( auto& thread : m_spReceiveThreads )
   {
      // Check if the RX thread is stuck and requires a nudge (first we try to interrupt it, then force stop)
      if ( thread->IsActive() )
      {
         if ( timeInCleanup > TIMEOUT_MS_RX_THREAD_SOFTSTOP )
         {
            // Try to interrupt the blocking gRPC call
            thread->InterruptThreadListening();
         }

         if ( timeInCleanup > TIMEOUT_MS_RX_THREAD_HARDSTOP )
         {
            // Burn it down
            (void)thread->ForceStopThread();
         }

         atLeastOneThreadActive = true;
      }
   }

   return atLeastOneThreadActive;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeApp::ExecUpdateAppRegState
// Description     : executive() and cleanup() helper method that checks
//                   if any peer applications would like to register or unregister
//                   with this application. During cleanup() this app postpones
//                   its shutdown to allow other apps to unregister first.
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeApp::ExecUpdateAppRegState( void )
{
   // Check for any incoming SCS traffic via the AppReg interface
   AppReg appRegRequestResponse;
   while ( m_pAppRegInput->get( appRegRequestResponse ) )
   {
      // Handle only the messages intended for this app
      if( appRegRequestResponse.IsMsgAddressedToMe( m_AppReg.GetAppName() ) )
      {
         const bool isRequest = ( appRegRequestResponse.GetMsgType() == AppRegStorage::APP_REG_REQ );
         BRIDGE_APP_LOG( "App '" << appRegRequestResponse.GetAppName() << "' sent us a (reg/unreg) request "
               << static_cast<int>( appRegRequestResponse.GetAppState() ), AIS_LOG_NOTICE, false );

         // Send a response
         if(isRequest)
         {
            m_AppReg.UpdateAppRegState( &appRegRequestResponse );
            m_pAppRegOutput->publish( appRegRequestResponse );
         }
      }
   }
}
