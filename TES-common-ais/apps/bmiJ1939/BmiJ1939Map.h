////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939Map
//
// File Name: BmiJ1939Map.h
//
//  Abstract: Declaration for the class that registers for
//             J1939 Read protocol, includes:
//             - Read Request handling
//             - client Connection handler
//
////////////////////////////////////////////////////////

#ifndef BMIJ1939MAP_H_
#define BMIJ1939MAP_H_
#include <string.h>
#include "BmiJ1939Config.h"

extern "C"
{
#include <scl_j1939_struct.h>
#include <cdl2_proto.h>
#include <scl_j1939.h>
#include <scl_j1939_proto.h>

}


class BmiJ1939Map
{
public:
	BmiJ1939Map( void ) { }
	virtual ~BmiJ1939Map( void ) { }
	static unsigned_32 app_map_cb (	const scl_j1939_link_t	link,
		const int_8			Pi8_init_ecm,
		const unsigned_8		Pu8_session,
		const unsigned_8 		Pu8_param_type,
		const unsigned_32 	Pu32_param,
		const unsigned_8 		Pu8_service,
		const unsigned_16 	Pu16_length,
		unsigned_16*		Ppu16_data_size,
		unsigned_8*			pData );
	static void app_map_complete_cb (
		const scl_j1939_link_t	link,
		const int_8			Pi8_init_ecm,
		const unsigned_8		Pu8_session,
		const unsigned_8 		Pu8_service,
		const unsigned_8 		Pu8_param_type,
		const unsigned_32 	Pu32_param,
		const unsigned_16 	Pu16_length );
	static void app_ma_client_status_cb(const scl_j1939_link_t  Ph_link,
								 const int_8 Pi8_init_ecm,
								 const unsigned_8  Pu8_session,
								 const unsigned_8  Pu8_status,
								 const unsigned_8  Pu8_service,
								 const unsigned_8  Pu8_param_type,
								 const unsigned_32 Pu32_param,
								 const unsigned_16 Pu16_length,
								 const unsigned_32 Pu32_error_code);

	static void MapInitJ1939(BmiJ1939Config::CDLPIDTableEntries_t* const pPidTables, const int_16 taskPeriod_ms );
	static void MapReqUpdateJ1939( BmiJ1939Config::CDLPIDTableEntries_t* const PidTables );
	static void findSwapStat(uint32_t,std::vector<uint8_t> &);
private:
	typedef struct MapTableEntry_s
	{
	    unsigned_8      DataSize;               // Size of the data in bytes
	    unsigned_32     SourceAddress;          // J1939 address, refer to https://datalinks.ecorp.cat.com/J1939/SourceAddresses/
	    unsigned_32     RequestRateMaxCount;    // Request maximum count is calculated based on configured request rate to send the request PID
	    float           Scaling;                // Parameter scaling factor
	    float           Offset;                 // Parameter offset
	    unsigned_8      Units;                  // Parameter units (as per DataLinkParam::DlpUnits_t)
	    unsigned_32     TimeoutMaxCount;        // Expected time frame to receive this PID
	    unsigned_8	    VarLengthDataType;      // Variable length parameter type
	    unsigned_32     request_counter;        // incremental counter is used to request PID at configured rate
	    unsigned_32     timeout_counter;        // incremental counter is used to find the timeout happened or not at configured rate
	    unsigned_16     dsi;					// which has dsi status
	    unsigned_8      ParameterType;          // used for automatic data status detection(From file  cdl2_struct.h)
	}MapTable_t;
	static std::map<uint32_t, MapTable_t> pMap;
};

#endif // BMIJ1939READ_H_
