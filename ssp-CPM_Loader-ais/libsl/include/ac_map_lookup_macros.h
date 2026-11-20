#ifndef AC_MAP_LOOKUP_MACROS_H_
#define AC_MAP_LOOKUP_MACROS_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains general sequential and bisection map lookukp macros.

FILE NAME : ac_map_lookup_macros.h
******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
/******************************************************************************
   MACRO: AC_MAP_LOOKUP_SEQUENTIAL_SEARCH()

   Description:
   Search an input array "a" for the nearest data to "x". The search
   is linear starting from "i". Upon exit i has been modified such that
   a[i] <= x < a[i+1].

   This routine may consume different amounts of CPU execution time from one
   call to the next depending on "smoothness" of input data.  This could
   potentially cause ECM execution time overflows in situations where the
   CPU load is heavily loaded and the input data stream becomes "eratic".

   Input:
   x - independent variable
   a - a strictly monotonically increasing array of data
   i - previous index into a

   Output:
   x - unchanged
   a - unchanged
   i - a[i] <= x < a[i+1]

   Assumptions:
   1) The size of a must be >= 2.
   2) array is monotonically increasing
   3) given that a has n points, i must be <= n - 2 on input
   4) a[0] <= x < a[n-1]
******************************************************************************/
#define AC_MAP_LOOKUP_SEQUENTIAL_SEARCH( x, a, i)                             \
{                                                                             \
  if((x) <= (a)[(i)])                                                         \
    while((x) < (a)[(i)])                                                     \
      (i)--;                                                                  \
  else                                                                        \
    while((x) >= (a)[(i)+1])                                                  \
      (i)++;                                                                  \
}


/******************************************************************************
   MACRO: AC_MAP_LOOKUP_BISECTION_SEARCH()

   Description:
   Search an input array "a" for the nearest data to "x". The search uses
   the method of bisection starting from the middle of the array "a". Upon
   exit i has been modified such that a[i] <= x < a[i+1].

   This routine should always consume nearly equal amounts of CPU execution
   time regardless of input data stream "smoothness".  This routine may not
   be as fast as the AC_MAP_SEARCH when input data stream is "smooth".

   Input:
   x  - independent variable
   a  - a strictly monotonically increasing array of data
   i  - previous index into a
   lo - uninitialized temporary variable (wordsize same as i)
   hi - uninitialized temproary variable (wordsize same aa i)

   Output:
   x -  unchanged
   a -  unchanged
   i -  a[i] <= x < a[i+1]

   Assumptions:
   1) The size of a must be >= 2.
   2) array is monotonically increasing
   3) given that a has n points, i must be <= n - 2 on input
   4) a[0] <= x < a[n-1]
******************************************************************************/
#define AC_MAP_LOOKUP_BISECTION_SEARCH( x, a, lo, mid, hi )                   \
{                                                                             \
  while( ( hi - lo ) > 1 ) {                                                  \
    mid = ( hi + lo ) >> 1;                                                   \
    if( (x) >= (a)[mid] )                                                     \
      lo = mid;                                                               \
    else                                                                      \
      hi = mid;                                                               \
  }                                                                           \
}

/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/

#endif /* AC_MAP_LOOKUP_MACROS_H_ */
