/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: rt_nonfinite.c
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
/*
 * Abstract:
 *      Function to intialize non-finites,
 *      (Inf, NaN and -Inf).
 */
#include "R2012b_rt_nonfinite.h"
#include "R2012b_rtGetNaN.h"
#include "R2012b_rtGetInf.h"

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/
real_T R2012b_rtInf;
real_T R2012b_rtMinusInf;
real_T R2012b_rtNan;
real32_T R2012b_rtInfF;
real32_T R2012b_rtMinusInfF;
real32_T R2012b_rtNaNF;

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/

/*
 * Initialize the R2012b_rtInf, R2012b_rtMinusInf, and R2012b_rtNan needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
void R2012b_rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  R2012b_rtNan = R2012b_rtGetNaN();
  R2012b_rtNaNF = R2012b_rtGetNaNF();
  R2012b_rtInf = R2012b_rtGetInf();
  R2012b_rtInfF = R2012b_rtGetInfF();
  R2012b_rtMinusInf = R2012b_rtGetMinusInf();
  R2012b_rtMinusInfF = R2012b_rtGetMinusInfF();
}

/* Test if value is infinite */
boolean_T R2012b_rtIsInf(real_T value)
{
  return (boolean_T)((value==R2012b_rtInf || value==R2012b_rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
boolean_T R2012b_rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==R2012b_rtInfF || (value)==R2012b_rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
boolean_T R2012b_rtIsNaN(real_T value)
{
  return (boolean_T)((value!=value) ? 1U : 0U);
}

/* Test if single-precision value is not a number */
boolean_T R2012b_rtIsNaNF(real32_T value)
{
  return (boolean_T)(((value!=value) ? 1U : 0U));
}
