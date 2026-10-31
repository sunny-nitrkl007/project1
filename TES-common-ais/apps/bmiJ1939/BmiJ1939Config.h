////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939Config
//
// File Name: BmiJ1939Config.h
//
//  Abstract: Declarations for the class that handles
//            the application configuration, including
//            J1939 parameter tables
//
////////////////////////////////////////////////////////

#ifndef BMIJ1939CONFIG_H_
#define BMIJ1939CONFIG_H_

#include <string>          // std::string
#include <unordered_map>
#include <vector>          // std::vector
#include <std_types.h>
#include <scl_health_j39_ecm.h>
#include <ais/config/ConfigSection.h>
#include "BmiJ1939SCS.h"
extern "C"
{
	#include <cdl2_struct.h>
}

#define NO_TIMEOUT 0 // Timeout value when there's no parameter timeout requested

typedef enum
		{
		   J1939_SPB_REQUEST = 0,
		   J1939_PGB_REQUEST,
		   J1939_ADT_REQUEST,
		   J1939_READ_POLL,
		   J1939_MAP_REQUEST,
		   J1939_INVALID_REQ_TYPE
		} J1939ParamReqType_t;

class BmiJ1939Config
{
public:

   typedef struct PGNTableEntry_s
   {
      std::string       ParameterGroupName;     // PGN name
      unsigned_32       ParameterGroupNumber;   // PGN
      unsigned_32       SourceAddress;          // J1939 address, refer to https://datalinks.ecorp.cat.com/J1939/SourceAddresses/
      std::string       SourceName;             // J1939 name of the source for the PGN
      unsigned_16       MsgHandlerIndex;        // Index of the function to handle this PGN from the table m_pgnHandlers
      int_16            Timeout_ms;             // Expected time frame to receive this PGN
      unsigned_8        Priority;               // Message priority when requesting PGN
      unsigned_32       ControlBitField;        // CBF (reference SCL_J1939_RX_MSG_CBF_ENABLED, etc. in scl_j1939_struct.h)
      unsigned_16       Cid;                    // ECM CID
      std::vector<scl_health_j39_id_and_type_t> SpnList; // List of SPNs for health monitoring

      // Overload "<" operator to support std::sort()
      bool operator< ( const struct PGNTableEntry_s& rhs ) const { return ParameterGroupNumber < rhs.ParameterGroupNumber; }
   } PGNTableEntry_t;

   typedef struct CDLPIDTableEntry_s
   {
      std::string       ParameterName;          // Name associated with PID
      unsigned_32       ParameterID;            // PID
      unsigned_8        DataSize;               // Size of the data in bytes
      unsigned_32       SourceAddress;          // J1939 address, refer to https://datalinks.ecorp.cat.com/J1939/SourceAddresses/
      unsigned_16       RequestRate_ms;         // PID request rate
      real_64           Scaling;                // Parameter scaling factor
      real_64           Offset;                 // Parameter offset
      unsigned_8        Units;                  // Parameter units (as per DataLinkParamInfo::DlpUnits_t)
      unsigned_16       Timeout_ms;             // Expected time frame to receive this PID
      std::string       Attributes;             // "signed", "DSI", "swap" are searched for in the string
      unsigned_8        RequestType;			// Request type pgb/spb/readpoll
      unsigned_8 		VarLengthDataType;		// Varible length parameter type
      unsigned_8		ParameterType;			// used for automatic data status detection(From file  cdl2_struct.h)
      unsigned_16		Cid;					// ECM CID
      // Overload "<" operator to support std::sort()
      bool operator< ( const struct CDLPIDTableEntry_s& rhs ) const { return ParameterID < rhs.ParameterID; }
   } CDLPIDTableEntry_t;

   typedef struct CATEXTIDTableEntry_s
   	{
   		std::string 	ParamName;
   		unsigned_32		ExtensionID;
   		unsigned_32     SourceAddress;
   		unsigned_8      Priority;
   		unsigned_16     RequestPeriod_ms;
   		unsigned_32		RestrictedAdtParamId; //use only if Restricted Read Request
   	}CATEXTIDTableEntry_t;

   struct SclHealthPeerConfigTable_t
   {
      scl_health_j39_peer_config_t peerConfig;
      uint16_t cid;
   };

   typedef std::vector<PGNTableEntry_t> PGNTableEntries_t;
   typedef std::vector<CDLPIDTableEntry_t> CDLPIDTableEntries_t;
   typedef std::vector<CATEXTIDTableEntry_t> EXTIDTableEntries_t;
   using SclHealthPeerConfigTableEntries_t = std::vector<SclHealthPeerConfigTable_t>;

   static BmiJ1939Config& GetInstance();
   bool Initialize( ConfigSection *Rubycfg, DataLinkParamInfo::DlpDataLinkType_t dataLinkType );
   bool inline ConfigParsed( void ) const { return m_ParseSuccessful; }
   PGNTableEntries_t inline GetConfiguredPGNs( void ) const { return m_PGNs; }
   CDLPIDTableEntries_t inline GetConfiguredPGBPIDs( void ) const { return m_PGBPIDs; }
   CDLPIDTableEntries_t inline GetConfiguredReadPIDs( void ) const { return m_ReadPIDs; }
   CDLPIDTableEntries_t inline GetConfiguredMapPIDs( void ) const { return m_MapPIDs; }
   CDLPIDTableEntries_t inline GetConfiguredADTPIDs( void ) const { return m_ADTPIDs; }
   EXTIDTableEntries_t inline GetConfiguredEXTIDs( void ) const { return m_CatExtIDs; }
   std::vector<SclHealthPeerConfigTable_t> inline GetSclHealthPeerConfigTable( void ) const { return m_SclHealthPeerConfigTable; }
   static uint16_t GetCidFromSid(uint32_t sourceAddress) { return BmiJ1939Config::GetInstance().m_SidCidTable[sourceAddress]; }
   static DataLinkParamInfo::DlpDataLinkType_t GetDataLinkType() { return BmiJ1939Config::GetInstance().m_DataLinkType; }
   static void SetDataLinkType(DataLinkParamInfo::DlpDataLinkType_t dataLinkType) { BmiJ1939Config::GetInstance().m_DataLinkType = dataLinkType; }

private:
   BmiJ1939Config() : m_ParseSuccessful( false ) {};
   virtual ~BmiJ1939Config( void ) { }
   bool ParseJSONFile( const std::string& filename );
   bool IsValidPGNExistsInJson();
   bool CreateSclHealthPeerConfig();
   bool AddToSclHealthPeerConfig( unsigned_32 sourceAddress, uint16_t cid);

   bool                                     m_ParseSuccessful;
   PGNTableEntries_t                        m_PGNs;
   CDLPIDTableEntries_t                     m_PGBPIDs;
   CDLPIDTableEntries_t                     m_ReadPIDs;
   CDLPIDTableEntries_t                     m_MapPIDs;
   CDLPIDTableEntries_t                     m_ADTPIDs;
   EXTIDTableEntries_t                      m_CatExtIDs;
   DataLinkParamInfo::DlpDataLinkType_t     m_DataLinkType;
   std::vector<SclHealthPeerConfigTable_t>  m_SclHealthPeerConfigTable;
   std::unordered_map<unsigned_32, uint16_t> m_SidCidTable;
};

#endif // BMIJ1939CONFIG_H_
