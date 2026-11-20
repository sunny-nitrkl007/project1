/******************************************************************************
**
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%
*** %% COPYRIGHT (C) 2001-2003 CATERPILLAR INC. ALL RIGHTS RESERVED.
*** %%     This work contains proprietary information which may
*** %%     constitute a trade secret and/or be confidential.
*** %%     Copyright notice is precautionary only and does not
*** %%     imply publication.
*** %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
**
*** FILE:
***     sss_oel_task_map.c
***
*** DESCRIPTION:
***     Copy of what use to be added to task.c
***        (i.e app_phs\master\test\src_main\task.c)
***
******************************************************************************/

/******************************************************************************
***
*** $Source: $
***
*** $Author: $
***
*** $Locker: $
***
*** $Date: $
***
*** $Revision: $
***
*** $View: $
***
******************************************************************************/

/******************************************************************************
***
***    External function prototypes, data, & symbols
***    -- #Include's --
***
******************************************************************************/
#ifndef __APP_RTOS_CONFIG_H__
#include <app_rtos_config.h>
#endif

#include <std_types.h>

/* headers required for sss */
#include <sss_oel_defs.h>
#include <SssMethodControl.h>
#include <SssPackD.h>
#include <SssSubsys.h>
#include <sss_oel_defs.h>
#include <sss_oel_macros.h>
#include <sss_oel_proto.h>
#include <sss_oel_types.h>
#ifndef __EH_SSS_OEL_H__
#include <eh_sss_oel.h>
#endif
#ifndef __EH_SSS_OEL_DEFS_H__
#include <eh_sss_oel_defs.h>
#endif

/* Define task loop times */
#define EH_SSS_TASK_25X_MS_LOOPTIME 250
#define EH_SSS_TASK_25X_LOOPTIME (0.0250)
#define EH_SSS_TASK_25X_SEC_L20_LOOPTIME ( (1<<20) * EH_SSS_TASK_25X_LOOPTIME )

#define EH_SSS_PERIOD_0250MSEC 250000
/* Define task ID's */
#define EH_SSS_TID_TASK_25X 5
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

/******************************************************************************
***
***    File scope functions defined for this file
***    -- Function Prototypes --
***
******************************************************************************/

/******************************************************************************
***
***    File scope symbols defined for this file
***    -- Symbols --
***
******************************************************************************/

/******************************************************************************
***
***    Global data symbols defined in this file
***    -- Global Symbols --
***
******************************************************************************/

/* map the pOSEK tasks to the SSS mechanism */
static sss_oel_task_map_t task_map[] =
{
  {
    EH_SSS_TID_TASK_2X,
    &task_0020ms_id,
    EH_SSS_PERIOD_0020MSEC

  },
   {
    EH_SSS_TID_TASK_25X,
    &task_0250ms_id,
    EH_SSS_PERIOD_0250MSEC
}
 
};

sss_oel_task_list_config_t task_list_config =
{
  task_map,
  sizeof(task_map)/sizeof(sss_oel_task_map_t)
};

/*********************************************************************************/
/* Declare package configuration list object. */
const sss_package_list_config_t  package_list_config =
{
     0, /*List Of Packages To Add  */
     0  /*Number Of Packages To Add*/
};

/*********************************************************************************/
