////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939DataHandlers
//
// File Name: BmiJ1939DataHandlers.cpp
//
//  Abstract: Implementation of the class that handles
//            incoming data over J1939 for the OEL task
//            (scl_j1939_control_task)
//
////////////////////////////////////////////////////////

extern "C"
{
#include <oel_pack.h>
}
#include <ais/log/AisLogger.h>
#include "BmiJ1939DataHandlers.h"
#include "BmiJ1939Config.h"
#include "BmiJ1939TaskInit.h"

#ifndef BMIJ1939RESTRICTEDREAD_H
#include "BmiJ1939RestrictedRead.h"
#endif

// The index of each item in the following array must match "Handler Index" in the JSON file
const scl_j1939_rx_mpfn_parser_t *BmiJ1939DataHandlers::m_pgnHandlers[] = {
	BmiJ1939PGNDefault,		// Index 0
	scl_j1939_cat_ppgn_hdlr // Index 1
};

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939DataHandlers::GetNumPgnHandlers
// Description     : Returns the number of PGN handlers pointed to by m_pgnHandlers
// Return Type     : unsigned_16 - Number of handlers
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
unsigned_16 BmiJ1939DataHandlers::GetNumPgnHandlers(void)
{
	return (sizeof(m_pgnHandlers) / sizeof(m_pgnHandlers[0]));
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939DataHandlers::BmiJ1939PIDDefault
// Description     : Default handler for a received PGB over J1939 message. Parses
//                   the message and adds to data to be sent over SCS
// Return Type     : int_least16_t - Not used anywhere, so always 0
// Argument [in]   : uint_least8_t* pData - Pointer to the received data,
//                   uint_least8_t dataLen - Data length in bytes,
//                   void* pRxContext - Pointer to the callback context,
//                   uint_least16_t dsiCode - Data Status Indicator.
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
int_least16_t BmiJ1939DataHandlers::BmiJ1939PIDDefault(uint_least8_t *pData, 
														uint_least8_t dataLen, 
														void *pRxContext, 
														uint_least16_t dsiCode)
{

	AIS_LOG_INFO(" PID handler: DSI 0x%X.", dsiCode);

	BmiJ1939Config::CDLPIDTableEntry_t *pContext = static_cast<BmiJ1939Config::CDLPIDTableEntry_t *>(pRxContext);

	/*Update the DSI status received to DSITable for diagnostics*/
	//BmiJ1939TaskInit::SetDsiTableData(pContext, dsiCode);

	if (0 != dsiCode)
	{
		AIS_LOG_NOTICE(" PID 0x%X from 0x%02X with DSI 0x%X",
				   pContext->ParameterID, pContext->SourceAddress, dsiCode);
	}

	// Add this data to be sent over SCS to other apps
	std::vector<unsigned_8> ParamData;
	DataLinkParam datalinkParameter;
	datalinkParameter.SetDataLinkType(BmiJ1939Config::GetDataLinkType());
	VarLengthDataLinkParamPool::VarLengthParamType varLengthParamType = static_cast<VarLengthDataLinkParamPool::VarLengthParamType>(pContext->VarLengthDataType);

	if (nullptr != pData)
	{
		switch (dataLen)
		{
		case sizeof(unsigned_8):
		{
			unsigned_8 tempValue;
			OEL_UNPACK_BE_8_NO_INCR(pData, tempValue);
			ParamData.assign(reinterpret_cast<unsigned_8 *>(&tempValue),
							 reinterpret_cast<unsigned_8 *>(&tempValue) + sizeof(tempValue)); //save temp value into ParamData
			break;
		}
		case sizeof(unsigned_16):
		{
			unsigned_16 tempValue;
			OEL_UNPACK_BE_16_NO_INCR(pData, tempValue);
			ParamData.assign(reinterpret_cast<unsigned_8 *>(&tempValue),
							 reinterpret_cast<unsigned_8 *>(&tempValue) + sizeof(tempValue)); //save temp value into ParamData
			break;
		}
		case sizeof(unsigned_32):
		{
			unsigned_32 tempValue;
			OEL_UNPACK_BE_32_NO_INCR(pData, tempValue);
			ParamData.assign(reinterpret_cast<unsigned_8 *>(&tempValue),
							 reinterpret_cast<unsigned_8 *>(&tempValue) + sizeof(tempValue)); //save temp value into ParamData
			break;
		}
		default: /*check for Variable length data*/
		{
			break;
		}
		}
	}

	datalinkParameter.SetParamId(pContext->ParameterID);
	datalinkParameter.SetSid(pContext->SourceAddress);

	if (VarLengthDataLinkParamPool::NOT_APPLICABLE == varLengthParamType)
	{
		datalinkParameter.SetLastValue(ParamData, dsiCode);
	}
	else if (VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER == varLengthParamType)
	{
		// for special pid like F5D9 swapping is needed for normal data
		if (dsiCode == DataLinkParam::DSI_CODE_OK())
		{
			AIS_LOG_INFO("Special Data Byte Order");
			std::reverse(ParamData.begin(), ParamData.end());
			datalinkParameter.SetLastValue(ParamData, dsiCode);
		}
	}
	else
	{
		datalinkParameter.SetVarLengthParamType(varLengthParamType);
		datalinkParameter.SetVarLengthParamValue(pData, dataLen, dsiCode);
	}

	if (dsiCode == DataLinkParam::DSI_CODE_OK())
	{
		AIS_LOG_INFO("pid : %x , dataLen : %d, dsiCode : %x", datalinkParameter.GetParamId(), dataLen, dsiCode);
		if (VarLengthDataLinkParamPool::NOT_APPLICABLE == varLengthParamType ||
			VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER == varLengthParamType)
		{
			AIS_LOG_INFO("data_ID %X  pidData  :   %x   %d", pContext->ParameterID, datalinkParameter.GetLastValue<unsigned_32>(), datalinkParameter.GetLastValue<unsigned_32>());
		}
		else
		{
			const unsigned_8 *varParamBlock = datalinkParameter.GetVarParamBlock();
			const unsigned_8 varParamBlockSize = datalinkParameter.GetVarParamBlockLength();
			for (int i = 0; i < varParamBlockSize; i++)
			{
				AIS_LOG_INFO("pidData[%2d]    %x", i, varParamBlock[i]);
			}
		}
	}
	datalinkParameter.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
	(void)BmiJ1939SCS::UpdateDataLinkData(datalinkParameter);

	/*Added only for Testing Restricted read params*/
	// BmiJ1939RestrictedRead::RestrictedParamDataUpdate( datalinkParameter );

	return 0;
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939DataHandlers::BmiJ1939PIDEvents
// Description     : Event handler for PGB over J1939
// Return Type     : None
// Argument [in]   : uint_least8_t* pData - Pointer to the received data,
//                   uint_least8_t dataLen - Data length in bytes,
//                   void* pRxContext - Pointer to the callback context,
//                   uint_least16_t dsiCode - Data Status Indicator.
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939DataHandlers::BmiJ1939PIDEvents(
	void *pEventContext,
	void *pDiagContext,
	const scl_pgb_j1939_rx_pid_config_t *pPIDCfg,
	scl_j1939_link_t linkHandle,
	int_least8_t ecmIdx,
	uint_least8_t remoteAddr,
	scl_pgb_j1939_event_t eventType)
{
	// "Touch" unused parameters to avoid compilation warnings
	(void)pEventContext;
	(void)pDiagContext;
	(void)linkHandle;
	(void)ecmIdx;

	switch (eventType)
	{
	case SCL_PGB_J1939_EVENT_PID_TIMEOUT:
	{
		AIS_LOG_ALERT("PID 0x%X from 0x%02X timed out", pPIDCfg->pid, remoteAddr);
		break;
	}

	case SCL_PGB_J1939_EVENT_PID_NA:
	{
		AIS_LOG_ALERT("PID 0x%X is not available from 0x%02X", pPIDCfg->pid, remoteAddr);
		break;
	}

	default:
	{
		// Do nothing
		break;
	}
	}
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939DataHandlers::BmiJ1939ADTDefault
// Description     : Default handler for a received PGB over J1939 message. Parses
//                   the message and adds to data to be sent over SCS
// Return Type     : int_least16_t - Not used anywhere, so always 0
// Argument [in]   : uint_least8_t* data - Pointer to the received data,
//                   uint_least8_t data_len - Data length in bytes,
//                   void* pRxContext - Pointer to the callback context,
//                   uint_least16_t dsiCode - Data Status Indicator.
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
int_least16_t BmiJ1939DataHandlers::BmiJ1939ADTDefault(uint_least8_t *data, 
														uint_least8_t data_len, 
														void *grp_pid_hdlr_context, 
														uint_least16_t dsi_code)
{

	BmiJ1939Config::CDLPIDTableEntry_t *pAdtContext = static_cast<BmiJ1939Config::CDLPIDTableEntry_t *>(grp_pid_hdlr_context);

	AIS_LOG_INFO(" ADT handler: DSI 0x%x", dsi_code);

	/*Update the DSI status received to DSITable for diagnostics*/
	//BmiJ1939TaskInit::SetDsiTableData(pAdtContext, dsi_code);

	if (DataLinkParam::DSI_CODE_OK() != dsi_code)
	{
		AIS_LOG_NOTICE(" PID 0x%X from 0x%02X with DSI 0x%X",
				   pAdtContext->ParameterID, pAdtContext->SourceAddress, dsi_code);
	}

	// Add this data to be sent over SCS to other apps
	std::vector<unsigned_8> ParamData;
	DataLinkParam datalinkParameter;
	datalinkParameter.SetDataLinkType(BmiJ1939Config::GetDataLinkType());
	VarLengthDataLinkParamPool::VarLengthParamType varLengthParamType = static_cast<VarLengthDataLinkParamPool::VarLengthParamType>(pAdtContext->VarLengthDataType);

	if (nullptr != data)
	{
		switch (data_len)
		{
		case sizeof(unsigned_8):
		{
			unsigned_8 tempValue;
			OEL_UNPACK_BE_8_NO_INCR(data, tempValue);
			ParamData.assign(reinterpret_cast<unsigned_8 *>(&tempValue),
							 reinterpret_cast<unsigned_8 *>(&tempValue) + sizeof(tempValue)); //save temp value into ParamData
			break;
		}
		case sizeof(unsigned_16):
		{
			unsigned_16 tempValue;
			OEL_UNPACK_BE_16_NO_INCR(data, tempValue);
			ParamData.assign(reinterpret_cast<unsigned_8 *>(&tempValue),
							 reinterpret_cast<unsigned_8 *>(&tempValue) + sizeof(tempValue)); //save temp value into ParamData
			break;
		}
		case sizeof(unsigned_32):
		{
			unsigned_32 tempValue;
			OEL_UNPACK_BE_32_NO_INCR(data, tempValue);
			ParamData.assign(reinterpret_cast<unsigned_8 *>(&tempValue),
							 reinterpret_cast<unsigned_8 *>(&tempValue) + sizeof(tempValue)); //save temp value into ParamData
			break;
		}
		default: /*check for Variable length data*/
		{
			break;
		}
		}

		datalinkParameter.SetParamId(pAdtContext->ParameterID);
		datalinkParameter.SetSid(pAdtContext->SourceAddress);

		if (VarLengthDataLinkParamPool::NOT_APPLICABLE == varLengthParamType)
		{
			datalinkParameter.SetLastValue(ParamData, dsi_code);
		}
		else if (VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER == varLengthParamType)
		{
			// for special pid like F5D9 swapping is needed for normal data
			if (dsi_code == DataLinkParam::DSI_CODE_OK())
			{
				AIS_LOG_INFO("Special Data Byte Order");
				std::reverse(ParamData.begin(), ParamData.end());
				datalinkParameter.SetLastValue(ParamData, dsi_code);
			}
		}
		else
		{
			// Variable length parameters
			if (dsi_code == DataLinkParam::DSI_CODE_OK())
			{
				datalinkParameter.SetVarLengthParamType(varLengthParamType);
				datalinkParameter.SetVarLengthParamValue(data, data_len, dsi_code);
			}
		}

		datalinkParameter.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);

		if (false == BmiJ1939SCS::UpdateDataLinkData(datalinkParameter))
		{
			return 0;
		}

		if (dsi_code == DataLinkParam::DSI_CODE_OK())
		{
			AIS_LOG_INFO("pid : %x , data_len : %d, dsi_code : %x", datalinkParameter.GetParamId(), data_len, dsi_code);
			if (VarLengthDataLinkParamPool::NOT_APPLICABLE == varLengthParamType ||
				VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER == varLengthParamType)
			{
				AIS_LOG_INFO("data_ID %X, pidData  :   %x   %d", pAdtContext->ParameterID, datalinkParameter.GetLastValue<unsigned_32>(), datalinkParameter.GetLastValue<unsigned_32>());
			}
			else
			{
				const unsigned_8 *varParamBlock = datalinkParameter.GetVarParamBlock();
				const unsigned_8 varParamBlockSize = datalinkParameter.GetVarParamBlockLength();
				for (int i = 0; i < varParamBlockSize; i++)
				{
					AIS_LOG_INFO("pidData[%2d]    %x", i, varParamBlock[i]);
				}
			}
		}
		else // if dsi_code not 0
		{
			AIS_LOG_NOTICE("pid %x, data_len %d, dsi_code %x", datalinkParameter.GetParamId(), data_len, dsi_code);

			if (VarLengthDataLinkParamPool::NOT_APPLICABLE == varLengthParamType ||
				VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER == varLengthParamType)
			{
				AIS_LOG_NOTICE("pidData %x   %d", datalinkParameter.GetLastValue<unsigned_32>(), datalinkParameter.GetLastValue<unsigned_32>());
			}
			else
			{
				for (int i = 0; i < data_len; i++)
				{
					AIS_LOG_NOTICE("pidData[%2d]          %x", i, data[i]);
				}
			}
		}
		//update the DLD Param for Restricted Param Check
		BmiJ1939RestrictedRead::RestrictedParamDataUpdate(datalinkParameter);
	}

	return 0;
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939DataHandlers::BmiJ1939AdtPIDEvents
// Description     : Event handler for ADT over J1939
// Return Type     : None
// Argument [in]   : scl_j1939_link_t - The scl_j1939 link that the timeout occurred,
//                   int_least8_t ecm_idx - The virtual ecm who failed to receive a  message,
//                   uint_least8_t remote_addr - The remote address who failed to transmit  a message,
//                   scl_adt_j1939_event_t - This parameter indicates the event type.
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939DataHandlers::BmiJ1939AdtPIDEvents(
	void *event_context,
	void *diagnostic_context,
	const scl_adt_j1939_client_grp_pid_config_t *client_grp_pid_config,
	scl_j1939_link_t link,
	int_least8_t ecm_idx,
	uint_least8_t remote_addr,
	scl_adt_j1939_event_t event)
{
	// "Touch" unused parameters to avoid compilation warnings
	(void)event_context;
	(void)diagnostic_context;
	(void)link;
	(void)ecm_idx;

	switch (event)
	{
	case SCL_ADT_J1939_EVENT_PID_INVALID_SEQUENCE:
	{
		AIS_LOG_ALERT("Invalid PID Sequence PID 0x%X from 0x%02X ", client_grp_pid_config->pid, remote_addr);
		break;
	}
	case SCL_ADT_J1939_EVENT_PID_TIMEOUT:
	{
		AIS_LOG_ALERT("PID 0x%X from 0x%02X timed out", client_grp_pid_config->pid, remote_addr);
		break;
	}

	case SCL_ADT_J1939_EVENT_PID_NA:
	{
		AIS_LOG_ALERT("PID 0x%X is not available from 0x%02X", client_grp_pid_config->pid, remote_addr);
		break;
	}

	case SCL_ADT_J1939_EVENT_PID_RXED:
	{
		AIS_LOG_INFO("PID 0x%X is Received from 0x%02X", client_grp_pid_config->pid, remote_addr);
		break;
	}
	case SCL_ADT_J1939_EVENT_PID_OVERFLOW:
	{
		AIS_LOG_ALERT("Overflow error for PID 0x%X from 0x%02X ", client_grp_pid_config->pid, remote_addr);
		break;
	}
	case SCL_ADT_J1939_EVENT_INVALID_REQUEST:
	{
		AIS_LOG_ALERT("Invalid Request for PID 0x%X from 0x%02X", client_grp_pid_config->pid, remote_addr);
		break;
	}
	case SCL_ADT_J1939_EVENT_UNKOWN_ERROR:
	{
		AIS_LOG_ALERT("Unknown error for PID 0x%X from 0x%02X ", client_grp_pid_config->pid, remote_addr);
		break;
	}
	case SCL_ADT_J1939_EVENT_NO_DATA_BUFFERS:
	{
		AIS_LOG_ALERT("No Data buffers available for PID 0x%X from 0x%02X ", client_grp_pid_config->pid, remote_addr);
		break;
	}
	case SCL_ADT_J1939_EVENT_PID_TOO_LONG:
	{
		AIS_LOG_ALERT("PID too Long for PID 0x%X from 0x%02X ", client_grp_pid_config->pid, remote_addr);
		break;
	}
	case SCL_ADT_J1939_EVENT_TP_NOT_AVAIL:
	{
		AIS_LOG_ALERT("No TP available for PID 0x%X from 0x%02X ", client_grp_pid_config->pid, remote_addr);
		break;
	}
	case SCL_ADT_J1939_EVENT_GRP_CONFIG_RETRY_FAILS:
	{
		AIS_LOG_ALERT("Event group config retry fails for PID 0x%X from 0x%02X ", client_grp_pid_config->pid, remote_addr);
		break;
	}
	default:
	{
		// Do nothing
		break;
	}
	}
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939DataHandlers::BmiJ1939PGNDefault
// Description     : Default handler for a received J1939 message. Parses
//                   the message and adds to data to be sent over SCS
// Return Type     : None
// Argument [in]   : const scl_j1939_link_t linkHandle - Link handle,
//                   const struct scl_j1939_rx_msg_s* pMsgProp - Pointer to
//                      message properties,
//                   const int_8 ecmIdx - Index to virtual ecm of request,
//                   const SCL_J1939_RX_MSG_CB_ENUM_t eventType - Reason
//                      for invocation of this handler,
//                   const scl_j1939_mbuf_hdr_t* pMsgBuffer - Pointer to the
//                      message buffer
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939DataHandlers::BmiJ1939PGNDefault(
	const scl_j1939_link_t linkHandle,
	const struct scl_j1939_rx_msg_s *pMsgProp,
	const int_8 ecmIdx,
	const SCL_J1939_RX_MSG_CB_ENUM_t eventType,
	const scl_j1939_mbuf_hdr_t *pMsgBuffer)
{
    // Get the attributes
    const auto dataPgn = pMsgProp->Mu32_pgn;
    const auto dataFrom = pMsgProp->Mu8_source_address;

    // "Touch" the unused arguments
    (void)linkHandle;
    (void)pMsgProp;
    (void)ecmIdx;

    switch (eventType) {
    case SCL_J1939_RX_MSG_PGN_RXED: // PGN Received
    {
        AIS_LOG_INFO("J1939 PGN Msg received");
        DataLinkParam datalinkParameter;
        // Grab all the data
        const auto dataLen = scl_j1939_get_mbuf_len( pMsgBuffer );
        unsigned_8 dataBuffer[dataLen];
        scl_j1939_get_data_from_mbuf( pMsgBuffer, dataBuffer, dataLen, 0 );
        AIS_LOG_INFO("dataLen = %d, dataPgn = 0x%X, dataFrom = 0x%X", dataLen, dataPgn, dataFrom);

        // Add this data to be sent over SCS to other apps
        datalinkParameter.SetDataLinkType(BmiJ1939Config::GetDataLinkType());
        datalinkParameter.SetParamIdentifierType( DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PUBLIC_PGN );
        datalinkParameter.SetParamId(dataPgn);
        datalinkParameter.SetSid(dataFrom);
        datalinkParameter.SetVarLengthParamType(VarLengthDataLinkParamPool::PGN);
        datalinkParameter.SetVarLengthParamValue(dataBuffer, dataLen, DataLinkParam::DSI_CODE_OK());
        (void)BmiJ1939SCS::UpdateDataLinkData(datalinkParameter);
        break;
    }

    //  The RX MSG Lost timer expired
    case SCL_J1939_RX_MSG_LOST:
    {
        DataLinkParam datalinkParameter;
        datalinkParameter.SetDataLinkType(BmiJ1939Config::GetDataLinkType());
        datalinkParameter.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PUBLIC_PGN);
        datalinkParameter.SetParamId(dataPgn);
        datalinkParameter.SetSid(dataFrom);
        datalinkParameter.SetVarLengthParamType(VarLengthDataLinkParamPool::PGN);
        datalinkParameter.SetVarLengthParamValue(nullptr, 0, DataLinkParam::DSI_CODE_NO_RESPONSE());
        (void)BmiJ1939SCS::UpdateDataLinkData(datalinkParameter);
        AIS_LOG_ALERT("PGN %u message was lost from 0x%X", dataPgn, dataFrom);
        break;
    }

    // A NAK was received in response to a "Request PGN"
    case SCL_J1939_RX_MSG_NAK:
    {
        AIS_LOG_ALERT( "Received NAK for PGN %u from 0x%X", dataPgn, dataFrom );
        break;
    }

    default:
    {
        AIS_LOG_ERROR( "Unhandled event %d received for PGN %u from 0x%X", static_cast<int>( eventType ), dataPgn, dataFrom );
        break;
    }
    }
}
