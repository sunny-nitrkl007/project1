/*******************************************************************************
* Copyright 2001-2016 Caterpillar Inc.  All rights reserved.
--------------------------------------------------------------------------------
FILE NAME:  app_rtos_config.h
DESCRIPTION:
*******************************************************************************/
#ifndef __APP_RTOS_CONFIG_H__
#define __APP_RTOS_CONFIG_H__

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <oel_rtos.h>
//#include <scl_j1939.h>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

         /*
         Task Periods

         Task periods are defined as macros to support their use in
         ROM configuration data.  They should be adjusted to match the run
         time values that have been adjusted to supported values.
         */

oel_rtos_function_t scl_CAN_control_task;


#define SCL_CAN_TASK_PERIOD  OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.01)

      /*
      events for task task_multi_event
      */

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

/*******************************************************************************
** -- Data Declarations
*******************************************************************************/

      /*
      arrays of pointers to initialization functions
      */
extern oel_rtos_init_object_t const* const app_pre_irq_init_list[];
extern oel_rtos_init_object_t const* const app_startup_init_list[];
extern const oel_rtos_resource_config_t *app_hal_canv3_resource_config;

      /*
      task ids
      */

      /*
      resources
      */
//	extern const scl_j1939_config_t app_scl_j1939_config;

#endif /* #ifndef __APP_RTOS_CONFIG_H__ */
