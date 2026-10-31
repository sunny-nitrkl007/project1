/*******************************************************************************
** COPYRIGHT (C) 2001-2003 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar’s proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  tasks.c
DESCRIPTION:
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
/* Application Includes */
#include <app_rtos_config.h>
#include <oil.h>

/* Core Includes */
#include <oel_oop.h>
#include <oel_rtos_osek.h>
#include <oel_rtos_isr.h>
#include <oel_assert.h>
#include <hal_watchdog_proto.h>
#include <hal_timer_proto.h>
#include <hal_spi.h>
#include <clock_globals.h>
#include <cdl2_proto.h>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

      /*
      verify the osek event masks match the definitions in app_rtos_config.h
      */

#if OSEK_OEL_RTOS_TIME_EVENT != OEL_RTOS_TIME_EVENT
   #error "OSEK_OEL_RTOS_TIME_EVENT != OEL_RTOS_TIME_EVENT"
#endif


/*******************************************************************************
** -- Data Definitions
*******************************************************************************/

      /*
      isr paramters
      */


      /*
      task ids
      */

oel_rtos_task_id_t task_io_id;
oel_rtos_task_id_t task_250ms_id;
oel_rtos_task_id_t task_background_id;
oel_rtos_task_id_t task_cbs_control_id;
oel_rtos_task_id_t task_can_control_id;

/* prototypes for wdog handlers */
void io_task_wdog_handler(oel_rtos_action_object_t* never_used);
void task_250ms_wdog_handler(oel_rtos_action_object_t* never_used);
void background_task_wdog_handler(oel_rtos_action_object_t* never_used);
void can_task_wdog_handler(oel_rtos_action_object_t* never_used);

/* pointers to wdog handlers */
oel_rtos_timer_alarm_handler_t io_task_wdog_handler_ptr = &io_task_wdog_handler;
oel_rtos_timer_alarm_handler_t task_250ms_wdog_handler_ptr = &task_250ms_wdog_handler;
oel_rtos_timer_alarm_handler_t background_task_wdog_handler_ptr = &background_task_wdog_handler;
oel_rtos_timer_alarm_handler_t can_task_wdog_handler_ptr = &can_task_wdog_handler;

const cdl2_cbs_oel_config_t app_cdl2_cbs_oel_config = 
CDL2_CBS_OEL_CONFIG(&task_cbs_control_id,
					__CDL2_CBS_TIME_EXPIRE_EVENT__,
					__CDL2_CBS_FIFO_INPUT_EVENT__);

      /*
      task config
      */

static const oel_rtos_task_config_t task_config[] =
{
   OEL_RTOS_OSEK_TASK_CONFIG(
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.000),   /* DELAY */
      TASK_IO_PERIOD,                           /* PERIOD */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(1.000),  	/* WDOG_DELAY */
      &io_task_wdog_handler_ptr,                /* WDOG_HANDLER */
      NULL,                                     /* DELAY_OK */
      TASK_IO,                                  /* OSEK_TASK_ID */
      TASK_IO_ALARM,                            /* OSEK_ALARM_ID */
      NULL,                                     /* OSEK_PEND_EVENT */
      &task_io_id),                             /* RTOS_TASK_ID_PTR */

   OEL_RTOS_OSEK_TASK_CONFIG(
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.000),   /* DELAY */
      TASK_250MS_PERIOD,                        /* PERIOD */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.500),   /* WDOG_DELAY */
      &task_250ms_wdog_handler_ptr,             /* WDOG_HANDLER */
      NULL,                                     /* DELAY_OK */
      TASK_250MS,                               /* OSEK_TASK_ID */
      TASK_250MS_ALARM,                         /* OSEK_ALARM_ID */
      NULL,                                     /* OSEK_PEND_EVENT */
      &task_250ms_id),                          /* RTOS_TASK_ID_PTR */

   OEL_RTOS_OSEK_TASK_CONFIG(
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0),       /* DELAY */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0),       /* PERIOD */
      UINT32_MAX,   							/* WDOG_DELAY */
      &background_task_wdog_handler_ptr,        /* WDOG_HANDLER */
      NULL,                                     /* DELAY_OK */
      TASK_BACKGROUND,                          /* OSEK_TASK_ID */
      0xFF,                                     /* OSEK_ALARM_ID */
      NULL,                                     /* OSEK_PEND_EVENT */
      &task_background_id),                     /* RTOS_TASK_ID_PTR */

   OEL_RTOS_OSEK_TASK_CONFIG(
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0),       /* DELAY */
      TASK_CBS_CONTROL_PERIOD,                  /* PERIOD */
      UINT32_MAX,                               /* WDOG_DELAY */
      NULL,                                     /* WDOG_HANDLER */
      NULL,                                     /* DELAY_OK */
      __CDL2_CBS_CONTROL_TASK__,                /* OSEK_TASK_ID */
      __CDL2_CBS_TIME_EXPIRE_ALARM__,           /* OSEK_ALARM_ID */
      NULL,                                     /* OSEK_PEND_EVENT */
      &task_cbs_control_id),					/* RTOS_TASK_ID_PTR */

	OEL_RTOS_OSEK_TASK_CONFIG(
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.000),   /* DELAY */
      TASK_CAN_CONTROL_PERIOD,                  /* PERIOD */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(1.000),   /* WDOG_DELAY */
      &can_task_wdog_handler_ptr,               /* WDOG_HANDLER */
      NULL,                                     /* DELAY_OK */
      __CAN_CONTROL_TASK__,                     /* OSEK_TASK_ID */
      TASK_CAN_CONTROL_ALARM,                   /* OSEK_ALARM_ID */
      NULL,                                     /* OSEK_PEND_EVENT */
      &task_can_control_id),					/* RTOS_TASK_ID_PTR */
};


#define NUMBER_OF_TASKS (sizeof(task_config) / sizeof(oel_rtos_task_config_t))

      /*
      app_oel_rtos_osek0_config
      */

/* uses the default platform specific definitions in HAL */

      /*
      app_oel_rtos_osek_config
      */

const oel_rtos_osek_config_i2_t app_oel_rtos_osek_config =
   OEL_RTOS_OSEK_CONFIG_I2(
      NUMBER_OF_TASKS,                          /* NUMBER_OF_TASKS */
      task_config,                              /* TASK_CONFIG */
      app_pre_irq_init_list,                    /* PRE_IRQ_INIT */
      app_startup_init_list,                    /* STARTUP_INIT */
      TRUE,                                     /* WDOG_ENABLED */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(1.000),   /* WDOG_STARTUP_DELAY */
      NULL,                                     /* WDOG_HANDLER */
      hal_watchdog_strobe,                      /* WDOG_STROBE */
      hal_timer_query_period,                   /* TICK_QUERY */
      hal_timer_dec_enable,                     /* TICK_ENABLE */
      SYSTEM_COUNTER,                           /* OSEK_SYSTEM_COUNTER */
      RES_SCHEDULER,                            /* RES_SCHEDULER */
      SEMAPHORE_EVENT,                          /* SEMAPHORE_EVENT */
      DELAY_EVENT,                              /* DELAY_EVENT */
      20,                                       /* OSEK_MAX_TID_VALUE */
      TRUE,                                     /* FPU_IS_ENABLED */
      TRUE);                                    /* DEBUG */



      /*
      spi config
      */

static const oel_rtos_resource_tpc_vconfig_t resource_spi_bus_vconfig =
    OEL_RTOS_RESOURCE_TPC_VCONFIG(
        SPI_Bus);

/* This must have this name because core externs it and defined it, but we need to override it.
   It was by design that this is overriding the core variable of the same name.
*/
const hal_spi_config_t app_hal_spi_config =
{
    OEL_BASE(&resource_spi_bus_vconfig)
};

      /*
      clock config
      */
static const oel_rtos_semaphore_pi_vconfig_t clock_semaphore_vconfig =
    OEL_RTOS_SEMAPHORE_PI_VCONFIG(1);

/* This must have this name because core externs it and defines it, but we need to override it.
   It was by design that this is overriding the core variable of the same name.
*/
const clock_config_t app_clock_config =
{
    OEL_BASE(&clock_semaphore_vconfig)
};

/* Override this function, otherwise it will create a new semaphore on the fly and not use ours.
   Not that that's a really bad thing, but it is deceiving to set it up here and not use it.
*/
void clock_set_res_id ( hal_u08_t  res_id ) { (void)res_id; }


      /*
      mutex
      */

      /*
      mutex config
      */



/******************************************************************************
FUNCTION NAME:  OSEK specific task funtions
DESCRIPTION:

   OSEK task functions have OSEK specific names created the the TASK() macro.
   Wrapper functions are created here so the source files for the tasks can
   be OS independent.  Alternately, if the application only supports OSEK
   these source files can directly use the OSEK specific names.

PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/

TASK(TASK_IO)
{
   oel_posek_msr_correction();    /* Correct pOSEK task msr defect.
                                     Also supports enabling of FPU.
                                     Must be at start of each task. */
   oel_fpu_enable();

   task_app_io();
}

TASK(TASK_250MS)
{
   oel_posek_msr_correction();    /* Correct pOSEK task msr defect.
                                     Also supports enabling of FPU.
                                     Must be at start of each task. */
   oel_fpu_enable();
   
   task_app_250ms();
}

TASK(TASK_BACKGROUND)
{
   oel_posek_msr_correction();    /* Correct pOSEK task msr defect.
                                     Also supports enabling of FPU.
                                     Must be at start of each task. */
   oel_fpu_enable();
   
   task_background();
}

TASK(__CDL2_CBS_CONTROL_TASK__)
{
   oel_posek_msr_correction();    /* Correct pOSEK task msr defect.
                                     Also supports enabling of FPU.
                                     Must be at start of each task. */
   oel_fpu_enable();
   
   cdl2_cbs_control_task();
}

TASK(__CAN_CONTROL_TASK__)
{
   oel_posek_msr_correction();    /* Correct pOSEK task msr defect.
                                     Also supports enabling of FPU.
                                     Must be at start of each task. */
  task_can(); 
}


/* WDog handlers */
void io_task_wdog_handler(oel_rtos_action_object_t* never_used)
{
	(void)never_used;    /* access arg to suppress warning */               
	oel_assert_always(0);
	/* DOES NOT RETURN */
	return;
}

void task_250ms_wdog_handler(oel_rtos_action_object_t* never_used)
{
	(void)never_used;    /* access arg to suppress warning */               
	oel_assert_always(0);
	/* DOES NOT RETURN */
	return;
}

void background_task_wdog_handler(oel_rtos_action_object_t* never_used)
{
	(void)never_used;    /* access arg to suppress warning */               
	oel_assert_always(0);
	/* DOES NOT RETURN */
	return;
}

/* WDog handlers */
void can_task_wdog_handler(oel_rtos_action_object_t* never_used)
{
	(void)never_used;    /* access arg to suppress warning */               
	oel_assert_always(0);
	/* DOES NOT RETURN */
	return;
}


