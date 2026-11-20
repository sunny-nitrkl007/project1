/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: rt_nonfinite.h
 **
 ** Real-Time Workshop code generated for Simulink model LIBINFO_WL_00.
 **
 ** Model version                        : 1.118
 ** Real-Time Workshop file version      : 8.3 (R2012b) 20-Jul-2012
 ** TLC version                          : 8.3 (Jul 21 2012)
 ** CATutils_MatLab version              : CATUTILS_MATLAB_4.3.3
 **
 ******************************************************************************/

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#ifndef RTW_HEADER_rt_nonfinite_h_
#define RTW_HEADER_rt_nonfinite_h_
#include <stddef.h>
#include "R2012b_rtwtypes.h"

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/
extern real_T R2012b_rtInf;
extern real_T R2012b_rtMinusInf;
extern real_T R2012b_rtNan;
extern real32_T R2012b_rtInfF;
extern real32_T R2012b_rtMinusInfF;
extern real32_T R2012b_rtNaNF;
extern void R2012b_rt_InitInfAndNaN(size_t realSize);
extern boolean_T R2012b_rtIsInf(real_T value);
extern boolean_T R2012b_rtIsInfF(real32_T value);
extern boolean_T R2012b_rtIsNaN(real_T value);
extern boolean_T R2012b_rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
#endif                                 /* RTW_HEADER_rt_nonfinite_h_ */
