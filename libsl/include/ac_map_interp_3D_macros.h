#ifndef AC_MAP_INTERP_3D_MACROS_H_
#define AC_MAP_INTERP_3D_MACROS_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains macros for performing operations relating to 3D map
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

FILE NAME : ac_map_interp_3D_macros.h
******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <ac_map_proto.h>


/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
/******************************************************************************
   MACRO: AC_MAP_INTERP_CONSTANT_3D()

   Description:
   Get array element for 3D map.  3D maps use dependent data in the form of an
   array written in row major format.  This format is the transpose of the
   way in which standard MW maps work but the same as all previous CAT maps
   and MatrixX.

   Thus, the dependent data matrix:
   z = [ z11, z21, z31;
         z12, z22, z32;
         z13, z23, z33;
         z13, z23, z34]

   is written in an array as:

   z = [z11, z21, z31, z12, z22, z32, z13, z23, z33, z13, z23, z34];
******************************************************************************/
#define AC_MAP_INTERP_CONSTANT_3D(axis,indexX,indexY,sizeX)                   \
  (axis)[(indexY)*(sizeX) + (indexX)]


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_3D_U8()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_3D_U8(val,z_axis,x_index,y_index,x_ratio,y_ratio,x_size) \
{                                                                             \
  uint16_t z_index;                                                        \
  uint8_t  *z_array, z0, z1, y_min, y_max;                                 \
                                                                              \
  /* Calculate y-min */                                                       \
  z_index = (uint16_t) ((x_index) + (y_index)*(x_size));                   \
  z_array = &((z_axis)[z_index]);                                             \
  if (x_ratio){                                                               \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_min = (uint8_t) (z0 + (((x_ratio)*(z1 - z0)) >> 8));                 \
  }                                                                           \
  else{                                                                       \
    y_min = *z_array;                                                         \
  }                                                                           \
                                                                              \
  /* Calculate y-max */                                                       \
  if (y_ratio){                                                               \
    z_index += (x_size);                                                      \
    z_array = &((z_axis)[z_index]);                                           \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_max = (uint8_t) (z0 + (((x_ratio)*(z1 - z0)) >> 8));                 \
                                                                              \
    /* Calculate and return z */                                              \
    val = (uint8_t) (y_min + (((y_ratio)*(y_max - y_min)) >> 8));          \
  }                                                                           \
  else{                                                                       \
    val = y_min;                                                              \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_3D_S8()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_3D_S8(val,z_axis,x_index,y_index,x_ratio,y_ratio,x_size) \
{                                                                             \
  uint16_t z_index;                                                        \
  int8_t       *z_array, z0, z1, y_min, y_max;                                 \
                                                                              \
  /* Calculate y-min */                                                       \
  z_index = (uint16_t) ((x_index) + (y_index)*(x_size));                   \
  z_array = &((z_axis)[z_index]);                                             \
  if (x_ratio){                                                               \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_min = (int8_t) (z0 + (((x_ratio)*(z1 - z0)) >> 8));                      \
  }                                                                           \
  else{                                                                       \
    y_min = *z_array;                                                         \
  }                                                                           \
                                                                              \
  /* Calculate y-max */                                                       \
  if (y_ratio){                                                               \
    z_index += (x_size);                                                      \
    z_array = &((z_axis)[z_index]);                                           \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_max = (int8_t) (z0 + (((x_ratio)*(z1 - z0)) >> 8));                      \
                                                                              \
    /* Calculate and return z */                                              \
    val = (int8_t) (y_min + (((y_ratio)*(y_max - y_min)) >> 8));               \
  }                                                                           \
  else{                                                                       \
    val = y_min;                                                              \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_3D_U16()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_3D_U16(val,z_axis,x_index,y_index,x_ratio,y_ratio,x_size)\
{                                                                             \
  uint32_t z_index;                                                        \
  uint16_t *z_array, z0, z1, y_min, y_max;                                 \
                                                                              \
  /* Calculate y-min */                                                       \
  z_index = (x_index) + (y_index)*(x_size);                                   \
  z_array = &((z_axis)[z_index]);                                             \
  if (x_ratio){                                                               \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_min = (uint16_t) (z0 + (((x_ratio)*(z1 - z0)) >> 16));               \
  }                                                                           \
  else{                                                                       \
    y_min = *z_array;                                                         \
  }                                                                           \
                                                                              \
  /* Calculate y-max */                                                       \
  if (y_ratio){                                                               \
    z_index += (x_size);                                                      \
    z_array = &((z_axis)[z_index]);                                           \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_max = (uint16_t) (z0 + (((x_ratio)*(z1 - z0)) >> 16));               \
                                                                              \
    /* Calculate and return z */                                              \
    val = (uint16_t) (y_min + (((y_ratio)*(y_max - y_min)) >> 16));        \
  }                                                                           \
  else{                                                                       \
    val = y_min;                                                              \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_3D_S16()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_3D_S16(val,z_axis,x_index,y_index,x_ratio,y_ratio,x_size)\
{                                                                             \
  uint32_t z_index;                                                        \
  int16_t      *z_array, z0, z1, y_min, y_max;                                 \
                                                                              \
  /* Calculate y-min */                                                       \
  z_index = (x_index) + (y_index)*(x_size);                                   \
  z_array = &((z_axis)[z_index]);                                             \
  if (x_ratio){                                                               \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_min = (int16_t) (z0 + (((x_ratio)*(z1 - z0)) >> 16));                    \
  }                                                                           \
  else{                                                                       \
    y_min = *z_array;                                                         \
  }                                                                           \
                                                                              \
  /* Calculate y-max */                                                       \
  if (y_ratio){                                                               \
    z_index += (x_size);                                                      \
    z_array = &((z_axis)[z_index]);                                           \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_max = (int16_t) (z0 + (((x_ratio)*(z1 - z0)) >> 16));                    \
                                                                              \
    /* Calculate and return z */                                              \
    val = (int16_t) (y_min + (((y_ratio)*(y_max - y_min)) >> 16));             \
  }                                                                           \
  else{                                                                       \
    val = y_min;                                                              \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_3D_U32()

   Description:
     uint64 target specific optimization currently turned off because of
     erratic timings measured on A4M1.  Usually faster, but occasionally
     slower than non-64bit implementation.

******************************************************************************/
#if defined(__DCC__) && defined(__ppc) && (0)
#define                                                                       \
AC_MAP_INTERP_LINEAR_3D_U32(val,z_axis,x_index,y_index,x_ratio,y_ratio,x_size)\
{                                                                             \
  uint32_t z_index;                                                        \
  uint32_t *z_array;                                                       \
  unsigned long long z0, z1, y_min, y_max;                                    \
                                                                              \
  /* Calculate y-min */                                                       \
  z_index = (x_index) + (y_index)*(x_size);                                   \
  z_array = &((z_axis)[z_index]);                                             \
  if (x_ratio){                                                               \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_min = z0 + (((x_ratio)*(z1 - z0)) >> 32);                               \
  }                                                                           \
  else{                                                                       \
    y_min = *z_array;                                                         \
  }                                                                           \
                                                                              \
  /* Calculate y-max */                                                       \
  if (y_ratio){                                                               \
    z_index += (x_size);                                                      \
    z_array = &((z_axis)[z_index]);                                           \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_max = z0 + (((x_ratio)*(z1 - z0)) >> 32);                               \
                                                                              \
    /* Calculate and return z */                                              \
    val = y_min + (((y_ratio)*(y_max - y_min)) >> 32);                        \
  }                                                                           \
  else{                                                                       \
    val = y_min;                                                              \
  }                                                                           \
}
#else
#define                                                                       \
AC_MAP_INTERP_LINEAR_3D_U32(val,z_axis,x_index,y_index,x_ratio,y_ratio,x_size)\
{                                                                             \
  uint32_t z_index;                                                        \
  uint32_t *z_array, z0, z1, y_min, y_max;                                 \
                                                                              \
  /* Calculate y-min */                                                       \
  z_index = (x_index) + (y_index)*(x_size);                                   \
  z_array = &((z_axis)[z_index]);                                             \
  if (x_ratio){                                                               \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_min = (uint32_t)                                                     \
            (z0 + ac_map_ratio_multiply_32((x_ratio), (z1 - z0)));            \
  }                                                                           \
  else{                                                                       \
    y_min = *z_array;                                                         \
  }                                                                           \
                                                                              \
  /* Calculate y-max */                                                       \
  if (y_ratio){                                                               \
    z_index += (x_size);                                                      \
    z_array = &((z_axis)[z_index]);                                           \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_max = (uint32_t)                                                     \
            (z0 + ac_map_ratio_multiply_32((x_ratio), (z1 - z0)));            \
                                                                              \
    /* Calculate and return z */                                              \
    val = (uint32_t)                                                       \
          (y_min + ac_map_ratio_multiply_32((y_ratio), (y_max - y_min)));     \
  }                                                                           \
  else{                                                                       \
    val = y_min;                                                              \
  }                                                                           \
}
#endif


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_3D_S32()

   Description:
     uint64 target specific optimization currently turned off because of
     erratic timings measured on A4M1.  Usually faster, but occasionally
     slower than non-64bit implementation.

******************************************************************************/
#if defined(__DCC__) && defined(__ppc) && (0)
#define                                                                       \
AC_MAP_INTERP_LINEAR_3D_S32(val,z_axis,x_index,y_index,x_ratio,y_ratio,x_size)\
{                                                                             \
  uint32_t z_index;                                                        \
  int32_t      *z_array;                                                       \
  signed long long z0, z1, y_min, y_max;                                      \
                                                                              \
  /* Calculate y-min */                                                       \
  z_index = (x_index) + (y_index)*(x_size);                                   \
  z_array = &((z_axis)[z_index]);                                             \
  if (x_ratio){                                                               \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_min = z0 + (((x_ratio)*(z1 - z0)) >> 32);                               \
  }                                                                           \
  else{                                                                       \
    y_min = *z_array;                                                         \
  }                                                                           \
                                                                              \
  /* Calculate y-max */                                                       \
  if (y_ratio){                                                               \
    z_index += (x_size);                                                      \
    z_array = &((z_axis)[z_index]);                                           \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_max = z0 + (((x_ratio)*(z1 - z0)) >> 32);                               \
                                                                              \
    /* Calculate and return z */                                              \
    val = y_min + (((y_ratio)*(y_max - y_min)) >> 32);                        \
  }                                                                           \
  else{                                                                       \
    val = y_min;                                                              \
  }                                                                           \
}
#else
#define                                                                       \
AC_MAP_INTERP_LINEAR_3D_S32(val,z_axis,x_index,y_index,x_ratio,y_ratio,x_size)\
{                                                                             \
  uint32_t z_index;                                                        \
  int32_t      *z_array, z0, z1, y_min, y_max;                                 \
                                                                              \
  /* Calculate y-min */                                                       \
  z_index = (x_index) + (y_index)*(x_size);                                   \
  z_array = &((z_axis)[z_index]);                                             \
  if (x_ratio){                                                               \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_min = (int32_t) (z0 + ac_map_ratio_multiply_32((x_ratio), (z1 - z0)));   \
  }                                                                           \
  else{                                                                       \
    y_min = *z_array;                                                         \
  }                                                                           \
                                                                              \
  /* Calculate y-max */                                                       \
  if (y_ratio){                                                               \
    z_index += (x_size);                                                      \
    z_array = &((z_axis)[z_index]);                                           \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_max = (int32_t) (z0 + ac_map_ratio_multiply_32((x_ratio), (z1 - z0)));   \
                                                                              \
    /* Calculate and return z */                                              \
    val = (int32_t)                                                            \
          (y_min + ac_map_ratio_multiply_32((y_ratio), (y_max - y_min)));     \
  }                                                                           \
  else{                                                                       \
    val = y_min;                                                              \
  }                                                                           \
}
#endif


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_3D_R32()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_3D_R32(val,z_axis,x_index,y_index,x_ratio,y_ratio,x_size)\
{                                                                             \
  uint32_t z_index;                                                        \
  float     *z_array, z0, z1, y_min, y_max;                                 \
                                                                              \
  /* Calculate y-min */                                                       \
  z_index = (x_index) + (y_index)*(x_size);                                   \
  z_array = &((z_axis)[z_index]);                                             \
  if (x_ratio){                                                               \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_min = z0 + ((x_ratio)*(z1 - z0));                                       \
  }                                                                           \
  else{                                                                       \
    y_min = *z_array;                                                         \
  }                                                                           \
                                                                              \
  /* Calculate y-max */                                                       \
  if (y_ratio){                                                               \
    z_index += (x_size);                                                      \
    z_array = &((z_axis)[z_index]);                                           \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_max = z0 + ((x_ratio)*(z1 - z0));                                       \
                                                                              \
    /* Calculate and return z */                                              \
    val = y_min + ((y_ratio)*(y_max - y_min));                                \
  }                                                                           \
  else{                                                                       \
    val = y_min;                                                              \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_3D_R64()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_3D_R64(val,z_axis,x_index,y_index,x_ratio,y_ratio,x_size)\
{                                                                             \
  uint32_t z_index;                                                        \
  double     *z_array, z0, z1, y_min, y_max;                                 \
                                                                              \
  /* Calculate y-min */                                                       \
  z_index = (x_index) + (y_index)*(x_size);                                   \
  z_array = &((z_axis)[z_index]);                                             \
  if (x_ratio){                                                               \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_min = z0 + ((x_ratio)*(z1 - z0));                                       \
  }                                                                           \
  else{                                                                       \
    y_min = *z_array;                                                         \
  }                                                                           \
                                                                              \
  /* Calculate y-max */                                                       \
  if (y_ratio){                                                               \
    z_index += (x_size);                                                      \
    z_array = &((z_axis)[z_index]);                                           \
    z0 = *z_array++;                                                          \
    z1 = *z_array;                                                            \
    y_max = z0 + ((x_ratio)*(z1 - z0));                                       \
                                                                              \
    /* Calculate and return z */                                              \
    val = y_min + ((y_ratio)*(y_max - y_min));                                \
  }                                                                           \
  else{                                                                       \
    val = y_min;                                                              \
  }                                                                           \
}
/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/

#endif /* AC_MAP_INTERP_3D_MACROS_H_ */

