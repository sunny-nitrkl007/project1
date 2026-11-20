/******************************************************************************************************************
 Copyright 2012 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: oel_u_dl_element.h

Description:  This file contains the public interfaces for the double-linked list element -- unordered class.
   This class allows objects to be placed into a list, and is NOT capable of handling interactions between
   interrupt-level code and task-level code.
******************************************************************************************************************/
#ifndef OEL_U_DL_ELEMENT_H_
#define OEL_U_DL_ELEMENT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <std_t.h>

/* This class models a double-linked list element.  Any object that may be placed into a list must define its
   first member as a list element and must give it the name "base".  This class uses 2 bytes of RAM.

   Note:  A list element can only reside in one list at a time.  Furthermore, the same list element cannot be
   placed into the same list more than once without first removing it from the list. */
typedef struct
{
   /* This attribute points to the previous indexed element before this one. If there is none before this one, 
    then the attribute is UINT_LEAST16_MAX. */
   uint_least16_t prev_index;
  
   /* This attribute points to the next indexed element after this one.  If there is none after this one, then the
      attribute is UINT_LEAST16_MAX. */
   uint_least16_t next_index;
} oel_u_dl_element_t;

#ifdef __cplusplus
}
#endif
#endif /* #ifndef OEL_U_DL_ELEMENT_H_ */
