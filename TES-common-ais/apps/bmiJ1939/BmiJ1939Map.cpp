////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939Read
//
// File Name: BmiJ1939Read.cpp
//
//  Abstract: Implementation of the class BmiJ1939Read which will handle rw protocol of J1939
////////////////////////////////////////////////////////
#include <ais/log/AisLogger.h>
#include "BmiJ1939Map.h"
#include "BmiJ1939TaskInit.h"
#include "BmiJ1939SCS.h"
#define TWO_BYTE_DATA 2
#define FOUR_BYTE_DATA 4

struct CDLPIDtable
{
	std::string       ParameterName;          // Name associated with PID
	unsigned_32       ParameterID;            // PID
	std::string       Attributes;             // "signed", "DSI", "swap" are searched for in the string
	bool swapFlag;
} ;
std::map<uint32_t, BmiJ1939Map::MapTable_t> BmiJ1939Map::pMap;
 CDLPIDtable BmiJ1939ReadTableEntry_s1;
 static std::vector<CDLPIDtable> BmiJ1939ReadTableEntry;
bool completeStat= 0;

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Map::MapReqUpdateJ1939
// Description     : Periodic Map Request update function  which sends read request for configured PID's
// Return Type     : None
// Argument [in]   : BmiJ1939Config::CDLPIDTableEntries_t* const pPidTables
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939Map::MapReqUpdateJ1939( BmiJ1939Config::CDLPIDTableEntries_t* const PidTables )
{
    int mapSize = pMap.size();
    uint32_t mapArray[mapSize];

    static int i = 0;

    // once sent request for all PIDs resetting iteration to zero for cycle request
    if (i >= mapSize) {
        i = 0;
    }

    //checking the callback status to send next PID
    if ((!completeStat) && (mapSize)) {
        int k = 0;
        for (const auto& it : pMap) {
            mapArray[k] = it.first;
            ++k;
        }

        const uint32_t parameterId = mapArray[i];
        auto& mapEntry = pMap[parameterId];

        if (mapEntry.request_counter == 0) {
            unsigned_8 result = 0;
            AIS_LOG_DEBUG("J1939_MAP_REQUEST for PID 0x%X  completeStat: %d", parameterId, completeStat);
            if (parameterId == 0x0800) {
                // This is a special ID that needs special access level
                // This is from the PressurePro Tire Pressure Monitoring Receiver
                result = scl_j1939_ma_clnt_trans_by_addr_with_access_lvl(Ph_Link_app, 0,
                        mapEntry.SourceAddress, MA_COMMAND_READ, MA_PTREXT_CDLPID_SPACE, parameterId,
                        1, app_map_complete_cb, app_map_cb, 0, 0xA53C);
                completeStat = 1;
            }
            else {
                result = scl_j1939_ma_client_transaction_by_address(Ph_Link_app, 0,
                        mapEntry.SourceAddress, MA_COMMAND_READ, MA_PTREXT_CDLPID_SPACE, parameterId,
                        mapEntry.DataSize, app_map_complete_cb, app_map_cb, 0);
                completeStat = 1;
            }
            AIS_LOG_INFO(" result : %d completeStat %d", result, completeStat);
        }

        mapEntry.request_counter= (uint32_t)((mapEntry.request_counter + 1) % mapEntry.RequestRateMaxCount);
        mapEntry.timeout_counter++;

        if (mapEntry.timeout_counter >  mapEntry.TimeoutMaxCount) {
            mapEntry.dsi = DataLinkParam::DSI_CODE_NO_RESPONSE();

            // Add this data to be sent over SCS to other apps
            DataLinkParam datalinkParameter;
            datalinkParameter.SetDataLinkType(BmiJ1939Config::GetDataLinkType());
            datalinkParameter.SetParamId(parameterId);
            datalinkParameter.SetSid(mapEntry.SourceAddress);
            if (mapEntry.DataSize > 4 /* Four Bytes */) {
                datalinkParameter.SetVarLengthParamValue(nullptr, 0, pMap[mapArray[i]].dsi);
            }
            else {
                // With an empty data vector SetLastValue() will ignore the first two parameters
                // and only set the DSI
                std::vector<unsigned_8> ParamData; // default constructed
                datalinkParameter.SetLastValue(ParamData, pMap[mapArray[i]].dsi);
            }
            datalinkParameter.SetParamIdentifierType( DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
            datalinkParameter.SetOffset(mapEntry.Offset );
            datalinkParameter.SetScaling(mapEntry.Scaling );
            datalinkParameter.SetUnits(static_cast<DataLinkParamInfo::DlpUnits_t>(mapEntry.Units));
            (void)BmiJ1939SCS::UpdateDataLinkData(datalinkParameter);

            // Start timeout counter over again.
            pMap[mapArray[i]].timeout_counter = 0;
        }

        AIS_LOG_DEBUG(" completeStat: %d Map request counter %d PID %x, DSI CODE %d",completeStat,pMap[mapArray[i]].request_counter,mapArray[i], pMap[mapArray[i]].dsi);

        ++i;
    }
}

void BmiJ1939Map::app_map_complete_cb (
	const scl_j1939_link_t	Ph_link,
	const int_8			Pi8_init_ecm,
	const unsigned_8		Pu8_session,
	const unsigned_8 		Pu8_service,
	const unsigned_8 		Pu8_param_type,
	const unsigned_32 	Pu32_param,
	const unsigned_16 	Pu16_length )
 {

	(void)Pi8_init_ecm;
	(void)Pu16_length;
	(void)Pu32_param;
	(void)Pu8_service;
	(void)Pu8_param_type;
	bool ress;
	ress = scl_j1939_end_ma_client_session(Ph_link,Pu8_session);
	AIS_LOG_NOTICE("Session ended  %d",ress);

}

void BmiJ1939Map::app_ma_client_status_cb(const scl_j1939_link_t  Ph_link,
							 const int_8 Pi8_init_ecm,
							 const unsigned_8  Pu8_session,
							 const unsigned_8  Pu8_status,
							 const unsigned_8  Pu8_service,
							 const unsigned_8  Pu8_param_type,
							 const unsigned_32 Pu32_param,
							 const unsigned_16 Pu16_length,
							 const unsigned_32 Pu32_error_code)
{
	   unsigned_8 result[6];
	   /* touch unused arguments */
	   (void) Pu8_session;
	   (void) Pu8_service;
	   (void) Pu32_param;
	   (void) Pu8_param_type;
	   (void) Pu16_length;


	   result[0] = Pu8_status;
	   result[1] = (unsigned_8)((Pu32_error_code >> 24) & 0xFF);
	   result[2] = (unsigned_8)((Pu32_error_code >> 16) & 0xFF);
	   result[3] = (unsigned_8)((Pu32_error_code >> 8) & 0xFF);
	   result[4] = (unsigned_8)(Pu32_error_code & 0xFF);
	   result[5] = Pu8_session;
	   AIS_LOG_INFO("Pu8_status %d  completeStat %d",Pu8_status,completeStat);
	   switch(Pu8_status)
	   {
	      case MA_RESPONSE_STATUS_SESSION_CLOSED:
	      {
	         scl_j1939_que_tx_msg_by_address(Ph_link,
	                                   0x00CD00,
	                                   6,
	                                   0xFA, // Broadcast
	                                   Pi8_init_ecm,
	                                   result,
	                                   sizeof(result));
	         completeStat = 0;
	         AIS_LOG_INFO("Session Closed");
	      }
	      break;
	      case MA_RESPONSE_STATUS_OP_COMPLETED:
	      case MA_RESPONSE_STATUS_OP_FAILED:
	      {
	         scl_j1939_que_tx_msg_by_address(Ph_link,
	                                   0x00CD00,
	                                   6,
	                                   0xFA, // Broadcast
	                                   Pi8_init_ecm,
	                                   result,
	                                   sizeof(result));
	         completeStat = 1;
	         AIS_LOG_INFO("Session Completed");
	      }
	      break;
	      case MA_RESPONSE_STATUS_INTERNAL_TIMEOUT:
	      {

	         scl_j1939_que_tx_msg_by_address(Ph_link,
	                                   0x00CD00,
	                                   6,
	                                   0xFA, // Broadcast
	                                   Pi8_init_ecm,
	                                   result,
	                                   sizeof(result));
	         completeStat = 1;
	      }
	      break;
	      case MA_RESPONSE_STATUS_PROCEED:
	      break;
	      default:
	      {
	         scl_j1939_que_tx_msg_by_address(Ph_link,
	                                   0x00CD00,
	                                   6,
	                                   0xFA, // Broadcast
	                                   Pi8_init_ecm,
	                                   result,
	                                   sizeof(result));
	         completeStat = 1;
	      }
	      break;
	   }
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Map::app_map_cb
// Description     : Map RX handler for a received J1939 map protocol message. Parses
//                   the message and adds to data to be sent over SCS
// Return Type     : None
// Argument [in]   : unsigned_8*       pData  - pointer to the data
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
unsigned_32 BmiJ1939Map::app_map_cb(
		const scl_j1939_link_t  link,
		const int_8       Pi8_init_ecm,
		const unsigned_8  Pu8_session,
		const unsigned_8  Pu8_param_type,
		const unsigned_32    Pu32_param,
		const unsigned_8  Pu8_service,
		const unsigned_16    Pu16_length,		/* parameter data length */
		unsigned_16*      Ppu16_data_size,		/* parameter data size */
		unsigned_8*       pData )				/* pointer to parameter data in message */
{

    unsigned_32 Sid = 0;                // Source Address
    VarLengthDataLinkParamPool::VarLengthParamType varLengthParamType = VarLengthDataLinkParamPool::NOT_APPLICABLE; // Variable length
    unsigned_8 Units = 0;               // Units
    real_64 Scaling = 0;        // Parameter scaling factor
    real_64 Offset = 0;     // Parameter offset
    unsigned_8 DataSize = 0;            // Data Size
    bool pidFound = false;
    uint_least16_t dsiCode = DataLinkParam::DSI_CODE_PARAM_NOT_AVAIL();

    /* touch unused arguments */
    (void)link;
    (void)Pi8_init_ecm;
    (void)Pu8_session;
    (void)Pu8_param_type;
    (void)Pu16_length;

    std::vector<unsigned_8> ParamData;

    auto it = pMap.find(Pu32_param);
    if (it != pMap.end()) {
        auto& mapItem = it->second;
        if (mapItem.DataSize == *Ppu16_data_size) {
            mapItem.timeout_counter = 0;
            Sid = mapItem.SourceAddress;
            varLengthParamType = static_cast<VarLengthDataLinkParamPool::VarLengthParamType>(mapItem.VarLengthDataType);
            Scaling = mapItem.Scaling;
            Offset = mapItem.Offset;
            Units = mapItem.Units;
            DataSize = mapItem.DataSize;
            pidFound = true;
            mapItem.dsi = DataLinkParam::DSI_CODE_OK();
            dsiCode = mapItem.dsi;
        }
        else {
            std::stringstream hexData;
            for (int i = 0; i < *Ppu16_data_size; ++i) {
                hexData << std::setfill ('0') << std::setw(sizeof(*pData) * 2) << std::uppercase << std::hex << static_cast<unsigned>(pData[i]);
            }
            AIS_LOG_ERROR("PID %X received with invalid Ppu16_data_size %u, pData 0x%s", Pu32_param, *Ppu16_data_size, hexData.str().c_str());
        }
    }

    if (pidFound && (Pu8_service == MA_COMMAND_READ)) {
        // Add this data to be sent over SCS to other apps
        DataLinkParam datalinkParameter;
        datalinkParameter.SetDataLinkType(BmiJ1939Config::GetDataLinkType());

        if (nullptr != pData) {
            switch (DataSize) {
            case sizeof(unsigned_8): {
                unsigned_8 tempValue;
                OEL_UNPACK_BE_8_NO_INCR(pData, tempValue) ;
                ParamData.assign(reinterpret_cast<unsigned_8*>(&tempValue),
                        reinterpret_cast<unsigned_8*>(&tempValue) + sizeof(tempValue)); //save temp value into ParamData
                break;
            }
            case sizeof(unsigned_16): {
                unsigned_16 tempValue;
                OEL_UNPACK_BE_16_NO_INCR(pData, tempValue );
                ParamData.assign(reinterpret_cast<unsigned_8*>(&tempValue),
                        reinterpret_cast<unsigned_8*>(&tempValue) + sizeof(tempValue)); //save temp value into ParamData
                break;
            }
            case sizeof(unsigned_32): {
                unsigned_32 tempValue;
                OEL_UNPACK_BE_32_NO_INCR(pData, tempValue);
                ParamData.assign(reinterpret_cast<unsigned_8*>(&tempValue),
                        reinterpret_cast<unsigned_8*>(&tempValue) + sizeof(tempValue)); //save temp value into ParamData
                break;
            }
            default: { /*check for Variable length data*/
                break;
            }
            }
        }

        datalinkParameter.SetParamId(Pu32_param);
        datalinkParameter.SetSid(Sid);

        if (VarLengthDataLinkParamPool::NOT_APPLICABLE == varLengthParamType) {
            findSwapStat(datalinkParameter.GetParamId(), ParamData);
            datalinkParameter.SetLastValue(ParamData, dsiCode);
        }
        else if (VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER == varLengthParamType) {
            // for special pid like F5D9 swapping is needed for normal data
            if (dsiCode == DataLinkParam::DSI_CODE_OK()) {
                datalinkParameter.SetLastValue(ParamData, dsiCode);
            }
        }
        else {
            // For variable length parameter last value is set by SetVarLengthParamValue
            datalinkParameter.SetVarLengthParamType(varLengthParamType);
            if (DataSize > 0) {
                // The MAP library already advances past the data length byte, so we don't need to advance again.
                datalinkParameter.SetVarLengthParamValue(pData, DataSize, dsiCode);
            }
            else {
                datalinkParameter.SetVarLengthParamValue(nullptr, 0, dsiCode);
            }
        }

        /*
        if (dsiCode == DataLinkParam::DSI_CODE_OK()) {
            AIS_LOG_DEBUG(" pid : %x, dsiCode %x, DataSize : %d", datalinkParameter.GetParamId(), dsiCode, DataSize);
            if (VarLengthDataLinkParamPool::NOT_APPLICABLE == varLengthParamType ||
                    VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER == varLengthParamType) {
                AIS_LOG_DEBUG("pidData  :   %x   %d", datalinkParameter.GetLastValue<unsigned_32>(), datalinkParameter.GetLastValue<unsigned_32>());
            }
            else {
                const unsigned_8* varParamBlock = datalinkParameter.GetVarParamBlock();
                const unsigned_8 varParamBlockSize = datalinkParameter.GetVarParamBlockLength();
                for (int i = 0; i < varParamBlockSize; ++i) {
                    AIS_LOG_DEBUG("pidData[%2d]    %x", i, varParamBlock[i]);
                }
            }
        }
        */

        datalinkParameter.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
        datalinkParameter.SetOffset(Offset);
        datalinkParameter.SetScaling(Scaling);
        datalinkParameter.SetUnits(static_cast<DataLinkParamInfo::DlpUnits_t>(Units));

        (void)BmiJ1939SCS::UpdateDataLinkData(datalinkParameter);

        return (MA_TRANS_ERROR_NONE);
    }
    else if (Pu8_service == MA_COMMAND_WRITE) {
        return (MA_TRANS_ERROR_NONE);
    }

    return (MA_TRANS_ERROR_NONE);
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Map::MapInitJ1939
// Description     : Initializes CAT DataLink PID for J1939 Map protocol
// Return Type     : None
// Argument [in]   : CDLPIDTableEntries_t* const pPidTables - Reference to the CDL PID table
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939Map::MapInitJ1939(BmiJ1939Config::CDLPIDTableEntries_t* const pPidTables,const int_16 taskPeriod_ms)
{
	AIS_LOG_INFO(" Initializing J1939 Map PID's ");
	scl_j1939_set_ma_client_configuration( Ph_Link_app, app_ma_client_status_cb, 10 );
	scl_j1939_ma_client_enable_ecm(Ph_Link_app,0);

	for ( auto &jsonPidParam : *pPidTables )
	{
		if(J1939_MAP_REQUEST == jsonPidParam.RequestType)
		{
			MapTable_t MapTable;
			MapTable.SourceAddress = jsonPidParam.SourceAddress;
			MapTable.RequestRateMaxCount = (uint32_t)(jsonPidParam.RequestRate_ms/taskPeriod_ms);
			MapTable.Scaling = jsonPidParam.Scaling;
			MapTable.Offset = jsonPidParam.Offset;
			MapTable.Units = jsonPidParam.Units;
			MapTable.DataSize = jsonPidParam.DataSize;
			MapTable.TimeoutMaxCount = (uint32_t)(jsonPidParam.Timeout_ms/taskPeriod_ms);
			MapTable.VarLengthDataType = jsonPidParam.VarLengthDataType;
			MapTable.request_counter = 0;
			MapTable.timeout_counter = MapTable.TimeoutMaxCount;
			MapTable.dsi = DataLinkParam::DSI_CODE_CONDITIONS_NOT_MET();
			pMap[jsonPidParam.ParameterID]=MapTable;

			BmiJ1939ReadTableEntry_s1.ParameterName = jsonPidParam.ParameterName;
			BmiJ1939ReadTableEntry_s1.ParameterID = jsonPidParam.ParameterID;
			BmiJ1939ReadTableEntry_s1.Attributes = jsonPidParam.Attributes;

			size_t found;
			found = BmiJ1939ReadTableEntry_s1.Attributes.find("swap bytes");
			if (found != std::string::npos)
			{
				BmiJ1939ReadTableEntry_s1.swapFlag = true;
			}
			else
			{
				BmiJ1939ReadTableEntry_s1.swapFlag = false;
			}
			BmiJ1939ReadTableEntry.push_back(BmiJ1939ReadTableEntry_s1);

		}
	}
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Map::findSwapStat
// Description     : swap the bytes if it is mentioned in json file before publish
// Return Type     : None
// Argument [in]   : uint32_t pid(PID),vector<uint8_t> &paramData(PIDs data to swap)
// Argument [out]  : paramData as reference
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939Map::findSwapStat(uint32_t pid, std::vector<uint8_t> &paramData)
{
	for(auto it = BmiJ1939ReadTableEntry.begin(); it != BmiJ1939ReadTableEntry.end(); ++it)
	{
		if((pid == it->ParameterID ) && (it->swapFlag == true ))
		{
			if(paramData.size() == TWO_BYTE_DATA)
			{
				std::swap(paramData[0], paramData[1]);
			}
			else if(paramData.size() == FOUR_BYTE_DATA)
			{
                std::swap(paramData[0], paramData[3]);
                std::swap(paramData[1], paramData[2]);
			}

		}
	}
}

