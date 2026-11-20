/*******************************************************************************
** COPYRIGHT (C) 2011-2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:  app_rtos_config_posix.c
DESCRIPTION:
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include "app_rtos_config.h"
#include <oel_oop.h>
#include <oel_rtos_posix.h>
#include <hal_watchdog_proto.h>
#include <scl_j1939.h>
#include <hal_timer_proto.h>
#include <hal_spi.h>
#include <oel_rtos.h>


static void app_wdog_strobe(void);


/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
         /*
         Task Priorities
         */
#define RESOURCE_HAL_CANV3_PRIORITY 14
#define RESOURCE_SCL_CAN_PRIORITY 14
#define TASK_CAN_PRIORITY         15



/*******************************************************************************
** -- Data Definitions
*******************************************************************************/

      /*
      task ids
      */
   oel_rtos_task_id_t scl_CAN_control_task_id;
      /*
      task config
      */

static const oel_rtos_posix_task_config_t task_config[] =
{
   OEL_RTOS_POSIX_TASK_CONFIG(
      &scl_CAN_control_task_id,               /* RTOS_TASK_ID_PTR */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.000),   /* DELAY */
      SCL_CAN_TASK_PERIOD                 ,   /* PERIOD */
      SCL_CAN_TASK_PERIOD +
         OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.100),/* WDOG_DELAY */
      NULL,                                     /* WDOG_HANDLER */
      80,                                       /* TASK_STACK_THRESHOLD */
      "scl_CAN_control_task",                 /* NAME */
      scl_CAN_control_task,                   /* ENTRY */
      2000,                                     /* STACK_SIZE */
      TASK_CAN_PRIORITY),                      /* PRIORITY */
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
      app_wdog_strobe,                          /* WDOG_STROBE */
      TRUE,                                     /* STACK_CHECK_ENABLE */
      80,                                       /* SYS_STACK_THRESHOLD */
      NULL,                                     /* STACK_HANDLER */
      TRUE,                                     /* DEBUG */
      OEL_RTOS_SECONDS_DBL_TO_U64_L32(0.01));   /* TICK_PERIOD */


static void app_wdog_strobe(void)
{
}


