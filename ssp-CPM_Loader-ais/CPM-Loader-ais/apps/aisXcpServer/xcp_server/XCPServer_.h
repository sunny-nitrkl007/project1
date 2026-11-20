/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar's proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  XCPServer_.h
DESCRIPTION:
*******************************************************************************/
#ifndef XCPSERVER__H_
#define XCPSERVER__H_

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <stdint.h>
#include "XCP.h"
#include "XCPServer.h"
#include "XCPHal_.h"
#include "polyfill.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
typedef struct XCPSERVER_ODT_ENTRY_T {
    uint32_t Address;
    uint8_t AddressExtension;
    uint8_t NumBytes;
    // uint8_t BitOffset;
} XCPSERVER_ODT_ENTRY_T;

typedef struct XCPSERVER_ODT_T {
    uint8_t PID;     //PID of this ODT
    uint8_t NumUsedODTEntries;  // Set to one more than the offset of the last used ODTEntry.
    XCPSERVER_ODT_ENTRY_T *pODTEntries;

    BOOL bSTIMReceived; // a STIM packet has been received for this ODT since the last time it was written.

    // Since DAQ and STIM can potentially be sent/received/processed in different threads, need
    // a separate reserved buffer for each ODT.
    uint8_t *pDAQMessageBuf; // pointer to the complete message buffer (includes CAN header, or XCP header on Ethernet)
    uint8_t *pDAQPacket; // pointer to the first data byte in the DAQ packet (pDAQMessageBuf)
    uint16_t PacketLength;  // packet length (length of data), not including header
} XCPSERVER_ODT_T;

typedef struct XCPSERVER_DAQ_LIST_T {
    // uint8_t NumODTs;
    uint8_t Properties;
    uint8_t Direction;  // or is this in Properties?
    uint8_t FirstPID;
    uint16_t EventID;
    uint8_t Prescaler;

    uint8_t EventCount;
    uint8_t StartStopSelected;

    uint8_t NumUsedODTs; // Set to one more than the offset of the last used ODT.

    XCPSERVER_ODT_T *pODTs;
} XCPSERVER_DAQ_LIST_T;


struct XCPSERVER_T {
    /*
        !!! Do we just keep a pointer to the original configuration, or do we need to
        copy the configuration locally, to prevent it from being changed externally?
        Assuming it's a static configuration for now.
    */
    XCPServer_Config_t const * pConfig;

    BOOL bConfigured;   // TRUE if the instance has been configured without errors.

    uint32_t MTA;            // Memory Transfer Address.
    uint8_t MTAAddressExtension;

    BOOL bIsConnected;  // Indicates if a Master is presently connected.

    uint32_t UDPMasterIP;   // for UDP.  IP address of connected Master
    uint16_t UDPMasterPort; // for UDP.  Port # of connected Master

    uint8_t LockedResourceStatus;

    uint8_t CurrentSeedKeyResource;  // Indicates which resource the current seed/key is for.
    uint8_t CurrentSeedLength;
    uint8_t CurrentRemainingSeedLength;  // used for transferring the seed to the client
    uint8_t CurrentSeed[255];
    // Actual key based on the current seed.
    BOOL bKeyGenerated;
    uint8_t CurrentActualKeyLength;
    uint8_t CurrentActualKey[XCP_MAX_SEED_LENGTH];

    // CurrentMaster is for holding key being sent by the Master to Slave via UNLOCK
    uint8_t CurrentMasterKeyLength;
    uint8_t CurrentMasterRemainingKeyLength;  // used for receiving the key from the client
    uint8_t CurrentMasterKey[XCP_MAX_KEY_LENGTH];

    uint16_t SessionConfigurationID;
    uint16_t DTOCounter;

    uint16_t DAQPtrListNumber;
    uint8_t DAQPtrODTNumber;
    uint8_t DAQPtrODTEntryNumber;

    uint8_t NumUsedDAQLists;
    XCPSERVER_DAQ_LIST_T *pDAQLists;

    // The Response Buffer
    // This is allocated based on the requested size, since this could be from 8 to 0xFFFF bytes (on TCP).
    // use pRespPacket to access the packet contents, so the packet can be built without worrying about
    // the physical layer, then the transport layer specifics can be filled in later.
    uint8_t *pRespMessageBuf;  // Should be MAX_DTO + transport layer specific wrapper in length,
                          // For CAN, this will be 2 or 4 bytes, depending on Slave ID.
                          // for UDP, this will be 4 bytes, with a 2 byte length and 2 byte counter
                          // This is allocated.
                          // Or, for CAN, this could be of a specific type...

    uint8_t *pRespPacket;  // Should be MAX_DTO in length, and point to the first packet byte in RespBufMessage
    uint8_t RespHeaderLength;

    // Callbacks
    XCPServer_MemValidateFunc_t* memValidate;
    void* pMemValidateContext;
    XCPServer_MemWriteFunc_t* memWrite;
    void* pMemWriteContext;
    XCPServer_MemReadFunc_t* memRead;
    void* pMemReadContext;

    // HAL
    XCP_HAL_INFO_T XCPHALInfo;
};

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
// HAL will call these
extern void XCPServerProcCANMsg(XCPServer_t *pXCP, uint8_t *pMsg, uint16_t MsgLength);
extern void XCPServerProcUDPMsg(XCPServer_t *pXCP, uint8_t *pMsg, uint16_t MsgLength, uint32_t SrcIP, uint16_t SrcPort);

// HAL will expose these
extern void XCPHALInit(XCPServer_t *pXCP);
extern void XCPHALMain(XCPServer_t *pXCP);

extern BOOL XCPHALOpenUDPPort(XCPServer_t *pXCP, uint16_t Port);
extern void XCPHALCloseUDPPort(XCPServer_t *pXCP);
extern BOOL XCPHALUDPSend(XCPServer_t *pXCP, uint8_t const * pMessage, uint16_t MessageLength, uint32_t DestIP, uint16_t DestPort);

extern BOOL XCPHALOpenCANPort(XCPServer_t *pXCP, uint8_t PortNum);
extern void XCPHALCloseCANPort(XCPServer_t *pXCP);
extern BOOL XCPHALCANSend(XCPServer_t *pXCP, uint8_t *pMessage, uint16_t MessageLength);

extern BOOL XCPServer_memValidate(XCPServer_t *pXCP, uint32_t addr, uint8_t addrExt, uint16_t numBytes);
extern BOOL XCPServer_memWrite(XCPServer_t *pXCP, uint32_t destAddr, uint8_t destAddrExt, uint8_t const * pSrc, uint16_t numBytes);
extern BOOL XCPServer_memRead(XCPServer_t *pXCP, uint32_t srcAddr, uint8_t srcAddrExt, uint8_t *pDest, uint16_t numBytes);

/*******************************************************************************
** -- Data Declarations
*******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* XCPSERVER__H_ */


