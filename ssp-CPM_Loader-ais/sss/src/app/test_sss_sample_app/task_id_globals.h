/******************************************************************************************************************
 Copyright 2016 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: task_id_globals.h

Description: 
******************************************************************************************************************/

#ifndef TASK_ID_GLOBALS_H_
#define TASK_ID_GLOBALS_H_

/******************************************************************************************************************
** -- #Include's --
******************************************************************************************************************/
#include <oel_rtos.h>
/******************************************************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
******************************************************************************************************************/

typedef struct
{
   oel_rtos_timer_alarm_handler_t base;
   uint_least32_t count;
} be_task_wdog_handler_t;

extern oel_rtos_init_object_t const* const app_pre_irq_init_list[];
extern oel_rtos_init_object_t const* const app_startup_init_list[];

extern be_task_wdog_handler_t task_wdog_task_background;
extern be_task_wdog_handler_t task_wdog_task_autostart;



#endif /* TASK_ID_GLOBALS_H_ */
