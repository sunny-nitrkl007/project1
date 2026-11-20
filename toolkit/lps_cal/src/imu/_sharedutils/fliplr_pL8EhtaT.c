/*
 * File: fliplr_pL8EhtaT.c
 *
 * Code generated for Simulink model 'imuCal'.
 *
 * Model version                  : 1.16
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Tue Feb 23 15:12:48 2021
 */

#include "rtwtypes.h"
#include "fliplr_pL8EhtaT.h"

/* Function for MATLAB Function: '<S1>/imuCal' */
void fliplr_pL8EhtaT(real_T x[51])
{
  real_T xtmp;
  int32_T b_j1;
  for (b_j1 = 0; b_j1 < 25; b_j1++) {
    xtmp = x[b_j1];
    x[b_j1] = x[50 - b_j1];
    x[50 - b_j1] = xtmp;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
