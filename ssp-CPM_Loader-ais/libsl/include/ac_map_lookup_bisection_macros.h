#ifndef AC_MAP_LOOKUP_BISESCTION_MACROS_H_
#define AC_MAP_LOOKUP_BISESCTION_MACROS_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains macros which perform bisection lookup (finding the working
point in an independent axis via the bisection search algorithm).

FILE NAME : ac_map_lookup_bisection_macros.h
******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include "ac_map_lookup_macros.h"

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
/******************************************************************************
   MACRO: AC_MAP_LOOKUP_BISECTION()

   Description:
   This macro supports the bisection method of determining a map working point.

   This macro should work on all wordsize targets.

   The following variables must be declared prior to calling this macro but
   do not need to be initialized:
   index, mid, hi
******************************************************************************/
#define AC_MAP_LOOKUP_BISECTION(val,axis,num_points,index,mid,hi)             \
{                                                                             \
  if ((val) <= *(axis)){                                                      \
    (index) = 0;                                                              \
  }                                                                           \
  else if ((val) >= (axis)[--(num_points)]) {                                 \
	(index) = (num_points);                                                   \
  }                                                                           \
  else {                                                                      \
    /* find axis working point */                                             \
    (index) = 0;                                                              \
    (hi) = (num_points);                                                      \
    AC_MAP_LOOKUP_BISECTION_SEARCH((val),(axis),(index),(mid),(hi));          \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_BISECTION_U8()

   Description:
   Need to adjust this to work on differenent wordsize targets.  Current
   supported target wordsize is 32 bits.
******************************************************************************/
#define AC_MAP_LOOKUP_INTERP_BISECTION_U8(val,axis,num_points,ratio,index)    \
{                                                                             \
  uint8_t mid, hi;                                                         \
  uint8_t p0, p1;                                                          \
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
    (index) = 0;                                                              \
    (hi) = (num_points);                                                      \
    AC_MAP_LOOKUP_BISECTION_SEARCH((val), (axis), (index), (mid), (hi));      \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = (uint8_t) ((((val) - (p0)) << 8)/((p1) - (p0)));            \
    (*(ratio))++;                                                             \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_BISECTION_S8()

   Description:
   Need to adjust this to work on differenent wordsize targets.
   Current supported target wordsize is 32 bits.
******************************************************************************/
#define AC_MAP_LOOKUP_INTERP_BISECTION_S8(val,axis,num_points,ratio,index)    \
{                                                                             \
  uint8_t mid, hi;                                                         \
  int8_t p0, p1;                                                               \
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
    (index) = 0;                                                              \
    (hi) = (num_points);                                                      \
    AC_MAP_LOOKUP_BISECTION_SEARCH((val), (axis), (index), (mid), (hi));      \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = (uint8_t) ((((val) - (p0)) << 8)/((p1) - (p0)));            \
    (*(ratio))++;                                                             \
  }                                                                           \
}

/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_BISECTION_U16()

   Description:
   Need to adjust this to work on differenent wordsize targets.
   Current supported target wordsize is 32 bits.
******************************************************************************/
#define AC_MAP_LOOKUP_INTERP_BISECTION_U16(val,axis,num_points,ratio,index)   \
{                                                                             \
  uint16_t mid, hi;                                                        \
  uint16_t p0, p1;                                                         \
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
    (index) = 0;                                                              \
    (hi) = (num_points);                                                      \
    AC_MAP_LOOKUP_BISECTION_SEARCH((val), (axis), (index), (mid), (hi));      \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = (uint16_t) ((((val) - (p0)) << 16)/((p1) - (p0)));          \
    (*(ratio))++;                                                             \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_BISECTION_S16()

   Description:
   Need to adjust this to work on differenent wordsize targets.
   Current supported target wordsize is 32 bits.
******************************************************************************/
#define AC_MAP_LOOKUP_INTERP_BISECTION_S16(val,axis,num_points,ratio,index)   \
{                                                                             \
  uint16_t mid, hi;                                                        \
  int16_t p0, p1;                                                              \
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
    (index) = 0;                                                              \
    (hi) = (num_points);                                                      \
    AC_MAP_LOOKUP_BISECTION_SEARCH((val), (axis), (index), (mid), (hi));      \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = (uint16_t) ((((val) - (p0)) << 16)/((p1) - (p0)));          \
    (*(ratio))++;                                                             \
  }                                                                           \
}

/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_BISECTION_U32()

   Description:
   Need to adjust this to work on differenent wordsize targets.
   Current supported target wordsize is 32 bits.
******************************************************************************/
#define AC_MAP_LOOKUP_INTERP_BISECTION_U32(val,axis,num_points,ratio,index)   \
{                                                                             \
  uint32_t mid, hi;                                                        \
  uint32_t p0, p1;                                                         \
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
    (index) = 0;                                                              \
    (hi) = (num_points);                                                      \
    AC_MAP_LOOKUP_BISECTION_SEARCH((val), (axis), (index), (mid), (hi));      \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = ac_map_ratio_divide_u32(((val) - (p0)), ((p1) - (p0)), 32);    \
    (*(ratio))++;                                                             \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_BISECTION_S32()

   Description:
   Need to adjust this to work on differenent wordsize targets.
   Current supported target wordsize is 32 bits.
******************************************************************************/
#define AC_MAP_LOOKUP_INTERP_BISECTION_S32(val,axis,num_points,ratio,index)   \
{                                                                             \
  uint32_t mid, hi;                                                        \
  int32_t p0, p1;                                                              \
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
    (index) = 0;                                                              \
    (hi) = (num_points);                                                      \
    AC_MAP_LOOKUP_BISECTION_SEARCH((val), (axis), (index), (mid), (hi));      \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = ac_map_ratio_divide_u32(((val) - (p0)), ((p1) - (p0)), 32);    \
    (*(ratio))++;                                                             \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_BISECTION_R32()

   Description:
   Need to adjust this to work on differenent wordsize targets.
   Current supported target wordsize is 32 bits.
******************************************************************************/
#define AC_MAP_LOOKUP_INTERP_BISECTION_R32(val,axis,num_points,ratio,index)   \
{                                                                             \
  uint32_t mid, hi;                                                        \
  float     p0, p1;                                                         \
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
    (index) = 0;                                                              \
    (hi) = (num_points);                                                      \
    AC_MAP_LOOKUP_BISECTION_SEARCH((val), (axis), (index), (mid), (hi));      \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = ((val) - (p0))/((p1) - (p0));                                  \
  }                                                                           \
}


/******************************************************************************
   MACRO: AC_MAP_LOOKUP_INTERP_BISECTION_R64()

   Description:
   Need to adjust this to work on differenent wordsize targets.
   Current supported target wordsize is 32 bits.
******************************************************************************/
#define AC_MAP_LOOKUP_INTERP_BISECTION_R64(val,axis,num_points,ratio,index)   \
{                                                                             \
  uint32_t mid, hi;                                                        \
  double     p0, p1;                                                         \
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
    (index) = 0;                                                              \
    (hi) = (num_points);                                                      \
    AC_MAP_LOOKUP_BISECTION_SEARCH((val), (axis), (index), (mid), (hi));      \
                                                                              \
    /* calculate x-ratio */                                                   \
    (axis) += (index);                                                        \
    (p0) = *(axis)++;                                                         \
    (p1) = *(axis);                                                           \
    *(ratio) = ((val) - (p0))/((p1) - (p0));                                  \
  }                                                                           \
}


/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/

#endif /* AC_MAP_LOOKUP_BISESCTION_MACROS_H_ */


