#ifndef AC_MAP_INTERP_4D_MACROS_H_
#define AC_MAP_INTERP_4D_MACROS_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains macros for performing operations relating to 4D map
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

FILE NAME : ac_map_interp_4D_macros.h
******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <ac_map_proto.h>
#include <ac_map_interp_3D_macros.h>


/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
/******************************************************************************
   MACRO: AC_MAP_INTERP_CONSTANT_4D()

   Description:
   Get array element for 4D map.  4D maps use dependent data in the form of an
   array written in columns major format.

   Thus, the dependent data matrix:
   d = [ d111, d121, d131;
         d211, d221, d231;
         d311, d321, d331;
         d411, d421, d431]

       [ d112, d122, d132;
         d212, d222, d232;
         d312, d322, d332;
         d412, d422, d432]

   is written in an array as:

   z = [d111, d211, d311, d411, d121, d221, d321, d421, d131, z231, z331, z431,
        d112, d212, d312, d412, d122, d222, d322, d422, d132, z232, z332, z432];
******************************************************************************/
#define AC_MAP_INTERP_CONSTANT_4D(axis,index1,index2,index3,size1,size2)      \
  (axis)[(index3)*(size2) + (index2)*(size1) + (index1)]


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_4D_U8()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_4D_U8(val,daxis1,index1,index2,index3,ratio1,ratio2,ratio3,size1,size2)\
{                                                                             \
  uint8_t val1, val2;                                                      \
  uint8_t *daxis1, *daxis2;                                                \
                                                                              \
  daxis1 = &(axis[(index3)*(size2)]);                                         \
  AC_MAP_INTERP_LINEAR_3D_U8(val1,daxis1,index1,index2,ratio1,ratio2,size1)   \
                                                                              \
  if (ratio3){                                                                \
    daxis2 = daxis1 + size2;                                                  \
    AC_MAP_INTERP_LINEAR_3D_U8(val2,daxis2,index1,index2,ratio1,ratio2,size1) \
                                                                              \
    val = (uint8_t) (val1 + (((ratio3)*(val2 - val1)) >> 8));              \
  }                                                                           \
  else{                                                                       \
	val = val1;                                                               \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_4D_S8()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_4D_S8(val,daxis1,index1,index2,index3,ratio1,ratio2,ratio3,size1,size2)\
{                                                                             \
  int8_t val1, val2;                                                           \
  int8_t *daxis1, *daxis2;                                                     \
                                                                              \
  daxis1 = &(axis[(index3)*(size2)]);                                         \
  AC_MAP_INTERP_LINEAR_3D_S8(val1,daxis1,index1,index2,ratio1,ratio2,size1)   \
                                                                              \
  if (ratio3){                                                                \
    daxis2 = daxis1 + size2;                                                  \
    AC_MAP_INTERP_LINEAR_3D_S8(val2,daxis2,index1,index2,ratio1,ratio2,size1) \
                                                                              \
    val = (int8_t) (val1 + (((ratio3)*(val2 - val1)) >> 8));                   \
  }                                                                           \
  else{                                                                       \
	val = val1;                                                               \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_4D_U16()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_4D_U16(val,daxis1,index1,index2,index3,ratio1,ratio2,ratio3,size1,size2)\
{                                                                             \
  uint16_t val1, val2;                                                     \
  uint16_t *daxis1, *daxis2;                                               \
                                                                              \
  daxis1 = &(axis[(index3)*(size2)]);                                         \
  AC_MAP_INTERP_LINEAR_3D_U16(val1,daxis1,index1,index2,ratio1,ratio2,size1)  \
                                                                              \
  if (ratio3){                                                                \
    daxis2 = daxis1 + size2;                                                  \
    AC_MAP_INTERP_LINEAR_3D_U16(val2,daxis2,index1,index2,ratio1,ratio2,size1)\
                                                                              \
    val = (uint16_t) (val1 + (((ratio3)*(val2 - val1)) >> 16));            \
  }                                                                           \
  else{                                                                       \
	val = val1;                                                               \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_4D_S16()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_4D_S16(val,daxis1,index1,index2,index3,ratio1,ratio2,ratio3,size1,size2)\
{                                                                             \
  int16_t val1, val2;                                                          \
  int16_t *daxis1, *daxis2;                                                    \
                                                                              \
  daxis1 = &(axis[(index3)*(size2)]);                                         \
  AC_MAP_INTERP_LINEAR_3D_S16(val1,daxis1,index1,index2,ratio1,ratio2,size1)  \
                                                                              \
  if (ratio3){                                                                \
    daxis2 = daxis1 + size2;                                                  \
    AC_MAP_INTERP_LINEAR_3D_S16(val2,daxis2,index1,index2,ratio1,ratio2,size1)\
                                                                              \
    val = (int16_t) (val1 + (((ratio3)*(val2 - val1)) >> 16));                 \
  }                                                                           \
  else{                                                                       \
	val = val1;                                                               \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_4D_U32()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_4D_U32(val,daxis1,index1,index2,index3,ratio1,ratio2,ratio3,size1,size2)\
{                                                                             \
  uint32_t val1, val2;                                                     \
  uint32_t *daxis1, *daxis2;                                               \
                                                                              \
  daxis1 = &(axis[(index3)*(size2)]);                                         \
  AC_MAP_INTERP_LINEAR_3D_U32(val1,daxis1,index1,index2,ratio1,ratio2,size1)  \
                                                                              \
  if (ratio3){                                                                \
    daxis2 = daxis1 + size2;                                                  \
    AC_MAP_INTERP_LINEAR_3D_U32(val2,daxis2,index1,index2,ratio1,ratio2,size1)\
                                                                              \
    val = val1 + ac_map_ratio_multiply_32((ratio3), (val2 - val1));           \
  }                                                                           \
  else{                                                                       \
	val = val1;                                                               \
  }                                                                           \
}



/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_4D_S32()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_4D_S32(val,daxis1,index1,index2,index3,ratio1,ratio2,ratio3,size1,size2)\
{                                                                             \
  int32_t val1, val2;                                                          \
  int32_t *daxis1, *daxis2;                                                    \
                                                                              \
  daxis1 = &(axis[(index3)*(size2)]);                                         \
  AC_MAP_INTERP_LINEAR_3D_S32(val1,daxis1,index1,index2,ratio1,ratio2,size1)  \
                                                                              \
  if (ratio3){                                                                \
    daxis2 = daxis1 + size2;                                                  \
    AC_MAP_INTERP_LINEAR_3D_S32(val2,daxis2,index1,index2,ratio1,ratio2,size1)\
                                                                              \
    val = val1 + ac_map_ratio_multiply_32((ratio3), (val2 - val1));           \
  }                                                                           \
  else{                                                                       \
	val = val1;                                                               \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_4D_R32()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_4D_R32(val,daxis1,index1,index2,index3,ratio1,ratio2,ratio3,size1,size2)\
{                                                                             \
  float val1, val2;                                                         \
  float *daxis1, *daxis2;                                                   \
                                                                              \
  daxis1 = &(axis[(index3)*(size2)]);                                         \
  AC_MAP_INTERP_LINEAR_3D_R32(val1,daxis1,index1,index2,ratio1,ratio2,size1)  \
                                                                              \
  if (ratio3){                                                                \
    daxis2 = daxis1 + size2;                                                  \
    AC_MAP_INTERP_LINEAR_3D_R32(val2,daxis2,index1,index2,ratio1,ratio2,size1)\
                                                                              \
    val = val1 + (ratio3)*(val2 - val1);                                      \
  }                                                                           \
  else{                                                                       \
	val = val1;                                                               \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_4D_R64()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_4D_R64(val,daxis1,index1,index2,index3,ratio1,ratio2,ratio3,size1,size2)\
{                                                                             \
  double val1, val2;                                                         \
  double *daxis1, *daxis2;                                                   \
                                                                              \
  daxis1 = &(axis[(index3)*(size2)]);                                         \
  AC_MAP_INTERP_LINEAR_3D_R64(val1,daxis1,index1,index2,ratio1,ratio2,size1)  \
                                                                              \
  if (ratio3){                                                                \
    daxis2 = daxis1 + size2;                                                  \
    AC_MAP_INTERP_LINEAR_3D_R64(val2,daxis2,index1,index2,ratio1,ratio2,size1)\
                                                                              \
    val = val1 + (ratio3)*(val2 - val1);                                      \
  }                                                                           \
  else{                                                                       \
	val = val1;                                                               \
  }                                                                           \
}


/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/

#endif /* AC_MAP_INTERP_4D_MACROS_H_ */

