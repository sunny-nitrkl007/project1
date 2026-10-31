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
***   Definitions of the SssTaskCtrlBlock Object and its associated Operations
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
#ifndef SSSTASKCTRLBLOCK_H_
#define SSSTASKCTRLBLOCK_H_

#ifndef STD_TYPES_H_
#include <std_types.h>
#endif
#ifndef SSS_PROTO_H_
#include <sss_proto.h>
#endif


/* -------------------------------------BEGIN SssTaskCtrlBlock Object----------------------------------------*/


typedef sss_tcb_t SssTaskCtrlBlock_t;      
  
/* -------------------------------------END SssTaskCtrlBlock Object----------------------------------------*/


/* ---------------------------------BEGIN SssTaskCtrlBlock Operations----------------------------------------*/

/* BEGIN OPERATION DEF: SssTaskCtrlBlock_get_task_exec_period() **********************/
/* Operation Prototype: */
beu_usec_u32_t
SssTaskCtrlBlock_get_task_exec_period(SssTaskCtrlBlock_t * 	me);		
				

/* Operation Macro: */
#define SssTaskCtrlBlock_GET_TASK_EXEC_PERIOD(me) \
		((beu_usec_u32_t)(((SssTaskCtrlBlock_t *)me)->period_actual))

/* END OPERATION DEF: SssTaskCtrlBlock_get_task_exec_period() ***********************/




/* -----------------------------------END SssTaskCtrlBlock Operations----------------------------------------*/					


#endif /* SSSTASKCTRLBLOCK_H_ */
