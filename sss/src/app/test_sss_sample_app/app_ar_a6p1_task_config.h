/******************************************************************************************************************
 Copyright 2016 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: app_ar_a6p1_task_config.h

Description: Application task entry point.
******************************************************************************************************************/
#ifndef __APP_AR_A6P1_TASK_CONFIG_H__
#define __APP_AR_A6P1_TASK_CONFIG_H__

/******************************************************************************************************************
** -- #Include's --
******************************************************************************************************************/

#include <oel_rtos.h>

/******************************************************************************************************************
** -- Data Declarations --
******************************************************************************************************************/

extern const oel_rtos_resource_config_t *app_hal_canv3_resource_config;

/* application-defined OEL task function prototypes */
oel_rtos_function_t                  task_0008msec;
oel_rtos_task_init_callback_t        task_0008msec_init;
oel_rtos_task_periodic_callback_t    task_0008msec_periodic;

oel_rtos_function_t                  task_0016msec;
oel_rtos_task_init_callback_t        task_0016msec_init;
oel_rtos_task_periodic_callback_t    task_0016msec_periodic;

oel_rtos_function_t                  task_0080msec;
oel_rtos_task_init_callback_t        task_0080msec_init;
oel_rtos_task_periodic_callback_t    task_0080msec_periodic;

oel_rtos_function_t                  task_0160msec;
oel_rtos_task_init_callback_t        task_0160msec_init;
oel_rtos_task_periodic_callback_t    task_0160msec_periodic;

oel_rtos_function_t                  task_background;
oel_rtos_task_init_callback_t        task_background_init;
oel_rtos_task_periodic_callback_t    task_background_periodic;

oel_rtos_function_t                  task_autostart;
oel_rtos_task_init_callback_t        task_autostart_init;
oel_rtos_task_periodic_callback_t    task_autostart_periodic;


#endif