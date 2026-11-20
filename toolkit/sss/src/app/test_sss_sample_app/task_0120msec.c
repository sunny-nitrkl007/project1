/******************************************************************************************************************
 Copyright 2016 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: task_0120msec.c

Description: o/s entry point for 30 msec periodic task
******************************************************************************************************************/

/******************************************************************************************************************
-- #Include's --
******************************************************************************************************************/

#include <oel_rtos.h>

/******************************************************************************************************************
Function Name: task_0120msec_proc()

Description:
   This is the o/s entry point for 120 msec periodic task running sss.  This
   entry point is intended to be o/s independant.

Parameter Description: oel_rtos_event_t pend_events.

Return Description: None.
******************************************************************************************************************/

void task_0120msec_proc(oel_rtos_event_t pend_events)
{
   oel_rtos_task_context_t
   my_task_context;
   /* Task init section.
   ----------------------------------------------------------------------- */

   /*
   Perform startup initialization or wait for another task to
   complete it.  ALL tasks that have any dependencies on this
   initialization (hal_init(), etc.) should call this.
   */
   oel_rtos_startup_init();

   /*
   Get my task context once and remember it to avoid the overhead of doing
   it again.
   */
   oel_rtos_task_get_context(&my_task_context);


   /* Task processing section.
   ----------------------------------------------------------------------- */

   while(1) {

   /* wait for synchronizing event */
   oel_rtos_event_pend(my_task_context, pend_events, NULL);
   };
} /* end */
