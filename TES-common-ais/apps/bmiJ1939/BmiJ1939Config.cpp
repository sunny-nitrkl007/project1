////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939Config
//
// File Name: BmiJ1939Config.cpp
//
//  Abstract: Implementation of the class that handles
//            the application configuration, including
//            J1939 parameter tables
//
////////////////////////////////////////////////////////

#include <algorithm>       // std::find
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <scl_j1939_struct.h>
#include "BmiJ1939Config.h"

// Most of the debug logging is done with the following macro; this allows us to change logging threshold in one place
#define LOG_CONFIG AIS_LOG_DEBUG

// The following macro wraps an instruction/operation into a try-catch block and outputs a log message in case of failure
#define BMIJ1939CFG_WRAP( instruction, flag, failureLogMsg, ... ) try {                   \
      instruction; flag = true; } catch ( const std::exception& e ) {                     \
         LOG_CONFIG( failureLogMsg ": [[%s]]", ##__VA_ARGS__, e.what() ); }

// We can add template parameters to JSON files with the following text pattern in the parameter name; these are skipped over
#define JSON_TEMPLATE_PATTERN 			"Template:"
#define J1939_CDL_PID_CONFIG 			"CDL_PID"
#define J1939_CAT_EXT_CONFIG 			"CAT_EXT_ID"
#define J1939_PGN_CONFIG 				"PGN"

#define J1939_PROP_A_PGN 	0xEF00
////////////////////////////////////////////////////////////////////////////
// Function        : GetJSONParam
// Description     : This function extract a parameter from a Property Tree
//                   built off JSON file
// Return Type     : bool - 'true' if extracted without errors, 'false' otherwise
// Argument [in]   : const boost::property_tree::ptree& propertyTree - Reference
//                      to the Property Tree,
//                   const std::string& parameterName - Name of the JSON element,
//                   const std::string& fieldName - Name of the parameter within
//                      JSON element
// Argument [out]  : T& dataStorage - Storage for the parameter
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
template <typename T>
static bool GetJSONParam( const boost::property_tree::ptree& propertyTree,
      const std::string& parameterName,
      const std::string& fieldName,
      T& dataStorage )
{
   bool returnFlag = false;
   const std::string extractNode = parameterName + "." + fieldName;

   LOG_CONFIG( "Attempting to extract %s for '%s'", fieldName.c_str(), parameterName.c_str() );
   BMIJ1939CFG_WRAP( dataStorage = propertyTree.get<T>( extractNode ),
         returnFlag, "%s for '%s' has failed the extraction", fieldName.c_str(), parameterName.c_str() )

   return returnFlag;
}

////////////////////////////////////////////////////////////////////////////
// Function        : GetJSONParamU32
// Description     : This function extract a parameter from a Property Tree
//                   built off JSON file and attempts to convert it to a decimal number.
//                   If failed to process as a number it will check if the parameter
//                   is a hexadecimal string (JSON does not support hex notation)
// Return Type     : bool - 'true' if converted successfully, 'false' otherwise
// Argument [in]   : const boost::property_tree::ptree& propertyTree - Reference
//                      to the Property Tree,
//                   const std::string& parameterName - Name of the JSON element,
//                   const std::string& fieldName - Name of the parameter within
//                      JSON element
// Argument [out]  : unsigned_32& dataStorage - Storage for the parameter
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
static bool GetJSONParamU32( const boost::property_tree::ptree& propertyTree,
      const std::string& parameterName,
      const std::string& fieldName,
      unsigned_32& dataStorage )
{
	std::string tempStorageStr;
	unsigned_32 tempStorageNum = 0;

	// Try as a decimal number first
	bool returnFlag = GetJSONParam( propertyTree, parameterName, fieldName, tempStorageNum );

   // If the extraction as a decimal has failed, then try as a hexadecimal string
   if ( !returnFlag && GetJSONParam( propertyTree, parameterName, fieldName, tempStorageStr ) )
   {
      std::size_t numCharsProcessed = 0;
      LOG_CONFIG( "Parsing '%s' of '%s' as a string", fieldName.c_str(), parameterName.c_str() );
      BMIJ1939CFG_WRAP( tempStorageNum = std::stoul( tempStorageStr, &numCharsProcessed, 16 ),
            returnFlag,
            "Failed to convert parameter '%s' field '%s' value '%s' to integer using hex base",
            parameterName.c_str(), fieldName.c_str(), tempStorageStr.c_str() )
      returnFlag &= ( tempStorageStr.length() == numCharsProcessed );
   }

   if ( returnFlag )
   {
      LOG_CONFIG( "Converted parameter '%s' field '%s' to 0x%X", parameterName.c_str(), fieldName.c_str(), tempStorageNum );
      dataStorage = tempStorageNum;
   }

   return returnFlag;
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Config::GetInstance
// Description     : Singleton factory interface to BmiJ1939Config
// Return Type     : BmiJ1939Config&
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
BmiJ1939Config& BmiJ1939Config::GetInstance()
{
   static BmiJ1939Config bmiJ1939Config;
   return bmiJ1939Config;
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Config::Initialize
// Description     : Parses all configuration files
// Return Type     : true if parse successful, false otherwise
// Argument [in]   : const ConfigSection& cfg - Task configuration
//                   DataLinkParamInfo::DlpDataLinkType_t dataLinkType - CAN1 or CAN2
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool BmiJ1939Config::Initialize( ConfigSection *Rubycfg, DataLinkParamInfo::DlpDataLinkType_t dataLinkType )
{
   m_DataLinkType = dataLinkType;
   std::string filename;
   if ( !(Rubycfg->get( "BMI_J1939_CONFIG_JSON_FILE_PATH", filename )) )
   {
	   AIS_LOG_ERROR( "unable to find the J1939 config json file path. Please configure correct file path!" );
   }
   else if ( !ParseJSONFile( filename ) )
   {
	   AIS_LOG_ERROR( " JSON file '%s' contains errors. Please update json file correctly! ", filename.c_str() );
   }
   else if( !IsValidPGNExistsInJson())
   {
	   AIS_LOG_ERROR("Please configure the required PROPA PGN in Json file to work with CDL PIDs over J1939.");
   }
   else if( !CreateSclHealthPeerConfig())
   {
	   AIS_LOG_ERROR("SCL Health Peer Config not created.");
   }
   else
   {
      m_ParseSuccessful = true;
   }
   return m_ParseSuccessful;
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Config::IsValidPGNExistsInJson
// Description     : Check for the valid PROPA PGN in the PGN List
// Return Type     : bool - 'true' if PROPRIETARY A (PROPA) PGN Exists, 'false' otherwise
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool BmiJ1939Config::IsValidPGNExistsInJson()
{
	bool ValidPGNExists = false;

	if(m_PGNs.end() != std::find_if(m_PGNs.begin(), m_PGNs.end(), [](const PGNTableEntry_t& containerElement){
		return containerElement.ParameterGroupNumber == J1939_PROP_A_PGN; } ))
	{
		LOG_CONFIG("Required PROPA PGN Exists in the PGN List");
		ValidPGNExists = true;
	}

 return ValidPGNExists;
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Config::ParseJSONFile
// Description     : JSON file parser that populates local/class table
//                   with the handled parameters
// Return Type     : bool - 'true' if parsed with no errors, 'false' otherwise
// Argument [in]   : const std::string& filename - JSON file name
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool BmiJ1939Config::ParseJSONFile( const std::string& filename )
{
   boost::property_tree::ptree propTree;
   bool overallSuccess = false;
   DataLinkParam dlParam;

   // Set DataLinkType
   dlParam.SetDataLinkType(m_DataLinkType);

   AIS_LOG_NOTICE( "Parsing file %s", filename.c_str() );

   // Attempt to load the JSON file
   BMIJ1939CFG_WRAP( boost::property_tree::read_json( filename, propTree ),
		   overallSuccess, "Failed to read '%s'", filename.c_str() )

   if ( overallSuccess )
     {
        // Go through each element of the JSON file
        for ( auto& jsonElement : propTree )
        {
           // Check the JSON element name to see if this is a template/example parameter
           if ( std::string::npos != jsonElement.first.find( JSON_TEMPLATE_PATTERN ) )
           {
              LOG_CONFIG( "Skipping over other parameters '%s'", jsonElement.first.c_str() );
           }
           // Check for the PGN tag in Json config file
           else if( std::string::npos != jsonElement.first.find( J1939_PGN_CONFIG ) )
		   {
        	  LOG_CONFIG( " Found JSON element '%s' ", jsonElement.first.c_str() );
        	  // Extract each node from Identified JSON element
        	  for(auto& property: jsonElement.second)
			  {
			  // Construct new entry with the element's name and all default parameters
			  PGNTableEntry_t newEntry { property.first, 0, SCL_J1939_GLOBAL_ADDRESS, "", 0, NO_TIMEOUT, 6, SCL_J1939_RX_MSG_CBF_ENABLED };
			  LOG_CONFIG( "Parsing element '%s'", newEntry.ParameterGroupName.c_str() );

			  // Extract all mandatory parameters first
			  if ( !GetJSONParamU32( jsonElement.second, newEntry.ParameterGroupName, "PGN", newEntry.ParameterGroupNumber ) )
			  {
				 AIS_LOG_ALERT( "Unable to retrieve PGN for J1939 parameter '%s'", newEntry.ParameterGroupName.c_str() );
				 overallSuccess = false;
			  }
			  else
			  {
				 // Extract all optional parameters
				 if ( !GetJSONParam( jsonElement.second, newEntry.ParameterGroupName, "Source Name", newEntry.SourceName ) )
				 {
					(void)GetJSONParamU32( jsonElement.second, newEntry.ParameterGroupName, "Source Address", newEntry.SourceAddress );
				 }
				 (void)GetJSONParam( jsonElement.second, newEntry.ParameterGroupName, "Handler Index", newEntry.MsgHandlerIndex );
				 (void)GetJSONParam( jsonElement.second, newEntry.ParameterGroupName, "Timeout(ms)", newEntry.Timeout_ms );
				 (void)GetJSONParam( jsonElement.second, newEntry.ParameterGroupName, "Priority", newEntry.Priority );
				 (void)GetJSONParamU32( jsonElement.second, newEntry.ParameterGroupName, "Control Bitfield", newEntry.ControlBitField );
             (void)GetJSONParam( jsonElement.second, newEntry.ParameterGroupName, "Cid", newEntry.Cid );

             // Parse SPN List, removing spaces
             std::string spnListRaw;
             (void)GetJSONParam(jsonElement.second, newEntry.ParameterGroupName, "SPN List", spnListRaw);
             spnListRaw.erase(std::remove_if(spnListRaw.begin(), spnListRaw.end(), isspace), spnListRaw.end());
             std::vector<std::string> spnListText;
             boost::split(spnListText, spnListRaw, boost::is_any_of(","));
             // Convert SPN to an unsigned int and add to the SpnList if it is unique
             for (auto &spnText : spnListText)
             {
                unsigned_32 spn;
                bool returnFlag = false;
                BMIJ1939CFG_WRAP(spn = std::stoul(spnText, nullptr), returnFlag,
                                 "Failed to convert SPN %s to unsigned", spnText.c_str())
                if (returnFlag &&
                    std::find_if(newEntry.SpnList.begin(), newEntry.SpnList.end(),
                                 [spn](const scl_health_j39_id_and_type_t &entry) { return entry.id == spn; }) == newEntry.SpnList.end())
                {
                   AIS_LOG_DEBUG("Adding SPN %u to PGN %u", spn, newEntry.ParameterGroupNumber);
                   newEntry.SpnList.push_back(scl_health_j39_id_and_type_t{SCL_HEALTH_J39_PTYPE_J1939_SPN, spn});
                }
             }

             if (newEntry.SpnList.size() == 0)
             {
                AIS_LOG_WARN("No SPNs found for PGN %u", newEntry.ParameterGroupNumber);
             }
             else
             {
                AIS_LOG_DEBUG("Parsed %u SPNs: %s", newEntry.SpnList.size(), spnListRaw.c_str());
             }

             /*Adding data to the new dlDataMap*/
				 if(newEntry.MsgHandlerIndex == 0) // Index 0 - User defined handler for Public PGN's
				 {
					 dlParam.SetParamIdentifierType( DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PUBLIC_PGN );
				 }
				 else //Index 1 - CSNS Handler
				 {
					 dlParam.SetParamIdentifierType( DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID );
				 }
				 dlParam.SetParameterName( newEntry.ParameterGroupName );
				 dlParam.SetParamId( newEntry.ParameterGroupNumber);
				 dlParam.SetSid( newEntry.SourceAddress );
				 dlParam.SetParameterType( CDL2_VAR_NO_DSI );
				 dlParam.SetVarLengthParamType(VarLengthDataLinkParamPool::PGN);
				 dlParam.SetScaling( 1 );
				 dlParam.SetOffset( 0 );
               if (false == BmiJ1939SCS::AddDataLinkData( dlParam ))
               {
                   overallSuccess = false;
                   break;
               }
				 // Check if the element with this ID has been previously processed (predicate is a lambda expression that looks for a matching ParameterGroupNumber in the container)
				 if ( m_PGNs.end() != std::find_if( m_PGNs.begin(), m_PGNs.end(),
					   [ newEntry ]( const PGNTableEntry_t& containerElement )->bool { return newEntry.ParameterGroupNumber == containerElement.ParameterGroupNumber; } ) )
				 {
					AIS_LOG_ALERT( "Found duplicate PGN 0x%X (%d) in %s", newEntry.ParameterGroupNumber, newEntry.ParameterGroupNumber, filename.c_str() );
				 }
				 else
				 {
					// Add the new PGN with all its properties to the container
					m_PGNs.push_back( newEntry );
				 }
			  }
			}
		   }
           // Check for the CDL PID tag in Json config file
           else if ( std::string::npos != jsonElement.first.find( J1939_CDL_PID_CONFIG ) )
  		   {
        	LOG_CONFIG( " Found JSON element '%s' ", jsonElement.first.c_str() );
        	// Extract each node from Identified JSON element
        	for(auto& property: jsonElement.second)
  			{
              // Construct new entry with the element's name and all default parameters
              CDLPIDTableEntry_t newEntry { property.first, 0, 0, 0, 0, 1.0, 0, 0, NO_TIMEOUT, "", J1939_INVALID_REQ_TYPE, 0, 0, 0};
              LOG_CONFIG( "Parsing element '%s'", newEntry.ParameterName.c_str() );

              // Extract all mandatory parameters first
              if ( !GetJSONParamU32( jsonElement.second, newEntry.ParameterName, "CDL PID", newEntry.ParameterID ) )
              {
                 AIS_LOG_ALERT( "Unable to retrieve CDL PID for parameter '%s'", newEntry.ParameterName.c_str() );
                 overallSuccess = false;
              }
              else if ( !GetJSONParam( jsonElement.second, newEntry.ParameterName, "Data Size(bytes)", newEntry.DataSize ) )
              {
                 AIS_LOG_ALERT( "Unable to retrieve CDL PID data size for parameter '%s'", newEntry.ParameterName.c_str() );
                 overallSuccess = false;
              }
              else if ( !GetJSONParamU32( jsonElement.second, newEntry.ParameterName, "Source J1939 Address", newEntry.SourceAddress ) )
              {
                 AIS_LOG_ALERT( "Unable to retrieve CDL PID source address for parameter '%s'", newEntry.ParameterName.c_str() );
                 overallSuccess = false;
              }
              else if ( !GetJSONParam( jsonElement.second, newEntry.ParameterName, "Request Rate(ms)", newEntry.RequestRate_ms ) )
              {
                 AIS_LOG_ALERT( "Unable to retrieve CDL PID request rate for parameter '%s'", newEntry.ParameterName.c_str() );
                 overallSuccess = false;
              }
              else
              {
              	newEntry.RequestType = static_cast<J1939ParamReqType_t>(newEntry.RequestType);
              	newEntry.ParameterType = static_cast<cdl2_parameter_type_e>(newEntry.ParameterType);
              	// Extract all optional parameters
                 (void)GetJSONParam( jsonElement.second, newEntry.ParameterName, "Scaling", newEntry.Scaling );
                 (void)GetJSONParam( jsonElement.second, newEntry.ParameterName, "Offset", newEntry.Offset );
                 (void)GetJSONParam( jsonElement.second, newEntry.ParameterName, "Units", newEntry.Units );
                 (void)GetJSONParam( jsonElement.second, newEntry.ParameterName, "Timeout(ms)", newEntry.Timeout_ms );
                 (void)GetJSONParam( jsonElement.second, newEntry.ParameterName, "Attributes", newEntry.Attributes );
                 (void)GetJSONParam( jsonElement.second, newEntry.ParameterName, "RequestType", newEntry.RequestType );
                 (void)GetJSONParam( jsonElement.second, newEntry.ParameterName, "VarLengthDataType", newEntry.VarLengthDataType );
                 (void)GetJSONParam( jsonElement.second, newEntry.ParameterName, "ParameterType", newEntry.ParameterType );
                 (void)GetJSONParam( jsonElement.second, newEntry.ParameterName, "Cid", newEntry.Cid );

                 /*Adding data to the new dlDataMap*/
                 dlParam.SetParameterName( newEntry.ParameterName );
                 dlParam.SetParamIdentifierType( DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID );
                 dlParam.SetParamId( newEntry.ParameterID );
                 dlParam.SetParameterType(newEntry.ParameterType);
                 dlParam.SetVarLengthParamType(static_cast<VarLengthDataLinkParamPool::VarLengthParamType>(newEntry.VarLengthDataType));
                 dlParam.SetSid( newEntry.SourceAddress );
                 dlParam.SetScaling( newEntry.Scaling );
                 dlParam.SetOffset( newEntry.Offset );
                 dlParam.SetUnits( static_cast<DataLinkParamInfo::DlpUnits_t>(newEntry.Units ));
               if (false == BmiJ1939SCS::AddDataLinkData(dlParam))
               {
                   overallSuccess = false;
                   break;
               }
                 // Check if the element with this ID has been previously processed (predicate is a lambda expression that looks for a matching ParameterID in the container)
               if ( m_PGBPIDs.end() != std::find_if( m_PGBPIDs.begin(), m_PGBPIDs.end(),
                       [ newEntry ]( const CDLPIDTableEntry_t& containerElement )->bool { return ( (newEntry.ParameterID == containerElement.ParameterID) && ( (newEntry.SourceAddress == containerElement.SourceAddress) )); } ) )
               {
                   AIS_LOG_ALERT( "Found duplicate PID 0x%X (%d) in %s", newEntry.ParameterID, newEntry.ParameterID, filename.c_str() );
               }
                 else if( J1939_PGB_REQUEST == newEntry.RequestType )/*check for parameter request type*/
                 {
                    // Add the new PID with all its properties to the container
              	   m_PGBPIDs.push_back( newEntry );
                 }
				 else if( J1939_READ_POLL == newEntry.RequestType )
				 {
				   // Add the new PID with all its properties to the container
				   m_ReadPIDs.push_back( newEntry );
				 }
				 else if( J1939_MAP_REQUEST == newEntry.RequestType )
				 {
				   // Add the new PID with all its properties to the container
				   m_MapPIDs.push_back( newEntry );
				 }
				 else if( J1939_ADT_REQUEST == newEntry.RequestType )/*check for parameter request type*/
				 {
					 // Add the new PID with all its properties to the container
				   m_ADTPIDs.push_back( newEntry );
				 }
				 else
				 {
				   AIS_LOG_ALERT("Unhandled request type");
				 }
              }
  		   }
  		 }
           // Check for the CAT EXT tag in Json config file
  		 else if ( std::string::npos != jsonElement.first.find( J1939_CAT_EXT_CONFIG ) )
  		 {
  			 LOG_CONFIG( " Found JSON element '%s' ", jsonElement.first.c_str() );
  			// Extract each node from the Identified JSON element
  			 for(auto& property: jsonElement.second)
  			 {
  				// Construct new entry with the element's name and all default parameters
  				CATEXTIDTableEntry_t newEntry { property.first, 0, 0, 0};
  				LOG_CONFIG( "Parsing element '%s'  '%s' ", property.first.c_str(), newEntry.ParamName.c_str() );

  				if ( !GetJSONParamU32( jsonElement.second, newEntry.ParamName, "CAT EXTID", newEntry.ExtensionID ) )
  				{
  				AIS_LOG_ALERT(" Unable to retrieve EXT ID for parameter '%s'", newEntry.ParamName.c_str() );
  				overallSuccess = false;
  				}
  				else if ( !GetJSONParamU32( jsonElement.second, newEntry.ParamName, "Source Address", newEntry.SourceAddress ) )
  				{
  				AIS_LOG_ALERT( "Unable to retrieve EXT PID source address for parameter '%s'", newEntry.ParamName.c_str() );
  				overallSuccess = false;
  				}
  				else if ( !GetJSONParam( jsonElement.second, newEntry.ParamName, "Request Rate(ms)", newEntry.RequestPeriod_ms ) )
				{
				AIS_LOG_ALERT( "Unable to retrieve EXT PID Request Rate for parameter '%s'", newEntry.ParamName.c_str() );
				overallSuccess = false;
				}
  				else
  				{
  					//extract all optional parameters
  					GetJSONParam( jsonElement.second, newEntry.ParamName, "Priority", newEntry.Priority );
  					GetJSONParamU32( jsonElement.second, newEntry.ParamName, "RestrAdtReadParam", newEntry.RestrictedAdtParamId );
               // GetJSONParam( jsonElement.second, newEntry.ParamName, "Cid", newEntry.Cid );

  					/*Adding CAT EXT ID data to the dlDataMap*/
  					dlParam.SetParameterName( newEntry.ParamName );
  					dlParam.SetParamIdentifierType( DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_CAT_EXT );
  					dlParam.SetParamId( newEntry.ExtensionID );
  					dlParam.SetSid( newEntry.SourceAddress );
					dlParam.SetParameterType( CDL2_VAR_NO_DSI );
					dlParam.SetVarLengthParamType(VarLengthDataLinkParamFactory::CAT_EXT);
					dlParam.SetScaling( 1 );
					dlParam.SetOffset( 0 );

                    if (false == BmiJ1939SCS::AddDataLinkData(dlParam))
                    {
                        overallSuccess = false;
                        break;
                    }

                    LOG_CONFIG("Adding param 0x%X to CAT EXT ID List", newEntry.ExtensionID);
  					m_CatExtIDs.push_back( newEntry );
  				 }
  			 }
  		 }
  		else
  		{
  			AIS_LOG_ALERT(" UnIdentified JSON element ");
  		}

        }
     }

return overallSuccess;
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Task::CreateSclHealthPeerConfigs
// Description     : Extracts all source addresses from the tables and adds to
//                   m_SclHealthPeerConfigTable.
// Return Type     : True if successful and false otherwise
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool BmiJ1939Config::CreateSclHealthPeerConfig( void )
{
   bool returnVal = true;
   for (const auto& param : m_PGBPIDs)
   {
      returnVal &= AddToSclHealthPeerConfig(param.SourceAddress, param.Cid);
   }   
   for (const auto& param : m_ADTPIDs)
   {
      returnVal &= AddToSclHealthPeerConfig(param.SourceAddress, param.Cid);
   
   }
   for (const auto& param : m_PGNs)
   {      
      returnVal &= AddToSclHealthPeerConfig(param.SourceAddress, param.Cid);
   }
   /*
   for (const auto& param : m_ReadPIDs)
   {
      returnVal &= AddToSclHealthPeerConfig(param.SourceAddress, param.Cid);
   }
   for (const auto& param : m_MapPIDs)
   {
      returnVal &= AddToSclHealthPeerConfig(param.SourceAddress, param.Cid);
   }
   */
   // CAT EXT ID not supported
   // for (const auto& param : m_CatExtIDs)
   // {
   //    returnVal &= AddToSclHealthPeerConfig(param.SourceAddress, param.Cid);
   // }
   // for (const auto& param : m_RestrictedParams)
   // {
   //    returnVal &= AddToSclHealthPeerConfig(param.SourceAddress, param.Cid);
   // }

   return returnVal;
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Task::AddToSclHealthPeerConfig
// Description     : Adds the id to the scl health peer config table if it's
//                   not already there.
// Return Type     : True if successful and false otherwise
// Argument [in]   : sourceAddress - source address/id
// Argument [in]   : cid - cid for datalink health
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool BmiJ1939Config::AddToSclHealthPeerConfig( unsigned_32 sourceAddress, uint16_t cid )
{
   auto peerAddress = static_cast<uint_least8_t>(sourceAddress);
   if (sourceAddress > peerAddress )
   {
      AIS_LOG_ERROR("Invalid source address %u", sourceAddress);
      return false;
   }

   // Search for duplicate
   if (std::find_if(m_SclHealthPeerConfigTable.begin(), m_SclHealthPeerConfigTable.end(),
       [sourceAddress] (const SclHealthPeerConfigTable_t& config) { return config.peerConfig.peer_address == sourceAddress; } ) 
       == m_SclHealthPeerConfigTable.end())
   {
      auto gid = static_cast<uint_least32_t>(m_SclHealthPeerConfigTable.size());
      scl_health_j39_peer_config_t peerConfig {
         SCL_HEALTH_J39_PEER_VER_0,          // version
         TRUE,                               // peer_known
         TRUE,                               // peer_by_address
         peerAddress,                        // peer_address
         {},                                 // peer_name
         {},                                 // peer_name_mask
         0,                                  // startup_delay
         30000,                              // eval_delay
         0,                                  // no_comm_timeout
         0,                                  // missing_param_timeout
         gid};                               // desc_gid
         m_SclHealthPeerConfigTable.push_back({std::move(peerConfig), cid});
     m_SidCidTable[sourceAddress] = cid;
     AIS_LOG_DEBUG("Adding source address 0x%02X to SCL Health Peer Config Table", peerAddress);
   }
   return true;
}
