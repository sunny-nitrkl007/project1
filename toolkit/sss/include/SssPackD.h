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
***   Definitions of the SssPackD Object and its associated Operations
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
#ifndef SSSPACKD_H_
#define SSSPACKD_H_

#ifndef STD_TYPES_H_
#include <std_types.h>
#endif
#ifndef SSSMETHODCONTROL_H_
#include <SssMethodControl.h>
#endif


/* ---------------------BEGIN SssPackD Object---------------------------------------*/

typedef struct
{
	void            *work;
	const void      *config;

	struct					/* (1...*) SssMethodControls */
	{
		unsigned_8		count;	/* Number of SssMethodControl Elements */
		SssMethodControl_t *	elem;	/* Pointer to an Array of SssMethodControls */
	}
	method;		
}	
SssPackD_t;      
  
/* -------------------------------------END SssPackD Object----------------------------------------*/


/* ---------------------------------BEGIN SssPackD Operations----------------------------------------*/

/* BEGIN OPERATION DEF: SssPackD_init() **********************/
/* Operation Prototype: */
void
	SssPackD_init(	const 	SssPackD_t * 		me);		/* This object */
				

/* Operation Macro: */
#define SssPackD_INIT(me,unused) (SssPackD_init(me))

/* END OPERATION DEF: SssPackD_init() ***********************/




/* -----------------------------------END SssPackD Operations----------------------------------------*/					


#endif /* SSSPACKD_H_ */
