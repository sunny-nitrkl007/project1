/*******************************************************************************
** COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
********************************************************************************
** File name: toa_wl00_model_if.c
** 
** Description: Public cycle segmentation interfaces.
*******************************************************************************/

#include <toa_wl00_model_if.h>

/* Inputs */

bool TOA_invalidate_outputs = true;   /* initialize to BAD*/
float  TOA_lift_valve_cmd = 0.f;
float  TOA_tilt_valve_cmd = 0.f;
float  TOA_tilt_extension = 0.f;
float  TOA_lift_angle = 0.f;
float  TOA_lift_he_pressure = 0.f;
float  TOA_lift_re_pressure = 0.f;
float  TOA_tilt_he_pressure = 0.f;
float  TOA_tilt_re_pressure = 0.f;
float  TOA_eef_imu_accelX = 0.f;
float  TOA_eef_imu_accelY = 0.f;
float  TOA_eef_imu_accelZ = 0.f;
float  TOA_steering_angle = 0.f;
float  TOA_tool_mass = 0.f;
float  TOA_truck_target_wt = 0.f;
float  TOA_truck_start_weight = 0.f;
uint8_t  TOA_bucket_current_weight_accuracy = 0;
float  TOA_bucket_current_weight = 0.f;
uint8_t  TOA_tipoff_mode = 0;
float TOA_zero_offset = 0.f;
float TOA_simple_cal_factor = 1.f;  /* default is 1 */
float TOA_imu_pitch_cal = 0.f;
float TOA_bucket_angle = 0.f;
bool TOA_unlatch_trigger = false;
float TOA_anchor_zero_offset = 0.f;
float TOA_anchor_factor = 1.f;
uint16_t TOA_Pass_Count = 0;;
float TOA_Lift_Norm_Angle = 0.f;
float TOA_Lift_Norm_Length = 0.f;
float TOA_Tilt_Norm_Angle = 0.f;
float TOA_Tilt_Norm_Length = 0.f;
float TOA_Friction_Mu = 0.f;
float TOA_Friction_Offset = 0.f;

/* Outputs */

float TOA_tilt_sensitivity_out = 0.f;
float TOA_tilt_pressure_out = 0.f;
float TOA_arbitrated_payload_norm_error_out = 0.f;
uint8_t TOA_weigh_status_out = 0;
float TOA_payload_norm_stdev_out = 0.f;
uint8_t TOA_pcs_weight_accuracy_out = 0;
float TOA_current_weight_norm_error_out = 0.f;
uint8_t TOA_error_code_out = 0;
float TOA_spill_rate_out = 0.f;
float TOA_payload_send_to_CPM = 0.f;
uint8_t TOA_payload_status_send_to_CPM = 0; /* INVALID*/
float  TOA_bucket_payload_target = 0.f;
float TOA_unsecured_payload_upper_bound_norm = 0.f;
float TOA_unsecured_payload_lower_bound_norm = 0.f;
uint8_t TOA_unsecured_PFW_status = 0;
float TOA_min_secure_bucket_angle = 0.f;
