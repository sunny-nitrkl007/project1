/*******************************************************************************
** COPYRIGHT (C) 2000 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillars proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME: sss_oel_macros.h
DESCRIPTION: SSS subsystem macros.
*******************************************************************************/
#ifndef SSS_OEL_MACROS_H_
#define SSS_OEL_MACROS_H_
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <oel_types.h>
/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

/* Division macro which returns N / D with rounding.
   --------------------------------------------------------------------------- */      
#define DIVIDE(      /* returns N / D with rounding */  \
  N,            /* numerator */                         \
  D)            /* denominator */                       \
(((N) + (D)/2) / (D))

/* Conversion macro which takes seconds in scale of 2^20 bits/sec and converts
   to number of tick periods.
   --------------------------------------------------------------------------- */
#define SEC_U32_L20_TO_RTOS_TICKS(             \
   TIME,                  /* oel_second_u32_l20_t */    \
   RTOS_TICK_PERIOD)      /* oel_second_u32_l20_t */    \
   (DIVIDE(TIME, RTOS_TICK_PERIOD))

/* Conversion macros which take microseconds and converts to a scale of 
   2^20 bits/sec.
   --------------------------------------------------------------------------- */
#define OEL_RTOS_US_PER_S            1000000
#define OEL_RTOS_US_TO_SEC_U32_L20(US)   /* us */  \
((oel_second_u32_l20_t)DIVIDE( ((uint_least64_t)(US)) << 20, OEL_RTOS_US_PER_S))

/* Task Watchdog snooze time
   --------------------------------------------------------------------------- */ 
#define APP_WDOG_SNOOZE_TIME OEL_RTOS_SECONDS_DBL_TO_U32_L20(1.0)

/* Empty subsystem used only when compile time flags create a subsystem with
   nothing defined.
   --------------------------------------------------------------------------- */
#define SSS_OEL_EMPTY_SUBSYSTEM (void*)0,0

/* Cast to a function pointer whose arguments are 2 void * and return type of
   void, which is of the correct type for subsystem services.
   --------------------------------------------------------------------------- */
#define SSS_OEL_CAST_PACKAGE_METHOD( method ) \
(void (*)(void *, const void *))(method)

/* Conversion to POSEK system counter ticks.
   --------------------------------------------------------------------------- */
#define SSS_OEL_POSEK_SEC_U32_L20_TO_SYS_TICKS( time_sec_u32_l20, \
						tick_period_sec_u32_l20 ) \
((((time_sec_u32_l20 << 1)/(tick_period_sec_u32_l20))+1)>>1)

/* Process methods macro.
   --------------------------------------------------------------------------- */
#define SSS_OEL_PROC_METHODS( method_item, method_item_init ) \
  for( (method_item) = (method_item_init);			\
       (method_item);						\
       (method_item) = (method_item)->next ) {			\
    								\
    (method_item)->method(					\
			  (method_item)->work,			\
			  (method_item)->config			\
			  );					\
  } /* end for( (method_item) = (method_item_init);...) */

#define SSS_GET_TASK_RATE_SEC(task_symbol)       \
(/*if*/( task_symbol == SSS_TID_0015MSEC ) ?     \
  (double)SSS_PERIOD_U32_L20_0015MSEC/(1<<20) :  \
/* else if*/( task_symbol == SSS_TID_0030MSEC ) ?\
  (double)SSS_PERIOD_U32_L20_0030MSEC/(1<<20) :  \
/* else if*/( task_symbol == SSS_TID_0060MSEC ) ?\
  (double)SSS_PERIOD_U32_L20_0060MSEC/(1<<20) :  \
/* else if*/( task_symbol == SSS_TID_0120MSEC ) ?\
  (double)SSS_PERIOD_U32_L20_0120MSEC/(1<<20) :  \
/* else if*/( task_symbol == SSS_TID_0240MSEC ) ?\
  (double)SSS_PERIOD_U32_L20_0240MSEC/(1<<20) :  \
/* else if*/( task_symbol == SSS_TID_0495MSEC ) ?\
  (double)SSS_PERIOD_U32_L20_0495MSEC/(1<<20) :  \
/* else if*/( task_symbol == SSS_TID_1005MSEC ) ?\
  (double)SSS_PERIOD_U32_L20_1005MSEC/(1<<20) :  \
/* else if*/( task_symbol == SSS_TID_1995MSEC ) ?\
  (double)SSS_PERIOD_U32_L20_1995MSEC/(1<<20) :  \
/*else*/ 0)

#endif /* SSS_OEL_MACROS_H_ */
