/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar's proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  XCPHal.c
DESCRIPTION:

*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../XCPServer_.h"
#include "XCPHal_.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

/*******************************************************************************
** -- Data Declarations 
*******************************************************************************/
BOOL XCPHALOpenUDPPort(XCPServer_t *pXCP, uint16_t Port)
{
    XCP_HAL_INFO_T* pInfo = &(pXCP->XCPHALInfo);
    struct sockaddr_in Socket;
    
	if (pInfo->SocketHandle >= 0) {
        // already open.
		return(TRUE);
	}

  	pInfo->Type = XCPHAL_TYPE_UDP;
    pInfo->SocketHandle = socket(PF_INET, SOCK_DGRAM, 0);
    
	if (pInfo->SocketHandle < 0) {
		return(FALSE);
	}

    Socket.sin_family = AF_INET;
    if (0 == inet_aton("165.26.79.19", &Socket.sin_addr)) {
        Socket.sin_addr.s_addr = INADDR_ANY;
    }
    Socket.sin_port = htons(Port);
    
    if (bind(pInfo->SocketHandle, (struct sockaddr *)&Socket, sizeof(Socket)) < 0)
	{
		XCPHALCloseUDPPort(pXCP);
		return FALSE;
	}
	
	return TRUE;
}

void XCPHALCloseUDPPort(XCPServer_t *pXCP)
{
    XCP_HAL_INFO_T* pInfo = &(pXCP->XCPHALInfo);
	if (pInfo->SocketHandle != -1) {
		shutdown(pInfo->SocketHandle, SHUT_RDWR);
	}
	pInfo->SocketHandle = -1;
}

BOOL XCPHALUDPSend(XCPServer_t *pXCP, uint8_t const * pMessage, uint16_t MessageLength, uint32_t DestIP, uint16_t DestPort)
{
	struct sockaddr_in SockAddr;
	int SendRet;
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_port = DestPort;
	SockAddr.sin_addr.s_addr = DestIP;

    SendRet = sendto(
        pXCP->XCPHALInfo.SocketHandle, 
        (void const *)pMessage, 
        MessageLength, 
        MSG_DONTWAIT,
        (struct sockaddr *)&SockAddr, 
        sizeof(SockAddr)
    );

	if (SendRet < 0) {
		return FALSE;
	}
	return TRUE;
}

BOOL XCPHALOpenCANPort(XCPServer_t *pXCP, uint8_t PortNum)
{
    return FALSE;
}

void XCPHALCloseCANPort(XCPServer_t *pXCP)
{
}

BOOL XCPHALCANSend(XCPServer_t *pXCP, uint8_t *pMessage, uint16_t MessageLength)
{
    return FALSE;
}

void XCPHALInit(XCPServer_t *pXCP)
{
    pXCP->XCPHALInfo.SocketHandle = -1;
}

void XCPHALMain(XCPServer_t *pXCP)
{
	int BytesRemaining;
    uint8_t Message[1500];
    struct sockaddr_in SockAddr;
	socklen_t SockAddrLen = sizeof(SockAddr);

    while ((BytesRemaining = recvfrom(pXCP->XCPHALInfo.SocketHandle, 
    								  &Message[0],
                                      1500, 
    								  MSG_DONTWAIT, 
    								  (struct sockaddr *)&SockAddr, 
    								  &SockAddrLen)) > 0) {
		// Note, there could actually be multiple messages within the
		// RxMsg, but they shouldn't exceed the overall data length
		// because the max message length is greater than the max
		// ethernet packet size.
		//fprintf(pDebugFile, "%ld, UDP Packet Rxed, %d bytes\n", GetCurrentTime(), BytesRemaining);
		XCPServerProcUDPMsg(pXCP, Message, (uint16_t)BytesRemaining, SockAddr.sin_addr.s_addr, SockAddr.sin_port);
	}
}

