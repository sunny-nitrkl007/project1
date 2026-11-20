/*******************************************************************************
** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar's proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  XCPServer_directMemImpl.c
DESCRIPTION:  XCP Server Memory Access Direct Implementation

*******************************************************************************/
#include <stdint.h>
#include <string.h>
#include "XCPServer.h"

BOOL XCPServer_directMemValidate(
    void *pContext,
    uint32_t addr,
    uint8_t addrExt,
    uint16_t numBytes)
{
    (void)pContext;
    return TRUE;
}

BOOL XCPServer_directMemWrite(
    void *pContext,
    uint32_t destAddr,
    uint8_t destAddrExt,
    uint8_t const * pSrc, uint16_t numBytes)
{
    (void)pContext;  // could use pContext as offset to start memory at some point.
    memcpy((uint8_t*)destAddr, pSrc, numBytes);
    return TRUE;
}

BOOL XCPServer_directMemRead(
    void *pContext,
    uint32_t srcAddr,
    uint8_t srcAddrExt,
    uint8_t *pDest, uint16_t numBytes)
{
    (void)pContext;  // could use pContext as offset to start memory at some point.
    memcpy(pDest, (uint8_t const *)srcAddr, numBytes);
    return TRUE;
}
