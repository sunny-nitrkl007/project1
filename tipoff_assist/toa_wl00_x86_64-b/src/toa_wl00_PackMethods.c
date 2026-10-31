/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: toa_wl00_PackMethods.c
 **
 ** Real-Time Workshop code generated for Simulink model toa_wl00.
 **
 ** Model version                        : 1.44
 ** Real-Time Workshop file version      : 8.13 (R2017b) 24-Jul-2017
 ** TLC version                          : 8.13 (Jul 25 2017)
 ** CATutils_MatLab version              : CATUTILS_MATLAB_4.6.1
 **
 ******************************************************************************/
/*
 ** This file contains the functions which provide a Package
 ** Architecture interface for the generated functions
 */

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#include <toa_wl00.h>
#include <toa_wl00_private.h>
#include <toa_wl00_Pack_proto.h>
#include <toa_wl00_po.h>
#include <sl_unused_param_macro.h>

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/

/******************************************************************************
 * FUNCTION NAME         : toa_wl00_method_update - 0.02 second
 * DESCRIPTION           :
 *
 * PARAMETER DESCRIPTION :
 *
 * RETURN VALUE:
 * void
 ******************************************************************************/
void toa_wl00_method_update (
  toa_wl00_work_t *work,
  const toa_wl00_config_t *config
  )
{
  /* Pre model step function code */

  /* Execute model step function. */
  toa_wl00_step(
                &(work->toa_wl00_M),
                *(config->PackIF.u.Invalidate_Outputs),
                *(config->PackIF.u.Lift_Valve_Command),
                *(config->PackIF.u.Tilt_Valve_Command),
                *(config->PackIF.u.Tilt_Extension),
                *(config->PackIF.u.Lift_Angle),
                *(config->PackIF.u.Lift_HE_Pressure),
                *(config->PackIF.u.Lift_RE_Pressure),
                *(config->PackIF.u.Tilt_HE_Pressure),
                *(config->PackIF.u.Tilt_RE_Pressure),
                *(config->PackIF.u.Steering_Angle),
                *(config->PackIF.u.Tool_Mass),
                *(config->PackIF.u.PCS_Truck_Target),
                *(config->PackIF.u.PCS_Truck_Start_Weight),
                *(config->PackIF.u.PCS_Bucket_Current_Weight_Accuracy),
                *(config->PackIF.u.PCS_Bucket_Current_Weight),
                *(config->PackIF.u.PCS_Tipoff_Mode),
                *(config->PackIF.u.EEF_IMU_AccelX),
                *(config->PackIF.u.EEF_IMU_AccelY),
                *(config->PackIF.u.EEF_IMU_AccelZ),
                *(config->PackIF.u.Zero_Offset),
                *(config->PackIF.u.Simple_Cal_Factor),
                *(config->PackIF.u.IMU_Pitch_Cal),
                *(config->PackIF.u.Bucket_Angle),
                *(config->PackIF.u.Unlatch_Trigger),
                *(config->PackIF.u.Anchor_Zero_Offset),
                *(config->PackIF.u.Anchor_Factor),
                *(config->PackIF.u.CPM_Pass_Count),
                *(config->PackIF.u.Lift_Norm_Angle),
                *(config->PackIF.u.Lift_Norm_Length),
                *(config->PackIF.u.Tilt_Norm_Angle),
                *(config->PackIF.u.Tilt_Norm_Length),
                *(config->PackIF.u.Friction_Mu),
                *(config->PackIF.u.Friction_Offset),
                config->PackIF.y.Tilt_Sensitivity,
                config->PackIF.y.Tilt_HE_Pressure_Out,
                config->PackIF.y.Arbitrated_Payload_Norm_Error,
                config->PackIF.y.Weigh_Status,
                config->PackIF.y.Payload_Norm_Stdev,
                config->PackIF.y.PCS_Bucket_Current_Weight_Accuracy_Out,
                config->PackIF.y.PCS_Bucket_Current_Weight_Norm_Error_Out,
                config->PackIF.y.Tipoff_Assist_Adv_Error_Code,
                config->PackIF.y.Spill_Rate_Norm,
                config->PackIF.y.Bucket_Payload_Target,
                config->PackIF.y.Payload_Send_To_CPM,
                config->PackIF.y.Payload_Status_Send_To_CPM,
                config->PackIF.y.Unsecured_Payload_Upper_Bound_Norm,
                config->PackIF.y.Unsecured_Payload_Lower_Bound_Norm,
                config->PackIF.y.Unsecured_PFW_Status,
                config->PackIF.y.Min_Secure_Bucket_Angle);

  /* Get model outputs here */

  /* Post model step function code */
}

/******************************************************************************
 * FUNCTION NAME         : toa_wl00_pack_init
 * DESCRIPTION           :
 *
 * PARAMETER DESCRIPTION :
 *
 * RETURN VALUE:
 * void
 ******************************************************************************/
void toa_wl00_pack_init(
  toa_wl00_work_t *work,
  const toa_wl00_config_t *config
  )
{
  /* Initialize the Model Structure (RTM) DWork */
  rtmSetRootDWork(&(work->toa_wl00_M),&(work->D_Work));

  /* Initialize the Model Structure (RTM) BlockIO */
  rtmSetBlockIO(&(work->toa_wl00_M),&(work->BlockIO));

  /* Execute Model Initializations */
  toa_wl00_initialize(
                      &(work->toa_wl00_M),
                      (config->PackIF.u.Invalidate_Outputs),
                      (config->PackIF.u.Lift_Valve_Command),
                      (config->PackIF.u.Tilt_Valve_Command),
                      (config->PackIF.u.Tilt_Extension),
                      (config->PackIF.u.Lift_Angle),
                      (config->PackIF.u.Lift_HE_Pressure),
                      (config->PackIF.u.Lift_RE_Pressure),
                      (config->PackIF.u.Tilt_HE_Pressure),
                      (config->PackIF.u.Tilt_RE_Pressure),
                      (config->PackIF.u.Steering_Angle),
                      (config->PackIF.u.Tool_Mass),
                      (config->PackIF.u.PCS_Truck_Target),
                      (config->PackIF.u.PCS_Truck_Start_Weight),
                      (config->PackIF.u.PCS_Bucket_Current_Weight_Accuracy),
                      (config->PackIF.u.PCS_Bucket_Current_Weight),
                      (config->PackIF.u.PCS_Tipoff_Mode),
                      (config->PackIF.u.EEF_IMU_AccelX),
                      (config->PackIF.u.EEF_IMU_AccelY),
                      (config->PackIF.u.EEF_IMU_AccelZ),
                      (config->PackIF.u.Zero_Offset),
                      (config->PackIF.u.Simple_Cal_Factor),
                      (config->PackIF.u.IMU_Pitch_Cal),
                      (config->PackIF.u.Bucket_Angle),
                      (config->PackIF.u.Unlatch_Trigger),
                      (config->PackIF.u.Anchor_Zero_Offset),
                      (config->PackIF.u.Anchor_Factor),
                      (config->PackIF.u.CPM_Pass_Count),
                      (config->PackIF.u.Lift_Norm_Angle),
                      (config->PackIF.u.Lift_Norm_Length),
                      (config->PackIF.u.Tilt_Norm_Angle),
                      (config->PackIF.u.Tilt_Norm_Length),
                      (config->PackIF.u.Friction_Mu),
                      (config->PackIF.u.Friction_Offset),
                      config->PackIF.y.Tilt_Sensitivity,
                      config->PackIF.y.Tilt_HE_Pressure_Out,
                      config->PackIF.y.Arbitrated_Payload_Norm_Error,
                      config->PackIF.y.Weigh_Status,
                      config->PackIF.y.Payload_Norm_Stdev,
                      config->PackIF.y.PCS_Bucket_Current_Weight_Accuracy_Out,
                      config->PackIF.y.PCS_Bucket_Current_Weight_Norm_Error_Out,
                      config->PackIF.y.Tipoff_Assist_Adv_Error_Code,
                      config->PackIF.y.Spill_Rate_Norm,
                      config->PackIF.y.Bucket_Payload_Target,
                      config->PackIF.y.Payload_Send_To_CPM,
                      config->PackIF.y.Payload_Status_Send_To_CPM,
                      config->PackIF.y.Unsecured_Payload_Upper_Bound_Norm,
                      config->PackIF.y.Unsecured_Payload_Lower_Bound_Norm,
                      config->PackIF.y.Unsecured_PFW_Status,
                      config->PackIF.y.Min_Secure_Bucket_Angle);

  /* Mark unused arguements */
  SL_UNUSED_PARAM(work);
  SL_UNUSED_PARAM(config);
}
