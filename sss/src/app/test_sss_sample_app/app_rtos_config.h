/******************************************************************************************************************
 Copyright 2016 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: app_rtos_config.h

Descriptions: This file provides application initialization functions that are called from oel during 
              application startup.
******************************************************************************************************************/
#ifndef APP_RTOS_CONFIG_H_
#define APP_RTOS_CONFIG_H_

/******************************************************************************************************************
   #Include's
******************************************************************************************************************/
#include <oel_rtos.h>

/******************************************************************************************************************
   #Defines
******************************************************************************************************************/
   
/* Task Periods Task periods are defined as macros to support their use in ROM configuration data.They should be
adjusted to match the run time values that have been adjusted to supported values.*/

#define TASK_0120MSEC_PERIOD		 OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.120)
#define TASK_1005MSEC_PERIOD		 OEL_RTOS_SECONDS_DBL_TO_U32_L20(1.005)
#define TASK_0030MSEC_PERIOD		 OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.030)

/******************************************************************************************************************
** -- Function Prototypes --
******************************************************************************************************************/
/******************************************************************************************************************
** -- Data Declarations --
******************************************************************************************************************/
/* arrays of pointers to initialization functions */

extern oel_rtos_init_object_t const* const app_pre_irq_init_list[];
extern oel_rtos_init_object_t const* const app_startup_init_list[];

/* resources */
extern const oel_rtos_resource_config_t *app_hal_canv3_resource_config;
extern const oel_rtos_semaphore_config_t * item_1_mutex_config;


extern oel_rtos_task_id_t       task_0030ms_id;
extern oel_rtos_task_id_t       task_0120ms_id;
extern oel_rtos_task_id_t       task_1005ms_id;

void task_0030msec(void);
void task_0120msec(void);
void task_1005msec(void);

void app_can_init(void);


#endif
