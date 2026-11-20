////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: FileTransferBridgeApp
//
// File Name: FileTransferBridgeApp.h
//
//  Abstract: CDA File Transfer Bridge application main class
//            definitions.
//
////////////////////////////////////////////////////////

#ifndef SCSCDATTIBRIDGE_H
#define SCSCDATTIBRIDGE_H

#include <vector>    // Needed for std::vector
#include <memory>    // Needed for std::unique_ptr
#include <mutex>     // Needed for std::mutex
#include <ais/task/Task.h>
#include <interfaces/FileTransferBridgeRequest/InterfaceTypes.h>
#include <interfaces/FileTransferBridgeResponse/InterfaceTypes.h>
#include <interfaces/FileTransferBridgeIndication/InterfaceTypes.h>

#include <interfaces/CreateFileRequest/InterfaceTypes.h>
#include <interfaces/AppReg/InterfaceTypes.h>

#include "FileTransferBridgeAppQueue.h"
#include "FileTransferBridgeAppCfg.h"
#include "FileTransferBridgeAppDef.h"
#include "FileTransferBridgeAppCda.h"
#include "FileTransferBridgeAppThreadRx.h"
#include "FileTransferBridgeAppThreadTx.h"
#include "CdaIoTHubComms.h"

class FileTransferBridgeApp: public task::Task
{
public:
   FileTransferBridgeApp( const std::string& taskName );
   virtual ~FileTransferBridgeApp( ) { }

   virtual bool initialize( );
   virtual bool executive( );
   virtual void cleanup( );

private:
   std::unique_ptr<FileTransferBridgeAppThreadTx>                    m_spTransmitThread;
   std::vector< std::unique_ptr<FileTransferBridgeAppThreadRx> >     m_spReceiveThreads;
   std::mutex                                                        m_LockScsForReceiveThreads;

   // Class objects for the app configuration and CDA client handler
   FileTransferBridgeAppCfg                                          m_CfgObject;
   bool                                                              m_AppInitialized;
   bool                                                              m_ShutdownInProgress;
   std::shared_ptr<FileTransferBridgeAppCda>                         m_spCdaClient;
   std::shared_ptr<grpc::ChannelInterface>                           m_spCurrentChannel;
   CdaIoTHubComms                                                    m_iotHubComms;

   // SCS objects
   FileTransferBridgeRequestInput*                                   m_pFileTransferBridgeAppReqInput;
   FileTransferBridgeResponseOutput*                                 m_pFileTransferBridgeAppRespOutput;
   FileTransferBridgeIndicationOutput*                               m_pFileTransferBridgeAppRecvFileOutput;
   CreateFileRequestOutput*                                          m_pFileTransferBridgeAppCreateReqOutput;
   AppRegInput*                                                      m_pAppRegInput;
   AppRegOutput*                                                     m_pAppRegOutput;
   AppReg                                                            m_AppReg;

   bool InitInterfaces( void );
   void InitRxThreads( const FileTransferBridge::FileTransferBridgeAppCfg_t& );
   void InitTxThread( const FileTransferBridge::FileTransferBridgeAppCfg_t& );
   void ExecProcessTxRequest( const FileTransferBridgeRequest& );
   bool CleanCheckRxThreads( const int32_t& );
   void ExecUpdateAppRegState( void );

   void GetCDAParameterInfoGroup(void);
   void GetCDAParameterDataGroup(void);
};

#endif //SCSCDATTIBRIDGE_H
