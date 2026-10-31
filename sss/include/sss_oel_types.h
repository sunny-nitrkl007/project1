#ifndef SSS_OEL_TYPES_H_
#define SSS_OEL_TYPES_H_

/*******************************************************************************
** COPYRIGHT (C) 2000 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillars proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME: sss_oel_types.h
DESCRIPTION:
Typedef's for subsystem services.

*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations
*******************************************************************************/

#ifndef HAL_TYPES_H_
#include <hal_types.h>
#endif

#ifndef HAL_STD_TYPES_H_
#include <hal_std_types.h>
#endif

#ifndef SSS_OEL_DEFS_H_
#include <sss_oel_defs.h>
#endif

#ifndef OEL_RTOS_H_
#include <oel_rtos.h>
#endif

typedef hal_u08_t sss_boolean_t;		/* Define subsystem boolean type. */
typedef hal_u08_t sss_task_id_t;		/* Define subsystem alias for RTOS task ID type. */
typedef hal_u08_t sss_submit_method_ret_t;	/* Define task submit method return type. */

typedef sss_boolean_t (*sss_get_key_switch_t)( void );	/* Key switch interface method. */

typedef void (*sss_task_method_t)(
				  void *work,	/* Pointer to workspace. */
				  const void *config	/* Pointer to config. */
				  );

/* Application specific task methods submitted at run time.
   -------------------------------------------------------------------------------- */

typedef struct sss_task_method_item_s
{
  sss_task_method_t method;  		/* Pointer to method. */
  void *work;				/* Pointer to workspace. */
  const void *config;			/* Pointer to config. */
  struct sss_task_method_item_s *next;	/* Pointer to next function,
						   NULL if end of list. */
}
sss_task_method_item_t;

/* Task method group.
   -------------------------------------------------------------------------------- */

typedef hal_u08_t sss_task_method_type_t;

typedef struct 
{
  sss_task_method_item_t *oneshot;	/* Array of oneshot init method lists (per task ID). */
  sss_task_method_item_t *periodic;	/* Array of periodic method lists (per task ID). */
}
sss_task_method_group_t;

/* Define subsystem package type.
   -------------------------------------------------------------------------------- */

typedef struct
{
  sss_task_method_t init;	/* Package init function. */
  void *work;		/* Package pointer to workspace. */
  const void *config;	/* Package pointer to configuration. */
}
sss_package_t;

/* Define subsystem package type.
   -------------------------------------------------------------------------------- */

typedef struct
{
  sss_package_t **package;	/* Array of pointers to package configs. */
  hal_u08_t number_of_packages;	/* Number of packages. */
}
sss_package_list_config_t;

/* Define subsystem init return type.
   -------------------------------------------------------------------------------- */

typedef struct
{
  hal_u08_t status;		/* Init subsystem error status return value. */
  sss_task_id_t task_id;	/* Task ID upon return from subsystem init. */
}
sss_oel_init_ret_t;

/* Define SSS task ID translation.
   -------------------------------------------------------------------------------- */

typedef struct 
{ /* Subsystem and OS task ID's may are not necessarily the same. */
  sss_task_id_t ss;			/* User defined subsystem task ID. */
  oel_rtos_task_id_t * os;	/* OS (Operating System) task ID. */
  hal_second_u32_l20_t period_desired;	/* Desired task period (per task ID),
					   LSB = u32_l20 sec. */
}
sss_oel_task_map_t;

/* Define subsystem task configuration list type.
   In the future, may need to extend this to include:
   - task type (periodic, aperiodic, ...),
   - task priority,
   - ???
   -------------------------------------------------------------------------------- */

typedef struct
{
  sss_oel_task_map_t *map;	/* Array of task ID mappings. */
  sss_task_id_t number_of_tasks;	/* Number of tasks. */
}
sss_oel_task_list_config_t;

/* Define master SSS task control block.
   -------------------------------------------------------------------------------- */

typedef struct
{
  sss_oel_task_map_t task_map;		/* SSS to OS task ID mapping (per task ID). */
  sss_task_method_group_t method_list;	/* List of method groups (per task ID). */
  hal_second_u32_l20_t period_actual;	/* Actual task period (per task ID),
					   LSB = u32_l20 sec. */
}
sss_oel_tcb_t;

/* Define master SSS task control block.
   -------------------------------------------------------------------------------- */

typedef struct
{
  sss_oel_tcb_t *tcb;			/* Array of SSS TCB's. */
  sss_task_id_t number_of_tasks;	/* Number of SSS TCB's. */
  hal_second_u32_l20_t period_os_tick;	/* Desired OS Tick period, LSB = u32_l20 sec. */
 
}
sss_oel_tcb_list_t;

/* subsystem control types
   -------------------------------------------------------------------------------*/
typedef hal_u08_t sss_subsys_control_elem_type_t;

#endif /* SSS_OEL_TYPES_H_ */
