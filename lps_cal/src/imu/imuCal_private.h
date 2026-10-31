/*
 * File: imuCal_private.h
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

#ifndef RTW_HEADER_imuCal_private_h_
#define RTW_HEADER_imuCal_private_h_
#include "rtwtypes.h"
#include "imuCal.h"

extern const real32_T rtCP_pooled_IVyURa6DTcY7[9];
extern const real32_T rtCP_pooled_wX4hB36b8Vmy[3];

#define rtCP_IMUcsystoEEFcsysrotmat_Val rtCP_pooled_IVyURa6DTcY7 /* Computed Parameter: rtCP_IMUcsystoEEFcsysrotmat_Val
                                                                  * Referenced by: '<S14>/IMU csys to EEF csys rot mat'
                                                                  */
#define rtCP_levelgravityaccel_Value   rtCP_pooled_wX4hB36b8Vmy  /* Computed Parameter: rtCP_levelgravityaccel_Value
                                                                  * Referenced by: '<S14>/level gravity accel'
                                                                  */

extern void imuCal_Filter_Init(self_Filter_imuCal_T *imuCal_self_arg, real32_T
  *rty_filtered);
extern void imuCal_Filter(self_Filter_imuCal_T *imuCal_self_arg, real32_T
  rtu_raw, boolean_T rtu_reset, real32_T rtu_ts, real32_T rtu_cf, real32_T
  *rty_filtered);
extern void imuCal_notchFilter_Init(RT_MODEL_imuCal_T * const imuCal_M);
extern void imuCal_notchFilter(RT_MODEL_imuCal_T * const imuCal_M, real32_T
  rtu_input, boolean_T rtu_reset, real32_T rtu_Ts, real32_T *rty_output);
extern void imuCal_toa_imuCalPayload(RT_MODEL_imuCal_T * const imuCal_M,
  real32_T rtu_liftAngle, real32_T rtu_tiltExt, real32_T rtu_tiltHePress,
  real32_T rtu_tiltRePress, real32_T rtu_liftPress, real32_T rtu_imuX, real32_T
  rtu_imuY, real32_T rtu_imuZ, real32_T rtu_steerAngle, real32_T
  rtu_imuPitchOffset, uint32_T rtu_toa_appNumber, real32_T rtu_toa_tiltBoreDia,
  real32_T rtu_toa_tiltRodDia, real32_T rtu_toa_liftBoreDia, uint8_T
  rtu_toa_tiltNumCyl, real32_T rtu_toa_toolBcLength, real32_T *rty_stuffWeight);

#endif                                 /* RTW_HEADER_imuCal_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
