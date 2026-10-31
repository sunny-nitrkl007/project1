/*******************************************************************************
** COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
*****************************************************************************
File name: toa_wl00_model_if.h

Description: Public cycle segmentation interfaces.
*******************************************************************************/

#ifndef TOA_WL00_MODEL_IF_H__
#define TOA_WL00_MODEL_IF_H__


#include "toa_wl00_Pack_types.h"

/*Target Where The File std_types.h Is Provided By Caterpillar
**     For this target, there is no AUTOSAR content, so there is
**     no conflict.
*/
#include <stdint.h>
#include <stdbool.h>
//#include <std_types.h>
//#include <cat_std_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------------------------------------------- */
/* Inputs */
/* --------------------------------------------------------------------- */

/* single input that qualifies the inputs for tipoff weight
 * true - inputs BAD
 * false - inputs GOOD
 * */
extern bool TOA_invalidate_outputs;

/* +/-100% */
extern float  TOA_lift_valve_cmd;

/* +/-100% */
extern float  TOA_tilt_valve_cmd;

/* millimeters */
extern float  TOA_tilt_extension;

/* degrees  */
extern float  TOA_lift_angle;

/* kpa */
extern float  TOA_lift_he_pressure;
extern float  TOA_lift_re_pressure;
extern float  TOA_tilt_he_pressure;
extern float  TOA_tilt_re_pressure;

/* m/s^2 */
extern float  TOA_eef_imu_accelX;
extern float  TOA_eef_imu_accelY;
extern float  TOA_eef_imu_accelZ;

/* degrees */
extern float  TOA_steering_angle;

/*metric tonnes */
extern float  TOA_tool_mass;

/* metric tonnes */
extern float  TOA_truck_target_wt;
extern float  TOA_truck_start_weight;

/*
 * 0 - none
 * 1 - low
 * 2 - med
 * 3 - high
 * */
extern uint8_t  TOA_bucket_current_weight_accuracy;

/* metric tonnes */
extern float  TOA_bucket_current_weight;

/*
 * 1 - Truck
 * 2 - Pile
 * */
extern uint8_t  TOA_tipoff_mode;

/* zero bucket offset */
extern float TOA_zero_offset;

/* simple cal adjust factor */
extern float TOA_simple_cal_factor;

/* bucket angle in degrees */
extern float TOA_bucket_angle;

/* command to unlatch bucket weight */
extern bool TOA_unlatch_trigger;

/* IMU placement error correction angle */
extern float TOA_imu_pitch_cal;

/* Anchor_Zero_Offset*/
extern float TOA_anchor_zero_offset;

/* Anchor factor*/
extern float TOA_anchor_factor;

/* TOA_Pass_Count*/
extern uint16_t TOA_Pass_Count;

/* TOA_Lift_Norm_Angle (0.0-1.0)*/
extern float TOA_Lift_Norm_Angle;

/* TOA_Lift_Norm_Length (0.0-1.0)*/
extern float TOA_Lift_Norm_Length;

/* TOA_Tilt_Norm_Angle (0.0-1.0)*/
extern float TOA_Tilt_Norm_Angle;

/* TOA_Tilt_Norm_Length (0.0-1.0)*/
extern float TOA_Tilt_Norm_Length;

/* TOA_Friction_Mu */
extern float TOA_Friction_Mu;

/* TOA_Friction_Offset */
extern float TOA_Friction_Offset;

/* --------------------------------------------------------------------- */
/* Outputs */
/* --------------------------------------------------------------------- */

/* mm/rad of tilt cylinder extension to bucket angle */
extern float TOA_tilt_sensitivity_out;

/* tilt head-end pressure, kpa */
extern float TOA_tilt_pressure_out;

/* payload error relative to bucket target - +/-200% of rated payload */
extern float TOA_arbitrated_payload_norm_error_out;

/*
 * 0 - Invalid (weight is not good enough)
 * 1 - Valid (weight is good)
 * 2 - Pending (conditions are good that you may get a valid weight soon)
 * */
extern uint8_t TOA_weigh_status_out;

/* stddev of weight samples collected during valid measurement conditions
 * in % of rated payload 0-175% (expected range)
 * */
extern float TOA_payload_norm_stdev_out;

/* same as input */
extern uint8_t TOA_pcs_weight_accuracy_out;

/* payload error relative to bucket target - +/-200% of rated payload TODO either add PCS or CPM in the name*/
extern float TOA_current_weight_norm_error_out;

/*
 * 0 - NO_ERROR
 * 1 - TIP_OFF_MODE_NOT_PILE
 * 2 - TRUCK_TARGET_NOT_SET
 * 3 - PAYLOAD_NOT_ACHIEVABLE
 *
 * */
extern uint8_t TOA_error_code_out;

/* rate at which material is spilling from bucket (% of rated payload per second) */
extern float TOA_spill_rate_out;

/* new math tipoff weight in tonnes */
extern float TOA_payload_send_to_CPM;

/* new math tipoff weight status
 * 0 - INVALID
 * 1 - LIVE
 * 2 - PSEUDO_FRICTIONLESS
 * */
extern uint8_t TOA_payload_status_send_to_CPM;

/*Bucket Payload Target in tonnes */
extern float  TOA_bucket_payload_target;

/* TOA_unsecured_payload_upper_bound_norm +/-200% */
extern float TOA_unsecured_payload_upper_bound_norm;

/* TOA_unsecured_payload_lower_bound_norm +/-200% */
extern float TOA_unsecured_payload_lower_bound_norm;

/* TOA_unsecured_PFW_status
 * 0 - INVALID
 * 1 - VALID
 * 2 - PENDING
 * 3 - FAULT
 * */
extern uint8_t TOA_unsecured_PFW_status;

/* TOA_min_secure_bucket_angle degrees */
extern float TOA_min_secure_bucket_angle;

/*
* Simulink Model work structure for troubleshooting access
*/
//extern toa_wl00_work_t toa_wl00_work;


#ifdef __cplusplus
}
#endif
#endif /* TOA_WL00_MODEL_IF_H__ */

