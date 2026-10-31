/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 2000-2001 CATERPILLAR INC.   ALL RIGHTS RESERVED.       %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
*** DESCRIPTION :
***   Data structure typedefs for the Subsystem PackD module and its related objects.
***
*** LANGUAGE :                  
***    ANSI C
***
*** NOTES:
***
*** MACRO LIST:
***
*** HISTORY:
***
*******************************************************************************/
#ifndef SSS_PACKD_TYPES_H_
#define SSS_PACKD_TYPES_H_

#ifndef STD_TYPES_H_
#include <std_types.h>
#endif
#ifndef SSS_TYPES_H_
#include <sss_types.h>
#endif


/* -------------BEGIN sss_packd_method_t---------------*/

typedef void (*sss_packd_method_t)(const void * me, void * unused);	
/* Holds a pointer to a container method */

/* -------------BEGIN sss_packd_method_t---------------*/

#endif /* SSS_PACKD_TYPES_H_ */
