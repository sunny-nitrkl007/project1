/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 2001 CATERPILLAR INC.   ALL RIGHTS RESERVED.            %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
*
*  File: app_can_init_proto.h
*
*/

#ifndef APP_CAN_PROTO_H
#define APP_CAN_PROTO_H

#ifndef HAL_CAN_H
#include <hal_can.h>
#endif

#ifndef __UTIL_PROTO_H__
#include <util_proto.h>
#endif

typedef struct mbuf_hdr_s
{
	UTIL_Lnk_t	link;
	unsigned_32 len;	
	unsigned_32 type;	
	unsigned_8 data[8];	
}mbuf_hdr_t;

/*********** Global procedures *******************************************/

void app_can_init(void);
void app_hal_can_tx_update(void);
int_32 app_get_rx_can_message(char *	packet);
boolean app_wait_rx_can_message(void);
int_32  app_can_tx_callback_fn(char * log, unsigned_32 size);

#endif /* APP_CAN_PROTO_H */
 
