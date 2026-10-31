////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: FileTransferBridgeAppCda
//
// File Name: FileTransferBridgeAppCdaServerCfg.cpp
//
//  Abstract: This source file works with the
//            CDA sever's hostname/common name.
//
////////////////////////////////////////////////////////

#include <fstream>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
//#include <fcntl.h>

#include "FileTransferBridgeAppCda.h"

#define HOSTS_PATH "/etc/hosts"
#define AIS_LOG_WRAPPER( logStatement ) { if ( !FailureLogged ) { logStatement } }

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppCda::GetCDAServerDnsFromIP
// Description     : Read the CDA server's common name from the hosts file
// Return Type     : bool - 'true' if the name was obtained, 'false' otherwise
// Argument [in]   : const std::string& ipAddr - Server's IP address.
// Argument [out]  : std::string& CDAServerDns - Server's name.
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeAppCda::GetCDAServerDnsFromIP( const std::string& ipAddr, std::string& CDAServerDns )
{
   bool retVal = false;
   std::ifstream hostsFile( HOSTS_PATH, std::ios_base::in );
   if ( hostsFile.is_open() )
   {
      std::string nextLine;
      while ( getline( hostsFile, nextLine ) )
      {
         std::string::size_type serverIpPos = nextLine.find( ipAddr );
         if( std::string::npos != serverIpPos )
         {
            nextLine.erase( serverIpPos, ipAddr.length() );
            // Erase spaces and tabs (Erase–remove idiom)
            nextLine.erase( std::remove( nextLine.begin(), nextLine.end(), ' ' ), nextLine.end() );
            nextLine.erase( std::remove( nextLine.begin(), nextLine.end(), '\t' ), nextLine.end() );
            CDAServerDns = nextLine;
            retVal = true;
            break;
         }
      }
      hostsFile.close();
   }

   return retVal;
}
