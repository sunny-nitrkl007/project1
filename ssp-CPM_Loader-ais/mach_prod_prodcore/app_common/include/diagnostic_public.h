/******************************************************************************
*******************************************************************************
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%
*** %% COPYRIGHT (C) 2001-2012 CATERPILLAR INC. ALL RIGHTS RESERVED.
*** %%     This work contains proprietary information which may constitute
*** %%     a trade secret and/or be confidential.  Copyright notice is
*** %%     precautionary only and does not imply publication.
*** %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
***
***  diagnostic_public.h
***
***  DESCRIPTION:
***     This is the definition include file for the diagnostic module.
***     All of the contents in this file are intended for other tasks/modules
***     to use.
***
***     IMPORTANT NOTE:  All global variables should be considered read-only
***                      by any external module that accesses them.
***                      It is forbidden for any routines besides those
***                      local to this module to alter these variables.
***
*******************************************************************************
******************************************************************************/

#ifndef DIAGNOSTIC_PUBLIC_H_
#define DIAGNOSTIC_PUBLIC_H_


/*******************************************************************************
** -- #Include's --
*******************************************************************************/

#ifndef DIAGNOSTIC_PRIVATE_H_
#include <diagnostic_private.h>
#endif

#ifndef DIAGNOSTICLIB_PUBLIC_H_
#include <diagnosticlib_public.h>
#endif

#ifndef __SCL_VI2_DISCRETE_G_H__
#include <scl_vi2_discrete_g.h>
#endif

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

/*Diagnostic Module Loop Time In Seconds*/
#define DIAGNOSTIC_LPTIM (0.040)

#define DIAGNOSTIC_ACTIVE(CONFIG,ACTIVE_STATUS) (scl_status_t ) (            \
   (diagnostic_retrieve_cur_status(CONFIG.id, CONFIG.modifier, NULL)==0x01)? \
   (ACTIVE_STATUS) : 0)
   

/*
**  --- Public Global Variables ---
*/

/* The following are declared public only so that they can be passed to
//     diagnostic_init in app_pre_irq_init.
*/

extern unsigned_8 diagnostic_module_storage[];
extern unsigned_32 diagnostic_module_storage_size;

/* These only need to be defined if you are not letting info lib initialize
//     and write to the non-volatile memory.
*/
extern unsigned_8 diagnostic_module_cache[];
extern unsigned_32 diagnostic_module_cache_size;   

#endif /* DIAGNOSTIC_PUBLIC_H_ */
