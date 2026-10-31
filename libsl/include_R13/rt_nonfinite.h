/*
 * Copyright 1994-2002 The MathWorks, Inc.
 *
 * File: rt_nonfinite.h     $Revision: 1.5 $
 *
 * Abstract:
 *      Real-Time Workshop function to intialize non-finites (inf, nan and -inf).
 */

#ifndef __RTW_NONFINITE__
#define __RTW_NONFINITE__

#include <tmwtypes.h>

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;

extern void rt_InitInfAndNaN(int_T realSize);

#endif
