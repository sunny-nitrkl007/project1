////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: FileTransferBridgeAppQueue
//
// File Name: FileTransferBridgeAppQueue.cpp
//
//  Abstract: File queue class implementation
//
////////////////////////////////////////////////////////

#include <algorithm> // Needed for std::find
#include <ais/task/Task.h>

#include "FileTransferBridgeAppLog.h"
#include "FileTransferBridgeAppQueue.h"
#include "FileTransferBridgeAppUtil.h"

using namespace FileTransferBridge;

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppQueue::FileTransferBridgeAppQueue
// Description     : Class constructor
// Return Type     : N/A
// Argument [in]   : CdaFileType_t fileType - Type of file to be serviced by the queue,
//                   CdaFileSize_t maxQueueSize - Maximum storage size for the queue,
//                   CdaFileSize_t maxFileSize - Maximum size of each file in the queue,
//                   const std::string& dataFileDirectory - File storage location
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
FileTransferBridgeAppQueue::FileTransferBridgeAppQueue( const CdaFileType_t fileType,
      const CdaFileSize_t maxQueueSize,
      const CdaFileSize_t maxFileSize,
      const std::string& dataFileDirectory ):
                              m_FileType( fileType ),
                              m_CurrentQueueSizeInBytes( 0 ),
                              m_MaxQueueSizeInBytes( maxQueueSize ),
                              m_MaxDataFileSizeInBytes( maxFileSize ),
                              m_DataFileDirPath( dataFileDirectory )
{
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppQueue::Rebuild
// Description     : Rebuilds the queue from a directory (note: both
//                   the directory and the file type are specified in
//                   the queue constructor)
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppQueue::Rebuild( void )
{
   BRIDGE_APP_LOG( "FileTransferBridgeAppQueue::Initiate", AIS_LOG_DEBUG, false );

   // Obtain the files and their information from the queue's storage directory
   std::vector<FileInfo_t> dataFiles = FileTransferBridgeAppUtil::ReadFilesFromDirectory( m_DataFileDirPath, m_FileType );

   // Lock the queue just in case someone tries to add/remove/read while we're rebuilding and reset it
   {
      std::lock_guard<std::mutex> scopeLock( m_Lock_Queue );
      std::vector<FileInfo_t>().swap( m_FileInfoQueue ); // Swap with empty vector
      m_CurrentQueueSizeInBytes = m_FileInfoQueue.size();
   }

   if ( !dataFiles.empty() )
   {
      for (const auto& fInfo : dataFiles)
      {
         (void)PushFile( fInfo );
      }

      BRIDGE_APP_LOG( "RebuildQueue obtained " << dataFiles.size() << " files of type " << m_FileType << " from "
            << m_DataFileDirPath << ". Queued " << m_FileInfoQueue.size(), AIS_LOG_NOTICE, true);
   }
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppQueue::PushFile
// Description     : Pushes the file into this queue
// Return Type     : bool - 'true' if file was queued successfully, 'false' otherwise
// Argument [in]   : const FileInfo_t& fileInfo - File to be queued
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeAppQueue::PushFile( const FileInfo_t& fileInfo )
{
   bool returned_val = false;

   // Check if this file already exists in the queue
   if ( m_FileInfoQueue.end()  != std::find_if( m_FileInfoQueue.begin(), m_FileInfoQueue.end(),
         [&fileInfo] ( const FileInfo_t& vectorElement ) { return vectorElement.Name == fileInfo.Name; } ) )
   {
      BRIDGE_APP_LOG( "File " << fileInfo.Name << " already exists in the queue. Skipping...", AIS_LOG_ALERT, true );
      return true;
   }

   // Validate file attributes
   returned_val = FileAttrValid( fileInfo );
   if ( false == returned_val )
   {
      // Validation fails
      BRIDGE_APP_LOG( "Invalid attribute for file " << fileInfo.Name << ". Deleting...", AIS_LOG_ERROR, true );
      std::string fullPath = fileInfo.DirPath + fileInfo.Name;
      if ( !FileTransferBridgeAppUtil::DeleteFile( fullPath ) )
      {
         BRIDGE_APP_LOG("DelFile failed for " << fullPath, AIS_LOG_ERROR, false);
      }
      else
      {
         BRIDGE_APP_LOG("DelFile successful for " << fullPath, AIS_LOG_DEBUG, false);
      }
      return returned_val;
   }

   // Check if the file is too large for the queue
   if ( fileInfo.SizeInBytes > m_MaxQueueSizeInBytes )
   {
      // Validation fails
      BRIDGE_APP_LOG( "Cannot queue " << fileInfo.Name << " of size " << fileInfo.SizeInBytes
            << " since it's too big for its queue of size " << m_MaxQueueSizeInBytes
            << ". Deleting...", AIS_LOG_ERROR, true );
      std::string fullPath = fileInfo.DirPath + fileInfo.Name;
      if (!FileTransferBridgeAppUtil::DeleteFile(fullPath))
      {
         BRIDGE_APP_LOG("DelFile failed for " << fullPath, AIS_LOG_ERROR, false);
      }
      else
      {
         BRIDGE_APP_LOG("DelFile successful for " << fullPath, AIS_LOG_DEBUG, false);
      }
      return false;
   }
   else
   {
      // Check if file size is too large for the remaining space of the queue. Attempt to free up space in the file system by deleting old files.
      bool dequeued = true;
      while ( ( ( m_CurrentQueueSizeInBytes + fileInfo.SizeInBytes ) > m_MaxQueueSizeInBytes ) && ( dequeued ) )
      {
         FileInfo_t oldestInQueue;
         if ( GetFile( oldestInQueue ) )
         {
            dequeued = PopFile( oldestInQueue );
            BRIDGE_APP_LOG( "Bridge queue too large, delete oldest file " << oldestInQueue.Name, AIS_LOG_WARN, true );
         }
      }

      if ( ( m_CurrentQueueSizeInBytes + fileInfo.SizeInBytes ) <= m_MaxQueueSizeInBytes )
      {
         std::lock_guard<std::mutex> scopeLock( m_Lock_Queue );

         m_FileInfoQueue.push_back ( fileInfo );
         m_CurrentQueueSizeInBytes += fileInfo.SizeInBytes;

         BRIDGE_APP_LOG( "Queued " << fileInfo.Name << ", queue size is " << m_FileInfoQueue.size()
               << " Current size in byte: "<< m_CurrentQueueSizeInBytes, AIS_LOG_INFO, false );
         returned_val = true;
      }
      else
      {
         BRIDGE_APP_LOG( "Failed to free the queue for the file " << fileInfo.Name, AIS_LOG_WARN, true );
         (void)FileTransferBridgeAppUtil::DeleteFile( fileInfo.DirPath + fileInfo.Name );
         returned_val = false;
      }
   }

   return returned_val;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppQueue::FileAttrValid
// Description     : Checks the validity of a file to be transferred to the CDA server
// Return Type     : bool - 'true' if the file is valid, 'false' otherwise
// Argument [in]   : const FileInfo_t& fileInfo - File information
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeAppQueue::FileAttrValid( const FileInfo_t& fileInfo )
{
   bool returned_val = false;

   if ( fileInfo.Name.empty() )
   {
      BRIDGE_APP_LOG( "FileAttrValid: Invalid file name", AIS_LOG_ERROR, false );
   }
   else if ( fileInfo.SizeInBytes < 1 )
   {
      BRIDGE_APP_LOG( "FileAttrValid: File too small  " << fileInfo.Name, AIS_LOG_ERROR, false );
   }
   else if ( fileInfo.SizeInBytes > m_MaxDataFileSizeInBytes )
   {
      BRIDGE_APP_LOG( "FileAttrValid: File size is too large  " << fileInfo.Name, AIS_LOG_ERROR, false );
   }
   else if ( fileInfo.SizeInBytes > m_MaxQueueSizeInBytes )
   {
      BRIDGE_APP_LOG( "FileAttrValid: File size is larger than the queue  " << fileInfo.Name, AIS_LOG_ERROR, false );
   }
   else
   {
      // Everything is OK
      returned_val = true;
   }

   return returned_val;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppQueue::GetFile
// Description     : Gets the information on the next file in the queue
// Return Type     : bool - 'true' if there is a file on a queue and
//                   it has been obtained, otherwise 'false'
// Argument [in]   : None
// Argument [out]  : FileInfo_t& queueEntry - Structure that contains the file information
//                   if the queue is not empty
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeAppQueue::GetFile( FileInfo_t& queueEntry )
{
   bool entryObtained = false;
   std::lock_guard<std::mutex> scopeLock( m_Lock_Queue );

   if ( !m_FileInfoQueue.empty() )
   {
      queueEntry = m_FileInfoQueue.front();
      entryObtained = true;
   }

   return entryObtained;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppQueue::PopFile
// Description     : Removes the queued file with the specified info and
//                   returns the status of the operation
// Return Type     : bool - 'true' if popped successfully, 'false' otherwise
// Argument [in]   : const FileInfo_t& fileInfo - File to be removed
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeAppQueue::PopFile( const FileInfo_t& fileInfo )
{
   bool returnValue = false;
   std::lock_guard<std::mutex> scopeLock( m_Lock_Queue );

   if ( !m_FileInfoQueue.empty() )
   {
      std::string fullPath = fileInfo.DirPath + fileInfo.Name;
      if ( !FileTransferBridgeAppUtil::DeleteFile( fullPath ) )
      {
         BRIDGE_APP_LOG("DelFile failed for " << fullPath, AIS_LOG_ERROR, false);
      }
      else
      {
         BRIDGE_APP_LOG("DelFile successful for " << fullPath, AIS_LOG_DEBUG, false);
      }

      auto position = std::find( m_FileInfoQueue.begin(), m_FileInfoQueue.end(), fileInfo );
      if ( position != m_FileInfoQueue.end() )
      {
         m_FileInfoQueue.erase( position );
         m_CurrentQueueSizeInBytes -= fileInfo.SizeInBytes;
         BRIDGE_APP_LOG( "Removed " << fullPath << " from the file queue. Queue size is " << m_FileInfoQueue.size(), AIS_LOG_DEBUG, false);
         returnValue = true;
      }
      else
      {
         BRIDGE_APP_LOG( "Failed to remove " << fullPath << " from the file queue: entry not found", AIS_LOG_ERROR, true);
      }
   }

   return returnValue;
}
