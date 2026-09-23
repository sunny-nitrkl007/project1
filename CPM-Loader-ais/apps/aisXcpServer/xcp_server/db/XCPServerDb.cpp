#include <stdint.h>

#include "XCPServerDb.hpp"

using namespace xcp_server;

/*
 * Create the one and only NullDbEntry
 */
internal_::NullDbEntry xcp_server::NullDbEntry;

/*
 * Callback functions for XCPServer
 */
BOOL internal_::memValidateCallback(void *pContext, uint32_t addr, uint8_t addrExt, uint16_t numBytes)
{
    //std::cout << "memValidateCallback, " << addr << ", " << addrExt << ", " << numBytes << std::endl;
    return static_cast<ParameterDb*>(pContext)->memValidate(addr, addrExt, numBytes);
}

BOOL internal_::memWriteCallback(void *pContext, uint32_t destAddr, uint8_t destAddrExt, uint8_t const *pSrc, uint16_t numBytes)
{
    //std::cout << "memWriteCallback, " << destAddr << ", " << destAddrExt << ", " << numBytes << std::endl;
    return static_cast<ParameterDb*>(pContext)->memWrite(destAddr, destAddrExt, pSrc, numBytes);
}

BOOL internal_::memReadCallback(void *pContext, uint32_t srcAddr, uint8_t srcAddrExt, uint8_t *pDest, uint16_t numBytes)
{
    //std::cout << "memReadCallback, " << srcAddr << ", " << srcAddrExt << ", " << numBytes << std::endl;
    return static_cast<ParameterDb*>(pContext)->memRead(srcAddr, srcAddrExt, pDest, numBytes);
}
