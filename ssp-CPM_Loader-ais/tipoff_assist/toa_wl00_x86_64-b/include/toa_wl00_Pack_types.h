/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: toa_wl00_Pack_types.h
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
 ** This file contains the type definitions for the package object data structures
 */

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#ifndef RTW_HEADER_toa_wl00_Pack_types_h_
#define RTW_HEADER_toa_wl00_Pack_types_h_
#include <toa_wl00.h>

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/* Package Interface inport mapping: toa_wl00 */
typedef struct _toa_wl00_PackIF_u
{
  boolean_T *Invalidate_Outputs;
  real32_T *Lift_Valve_Command;
  real32_T *Tilt_Valve_Command;
  real32_T *Tilt_Extension;
  real32_T *Lift_Angle;
  real32_T *Lift_HE_Pressure;
  real32_T *Lift_RE_Pressure;
  real32_T *Tilt_HE_Pressure;
  real32_T *Tilt_RE_Pressure;
  real32_T *Steering_Angle;
  real32_T *Tool_Mass;
  real32_T *PCS_Truck_Target;
  real32_T *PCS_Truck_Start_Weight;
  uint8_t *PCS_Bucket_Current_Weight_Accuracy;
  real32_T *PCS_Bucket_Current_Weight;
  uint8_t *PCS_Tipoff_Mode;
  real32_T *EEF_IMU_AccelX;
  real32_T *EEF_IMU_AccelY;
  real32_T *EEF_IMU_AccelZ;
  real32_T *Zero_Offset;
  real32_T *Simple_Cal_Factor;
  real32_T *IMU_Pitch_Cal;
  real32_T *Bucket_Angle;
  boolean_T *Unlatch_Trigger;
  real32_T *Anchor_Zero_Offset;
  real32_T *Anchor_Factor;
  uint16_t *CPM_Pass_Count;
  real32_T *Lift_Norm_Angle;
  real32_T *Lift_Norm_Length;
  real32_T *Tilt_Norm_Angle;
  real32_T *Tilt_Norm_Length;
  real32_T *Friction_Mu;
  real32_T *Friction_Offset;
} toa_wl00_PackIF_u_t;

/* Package Interface outport mapping: toa_wl00 */
typedef struct _toa_wl00_PackIF_y
{
  real32_T *Tilt_Sensitivity;
  real32_T *Tilt_HE_Pressure_Out;
  real32_T *Arbitrated_Payload_Norm_Error;
  uint8_t *Weigh_Status;
  real32_T *Payload_Norm_Stdev;
  uint8_t *PCS_Bucket_Current_Weight_Accuracy_Out;
  real32_T *PCS_Bucket_Current_Weight_Norm_Error_Out;
  uint8_t *Tipoff_Assist_Adv_Error_Code;
  real32_T *Spill_Rate_Norm;
  real32_T *Bucket_Payload_Target;
  real32_T *Payload_Send_To_CPM;
  uint8_t *Payload_Status_Send_To_CPM;
  real32_T *Unsecured_Payload_Upper_Bound_Norm;
  real32_T *Unsecured_Payload_Lower_Bound_Norm;
  uint8_t *Unsecured_PFW_Status;
  real32_T *Min_Secure_Bucket_Angle;
} toa_wl00_PackIF_y_t;

/* Package Interface inport/outport mapping: toa_wl00 */
typedef struct _toa_wl00_PackIF
{
  toa_wl00_PackIF_u_t u;
  toa_wl00_PackIF_y_t y;
} toa_wl00_PackIF_t;

/* Package work definition: toa_wl00 */
typedef struct {
  RT_MODEL_toa_wl00 toa_wl00_M;
  D_Work_toa_wl00 D_Work;
  BlockIO_toa_wl00 BlockIO;
} toa_wl00_work_t;

/* Package config struct definition: toa_wl00 */
typedef struct {
  toa_wl00_PackIF_t PackIF;
} toa_wl00_config_t;

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
#endif                                 /* RTW_HEADER_toa_wl00_Pack_types_h_ */
