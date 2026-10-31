/******************************************************************************************************************
 Copyright 2009 - 2011 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: app_rtos_config.h

Description: File contains the task related defines and prototypes
******************************************************************************************************************/
#ifndef  APP_RTOS_CONFIG_H_
#define  APP_RTOS_CONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif


#include <oel_rtos.h>
#include <cdl2_mod_defs.h>
#include <cdl2_proto.h>
#include <cdl_struct.h>
#include <cdl_mod_struct.h>
#include <cdl_std_hdlr_struct.h>
/*
#if( !defined(DSE_300E) && !defined(WIN32) && !defined(A5N2) && !defined(T5R1) && !defined (T6R8) )
   #define SCL_J1939_fl
   #include "app_j1939.h"
#endif
*/

#define CDL2_CBS_fl

/*  Task Periods
    Task periods are defined as macros to support their use in  ROM configuration data.They should be adjusted to
    match the run time values that have been adjusted to supported values.  */

#define TASK1_PERIOD                 OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.010)
#define CDL2_CBS_CONTROL_TASK_PERIOD \
          OEL_RTOS_SECONDS_DBL_TO_U32_L20(1.0/CDL2_CBS_UPDATES_PER_SECOND)
#define APP_INF_TASK_PERIOD          OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.016)

#define APP_RECV_MAIN_TASK_PERIOD  OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.015)

#ifdef SCL_J1939_fl
   #define TASK2_PERIOD                 OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.020)
#endif
/* events for task task_multi_event */

#define CDL2_CBS_TIME_EXPIRE_EVENT      OEL_RTOS_TIME_EVENT
#define CDL2_CBS_FIFO_INPUT_EVENT       OEL_RTOS_EVENT_N_TO_MASK(0)
#define COM_INF_FIFO_INPUT_EVENT        OEL_RTOS_EVENT_N_TO_MASK(0)

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*      task prototypes      */
oel_rtos_function_t  task1;
oel_rtos_function_t  cdl2_cbs_control_task;
oel_rtos_function_t  app_recv_main_task;
oel_rtos_function_t  app_cdl2_task_bckgnd;

#ifdef SCL_J1939_fl
  oel_rtos_function_t  task2;
#endif

/* arrays of pointers to initialization functions */

extern oel_rtos_init_object_t const* const app_pre_irq_init_list[];
extern oel_rtos_init_object_t const* const app_startup_init_list[];


/* task ids */

extern oel_rtos_task_id_t task1_id;
extern oel_rtos_task_id_t cdl2_cbs_control_task_id;
extern oel_rtos_task_id_t app_recv_main_task_id;

#ifdef SCL_J1939_fl
   extern oel_rtos_task_id_t task2_id;
#endif
/* resources */
extern const oel_rtos_resource_config_t *app_hal_canv3_resource_config;
extern const oel_rtos_resource_config_t *app_scl_ccp_resource_config;
extern const cdl2_cbs_oel_config_t app_cdl2_cbs_oel_config;
#ifdef SCL_J1939_fl
   extern const scl_j1939_config_t app_scl_j1939_config;
#endif
#ifdef __cplusplus
}
#endif
#endif /* #ifndef APP_RTOS_CONFIG_H_ */
