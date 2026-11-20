/*******************************************************************************
** COPYRIGHT (C) 2005 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar’s proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  perfmon.h
DESCRIPTION:

   This file is the top level header for the performance monitor component.

*******************************************************************************/
#ifndef _PERFMON_H_
#define _PERFMON_H_

/*******************************************************************************
** -- #Include's --
*******************************************************************************/

#include <std_t.h>
#include <hal_types.h>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
typedef struct
{
uint_least32_t task_start_time;
uint_least32_t interrupt_ex_timer;
uint_least32_t task_measure_ex_start_time;
uint_least32_t task_ex_time;
bool_least_t task_active;
} perfmon_task_work_t;

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/


/*******************************************************************************
** -- Data Definitions
*******************************************************************************/

extern hal_u32_t   perfmon_isr_time_ctr;
/* The accumulated time spent in interrupt service routines.
   1 bit = 1 usec. */

extern hal_u32_t   perfmon_isr_cmpl_ctr;
/* The number of interrupts that have been serviced */

extern hal_u32_t   perfmon_isr_nest_ctr;
/* The number of interrupt service routines that are currently active
   A number greater than 1 indicates that interrupt service routines are
   nested.  A value of zero means no interrupt is active.  As viewed from
   a task this value should always be zero!  */

extern hal_u32_t   perfmon_isr_occr_ctr;
/* The number of interrupts that have occurred since the nesting counter
   since we last exited all interrupts.  This value can be >1 if interrupts
   nest. This value increments with each interrupt service routine that
   is started.  It is reset to 0 when the nesting level drops to 0.
   This value is not the same as the maximum nesting depth, since new
   interrupts can be pending when a nested interrupt service finishes.
   We could service 3 or more interrupts since the last main level
   code was executed, even with a maximum nesting level of 2.  */

extern hal_u32_t   perfmon_isr_entry_time;
/* The realtime time stamp for when the first of one or more successive
   interrupts is started. */

extern hal_u32_t   perfmon_isr_measure_start_time_ctr;
/* The interrupt execution time value when a measurement interval
   started. */

extern hal_u32_t   perfmon_isr_measure_cmpl_ctr;
/* The interrupt completion count when a measurement interval started. */


/******************************************************************************
FUNCTION NAME:
DESCRIPTION:

PARAMETER DESCRIPTION:

RETURN VALUE:
*******************************************************************************/


/*******************************************************************************
FUNCTION NAME:  read_spr_TBL

DESCRIPTION:
   This function returns the value of the lower 32 bit half of the timebase
   register.

REENTRANCY: This code is not reentrant.

PARAMETER DESCRIPTION: none

RETURN VALUE: The current timebase value as 32bit unsigned value.  The scaling
is dependent on the configuration, but for all known application it is 1.00
microsecond per bit.

Note:
   This assembly language macro is specific to the Diab compiler and the
   PowerPC processor architecture.

*******************************************************************************/

/* This assembly function returns the TBL (Lower Timebase) register value
   The EABI calling conventions use R3 as the return value for
   32 bit values.
*/
__asm hal_u32_t read_spr_TBL (void)
{
!  /* no scratch registers used */

   mftb R3

}

/******************************************************************************
NAME:       perfmon_task_ex_init
DESCRIPTION:is called during each function
NOTES:      perfmon_task_ex_init will use the pOSEK GetTaskID function to get
the current POSEK TaskID.  That will be used as an index into the translation
array to assign the task number to that TaskID.  It will also initialize the
associated element in the work array.  This will zero the execution timer and
clear the active flag.

GLOBALS:
*******************************************************************************/
 void perfmon_task_ex_init(uint_least8_t num_of_tasks,
                          uint_least8_t translation_array[],
                          perfmon_task_work_t work_array[],
                          uint_least8_t task_number);

/*******************************************************************************
NAME:       perfmon_task_entry
DESCRIPTION:Called at the begining of the task functions
NOTES:      perfmon_task_entry will convert the current TaskID to the task
            number and use that to address the associated work_array element.
            It will sample the current free-running timer and save that value in
            the entry time, sample the current isr execution timer and save that
            in the isr entry time value, and set the task active flag.
GLOBALS:
*******************************************************************************/

void perfmon_task_entry (uint_least8_t num_of_tasks,
                        uint_least8_t translation_array[],
                        perfmon_task_work_t work_array[]);

/*******************************************************************************
NAME:       perfmon_task_leave
DESCRIPTION:Called at the end of the task functions
NOTES:      perfmon_task_leave will convert the current TaskID to the task
            number and use that to address the associated work_array element.
            It will sample the current free-running timer and the current isr
            execution timer.  It will use those two values to compute the amount
            of execution time incurred since the task was entered, and add that
            to the running execution time.  It will also clear the task active
            flag.
GLOBALS:
*******************************************************************************/

void perfmon_task_leave (uint_least8_t num_of_tasks,
                        uint_least8_t translation_array[],
                        perfmon_task_work_t work_array[]);


/*******************************************************************************
NAME:       perfmon_task_reset_all
DESCRIPTION:
METHOD:
   Inhibits interrupts to suspend task switches and interrupt processing.

   If the current task is active, it records the task start time as the
   current realtime, otherwise the current realtime counter is recorded.

   The current execution timer for each task is captured and recorded as the
   starting point for the current measurement window.  The change from this
   captured value will indicate the execution time accumulated in the window.

   Since there is no task number 0, index 0 of the work array is used to record
   information about the sampling period.

NOTES:

GLOBALS:
*******************************************************************************/
void perfmon_task_reset_all (uint_least8_t num_of_tasks,
      perfmon_task_work_t work_array[],
      uint_least8_t task_number);

/*******************************************************************************
NAME:       perfmon_task_sample_and_reset_all
DESCRIPTION:
METHOD:
   Inhibits interrupts to suspend task switches and interrupt processing.

   If the current task is active, it records the task start time as the
   current realtime, otherwise the current realtime counter is recorded.

   The change in the execution timer for each task is calculated and recorded
   in the output array in entries 1 through num_of_tasks.
   The current execution timer for each task is captured and recorded as the
   starting point for the current measurement window.  The change from this
   captured value will indicate the execution time accumulated in the window.

   The change in the realtime counter is recorded in the output array entry 0.
   The change in the interrupt execution time is recorded in the output array
   in entry num_of_tasks+1 and the change in the number of interrupt completed
   is recorded in the entry num_of_tasks+2.

   Since there is no task number 0, index 0 of the work array is used to record
   information about the sampling period.

NOTES:

GLOBALS:
*******************************************************************************/
bool_least_t perfmon_task_sample_and_reset_all (uint_least8_t num_of_tasks,
      perfmon_task_work_t work_array[],
      uint_least32_t times[],
      uint_least32_t period,
      uint_least8_t task_number);

/*******************************************************************************
NAME:       perfmon_percents
DESCRIPTION:
METHOD:

NOTES:

GLOBALS:
*******************************************************************************/
void perfmon_percents (uint_least8_t num_of_tasks,
      uint_least32_t times[],
      uint_least16_t percents[]);

/*******************************************************************************
NAME:       perfmon_task_time
DESCRIPTION:
METHOD:

NOTES:

GLOBALS:
*******************************************************************************/
uint_least32_t perfmon_task_time (uint_least8_t num_of_tasks,
                                  uint_least8_t translation_array[],
                                  perfmon_task_work_t work_array[]);


#endif                                  /* _PERFMON_H_ */

