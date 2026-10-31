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
#include <unordered_map>
#include "BmiJ1939Read.h"
#include "BmiJ1939TaskInit.h"
#include "BmiJ1939SCS.h"
using namespace std;
#define SCL_RW_J1939_READ_REQ       0xF087
#define BYTE_2_MASK                 0xFF00
#define BYTE_1_MASK                 0x00FF
//#define CDL2_NUM_CON_RX_PIT 50
#define SCL_RW_J1939_SHIFT_ONE_BYTE 8
#define SCL_RW_J1939_SHIFT_TWO_BYTE 16
#define pidF5D9 0xf5d9
#define TWO_BYTE_DATA 2
#define FOUR_BYTE_DATA 4

scl_j1939_link_t Ph_Link_app;

//const unsigned_16    cdl2_num_con_rx_pit = CDL2_NUM_CON_RX_PIT;
//cdl2_con_rx_pit_t    cdl2_con_rx_pit[cdl2_num_con_rx_pit];
struct CDLPIDtable
{
    BmiJ1939Config::CDLPIDTableEntry_t cdlPIDTableEntry;
    bool swapFlag;
};
std::map<uint32_t, BmiJ1939Read::ReadPollTable_t> BmiJ1939Read::pReadPoll;
std::unordered_map<uint32_t, CDLPIDtable> cdlPidTable;

/* Application to get Request Receive Parameter ID */
Cdl_gen_ovr_parm_08_t  appget_request_parm;

/* Application to get Request Receive Parameter Information Entry */
const Cdl_gen_ovr_pie_08_t   appget_request_pie =
{
        /*Parameter To Receive Size  */
        sizeof(appget_request_parm.data),
        /*Address Of Parameter Data  */
        &appget_request_parm
};

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Read::AppGetReadupdateJ1939
// Description     : Periodic Read Request update function  which sends read request for configured PID's
// Return Type     : None
// Argument [in]   : BmiJ1939Config::CDLPIDTableEntries_t* const pPidTables
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939Read::ReadReqUpdateJ1939( BmiJ1939Config::CDLPIDTableEntries_t* const pPidTables )
{
    /*Frame default tx_msg with padding bytes*/
    unsigned_8 tx_message[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    for(auto& readPollItem : pReadPoll)
    {
        /* send a request message when timer is elapsed*/
        if (readPollItem.second.request_counter == 0)
        {
            unsigned_32 dataID = readPollItem.first;
            std::stringstream ss;
            ss<< std::hex << dataID;
            std::string Result ( ss.str() );
            unsigned_8 Pid_size = (Result.size())/2;
            /*Extended Id For CAT Data Link PID Read Request*/
            tx_message[0] = (unsigned_8)((SCL_RW_J1939_READ_REQ & BYTE_2_MASK) >> 8);  /* EXTID MSB */
            tx_message[1] = (unsigned_8) (SCL_RW_J1939_READ_REQ & BYTE_1_MASK);        /* EXTID LSB */

            switch(Pid_size)
            {
                case 1:
                {
                    tx_message[2] = (unsigned_8)dataID;
                }
                break;

                case 2:
                {
                    tx_message[2] = (unsigned_8)(dataID >> SCL_RW_J1939_SHIFT_ONE_BYTE);
                    tx_message[3] = (unsigned_8)dataID;
                }
                break;

                case 3:
                {
                    tx_message[2] = (unsigned_8)(dataID >> SCL_RW_J1939_SHIFT_TWO_BYTE);
                    tx_message[3] = (unsigned_8)(dataID >> SCL_RW_J1939_SHIFT_ONE_BYTE);
                    tx_message[4] = (unsigned_8)dataID;
                }
                break;

                default: /* discard the message */
                {
                    //msg_len = 0;
                }
                break;
            }

            /* send read request for required PID  */
            if(FALSE == scl_j1939_que_tx_msg_by_address(
                    Ph_Link_app,                /* Handle identifying J1939 connection */
                    0x00EF00,                   /* Proprietary PGN */
                    6,                          /* priority identifier field */
                    readPollItem.second.SourceAddress, /* destination address used in the PS field */
                    0,                          /* Index to ecm in address table */
                    tx_message,                 /* pointer to the data field that will be transmitted */
                    sizeof(tx_message)))        /* the length of the data field in number of bytes */
            {
            	AIS_LOG_WARN("Failed to send Read Request for PID 0x%X", dataID);
            }
            else
            {
                AIS_LOG_INFO("Read poll Request sent successfully for PID 0x%X", dataID);
            }

        }
        AIS_LOG_INFO("Read poll request_counter for PID 0x%X  %d" ,readPollItem.first, readPollItem.second.request_counter );
        readPollItem.second.request_counter = (uint32_t)((readPollItem.second.request_counter +1) % readPollItem.second.RequestRateMaxCount);
    }
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Read::J1939ClientRxHandler
// Description     : Default handler for a received J1939 read protocol message. Parses
//                   the message and adds to data to be sent over SCS
// Return Type     : int_least16_t - Not used anywhere, so always 0
// Argument [in]   : unsigned_32 con_index - this identifies J1939 link. In future it may be used to identify a connection within a data link,
//                   unsigned_8 pdl - Data length in bytes,
//                   void *rx_pie - Pointer to the callback info entry,
//                   unsigned_32 data_ID - Data ID.
//                   unsigned_8 *data - pointer to the parameter data
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
int_least16_t BmiJ1939Read::J1939ClientRxHandler ( cdl2_con_rx_data_link_t data_link_type,    /* Identify link: CDL or J1939 */
        unsigned_32 con_index,
        cdl2_con_rx_event_t ack_event,    /* ack event: receieved/not supported/ retry */
        void *rx_pie,        /* pointer to parm info entry */
        unsigned_8 sid,        /* message sid */
        unsigned_8 did,        /* message did, this is ecm index for J1939  */
        unsigned_32 data_ID, /* data ID */
        unsigned_8 pdl,    /* parameter data length */
        unsigned_8 *data /* pointer to parameter data in message */)
{
    Cdl_gen_ovr_parm_27_t *param;
    unsigned_16 l_index;
    unsigned_32 paramData = 0;
    DataLinkParam dlParameter;
    dlParameter.SetDataLinkType(BmiJ1939Config::GetDataLinkType());
    /* unused parameters, hence use void to avoid compiler warnings */
    (void)data_link_type;
    (void)con_index;
    (void)ack_event;
    (void)data_ID;

    AIS_LOG_INFO("data_ID: %x", data_ID);

    param = ((Cdl_gen_ovr_pie_27_t *)rx_pie)->parm;
    param->counter++;         /* increment the reception counter */
    param->sid = sid;        /* store the SID in the parameter area */
    param->did = did;        /* store the DID in the parameter area */
    param->pdl = pdl;         /* store the parameter data length */

    /* move the data */
    for (l_index=0; l_index<(param->pdl); l_index++)
    {
        param->data[l_index] = data[l_index];
        AIS_LOG_INFO("param->data[%d] = ox%X",l_index, param->data[l_index] );
    }

    if( CDL2_CON_RX_DATA_LINK_J1939 == data_link_type )/*Data link type should be J1939*/
    {
       switch(ack_event)
       {
           case CDL2_CON_RX_PID_RXED:
           {
               dlParameter.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
               VarLengthDataLinkParamPool::VarLengthParamType varLengthParamType = VarLengthDataLinkParamPool::NOT_APPLICABLE;
               dlParameter.SetParamId(data_ID);
               dlParameter.SetSid(param->sid);
               auto pidSearch = cdlPidTable.find(data_ID);
               if (pidSearch != cdlPidTable.end())
               {
                   if (nullptr != data)
                   {
                       switch (param->pdl)
                       {
                           case 1:
                           {
                               OEL_UNPACK_BE_8_NO_INCR(data, paramData);
                               break;
                           }
                           case 2:
                           {
                               OEL_UNPACK_BE_16_NO_INCR(data, paramData);
                               break;
                           }
                           case 4:
                           {
                               OEL_UNPACK_BE_32_NO_INCR(data, paramData);
                               break;
                           }
                           default:
                           {
                               /*Check for Variable length Data*/
                               varLengthParamType = static_cast<VarLengthDataLinkParamPool::VarLengthParamType>(pidSearch->second.cdlPIDTableEntry.VarLengthDataType);
                               if ((varLengthParamType == VarLengthDataLinkParamPool::NOT_APPLICABLE) || (varLengthParamType == VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER))
                               {
                                   AIS_LOG_ALERT("Attention: Received data of unhandled length %d for PID 0x%X", param->pdl, data_ID);
                               }
                               break;
                           }
                       }

                       if (VarLengthDataLinkParamPool::NOT_APPLICABLE == varLengthParamType)
                       {
                           // F5D9 is special pid
                           if (pidF5D9 != dlParameter.GetParamId())
                           {
                               AIS_LOG_INFO(" Read swap %x", dlParameter.GetParamId());
                               SwapJ1939Read(dlParameter.GetParamId(), param->pdl, paramData);
                           }

                           std::vector<unsigned_8> paramDataVec;
                           paramDataVec.assign(reinterpret_cast<unsigned_8 *>(&paramData),
                               reinterpret_cast<unsigned_8 *>(&paramData) + sizeof(paramData));

                           dlParameter.SetLastValue(paramDataVec, DataLinkParam::DSI_CODE_OK());

                           AIS_LOG_INFO("paramID %x length %d data %d", dlParameter.GetParamId(), param->pdl, paramData);
                       }
                       else if (VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER != varLengthParamType)
                       {
                           dlParameter.SetVarLengthParamType(varLengthParamType);
                           dlParameter.SetVarLengthParamValue(&data[0], param->pdl, DataLinkParam::DSI_CODE_OK());
                       }
                       else
                       {
                           AIS_LOG_ALERT("Attention: Unhandled varLengthParamType(%d)", varLengthParamType);
                       }

                       if (true == BmiJ1939SCS::UpdateDataLinkData(dlParameter))
                       {
                           if (VarLengthDataLinkParamPool::NOT_APPLICABLE == varLengthParamType ||
                               VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER == varLengthParamType)
                           {
                               AIS_LOG_INFO("data_ID %X  pidData  0x%X   (%d)", data_ID, paramData, paramData);
                           }
                           else
                           {
                               const unsigned_8* varParamBlock = dlParameter.GetVarParamBlock();
                               const unsigned_8 varParamBlockSize = dlParameter.GetVarParamBlockLength();
                               AIS_LOG_INFO("varParamBlockSize : %d", varParamBlockSize);
                               for (int i = 0; i < varParamBlockSize; i++)
                               {
                                   AIS_LOG_INFO("data_ID %X pidData[%2d]    0x%X", data_ID, i, varParamBlock[i]);
                               }
                           }
                       }
                   }
               }
               break; /*outer switch case*/
           }

           case CDL2_CON_RX_PID_RETRY:
           {
               /* Request again */
               AIS_LOG_ALERT("Request Again");
               break;
           }

           case CDL2_CON_RX_PID_WR_UNSUCCESS:
           case CDL2_CON_RX_PID_WR_NOT_SUPPORTED:
           case CDL2_CON_RX_PID_RD_NOT_SUPPORTED:
           {
               /* take appropriate action for failure */
               AIS_LOG_ALERT("Failed to receive RX PID");
               break;
           }

           default: /* handle other ack */
               AIS_LOG_ERROR("Unhandled event received");
               break;
       }
    }
    else /* CDL */
    {
        AIS_LOG_ERROR("Invalid data_link_type - CDL");
    }

    return CDL2_SUCCESSFUL;
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Read::AppGetReadInitJ1939
// Description     : Initializes CAT DataLink PID for J1939 Read protocol
// Return Type     : None
// Argument [in]   : CDLPIDTableEntries_t* const pPidTables - Reference to the CDL PID table
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939Read::ReadReqInitJ1939(BmiJ1939Config::CDLPIDTableEntries_t* const pPidTables,const int_16 taskPeriod_ms)
{
    
    for ( auto& jsonPidParam : *pPidTables )
    {
        if(J1939_READ_POLL == jsonPidParam.RequestType)
        {
            AIS_LOG_INFO("Adding PID 0x%X to con rx pit", jsonPidParam.ParameterID);
            /* Register Message To Be Received */
            uint8_t addRxPitStatus = cdl2_add_to_con_rx_pit( jsonPidParam.ParameterID,
                    										 &BmiJ1939Read::J1939ClientRxHandler,
                    										 &appget_request_pie );
            if (addRxPitStatus != CDL2_SUCCESSFUL)
            {
				switch(addRxPitStatus)
				{
				case CDL2_PIT_TABLE_FULL:
					AIS_LOG_FATAL(" Failed to add to rx pit (the receive pit is full)" );
					break;
				case CDL2_EXISTS_FOR_ANOTHER_ENTRY:
					AIS_LOG_FATAL(" Failed to add to rx pit (Data Id exists in another entry)" );
					break;
				default:
					AIS_LOG_FATAL(" Failed to add to rx pit" );
					break;
				}
            }
            ReadPollTable_t ReadPollTable;
            ReadPollTable.SourceAddress = jsonPidParam.SourceAddress;
            ReadPollTable.RequestRateMaxCount = (uint32_t)(jsonPidParam.RequestRate_ms/taskPeriod_ms);
            ReadPollTable.request_counter = 0;
            pReadPoll[jsonPidParam.ParameterID] = ReadPollTable;
            AIS_LOG_INFO("read poll PID %x reuqestcounter %d",jsonPidParam.ParameterID, ReadPollTable.RequestRateMaxCount);

            CDLPIDtable BmiJ1939ReadTableEntry_s;
            BmiJ1939ReadTableEntry_s.cdlPIDTableEntry = jsonPidParam;
            size_t found = jsonPidParam.Attributes.find("swap bytes");
            if (found != string::npos)
            {
                BmiJ1939ReadTableEntry_s.swapFlag = true;
            }
            else
            {
                BmiJ1939ReadTableEntry_s.swapFlag = false;
            }

            cdlPidTable[jsonPidParam.ParameterID] = BmiJ1939ReadTableEntry_s;
        }

    }
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Map::SwapJ1939Read
// Description     : swap the bytes if it is mentioned in json file before publish
// Return Type     : None
// Argument [in]   : uint32_t pid(PID),unsigned_8 len(length of PID),unsigned_32 &paramData(PIDs data to swap)
// Argument [out]  : paramData as reference
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939Read::SwapJ1939Read(uint32_t pid,unsigned_8 len,unsigned_32 &paramData)
{
    AIS_LOG_DEBUG("Read poll paramData before swap %x", paramData);
    auto pidSearch = cdlPidTable.find(pid);
    if ((pidSearch != cdlPidTable.end()) && (pidSearch->second.swapFlag == true))
    {
        if (len == TWO_BYTE_DATA)
        {
            paramData = ((paramData << 8) & 0xff00) | ((paramData >> 8) & 0x00ff);
        }
        else if (len == FOUR_BYTE_DATA)
        {
            paramData = ((paramData << 8) & 0xFF00FF00) | ((paramData >> 8) & 0xFF00FF);
            paramData = ((paramData << 16) | (paramData >> 16));
        }
    }
    AIS_LOG_DEBUG("Read poll paramData after swap %x", paramData);
}

