/*******************************************************************************
COPYRIGHT (C) 2011 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:  app_rtos_config_posix.c

DESCRIPTION: posix Configuration
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
******************************************************************************/
#include <oel_oop.h>
#include <oel_rtos_posix.h>
#include <hal_watchdog_proto.h>
#include <oel_rtos.h>
#include <hal_timer_proto.h>
#include <hal_spi.h>
#include "app_rtos_config.h"
#include "bmi_cdl_recv_main.h"

static void app_wdog_strobe(void);

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
/*
  Task Priorities
*/
#define CDL2_CBS_CONTROL_TASK_PRIORITY   -21

#define APP_RECV_MAIN_TASK_PRIORITY      -20

/*
  Task Stack Sizes
*/
#define CDL2_CBS_CONTROL_TASK_STCK  10240

#define APP_RECV_MAIN_TASK_STACK  10240




/*******************************************************************************
** -- Data Definitions
*******************************************************************************/

oel_rtos_task_id_t cdl2_cbs_control_task_id;
oel_rtos_task_id_t app_recv_main_task_id;

/*
task config
*/

static const oel_rtos_posix_task_config_t task_config[] =
{
   OEL_RTOS_POSIX_TASK_CONFIG_I1(
        &cdl2_cbs_control_task_id,                /* RTOS_TASK_ID_PTR */
        OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.000),   /* DELAY */
        CDL2_CBS_CONTROL_TASK_PERIOD,             /* PERIOD */
        CDL2_CBS_CONTROL_TASK_PERIOD +            /* WDOG_DELAY */
        OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.100),
        NULL,                                     /* WDOG_HANDLER */
        80,                                       /* TASK_STACK_THRESHOLD */
        "cdl2_cbs_control_task",                  /* NAME */
        cdl2_cbs_control_task,                    /* ENTRY */
        CDL2_CBS_CONTROL_TASK_STCK,               /* STACK_SIZE */
        CDL2_CBS_CONTROL_TASK_PRIORITY,           /* PRIORITY */
        SCHED_FIFO),                              /* SCHEDULING POLICY */

   OEL_RTOS_POSIX_TASK_CONFIG_I1(
        &app_recv_main_task_id,                		/* RTOS_TASK_ID_PTR */
        OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.000),   	/* DELAY */
        APP_RECV_MAIN_TASK_PERIOD,             		/* PERIOD */
        APP_RECV_MAIN_TASK_PERIOD +            		/* WDOG_DELAY */
        OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.100),
        NULL,                                     	/* WDOG_HANDLER */
        80,                                       	/* TASK_STACK_THRESHOLD */
        "app_recv_main_task",                  		/* NAME */
        app_recv_main_task,                    		/* ENTRY */
        APP_RECV_MAIN_TASK_STACK,               	/* STACK_SIZE */
        APP_RECV_MAIN_TASK_PRIORITY,           		/* PRIORITY */
        SCHED_FIFO),                                /* SCHEDULING POLICY */

};


#define NUMBER_OF_TASKS (sizeof(task_config) / sizeof(oel_rtos_posix_task_config_t))

/*
rtos config
*/
oel_rtos_posix_config_t app_oel_rtos_posix_config =
    OEL_RTOS_POSIX_CONFIG(
        NUMBER_OF_TASKS,                          /* NUMBER_OF_TASKS */
        task_config,                              /* TASK_CONFIG */
        app_pre_irq_init_list,                    /* PRE_IRQ_INIT */
        app_startup_init_list,                    /* STARTUP_INIT */
        OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.100),   /* WDOG_STARTUP_DELAY */
        NULL,                                     /* WDOG_HANDLER */
        &app_wdog_strobe,                         /* WDOG_STROBE */
        TRUE,                                     /* STACK_CHECK_ENABLE */
        80,                                       /* SYS_STACK_THRESHOLD */
        NULL,                                     /* STACK_HANDLER */
        TRUE,                                     /* DEBUG */
        OEL_RTOS_SECONDS_DBL_TO_U64_L32(0.010));  /* TICK_PERIOD */

static void app_wdog_strobe(void)
{
    /*Stub Function */
}


/*   resources  */
static const oel_rtos_resource_pi_vconfig_t resource_hal_canv3_vconfig =
    OEL_RTOS_RESOURCE_PI_VCONFIG();

const oel_rtos_resource_config_t *app_hal_canv3_resource_config =
    OEL_BASE(&resource_hal_canv3_vconfig);

/*   scl_ccp resource configuration      */
static const oel_rtos_resource_pi_vconfig_t app_scl_ccp_resource_tpc_vconfig = \
        OEL_RTOS_RESOURCE_PI_VCONFIG();

const oel_rtos_resource_config_t *app_scl_ccp_resource_config = \
        OEL_BASE(&app_scl_ccp_resource_tpc_vconfig);








