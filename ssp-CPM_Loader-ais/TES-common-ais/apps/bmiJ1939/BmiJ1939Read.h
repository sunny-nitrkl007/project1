////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939Read
//
// File Name: BmiJ1939Read.h
//
//  Abstract: Declaration for the class that registers for
//             J1939 Read protocol, includes:
//             - Read Request handling
//             - client Connection handler
//
////////////////////////////////////////////////////////

#ifndef BMIJ1939READ_H_
#define BMIJ1939READ_H_
#include <string.h>
#include <vector>
#include "BmiJ1939Config.h"
using namespace std;
extern "C"
{
#include <cdl2_proto.h>
#include <scl_j1939.h>
#include <scl_rw_j1939.h>
#include <scl_j1939_proto.h>
#include <std_types.h>
#include <cdl2_gen_struct.h>
#include <cdl2_gen_proto.h>
}

class BmiJ1939Read
{
public:
	BmiJ1939Read( void ) { }
	virtual ~BmiJ1939Read( void ) { }

	// Callback function for J1939 rx handler for read request
	static cdl2_con_rx_hdlr_t J1939ClientRxHandler;
	static void ReadReqInitJ1939( BmiJ1939Config::CDLPIDTableEntries_t* const pPidTables,const int_16 taskPeriod_ms);
	static void ReadReqUpdateJ1939( BmiJ1939Config::CDLPIDTableEntries_t* const pPidTables );
	static void SwapJ1939Read(uint32_t,unsigned_8,unsigned_32 &);

private:
	typedef struct ReadPollTable_s
	{
	    unsigned_32     SourceAddress;          // J1939 address, refer to https://datalinks.ecorp.cat.com/J1939/SourceAddresses/
	    unsigned_32     RequestRateMaxCount;    // Request maximum count is calculated based on configured request rate to send the request PID
	    unsigned_32     request_counter;        // incremental counter is used to request PID at configured rate
	}ReadPollTable_t;	
	static std::map<uint32_t, ReadPollTable_t> pReadPoll;
};

#endif // BMIJ1939READ_H_
