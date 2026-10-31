/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 1994-1995 CATERPILLAR INC.   ALL RIGHTS RESERVED.       %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
***
*** DESCRIPTION :
***   Header file for application utility functions.
***
*** LANGUAGE :                  
***    ANSI C
***
*** NOTES:
***
*** MACRO LIST:
***
*******************************************************************************/
#ifndef __APP_UTIL_PROTO_H__
#define __APP_UTIL_PROTO_H__

#include <std_types.h>

extern void app_connect_func( unsigned_8 mid, unsigned_8 status);
extern void app_periodic_func( unsigned_8 mid);

extern void *app_get_fnc_ptr( unsigned_32 functionid);
extern void *app_get_data_ptr( unsigned_32 dataid);

extern void app_activate_system_event( unsigned_16 cid, unsigned_8 fmi);
extern void app_deactivate_system_event( unsigned_16 cid, unsigned_8 fmi);

void app_inf_sys_event_proc(com_inf_input_request_t *req_ptr);
void app_inf_data_event_proc(com_inf_input_request_t *req_ptr);

void app_inf_sys_evt_summary(com_inf_input_request_t *req_ptr);
void app_inf_data_evt_summary(com_inf_input_request_t *req_ptr);

boolean_t app_clear_all_events(void);

#endif /* __APP_UTIL_PROTO_H__ */
