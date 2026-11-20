////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: FileTransferBridgeAppThreadTx
//
// File Name: FileTransferBridgeAppThreadTx.cpp
//
//  Abstract: This file is a class implementation for a thread
//            that is transmitting files to CDA Server
//
////////////////////////////////////////////////////////

#include "FileTransferBridgeAppThreadTx.h"

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <dirent.h>

#include "FileTransferBridgeAppLog.h"
#include "FileTransferBridgeAppUtil.h"

using namespace FileTransferBridge;

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadTx::FileTransferBridgeAppThreadTx
// Description     : Class constructor
// Return Type     : N/A
// Argument [in]   : const FileTransferBridgeAppCfg_t& configTable -
//                   Application configuration table
// Argument [out]  : None
// Argument [I/O]  : FileTransferBridgeAppCda* pCDAClient - Pointer to the
//                   instance of CDA Client
////////////////////////////////////////////////////////////////////////////
FileTransferBridgeAppThreadTx::FileTransferBridgeAppThreadTx( const FileTransferBridgeAppCfg_t& configTable,
      std::shared_ptr<FileTransferBridgeAppCda> pCDAClient ):
            m_TerminateThread( false ),
            m_MapFileTypes( configTable.MapFileTypes ),
            m_spCDAClient( pCDAClient ),
            m_OutgoingFilesCount( 0 ),
            m_ThisAppFID( configTable.DefaultSourceFID ),
            m_AllowTransfer( false )
{
   // Create and rebuild all necessary queues
   for (const auto& fileTypeToProperties : configTable.MapFileTypes)
   {
      m_MapFileQueues[fileTypeToProperties.first].reset( new FileTransferBridgeAppQueue( fileTypeToProperties.first,
            fileTypeToProperties.second.TxQueueSize,
            configTable.MaxDataFileSizeInBytes,
            configTable.DataFileStoreDirPath ) );
   }

   /*
    * To build the Tx queues for the first time, we also want to delete files that are not supported.
    * If we do not delete the files that are not supported, they could accumulate without bound.
    */
   {
      struct dirent* pDirEntry;
      std::vector<FileInfo_t> files;
      DIR* pDirHandle = opendir(configTable.DataFileStoreDirPath.c_str());

      if (nullptr == pDirHandle) {
         BRIDGE_APP_LOG("Error (" << errno << ") opening " << configTable.DataFileStoreDirPath, AIS_LOG_ERROR, false);
      }
      else {
         // Read files one by one
         while (nullptr != (pDirEntry = readdir(pDirHandle))) {
            FileInfo_t fileInfo;
            std::string fileName(pDirEntry->d_name);

            if ((DT_REG == pDirEntry->d_type) || (DT_LNK == pDirEntry->d_type)) {
               // Only look at regular files and symbolic links
               if (FileTransferBridgeAppUtil::GetFileAttributes(configTable.DataFileStoreDirPath, fileName, 0, 0, fileInfo)) {
                  if (configTable.MapFileTypes.count(fileInfo.TelematicsFileNumber) > 0) {
                     // This is a supported file type
                     files.push_back(fileInfo);
                  }
                  else {
                     // This is not a supported file type... remove it.
                     BRIDGE_APP_LOG("Deleting unsupported file " << fileName, AIS_LOG_WARN, false);
                     FileTransferBridgeAppUtil::DeleteFile(configTable.DataFileStoreDirPath + fileName);
                  }
               }
               else {
                  // It is in our queue directory and we don't now how to deal with it... remove it.
                  BRIDGE_APP_LOG("Deleting broken file or link " << fileName, AIS_LOG_WARN, false);
                  FileTransferBridgeAppUtil::DeleteFile(configTable.DataFileStoreDirPath + fileName);
               }
            }
         }

         closedir(pDirHandle);

         // Sort the list of the files by the file modification time (specified in the definition of FileInfo_t by an overloaded operator)
         std::sort(files.begin(), files.end());
      }

      int filesQueued = 0;

      // Loop through files and push them into queues
      for (const auto& fInfo : files) {
         const auto& q = m_MapFileQueues[fInfo.TelematicsFileNumber];
         if (nullptr != q) {
             if (q->PushFile(fInfo)) {
                ++filesQueued;
             }
         }
      }

      BRIDGE_APP_LOG("RebuildQueue obtained " << files.size() << " files from "
            << configTable.DataFileStoreDirPath << " and queued " << filesQueued, AIS_LOG_NOTICE, true);
   }

   // Create and start the thread
   BRIDGE_APP_LOG( "Starting CDA/TTI and CDA/SFT TX thread for all file types and their default CDA nodes:", AIS_LOG_NOTICE, true );
   for (const auto& fileType : m_MapFileTypes)
   {
      std::stringstream fileTypesAndNodes;
      fileTypesAndNodes << "    " << fileType.first << ": ";
      for ( CdaNodeList_t::size_type iter = 0; iter < fileType.second.CdaDefaultDestinationNodes.size(); iter++ )
      {
         if ( iter > 0 )
         {
            fileTypesAndNodes << ", ";
         }
         fileTypesAndNodes << fileType.second.CdaDefaultDestinationNodes.at( iter );
      }
      BRIDGE_APP_LOG( fileTypesAndNodes.str(), AIS_LOG_NOTICE, true );
   }
   m_spThread.reset( new std::thread( [this] { ThreadImplementation(); } ) );
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadTx::~FileTransferBridgeAppThreadTx
// Description     : Class destructor that joins with main thread with Tx thread
// Return Type     : N/A
// Argument [in]   : N/A
// Argument [out]  : N/A
// Argument [I/O]  : N/A
////////////////////////////////////////////////////////////////////////////
FileTransferBridgeAppThreadTx::~FileTransferBridgeAppThreadTx()
{
   BRIDGE_APP_LOG( "Joining Tx thread with the main thread", AIS_LOG_DEBUG, false );
   if ( m_spThread->joinable() )
   {
      m_spThread->join();
   }
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadTx::ThreadImplementation
// Description     : Implementation of a TX thread
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppThreadTx::ThreadImplementation(void) {

    while(!m_TerminateThread) {

        BRIDGE_APP_LOG("Tx thread [" << THREAD_ID << "] is entering the loop", AIS_LOG_DEBUG, false);

        WaitToBeUnblocked();

        // Check if we're ok to start sending
        if (!m_TerminateThread) {

            // Go through each queue
            for (const auto& fileTypeToQueue : m_MapFileQueues) {
                const auto& q = fileTypeToQueue.second;
                if (nullptr == q) {
                    continue;
                }

                bool skipThisQueue = false;

                const CdaFileType_t fileType = q->GetFileType();

                FileInfo_t fileToTransfer;
                while ((!skipThisQueue) && (q->GetFile(fileToTransfer))) {

                    std::string fileContents;

                    if (FileTransferBridgeAppUtil::ReadFile(fileToTransfer, fileContents)) {
                        // Find the CDA/TTI nodes that the associated file type is going to
                        const CdaNodeList_t nodes = m_MapFileTypes.at(fileType).CdaDefaultDestinationNodes;

                        using ReturnCode = FileTransferBridgeAppCda::SendDataFileReturnCode;

                        // Send to all associated nodes
                        ReturnCode returnCode = m_spCDAClient->SendDataFile(fileToTransfer, fileContents, nodes, m_ThisAppFID);

                        switch (returnCode) {

                        case (ReturnCode::OK): {
                            // Remove the file from the queue
                            (void)q->PopFile(fileToTransfer);
                            BRIDGE_APP_LOG("Successfully staged " << fileToTransfer.Name << " for transfer", AIS_LOG_NOTICE, false);
                            break;
                        }

                        case (ReturnCode::SERVICE_ERROR): {
                            // The service is currently down.  No problem, just try again later.
                            skipThisQueue = true;
                            break;
                        }

                        case (ReturnCode::FILE_TYPE_NOT_SUPPORTED): {
                            // This file type is not supported at this time, we lose it.
                            // We will not indefinitely queue files until the file is supported.
                            // If it is not supported, it will not be sent.
                            (void)q->PopFile(fileToTransfer);
                            skipThisQueue = true;
                            BRIDGE_APP_LOG("Failed to stage " << fileToTransfer.Name << " for transfer, file type not supported", AIS_LOG_NOTICE, false);
                            break;
                        }

                        case (ReturnCode::BAD_FILE): {
                            // This file is bad, and won't be better the next time we try, so don't try this file again.
                            (void)q->PopFile(fileToTransfer);
                            BRIDGE_APP_LOG("Failed to stage " << fileToTransfer.Name << " for transfer, bad file", AIS_LOG_ERROR, false);
                            break;
                        }

                        case (ReturnCode::MULTIPLE_ERRORS):
                        default: {
                            // Multiple differing errors, or an unknown condition
                            // It is not clear what to do in this scenario since we do not have
                            //  the error code from each destination node separately.
                            (void)q->PopFile(fileToTransfer);
                            BRIDGE_APP_LOG("Failed to stage " << fileToTransfer.Name << " for transfer, multiple errors", AIS_LOG_ERROR, false);
                            break;
                        }
                        }
                    }
                    else {
                        // Failed to read the file, delete it
                        q->PopFile(fileToTransfer);
                        BRIDGE_APP_LOG("Failed to read " << fileToTransfer.Name << " of size " << fileContents.size() << "/" << fileToTransfer.SizeInBytes, AIS_LOG_WARN, false);
                    }
                }
            }
        }
    }

    BRIDGE_APP_LOG("Transmit thread " << THREAD_ID << " is ending", AIS_LOG_NOTICE, false);
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadTx::UnblockThread
// Description     : Allows Tx thread to send files; this is meant to
//                   be invoked every executive() cycle
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppThreadTx::UnblockThread( void )
{
   std::unique_lock<std::mutex> scopeLock( m_LockAllowTransfer );
   m_AllowTransfer = true;
   m_EventAllowTransfer.notify_all();
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadTx::TryToQueue
// Description     : Attempts to queue the file to be transferred to CDA server
// Return Type     : ScsCdaTtiBridgeRet_t - response to the client of this application
// Argument [in]   : const FileInfo_t& fileInfo - File to be transferred
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
ScsCdaTtiBridgeRet_t FileTransferBridgeAppThreadTx::TryToQueue( const FileInfo_t& fileInfo )
{
   ScsCdaTtiBridgeRet_t ret_val;

   try {
       const auto& q = m_MapFileQueues.at(fileInfo.TelematicsFileNumber);

       if (nullptr == q) {
           ret_val = SCS_CDA_TTI_BRIDGE_FILE_TYPE_NOT_SUPPORTED;
       }
       // Double check if the file fits inside the queue (we've already checked for other conditions)
       else if (!q->FileAttrValid(fileInfo)) {
          ret_val = SCS_CDA_TTI_BRIDGE_FILE_SIZE_LIMIT;
       }
       // All attributes check out. Let's try to queue the file
       else if (!q->PushFile(fileInfo)) {
          ret_val = SCS_CDA_TTI_BRIDGE_FILE_NOT_QUEUED;
       }
       else {
          ret_val = SCS_CDA_TTI_BRIDGE_SUCCESS;
       }
   }
   catch (const std::out_of_range&) {
       // File type not supported
       ret_val = SCS_CDA_TTI_BRIDGE_FILE_TYPE_NOT_SUPPORTED;
   }

   return ret_val;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadTx::CheckForFilesToQueue
// Description     : Checks if there are any files in the file system that
//                   need to be queued for transmission (rebuilds the queue
//                   from the file system)
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppThreadTx::CheckForFilesToQueue(void)
{
    for (const auto& fileTypeToQueue : m_MapFileQueues) {
        const auto& q = fileTypeToQueue.second;
        if (nullptr != q) {
            q->Rebuild();
        }
    }
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppThreadTx::WaitToBeUnblocked
// Description     : Blocks the thread pending the next executive() cycle
//                   (released through UnblockThread by the main thread)
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppThreadTx::WaitToBeUnblocked( void )
{
   if ( !m_TerminateThread )
   {
      std::unique_lock<std::mutex> threadLock( m_LockAllowTransfer );
      m_AllowTransfer = false;
      m_EventAllowTransfer.wait( threadLock, [this]{ return m_AllowTransfer; } );
   }
}
