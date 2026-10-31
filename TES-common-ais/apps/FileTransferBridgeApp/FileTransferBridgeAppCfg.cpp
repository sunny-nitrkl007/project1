////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: FileTransferBridgeAppCfg
//
// File Name: FileTransferBridgeAppCfg.cpp
//
//  Abstract: The code in this file was derived from CSNS
//            library libGetCDAServerDns.a and app
//            SetCDAServerDnsForClient. It is meant to make
//            File Transfer Bridge app independent of the
//            CDA verity and to contain configuration setup to
//            the .rb config script.
//            SetCDAServerDnsForClient is implemented in
//            FileTransferBridgeAppCda::SetCDAServerDns,
//            libGetCDAServerDns.a is implemented in
//            FileTransferBridgeAppCda::GetCDAServerDns.
//
////////////////////////////////////////////////////////

#include "FileTransferBridgeAppCfg.h"
#include "FileTransferBridgeAppUtil.h"
#include "FileTransferBridgeAppLog.h"

#include <boost/filesystem.hpp>

#include <CDASecureConfigs.h>

using namespace FileTransferBridge;

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppCfg::FileTransferBridgeAppCfg
// Description     : Class constructor
// Return Type     : N/A
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
FileTransferBridgeAppCfg::FileTransferBridgeAppCfg( ): m_ConfigTable()
{
}

////////////////////////////////////////////////////////////////////////////
// Function        : FileTransferBridgeAppCfg::ParseConfig
// Description     : Configuration file parser to populate local configuration table.
// Return Type     : bool - 'true' if configuration was parsed successfully,
//                   'false' otherwise
// Argument [in]   : ConfigSection& pRubyCfg - Main config section in the configuration file,
//                   TaskParser& rubyParser - Configuration file parser
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool FileTransferBridgeAppCfg::ParseConfig( ConfigSection& rubyCfg, TaskParser& rubyParser )
{
   bool returnValue = true;
   std::string parameterStringValue;
   m_ConfigTable = {};

   returnValue &= rubyCfg.get( "cycleRate_hz", m_ConfigTable.CycleRateHz );
   returnValue &= rubyCfg.get( "MaxDataFileSizeInBytes", m_ConfigTable.MaxDataFileSizeInBytes );
   returnValue &= rubyCfg.get( "PathOutgoing", m_ConfigTable.DataFileStoreDirPath );
   returnValue &= rubyCfg.get( "PathIncoming", m_ConfigTable.RecvDataFileStoreDirPath );
   returnValue &= rubyCfg.get( "PathAppLog", m_ConfigTable.FileStatusLogDirPath );
   returnValue &= rubyCfg.get( "NameAppLog", m_ConfigTable.FileStatusLogName );
   returnValue &= rubyCfg.get( "ClientConnModeSecure", parameterStringValue );
   m_ConfigTable.ClientConnModeSecure = ( "YES" == parameterStringValue );
   returnValue &= rubyCfg.get( "KeyOffTimeOutMSec", m_ConfigTable.KeyOffTimeOutMSec );
   returnValue &= rubyCfg.get( "SendWithoutScsRequests", parameterStringValue );
   m_ConfigTable.RebuildQueueEveryCycle = ( "YES" == parameterStringValue );
   rubyCfg.get( "ServerIP", m_ConfigTable.CDAServerIPAddress );
   if (!rubyCfg.get("ServerPort", m_ConfigTable.CDAServerPort))
   {
      m_ConfigTable.CDAServerPort = CDA_SERVER_PORT_FOR_ALL_CLIENTS;
   }
   if (!rubyCfg.get( "CertChainFile", m_ConfigTable.CertChainFilePath ))
   {
      m_ConfigTable.CertChainFilePath = CDA_SERVER_CA_CERT_CHAIN_PATH;
   }
   if (!boost::filesystem::is_regular_file(m_ConfigTable.CertChainFilePath))
   {
      AIS_LOG_FATAL("Certs file %s not found", m_ConfigTable.CertChainFilePath.c_str());
      return false;
   }

   returnValue &= rubyCfg.get( "FID_ThisApp", m_ConfigTable.DefaultSourceFID );

   { // IoTHubComms Configuration
       if (!rubyCfg.get("IoTHubOutboundQueueMaxSize", m_ConfigTable.IoTHubOutboundQueueMaxSize)) {
           // Default to 20
           m_ConfigTable.IoTHubOutboundQueueMaxSize = 20;

           AIS_LOG_WARN("IoTHubOutboundQueueMaxSize is not configured, default of %d used.", m_ConfigTable.IoTHubOutboundQueueMaxSize);
       }

       if (!rubyCfg.get("IoTHubInboundFileTypes", m_ConfigTable.IoTHubInboundFileTypes)) {
           // Default to none
           m_ConfigTable.IoTHubInboundFileTypes.clear();

           AIS_LOG_WARN("IoTHubInboundFileTypes is not configured, no inbound message will be received.");
       }
   }

   std::vector<std::string> supportedFileTypes;
   if ( returnValue &= rubyCfg.get( "FileTypes", supportedFileTypes ) )
   {
      m_ConfigTable.SupportReportTrigger = false;

      // Process each file type from "FileTypes" section
      for ( auto& fileType : supportedFileTypes )
      {
         // Get the section
         ConfigSection fileTypeConfigSection;
         if ( returnValue &= rubyParser.getSection( fileType, fileTypeConfigSection ) )
         {
            // Process parameters in this file type section
            CdaFileType_t fileType;
            CdaFileProperties_t fileTypeProperties;
            bool goodSection = fileTypeConfigSection.get( "Telematics File Number (File Type)", fileType ) &&
                               fileTypeConfigSection.get( "Transmit Queue Size Limit (Bytes)", fileTypeProperties.TxQueueSize ) &&
                               fileTypeConfigSection.get( "Receive Queue Size Limit (Bytes)", fileTypeProperties.RxQueueSize );

            (void)fileTypeConfigSection.get( "Default Outgoing Traffic Destinations", fileTypeProperties.CdaDefaultDestinationNodes );
            (void)fileTypeConfigSection.get( "CDA/TTI Server Incoming Traffic Accepted Sources", fileTypeProperties.CdaTtiSourceNodes );
            (void)fileTypeConfigSection.get( "CDA/SFT Incoming Traffic Accepted Sources", fileTypeProperties.CdaSftSourceNodes );
            if ( fileTypeConfigSection.get( "CDA/SFT Report Trigger Sources", fileTypeProperties.CdaSftReportTriggerNodes ) )
            {
               m_ConfigTable.SupportReportTrigger = true;
            }
            fileTypeProperties.AcceptCdaSftTraffic = fileTypeConfigSection.get( "CDA/SFT Incoming Traffic Intended Destinations", fileTypeProperties.CdaSftIntendedDestinationNodes );

            // If this file type section has been parsed successfully, then add the file type to our map
            if ( goodSection )
            {
               m_ConfigTable.MapFileTypes[fileType] = fileTypeProperties;
            }
            returnValue &= goodSection;
         }
      }
   }

   if ( false == returnValue )
   {
      BRIDGE_APP_LOG( "File Transfer Bridge was unable to read its configuration", AIS_LOG_FATAL, true );
      BRIDGE_APP_LOG( "*** cycleRate_hz: " << m_ConfigTable.CycleRateHz, AIS_LOG_ERROR, false );
      BRIDGE_APP_LOG( "*** MaxDataFileSizeInBytes: " << m_ConfigTable.MaxDataFileSizeInBytes, AIS_LOG_ERROR, false );
      BRIDGE_APP_LOG( "*** PathOutgoing: " << m_ConfigTable.DataFileStoreDirPath, AIS_LOG_ERROR, false );
      BRIDGE_APP_LOG( "*** PathIncoming: " << m_ConfigTable.RecvDataFileStoreDirPath, AIS_LOG_ERROR, false );
      BRIDGE_APP_LOG( "*** App log: " << m_ConfigTable.FileStatusLogDirPath << "/" << m_ConfigTable.FileStatusLogName, AIS_LOG_ERROR, false );
      BRIDGE_APP_LOG( "*** ClientConnModeSecure: " << static_cast<unsigned_16>( m_ConfigTable.ClientConnModeSecure ), AIS_LOG_ERROR, false );
      BRIDGE_APP_LOG( "*** KeyOffTimeOutMSec: " << m_ConfigTable.KeyOffTimeOutMSec, AIS_LOG_ERROR, false );
      BRIDGE_APP_LOG( "*** SendWithoutScsRequests: " << static_cast<unsigned_16>( m_ConfigTable.RebuildQueueEveryCycle ), AIS_LOG_ERROR, false );
      BRIDGE_APP_LOG( "*** ServerIP: " << m_ConfigTable.CDAServerIPAddress, AIS_LOG_ERROR, false );
      BRIDGE_APP_LOG( "*** ServerPort: " << m_ConfigTable.CDAServerPort, AIS_LOG_ERROR, false );
      BRIDGE_APP_LOG( "*** CertChainFile: " << m_ConfigTable.CertChainFilePath, AIS_LOG_ERROR, false );
      BRIDGE_APP_LOG( "*** FID_ThisApp: " << static_cast<unsigned_32>( m_ConfigTable.DefaultSourceFID ), AIS_LOG_ERROR, false );
      BRIDGE_APP_LOG( "*** MapFileTypes size: " << m_ConfigTable.MapFileTypes.size(), AIS_LOG_ERROR, false );
   }
   else
   {
      // Create all necessary paths
      BRIDGE_APP_LOG( "| | | | | | TX directory path set by .rb config: " << m_ConfigTable.DataFileStoreDirPath, AIS_LOG_NOTICE, false );
      FileTransferBridgeAppUtil::PathFixSlash( m_ConfigTable.DataFileStoreDirPath );
      (void)FileTransferBridgeAppUtil::MakeDirFullPath( m_ConfigTable.DataFileStoreDirPath );
      FileTransferBridgeAppUtil::PathFixSlash( m_ConfigTable.RecvDataFileStoreDirPath );
      (void)FileTransferBridgeAppUtil::MakeDirFullPath( m_ConfigTable.RecvDataFileStoreDirPath );
      FileTransferBridgeAppUtil::PathFixSlash( m_ConfigTable.FileStatusLogDirPath );
      (void)FileTransferBridgeAppUtil::MakeDirFullPath( m_ConfigTable.FileStatusLogDirPath );
   }

   return returnValue;
}
