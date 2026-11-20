////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: FileTransferBridgeAppThreadTx
//
// File Name: FileTransferBridgeAppThreadTx.h
//
//  Abstract: This file is a class declaration for a thread
//            that is transmitting files to CDA Server
//
////////////////////////////////////////////////////////

#ifndef SCSCDATTIBRIDGETX_H
#define SCSCDATTIBRIDGETX_H

#include <memory>             // Needed for shared_ptr
#include <mutex>              // Needed for std::mutex
#include <thread>             // Needed for std::thread
#include <condition_variable> // Needed for std::condition_variable
#include <map>                // Needed for std::map
#include <interfaces/FileTransferBridgeResponse/InterfaceTypes.h>
#include "FileTransferBridgeAppDef.h"        // FileTransferBridge namespace and types
#include "FileTransferBridgeAppCda.h"        // CDA Client routines
#include "FileTransferBridgeAppQueue.h"      // Queue implementation

class FileTransferBridgeAppThreadTx
{
public:
   FileTransferBridgeAppThreadTx( const FileTransferBridge::FileTransferBridgeAppCfg_t&, std::shared_ptr<FileTransferBridgeAppCda> );
   ~FileTransferBridgeAppThreadTx( );

   inline void StopThread( void ) { m_TerminateThread = true; UnblockThread(); }
   void UnblockThread( void );

   ScsCdaTtiBridgeRet_t TryToQueue( const FileTransferBridge::FileInfo_t& );
   void CheckForFilesToQueue( void );

private:
   void ThreadImplementation( void );
   void WaitToBeUnblocked( void );

   std::unique_ptr<std::thread>                                                                 m_spThread;
   bool                                                                                         m_TerminateThread;
   std::map< FileTransferBridge::CdaFileType_t, std::unique_ptr<FileTransferBridgeAppQueue> >   m_MapFileQueues;
   std::map<FileTransferBridge::CdaFileType_t, FileTransferBridge::CdaFileProperties_t>         m_MapFileTypes;
   std::shared_ptr<FileTransferBridgeAppCda>                                                    m_spCDAClient;
   unsigned_32                                                                                  m_OutgoingFilesCount;
   const FileTransferBridge::CdaNode_t                                                          m_ThisAppFID;

   // Semaphore members for the main thread
   bool                          m_AllowTransfer;
   std::condition_variable       m_EventAllowTransfer;
   std::mutex                    m_LockAllowTransfer;
};

#endif // SCSCDATTIBRIDGETX_H
