////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: FileTransferBridgeAppCfg
//
// File Name: FileTransferBridgeAppCfg.h
//
//  Abstract: Declarations for the Bridge
//            application configuration manager.
//
////////////////////////////////////////////////////////

#ifndef SCSCDATTIBRIDGECFG_H
#define SCSCDATTIBRIDGECFG_H

#include <string>    // Needed for std::string
#include <map>       // Needed for std::map
#include <ais/config/ConfigSection.h>
#include <ais/config/TaskParser.h>
#include "FileTransferBridgeAppDef.h"

class FileTransferBridgeAppCfg
{
public:
   FileTransferBridgeAppCfg( );
   ~FileTransferBridgeAppCfg( ) { }

   bool ParseConfig( ConfigSection& rubyCfg, TaskParser& rubyParser );
   inline FileTransferBridge::FileTransferBridgeAppCfg_t GetConfiguration( void )
   {
      return m_ConfigTable;
   }

protected:

private:
   FileTransferBridge::FileTransferBridgeAppCfg_t m_ConfigTable;
};


#endif // SCSCDATTIBRIDGECFG_H
