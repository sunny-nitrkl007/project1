/******************************************************************************************************************
 Copyright 2011 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: oel_u_sllist.h

Description:  This file contains the public interfaces for the single-linked list -- unordered class. This class
   is NOT capable of handling interactions between interrupt-level code and task-level code.
******************************************************************************************************************/
#ifndef OEL_U_SLLIST_H_
#define OEL_U_SLLIST_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <oel_oop.h>
#include <oel_u_sllelmnt.h>

/* Disallowed definition for macro */
/* [MISRA 2004 Rule 19.4] */ /*lint -save -esym(960,19.4) */
/* Function-like macro defined */
/* [MISRA 2004 Rule 19.7] */ /*lint -save -esym(961,19.7) */

/* This class models a single-linked list.  It is capable of handling any number of list elements
   (subject to memory availability).  This class uses 6 bytes of RAM. */
typedef struct
{
   /* This attribute maintains a count of the number of elements that exist in the list. */
   uint_least16_t count;
   /* This attribute indicates the first indexed element in the list.  This attribute should be UINT_LEAST16_MAX
      if there are no elements in the list. */
   uint_least16_t head_index;
   /* This attribute indicates the last indexed element in the list.  This attribute should be UINT_LEAST16_MAX
      if there are no elements in the list. */
   uint_least16_t tail_index;
} oel_u_sllist_t;

/******************************************************************************************************************
Macro name: OEL_U_SLLIST_DEFINE

Description:  This macro initializes members of the list structure.  It may only be used to initialize a list
   variable as it is being defined, e.g., oel_u_sllist_t sllist = OEL_U_SLLIST_DEFINE();
******************************************************************************************************************/
#define OEL_U_SLLIST_DEFINE() { 0U, UINT_LEAST16_MAX, UINT_LEAST16_MAX }

/******************************************************************************************************************
Macro name: OEL_U_SLLIST_INIT

Description:  This operation initializes members of the single linked list structure to default values.  It may
   only be used to initialize a list variable that is already defined.

Parameter Description:
   volatile oel_u_sllist_t * sllist -  This parameter is a pointer to a single-linked list.  
******************************************************************************************************************/
#define OEL_U_SLLIST_INIT( sllist )                                                                               \
{                                                                                                                 \
   (sllist)->count = 0U;                                                                                           \
   (sllist)->head_index = UINT_LEAST16_MAX;                                                                       \
   (sllist)->tail_index = UINT_LEAST16_MAX;                                                                       \
}


/******************************************************************************************************************
Function name: OEL_U_SLLIST_ADD_ELMNT

Description:  This macro was created to reduce the overhead involved in a function call. This macro
   takes the given indexed element and inserts it at the end of the list.  Please note that this macro is
   sequential only, and does not provide for exclusive synchronized access.

Parameter Description:
   volatile oel_u_sllist_t * sllist -  This parameter is a pointer to a single-linked list.
   array                            -  This parameter is a global array pool of elements.
   uint_least16_t index             -  index of the element to be added to the list

******************************************************************************************************************/
#define OEL_U_SLLIST_ADD_ELMNT( sllist, array, index )                                                            \
{                                                                                                                 \
   (OEL_BASE( &(array)[(index)] ))->next_index = UINT_LEAST16_MAX;                                                \
                                                                                                                  \
   if( (sllist)->count == 0U )                                                                                     \
   {                                                                                                              \
      (sllist)->head_index = (index);                                                                             \
   }                                                                                                              \
   else                                                                                                           \
   {                                                                                                              \
      (OEL_BASE( &(array)[(sllist)->tail_index] ))->next_index = (index);                                         \
   }                                                                                                              \
                                                                                                                  \
   (sllist)->tail_index = (index);                                                                                \
                                                                                                                  \
   (sllist)->count++;                                                                                             \
}

/******************************************************************************************************************
Macro name: OEL_U_SLLIST_GET_HEAD

Description:  This macro returns the head element pointer of the sllist.

Parameter Description:
   volatile oel_u_sllist_t * sllist -  This parameter is a pointer to a single-linked list.
   array                            -  This parameter is a global array pool of elements.

******************************************************************************************************************/
#define OEL_U_SLLIST_GET_HEAD(sllist)    (sllist).head_index


/******************************************************************************************************************
Macro name: OEL_U_SLLIST_GET_NEXT_ELMNT

Description:  This macro returns the next element in the list. If hit the tail of the list returns NULL

Parameter Description:
   uint_least16_t sllist_elmnt_index -  This parameter is a index to a single-linked list element.
   array                             -  This parameter is a global array pool of elements.

******************************************************************************************************************/
#define OEL_U_SLLIST_GET_NEXT_ELMNT(sllist_elmnt_index,array)       OEL_BASE(&(array)[(sllist_elmnt_index)])->next_index

/* Restore the MISRA rules */
/*lint -restore +esym(960,19.4) */
/*lint -restore +esym(961,19.7) */

#ifdef __cplusplus
}
#endif
#endif /* #ifndef OEL_U_SLLIST_H_ */
