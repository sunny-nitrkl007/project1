/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <stdio.h>

#include<oel_rtos.h>

#ifndef CSF_ETH_HEALTH_H
#include<csf_eth_health.h>
#endif

#ifndef APP_RECV_MAIN_H_
#include "app_recv_main.h"
#endif

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

void app_recv_main_task(void)
{
    printf("******************app_receive_main_task ******************\n");

    oel_rtos_task_context_t my_task_context;

    /*
       Perform rtos startup initialization.  Must be the first code in the first
       running task.  Subsequent calls are ignored so it can be included in all
       tasks.  This is not required for rtos implementations with a startup task
       (such as OSE Delta).
       */
    oel_rtos_startup_init();

    oel_rtos_task_get_context(&my_task_context);

    while (TRUE)   /* until loss of power or reset */
    {
             /*
             wait for synchronizing event
             */
          oel_rtos_event_pend(my_task_context, OEL_RTOS_TIME_EVENT, NULL);

          csf_eth_health_link_update();

    }
}
