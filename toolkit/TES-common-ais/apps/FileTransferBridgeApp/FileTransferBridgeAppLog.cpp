////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: FileTransferBridgeAppLog
//
// File Name: FileTransferBridgeAppLog.cpp
//
//  Abstract: Implementation of the Bridge
//            application logging functionality.
//
////////////////////////////////////////////////////////

#include <app_log.h>
#include <sys/stat.h>

#include "FileTransferBridgeAppLog.h"
#include "FileTransferBridgeAppUtil.h"

#define SCS_CDA_TTI_BRIDGE_LOG_MAX_SIZE_BYTES 20000
#define SCS_CDA_TTI_BRIDGE_LOG_MAX_LOGS 4

using namespace FileTransferBridge;

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppLog::GetInst
// Description     : Gets the instance of the log class
// Return Type     : FileTransferBridgeAppLog* - Pointer to the instance
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
FileTransferBridgeAppLog* FileTransferBridgeAppLog::GetInst()
{
   static FileTransferBridgeAppLog instance;

   return &instance;
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppLog::Init
// Description     : Prepares the log file for any follow-up logging
// Return Type     : None
// Argument [in]   : const FileTransferBridgeAppCfg_t& cfg - App configuration table
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppLog::Init( const FileTransferBridgeAppCfg_t& cfg )
{
   app_log_config_t appLogConfig;
   std::string logPath = cfg.FileStatusLogDirPath + "/" + cfg.FileStatusLogName;

   // Check if the log path and the name are correct
   if ( cfg.FileStatusLogDirPath.empty( ) || cfg.FileStatusLogName.empty( ) )
   {
      BRIDGE_APP_LOG( "App log invalid path: " << logPath, AIS_LOG_ERROR, false );
   }
   else
   {
      if ( FileTransferBridgeAppUtil::IsDirectory( cfg.FileStatusLogDirPath ) )
      {
         strncpy( appLogConfig.log_filename, logPath.c_str(), sizeof( appLogConfig.log_filename ) );
         BRIDGE_APP_LOG( "Log file path: " << appLogConfig.log_filename, AIS_LOG_INFO, false );

         // Set max size of log in bytes before log is rotated (NOTE: Must be between 1kB and 10MB)
         appLogConfig.max_size_bytes = SCS_CDA_TTI_BRIDGE_LOG_MAX_SIZE_BYTES;

         // Set max number of logs to keep in history of rotation (NOTE: Must be between 0 and 10)
         appLogConfig.max_logs = SCS_CDA_TTI_BRIDGE_LOG_MAX_LOGS;

         AppLogId = app_log_init( &appLogConfig );
         if ( AppLogId < 0 )
         {
            BRIDGE_APP_LOG( "Error initializing App Log, ID = " << AppLogId, AIS_LOG_ERROR, false );
         }
         else
         {
            logInit = true;
         }
      }
   }
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppLog::LogMsg
// Description     : Logs a message to the log file
// Return Type     : None
// Argument [in]   : const std::string& message - Message to be written into log
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void FileTransferBridgeAppLog::LogMsg( const std::string& message )
{
   if ( logInit )
   {
      // Log a message to specific log referenced by the provided ID
      int appLogRet = app_log(AppLogId, message.c_str());

      // Check that message was logged without error
      if ( appLogRet != 0 )
      {
         // Error initializing log
         AIS_LOG_ERROR("Error initializing App Log, ID = %d", AppLogId);
      }
   }
}
