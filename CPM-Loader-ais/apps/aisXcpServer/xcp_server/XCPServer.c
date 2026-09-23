/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar's proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  XCPServer.c
DESCRIPTION:

    Key features:
        DAQ and STIM.
        Static DAQ/STIM size for better predictability than Dynamic.
        Multiple instances on CAN and/or Ethernet.
        Larger CTO/DTO size than Vector library.


    Presently STIM checks to see if data has been received before writing.
    It is only checking at the ODT level.  It does not check to see if
    the entire DAQ has been received, so there may need to be an extra
    check to see if all ODTs for a DAQ have been received before writing.


    Features not supported
        Block transfer.  Reasoning: Block mode involves transfer of a large
        amount of data with minimal handshaking and auto incrementing of
        memory transfer pointers.  Any missing/extra message can corrupt
        memory.

        PID_OFF.  PID_OFF is not supported as it requires that each ODT
        have a unique CAN ID.  This would require many more CAN IDs be
        reserved for each ECM, which is not feasible on the already
        burdened Cat CAN links.

    Assumptions:
    32 bit address space/pointers. (Note: XCP does not explicitly handle
    64 bit pointers)
    ADDRESS_GRANULARITY == 1
    PID_OFF_SUPPORTED == FALSE
    TIMESTAMP_SUPPORTED == FALSE
    BIT_STIM_SUPPORTED == TRUE
    RESUME_SUPPORTED == FALSE
    PRESCALER_SUPPORTED == TRUE
    ADDRESS_EXTENSION == FREE
    ID_FIELD_TYPE == ABSOLUTE
    MAX_ODT_ENTRY_SIZE_DAQ/STIM =  Application Dependent, 4 for CAN.
    MIN_DAQ ==0
    MAX_DAQ == Application dependent.

    MAX_CTO/MAX_DTO for CAN == 8
    MAX_CTO/MAX_DTO for Ethernet = 255/1024 (recommended)
    BYTE_ORDER == System dependent.  This must match the byte order of the
                   system or else this code will fail.

    GRANULARITY_ODT_ENTRY_SIZE /daq/stim == BYTE
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "XCP.h"
#include "XCPServer.h"
#include "XCPServer_.h"
#include "polyfill.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#   define SYSTEM_IS_BIG_ENDIAN 1
#else
#   define SYSTEM_IS_BIG_ENDIAN 0
#endif

#define XCPSERVER_DAQLIST_DIRECTION_DAQ  0x00
#define XCPSERVER_DAQLIST_DIRECTION_STIM 0x01

#define XCPSERVER_EVENT_NAME_LENGTH (8)

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
static void XCPServerFreeDAQ(XCPServer_t *pXCP);
static void XCPServerResetConnection(XCPServer_t *pXCP);
static void XCPServerClearDAQList(XCPServer_t *pXCP, XCPSERVER_DAQ_LIST_T *pDAQList);
static void XCPServerSendDAQ(XCPServer_t *pXCP, XCPSERVER_DAQ_LIST_T *pDAQList);
static void XCPServerWriteSTIMDAQ(XCPServer_t *pXCP, XCPSERVER_DAQ_LIST_T *pDAQList);
static void XCPServerProcCmdPacket(XCPServer_t *pXCP, uint8_t *pPacket, uint16_t PacketLength);
static void XCPServerProcSTIMPacket(XCPServer_t *pXCP, uint8_t *pPacket, uint16_t PacketLength);
static BOOL XCPServerSendErrorResponse(XCPServer_t *pXCP, uint8_t ErrorCode);
static BOOL XCPServerSendResponse(XCPServer_t *pXCP, uint16_t PacketLength);
static void XCPServerGetSeedAndKey(XCPServer_t *pXCP, uint8_t Resource);
static BOOL XCPServerValidateKey(XCPServer_t *pXCP);
static BOOL XCPServerValidateMemory(XCPServer_t *pXCP, uint32_t Address, uint8_t AddressExtension);
static BOOL XCPServerValidateMemoryRange(XCPServer_t *pXCP, uint32_t Address, uint8_t AddressExtension, uint8_t NumBytes);
static void XCPServerReadMemoryFromMTA(XCPServer_t *pXCP, uint8_t *pDest, uint8_t NumBytes);
static void XCPServerWriteMemoryToMTA(XCPServer_t *pXCP, uint8_t const * pSrc, uint8_t NumBytes);
/*static BOOL XCPServerValidateDAQ(XCPServer_t *pXCP, XCPSERVER_DAQ_LIST_T *pDAQList);*/
static BOOL XCPServerValidateODT(XCPServer_t *pXCP, XCPSERVER_ODT_T *pODT, uint8_t NumAdditionalBytes);
static void XCPServerStartStopSynchSelected(XCPServer_t *pXCP, uint8_t Mode);
static void XCPServerReadODTEntry(XCPServer_t *pXCP, XCPSERVER_ODT_ENTRY_T *pODTEntry, uint8_t *pDest);
static BOOL XCPServerSendUDPResp(XCPServer_t *pXCP, uint8_t *pMsgBuf, uint16_t PacketLength);
static BOOL XCPServerSendCANResp(XCPServer_t *pXCP,  uint8_t *pMsgBuf, uint16_t PacketLength);
static void XCPServerWriteODTEntry(XCPServer_t *pXCP, XCPSERVER_ODT_ENTRY_T *pODTEntry, uint8_t *pSrc);
static void XCPServerPrepDAQListForStart(XCPServer_t *pXCP, XCPSERVER_DAQ_LIST_T *pDAQList);

/*******************************************************************************
** -- Data Declarations
*******************************************************************************/

/*
    All data is defined within the XCPServer_t for each XCP instance.
*/
XCPServer_t* XCPServer_new(void)
{
    return (XCPServer_t*)malloc(sizeof(XCPServer_t));
}

void XCPServer_free(XCPServer_t* pXCP)
{
    free(pXCP);
}

/******************************************************************************
Function Name: XCPServer_init

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
BOOL XCPServer_init(XCPServer_t *pXCP, XCPServer_Config_t const *pConfig)
{
    uint8_t DAQListNum, ODTNum;
    XCPSERVER_DAQ_LIST_T *pDAQList;
    BOOL bDAQAllocFailed;
    XCPSERVER_ODT_T *pODT;

    if (pXCP == NULL) {
        return(FALSE);
    }

    XCPHALInit(pXCP);

    pXCP->bConfigured = FALSE;

    pXCP->pConfig = NULL;
    pXCP->MTAAddressExtension = 0;
    pXCP->MTA = 0;

    //??? Does STIM need to be configurable?
    //??? Can STIM seed/key be bypassed by factory password?

    pXCP->LockedResourceStatus = XCP_RESOURCE_STIM | XCP_RESOURCE_DAQ | XCP_RESOURCE_CALPAG;
    pXCP->pDAQLists = NULL;
    pXCP->pRespMessageBuf = NULL;

    pXCP->memValidate = NULL;
    pXCP->pMemValidateContext = NULL;
    pXCP->memWrite = NULL;
    pXCP->pMemWriteContext = NULL;
    pXCP->memRead = NULL;
    pXCP->pMemReadContext = NULL;

    pXCP->pConfig = pConfig;
    if (pConfig == NULL) {
        return(FALSE);
    }

    switch (pConfig->SetupInfoType) {
        case XCP_XPORT_UDP:
            // supported type
            // Need sanity check on MaxDTO, but also need to ensure it agrees with NumODTEntriesPerODT
            // Can't have more ODT entries than MaxDTO - DAQ header length
            if (pConfig->MaxCTO > pConfig->MaxDTO) {
                // Max DTO should be at least equal to Max CTO.
                return(FALSE);
            }
            pXCP->pRespMessageBuf = (uint8_t *) malloc(pConfig->MaxDTO + 4);
            if (pXCP->pRespMessageBuf == NULL) {
                return(FALSE);
            }
            pXCP->RespHeaderLength = 4;
            pXCP->pRespPacket = &pXCP->pRespMessageBuf[4];

            // Need to open/map to a UDP socket here.
            if (!XCPHALOpenUDPPort(pXCP, pConfig->Port)) {
                return(FALSE);
            }

            break;
        case XCP_XPORT_CAN:
            if ((pConfig->MaxCTO != 8) ||
                (pConfig->MaxDTO != 8)) {
                return(FALSE);
            }

            if (pConfig->SlaveID & 0x80000000) {
                // 29 bit
                pXCP->pRespMessageBuf = (uint8_t *)malloc(pConfig->MaxDTO + 4);
                if (pXCP->pRespMessageBuf == NULL) {
                    return(FALSE);
                }
                pXCP->RespHeaderLength = 4;
                pXCP->pRespPacket = &pXCP->pRespMessageBuf[4];

                // No sense in copying this every single time we send a message.
                // Preload it once here.
                pXCP->pRespMessageBuf[0] = (uint8_t) (pConfig->SlaveID >> 24);
                pXCP->pRespMessageBuf[1] = (uint8_t) (pConfig->SlaveID >> 16);
                pXCP->pRespMessageBuf[2] = (uint8_t) (pConfig->SlaveID >> 8);
                pXCP->pRespMessageBuf[3] = (uint8_t) (pConfig->SlaveID );
            } else {
                // 11 bit
                pXCP->pRespMessageBuf = (uint8_t *) malloc(pConfig->MaxDTO + 2);
                if (pXCP->pRespMessageBuf == NULL)
                {
                    return(FALSE);
                }
                pXCP->RespHeaderLength = 2;
                pXCP->pRespPacket = &pXCP->pRespMessageBuf[2];

                pXCP->pRespMessageBuf[0] = (uint8_t) (pConfig->SlaveID >> 8);
                pXCP->pRespMessageBuf[1] = (uint8_t) (pConfig->SlaveID );
            }

            // Need to map to a CAN port /socket here.
            if (!XCPHALOpenCANPort(pXCP, 0)) {
                return(FALSE);
            }

            break;
        default:
            //unsupported type.
            return(FALSE);

    };
    if (pConfig->NumEvents > XCPSERVER_MAX_EVENTS) {
        // Invalid number of events
        return(FALSE);
    }

    // Allocate memory for DAQ lists.
    if ((pConfig->NumDAQSTIMLists == 0) ||
        (pConfig->NumODTPerDAQSTIM == 0) ||
        (pConfig->NumODTEntriesPerODT == 0)) {
        return(FALSE);
    }

    if (pConfig->NumDAQSTIMLists * pConfig->NumODTPerDAQSTIM > XCP_CMD_MINVALUE) {
        // if we allocate more than XCP_CMD_MINVALUE, then the STIM broadcasts
        // could potentially flow into the CMD space.
        return(FALSE);
    }

    /*
        Each DAQ/STIM transmit has overhead associated with it.
        In this case, the overhead is 1 byte of absolute ODT.
        The max # of entries per ODT + this header should not exceed the MaxDTO, otherwise
        we're allocating unusable space.

        Note if Timestamps are later supported and set at fixed, or if the addressing mode changes, or
        if PID_OFF is supported, then this could change.
    */
    if (1 + pConfig->NumODTEntriesPerODT >= pConfig->MaxDTO) {
        return(FALSE);
    }

    pXCP->pDAQLists = (XCPSERVER_DAQ_LIST_T *) malloc(sizeof(XCPSERVER_DAQ_LIST_T) * pConfig->NumDAQSTIMLists);
    if (pXCP->pDAQLists == NULL) {
        return(FALSE);
    }

    bDAQAllocFailed = FALSE;

    for(DAQListNum=0; DAQListNum < pConfig->NumDAQSTIMLists; DAQListNum++) {
        pDAQList = &pXCP->pDAQLists[DAQListNum];

        pDAQList->pODTs = (XCPSERVER_ODT_T *) malloc(sizeof(XCPSERVER_ODT_T) * pConfig->NumODTPerDAQSTIM);
        if (pDAQList->pODTs == NULL) {
            bDAQAllocFailed = TRUE;
        } else {
            for(ODTNum = 0; ODTNum < pConfig->NumODTPerDAQSTIM; ODTNum++) {
                pODT = &pDAQList->pODTs[ODTNum];
                pODT->PID = DAQListNum * pConfig->NumODTPerDAQSTIM + ODTNum;
                pODT->pODTEntries = (XCPSERVER_ODT_ENTRY_T *) malloc(sizeof(XCPSERVER_ODT_ENTRY_T) * pConfig->NumODTEntriesPerODT);
                if (pODT->pODTEntries == NULL) {
                    bDAQAllocFailed = TRUE;
                }

                // Note: this could be made more efficient by allocating one memory block for everything at once to
                // minimize memory used by malloc/free overhead.
                pODT->pDAQMessageBuf = (uint8_t *) malloc(pConfig->MaxDTO + pXCP->RespHeaderLength);
                if (pODT->pDAQMessageBuf == NULL) {
                    bDAQAllocFailed = TRUE;
                } else {
                    pODT->pDAQPacket = &pODT->pDAQMessageBuf[pXCP->RespHeaderLength];

                    if (pConfig->SetupInfoType == XCP_XPORT_CAN) {
                        if (pConfig->SlaveID & 0x80000000) {
                            // 29 bit
                            // No sense in copying this every single time we send a message.
                            // Preload it once here.
                            pODT->pDAQMessageBuf[0] = (uint8_t) (pXCP->pConfig->SlaveID >> 24);
                            pODT->pDAQMessageBuf[1] = (uint8_t) (pXCP->pConfig->SlaveID >> 16);
                            pODT->pDAQMessageBuf[2] = (uint8_t) (pXCP->pConfig->SlaveID >> 8);
                            pODT->pDAQMessageBuf[3] = (uint8_t) (pXCP->pConfig->SlaveID );
                        } else {
                            // 11 bit
                            pODT->pDAQMessageBuf[0] = (uint8_t) (pXCP->pConfig->SlaveID >> 8);
                            pODT->pDAQMessageBuf[1] = (uint8_t) (pXCP->pConfig->SlaveID );
                        }
                    }
                }
            }
        }
        pDAQList->FirstPID = DAQListNum * pConfig->NumODTPerDAQSTIM;
    }

    if (bDAQAllocFailed) {
        XCPServer_cleanup(pXCP);
        return(FALSE);
    }

    pXCP->bConfigured = TRUE;

    XCPServerResetConnection(pXCP);
    return(TRUE);
}

void XCPServer_main(XCPServer_t* pXCP)
{
    XCPHALMain(pXCP);
}

/******************************************************************************
Function Name: XCPServer_cleanup

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
void XCPServer_cleanup(XCPServer_t *pXCP)
{
    XCPServer_Config_t const *pConfig;

    if (pXCP == NULL) {
        return;
    }

    pXCP->memValidate = NULL;
    pXCP->memWrite = NULL;
    pXCP->memRead = NULL;

    pConfig = pXCP->pConfig;
    switch (pConfig->SetupInfoType) {
        case XCP_XPORT_UDP:
            XCPHALCloseUDPPort(pXCP);
        case XCP_XPORT_CAN:
            XCPHALCloseCANPort(pXCP);
        default:
            break;
    }

    if (pXCP->pRespMessageBuf != NULL) {
        free(pXCP->pRespMessageBuf);
    }
    XCPServerFreeDAQ(pXCP);
    pXCP->pConfig = NULL;
    pXCP->bConfigured = FALSE;
}

/******************************************************************************
Function Name: XCPServerFreeDAQ

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
    Only done during final cleanup to free up any allocated memory.
******************************************************************************/
static void XCPServerFreeDAQ(XCPServer_t *pXCP)
{
    if (pXCP->pDAQLists != NULL) {
        uint8_t DAQListNum;
        for(DAQListNum=0; DAQListNum < pXCP->pConfig->NumDAQSTIMLists; DAQListNum++) {
            XCPSERVER_DAQ_LIST_T *pDAQList = &pXCP->pDAQLists[DAQListNum];

            if (pDAQList->pODTs != NULL) {
                uint8_t ODTNum;
                for(ODTNum = 0; ODTNum < pXCP->pConfig->NumODTPerDAQSTIM; ODTNum++) {
                    XCPSERVER_ODT_T *pODT = &pDAQList->pODTs[ODTNum];

                    if (pODT->pODTEntries != NULL) {
                        free(pODT->pODTEntries);
                    }

                    if (pODT->pDAQMessageBuf != NULL) {
                        free(pODT->pDAQMessageBuf);
                    }
                }
                free(pXCP->pDAQLists[DAQListNum].pODTs);
            }
        }
        free(pXCP->pDAQLists);
    }
}

/******************************************************************************
Function Name: XCPServerResetConnection

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static void XCPServerResetConnection(XCPServer_t *pXCP)
{
    uint8_t DAQNum;

    if ((pXCP == NULL) || (pXCP->bConfigured == FALSE)) {
        return;
    }

    pXCP->bIsConnected = FALSE;
    pXCP->LockedResourceStatus = XCP_RESOURCE_STIM | XCP_RESOURCE_DAQ | XCP_RESOURCE_CALPAG;
    pXCP->SessionConfigurationID = 0;
    pXCP->CurrentSeedKeyResource = 0;
    pXCP->DTOCounter = 0;

    // clear seed/key
    pXCP->CurrentSeedKeyResource = 0;
    pXCP->CurrentSeedLength = 0;
    pXCP->CurrentRemainingSeedLength = 0;

    pXCP->bKeyGenerated = FALSE;
    pXCP->CurrentActualKeyLength = 0;

    pXCP->CurrentMasterKeyLength = 0;
    pXCP->CurrentMasterRemainingKeyLength = 0;

    // Clear MTA
    pXCP->MTAAddressExtension = 0;
    pXCP->MTA = 0;

    // Clear DAQ pointer
    pXCP->DAQPtrListNumber = 0;
    pXCP->DAQPtrODTNumber = 0;
    pXCP->DAQPtrODTEntryNumber = 0;

    for(DAQNum = 0; DAQNum<pXCP->pConfig->NumDAQSTIMLists; DAQNum++) {
        // shut down any active broadcasts
        XCPSERVER_DAQ_LIST_T *pDAQList = &pXCP->pDAQLists[DAQNum];
        XCPServerClearDAQList(pXCP, pDAQList);
    }
    pXCP->NumUsedDAQLists = 0;
}

/******************************************************************************
Function Name: XCPServer_procEvent

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
pXCP                I   XCPServer_t *       pointer to this instance of XCP
EventID             I   uint16_t                 Event ID to process DAQ/STIM for

Description:

    Sends DAQ and processes STIM tied to the specified event.

Comments:
    May need to break this into separate functions, one for STIM, and
    one for DAQ, so that STIM can be run at the beginning of the event, and
    DAQ can be run after.
******************************************************************************/
extern void XCPServer_procEvent(XCPServer_t* pXCP, uint16_t EventID)
{
    uint8_t DAQNum;

    if ((pXCP == NULL) || (pXCP->bConfigured == FALSE)) {
        return;
    }
    /* if Connected and transmitting DAQ, send all DAQs tied to this Event if prescaler/elapsed time matches

        if Connected and receiving STIM, write all STIM lists tied to this event. (prescaler not used)
    */
    if (pXCP->bIsConnected == FALSE) {
        return;
    }

    for(DAQNum = 0; DAQNum < pXCP->NumUsedDAQLists; DAQNum++) {
        XCPSERVER_DAQ_LIST_T *pDAQList = &pXCP->pDAQLists[DAQNum];
        if (pDAQList->EventID == EventID) {
            if (pDAQList->Direction == XCPSERVER_DAQLIST_DIRECTION_DAQ) {
                if (pDAQList->StartStopSelected == XCP_STARTSTOPDAQLIST_MODE_START) {
                    pDAQList->EventCount++;
                    if (pDAQList->EventCount >= pDAQList->Prescaler) {
                        pDAQList->EventCount = 0;
                        // Send DAQ;
                        XCPServerSendDAQ(pXCP, pDAQList);
                    }
                }
            } else if (pDAQList->Direction == XCPSERVER_DAQLIST_DIRECTION_STIM) {
                // STIM
                if (pDAQList->StartStopSelected == XCP_STARTSTOPDAQLIST_MODE_START) {
                    XCPServerWriteSTIMDAQ(pXCP, pDAQList);
                }
            }
        }
    }
}

/******************************************************************************
Function Name: XCPServerProcCANMsg

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
void XCPServerProcCANMsg(XCPServer_t *pXCP, uint8_t *pMsg, uint16_t MsgLength)
{
    uint32_t CANID;
    uint8_t *pPacket;
    uint16_t PacketLength;

    if ((pXCP == NULL) || (pXCP->bConfigured == FALSE)) {
        return;
    }
    /*
        Process CAN header, determine if need to process.
    */
    if (pMsg[0] & 0x80) {   // 29 bit ID
        CANID = (pMsg[0] << 24) + (pMsg[1] << 16) + (pMsg[2] << 8) + pMsg[3];
        pPacket = &pMsg[4];
        PacketLength = MsgLength - 4;
    } else {
        // 11 bit ID
        CANID = (pMsg[0] << 8) + pMsg[1];
        pPacket = &pMsg[2] ;
        PacketLength = MsgLength - 2;
    }

    if (CANID == pXCP->pConfig->MasterID) {
        if (pPacket[0] >= XCP_CMD_MINVALUE) {
            XCPServerProcCmdPacket(pXCP, pPacket, PacketLength);
        } else {
            XCPServerProcSTIMPacket(pXCP, pPacket, PacketLength);
        }
    } else if (CANID == pXCP->pConfig->BroadcastID) {
        // handle discovery
        if (PacketLength <6) {
            return;
        }

        if ((pPacket[0] == XCP_CMD_TRANSPORT_LAYER_CMD) &&
            (pPacket[1] == 0xFF) && // subcommand code
            (pPacket[2] == 0x58) &&
            (pPacket[3] == 0x43) &&
            (pPacket[4] == 0x50) &&
            (pPacket[5] < 2)) {
            pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
            if (pPacket[5] == 0) {
                // identify by echo
                pXCP->pRespPacket[1] = 0x58;
                pXCP->pRespPacket[2] = 0x43;
                pXCP->pRespPacket[3] = 0x50;
            } else {
                // (pPacket[5] == 1) // confirm by inverse echo
                pXCP->pRespPacket[1] = 0xA7;
                pXCP->pRespPacket[2] = 0xBC;
                pXCP->pRespPacket[3] = 0xAF;
            }
            /*
                CAN identifier is always send LSB first.
                Set most significant bit to indicate 29 bit ID. (should already be set in config)
            */
            pXCP->pRespPacket[4] = (uint8_t) (pXCP->pConfig->SlaveID);
            pXCP->pRespPacket[5] = (uint8_t) (pXCP->pConfig->SlaveID >> 8);
            pXCP->pRespPacket[6] = (uint8_t) (pXCP->pConfig->SlaveID >> 16);
            pXCP->pRespPacket[7] = (uint8_t) (pXCP->pConfig->SlaveID >> 24);
            XCPServerSendResponse(pXCP, 8);
        }
    }
}

/******************************************************************************
Function Name: XCPServerProcUDPMsg

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
void XCPServerProcUDPMsg(XCPServer_t *pXCP, uint8_t *pMsg, uint16_t MsgLength, uint32_t SrcIP, uint16_t SrcPort)
{
    uint16_t PacketLength;
    uint16_t RemainingMsgLength;

    if ((pXCP == NULL) || (pXCP->bConfigured == FALSE)) {
        return;
    }
    /*
        Process UDP data, determine if need to process.

        There may be multiple XCP commands within one UDP packet.
    */
    if (MsgLength < 5) {
        // Not long enough to be valid.
        return;
    }

    if (pXCP->bIsConnected) {
        if((SrcIP != pXCP->UDPMasterIP) ||
           (SrcPort != pXCP->UDPMasterPort)) {
            // Incoming message is not for the IP address/port we were last connected to.
            // Master could have lost connection and reset, or could be two tools contending for the
            // connection.
            XCPServerResetConnection(pXCP);
        }
    }

    /*
        Technically the Master is allowed to put multiple XCP messages within the same UDP packet.
    */
    RemainingMsgLength = MsgLength;
    while(RemainingMsgLength > 4) {
        uint8_t *pPacket;
        // Header is {uint16_t Packet Length, uint16_t Count}, always LSB first.

        PacketLength = (pMsg[1] << 8    ) + pMsg[0];
        // count is bytes 2 and 3.  Ignoring this for now.
        pPacket = &pMsg[4];
        RemainingMsgLength -= 4;
        if ((PacketLength > RemainingMsgLength) ||
            (PacketLength == 0)) { // need at least one byte for a valid command
            // invalid packet
            break;
        }

        if (pPacket[0] >= XCP_CMD_MINVALUE) {
            if (pPacket[0] == XCP_CMD_CONNECT) {
                pXCP->UDPMasterIP = SrcIP;
                pXCP->UDPMasterPort = SrcPort;
            }
            XCPServerProcCmdPacket(pXCP, pPacket, PacketLength);
        } else {
            XCPServerProcSTIMPacket(pXCP, pPacket, PacketLength);
        }
        RemainingMsgLength -= PacketLength;
        pMsg += 4 + PacketLength;
    }
}

/******************************************************************************
Function Name: XCPServerProcCmdPacket

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
void XCPServerProcCmdPacket(XCPServer_t *pXCP, uint8_t *pPacket, uint16_t PacketLength)
{
    uint8_t CommandID;
    uint8_t DAQNum;
    uint8_t TempU8;
    uint16_t TempU16;
    uint32_t TempU32;
    uint8_t NumElements;
    uint16_t ListNum, EventNum;

    /*
        Process command.
    */
    CommandID = pPacket[0];

    if (CommandID == XCP_CMD_CONNECT) {
        /*  dawdyka note:
            The XCP protocol doc states that:

            "During a running XCP session (CONNECTED) this command has no
            influence on any configuration of the XCP slave driver."

            But, if using TCP or UDP, if you receive a CONNECT from an IP address/port
            other than what is currently connected, what should be done about it?  It's
            obviously a different connection.

            Also, if a previous connection was lost (due to improper shutdown, etc.)
            we wouldn't necessarily want to keep the session open and unlocked.

            A tool shouldn't be issuing the CONNECT command during a truly connected session anyway.

        */
        //printf("Connection Request...\n");

        XCPServerResetConnection(pXCP);
        if (PacketLength < 2) {
            XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
            return;
        }

        // Data[1] is Mode.  00 = Normal, 01 = User Defined.
        if (pPacket[1] != 0x00) {
            XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
            return;
        }

        /*
            Response
            Data[1] = Resource
            Data[2] = COMM_MODE_BASIC
            Data[3] = Max CTO
            Data[4,5] = Max DTO (big or little endian, or specified by byte_order in COMM_MODE_BASIC?
            Data[6] = XCP Protocol Layer Version # (MSB only)
            Data[7] = XCP Transport Layer Version # (MSB only)
        */

        pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
        // CAL, DAQ, and STIM supported.
        pXCP->pRespPacket[1] = XCP_RESOURCE_STIM | XCP_RESOURCE_DAQ | XCP_RESOURCE_CALPAG;

        // Fill in COMM_MODE_BASIC byte.
        pXCP->pRespPacket[2] = 0x00;    // AG is 1 byte.

        if (SYSTEM_IS_BIG_ENDIAN) {
            pXCP->pRespPacket[2] |= XCP_COMMMODEBASIC_BYTEORDER;
        }

        pXCP->pRespPacket[2] |= XCP_COMMMODEBASIC_OPTIONAL;

        /* Are we supporting slave block mode?
            if (m_bSlaveBlockModeAvailable == TRUE)
            {
                pXCP->pRespPacket[2] |= XCP_COMMMODEBASIC_SLAVEBLOCKMODE;
            }
        */

        pXCP->pRespPacket[3] = (uint8_t) pXCP->pConfig->MaxCTO;

        memcpy(&pXCP->pRespPacket[4], &pXCP->pConfig->MaxDTO, 2);

        pXCP->pRespPacket[6] = 1;   // Protocol major version
        pXCP->pRespPacket[7] = 1;   // Transport major version

        if (XCPServerSendResponse(pXCP, 8) != FALSE) {
            pXCP->bIsConnected = TRUE;
        }

        return;
    }

    if (pXCP->bIsConnected == FALSE) {
        // No active connection and not a connect message.   Don't process.
        return;
    }

    switch(CommandID) {
        case XCP_CMD_DISCONNECT:
            pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
            XCPServerResetConnection(pXCP);
            if (XCPServerSendResponse(pXCP, 1) != FALSE) {
            }
            break;
        case XCP_CMD_GET_STATUS:
            /* Response format:
                Data[1] = Session Status
                Data[2] = Resource Protection Status
                Data[3] = reserved (can have arbitrary value)
                Data[4,5] = Session Configuration ID.
            */
            pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
            pXCP->pRespPacket[1] = 0x00;

            for(DAQNum = 0; DAQNum<pXCP->pConfig->NumDAQSTIMLists; DAQNum++) {
                XCPSERVER_DAQ_LIST_T *pDAQList = &pXCP->pDAQLists[DAQNum];
                if (pDAQList->StartStopSelected == XCP_STARTSTOPDAQLIST_MODE_START) {
                    pXCP->pRespPacket[1] |= XCP_SESSIONSTATUS_DAQRUNNING;
                    break;
                }
            }

            pXCP->pRespPacket[2] = pXCP->LockedResourceStatus;
            pXCP->pRespPacket[3] = 0xFF;
            memcpy(&pXCP->pRespPacket[4], &pXCP->SessionConfigurationID, 2);

            XCPServerSendResponse(pXCP, 6);

            break;
        case XCP_CMD_SYNCH:
            XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNCH);
            break;
        case XCP_CMD_GET_COMM_MODE_INFO:
            {   // normal command processing.
                /* Response format
                Position    Type    Description
                0           BYTE    Packet ID: 0xFF
                1           BYTE    Reserved
                2           BYTE    COMM_MODE_OPTIONAL
                3           BYTE    Reserved
                4           BYTE    MAX_BS
                5           BYTE    MIN_ST
                6           BYTE    QUEUE_SIZE
                7           BYTE    XCP Driver Version Number
                */
                pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                pXCP->pRespPacket[1] = 0xFF;
                pXCP->pRespPacket[2] = 0x00;    // default, possibly changed below
                pXCP->pRespPacket[3] = 0xFF;    // reserved.
                pXCP->pRespPacket[4] = 0xFF;    // default, possibly changed below
                pXCP->pRespPacket[5] = 0xFF;    // default, possibly changed below
                pXCP->pRespPacket[6] = 0xFF;    // default, possibly changed below

                /*
                if (m_bMasterBlockModeAvailable != FALSE)
                {
                    pXCP->pRespPacket[2] |= XCP_COMMODEOPT_MASTERBLOCKMODE;
                    pXCP->pRespPacket[4] = m_MasterBlockModeBlockSize;
                    pXCP->pRespPacket[5] = m_MasterBlockModeMinSeparationTime;
                }
                if (m_bInterleavedModeAvailable != FALSE)
                {
                    pXCP->pRespPacket[2] |= XCP_COMMODEOPT_INTERLEAVEDMODE;
                    pXCP->pRespPacket[6] = m_InterleavedModeQueueSize;
                }
                */
                // driver version number.  Upper nibble is major version, lower nibble is minor version
                pXCP->pRespPacket[7] = 0x10; // Say 1.0
                XCPServerSendResponse(pXCP, 8);
            }
            break;
        //------------------------------------------------------------
        case XCP_CMD_GET_SEED:
            // if seed/key is enabled, the command should be supported
            /*
                Byte 0 = command code
                Byte 1 = Mode
                          0 = first part of seed
                          1 = remaining part of seed
                Byte 2 = Mode=0: Resource
                         Mode=1: Don't care
            */
            if (PacketLength < 3) {
                // CAN could be 8 bytes filled with FFs.
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
                return;
            }

            if (pPacket[1] == 0) {
                // Check Resource mask.
                // Check to make sure only one resource is being asked for.
                if ((pPacket[2] & XCP_RESOURCE_STIM) != 0) {
                    if ((pPacket[2] & (~XCP_RESOURCE_STIM)) != 0) {
                        // master requesting multiple resources
                        XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                        return;
                    }
                } else if ((pPacket[2] & XCP_RESOURCE_DAQ) != 0) {
                    if ((pPacket[2] & (~XCP_RESOURCE_DAQ)) != 0) {
                        // master requesting multiple resources
                        XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                        return;
                    }
                } else if ((pPacket[2] & XCP_RESOURCE_CALPAG) != 0) {
                    if ((pPacket[2] & (~XCP_RESOURCE_CALPAG)) != 0) {
                        // master requesting multiple resources
                        XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                        return;
                    }
                } else {
                    // No resource specified, or resource not supported.
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                    return;
                }

                XCPServerGetSeedAndKey(pXCP, pPacket[2]);
                if (pXCP->bKeyGenerated == FALSE) {
                    //  Couldn't generate a seed/key for some reason.  In this case anyone will be locked out.
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_TEMPNOACCESS);
                    return;
                }

                if (pXCP->CurrentSeedLength == 0) {
                    // Key was generated, and it is 0 length.  Likely using FPS to override.
                    pXCP->LockedResourceStatus &= ~pPacket[2];
                }

                pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                pXCP->pRespPacket[1] = pXCP->CurrentSeedLength;

                if (pXCP->CurrentSeedLength > pXCP->pConfig->MaxDTO - 2) {
                    TempU8 = pXCP->pConfig->MaxDTO - 2;
                } else {
                    TempU8 = pXCP->CurrentSeedLength;
                }
                memcpy(&pXCP->pRespPacket[2], &pXCP->CurrentSeed[0] ,TempU8);

                if (XCPServerSendResponse(pXCP, TempU8 + 2) != FALSE) {
                    pXCP->CurrentRemainingSeedLength = pXCP->CurrentSeedLength - TempU8;
                }
            } else if (pPacket[1] == 1) {
                // Mode 1.
                if (pXCP->CurrentRemainingSeedLength == 0) {
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_SEQUENCE);
                } else {
                    pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                    pXCP->pRespPacket[1] = pXCP->CurrentRemainingSeedLength;

                    if (pXCP->CurrentRemainingSeedLength > pXCP->pConfig->MaxDTO - 2) {
                        TempU8 = pXCP->pConfig->MaxDTO - 2;
                    } else {
                        TempU8 = pXCP->CurrentRemainingSeedLength;
                    }

                    memcpy(&pXCP->pRespPacket[2], &pXCP->CurrentSeed[pXCP->CurrentSeedLength - pXCP->CurrentRemainingSeedLength] ,TempU8);

                    if (XCPServerSendResponse(pXCP, TempU8 + 2) != FALSE) {
                        pXCP->CurrentRemainingSeedLength -= TempU8;
                    }
                }
            } else {
                // invalid
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
            }
            break;
        //------------------------------------------------------------
        case XCP_CMD_UNLOCK:
            /*
                Byte 0 : Command Code
                Byte 1 : (remaining) length of key in bytes.
                Byte 2.. MAX_CTO-1 : Key
            */
            if (PacketLength < 2) {
                // CAN could be 8 bytes filled with FFs.
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
                return;
            }

            if (pXCP->CurrentMasterKeyLength <= pPacket[1]) {
                pXCP->CurrentMasterKeyLength = pPacket[1];
                pXCP->CurrentMasterRemainingKeyLength = pPacket[1];
            } else if (pXCP->CurrentMasterRemainingKeyLength != pPacket[1]) {
                // Master has skipped some bytes or is confused.
                XCPServerSendErrorResponse(pXCP, XCP_ERR_SEQUENCE);
                return;
            }

            if (pPacket[1] > pXCP->pConfig->MaxCTO - 2) {
                TempU8 = pXCP->pConfig->MaxCTO - 2;
            } else {
                TempU8 = pPacket[1];
            }
            // TempU8 contains # of key bytes that should be in the packet.
            if (TempU8 > PacketLength - 2) {
                // Packet isn't long enough to contain the # of bytes indicated.
                // note PacketLength can be greater than TempU8 if on CAN and filling to 8 bytes with FFs.
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
                return;
            }

            memcpy(&pXCP->CurrentMasterKey[pXCP->CurrentMasterKeyLength - pXCP->CurrentMasterRemainingKeyLength], &pPacket[2], TempU8);
            pXCP->CurrentMasterRemainingKeyLength -= TempU8;

            if (pXCP->CurrentMasterRemainingKeyLength == 0) {
                if (XCPServerValidateKey(pXCP) == FALSE) {
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);

                    //!!! if we want to enforce a delay between unlock attempts, need to initialize
                    // the delay timer/counter here.
                    // According to XCP standard, we should now go to a disconnected state.
                    XCPServerResetConnection(pXCP);
                    return;
                }
            }

            pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
            pXCP->pRespPacket[1] = pXCP->LockedResourceStatus;

            XCPServerSendResponse(pXCP, 2);
            break;
        case XCP_CMD_SET_MTA:
            if (PacketLength != 8) {
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
            } else if ((pXCP->LockedResourceStatus & XCP_RESOURCE_CALPAG) != 0) {
                // Seed/key enabled and locked
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
            } else {
                // normal command processing.
                /*
                Position    Type    Description
                0           BYTE    Command Code = 0xF6
                1           WORD    Reserved
                3           BYTE    Address extension
                4           DWORD   Address
                */

                TempU8 = pPacket[3];
                memcpy(&TempU32, &pPacket[4], 4);

                if (XCPServerValidateMemory(pXCP, TempU32, TempU8) == FALSE) {
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_DENIED);
                    return;
                }

                pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                if (XCPServerSendResponse(pXCP, 1) != FALSE) {
                    pXCP->MTA = TempU32;
                    pXCP->MTAAddressExtension = TempU8;
                }
            }
            break;
        case XCP_CMD_UPLOAD:
            if (PacketLength < 2) {
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
                return;
            }
            /*
                Data[1] = n = Number of data elements [AG]
                                [1..MAX_CTO/AG -1] Standard mode
                                [1..255] Block mode
            */
            if ((pXCP->LockedResourceStatus & XCP_RESOURCE_CALPAG) != 0) {
                // Seed/key enabled and locked
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
            } else if (pXCP->MTA == 0) {
                // MTA hasn't been set yet.
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_DENIED);
            } else if (pXCP->pConfig->MaxDTO < pPacket[1] + 1) {
                // # of bytes requested won't fit in the response.
                XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
            } else {
                // normal command processing.

                // First make sure MTA is set to valid address for this command and the requested
                // range is valid.

                if (XCPServerValidateMemoryRange(pXCP, pXCP->MTA, pXCP->MTAAddressExtension, pPacket[1]) == FALSE) {
                    pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                    memset(&pXCP->pRespPacket[1], 0xFF, pPacket[1]);
                }
                else {
                    pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                    XCPServerReadMemoryFromMTA(pXCP, &pXCP->pRespPacket[1], pPacket[1]);
                }

                /*  UPLOAD and SHORT_UPLOAD response structure
                Position    Type        Description
                0           BYTE        Packet ID: 0xFF
                ..          BYTEs       Used for alignment only if AG > 1
                AG          ELEMENT 1   1st data element
                ..
                ..
                ..
                n*AG        ELEMENT n   nth data element
                */

                if (XCPServerSendResponse(pXCP, pPacket[1] + 1) != FALSE) {
                    // Sent.
                    pXCP->MTA += pPacket[1];
                    // Note, there isn't really any definition as what happens to the address extension
                    // if the MTA wraps.
                }
            }
            break;
        case XCP_CMD_SHORT_UPLOAD:
            /*
                Position    Type    Description
                0           BYTE    Command Code = 0xF4
                1           BYTE    n = Number of data elements [AG]
                                    [1..MAX_CTO/AG]
                2           BYTE    Reserved
                3           BYTE    Address extension
                4           DWORD   Address
            */
            if (PacketLength != 8) {
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
            } else if ((pXCP->LockedResourceStatus & XCP_RESOURCE_CALPAG) != 0) {
                // Seed/key enabled and locked
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
            } else {
                // normal command processing.

                TempU8 = pPacket[3];    // Address Extension
                memcpy(&TempU32, &pPacket[4], 4);
                /*  UPLOAD and SHORT_UPLOAD response structure
                Position    Type        Description
                0           BYTE        Packet ID: 0xFF
                ..          BYTEs       Used for alignment only if AG > 1
                AG          ELEMENT 1   1st data element
                ..
                ..
                ..
                n*AG        ELEMENT n   nth data element

                A data block of the specified length, starting at address will be returned.
                The MTA pointer is set to the first data byte behind the uploaded data block.
                This command does not support block transfer and it must not be used
                within a block transfer sequence.
                */
                NumElements = pPacket[1];

                if (pXCP->pConfig->MaxDTO < NumElements + 1) {
                    // # of bytes requested won't fit in the response.
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                    return;
                }

                pXCP->MTA = TempU32;
                pXCP->MTAAddressExtension = TempU8;

                if (XCPServerValidateMemoryRange(pXCP, TempU32, TempU8, NumElements) == FALSE) {
                    pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                    memset(&pXCP->pRespPacket[1], 0xFF, NumElements);
                }
                else {
                    pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                    XCPServerReadMemoryFromMTA(pXCP, &pXCP->pRespPacket[1], NumElements);
                }

                if (XCPServerSendResponse(pXCP, NumElements +1) == FALSE) {
                    pXCP->MTA += NumElements;
                }
            }
            break;
        case XCP_CMD_DOWNLOAD:
            // Not optional
            // normal command processing.
            /*
                Byte 0   : command code
                Byte 1   : # of elements
                Byte 2   : 1st data element
                Byte n+1 : nth data element
            */
            if ((pXCP->LockedResourceStatus & XCP_RESOURCE_CALPAG) != 0) {
                // Seed/key enabled and locked
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
            } else if (pXCP->MTA == 0) {
                // No address set.  Return error.
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_DENIED);
            } else {
                if (pPacket[1] +2 > PacketLength) {
                    // Packet isn't long enough to contain the data indicated
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
                } else if (PacketLength > pXCP->pConfig->MaxCTO) {
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                } else {
                    if (XCPServerValidateMemoryRange(pXCP, pXCP->MTA, pXCP->MTAAddressExtension, pPacket[1]) == FALSE) {
                        XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_DENIED);
                    } else {
                        XCPServerWriteMemoryToMTA(pXCP, &pPacket[2], pPacket[1]);
                        // MTA will be post incremented
                        pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;

                        if (XCPServerSendResponse(pXCP, 1 ) != FALSE) {
                            pXCP->MTA += pPacket[1];
                        }
                    }
                }
            }
            break;
        case XCP_CMD_SHORT_DOWNLOAD:
            //  optional
            /*
                Byte 0   : command code
                Byte 1   : # of elements
                Byte 2   : reserved
                Byte 3   : address extension
                Byte 4-7 : Address
                Byte 8.. :  data elements
            */
            if (pXCP->pConfig->SetupInfoType == XCP_XPORT_CAN) {
                // Note : this doesn't work on CAN.  CAN messages are too short to contain the data.
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_UNKNOWN);
                return;
            }

            if ((pXCP->LockedResourceStatus & XCP_RESOURCE_CALPAG) != 0) {
                // Seed/key enabled and locked
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
            } else {
                if (pPacket[1] + 8 != PacketLength) {
                    // Packet isn't long enough to contain the data.
                    // Since this isn't on CAN, the actual packet length should contain the data.
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
                } else if (PacketLength > pXCP->pConfig->MaxCTO) {
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                } else {
                    memcpy(&TempU32, &pPacket[4], 4);
                    TempU8 = pPacket[3];
                    if (XCPServerValidateMemoryRange(pXCP, TempU32, TempU8, pPacket[1]) == FALSE) {
                        XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_DENIED);
                    } else {
                        XCPServerWriteMemoryToMTA(pXCP, &pPacket[2], pPacket[1]);
                        // MTA will be post incremented
                        pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;

                        if (XCPServerSendResponse(pXCP, 1 ) != FALSE) {
                            pXCP->MTA += pPacket[1];
                        }
                    }
                }
            }
            break;
        case XCP_CMD_SET_CAL_PAGE:
            /*
                dawdyka note:
                I'm uncertain as to the practical implementation of this command.
                It might apply to calibration bank switching, which I'm not sure if Cat is using?
            */
            XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_UNKNOWN);
            break;
        case XCP_CMD_CLEAR_DAQ_LIST:
            // Not optional(if DAQ available and static?)
            if ((pXCP->LockedResourceStatus & XCP_RESOURCE_DAQ) != 0) {
                // Seed/key enabled and locked
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
            } else {
                /*  CLEAR_DAQ_LIST command format:
                    Position        Type    Description
                    0               BYTE    Command Code = 0xE3
                    1               BYTE    reserved
                    2               WORD    DAQ_LIST_NUMBER [0,1..MAX_DAQ-1]

                CLEAR_DAQ_LIST clears the specified DAQ list. For a configurable DAQ list,
                all ODT entries will be reset to address=0, extension=0 and size=0
                (if valid : bit_offset = 0xFF). For PREDEFINED and configurable DAQ lists,
                the running Data Transmission on this list will be stopped and all DAQ list
                states are reset.
                */

                if (PacketLength < 4) {
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
                }
                memcpy(&ListNum, &pPacket[2], 2);

                if (ListNum >= pXCP->pConfig->NumDAQSTIMLists) {
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                    return;
                }
                XCPServerClearDAQList(pXCP, &pXCP->pDAQLists[ListNum]);

                pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                XCPServerSendResponse(pXCP, 1);
            }
            break;
        case XCP_CMD_SET_DAQ_PTR:
            // Not optional(if DAQ available)
            if ((pXCP->LockedResourceStatus & XCP_RESOURCE_DAQ) != 0) {
                // Seed/key enabled and locked
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
            } else if (PacketLength < 6) {
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
            } else {
                /* SET_DAQ_PTR command format
                    Position        Type    Description
                    0               BYTE    Command Code = 0xE2
                    1               BYTE    Reserved
                    2               WORD    DAQ_LIST_NUMBER [0,1,..MAX_DAQ-1]
                    4               BYTE    ODT_NUMBER [0,1,..MAX_ODT(DAQ list)-1]
                    5               BYTE    ODT_ENTRY_NUMBER [0,1,..MAX_ODT_ENTRIES(DAQ list)-1]
                */
                memcpy(&TempU16, &pPacket[2], 2);
                // Note: DAQ_LIST_NUMBER is a 2 byte value, but since we're using absolute addressing,
                // our NumDAQLists is only a 1 byte value.
                if ((TempU16 >= pXCP->pConfig->NumDAQSTIMLists) ||
                    (pPacket[4] >= pXCP->pConfig->NumODTPerDAQSTIM) ||
                    (pPacket[5] >=  pXCP->pConfig->NumODTEntriesPerODT)) {
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                    return;
                }

                pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                if (XCPServerSendResponse(pXCP, 1) != FALSE) {
                    pXCP->DAQPtrListNumber = TempU16;
                    pXCP->DAQPtrODTNumber = pPacket[4];
                    pXCP->DAQPtrODTEntryNumber = pPacket[5];
                }

            }
            break;
        case XCP_CMD_WRITE_DAQ:
            // Not optional(if DAQ available)
            if ((pXCP->LockedResourceStatus & XCP_RESOURCE_DAQ) != 0) {
                // Seed/key enabled and locked
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
            } else if (PacketLength != 8) {
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
            }
            // double check DAQ list selection
            else if ((pXCP->DAQPtrListNumber >= pXCP->pConfig->NumDAQSTIMLists) ||
                     (pXCP->DAQPtrODTNumber >= pXCP->pConfig->NumODTPerDAQSTIM) ||
                     (pXCP->DAQPtrODTEntryNumber >=  pXCP->pConfig->NumODTEntriesPerODT)) {
                XCPServerSendErrorResponse(pXCP, XCP_ERR_WRITE_PROTECTED);
                return;
            } else if (pPacket[1] != 0xFF) {
                // bitwise operations not handled at the moment.  The standard does not
                // say how to respond if a bitwise operation is commanded when it is not supported.
                // BIT_STIM_SUPPORTED is specified in DAQ_PROPERTIES.
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);

            } else if (pPacket[2] > pXCP->pConfig->MaxODTEntrySizeDAQSTIM) {
                XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
            } else {
                XCPSERVER_DAQ_LIST_T *pDAQList = &pXCP->pDAQLists[pXCP->DAQPtrListNumber];
                XCPSERVER_ODT_T *pODT = &pDAQList->pODTs[pXCP->DAQPtrODTNumber];
                XCPSERVER_ODT_ENTRY_T *pODTEntry = &pODT->pODTEntries[pXCP->DAQPtrODTEntryNumber];

                if (pDAQList->StartStopSelected != XCP_STARTSTOPDAQLIST_MODE_STOP) {
                    // don't allow user to change DAQ list while not stopped.
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_SEQUENCE);
                    return;
                }
                /*  WRITE_DAQ command format
                Position    Type    Description
                0           BYTE    Command Code = 0xE1
                1           BYTE    BIT_OFFSET [0..31] Position of bit in 32-bit variable referenced by the address and extension below
                2           BYTE    Size of DAQ element [AG] 0<= size <=MAX_ODT_ENTRY_SIZE_x
                3           BYTE    Address extension of DAQ element
                4           DWORD   Address of DAQ element
                */

                TempU8 = pPacket[3];

                memcpy(&TempU32, &pPacket[4], 4);

                if (XCPServerValidateMemory(pXCP, TempU32, TempU8) == FALSE) {
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_DENIED);
                    return;
                }

                //pElement->BitOffset = pPacket[1];


                if (XCPServerValidateODT(pXCP, pODT,pPacket[2]) == FALSE) {
                    // User is requesting more data than will fit in the MAX_DTO
                    pODTEntry->NumBytes = 0;
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                    return;
                }

                pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                if (XCPServerSendResponse(pXCP, 1) != FALSE) {
                    pODTEntry->AddressExtension = TempU8;
                    pODTEntry->Address = TempU32;
                    pODTEntry->NumBytes = pPacket[2] ;
                    /*
                        The DAQ list pointer is auto post incremented to the next ODT entry
                        within one and the same ODT. After writing to the last ODT entry of
                        an ODT, the value of the DAQ pointer is undefined. The master has
                        to make sure the correct position of the DAQ pointer when writing
                        to the next ODT respectively the next DAQ list.
                    */

                    /*
                        The NumUsed parameters are set this way because by the standard there is
                        nothing forcing the Master to write to contiguous DAQ lists, ODTs, and ODT entries
                        or to write them in numerical order.
                        (although there are some provisions for stopping when the ODT entry length is 0)
                    */
                    if (pXCP->NumUsedDAQLists < pXCP->DAQPtrListNumber + 1) {
                        pXCP->NumUsedDAQLists = pXCP->DAQPtrListNumber + 1;
                    }

                    if (pDAQList->NumUsedODTs < pXCP->DAQPtrODTNumber + 1) {
                        pDAQList->NumUsedODTs = pXCP->DAQPtrODTNumber + 1;
                    }

                    if (pODT->NumUsedODTEntries < pXCP->DAQPtrODTEntryNumber + 1) {
                        pODT->NumUsedODTEntries = pXCP->DAQPtrODTEntryNumber + 1;
                    }

                    pXCP->DAQPtrODTEntryNumber++;
                }
            }
            break;
        case XCP_CMD_SET_DAQ_LIST_MODE:
            // Not optional(if DAQ available)
            if (PacketLength != 8) {
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
            } else {
                if (pPacket[1] & XCP_SETDAQLISTMODE_MODE_DIRECTION) {
                    // STIM
                    if ((pXCP->LockedResourceStatus & XCP_RESOURCE_STIM) != 0) {
                        // Seed/key enabled and locked
                        XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
                        return;
                    }
                } else {
                    // DAQ
                    if ((pXCP->LockedResourceStatus & XCP_RESOURCE_DAQ) != 0) {
                        // Seed/key enabled and locked
                        XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
                        return;
                    }
                }


                /* SET_DAQ_LIST_MODE Command format:
                    Position        Type    Description
                    0               BYTE    Command Code = 0xE0
                    1               BYTE    Mode
                    2               WORD    DAQ_LIST_NUMBER [0,1,..MAX_DAQ-1]
                    4               WORD    Event channel number [0,1,..MAX_EVENT_CHANNEL-1]
                    6               BYTE    Transmission rate prescaler (=>1)
                    7               BYTE    DAQ list priority (FF Highest)
                */

                memcpy(&ListNum, &pPacket[2], 2);

                if ((ListNum >= pXCP->pConfig->NumDAQSTIMLists) ||
                    (pPacket[6] == 0)) {  // prescaler cannot be 0.
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                    return;
                }
                // Validate requested mode

                if (((pPacket[1] & XCP_SETDAQLISTMODE_MODE_ALTERNATING) != 0) || // not allowing alternating mode
                    ((pPacket[1] & XCP_SETDAQLISTMODE_MODE_TIMESTAMP) != 0) || // or timestamps
                    ((pPacket[1] & XCP_SETDAQLISTMODE_MODE_PID_OFF) != 0)) { // or PID_OFF
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_MODE_NOT_VALID);
                    return;
                }

                // Validate requested event

                memcpy(&EventNum, &pPacket[4], 2);

                // Is this event valid for this DAQ list?
                // Presently any valid event is valid for any DAQ list, with no limit on # of DAQs that
                // the event can be used with.

                if (EventNum >= pXCP->pConfig->NumEvents) {
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                    return;
                }

                /*
                 * Not supporting priority at this time.
                 *
                 * pPacket[7] can be anything and it is ignored
                 *
                 * dawdyka note:
                 *  The XCP 1.1 Part 2 standard states that:
                 *  "If the ECU doesn�t support the prioritization of DAQ lists , a DAQ list
                 *  priority > 0 is not allowed and will be indicated by returning ERR_OUT_OF_RANGE."
                 *
                 * While this is what the standard states, it goes against graceful support of
                 * different tools.  The tool/end user is going to have to live with what this
                 * server supports either way, and reporting an error that further complicates
                 * the use of the tools is not productive.  If this causes issues with certain
                 * tools, then remove the check and allow the user to specify any priority but
                 * ignore it.
                 *
                 * shattar note:
                 *  As dawdyka predicted, this caused issues with certain tools (CANape 16 SP7)
                 *  CANape 16 SP6 works fine, but for some reason Vector changed it in SP7 to
                 *  specify a priority of 255 instead of 0.
                 */

                pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                if (XCPServerSendResponse(pXCP, 1) != FALSE) {
                    if ((pPacket[1] & XCP_SETDAQLISTMODE_MODE_DIRECTION) != 0) {
                        pXCP->pDAQLists[ListNum].Direction = XCPSERVER_DAQLIST_DIRECTION_STIM;
                    } else {
                        pXCP->pDAQLists[ListNum].Direction = XCPSERVER_DAQLIST_DIRECTION_DAQ;
                    }

                    pXCP->pDAQLists[ListNum].EventID = EventNum;
                    // Note, prescaler only used for DAQ, not STIM
                    pXCP->pDAQLists[ListNum].Prescaler = pPacket[6];
                    // Priority not used at this time.
                }
            }
            break;
        case XCP_CMD_START_STOP_DAQ_LIST:
            // Not optional.
            if ((pXCP->LockedResourceStatus & XCP_RESOURCE_DAQ) != 0) {
                // Seed/key enabled and locked
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
            } else if (PacketLength < 4) {
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
            } else  {
                /* START_STOP_DAQ_LIST command format:
                    Position        Type    Description
                    0               BYTE    Command Code = 0xDE
                    1               BYTE    Mode 00 = stop 01 = start 02 = select
                    2               WORD    DAQ_LIST_NUMBER [0,1,..MAX_DAQ-1]
                */
                memcpy(&ListNum, &pPacket[2], 2);
                if (ListNum >= pXCP->pConfig->NumDAQSTIMLists) {
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                    return;
                }

                if ((pPacket[1] != XCP_STARTSTOPDAQLIST_MODE_STOP) &&
                    (pPacket[1] != XCP_STARTSTOPDAQLIST_MODE_START) &&
                    (pPacket[1] != XCP_STARTSTOPDAQLIST_MODE_SELECT)) {
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                    return;
                }


                pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                pXCP->pRespPacket[1] = pXCP->pDAQLists[ListNum].FirstPID ;// First PID

                if (XCPServerSendResponse(pXCP, 2) != FALSE) {
                    if (pPacket[1] == XCP_STARTSTOPDAQLIST_MODE_START) {
                        XCPServerPrepDAQListForStart(pXCP, &pXCP->pDAQLists[ListNum]);
                    }
                    pXCP->pDAQLists[ListNum].StartStopSelected = pPacket[1];
                }
            }
            break;
        case XCP_CMD_START_STOP_SYNCH:
            // Not optional
            if ((pXCP->LockedResourceStatus & XCP_RESOURCE_DAQ) != 0) {
                // Seed/key enabled and locked
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
            } else if (PacketLength < 2) {
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
            } else {
                /*  START_STOP_SYNCH command format:
                    Position        Type    Description
                    0               BYTE    Command Code = 0xDD
                    1               BYTE    Mode 00 = stop all 01 = start selected 02 = stop selected
                */
                if ((pPacket[1] != XCP_STARTSTOPSYNCH_STOPALL) &&
                    (pPacket[1] != XCP_STARTSTOPSYNCH_STARTSEL) &&
                    (pPacket[1] != XCP_STARTSTOPSYNCH_STOPSEL)) {
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                    return;
                }

                pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                if (XCPServerSendResponse(pXCP, 1) != FALSE) {
                    XCPServerStartStopSynchSelected(pXCP, pPacket[1]);
                }
            }
            break;
        case XCP_CMD_GET_DAQ_PROCESSOR_INFO:
            if ((pXCP->LockedResourceStatus & XCP_RESOURCE_DAQ) != 0) {
                // Seed/key enabled and locked
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
            } else {
                // normal command processing.
                /* GET_DAQ_PROCESSOR_INFO response format
                    Position        Type    Description
                    0               BYTE    Packet ID: 0xFF
                    1               BYTE    DAQ_PROPERTIES  General properties of DAQ lists
                    2               WORD    MAX_DAQ Total number of available DAQ lists
                    4               WORD    MAX_EVENT_CHANNEL   Total number of available event channels
                    6               BYTE    MIN_DAQ Total number of predefined DAQ lists
                    7               BYTE    DAQ_KEY_BYTE


                    !!! if TIMESTAMP_SUPPORTED, and TIMESTAMP flag at SET_DAQ_LIST_MODE or
                        TIMESTAMP_FIXED flag in TIMESTAMP_MODE at GET_DAQ_RESOLUTION_INFO
                        then message with first ODT for the DAQ list has to contain TIMESTAMP.
                        On CAN, this will prevent us from using a full 7/8 bytes for the first ODT.
                        Standard really doesn't say anything about handling this.
                        Master would have to figure if using TIMESTAMP, then size of timestamp
                        would reduce the # of available bytes for the first ODT for that DAQ list.

                */
                pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;

                // DAQ Properties.
                // Overload Event = 0;  Overload MSB = 0;  No overload indication.
                // PID_OFF_SUPPORTED = 0;
                // TIMESTAMP_SUPPORTED = 0;
                // BIT_STIM_SUPPORTED = 0;
                // RESUME_SUPPORTED = 0;
                // DAQ_CONFIG_TYPE = 0;  Static.
                pXCP->pRespPacket[1] = XCP_DAQPROCINFO_PRESCALERSUPPORTED;

                TempU16 = pXCP->pConfig->NumDAQSTIMLists;
                memcpy(&pXCP->pRespPacket[2], &TempU16, 2);

                TempU16 = pXCP->pConfig->NumEvents;
                memcpy(&pXCP->pRespPacket[4], &TempU16, 2);

                pXCP->pRespPacket[6] = 0;  // No predefined lists.

                // Note the following values are technically all 0, but showing them here to be explicit.
                pXCP->pRespPacket[7] = (XCP_IDFIELD_ABSOLUTEODTNUM << 6) | (XCP_ADDEXT_DIFFERENTINODT << 4) | XCP_OPTIMIZATION_DEFAULT;

                XCPServerSendResponse(pXCP, 8);
            }
            break;

        case XCP_CMD_GET_DAQ_RESOLUTION_INFO:
            if ((pXCP->LockedResourceStatus & XCP_RESOURCE_DAQ) != 0) {
                // Seed/key enabled and locked
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
            } else {
                // normal command processing.
                /*
                    Data[0] = packet ID 0xFF
                    Data[1] = GRANULARITY_ODT_ENTRY_SIZE_DAQ
                    Data[2] = MAX_ODT_ENTRY_SIZE_DAQ
                    Data[3] = GRANULARITY_ODT_ENTRY_SIZE_STIM
                    Data[4] = MAX_ODT_ENTRY_SIZE_STIM
                    Data[5] = TIMESTAMP_MODE
                    Data[6,7] = TIMESTAMP_TICKS
                */
                pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                pXCP->pRespPacket[1] = 1;
                pXCP->pRespPacket[2] = pXCP->pConfig->MaxODTEntrySizeDAQSTIM;
                pXCP->pRespPacket[3] = 1;
                pXCP->pRespPacket[4] = pXCP->pConfig->MaxODTEntrySizeDAQSTIM;
                pXCP->pRespPacket[5] = 0x00;    // No timestamp supported, so 0.
                pXCP->pRespPacket[6] = 0xFF;
                pXCP->pRespPacket[7] = 0xFF;

                XCPServerSendResponse(pXCP, 8);
            }
            break;
        case XCP_CMD_GET_DAQ_LIST_INFO:
            if ((pXCP->LockedResourceStatus & XCP_RESOURCE_DAQ) != 0) {
                // Seed/key enabled and locked
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
            } else if (PacketLength < 4) {
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
            } else {
                // normal command processing.
                /*  GET_DAQ_LIST_INFO command format
                    Position        Type        Description
                    0               BYTE        Command Code = 0xD8
                    1               BYTE        reserved
                    2               WORD        DAQ_LIST_NUMBER [0,1,...,MAX_DAQ-1]
                */
                memcpy(&ListNum, &pPacket[2], 2);

                if (ListNum >= pXCP->pConfig->NumDAQSTIMLists) {
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                    return;
                }

                /* GET_DAQ_LIST_INFO response format
                    Position        Type    Description
                    0               BYTE    Packet ID: 0xFF
                    1               BYTE    DAQ_LIST_PROPERTIES
                                            Specific properties for this DAQ list
                    2               BYTE    MAX_ODT
                                            Number of ODTs in this DAQ list
                    3               BYTE    MAX_ODT_ENTRIES
                                            Maximum number of entries in an ODT
                    4               WORD    FIXED_EVENT Number of the fixed event channel for this DAQ list
                */
                pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                pXCP->pRespPacket[1] = XCP_DAQLISTINFO_DAQLISTPROP_DAQ; // No stim, DAQ supported, event and daq both configurable.

                pXCP->pRespPacket[2] = pXCP->pConfig->NumODTPerDAQSTIM;
                pXCP->pRespPacket[3] = pXCP->pConfig->NumODTEntriesPerODT;
// No fixed event.  Fill with 0 for known value.
                pXCP->pRespPacket[4] = 0;
                pXCP->pRespPacket[5] = 0;
//              memcpy(&pXCP->pRespPacket[4], &pXCP->pDAQLists[ListNum].EventID, 2);

                XCPServerSendResponse(pXCP, 6);
            }
            break;
        case XCP_CMD_GET_DAQ_EVENT_INFO:
            /*
                Byte 0 : Command Code = 0xD7
                Byte 1 : Reserved
                Byte 2,3 : Event channel number
            */
            /* do we support this or not?
                The main issue is that this command automatically sets the Memory Transfer Address (MTA)
                to the address of the event channel name, so the master can upload this name
                using one or more UPLOAD commands.
                The issue is that UPLOAD is not a DAQSTIM command, and so it doesn't fall under
                the DAQSTIM seed/key unlock umbrella.
                According to the protocol standard, UPLOAD is a basic command, and doesn't fall under the CAL seed/key
                umbrella either, but we're essentially going to force a tool to do CAL unlock if it wants
                to do any UPLOAD.
                If we say the channel name length is unavailable, then technically we don't need to worry about
                an UPLOAD attempt following this command.
            */
            if ((pXCP->LockedResourceStatus & XCP_RESOURCE_DAQ) != 0) {
                // Seed/key enabled and locked
                XCPServerSendErrorResponse(pXCP, XCP_ERR_ACCESS_LOCKED);
            } else if (PacketLength < 4) {
                XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_SYNTAX);
            } else {
                memcpy(&EventNum, &pPacket[2], 2);
                if (EventNum >= pXCP->pConfig->NumEvents) {
                    XCPServerSendErrorResponse(pXCP, XCP_ERR_OUT_OF_RANGE);
                    return;
                }
                /*
                    Response:
                        Byte 0 : Packet ID: 0xFF
                        Byte 1 : DAQ_EVENT_PROPERTIES
                        Byte 2 : MAX_DAQ_LIST
                        Byte 3 : EVENT_CHANNEL_NAME_LENGTH
                        Byte 4 : EVENT_CHANNEL_TIME_CYCLE
                        Byte 5 : EVENT_CHANNEL_TIME_UNIT
                        Byte 6 : EVENT_CHANNEL_PRIORITY
                */
                pXCP->pRespPacket[0] = XCP_SLAVE_CMD_RESP_PACKET;
                pXCP->pRespPacket[1] = XCP_EVENTPROP_CONSISTENCY_EVENT | XCP_EVENTPROP_STIM | XCP_EVENTPROP_DAQ;
                pXCP->pRespPacket[2] = 0xFF; // No limitation

                if (0 == EventNum) {
                    // Setting name length to 8 for "BaseRate"
                    pXCP->pRespPacket[3] = XCPSERVER_EVENT_NAME_LENGTH;
                    pXCP->MTA = 0xFFFFFFFF;
                    pXCP->MTAAddressExtension = 0;
                }
                else {
                    pXCP->pRespPacket[3] = 0; // No length. Not available.
                }

                pXCP->pRespPacket[4] = pXCP->pConfig->EventInfo[EventNum].TimeCycle;
                pXCP->pRespPacket[5] = pXCP->pConfig->EventInfo[EventNum].TimeUnit;
                pXCP->pRespPacket[6] = 0xFF; // Priority = 0xFF.  All events are of the highest priority.
                                                // Note, this is a fixed attribute and not configurable, so only
                                                // reporting this for informational purposes.  Could have the user
                                                // set a priority based on implied priority of the various threads,
                                                // but that is overly complicating things.  The actual priority of the
                                                // events will be based upon the priority of the threads/tasks.
                XCPServerSendResponse(pXCP, 7);
            }

            break;
        default:
            // Not one of the explicitly handled commands.
            XCPServerSendErrorResponse(pXCP, XCP_ERR_CMD_UNKNOWN);
            break;
    }
}

/******************************************************************************
Function Name: XCPServerSendDAQ

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static void XCPServerSendDAQ(XCPServer_t *pXCP, XCPSERVER_DAQ_LIST_T *pDAQList)
{
    uint8_t ODTNum;
    uint8_t ODTEntryNum;
    XCPSERVER_ODT_T *pODT;
    XCPSERVER_ODT_ENTRY_T *pODTEntry;
    uint8_t *pPacket;

    /*
        From ASAM_XCP_Part1-Overview_V1-1-0, section 1.1.3.1

        "When processing an ODT, the slave can go to the next ODT as soon as it finds an
        element with size = 0 in the current ODT or all ODT entries of this ODT have been
        processed.

        When processing a DAQ list, the slave can go to the next DAQ list as
        soon as it finds an element with size = 0 at the first ODT entry of the first ODT
        of this DAQ list or all ODTs of this DAQ list have been processed."

    */

    for(ODTNum = 0; ODTNum < pDAQList->NumUsedODTs; ODTNum++) {
        pODT = &pDAQList->pODTs[ODTNum];
        pPacket = pODT->pDAQPacket;
        *(pPacket++) = pODT->PID;

        if (pODT->PacketLength != 0) {
            for(ODTEntryNum = 0; ODTEntryNum < pODT->NumUsedODTEntries; ODTEntryNum++) {
                pODTEntry = &pODT->pODTEntries[ODTEntryNum];
                if (pODTEntry->NumBytes == 0) {
                    break;
                }

                XCPServerReadODTEntry(pXCP, pODTEntry, pPacket);
                pPacket += pODTEntry->NumBytes;
            }

            switch(pXCP->pConfig->SetupInfoType) {
                case XCP_XPORT_UDP:
                    XCPServerSendUDPResp(pXCP, pODT->pDAQMessageBuf, pODT->PacketLength);
                    break;
                case XCP_XPORT_CAN:
                    XCPServerSendCANResp(pXCP, pODT->pDAQMessageBuf, pODT->PacketLength);
                    break;
                default:
                    return;
            }
        }
    }
}

/******************************************************************************
Function Name: XCPServerValidateDAQ

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
/* static BOOL XCPServerValidateDAQ(XCPServer_t *pXCP, XCPSERVER_DAQ_LIST_T *pDAQList)
{
    uint8_t ODTNum;

    for(ODTNum = 0; ODTNum < pDAQList->NumUsedODTs; ODTNum++) {
        if (XCPServerValidateODT(pXCP, &pDAQList->pODTs[ODTNum],0) == FALSE) {
            return(FALSE);
        }
    }
    return(TRUE);
}*/

/******************************************************************************
Function Name: XCPServerValidateODT

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static BOOL XCPServerValidateODT(XCPServer_t *pXCP, XCPSERVER_ODT_T *pODT, uint8_t NumAdditionalBytes)
{
    // Validate that the ODT setup will exceed the MAX_DTO.
    uint8_t ODTEntryNum;
    /*
        Since using only Absolute addressing, no timestamps, and no PID_OFF, then
        header of DAQ is only 1 byte.
    */
    uint16_t PacketLength = 1 + NumAdditionalBytes;

    for(ODTEntryNum = 0; ODTEntryNum < pODT->NumUsedODTEntries; ODTEntryNum++) {
        PacketLength += pODT->pODTEntries[ODTEntryNum].NumBytes;
    }

    if (PacketLength > pXCP->pConfig->MaxDTO) {
        // Data will be too long to fit within the MAX_DTO.
        // Do not send.
        pODT->PacketLength = 0;
        return(FALSE);
    }

    pODT->PacketLength = PacketLength;

    return(TRUE);

}


/******************************************************************************
Function Name: XCPServerWriteSTIMDAQ

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static void XCPServerWriteSTIMDAQ(XCPServer_t *pXCP, XCPSERVER_DAQ_LIST_T *pDAQList)
{
    // copy data from ODT Packets into actual memory.
    uint8_t ODTNum;
    uint8_t ODTEntryNum;
    XCPSERVER_ODT_T *pODT;
    XCPSERVER_ODT_ENTRY_T *pODTEntry;
    uint8_t *pPacket;

    for(ODTNum = 0; ODTNum < pDAQList->NumUsedODTs; ODTNum++) {
        pODT = &pDAQList->pODTs[ODTNum];
        pPacket = &pODT->pDAQPacket[1];

        if (pODT->bSTIMReceived) {
            for(ODTEntryNum = 0; ODTEntryNum < pODT->NumUsedODTEntries; ODTEntryNum++) {
                pODTEntry = &pODT->pODTEntries[ODTEntryNum];
                if (pODTEntry->NumBytes != 0) {
                    XCPServerWriteODTEntry(pXCP, &pODT->pODTEntries[ODTEntryNum], pPacket);
                    pPacket += pODTEntry->NumBytes;
                }
            }
            pODT->bSTIMReceived = FALSE;
        }
    }
}

/******************************************************************************
Function Name: XCPServerSendResponse

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static BOOL XCPServerSendResponse(XCPServer_t *pXCP, uint16_t PacketLength)
{
    switch(pXCP->pConfig->SetupInfoType) {
        case XCP_XPORT_UDP:
            return(XCPServerSendUDPResp(pXCP, pXCP->pRespMessageBuf, PacketLength));
        case XCP_XPORT_CAN:
            return(XCPServerSendCANResp(pXCP, pXCP->pRespMessageBuf, PacketLength));
        default:
            return(FALSE);
    }
}

/******************************************************************************
Function Name: XCPServerSendCANResp

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static BOOL XCPServerSendCANResp(XCPServer_t *pXCP, uint8_t *pMsgBuf, uint16_t PacketLength)
{
    // PacketLength data at pXCP->pRespMessageBuf
    // Add 2 or 4 byte header based on CAN ID length and send.

    // pXCP->pRespMessageBuf was preloaded at init, since it never changes.
    // send pMsgBuf on CAN with length = PacketLength + pXCP->RespHeaderLength;

    return(XCPHALCANSend(pXCP, pMsgBuf, PacketLength + pXCP->RespHeaderLength));
}

/******************************************************************************
Function Name: XCPServerSendUDPResp

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static BOOL XCPServerSendUDPResp(XCPServer_t *pXCP,  uint8_t *pMsgBuf, uint16_t PacketLength)
{
    // PacketLength data at pXCP->pRespPacket
    // Add 4 byte header to pRespMessageBuf and send.

    // Need a socket to send on.  Send to UDPMasterIP, UDPMasterPort

    // Header is {uint16_t Packet Length, uint16_t Count}, always LSB first.
    pMsgBuf[0] = (uint8_t) PacketLength;
    pMsgBuf[1] = (PacketLength >> 8);
    pMsgBuf[2] = (uint8_t) pXCP->DTOCounter;
    pMsgBuf[3] = (uint8_t) (pXCP->DTOCounter >> 8);

    // Send pRespMessageBuf with PacketLength + 4 message on UDP socket here.
    if (XCPHALUDPSend(pXCP, pMsgBuf, PacketLength + 4, pXCP->UDPMasterIP, pXCP->UDPMasterPort)) {
        pXCP->DTOCounter++;
        return(TRUE);
    }
    return(FALSE);
}

/******************************************************************************
Function Name: XCPServerSendErrorResponse

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static BOOL XCPServerSendErrorResponse(XCPServer_t *pXCP, uint8_t ErrorCode)
{
    pXCP->pRespPacket[0] = XCP_SLAVE_ERROR_PACKET;
    pXCP->pRespPacket[1] = ErrorCode;

    return(XCPServerSendResponse(pXCP, 2));
}

/******************************************************************************
Function Name: XCPServerGetSeedAndKey

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static void XCPServerGetSeedAndKey(XCPServer_t *pXCP, uint8_t Resource)
{
    pXCP->CurrentSeedKeyResource = Resource;
    pXCP->bKeyGenerated = TRUE;

    //pXCP->CurrentSeedLength = 0;

    // Throwing in an actual seed/key here for testing.   Replace with actual dynamic seed/key generation.
    pXCP->CurrentSeedLength = 16;

    // seed: 02 7A A4 44 93 67 00 00 00 00 00 00 00 00 00 00
    // Key:  27 1D 3D 0E 3F 31 AD 12 E5 10 82 59 09 20 3E F7
    pXCP->CurrentSeed[0] = 0x02;
    pXCP->CurrentSeed[1] = 0x7A;
    pXCP->CurrentSeed[2] = 0xA4;
    pXCP->CurrentSeed[3] = 0x44;
    pXCP->CurrentSeed[4] = 0x93;
    pXCP->CurrentSeed[5] = 0x67;
    pXCP->CurrentSeed[6] = 0x00;
    pXCP->CurrentSeed[7] = 0x00;
    pXCP->CurrentSeed[8] = 0x00;
    pXCP->CurrentSeed[9] = 0x00;
    pXCP->CurrentSeed[10] = 0x00;
    pXCP->CurrentSeed[11] = 0x00;
    pXCP->CurrentSeed[12] = 0x00;
    pXCP->CurrentSeed[13] = 0x00;
    pXCP->CurrentSeed[14] = 0x00;
    pXCP->CurrentSeed[15] = 0x00;

    pXCP->CurrentActualKeyLength = 16;
    pXCP->CurrentActualKey[0] = 0x27;
    pXCP->CurrentActualKey[1] = 0x1D;
    pXCP->CurrentActualKey[2] = 0x3D;
    pXCP->CurrentActualKey[3] = 0x0E;
    pXCP->CurrentActualKey[4] = 0x3F;
    pXCP->CurrentActualKey[5] = 0x31;
    pXCP->CurrentActualKey[6] = 0xAD;
    pXCP->CurrentActualKey[7] = 0x12;
    pXCP->CurrentActualKey[8] = 0xE5;
    pXCP->CurrentActualKey[9] = 0x10;
    pXCP->CurrentActualKey[10] = 0x82;
    pXCP->CurrentActualKey[11] = 0x59;
    pXCP->CurrentActualKey[12] = 0x09;
    pXCP->CurrentActualKey[13] = 0x20;
    pXCP->CurrentActualKey[14] = 0x3E;
    pXCP->CurrentActualKey[15] = 0xF7;

    /*
        Generate Seed and Key here.
        Populate pXCP->CurrentSeedLength;
        Populate pXCP->CurrentSeed;
        Populate pXCP->CurrentActualKeyLength;
        Populate pXCP->CurrentActualKey;

        if ActualKey generated without issue, then set pXCP->bKeyGenerated
    */
}

/******************************************************************************
Function Name: XCPServerValidateKey

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static BOOL XCPServerValidateKey(XCPServer_t *pXCP)
{
    // Compare
    //   pXCP->CurrentActualKey;
    if (pXCP->bKeyGenerated == FALSE) {
        // Server has sent a key, but no key has been generated.
        return(FALSE);
    }

    if (pXCP->CurrentMasterKeyLength == pXCP->CurrentActualKeyLength) {
        if (memcmp(pXCP->CurrentMasterKey, pXCP->CurrentActualKey, pXCP->CurrentActualKeyLength) == 0) {
            // Key matches.
            pXCP->LockedResourceStatus &= ~pXCP->CurrentSeedKeyResource;
            return(TRUE);
        }
    }
    /*
        Note, for CCP there was a lockout strategy that temporarily locked out
        UNLOCK retries for a period of time after a failed unlock attempt.

        This was to prevent brute force attempts at unlocking the ECM.
        A similar strategy may need to be adopted here.
    */
    // Failed. Force client to redo GET_SEED and generate a new key.
    pXCP->bKeyGenerated = FALSE;

    return(FALSE);
}

/******************************************************************************
Function Name: XCPServerValidateMemory

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static BOOL XCPServerValidateMemory(XCPServer_t *pXCP, uint32_t Address, uint8_t AddressExtension)
{
    return XCPServerValidateMemoryRange(pXCP, Address, AddressExtension, 0);
}

/******************************************************************************
Function Name: XCPServerValidateMemoryRange

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static BOOL XCPServerValidateMemoryRange(XCPServer_t *pXCP, uint32_t Address, uint8_t AddressExtension, uint8_t NumBytes)
{
    if ((0xFFFFFFFF == Address) && (XCPSERVER_EVENT_NAME_LENGTH == NumBytes)) {
        return TRUE;
    }

    return XCPServer_memValidate(pXCP, Address, AddressExtension, NumBytes);
}

/******************************************************************************
Function Name: XCPServerReadMemoryFromMTA

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static void XCPServerReadMemoryFromMTA(XCPServer_t *pXCP, uint8_t *pDest, uint8_t NumBytes)
{
    if ((0xFFFFFFFF == pXCP->MTA) && (XCPSERVER_EVENT_NAME_LENGTH == NumBytes)) {
        memcpy(pDest, "BaseRate", XCPSERVER_EVENT_NAME_LENGTH);
        return;
    }

    XCPServer_memRead(pXCP, pXCP->MTA, pXCP->MTAAddressExtension, pDest, NumBytes);
}

/******************************************************************************
Function Name: XCPServerWriteMemoryToMTA

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static void XCPServerWriteMemoryToMTA(XCPServer_t *pXCP, uint8_t const * pSrc, uint8_t NumBytes)
{
    XCPServer_memWrite(pXCP, pXCP->MTA, pXCP->MTAAddressExtension, pSrc, NumBytes);
}

/******************************************************************************
Function Name: XCPServerReadODTEntry

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static void XCPServerReadODTEntry(XCPServer_t *pXCP, XCPSERVER_ODT_ENTRY_T *pODTEntry, uint8_t *pDest)
{
    XCPServer_memRead(pXCP, pODTEntry->Address, pODTEntry->AddressExtension, pDest, pODTEntry->NumBytes);
}

/******************************************************************************
Function Name: XCPServerWriteODTEntry

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static void XCPServerWriteODTEntry(XCPServer_t *pXCP, XCPSERVER_ODT_ENTRY_T *pODTEntry, uint8_t *pSrc)
{
    XCPServer_memWrite(pXCP, pODTEntry->Address, pODTEntry->AddressExtension, pSrc, pODTEntry->NumBytes);
}

/******************************************************************************
Function Name: XCPServerClearDAQList

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static void XCPServerClearDAQList(XCPServer_t *pXCP, XCPSERVER_DAQ_LIST_T *pDAQList)
{
    uint8_t ODTNum, ODTEntryNum;
    XCPSERVER_ODT_T *pODT;
    XCPSERVER_ODT_ENTRY_T *pODTEntry;

    pDAQList->Direction = XCPSERVER_DAQLIST_DIRECTION_DAQ;
    pDAQList->StartStopSelected = XCP_STARTSTOPDAQLIST_MODE_STOP;
    pDAQList->Prescaler = 0;
    pDAQList->EventCount = 0;

    for(ODTNum = 0; ODTNum < pXCP->pConfig->NumODTPerDAQSTIM; ODTNum++) {
        pODT = &pDAQList->pODTs[ODTNum];
        for(ODTEntryNum = 0; ODTEntryNum < pXCP->pConfig->NumODTEntriesPerODT; ODTEntryNum++) {
            pODTEntry = &pODT->pODTEntries[ODTEntryNum];
            memset(pODTEntry, 0, sizeof(XCPSERVER_ODT_ENTRY_T));
        }
        pODT->PacketLength = 0;
        pODT->NumUsedODTEntries = 0;
    }
    pDAQList->NumUsedODTs = 0;
}

/******************************************************************************
Function Name: XCPServerStartStopSynchSelected

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static void XCPServerStartStopSynchSelected(XCPServer_t *pXCP, uint8_t Mode)
{   //Mode 00 = stop all 01 = start selected 02 = stop selected
    uint16_t DAQListNum;

    for (DAQListNum=0; DAQListNum < pXCP->pConfig->NumDAQSTIMLists; DAQListNum++) {
        XCPSERVER_DAQ_LIST_T *pDAQList = &pXCP->pDAQLists[DAQListNum];
        if (Mode == XCP_STARTSTOPSYNCH_STOPALL) {
            pDAQList->StartStopSelected = XCP_STARTSTOPDAQLIST_MODE_STOP;
        } else {
            if (pDAQList->StartStopSelected == XCP_STARTSTOPDAQLIST_MODE_SELECT) {
                if (Mode == XCP_STARTSTOPSYNCH_STARTSEL) {
                    XCPServerPrepDAQListForStart(pXCP, pDAQList);
                    pDAQList->StartStopSelected = XCP_STARTSTOPDAQLIST_MODE_START;
                } else if (Mode == XCP_STARTSTOPSYNCH_STOPSEL) {
                    pDAQList->StartStopSelected = XCP_STARTSTOPDAQLIST_MODE_STOP;
                }
            }
        }
    }
}

/******************************************************************************
Function Name: XCPServerProcSTIMPacket

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static void XCPServerProcSTIMPacket(XCPServer_t *pXCP, uint8_t *pPacket, uint16_t PacketLength)
{
    XCPSERVER_DAQ_LIST_T *pDAQList;
    XCPSERVER_ODT_T *pODT;
    uint8_t DAQNum, ODTNum;

    if ((pXCP->LockedResourceStatus &  XCP_RESOURCE_STIM) != 0) {
        // STIM not unlocked.  Access denied.
        return;
    }

    // pPacket[0] should be STIM ID, absolute ODT.
    if (pXCP->pConfig->NumDAQSTIMLists == 0) {
        // prevent divide by 0
        return;
    }

    // if we don't want to do the divides here, would need a lookup table based on PID.
    // Table could also support prevalidation of direction, started, DAQ/ODT num
    //  assuming lookup provides a null pointer if invalid PID

    DAQNum = pPacket[0] / pXCP->pConfig->NumODTPerDAQSTIM;
    ODTNum = pPacket[0] % pXCP->pConfig->NumODTPerDAQSTIM;

    if ((DAQNum >= pXCP->NumUsedDAQLists)) {
        // Invalid DAQ num
        return;
    }

    pDAQList = &pXCP->pDAQLists[DAQNum];

    if ((pDAQList->Direction != XCPSERVER_DAQLIST_DIRECTION_STIM) &&
        (pDAQList->StartStopSelected == XCP_STARTSTOPDAQLIST_MODE_START)) {
        // DAQ list direction is not STIM, or not started
        return;
    }

    if (ODTNum >= pDAQList->NumUsedODTs) {
        // Invalid ODT num
        return;
    }

    pODT = &pDAQList->pODTs[ODTNum];

    // if CAN, PacketLength can be longer than expected packetlength if it's padded to 8 bytes.
    if (pODT->PacketLength <= PacketLength) {
        memcpy(pODT->pDAQPacket, pPacket, pODT->PacketLength);
        pODT->bSTIMReceived = TRUE;
    }
}

/******************************************************************************
Function Name: XCPServerPrepDAQListForStart

I/O Parameters:

Name                I/O Type                Parameter Description / Contents
------------------- --- ----------          ----------------------------------
Name                IO  Type                Description

Description:

Comments:
******************************************************************************/
static void XCPServerPrepDAQListForStart(XCPServer_t *pXCP, XCPSERVER_DAQ_LIST_T *pDAQList)
{
    uint8_t ODTNum;

    // Set EventCount such that transmit will fire off at the next instance of that event.
    pDAQList->EventCount = pDAQList->Prescaler - 1;

    if (pDAQList->Direction == XCPSERVER_DAQLIST_DIRECTION_STIM) {
        // If STIM, mark each ODT as not received, so that we only write data
        // once it has been received.
        for (ODTNum = 0; ODTNum < pXCP->pConfig->NumODTPerDAQSTIM; ODTNum++) {
            pDAQList->pODTs[ODTNum].bSTIMReceived = FALSE;
        }
    }
}
