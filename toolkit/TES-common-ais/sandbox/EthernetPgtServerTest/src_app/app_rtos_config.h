/*******************************************************************************
* Copyright 2001-2008 Caterpillar Inc.  All rights reserved.
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

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

         /*
         Task Periods

         Task periods are defined as macros to support their use in
         ROM configuration data.  They should be adjusted to match the run
         time values that have been adjusted to supported values.
         */

oel_rtos_function_t oel_control_task;


#define OEL_TASK_PERIOD  OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.1)

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

      /*
      task ids
      */

      /*
      resources
      */

extern bool_t app_init_completed;

typedef void (*oel_app_function_t)();

extern oel_app_function_t appInitFunction;
extern oel_app_function_t appUpdateFunction;

#endif /* #ifndef __APP_RTOS_CONFIG_H__ */
