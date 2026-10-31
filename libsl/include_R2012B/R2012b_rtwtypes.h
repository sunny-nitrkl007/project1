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

#ifndef TRUE
# define TRUE                          (1U)
#endif

#ifndef FALSE
# define FALSE                         (0U)
#endif

#ifndef __TMWTYPES__
#define __TMWTYPES__
#include <limits.h>

/*=======================================================================*
 * Target hardware information
 *   Device type: Intel->x86-64
 *   Number of bits:     char:   8    short:   16    int:  32
 *                       long:  64
 *                       native word size:  64
 *   Byte ordering: LittleEndian
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
 *                           ulong_T, char_T and byte_T.                     *
 *===========================================================================*/
typedef double real_T;
typedef double time_T;
typedef uint8_t boolean_T;
typedef int32_t int_T;
typedef uint32_t uint_T;
typedef uint64_t ulong_T;
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

#define _CINT8_T

typedef struct {
  int8_T re;
  int8_T im;
} cint8_T;

#define _CUINT8_T

typedef struct {
  uint8_T re;
  uint8_T im;
} cuint8_T;

#define _CINT16_T

typedef struct {
  int16_T re;
  int16_T im;
} cint16_T;

#define _CUINT16_T

typedef struct {
  uint16_T re;
  uint16_T im;
} cuint16_T;

#define _CINT32_T

typedef struct {
  int32_T re;
  int32_T im;
} cint32_T;

#define _CUINT32_T

typedef struct {
  uint32_T re;
  uint32_T im;
} cuint32_T;

#define _CINT64_T

typedef struct {
  int64_T re;
  int64_T im;
} cint64_T;

#define _CUINT64_T

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

/* Logical type definitions */
#if (!defined(__cplusplus)) && (!defined(__true_false_are_keywords))
#  ifndef false
#   define false                       (0U)
#  endif

#  ifndef true
#   define true                        (1U)
#  endif
#endif

/*
 * Simulink Coder assumes the code is compiled on a target using a 2's complement representation
 * for signed integer values.
 */
#if ((SCHAR_MIN + 1) != -SCHAR_MAX)
#error "This code must be compiled using a 2's complement representation for signed integer values"
#endif

/* This ID is used to detect inclusion of an incompatible rtwtypes.h */
#define RTWTYPES_ID_C08S16I32L64N64F1
#define RTWTYPES_ID_C08S16I32L64N64F0
#else                                  /* __TMWTYPES__ */
#define TMWTYPES_PREVIOUSLY_INCLUDED
#endif                                 /* __TMWTYPES__ */

/* Block D-Work pointer type */
typedef void * pointer_T;



/* Simulink specific types */
#ifndef __SIMSTRUC_TYPES_H__
#define __SIMSTRUC_TYPES_H__

/* Include guard from R2016a's zero_crossing_types.h */
#ifndef __ZERO_CROSSING_TYPES_H__
#define __ZERO_CROSSING_TYPES_H__

/* Trigger directions: falling, either, and rising */
typedef enum {
  FALLING_ZERO_CROSSING = -1,
  ANY_ZERO_CROSSING = 0,
  RISING_ZERO_CROSSING = 1
} ZCDirection;

/* Previous state of a trigger signal */
typedef uint8_T ZCSigState;

/* Initial value of a trigger zero crossing signal */
#define UNINITIALIZED_ZCSIG            0x03U
#define NEG_ZCSIG                      0x02U
#define POS_ZCSIG                      0x01U
#define ZERO_ZCSIG                     0x00U

/* Current state of a trigger signal */
typedef enum {
  FALLING_ZCEVENT = -1,
  NO_ZCEVENT = 0,
  RISING_ZCEVENT = 1
} ZCEventType;

#endif                                 /* __ZERO_CROSSING_TYPES_H__ */
#endif                                 /* __SIMSTRUC_TYPES_H__ */
#endif /* RTWTYPES_H */
#endif /* __RTWTYPES_H__ */


/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
