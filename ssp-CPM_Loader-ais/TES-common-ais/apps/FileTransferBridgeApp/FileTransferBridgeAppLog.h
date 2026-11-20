////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: FileTransferBridgeAppLog
//
// File Name: FileTransferBridgeAppLog.h
//
//  Abstract: Declarations for the Bridge
//            application logging functionality.
//
////////////////////////////////////////////////////////

#ifndef SCSCDATTIBRIDGELOG_H
#define SCSCDATTIBRIDGELOG_H

#include <string> // std::string
#include <ais/log/AisLogger.h>

#include "FileTransferBridgeAppDef.h"

#define LOG_TO_FILE(trueFalse) LOG_TO_FILE_##trueFalse
#define LOG_TO_FILE_true FileTransferBridgeAppLog::GetInst()->LogMsg( logMsg.str() )
#define LOG_TO_FILE_false

// Define a callback API to add a log entry
// Usage:
//    BRIDGE_APP_LOG(<message stream>, <log priority>, <write to file>)
// e.g.:
//    BRIDGE_APP_LOG("Some simple debug message written to file", AIS_LOG_DEBUG, true);
//    BRIDGE_APP_LOG("Some complex error message with an integer without writing to file: " << someInteger, AIS_LOG_ERROR, false);
#define BRIDGE_APP_LOG(msgStream, msgType, fileFlag) {                                             \
      std::stringstream logMsg;                                                                    \
      logMsg << msgStream;                                                                         \
      msgType( logMsg.str().c_str() );                                                             \
      LOG_TO_FILE(fileFlag);                                                                       \
}

class FileTransferBridgeAppLog
{
public:
   static FileTransferBridgeAppLog* GetInst( );
   void Init( const FileTransferBridge::FileTransferBridgeAppCfg_t& cfg );
   void LogMsg( const std::string& message );

protected:

private:
   FileTransferBridgeAppLog(): logInit( false ) { };

   int AppLogId;
   bool logInit;
};

#endif // SCSCDATTIBRIDGELOG_H
