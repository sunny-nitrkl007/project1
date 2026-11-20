/******************************************************************************************************************
 Copyright 2016 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: task_set_01_globals.c

Description: File to interface for sss task 
******************************************************************************************************************/

/******************************************************************************************************************
-- #Include's --
******************************************************************************************************************/
#include <sss_oel_defs.h>
#include <sss_oel_types.h>
#include "task_id_globals.h"
#include "app_rtos_config.h"

#if defined(A6P1)
#include <oel_os_cfg_csns_test.h>
#include <oel_rtos.h>
#include <oel_rtos_ar.h>
#include "app_ar_a6p1_task_config.h"
#endif


/******************************************************************************************************************
** -- Data Definitions --
******************************************************************************************************************/
#if defined(A6P1)

sss_oel_task_map_t task_set_01_map[] =
{
  {
    SSS_TID_1005MSEC,
    &task_0008ms_id,
    SSS_PERIOD_U32_L20_1005MSEC
  },
    {
    SSS_TID_0120MSEC,
    &task_0016ms_id,
    SSS_PERIOD_U32_L20_0120MSEC
  },
    {
    SSS_TID_0030MSEC,
    &task_0080ms_id,
    SSS_PERIOD_U32_L20_0030MSEC
  }, 
  
};

#else

sss_oel_task_map_t task_set_01_map[] =
{
   {
      SSS_TID_1005MSEC,
      &task_1005ms_id,
      SSS_PERIOD_U32_L20_1005MSEC
   },
   {
      SSS_TID_0120MSEC,
      &task_0120ms_id,
      SSS_PERIOD_U32_L20_0120MSEC
   },
   {
      SSS_TID_0030MSEC,
      &task_0030ms_id,
      SSS_PERIOD_U32_L20_0030MSEC
   }, 
  
};

#endif

sss_oel_task_list_config_t task_set_01_config =
{
   task_set_01_map,
   sizeof(task_set_01_map)/sizeof(sss_oel_task_map_t)
};
