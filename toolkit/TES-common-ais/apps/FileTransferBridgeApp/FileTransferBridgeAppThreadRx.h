////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: FileTransferBridgeAppThreadRx
//
// File Name: FileTransferBridgeAppThreadRx.h
//
//  Abstract: This file is a class declaration for threads
//            receiving files from CDA Server
//
////////////////////////////////////////////////////////

#ifndef SCSCDATTIBRIDGERX_H
#define SCSCDATTIBRIDGERX_H

#include <memory>             // Needed for std::unique_ptr, std::shared_ptr
#include <mutex>              // Needed for std::mutex
#include <thread>             // Needed for std::thread
#include <condition_variable> // Needed for std::condition_variable
#include <string>             // Needed for std::string
#include <interfaces/FileTransferBridgeIndication/InterfaceTypes.h>
#include <interfaces/CreateFileRequest/InterfaceTypes.h>
#include "FileTransferBridgeAppDef.h"        // FileTransferBridge namespace and types
#include "FileTransferBridgeAppCda.h"        // CDA Client routines
#include "FileTransferBridgeAppQueue.h"      // Queue implementation

class FileTransferBridgeAppThreadRx
{
public:
   // ============================= CDA/TTI public class members =============================
   FileTransferBridgeAppThreadRx( const FileTransferBridge::CdaNode_t& sourceNodeServiced,
         const std::vector<FileTransferBridge::CdaFileType_t>& fileTypes,
         const FileTransferBridge::FileTransferBridgeAppCfg_t& configTable,
         std::shared_ptr<FileTransferBridgeAppCda> pCDAClient,
         FileTransferBridgeIndicationOutput* pScsObjectFile,
         std::mutex& scsMutexLock );

   // ============================= CDA/SFT public class members =============================
   FileTransferBridgeAppThreadRx( const FileTransferBridge::FileTransferBridgeAppCfg_t& configTable,
         std::shared_ptr<FileTransferBridgeAppCda> pCDAClient,
         FileTransferBridgeIndicationOutput* pScsObjectFile,
         CreateFileRequestOutput* pScsObjectCommand,
         std::mutex& scsMutexLock );

   // ============================= Common public class members =============================
   ~FileTransferBridgeAppThreadRx( );
   inline void StopThread( void ) {
       m_TerminateThread = true;

       // If there are any pending/blocking ReceiveDataFile calls, interrupt it.
       if (nullptr != m_pCDAContext) {
           m_pCDAContext->TryCancel();
       }

       UnblockThread();
   }
   inline bool IsActive( void ) { return m_ThreadActive; }
   bool ForceStopThread( void );
   void InterruptThreadListening( void );
   void UnblockThread( void );

private:
   // ============================= CDA/TTI private class members =============================
   void ThreadImplementationTti( void );

   // ============================= CDA/SFT private class members =============================
   void ThreadImplementationSft( void );
   static bool TriggerCallback( const FileTransferBridgeAppCda::Trigger_t& triggerProperties );

   const std::map<FileTransferBridge::CdaFileType_t, FileTransferBridge::CdaFileProperties_t>   m_MapFileTypesToProperties;
   FileTransferBridge::CdaNodeList_t                                                            m_ServicedDestinationNodes;
   FileTransferBridge::CdaNodeList_t                                                            m_ServicedTriggerNodes;

   // ============================= Common private class members =============================
   void SetThreadClientContext( grpc::ClientContext* pContext );
   void WaitToBeUnblocked( void );
   void ProcessReceivedFile( const std::string& fileContents,
         const FileTransferBridge::CdaFileSize_t& fileSize,
         const FileTransferBridge::CdaFileType_t& fileType,
         const std::string fileNameSuggested,
         const FileTransferBridge::CdaNode_t& sourceFID = 0,
         const FileTransferBridge::CdaNode_t& destinationFID = 0 );

   FileTransferBridge::CdaNodeList_t                                                            m_ServicedSourceNodes;
   std::vector<FileTransferBridge::CdaFileType_t>                                               m_ServicedFileTypes;
   std::map< FileTransferBridge::CdaFileType_t, std::unique_ptr<FileTransferBridgeAppQueue> >   m_MapFileQueues;
   const std::string                                                                            m_FilesPath;
   const FileTransferBridge::CdaFileSize_t                                                      m_MaxSizeOfFile;
   std::unique_ptr<std::thread>                                                                 m_spThread;
   volatile bool                                                                                m_TerminateThread;
   volatile bool                                                                                m_ThreadActive;
   volatile bool                                                                                m_PendingConnection;
   std::shared_ptr<FileTransferBridgeAppCda>                                                    m_spCDAClient;
   std::condition_variable                                                                      m_EventPendingConnection;
   std::mutex                                                                                   m_LockPendingConnection;
   grpc::ClientContext*                                                                         m_pCDAContext;
   std::mutex                                                                                   m_LockpCDAContext;
   static std::mutex*                                                                           m_pLockSCS;
   FileTransferBridgeIndicationOutput* const                                                    m_pScsObjectFile;
   static CreateFileRequestOutput*                                                              m_pScsObjectCommand;
   unsigned_32                                                                                  m_InboundFilesCount;
   enum RxThreadsState_e
   {
      THREAD_RUNNING = 0,
      THREAD_COMMANDED_TO_STOP,
      THREAD_ISSUED_INTERRUPT,
      THREAD_ISSUED_FORCE_STOP,
      THREAD_STOPPED,
      THREAD_NOT_INITIALIZED
   }                                                                                            m_rxThreadState;
};

#endif // SCSCDATTIBRIDGERX_H
