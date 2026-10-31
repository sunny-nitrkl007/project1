/******************************************************************************
*** FILE:
*** task_can.c
***
*** COPYRIGHT NOTICE:
*** Copyright 2004.  Caterpillar Inc.  All Rights Reserved.
*** This work contains Caterpillar's proprietary information which
*** may constitute a trade secret and/or be confidential.  Copyright
*** notice is precautionary only and does not imply publication.
***
*** DESCRIPTION:
*** This task is scheduled to run every 3.3ms.
*** All routines that need to be run at this rate should be placed
*** in this function.
******************************************************************************/

#include <app_rtos_config.h>
#include <oel_rtos.h>
#include <app_can_init_proto.h>

/*******************************************************************************
***
*** FUNCTION NAME: task_can
***
*** DESCRIPTION:
***	
***
*******************************************************************************/
void task_can(void)
{
	oel_rtos_task_context_t task_context;
	
   /*
   Perform rtos startup initialization.  Must be the first code in the first
   running task.  Subsequent calls are ignored so it can be included in all
   tasks.  This is not required for rtos implementations with a startup task
   (such as OSE Delta).
   */
   oel_rtos_startup_init();

   /*
   ** Get my task context once and remember it to avoid the overhead of doing
   ** it again.
   */
   oel_rtos_task_get_context(&task_context);

	/*
	** Periodic Main Loop
	*/
	while (TRUE)   /* until loss of power or reset */
	{
		/*
		** wait for synchronizing event
		*/
		oel_rtos_event_pend(task_context,OEL_RTOS_TIME_EVENT, NULL); /* OEL_RTOS_TIME_EVENT*/

		/* Send All queued CAN tx messages */
	    app_hal_can_tx_update();


	} /* end while() */

} /* end task_can() */
