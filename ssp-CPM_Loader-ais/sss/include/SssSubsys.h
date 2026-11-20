#ifndef SSSSUBSYS_H_
#define SSSSUBSYS_H_
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
***   Definitions of the SssSubsys Object and its associated Operations
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
#ifndef STD_TYPES_H_
#include <std_types.h>
#endif
#ifndef SSS_TYPES_H_
#include <sss_types.h>
#endif


typedef struct
{
  void                           *config;
  sss_subsys_control_elem_type_t elem_type;
}
SssSubsysControl_t;      

typedef struct
{
  struct
  {
    unsigned_8           count; /* Number of Elements */
    SssSubsysControl_t  *elem;  /* Pointer to an Array of
                                   pointers to controls */
  } 
  control;      
}   
SssSubsys_t;      
  
/* BEGIN OPERATION DEF: SssSubsys_init() **********************/
/* Operation Prototype: */
void
SssSubsys_init(const SssSubsys_t *me);      /* This object */
            

#endif /* SSSSUBSYS_H_ */
