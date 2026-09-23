/*******************************************************************************
** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar's proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  XCPServer_defaultMemImpl.c
DESCRIPTION:  XCP Server Memory Access Default Implementation

*******************************************************************************/
#include <stdint.h>
#include <string.h>
#include "XCPServer.h"

static uint8_t simMemory[0x10000];

BOOL XCPServer_defaultMemValidate(
    void *pContext,
    uint32_t addr,
    uint8_t addrExt,
    uint16_t numBytes)
{
    (void)pContext;
    
    if ((addr + numBytes) > sizeof(simMemory)) {
        return FALSE;
    }

    return TRUE;
}

BOOL XCPServer_defaultMemWrite(
    void *pContext,
    uint32_t destAddr,
    uint8_t destAddrExt,
    uint8_t const * pSrc, uint16_t numBytes)
{
    uint8_t* pDest;

    (void)pContext;
    
    if ((destAddr + numBytes) > sizeof(simMemory)) {
        return FALSE;
    }

    pDest = &(simMemory[destAddr]);
    memcpy(pDest, pSrc, numBytes);
    return TRUE;
}

BOOL XCPServer_defaultMemRead(
    void *pContext,
    uint32_t srcAddr,
    uint8_t srcAddrExt,
    uint8_t *pDest, uint16_t numBytes)
{
    uint8_t const * pSrc;

    (void)pContext;
    
    if ((srcAddr + numBytes) > sizeof(simMemory)) {
        return FALSE;
    }

    pSrc = &(simMemory[srcAddr]);
    memcpy(pDest, pSrc, numBytes);
    return TRUE;
}
