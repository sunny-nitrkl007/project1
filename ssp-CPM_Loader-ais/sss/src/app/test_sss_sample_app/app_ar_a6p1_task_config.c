/******************************************************************************************************************
 Copyright 2016 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: app_a6p1_task_config.c

Description: Application task entry point.
******************************************************************************************************************/

/******************************************************************************************************************
-- #Include's --
******************************************************************************************************************/
#include <oel_os_cfg_csns_test.h>
#include <oel_rtos.h>
#include <oel_rtos_ar.h>
#include "app_ar_a6p1_task_config.h"

/******************************************************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
/******************************************************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/******************************************************************************************************************
** -- Data Declarations
*******************************************************************************/
#define TASK_0008MSEC_PERIOD           OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.008)
#define TASK_0016MSEC_PERIOD           OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.016)
#define TASK_0080MSEC_PERIOD           OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.080)
#define TASK_0160MSEC_PERIOD           OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.160)

static oel_rtos_task_framework_wksp_t      task_0008msec_wksp;
static oel_rtos_task_framework_wksp_t      task_0016msec_wksp;
static oel_rtos_task_framework_wksp_t      task_0080msec_wksp;
static oel_rtos_task_framework_wksp_t      task_0160msec_wksp;
static oel_rtos_task_framework_wksp_t      task_autostart_wksp;
static oel_rtos_task_framework_wksp_t      task_background_wksp;


const oel_rtos_task_framework_cfg_t task_0008msec_frmwrk_cfg =
               OEL_RTOS_TASK_FRAMEWORK_CFG(task_0008ms_id,
                                           task_0008msec_init,
                                           task_0008msec_periodic,
                                           task_0008msec_wksp,
                                           OEL_RTOS_TIME_EVENT);
										   
					   
const oel_rtos_task_framework_cfg_t task_0016msec_frmwrk_cfg =
               OEL_RTOS_TASK_FRAMEWORK_CFG(task_0016ms_id,
                                           task_0016msec_init,
                                           task_0016msec_periodic,
                                           task_0016msec_wksp,
                                           OEL_RTOS_TIME_EVENT);
										   

const oel_rtos_task_framework_cfg_t task_0080msec_frmwrk_cfg =
               OEL_RTOS_TASK_FRAMEWORK_CFG(task_0080ms_id,
                                           task_0080msec_init,
                                           task_0080msec_periodic,
                                           task_0080msec_wksp,
                                           OEL_RTOS_TIME_EVENT);
										   

const oel_rtos_task_framework_cfg_t task_0160msec_frmwrk_cfg =
               OEL_RTOS_TASK_FRAMEWORK_CFG(task_0160ms_id,
                                           task_0160msec_init,
                                           task_0160msec_periodic,
                                           task_0160msec_wksp,
                                           OEL_RTOS_TIME_EVENT);					   
										   

const oel_rtos_task_framework_cfg_t task_autostart_frmwrk_cfg =
               OEL_RTOS_TASK_FRAMEWORK_CFG(task_autostart_id,
                                           task_autostart_init,
                                           task_autostart_periodic,
                                           task_autostart_wksp,
                                           OEL_RTOS_TIME_EVENT);
										   

const oel_rtos_task_framework_cfg_t task_background_frmwrk_cfg =
               OEL_RTOS_TASK_FRAMEWORK_CFG(task_background_id,
                                           task_background_init,
                                           task_background_periodic,
                                           task_background_wksp,
                                           NULL);

/******************************************************************************************************************
FUNCTION NAME: task_0008msec_init

PARAMETER DESCRIPTION:
   oel_rtos_task_id_t taskID - ID of this task

RETURN VALUE:
   void

DESCRIPTION:
   Task initialization callback function.
   This function is only called once at initialization for the task.
******************************************************************************************************************/
void task_0008msec_init(oel_rtos_task_id_t taskID)
{
    /* void to avoid Compiler Error*/
    (void)taskID;
}

/******************************************************************************************************************
FUNCTION NAME: task_0016msec_init

PARAMETER DESCRIPTION:
   oel_rtos_task_id_t taskID - ID of this task

RETURN VALUE:
   void

DESCRIPTION:
   Task initialization callback function.
   This function is only called once at initialization for the task.
******************************************************************************************************************/
void task_0016msec_init(oel_rtos_task_id_t taskID)
{
    /* void to avoid Compiler Error*/
    (void)taskID;
}

/******************************************************************************************************************
FUNCTION NAME: task_0080msec_init

PARAMETER DESCRIPTION:
   oel_rtos_task_id_t taskID - ID of this task

RETURN VALUE:
   void

DESCRIPTION:
   Task initialization callback function.
   This function is only called once at initialization for the task.
******************************************************************************************************************/
void task_0080msec_init(oel_rtos_task_id_t taskID)
{
    /* void to avoid Compiler Error*/
    (void)taskID;
}

/******************************************************************************************************************
FUNCTION NAME: task_0160msec_init

PARAMETER DESCRIPTION:
   oel_rtos_task_id_t taskID - ID of this task

RETURN VALUE:
   void

DESCRIPTION:
   Task initialization callback function.
   This function is only called once at initialization for the task.
******************************************************************************************************************/
void task_0160msec_init(oel_rtos_task_id_t taskID)
{
    /* void to avoid Compiler Error*/
    (void)taskID;
}

/******************************************************************************************************************
FUNCTION NAME: task_0008msec_periodic

PARAMETER DESCRIPTION:
   oel_rtos_task_id_t taskID - ID of this task
   oel_rtos_event_t   event  - Any event flags that were configured and set.

RETURN VALUE:
   void

DESCRIPTION:
   Task periodic callback function.
   This function is called at the task's periodic rate.
******************************************************************************************************************/
void task_0008msec_periodic(oel_rtos_task_id_t taskID, oel_rtos_event_t event)
{
    /* void to avoid Compiler Error*/
    (void)taskID;
    (void)event;
}

/******************************************************************************************************************
FUNCTION NAME: task_0016msec_periodic

PARAMETER DESCRIPTION:
   oel_rtos_task_id_t taskID - ID of this task
   oel_rtos_event_t   event  - Any event flags that were configured and set.

RETURN VALUE:
   void

DESCRIPTION:
   Task periodic callback function.
   This function is called at the task's periodic rate.
******************************************************************************************************************/
void task_0016msec_periodic(oel_rtos_task_id_t taskID, oel_rtos_event_t event)
{
    /* void to avoid Compiler Error*/
    (void)taskID;
    (void)event;
	
}


/******************************************************************************************************************
FUNCTION NAME: task_0080msec_periodic

PARAMETER DESCRIPTION:
   oel_rtos_task_id_t taskID - ID of this task
   oel_rtos_event_t   event  - Any event flags that were configured and set.

RETURN VALUE:
   void

DESCRIPTION:
   Task periodic callback function.
   This function is called at the task's periodic rate.
******************************************************************************************************************/
void task_0080msec_periodic(oel_rtos_task_id_t taskID, oel_rtos_event_t event)
{
    /* void to avoid Compiler Error*/
    (void)taskID;
    (void)event;
}

/******************************************************************************************************************
FUNCTION NAME: task_0160msec_periodic

PARAMETER DESCRIPTION:
   oel_rtos_task_id_t taskID - ID of this task
   oel_rtos_event_t   event  - Any event flags that were configured and set.

RETURN VALUE:
   void

DESCRIPTION:
   Task periodic callback function.
   This function is called at the task's periodic rate.
******************************************************************************************************************/
void task_0160msec_periodic(oel_rtos_task_id_t taskID, oel_rtos_event_t event)
{
    /* void to avoid Compiler Error*/
    (void)taskID;
    (void)event;
}

/******************************************************************************************************************
FUNCTION NAME: task_autostart_init

PARAMETER DESCRIPTION:
   oel_rtos_task_id_t taskID - ID of this task

RETURN VALUE:
   void

DESCRIPTION:
   Task initialization callback function.
   This function is only called once at initialization for the task.
******************************************************************************************************************/
void task_autostart_init(oel_rtos_task_id_t taskID)
{
    /* void to avoid Compiler Error*/
    (void)taskID;
}

/******************************************************************************************************************
FUNCTION NAME: task_autostart_periodic

PARAMETER DESCRIPTION:
   oel_rtos_task_id_t taskID - ID of this task
   oel_rtos_event_t   event  - Any event flags that were configured and set.

RETURN VALUE:
   void

DESCRIPTION:
   Task periodic callback function.
   This function is called at the task's periodic rate.
******************************************************************************************************************/
void task_autostart_periodic(oel_rtos_task_id_t taskID, oel_rtos_event_t event)
{
    /* void to avoid Compiler Error*/
    (void)taskID;
    (void)event;
}

/******************************************************************************************************************
FUNCTION NAME: task_background_init

PARAMETER DESCRIPTION:
   oel_rtos_task_id_t taskID - ID of this task

RETURN VALUE:
   void

DESCRIPTION:
   Task initialization callback function.
   This function is only called once at initialization for the task.
******************************************************************************************************************/
void task_background_init(oel_rtos_task_id_t taskID)
{
    /* void to avoid Compiler Error*/
    (void)taskID;
}

/******************************************************************************************************************
FUNCTION NAME: task_background_periodic

PARAMETER DESCRIPTION:
   oel_rtos_task_id_t taskID - ID of this task
   oel_rtos_event_t   event  - Any event flags that were configured and set.

RETURN VALUE:
   void

DESCRIPTION:
   Task periodic callback function.
   This function is called at the task's periodic rate.
******************************************************************************************************************/
void task_background_periodic(oel_rtos_task_id_t taskID, oel_rtos_event_t event)
{
    /* void to avoid Compiler Error*/
    (void)taskID;
    (void)event;
}


const oel_rtos_resource_config_t *app_hal_canv3_resource_config = 
    OEL_BASE(&resource_hal_canv3_vconfig);

	
