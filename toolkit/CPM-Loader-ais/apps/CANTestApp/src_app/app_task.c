/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                       %%
*** %%  COPYRIGHT (C) 2003-2016 CATERPILLAR INC.   ALL RIGHTS RESERVED.      %%
*** %%                                                                       %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
***
*** DESCRIPTION : This is the task1 for app template 2.
***
*** REQUIRED HEADER :
***
*** LANGUAGE :                  
***    ANSI C
***
*** COMPILE FLAGS :
***
*** METHOD:
***
*** NOTES:
***
*** GLOBALS USED:
***
*** History:  Initial version, March 3rd, 2003     Leyan Xu
*******************************************************************************/

/*******************************************************************************
***
***    Referenced Functions, Data, & Symbols
***    -- #Include's --
***
*******************************************************************************/

#include "app_rtos_config.h"
#include "../src_CAN/app_can_init.h"

static unsigned_32 j1939_counter;

/*******************************************************************************
***
*** FUNCTION NAME: scl_j1939_control_task()
***
*** DESCRIPTION:
***   The main periodic task for the app template 2 application.
***
*******************************************************************************/
void scl_CAN_control_task(void)
{
  oel_rtos_task_context_t my_task_context;

   /*
   Perform rtos startup initialization.  Must be the first code in the first
   running task.  Subsequent calls are ignored so it can be included in all
   tasks.  This is not required for rtos implementations with a startup task
   (such as OSE Delta).
   */
   oel_rtos_startup_init();

   /*
   Get my task context once and remember it to avoid the overhead of doing
   it again.
   */
   oel_rtos_task_get_context(&my_task_context);

   /*
   Periodic Main Loop
   */
   while (TRUE)   /* until loss of power or reset */
   {
	   j1939_counter++;
      /*
      wait for synchronizing event
      */
      oel_rtos_event_pend(my_task_context, OEL_RTOS_TIME_EVENT, NULL);
      

   } /* end while() */

} /* end eol_main_task() */
