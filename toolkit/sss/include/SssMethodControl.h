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
***   Definitions of the SssMethodControl Object and its associated Operations
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
#ifndef SSSMETHODCONTROL_H_
#define SSSMETHODCONTROL_H_

#ifndef STD_TYPES_H_
#include <std_types.h>
#endif
#ifndef SSS_PACKD_TYPES_H_
#include <sss_packd_types.h>
#endif


/* -------------------------------------BEGIN SssMethodControl Object----------------------------------------*/

typedef struct
{
	sss_task_id_t		task_id;	/* Identifies in which task the exe will execute */
	sss_packd_method_t	exe;		/* The executable PackD method */
}	
SssMethodControl_t;      
  
/* -------------------------------------END SssMethodControl Object----------------------------------------*/


/* ---------------------------------BEGIN SssMethodControl Operations----------------------------------------*/

/* BEGIN OPERATION DEF: **********************/
/* Operation Prototype: */

/* Operation Macro: */

/* END OPERATION DEF: ***********************/



/* -----------------------------------END SssMethodControl Operations----------------------------------------*/					


#endif /* SSSMETHODCONTROL_H_ */
