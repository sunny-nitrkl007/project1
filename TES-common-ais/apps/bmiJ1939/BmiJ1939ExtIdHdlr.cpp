////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939ExtIdHdlr
//
// File Name: BmiJ1939ExtIdHdlr.cpp
//
//  Abstract: Declarations for the class that handles
//            J1939 Extension ID handlers in the application
//
////////////////////////////////////////////////////////
#include <mutex>
#include <chrono>
#include <vector>
#include <unordered_map>

#include <oel_pack.h>

#include <ais/log/AisLogger.h>

#include "BmiJ1939TaskInit.h"

#include "BmiJ1939ExtIdHdlr.h"

std::vector<SCL_J1939_CAT_PPGN_ID_HDLR_t> BmiJ1939ExtIdHdlr::J1939ExtIdRxTable;

std::unordered_map<uint32_t, BmiJ1939ExtIdHdlr::ExtIdTable_t> BmiJ1939ExtIdHdlr::pCatExtId;

static bool somethingPending = false;

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939ExtIdHdlr::BuildCatExtIdTables
// Description     : Function which builds tables for CAT EXTID's
// Return Type     : None
// Argument [in]   : BmiJ1939Config::EXTIDTableEntries_t* const pAppExtIdTables
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939ExtIdHdlr::BuildCatExtIdTables(const BmiJ1939Config::EXTIDTableEntries_t* pExtIdTables)
{
    if (nullptr == pExtIdTables) {
        AIS_LOG_ERROR("pExtIdTables is null!");
        return;
    }

	for (const auto& jsonExtIdBlock : *pExtIdTables) {
		AIS_LOG_INFO("jsonExtIdBlock.ParamName: %s", jsonExtIdBlock.ParamName.c_str());
		AIS_LOG_INFO("jsonExtIdBlock.ExtensionID: 0x%X", jsonExtIdBlock.ExtensionID);
		AIS_LOG_INFO("jsonExtIdBlock.SourceAddress: 0x%X", jsonExtIdBlock.SourceAddress);
		AIS_LOG_INFO("jsonExtIdBlock.Priority: %d", jsonExtIdBlock.Priority);
		AIS_LOG_INFO("jsonExtIdBlock.RequestPeriod_ms: %u",jsonExtIdBlock.RequestPeriod_ms);

		// Build the EXT ID Rx table
		SCL_J1939_CAT_PPGN_ID_HDLR_t catExtIdRxEntry = {
				static_cast<unsigned_16>(jsonExtIdBlock.ExtensionID), // Command to match to allow handler to execute
				0,													  // CAT Ext-ID to match to allow handler to execute
				(scl_j1939_rx_parse_func_t*)&CatExtIdRxHandler,       // Function that unpacks the data from the J1939 component
				nullptr,
				nullptr,
				nullptr
		};

		J1939ExtIdRxTable.push_back( catExtIdRxEntry  );

		{ // Create the extension id data
		    auto timeout = std::chrono::milliseconds(jsonExtIdBlock.RequestPeriod_ms);

		    // Limit the timeout period
	        // If the timeout period is too short, we have no chance of catching the parameter
	        if (timeout < std::chrono::milliseconds(2000)) {
	            timeout = std::chrono::milliseconds(2000);
	        }
	        // If the timeout period is too long, it will block other requests too long while this is pending.
	        else if (timeout > std::chrono::milliseconds(10000)) {
	            timeout = std::chrono::milliseconds(10000);
	        }

	        /*
	         * We have to construct the ExtIdTable_t object in place instead of copy or move
	         * because there is a mutex member in the class which is not copyable or moveable.
	         * For this, we use piecewise pair construction so that both 'first' and 'second'
	         * members of the 'pair' are constructed in place with the arguments forwarded
	         * as tuples.
	         */
	        pCatExtId.emplace(std::piecewise_construct,
	                // Arguments to the constructor for the 'key'
	                std::forward_as_tuple(jsonExtIdBlock.ExtensionID),
	                // Arguments to the constructor for the 'value'
	                std::forward_as_tuple(jsonExtIdBlock.SourceAddress,
	                        jsonExtIdBlock.Priority,
	                        std::chrono::milliseconds(jsonExtIdBlock.RequestPeriod_ms),
	                        timeout,
	                        jsonExtIdBlock.RestrictedAdtParamId));
		}
	}
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939ExtIdHdlr::ExtIdTimeoutEventUpdate
// Description     : Function which handles the timeout event for all the requested CAT Ext Id's
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939ExtIdHdlr::ExtIdTimeoutEventUpdate()
{
    bool nothingPending = true;
    auto now = std::chrono::steady_clock::now();

    for (auto& extIdItem : pCatExtId) {
	    BmiJ1939ExtIdHdlr::ExtIdTable_t& extIdData = extIdItem.second;
	    std::lock_guard<std::mutex> lck(extIdData.mtx);

	    if (extIdData.pending) {
	        nothingPending = false;

	        // This is the extension id that is pending, see if it has timed out
	        auto timeSinceLastRequest = std::chrono::duration_cast<std::chrono::milliseconds>(now - extIdData.lastRequestTime);

	        if (timeSinceLastRequest > extIdData.timeoutPeriod) {
	            somethingPending = false;

	            AIS_LOG_ERROR("CAT EXT ID %X timed out.", extIdItem.first);

	            DataLinkParam dlParameter;
                dlParameter.SetDataLinkType(BmiJ1939Config::GetDataLinkType());
                dlParameter.SetSid(extIdData.sourceAddress);
	            dlParameter.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_CAT_EXT);
	            dlParameter.SetParamId(extIdItem.first);
                dlParameter.SetVarLengthParamType(VarLengthDataLinkParamPool::CAT_EXT);
	            dlParameter.SetVarLengthParamValue(nullptr, 0, DataLinkParam::DSI_CODE_NO_RESPONSE());
	            BmiJ1939SCS::UpdateDataLinkData(dlParameter);

	            extIdData.pending = false;
	        }
	    }
    }

    // This is just a fail-safe to make sure we don't accidentally block forever.
    if (nothingPending) {
        somethingPending = false;
    }
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939ExtIdHdlr::SendCatExtIdRequest
// Description     : Function which sends read request for CAT EXTID's
// Return Type     : None
// Argument [in]   : BmiJ1939Config::EXTIDTableEntries_t* const pAppExtIdTables
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939ExtIdHdlr::SendCatExtIdRequest(const BmiJ1939Config::EXTIDTableEntries_t* pExtIdTables)
{
    auto now = std::chrono::steady_clock::now();
    uint32_t idToSend = 0;

    // If there is nothing pending, see if we need to start a new request.
    if (!somethingPending) {
        std::chrono::steady_clock::time_point idToSendLastRequestTime = std::chrono::steady_clock::time_point::max();

        // For each configured extension id
        for (auto& extIdItem : pCatExtId) {
            ExtIdTable_t& extIdData = extIdItem.second;
            std::lock_guard<std::mutex> lck(extIdData.mtx);
            bool wantToRequest = false;

            if (extIdData.requestNow) {
                // It was asynchronously triggered to request
                wantToRequest = true;
            }
            else if (extIdData.requestPeriod > std::chrono::milliseconds(0)) {
                // Overflow occurs with std::chrono::steady_clock::now() - std::chrono::steady_clock::time_point::min()
                // since lastRequestTime is initialized to min(), we have to avoid now() - lastRequestTime.
                if (now >= (extIdData.lastRequestTime + extIdData.requestPeriod)) {
                    // It is periodically triggered to request
                    wantToRequest = true;
                }
            }

            if (wantToRequest) {
                AIS_LOG_INFO("CAT EXT ID %X Read request wanted.", extIdItem.first);

                // It's time to request this one, is it the oldest?
                if (extIdData.lastRequestTime < idToSendLastRequestTime) {
                    idToSend = extIdItem.first;
                    idToSendLastRequestTime = extIdData.lastRequestTime;
                }
            }
        }
    }

    // Is there anything to send?
    auto itExtIdItem = pCatExtId.find(idToSend);
    if (itExtIdItem != pCatExtId.end()) {
        uint32_t extensionId = itExtIdItem->first;
        ExtIdTable_t& extIdData = itExtIdItem->second;
        std::lock_guard<std::mutex> lck(extIdData.mtx);
        bool messageBuilt = false;
        uint8_t messageBuffer[] = { 0x80 /* Read Request */, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

        if (extensionId > 0xFFFF) {
            // Invalid Extension Id
            AIS_LOG_ERROR("Invalid length for CAT EXT ID: %X", extensionId);

            // Disable it
            extIdData.requestPeriod = std::chrono::milliseconds(0);
            extIdData.requestNow = false;
        }
        else if (extensionId > 0xFF) {
            // Two Byte
            OEL_PACK_BE_16_NO_INCR(&messageBuffer[1], extensionId);
            messageBuilt = true;
        }
        else {
            // One Byte
            OEL_PACK_BE_8_NO_INCR(&messageBuffer[1], extensionId);
            messageBuilt = true;
        }

        if (messageBuilt) {
            if (scl_j1939_que_tx_msg_by_address(Ph_Link_app,
                    0xEF00,
                    extIdData.priority,
                    extIdData.sourceAddress,
                    0,
                    messageBuffer,
                    sizeof(messageBuffer)/sizeof(messageBuffer[0]))) {
                somethingPending = true;
                extIdData.pending = true;
                extIdData.lastRequestTime = now;
            }
            else {
                AIS_LOG_ERROR("Failed to send Read Request for CAT EXT ID: %X", extensionId);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939ExtIdHdlr::CatExtIdRxHandler
// Description     : CAT EXT ID RX handler for a received J1939 message. Parses
//                   the message and adds to data to be sent over SCS
// Return Type     : None
// Argument [in]   : const scl_j1939_mbuf_hdr_t* mbuf_ptr - Pointer to the
//                      message buffer
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939ExtIdHdlr::CatExtIdRxHandler(scl_j1939_mbuf_hdr_t* mbuf_ptr)
{
	if (nullptr != mbuf_ptr) {
		// Get the attributes from mbuf_ptr
		const auto dataSrc = scl_j1939_get_mbuf_sa(mbuf_ptr);

		unsigned_16 extensionId;
		scl_j1939_get_cat_ext_from_mbuf(mbuf_ptr, &extensionId, 0);

		auto itExtIdItem = pCatExtId.find(extensionId);
		if (itExtIdItem != pCatExtId.end()) {
		    ExtIdTable_t& extIdData = itExtIdItem->second;
		    std::lock_guard<std::mutex> lck(extIdData.mtx);
		    if (dataSrc == extIdData.sourceAddress) {
		        // We are interested in this.
		        extIdData.requestNow = false;
		        if (extIdData.pending) {
                    extIdData.pending = false;
                    somethingPending = false;
		        }
		    }
		}

        const auto dataLen = scl_j1939_get_mbuf_len(mbuf_ptr);
        if (dataLen > 0) {
            // Get the data out.
            unsigned_8 dataBuffer[dataLen];
            scl_j1939_get_data_from_mbuf(mbuf_ptr, dataBuffer, dataLen, 0);

            // Build the datalink parameter and update
            DataLinkParam dlParameter;
            dlParameter.SetDataLinkType(BmiJ1939Config::GetDataLinkType());
            dlParameter.SetSid(dataSrc);
            dlParameter.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_CAT_EXT);
            dlParameter.SetParamId(extensionId);
            dlParameter.SetVarLengthParamType(VarLengthDataLinkParamPool::CAT_EXT);
            dlParameter.SetVarLengthParamValue(dataBuffer, dataLen, DataLinkParam::DSI_CODE_OK());
            BmiJ1939SCS::UpdateDataLinkData(dlParameter);
        }
    }
}

void BmiJ1939ExtIdHdlr::NotifyTriggerParameterChanged(uint32_t triggerParameterId)
{
    // Trigger any parameter that needs it
    for (auto& extIdItem : pCatExtId) {
        ExtIdTable_t& extIdData = extIdItem.second;
        std::lock_guard<std::mutex> lck(extIdData.mtx);
        if (triggerParameterId == extIdData.triggerParameterId) {
            extIdData.requestNow = true;
        }
    }
}

