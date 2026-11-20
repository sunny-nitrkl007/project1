/*******************************************************************************
** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar's proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  XCPServer_mem.c
DESCRIPTION:  XCP Server Memory Access Interface

*******************************************************************************/
#include <stdint.h>
#include "XCPServer.h"
#include "XCPServer_.h"
#include "polyfill.h"

void XCPServer_registerMemValidate(XCPServer_t *pXCP, XCPServer_MemValidateFunc_t* pFunc, void *pContext)
{
    if (NULL != pXCP) {
        // For now, just replace the function.
        // Maybe in the future we will have a list of functions.
        pXCP->pMemValidateContext = pContext;
        pXCP->memValidate = pFunc;
    }
}

void XCPServer_registerMemWrite(XCPServer_t *pXCP, XCPServer_MemWriteFunc_t* pFunc, void *pContext)
{
    if (NULL != pXCP) {
        // For now, just replace the function.
        // Maybe in the future we will have a list of functions.
        pXCP->pMemWriteContext = pContext;
        pXCP->memWrite = pFunc;
    }
}

void XCPServer_registerMemRead(XCPServer_t *pXCP, XCPServer_MemReadFunc_t* pFunc, void *pContext)
{
    if (NULL != pXCP) {
        // For now, just replace the function.
        // Maybe in the future we will have a list of functions.
        pXCP->pMemReadContext = pContext;
        pXCP->memRead = pFunc;
    }
}

BOOL XCPServer_memValidate(
    XCPServer_t *pXCP,
    uint32_t addr,
    uint8_t addrExt,
    uint16_t numBytes)
{
    XCPServer_MemValidateFunc_t* memValidate = pXCP->memValidate;

    if (NULL == memValidate) {
        return TRUE; // If nothing is registered, defer to read and write
    }

    return memValidate(pXCP->pMemValidateContext, addr, addrExt, numBytes);
}

BOOL XCPServer_memWrite(
    XCPServer_t *pXCP,
    uint32_t destAddr,
    uint8_t destAddrExt,
    uint8_t const * pSrc, uint16_t numBytes)
{
    XCPServer_MemWriteFunc_t* memWrite = pXCP->memWrite;

    if (NULL == memWrite) {
        return FALSE;
    }

    return memWrite(pXCP->pMemWriteContext, destAddr, destAddrExt, pSrc, numBytes);
}

BOOL XCPServer_memRead(
    XCPServer_t *pXCP,
    uint32_t srcAddr,
    uint8_t srcAddrExt,
    uint8_t *pDest, uint16_t numBytes)
{
    XCPServer_MemReadFunc_t* memRead = pXCP->memRead;

    if (NULL == memRead) {
        return FALSE;
    }

    return memRead(pXCP->pMemReadContext, srcAddr, srcAddrExt, pDest, numBytes);
}

