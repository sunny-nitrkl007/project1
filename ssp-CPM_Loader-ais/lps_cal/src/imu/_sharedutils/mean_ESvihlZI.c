/*
 * File: mean_ESvihlZI.c
 *
 * Code generated for Simulink model 'imuCal'.
 *
 * Model version                  : 1.16
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Tue Feb 23 15:12:48 2021
 */

#include "rtwtypes.h"
#include "mean_ESvihlZI.h"

/* Function for MATLAB Function: '<S1>/imuCal' */
real32_T mean_ESvihlZI(const real32_T x[51])
{
  real32_T b_y;
  int32_T k;
  b_y = x[0];
  for (k = 0; k < 50; k++) {
    b_y += x[k + 1];
  }

  return b_y / 51.0F;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
