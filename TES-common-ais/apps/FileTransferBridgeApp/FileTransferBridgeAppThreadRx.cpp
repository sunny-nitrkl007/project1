////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: FileTransferBridgeAppThreadRx
//
// File Name: FileTransferBridgeAppThreadRx.cpp
//
//  Abstract: This file is a class implementation for threads
//            receiving files from CDA Server
//
////////////////////////////////////////////////////////

#include "FileTransferBridgeAppThreadRx.h"
#include "FileTransferBridgeAppUtil.h"

#define LOG_FROM_VECTOR( logStr, vectorContainer ) {                             \
   std::stringstream sstream;                                                    \
   for (const auto& vElem : vectorContainer)                                     \
   {                                                                             \
      sstream << vElem << " ";                                                   \
   }                                                                             \
   BRIDGE_APP_LOG( "    " logStr ": " << sstream.str(), AIS_LOG_NOTICE, true );      \
}

using namespace FileTransferBridge;
std::mutex* FileTransferBridgeAppThreadRx::m_pLockSCS = nullptr;
CreateFileRequestOutput* FileTransferBridgeAppThreadRx::m_pScsObjectCommand = nullptr;

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadRx::FileTransferBridgeAppThreadRx
// Description     : Class constructor that starts an Rx thread for a CDA/TTI node
// Return Type     : N/A
// Argument [in]   : const CdaNode_t& sourceNodeServiced - CDA node that this thread services,
//                   const std::vector<CdaFileType_t>& fileTypes - File types associated
//                      with CDA node,
//                   const FileTransferBridgeAppCfg_t& configTable - Application configuration table
// Argument [out]  : None
// Argument [I/O]  : - std::shared_ptr<FileTransferBridgeAppCda> pCDAClient - Pointer to the
//                      instance of CDA Client that this thread could use,
//                   - FileTransferBridgeIndication* pScsObject -
//                      Pointer to the SCS object that is used to send out data,
//                   - std::mutex& scsMutexLock - Reference to the mutex lock
//                      that guards the outgoing SCS messages
////////////////////////////////////////////////////////////////////////////
FileTransferBridgeAppThreadRx::FileTransferBridgeAppThreadRx( const CdaNode_t& sourceNodeServiced,
      const std::vector<CdaFileType_t>& fileTypes,
      const FileTransferBridgeAppCfg_t& configTable,
      std::shared_ptr<FileTransferBridgeAppCda> pCDAClient,
      FileTransferBridgeIndicationOutput* pScsObjectFile,
      std::mutex& scsMutexLock ):
                  m_ServicedSourceNodes { sourceNodeServiced },
                  m_ServicedFileTypes( fileTypes ),
                  m_FilesPath( configTable.RecvDataFileStoreDirPath ),
                  m_MaxSizeOfFile( configTable.MaxDataFileSizeInBytes ),
                  m_TerminateThread ( false ),
                  m_ThreadActive( false ),
                  m_PendingConnection( true ),
                  m_spCDAClient( pCDAClient ),
                  m_pCDAContext( nullptr ),
                  m_pScsObjectFile( pScsObjectFile ),
                  m_InboundFilesCount( 0 ),
                  m_rxThreadState( THREAD_NOT_INITIALIZED )
{
   // Create queues for every file type serviced
   for (const auto& fileType : fileTypes)
   {
      const CdaFileSize_t& queueSize = configTable.MapFileTypes.at( fileType ).RxQueueSize;
      m_MapFileQueues[fileType].reset( new FileTransferBridgeAppQueue(
            fileType,
            queueSize,
            configTable.MaxDataFileSizeInBytes,
            configTable.RecvDataFileStoreDirPath ) );
   }

   // Update static members
   m_pLockSCS = &scsMutexLock;
   m_pScsObjectCommand = nullptr; // Used only by CDA/SFT thread

   // Create and start the thread
   BRIDGE_APP_LOG( "Starting CDA/TTI RX thread for CDA node "
         << m_ServicedSourceNodes.at(0) << " to work with:", AIS_LOG_NOTICE, true );
   LOG_FROM_VECTOR( "File types", m_ServicedFileTypes );
   m_spThread.reset( new std::thread( [this] { ThreadImplementationTti(); } ) );
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadRx::FileTransferBridgeAppThreadRx
// Description     : Class constructor that starts an Rx thread for all CDA/SFT nodes
// Return Type     : N/A
// Argument [in]   : const FileTransferBridgeAppCfg_t& configTable - Application configuration table
// Argument [out]  : None
// Argument [I/O]  : - std::shared_ptr<FileTransferBridgeAppCda> pCDAClient - Pointer to the
//                      instance of CDA Client that this thread could use,
//                   - FileTransferBridgeIndication* pScsObject -
//                      Pointer to the SCS object that is used to send out data,
//                   - CreateFileRequestOutput* pScsObjectCommand - Pointer
//                      to the SCS object that is used to send triggers
//                   - std::mutex& scsMutexLock - Reference to the mutex lock
//                      that guards the outgoing SCS messages
////////////////////////////////////////////////////////////////////////////
FileTransferBridgeAppThreadRx::FileTransferBridgeAppThreadRx( const FileTransferBridgeAppCfg_t& configTable,
      std::shared_ptr<FileTransferBridgeAppCda> pCDAClient,
      FileTransferBridgeIndicationOutput* pScsObjectFile,
      CreateFileRequestOutput* pScsObjectCommand,
      std::mutex& scsMutexLock ):
                  m_MapFileTypesToProperties( configTable.MapFileTypes ),
                  m_FilesPath( configTable.RecvDataFileStoreDirPath ),
                  m_MaxSizeOfFile( configTable.MaxDataFileSizeInBytes ),
                  m_TerminateThread ( false ),
                  m_ThreadActive( false ),
                  m_PendingConnection( true ),
                  m_spCDAClient( pCDAClient ),
                  m_pCDAContext( nullptr ),
                  m_pScsObjectFile( pScsObjectFile ),
                  m_InboundFilesCount( 0 ),
                  m_rxThreadState( THREAD_NOT_INITIALIZED )
{
   // Update static members
   m_pLockSCS = &scsMutexLock;
   m_pScsObjectCommand = pScsObjectCommand;

   // Report Trigger message comes with its own file type. Check if we support Report Trigger for any file types and if so
   // then add the report trigger "file type" to the list of serviced file types
   if ( configTable.SupportReportTrigger )
   {
      m_ServicedFileTypes.push_back( TRIGGER_TYPE );
   }

   // Go through the map of all file types picked from .rb config
   bool acceptToAllDestinations = false;
   bool acceptFromAllSources = false;
   for (const auto& fileTypeToProperties : configTable.MapFileTypes)
   {
      if ( fileTypeToProperties.second.AcceptCdaSftTraffic )
      {
         // First let's make sure we add the current file type to the list of serviced file types
         m_ServicedFileTypes.push_back( fileTypeToProperties.first );

         // Create a queue for this file type
         const CdaFileSize_t& queueSize = configTable.MapFileTypes.at( fileTypeToProperties.first ).RxQueueSize;
         m_MapFileQueues[fileTypeToProperties.first].reset( new FileTransferBridgeAppQueue(
               fileTypeToProperties.first,
               queueSize,
               configTable.MaxDataFileSizeInBytes,
               configTable.RecvDataFileStoreDirPath ) );

         // Check if the current file type expects messages from all sources and/or to all destinations
         acceptFromAllSources |= fileTypeToProperties.second.CdaSftSourceNodes.empty() && fileTypeToProperties.second.AcceptCdaSftTraffic;
         acceptToAllDestinations |= fileTypeToProperties.second.CdaSftIntendedDestinationNodes.empty() && fileTypeToProperties.second.AcceptCdaSftTraffic;

         // Now let's add all of the file type's expecting CDA nodes to our lists for internal tracking
         if ( !acceptFromAllSources )
         {
            ADD_UNIQUE_ELEMENTS_FROM_VECTOR( m_ServicedSourceNodes, fileTypeToProperties.second.CdaSftSourceNodes );
         }
         else
         {
            // Empty the list to indicate that all FIDs are processed
            CdaNodeList_t().swap( m_ServicedSourceNodes );
         }
         if ( !acceptToAllDestinations )
         {
            ADD_UNIQUE_ELEMENTS_FROM_VECTOR( m_ServicedDestinationNodes, fileTypeToProperties.second.CdaSftIntendedDestinationNodes );
         }
         else
         {
            // Empty the list to indicate that all FIDs are processed
            CdaNodeList_t().swap( m_ServicedDestinationNodes );
         }
      }

      ADD_UNIQUE_ELEMENTS_FROM_VECTOR( m_ServicedTriggerNodes, fileTypeToProperties.second.CdaSftReportTriggerNodes );
   }

   // Create and start the thread
   BRIDGE_APP_LOG( "Starting CDA/SFT RX thread that will work with:", AIS_LOG_NOTICE, true );
   LOG_FROM_VECTOR( "File types", m_ServicedFileTypes );
   LOG_FROM_VECTOR( "Remote source FIDs for files", m_ServicedSourceNodes );
   LOG_FROM_VECTOR( "Remote source FIDs for triggers", m_ServicedTriggerNodes );
   LOG_FROM_VECTOR( "Local destination FIDs", m_ServicedDestinationNodes );
   m_spThread.reset( new std::thread( [this] { ThreadImplementationSft(); } ) );
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadRx::~FileTransferBridgeAppThreadRx
// Description     : Class destructor that joins with all Rx threads
// Return Type     : N/A
// Argument [in]   : N/A
// Argument [out]  : N/A
// Argument [I/O]  : N/A
////////////////////////////////////////////////////////////////////////////
FileTransferBridgeAppThreadRx::~FileTransferBridgeAppThreadRx()
{
   const std::thread::id threadId = m_spThread->get_id();
   BRIDGE_APP_LOG( "Joining thread " << threadId << ". Still running = " << static_cast<int>( m_ThreadActive ), AIS_LOG_DEBUG, false );

   if ( m_spThread->joinable() )
   {
      m_spThread->join();
   }
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadRx::ThreadImplementationTti
// Description     : Implementation of an RX thread for CDA/TTI node
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppThreadRx::ThreadImplementationTti( void )
{
   m_rxThreadState = THREAD_RUNNING;
   m_ThreadActive = true;

   // This outer loop handles one single connection with the CDA server per loop cycle
   // I.e. if the connection is lost/broken then we start another loop cycle
   while( !m_TerminateThread )
   {
      BRIDGE_APP_LOG( "Thread [" << THREAD_ID << "] " << " is entering the loop", AIS_LOG_DEBUG, false );

      FileTransferBridgeAppCda::RxStreamAttributesTti_s streamAttributesTti( m_ServicedFileTypes, m_ServicedSourceNodes.at(0) );
      SetThreadClientContext( &streamAttributesTti.clientContext );

      // Block the thread, waiting for a connection with CDA/TTI server
      WaitToBeUnblocked();

      // Register with the CDA server for the file types that we're interested in
      if ( !m_TerminateThread && m_spCDAClient->IsConnActive( m_ServicedSourceNodes.at(0) ) &&
            m_spCDAClient->RegisterForFileType( streamAttributesTti ) )
      {
         std::string fileContainer;
         CdaFileType_t fileTypeContainer;
         std::string nameContainer;

         // This inner loop handles each received file: one loop cycle = one file received
         while ( !m_TerminateThread &&
                 m_spCDAClient->ReceiveDataFile( m_TerminateThread, streamAttributesTti, fileContainer, fileTypeContainer, nameContainer ) )
         {
            const CdaFileSize_t fileSize = fileContainer.size();
            if( fileSize > m_MaxSizeOfFile )
            {
               BRIDGE_APP_LOG( "File received by CDA/TTI thread " << THREAD_ID << " is larger than max ("
                     << fileSize << " > " << m_MaxSizeOfFile << ") and is therefore ignored", AIS_LOG_WARN, true );
            }
            else
            {
               ProcessReceivedFile( fileContainer, fileSize, fileTypeContainer, nameContainer );
            }
         }

         // Check if the main thread requested a shutdown
         if( !m_TerminateThread )
         {
            // Main thread didn't request shutdown. We must have lost the connection with the CDA server
            std::unique_lock<std::mutex> scopeLock( m_LockPendingConnection );
            m_PendingConnection = true;
            m_spCDAClient->SetConnInactive( m_ServicedSourceNodes.at(0) );
            BRIDGE_APP_LOG( "CDA/TTI RX thread " << THREAD_ID << " got a broken read. Server disconnected?", AIS_LOG_ALERT, true );
         }
      }

      // Reset the context pointer
      SetThreadClientContext( nullptr );

      if (!m_TerminateThread) {
          // Give me a break here... stop the while(true); loop
          std::this_thread::sleep_for(std::chrono::milliseconds(500));
      }
   }

   BRIDGE_APP_LOG( "CDA/TTI RX thread " << THREAD_ID << " servicing node " << m_ServicedSourceNodes.at(0) << " is ending", AIS_LOG_NOTICE, false );
   m_ThreadActive = false;
   m_rxThreadState = THREAD_STOPPED;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadRx::ThreadImplementationSft
// Description     : Implementation of an RX thread for CDA/SFT node
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppThreadRx::ThreadImplementationSft( void )
{
   m_rxThreadState = THREAD_RUNNING;
   m_ThreadActive = true;

   // This outer loop handles one single connection with the CDA server per loop cycle
   // I.e. if the connection is lost/broken then we start another loop cycle
   while( !m_TerminateThread )
   {
      BRIDGE_APP_LOG( "Thread [" << THREAD_ID << "] " << " is entering the loop", AIS_LOG_DEBUG, false );

      FileTransferBridgeAppCda::RxStreamAttributesSft_s streamAttributesSft( m_ServicedFileTypes, m_ServicedDestinationNodes );
      SetThreadClientContext( &streamAttributesSft.clientContext );

      // Block the thread, waiting for a connection with CDA/SFT server
      WaitToBeUnblocked();

      // Register with the CDA server for the file types that we're interested in
      if ( !m_TerminateThread && m_spCDAClient->IsConnActive( ALL_SFT_NODES ) &&
           m_spCDAClient->RegisterForFileType( streamAttributesSft ) )
      {
         std::string fileContainer;
         CdaFileType_t fileTypeContainer;
         CdaNode_t fileSourceContainer;
         CdaNode_t fileDestinationContainer;

         // This inner loop handles each received file: one loop cycle = one file received
         while ( !m_TerminateThread && m_spCDAClient->ReceiveDataFile( m_TerminateThread,
               streamAttributesSft,
               m_MapFileTypesToProperties,
               fileContainer,
               fileTypeContainer,
               fileSourceContainer,
               fileDestinationContainer,
               &TriggerCallback ) )
         {
            const CdaFileSize_t fileSize = fileContainer.size();
            if( fileSize > m_MaxSizeOfFile )
            {
               BRIDGE_APP_LOG( "File received by CDA/SFT thread " << THREAD_ID << " is larger than max ("
                     << fileSize << " > " << m_MaxSizeOfFile << ") and is therefore ignored", AIS_LOG_WARN, true );
            }
            else
            {
               ProcessReceivedFile( fileContainer, fileSize, fileTypeContainer, "", fileSourceContainer, fileDestinationContainer );
            }
         }

         // Check if the main thread requested a shutdown
         if( !m_TerminateThread )
         {
            // Main thread didn't request shutdown. We must have lost the connection with the CDA server
            std::unique_lock<std::mutex> scopeLock( m_LockPendingConnection );
            m_PendingConnection = true;
            m_spCDAClient->SetConnInactive( ALL_SFT_NODES );
            BRIDGE_APP_LOG( "CDA/SFT RX thread " << THREAD_ID << " got a broken read. Server disconnected?", AIS_LOG_ALERT, true );
         }
      }

      // Reset the context pointer
      SetThreadClientContext( nullptr );

      if (!m_TerminateThread) {
          // Give me a break here... stop the while(true); loop
          std::this_thread::sleep_for(std::chrono::milliseconds(500));
      }
   }

   BRIDGE_APP_LOG( "CDA/SFT RX thread " << THREAD_ID << " is ending", AIS_LOG_NOTICE, false );
   m_ThreadActive = false;
   m_rxThreadState = THREAD_STOPPED;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadRx::TriggerCallback
// Description     : Callback function that is invoked when we receive a
//                   Report Trigger from the CDA Server. Sends appropriate
//                   SCS message to VP3 creator app
// Return Type     : bool - 'true' if trigger was generated, 'false' otherwise
// Argument [in]   : const FileTransferBridgeAppCda::Trigger_t& triggerProperties -
//                      Properties of the trigger
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeAppThreadRx::TriggerCallback( const FileTransferBridgeAppCda::Trigger_t& triggerProperties )
{
   bool triggered = false;
   if ( m_pScsObjectCommand )
   {
      CreateFileRequest triggerRequest;
      triggered = true;
      triggerRequest.fileNumber = static_cast<decltype( triggerRequest.fileNumber )>( triggerProperties.triggerFileType );
      triggerRequest.messageId = static_cast<decltype( triggerRequest.messageId )>( triggerProperties.message_id );
      switch( triggerProperties.triggerSource )
      {
         case 79:
         {
            triggerRequest.Requester = std::string( "WebPage at FID " ) + std::to_string( triggerProperties.sourceNodeFid );
            break;
         }
         case 80:
         {
            triggerRequest.Requester = std::string( "CommunicatorScheduler at FID " ) + std::to_string( triggerProperties.sourceNodeFid );
            break;
         }
         case 81:
         {
            triggerRequest.Requester = std::string( "ProductLinkScheduler at FID " ) + std::to_string( triggerProperties.sourceNodeFid );
            break;
         }
         case 68:
         {
            triggerRequest.Requester = std::string( "BackOffice at FID " ) + std::to_string( triggerProperties.sourceNodeFid );
            break;
         }
         default:
         {
            triggerRequest.Requester = std::string( "Unknown at FID " ) + std::to_string( triggerProperties.sourceNodeFid );
            break;
         }
      }
      triggerRequest.Command = static_cast<decltype( triggerRequest.Command )>( triggerProperties.triggerCommand );

      std::unique_lock<std::mutex> scopeLock( *m_pLockSCS );
      (void)m_pScsObjectCommand->publish( triggerRequest );

      BRIDGE_APP_LOG( "CDA/SFT RX Thread " << THREAD_ID << " generated Report Trigger from " << triggerRequest.Requester
            << " for file type " << triggerRequest.fileNumber, AIS_LOG_NOTICE, true );
   }

   return triggered;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadRx::ForceStopThread
// Description     : Attempts to force stop the stuck thread (do not use unless really necessary)
//                   Note: currently only works with POSIX threads
// Return Type     : bool - 'true' if thread is still running, 'false' otherwise
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeAppThreadRx::ForceStopThread( void )
{
   bool threadRunning = true;

   if ( IsActive() && ( m_rxThreadState < THREAD_ISSUED_FORCE_STOP ) )
   {
      const std::thread::id threadId = m_spThread->get_id();
      m_rxThreadState = THREAD_ISSUED_FORCE_STOP;

#ifdef _PTHREAD_H
      // Convert to POSIX thread
      pthread_t threadHandle = m_spThread->native_handle();
      m_spThread->detach();

      // Attempt to cancel the POSIX thread
      threadRunning = ( 0 != pthread_cancel( threadHandle ) );
      if ( threadRunning )
      {
         BRIDGE_APP_LOG( "Failed to force stop Rx thread " << threadId, AIS_LOG_EMERG, true );
      }
      else
      {
         BRIDGE_APP_LOG( "Force stopped Rx thread " << threadId, AIS_LOG_ALERT, true );
      }
#else
      m_spThread->detach();

      BRIDGE_APP_LOG( "Unable to force stop Rx thread " << threadId, AIS_LOG_EMERG, true );
#endif
   }

   return threadRunning;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadRx::InterruptThreadListening
// Description     : Attempts to stop the active threads from listening
//                   to incoming messages from the CDA server
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppThreadRx::InterruptThreadListening( void )
{
   if ( IsActive() && ( m_rxThreadState < THREAD_ISSUED_INTERRUPT ) )
   {
      m_rxThreadState = THREAD_ISSUED_INTERRUPT;

      const std::thread::id threadId = m_spThread->get_id();
      std::lock_guard<std::mutex> scopeLock( m_LockpCDAContext );
      if ( nullptr != m_pCDAContext )
      {
         BRIDGE_APP_LOG( "Interrupting Rx thread " << threadId, AIS_LOG_NOTICE, false );
         m_pCDAContext->TryCancel();
      }
   }
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadRx::UnblockThread
// Description     : If the thread was waiting to be connected to CDA Server, then
//                   sets an event lifting the thread block
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppThreadRx::UnblockThread( void )
{
   // Check the connection for a serviced node; an empty list of nodes could only mean that this is a CDA/SFT thread
   if ( ( !m_ServicedSourceNodes.empty() && m_spCDAClient->IsConnActive( m_ServicedSourceNodes.at(0) ) ) ||
        m_spCDAClient->IsConnActive( ALL_SFT_NODES ) ||
        m_TerminateThread ) // We also want to unblock if trying to shut down
   {
      const std::thread::id threadId = m_spThread->get_id();
      BRIDGE_APP_LOG( "Waking up Rx thread " << threadId, AIS_LOG_DEBUG, false );

      std::unique_lock<std::mutex> scopeLock( m_LockPendingConnection );
      m_PendingConnection = false;
      m_EventPendingConnection.notify_all();
   }
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadRx::SetThreadClientContext
// Description     : Assigns (or unassigns) the global pointer to the gRPC
//                   client context. The global pointer is used by the main thead
//                   to break the receive thread out of a blocking wait
// Return Type     : None
// Argument [in]   : grpc::ClientContext* pContext - Pointer to context (or nullptr to reset)
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppThreadRx::SetThreadClientContext( grpc::ClientContext* pContext )
{
   std::unique_lock<std::mutex> scopeLock( m_LockpCDAContext );
   m_pCDAContext = pContext;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadRx::WaitToBeUnblocked
// Description     : Blocks the thread pending connection to CDA Server
//                   (released through UnblockThread by the main thread)
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppThreadRx::WaitToBeUnblocked( void )
{
   std::unique_lock<std::mutex> threadLock( m_LockPendingConnection );
   m_EventPendingConnection.wait( threadLock, [this]{ return !m_PendingConnection; } );
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadRx::ProcessReceivedFile
// Description     : Queues and sends out a new received file
// Return Type     : None
// Argument [in]   : const std::string& fileContents - The contents of the file
//                      encoded into a string,
//                   const CdaFileSize_t& fileSize - File size in bytes,
//                   const CdaFileType_t& fileType - Telematics File Number,
//                   const std::string fileNameSuggested - Optional parameter
//                      with a file name suggested by the CDA server,
//                   const CdaNode_t& sourceFID - Optional Source node FID,
//                   const CdaNode_t& destinationFID - Optional Destination node FID.
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppThreadRx::ProcessReceivedFile( const std::string& fileContents,
      const CdaFileSize_t& fileSize,
      const CdaFileType_t& fileType,
      const std::string fileNameSuggested,
      const CdaNode_t& sourceFID,
      const CdaNode_t& destinationFID )
{
   const auto& q = m_MapFileQueues[fileType];
   if (nullptr == q) {
      return;
   }

   // From the transaction stream set new file attributes
   FileTransferBridgeIndication scsObjectFileInfo;
   FileInfo_t fileAttr;
   scsObjectFileInfo.fileAttr.Name = fileNameSuggested.empty() ? scsObjectFileInfo.GenerateFileName( fileType ).Name : fileNameSuggested ;
   scsObjectFileInfo.fileAttr.TelematicsFileNumber = fileType;
   scsObjectFileInfo.fileAttr.SizeInBytes = fileSize;
   scsObjectFileInfo.fileAttr.FidSource = sourceFID;
   scsObjectFileInfo.fileAttr.FidDestination = destinationFID;
   fileAttr.DirPath = scsObjectFileInfo.fileAttr.DirPath = m_FilesPath;
   fileAttr.Name = scsObjectFileInfo.fileAttr.Name;

   BRIDGE_APP_LOG( "Thread [" << THREAD_ID << "] " << " received file of size " << fileSize << " bytes. (Suggested/used name "
         << fileNameSuggested << " / " << scsObjectFileInfo.fileAttr.Name << "). Total count is " << ++m_InboundFilesCount, AIS_LOG_NOTICE, true );

   // At this point we start operating on the queue of the file type that may be shared across the Rx threads.
   // Prevent the file system chaos by locking the mutex for the duration of this block of code
   std::unique_lock<std::mutex> scopeLock( *m_pLockSCS );
   q->Rebuild();

   // We only queue the file if file is successfully created
   if ( FileTransferBridgeAppUtil::CreateNewFile( fileAttr, fileContents ) )
   {
      (void)FileTransferBridgeAppUtil::GetFileAttributes( scsObjectFileInfo.fileAttr.DirPath, scsObjectFileInfo.fileAttr.Name, sourceFID, destinationFID, fileAttr );

      // Queue the file in the list of received files and publish it over SCS
      if( q->PushFile( fileAttr ) )
      {
         // Send out a beacon to other apps notifying of a new file in the hold area
         m_pScsObjectFile->publish( scsObjectFileInfo );

         BRIDGE_APP_LOG( "Receive thread " << THREAD_ID << " queued and published file " << fileAttr.Name
               << " of type "<< fileAttr.TelematicsFileNumber
               << " and size "<< fileAttr.SizeInBytes, AIS_LOG_NOTICE, true );
      }
      else
      {
         // Log if the queuing of file failed and delete the file
         BRIDGE_APP_LOG( "Receive thread " << THREAD_ID << " failed to queue file " << fileAttr.Name, AIS_LOG_ERROR, true );
      }
   }
   else
   {
      BRIDGE_APP_LOG( "Receive thread " << THREAD_ID << " failed to create file " << fileAttr.Name, AIS_LOG_ERROR, true );
   }
}
