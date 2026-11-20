/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar's proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  XCPServer.h
DESCRIPTION:
*******************************************************************************/
#ifndef XCPSERVER_H_
#define XCPSERVER_H_

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <stdint.h>
#include "XCP.h"
#include "polyfill.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
/*
    With CAT CCP, most ECMs supported 1 Event, at either 10 ms or 15 ms loop time.
    With XCP, most ECMs will likely still just support this, but some may want to
    support a faster loop time (5 ms may be feasible, but 1 ms will likely be too
    fast.  Latency is likely to be a millisecond or longer in most systems, and
    jitter at 1 ms loop time will reduce the data quality further.)
    or a slower loop time (CCP supported a 2 byte prescaler, XCP only supports
    a 1 byte prescaler, so if someone thinks they'll need data every 5 milliseconds
    and 5 seconds, they'll need to define both a fast and a slow event)

*/
#define XCPSERVER_MAX_EVENTS 4
//#define XCPSERVER_EVENTMAXNAMELENGTH 20

struct XCPSERVER_EVENT_T {
    //uint16_t EventID;  // EventID/ Event Number is the offset into XCPSERVER_EVENT_T EventInfo[XCPSERVER_MAX_EVENTS];
    //char Name[XCPSERVER_EVENTMAXNAMELENGTH];  Not reporting a name.
    uint8_t TimeCycle;  // 0 if not cyclic, otherwise multiply time represented by TimeUnit to get period of this event.
    uint8_t TimeUnit;  // If TimeCycle not zero, should be one of the values of XCP_EVENT_TU_
};

typedef struct {
    uint8_t SetupInfoType;  // XCP_XPORT_UDP or XCP_XPORT_CAN

    // Ethernet specific
    uint16_t Port;  // UDP Port #, if UDP.

    // CAN specific, set most sig bit to indicate 29 bit CAN.
    uint32_t MasterID;  // Master CAN ID, set MSB of 32 bit to indicate 29 bit ID
    uint32_t SlaveID;  // Slave CAN ID, set MSB of 32 bit to indicate 29 bit ID
    uint32_t BroadcastID;  // Broadcast CAN ID, set MSB of 32 bit to indicate 29 bit ID

    uint8_t NumDAQSTIMLists;  // # DAQ/STIM lists (0-192)
    uint8_t NumODTPerDAQSTIM;  // # ODTs per DAQ (max of 192 total ODTs)
    uint8_t NumODTEntriesPerODT;  // # ODT entries per ODT, must be < MAX_DTO - 1 and <= 255
    uint8_t MaxODTEntrySizeDAQSTIM;  // Max ODT entry size in bytes (1..255, 8 works for most implementations)

    uint8_t MaxCTO;  // MAX_CTO (8..255)
    uint16_t MaxDTO;  // MAX_DTO (8..~1500 on UDP)

    uint8_t NumEvents;  // Num Events (MAX_EVENTS)
    struct XCPSERVER_EVENT_T EventInfo[XCPSERVER_MAX_EVENTS];  // Event ID is offset into EventInfo[]
} XCPServer_Config_t;

typedef BOOL XCPServer_MemValidateFunc_t(
    void* pContext,
    uint32_t addr,
    uint8_t addrExt,
    uint16_t numBytes);

typedef BOOL XCPServer_MemWriteFunc_t(
    void* pContext,
    uint32_t destAddr,
    uint8_t destAddrExt,
    uint8_t const * pSrc,
    uint16_t numBytes);

typedef BOOL XCPServer_MemReadFunc_t(
    void* pContext,
    uint32_t srcAddr,
    uint8_t srcAddrExt,
    uint8_t* pDest,
    uint16_t numBytes);

typedef struct XCPSERVER_T XCPServer_t;

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
extern XCPServer_t* XCPServer_new(void);
extern BOOL XCPServer_init(XCPServer_t* pXCP, XCPServer_Config_t const * pConfig);
extern void XCPServer_main(XCPServer_t* pXCP);
extern void XCPServer_procEvent(XCPServer_t* pXCP, uint16_t EventID);
extern void XCPServer_cleanup(XCPServer_t* pXCP);
extern void XCPServer_free(XCPServer_t* pXCP);

// Register memory access function
extern void XCPServer_registerMemValidate(XCPServer_t *pXCP, XCPServer_MemValidateFunc_t* pFunc, void* pContext);
extern void XCPServer_registerMemWrite(XCPServer_t *pXCP, XCPServer_MemWriteFunc_t* pFunc, void* pContext);
extern void XCPServer_registerMemRead(XCPServer_t *pXCP, XCPServer_MemReadFunc_t* pFunc, void* pContext);

// Default memory access implementations
extern XCPServer_MemValidateFunc_t XCPServer_defaultMemValidate;
extern XCPServer_MemWriteFunc_t XCPServer_defaultMemWrite;
extern XCPServer_MemReadFunc_t XCPServer_defaultMemRead;

// Direct memory access implementations
extern XCPServer_MemValidateFunc_t XCPServer_directMemValidate;
extern XCPServer_MemWriteFunc_t XCPServer_directMemWrite;
extern XCPServer_MemReadFunc_t XCPServer_directMemRead;

/*******************************************************************************
** -- Data Declarations
*******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* XCPSERVER_H_ */


