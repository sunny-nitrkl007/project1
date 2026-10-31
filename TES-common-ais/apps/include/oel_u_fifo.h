/******************************************************************************************************************
 Copyright 2009-2014 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: oel_u_fifo.h

Description: Public interface for oel_u_fifo which is a standard FIFO array class.
******************************************************************************************************************/

#ifndef OEL_U_FIFO_H
#define OEL_U_FIFO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <std_t.h>
#include "oel_u.h"
#include "oel_assert.h"
/* Disallowed definition for macro */
/* [MISRA 2004 Rule 19.4] */ /*lint -save -esym(960,19.4) */
/* Function-like macro defined */
/* [MISRA 2004 Rule 19.7] */ /*lint -save -esym(961,19.7) */

#if defined (__ghs__)

#include <INTEGRITY.h>

extern LocalMutex oel_u_fifo_ghs_local_mutex;

#define OEL_U_FIFO_ENTER_CRITICAL_SECTION() WaitForLocalMutex(oel_u_fifo_ghs_local_mutex);
#define OEL_U_FIFO_LEAVE_CRITICAL_SECTION(status) (void)(status); ReleaseLocalMutex(oel_u_fifo_ghs_local_mutex);

#elif (defined (WIN32) || defined (WINCE)|| defined (__linux))

/* This is the main resource used by oel_u_fifo to guarantee synchronization
   between tasks. */
extern oel_rtos_resource_t *oel_u_fifo_resource;

#define OEL_U_FIFO_ENTER_CRITICAL_SECTION()        \
0;                                                 \
{                                                  \
   if(!oel_u_init_flag)                            \
   {                                               \
      oel_assert(oel_u_init_flag);                 \
   }                                               \
   else                                            \
   {                                               \
      oel_rtos_resource_lock(oel_u_fifo_resource); \
   }                                               \
}
#define OEL_U_FIFO_LEAVE_CRITICAL_SECTION(status)  \
{                                                  \
   (void) status;                                  \
   oel_rtos_resource_unlock(oel_u_fifo_resource);  \
}

#else

#define OEL_U_FIFO_ENTER_CRITICAL_SECTION() OEL_RTOS_DISABLE_INTERRUPTS()
#define OEL_U_FIFO_LEAVE_CRITICAL_SECTION(status) OEL_RTOS_RESTORE_INTERRUPTS(status)

#endif

/* Class instance data.
Implements a FIFO circular queue. */
typedef struct
{
   /* A pointer to an array of event elements from which new event fifo elements can be allocated. */
   uint_least8_t *array;

   /* The array index at which to add new items to the fifo. */
   uint_least16_t head;

   /* The index of the first item to remove from the fifo. */
   uint_least16_t tail;

   /* The number of bytes in each fifo element. */
   uint_least16_t entry_size;

   /* The number of entries allocated for the fifo. */
   uint_least16_t num_entries;

   /* The number of entries stored in the fifo. */
   uint_least16_t count;
   
   /* The maximum number of entries ever stored in the fifo. */
   uint_least16_t max_count;

} oel_u_fifo_t;

#define OEL_U_FIFO_DEFINE() { NULL, 0U, 0U, 0U, 0U, 0U, 0U }

/*------------------------------------------------------------------------------
Name:       oel_u_fifo_init()

Arguments:  oel_u_fifo_t *oel_u_fifo: The class data pointer
            uint_least16_t entry_size: The size of an element.
            uint_least16_t num_entries: The number of entries in the FIFO.

Return: bool_t: Returns TRUE on success and FALSE if malloc failed.
           
Description
Allocate memory for the FIFO and initialize it.
*/
bool_t oel_u_fifo_init(oel_u_fifo_t *fifo, uint_least16_t entry_size, uint_least16_t num_entries);

/******************************************************************************************************************
Function name: oel_u_fifo_static_init()

Description: To initialize the static memory allocated for the FIF0.

Parameter Description:  oel_u_fifo_t *oel_u_fifo: The class data pointer
                        uint_least16_t entry_size: The size of an element.
                        uint_least16_t num_entries: The number of entries in the FIFO.
                        uint_least8_t *fifo_array : Pointer to the fifo array
                        Note: fifo_array size should be greater than ((num_entries + 1) * entry_size)
                       
Return Description:  bool_t: Returns TRUE on success and FALSE if pointer to array is NULL.

Note: User can use either oel_u_fifo_init() or oel_u_fifo_static_init() for FIFO initialization
******************************************************************************************************************/
bool_t oel_u_fifo_static_init
(
   oel_u_fifo_t *fifo,
   uint_least16_t entry_size,
   uint_least16_t num_entries,
   uint_least8_t *fifo_array
);

/*------------------------------------------------------------------------------
Name:       oel_u_fifo_put()

Arguments:  oel_u_fifo_t *oel_u_fifo: The class data pointer
            void *item: The item is filled in to the location pointed to.

Return: bool_t: Returns TRUE on success.  
                Returns FALSE if there are no free event entries in the pool.
           
Description
Copy the item pointed to into the end of the queue.
*/
bool_t oel_u_fifo_get(oel_u_fifo_t *fifo, void *item);

/*------------------------------------------------------------------------------
Name:       oel_u_fifo_get()

Arguments:  oel_u_fifo_t *oel_u_fifo: The class data pointer
            void *item: A pointer to the item to add.

Return: bool_t: Returns TRUE on success.  
                Returns FALSE if the queue is empty.
           
Description
Copy the first entry in the queue into the object pointed to by the item pointer and remove the entry from the queue.
*/
bool_t oel_u_fifo_put(oel_u_fifo_t *fifo, void *item);

/* Restore the MISRA rules */
/*lint -restore +esym(960,19.4) */
/*lint -restore +esym(961,19.7) */

#ifdef __cplusplus
}
#endif
#endif /* #ifndef OEL_U_FIFO_H_ */
