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
***	Globals used by PCS 
***
*** LANGUAGE :
***    ANSI C
***
*** MACRO LIST:
***
*******************************************************************************/
#ifndef __PCS_GLOBAL_H__
#define __PCS_GLOBAL_H__

#include <pcs_structures.h>
#include <clock_proto.h>
//#include <pd_public.h>

extern WORKDATA pcs_data;
extern NVMDATA pcs_nvm_data;
extern MODEL_SPECIFIC_VALUES const * pcs_model_spec_vals;
extern MODEL_SPECIFIC_VALUES const * pcs_model_spec_vals_default;
extern RECORD_PACKET	*data_log;
extern boolean	cal_in_progress;
//TODO: temp for testing
extern boolean	payload_cal_flag;
extern boolean empty_bkt_cal_done;
extern boolean full_bkt_cal_done;
extern pcs_print_ticket_t	*print_ticket;
extern pcs_print_totals_t	*print_totals;
extern AUTO_ZERO	auto_zero;
extern boolean scaleless_cal_in_progress;
extern boolean sc_data_status;
extern STATUS_BLOCK_STALE_TIME_BUFFER stale_time_status_record_buffer[MAX_STATUS_RECS_STORED_IN_BUFFER];

extern boolean pcs_sc_cal_loading_bkt(void);

#endif /* __PCS_GLOBAL_H__ */
