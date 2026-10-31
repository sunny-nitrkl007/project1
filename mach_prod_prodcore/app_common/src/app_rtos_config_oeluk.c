/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                       %%
*** %% COPYRIGHT (C)2005-2014  CATERPILLAR INC. ALL RIGHTS RESERVED.         %%
*** %%                                                                       %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** FILE NAME   : app_rtos_config_osek.c
***
*** DESCRIPTION : 
***
*******************************************************************************/

/*******************************************************************************
***
***    External function prototypes, data, & symbols
***    -- #Include's --
***
*******************************************************************************/

#include <app_rtos_config.h>

#ifndef STD_TYPES_H_
#include <std_types.h>
#endif

#ifndef APP_PUBLIC_H_
#include <app_public.h>
#endif
/* Core Includes  */
#ifndef OEL_OOP_H_
#include <oel_oop.h>
#endif
#ifndef OEL_RTOS_OELUK_H_
#include <oel_rtos_oeluk.h>
#endif
#ifndef OEL_RTOS_ISR_H_
#include <oel_rtos_isr.h>
#endif
#ifndef HAL_WATCHDOG_PROTO_H_
#include <hal_watchdog_proto.h>
#endif
#ifndef HAL_TIMER_PROTO_H_
#include <hal_timer_proto.h>
#endif
#ifndef HAL_SPI_H_
#include <hal_spi.h>
#endif
#ifndef CDL2_PROTO_H_
#include <cdl2_proto.h>
#endif
#ifndef CLOCK_STRUCT_H_
#include <clock_struct.h>
#endif
#ifndef SCL_J1939_H_
#include <scl_j1939.h>
#endif
#ifndef   OEL_ASSERT_H_
#include <oel_assert.h>
#endif

#ifndef TASK_TIMES_H_
#include <task_times.h>
#endif

/******************************************************************************
***
***    Constants defined for this file
***    -- #Define's --
***
******************************************************************************/

/******************************************************************************
***
***    Data types defined for this file
***    -- Struct's, Typedef's, Enum's --
***
******************************************************************************/
/*Task Watchdog Counters
//     The below counters are incremented whenever the task watchdog fires.
//     The first counter will fire if any periodic task watchdog occurs.
//     This will make it easier to take data and/or trigger the debugger.
*/
unsigned_32   task_ptask_wdog_cnt;
unsigned_32   task_10ms_wdog_cnt;
unsigned_32   task_20ms_wdog_cnt;
unsigned_32   task_250ms_wdog_cnt;
unsigned_32   task_background_wdog_cnt;
unsigned_32   task_cbs_wdog_cnt;


void
task_10ms_wdog_handler(oel_rtos_action_object_t *action_config)
/******************************************************************************* 
   BEFORE: 

   AFTER:  
*******************************************************************************/
{
     (void)action_config;

     task_10ms_wdog_cnt++;
     task_ptask_wdog_cnt++;

     /*reset the ECM*/
     /*NOTE:  Reseting should be enabled all of the time, as this
     //       is required for production ECMs.  However, given the
     //       troubles with execution time, I am going to tie it to
     //       run for development so we will have some backdoor way
     //       to disable the watchdog.
     */
     oel_assert_always(0);

     return;
}

/*Task 10ms Watchdog Configuration
//     This function describes the action that should be taken when
//     the indicated task watchdogs.
*/
oel_rtos_action_object_t  task_10ms_wdog_config =
{
     task_10ms_wdog_handler       /*Function To Call When Watchdog Triggered*/
};


void
task_20ms_wdog_handler(oel_rtos_action_object_t *action_config)
/******************************************************************************* 
   BEFORE: 

   AFTER:  
*******************************************************************************/
{
     (void)action_config;

     task_20ms_wdog_cnt++;
     task_ptask_wdog_cnt++;

     /*reset the ECM*/
     /*NOTE:  Reseting should be enabled all of the time, as this
     //       is required for production ECMs.  However, given the
     //       troubles with execution time, I am going to tie it to
     //       run for development so we will have some backdoor way
     //       to disable the watchdog.
     */
     oel_assert_always(0);

     return;
}

/*Task 20ms Watchdog Configuration
//     This function describes the action that should be taken when
//     the indicated task watchdogs.
*/
oel_rtos_action_object_t  task_20ms_wdog_config =
{
     task_20ms_wdog_handler       /*Function To Call When Watchdog Triggered*/
};






void
task_250ms_wdog_handler(oel_rtos_action_object_t *action_config)
/******************************************************************************* 
   BEFORE: 

   AFTER:  
*******************************************************************************/
{
     (void)action_config;

     task_250ms_wdog_cnt++;
     task_ptask_wdog_cnt++;

     /*reset the ECM*/
     /*NOTE:  Reseting should be enabled all of the time, as this
     //       is required for production ECMs.  However, given the
     //       troubles with execution time, I am going to tie it to
     //       run for development so we will have some backdoor way
     //       to disable the watchdog.
     */
     oel_assert_always(0);

     return;
}

/*Task 250ms Watchdog Configuration
//     This function describes the action that should be taken when
//     the indicated task watchdogs.
*/
oel_rtos_action_object_t  task_250ms_wdog_config =
{
     task_250ms_wdog_handler       /*Function To Call When Watchdog Triggered*/
};


/******************************************************************************* 
   BEFORE: 

   AFTER:  
*******************************************************************************/


void
task_cbs_wdog_handler(oel_rtos_action_object_t *action_config)
/******************************************************************************* 
   BEFORE: 

   AFTER:  
*******************************************************************************/
{
     (void)action_config;

     task_cbs_wdog_cnt++;

     return;
}




/*Task CBS Watchdog Configuration
//     This function describes the action that should be taken when
//     the indicated task watchdogs.
*/
oel_rtos_action_object_t  task_cbs_wdog_config =
{
     task_cbs_wdog_handler        /*Function To Call When Watchdog Triggered*/
};


void
task_background_wdog_handler(oel_rtos_action_object_t *action_config)
/******************************************************************************* 
   BEFORE: 

   AFTER:  
*******************************************************************************/
{
     (void)action_config;

     task_background_wdog_cnt++;

     return;
}

/*Task Background Watchdog Configuration
//     This function describes the action that should be taken when
//     the indicated task watchdogs.
*/
oel_rtos_action_object_t  task_background_wdog_config =
{
     task_background_wdog_handler /*Function To Call When Watchdog Triggered*/
};

/*****************************************************************************/
/*****                   OEL RTOS Task Configuration                     *****/

/*OEL RTOS Task Id
//     These variables are generic Real Time Operating System (RTOS)
//     ids (probably more properly called handles/objects) for each task.
//     Note that this interface to the task id is operating system independent.
//     The following variables will always be valid no matter if we were
//     using OSEK, VRTX, Linix, or Windows (ack!).
//
//     These variables may be used by other parts of the software to
//     be aware of the task they are executing in.
*/
oel_rtos_task_id_t task_0010ms_id;
oel_rtos_task_id_t task_0020ms_id;
oel_rtos_task_id_t task_0250ms_id;
oel_rtos_task_id_t task_background_id;
oel_rtos_task_id_t task_cbs_control_id;

/***************  task config *************************************************/


static const oel_rtos_oeluk_task_config_t task_config[] =
{


   OEL_RTOS_OELUK_TASK_CONFIG(             /*Task 20ms Configuration        */
      &task_0020ms_id,                          /* Pointer To RTOS Task Id   */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.000),   /* Initial Delay For Task    */
      TASK_0020MS_PERIOD,                       /* Task Period               */
      10*TASK_0020MS_PERIOD,                    /* Watchdog Duration         */
      &task_20ms_wdog_config,                   /* Watchdog Handler          */
      80,                                       /* TASK_STACK_THRESHOLD */
      "task_app_io",                                /* NAME */
      task_app_io,                                  /* ENTRY */
      OEL_HEAP_2_ID,                            /* STACK_HEAP */
      TASK_20MS_STACK_SIZE,                       /* STACK_SIZE */
      TASK_20MS_PRIORITY,                         /* PRIORITY */
      FALSE,                                    /* SUSPENDED */
      FALSE),                                   /* EXTENDED */

  
       
       
    OEL_RTOS_OELUK_TASK_CONFIG
   (                                       /*Task 250ms Configuration        */
      &task_0250ms_id,                          /* Pointer To RTOS Task Id   */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.000),   /* Initial Delay For Task    */
      TASK_0250MS_PERIOD,                       /* Task Period               */
      10*TASK_0250MS_PERIOD,                    /* Watchdog Duration         */
      &task_250ms_wdog_config,                   /* Watchdog Handler          */
      80,                                       /* TASK_STACK_THRESHOLD */
      "task_app_250ms",                                /* NAME */
      task_app_250ms,                                  /* ENTRY */
      OEL_HEAP_2_ID,                            /* STACK_HEAP */
      TASK_250MS_STACK_SIZE,                       /* STACK_SIZE */
      TASK_250MS_PRIORITY,                         /* PRIORITY */
      FALSE,                                    /* SUSPENDED */
      FALSE),                                   /* EXTENDED */
      
   OEL_RTOS_OELUK_TASK_CONFIG
   (                                       /*Task CDL CBS Configuration     */
      &task_cbs_control_id,                /* RTOS_TASK_ID_PTR */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.010),   /* DELAY */
      TASK_CBS_CONTROL_PERIOD,             /* PERIOD */
      TASK_CBS_CONTROL_PERIOD +
        OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.100), /* WDOG_DELAY */
      &task_cbs_wdog_config,                    /* Watchdog Handler          */
      80,                                       /* TASK_STACK_THRESHOLD */
      "cdl2_cbs_control_task",                  /* NAME */
      cdl2_cbs_control_task,                    /* ENTRY */
      OEL_HEAP_2_ID,                            /* STACK_HEAP */
      CDL_CBS_TASK_STACK_SIZE,                  /* STACK_SIZE */
      CDL_CBS_TASK_PRIORITY,                    /* PRIORITY */
      FALSE,                                    /* SUSPENDED */
      FALSE),                                   /* EXTENDED */

   OEL_RTOS_OELUK_TASK_CONFIG
   (                                       /*Task Background Configuration  */
      &task_background_id,                      /* Pointer To RTOS Task Id   */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.000),   /* Initial Delay For Task    */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.000),   /* Task Period               */
      HAL_U32_MAX,                              /* Watchdog Duration[Disable]*/
      &task_background_wdog_config,             /* Watchdog Handler          */
      80,                                       /* TASK_STACK_THRESHOLD */
      "task_background",                        /* NAME */
      task_background,                          /* ENTRY */
      OEL_HEAP_2_ID,                            /* STACK_HEAP */
      TASK_BACKGROUND_STACK_SIZE,               /* STACK_SIZE */
      TASK_BACKGROUND_PRIORITY,                 /* PRIORITY */
      FALSE,                                    /* SUSPENDED */
      FALSE)                                    /* EXTENDED */
      
};

#define NUMBER_OF_TASKS (sizeof(task_config) / sizeof(oel_rtos_oeluk_task_config_t))

      /*
      rtos config
      */
const oel_rtos_oeluk_config_t app_oel_rtos_oeluk_config =
OEL_RTOS_OELUK_CONFIG_I2
(
      NUMBER_OF_TASKS,                          /* NUMBER_OF_TASKS */
      task_config,                              /* TASK_CONFIG */
      app_pre_irq_init_list,                    /* PRE_IRQ_INIT */
      app_startup_init_list,                    /* STARTUP_INIT */
      OEL_RTOS_SECONDS_DBL_TO_U32_L20(1.000),   /* WDOG_STARTUP_DELAY */
      &oel_rtos_wdog_default_handler,           /* Default Watchdog Handler  */
      hal_watchdog_strobe,                      /* Watchdog Strobe Function */
      TRUE,                                     /* STACK_CHECK_ENABLE */
      80,                                       /* SYS_STACK_THRESHOLD */
      NULL,                                     /* STACK_HANDLER */
      0,                                        /* Startup memory test function ptr */
      TRUE,                                     /* DEBUG */
      10000, /* microseconds */                  /* TICK_PERIOD */
      FALSE,                                    /* EXTENDED */
      NULL,                                     /* Pointer to subloop processing function */
      0                                         /* Subloop divisor of tick period      */

);

/* Define configuration of tasks for performance monitor. */
OEL_TASK_OBSERVER_CONFIG(task_config);

/* Resource configuration information for HAL CANV3 */
const oel_rtos_resource_tpc_vconfig_t resource_canv3_port_config =
   OEL_RTOS_RESOURCE_TPC_VCONFIG( RESOURCE_HAL_CANV3_PRIORITY );


/* Configuration information for BDT */
const oel_rtos_resource_tpc_vconfig_t resource_bdt_j1939_vconfig =
   OEL_RTOS_RESOURCE_TPC_VCONFIG( RESOURCE_BDT_PRIORITY );

const oel_rtos_semaphore_pi_vconfig_t clock_semaphore_vconfig =
            OEL_RTOS_SEMAPHORE_PI_VCONFIG(1);

/*OEL RTOS SCL CCP Resource Lock To Task Priority Ceiling Virtual Configuration
//     CAN Calibration Protocol (CCP) Resource
//
//     On A4:M1 platforms, this resource is used by the CCP module to
//     keep multiple copies of itself from running at the same time.
//     An application may call the CCP update function from a background
//     task as well as from a periodic task.  This will allow transfer of
//     data to happen sooner if there is spare time.
//
//     This variable contains all of the OSEK information that is needed to
//     create a general RTOS resource that can be accessed in a operating
//     system generic way from this point forward.
//
//     This resource allows a given thread of software to lock the
//     current execution of code such that even the highest priority task
//     may not interrupt.  Note that this only locks to the *task* ceiling
//     on priority:  interrupt routines may still interrupt execution locked
//     by this resource.
*/
const oel_rtos_resource_tpc_vconfig_t  resource_scl_ccp_vconfig =
OEL_RTOS_RESOURCE_TPC_VCONFIG
(
     RESOURCE_CCP_PRIORITY  /*OSEK Resource Id*/
);
/* This must have this name */
const clock_config_t app_clock_config =
{
    OEL_BASE(&clock_semaphore_vconfig)
};

HOUR_SET_RESOURCE_ID(OELUK_CLOCK_RES);
