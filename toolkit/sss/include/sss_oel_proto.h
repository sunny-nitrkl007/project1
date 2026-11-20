#ifndef SSS_OEL_PROTO_H_
#define SSS_OEL_PROTO_H_

/*******************************************************************************
** COPYRIGHT (C) 2000 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillars proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME: sss_oel_proto.h
DESCRIPTION:
Public prototypes for subsystem services init subsystem module.

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
#ifndef SSS_OEL_TYPES_H_
#include <sss_oel_types.h>
#endif

/******************************************************************************
FUNCTION NAME: oel_init_task()

DESCRIPTION:

  Initializes all the core OEL functions previously included in task_autostart_init.c

REENTRANCY:

  NO.

*******************************************************************************/
void sss_oel_init_task (sss_oel_task_list_config_t * me);

/******************************************************************************
FUNCTION NAME: sss_oel_get_tcb_list()

DESCRIPTION:

  Returns pointer to the master TCB list.

*******************************************************************************/
sss_oel_tcb_list_t *sss_oel_get_tcb_list( void );

/******************************************************************************
FUNCTION NAME: sss_oel_get_task_index()

DESCRIPTION:

  Returns an index into the TCB array for the subsystem task ID corresponding
  to the current task.

REENTRANCY:

  YES.

*******************************************************************************/
sss_task_id_t sss_oel_get_task_index( void  );

/******************************************************************************
FUNCTION NAME: sss_oel_oel_get_task_id()

DESCRIPTION:

  Returns application subsystem task ID corresponding to the current task.

*******************************************************************************/
sss_task_id_t sss_oel_get_ss_task_id(
				     sss_oel_tcb_t *tcb
				     );


/******************************************************************************
FUNCTION NAME: sss_oel_get_method_list()

DESCRIPTION:

  Returns method list corresponding to the current task.

METHOD:

*******************************************************************************/
sss_task_method_group_t *sss_oel_get_method_list(
						 sss_oel_tcb_t *tcb
						 );

/******************************************************************************
FUNCTION NAME: sss_oel_get_tcb()

DESCRIPTION:

  Returns TCB corresponding to the current task.

REENTRANCY:

  YES.

*******************************************************************************/
sss_oel_tcb_t *sss_oel_get_tcb( void );

/******************************************************************************
FUNCTION NAME: sss_init_subsystem()

DESCRIPTION:

  Generic subsystem initialization.

METHOD:
  - Initializes all tasks passed through the argument list.

REENTRANCY:

  NO.

NOTES:

*******************************************************************************/
sss_oel_init_ret_t sss_oel_init_subsystem(
                                          sss_oel_task_list_config_t *task_list
                                          );


/******************************************************************************
FUNCTION NAME: sss_oel_init_package_list()

DESCRIPTION:

  Pcakage list initialization routine

METHOD:

  - Installs all packages passed through the argument list.

REENTRANCY:

  NO.

NOTES:

!!!!!!!!!! IMPORTANT !!!!!!!!!!
  The sequence of execution of package methods within their assigned task
  will be in the same order as the positions of the package definitions
  within the argument list.

*******************************************************************************/
void sss_oel_init_package_list(
			       sss_package_list_config_t package_config
			       );

/******************************************************************************
FUNCTION NAME: sss_oel_task_proc_methods()

DESCRIPTION:

  Subsystem function that allows the caller to process package methods from
  within any task thread.  Assumes task ID mapping (OS dependent) and
  sss_oel_init_subsystem() have been executed during startup.

REENTRANCY:

  YES.

*******************************************************************************/
void sss_oel_task_proc_methods(
			       sss_oel_tcb_t *tcb
			       );

/******************************************************************************
FUNCTION NAME: sss_oel_task_proc_oneshot_methods()

DESCRIPTION:

  Subsystem function that allows the caller to process oneshot methods package from
  within any task thread.  This would primarily be useful for the oneshot processing
  segment of an OSEK extended task.  Assumes task ID mapping (OS dependent) and
  sss_init_subsystem() have been executed during startup.

REENTRANCY:

  YES.

*******************************************************************************/
void sss_oel_task_proc_oneshot_methods(
				       sss_oel_tcb_t *tcb
				       );

/******************************************************************************
FUNCTION NAME: sss_oel_task_proc_periodic_methods()

DESCRIPTION:

  Subsystem function that allows the caller to process package periodic methods from
  within any task thread.  This would primarily be useful for the periodic processing
  segment of an OSEK extended task.  Assumes task ID mapping (OS dependent) and
  sss_init_subsystem() have been executed during startup.

REENTRANCY:

  YES.

*******************************************************************************/
void sss_oel_task_proc_periodic_methods(
					sss_oel_tcb_t *tcb
					);


/******************************************************************************
FUNCTION NAME: sss_task_submit_method()

DESCRIPTION:

  Subsystem function that allows the caller to submit a method to be
  processed in the specified task.

METHOD:

  - Checks for valid task ID.
  - For invalid task ID, returns error.
  - For valid task ID,
      - if method list doesn't exist, create new list
      - adds method to method list
      - return ok

REENTRANCY:

  NO.

NOTES:

  !!!!!!!!!! IMPORTANT !!!!!!!!!!
  Order of method submission will be order of method execution within
  the specified task.

*******************************************************************************/
sss_submit_method_ret_t sss_task_submit_method(
					       sss_task_id_t task_id_ss,
					       sss_task_method_t method,
					       void *work,
					       const void *config
					       );

/******************************************************************************
FUNCTION NAME: sss_oel_get_task_period()

DESCRIPTION:

Returns subsystem ID's corresponding task period.
Callable anytime after sss_oel_init_subsystem().

*******************************************************************************/
hal_second_u32_l20_t sss_oel_get_task_period(
					     sss_task_id_t task_id_ss
					     );

#endif /* SSS_OEL_PROTO_H_ */
