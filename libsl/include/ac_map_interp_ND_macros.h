#ifndef AC_MAP_INTERP_ND_MACROS_H_
#define AC_MAP_INTERP_ND_MACROS_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains macros for performing operations relating to ND map
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

FILE NAME : ac_map_interp_ND_macros.h
******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <ac_map_proto.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
/* This defines the max number of axises supported by the ND map routines.   */
#define MAX_NUMBER_AXISES 8


/******************************************************************************
   MACRO: AC_MAP_INTERP_ND_START_OFFSET()

   Description:
   This macro calculates the start offset array required for the ND map interp
   routines based on the array of sizes for each independent axis.

   The ND map routines require a pre-calculated start offset - which is the
   index into the dependent array for the first value for each dimension lies.
   Pre-calculating these values prevents the need to constantly calculate this
   information each loop at the cost of a bit of ram.
******************************************************************************/
#define AC_MAP_INTERP_ND_START_OFFSET(num_inputs, size, start_offset)         \
{                                                                             \
  uint8_t i,j;                                                             \
                                                                              \
  for (i=0;i<(num_inputs);++i){                                               \
  (start_offset)[i] = 1;                                                      \
    for (j=0;j<(i+1);++j){                                                    \
      (start_offset)[i] *= (size)[j];                                         \
    }                                                                         \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_CONSTANT_ND()

   Description:
   Get array element for an ND map.  ND maps use dependent data in the form of
   an array written in row major format.  This format is the transpose of the
   way in which standard MW maps work but the same as all previous CAT maps
   and MatrixX.

   Thus, the dependent data (only supported as an array):

   z = [[ z111, z211, z311,   [ z112, z212, z312,
          z121, z221, z321,     z122, z222, z322,
        z131, z231, z331,     z132, z232, z332,
        z131, z231, z341],    z132, z232, z342]]

******************************************************************************/
#define AC_MAP_INTERP_CONSTANT_ND(dep_val,axis,num_inputs,start_offset,index) \
{                                                                             \
  uint8_t  i;                                                              \
  uint32_t offset;                                                         \
                                                                              \
  offset = (index)[0];                                                        \
  for (i=1;i<(num_inputs);++i){                                               \
    offset += (start_offset)[i-1]*(index)[i];                                 \
  }                                                                           \
  (dep_val) = (axis)[offset];                                                 \
}                                                                             \


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_ND_R64()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_ND_R64(dep_array,num_inputs,start_offset,index,ratio)    \
{                                                                             \
  uint8_t  i,j;                                                            \
  uint32_t dep_idx[MAX_NUMBER_AXISES];                                     \
  double     y_max, y_min;                                                   \
                                                                              \
  for (i=0;i<(1<<((num_inputs)-1));++i){                                      \
    /* get indices into dependent array */                                    \
    dep_idx[i] = (index)[0];                                                  \
    for (j=1;j<(num_inputs);++j){                                             \
      if (i&j){                                                               \
        dep_idx[i] += ((index)[j]+1)*(start_offset)[j-1];                     \
      }                                                                       \
      else{                                                                   \
        dep_idx[i] += ((index)[j])*(start_offset)[j-1];                       \
      }                                                                       \
    }                                                                         \
                                                                              \
    /* dependent data interpolations interpolations */                        \
    y_min = (dep_array)[dep_idx[i]];                                          \
    if ((ratio)[0]){                                                          \
      y_max = (dep_array)[dep_idx[i]+1];                                      \
      dep_val[i] = (double) (y_min + (ratio)[0]*(y_max - y_min));            \
    }                                                                         \
    else{                                                                     \
      dep_val[i] = y_min;                                                     \
    }                                                                         \
  }                                                                           \
                                                                              \
  /* interpolations of interpolations */                                      \
  for (i=1;i<(num_inputs);++i){                                               \
    for (j=0;j<((num_inputs)-i);++j){                                         \
      y_min = dep_val[j<<1];                                                  \
      if ((ratio)[i]){                                                        \
        y_max = dep_val[(j<<1)+1];                                            \
        dep_val[j] = (double) (y_min + (ratio)[i]*(y_max - y_min));          \
      }                                                                       \
      else{                                                                   \
        dep_val[j] = y_min;                                                   \
      }                                                                       \
    }                                                                         \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_ND_R32()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_ND_R32(dep_array,num_inputs,start_offset,index,ratio)    \
{                                                                             \
  uint8_t  i,j;                                                            \
  uint32_t dep_idx[MAX_NUMBER_AXISES];                                     \
  float     y_max, y_min;                                                   \
                                                                              \
  for (i=0;i<(1<<((num_inputs)-1));++i){                                      \
    /* get indices into dependent array */                                    \
    dep_idx[i] = (index)[0];                                                  \
    for (j=1;j<(num_inputs);++j){                                             \
      if (i&j){                                                               \
        dep_idx[i] += ((index)[j]+1)*(start_offset)[j-1];                     \
      }                                                                       \
      else{                                                                   \
        dep_idx[i] += ((index)[j])*(start_offset)[j-1];                       \
      }                                                                       \
    }                                                                         \
                                                                              \
    /* dependent data interpolations interpolations */                        \
    y_min = (dep_array)[dep_idx[i]];                                          \
    if ((ratio)[0]){                                                          \
      y_max = (dep_array)[dep_idx[i]+1];                                      \
      dep_val[i] = (float) (y_min + (ratio)[0]*(y_max - y_min));            \
    }                                                                         \
    else{                                                                     \
      dep_val[i] = y_min;                                                     \
    }                                                                         \
  }                                                                           \
                                                                              \
  /* interpolations of interpolations */                                      \
  for (i=1;i<(num_inputs);++i){                                               \
    for (j=0;j<((num_inputs)-i);++j){                                         \
      y_min = dep_val[j<<1];                                                  \
      if ((ratio)[i]){                                                        \
        y_max = dep_val[(j<<1)+1];                                            \
        dep_val[j] = (float) (y_min + (ratio)[i]*(y_max - y_min));          \
      }                                                                       \
      else{                                                                   \
        dep_val[j] = y_min;                                                   \
      }                                                                       \
    }                                                                         \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_ND_S8()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_ND_S8(dep_array,num_inputs,start_offset,index,ratio)     \
{                                                                             \
  uint8_t  i,j;                                                            \
  uint16_t dep_idx[MAX_NUMBER_AXISES];                                     \
  int8_t       y_max, y_min;                                                   \
                                                                              \
  for (i=0;i<(1<<((num_inputs)-1));++i){                                      \
    /* get indices into dependent array */                                    \
    dep_idx[i] = (index)[0];                                                  \
    for (j=1;j<(num_inputs);++j){                                             \
      if (i&j){                                                               \
        dep_idx[i] += ((index)[j]+1)*(start_offset)[j-1];                     \
      }                                                                       \
      else{                                                                   \
        dep_idx[i] += ((index)[j])*(start_offset)[j-1];                       \
      }                                                                       \
    }                                                                         \
                                                                              \
    /* dependent data interpolations interpolations */                        \
    y_min = (dep_array)[dep_idx[i]];                                          \
    if ((ratio)[0]){                                                          \
      y_max = (dep_array)[dep_idx[i]+1];                                      \
      dep_val[i] = (int8_t) (y_min + (((ratio)[0]*(y_max - y_min)) >> 8));     \
    }                                                                         \
    else{                                                                     \
      dep_val[i] = y_min;                                                     \
    }                                                                         \
  }                                                                           \
                                                                              \
  /* interpolations of interpolations */                                      \
  for (i=1;i<(num_inputs);++i){                                               \
    for (j=0;j<((num_inputs)-i);++j){                                         \
      y_min = dep_val[j<<1];                                                  \
      if ((ratio)[i]){                                                        \
        y_max = dep_val[(j<<1)+1];                                            \
        dep_val[j] = (int8_t) (y_min + (((ratio)[i]*(y_max - y_min)) >> 8));   \
      }                                                                       \
      else{                                                                   \
        dep_val[j] = y_min;                                                   \
      }                                                                       \
    }                                                                         \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_ND_U8()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_ND_U8(dep_array,num_inputs,start_offset,index,ratio)     \
{                                                                             \
  uint8_t  i,j;                                                            \
  uint16_t dep_idx[MAX_NUMBER_AXISES];                                     \
  uint8_t  y_max, y_min;                                                   \
                                                                              \
  for (i=0;i<(1<<((num_inputs)-1));++i){                                      \
    /* get indices into dependent array */                                    \
    dep_idx[i] = (index)[0];                                                  \
    for (j=1;j<(num_inputs);++j){                                             \
      if (i&j){                                                               \
        dep_idx[i] += ((index)[j]+1)*(start_offset)[j-1];                     \
      }                                                                       \
      else{                                                                   \
        dep_idx[i] += ((index)[j])*(start_offset)[j-1];                       \
      }                                                                       \
    }                                                                         \
                                                                              \
    /* dependent data interpolations interpolations */                        \
    y_min = (dep_array)[dep_idx[i]];                                          \
    if ((ratio)[0]){                                                          \
      y_max = (dep_array)[dep_idx[i]+1];                                      \
      dep_val[i] = (uint8_t) (y_min +                                      \
                   (((ratio)[0]*(y_max - y_min)) >> 8));                      \
    }                                                                         \
    else{                                                                     \
      dep_val[i] = y_min;                                                     \
    }                                                                         \
  }                                                                           \
                                                                              \
  /* interpolations of interpolations */                                      \
  for (i=1;i<(num_inputs);++i){                                               \
    for (j=0;j<((num_inputs)-i);++j){                                         \
      y_min = dep_val[j<<1];                                                  \
      if ((ratio)[i]){                                                        \
        y_max = dep_val[(j<<1)+1];                                            \
        dep_val[j] = (uint8_t) (y_min +                                    \
                     (((ratio)[i]*(y_max - y_min)) >> 8));                    \
      }                                                                       \
      else{                                                                   \
        dep_val[j] = y_min;                                                   \
      }                                                                       \
    }                                                                         \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_ND_S16()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_ND_S16(dep_array,num_inputs,start_offset,index,ratio)    \
{                                                                             \
  uint8_t  i,j;                                                            \
  uint32_t dep_idx[MAX_NUMBER_AXISES];                                     \
  int16_t      y_max, y_min;                                                   \
                                                                              \
  for (i=0;i<(1<<((num_inputs)-1));++i){                                      \
    /* get indices into dependent array */                                    \
    dep_idx[i] = (index)[0];                                                  \
    for (j=1;j<(num_inputs);++j){                                             \
      if (i&j){                                                               \
        dep_idx[i] += ((index)[j]+1)*(start_offset)[j-1];                     \
      }                                                                       \
      else{                                                                   \
        dep_idx[i] += ((index)[j])*(start_offset)[j-1];                       \
      }                                                                       \
    }                                                                         \
                                                                              \
    /* dependent data interpolations interpolations */                        \
    y_min = (dep_array)[dep_idx[i]];                                          \
    if ((ratio)[0]){                                                          \
      y_max = (dep_array)[dep_idx[i]+1];                                      \
      dep_val[i] = (int16_t) (y_min +                                          \
                   (((ratio)[0]*(y_max - y_min)) >> 16));                     \
    }                                                                         \
    else{                                                                     \
      dep_val[i] = y_min;                                                     \
    }                                                                         \
  }                                                                           \
                                                                              \
  /* interpolations of interpolations */                                      \
  for (i=1;i<(num_inputs);++i){                                               \
    for (j=0;j<((num_inputs)-i);++j){                                         \
      y_min = dep_val[j<<1];                                                  \
      if ((ratio)[i]){                                                        \
        y_max = dep_val[(j<<1)+1];                                            \
        dep_val[j] = (int16_t) (y_min +                                        \
                     (((ratio)[i]*(y_max - y_min)) >> 16));                   \
      }                                                                       \
      else{                                                                   \
        dep_val[j] = y_min;                                                   \
      }                                                                       \
    }                                                                         \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_ND_U16()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_ND_U16(dep_array,num_inputs,start_offset,index,ratio)    \
{                                                                             \
  uint8_t  i,j;                                                            \
  uint32_t dep_idx[MAX_NUMBER_AXISES];                                     \
  uint16_t y_max, y_min;                                                   \
                                                                              \
  for (i=0;i<(1<<((num_inputs)-1));++i){                                      \
    /* get indices into dependent array */                                    \
    dep_idx[i] = (index)[0];                                                  \
    for (j=1;j<(num_inputs);++j){                                             \
      if (i&j){                                                               \
        dep_idx[i] += ((index)[j]+1)*(start_offset)[j-1];                     \
      }                                                                       \
      else{                                                                   \
        dep_idx[i] += ((index)[j])*(start_offset)[j-1];                       \
      }                                                                       \
    }                                                                         \
                                                                              \
    /* dependent data interpolations interpolations */                        \
    y_min = (dep_array)[dep_idx[i]];                                          \
    if ((ratio)[0]){                                                          \
      y_max = (dep_array)[dep_idx[i]+1];                                      \
      dep_val[i] = (uint16_t) (y_min +                                     \
                   (((ratio)[0]*(y_max - y_min)) >> 16));                     \
    }                                                                         \
    else{                                                                     \
      dep_val[i] = y_min;                                                     \
    }                                                                         \
  }                                                                           \
                                                                              \
  /* interpolations of interpolations */                                      \
  for (i=1;i<(num_inputs);++i){                                               \
    for (j=0;j<((num_inputs)-i);++j){                                         \
      y_min = dep_val[j<<1];                                                  \
      if ((ratio)[i]){                                                        \
        y_max = dep_val[(j<<1)+1];                                            \
        dep_val[j] = (uint16_t) (y_min +                                   \
                     (((ratio)[i]*(y_max - y_min)) >> 16));                   \
      }                                                                       \
      else{                                                                   \
        dep_val[j] = y_min;                                                   \
      }                                                                       \
    }                                                                         \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_ND_S32()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_ND_S32(dep_array,num_inputs,start_offset,index,ratio)    \
{                                                                             \
  uint8_t  i,j;                                                            \
  uint32_t dep_idx[MAX_NUMBER_AXISES];                                     \
  int32_t      y_max, y_min;                                                   \
                                                                              \
  for (i=0;i<(1<<((num_inputs)-1));++i){                                      \
    /* get indices into dependent array */                                    \
    dep_idx[i] = (index)[0];                                                  \
    for (j=1;j<(num_inputs);++j){                                             \
      if (i&j){                                                               \
        dep_idx[i] += ((index)[j]+1)*(start_offset)[j-1];                     \
      }                                                                       \
      else{                                                                   \
        dep_idx[i] += ((index)[j])*(start_offset)[j-1];                       \
      }                                                                       \
    }                                                                         \
                                                                              \
    /* dependent data interpolations interpolations */                        \
    y_min = (dep_array)[dep_idx[i]];                                          \
    if ((ratio)[0]){                                                          \
      y_max = (dep_array)[dep_idx[i]+1];                                      \
      dep_val[i] = (int32_t) (y_min +                                          \
                   ac_map_ratio_multiply_32((ratio)[0],(y_max-y_min)));       \
    }                                                                         \
    else{                                                                     \
      dep_val[i] = y_min;                                                     \
    }                                                                         \
  }                                                                           \
                                                                              \
  /* interpolations of interpolations */                                      \
  for (i=1;i<(num_inputs);++i){                                               \
    for (j=0;j<((num_inputs)-i);++j){                                         \
      y_min = dep_val[j<<1];                                                  \
      if ((ratio)[i]){                                                        \
        y_max = dep_val[(j<<1)+1];                                            \
        dep_val[j] = (int32_t) (y_min +                                        \
                     ac_map_ratio_multiply_32((ratio)[i],(y_max-y_min)));     \
      }                                                                       \
      else{                                                                   \
        dep_val[j] = y_min;                                                   \
      }                                                                       \
    }                                                                         \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_INTERP_LINEAR_ND_U32()

   Description:

******************************************************************************/
#define                                                                       \
AC_MAP_INTERP_LINEAR_ND_U32(dep_array,num_inputs,start_offset,index,ratio)    \
{                                                                             \
  uint8_t  i,j;                                                            \
  uint32_t dep_idx[MAX_NUMBER_AXISES];                                     \
  uint32_t y_max, y_min;                                                   \
                                                                              \
  for (i=0;i<(1<<((num_inputs)-1));++i){                                      \
    /* get indices into dependent array */                                    \
    dep_idx[i] = (index)[0];                                                  \
    for (j=1;j<(num_inputs);++j){                                             \
      if (i&j){                                                               \
        dep_idx[i] += ((index)[j]+1)*(start_offset)[j-1];                     \
      }                                                                       \
      else{                                                                   \
        dep_idx[i] += ((index)[j])*(start_offset)[j-1];                       \
      }                                                                       \
    }                                                                         \
                                                                              \
    /* dependent data interpolations interpolations */                        \
    y_min = (dep_array)[dep_idx[i]];                                          \
    if ((ratio)[0]){                                                          \
      y_max = (dep_array)[dep_idx[i]+1];                                      \
      dep_val[i] = (uint32_t) (y_min +                                     \
                   ac_map_ratio_multiply_32((ratio)[0],(y_max-y_min)));       \
    }                                                                         \
    else{                                                                     \
      dep_val[i] = y_min;                                                     \
    }                                                                         \
  }                                                                           \
                                                                              \
  /* interpolations of interpolations */                                      \
  for (i=1;i<(num_inputs);++i){                                               \
    for (j=0;j<((num_inputs)-i);++j){                                         \
      y_min = dep_val[j<<1];                                                  \
      if ((ratio)[i]){                                                        \
        y_max = dep_val[(j<<1)+1];                                            \
        dep_val[j] = (uint32_t) (y_min +                                   \
                     ac_map_ratio_multiply_32((ratio)[i],(y_max-y_min)));     \
      }                                                                       \
      else{                                                                   \
        dep_val[j] = y_min;                                                   \
      }                                                                       \
    }                                                                         \
  }                                                                           \
}

/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Decla(ratio)ns --
******************************************************************************/

#endif /* AC_MAP_INTERP_ND_MACROS_H_ */

