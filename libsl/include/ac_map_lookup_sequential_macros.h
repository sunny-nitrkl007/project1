#ifndef AC_MAP_LOOKUP_SEQUENTIAL_MACROS_H_
#define AC_MAP_LOOKUP_SEQUENTIAL_MACROS_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains macros which perform sequential lookup (finding the working
point in an independent axis via the sequential search algorithm starting
from a supplied initial index).

FILE NAME : ac_map_lookup_sequential_macros.h
******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include "ac_map_lookup_macros.h"

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
/******************************************************************************
   MACRO: AC_MAP_LOOKUP_SEQUENTIAL()

   Description:
   This macro supports the bisection method of determining a map working point.

   This macro should work on all wordsize targets.

   The following variables must be declared prior to calling this macro but
   do not need to be initialized:
   index
******************************************************************************/
#define AC_MAP_LOOKUP_SEQUENTIAL(val,axis,num_points,past_index,index)        \
{                                                                             \
  /* start search w/ past index */                                            \
  (index) = *(past_index);                                                    \
                                                                              \
  if ((val) <= *(axis)){                                                      \
    (index) = 0;                                                              \
  }                                                                           \
  else if ((val) >= (axis)[--(num_points)]) {                                 \
    (index) = (num_points);                                                   \
  }                                                                           \
  else {                                                                      \
    /* find axis working point */                                             \
    AC_MAP_LOOKUP_SEQUENTIAL_SEARCH((val), (axis), (index));                  \
  }                                                                           \
                                                                              \
  /* save current index for next call */                                      \
  *(past_index) = (index);                                                    \
}


/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_SEQUENTIAL_U8()

   Description:
   Need to adjust this to work on differenent wordsize targets.  Current
   supported target wordsize is 32 bits.

   The following variables must be declared prior to calling this macro but
   do not need to be initialized:
   index, ratio
******************************************************************************/
#define                                                                       \
AC_MAP_LOOKUP_INTERP_SEQUENTIAL_U8(val,axis,num_points,past_index,ratio,index) \
{                                                                             \
  uint8_t p0, p1;                                                          \
                                                                              \
  /* start search w/ past index */                                            \
  (index) = *(past_index);                                                    \
                                                                              \
  if ((val) <= *(axis)){                                                      \
    (index) = 0;                                                              \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else if ((val) >= (axis)[--(num_points)]) {                                 \
    (index) = (num_points);                                                   \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else {                                                                      \
    /* find axis working point */                                             \
    AC_MAP_LOOKUP_SEQUENTIAL_SEARCH((val), (axis), (index));                  \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = (uint8_t) ((((val) - (p0)) << 8)/((p1) - (p0)));            \
  }                                                                           \
                                                                              \
  /* save current index for next call */                                      \
  *(past_index) = (index);                                                    \
}


/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_SEQUENTIAL_S8()

   Description:
   Need to adjust this to work on differenent wordsize targets.  Current
   supported target wordsize is 32 bits.
******************************************************************************/
#define                                                                       \
AC_MAP_LOOKUP_INTERP_SEQUENTIAL_S8(val,axis,num_points,past_index,ratio,index)\
{                                                                             \
  int8_t p0, p1;                                                               \
                                                                              \
  /* start search w/ past index */                                            \
  (index) = *(past_index);                                                    \
                                                                              \
  if ((val) <= *(axis)){                                                      \
    (index) = 0;                                                              \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else if ((val) >= (axis)[--(num_points)]) {                                 \
    (index) = (num_points);                                                   \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else {                                                                      \
    /* find axis working point */                                             \
    AC_MAP_LOOKUP_SEQUENTIAL_SEARCH((val), (axis), (index));                  \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = (uint8_t) ((((val) - (p0)) << 8)/((p1) - (p0)));            \
  }                                                                           \
                                                                              \
  /* save current index for next call */                                      \
  *(past_index) = (index);                                                    \
}


/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_SEQUENTIAL_U16()

   Description:
   Need to adjust this to work on different wordsize targets.  Current
   supported target wordsize is 32 bits.
******************************************************************************/
#define                                                                       \
AC_MAP_LOOKUP_INTERP_SEQUENTIAL_U16(val,axis,num_points,past_index,ratio,index)\
{                                                                             \
  uint16_t p0, p1;                                                         \
                                                                              \
  /* start search w/ past index */                                            \
  (index) = *(past_index);                                                    \
                                                                              \
  if ((val) <= *(axis)){                                                      \
    (index) = 0;                                                              \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else if ((val) >= (axis)[--(num_points)]) {                                 \
    (index) = (num_points);                                                   \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else {                                                                      \
    /* find axis working point */                                             \
    AC_MAP_LOOKUP_SEQUENTIAL_SEARCH((val), (axis), (index));                  \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = (uint16_t) ((((val) - (p0)) << 16)/((p1) - (p0)));          \
  }                                                                           \
                                                                              \
  /* save current index for next call */                                      \
  *(past_index) = (index);                                                    \
}


/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_SEQUENTIAL_S16()

   Description:
   Need to adjust this to work on differenent wordsize targets.  Current
   supported target wordsize is 32 bits.
******************************************************************************/
#define                                                                       \
AC_MAP_LOOKUP_INTERP_SEQUENTIAL_S16(val,axis,num_points,past_index,ratio,index)\
{                                                                             \
  int16_t p0, p1;                                                              \
                                                                              \
  /* start search w/ past index */                                            \
  (index) = *(past_index);                                                    \
                                                                              \
  if ((val) <= *(axis)){                                                      \
    (index) = 0;                                                              \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else if ((val) >= (axis)[--(num_points)]) {                                 \
    (index) = (num_points);                                                   \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else {                                                                      \
    /* find axis working point */                                             \
    AC_MAP_LOOKUP_SEQUENTIAL_SEARCH((val), (axis), (index));                  \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = (uint16_t) ((((val) - (p0)) << 16)/((p1) - (p0)));          \
  }                                                                           \
                                                                              \
  /* save current index for next call */                                      \
  *(past_index) = (index);                                                    \
}


/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_SEQUENTIAL_U32()

   Description:
     uint64 target specific optimization currently turned off because of
     erratic timings measured on A4M1.  Usually faster, but occasionally
     slower than non-64bit implementation.
******************************************************************************/
#if defined(__DCC__) && defined(__ppc) && (0)
#define                                                                      \
AC_MAP_LOOKUP_INTERP_SEQUENTIAL_U32(val,axis,num_points,past_index,ratio,index)\
{                                                                             \
  unsigned long long p0, p1;                                                  \
                                                                              \
  /* start search w/ past index */                                            \
  (index) = *(past_index);                                                    \
                                                                              \
  if ((val) <= *(axis)){                                                      \
    (index) = 0;                                                              \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else if ((val) >= (axis)[--(num_points)]) {                                 \
    (index) = (num_points);                                                   \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else {                                                                      \
    /* find axis working point */                                             \
    AC_MAP_LOOKUP_SEQUENTIAL_SEARCH((val), (axis), (index));                  \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = (((val) - (p0)) << 32)/((p1) - (p0));                          \
  }                                                                           \
                                                                              \
  /* save current index for next call */                                      \
  *(past_index) = (index);                                                    \
}
#else
#define                                                                      \
AC_MAP_LOOKUP_INTERP_SEQUENTIAL_U32(val,axis,num_points,past_index,ratio,index)\
{                                                                             \
  uint32_t p0, p1;                                                         \
                                                                              \
  /* start search w/ past index */                                            \
  (index) = *(past_index);                                                    \
                                                                              \
  if ((val) <= *(axis)){                                                      \
    (index) = 0;                                                              \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else if ((val) >= (axis)[--(num_points)]) {                                 \
    (index) = (num_points);                                                   \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else {                                                                      \
    /* find axis working point */                                             \
    AC_MAP_LOOKUP_SEQUENTIAL_SEARCH((val), (axis), (index));                  \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = ac_map_ratio_divide_u32(((val)-(p0)), ((p1)-(p0)), 32);        \
  }                                                                           \
                                                                              \
  /* save current index for next call */                                      \
  *(past_index) = (index);                                                    \
}
#endif


/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_SEQUENTIAL_S32()

   Description:
     uint64 target specific optimization currently turned off because of
     erratic timings measured on A4M1.  Usually faster, but occasionally
     slower than non-64bit implementation.
******************************************************************************/
#if defined(__DCC__) && defined(__ppc) && (0)
#define                                                                       \
AC_MAP_LOOKUP_INTERP_SEQUENTIAL_S32(val,axis,num_points,past_index,ratio,index)\
{                                                                             \
  signed long long p0, p1;                                                    \
                                                                              \
  /* start search w/ past index */                                            \
  (index) = *(past_index);                                                    \
                                                                              \
  if ((val) <= *(axis)){                                                      \
    (index) = 0;                                                              \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else if ((val) >= (axis)[--(num_points)]) {                                 \
    (index) = (num_points);                                                   \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else {                                                                      \
    /* find axis working point */                                             \
    AC_MAP_LOOKUP_SEQUENTIAL_SEARCH((val), (axis), (index));                  \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = (((val) - (p0)) << 32)/((p1) - (p0));                          \
  }                                                                           \
                                                                              \
  /* save current index for next call */                                      \
  *(past_index) = (index);                                                    \
}
#else
#define                                                                       \
AC_MAP_LOOKUP_INTERP_SEQUENTIAL_S32(val,axis,num_points,past_index,ratio,index)\
{                                                                             \
  int32_t p0, p1;                                                              \
                                                                              \
  /* start search w/ past index */                                            \
  (index) = *(past_index);                                                    \
                                                                              \
  if ((val) <= *(axis)){                                                      \
    (index) = 0;                                                              \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else if ((val) >= (axis)[--(num_points)]) {                                 \
    (index) = (num_points);                                                   \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else {                                                                      \
    /* find axis working point */                                             \
    AC_MAP_LOOKUP_SEQUENTIAL_SEARCH((val), (axis), (index));                  \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = ac_map_ratio_divide_u32(((val)-(p0)), ((p1)-(p0)), 32);        \
  }                                                                           \
                                                                              \
  /* save current index for next call */                                      \
  *(past_index) = (index);                                                    \
}
#endif


/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_SEQUENTIAL_R32()

   Description:
   Need to adjust this to work on differenent wordsize targets.  Current
   supported target wordsize is 32 bits.
******************************************************************************/
#define                                                                       \
AC_MAP_LOOKUP_INTERP_SEQUENTIAL_R32(val,axis,num_points,past_index,ratio,index)\
{                                                                             \
  float p0, p1;                                                             \
                                                                              \
  /* start search w/ past index */                                            \
  (index) = *(past_index);                                                    \
                                                                              \
  if ((val) <= *(axis)){                                                      \
    (index) = 0;                                                              \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else if ((val) >= (axis)[--(num_points)]) {                                 \
    (index) = (num_points);                                                   \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else {                                                                      \
    /* find axis working point */                                             \
    AC_MAP_LOOKUP_SEQUENTIAL_SEARCH((val), (axis), (index));                  \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = ((val) - (p0))/((p1) - (p0));                                  \
  }                                                                           \
                                                                              \
  /* save current index for next call */                                      \
  *(past_index) = (index);                                                    \
}


/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_SEQUENTIAL_R64()

   Description:
   Need to adjust this to work on differenent wordsize targets.  Current
   supported target wordsize is 32 bits.
******************************************************************************/
#define                                                                       \
AC_MAP_LOOKUP_INTERP_SEQUENTIAL_R64(val,axis,num_points,past_index,ratio,index)\
{                                                                             \
  double p0, p1;                                                             \
                                                                              \
  /* start search w/ past index */                                            \
  (index) = *(past_index);                                                    \
                                                                              \
  if ((val) <= *(axis)){                                                      \
    (index) = 0;                                                              \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else if ((val) >= (axis)[--(num_points)]) {                                 \
    (index) = (num_points);                                                   \
    *(ratio) = 0;                                                             \
  }                                                                           \
  else {                                                                      \
    /* find axis working point */                                             \
    AC_MAP_LOOKUP_SEQUENTIAL_SEARCH((val), (axis), (index));                  \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = ((val) - (p0))/((p1) - (p0));                                  \
  }                                                                           \
                                                                              \
  /* save current index for next call */                                      \
  *(past_index) = (index);                                                    \
}
/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/

#endif /* AC_MAP_LOOKUP_SEQUENTIAL_MACROS_H_ */
