/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: rtwtypes.h
 **
 ** Standard types for code generated from Simulink Coder at Caterpillar
 **
 ** Model version                        : 1.5
 ** Real-Time Workshop file version      : 8.6 (R2014a) 27-Dec-2013
 ** TLC version                          : 8.6 (Jan 30 2014)
 ** CATutils_MatLab version              :
 **
 ******************************************************************************/

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/
#ifndef __RTWTYPES_H__
#define __RTWTYPES_H__

#ifndef RTWTYPES_H
#define RTWTYPES_H

/* Define Simulink Coder replacement data types. */
#include "std_t.h"                     /* User defined replacement datatype for int8_T uint8_T int16_T uint16_T int32_T uint32_T  */

/* zero_crossing_types.h
 *   In R2014b and earlier ZCDirection, ZCSigState, and ZCEventType were
 *   defined by rtwtypes.h.  In R2015a and later, they are defined by
 *   zero_crossing_types.h.  This file is supposed to be common for
 *   R2014a and later, so it must define these types.  To avoid duplicate
 *   definitions, the zero_crossing_types.h generated from R2015a is
 *   unconditionally included here, and the definition that existed was
 *   deleted.
 */
#include <zero_crossing_types.h>

/* Logical type definitions */
#if (!defined(__cplusplus))
#  ifndef false
#   define false                       (0U)
#  endif

#  ifndef true
#   define true                        (1U)
#  endif
#endif


/* This ID is used to detect inclusion of an incompatible rtwtypes.h */
#define RTWTYPES_ID_C08S16I32L32N32F1

#define __TMWTYPES__

/*=======================================================================*
 * Target hardware information
 *   Device type: Freescale->MPC55xx
 *   Number of bits:     char:   8    short:   16    int:  32
 *                       long:  32    long long:  64
 *                       native word size:  32
 *   Byte ordering: BigEndian
 *   Signed integer division rounds to: Zero
 *   Shift right on a signed integer as arithmetic shift: on
 *=======================================================================*/

/*=======================================================================*
 * Fixed width word size data types:                                     *
 *   int8_T, int16_T, int32_T     - signed 8, 16, or 32 bit integers     *
 *   uint8_T, uint16_T, uint32_T  - unsigned 8, 16, or 32 bit integers   *
 *   real32_T, real64_T           - 32 and 64 bit floating point numbers *
 *=======================================================================*/
typedef int8_t int8_T;
typedef uint8_t uint8_T;
typedef int16_t int16_T;
typedef uint16_t uint16_T;
typedef int32_t int32_T;
typedef uint32_t uint32_T;
typedef int64_t int64_T;
typedef uint64_t uint64_T;
typedef float real32_T;
typedef double real64_T;

/*===========================================================================*
 * Generic type definitions: real_T, time_T, boolean_T, int_T, uint_T,       *
 *                           ulong_T, char_T , ulonglong_T and byte_T.       *
 *===========================================================================*/
typedef double real_T;
typedef double time_T;
typedef uint8_t boolean_T;
typedef int32_t int_T;
typedef uint32_t uint_T;
typedef unsigned long ulong_T;
typedef uint64_t ulonglong_T;
typedef char char_T;
typedef uint8_t uchar_T;
typedef char_T byte_T;

/*===========================================================================*
 * Complex number type definitions                                           *
 *===========================================================================*/
#define CREAL_T

typedef struct {
  real32_T re;
  real32_T im;
} creal32_T;

typedef struct {
  real64_T re;
  real64_T im;
} creal64_T;

typedef struct {
  real_T re;
  real_T im;
} creal_T;

#define CINT8_T

typedef struct {
  int8_T re;
  int8_T im;
} cint8_T;

#define CUINT8_T

typedef struct {
  uint8_T re;
  uint8_T im;
} cuint8_T;

#define CINT16_T

typedef struct {
  int16_T re;
  int16_T im;
} cint16_T;

#define CUINT16_T

typedef struct {
  uint16_T re;
  uint16_T im;
} cuint16_T;

#define CINT32_T

typedef struct {
  int32_T re;
  int32_T im;
} cint32_T;

#define CUINT32_T

typedef struct {
  uint32_T re;
  uint32_T im;
} cuint32_T;

#define CINT64_T

typedef struct {
  int64_T re;
  int64_T im;
} cint64_T;

#define CUINT64_T

typedef struct {
  uint64_T re;
  uint64_T im;
} cuint64_T;

/*=======================================================================*
 * Min and Max:                                                          *
 *   int8_T, int16_T, int32_T     - signed 8, 16, or 32 bit integers     *
 *   uint8_T, uint16_T, uint32_T  - unsigned 8, 16, or 32 bit integers   *
 *=======================================================================*/
#define MAX_int8_T    (INT8_MAX)
#define MIN_int8_T    (INT8_MIN)
#define MAX_uint8_T   (UINT8_MAX)
#define MIN_uint8_T   (0U)
#define MAX_int16_T   (INT16_MAX)
#define MIN_int16_T   (INT16_MIN)
#define MAX_uint16_T  (UINT16_MAX)
#define MIN_uint16_T  (0U)
#define MAX_int32_T   (INT32_MAX)
#define MIN_int32_T   (INT32_MIN)
#define MAX_uint32_T  (UINT32_MAX)
#define MIN_uint32_T  (0U)
#define MAX_int64_T   (INT64_MAX)
#define MIN_int64_T   (INT64_MIN)
#define MAX_uint64_T  (UINT64_MAX)
#define MIN_uint64_T  (0U)

/* Block D-Work pointer type */
typedef void * pointer_T;



/* Simulink specific types */

#endif                                 /*   RTWTYPES_H   */
#endif                                 /* __RTWTYPES_H__ */

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
