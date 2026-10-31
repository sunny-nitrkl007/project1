/******************************************************************************
***
***  app_sss_public.h
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                       %%
*** %% COPYRIGHT (C) 2001 - 2011 CATERPILLAR INC. ALL RIGHTS RESERVED.       %%
*** %%                                                                       %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
***  DESCRIPTION:
***     This is the include file for the application subsystem services.
***
******************************************************************************/

#ifndef __APP_SSS_PUBLIC_H__
#define __APP_SSS_PUBLIC_H__


/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#ifndef __SSSMETHODCONTROL_H__
#include <SssMethodControl.h>
#endif

#ifndef __SSSPACKD_H__
#include <SssPackD.h>
#endif

#if (defined A4M1V2)
#include <sss_oel_posek_proto.h>
#else
/*do nothing*/
#endif

#ifndef __SSS_OEL_DEFS_H__
#include <sss_oel_defs.h>
#endif

#ifndef __SSS_OEL_MACROS_H__
#include <sss_oel_macros.h>
#endif

#ifndef __SSS_OEL_PROTO_H__
#include <sss_oel_proto.h>
#endif

#ifndef __SSS_OEL_TYPES_H__
#include <sss_oel_types.h>
#endif

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

/*******************************************************************************
** -- Symbols --
*******************************************************************************/

#endif /*__APP_SSS_PUBLIC_H__ */
