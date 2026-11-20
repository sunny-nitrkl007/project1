////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: FileTransferBridgeAppQueue
//
// File Name: FileTransferBridgeAppQueue.h
//
//  Abstract: File queue class declarations
//
////////////////////////////////////////////////////////

#ifndef SCSCDATTIBRIDGEQUEUE_H
#define SCSCDATTIBRIDGEQUEUE_H

#include <vector>    // Needed for std::vector
#include <string>    // Needed for std::string
#include <mutex>     // Needed for std::mutex
#include "FileTransferBridgeAppDef.h"

class FileTransferBridgeAppQueue
{
public:
   //methods
   FileTransferBridgeAppQueue( const FileTransferBridge::CdaFileType_t fileType,
         const FileTransferBridge::CdaFileSize_t maxQueueSize,
         const FileTransferBridge::CdaFileSize_t maxFileSize,
         const std::string& dataFileDirectory );
   ~FileTransferBridgeAppQueue( ) { }

   void     Rebuild( void );
   bool     PushFile( const FileTransferBridge::FileInfo_t& fileInfo );
   bool     GetFile( FileTransferBridge::FileInfo_t& queueEntry );
   bool     PopFile( const FileTransferBridge::FileInfo_t& fileInfo );

   inline FileTransferBridge::CdaFileType_t GetFileType( void ) { return m_FileType; }
   bool     FileAttrValid( const FileTransferBridge::FileInfo_t& fileInfo );

private:
   std::vector<FileTransferBridge::FileInfo_t>  m_FileInfoQueue;
   std::mutex                                   m_Lock_Queue;

   const FileTransferBridge::CdaFileType_t      m_FileType;
   FileTransferBridge::CdaFileSize_t            m_CurrentQueueSizeInBytes;
   const FileTransferBridge::CdaFileSize_t      m_MaxQueueSizeInBytes;
   const FileTransferBridge::CdaFileSize_t      m_MaxDataFileSizeInBytes;
   const std::string                            m_DataFileDirPath;
};

#endif // SCSCDATTIBRIDGEQUEUE_H
