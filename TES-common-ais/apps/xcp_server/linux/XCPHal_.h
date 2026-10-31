/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar's proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  XCPHal_.h
DESCRIPTION:
*******************************************************************************/
#ifndef XCP_HAL__H_
#define XCP_HAL__H_

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
typedef enum {
	XCPHAL_TYPE_CAN,
	XCPHAL_TYPE_UDP,
} XCPHAL_TYPE_T;

typedef struct XCP_HAL_INFO_T {
	XCPHAL_TYPE_T Type;
	//CAsyncSocket *pSocket;
	//SOCKET UDPSocket;
	//uint16_t Port;
	int32_t SocketHandle;
} XCP_HAL_INFO_T;

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

/*******************************************************************************
** -- Data Declarations 
*******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* XCP_HAL__H_ */
