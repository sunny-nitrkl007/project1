/*
 * File: polyfit_vO5e321P.c
 *
 * Code generated for Simulink model 'imuCal'.
 *
 * Model version                  : 1.16
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Tue Feb 23 15:12:48 2021
 */

#include "rtwtypes.h"
#include <string.h>
#include "xgeqp3_3UMNqo7x.h"
#include "polyfit_vO5e321P.h"

/* Function for MATLAB Function: '<S1>/imuCal' */
void polyfit_vO5e321P(const real_T x[51], const real32_T y[51], real32_T p[2])
{
  real_T V[102];
  int32_T k;
  real_T tau[2];
  int32_T jpvt[2];
  real32_T B[51];
  real32_T wj;
  for (k = 0; k < 51; k++) {
    V[51 + k] = 1.0;
    V[k] = x[k];
  }

  xgeqp3_3UMNqo7x(V, tau, jpvt);
  p[0] = 0.0F;
  p[1] = 0.0F;
  memcpy(&B[0], &y[0], 51U * sizeof(real32_T));
  if (tau[0] != 0.0) {
    wj = B[0];
    for (k = 1; k + 1 < 52; k++) {
      wj += (real32_T)V[k] * B[k];
    }

    wj *= (real32_T)tau[0];
    if (wj != 0.0F) {
      B[0] -= wj;
      for (k = 1; k + 1 < 52; k++) {
        B[k] -= (real32_T)V[k] * wj;
      }
    }
  }

  if (tau[1] != 0.0) {
    wj = B[1];
    for (k = 2; k + 1 < 52; k++) {
      wj += (real32_T)V[k + 51] * B[k];
    }

    wj *= (real32_T)tau[1];
    if (wj != 0.0F) {
      B[1] -= wj;
      for (k = 2; k + 1 < 52; k++) {
        B[k] -= (real32_T)V[k + 51] * wj;
      }
    }
  }

  p[jpvt[0] - 1] = B[0];
  p[jpvt[1] - 1] = B[1];
  p[jpvt[1] - 1] /= (real32_T)V[52];
  k = 1;
  while (k <= 1) {
    p[jpvt[0] - 1] -= p[jpvt[1] - 1] * (real32_T)V[51];
    k = 2;
  }

  p[jpvt[0] - 1] /= (real32_T)V[0];
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
