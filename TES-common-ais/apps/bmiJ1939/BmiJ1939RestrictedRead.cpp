////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//
//
//  Abstract: Handle incoming restricted read parameters.
//
////////////////////////////////////////////////////////
#include <unordered_map>

#include <ais/log/AisLogger.h>

#ifndef BMIJ1939RESTRICTEDREAD_H
#include "BmiJ1939RestrictedRead.h"
#endif
#ifndef BMIJ1939EXTIDHDLR_H
#include "BmiJ1939ExtIdHdlr.h"
#endif

std::unordered_map<DataLinkParamInfo::PidKey_t, DataLinkParam> BmiJ1939RestrictedRead::m_restParamDataTable;

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939RestrictedRead::RestrictedParamDataUpdate
// Description     : Function which builds tables for sending Restricted Read Request
// Return Type     : None
// Argument [in]   : DataLinkParam dlParm
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939RestrictedRead::RestrictedParamDataUpdate(const DataLinkParam& dlParm)
{
	DataLinkParamInfo::PidKey_t key;
	if (dlParm.GenerateCdlKey(key, false)) {
	    uint32_t thisParamId = dlParm.GetParamId();

        auto itr = m_restParamDataTable.find(key);
        if (itr != m_restParamDataTable.end()) {
            const auto& dlParmPrev = itr->second;

            if (DataLinkParam::DSI_CODE_OK() == dlParm.GetLastValueDsi()) {
                // The incoming data is good
                if (DataLinkParam::DSI_CODE_OK() != dlParmPrev.GetLastValueDsi()) {
                    // The previous data is bad, new is good, notify of change
                    // There is currently no way to make a distinction between
                    // parameter id type, datalink type, or source address.
                    AIS_LOG_INFO("Restricted Read bad-to-good trigger %X", thisParamId);
                    BmiJ1939ExtIdHdlr::NotifyTriggerParameterChanged(thisParamId);
                }
                // Both the new data and previous data are good, are the different?
                // We only support uint32 data or smaller right now.
                else if (dlParm.GetLastValue<unsigned_32>() != dlParmPrev.GetLastValue<unsigned_32>()) {
                    // Something changed, notify
                    // There is currently no way to make a distinction between
                    // parameter id type, datalink type, or source address.
                    AIS_LOG_INFO("Restricted Read value change trigger %X", thisParamId);
                    BmiJ1939ExtIdHdlr::NotifyTriggerParameterChanged(thisParamId);
                }

                // Update our previous data cache
                m_restParamDataTable[key] = dlParm;
            }
            else {
                // The incoming data is bad, don't do anything
            }
        }
        else {
            // Not found in table, meaning we don't know the previous value
            if (DataLinkParam::DSI_CODE_OK() == dlParm.GetLastValueDsi()) {
                // It went from unknown to something good... add and notify
                m_restParamDataTable[key] = dlParm;

                AIS_LOG_INFO("Restricted Read unknown to good trigger %X", thisParamId);

                // There is currently no way to make a distinction between
                // parameter id type, datalink type, or source address.
                BmiJ1939ExtIdHdlr::NotifyTriggerParameterChanged(thisParamId);
            }
        }
	}
}

