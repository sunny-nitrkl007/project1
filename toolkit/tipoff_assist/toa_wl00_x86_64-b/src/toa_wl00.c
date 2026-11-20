/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: toa_wl00.c
 **
 ** Real-Time Workshop code generated for Simulink model toa_wl00.
 **
 ** Model version                        : 1.44
 ** Real-Time Workshop file version      : 8.13 (R2017b) 24-Jul-2017
 ** TLC version                          : 8.13 (Jul 25 2017)
 ** CATutils_MatLab version              : CATUTILS_MATLAB_4.6.1
 **
 ******************************************************************************/

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#include "toa_wl00.h"
#include "toa_wl00_private.h"
#include "rt_atan2f_snf.h"

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/* Forward declaration for local functions */
static void toa_wl00_updateFilter(real32_T rtu_raw, real32_T *rty_filtered,
  rtDW_Filter_toa_wl00 *localDW);
static void toa_wl00_initFilter(real32_T rtu_raw, real32_T rtu_ts, real32_T
  rtu_cf, real32_T *rty_filtered, rtDW_Filter_toa_wl00 *localDW);

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/

/*
 * Output and update for atomic system:
 *    '<S142>/MATLAB Function'
 *    '<S142>/MATLAB Function1'
 *    '<S142>/MATLAB Function2'
 *    '<S143>/MATLAB Function1'
 *    '<S221>/MATLAB Function1'
 *    '<S222>/MATLAB Function1'
 */
void toa_wl00_MATLABFunction(real_T rtu_timestep, real_T
  rtu_lowPassFilterCutoffHz, real_T *rty_lowPassFilterFactor)
{
  real_T angle;
  real_T tmp;

  /*  Low-pass filter cutoff (rad/s) */
  /* MATLAB Function 'MATLAB Function': '<S148>:1' */
  /* '<S148>:1:4' cutoff = lowPassFilterCutoffHz * (2 * pi); */
  /*  Low-pass filter angle (rad) */
  /* '<S148>:1:6' angle = cutoff * timestep; */
  angle = (rtu_lowPassFilterCutoffHz * 6.2831853071795862) * rtu_timestep;

  /*  Filter factor corresponding to cutoff */
  /* '<S148>:1:8' lowPassFilterFactor = ... */
  /* '<S148>:1:9'     (cos(angle) - 1) + sqrt((cos(angle) - 3) * (cos(angle) - 1)); */
  tmp = cos(angle);
  *rty_lowPassFilterFactor = sqrt((tmp - 3.0) * (tmp - 1.0)) + (cos(angle) - 1.0);
}

/* Function for Chart: '<S157>/Filter' */
static void toa_wl00_updateFilter(real32_T rtu_raw, real32_T *rty_filtered,
  rtDW_Filter_toa_wl00 *localDW)
{
  /* Graphical Function 'updateFilter': '<S160>:19' */
  /* Transition: '<S160>:28' */
  localDW->rawHist[2] = localDW->rawHist[1];
  localDW->rawHist[1] = localDW->rawHist[0];
  localDW->rawHist[0] = rtu_raw;

  /* Transition: '<S160>:31' */
  localDW->filtHist[2] = localDW->filtHist[1];
  localDW->filtHist[1] = localDW->filtHist[0];
  localDW->filtHist[0] = ((((localDW->rawHist[0] + localDW->rawHist[2]) -
    localDW->filtHist[2]) * localDW->alpha) + ((localDW->rawHist[1] -
    localDW->filtHist[1]) * localDW->beta)) + (localDW->gamma *
    localDW->filtHist[2]);

  /* Transition: '<S160>:39' */
  *rty_filtered = localDW->filtHist[0];
}

/* Function for Chart: '<S157>/Filter' */
static void toa_wl00_initFilter(real32_T rtu_raw, real32_T rtu_ts, real32_T
  rtu_cf, real32_T *rty_filtered, rtDW_Filter_toa_wl00 *localDW)
{
  real32_T q;
  real32_T r;
  real32_T t;

  /* Graphical Function 'initFilter': '<S160>:18' */
  /* Transition: '<S160>:20' */
  q = (((rtu_cf * rtu_cf) * rtu_ts) * rtu_ts) / 4.0F;
  r = rtu_cf * rtu_ts;
  t = (1.0F + q) + r;
  localDW->alpha = (1.0F + q) / t;
  localDW->beta = ((q - 1.0F) * 2.0F) / t;
  localDW->gamma = r / t;

  /* Transition: '<S160>:33' */
  localDW->rawHist[0] = rtu_raw;
  localDW->rawHist[1] = rtu_raw;
  localDW->rawHist[2] = rtu_raw;

  /* Transition: '<S160>:35' */
  localDW->filtHist[0] = rtu_raw;
  localDW->filtHist[1] = rtu_raw;
  localDW->filtHist[2] = rtu_raw;

  /* Transition: '<S160>:37' */
  *rty_filtered = localDW->filtHist[0];
}

/*
 * System initialize for atomic system:
 *    '<S157>/Filter'
 *    '<S158>/Filter'
 *    '<S159>/Filter'
 *    '<S237>/Filter'
 *    '<S238>/Filter'
 *    '<S239>/Filter'
 *    '<S243>/Filter'
 *    '<S244>/Filter'
 *    '<S245>/Filter'
 */
void toa_wl00_Filter_Init(real32_T *rty_filtered, rtDW_Filter_toa_wl00 *localDW)
{
  localDW->is_active_c24_tip_assist_lib_support = 0U;
  localDW->rawHist[0] = 0.0F;
  localDW->filtHist[0] = 0.0F;
  localDW->rawHist[1] = 0.0F;
  localDW->filtHist[1] = 0.0F;
  localDW->rawHist[2] = 0.0F;
  localDW->filtHist[2] = 0.0F;
  localDW->alpha = 0.0F;
  localDW->beta = 0.0F;
  localDW->gamma = 0.0F;
  *rty_filtered = 0.0F;
}

/*
 * Output and update for atomic system:
 *    '<S157>/Filter'
 *    '<S158>/Filter'
 *    '<S159>/Filter'
 *    '<S237>/Filter'
 *    '<S238>/Filter'
 *    '<S239>/Filter'
 *    '<S243>/Filter'
 *    '<S244>/Filter'
 *    '<S245>/Filter'
 */
void toa_wl00_Filter(real32_T rtu_raw, boolean_T rtu_reset, real32_T rtu_ts,
                     real32_T rtu_cf, real32_T *rty_filtered,
                     rtDW_Filter_toa_wl00 *localDW)
{
  /* Chart: '<S157>/Filter' */
  /* Gateway: Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Notch filter/NotchFilter/Filter */
  /* During: Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Notch filter/NotchFilter/Filter */
  if (localDW->is_active_c24_tip_assist_lib_support == 0U) {
    /* Entry: Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Notch filter/NotchFilter/Filter */
    localDW->is_active_c24_tip_assist_lib_support = 1U;

    /* Entry Internal: Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Notch filter/NotchFilter/Filter */
    /* Transition: '<S160>:12' */
    /* Transition: '<S160>:14' */
    toa_wl00_initFilter(rtu_raw, rtu_ts, rtu_cf, rty_filtered, localDW);
  } else {
    /* During 'Update': '<S160>:11' */
    if (rtu_reset) {
      /* Transition: '<S160>:17' */
      /* Transition: '<S160>:14' */
      toa_wl00_initFilter(rtu_raw, rtu_ts, rtu_cf, rty_filtered, localDW);
    } else {
      toa_wl00_updateFilter(rtu_raw, rty_filtered, localDW);
    }
  }

  /* End of Chart: '<S157>/Filter' */
}

/*
 * System initialize for atomic system:
 *    '<S221>/MATLAB Function'
 *    '<S222>/MATLAB Function'
 */
void toa_wl00_MATLABFunction_nat1_Init(rtDW_MATLABFunction_toa_wl00_flu5
  *localDW)
{
  localDW->lastMeanEst_not_empty = false;
}

/*
 * Output and update for atomic system:
 *    '<S221>/MATLAB Function'
 *    '<S222>/MATLAB Function'
 */
void toa_wl00_MATLABFunction_fw1r(real32_T rtu_newSample, real_T
  rtu_filterFactor, boolean_T rtu_reset, real32_T rtu_resetVariance, real32_T
  *rty_meanEst, real32_T *rty_stdevEst, rtDW_MATLABFunction_toa_wl00_flu5
  *localDW)
{
  real32_T meanEst;
  real32_T varianceEst_tmp;

  /*  Implements a running mean and standard deviation estimate. */
  /*  Formula from: */
  /*    Estimation of Variance by a Recursive Equation */
  /*    by M. Melvin Bruce, October 1969, Langley Research Center (NASA) */
  /*  Adapted from PCS's pcs_io.c file. */
  /* MATLAB Function 'Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Statistics Estimation1/MATLAB Function': '<S284>:1' */
  /*  Init to a high variance to ensure confidence is initially low. */
  /*  Init to a high mean so the true value is always approached from above, */
  /*  which will ensure a non-warmed-up filter errs high, which will cause */
  /*  Tip-Off Assist to err low to prevent truck overload. */
  /* '<S284>:1:14' if isempty(lastMeanEst) || reset */
  if ((!localDW->lastMeanEst_not_empty) || rtu_reset) {
    /* '<S284>:1:15' lastMeanEst = single(resetSample); */
    localDW->lastMeanEst = rtu_newSample;
    localDW->lastMeanEst_not_empty = true;

    /* '<S284>:1:16' lastVarianceEst = single(resetVariance); */
    localDW->lastVarianceEst = rtu_resetVariance;
  }

  /* '<S284>:1:19' A = 1 - filterFactor; */
  /*  "A" from the NASA paper */
  /* '<S284>:1:20' meanEst = A * lastMeanEst + (1.0 - A) * newSample; */
  meanEst = (((real32_T)(1.0 - (1.0 - rtu_filterFactor))) * rtu_newSample) +
    (((real32_T)(1.0 - rtu_filterFactor)) * localDW->lastMeanEst);

  /* '<S284>:1:21' varianceEst = A * lastVarianceEst + (1.0 - A) * (1.0 + A) * (newSample - lastMeanEst) * (newSample - lastMeanEst) / 2.0; */
  varianceEst_tmp = rtu_newSample - localDW->lastMeanEst;
  localDW->lastVarianceEst = (((((real32_T)((1.0 - (1.0 - rtu_filterFactor)) *
    ((1.0 - rtu_filterFactor) + 1.0))) * varianceEst_tmp) * varianceEst_tmp) /
    2.0F) + (((real32_T)(1.0 - rtu_filterFactor)) * localDW->lastVarianceEst);

  /* '<S284>:1:22' stdevEst = sqrt(varianceEst); */
  /*  For next time... */
  /* '<S284>:1:25' lastMeanEst = meanEst; */
  localDW->lastMeanEst = meanEst;

  /* '<S284>:1:26' lastVarianceEst = varianceEst; */
  *rty_meanEst = meanEst;
  *rty_stdevEst = sqrtf(localDW->lastVarianceEst);
}

/*
 * Output and update for atomic system:
 *    '<S221>/Two Sided St. Dev. from Bound'
 *    '<S222>/Two Sided St. Dev. from Bound'
 */
void toa_wl00_TwoSidedStDevfromBound(real32_T rtu_confidence, real32_T rtu_bound,
  real32_T *rty_stdev)
{
  real32_T stdev_ratio;
  int32_t low_i;
  int32_t low_ip1;
  int32_t high_i;
  int32_t mid_i;
  static const real_T b[17] = { 0.0, 0.235822844, 0.382924922, 0.516072694,
    0.631879747, 0.728667676, 0.806398927, 0.866385543, 0.910869057, 0.942566872,
    0.964271153, 0.978551778, 0.987580668, 0.993066052, 0.997300204, 0.999534742,
    1.0 };

  static const real_T c[17] = { 0.0, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9,
    2.1, 2.3, 2.5, 2.7, 3.0, 3.5, 4.0 };

  /*  Calculates the st. dev. of a confidence interval in terms of half its width. */
  /*  */
  /*  Inputs: */
  /*    confidence */
  /*    Confidence that the input bound will enclose the true value. */
  /*    bound */
  /*    Bound of the confidence interval, expressed in the same units as stdev. */
  /*     */
  /*    For lower bound, the true value will lie above the mean minus this */
  /*    value. */
  /*    The opposite is true for an upper bound. */
  /*    Potential units for the arguments are percent of rated payload or */
  /*    payload. */
  /*  Outputs: */
  /*    stdev */
  /*    The standard deviation, expressed in the same units as */
  /*    bound, that corresponds to the given bound. Can be thought of as */
  /*    describing the scale of the normal distribution whose confidence */
  /*    interval with given bounds results in the given confidence. */
  /*  Inspired from pcs_calculate_confidence() in pcs_io.c */
  /* MATLAB Function 'Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Statistics Estimation1/Two Sided St. Dev. from Bound': '<S286>:1' */
  /*  Table of confidence vs two-sided confidence interval bound. */
  /*  Units of confidence decimal percent and the ratio of standard */
  /*  deviation of a standard normal distribution. */
  /* '<S286>:1:30' xConfidenceTwoSided = [ 0.0, 0.235822844, 0.382924922, 0.516072694, 0.631879747, 0.728667676, 0.806398927, 0.866385543, 0.910869057, 0.942566872, 0.964271153, 0.978551778, 0.987580668, 0.993066052, 0.997300204, 0.999534742, 1.0 ]; */
  /* '<S286>:1:31' yStdevRatio = [ 0.0, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9, 2.1, 2.3, 2.5, 2.7, 3.0, 3.5, 4.0 ]; */
  /* '<S286>:1:32' stdev_ratio = interp1(xConfidenceTwoSided, yStdevRatio, confidence); */
  stdev_ratio = (rtNaNF);
  if ((!rtIsNaNF(rtu_confidence)) && (!((rtu_confidence > 1.0F) ||
        (rtu_confidence < 0.0F)))) {
    low_i = 0;
    low_ip1 = 2;
    high_i = 17;
    while (high_i > low_ip1) {
      mid_i = (((low_i + high_i) + 1) >> 1);
      if (rtu_confidence >= b[mid_i - 1]) {
        low_i = mid_i - 1;
        low_ip1 = mid_i + 1;
      } else {
        high_i = mid_i;
      }
    }

    stdev_ratio = (rtu_confidence - ((real32_T)b[low_i])) / ((real32_T)(b[low_i
      + 1] - b[low_i]));
    if (stdev_ratio == 0.0F) {
      stdev_ratio = (real32_T)c[low_i];
    } else if (stdev_ratio == 1.0F) {
      stdev_ratio = (real32_T)c[low_i + 1];
    } else if (c[low_i + 1] == c[low_i]) {
      stdev_ratio = (real32_T)c[low_i];
    } else {
      stdev_ratio = ((1.0F - stdev_ratio) * ((real32_T)c[low_i])) + (((real32_T)
        c[low_i + 1]) * stdev_ratio);
    }
  }

  /* '<S286>:1:33' stdev = bound / stdev_ratio; */
  *rty_stdev = rtu_bound / stdev_ratio;
}

/*
 * Output and update for atomic system:
 *    '<S227>/One Sided Confidence Limit'
 *    '<S228>/One Sided Confidence Limit'
 *    '<S229>/One Sided Confidence Limit'
 */
void toa_wl00_OneSidedConfidenceLimit(real_T rtu_confidence, real32_T rtu_stdev,
  real32_T *rty_bound)
{
  real_T stdev_ratio;
  int32_t low_i;
  int32_t low_ip1;
  int32_t high_i;
  int32_t mid_i;
  static const real_T b[17] = { 0.5, 0.617911422, 0.691462461, 0.758036347,
    0.8159398735, 0.864333838, 0.9031994635, 0.9331927715, 0.9554345285,
    0.971283436, 0.9821355765, 0.989275889, 0.993790334, 0.996533026,
    0.998650102, 0.999767371, 1.0 };

  static const real_T c[17] = { 0.0, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9,
    2.1, 2.3, 2.5, 2.7, 3.0, 3.5, 4.0 };

  /*  Calculates the size of a confidence interval in terms of half its width. */
  /*  */
  /*  Inputs: */
  /*    confidence */
  /*    Confidence that the resulting bound will enclose the true value. */
  /*    stdev */
  /*    The observed standard deviation, expressed in the same units as */
  /*    bound. Can be thought of as defining the scale of the normal */
  /*    distribution that we are assuming represents the data we are sampling. */
  /*    Potential units for the arguments are percent of rated payload or */
  /*    payload. */
  /*  Outputs: */
  /*    bound */
  /*    Bound of the confidence interval, expressed in the same units as stdev. */
  /*     */
  /*    For lower bound, the true value will lie above the mean minus this */
  /*    value. */
  /*    The opposite is true for an upper bound. */
  /*  Inspired from pcs_calculate_confidence() in pcs_io.c */
  /* MATLAB Function 'Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Weighing Statistics, No Notch, No Latch/One Sided Confidence Limit': '<S292>:1' */
  /*  Table of confidence vs one-sided confidence interval bound. */
  /*  Units of confidence decimal percent and the ratio of standard */
  /*  deviation of a standard normal distribution. */
  /* '<S292>:1:29' xConfidenceOneSided = [0.500000000000000,0.617911422000000,0.691462461000000,0.758036347000000,0.815939873500000,0.864333838000000,0.903199463500000,0.933192771500000,0.955434528500000,0.971283436000000,0.982135576500000,0.989275889000000,0.993790334000000,0.996533026000000,0.998650102000000,0.999767371000000,1]; */
  /* '<S292>:1:30' yStdevRatio = [ 0.0, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9, 2.1, 2.3, 2.5, 2.7, 3.0, 3.5, 4.0 ]; */
  /* '<S292>:1:31' stdev_ratio = interp1(xConfidenceOneSided, yStdevRatio, confidence); */
  stdev_ratio = (rtNaN);
  if ((!rtIsNaN(rtu_confidence)) && (!((rtu_confidence > 1.0) || (rtu_confidence
         < 0.5)))) {
    low_i = 0;
    low_ip1 = 2;
    high_i = 17;
    while (high_i > low_ip1) {
      mid_i = (((low_i + high_i) + 1) >> 1);
      if (rtu_confidence >= b[mid_i - 1]) {
        low_i = mid_i - 1;
        low_ip1 = mid_i + 1;
      } else {
        high_i = mid_i;
      }
    }

    stdev_ratio = (rtu_confidence - b[low_i]) / (b[low_i + 1] - b[low_i]);
    if (stdev_ratio == 0.0) {
      stdev_ratio = c[low_i];
    } else if (stdev_ratio == 1.0) {
      stdev_ratio = c[low_i + 1];
    } else if (c[low_i + 1] == c[low_i]) {
      stdev_ratio = c[low_i];
    } else {
      stdev_ratio = ((1.0 - stdev_ratio) * c[low_i]) + (c[low_i + 1] *
        stdev_ratio);
    }
  }

  /* '<S292>:1:32' bound = stdev_ratio * stdev; */
  *rty_bound = ((real32_T)stdev_ratio) * rtu_stdev;
}

/*
 * Output and update for atomic system:
 *    '<S227>/Two Sided Confidence Limit'
 *    '<S228>/Two Sided Confidence Limit'
 *    '<S229>/Two Sided Confidence Limit'
 */
void toa_wl00_TwoSidedConfidenceLimit(real_T rtu_confidence, real32_T rtu_stdev,
  real32_T *rty_bound)
{
  real_T stdev_ratio;
  int32_t low_i;
  int32_t low_ip1;
  int32_t high_i;
  int32_t mid_i;
  static const real_T b[17] = { 0.0, 0.235822844, 0.382924922, 0.516072694,
    0.631879747, 0.728667676, 0.806398927, 0.866385543, 0.910869057, 0.942566872,
    0.964271153, 0.978551778, 0.987580668, 0.993066052, 0.997300204, 0.999534742,
    1.0 };

  static const real_T c[17] = { 0.0, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9,
    2.1, 2.3, 2.5, 2.7, 3.0, 3.5, 4.0 };

  /*  Calculates the size of a confidence interval in terms of half its width. */
  /*  */
  /*  Inputs: */
  /*    confidence */
  /*    Confidence that the resulting bound will enclose the true value. */
  /*    stdev */
  /*    The observed standard deviation, expressed in the same units as */
  /*    bound. Can be thought of as defining the scale of the normal */
  /*    distribution that we are assuming represents the data we are sampling. */
  /*    Potential units for the arguments are percent of rated payload or */
  /*    payload. */
  /*  Outputs: */
  /*    bound */
  /*    Bound of the confidence interval, expressed in the same units as stdev. */
  /*     */
  /*    For lower bound, the true value will lie above the mean minus this */
  /*    value. */
  /*    The opposite is true for an upper bound. */
  /*  Inspired from pcs_calculate_confidence() in pcs_io.c */
  /* MATLAB Function 'Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Weighing Statistics, No Notch, No Latch/Two Sided Confidence Limit': '<S293>:1' */
  /*  Table of confidence vs two-sided confidence interval bound. */
  /*  Units of confidence decimal percent and the ratio of standard */
  /*  deviation of a standard normal distribution. */
  /* '<S293>:1:29' xConfidenceTwoSided = [ 0.0, 0.235822844, 0.382924922, 0.516072694, 0.631879747, 0.728667676, 0.806398927, 0.866385543, 0.910869057, 0.942566872, 0.964271153, 0.978551778, 0.987580668, 0.993066052, 0.997300204, 0.999534742, 1.0 ]; */
  /* '<S293>:1:30' yStdevRatio = [ 0.0, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9, 2.1, 2.3, 2.5, 2.7, 3.0, 3.5, 4.0 ]; */
  /* '<S293>:1:31' stdev_ratio = interp1(xConfidenceTwoSided, yStdevRatio, confidence); */
  stdev_ratio = (rtNaN);
  if ((!rtIsNaN(rtu_confidence)) && (!((rtu_confidence > 1.0) || (rtu_confidence
         < 0.0)))) {
    low_i = 0;
    low_ip1 = 2;
    high_i = 17;
    while (high_i > low_ip1) {
      mid_i = (((low_i + high_i) + 1) >> 1);
      if (rtu_confidence >= b[mid_i - 1]) {
        low_i = mid_i - 1;
        low_ip1 = mid_i + 1;
      } else {
        high_i = mid_i;
      }
    }

    stdev_ratio = (rtu_confidence - b[low_i]) / (b[low_i + 1] - b[low_i]);
    if (stdev_ratio == 0.0) {
      stdev_ratio = c[low_i];
    } else if (stdev_ratio == 1.0) {
      stdev_ratio = c[low_i + 1];
    } else if (c[low_i + 1] == c[low_i]) {
      stdev_ratio = c[low_i];
    } else {
      stdev_ratio = ((1.0 - stdev_ratio) * c[low_i]) + (c[low_i + 1] *
        stdev_ratio);
    }
  }

  /* '<S293>:1:32' bound = stdev_ratio * stdev; */
  *rty_bound = ((real32_T)stdev_ratio) * rtu_stdev;
}

/* Model step function */
void toa_wl00_step(RT_MODEL_toa_wl00 *const toa_wl00_M, boolean_T
                   toa_wl00_U_Invalidate_Outputs, real32_T
                   toa_wl00_U_Lift_Valve_Command, real32_T
                   toa_wl00_U_Tilt_Valve_Command, real32_T
                   toa_wl00_U_Tilt_Extension, real32_T toa_wl00_U_Lift_Angle,
                   real32_T toa_wl00_U_Lift_HE_Pressure, real32_T
                   toa_wl00_U_Lift_RE_Pressure, real32_T
                   toa_wl00_U_Tilt_HE_Pressure, real32_T
                   toa_wl00_U_Tilt_RE_Pressure, real32_T
                   toa_wl00_U_Steering_Angle, real32_T toa_wl00_U_Tool_Mass,
                   real32_T toa_wl00_U_PCS_Truck_Target, real32_T
                   toa_wl00_U_PCS_Truck_Start_Weight, uint8_t
                   toa_wl00_U_PCS_Bucket_Current_Weight_Accuracy, real32_T
                   toa_wl00_U_PCS_Bucket_Current_Weight, uint8_t
                   toa_wl00_U_PCS_Tipoff_Mode, real32_T
                   toa_wl00_U_EEF_IMU_AccelX, real32_T toa_wl00_U_EEF_IMU_AccelY,
                   real32_T toa_wl00_U_EEF_IMU_AccelZ, real32_T
                   toa_wl00_U_Zero_Offset, real32_T toa_wl00_U_Simple_Cal_Factor,
                   real32_T toa_wl00_U_IMU_Pitch_Cal, real32_T
                   toa_wl00_U_Bucket_Angle, boolean_T toa_wl00_U_Unlatch_Trigger,
                   real32_T toa_wl00_U_Anchor_Zero_Offset, real32_T
                   toa_wl00_U_Anchor_Factor, uint16_t toa_wl00_U_CPM_Pass_Count,
                   real32_T toa_wl00_U_Lift_Norm_Angle, real32_T
                   toa_wl00_U_Lift_Norm_Length, real32_T
                   toa_wl00_U_Tilt_Norm_Angle, real32_T
                   toa_wl00_U_Tilt_Norm_Length, real32_T toa_wl00_U_Friction_Mu,
                   real32_T toa_wl00_U_Friction_Offset, real32_T
                   *toa_wl00_Y_Tilt_Sensitivity, real32_T
                   *toa_wl00_Y_Tilt_HE_Pressure_Out, real32_T
                   *toa_wl00_Y_Arbitrated_Payload_Norm_Error, uint8_t
                   *toa_wl00_Y_Weigh_Status, real32_T
                   *toa_wl00_Y_Payload_Norm_Stdev, uint8_t
                   *toa_wl00_Y_PCS_Bucket_Current_Weight_Accuracy_Out, real32_T *
                   toa_wl00_Y_PCS_Bucket_Current_Weight_Norm_Error_Out, uint8_t *
                   toa_wl00_Y_Tipoff_Assist_Adv_Error_Code, real32_T
                   *toa_wl00_Y_Spill_Rate_Norm, real32_T
                   *toa_wl00_Y_Bucket_Payload_Target, real32_T
                   *toa_wl00_Y_Payload_Send_To_CPM, uint8_t
                   *toa_wl00_Y_Payload_Status_Send_To_CPM, real32_T
                   *toa_wl00_Y_Unsecured_Payload_Upper_Bound_Norm, real32_T
                   *toa_wl00_Y_Unsecured_Payload_Lower_Bound_Norm, uint8_t
                   *toa_wl00_Y_Unsecured_PFW_Status, real32_T
                   *toa_wl00_Y_Min_Secure_Bucket_Angle)
{
  BlockIO_toa_wl00 *toa_wl00_B = ((BlockIO_toa_wl00 *) toa_wl00_M->blockIO);
  D_Work_toa_wl00 *toa_wl00_DWork = ((D_Work_toa_wl00 *) toa_wl00_M->dwork);

  /* local block i/o variables */
  uint16_t rtb_QuerySampleTime;
  uint16_t rtb_QuerySampleTime_i540;
  uint16_t rtb_QuerySampleTime_h1dv;
  boolean_T rtb_LogicalOperator_fcyj;
  int8_t I[9];
  static const int8_t b[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  static const int8_t c[9] = { 0, 0, -1, 0, 0, 0, 1, 0, 0 };

  static const int8_t d[9] = { 0, 0, 0, 0, 1, 0, 0, 0, 0 };

  real32_T cpNorm;
  real32_T t;
  static const int8_t b_0[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  real32_T rtb_Switch_oqyb;
  real_T rtb_SquareRoot;
  real_T rtb_Subtract;
  int8_t rtb_MaxSwitch;
  real32_T rtb_kNpermm2tokPa;
  real32_T rtb_applycalibration[3];
  boolean_T rtb_LogicalOperator;
  boolean_T rtb_LogicalOperator_bt32;
  int8_t rtb_MaxSwitch_jl40;
  int8_t rtb_MaxSwitch_ankt;
  boolean_T rtb_resetSwitch_ifkf;
  boolean_T rtb_LogicalOperator8;
  boolean_T rtb_ConditionstoLatchNewValues;
  boolean_T rtb_resetSwitch_ebtw;
  real32_T rtb_resetSwitch_cwhz;
  real32_T rtb_TSamp;
  real32_T rtb_Sum1_gemz;
  real32_T rtb_rotMatrix[9];
  real32_T rtb_InitToInput[3];
  real32_T rtb_Sum1[3];
  real32_T rtb_MathFunction_dgrl[3];
  uint16_t rtb_EnableCheck;
  uint16_t rtb_EnableCheck_hpd1;
  uint16_t rtb_EnableCheck_hb3g;
  real_T rtb_toa_tilt_sens_to_bucket_ang_by_id_sfunc;
  real_T rtb_DataTypeConversion2;
  boolean_T FixPtRelationalOperator;
  boolean_T FixPtRelationalOperator_meyn;
  real32_T filtered;
  real32_T Sum1_enp4;
  real32_T filtered_idbq;
  real32_T filtered_d1c3;
  real32_T filtered_esvw;
  real32_T filtered_krzt;
  real32_T tmp[3];
  int32_t i;
  int32_t i_0;
  real32_T tmp_0[9];
  boolean_T exitg1;

  /* SignalConversion: '<S131>/Copy' incorporates:
   *  Inport: '<Root>/Tilt_Extension'
   */
  toa_wl00_B->toa_inTsTiltExt = toa_wl00_U_Tilt_Extension;

  /* DataTypeConversion: '<S34>/Data Type Conversion1' */
  rtb_toa_tilt_sens_to_bucket_ang_by_id_sfunc = toa_wl00_B->toa_inTsTiltExt;

  /* SignalConversion: '<S129>/Copy' incorporates:
   *  Gain: '<S134>/Gain1'
   *  Inport: '<Root>/Lift_Angle'
   */
  toa_wl00_B->toa_inTsLiftAngle = 0.0174532924F * toa_wl00_U_Lift_Angle;

  /* DataTypeConversion: '<S34>/Data Type Conversion2' */
  rtb_DataTypeConversion2 = toa_wl00_B->toa_inTsLiftAngle;

  /* SignalConversion: '<S130>/Copy' incorporates:
   *  Constant: '<S30>/Length btw BC pins, mm'
   */
  toa_wl00_B->toa_inTsBc = toa_wl00_M->
    toa_wl00_catParameters_si_RAM_p->toa_toolBcLength;

  /* DataTypeConversion: '<S34>/Data Type Conversion3' */
  rtb_SquareRoot = toa_wl00_B->toa_inTsBc;

  /* SignalConversion: '<S132>/Copy' incorporates:
   *  Constant: '<S30>/BC Angle, deg'
   *  Gain: '<S133>/Gain1'
   */
  toa_wl00_B->toa_inTsBcAng = 0.0174532924F *
    toa_wl00_M->toa_wl00_catParameters_si_RAM_p->toa_toolBcAngle;

  /* DataTypeConversion: '<S34>/Data Type Conversion4' */
  rtb_Subtract = toa_wl00_B->toa_inTsBcAng;

  /* S-Function (toa_tilt_sens_to_bucket_ang_by_id_sfunc): '<S34>/toa_tilt_sens_to_bucket_ang_by_id_sfunc' incorporates:
   *  Constant: '<S30>/Tip-Off Assist App Number'
   */
  toa_tilt_sens_to_bucket_ang_by_id(toa_wl00_M->
    toa_wl00_catParameters_si_RAM_p->toa_appNumber,
    rtb_toa_tilt_sens_to_bucket_ang_by_id_sfunc, rtb_DataTypeConversion2,
    rtb_SquareRoot, rtb_Subtract, &rtb_toa_tilt_sens_to_bucket_ang_by_id_sfunc);

  /* SignalConversion: '<S15>/Copy' incorporates:
   *  DataTypeConversion: '<S34>/Data Type Conversion5'
   */
  toa_wl00_B->toa_tiltSensitivity = (real32_T)
    rtb_toa_tilt_sens_to_bucket_ang_by_id_sfunc;

  /* SignalConversion: '<S22>/Copy' */
  toa_wl00_B->toa_outTiltSensToBucket = toa_wl00_B->toa_tiltSensitivity;

  /* Outport: '<Root>/Tilt_Sensitivity' */
  *toa_wl00_Y_Tilt_Sensitivity = toa_wl00_B->toa_outTiltSensToBucket;

  /* SignalConversion: '<S8>/Copy' incorporates:
   *  Inport: '<Root>/Tilt_HE_Pressure'
   */
  toa_wl00_B->toa_outTiltHePress = toa_wl00_U_Tilt_HE_Pressure;

  /* Outport: '<Root>/Tilt_HE_Pressure_Out' */
  *toa_wl00_Y_Tilt_HE_Pressure_Out = toa_wl00_B->toa_outTiltHePress;

  /* Switch: '<S282>/Max Switch' incorporates:
   *  Constant: '<S220>/expected bucket angle noise amplitude, deg'
   *  Constant: '<S220>/sliding threshold, degrees'
   *  Constant: '<S282>/Hi Value'
   *  Inport: '<Root>/Bucket_Angle'
   *  Memory: '<S283>/Memory 1'
   *  Memory: '<S283>/Memory 2'
   *  RelationalOperator: '<S282>/Compare Max'
   *  RelationalOperator: '<S282>/Compare Min'
   *  Sum: '<S220>/Add1'
   *  Switch: '<S282>/Min Switch'
   *  Switch: '<S283>/Init'
   */
  if (toa_wl00_U_Bucket_Angle > 8.0F) {
    rtb_MaxSwitch = 1;
  } else if (toa_wl00_U_Bucket_Angle < 7.0F) {
    /* Switch: '<S282>/Min Switch' incorporates:
     *  Constant: '<S282>/Lo Value'
     */
    rtb_MaxSwitch = 0;
  } else if (toa_wl00_DWork->Memory1_PreviousInput != 0) {
    /* Switch: '<S283>/Init' incorporates:
     *  Constant: '<S282>/Lo Value'
     *  Switch: '<S282>/Min Switch'
     */
    rtb_MaxSwitch = 0;
  } else {
    rtb_MaxSwitch = toa_wl00_DWork->Memory2_PreviousInput;
  }

  /* End of Switch: '<S282>/Max Switch' */

  /* SignalConversion: '<S186>/Copy' incorporates:
   *  DataTypeConversion: '<S220>/Data Type Conversion'
   */
  toa_wl00_B->toa_pfwSecIsNoSliding = (rtb_MaxSwitch != 0);

  /* Product: '<S127>/Multiply2' incorporates:
   *  Constant: '<S127>/Constant2'
   *  Constant: '<S30>/tilt bore dia, mm'
   *  Math: '<S127>/Math Function'
   */
  rtb_Switch_oqyb = (toa_wl00_M->
                     toa_wl00_catParameters_si_RAM_p->toa_tiltBoreDia *
                     toa_wl00_M->
                     toa_wl00_catParameters_si_RAM_p->toa_tiltBoreDia) *
    0.785398185F;

  /* SignalConversion: '<S18>/Copy' incorporates:
   *  Constant: '<S128>/Constant2'
   *  Constant: '<S30>/# of tilt cyls'
   *  Constant: '<S30>/tilt rod dia, mm'
   *  Constant: '<S33>/mN to kN'
   *  Inport: '<Root>/Tilt_HE_Pressure'
   *  Inport: '<Root>/Tilt_RE_Pressure'
   *  Math: '<S128>/Math Function'
   *  Product: '<S128>/Multiply2'
   *  Product: '<S33>/Multiply'
   *  Product: '<S33>/Multiply1'
   *  Product: '<S33>/Multiply2'
   *  Product: '<S5>/Multiply1'
   *  Sum: '<S33>/Subtract'
   *  Sum: '<S33>/Subtract1'
   */
  toa_wl00_B->toa_tiltForce = (((rtb_Switch_oqyb * toa_wl00_U_Tilt_HE_Pressure)
    - ((rtb_Switch_oqyb - ((toa_wl00_M->
    toa_wl00_catParameters_si_RAM_p->toa_tiltRodDia *
    toa_wl00_M->toa_wl00_catParameters_si_RAM_p->toa_tiltRodDia) * 0.785398185F))
       * toa_wl00_U_Tilt_RE_Pressure)) * 1.0E-6F) * ((real32_T)
    toa_wl00_M->toa_wl00_catParameters_si_RAM_p->toa_tiltNumCyl);

  /* SignalConversion: '<S88>/Copy' incorporates:
   *  Constant: '<S31>/Constant'
   *  Product: '<S31>/Multiply'
   */
  toa_wl00_B->toa_sfuncInTiltForce = 1.0E+6F * toa_wl00_B->toa_tiltForce;

  /* SignalConversion: '<S81>/Copy' incorporates:
   *  DataTypeConversion: '<S31>/Data Type Conversion3'
   */
  toa_wl00_B->toa_sfuncInRawTiltForce = toa_wl00_B->toa_sfuncInTiltForce;

  /* Product: '<S76>/Multiply2' incorporates:
   *  Constant: '<S30>/lift bore dia, mm'
   *  Constant: '<S76>/Constant2'
   *  Math: '<S76>/Math Function'
   *  Product: '<S71>/Multiply2'
   */
  rtb_Switch_oqyb = (toa_wl00_M->
                     toa_wl00_catParameters_si_RAM_p->toa_liftBoreDia *
                     toa_wl00_M->
                     toa_wl00_catParameters_si_RAM_p->toa_liftBoreDia) *
    0.785398185F;

  /* SignalConversion: '<S74>/Copy' incorporates:
   *  Constant: '<S28>/mN to kN'
   *  Constant: '<S30>/lift rod dia, mm'
   *  Constant: '<S72>/Constant2'
   *  Inport: '<Root>/Lift_HE_Pressure'
   *  Inport: '<Root>/Lift_RE_Pressure'
   *  Math: '<S72>/Math Function'
   *  Product: '<S28>/Multiply'
   *  Product: '<S28>/Multiply1'
   *  Product: '<S28>/Multiply2'
   *  Product: '<S72>/Multiply2'
   *  Sum: '<S28>/Subtract'
   *  Sum: '<S28>/Subtract1'
   */
  toa_wl00_B->toa_fcLiftForceRaw = ((rtb_Switch_oqyb *
    toa_wl00_U_Lift_HE_Pressure) - ((rtb_Switch_oqyb -
    ((toa_wl00_M->toa_wl00_catParameters_si_RAM_p->toa_liftRodDia *
      toa_wl00_M->toa_wl00_catParameters_si_RAM_p->toa_liftRodDia) *
     0.785398185F)) * toa_wl00_U_Lift_RE_Pressure)) * 1.0E-6F;

  /* Gain: '<S29>/kN per mm^2 to kPa' incorporates:
   *  Product: '<S29>/Divide'
   *  Product: '<S76>/Multiply2'
   */
  rtb_kNpermm2tokPa = ((1.0F / rtb_Switch_oqyb) * toa_wl00_B->toa_fcLiftForceRaw)
    * 1.0E+6F;

  /* MATLAB Function: '<S29>/MATLAB Function' incorporates:
   *  Inport: '<Root>/Friction_Mu'
   *  Inport: '<Root>/Friction_Offset'
   *  Inport: '<Root>/Lift_Valve_Command'
   */
  /*  rawPress */
  /*    Equivalent HE pressure in kPa */
  /*  liftCmd */
  /*    Lift command with */
  /*  fricCoeff */
  /*    Friction coefficient in units of kPa of friction / raw kPa */
  /*  fricOffset */
  /*    Friction offset in units of kPa */
  /* MATLAB Function 'Tip-Off Assist Support Lib/Lift Friction Compensation/MATLAB Function': '<S75>:1' */
  /* '<S75>:1:11' if liftCmd < 0.0 */
  if (toa_wl00_U_Lift_Valve_Command < 0.0F) {
    /*  Lower */
    /* '<S75>:1:12' compPress = (1 + fricCoeff) * rawPress + fricOffset; */
    rtb_kNpermm2tokPa = ((1.0F + toa_wl00_U_Friction_Mu) * rtb_kNpermm2tokPa) +
      toa_wl00_U_Friction_Offset;
  } else if (!(toa_wl00_U_Lift_Valve_Command == 0.0F)) {
    if (toa_wl00_U_Lift_Valve_Command > 0.0F) {
      /* '<S75>:1:15' elseif liftCmd > 0.0 */
      /*  Raise */
      /* '<S75>:1:16' compPress = (1 - fricCoeff) * rawPress - fricOffset; */
      rtb_kNpermm2tokPa = ((1.0F - toa_wl00_U_Friction_Mu) * rtb_kNpermm2tokPa)
        - toa_wl00_U_Friction_Offset;
    } else {
      /* '<S75>:1:17' else */
      /*  Unexpected, so propogate value that triggers bad status */
      /* '<S75>:1:19' compPress = single(NaN); */
      rtb_kNpermm2tokPa = (rtNaNF);
    }
  } else {
    /* '<S75>:1:13' elseif liftCmd == 0.0 */
    /*  Hold */
    /* '<S75>:1:14' compPress = rawPress; */
  }

  /* End of MATLAB Function: '<S29>/MATLAB Function' */

  /* SignalConversion: '<S73>/Copy' incorporates:
   *  Gain: '<S29>/kPa to kN per mm^2'
   *  Product: '<S29>/Product'
   *  Product: '<S76>/Multiply2'
   */
  toa_wl00_B->toa_fcLiftForceComp = (1.0E-6F * rtb_kNpermm2tokPa) *
    rtb_Switch_oqyb;

  /* SignalConversion: '<S19>/Copy' incorporates:
   *  Constant: '<S5>/# of lift cyls'
   *  Product: '<S5>/Multiply'
   */
  toa_wl00_B->toa_liftForce = toa_wl00_B->toa_fcLiftForceComp * 2.0F;

  /* SignalConversion: '<S90>/Copy' incorporates:
   *  Constant: '<S31>/Constant'
   *  Product: '<S31>/Multiply1'
   */
  toa_wl00_B->toa_sfuncInLiftForce = 1.0E+6F * toa_wl00_B->toa_liftForce;

  /* SignalConversion: '<S82>/Copy' incorporates:
   *  DataTypeConversion: '<S31>/Data Type Conversion1'
   */
  toa_wl00_B->toa_sfuncInRawLiftForce = toa_wl00_B->toa_sfuncInLiftForce;

  /* SignalConversion: '<S78>/Copy' incorporates:
   *  Inport: '<Root>/Tilt_Extension'
   */
  toa_wl00_B->toa_sfuncInTiltExt = toa_wl00_U_Tilt_Extension;

  /* SignalConversion: '<S83>/Copy' incorporates:
   *  DataTypeConversion: '<S31>/Data Type Conversion2'
   */
  toa_wl00_B->toa_sfuncInRawTiltExt = toa_wl00_B->toa_sfuncInTiltExt;

  /* SignalConversion: '<S98>/Copy' incorporates:
   *  Inport: '<Root>/Lift_Angle'
   */
  toa_wl00_B->toa_sfuncInLiftAng = toa_wl00_U_Lift_Angle;

  /* SignalConversion: '<S84>/Copy' incorporates:
   *  DataTypeConversion: '<S31>/Data Type Conversion4'
   *  Gain: '<S100>/Gain1'
   */
  toa_wl00_B->toa_sfuncInRawLiftAng = 0.0174532924F *
    toa_wl00_B->toa_sfuncInLiftAng;

  /* SignalConversion: '<S95>/Copy' incorporates:
   *  Constant: '<S30>/Length btw BC pins, mm'
   */
  toa_wl00_B->toa_sfuncInBcLength = toa_wl00_M->
    toa_wl00_catParameters_si_RAM_p->toa_toolBcLength;

  /* SignalConversion: '<S85>/Copy' incorporates:
   *  DataTypeConversion: '<S31>/Data Type Conversion5'
   */
  toa_wl00_B->toa_sfuncInRawBcLength = toa_wl00_B->toa_sfuncInBcLength;

  /* MATLAB Function: '<S26>/Rotation Matrix About Z' incorporates:
   *  Inport: '<Root>/IMU_Pitch_Cal'
   */
  /*  Calculates a rotation matrix from an angle in deg */
  /* MATLAB Function 'Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/Rotation Matrix About Z': '<S48>:1' */
  /* '<S48>:1:3' if angle == 0 */
  if (toa_wl00_U_IMU_Pitch_Cal == 0.0F) {
    /* '<S48>:1:4' rotMatrix = single(eye(3)); */
    for (i = 0; i < 9; i++) {
      I[i] = 0;
    }

    I[0] = 1;
    I[4] = 1;
    I[8] = 1;
    for (i = 0; i < 9; i++) {
      rtb_rotMatrix[i] = I[i];
    }
  } else {
    /* '<S48>:1:8' angleRad = angle / 180.0 * pi; */
    rtb_kNpermm2tokPa = (toa_wl00_U_IMU_Pitch_Cal / 180.0F) * 3.14159274F;

    /*  Form rotation matrix */
    /* '<S48>:1:11' a = cos(angleRad); */
    rtb_Switch_oqyb = cosf(rtb_kNpermm2tokPa);

    /* '<S48>:1:12' b = sin(angleRad); */
    rtb_kNpermm2tokPa = sinf(rtb_kNpermm2tokPa);

    /* '<S48>:1:13' rotMatrix = [ */
    /* '<S48>:1:14'     a, -b, 0; */
    /* '<S48>:1:15'     b, a, 0; */
    /* '<S48>:1:16'     0, 0, 1 */
    /* '<S48>:1:17'     ]; */
    rtb_rotMatrix[0] = rtb_Switch_oqyb;
    rtb_rotMatrix[3] = -rtb_kNpermm2tokPa;
    rtb_rotMatrix[6] = 0.0F;
    rtb_rotMatrix[1] = rtb_kNpermm2tokPa;
    rtb_rotMatrix[4] = rtb_Switch_oqyb;
    rtb_rotMatrix[7] = 0.0F;
    rtb_rotMatrix[2] = 0.0F;
    rtb_rotMatrix[5] = 0.0F;
    rtb_rotMatrix[8] = 1.0F;
  }

  /* End of MATLAB Function: '<S26>/Rotation Matrix About Z' */

  /* SignalConversion: '<S1>/Copy' incorporates:
   *  Inport: '<Root>/EEF_IMU_AccelX'
   */
  toa_wl00_B->toa_inImuAcclX = toa_wl00_U_EEF_IMU_AccelX;

  /* SignalConversion: '<S2>/Copy' incorporates:
   *  Inport: '<Root>/EEF_IMU_AccelY'
   */
  toa_wl00_B->toa_inImuAcclY = toa_wl00_U_EEF_IMU_AccelY;

  /* SignalConversion: '<S3>/Copy' incorporates:
   *  Inport: '<Root>/EEF_IMU_AccelZ'
   */
  toa_wl00_B->toa_inImuAcclZ = toa_wl00_U_EEF_IMU_AccelZ;

  /* Product: '<S26>/transform to basic EEF' incorporates:
   *  Constant: '<S26>/IMU csys to EEF csys rot mat'
   *  Product: '<S26>/apply calibration'
   *  SignalConversion: '<Root>/ConcatBufferAtConcatenate VectorIn1'
   *  SignalConversion: '<Root>/ConcatBufferAtConcatenate VectorIn2'
   *  SignalConversion: '<Root>/ConcatBufferAtConcatenate VectorIn3'
   */
  for (i = 0; i < 3; i++) {
    tmp[i] = 0.0F;
    tmp[i] += toa_wl00_ConstP.IMUcsystoEEFcsysrotmat_Value[i] *
      toa_wl00_B->toa_inImuAcclX;
    tmp[i] += toa_wl00_ConstP.IMUcsystoEEFcsysrotmat_Value[i + 3] *
      toa_wl00_B->toa_inImuAcclY;
    tmp[i] += toa_wl00_ConstP.IMUcsystoEEFcsysrotmat_Value[i + 6] *
      toa_wl00_B->toa_inImuAcclZ;
  }

  /* End of Product: '<S26>/transform to basic EEF' */

  /* Logic: '<S59>/Logical Operator' incorporates:
   *  UnitDelay: '<S58>/Unit Delay'
   */
  rtb_LogicalOperator = (toa_wl00_DWork->UnitDelay_DSTATE_mvg5 != 0);

  /* Logic: '<S61>/Logical Operator' incorporates:
   *  UnitDelay: '<S60>/Unit Delay'
   */
  rtb_LogicalOperator_bt32 = (toa_wl00_DWork->UnitDelay_DSTATE_j5gs != 0);
  for (i = 0; i < 3; i++) {
    /* Product: '<S26>/apply calibration' */
    rtb_Switch_oqyb = (rtb_rotMatrix[i + 6] * tmp[2]) + ((rtb_rotMatrix[i + 3] *
      tmp[1]) + (rtb_rotMatrix[i] * tmp[0]));

    /* Switch: '<S56>/InitToInput' incorporates:
     *  UnitDelay: '<S56>/Unit Delay1'
     */
    if (rtb_LogicalOperator) {
      rtb_kNpermm2tokPa = toa_wl00_DWork->UnitDelay1_DSTATE[i];
    } else {
      rtb_kNpermm2tokPa = rtb_Switch_oqyb;
    }

    /* Sum: '<S56>/Sum1' incorporates:
     *  Product: '<S56>/Product'
     *  Sum: '<S56>/Sum3'
     */
    filtered_d1c3 = ((rtb_Switch_oqyb - rtb_kNpermm2tokPa) * 0.0608986616F) +
      rtb_kNpermm2tokPa;

    /* Switch: '<S57>/InitToInput' incorporates:
     *  UnitDelay: '<S57>/Unit Delay1'
     */
    if (rtb_LogicalOperator_bt32) {
      rtb_kNpermm2tokPa = toa_wl00_DWork->UnitDelay1_DSTATE_mga0[i];
    } else {
      rtb_kNpermm2tokPa = filtered_d1c3;
    }

    /* End of Switch: '<S57>/InitToInput' */

    /* Sum: '<S57>/Sum1' incorporates:
     *  Product: '<S57>/Product'
     *  Sum: '<S57>/Sum3'
     */
    rtb_kNpermm2tokPa += (filtered_d1c3 - rtb_kNpermm2tokPa) * 0.0608986616F;

    /* DataTypeConversion: '<S57>/Data Type Conversion' */
    toa_wl00_B->toa_imu_eef_accl_vec_post_lpf[i] = rtb_kNpermm2tokPa;

    /* Math: '<S51>/Math Function' */
    rtb_MathFunction_dgrl[i] = toa_wl00_B->toa_imu_eef_accl_vec_post_lpf[i] *
      toa_wl00_B->toa_imu_eef_accl_vec_post_lpf[i];

    /* Switch: '<S56>/InitToInput' */
    rtb_InitToInput[i] = rtb_kNpermm2tokPa;

    /* Sum: '<S56>/Sum1' */
    rtb_Sum1[i] = filtered_d1c3;

    /* Product: '<S26>/apply calibration' */
    rtb_applycalibration[i] = rtb_Switch_oqyb;
  }

  /* Sum: '<S51>/Sum of Elements' */
  filtered_krzt = (rtb_MathFunction_dgrl[0] + rtb_MathFunction_dgrl[1]) +
    rtb_MathFunction_dgrl[2];

  /* Math: '<S51>/Math Function1' incorporates:
   *  Sum: '<S51>/Sum of Elements'
   *
   * About '<S51>/Math Function1':
   *  Operator: sqrt
   */
  if (filtered_krzt < 0.0F) {
    rtb_Switch_oqyb = -sqrtf(fabsf(filtered_krzt));
  } else {
    rtb_Switch_oqyb = sqrtf(filtered_krzt);
  }

  /* End of Math: '<S51>/Math Function1' */

  /* Gain: '<S45>/Gain1' incorporates:
   *  Inport: '<Root>/Steering_Angle'
   */
  rtb_kNpermm2tokPa = 0.0174532924F * toa_wl00_U_Steering_Angle;

  /* MATLAB Function: '<S26>/EEF vector to NEEF vector' incorporates:
   *  Constant: '<S26>/gravity magnitude'
   *  Product: '<S26>/Product'
   *  Product: '<S51>/Divide'
   */
  /*  Transforms a vector on the EEF to a vector on the NEEF via steering angle */
  /* MATLAB Function 'Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/EEF vector to NEEF vector': '<S46>:1' */
  /* '<S46>:1:3' rotAxis = [0; 1; 0]; */
  /*  Steering right is positive angle */
  /* '<S46>:1:4' angle = steeringAngle; */
  /*  Form rotation matrix */
  /* '<S46>:1:7' crossProductMatrix = [ */
  /* '<S46>:1:8'     0,          -rotAxis(3),  rotAxis(2); */
  /* '<S46>:1:9'      rotAxis(3), 0,          -rotAxis(1); */
  /* '<S46>:1:10'     -rotAxis(2), rotAxis(1),  0 */
  /* '<S46>:1:11' ]; */
  /* '<S46>:1:12' tensorProduct = rotAxis * transpose(rotAxis); */
  /* '<S46>:1:13' rotMatrix = cos(angle) * eye(3) + sin(angle) * crossProductMatrix + ... */
  /* '<S46>:1:14'     (1 - cos(angle)) * tensorProduct; */
  filtered_krzt = cosf(rtb_kNpermm2tokPa);
  filtered_esvw = sinf(rtb_kNpermm2tokPa);

  /* '<S46>:1:16' neefVector = rotMatrix * eefVector; */
  i = 0;
  for (i_0 = 0; i_0 < 3; i_0++) {
    rtb_rotMatrix[i] = ((((real32_T)b[i]) * filtered_krzt) + (((real32_T)c[i]) *
      filtered_esvw)) + (((real32_T)d[i]) * (1.0F - filtered_krzt));
    rtb_rotMatrix[i + 1] = ((((real32_T)b[i + 1]) * filtered_krzt) + (((real32_T)
      c[i + 1]) * filtered_esvw)) + (((real32_T)d[i + 1]) * (1.0F -
      filtered_krzt));
    rtb_rotMatrix[i + 2] = ((((real32_T)b[i + 2]) * filtered_krzt) + (((real32_T)
      c[i + 2]) * filtered_esvw)) + (((real32_T)d[i + 2]) * (1.0F -
      filtered_krzt));
    tmp[i_0] = (toa_wl00_B->toa_imu_eef_accl_vec_post_lpf[i_0] / rtb_Switch_oqyb)
      * 9.80665F;
    i += 3;
  }

  for (i = 0; i < 3; i++) {
    toa_wl00_B->toa_imu_neef_accl_vec[i] = 0.0F;
    toa_wl00_B->toa_imu_neef_accl_vec[i] += rtb_rotMatrix[i] * tmp[0];
    toa_wl00_B->toa_imu_neef_accl_vec[i] += rtb_rotMatrix[i + 3] * tmp[1];
    toa_wl00_B->toa_imu_neef_accl_vec[i] += rtb_rotMatrix[i + 6] * tmp[2];

    /* Gain: '<S26>/convert "proper acceleration" to gravity' */
    rtb_MathFunction_dgrl[i] = -toa_wl00_B->toa_imu_neef_accl_vec[i];
  }

  /* End of MATLAB Function: '<S26>/EEF vector to NEEF vector' */

  /* SignalConversion: '<S91>/Copy' incorporates:
   *  Switch: '<S70>/Switch'
   */
  toa_wl00_B->toa_sfuncInGravX = rtb_MathFunction_dgrl[0];

  /* DataTypeConversion: '<S31>/Data Type Conversion8' */
  rtb_Subtract = toa_wl00_B->toa_sfuncInGravX;

  /* SignalConversion: '<S93>/Copy' */
  toa_wl00_B->toa_sfuncInRawGravX = rtb_Subtract;

  /* SignalConversion: '<S92>/Copy' incorporates:
   *  Switch: '<S68>/Switch'
   */
  toa_wl00_B->toa_sfuncInGravY = rtb_MathFunction_dgrl[1];

  /* DataTypeConversion: '<S31>/Data Type Conversion9' */
  rtb_Subtract = toa_wl00_B->toa_sfuncInGravY;

  /* SignalConversion: '<S94>/Copy' */
  toa_wl00_B->toa_sfuncInRawGravY = rtb_Subtract;

  /* S-Function (toa_mass_and_dist_by_id_sfunc): '<S31>/toa_mass_and_dist_by_id_sfunc' incorporates:
   *  Constant: '<S30>/Tip-Off Assist App Number'
   */
  toa_mass_and_dist_by_id(toa_wl00_M->
    toa_wl00_catParameters_si_RAM_p->toa_appNumber,
    toa_wl00_B->toa_sfuncInRawTiltForce, toa_wl00_B->toa_sfuncInRawLiftForce,
    toa_wl00_B->toa_sfuncInRawTiltExt, toa_wl00_B->toa_sfuncInRawLiftAng,
    toa_wl00_B->toa_sfuncInRawBcLength, toa_wl00_B->toa_sfuncInRawGravX,
    toa_wl00_B->toa_sfuncInRawGravY, &rtb_Subtract, &rtb_SquareRoot);

  /* SignalConversion: '<S89>/Copy' */
  toa_wl00_B->toa_sfuncOutRawMass = rtb_Subtract;

  /* SignalConversion: '<S79>/Copy' incorporates:
   *  DataTypeConversion: '<S31>/Data Type Conversion6'
   *  Gain: '<S31>/grams to tonnes'
   */
  toa_wl00_B->toa_sfuncOutRawMassTonne = 1.0E-6F * ((real32_T)
    toa_wl00_B->toa_sfuncOutRawMass);

  /* SignalConversion: '<S96>/Copy' incorporates:
   *  Inport: '<Root>/Tool_Mass'
   *  Sum: '<S31>/Tool Mass Offset'
   */
  toa_wl00_B->toa_rawPayload = toa_wl00_B->toa_sfuncOutRawMassTonne -
    toa_wl00_U_Tool_Mass;

  /* SignalConversion: '<S86>/Copy' incorporates:
   *  Inport: '<Root>/Anchor_Zero_Offset'
   *  Sum: '<S31>/Apply Anchor Zero'
   */
  toa_wl00_B->toa_payloadAncZeroed = toa_wl00_B->toa_rawPayload -
    toa_wl00_U_Anchor_Zero_Offset;

  /* SignalConversion: '<S87>/Copy' incorporates:
   *  Inport: '<Root>/Anchor_Factor'
   *  Product: '<S31>/Apply Anchor Factor'
   */
  toa_wl00_B->toa_payloadAncAdjusted = toa_wl00_U_Anchor_Factor *
    toa_wl00_B->toa_payloadAncZeroed;

  /* SignalConversion: '<S99>/Copy' incorporates:
   *  Inport: '<Root>/Zero_Offset'
   *  Sum: '<S31>/Apply Zero'
   */
  toa_wl00_B->toa_payloadZeroed = toa_wl00_B->toa_payloadAncAdjusted -
    toa_wl00_U_Zero_Offset;

  /* SignalConversion: '<S97>/Copy' incorporates:
   *  Inport: '<Root>/Simple_Cal_Factor'
   *  Product: '<S31>/Apply Scale Factor'
   */
  toa_wl00_B->toa_payloadAdjusted = toa_wl00_U_Simple_Cal_Factor *
    toa_wl00_B->toa_payloadZeroed;

  /* Logic: '<S5>/Logical Operator' incorporates:
   *  Inport: '<Root>/Invalidate_Outputs'
   *  RelationalOperator: '<S5>/Relational Operator'
   */
  rtb_LogicalOperator = (toa_wl00_U_Invalidate_Outputs || (rtIsNaNF
    (toa_wl00_B->toa_payloadAdjusted)));

  /* RelationalOperator: '<S213>/FixPt Relational Operator' incorporates:
   *  UnitDelay: '<S213>/Delay Input1'
   *
   * Block description for '<S213>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FixPtRelationalOperator = (((int32_t)rtb_LogicalOperator) < ((int32_t)
    toa_wl00_DWork->DelayInput1_DSTATE));

  /* Switch: '<S231>/resetSwitch' incorporates:
   *  Constant: '<S231>/false'
   *  Delay: '<S202>/Delay2'
   *  Inport: '<Root>/Bucket_Angle'
   *  Inport: '<Root>/Unlatch_Trigger'
   *  Logic: '<S202>/Logical Operator'
   *  RelationalOperator: '<S202>/Current Bucket Angle Lower Than Or Equal To Previous Min Angle'
   *  Switch: '<S231>/setSwitch'
   *  UnitDelay: '<S231>/Unit Delay'
   */
  if (toa_wl00_U_Unlatch_Trigger || FixPtRelationalOperator) {
    rtb_Switch_oqyb = 99.0F;
  } else if (toa_wl00_DWork->Delay2_DSTATE > toa_wl00_U_Bucket_Angle) {
    /* Switch: '<S231>/setSwitch' incorporates:
     *  Inport: '<Root>/Bucket_Angle'
     */
    rtb_Switch_oqyb = toa_wl00_U_Bucket_Angle;
  } else {
    rtb_Switch_oqyb = toa_wl00_DWork->UnitDelay_DSTATE;
  }

  /* End of Switch: '<S231>/resetSwitch' */

  /* Switch: '<S230>/Max Switch' incorporates:
   *  Constant: '<S202>/Secure Load Buffer Angle, degrees'
   *  Constant: '<S202>/expected bucket angle noise amplitude, deg'
   *  Constant: '<S230>/Hi Value'
   *  Inport: '<Root>/Bucket_Angle'
   *  Memory: '<S232>/Memory 1'
   *  Memory: '<S232>/Memory 2'
   *  RelationalOperator: '<S230>/Compare Max'
   *  RelationalOperator: '<S230>/Compare Min'
   *  Sum: '<S202>/Add'
   *  Sum: '<S202>/Add2'
   *  Switch: '<S230>/Min Switch'
   *  Switch: '<S232>/Init'
   */
  if (toa_wl00_U_Bucket_Angle > ((rtb_Switch_oqyb + 6.0F) + 1.0F)) {
    rtb_MaxSwitch_jl40 = 1;
  } else if (toa_wl00_U_Bucket_Angle < (rtb_Switch_oqyb + 6.0F)) {
    /* Switch: '<S230>/Min Switch' incorporates:
     *  Constant: '<S230>/Lo Value'
     */
    rtb_MaxSwitch_jl40 = 0;
  } else if (toa_wl00_DWork->Memory1_PreviousInput_ddl0 != 0) {
    /* Switch: '<S232>/Init' incorporates:
     *  Constant: '<S230>/Lo Value'
     *  Switch: '<S230>/Min Switch'
     */
    rtb_MaxSwitch_jl40 = 0;
  } else {
    rtb_MaxSwitch_jl40 = toa_wl00_DWork->Memory2_PreviousInput_i53e;
  }

  /* End of Switch: '<S230>/Max Switch' */

  /* SignalConversion: '<S194>/Copy' incorporates:
   *  DataTypeConversion: '<S202>/Data Type Conversion'
   */
  toa_wl00_B->toa_pfwSecIsNoCollapsing = (rtb_MaxSwitch_jl40 != 0);

  /* MinMax: '<S212>/MinMax' incorporates:
   *  Inport: '<Root>/Tilt_Norm_Angle'
   *  Inport: '<Root>/Tilt_Norm_Length'
   */
  rtb_kNpermm2tokPa = fmaxf(toa_wl00_U_Tilt_Norm_Angle,
    toa_wl00_U_Tilt_Norm_Length);

  /* Switch: '<S277>/Max Switch' incorporates:
   *  Constant: '<S212>/min tilt norm angle to be considered racked'
   *  Constant: '<S277>/Hi Value'
   *  Gain: '<S212>/guessed typical ratio of tilt norm angle to bucket angle'
   *  Memory: '<S278>/Memory 1'
   *  Memory: '<S278>/Memory 2'
   *  RelationalOperator: '<S277>/Compare Max'
   *  RelationalOperator: '<S277>/Compare Min'
   *  Sum: '<S212>/Add1'
   *  Switch: '<S277>/Min Switch'
   *  Switch: '<S278>/Init'
   */
  if (rtb_kNpermm2tokPa > 0.97F) {
    rtb_MaxSwitch_ankt = 1;
  } else if (rtb_kNpermm2tokPa < 0.962500036F) {
    /* Switch: '<S277>/Min Switch' incorporates:
     *  Constant: '<S277>/Lo Value'
     */
    rtb_MaxSwitch_ankt = 0;
  } else if (toa_wl00_DWork->Memory1_PreviousInput_gnui != 0) {
    /* Switch: '<S278>/Init' incorporates:
     *  Constant: '<S277>/Lo Value'
     *  Switch: '<S277>/Min Switch'
     */
    rtb_MaxSwitch_ankt = 0;
  } else {
    rtb_MaxSwitch_ankt = toa_wl00_DWork->Memory2_PreviousInput_pgwc;
  }

  /* End of Switch: '<S277>/Max Switch' */

  /* SignalConversion: '<S196>/Copy' incorporates:
   *  DataTypeConversion: '<S212>/Data Type Conversion'
   */
  toa_wl00_B->toa_pfwSecIsRacked = (rtb_MaxSwitch_ankt != 0);

  /* Logic: '<S143>/Secure Payload Assumed Combined' incorporates:
   *  Logic: '<S143>/Secure Payload Assumed 1'
   */
  rtb_LogicalOperator_bt32 = (((toa_wl00_B->toa_pfwSecIsNoSliding) &&
    (toa_wl00_B->toa_pfwSecIsNoCollapsing)) || (toa_wl00_B->toa_pfwSecIsRacked));

  /* SignalConversion: '<S279>/Copy' incorporates:
   *  Inport: '<Root>/Unlatch_Trigger'
   *  Logic: '<S218>/Logical Operator3'
   *  RelationalOperator: '<S205>/FixPt Relational Operator'
   *  UnitDelay: '<S205>/Delay Input1'
   *
   * Block description for '<S205>/Delay Input1':
   *
   *  Store in Global RAM
   */
  toa_wl00_B->toa_pfwLatchInvalidate = (toa_wl00_U_Unlatch_Trigger || (((int32_t)
    rtb_LogicalOperator_bt32) < ((int32_t)
    toa_wl00_DWork->DelayInput1_DSTATE_prcl)));

  /* Switch: '<S219>/InitToInput' incorporates:
   *  Logic: '<S281>/Logical Operator'
   *  Logic: '<S281>/Logical Operator1'
   *  UnitDelay: '<S219>/Unit Delay1'
   *  UnitDelay: '<S280>/Unit Delay'
   */
  if ((toa_wl00_DWork->UnitDelay_DSTATE_bw1s != 0) && (!FixPtRelationalOperator))
  {
    rtb_kNpermm2tokPa = toa_wl00_DWork->UnitDelay1_DSTATE_fp5d;
  } else {
    rtb_kNpermm2tokPa = toa_wl00_B->toa_payloadAdjusted;
  }

  /* End of Switch: '<S219>/InitToInput' */

  /* MATLAB Function: '<S143>/MATLAB Function1' incorporates:
   *  Constant: '<S143>/Constant3'
   *  Constant: '<S143>/Constant4'
   */
  toa_wl00_MATLABFunction(0.02, 0.6, &rtb_Subtract);

  /* Sum: '<S219>/Sum1' incorporates:
   *  Product: '<S219>/Product'
   *  Sum: '<S219>/Sum3'
   */
  rtb_kNpermm2tokPa += (real32_T)((toa_wl00_B->toa_payloadAdjusted -
    rtb_kNpermm2tokPa) * rtb_Subtract);

  /* Chart: '<S243>/Filter' incorporates:
   *  Constant: '<S243>/Constant'
   *  SampleTimeMath: '<S243>/Weighted Sample Time'
   *
   * About '<S243>/Weighted Sample Time':
   *  y = K where K = ( w * Ts )
   */
  toa_wl00_Filter(rtb_kNpermm2tokPa, FixPtRelationalOperator, 0.02F, 5.0F,
                  &filtered_idbq, &toa_wl00_DWork->sf_Filter);

  /* Chart: '<S244>/Filter' incorporates:
   *  Constant: '<S244>/Constant'
   *  SampleTimeMath: '<S244>/Weighted Sample Time'
   *
   * About '<S244>/Weighted Sample Time':
   *  y = K where K = ( w * Ts )
   */
  toa_wl00_Filter(filtered_idbq, FixPtRelationalOperator, 0.02F, 7.5F,
                  &filtered_d1c3, &toa_wl00_DWork->sf_Filter_jasu);

  /* Chart: '<S245>/Filter' incorporates:
   *  Constant: '<S245>/Constant'
   *  SampleTimeMath: '<S245>/Weighted Sample Time'
   *
   * About '<S245>/Weighted Sample Time':
   *  y = K where K = ( w * Ts )
   */
  toa_wl00_Filter(filtered_d1c3, FixPtRelationalOperator, 0.02F, 12.0F,
                  &filtered, &toa_wl00_DWork->sf_Filter_ewyz);

  /* Switch: '<S266>/resetSwitch' incorporates:
   *  Constant: '<S263>/Constant'
   *  Constant: '<S264>/Constant'
   *  Constant: '<S265>/Constant'
   *  Constant: '<S266>/false'
   *  Inport: '<Root>/Lift_Valve_Command'
   *  Inport: '<Root>/Tilt_Valve_Command'
   *  Logic: '<S259>/Logical Operator4'
   *  RelationalOperator: '<S263>/Compare'
   *  RelationalOperator: '<S264>/Compare'
   *  RelationalOperator: '<S265>/Compare'
   *  UnitDelay: '<S266>/Unit Delay'
   */
  if ((toa_wl00_U_Tilt_Valve_Command > 0.0F) || (toa_wl00_U_Lift_Valve_Command <
       0.0F)) {
    rtb_resetSwitch_ifkf = false;
  } else {
    rtb_resetSwitch_ifkf = ((toa_wl00_U_Tilt_Valve_Command < 0.0F) ||
      (toa_wl00_DWork->UnitDelay_DSTATE_fett));
  }

  /* End of Switch: '<S266>/resetSwitch' */

  /* SignalConversion: '<S249>/Copy' incorporates:
   *  Constant: '<S255>/Max travel'
   *  Constant: '<S256>/Max travel'
   *  Inport: '<Root>/Tilt_Norm_Angle'
   *  Inport: '<Root>/Tilt_Norm_Length'
   *  Logic: '<S259>/Logical Operator3'
   *  Logic: '<S259>/Might be rack stalled based on position only'
   *  Logic: '<S259>/not'
   *  RelationalOperator: '<S255>/Relational Operator'
   *  RelationalOperator: '<S256>/Relational Operator'
   */
  toa_wl00_B->toa_pfwMcMaybeRackStall = (((toa_wl00_U_Tilt_Norm_Angle >= 0.97F) ||
    (toa_wl00_U_Tilt_Norm_Length >= 0.97F)) && (!rtb_resetSwitch_ifkf));

  /* SignalConversion: '<S250>/Copy' incorporates:
   *  Constant: '<S253>/Max travel'
   *  Constant: '<S253>/Min travel'
   *  Constant: '<S254>/Max travel'
   *  Constant: '<S254>/Min travel'
   *  Constant: '<S255>/Min travel'
   *  Constant: '<S256>/Min travel'
   *  Inport: '<Root>/Lift_Norm_Angle'
   *  Inport: '<Root>/Lift_Norm_Length'
   *  Inport: '<Root>/Tilt_Norm_Angle'
   *  Inport: '<Root>/Tilt_Norm_Length'
   *  Logic: '<S211>/Logical Operator'
   *  RelationalOperator: '<S253>/Relational Operator'
   *  RelationalOperator: '<S253>/Relational Operator1'
   *  RelationalOperator: '<S254>/Relational Operator'
   *  RelationalOperator: '<S254>/Relational Operator1'
   *  RelationalOperator: '<S255>/Relational Operator1'
   *  RelationalOperator: '<S256>/Relational Operator1'
   */
  toa_wl00_B->toa_pfwMcMaybeStalled = (((((((toa_wl00_U_Lift_Norm_Angle >= 0.97F)
    || (toa_wl00_U_Lift_Norm_Angle <= 0.03F)) || (toa_wl00_U_Lift_Norm_Length >=
    0.97F)) || (toa_wl00_U_Lift_Norm_Length <= 0.03F)) ||
    (toa_wl00_U_Tilt_Norm_Angle <= 0.03F)) || (toa_wl00_U_Tilt_Norm_Length <=
    0.03F)) || (toa_wl00_B->toa_pfwMcMaybeRackStall));

  /* SignalConversion: '<S251>/Copy' incorporates:
   *  Constant: '<S258>/Constant'
   *  Constant: '<S258>/Constant1'
   *  Constant: '<S258>/Constant2'
   *  Inport: '<Root>/Bucket_Angle'
   *  Inport: '<Root>/Lift_Norm_Angle'
   *  Logic: '<S258>/Logical Operator1'
   *  Logic: '<S258>/Logical Operator3'
   *  RelationalOperator: '<S258>/Relational Operator'
   *  RelationalOperator: '<S258>/Relational Operator1'
   *  RelationalOperator: '<S258>/Relational Operator2'
   */
  toa_wl00_B->toa_pfwMcMaybeGrounded = ((toa_wl00_U_Lift_Norm_Angle <= 0.07F) ||
    ((toa_wl00_U_Lift_Norm_Angle <= 0.12F) && (toa_wl00_U_Bucket_Angle <= 0.0F)));

  /* SignalConversion: '<S193>/Copy' incorporates:
   *  Constant: '<S203>/Constant'
   *  Inport: '<Root>/Lift_Valve_Command'
   *  RelationalOperator: '<S203>/Compare'
   */
  toa_wl00_B->toa_isLiftValveCmd = (toa_wl00_U_Lift_Valve_Command != 0.0F);

  /* SignalConversion: '<S192>/Copy' incorporates:
   *  Constant: '<S204>/Constant'
   *  Inport: '<Root>/Tilt_Valve_Command'
   *  RelationalOperator: '<S204>/Compare'
   */
  toa_wl00_B->toa_isTiltValveCmd = (toa_wl00_U_Tilt_Valve_Command != 0.0F);

  /* Logic: '<S260>/Logical Operator' */
  rtb_LogicalOperator_fcyj = !toa_wl00_B->toa_isLiftValveCmd;

  /* S-Function (SampleTime_DataType_sfun): '<S271>/Query Sample Time' */
  /* Sample time: 0.02 seconds */
  rtb_QuerySampleTime = (1U);

  /* Switch: '<S267>/Enable Check' incorporates:
   *  Constant: '<S267>/Constant1'
   *  RelationalOperator: '<S270>/Compare'
   *  RelationalOperator: '<S272>/Compare'
   *  Switch: '<S267>/Finished Check'
   *  UnitDelay: '<S267>/Timer'
   */
  if (!rtb_LogicalOperator_fcyj) {
    /* MinMax: '<S267>/MinMax' incorporates:
     *  Constant: '<S267>/Constant2'
     */
    if (225 > rtb_QuerySampleTime) {
      rtb_EnableCheck = 225U;
    } else {
      rtb_EnableCheck = rtb_QuerySampleTime;
    }

    /* End of MinMax: '<S267>/MinMax' */
  } else if (toa_wl00_DWork->Timer_DSTATE > 0) {
    /* Switch: '<S267>/Finished Check' incorporates:
     *  Sum: '<S271>/Sum'
     *  UnitDelay: '<S267>/Timer'
     */
    rtb_EnableCheck = (uint16_t)(toa_wl00_DWork->Timer_DSTATE -
      rtb_QuerySampleTime);
  } else {
    rtb_EnableCheck = 0U;
  }

  /* End of Switch: '<S267>/Enable Check' */

  /* Logic: '<S260>/Logical Operator5' */
  toa_wl00_B->toa_is_not_tilt_valve_cmd = !toa_wl00_B->toa_isTiltValveCmd;

  /* S-Function (SampleTime_DataType_sfun): '<S275>/Query Sample Time' */
  /* Sample time: 0.02 seconds */
  rtb_QuerySampleTime_i540 = (1U);

  /* Switch: '<S268>/Enable Check' incorporates:
   *  Constant: '<S268>/Constant1'
   *  RelationalOperator: '<S274>/Compare'
   *  RelationalOperator: '<S276>/Compare'
   *  Switch: '<S268>/Finished Check'
   *  UnitDelay: '<S268>/Timer'
   */
  if (!toa_wl00_B->toa_is_not_tilt_valve_cmd) {
    /* MinMax: '<S268>/MinMax' incorporates:
     *  Constant: '<S268>/Constant2'
     */
    if (225 > rtb_QuerySampleTime_i540) {
      rtb_EnableCheck_hpd1 = 225U;
    } else {
      rtb_EnableCheck_hpd1 = rtb_QuerySampleTime_i540;
    }

    /* End of MinMax: '<S268>/MinMax' */
  } else if (toa_wl00_DWork->Timer_DSTATE_dme3 > 0) {
    /* Switch: '<S268>/Finished Check' incorporates:
     *  Sum: '<S275>/Sum'
     *  UnitDelay: '<S268>/Timer'
     */
    rtb_EnableCheck_hpd1 = (uint16_t)(toa_wl00_DWork->Timer_DSTATE_dme3 -
      rtb_QuerySampleTime_i540);
  } else {
    rtb_EnableCheck_hpd1 = 0U;
  }

  /* End of Switch: '<S268>/Enable Check' */

  /* RelationalOperator: '<S273>/Compare' */
  toa_wl00_B->toa_tilt_timer_expired = (rtb_EnableCheck_hpd1 <= 0);

  /* Logic: '<S260>/Logical Operator4' */
  toa_wl00_B->toa_tilt_timer_not_expired = !toa_wl00_B->toa_tilt_timer_expired;

  /* Logic: '<S211>/Logical Operator8' incorporates:
   *  Inport: '<Root>/Unlatch_Trigger'
   *  Logic: '<S211>/Logical Operator1'
   *  Logic: '<S211>/Logical Operator9'
   *  Logic: '<S211>/Measurement Conditions Not OK'
   *  Logic: '<S260>/Logical Operator1'
   *  Logic: '<S260>/Logical Operator2'
   *  Logic: '<S260>/Logical Operator3'
   *  Logic: '<S260>/Logical Operator6'
   *  RelationalOperator: '<S269>/Compare'
   */
  rtb_LogicalOperator8 = ((!(((((toa_wl00_B->toa_pfwMcMaybeStalled) ||
    (toa_wl00_B->toa_pfwMcMaybeGrounded)) || rtb_LogicalOperator) ||
    toa_wl00_U_Unlatch_Trigger) || ((toa_wl00_B->toa_isLiftValveCmd) ||
    (toa_wl00_B->toa_isTiltValveCmd)))) && ((rtb_LogicalOperator_fcyj &&
    (!(rtb_EnableCheck <= 0))) && ((toa_wl00_B->toa_is_not_tilt_valve_cmd) &&
    (toa_wl00_B->toa_tilt_timer_not_expired))));

  /* Logic: '<S143>/Logical Operator' incorporates:
   *  Delay: '<S257>/Delay'
   *  Logic: '<S257>/Logical Operator'
   *  RelationalOperator: '<S262>/Compare'
   */
  FixPtRelationalOperator = (FixPtRelationalOperator || (rtb_LogicalOperator8 &&
    (!toa_wl00_DWork->Delay_DSTATE_obnz)));

  /* Switch: '<S143>/Use Live Payload When Resetting' */
  if (!FixPtRelationalOperator) {
    filtered = toa_wl00_B->toa_payloadAdjusted;
  }

  /* End of Switch: '<S143>/Use Live Payload When Resetting' */

  /* Chart: '<S237>/Filter' incorporates:
   *  Constant: '<S237>/Constant'
   *  SampleTimeMath: '<S237>/Weighted Sample Time'
   *
   * About '<S237>/Weighted Sample Time':
   *  y = K where K = ( w * Ts )
   */
  toa_wl00_Filter(filtered, FixPtRelationalOperator, 0.02F, 5.0F, &filtered_idbq,
                  &toa_wl00_DWork->sf_Filter_ozu2);

  /* Chart: '<S238>/Filter' incorporates:
   *  Constant: '<S238>/Constant'
   *  SampleTimeMath: '<S238>/Weighted Sample Time'
   *
   * About '<S238>/Weighted Sample Time':
   *  y = K where K = ( w * Ts )
   */
  toa_wl00_Filter(filtered_idbq, FixPtRelationalOperator, 0.02F, 7.5F,
                  &filtered_d1c3, &toa_wl00_DWork->sf_Filter_f5hh);

  /* SignalConversion: '<S198>/Copy' incorporates:
   *  Chart: '<S239>/Filter'
   *  Constant: '<S239>/Constant'
   *  SampleTimeMath: '<S239>/Weighted Sample Time'
   *
   * About '<S239>/Weighted Sample Time':
   *  y = K where K = ( w * Ts )
   */
  toa_wl00_Filter(filtered_d1c3, FixPtRelationalOperator, 0.02F, 12.0F,
                  &toa_wl00_B->toa_pfwPayloadNotchPost,
                  &toa_wl00_DWork->sf_Filter_n3ho);

  /* MATLAB Function: '<S225>/MATLAB Function' */
  /* MATLAB Function 'Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Variance Anti-Noise Filter1/MATLAB Function': '<S290>:1' */
  /* '<S290>:1:4' if isempty(lastSample) || reset */
  if ((!toa_wl00_DWork->lastSample_not_empty_m4ln) || FixPtRelationalOperator) {
    /* '<S290>:1:5' lastSample = u; */
    toa_wl00_DWork->lastSample_kln4 = toa_wl00_B->toa_pfwPayloadNotchPost;
    toa_wl00_DWork->lastSample_not_empty_m4ln = true;
  }

  /* SignalConversion: '<S197>/Copy' incorporates:
   *  MATLAB Function: '<S225>/MATLAB Function'
   */
  /* '<S290>:1:7' y = (u + lastSample) / 2; */
  toa_wl00_B->toa_pfwPayloadNotchFiltFinal =
    (toa_wl00_B->toa_pfwPayloadNotchPost + toa_wl00_DWork->lastSample_kln4) /
    2.0F;

  /* MATLAB Function: '<S225>/MATLAB Function' */
  /* '<S290>:1:8' lastSample = u; */
  toa_wl00_DWork->lastSample_kln4 = toa_wl00_B->toa_pfwPayloadNotchPost;

  /* MATLAB Function: '<S221>/MATLAB Function1' incorporates:
   *  Constant: '<S143>/Constant1'
   *  Constant: '<S221>/Constant2'
   */
  toa_wl00_MATLABFunction(0.02, 0.6, &rtb_Subtract);

  /* MATLAB Function: '<S221>/Two Sided St. Dev. from Bound' incorporates:
   *  Constant: '<S221>/Constant'
   *  Constant: '<S221>/Constant1'
   *  Constant: '<S30>/Rated Payload, tonne'
   *  Product: '<S221>/Product'
   */
  toa_wl00_TwoSidedStDevfromBound(0.997F,
    toa_wl00_M->toa_wl00_catParameters_si_RAM_p->toa_ratedPayload * 0.3F,
    &toa_wl00_B->toa_statPayloadNlOneSize);

  /* MATLAB Function: '<S221>/MATLAB Function' incorporates:
   *  Math: '<S221>/Math Function'
   */
  toa_wl00_MATLABFunction_fw1r(toa_wl00_B->toa_pfwPayloadNotchFiltFinal,
    rtb_Subtract, FixPtRelationalOperator, toa_wl00_B->toa_statPayloadNlOneSize *
    toa_wl00_B->toa_statPayloadNlOneSize, &toa_wl00_B->toa_pfwNlNotchMeanEst,
    &toa_wl00_B->toa_pfwNlNotchStDevEst, &toa_wl00_DWork->sf_MATLABFunction_fw1r);

  /* SignalConversion: '<S252>/Copy' */
  toa_wl00_B->toa_pfwMcOk = rtb_LogicalOperator8;

  /* S-Function (SampleTime_DataType_sfun): '<S235>/Query Sample Time' */
  /* Sample time: 0.02 seconds */
  rtb_QuerySampleTime_h1dv = (1U);

  /* Switch: '<S208>/Enable Check' incorporates:
   *  Constant: '<S208>/Constant1'
   *  RelationalOperator: '<S234>/Compare'
   *  RelationalOperator: '<S236>/Compare'
   *  Switch: '<S208>/Finished Check'
   *  UnitDelay: '<S208>/Timer'
   */
  if (!toa_wl00_B->toa_pfwMcOk) {
    /* MinMax: '<S208>/MinMax' incorporates:
     *  Constant: '<S208>/Constant2'
     */
    if (50 > rtb_QuerySampleTime_h1dv) {
      rtb_EnableCheck_hb3g = 50U;
    } else {
      rtb_EnableCheck_hb3g = rtb_QuerySampleTime_h1dv;
    }

    /* End of MinMax: '<S208>/MinMax' */
  } else if (toa_wl00_DWork->Timer_DSTATE_jrr0 > 0) {
    /* Switch: '<S208>/Finished Check' incorporates:
     *  Sum: '<S235>/Sum'
     *  UnitDelay: '<S208>/Timer'
     */
    rtb_EnableCheck_hb3g = (uint16_t)(toa_wl00_DWork->Timer_DSTATE_jrr0 -
      rtb_QuerySampleTime_h1dv);
  } else {
    rtb_EnableCheck_hb3g = 0U;
  }

  /* End of Switch: '<S208>/Enable Check' */

  /* SignalConversion: '<S191>/Copy' incorporates:
   *  Logic: '<S143>/Conditions for Warm'
   *  RelationalOperator: '<S233>/Compare'
   */
  toa_wl00_B->toa_pfwIsWarm = ((toa_wl00_B->toa_pfwMcOk) &&
    (rtb_EnableCheck_hb3g <= 0));

  /* SignalConversion: '<S185>/Copy' */
  toa_wl00_B->toa_pfwSecIsSecure = rtb_LogicalOperator_bt32;

  /* Logic: '<S143>/Conditions to Latch New Values' incorporates:
   *  Delay: '<S143>/Delay'
   *  RelationalOperator: '<S143>/Current Std Dev Better or Equal to Previously Latched Std Dev'
   */
  rtb_ConditionstoLatchNewValues = (((toa_wl00_DWork->Delay_DSTATE >=
    toa_wl00_B->toa_pfwNlNotchStDevEst) && (toa_wl00_B->toa_pfwIsWarm)) &&
    (toa_wl00_B->toa_pfwSecIsSecure));

  /* Switch: '<S214>/resetSwitch' incorporates:
   *  Constant: '<S214>/false'
   *  Constant: '<S216>/false'
   *  Switch: '<S214>/setSwitch'
   *  Switch: '<S216>/resetSwitch'
   *  Switch: '<S216>/setSwitch'
   *  UnitDelay: '<S214>/Unit Delay'
   *  UnitDelay: '<S216>/Unit Delay'
   */
  if (toa_wl00_B->toa_pfwLatchInvalidate) {
    filtered_d1c3 = (rtNaNF);
    rtb_resetSwitch_ebtw = false;
  } else {
    if (rtb_ConditionstoLatchNewValues) {
      /* Switch: '<S214>/setSwitch' */
      filtered_d1c3 = toa_wl00_B->toa_pfwNlNotchMeanEst;
    } else {
      filtered_d1c3 = toa_wl00_DWork->UnitDelay_DSTATE_hioq;
    }

    rtb_resetSwitch_ebtw = (rtb_ConditionstoLatchNewValues ||
      (toa_wl00_DWork->UnitDelay_DSTATE_nds1));
  }

  /* End of Switch: '<S214>/resetSwitch' */

  /* SignalConversion: '<S136>/Copy' */
  toa_wl00_B->toa_pfwSecPayload = filtered_d1c3;

  /* SignalConversion: '<S138>/Copy' */
  toa_wl00_B->toa_pfwSecLatch = rtb_resetSwitch_ebtw;

  /* RelationalOperator: '<S152>/FixPt Relational Operator' incorporates:
   *  UnitDelay: '<S152>/Delay Input1'
   *
   * Block description for '<S152>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FixPtRelationalOperator_meyn = (((int32_t)rtb_LogicalOperator) < ((int32_t)
    toa_wl00_DWork->DelayInput1_DSTATE_nzby));

  /* Switch: '<S154>/InitToInput' incorporates:
   *  Logic: '<S164>/Logical Operator'
   *  Logic: '<S164>/Logical Operator1'
   *  UnitDelay: '<S154>/Unit Delay1'
   *  UnitDelay: '<S163>/Unit Delay'
   */
  if ((toa_wl00_DWork->UnitDelay_DSTATE_fdvn != 0) &&
      (!FixPtRelationalOperator_meyn)) {
    toa_wl00_B->toa_pfwUnsecBoundUpper = toa_wl00_DWork->UnitDelay1_DSTATE_bcfn;
  } else {
    toa_wl00_B->toa_pfwUnsecBoundUpper = toa_wl00_B->toa_payloadAdjusted;
  }

  /* End of Switch: '<S154>/InitToInput' */

  /* MATLAB Function: '<S142>/MATLAB Function' incorporates:
   *  Constant: '<S142>/Constant2'
   *  Constant: '<S142>/Constant3'
   */
  toa_wl00_MATLABFunction(0.02, 0.6, &rtb_Subtract);

  /* Sum: '<S154>/Sum1' incorporates:
   *  Product: '<S154>/Product'
   *  Sum: '<S154>/Sum3'
   */
  filtered_idbq = ((real32_T)((toa_wl00_B->toa_payloadAdjusted -
    toa_wl00_B->toa_pfwUnsecBoundUpper) * rtb_Subtract)) +
    toa_wl00_B->toa_pfwUnsecBoundUpper;

  /* SignalConversion: '<S146>/Copy' */
  toa_wl00_B->toa_lwLpfPost = filtered_idbq;

  /* Switch: '<S112>/Switch' */
  if (toa_wl00_B->toa_pfwSecLatch) {
    /* SignalConversion: '<S102>/Copy' */
    toa_wl00_B->toa_sendPayloadArb = toa_wl00_B->toa_pfwSecPayload;
  } else {
    /* SignalConversion: '<S102>/Copy' */
    toa_wl00_B->toa_sendPayloadArb = toa_wl00_B->toa_lwLpfPost;
  }

  /* End of Switch: '<S112>/Switch' */

  /* SignalConversion: '<S115>/Copy' incorporates:
   *  Inport: '<Root>/PCS_Truck_Start_Weight'
   *  Inport: '<Root>/PCS_Truck_Target'
   *  Sum: '<S104>/Add'
   */
  toa_wl00_B->toa_targetPayloadPreComp = toa_wl00_U_PCS_Truck_Target -
    toa_wl00_U_PCS_Truck_Start_Weight;

  /* SignalConversion: '<S113>/Copy' */
  toa_wl00_B->toa_targetPayloadFinal = toa_wl00_B->toa_targetPayloadPreComp;

  /* Product: '<S106>/Multiply1' incorporates:
   *  Constant: '<S106>/Constant3'
   *  Constant: '<S30>/Rated Payload, tonne'
   *  Product: '<S106>/Divide1'
   *  Sum: '<S32>/Sum1'
   */
  toa_wl00_B->toa_pfwUnsecBoundUpper = ((1.0F /
    toa_wl00_M->toa_wl00_catParameters_si_RAM_p->toa_ratedPayload) *
    (toa_wl00_B->toa_sendPayloadArb - toa_wl00_B->toa_targetPayloadFinal)) *
    100.0F;

  /* Switch: '<S103>/Switch' incorporates:
   *  Constant: '<S103>/Constant'
   *  RelationalOperator: '<S103>/Relational Operator'
   */
  if (rtIsNaNF(toa_wl00_B->toa_pfwUnsecBoundUpper)) {
    toa_wl00_B->toa_pfwUnsecBoundUpper = 200.0F;
  }

  /* End of Switch: '<S103>/Switch' */

  /* Saturate: '<S103>/Saturation' */
  if (toa_wl00_B->toa_pfwUnsecBoundUpper > 200.0F) {
    /* SignalConversion: '<S14>/Copy' */
    toa_wl00_B->toa_outPayloadArbNormError = 200.0F;
  } else if (toa_wl00_B->toa_pfwUnsecBoundUpper < -200.0F) {
    /* SignalConversion: '<S14>/Copy' */
    toa_wl00_B->toa_outPayloadArbNormError = -200.0F;
  } else {
    /* SignalConversion: '<S14>/Copy' */
    toa_wl00_B->toa_outPayloadArbNormError = toa_wl00_B->toa_pfwUnsecBoundUpper;
  }

  /* End of Saturate: '<S103>/Saturation' */

  /* Outport: '<Root>/Arbitrated_Payload_Norm_Error' */
  *toa_wl00_Y_Arbitrated_Payload_Norm_Error =
    toa_wl00_B->toa_outPayloadArbNormError;

  /* MATLAB Function: '<S143>/Secure Payload Status' */
  /* MATLAB Function 'Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Secure Payload Status': '<S217>:1' */
  /* '<S217>:1:3' if inputsBad */
  if (rtb_LogicalOperator) {
    /* SignalConversion: '<S135>/Copy' */
    /* '<S217>:1:4' status = TipAssistSecPfwStatus_t.FAULT; */
    toa_wl00_B->toa_pfwSecStatus = TipAssistSecPfwStatus_t_FAULT;
  } else if ((rtb_resetSwitch_ebtw && (toa_wl00_B->toa_pfwMcOk)) &&
             (toa_wl00_B->toa_pfwSecIsSecure)) {
    /* SignalConversion: '<S135>/Copy' */
    /* '<S217>:1:5' elseif latched && measCondOk && secureAssumed */
    /*  Let consumers know that PFW is valid and may improve in confidence */
    /* '<S217>:1:7' status = TipAssistSecPfwStatus_t.VALID_MEASURING; */
    toa_wl00_B->toa_pfwSecStatus = TipAssistSecPfwStatus_t_VALID_MEASURING;
  } else if ((rtb_resetSwitch_ebtw && (!toa_wl00_B->toa_pfwMcOk)) &&
             (toa_wl00_B->toa_pfwSecIsSecure)) {
    /* SignalConversion: '<S135>/Copy' */
    /* '<S217>:1:8' elseif latched && ~measCondOk && secureAssumed */
    /*  Let consumers know that PFW is valid, but won't improve in confidence */
    /* '<S217>:1:10' status = TipAssistSecPfwStatus_t.VALID_NOT_MEASURING; */
    toa_wl00_B->toa_pfwSecStatus = TipAssistSecPfwStatus_t_VALID_NOT_MEASURING;
  } else if (((!rtb_resetSwitch_ebtw) && (toa_wl00_B->toa_pfwMcOk)) &&
             (toa_wl00_B->toa_pfwSecIsSecure)) {
    /* SignalConversion: '<S135>/Copy' */
    /* '<S217>:1:11' elseif ~latched && measCondOk && secureAssumed */
    /*  Let consumers know that PFW is likely about to become valid */
    /* '<S217>:1:13' status = TipAssistSecPfwStatus_t.PENDING; */
    toa_wl00_B->toa_pfwSecStatus = TipAssistSecPfwStatus_t_PENDING;
  } else {
    /* SignalConversion: '<S135>/Copy' */
    /* '<S217>:1:14' else */
    /* '<S217>:1:15' status = TipAssistSecPfwStatus_t.INVALID; */
    toa_wl00_B->toa_pfwSecStatus = TipAssistSecPfwStatus_t_INVALID;
  }

  /* End of MATLAB Function: '<S143>/Secure Payload Status' */

  /* SignalConversion: '<S16>/Copy' */
  toa_wl00_B->toa_outPfwStat = toa_wl00_B->toa_pfwSecStatus;

  /* Outport: '<Root>/Weigh_Status' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion1'
   */
  *toa_wl00_Y_Weigh_Status = (uint8_t)toa_wl00_B->toa_outPfwStat;

  /* Switch: '<S215>/resetSwitch' incorporates:
   *  Constant: '<S215>/false'
   *  Switch: '<S215>/setSwitch'
   *  UnitDelay: '<S215>/Unit Delay'
   */
  if (toa_wl00_B->toa_pfwLatchInvalidate) {
    rtb_resetSwitch_cwhz = (rtInfF);
  } else if (rtb_ConditionstoLatchNewValues) {
    /* Switch: '<S215>/setSwitch' */
    rtb_resetSwitch_cwhz = toa_wl00_B->toa_pfwNlNotchStDevEst;
  } else {
    rtb_resetSwitch_cwhz = toa_wl00_DWork->UnitDelay_DSTATE_jlpe;
  }

  /* End of Switch: '<S215>/resetSwitch' */

  /* SignalConversion: '<S137>/Copy' */
  toa_wl00_B->toa_pfwSecStDev = rtb_resetSwitch_cwhz;

  /* Product: '<S110>/Multiply1' incorporates:
   *  Constant: '<S110>/Constant3'
   *  Constant: '<S30>/Rated Payload, tonne'
   *  Product: '<S110>/Divide1'
   */
  toa_wl00_B->toa_outPfwPayloadNormStdev = ((1.0F /
    toa_wl00_M->toa_wl00_catParameters_si_RAM_p->toa_ratedPayload) *
    toa_wl00_B->toa_pfwSecStDev) * 100.0F;

  /* Saturate: '<S32>/PFW Std. Dev. Fit in Datalink Representation' */
  if (toa_wl00_B->toa_outPfwPayloadNormStdev > 175.0F) {
    /* Product: '<S110>/Multiply1' incorporates:
     *  SignalConversion: '<S17>/Copy'
     */
    toa_wl00_B->toa_outPfwPayloadNormStdev = 175.0F;
  } else {
    if (toa_wl00_B->toa_outPfwPayloadNormStdev < 0.0F) {
      /* Product: '<S110>/Multiply1' incorporates:
       *  SignalConversion: '<S17>/Copy'
       */
      toa_wl00_B->toa_outPfwPayloadNormStdev = 0.0F;
    }
  }

  /* End of Saturate: '<S32>/PFW Std. Dev. Fit in Datalink Representation' */

  /* Outport: '<Root>/Payload_Norm_Stdev' */
  *toa_wl00_Y_Payload_Norm_Stdev = toa_wl00_B->toa_outPfwPayloadNormStdev;

  /* SignalConversion: '<S11>/Copy' incorporates:
   *  Inport: '<Root>/PCS_Bucket_Current_Weight_Accuracy'
   */
  toa_wl00_B->toa_outCpmAccu = toa_wl00_U_PCS_Bucket_Current_Weight_Accuracy;

  /* Outport: '<Root>/PCS_Bucket_Current_Weight_Accuracy_Out' */
  *toa_wl00_Y_PCS_Bucket_Current_Weight_Accuracy_Out =
    toa_wl00_B->toa_outCpmAccu;

  /* SignalConversion: '<S12>/Copy' incorporates:
   *  Constant: '<S107>/Constant3'
   *  Constant: '<S30>/Rated Payload, tonne'
   *  Inport: '<Root>/PCS_Bucket_Current_Weight'
   *  Product: '<S107>/Divide1'
   *  Product: '<S107>/Multiply1'
   *  Sum: '<S32>/Sum'
   */
  toa_wl00_B->toa_outCpmPayloadNormError = ((1.0F /
    toa_wl00_M->toa_wl00_catParameters_si_RAM_p->toa_ratedPayload) *
    (toa_wl00_U_PCS_Bucket_Current_Weight - toa_wl00_B->toa_targetPayloadFinal))
    * 100.0F;

  /* Outport: '<Root>/PCS_Bucket_Current_Weight_Norm_Error_Out' */
  *toa_wl00_Y_PCS_Bucket_Current_Weight_Norm_Error_Out =
    toa_wl00_B->toa_outCpmPayloadNormError;

  /* Switch: '<S142>/Switch' incorporates:
   *  MATLAB Function: '<S143>/Unsecure Payload Status'
   */
  if (rtb_LogicalOperator) {
    /* SignalConversion: '<S144>/Copy' incorporates:
     *  Constant: '<S142>/Constant'
     */
    toa_wl00_B->toa_lwStatus = TipAssistLiveWeighStatus_t_FAULT;

    /* SignalConversion: '<S139>/Copy' */
    /* '<S224>:1:4' status = TipAssistUnsecPfwStatus_t.FAULT; */
    toa_wl00_B->toa_pfwUnsecStatus = TipAssistUnsecPfwStatus_t_FAULT;
  } else {
    /* SignalConversion: '<S144>/Copy' incorporates:
     *  Constant: '<S142>/Constant1'
     */
    toa_wl00_B->toa_lwStatus = TipAssistLiveWeighStatus_t_VALID;
    if ((toa_wl00_B->toa_pfwIsWarm) && (toa_wl00_B->toa_pfwMcOk)) {
      /* SignalConversion: '<S139>/Copy' */
      /* '<S224>:1:5' elseif warm && measCondOk */
      /*  Let consumers know that PFW is valid and may improve in confidence */
      /* '<S224>:1:7' status = TipAssistUnsecPfwStatus_t.VALID; */
      toa_wl00_B->toa_pfwUnsecStatus = TipAssistUnsecPfwStatus_t_VALID;
    } else if ((!toa_wl00_B->toa_pfwIsWarm) && (toa_wl00_B->toa_pfwMcOk)) {
      /* SignalConversion: '<S139>/Copy' */
      /* '<S224>:1:8' elseif ~warm && measCondOk */
      /*  Let consumers know that PFW is likely about to become valid */
      /* '<S224>:1:10' status = TipAssistUnsecPfwStatus_t.PENDING; */
      toa_wl00_B->toa_pfwUnsecStatus = TipAssistUnsecPfwStatus_t_PENDING;
    } else {
      /* SignalConversion: '<S139>/Copy' */
      /* '<S224>:1:11' else */
      /* '<S224>:1:12' status = TipAssistUnsecPfwStatus_t.INVALID; */
      toa_wl00_B->toa_pfwUnsecStatus = TipAssistUnsecPfwStatus_t_INVALID;
    }
  }

  /* End of Switch: '<S142>/Switch' */

  /* SignalConversion: '<S114>/Copy' incorporates:
   *  Constant: '<S116>/Constant'
   *  Inport: '<Root>/PCS_Truck_Target'
   *  RelationalOperator: '<S116>/Compare'
   */
  /* MATLAB Function 'Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Unsecure Payload Status': '<S224>:1' */
  /* '<S224>:1:3' if inputsBad */
  toa_wl00_B->toa_targetPayloadStatus = (toa_wl00_U_PCS_Truck_Target != 0.0F);

  /* Switch: '<S105>/Switch3' incorporates:
   *  Constant: '<S105>/Constant4'
   *  Constant: '<S121>/Constant'
   *  Constant: '<S122>/Constant'
   *  Constant: '<S123>/Constant'
   *  Constant: '<S124>/Constant'
   *  Constant: '<S125>/Constant'
   *  Constant: '<S126>/Constant3'
   *  Constant: '<S30>/Rated Payload, tonne'
   *  DataTypeConversion: '<Root>/Data Type Conversion2'
   *  Inport: '<Root>/PCS_Tipoff_Mode'
   *  Logic: '<S105>/Logical Operator'
   *  Product: '<S126>/Divide1'
   *  Product: '<S126>/Multiply1'
   *  RelationalOperator: '<S120>/Compare'
   *  RelationalOperator: '<S121>/Compare'
   *  RelationalOperator: '<S122>/Compare'
   *  RelationalOperator: '<S123>/Compare'
   *  RelationalOperator: '<S124>/Compare'
   *  RelationalOperator: '<S125>/Compare'
   *  Switch: '<S105>/Switch'
   *  Switch: '<S105>/Switch1'
   *  Switch: '<S105>/Switch2'
   */
  if (((toa_wl00_B->toa_pfwSecStatus == TipAssistSecPfwStatus_t_FAULT) ||
       (toa_wl00_B->toa_lwStatus == TipAssistLiveWeighStatus_t_FAULT)) ||
      (toa_wl00_B->toa_pfwUnsecStatus == TipAssistUnsecPfwStatus_t_FAULT)) {
    toa_wl00_B->toa_outAdvErrorCode = TipAssistAdvEcmError_t_FAULT;
  } else if (!toa_wl00_B->toa_targetPayloadStatus) {
    /* Switch: '<S105>/Switch1' incorporates:
     *  Constant: '<S105>/Constant3'
     */
    toa_wl00_B->toa_outAdvErrorCode =
      TipAssistAdvEcmError_t_TRUCK_TARGET_NOT_SET;
  } else if ((((1.0F / toa_wl00_M->
                toa_wl00_catParameters_si_RAM_p->toa_ratedPayload) *
               toa_wl00_B->toa_targetPayloadFinal) * 100.0F) < 5.0F) {
    /* Switch: '<S105>/Switch2' incorporates:
     *  Constant: '<S105>/Constant2'
     *  Switch: '<S105>/Switch1'
     */
    toa_wl00_B->toa_outAdvErrorCode =
      TipAssistAdvEcmError_t_PAYLOAD_NOT_ACHIEVABLE;
  } else if (toa_wl00_U_PCS_Tipoff_Mode != ((int32_t)
              TipAssistCpmTipOffMode_t_TIP_OFF_MODE_PILE)) {
    /* Switch: '<S105>/Switch' incorporates:
     *  Constant: '<S105>/Constant'
     *  Switch: '<S105>/Switch1'
     *  Switch: '<S105>/Switch2'
     */
    toa_wl00_B->toa_outAdvErrorCode =
      TipAssistAdvEcmError_t_TIP_OFF_MODE_NOT_PILE;
  } else {
    /* Switch: '<S105>/Switch1' incorporates:
     *  Constant: '<S105>/Constant1'
     *  Switch: '<S105>/Switch'
     *  Switch: '<S105>/Switch2'
     */
    toa_wl00_B->toa_outAdvErrorCode = TipAssistAdvEcmError_t_NO_ERROR;
  }

  /* End of Switch: '<S105>/Switch3' */

  /* Outport: '<Root>/Tipoff_Assist_Adv_Error_Code' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   */
  *toa_wl00_Y_Tipoff_Assist_Adv_Error_Code = (uint8_t)
    toa_wl00_B->toa_outAdvErrorCode;

  /* SampleTimeMath: '<S153>/TSamp'
   *
   * About '<S153>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp = toa_wl00_B->toa_lwLpfPost * 50.0F;

  /* Delay: '<S153>/Resettable Delay' */
  if (FixPtRelationalOperator_meyn) {
    toa_wl00_DWork->icLoad = 1U;
  }

  if (toa_wl00_DWork->icLoad != 0) {
    toa_wl00_DWork->ResettableDelay_DSTATE = rtb_TSamp;
  }

  /* Gain: '<S142>/Gain' incorporates:
   *  Delay: '<S153>/Resettable Delay'
   *  Sum: '<S153>/Diff'
   *
   * Block description for '<S153>/Diff':
   *
   *  Add in CPU
   */
  toa_wl00_B->toa_pfwUnsecBoundUpper = -(rtb_TSamp -
    toa_wl00_DWork->ResettableDelay_DSTATE);

  /* Switch: '<S156>/InitToInput' incorporates:
   *  Logic: '<S168>/Logical Operator'
   *  Logic: '<S168>/Logical Operator1'
   *  UnitDelay: '<S156>/Unit Delay1'
   *  UnitDelay: '<S167>/Unit Delay'
   */
  if ((toa_wl00_DWork->UnitDelay_DSTATE_pigm != 0) &&
      (!FixPtRelationalOperator_meyn)) {
    toa_wl00_B->toa_pfwUnsecBoundLower = toa_wl00_DWork->UnitDelay1_DSTATE_bo33;
  } else {
    toa_wl00_B->toa_pfwUnsecBoundLower = toa_wl00_B->toa_pfwUnsecBoundUpper;
  }

  /* End of Switch: '<S156>/InitToInput' */

  /* Sum: '<S156>/Sum3' */
  toa_wl00_B->toa_pfwUnsecBoundUpper -= toa_wl00_B->toa_pfwUnsecBoundLower;

  /* MATLAB Function: '<S142>/MATLAB Function2' incorporates:
   *  Constant: '<S142>/Constant5'
   *  Constant: '<S142>/Constant6'
   */
  toa_wl00_MATLABFunction(0.02, 0.5, &rtb_Subtract);

  /* Sum: '<S156>/Sum1' incorporates:
   *  Product: '<S156>/Product'
   */
  rtb_Sum1_gemz = ((real32_T)(toa_wl00_B->toa_pfwUnsecBoundUpper * rtb_Subtract))
    + toa_wl00_B->toa_pfwUnsecBoundLower;

  /* SignalConversion: '<S147>/Copy' */
  toa_wl00_B->toa_lwSpillRate = rtb_Sum1_gemz;

  /* Product: '<S111>/Multiply1' incorporates:
   *  Constant: '<S111>/Constant3'
   *  Constant: '<S30>/Rated Payload, tonne'
   *  Product: '<S111>/Divide1'
   */
  toa_wl00_B->toa_outSpillRateNorm = ((1.0F /
    toa_wl00_M->toa_wl00_catParameters_si_RAM_p->toa_ratedPayload) *
    toa_wl00_B->toa_lwSpillRate) * 100.0F;

  /* Saturate: '<S32>/Spill Rate Fit In Datalink Representation' */
  if (toa_wl00_B->toa_outSpillRateNorm > 300.0F) {
    /* Product: '<S111>/Multiply1' incorporates:
     *  SignalConversion: '<S10>/Copy'
     */
    toa_wl00_B->toa_outSpillRateNorm = 300.0F;
  } else {
    if (toa_wl00_B->toa_outSpillRateNorm < 0.0F) {
      /* Product: '<S111>/Multiply1' incorporates:
       *  SignalConversion: '<S10>/Copy'
       */
      toa_wl00_B->toa_outSpillRateNorm = 0.0F;
    }
  }

  /* End of Saturate: '<S32>/Spill Rate Fit In Datalink Representation' */

  /* Outport: '<Root>/Spill_Rate_Norm' */
  *toa_wl00_Y_Spill_Rate_Norm = toa_wl00_B->toa_outSpillRateNorm;

  /* SignalConversion: '<S23>/Copy' */
  toa_wl00_B->toa_outBucketPayloadTarget = toa_wl00_B->toa_targetPayloadFinal;

  /* Outport: '<Root>/Bucket_Payload_Target' */
  *toa_wl00_Y_Bucket_Payload_Target = toa_wl00_B->toa_outBucketPayloadTarget;

  /* MATLAB Function: '<S229>/Two Sided Confidence Limit' incorporates:
   *  Constant: '<S229>/Constant'
   */
  toa_wl00_TwoSidedConfidenceLimit(0.997, rtb_resetSwitch_cwhz,
    &toa_wl00_B->toa_statPayloadSecureTwoSize);

  /* SignalConversion: '<S37>/Copy' */
  toa_wl00_B->toa_sendCpmPfwSecSize = toa_wl00_B->toa_statPayloadSecureTwoSize;

  /* SignalConversion: '<S36>/Copy' incorporates:
   *  Constant: '<S25>/Constant'
   *  Constant: '<S30>/Rated Payload, tonne'
   *  Product: '<S25>/Divide'
   *  RelationalOperator: '<S25>/Relational Operator'
   */
  toa_wl00_B->toa_sendCpmPfwIsPrecise = ((toa_wl00_B->toa_sendCpmPfwSecSize /
    toa_wl00_M->toa_wl00_catParameters_si_RAM_p->toa_ratedPayload) <= 0.02);

  /* Switch: '<S155>/InitToInput' incorporates:
   *  Logic: '<S166>/Logical Operator'
   *  Logic: '<S166>/Logical Operator1'
   *  UnitDelay: '<S155>/Unit Delay1'
   *  UnitDelay: '<S165>/Unit Delay'
   */
  if ((toa_wl00_DWork->UnitDelay_DSTATE_kdv5 != 0) &&
      (!FixPtRelationalOperator_meyn)) {
    toa_wl00_B->toa_pfwUnsecBoundUpper = toa_wl00_DWork->UnitDelay1_DSTATE_e2d2;
  } else {
    toa_wl00_B->toa_pfwUnsecBoundUpper = toa_wl00_B->toa_payloadAdjusted;
  }

  /* End of Switch: '<S155>/InitToInput' */

  /* MATLAB Function: '<S142>/MATLAB Function1' incorporates:
   *  Constant: '<S142>/Constant2'
   *  Constant: '<S142>/Constant4'
   */
  toa_wl00_MATLABFunction(0.02, 0.955, &rtb_Subtract);

  /* Sum: '<S155>/Sum1' incorporates:
   *  Product: '<S155>/Product'
   *  Sum: '<S155>/Sum3'
   */
  Sum1_enp4 = ((real32_T)((toa_wl00_B->toa_payloadAdjusted -
    toa_wl00_B->toa_pfwUnsecBoundUpper) * rtb_Subtract)) +
    toa_wl00_B->toa_pfwUnsecBoundUpper;

  /* Chart: '<S157>/Filter' incorporates:
   *  Constant: '<S157>/Constant'
   *  SampleTimeMath: '<S157>/Weighted Sample Time'
   *
   * About '<S157>/Weighted Sample Time':
   *  y = K where K = ( w * Ts )
   */
  toa_wl00_Filter(Sum1_enp4, FixPtRelationalOperator_meyn, 0.02F, 5.0F,
                  &filtered_esvw, &toa_wl00_DWork->sf_Filter_dsll);

  /* Chart: '<S158>/Filter' incorporates:
   *  Constant: '<S158>/Constant'
   *  SampleTimeMath: '<S158>/Weighted Sample Time'
   *
   * About '<S158>/Weighted Sample Time':
   *  y = K where K = ( w * Ts )
   */
  toa_wl00_Filter(filtered_esvw, FixPtRelationalOperator_meyn, 0.02F, 7.5F,
                  &filtered_krzt, &toa_wl00_DWork->sf_Filter_c1cw);

  /* SignalConversion: '<S145>/Copy' incorporates:
   *  Chart: '<S159>/Filter'
   *  Constant: '<S159>/Constant'
   *  SampleTimeMath: '<S159>/Weighted Sample Time'
   *
   * About '<S159>/Weighted Sample Time':
   *  y = K where K = ( w * Ts )
   */
  toa_wl00_Filter(filtered_krzt, FixPtRelationalOperator_meyn, 0.02F, 12.0F,
                  &toa_wl00_B->toa_sendCpmLivePayload,
                  &toa_wl00_DWork->sf_Filter_ifuw);

  /* MATLAB Function: '<S25>/MATLAB Function' */
  /* MATLAB Function 'Tip-Off Assist Support Lib/CPM Payload Send/MATLAB Function': '<S38>:1' */
  /* '<S38>:1:3' if pfwIsPrecise && (pfwStatus == TipAssistSecPfwStatus_t.VALID_MEASURING || pfwStatus == TipAssistSecPfwStatus_t.VALID_NOT_MEASURING) */
  if ((toa_wl00_B->toa_sendCpmPfwIsPrecise) && ((toa_wl00_B->toa_pfwSecStatus ==
        TipAssistSecPfwStatus_t_VALID_MEASURING) ||
       (toa_wl00_B->toa_pfwSecStatus ==
        TipAssistSecPfwStatus_t_VALID_NOT_MEASURING))) {
    /* SignalConversion: '<S20>/Copy' */
    /* '<S38>:1:4' outStatus = TipAssistSendCpmStatus_t.PSEUDO_FRICTIONLESS; */
    toa_wl00_B->toa_outSendCpmStatus =
      TipAssistSendCpmStatus_t_PSEUDO_FRICTIONLESS;

    /* SignalConversion: '<S6>/Copy' */
    /* '<S38>:1:5' outPayload = pfwPayload; */
    toa_wl00_B->toa_outSendCpmPayload = toa_wl00_B->toa_pfwSecPayload;
  } else if (toa_wl00_B->toa_lwStatus == TipAssistLiveWeighStatus_t_VALID) {
    /* SignalConversion: '<S20>/Copy' */
    /* '<S38>:1:6' elseif liveStatus == TipAssistLiveWeighStatus_t.VALID */
    /* '<S38>:1:7' outStatus = TipAssistSendCpmStatus_t.LIVE; */
    toa_wl00_B->toa_outSendCpmStatus = TipAssistSendCpmStatus_t_LIVE;

    /* SignalConversion: '<S6>/Copy' */
    /* '<S38>:1:8' outPayload = livePayload; */
    toa_wl00_B->toa_outSendCpmPayload = toa_wl00_B->toa_sendCpmLivePayload;
  } else {
    /* SignalConversion: '<S20>/Copy' */
    /* '<S38>:1:9' else */
    /* '<S38>:1:10' outStatus = TipAssistSendCpmStatus_t.INVALID; */
    toa_wl00_B->toa_outSendCpmStatus = TipAssistSendCpmStatus_t_INVALID;

    /* SignalConversion: '<S6>/Copy' */
    /* '<S38>:1:11' outPayload = single(NaN); */
    toa_wl00_B->toa_outSendCpmPayload = (rtNaNF);
  }

  /* End of MATLAB Function: '<S25>/MATLAB Function' */

  /* Outport: '<Root>/Payload_Send_To_CPM' */
  *toa_wl00_Y_Payload_Send_To_CPM = toa_wl00_B->toa_outSendCpmPayload;

  /* Outport: '<Root>/Payload_Status_Send_To_CPM' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion3'
   */
  *toa_wl00_Y_Payload_Status_Send_To_CPM = (uint8_t)
    toa_wl00_B->toa_outSendCpmStatus;

  /* MATLAB Function: '<S228>/One Sided Confidence Limit' incorporates:
   *  Constant: '<S228>/Constant'
   */
  toa_wl00_OneSidedConfidenceLimit(0.997, toa_wl00_B->toa_pfwNlNotchStDevEst,
    &toa_wl00_B->toa_statPayloadSecureOneSize);

  /* Sum: '<S228>/Add' */
  toa_wl00_B->toa_pfwUnsecBoundUpper = toa_wl00_B->toa_statPayloadSecureOneSize
    + toa_wl00_B->toa_pfwNlNotchMeanEst;

  /* SignalConversion: '<S24>/Copy' incorporates:
   *  Constant: '<S108>/Constant3'
   *  Constant: '<S30>/Rated Payload, tonne'
   *  Product: '<S108>/Divide1'
   *  Product: '<S108>/Multiply1'
   *  Sum: '<S32>/Sum2'
   */
  toa_wl00_B->toa_outUnsecPayloadNormUp = ((1.0F /
    toa_wl00_M->toa_wl00_catParameters_si_RAM_p->toa_ratedPayload) *
    (toa_wl00_B->toa_pfwUnsecBoundUpper - toa_wl00_B->toa_targetPayloadFinal)) *
    100.0F;

  /* Outport: '<Root>/Unsecured_Payload_Upper_Bound_Norm' */
  *toa_wl00_Y_Unsecured_Payload_Upper_Bound_Norm =
    toa_wl00_B->toa_outUnsecPayloadNormUp;

  /* Sum: '<S228>/Subtract' */
  toa_wl00_B->toa_pfwUnsecBoundLower = toa_wl00_B->toa_pfwNlNotchMeanEst -
    toa_wl00_B->toa_statPayloadSecureOneSize;

  /* SignalConversion: '<S7>/Copy' incorporates:
   *  Constant: '<S109>/Constant3'
   *  Constant: '<S30>/Rated Payload, tonne'
   *  Product: '<S109>/Divide1'
   *  Product: '<S109>/Multiply1'
   *  Sum: '<S32>/Sum3'
   */
  toa_wl00_B->toa_outUnsecPayloadNormLow = ((1.0F /
    toa_wl00_M->toa_wl00_catParameters_si_RAM_p->toa_ratedPayload) *
    (toa_wl00_B->toa_pfwUnsecBoundLower - toa_wl00_B->toa_targetPayloadFinal)) *
    100.0F;

  /* Outport: '<Root>/Unsecured_Payload_Lower_Bound_Norm' */
  *toa_wl00_Y_Unsecured_Payload_Lower_Bound_Norm =
    toa_wl00_B->toa_outUnsecPayloadNormLow;

  /* SignalConversion: '<S9>/Copy' */
  toa_wl00_B->toa_outUnsecPayloadStatus = toa_wl00_B->toa_pfwUnsecStatus;

  /* Outport: '<Root>/Unsecured_PFW_Status' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion4'
   */
  *toa_wl00_Y_Unsecured_PFW_Status = (uint8_t)
    toa_wl00_B->toa_outUnsecPayloadStatus;

  /* SignalConversion: '<S195>/Copy' incorporates:
   *  Constant: '<S202>/Secure Load Buffer Angle, degrees'
   *  Constant: '<S220>/sliding threshold, degrees'
   *  MinMax: '<S143>/MinMax1'
   *  Sum: '<S202>/Add'
   */
  toa_wl00_B->toa_pfwSecMinBucketAng = fmaxf(7.0F, rtb_Switch_oqyb + 6.0F);

  /* SignalConversion: '<S13>/Copy' */
  toa_wl00_B->toa_outMinSecBucketAng = toa_wl00_B->toa_pfwSecMinBucketAng;

  /* Outport: '<Root>/Min_Secure_Bucket_Angle' */
  *toa_wl00_Y_Min_Secure_Bucket_Angle = toa_wl00_B->toa_outMinSecBucketAng;

  /* SignalConversion: '<S39>/Copy' incorporates:
   *  SignalConversion: '<S26>/Signal Conversion1'
   */
  toa_wl00_B->toa_imuRawEefAcclX = rtb_applycalibration[0];

  /* SignalConversion: '<S40>/Copy' incorporates:
   *  SignalConversion: '<S26>/Signal Conversion'
   */
  toa_wl00_B->toa_imuRawEefAcclY = rtb_applycalibration[1];

  /* SignalConversion: '<S41>/Copy' incorporates:
   *  SignalConversion: '<S26>/Signal Conversion2'
   */
  toa_wl00_B->toa_imuRawEefAcclZ = rtb_applycalibration[2];

  /* SignalConversion: '<S42>/Copy' incorporates:
   *  SignalConversion: '<S26>/Signal Conversion4'
   */
  toa_wl00_B->toa_imuNeefGravX = rtb_MathFunction_dgrl[0];

  /* SignalConversion: '<S43>/Copy' incorporates:
   *  SignalConversion: '<S26>/Signal Conversion3'
   */
  toa_wl00_B->toa_imuNeefGravY = rtb_MathFunction_dgrl[1];

  /* SignalConversion: '<S44>/Copy' incorporates:
   *  SignalConversion: '<S26>/Signal Conversion5'
   */
  toa_wl00_B->toa_imuNeefGravZ = rtb_MathFunction_dgrl[2];

  /* MATLAB Function: '<S26>/rotation matrix calc from two vectors' */
  /*  Should match output of: */
  /*      vrrotvec2mat(vrrotvec(level_vec_meas, level_vec_act)) */
  /* MATLAB Function 'Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/rotation matrix calc from two vectors': '<S52>:1' */
  /* '<S52>:1:5' if all(level_vec_meas == level_vec_act) */
  FixPtRelationalOperator_meyn = true;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 3)) {
    if (!(rtb_MathFunction_dgrl[i] == toa_wl00_ConstP.levelgravityaccel_Value[i]))
    {
      FixPtRelationalOperator_meyn = false;
      exitg1 = true;
    } else {
      i++;
    }
  }

  if (FixPtRelationalOperator_meyn) {
    /*  No transform necessary, return identity matrix */
    /* '<S52>:1:7' rotAxis = single([9999; 9999; 9999]); */
    toa_wl00_B->toa_grav_rotAxis[0] = 9999.0F;
    toa_wl00_B->toa_grav_rotAxis[1] = 9999.0F;
    toa_wl00_B->toa_grav_rotAxis[2] = 9999.0F;

    /* '<S52>:1:8' angle = single(9999); */
    toa_wl00_B->toa_grav_angle = 9999.0F;

    /* '<S52>:1:9' rotMatrix = single(eye(3)); */
    for (i = 0; i < 9; i++) {
      I[i] = 0;
    }

    I[0] = 1;
    I[4] = 1;
    I[8] = 1;
    for (i = 0; i < 9; i++) {
      toa_wl00_B->toa_grav_rotMatrix[i] = I[i];
    }
  } else {
    /* '<S52>:1:13' a = level_vec_meas; */
    /* '<S52>:1:14' b = level_vec_act; */
    /* '<S52>:1:16' cp = cross(a, b); */
    toa_wl00_B->toa_grav_rotAxis[0] = (rtb_MathFunction_dgrl[1] * 0.0F) -
      (rtb_MathFunction_dgrl[2] * -9.80665F);
    toa_wl00_B->toa_grav_rotAxis[1] = (rtb_MathFunction_dgrl[2] * 0.0F) -
      (rtb_MathFunction_dgrl[0] * 0.0F);
    toa_wl00_B->toa_grav_rotAxis[2] = (rtb_MathFunction_dgrl[0] * -9.80665F) -
      (rtb_MathFunction_dgrl[1] * 0.0F);

    /* '<S52>:1:17' cpNorm = norm(cp); */
    filtered_krzt = 1.29246971E-26F;
    filtered_esvw = fabsf(toa_wl00_B->toa_grav_rotAxis[0]);
    if (filtered_esvw > 1.29246971E-26F) {
      cpNorm = 1.0F;
      filtered_krzt = filtered_esvw;
    } else {
      t = filtered_esvw / 1.29246971E-26F;
      cpNorm = t * t;
    }

    filtered_esvw = fabsf(toa_wl00_B->toa_grav_rotAxis[1]);
    if (filtered_esvw > filtered_krzt) {
      t = filtered_krzt / filtered_esvw;
      cpNorm = ((cpNorm * t) * t) + 1.0F;
      filtered_krzt = filtered_esvw;
    } else {
      t = filtered_esvw / filtered_krzt;
      cpNorm += t * t;
    }

    filtered_esvw = fabsf(toa_wl00_B->toa_grav_rotAxis[2]);
    if (filtered_esvw > filtered_krzt) {
      t = filtered_krzt / filtered_esvw;
      cpNorm = ((cpNorm * t) * t) + 1.0F;
      filtered_krzt = filtered_esvw;
    } else {
      t = filtered_esvw / filtered_krzt;
      cpNorm += t * t;
    }

    cpNorm = filtered_krzt * sqrtf(cpNorm);

    /* '<S52>:1:19' rotAxis = cp/cpNorm; */
    /* '<S52>:1:20' angle_rad = atan(cpNorm/dot(a, b)); */
    toa_wl00_B->toa_grav_rotAxis[0] /= cpNorm;
    toa_wl00_B->toa_grav_rotAxis[1] /= cpNorm;
    toa_wl00_B->toa_grav_rotAxis[2] /= cpNorm;
    filtered_esvw = atanf(cpNorm / (((rtb_MathFunction_dgrl[0] * 0.0F) +
      (rtb_MathFunction_dgrl[1] * -9.80665F)) + (rtb_MathFunction_dgrl[2] * 0.0F)));

    /* '<S52>:1:21' angle = angle_rad * 180.0 / pi; */
    toa_wl00_B->toa_grav_angle = (filtered_esvw * 180.0F) / 3.14159274F;

    /*  Form rotation matrix */
    /* '<S52>:1:24' crossProductMatrix = [ */
    /* '<S52>:1:25'     0,          -rotAxis(3),  rotAxis(2); */
    /* '<S52>:1:26'      rotAxis(3), 0,          -rotAxis(1); */
    /* '<S52>:1:27'     -rotAxis(2), rotAxis(1),  0 */
    /* '<S52>:1:28' ]; */
    /* '<S52>:1:29' tensorProduct = rotAxis * transpose(rotAxis); */
    /* '<S52>:1:30' rotMatrix = cos(angle_rad) * eye(3) + sin(angle_rad) * crossProductMatrix + ... */
    /* '<S52>:1:31'     (1 - cos(angle_rad)) * tensorProduct; */
    filtered_krzt = cosf(filtered_esvw);
    filtered_esvw = sinf(filtered_esvw);
    rtb_rotMatrix[0] = filtered_esvw * 0.0F;
    rtb_rotMatrix[3] = filtered_esvw * (-toa_wl00_B->toa_grav_rotAxis[2]);
    rtb_rotMatrix[6] = filtered_esvw * toa_wl00_B->toa_grav_rotAxis[1];
    rtb_rotMatrix[1] = filtered_esvw * toa_wl00_B->toa_grav_rotAxis[2];
    rtb_rotMatrix[4] = filtered_esvw * 0.0F;
    rtb_rotMatrix[7] = filtered_esvw * (-toa_wl00_B->toa_grav_rotAxis[0]);
    rtb_rotMatrix[2] = filtered_esvw * (-toa_wl00_B->toa_grav_rotAxis[1]);
    rtb_rotMatrix[5] = filtered_esvw * toa_wl00_B->toa_grav_rotAxis[0];
    rtb_rotMatrix[8] = filtered_esvw * 0.0F;
    for (i = 0; i < 3; i++) {
      tmp_0[i] = toa_wl00_B->toa_grav_rotAxis[i] * toa_wl00_B->toa_grav_rotAxis
        [0];
      tmp_0[i + 3] = toa_wl00_B->toa_grav_rotAxis[i] *
        toa_wl00_B->toa_grav_rotAxis[1];
      tmp_0[i + 6] = toa_wl00_B->toa_grav_rotAxis[i] *
        toa_wl00_B->toa_grav_rotAxis[2];
    }

    i = 0;
    for (i_0 = 0; i_0 < 3; i_0++) {
      toa_wl00_B->toa_grav_rotMatrix[i] = ((((real32_T)b_0[i]) * filtered_krzt)
        + rtb_rotMatrix[i]) + (tmp_0[i] * (1.0F - filtered_krzt));
      toa_wl00_B->toa_grav_rotMatrix[i + 1] = ((((real32_T)b_0[i + 1]) *
        filtered_krzt) + rtb_rotMatrix[i + 1]) + (tmp_0[i + 1] * (1.0F -
        filtered_krzt));
      toa_wl00_B->toa_grav_rotMatrix[i + 2] = ((((real32_T)b_0[i + 2]) *
        filtered_krzt) + rtb_rotMatrix[i + 2]) + (tmp_0[i + 2] * (1.0F -
        filtered_krzt));
      i += 3;
    }
  }

  /* End of MATLAB Function: '<S26>/rotation matrix calc from two vectors' */

  /* MATLAB Function: '<S26>/euler angles from rot matrix' */
  /*    Input:  3x3 rotation matrix */
  /*    Output: 1x3 vector of euler angles in degrees */
  /* MATLAB Function 'Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/euler angles from rot matrix': '<S49>:1' */
  /* '<S49>:1:4' rotations = zeros(1,3); */
  toa_wl00_B->toa_grav_angles[0] = 0.0;
  toa_wl00_B->toa_grav_angles[1] = 0.0;
  toa_wl00_B->toa_grav_angles[2] = 0.0;

  /* '<S49>:1:5' rotations(1) = atan2(rotMatrix(3,2),rotMatrix(3,3)); */
  toa_wl00_B->toa_grav_angles[0] = rt_atan2f_snf(toa_wl00_B->toa_grav_rotMatrix
    [5], toa_wl00_B->toa_grav_rotMatrix[8]);

  /* '<S49>:1:6' rotations(2) = atan2(-rotMatrix(3,1), (sqrt((rotMatrix(3,2)^2)+(rotMatrix(3,3)^2)))); */
  toa_wl00_B->toa_grav_angles[1] = rt_atan2f_snf(-toa_wl00_B->
    toa_grav_rotMatrix[2], sqrtf((toa_wl00_B->toa_grav_rotMatrix[5] *
    toa_wl00_B->toa_grav_rotMatrix[5]) + (toa_wl00_B->toa_grav_rotMatrix[8] *
    toa_wl00_B->toa_grav_rotMatrix[8])));

  /* '<S49>:1:7' rotations(3) = atan2(rotMatrix(2,1),rotMatrix(1,1)); */
  toa_wl00_B->toa_grav_angles[2] = rt_atan2f_snf(toa_wl00_B->toa_grav_rotMatrix
    [1], toa_wl00_B->toa_grav_rotMatrix[0]);

  /*  convert back to degrees */
  /* '<S49>:1:9' for i=1:size(rotations,2) */
  /* '<S49>:1:10' rotations(i) = 180*rotations(i)/pi; */
  toa_wl00_B->toa_grav_angles[0] = (180.0 * toa_wl00_B->toa_grav_angles[0]) /
    3.1415926535897931;

  /* '<S49>:1:10' rotations(i) = 180*rotations(i)/pi; */
  toa_wl00_B->toa_grav_angles[1] = (180.0 * toa_wl00_B->toa_grav_angles[1]) /
    3.1415926535897931;

  /* '<S49>:1:10' rotations(i) = 180*rotations(i)/pi; */
  toa_wl00_B->toa_grav_angles[2] = (180.0 * toa_wl00_B->toa_grav_angles[2]) /
    3.1415926535897931;

  /* SignalConversion: '<S62>/Copy' incorporates:
   *  Constant: '<S27>/Constant'
   *  Gain: '<S27>/convert "proper acceleration" to gravity1'
   *  Gain: '<S66>/Gain'
   *  Sum: '<S27>/Add'
   *  Switch: '<S68>/Switch'
   *  Switch: '<S70>/Switch'
   *  Trigonometry: '<S27>/Trigonometric Function'
   */
  toa_wl00_B->toa_imuNeefPitch = -((57.2957802F * rt_atan2f_snf
    (rtb_MathFunction_dgrl[1], rtb_MathFunction_dgrl[0])) + 90.0);

  /* Sum: '<S63>/Sum of Elements' incorporates:
   *  Math: '<S63>/Math Function'
   *  Switch: '<S68>/Switch'
   *  Switch: '<S70>/Switch'
   */
  filtered_krzt = (rtb_MathFunction_dgrl[0] * rtb_MathFunction_dgrl[0]) +
    (rtb_MathFunction_dgrl[1] * rtb_MathFunction_dgrl[1]);

  /* Math: '<S63>/Math Function1' incorporates:
   *  Sum: '<S63>/Sum of Elements'
   *
   * About '<S63>/Math Function1':
   *  Operator: sqrt
   */
  if (filtered_krzt < 0.0F) {
    toa_wl00_B->toa_grav_neef_xy_mag = -sqrtf(fabsf(filtered_krzt));
  } else {
    toa_wl00_B->toa_grav_neef_xy_mag = sqrtf(filtered_krzt);
  }

  /* End of Math: '<S63>/Math Function1' */

  /* SignalConversion: '<S77>/Copy' */
  toa_wl00_B->toa_sfuncOutRawDist = rtb_SquareRoot;

  /* SignalConversion: '<S80>/Copy' incorporates:
   *  DataTypeConversion: '<S31>/Data Type Conversion7'
   */
  toa_wl00_B->toa_rawDist = (real32_T)toa_wl00_B->toa_sfuncOutRawDist;

  /* MultiPortSwitch: '<S112>/Indexed switch' */
  if (!toa_wl00_B->toa_pfwSecLatch) {
    /* SignalConversion: '<S101>/Copy' incorporates:
     *  Constant: '<S112>/Constant'
     */
    toa_wl00_B->toa_sendPayloadType = TipAssistPayloadType_t_LIVE;
  } else {
    /* SignalConversion: '<S101>/Copy' incorporates:
     *  Constant: '<S112>/Constant1'
     */
    toa_wl00_B->toa_sendPayloadType = TipAssistPayloadType_t_PSEUDO_FRICTIONLESS;
  }

  /* End of MultiPortSwitch: '<S112>/Indexed switch' */

  /* Product: '<S117>/Product2' incorporates:
   *  Constant: '<S117>/Exprected TOA Measurement Precision (1 sigma), pct of rated payload'
   *  Constant: '<S30>/Rated Payload, tonne'
   */
  rtb_Subtract = 0.02 * toa_wl00_M->
    toa_wl00_catParameters_si_RAM_p->toa_ratedPayload;

  /* Math: '<S117>/Math Function1' */
  rtb_toa_tilt_sens_to_bucket_ang_by_id_sfunc = rtb_Subtract * rtb_Subtract;

  /* Product: '<S117>/Product' incorporates:
   *  Constant: '<S117>/Exprected CPM Precision (1 sigma), pct of rated payload'
   *  Constant: '<S30>/Rated Payload, tonne'
   */
  rtb_Subtract = toa_wl00_M->toa_wl00_catParameters_si_RAM_p->toa_ratedPayload *
    0.01;

  /* Math: '<S117>/Math Function' */
  rtb_Subtract *= rtb_Subtract;

  /* Product: '<S117>/Product1' incorporates:
   *  Inport: '<Root>/CPM_Pass_Count'
   */
  rtb_SquareRoot = rtb_Subtract * ((real_T)toa_wl00_U_CPM_Pass_Count);

  /* Sum: '<S117>/Add' incorporates:
   *  Product: '<S117>/Product3'
   */
  rtb_SquareRoot += rtb_toa_tilt_sens_to_bucket_ang_by_id_sfunc;

  /* SignalConversion: '<S119>/Copy' incorporates:
   *  Sqrt: '<S117>/Square Root'
   */
  toa_wl00_B->toa_targetCompMargin = sqrt(rtb_SquareRoot);

  /* SignalConversion: '<S118>/Copy' incorporates:
   *  Sum: '<S117>/Subtract'
   */
  toa_wl00_B->toa_targetPayloadPostComp = toa_wl00_B->toa_targetPayloadPreComp -
    toa_wl00_B->toa_targetCompMargin;

  /* SignalConversion: '<S169>/Copy' incorporates:
   *  Sum: '<S229>/Subtract1'
   */
  toa_wl00_B->toa_statPayloadSecureTwoLower = filtered_d1c3 -
    toa_wl00_B->toa_statPayloadSecureTwoSize;

  /* SignalConversion: '<S171>/Copy' */
  toa_wl00_B->toa_statPayloadNlNotchOneUp = toa_wl00_B->toa_pfwUnsecBoundUpper;

  /* SignalConversion: '<S172>/Copy' */
  toa_wl00_B->toa_statPayloadNlNotchOneSize =
    toa_wl00_B->toa_statPayloadSecureOneSize;

  /* MATLAB Function: '<S228>/Two Sided Confidence Limit' incorporates:
   *  Constant: '<S228>/Constant'
   */
  toa_wl00_TwoSidedConfidenceLimit(0.997, toa_wl00_B->toa_pfwNlNotchStDevEst,
    &toa_wl00_B->toa_statPayloadSecureOneSize);

  /* SignalConversion: '<S173>/Copy' incorporates:
   *  Sum: '<S228>/Add1'
   */
  toa_wl00_B->toa_statPayloadNlNotchTwoUp =
    toa_wl00_B->toa_statPayloadSecureOneSize + toa_wl00_B->toa_pfwNlNotchMeanEst;

  /* SignalConversion: '<S174>/Copy' */
  toa_wl00_B->toa_statPayloadNlNotchTwoSize =
    toa_wl00_B->toa_statPayloadSecureOneSize;

  /* SignalConversion: '<S175>/Copy' incorporates:
   *  Sum: '<S228>/Subtract1'
   */
  toa_wl00_B->toa_statPayloadNlNotchTwoLow = toa_wl00_B->toa_pfwNlNotchMeanEst -
    toa_wl00_B->toa_statPayloadSecureOneSize;

  /* MATLAB Function: '<S226>/MATLAB Function' */
  /* MATLAB Function 'Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Variance Anti-Noise Filter2/MATLAB Function': '<S291>:1' */
  /* '<S291>:1:4' if isempty(lastSample) || reset */
  if ((!toa_wl00_DWork->lastSample_not_empty) || FixPtRelationalOperator) {
    /* '<S291>:1:5' lastSample = single(u); */
    toa_wl00_DWork->lastSample = filtered;
    toa_wl00_DWork->lastSample_not_empty = true;
  }

  /* '<S291>:1:7' y = (u + lastSample) / 2; */
  toa_wl00_B->toa_pfwPayloadFiltFinal = (filtered + toa_wl00_DWork->lastSample) /
    2.0F;

  /* '<S291>:1:8' lastSample = u; */
  toa_wl00_DWork->lastSample = filtered;

  /* End of MATLAB Function: '<S226>/MATLAB Function' */

  /* MATLAB Function: '<S222>/MATLAB Function1' incorporates:
   *  Constant: '<S143>/Constant2'
   *  Constant: '<S222>/Constant2'
   */
  toa_wl00_MATLABFunction(0.02, 0.6, &rtb_Subtract);

  /* MATLAB Function: '<S222>/Two Sided St. Dev. from Bound' incorporates:
   *  Constant: '<S222>/Constant'
   *  Constant: '<S222>/Constant1'
   *  Constant: '<S30>/Rated Payload, tonne'
   *  Product: '<S222>/Product'
   */
  toa_wl00_TwoSidedStDevfromBound(0.997F,
    toa_wl00_M->toa_wl00_catParameters_si_RAM_p->toa_ratedPayload * 0.3F,
    &toa_wl00_B->toa_statPayloadNlOneSize);

  /* MATLAB Function: '<S222>/MATLAB Function' incorporates:
   *  Math: '<S222>/Math Function'
   */
  toa_wl00_MATLABFunction_fw1r(toa_wl00_B->toa_pfwPayloadFiltFinal, rtb_Subtract,
    FixPtRelationalOperator, toa_wl00_B->toa_statPayloadNlOneSize *
    toa_wl00_B->toa_statPayloadNlOneSize,
    &toa_wl00_B->toa_statPayloadSecureOneSize,
    &toa_wl00_B->toa_statPayloadNlOneSize,
    &toa_wl00_DWork->sf_MATLABFunction_iawv);

  /* SignalConversion: '<S184>/Copy' */
  toa_wl00_B->toa_pfwNlStDevEst = toa_wl00_B->toa_statPayloadNlOneSize;

  /* MATLAB Function: '<S227>/One Sided Confidence Limit' incorporates:
   *  Constant: '<S227>/Constant'
   */
  toa_wl00_OneSidedConfidenceLimit(0.997, toa_wl00_B->toa_pfwNlStDevEst,
    &toa_wl00_B->toa_statPayloadNlOneSize);

  /* SignalConversion: '<S183>/Copy' */
  toa_wl00_B->toa_pfwNlMeanEst = toa_wl00_B->toa_statPayloadSecureOneSize;

  /* SignalConversion: '<S176>/Copy' incorporates:
   *  Sum: '<S227>/Add'
   */
  toa_wl00_B->toa_statPayloadNlOneUp = toa_wl00_B->toa_statPayloadNlOneSize +
    toa_wl00_B->toa_pfwNlMeanEst;

  /* MATLAB Function: '<S227>/Two Sided Confidence Limit' incorporates:
   *  Constant: '<S227>/Constant'
   */
  toa_wl00_TwoSidedConfidenceLimit(0.997, toa_wl00_B->toa_pfwNlStDevEst,
    &toa_wl00_B->toa_statPayloadSecureOneSize);

  /* SignalConversion: '<S178>/Copy' incorporates:
   *  Sum: '<S227>/Add1'
   */
  toa_wl00_B->toa_statPayloadNlTwoUp = toa_wl00_B->toa_statPayloadSecureOneSize
    + toa_wl00_B->toa_pfwNlMeanEst;

  /* SignalConversion: '<S179>/Copy' */
  toa_wl00_B->toa_statPayloadNlTwoSize =
    toa_wl00_B->toa_statPayloadSecureOneSize;

  /* SignalConversion: '<S181>/Copy' incorporates:
   *  Sum: '<S227>/Subtract1'
   */
  toa_wl00_B->toa_statPayloadNlTwoLow = toa_wl00_B->toa_pfwNlMeanEst -
    toa_wl00_B->toa_statPayloadSecureOneSize;

  /* SignalConversion: '<S182>/Copy' incorporates:
   *  Sum: '<S227>/Subtract'
   */
  toa_wl00_B->toa_statPayloadNlOneLow = toa_wl00_B->toa_pfwNlMeanEst -
    toa_wl00_B->toa_statPayloadNlOneSize;

  /* MATLAB Function: '<S229>/One Sided Confidence Limit' incorporates:
   *  Constant: '<S229>/Constant'
   */
  toa_wl00_OneSidedConfidenceLimit(0.997, rtb_resetSwitch_cwhz,
    &toa_wl00_B->toa_statPayloadSecureOneSize);

  /* SignalConversion: '<S187>/Copy' incorporates:
   *  Sum: '<S229>/Add'
   */
  toa_wl00_B->toa_statPayloadSecureOneUpper =
    toa_wl00_B->toa_statPayloadSecureOneSize + filtered_d1c3;

  /* SignalConversion: '<S188>/Copy' incorporates:
   *  Sum: '<S229>/Subtract'
   */
  toa_wl00_B->toa_statPayloadSecureOneLower = filtered_d1c3 -
    toa_wl00_B->toa_statPayloadSecureOneSize;

  /* SignalConversion: '<S190>/Copy' incorporates:
   *  Sum: '<S229>/Add1'
   */
  toa_wl00_B->toa_statPayloadSecureTwoUpper =
    toa_wl00_B->toa_statPayloadSecureTwoSize + filtered_d1c3;

  /* SignalConversion: '<S200>/Copy' */
  toa_wl00_B->toa_statPayloadNlNotchOneLow = toa_wl00_B->toa_pfwUnsecBoundLower;

  /* Update for Memory: '<S283>/Memory 1' incorporates:
   *  Constant: '<S283>/FixPt Constant'
   */
  toa_wl00_DWork->Memory1_PreviousInput = 0U;

  /* Update for Memory: '<S283>/Memory 2' */
  toa_wl00_DWork->Memory2_PreviousInput = rtb_MaxSwitch;

  /* Update for UnitDelay: '<S58>/Unit Delay' incorporates:
   *  Constant: '<S58>/FirstLoop'
   */
  toa_wl00_DWork->UnitDelay_DSTATE_mvg5 = 1U;

  /* Update for UnitDelay: '<S56>/Unit Delay1' */
  toa_wl00_DWork->UnitDelay1_DSTATE[0] = rtb_Sum1[0];

  /* Update for UnitDelay: '<S57>/Unit Delay1' */
  toa_wl00_DWork->UnitDelay1_DSTATE_mga0[0] = rtb_InitToInput[0];

  /* Update for UnitDelay: '<S56>/Unit Delay1' */
  toa_wl00_DWork->UnitDelay1_DSTATE[1] = rtb_Sum1[1];

  /* Update for UnitDelay: '<S57>/Unit Delay1' */
  toa_wl00_DWork->UnitDelay1_DSTATE_mga0[1] = rtb_InitToInput[1];

  /* Update for UnitDelay: '<S56>/Unit Delay1' */
  toa_wl00_DWork->UnitDelay1_DSTATE[2] = rtb_Sum1[2];

  /* Update for UnitDelay: '<S57>/Unit Delay1' */
  toa_wl00_DWork->UnitDelay1_DSTATE_mga0[2] = rtb_InitToInput[2];

  /* Update for UnitDelay: '<S60>/Unit Delay' incorporates:
   *  Constant: '<S60>/FirstLoop'
   */
  toa_wl00_DWork->UnitDelay_DSTATE_j5gs = 1U;

  /* Update for UnitDelay: '<S213>/Delay Input1'
   *
   * Block description for '<S213>/Delay Input1':
   *
   *  Store in Global RAM
   */
  toa_wl00_DWork->DelayInput1_DSTATE = rtb_LogicalOperator;

  /* Update for Delay: '<S202>/Delay2' */
  toa_wl00_DWork->Delay2_DSTATE = rtb_Switch_oqyb;

  /* Update for UnitDelay: '<S231>/Unit Delay' */
  toa_wl00_DWork->UnitDelay_DSTATE = rtb_Switch_oqyb;

  /* Update for Memory: '<S232>/Memory 1' incorporates:
   *  Constant: '<S232>/FixPt Constant'
   */
  toa_wl00_DWork->Memory1_PreviousInput_ddl0 = 0U;

  /* Update for Memory: '<S232>/Memory 2' */
  toa_wl00_DWork->Memory2_PreviousInput_i53e = rtb_MaxSwitch_jl40;

  /* Update for Memory: '<S278>/Memory 1' incorporates:
   *  Constant: '<S278>/FixPt Constant'
   */
  toa_wl00_DWork->Memory1_PreviousInput_gnui = 0U;

  /* Update for Memory: '<S278>/Memory 2' */
  toa_wl00_DWork->Memory2_PreviousInput_pgwc = rtb_MaxSwitch_ankt;

  /* Update for UnitDelay: '<S205>/Delay Input1'
   *
   * Block description for '<S205>/Delay Input1':
   *
   *  Store in Global RAM
   */
  toa_wl00_DWork->DelayInput1_DSTATE_prcl = rtb_LogicalOperator_bt32;

  /* Update for UnitDelay: '<S219>/Unit Delay1' */
  toa_wl00_DWork->UnitDelay1_DSTATE_fp5d = rtb_kNpermm2tokPa;

  /* Update for UnitDelay: '<S280>/Unit Delay' incorporates:
   *  Constant: '<S280>/FirstLoop'
   */
  toa_wl00_DWork->UnitDelay_DSTATE_bw1s = 1U;

  /* Update for UnitDelay: '<S266>/Unit Delay' */
  toa_wl00_DWork->UnitDelay_DSTATE_fett = rtb_resetSwitch_ifkf;

  /* Update for UnitDelay: '<S267>/Timer' */
  toa_wl00_DWork->Timer_DSTATE = rtb_EnableCheck;

  /* Update for UnitDelay: '<S268>/Timer' */
  toa_wl00_DWork->Timer_DSTATE_dme3 = rtb_EnableCheck_hpd1;

  /* Update for Delay: '<S257>/Delay' */
  toa_wl00_DWork->Delay_DSTATE_obnz = rtb_LogicalOperator8;

  /* Update for Delay: '<S143>/Delay' */
  toa_wl00_DWork->Delay_DSTATE = rtb_resetSwitch_cwhz;

  /* Update for UnitDelay: '<S208>/Timer' */
  toa_wl00_DWork->Timer_DSTATE_jrr0 = rtb_EnableCheck_hb3g;

  /* Update for UnitDelay: '<S214>/Unit Delay' */
  toa_wl00_DWork->UnitDelay_DSTATE_hioq = filtered_d1c3;

  /* Update for UnitDelay: '<S216>/Unit Delay' */
  toa_wl00_DWork->UnitDelay_DSTATE_nds1 = rtb_resetSwitch_ebtw;

  /* Update for UnitDelay: '<S154>/Unit Delay1' */
  toa_wl00_DWork->UnitDelay1_DSTATE_bcfn = filtered_idbq;

  /* Update for UnitDelay: '<S163>/Unit Delay' incorporates:
   *  Constant: '<S163>/FirstLoop'
   */
  toa_wl00_DWork->UnitDelay_DSTATE_fdvn = 1U;

  /* Update for UnitDelay: '<S152>/Delay Input1'
   *
   * Block description for '<S152>/Delay Input1':
   *
   *  Store in Global RAM
   */
  toa_wl00_DWork->DelayInput1_DSTATE_nzby = rtb_LogicalOperator;

  /* Update for UnitDelay: '<S215>/Unit Delay' */
  toa_wl00_DWork->UnitDelay_DSTATE_jlpe = rtb_resetSwitch_cwhz;

  /* Update for Delay: '<S153>/Resettable Delay' */
  toa_wl00_DWork->icLoad = 0U;
  toa_wl00_DWork->ResettableDelay_DSTATE = rtb_TSamp;

  /* Update for UnitDelay: '<S156>/Unit Delay1' */
  toa_wl00_DWork->UnitDelay1_DSTATE_bo33 = rtb_Sum1_gemz;

  /* Update for UnitDelay: '<S167>/Unit Delay' incorporates:
   *  Constant: '<S167>/FirstLoop'
   */
  toa_wl00_DWork->UnitDelay_DSTATE_pigm = 1U;

  /* Update for UnitDelay: '<S155>/Unit Delay1' */
  toa_wl00_DWork->UnitDelay1_DSTATE_e2d2 = Sum1_enp4;

  /* Update for UnitDelay: '<S165>/Unit Delay' incorporates:
   *  Constant: '<S165>/FirstLoop'
   */
  toa_wl00_DWork->UnitDelay_DSTATE_kdv5 = 1U;
}

/* Model initialize function */
void toa_wl00_initialize(RT_MODEL_toa_wl00 *const toa_wl00_M, boolean_T
  *toa_wl00_U_Invalidate_Outputs, real32_T *toa_wl00_U_Lift_Valve_Command,
  real32_T *toa_wl00_U_Tilt_Valve_Command, real32_T *toa_wl00_U_Tilt_Extension,
  real32_T *toa_wl00_U_Lift_Angle, real32_T *toa_wl00_U_Lift_HE_Pressure,
  real32_T *toa_wl00_U_Lift_RE_Pressure, real32_T *toa_wl00_U_Tilt_HE_Pressure,
  real32_T *toa_wl00_U_Tilt_RE_Pressure, real32_T *toa_wl00_U_Steering_Angle,
  real32_T *toa_wl00_U_Tool_Mass, real32_T *toa_wl00_U_PCS_Truck_Target,
  real32_T *toa_wl00_U_PCS_Truck_Start_Weight, uint8_t
  *toa_wl00_U_PCS_Bucket_Current_Weight_Accuracy, real32_T
  *toa_wl00_U_PCS_Bucket_Current_Weight, uint8_t *toa_wl00_U_PCS_Tipoff_Mode,
  real32_T *toa_wl00_U_EEF_IMU_AccelX, real32_T *toa_wl00_U_EEF_IMU_AccelY,
  real32_T *toa_wl00_U_EEF_IMU_AccelZ, real32_T *toa_wl00_U_Zero_Offset,
  real32_T *toa_wl00_U_Simple_Cal_Factor, real32_T *toa_wl00_U_IMU_Pitch_Cal,
  real32_T *toa_wl00_U_Bucket_Angle, boolean_T *toa_wl00_U_Unlatch_Trigger,
  real32_T *toa_wl00_U_Anchor_Zero_Offset, real32_T *toa_wl00_U_Anchor_Factor,
  uint16_t *toa_wl00_U_CPM_Pass_Count, real32_T *toa_wl00_U_Lift_Norm_Angle,
  real32_T *toa_wl00_U_Lift_Norm_Length, real32_T *toa_wl00_U_Tilt_Norm_Angle,
  real32_T *toa_wl00_U_Tilt_Norm_Length, real32_T *toa_wl00_U_Friction_Mu,
  real32_T *toa_wl00_U_Friction_Offset, real32_T *toa_wl00_Y_Tilt_Sensitivity,
  real32_T *toa_wl00_Y_Tilt_HE_Pressure_Out, real32_T
  *toa_wl00_Y_Arbitrated_Payload_Norm_Error, uint8_t *toa_wl00_Y_Weigh_Status,
  real32_T *toa_wl00_Y_Payload_Norm_Stdev, uint8_t
  *toa_wl00_Y_PCS_Bucket_Current_Weight_Accuracy_Out, real32_T
  *toa_wl00_Y_PCS_Bucket_Current_Weight_Norm_Error_Out, uint8_t
  *toa_wl00_Y_Tipoff_Assist_Adv_Error_Code, real32_T *toa_wl00_Y_Spill_Rate_Norm,
  real32_T *toa_wl00_Y_Bucket_Payload_Target, real32_T
  *toa_wl00_Y_Payload_Send_To_CPM, uint8_t
  *toa_wl00_Y_Payload_Status_Send_To_CPM, real32_T
  *toa_wl00_Y_Unsecured_Payload_Upper_Bound_Norm, real32_T
  *toa_wl00_Y_Unsecured_Payload_Lower_Bound_Norm, uint8_t
  *toa_wl00_Y_Unsecured_PFW_Status, real32_T *toa_wl00_Y_Min_Secure_Bucket_Angle)
{
  D_Work_toa_wl00 *toa_wl00_DWork = ((D_Work_toa_wl00 *) toa_wl00_M->dwork);
  BlockIO_toa_wl00 *toa_wl00_B = ((BlockIO_toa_wl00 *) toa_wl00_M->blockIO);

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* block I/O */
  (void) memset(((void *) toa_wl00_B), 0,
                sizeof(BlockIO_toa_wl00));

  {
    toa_wl00_B->toa_pfwSecStatus = TipAssistSecPfwStatus_t_INVALID;
    toa_wl00_B->toa_outPfwStat = TipAssistSecPfwStatus_t_INVALID;
    toa_wl00_B->toa_lwStatus = TipAssistLiveWeighStatus_t_VALID;
    toa_wl00_B->toa_pfwUnsecStatus = TipAssistUnsecPfwStatus_t_INVALID;
    toa_wl00_B->toa_outUnsecPayloadStatus = TipAssistUnsecPfwStatus_t_INVALID;
    toa_wl00_B->toa_outAdvErrorCode = TipAssistAdvEcmError_t_NO_ERROR;
    toa_wl00_B->toa_sendPayloadType = TipAssistPayloadType_t_LIVE;
    toa_wl00_B->toa_outSendCpmStatus = TipAssistSendCpmStatus_t_INVALID;
  }

  /* states (dwork) */
  (void) memset((void *)toa_wl00_DWork, 0,
                sizeof(D_Work_toa_wl00));

  /* external inputs */
  *toa_wl00_U_Invalidate_Outputs = false;
  *toa_wl00_U_Lift_Valve_Command = 0.0F;
  *toa_wl00_U_Tilt_Valve_Command = 0.0F;
  *toa_wl00_U_Tilt_Extension = 0.0F;
  *toa_wl00_U_Lift_Angle = 0.0F;
  *toa_wl00_U_Lift_HE_Pressure = 0.0F;
  *toa_wl00_U_Lift_RE_Pressure = 0.0F;
  *toa_wl00_U_Tilt_HE_Pressure = 0.0F;
  *toa_wl00_U_Tilt_RE_Pressure = 0.0F;
  *toa_wl00_U_Steering_Angle = 0.0F;
  *toa_wl00_U_Tool_Mass = 0.0F;
  *toa_wl00_U_PCS_Truck_Target = 0.0F;
  *toa_wl00_U_PCS_Truck_Start_Weight = 0.0F;
  *toa_wl00_U_PCS_Bucket_Current_Weight_Accuracy = 0U;
  *toa_wl00_U_PCS_Bucket_Current_Weight = 0.0F;
  *toa_wl00_U_PCS_Tipoff_Mode = 0U;
  *toa_wl00_U_EEF_IMU_AccelX = 0.0F;
  *toa_wl00_U_EEF_IMU_AccelY = 0.0F;
  *toa_wl00_U_EEF_IMU_AccelZ = 0.0F;
  *toa_wl00_U_Zero_Offset = 0.0F;
  *toa_wl00_U_Simple_Cal_Factor = 0.0F;
  *toa_wl00_U_IMU_Pitch_Cal = 0.0F;
  *toa_wl00_U_Bucket_Angle = 0.0F;
  *toa_wl00_U_Unlatch_Trigger = false;
  *toa_wl00_U_Anchor_Zero_Offset = 0.0F;
  *toa_wl00_U_Anchor_Factor = 0.0F;
  *toa_wl00_U_CPM_Pass_Count = 0U;
  *toa_wl00_U_Lift_Norm_Angle = 0.0F;
  *toa_wl00_U_Lift_Norm_Length = 0.0F;
  *toa_wl00_U_Tilt_Norm_Angle = 0.0F;
  *toa_wl00_U_Tilt_Norm_Length = 0.0F;
  *toa_wl00_U_Friction_Mu = 0.0F;
  *toa_wl00_U_Friction_Offset = 0.0F;

  /* external outputs */
  (*toa_wl00_Y_Tilt_Sensitivity) = 0.0F;
  (*toa_wl00_Y_Tilt_HE_Pressure_Out) = 0.0F;
  (*toa_wl00_Y_Arbitrated_Payload_Norm_Error) = 0.0F;
  (*toa_wl00_Y_Weigh_Status) = 0U;
  (*toa_wl00_Y_Payload_Norm_Stdev) = 0.0F;
  (*toa_wl00_Y_PCS_Bucket_Current_Weight_Accuracy_Out) = 0U;
  (*toa_wl00_Y_PCS_Bucket_Current_Weight_Norm_Error_Out) = 0.0F;
  (*toa_wl00_Y_Tipoff_Assist_Adv_Error_Code) = 0U;
  (*toa_wl00_Y_Spill_Rate_Norm) = 0.0F;
  (*toa_wl00_Y_Bucket_Payload_Target) = 0.0F;
  (*toa_wl00_Y_Payload_Send_To_CPM) = 0.0F;
  (*toa_wl00_Y_Payload_Status_Send_To_CPM) = 0U;
  (*toa_wl00_Y_Unsecured_Payload_Upper_Bound_Norm) = 0.0F;
  (*toa_wl00_Y_Unsecured_Payload_Lower_Bound_Norm) = 0.0F;
  (*toa_wl00_Y_Unsecured_PFW_Status) = 0U;
  (*toa_wl00_Y_Min_Secure_Bucket_Angle) = 0.0F;

  {
    real32_T filtered_idbq;

    /* InitializeConditions for Memory: '<S283>/Memory 1' */
    toa_wl00_DWork->Memory1_PreviousInput = 1U;

    /* InitializeConditions for UnitDelay: '<S231>/Unit Delay' */
    toa_wl00_DWork->UnitDelay_DSTATE = 99.0F;

    /* InitializeConditions for Memory: '<S232>/Memory 1' */
    toa_wl00_DWork->Memory1_PreviousInput_ddl0 = 1U;

    /* InitializeConditions for Memory: '<S278>/Memory 1' */
    toa_wl00_DWork->Memory1_PreviousInput_gnui = 1U;

    /* InitializeConditions for UnitDelay: '<S267>/Timer' */
    toa_wl00_DWork->Timer_DSTATE = 225U;

    /* InitializeConditions for UnitDelay: '<S268>/Timer' */
    toa_wl00_DWork->Timer_DSTATE_dme3 = 225U;

    /* InitializeConditions for UnitDelay: '<S208>/Timer' */
    toa_wl00_DWork->Timer_DSTATE_jrr0 = 50U;

    /* InitializeConditions for UnitDelay: '<S214>/Unit Delay' */
    toa_wl00_DWork->UnitDelay_DSTATE_hioq = (rtNaNF);

    /* InitializeConditions for UnitDelay: '<S215>/Unit Delay' */
    toa_wl00_DWork->UnitDelay_DSTATE_jlpe = (rtInfF);

    /* InitializeConditions for Delay: '<S153>/Resettable Delay' */
    toa_wl00_DWork->icLoad = 1U;

    /* SystemInitialize for Chart: '<S243>/Filter' */
    toa_wl00_Filter_Init(&filtered_idbq, &toa_wl00_DWork->sf_Filter);

    /* SystemInitialize for Chart: '<S244>/Filter' */
    toa_wl00_Filter_Init(&filtered_idbq, &toa_wl00_DWork->sf_Filter_jasu);

    /* SystemInitialize for Chart: '<S245>/Filter' */
    toa_wl00_Filter_Init(&filtered_idbq, &toa_wl00_DWork->sf_Filter_ewyz);

    /* SystemInitialize for Chart: '<S237>/Filter' */
    toa_wl00_Filter_Init(&filtered_idbq, &toa_wl00_DWork->sf_Filter_ozu2);

    /* SystemInitialize for Chart: '<S238>/Filter' */
    toa_wl00_Filter_Init(&filtered_idbq, &toa_wl00_DWork->sf_Filter_f5hh);

    /* SystemInitialize for Chart: '<S239>/Filter' */
    toa_wl00_Filter_Init(&filtered_idbq, &toa_wl00_DWork->sf_Filter_n3ho);

    /* SystemInitialize for MATLAB Function: '<S225>/MATLAB Function' */
    toa_wl00_DWork->lastSample_not_empty_m4ln = false;

    /* SystemInitialize for MATLAB Function: '<S221>/MATLAB Function' */
    toa_wl00_MATLABFunction_nat1_Init(&toa_wl00_DWork->sf_MATLABFunction_fw1r);

    /* SystemInitialize for Chart: '<S157>/Filter' */
    toa_wl00_Filter_Init(&filtered_idbq, &toa_wl00_DWork->sf_Filter_dsll);

    /* SystemInitialize for Chart: '<S158>/Filter' */
    toa_wl00_Filter_Init(&filtered_idbq, &toa_wl00_DWork->sf_Filter_c1cw);

    /* SystemInitialize for Chart: '<S159>/Filter' */
    toa_wl00_Filter_Init(&filtered_idbq, &toa_wl00_DWork->sf_Filter_ifuw);

    /* SystemInitialize for MATLAB Function: '<S226>/MATLAB Function' */
    toa_wl00_DWork->lastSample_not_empty = false;

    /* SystemInitialize for MATLAB Function: '<S222>/MATLAB Function' */
    toa_wl00_MATLABFunction_nat1_Init(&toa_wl00_DWork->sf_MATLABFunction_iawv);
  }
}
