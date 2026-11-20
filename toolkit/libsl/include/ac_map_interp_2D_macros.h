#ifndef AC_MAP_INTERP_2D_MACROS_H_
#define AC_MAP_INTERP_2D_MACROS_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains macros for performing operations relating to 2D map
interpolations.

Currently, these routines may access memory that is 'outside' of the
dependent axis.  This occurs when the input is equal to the last point in the
independent axis.  If the next 'point' past the end of the dependent axis is
in memory that may not be accessed (e.g. an invalid address), this may cause a
run-time exception.  The value in memory for this location is unimportant as
its data is not used because the ratio will be equal to 0.

In order to correct for this situation, a check would need to be added to test
if the ratio was zero and then skip accessing the unneeded memory location.
This adds extra overhead in all cases.  Instances where this would cause
problems should be extremely rare.

FILE NAME : ac_map_interp_2D_macros.h
******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <ac_map_proto.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
/******************************************************************************
   MACRO: AC_MAP_INTERP_CONSTANT_2D()

   Description:
   Gets value from 2D Map from input index using constant interpolation.
******************************************************************************/
#define AC_MAP_INTERP_CONSTANT_2D(axis,index)  (axis)[(index)]


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_2D_U8()

   Description:

******************************************************************************/
#define AC_MAP_INTERP_LINEAR_2D_U8(axis,ratio,index,val)                      \
{                                                                             \
  if (ratio)                                                                  \
    (val) = (uint8_t) ((axis)[(index)] +                                   \
            (((ratio)*((axis)[(index)+1] - (axis)[(index)])) >> 8));          \
  else                                                                        \
    (val) = (axis)[(index)];                                                  \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_2D_S8()

   Description:

******************************************************************************/
#define AC_MAP_INTERP_LINEAR_2D_S8(axis,ratio,index,val)                      \
{                                                                             \
  if (ratio)                                                                  \
    (val) = (int8_t) ((axis)[(index)] +                                        \
            (((ratio)*((axis)[(index)+1] - (axis)[(index)])) >> 8));          \
  else                                                                        \
    (val) = (axis)[(index)];                                                  \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_2D_U16()

   Description:

******************************************************************************/
#define AC_MAP_INTERP_LINEAR_2D_U16(axis,ratio,index,val)                     \
{                                                                             \
  if (ratio)                                                                  \
    (val) = (uint16_t) ((axis)[(index)] +                                   \
            (((ratio)*((axis)[(index)+1] - (axis)[(index)])) >> 16));         \
  else                                                                        \
    (val) = (axis)[(index)];                                                  \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_2D_S16()

   Description:

******************************************************************************/
#define AC_MAP_INTERP_LINEAR_2D_S16(axis,ratio,index,val)                     \
{                                                                             \
  if (ratio)                                                                  \
    (val) = (int16_t) ((axis)[(index)] +                                        \
            (((ratio)*((axis)[(index)+1] - (axis)[(index)])) >> 16));         \
  else                                                                        \
    (val) = (axis)[(index)];                                                  \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_2D_U32()

   Description:
     uint64 target specific optimization currently turned off because of
     erratic timings measured on A4M1.  Usually faster, but occasionally
     slower than non-64bit implementation.

******************************************************************************/
#if defined(__DCC__) && defined(__ppc) && (0)
#define AC_MAP_INTERP_LINEAR_2D_U32(axis,ratio,index,val)                     \
{                                                                             \
  if (ratio)                                                                  \
    (val) = (axis)[(index)] +                                                 \
            (((ratio)*((unsigned long long) ((axis)[(index)+1]) -             \
                       (unsigned long long) ((axis)[(index)]))) >> 32);       \
  else                                                                        \
    (val) = (axis)[(index)];                                                  \
}

#else
#define AC_MAP_INTERP_LINEAR_2D_U32(axis,ratio,index,val)                     \
{                                                                             \
  if (ratio)                                                                  \
    (val) = (uint32_t) ((axis)[(index)] +                                   \
             ac_map_ratio_multiply_32((ratio), (uint32_t)                  \
                                      ((axis)[(index)+1] - (axis)[(index)])));\
  else                                                                        \
    (val) = (axis)[(index)];                                                  \
}
#endif


/******************************************************************************
   MACRO: AC_MAP_INTERP_2D_S32()

   Description:
     uint64 target specific optimization currently turned off because of
     erratic timings measured on A4M1.  Usually faster, but occasionally
     slower than non-64bit implementation.

******************************************************************************/
#if defined(__DCC__) && defined(__ppc) && (0)
#define AC_MAP_INTERP_LINEAR_2D_S32(axis,ratio,index,val)                     \
{                                                                             \
  if (ratio)                                                                  \
    (val) = (axis)[(index)] +                                                 \
            (((ratio)*((unsigned long long) ((axis)[(index)+1]) -             \
                       (unsigned long long) ((axis)[(index)]))) >> 32);       \
  else                                                                        \
    (val) = (axis)[(index)];                                                  \
}

#else
#define AC_MAP_INTERP_LINEAR_2D_S32(axis,ratio,index,val)                     \
{                                                                             \
  if (ratio)                                                                  \
    (val) = (int32_t) ((axis)[(index)] +                                        \
             ac_map_ratio_multiply_32((ratio), (uint32_t)                  \
                                      ((axis)[(index)+1] - (axis)[(index)])));\
  else                                                                        \
    (val) = (axis)[(index)];                                                  \
}
#endif


/******************************************************************************
   MACRO: AC_MAP_INTERP_2D_R32()

   Description:

******************************************************************************/
#define AC_MAP_INTERP_LINEAR_2D_R32(axis,ratio,index,val)                     \
{                                                                             \
  if (ratio)                                                                  \
    (val) = (axis)[index] + (ratio)*((axis)[(index)+1] - (axis)[(index)]);    \
  else                                                                        \
    (val) = (axis)[(index)];                                                  \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_2D_R64()

   Description:

******************************************************************************/
#define AC_MAP_INTERP_LINEAR_2D_R64(axis,ratio,index,val)                     \
{                                                                             \
  if (ratio)                                                                  \
    (val) = (axis)[(index)] + (ratio)*((axis)[(index)+1] - (axis)[(index)]);  \
  else                                                                        \
    (val) = (axis)[(index)];                                                  \
}

/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/

#endif /* AC_MAP_INTERP_2D_MACROS_H_ */


