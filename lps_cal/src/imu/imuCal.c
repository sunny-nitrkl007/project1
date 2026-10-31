/*
 * File: imuCal.c
 *
 * Code generated for Simulink model 'imuCal'.
 *
 * Model version                  : 1.16
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Tue Feb  8 15:38:09 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "imuCal.h"
#include "imuCal_private.h"
#include "fliplr_pL8EhtaT.h"
#include "mean_ESvihlZI.h"
#include "polyfit_vO5e321P.h"
#include "rt_atan2f_snf.h"
#include "rt_roundd_snf.h"

/* Forward declaration for local functions */
static void imuCal_updateFilter(self_Filter_imuCal_T *imuCal_self_arg, real32_T
  rtu_raw, real32_T *rty_filtered);
static void imuCal_initFilter(self_Filter_imuCal_T *imuCal_self_arg, real32_T
  rtu_raw, real32_T rtu_ts, real32_T rtu_cf, real32_T *rty_filtered);

/* Forward declaration for local functions */
static void imuCal_calcMass_Gs4pQXWb(real_T endDataIdx, real32_T Ts, const
  real32_T bufLiftAngle[2750], const real32_T bufTiltExt[2750], const real32_T
  bufTiltHePress[2750], const real32_T bufTiltRePress[2750], const real32_T
  bufLiftPress[2750], const real32_T bufImuX[2750], const real32_T bufImuY[2750],
  const real32_T bufImuZ[2750], const real32_T bufSteerAngle[2750], real32_T
  pitchOffset, uint32_T toa_appNumber, real32_T toa_tiltBoreDia, real32_T
  toa_tiltRodDia, real32_T toa_liftBoreDia, uint8_T toa_tiltNumCyl, real32_T
  toa_toolBcLength, real32_T weightsFilt[2750], B_imuCal_T *imuCal_B, RT_MODEL_imuCal_T *const imuCal_M);

/* Function for Chart: '<S6>/Filter' */
static void imuCal_updateFilter(self_Filter_imuCal_T *imuCal_self_arg, real32_T
  rtu_raw, real32_T *rty_filtered)
{
  imuCal_self_arg->dwork.rawHist[2] = imuCal_self_arg->dwork.rawHist[1];
  imuCal_self_arg->dwork.rawHist[1] = imuCal_self_arg->dwork.rawHist[0];
  imuCal_self_arg->dwork.rawHist[0] = rtu_raw;
  imuCal_self_arg->dwork.filtHist[2] = imuCal_self_arg->dwork.filtHist[1];
  imuCal_self_arg->dwork.filtHist[1] = imuCal_self_arg->dwork.filtHist[0];
  imuCal_self_arg->dwork.filtHist[0] = (((imuCal_self_arg->dwork.rawHist[0] +
    imuCal_self_arg->dwork.rawHist[2]) - imuCal_self_arg->dwork.filtHist[2]) *
    imuCal_self_arg->dwork.alpha + (imuCal_self_arg->dwork.rawHist[1] -
    imuCal_self_arg->dwork.filtHist[1]) * imuCal_self_arg->dwork.beta) +
    imuCal_self_arg->dwork.gamma * imuCal_self_arg->dwork.filtHist[2];
  *rty_filtered = imuCal_self_arg->dwork.filtHist[0];
}

/* Function for Chart: '<S6>/Filter' */
static void imuCal_initFilter(self_Filter_imuCal_T *imuCal_self_arg, real32_T
  rtu_raw, real32_T rtu_ts, real32_T rtu_cf, real32_T *rty_filtered)
{
  real32_T q;
  real32_T r;
  real32_T t;
  q = rtu_cf * rtu_cf * rtu_ts * rtu_ts / 4.0F;
  r = rtu_cf * rtu_ts;
  t = (1.0F + q) + r;
  imuCal_self_arg->dwork.alpha = (1.0F + q) / t;
  imuCal_self_arg->dwork.beta = (q - 1.0F) * 2.0F / t;
  imuCal_self_arg->dwork.gamma = r / t;
  imuCal_self_arg->dwork.rawHist[0] = rtu_raw;
  imuCal_self_arg->dwork.rawHist[1] = rtu_raw;
  imuCal_self_arg->dwork.rawHist[2] = rtu_raw;
  imuCal_self_arg->dwork.filtHist[0] = rtu_raw;
  imuCal_self_arg->dwork.filtHist[1] = rtu_raw;
  imuCal_self_arg->dwork.filtHist[2] = rtu_raw;
  *rty_filtered = imuCal_self_arg->dwork.filtHist[0];
}

/*
 * System initialize for atomic system:
 *    '<S6>/Filter'
 *    '<S7>/Filter'
 *    '<S8>/Filter'
 */
void imuCal_Filter_Init(self_Filter_imuCal_T *imuCal_self_arg, real32_T
  *rty_filtered)
{
  imuCal_self_arg->dwork.is_active_c2_lib_imuCal = 0U;
  imuCal_self_arg->dwork.rawHist[0] = 0.0F;
  imuCal_self_arg->dwork.filtHist[0] = 0.0F;
  imuCal_self_arg->dwork.rawHist[1] = 0.0F;
  imuCal_self_arg->dwork.filtHist[1] = 0.0F;
  imuCal_self_arg->dwork.rawHist[2] = 0.0F;
  imuCal_self_arg->dwork.filtHist[2] = 0.0F;
  imuCal_self_arg->dwork.alpha = 0.0F;
  imuCal_self_arg->dwork.beta = 0.0F;
  imuCal_self_arg->dwork.gamma = 0.0F;
  *rty_filtered = 0.0F;
}

/*
 * Output and update for atomic system:
 *    '<S6>/Filter'
 *    '<S7>/Filter'
 *    '<S8>/Filter'
 */
void imuCal_Filter(self_Filter_imuCal_T *imuCal_self_arg, real32_T rtu_raw,
                   boolean_T rtu_reset, real32_T rtu_ts, real32_T rtu_cf,
                   real32_T *rty_filtered)
{
  /* Chart: '<S6>/Filter' */
  if (imuCal_self_arg->dwork.is_active_c2_lib_imuCal == 0U) {
    imuCal_self_arg->dwork.is_active_c2_lib_imuCal = 1U;
    imuCal_initFilter(imuCal_self_arg, rtu_raw, rtu_ts, rtu_cf, rty_filtered);
  } else if (rtu_reset) {
    imuCal_initFilter(imuCal_self_arg, rtu_raw, rtu_ts, rtu_cf, rty_filtered);
  } else {
    imuCal_updateFilter(imuCal_self_arg, rtu_raw, rty_filtered);
  }

  /* End of Chart: '<S6>/Filter' */
}

/* System initialize for Simulink Function: '<S1>/Notch Filter Simulink Function' */
void imuCal_notchFilter_Init(RT_MODEL_imuCal_T * const imuCal_M)
{
  /* SystemInitialize for Chart: '<S6>/Filter' */
  imuCal_Filter_Init(&(imuCal_M)->sf_Filter, &(imuCal_M)->blockIO.filtered_j);

  /* SystemInitialize for Chart: '<S7>/Filter' */
  imuCal_Filter_Init(&(imuCal_M)->sf_Filter_c, &(imuCal_M)->blockIO.filtered_i);

  /* SystemInitialize for Chart: '<S8>/Filter' */
  imuCal_Filter_Init(&(imuCal_M)->sf_Filter_d, &(imuCal_M)->blockIO.filtered);
}

/* Output and update for Simulink Function: '<S1>/Notch Filter Simulink Function' */
void imuCal_notchFilter(RT_MODEL_imuCal_T * const imuCal_M, real32_T rtu_input,
  boolean_T rtu_reset, real32_T rtu_Ts, real32_T *rty_output)
{
  /* Chart: '<S6>/Filter' incorporates:
   *  Constant: '<S6>/Constant'
   *  SignalConversion: '<S2>/TmpSignal ConversionAtinputOutport1'
   *  SignalConversion: '<S2>/TmpSignal ConversionAtreset1Outport1'
   *  SignalConversion: '<S2>/TmpSignal ConversionAtresetOutport1'
   */
  imuCal_Filter(&(imuCal_M)->sf_Filter, rtu_input, rtu_reset, rtu_Ts, 5.0F,
                &(imuCal_M)->blockIO.filtered_j);

  /* Chart: '<S7>/Filter' incorporates:
   *  Constant: '<S7>/Constant'
   *  SignalConversion: '<S2>/TmpSignal ConversionAtreset1Outport1'
   *  SignalConversion: '<S2>/TmpSignal ConversionAtresetOutport1'
   */
  imuCal_Filter(&(imuCal_M)->sf_Filter_c, (imuCal_M)->blockIO.filtered_j,
                rtu_reset, rtu_Ts, 7.5F, &(imuCal_M)->blockIO.filtered_i);

  /* Chart: '<S8>/Filter' incorporates:
   *  Constant: '<S8>/Constant'
   *  SignalConversion: '<S2>/TmpSignal ConversionAtreset1Outport1'
   *  SignalConversion: '<S2>/TmpSignal ConversionAtresetOutport1'
   */
  imuCal_Filter(&(imuCal_M)->sf_Filter_d, (imuCal_M)->blockIO.filtered_i,
                rtu_reset, rtu_Ts, 12.0F, &(imuCal_M)->blockIO.filtered);

  /* SignalConversion: '<S2>/TmpSignal ConversionAtoutputInport1' */
  *rty_output = imuCal_M->blockIO.filtered;
}

/* Output and update for Simulink Function: '<S1>/TOA Weight Simulink Function' */
void imuCal_toa_imuCalPayload(RT_MODEL_imuCal_T * const imuCal_M, real32_T
  rtu_liftAngle, real32_T rtu_tiltExt, real32_T rtu_tiltHePress, real32_T
  rtu_tiltRePress, real32_T rtu_liftPress, real32_T rtu_imuX, real32_T rtu_imuY,
  real32_T rtu_imuZ, real32_T rtu_steerAngle, real32_T rtu_imuPitchOffset,
  uint32_T rtu_toa_appNumber, real32_T rtu_toa_tiltBoreDia, real32_T
  rtu_toa_tiltRodDia, real32_T rtu_toa_liftBoreDia, uint8_T rtu_toa_tiltNumCyl,
  real32_T rtu_toa_toolBcLength, real32_T *rty_stuffWeight)
{
  /* local block i/o variables */
  real_T rtb_toa_mass_and_dist_by_id_sfu;
  real32_T a;
  int8_T I[9];
  static const int8_T b[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  static const int8_T c[9] = { 0, 0, -1, 0, 0, 0, 1, 0, 0 };

  static const int8_T d[9] = { 0, 0, 0, 0, 1, 0, 0, 0, 0 };

  boolean_T y;
  real32_T scale;
  real32_T absxk;
  real32_T t;
  static const int8_T b_0[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  real32_T rtb_Switch;
  real32_T rtb_Switch_n;
  real32_T rtb_ConcatenateVector[3];
  real32_T rtb_rotMatrix[9];
  uint32_T rtb_TmpSignalConversionAttoa_ap;
  real_T rtb_toa_mass_and_dist_by_id_s_p;
  real32_T tmp[3];
  int32_T i;
  real32_T tmp_0[9];
  int32_T scale_tmp;
  boolean_T exitg1;

  /* SignalConversion: '<S3>/TmpSignal ConversionAttoa_appNumberOutport1' */
  rtb_TmpSignalConversionAttoa_ap = rtu_toa_appNumber;

  /* Product: '<S47>/Multiply2' incorporates:
   *  Constant: '<S47>/Constant2'
   *  Math: '<S47>/Math Function'
   *  SignalConversion: '<S3>/TmpSignal ConversionAttoa_tiltBoreDiaOutport1'
   */
  rtb_Switch = rtu_toa_tiltBoreDia * rtu_toa_tiltBoreDia * 0.785398185F;

  /* SignalConversion: '<S12>/Copy' incorporates:
   *  Constant: '<S18>/mN to kN'
   *  Constant: '<S48>/Constant2'
   *  Math: '<S48>/Math Function'
   *  Product: '<S18>/Multiply'
   *  Product: '<S18>/Multiply1'
   *  Product: '<S18>/Multiply2'
   *  Product: '<S3>/Multiply1'
   *  Product: '<S48>/Multiply2'
   *  SignalConversion: '<S3>/TmpSignal ConversionAttiltHePressOutport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAttiltRePressOutport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAttoa_tiltNumCylOutport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAttoa_tiltRodDiaOutport1'
   *  Sum: '<S18>/Subtract'
   *  Sum: '<S18>/Subtract1'
   */
  imuCal_M->blockIO.toa_tiltForce = (rtb_Switch * rtu_tiltHePress - (rtb_Switch
    - rtu_toa_tiltRodDia * rtu_toa_tiltRodDia * 0.785398185F) * rtu_tiltRePress)
    * 1.0E-6F * (real32_T)rtu_toa_tiltNumCyl;

  /* Product: '<S17>/Multiply' incorporates:
   *  Constant: '<S17>/Constant'
   */
  imuCal_M->blockIO.toa_sfuncInTiltForce = 1.0E+6F *
    imuCal_M->blockIO.toa_tiltForce;

  /* SignalConversion: '<S36>/Copy' incorporates:
   *  DataTypeConversion: '<S17>/Data Type Conversion3'
   */
  imuCal_M->blockIO.toa_sfuncInRawTiltForce =
    imuCal_M->blockIO.toa_sfuncInTiltForce;

  /* Product: '<S32>/Multiply2' incorporates:
   *  Constant: '<S32>/Constant2'
   *  Math: '<S32>/Math Function'
   *  SignalConversion: '<S3>/TmpSignal ConversionAttoa_liftBoreDiaOutport1'
   */
  rtb_Switch_n = rtu_toa_liftBoreDia * rtu_toa_liftBoreDia * 0.785398185F;

  /* SignalConversion: '<S13>/Copy' incorporates:
   *  Constant: '<S16>/mN to kN'
   *  Constant: '<S3>/# of lift cyls'
   *  Constant: '<S3>/Constant'
   *  Product: '<S16>/Multiply'
   *  Product: '<S16>/Multiply1'
   *  Product: '<S16>/Multiply2'
   *  Product: '<S3>/Multiply'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtliftPressOutport1'
   *  Sum: '<S16>/Subtract'
   *  Sum: '<S16>/Subtract1'
   */
  imuCal_M->blockIO.toa_liftForce = (rtb_Switch_n * rtu_liftPress -
    (rtb_Switch_n - imuCal_ConstB.Multiply2) * 0.0F) * 1.0E-6F * 2.0F;

  /* Product: '<S17>/Multiply1' incorporates:
   *  Constant: '<S17>/Constant'
   */
  imuCal_M->blockIO.toa_sfuncInLiftForce = 1.0E+6F *
    imuCal_M->blockIO.toa_liftForce;

  /* SignalConversion: '<S37>/Copy' incorporates:
   *  DataTypeConversion: '<S17>/Data Type Conversion1'
   */
  imuCal_M->blockIO.toa_sfuncInRawLiftForce =
    imuCal_M->blockIO.toa_sfuncInLiftForce;

  /* SignalConversion: '<S35>/Copy' incorporates:
   *  SignalConversion: '<S3>/TmpSignal ConversionAttiltExtOutport1'
   */
  imuCal_M->blockIO.toa_sfuncInTiltExt = rtu_tiltExt;

  /* SignalConversion: '<S38>/Copy' incorporates:
   *  DataTypeConversion: '<S17>/Data Type Conversion2'
   */
  imuCal_M->blockIO.toa_sfuncInRawTiltExt = imuCal_M->blockIO.toa_sfuncInTiltExt;

  /* SignalConversion: '<S45>/Copy' incorporates:
   *  SignalConversion: '<S3>/TmpSignal ConversionAtliftAngleOutport1'
   */
  imuCal_M->blockIO.toa_sfuncInLiftAng = rtu_liftAngle;

  /* SignalConversion: '<S39>/Copy' incorporates:
   *  DataTypeConversion: '<S17>/Data Type Conversion4'
   *  Gain: '<S46>/Gain1'
   */
  imuCal_M->blockIO.toa_sfuncInRawLiftAng = 0.0174532924F *
    imuCal_M->blockIO.toa_sfuncInLiftAng;

  /* SignalConversion: '<S44>/Copy' incorporates:
   *  SignalConversion: '<S3>/TmpSignal ConversionAttoa_toolBcLengthOutport1'
   */
  imuCal_M->blockIO.toa_sfuncInBcLength = rtu_toa_toolBcLength;

  /* SignalConversion: '<S40>/Copy' incorporates:
   *  DataTypeConversion: '<S17>/Data Type Conversion5'
   */
  imuCal_M->blockIO.toa_sfuncInRawBcLength =
    imuCal_M->blockIO.toa_sfuncInBcLength;

  /* MATLAB Function: '<S14>/Rotation Matrix About Z' incorporates:
   *  SignalConversion: '<S3>/TmpSignal ConversionAtimuPitchOffsetOutport1'
   */
  if (rtu_imuPitchOffset == 0.0F) {
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
    rtb_Switch = rtu_imuPitchOffset / 180.0F * 3.14159274F;
    a = cosf(rtb_Switch);
    rtb_Switch = sinf(rtb_Switch);
    rtb_rotMatrix[0] = a;
    rtb_rotMatrix[3] = -rtb_Switch;
    rtb_rotMatrix[6] = 0.0F;
    rtb_rotMatrix[1] = rtb_Switch;
    rtb_rotMatrix[4] = a;
    rtb_rotMatrix[7] = 0.0F;
    rtb_rotMatrix[2] = 0.0F;
    rtb_rotMatrix[5] = 0.0F;
    rtb_rotMatrix[8] = 1.0F;
  }

  /* End of MATLAB Function: '<S14>/Rotation Matrix About Z' */

  /* Product: '<S14>/transform to basic EEF' incorporates:
   *  Constant: '<S14>/IMU csys to EEF csys rot mat'
   *  Product: '<S14>/apply calibration'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtimuXOutport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtimuYOutport1'
   *  SignalConversion: '<S3>/TmpSignal ConversionAtimuZOutport1'
   */
  for (i = 0; i < 3; i++) {
    tmp[i] = rtCP_IMUcsystoEEFcsysrotmat_Val[i + 6] * rtu_imuZ +
      (rtCP_IMUcsystoEEFcsysrotmat_Val[i + 3] * rtu_imuY +
       rtCP_IMUcsystoEEFcsysrotmat_Val[i] * rtu_imuX);
  }

  /* End of Product: '<S14>/transform to basic EEF' */
  for (i = 0; i < 3; i++) {
    /* Product: '<S14>/apply calibration' */
    imuCal_M->blockIO.toa_imu_eef_accl_vec[i] = 0.0F;
    imuCal_M->blockIO.toa_imu_eef_accl_vec[i] += rtb_rotMatrix[i] * tmp[0];
    imuCal_M->blockIO.toa_imu_eef_accl_vec[i] += rtb_rotMatrix[i + 3] * tmp[1];
    imuCal_M->blockIO.toa_imu_eef_accl_vec[i] += rtb_rotMatrix[i + 6] * tmp[2];

    /* Math: '<S23>/Math Function' */
    rtb_ConcatenateVector[i] = imuCal_M->blockIO.toa_imu_eef_accl_vec[i] *
      imuCal_M->blockIO.toa_imu_eef_accl_vec[i];
  }

  /* Sum: '<S23>/Sum of Elements' */
  rtb_Switch_n = (rtb_ConcatenateVector[0] + rtb_ConcatenateVector[1]) +
    rtb_ConcatenateVector[2];

  /* Math: '<S23>/Math Function1'
   *
   * About '<S23>/Math Function1':
   *  Operator: sqrt
   */
  if (rtb_Switch_n < 0.0F) {
    rtb_Switch_n = -sqrtf(fabsf(rtb_Switch_n));
  } else {
    rtb_Switch_n = sqrtf(rtb_Switch_n);
  }

  /* End of Math: '<S23>/Math Function1' */

  /* Gain: '<S19>/Gain1' incorporates:
   *  SignalConversion: '<S3>/TmpSignal ConversionAtsteerAngleOutport1'
   */
  rtb_Switch = 0.0174532924F * rtu_steerAngle;

  /* MATLAB Function: '<S14>/EEF vector to NEEF vector' */
  scale = cosf(rtb_Switch);
  absxk = sinf(rtb_Switch);
  for (i = 0; i < 3; i++) {
    rtb_rotMatrix[3 * i] = ((real32_T)b[3 * i] * scale + (real32_T)c[3 * i] *
      absxk) + (real32_T)d[3 * i] * (1.0F - scale);
    scale_tmp = 3 * i + 1;
    rtb_rotMatrix[1 + 3 * i] = ((real32_T)b[scale_tmp] * scale + (real32_T)
      c[scale_tmp] * absxk) + (real32_T)d[scale_tmp] * (1.0F - scale);
    scale_tmp = 3 * i + 2;
    rtb_rotMatrix[2 + 3 * i] = ((real32_T)b[scale_tmp] * scale + (real32_T)
      c[scale_tmp] * absxk) + (real32_T)d[scale_tmp] * (1.0F - scale);

    /* Product: '<S14>/Product' incorporates:
     *  Constant: '<S14>/gravity magnitude'
     *  Product: '<S23>/Divide'
     */
    tmp[i] = imuCal_M->blockIO.toa_imu_eef_accl_vec[i] / rtb_Switch_n * 9.80665F;
  }

  for (i = 0; i < 3; i++) {
    imuCal_M->blockIO.toa_imu_neef_accl_vec[i] = 0.0F;
    imuCal_M->blockIO.toa_imu_neef_accl_vec[i] += rtb_rotMatrix[i] * tmp[0];
    imuCal_M->blockIO.toa_imu_neef_accl_vec[i] += rtb_rotMatrix[i + 3] * tmp[1];
    imuCal_M->blockIO.toa_imu_neef_accl_vec[i] += rtb_rotMatrix[i + 6] * tmp[2];

    /* Gain: '<S14>/convert "proper acceleration" to gravity' */
    imuCal_M->blockIO.toa_grav_neef_vec[i] =
      -imuCal_M->blockIO.toa_imu_neef_accl_vec[i];
  }

  /* End of MATLAB Function: '<S14>/EEF vector to NEEF vector' */

  /* Switch: '<S31>/Switch' incorporates:
   *  Constant: '<S27>/OV Val'
   */
  if (imuCal_ConstB.RelationalOperator) {
    rtb_Switch_n = 0.0F;
  } else {
    rtb_Switch_n = imuCal_M->blockIO.toa_grav_neef_vec[0];
  }

  /* End of Switch: '<S31>/Switch' */

  /* Switch: '<S29>/Switch' incorporates:
   *  Constant: '<S26>/OV Val'
   */
  if (imuCal_ConstB.RelationalOperator_n) {
    rtb_Switch = 0.0F;
  } else {
    rtb_Switch = imuCal_M->blockIO.toa_grav_neef_vec[1];
  }

  /* End of Switch: '<S29>/Switch' */

  /* SignalConversion: '<S17>/Signal Conversion1' incorporates:
   *  SignalConversion: '<S15>/ConcatBufferAtVector Concatenate1In1'
   */
  imuCal_M->blockIO.toa_sfuncInGravX = rtb_Switch_n;

  /* DataTypeConversion: '<S17>/Data Type Conversion8' */
  rtb_toa_mass_and_dist_by_id_s_p = imuCal_M->blockIO.toa_sfuncInGravX;

  /* SignalConversion: '<S42>/Copy' */
  imuCal_M->blockIO.toa_sfuncInRawGravX = rtb_toa_mass_and_dist_by_id_s_p;

  /* SignalConversion: '<S17>/Signal Conversion' incorporates:
   *  SignalConversion: '<S15>/ConcatBufferAtVector Concatenate1In2'
   */
  imuCal_M->blockIO.toa_sfuncInGravY = rtb_Switch;

  /* DataTypeConversion: '<S17>/Data Type Conversion9' */
  rtb_toa_mass_and_dist_by_id_s_p = imuCal_M->blockIO.toa_sfuncInGravY;

  /* SignalConversion: '<S43>/Copy' */
  imuCal_M->blockIO.toa_sfuncInRawGravY = rtb_toa_mass_and_dist_by_id_s_p;

  /* S-Function (toa_mass_and_dist_by_id_sfunc): '<S17>/toa_mass_and_dist_by_id_sfunc' */
  toa_mass_and_dist_by_id(rtb_TmpSignalConversionAttoa_ap, (imuCal_M)
    ->blockIO.toa_sfuncInRawTiltForce, (imuCal_M)
    ->blockIO.toa_sfuncInRawLiftForce, (imuCal_M)->blockIO.toa_sfuncInRawTiltExt,
    (imuCal_M)->blockIO.toa_sfuncInRawLiftAng, (imuCal_M)
    ->blockIO.toa_sfuncInRawBcLength, (imuCal_M)->blockIO.toa_sfuncInRawGravX,
    (imuCal_M)->blockIO.toa_sfuncInRawGravY, &rtb_toa_mass_and_dist_by_id_s_p,
    &rtb_toa_mass_and_dist_by_id_sfu);

  /* SignalConversion: '<S41>/Copy' */
  imuCal_M->blockIO.toa_sfuncOutRawMass = rtb_toa_mass_and_dist_by_id_s_p;

  /* Gain: '<S17>/grams to tonnes' incorporates:
   *  DataTypeConversion: '<S17>/Data Type Conversion6'
   */
  imuCal_M->blockIO.toa_sfuncOutRawMassTonne = 1.0E-6F * (real32_T)
    imuCal_M->blockIO.toa_sfuncOutRawMass;

  /* Sum: '<S17>/Tool Mass Offset' */
  imuCal_M->blockIO.toa_rawPayload = imuCal_M->blockIO.toa_sfuncOutRawMassTonne;

  /* Sum: '<S17>/Apply Zero' */
  imuCal_M->blockIO.toa_payloadZeroed = imuCal_M->blockIO.toa_rawPayload;

  /* Product: '<S17>/Apply Scale Factor' */
  imuCal_M->blockIO.toa_payloadAdjusted = imuCal_M->blockIO.toa_payloadZeroed;

  /* SignalConversion: '<S3>/TmpSignal ConversionAtstuffWeightInport1' */
  *rty_stuffWeight = imuCal_M->blockIO.toa_payloadAdjusted;

  /* MATLAB Function: '<S14>/rotation matrix calc from two vectors' */
  y = true;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 3)) {
    if (!(imuCal_M->blockIO.toa_grav_neef_vec[i] ==
          rtCP_levelgravityaccel_Value[i])) {
      y = false;
      exitg1 = true;
    } else {
      i++;
    }
  }

  if (y) {
    imuCal_M->blockIO.toa_grav_rotAxis[0] = 9999.0F;
    imuCal_M->blockIO.toa_grav_rotAxis[1] = 9999.0F;
    imuCal_M->blockIO.toa_grav_rotAxis[2] = 9999.0F;
    imuCal_M->blockIO.toa_grav_angle = 9999.0F;
    for (i = 0; i < 9; i++) {
      I[i] = 0;
    }

    I[0] = 1;
    I[4] = 1;
    I[8] = 1;
    for (i = 0; i < 9; i++) {
      imuCal_M->blockIO.toa_grav_rotMatrix[i] = I[i];
    }
  } else {
    imuCal_M->blockIO.toa_grav_rotAxis[0] = imuCal_M->blockIO.toa_grav_neef_vec
      [1] * 0.0F - imuCal_M->blockIO.toa_grav_neef_vec[2] * -9.80665F;
    imuCal_M->blockIO.toa_grav_rotAxis[1] = imuCal_M->blockIO.toa_grav_neef_vec
      [2] * 0.0F - imuCal_M->blockIO.toa_grav_neef_vec[0] * 0.0F;
    imuCal_M->blockIO.toa_grav_rotAxis[2] = imuCal_M->blockIO.toa_grav_neef_vec
      [0] * -9.80665F - imuCal_M->blockIO.toa_grav_neef_vec[1] * 0.0F;
    scale = 1.29246971E-26F;
    absxk = fabsf(imuCal_M->blockIO.toa_grav_rotAxis[0]);
    if (absxk > 1.29246971E-26F) {
      a = 1.0F;
      scale = absxk;
    } else {
      t = absxk / 1.29246971E-26F;
      a = t * t;
    }

    absxk = fabsf(imuCal_M->blockIO.toa_grav_rotAxis[1]);
    if (absxk > scale) {
      t = scale / absxk;
      a = a * t * t + 1.0F;
      scale = absxk;
    } else {
      t = absxk / scale;
      a += t * t;
    }

    absxk = fabsf(imuCal_M->blockIO.toa_grav_rotAxis[2]);
    if (absxk > scale) {
      t = scale / absxk;
      a = a * t * t + 1.0F;
      scale = absxk;
    } else {
      t = absxk / scale;
      a += t * t;
    }

    a = scale * sqrtf(a);
    imuCal_M->blockIO.toa_grav_rotAxis[0] /= a;
    imuCal_M->blockIO.toa_grav_rotAxis[1] /= a;
    imuCal_M->blockIO.toa_grav_rotAxis[2] /= a;
    a = atanf(a / ((imuCal_M->blockIO.toa_grav_neef_vec[0] * 0.0F +
                    imuCal_M->blockIO.toa_grav_neef_vec[1] * -9.80665F) +
                   imuCal_M->blockIO.toa_grav_neef_vec[2] * 0.0F));
    imuCal_M->blockIO.toa_grav_angle = a * 180.0F / 3.14159274F;
    scale = cosf(a);
    absxk = sinf(a);
    rtb_rotMatrix[0] = absxk * 0.0F;
    rtb_rotMatrix[3] = absxk * -imuCal_M->blockIO.toa_grav_rotAxis[2];
    rtb_rotMatrix[6] = absxk * imuCal_M->blockIO.toa_grav_rotAxis[1];
    rtb_rotMatrix[1] = absxk * imuCal_M->blockIO.toa_grav_rotAxis[2];
    rtb_rotMatrix[4] = absxk * 0.0F;
    rtb_rotMatrix[7] = absxk * -imuCal_M->blockIO.toa_grav_rotAxis[0];
    rtb_rotMatrix[2] = absxk * -imuCal_M->blockIO.toa_grav_rotAxis[1];
    rtb_rotMatrix[5] = absxk * imuCal_M->blockIO.toa_grav_rotAxis[0];
    rtb_rotMatrix[8] = absxk * 0.0F;
    for (i = 0; i < 3; i++) {
      tmp_0[i] = imuCal_M->blockIO.toa_grav_rotAxis[i] *
        imuCal_M->blockIO.toa_grav_rotAxis[0];
      tmp_0[i + 3] = imuCal_M->blockIO.toa_grav_rotAxis[i] *
        imuCal_M->blockIO.toa_grav_rotAxis[1];
      tmp_0[i + 6] = imuCal_M->blockIO.toa_grav_rotAxis[i] *
        imuCal_M->blockIO.toa_grav_rotAxis[2];
    }

    for (i = 0; i < 3; i++) {
      imuCal_M->blockIO.toa_grav_rotMatrix[3 * i] = ((real32_T)b_0[3 * i] *
        scale + rtb_rotMatrix[3 * i]) + tmp_0[3 * i] * (1.0F - scale);
      scale_tmp = 3 * i + 1;
      imuCal_M->blockIO.toa_grav_rotMatrix[1 + 3 * i] = ((real32_T)b_0[scale_tmp]
        * scale + rtb_rotMatrix[scale_tmp]) + tmp_0[scale_tmp] * (1.0F - scale);
      scale_tmp = 3 * i + 2;
      imuCal_M->blockIO.toa_grav_rotMatrix[2 + 3 * i] = ((real32_T)b_0[scale_tmp]
        * scale + rtb_rotMatrix[scale_tmp]) + tmp_0[scale_tmp] * (1.0F - scale);
    }
  }

  /* End of MATLAB Function: '<S14>/rotation matrix calc from two vectors' */

  /* MATLAB Function: '<S14>/euler angles from rot matrix' */
  imuCal_M->blockIO.toa_grav_angles[0] = 0.0;
  imuCal_M->blockIO.toa_grav_angles[1] = 0.0;
  imuCal_M->blockIO.toa_grav_angles[2] = 0.0;
  imuCal_M->blockIO.toa_grav_angles[0] = rt_atan2f_snf((imuCal_M)
    ->blockIO.toa_grav_rotMatrix[5], (imuCal_M)->blockIO.toa_grav_rotMatrix[8]);
  imuCal_M->blockIO.toa_grav_angles[1] = rt_atan2f_snf(-(imuCal_M)
    ->blockIO.toa_grav_rotMatrix[2], sqrtf((imuCal_M)
    ->blockIO.toa_grav_rotMatrix[5] * (imuCal_M)->blockIO.toa_grav_rotMatrix[5]
    + (imuCal_M)->blockIO.toa_grav_rotMatrix[8] * (imuCal_M)
    ->blockIO.toa_grav_rotMatrix[8]));
  imuCal_M->blockIO.toa_grav_angles[2] = rt_atan2f_snf((imuCal_M)
    ->blockIO.toa_grav_rotMatrix[1], (imuCal_M)->blockIO.toa_grav_rotMatrix[0]);
  imuCal_M->blockIO.toa_grav_angles[0] = 180.0 *
    imuCal_M->blockIO.toa_grav_angles[0] / 3.1415926535897931;
  imuCal_M->blockIO.toa_grav_angles[1] = 180.0 *
    imuCal_M->blockIO.toa_grav_angles[1] / 3.1415926535897931;
  imuCal_M->blockIO.toa_grav_angles[2] = 180.0 *
    imuCal_M->blockIO.toa_grav_angles[2] / 3.1415926535897931;

  /* Sum: '<S25>/Sum of Elements' incorporates:
   *  Math: '<S25>/Math Function'
   *  SignalConversion: '<S15>/ConcatBufferAtVector Concatenate1In1'
   *  SignalConversion: '<S15>/ConcatBufferAtVector Concatenate1In2'
   */
  a = rtb_Switch_n * rtb_Switch_n + rtb_Switch * rtb_Switch;

  /* Math: '<S25>/Math Function1'
   *
   * About '<S25>/Math Function1':
   *  Operator: sqrt
   */
  if (a < 0.0F) {
    imuCal_M->blockIO.toa_grav_neef_xy_mag = -sqrtf(fabsf(a));
  } else {
    imuCal_M->blockIO.toa_grav_neef_xy_mag = sqrtf(a);
  }

  /* End of Math: '<S25>/Math Function1' */

  /* Trigonometry: '<S15>/Trigonometric Function' incorporates:
   *  Gain: '<S15>/convert "proper acceleration" to gravity1'
   */
  imuCal_M->blockIO.toa_grav_neef_pitch_ang = rt_atan2f_snf(rtb_Switch_n,
    -rtb_Switch);

  /* SignalConversion: '<S34>/Copy' */
  imuCal_M->blockIO.toa_sfuncOutRawDist = rtb_toa_mass_and_dist_by_id_sfu;

  /* DataTypeConversion: '<S17>/Data Type Conversion7' */
  imuCal_M->blockIO.toa_rawDist = (real32_T)
    imuCal_M->blockIO.toa_sfuncOutRawDist;
}

/* Function for MATLAB Function: '<S1>/imuCal' */
static void imuCal_calcMass_Gs4pQXWb(real_T endDataIdx, real32_T Ts, const
  real32_T bufLiftAngle[2750], const real32_T bufTiltExt[2750], const real32_T
  bufTiltHePress[2750], const real32_T bufTiltRePress[2750], const real32_T
  bufLiftPress[2750], const real32_T bufImuX[2750], const real32_T bufImuY[2750],
  const real32_T bufImuZ[2750], const real32_T bufSteerAngle[2750], real32_T
  pitchOffset, uint32_T toa_appNumber, real32_T toa_tiltBoreDia, real32_T
  toa_tiltRodDia, real32_T toa_liftBoreDia, uint8_T toa_tiltNumCyl, real32_T
  toa_toolBcLength, real32_T weightsFilt[2750], B_imuCal_T *imuCal_B, RT_MODEL_imuCal_T *const imuCal_M)
{
  real_T reverseIdx;
  int32_T idx;
  real32_T unusedExpr;
  int32_T tmp;
  int32_T exitg1;
  memset(&imuCal_M->blockIO.weights[0], 0, 2750U * sizeof(real32_T));
  memset(&weightsFilt[0], 0, 2750U * sizeof(real32_T));
  memset(&imuCal_M->blockIO.phaselessTemp[0], 0, 2750U * sizeof(real32_T));
  idx = 0;
  do {
    exitg1 = 0;
    tmp = (int32_T)endDataIdx - 1;
    if (idx <= tmp) {
      imuCal_toa_imuCalPayload(imuCal_M, bufLiftAngle[idx], bufTiltExt[idx],
        bufTiltHePress[idx], bufTiltRePress[idx], bufLiftPress[idx], bufImuX[idx],
        bufImuY[idx], bufImuZ[idx], bufSteerAngle[idx], pitchOffset,
        toa_appNumber, toa_tiltBoreDia, toa_tiltRodDia, toa_liftBoreDia,
        toa_tiltNumCyl, toa_toolBcLength, &imuCal_M->blockIO.weights[idx]);
      if (1.0 + (real_T)idx == 1.0) {
        imuCal_notchFilter(imuCal_M, imuCal_M->blockIO.weights[idx], true, Ts, &unusedExpr);
      }

      imuCal_notchFilter(imuCal_M, imuCal_M->blockIO.weights[idx], false, Ts,
                         &imuCal_M->blockIO.phaselessTemp[idx]);
      idx++;
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  imuCal_notchFilter(imuCal_M, imuCal_M->blockIO.phaselessTemp[(int32_T)endDataIdx - 1],
                     true, Ts, &unusedExpr);
  for (idx = 0; idx <= tmp; idx++) {
    reverseIdx = (endDataIdx - (1.0 + (real_T)idx)) + 1.0;
    imuCal_notchFilter(imuCal_M, imuCal_M->blockIO.phaselessTemp[(int32_T)reverseIdx - 1],
                       false, Ts, &weightsFilt[(int32_T)reverseIdx - 1]);
  }
}

/* Model step function */
void imuCal_fcn_call(RT_MODEL_imuCal_T *const imuCal_M)
{
  B_imuCal_T *imuCal_B = ((B_imuCal_T *) &(imuCal_M->blockIO));
  DW_imuCal_T *imuCal_DW = ((DW_imuCal_T *) &(imuCal_M->dwork));
  ExtU_imuCal_T *imuCal_U = (ExtU_imuCal_T *) imuCal_M->inputs;
  ExtY_imuCal_T *imuCal_Y = (ExtY_imuCal_T *) imuCal_M->outputs;
  real32_T searchLeastSlope;
  real32_T searchLeastSlopeIdx;
  real32_T searchLeastSlopePitchOffset;
  real32_T searchLeastSlopeLumpedWeight;
  real32_T searchNoFricWeight[51];
  real32_T dummy[2];
  int32_T ixstart;
  int32_T ix;
  static const real32_T b[161] = { -8.0F, -7.9F, -7.8F, -7.7F, -7.6F, -7.5F,
    -7.4F, -7.3F, -7.2F, -7.1F, -7.0F, -6.9F, -6.8F, -6.7F, -6.6F, -6.5F, -6.4F,
    -6.3F, -6.2F, -6.1F, -6.0F, -5.89999962F, -5.8F, -5.7F, -5.6F, -5.5F,
    -5.39999962F, -5.3F, -5.2F, -5.1F, -5.0F, -4.89999962F, -4.8F, -4.7F, -4.6F,
    -4.5F, -4.39999962F, -4.3F, -4.2F, -4.1F, -4.0F, -3.9F, -3.79999971F,
    -3.69999981F, -3.6F, -3.5F, -3.4F, -3.29999971F, -3.19999981F, -3.1F, -3.0F,
    -2.9F, -2.79999971F, -2.69999981F, -2.6F, -2.5F, -2.4F, -2.29999971F,
    -2.19999981F, -2.1F, -2.0F, -1.9000001F, -1.79999971F, -1.69999981F,
    -1.5999999F, -1.5F, -1.4000001F, -1.29999971F, -1.19999981F, -1.0999999F,
    -1.0F, -0.900000095F, -0.799999714F, -0.699999809F, -0.599999905F, -0.5F,
    -0.400000095F, -0.299999714F, -0.199999809F, -0.0999999046F, 0.0F,
    0.0999999046F, 0.199999809F, 0.299999714F, 0.400000095F, 0.5F, 0.599999905F,
    0.699999809F, 0.799999714F, 0.900000095F, 1.0F, 1.0999999F, 1.19999981F,
    1.29999971F, 1.4000001F, 1.5F, 1.5999999F, 1.69999981F, 1.79999971F,
    1.9000001F, 2.0F, 2.1F, 2.19999981F, 2.29999971F, 2.4F, 2.5F, 2.6F,
    2.69999981F, 2.79999971F, 2.9F, 3.0F, 3.1F, 3.19999981F, 3.29999971F, 3.4F,
    3.5F, 3.6F, 3.69999981F, 3.79999971F, 3.9F, 4.0F, 4.1F, 4.2F, 4.3F,
    4.39999962F, 4.5F, 4.6F, 4.7F, 4.8F, 4.89999962F, 5.0F, 5.1F, 5.2F, 5.3F,
    5.39999962F, 5.5F, 5.6F, 5.7F, 5.8F, 5.89999962F, 6.0F, 6.1F, 6.2F, 6.3F,
    6.4F, 6.5F, 6.6F, 6.7F, 6.8F, 6.9F, 7.0F, 7.1F, 7.2F, 7.3F, 7.4F, 7.5F, 7.6F,
    7.7F, 7.8F, 7.9F, 8.0F };

  real_T c[51];
  boolean_T tmp;
  real_T tmp_0[51];
  real_T tmp_1;
  uint8_T tmp_2;
  boolean_T exitg1;
  tmp = false;

  /* RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_imuCal_fcn_call_at_outport_1' incorporates:
   *  SubSystem: '<Root>/imuCal Subsystem'
   */
  /* MATLAB Function: '<S1>/imuCal' incorporates:
   *  Inport: '<Root>/calDirectionFlag'
   *  Inport: '<Root>/getPitchOffsetFlag'
   *  Inport: '<Root>/imuX'
   *  Inport: '<Root>/imuY'
   *  Inport: '<Root>/imuZ'
   *  Inport: '<Root>/liftAngle'
   *  Inport: '<Root>/liftHeight'
   *  Inport: '<Root>/liftPress'
   *  Inport: '<Root>/resetLowerFlag'
   *  Inport: '<Root>/resetRaiseFlag'
   *  Inport: '<Root>/steerAngle'
   *  Inport: '<Root>/tiltExt'
   *  Inport: '<Root>/tiltHePress'
   *  Inport: '<Root>/tiltRePress'
   *  Inport: '<Root>/toa_appNumber'
   *  Inport: '<Root>/toa_liftBoreDia'
   *  Inport: '<Root>/toa_tiltBoreDia'
   *  Inport: '<Root>/toa_tiltNumCyl'
   *  Inport: '<Root>/toa_tiltRodDia'
   *  Inport: '<Root>/toa_toolBcLength'
   */
  if (!imuCal_M->dwork.initialized_not_empty) {
    imuCal_M->dwork.initialized_not_empty = true;
    memset(&imuCal_M->dwork.raiseBufTiltHePress[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.raiseBufTiltRePress[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.raiseBufLiftPress[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.raiseBufImuX[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.raiseBufImuY[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.raiseBufImuZ[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.raiseBufLiftAngle[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.raiseBufTiltExt[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.raiseBufSteerAngle[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.lowerBufTiltHePress[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.lowerBufTiltRePress[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.lowerBufLiftPress[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.lowerBufImuX[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.lowerBufImuY[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.lowerBufImuZ[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.lowerBufLiftAngle[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.lowerBufTiltExt[0], 0, 2750U * sizeof(real32_T));
    memset(&imuCal_M->dwork.lowerBufSteerAngle[0], 0, 2750U * sizeof(real32_T));
  }

  if ((imuCal_U->resetLowerFlag != 0.0) || (imuCal_U->resetRaiseFlag != 0.0)) {
    printf("# RESET - imuCal() called with arguments:\n");
    fflush(stdout);
    tmp_1 = rt_roundd_snf(imuCal_U->resetLowerFlag);
    if (tmp_1 < 256.0) {
      if (tmp_1 >= 0.0) {
        tmp_2 = (uint8_T)tmp_1;
      } else {
        tmp_2 = 0U;
      }
    } else {
      tmp_2 = MAX_uint8_T;
    }

    printf("## resetLowerFlag = %u\n", tmp_2);
    fflush(stdout);
    tmp_1 = rt_roundd_snf(imuCal_U->resetRaiseFlag);
    if (tmp_1 < 256.0) {
      if (tmp_1 >= 0.0) {
        tmp_2 = (uint8_T)tmp_1;
      } else {
        tmp_2 = 0U;
      }
    } else {
      tmp_2 = MAX_uint8_T;
    }

    printf("## resetRaiseFlag = %u\n", tmp_2);
    fflush(stdout);
    tmp_1 = rt_roundd_snf(imuCal_U->calDirectionFlag);
    if (tmp_1 < 256.0) {
      if (tmp_1 >= 0.0) {
        tmp_2 = (uint8_T)tmp_1;
      } else {
        tmp_2 = 0U;
      }
    } else {
      tmp_2 = MAX_uint8_T;
    }

    printf("## calDirectionFlag = %u\n", tmp_2);
    fflush(stdout);
    tmp_1 = rt_roundd_snf(imuCal_U->getPitchOffsetFlag);
    if (tmp_1 < 256.0) {
      if (tmp_1 >= 0.0) {
        tmp_2 = (uint8_T)tmp_1;
      } else {
        tmp_2 = 0U;
      }
    } else {
      tmp_2 = MAX_uint8_T;
    }

    printf("## getPitchOffsetFlag = %u\n", tmp_2);
    fflush(stdout);
    if (imuCal_U->resetLowerFlag != 0.0) {
      imuCal_M->dwork.lowerStarted = false;
      imuCal_M->dwork.lowerDone = false;
      imuCal_M->dwork.lowerFailed = false;
      imuCal_M->dwork.lowerBufferIdx = 0.0;
      imuCal_M->dwork.lowerLaSlopePointsDone = false;
      memset(&imuCal_M->dwork.lowerLaSlopePointsIdxs[0], 0, 51U * sizeof(real_T));
      imuCal_M->dwork.lowerLaSlopePointsIdx = 1.0;
      memset(&imuCal_M->dwork.lowerBufTiltHePress[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.lowerBufTiltRePress[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.lowerBufLiftPress[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.lowerBufImuX[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.lowerBufImuY[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.lowerBufImuZ[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.lowerBufLiftAngle[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.lowerBufTiltExt[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.lowerBufSteerAngle[0], 0, 2750U * sizeof(real32_T));
    }

    if (imuCal_U->resetRaiseFlag != 0.0) {
      imuCal_M->dwork.raiseStarted = false;
      imuCal_M->dwork.raiseDone = false;
      imuCal_M->dwork.raiseFailed = false;
      imuCal_M->dwork.raiseBufferIdx = 0.0;
      imuCal_M->dwork.raiseLaSlopePointsDone = false;
      memset(&imuCal_M->dwork.raiseLaSlopePointsIdxs[0], 0, 51U * sizeof(real_T));
      imuCal_M->dwork.raiseLaSlopePointsIdx = 1.0;
      memset(&imuCal_M->dwork.raiseBufTiltHePress[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.raiseBufTiltRePress[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.raiseBufLiftPress[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.raiseBufImuX[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.raiseBufImuY[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.raiseBufImuZ[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.raiseBufLiftAngle[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.raiseBufTiltExt[0], 0, 2750U * sizeof(real32_T));
      memset(&imuCal_M->dwork.raiseBufSteerAngle[0], 0, 2750U * sizeof(real32_T));
    }

    searchLeastSlopePitchOffset = (rtNaNF);
    searchLeastSlopeLumpedWeight = (rtNaNF);
  } else if (imuCal_U->getPitchOffsetFlag != 0.0) {
    printf("# GET OFFSET - imuCal() called with arguments:\n");
    fflush(stdout);
    tmp_1 = rt_roundd_snf(imuCal_U->resetLowerFlag);
    if (tmp_1 < 256.0) {
      if (tmp_1 >= 0.0) {
        tmp_2 = (uint8_T)tmp_1;
      } else {
        tmp_2 = 0U;
      }
    } else {
      tmp_2 = MAX_uint8_T;
    }

    printf("## resetLowerFlag = %u\n", tmp_2);
    fflush(stdout);
    tmp_1 = rt_roundd_snf(imuCal_U->resetRaiseFlag);
    if (tmp_1 < 256.0) {
      if (tmp_1 >= 0.0) {
        tmp_2 = (uint8_T)tmp_1;
      } else {
        tmp_2 = 0U;
      }
    } else {
      tmp_2 = MAX_uint8_T;
    }

    printf("## resetRaiseFlag = %u\n", tmp_2);
    fflush(stdout);
    tmp_1 = rt_roundd_snf(imuCal_U->calDirectionFlag);
    if (tmp_1 < 256.0) {
      if (tmp_1 >= 0.0) {
        tmp_2 = (uint8_T)tmp_1;
      } else {
        tmp_2 = 0U;
      }
    } else {
      tmp_2 = MAX_uint8_T;
    }

    printf("## calDirectionFlag = %u\n", tmp_2);
    fflush(stdout);
    tmp_1 = rt_roundd_snf(imuCal_U->getPitchOffsetFlag);
    if (tmp_1 < 256.0) {
      if (tmp_1 >= 0.0) {
        tmp_2 = (uint8_T)tmp_1;
      } else {
        tmp_2 = 0U;
      }
    } else {
      tmp_2 = MAX_uint8_T;
    }

    printf("## getPitchOffsetFlag = %u\n", tmp_2);
    fflush(stdout);
    printf("### RAISE\n");
    fflush(stdout);
    tmp_1 = rt_roundd_snf((imuCal_M)->dwork.raiseBufferIdx);
    if (tmp_1 < 256.0) {
      if (tmp_1 >= 0.0) {
        tmp_2 = (uint8_T)tmp_1;
      } else {
        tmp_2 = 0U;
      }
    } else {
      tmp_2 = MAX_uint8_T;
    }

    printf("#### raiseBufferIdx = %u\n", tmp_2);
    fflush(stdout);
    printf("#### raiseFailed = %u\n", (uint8_T)imuCal_M->dwork.raiseFailed);
    fflush(stdout);
    printf("#### raiseStarted = %u\n", (uint8_T)imuCal_M->dwork.raiseStarted);
    fflush(stdout);
    printf("#### raiseDone = %u\n", (uint8_T)imuCal_M->dwork.raiseDone);
    fflush(stdout);
    ixstart = 1;
    searchLeastSlope = imuCal_M->dwork.raiseBufLiftAngle[0];
    if (rtIsNaNF(imuCal_M->dwork.raiseBufLiftAngle[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix < 2751)) {
        ixstart = ix;
        if (!rtIsNaNF(imuCal_M->dwork.raiseBufLiftAngle[ix - 1])) {
          searchLeastSlope = imuCal_M->dwork.raiseBufLiftAngle[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < 2750) {
      while (ixstart + 1 < 2751) {
        if (imuCal_M->dwork.raiseBufLiftAngle[ixstart] < searchLeastSlope) {
          searchLeastSlope = imuCal_M->dwork.raiseBufLiftAngle[ixstart];
        }

        ixstart++;
      }
    }

    ixstart = 1;
    searchLeastSlopeIdx = imuCal_M->dwork.raiseBufLiftAngle[0];
    if (rtIsNaNF(imuCal_M->dwork.raiseBufLiftAngle[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix < 2751)) {
        ixstart = ix;
        if (!rtIsNaNF(imuCal_M->dwork.raiseBufLiftAngle[ix - 1])) {
          searchLeastSlopeIdx = imuCal_M->dwork.raiseBufLiftAngle[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < 2750) {
      while (ixstart + 1 < 2751) {
        if (imuCal_M->dwork.raiseBufLiftAngle[ixstart] > searchLeastSlopeIdx) {
          searchLeastSlopeIdx = imuCal_M->dwork.raiseBufLiftAngle[ixstart];
        }

        ixstart++;
      }
    }

    printf("#### lift angle min = %.1f, max = %.1f\n", searchLeastSlope,
           searchLeastSlopeIdx);
    fflush(stdout);
    printf("### LOWER\n");
    fflush(stdout);
    tmp_1 = rt_roundd_snf((imuCal_M)->dwork.lowerBufferIdx);
    if (tmp_1 < 256.0) {
      if (tmp_1 >= 0.0) {
        tmp_2 = (uint8_T)tmp_1;
      } else {
        tmp_2 = 0U;
      }
    } else {
      tmp_2 = MAX_uint8_T;
    }

    printf("#### lowerBufferIdx = %u\n", tmp_2);
    fflush(stdout);
    printf("#### lowerFailed = %u\n", (uint8_T)imuCal_M->dwork.lowerFailed);
    fflush(stdout);
    printf("#### lowerStarted = %u\n", (uint8_T)imuCal_M->dwork.lowerStarted);
    fflush(stdout);
    printf("#### lowerDone = %u\n", (uint8_T)imuCal_M->dwork.lowerDone);
    fflush(stdout);
    ixstart = 1;
    searchLeastSlope = imuCal_M->dwork.lowerBufLiftAngle[0];
    if (rtIsNaNF(imuCal_M->dwork.lowerBufLiftAngle[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix < 2751)) {
        ixstart = ix;
        if (!rtIsNaNF(imuCal_M->dwork.lowerBufLiftAngle[ix - 1])) {
          searchLeastSlope = imuCal_M->dwork.lowerBufLiftAngle[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < 2750) {
      while (ixstart + 1 < 2751) {
        if (imuCal_M->dwork.lowerBufLiftAngle[ixstart] < searchLeastSlope) {
          searchLeastSlope = imuCal_M->dwork.lowerBufLiftAngle[ixstart];
        }

        ixstart++;
      }
    }

    ixstart = 1;
    searchLeastSlopeIdx = imuCal_M->dwork.lowerBufLiftAngle[0];
    if (rtIsNaNF(imuCal_M->dwork.lowerBufLiftAngle[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix < 2751)) {
        ixstart = ix;
        if (!rtIsNaNF(imuCal_M->dwork.lowerBufLiftAngle[ix - 1])) {
          searchLeastSlopeIdx = imuCal_M->dwork.lowerBufLiftAngle[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < 2750) {
      while (ixstart + 1 < 2751) {
        if (imuCal_M->dwork.lowerBufLiftAngle[ixstart] > searchLeastSlopeIdx) {
          searchLeastSlopeIdx = imuCal_M->dwork.lowerBufLiftAngle[ixstart];
        }

        ixstart++;
      }
    }

    printf("#### lift angle min = %.1f, max = %.1f\n", searchLeastSlope,
           searchLeastSlopeIdx);
    fflush(stdout);
    if (imuCal_M->dwork.raiseFailed || imuCal_M->dwork.lowerFailed) {
      searchLeastSlopePitchOffset = (rtNaNF);
      searchLeastSlopeLumpedWeight = (rtNaNF);
      printf("Raise or lower failed.  getPitchOffset not possible.");
      fflush(stdout);
    } else {
      searchLeastSlope = 9999.0F;
      searchLeastSlopeIdx = 999999.0F;
      searchLeastSlopePitchOffset = (rtNaNF);
      searchLeastSlopeLumpedWeight = (rtNaNF);
      for (ixstart = 0; ixstart < 161; ixstart++) {
        if (imuCal_M->dwork.lowerDone && imuCal_M->dwork.raiseDone) {
          imuCal_calcMass_Gs4pQXWb((imuCal_M)->dwork.raiseBufferIdx, 0.02F,
            (imuCal_M)->dwork.raiseBufLiftAngle, (imuCal_M)
            ->dwork.raiseBufTiltExt, (imuCal_M)->dwork.raiseBufTiltHePress,
            (imuCal_M)->dwork.raiseBufTiltRePress, (imuCal_M)
            ->dwork.raiseBufLiftPress, (imuCal_M)->dwork.raiseBufImuX, (imuCal_M)
            ->dwork.raiseBufImuY, (imuCal_M)->dwork.raiseBufImuZ, (imuCal_M)
            ->dwork.raiseBufSteerAngle, b[ixstart], imuCal_U->toa_appNumber,
            imuCal_U->toa_tiltBoreDia, imuCal_U->toa_tiltRodDia,
            imuCal_U->toa_liftBoreDia, imuCal_U->toa_tiltNumCyl,
            imuCal_U->toa_toolBcLength, (imuCal_M)->blockIO.NEW_BUFFER, imuCal_B, imuCal_M);
          imuCal_calcMass_Gs4pQXWb((imuCal_M)->dwork.lowerBufferIdx, 0.02F,
            (imuCal_M)->dwork.lowerBufLiftAngle, (imuCal_M)
            ->dwork.lowerBufTiltExt, (imuCal_M)->dwork.lowerBufTiltHePress,
            (imuCal_M)->dwork.lowerBufTiltRePress, (imuCal_M)
            ->dwork.lowerBufLiftPress, (imuCal_M)->dwork.lowerBufImuX, (imuCal_M)
            ->dwork.lowerBufImuY, (imuCal_M)->dwork.lowerBufImuZ, (imuCal_M)
            ->dwork.lowerBufSteerAngle, b[ixstart], imuCal_U->toa_appNumber,
            imuCal_U->toa_tiltBoreDia, imuCal_U->toa_tiltRodDia,
            imuCal_U->toa_liftBoreDia, imuCal_U->toa_tiltNumCyl,
            imuCal_U->toa_toolBcLength, (imuCal_M)->blockIO.searchLowerWeight,
            imuCal_B, imuCal_M);
          memcpy(&c[0], &imuCal_M->dwork.lowerLaSlopePointsIdxs[0], 51U * sizeof
                 (real_T));
          fliplr_pL8EhtaT(c);
          for (ix = 0; ix < 51; ix++) {
            searchNoFricWeight[ix] = (imuCal_M->blockIO.NEW_BUFFER[(int32_T)
              imuCal_M->dwork.raiseLaSlopePointsIdxs[ix] - 1] +
              imuCal_M->blockIO.searchLowerWeight[(int32_T)c[ix] - 1]) / 2.0F;
          }

          if (!tmp) {
            for (ix = 0; ix < 51; ix++) {
              tmp_0[ix] = 0.5 * (real_T)ix + -10.0;
            }

            tmp = true;
          }

          polyfit_vO5e321P(tmp_0, searchNoFricWeight, dummy);
          if (fabsf(dummy[0]) < fabsf(searchLeastSlope)) {
            searchLeastSlope = dummy[0];
            searchLeastSlopeIdx = 1.0F + (real32_T)ixstart;
            searchLeastSlopePitchOffset = b[ixstart];
            searchLeastSlopeLumpedWeight = mean_ESvihlZI(searchNoFricWeight);
          }
        }
      }

      if (imuCal_M->dwork.raiseDone && imuCal_M->dwork.lowerDone) {
        printf("## Slope = %.4f\n## Index = %f\n## Pitch = %.4f\n## Weight = %.4f\n",
               searchLeastSlope, searchLeastSlopeIdx,
               searchLeastSlopePitchOffset, searchLeastSlopeLumpedWeight);
        fflush(stdout);
      }

      if (!(imuCal_M->dwork.raiseDone && imuCal_M->dwork.lowerDone)) {
        searchLeastSlopePitchOffset = (rtNaNF);
        searchLeastSlopeLumpedWeight = (rtNaNF);
      }

      printf("# Returned Pitch Offset = %.4f\n", searchLeastSlopePitchOffset);
      fflush(stdout);
    }
  } else if (imuCal_U->calDirectionFlag == 0.0) {
    if (imuCal_M->dwork.raiseBufferIdx == 2750.0) {
      printf("IMU Cal: Raise data capture failed due to buffer too small!\n");
      fflush(stdout);
      imuCal_M->dwork.raiseFailed = true;
    }

    if (imuCal_U->liftHeight > 35.0) {
      imuCal_M->dwork.raiseStarted = true;
    }

    if (imuCal_U->liftHeight > 80.0) {
      imuCal_M->dwork.raiseDone = true;
    }

    if (imuCal_M->dwork.raiseStarted && (!imuCal_M->dwork.raiseDone) &&
        (!imuCal_M->dwork.raiseFailed)) {
      imuCal_M->dwork.raiseBufferIdx++;
      ixstart = (int32_T)imuCal_M->dwork.raiseBufferIdx - 1;
      imuCal_M->dwork.raiseBufTiltHePress[ixstart] = (real32_T)
        imuCal_U->tiltHePress;
      imuCal_M->dwork.raiseBufTiltRePress[ixstart] = (real32_T)
        imuCal_U->tiltRePress;
      imuCal_M->dwork.raiseBufLiftPress[ixstart] = (real32_T)imuCal_U->liftPress;
      imuCal_M->dwork.raiseBufImuX[ixstart] = (real32_T)imuCal_U->imuX;
      imuCal_M->dwork.raiseBufImuY[ixstart] = (real32_T)imuCal_U->imuY;
      imuCal_M->dwork.raiseBufImuZ[ixstart] = (real32_T)imuCal_U->imuZ;
      imuCal_M->dwork.raiseBufLiftAngle[ixstart] = (real32_T)imuCal_U->liftAngle;
      imuCal_M->dwork.raiseBufTiltExt[ixstart] = (real32_T)imuCal_U->tiltExt;
      imuCal_M->dwork.raiseBufSteerAngle[ixstart] = (real32_T)
        imuCal_U->steerAngle;
      ix = (int32_T)imuCal_M->dwork.raiseLaSlopePointsIdx - 1;
      if ((!imuCal_M->dwork.raiseLaSlopePointsDone) && (imuCal_U->liftAngle >
           (real_T)ix * 0.5 + -10.0)) {
        imuCal_M->dwork.raiseLaSlopePointsIdxs[ix] =
          imuCal_M->dwork.raiseBufferIdx;
        if (imuCal_M->dwork.raiseLaSlopePointsIdx < 51.0) {
          imuCal_M->dwork.raiseLaSlopePointsIdx++;
          if (imuCal_U->liftAngle > (real_T)((int32_T)
               imuCal_M->dwork.raiseLaSlopePointsIdx - 1) * 0.5 + -10.0) {
            imuCal_M->dwork.raiseFailed = true;
            printf("IMU Cal: Raise data capture failed due to func not called frequently enough!\n");
            fflush(stdout);
          }
        } else {
          imuCal_M->dwork.raiseLaSlopePointsDone = true;
        }
      }
    }

    searchLeastSlopePitchOffset = (rtNaNF);
    searchLeastSlopeLumpedWeight = (rtNaNF);
  } else if (imuCal_U->calDirectionFlag == 1.0) {
    if (imuCal_M->dwork.lowerBufferIdx == 2750.0) {
      printf("IMU Cal: Lower data capture failed due to buffer too small!\n");
      fflush(stdout);
      imuCal_M->dwork.lowerFailed = true;
    }

    if (imuCal_U->liftHeight < 80.0) {
      imuCal_M->dwork.lowerStarted = true;
    }

    if (imuCal_U->liftHeight < 35.0) {
      imuCal_M->dwork.lowerDone = true;
    }

    if (imuCal_M->dwork.lowerStarted && (!imuCal_M->dwork.lowerDone) &&
        (!imuCal_M->dwork.lowerFailed)) {
      imuCal_M->dwork.lowerBufferIdx++;
      ixstart = (int32_T)imuCal_M->dwork.lowerBufferIdx - 1;
      imuCal_M->dwork.lowerBufTiltHePress[ixstart] = (real32_T)
        imuCal_U->tiltHePress;
      imuCal_M->dwork.lowerBufTiltRePress[ixstart] = (real32_T)
        imuCal_U->tiltRePress;
      imuCal_M->dwork.lowerBufLiftPress[ixstart] = (real32_T)imuCal_U->liftPress;
      imuCal_M->dwork.lowerBufImuX[ixstart] = (real32_T)imuCal_U->imuX;
      imuCal_M->dwork.lowerBufImuY[ixstart] = (real32_T)imuCal_U->imuY;
      imuCal_M->dwork.lowerBufImuZ[ixstart] = (real32_T)imuCal_U->imuZ;
      imuCal_M->dwork.lowerBufLiftAngle[ixstart] = (real32_T)imuCal_U->liftAngle;
      imuCal_M->dwork.lowerBufTiltExt[ixstart] = (real32_T)imuCal_U->tiltExt;
      imuCal_M->dwork.lowerBufSteerAngle[ixstart] = (real32_T)
        imuCal_U->steerAngle;
      ix = (int32_T)imuCal_M->dwork.lowerLaSlopePointsIdx - 1;
      if ((!imuCal_M->dwork.lowerLaSlopePointsDone) && (imuCal_U->liftAngle <
           (real_T)ix * -0.5 + 15.0)) {
        imuCal_M->dwork.lowerLaSlopePointsIdxs[ix] =
          imuCal_M->dwork.lowerBufferIdx;
        if (imuCal_M->dwork.lowerLaSlopePointsIdx < 51.0) {
          imuCal_M->dwork.lowerLaSlopePointsIdx++;
          if (imuCal_U->liftAngle < (real_T)((int32_T)
               imuCal_M->dwork.lowerLaSlopePointsIdx - 1) * -0.5 + 15.0) {
            imuCal_M->dwork.lowerFailed = true;
            printf("IMU Cal: Lower data capture failed due to func not called frequently enough!\n");
            fflush(stdout);
          }
        } else {
          imuCal_M->dwork.lowerLaSlopePointsDone = true;
        }
      }
    }

    searchLeastSlopePitchOffset = (rtNaNF);
    searchLeastSlopeLumpedWeight = (rtNaNF);
  } else {
    searchLeastSlopePitchOffset = (rtNaNF);
    searchLeastSlopeLumpedWeight = (rtNaNF);
  }

  /* Outport: '<Root>/pitchOffset' incorporates:
   *  MATLAB Function: '<S1>/imuCal'
   */
  imuCal_Y->pitchOffset = searchLeastSlopePitchOffset;

  /* Outport: '<Root>/lumpedWeight' incorporates:
   *  MATLAB Function: '<S1>/imuCal'
   */
  imuCal_Y->lumpedWeight = searchLeastSlopeLumpedWeight;

  /* End of Outputs for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_imuCal_fcn_call_at_outport_1' */
}

/* Model initialize function */
void imuCal_initialize(RT_MODEL_imuCal_T *const imuCal_M)
{
  DW_imuCal_T *imuCal_DW = ((DW_imuCal_T *) &(imuCal_M->dwork));
  B_imuCal_T *imuCal_B = ((B_imuCal_T *) &(imuCal_M->blockIO));
  ExtU_imuCal_T *imuCal_U = (ExtU_imuCal_T *) imuCal_M->inputs;
  ExtY_imuCal_T *imuCal_Y = (ExtY_imuCal_T *) imuCal_M->outputs;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* constant block I/O */
    ;

    /* external inputs */
    imuCal_M->inputs = (((void*)imuCal_U));
    (void)memset((void *)imuCal_U, 0, sizeof(ExtU_imuCal_T));

    /* external outputs */
    imuCal_M->outputs = (imuCal_Y);
    (void) memset((void *)imuCal_Y, 0,
                  sizeof(ExtY_imuCal_T));
  }

  /* SystemInitialize for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_imuCal_fcn_call_at_outport_1' incorporates:
   *  SubSystem: '<Root>/imuCal Subsystem'
   */

  /* SystemInitialize for S-Function (sfun_private_function_caller): '<S1>/sfcn_inserted_server' incorporates:
   *  SubSystem: '<S1>/Notch Filter Simulink Function'
   */
  imuCal_notchFilter_Init(imuCal_M);

  /* End of SystemInitialize for S-Function (sfun_private_function_caller): '<S1>/sfcn_inserted_server' */

  /* SystemInitialize for MATLAB Function: '<S1>/imuCal' */
  imuCal_M->dwork.initialized_not_empty = false;
  imuCal_M->dwork.raiseStarted = false;
  imuCal_M->dwork.raiseDone = false;
  imuCal_M->dwork.raiseFailed = false;
  imuCal_M->dwork.raiseBufferIdx = 0.0;
  imuCal_M->dwork.raiseLaSlopePointsDone = false;
  imuCal_M->dwork.raiseLaSlopePointsIdx = 1.0;
  imuCal_M->dwork.lowerStarted = false;
  imuCal_M->dwork.lowerDone = false;
  imuCal_M->dwork.lowerFailed = false;
  imuCal_M->dwork.lowerBufferIdx = 0.0;
  imuCal_M->dwork.lowerLaSlopePointsDone = false;
  memset(&imuCal_M->dwork.raiseLaSlopePointsIdxs[0], 0, 51U * sizeof(real_T));
  memset(&imuCal_M->dwork.lowerLaSlopePointsIdxs[0], 0, 51U * sizeof(real_T));
  imuCal_M->dwork.lowerLaSlopePointsIdx = 1.0;

  /* End of SystemInitialize for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_imuCal_fcn_call_at_outport_1' */
}

/* Model terminate function */
void imuCal_terminate(RT_MODEL_imuCal_T *const imuCal_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(imuCal_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
