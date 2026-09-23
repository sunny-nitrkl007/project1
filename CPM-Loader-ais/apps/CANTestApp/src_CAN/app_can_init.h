/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 2013-2016 CATERPILLAR INC.   ALL RIGHTS RESERVED.       %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
*
*  File: app_can_init.h
*
*/

#ifndef __APP_CAN_INIT_H__
#define __APP_CAN_INIT_H__

#include <scl_j1939.h>
#include <scl_rw_j1939.h>
/*********** Global procedures *******************************************/

extern void app_can_init(void);

extern int base_can_port;
extern bool_t can_init_completed;
extern scl_j1939_link_t Ph_Link_app;
extern hal_canv3_client_t *client;
extern uint_least8_t app_hal_canv3_owner;
extern boolean canBflag;
#endif /* __APP_CAN_INIT_H__ */
 
