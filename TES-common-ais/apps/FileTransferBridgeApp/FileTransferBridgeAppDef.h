////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: N/A
//
// File Name: FileTransferBridgeAppDef.h
//
//  Abstract: Bridge application common definitions.
//
////////////////////////////////////////////////////////

#ifndef SCSCDATTIBRIDGEDEF_H
#define SCSCDATTIBRIDGEDEF_H

#include <map>       // Needed for std::map
#include <string>    // Needed for std::string
#include <vector>    // Needed for std::vector
#include <algorithm> // Needed for std::find
#include <cstdint>
#include <cat_std_types.h>

// Macro returning the std::thread ID
#define THREAD_ID std::this_thread::get_id()

// Macro that checks a vector for an element ("returns" true if element is found)
#define VECTOR_HAS_ELEMENT( vectorElement, vectorContainer ) \
      ( std::find( vectorContainer.begin(), vectorContainer.end(), vectorElement ) != vectorContainer.end() )

// Macro that iterates through a source vector and adds elements to destination vector if they don't already exist
#define ADD_UNIQUE_ELEMENTS_FROM_VECTOR( destinationVector, sourceVector )                                              \
      for ( auto& sourceNode : sourceVector )                                                                           \
      {                                                                                                                 \
         if ( !VECTOR_HAS_ELEMENT( sourceNode, destinationVector ) )                                                    \
         {                                                                                                              \
            destinationVector.push_back( sourceNode );                                                                  \
         }                                                                                                              \
      }


namespace FileTransferBridge
{
   // Define named types for a File Type and File Size in case the base type ever changes
   typedef unsigned_32     CdaFileType_t;
   typedef unsigned_32     CdaFileSize_t;

   // All serviceable nodes over CDA must have a unique ID. This can be either FID or value from enum DestinationMessage_DESTINATION
   typedef unsigned_32 CdaNode_t;
   typedef std::vector<CdaNode_t> CdaNodeList_t;

   // Type definition for the properties that comes with each transmitted File Type
   typedef struct CdaFileProperties_s
   {
      CdaFileSize_t     TxQueueSize;
      CdaFileSize_t     RxQueueSize;
      CdaNodeList_t     CdaDefaultDestinationNodes;
      CdaNodeList_t     CdaTtiSourceNodes;
      CdaNodeList_t     CdaSftSourceNodes;
      CdaNodeList_t     CdaSftIntendedDestinationNodes;
      CdaNodeList_t     CdaSftReportTriggerNodes;
      bool              AcceptCdaSftTraffic;
   } CdaFileProperties_t;

   // This application's configuration
   typedef struct FileTransferBridgeAppCfg_s
   {
      unsigned_16                                        CycleRateHz;
      CdaFileSize_t                                      MaxDataFileSizeInBytes;
      std::string                                        DataFileStoreDirPath;
      std::string                                        RecvDataFileStoreDirPath;
      std::string                                        FileStatusLogDirPath;
      std::string                                        FileStatusLogName;
      std::map<CdaFileType_t, CdaFileProperties_t>       MapFileTypes;
      unsigned_32                                        KeyOffTimeOutMSec;
      std::string                                        LogDataFileName;
      bool                                               ClientConnModeSecure;
      bool                                               RebuildQueueEveryCycle;
      CdaNode_t                                          DefaultSourceFID;
      std::string                                        CDAServerIPAddress;
      std::string                                        CDAServerPort;
      std::string                                        CertChainFilePath;
      bool                                               SupportReportTrigger;
      std::vector<uint32_t>                              IoTHubInboundFileTypes;
      uint16_t                                           IoTHubOutboundQueueMaxSize;
   } FileTransferBridgeAppCfg_t;

   typedef struct FileInfo_s
   {
      CdaFileType_t     TelematicsFileNumber; // File Type
      CdaFileSize_t     SizeInBytes;
      std::string       Name;
      std::string       DirPath;
      unsigned_32       ModifyTime; // Last time the file was modified in seconds since epoch
      CdaNode_t         SourceFID;
      CdaNode_t         DestinationFID;

      // Default constructor
      FileInfo_s(): TelematicsFileNumber(0), SizeInBytes(0), Name(), DirPath(), ModifyTime(0), SourceFID(0), DestinationFID(0) { }

      // Overload the less-than operator to compare the modification time
      bool operator<( const FileInfo_s& rhs ) const { return ( ModifyTime < rhs.ModifyTime ); }

      // Overload the is-equal operator to check if the file names match
      bool operator==( const FileInfo_s& rhs ) const { return ( Name == rhs.Name ); }
   } FileInfo_t;

} // End of namespace block

#endif /* #ifndef SCSCDATTIBRIDGEDEF_H */
