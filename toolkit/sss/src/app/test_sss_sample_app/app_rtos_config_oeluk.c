/******************************************************************************************************************
 Copyright 2016 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: app_rtos_config_oeluk.c

Description: RTOS Configuration information for oeluk target
******************************************************************************************************************/

/******************************************************************************************************************
-- #Include's --
******************************************************************************************************************/
#include <oel_oop.h>
#include <oel_rtos_oeluk.h>
#include <hal_watchdog_proto.h>
#include <hal_timer_proto.h>
#include <hal_spi.h>
#include <clock_globals.h>
#include "app_rtos_config.h"
#include "task_id_globals.h"
#include <oel_assert.h>

/******************************************************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
******************************************************************************************************************/

#define RESOURCE_HAL_CANV3_PRIORITY       14

#define TASK0030_PRIORITY                 19
#define TASK0120_PRIORITY                 21
#define TASK1005_PRIORITY                 23

         /*
         Task Stack Sizes
         */
#define TASK0030_STACK_SIZE               2048
#define TASK0120_STACK_SIZE               2048
#define TASK1005_STACK_SIZE               2048


/******************************************************************************************************************
** -- Data Definitions --
******************************************************************************************************************/

oel_rtos_task_id_t       task_0030ms_id;
oel_rtos_task_id_t       task_0120ms_id;
oel_rtos_task_id_t       task_1005ms_id;

static const oel_rtos_oeluk_task_config_t task_config[] =
{
   OEL_RTOS_OELUK_TASK_CONFIG(
      &task_0030ms_id,                          /* RTOS_TASK_ID_PTR */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.000),   /* DELAY */
      TASK_0030MSEC_PERIOD,
      TASK_0030MSEC_PERIOD+
	  OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.500),
      NULL,                                     /* WDOG_HANDLER */
      80,                                       /* TASK_STACK_THRESHOLD */
      "task_0030msec",                          /* NAME */
      task_0030msec,                            /* ENTRY */
      OEL_HEAP_2_ID,                              /* STACK_HEAP */
      TASK0030_STACK_SIZE,                      /* STACK_SIZE */
      TASK0030_PRIORITY,                        /* PRIORITY */
      FALSE,                                    /* SUSPENDED */
      FALSE),                                   /* EXTENDED */

   OEL_RTOS_OELUK_TASK_CONFIG(
      &task_0120ms_id,                          /* RTOS_TASK_ID_PTR */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.000),   /* DELAY */
      TASK_0120MSEC_PERIOD,                     /* PERIOD */
      TASK_0120MSEC_PERIOD +
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.500),   /* WDOG_DELAY */
      NULL,                                     /* WDOG_HANDLER */
      80,                                       /* TASK_STACK_THRESHOLD */
      "task_0120msec",                          /* NAME */
      task_0120msec,                            /* ENTRY */
      OEL_HEAP_2_ID,                              /* STACK_HEAP */
      TASK0120_STACK_SIZE,                      /* STACK_SIZE */
      TASK0120_PRIORITY,                        /* PRIORITY */
      FALSE,                                    /* SUSPENDED */
      FALSE),                                   /* EXTENDED */

   OEL_RTOS_OELUK_TASK_CONFIG(
      &task_1005ms_id,                          /* RTOS_TASK_ID_PTR */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.000),   /* DELAY */
      TASK_1005MSEC_PERIOD,                     /* PERIOD */
      TASK_1005MSEC_PERIOD +                    /* WDOG_DELAY */
	  OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.500),
      NULL,                                      /* WDOG_HANDLER */
      80,                                       /* TASK_STACK_THRESHOLD */
      "task_1005msec",                          /* NAME */
      task_1005msec,                            /* ENTRY */
      OEL_HEAP_2_ID,                              /* STACK_HEAP */
      TASK1005_STACK_SIZE,                      /* STACK_SIZE */
      TASK1005_PRIORITY,                        /* PRIORITY */
      FALSE,                                    /* SUSPENDED */
      FALSE),                                   /* EXTENDED */
};

#define NUMBER_OF_TASKS (sizeof(task_config) / sizeof(oel_rtos_oeluk_task_config_t))
      /*
      rtos config
      */
   const oel_rtos_oeluk_config_t app_oel_rtos_oeluk_config =
   OEL_RTOS_OELUK_CONFIG(
      NUMBER_OF_TASKS,                          /* NUMBER_OF_TASKS */
      task_config,                              /* TASK_CONFIG */
      app_pre_irq_init_list,                    /* PRE_IRQ_INIT */
      app_startup_init_list,                    /* STARTUP_INIT */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.100),   /* WDOG_STARTUP_DELAY */
      NULL,                                     /* WDOG_HANDLER */
      hal_watchdog_strobe,                      /* WDOG_STROBE */
      TRUE,                                     /* STACK_CHECK_ENABLE */
      80,                                       /* SYS_STACK_THRESHOLD */
      NULL,                                     /* STACK_HANDLER */
      TRUE,                                     /* DEBUG */
      5000, /* microseconds */                 /* TICK_PERIOD */
      FALSE);                                   /* EXTENDED */

/* Define configuration of tasks for performance monitor. */
OEL_TASK_OBSERVER_CONFIG(task_config);


  static const oel_rtos_resource_tpc_vconfig_t resource_hal_canv3_vconfig =
      OEL_RTOS_RESOURCE_TPC_VCONFIG( RESOURCE_HAL_CANV3_PRIORITY );

   const oel_rtos_resource_config_t *app_hal_canv3_resource_config =
      OEL_BASE(&resource_hal_canv3_vconfig);

