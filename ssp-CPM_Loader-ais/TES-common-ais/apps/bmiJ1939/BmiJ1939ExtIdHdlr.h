////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939ExtIdHdlr
//
// File Name: BmiJ1939ExtIdHdlr.h
//
//  Abstract: Implementations for the class that handles
//            J1939 Extension ID handlers in the application
//
////////////////////////////////////////////////////////
#ifndef BMIJ1939EXTIDHDLR_H
#define BMIJ1939EXTIDHDLR_H

#include <mutex>
#include <chrono>
#include <vector>
#include <unordered_map>

#include "BmiJ1939Config.h"
#include "BmiJ1939SCS.h"

#include <scl_j1939.h>
#include <std_types.h>


class BmiJ1939ExtIdHdlr
{
public:
	BmiJ1939ExtIdHdlr() = delete;
   
    static std::vector<SCL_J1939_CAT_PPGN_ID_HDLR_t> J1939ExtIdRxTable;

	static void SendCatExtIdRequest(const BmiJ1939Config::EXTIDTableEntries_t* pExtIdTables);
	static void CatExtIdRxHandler(scl_j1939_mbuf_hdr_t* mbuf_ptr);
	static void BuildCatExtIdTables(const BmiJ1939Config::EXTIDTableEntries_t* pExtIdTables);
	static void ExtIdTimeoutEventUpdate();
	static void NotifyTriggerParameterChanged(uint32_t triggerParameterId);


protected:

private:
    //static BmiJ1939Config::EXTIDTableEntries_t*    m_pAppExtIdCfgTbl;

    struct ExtIdTable_t {
        ExtIdTable_t(uint32_t sourceAddress_,
                uint8_t priority_,
                std::chrono::milliseconds requestPeriod_,
                std::chrono::milliseconds timeoutPeriod_,
                uint32_t triggerParameterId_) :
            mtx(),
            sourceAddress(sourceAddress_),
            priority(priority_),
            lastRequestTime(std::chrono::steady_clock::time_point::min()),
            requestPeriod(requestPeriod_),
            triggerParameterId(triggerParameterId_),
            timeoutPeriod(timeoutPeriod_),
            pending(false),
            requestNow(false) {}

        ExtIdTable_t() : ExtIdTable_t(0, 0, std::chrono::milliseconds(0), std::chrono::milliseconds(0), 0) {}

        std::mutex mtx;
        uint32_t sourceAddress;
        uint8_t priority;
        std::chrono::steady_clock::time_point lastRequestTime;
        std::chrono::milliseconds requestPeriod;
        uint32_t triggerParameterId;
        std::chrono::milliseconds timeoutPeriod;
        bool pending;
        bool requestNow;
    };

	static std::unordered_map<uint32_t, ExtIdTable_t> pCatExtId;

};

#endif //BMIJ1939EXTIDHDLR_H
