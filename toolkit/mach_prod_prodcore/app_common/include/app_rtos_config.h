/*******************************************************************************
** COPYRIGHT (C) 2013 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar’s proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  app_rtos_config.h
DESCRIPTION:
*******************************************************************************/
#ifndef __APP_RTOS_CONFIG_H__
#define __APP_RTOS_CONFIG_H__

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <platform_declaration.h>


#ifdef A4M1V2

#include <oel_rtos.h>
#ifndef CDL2_MOD_DEFS_H_
#include <cdl2_mod_defs.h>
#endif

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

         /*
         Task Periods

         Task periods are defined as macros to support their use in
         ROM configuration data.  They should be adjusted to match the run
         time values that have been adjusted to supported values.
         */

#define TASK_IO_PERIOD                     OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.020)
#define TASK_250MS_PERIOD                  OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.250)
#define TASK_CBS_CONTROL_PERIOD            OEL_RTOS_SECONDS_DBL_TO_U32_L20(1.0/(CDL2_CBS_UPDATES_PER_SECOND))
#define TASK_CAN_CONTROL_PERIOD			   OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.010)
      /*
      events for task task_multi_event

      NOTE:  These must match events in OSEK oil file.  The osek header
      is not used directly so the source files can be OS independent.
      The app_rtos_config_osek.c checks that they match.  Applications
      for OSEK only should directly use the event macros from osek.
      */


/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

      /*
      task prototypes
      */
oel_rtos_function_t  task_app_io;
oel_rtos_function_t  task_app_250ms;
oel_rtos_function_t  task_background;
oel_rtos_function_t	 task_can;

/*******************************************************************************
** -- Data Declarations
*******************************************************************************/

      /*
      arrays of pointers to initialization functions
      */

extern oel_rtos_init_object_t const * const app_pre_irq_init_list[];
extern oel_rtos_init_object_t const * const app_startup_init_list[];

      /*
      isr parameters
      */

      /*
      task ids
      */

extern oel_rtos_task_id_t task_io_id;
extern oel_rtos_task_id_t task_250ms_id;
extern oel_rtos_task_id_t task_background_id;
extern oel_rtos_task_id_t task_cbs_control_id;
extern oel_rtos_task_id_t task_can_control_id;

#endif


#ifdef A5M4V1

#ifndef   OEL_RTOS_H_
#include <oel_rtos.h>
#endif

#include <oel_rtos_oeluk.h>
#include <cdl2_mod_defs.h>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
/*
Task Periods

Task periods are defined as macros to support their use in
ROM configuration data.  They should be adjusted to match the run
time values that have been adjusted to supported values.
*/
#define TASK_0010MS_PERIOD                OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.010)
#define TASK_0020MS_PERIOD                OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.020)
#define TASK_0250MS_PERIOD                OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.250)
#define TASK_CBS_CONTROL_PERIOD           OEL_RTOS_SECONDS_DBL_TO_U32_L20(1.0/(CDL2_CBS_UPDATES_PER_SECOND))



#define CDL2_CBS_TIME_EXPIRE_EVENT      OEL_RTOS_TIME_EVENT
#define CDL2_CBS_FIFO_INPUT_EVENT       OEL_RTOS_EVENT_N_TO_MASK(0)

/*
** Task Priorities - MUST BE BETWEEN 1 AND 31
*/
#define RESOURCE_BDT_PRIORITY             12
#define RESOURCE_HAL_CANV3_PRIORITY       13
#define RESOURCE_CCP_PRIORITY             15
#define TASK_10MS_PRIORITY                20
#define TASK_20MS_PRIORITY                22
#define TASK_250MS_PRIORITY               24
#define CDL_CBS_TASK_PRIORITY             30
#define TASK_BACKGROUND_PRIORITY          31

/*
** Task Stack Sizes
*/
#define TASK_10MS_STACK_SIZE                4000
#define TASK_20MS_STACK_SIZE                2048
#define TASK_250MS_STACK_SIZE               2048
#define CDL_CBS_TASK_STACK_SIZE             1024
#define TASK_BACKGROUND_STACK_SIZE          2048

/*******************************************************************************
** -- Data Declarations
*******************************************************************************/
extern oel_rtos_function_t       task_10ms;
extern oel_rtos_function_t       task_app_io;
extern oel_rtos_function_t       task_app_250ms;
extern oel_rtos_function_t       task_background;
extern oel_rtos_function_t	     cdl2_cbs_control_task;

/*
arrays of pointers to initialization functions
*/
extern oel_rtos_init_object_t const * const app_pre_irq_init_list[];
extern oel_rtos_init_object_t const * const app_startup_init_list[];

/*
task ids
*/
extern oel_rtos_task_id_t task_0010ms_id;
extern oel_rtos_task_id_t task_0020ms_id;
extern oel_rtos_task_id_t task_0250ms_id;
extern oel_rtos_task_id_t task_background_id;
extern oel_rtos_task_id_t task_cbs_control_id;
extern oel_rtos_task_id_t task_scl_j1939_id;


/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations
*******************************************************************************/

/* Resource configuration information for HAL CANV3 */
extern const oel_rtos_resource_tpc_vconfig_t resource_canv3_port_config;
															   
/* Configuration information for CCP */
extern const oel_rtos_resource_tpc_vconfig_t resource_scl_ccp_vconfig;

/* Resource configuration information for BDT */
extern const oel_rtos_resource_tpc_vconfig_t resource_bdt_j1939_vconfig;

#endif /* #ifndef __APP_RTOS_CONFIG_H__ */

#endif
