/******************************************************************************************************************
 Copyright 2012 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: oel_u_dl_list.h

Description:  This file contains the public interfaces for the single-linked list -- unordered class. This class
   is NOT capable of handling interactions between interrupt-level code and task-level code.
******************************************************************************************************************/
#ifndef OEL_U_DL_LIST_H_
#define OEL_U_DL_LIST_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <oel_rtos.h>
#include <oel_oop.h>
#include "oel_u_dl_element.h"
#include "oel_assert.h"

/* Disallowed definition for macro */
/* [MISRA 2004 Rule 19.4] */ /*lint -save -esym(960,19.4) */
/* Function-like macro defined */
/* [MISRA 2004 Rule 19.7] */ /*lint -save -esym(961,19.7) */

#if (defined(WIN32) || defined (WINCE) || defined (__linux)) && !defined(__MINGW64__)

/* This is the main resource used by oel_u_dl_list to guarantee synchronization
   between tasks. */
extern oel_rtos_resource_t *oel_u_dl_list_resource;

#define OEL_U_DL_LIST_ENTER_CRITICAL_SECTION()         \
0;                                                     \
{                                                      \
   if(!oel_u_init_flag)                                \
   {                                                   \
      oel_assert(oel_u_init_flag);                     \
   }                                                   \
   else                                                \
   {                                                   \
      oel_rtos_resource_lock(oel_u_dl_list_resource);  \
   }                                                   \
}
#define OEL_U_DL_LIST_LEAVE_CRITICAL_SECTION(status)   \
{                                                      \
   (void) status;                                      \
   oel_rtos_resource_unlock(oel_u_dl_list_resource);   \
}

#else

#define OEL_U_DL_LIST_ENTER_CRITICAL_SECTION() OEL_RTOS_DISABLE_INTERRUPTS()
#define OEL_U_DL_LIST_LEAVE_CRITICAL_SECTION(status) OEL_RTOS_RESTORE_INTERRUPTS(status)

#endif

#if (defined (WIN32) || defined (WINCE)) && !defined(__MINGW64__)

   /*  dl_list resource CS configuration  */

#define OEL_U_DL_LIST_RESOURCE_INIT()                                                                     \
{                                                                                                         \
   static const oel_rtos_resource_cs_vconfig_t dl_list_resource_vconfig = OEL_RTOS_RESOURCE_CS_VCONFIG(); \
   const oel_rtos_resource_config_t *dl_list_resource_config = OEL_BASE(&dl_list_resource_vconfig);       \
   oel_u_dl_list_resource = oel_rtos_resource_new(dl_list_resource_config);                               \
}

#elif defined(__linux)

   /*  dl_list resource PI configuration  */

#define OEL_U_DL_LIST_RESOURCE_INIT()                                                                     \
{                                                                                                         \
   static const oel_rtos_resource_pi_vconfig_t dl_list_resource_vconfig = OEL_RTOS_RESOURCE_PI_VCONFIG(); \
   const oel_rtos_resource_config_t *dl_list_resource_config = OEL_BASE(&dl_list_resource_vconfig);       \
   oel_u_dl_list_resource = oel_rtos_resource_new(dl_list_resource_config);                               \
}

#else

#define OEL_U_DL_LIST_RESOURCE_INIT()  

#endif

/* This class models a double-linked list.  It is capable of handling any number of list elements
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
} oel_u_dl_list_t;

/******************************************************************************************************************
Macro name: OEL_U_DL_LIST_DEFINE

Description:  This macro initializes members of the list structure.  It may only be used to initialize a list
   variable as it is being defined, e.g., oel_u_dl_list_t dllist = OEL_U_DL_LIST_DEFINE();
******************************************************************************************************************/
#define OEL_U_DL_LIST_DEFINE() { 0U, UINT_LEAST16_MAX, UINT_LEAST16_MAX, UINT_LEAST16_MAX }

/******************************************************************************************************************
Macro name: OEL_U_DL_LIST_INIT

Description:  This operation initializes members of the double linked list structure to default values.  It may
   only be used to initialize a list variable that is already defined.

Parameter Description:
   volatile oel_u_dl_list_t * dllist -  This parameter is a pointer to a double-linked list.  
******************************************************************************************************************/
#define OEL_U_DL_LIST_INIT( dllist )                                                                              \
{                                                                                                                 \
   (dllist)->count = 0U;                                                                                          \
   (dllist)->head_index = UINT_LEAST16_MAX;                                                                       \
   (dllist)->tail_index = UINT_LEAST16_MAX;                                                                       \
}

/******************************************************************************************************************
Macro name: OEL_U_DL_LIST_ADD_ELEMENT

Description:  This macro was created to reduce the overhead involved in a function call. This macro
   takes the given indexed element and inserts it at the end of the list.  

Parameter Description:
   volatile oel_u_dl_list_t * dllist -  This parameter is a pointer to a double-linked list.
   array                            -  This parameter is a global array pool of elements.
   uint_least16_t index             -  index of the element to be added to the list
******************************************************************************************************************/
#define OEL_U_DL_LIST_ADD_ELEMENT( dllist, array, index )                                                         \
{                                                                                                                 \
   uint_least16_t dl_index;                                                                                       \
                                                                                                                  \
   oel_rtos_interrupt_status_t oel_dl_add_interrupt_status;                                                       \
   oel_dl_add_interrupt_status = OEL_U_DL_LIST_ENTER_CRITICAL_SECTION();                                          \
                                                                                                                  \
   for( dl_index = (dllist)->head_index; dl_index != UINT_LEAST16_MAX;                                            \
         dl_index = (OEL_BASE( &(array)[dl_index] ))->next_index)                                                 \
   {                                                                                                              \
      if(dl_index == (index))                                                                                       \
      {                                                                                                           \
         break;                                                                                                   \
      }                                                                                                           \
   }                                                                                                              \
                                                                                                                  \
   if( (dl_index == UINT_LEAST16_MAX) && ((index) != UINT_LEAST16_MAX) )                                                \
   {                                                                                                              \
      (OEL_BASE( &(array)[(index)] ))->next_index = UINT_LEAST16_MAX;                                             \
      (OEL_BASE( &(array)[(index)] ))->prev_index = UINT_LEAST16_MAX;                                             \
                                                                                                                  \
      if( (dllist)->count == 0U )                                                                                 \
      {                                                                                                           \
         (dllist)->head_index = (index);                                                                          \
      }                                                                                                           \
      else                                                                                                        \
      {                                                                                                           \
         (OEL_BASE( &(array)[(index)] ))->prev_index = (dllist)->tail_index;                                      \
         (OEL_BASE( &(array)[(dllist)->tail_index] ))->next_index = (index);                                      \
      }                                                                                                           \
                                                                                                                  \
      (dllist)->tail_index = (index);                                                                             \
      (dllist)->count++;                                                                                          \
                                                                                                                  \
   }                                                                                                              \
   OEL_U_DL_LIST_LEAVE_CRITICAL_SECTION( oel_dl_add_interrupt_status );                                           \
}

/******************************************************************************************************************
Macro name: OEL_U_DL_LIST_REMOVE_ELEMENT

Description:  This macro was created to reduce the overhead involved in a function call. This macro
   takes the given indexed element and removes it from the list.  

Parameter Description:
   volatile oel_u_dl_list_t * dllist -  This parameter is a pointer to a double-linked list.
   array                            -  This parameter is a global array pool of elements.
   uint_least16_t index             -  index of the element to be removed from the list.
                                       if the index element cannot be removed or not exists then index will be 
                                       updated as   UINT_LEAST16_MAX
******************************************************************************************************************/   
#define OEL_U_DL_LIST_REMOVE_ELEMENT( dllist, array, index )                                                      \
{                                                                                                                 \
   uint_least16_t dl_index;                                                                                       \
   oel_rtos_interrupt_status_t oel_dl_rmv_interrupt_status;                                                       \
   oel_dl_rmv_interrupt_status = OEL_U_DL_LIST_ENTER_CRITICAL_SECTION();                                          \
                                                                                                                  \
   if ((dllist)->count !=0U )                                                                                     \
   {                                                                                                              \
      for( dl_index = (dllist)->head_index; dl_index != UINT_LEAST16_MAX;                                         \
                                        dl_index = (OEL_BASE( &(array)[dl_index] ))->next_index)                  \
      {                                                                                                           \
         if(dl_index == (index))                                                                                    \
         {                                                                                                        \
            break;                                                                                                \
         }                                                                                                        \
      }                                                                                                           \
      if(dl_index != (index))                                                                                       \
      {                                                                                                           \
         (index) = UINT_LEAST16_MAX;                                                                                \
      }                                                                                                           \
      if( (dl_index != UINT_LEAST16_MAX) && ((index) != UINT_LEAST16_MAX) )                                       \
      {                                                                                                           \
         if ((dllist)->count == 1U)                                                                               \
         {                                                                                                        \
            (dllist)->head_index = UINT_LEAST16_MAX;                                                              \
            (dllist)->tail_index = UINT_LEAST16_MAX;                                                              \
         }                                                                                                        \
         else if ((OEL_BASE( &(array)[(index)] ))->next_index == UINT_LEAST16_MAX)                                \
         {                                                                                                        \
            (dllist)->tail_index = (OEL_BASE( &(array)[(dllist)->tail_index] ))->prev_index;                      \
            (OEL_BASE( &(array)[(dllist)->tail_index] ))->next_index = UINT_LEAST16_MAX;                          \
         }                                                                                                        \
         else if ((OEL_BASE( &(array)[(index)] ))->prev_index == UINT_LEAST16_MAX)                                \
         {                                                                                                        \
            (dllist)->head_index = (OEL_BASE( &(array)[(dllist)->head_index] ))->next_index;                      \
            (OEL_BASE( &(array)[(dllist)->head_index] ))->prev_index = UINT_LEAST16_MAX;                          \
         }                                                                                                        \
         else                                                                                                     \
         {                                                                                                        \
            (OEL_BASE( &(array)[(OEL_BASE( &(array)[(index)] ))->prev_index] ))->next_index =                     \
                                                                (OEL_BASE( &(array)[(index)] ))->next_index;      \
            (OEL_BASE( &(array)[(OEL_BASE( &(array)[(index)] ))->next_index] ))->prev_index =                     \
                                                                (OEL_BASE( &(array)[(index)] ))->prev_index;      \
         }                                                                                                        \
         (dllist)->count--;                                                                                       \
         (OEL_BASE( &(array)[(index)] ))->next_index = UINT_LEAST16_MAX;                                          \
         (OEL_BASE( &(array)[(index)] ))->prev_index = UINT_LEAST16_MAX;                                          \
      }                                                                                                           \
   }                                                                                                              \
   else                                                                                                           \
   {                                                                                                              \
      (index) = UINT_LEAST16_MAX;                                                                                   \
   }                                                                                                              \
                                                                                                                  \
   OEL_U_DL_LIST_LEAVE_CRITICAL_SECTION( oel_dl_rmv_interrupt_status );                                           \
}

/******************************************************************************************************************
Macro name: OEL_U_DL_LIST_RESET_SCAN

Description:  This macro was created to reduce the overhead involved in a function call. This macro
   resets the value of scan_index (initializes it to the head_index).  

Parameter Description:
   volatile oel_u_dl_list_t * dllist -  This parameter is a pointer to a double-linked list.
******************************************************************************************************************/   
#define OEL_U_DL_LIST_RESET_SCAN(dllist, get_head_index)                                                          \
{                                                                                                                 \
   oel_rtos_interrupt_status_t oel_dl_rst_interrupt_status;                                                       \
   oel_dl_rst_interrupt_status = OEL_U_DL_LIST_ENTER_CRITICAL_SECTION();                                          \
   (get_head_index) = (dllist)->head_index;                                                                         \
   OEL_U_DL_LIST_LEAVE_CRITICAL_SECTION( oel_dl_rst_interrupt_status );                                           \
}

/******************************************************************************************************************
Macro name: OEL_U_DL_LIST_SCAN_ELEMENT

Description:  This macro was created to reduce the overhead involved in a function call. This macro
   is used to get the value of the scan_index. 

Parameter Description:
   volatile oel_u_dl_list_t * dllist -  This parameter is a pointer to a double-linked list.
   uint_least16_t current_index, next_index         -  The index to be scanned(scan_index)
******************************************************************************************************************/    
#define OEL_U_DL_LIST_SCAN_ELEMENT(dllist, array, current_index, get_next_index)                                  \
{                                                                                                                 \
   oel_rtos_interrupt_status_t oel_dl_scn_el_interrupt_status;                                                    \
   oel_dl_scn_el_interrupt_status = OEL_U_DL_LIST_ENTER_CRITICAL_SECTION();                                       \
                                                                                                                  \
   if((current_index) != UINT_LEAST16_MAX )                                                                         \
   {                                                                                                              \
     (get_next_index) = (OEL_BASE( &(array)[(current_index)] ))->next_index;                                          \
   }                                                                                                              \
   OEL_U_DL_LIST_LEAVE_CRITICAL_SECTION( oel_dl_scn_el_interrupt_status );                                        \
}

/******************************************************************************************************************
Macro name: OEL_U_DL_LIST_COUNT_ELEMENT

Description:  This macro was created to reduce the overhead involved in a function call. This macro
   is used to find the number of elements in the list(count).  

Parameter Description:
   volatile oel_u_dl_list_t * dllist -  This parameter is a pointer to a double-linked list.
   uint_least16_t list_count         -  The number of elements in the list(count) 
******************************************************************************************************************/  
#define OEL_U_DL_LIST_COUNT_ELEMENT(dllist, list_count)                                                           \
{                                                                                                                 \
   oel_rtos_interrupt_status_t oel_dl_c_interrupt_status;                                                         \
   oel_dl_c_interrupt_status = OEL_U_DL_LIST_ENTER_CRITICAL_SECTION();                                            \
                                                                                                                  \
   (list_count) = (dllist)->count;                                                                                  \
                                                                                                                  \
   OEL_U_DL_LIST_LEAVE_CRITICAL_SECTION( oel_dl_c_interrupt_status );                                             \
}
 
 
/******************************************************************************************************************
Macro name: OEL_U_DL_LIST_GET_HEAD

Description:  This macro was created to get the head index of the double link list 

Parameter Description:
   volatile oel_u_dl_list_t * dllist -  This parameter is a pointer to a double-linked list.
   uint_least16_t get_index         -  The head index of the list. 
******************************************************************************************************************/  
#define OEL_U_DL_LIST_GET_HEAD(dllist, get_index)                                                                 \
{                                                                                                                 \
   oel_rtos_interrupt_status_t oel_dl_head_interrupt_status;                                                      \
   oel_dl_head_interrupt_status = OEL_U_DL_LIST_ENTER_CRITICAL_SECTION();                                         \
                                                                                                                  \
   (get_index) = (dllist)->head_index;                                                                              \
                                                                                                                  \
   OEL_U_DL_LIST_LEAVE_CRITICAL_SECTION( oel_dl_head_interrupt_status );                                          \
}

/******************************************************************************************************************
Macro name: OEL_U_DL_LIST_GET_NEXT

Description:  This macro was created to get the next index of the given double link list 

Parameter Description:
   volatile array * dllist -  This parameter is the array.
   uint_least16_t next_elmt_index -  The next index of the list. 
******************************************************************************************************************/  
#define OEL_U_DL_LIST_GET_NEXT(array, next_elmt_index)                                                            \
{                                                                                                                 \
   oel_rtos_interrupt_status_t oel_dl_nxt_interrupt_status;                                                       \
   oel_dl_nxt_interrupt_status = OEL_U_DL_LIST_ENTER_CRITICAL_SECTION();                                         \
                                                                                                                  \
   (next_elmt_index) = (OEL_BASE(&(array)))->next_index;                                                              \
                                                                                                                  \
   OEL_U_DL_LIST_LEAVE_CRITICAL_SECTION( oel_dl_nxt_interrupt_status );                                           \
}
/* Restore the MISRA rules */
/*lint -restore +esym(960,19.4) */
/*lint -restore +esym(961,19.7) */

#ifdef __cplusplus
}
#endif
#endif /* #ifndef OEL_U_DL_LIST_H_ */
