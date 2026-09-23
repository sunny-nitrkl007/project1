/******************************************************************************
 **          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 **         This work contains proprietary information, which may
 **         constitute a trade secret and/or be confidential.
 **-----------------------------------------------------------------------------
 ** File: demo_sim_a6n2_variant.h
 **
 ** Real-Time Workshop code generated for Simulink model demo_sim_a6n2.
 **
 ** Model version                        : 1.42
 ** Real-Time Workshop file version      : 8.13 (R2017b) 24-Jul-2017
 ** MATLAB Version                       : 9.3.0.948333 (R2017b) Update 9
 ** CATutils_MatLab version              : CATUTILS_MATLAB_4.6.5
 **
 ******************************************************************************/

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#ifndef RTW_HEADER_demo_sim_a6n2_variant_h_
#define RTW_HEADER_demo_sim_a6n2_variant_h_
#include "rtwtypes.h"
#include "demo_sim_a6n2_types.h"

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/
typedef struct demo_sim_a6n2_catParameters_si_RAM_tag {
  real32_T angle_ABC_supplement_map_lift_cyl_ext[40];
  real32_T angle_ABC_supplement_map_output[1600];
  real32_T angle_ABC_supplement_map_tilt_cyl_ext[40];
  real32_T angle_AFE_map_lift_cyl_ext[40];
  real32_T angle_AFE_map_output[1600];
  real32_T angle_AFE_map_tilt_cyl_ext[40];
  real32_T bucket_ang_map_lift_cyl_ext[40];
  real32_T bucket_ang_map_output[1600];
  real32_T bucket_ang_map_tilt_cyl_ext[40];
  real32_T lift_ang_map_lift_cyl_ext[40];
  real32_T lift_ang_map_output[40];
  real32_T lift_cycle_time;
  real32_T lift_cyl_he_area;
  real32_T lift_cyl_len_max_mm;
  real32_T lift_cyl_len_min_mm;
  real32_T lift_cyl_re_area;
  real32_T lift_flow_map_lever_cmd[21];
  real32_T lift_flow_map_output[21];
  real32_T manual_override;
  real32_T payload_desired_ov;
  real32_T pos_lift_desired_ov;
  real32_T pos_lift_lever_ov;
  real32_T pos_tilt_desired_ov;
  real32_T pos_tilt_lever_ov;
  real32_T position_control;
  real32_T raise_slow_empty_lift_heights[26];
  real32_T raise_slow_empty_lift_pressures[26];
  real32_T raise_slow_full_lift_heights[26];
  real32_T raise_slow_full_lift_pressures[26];
  real32_T rated_payload;
  real32_T tilt_cycle_time;
  real32_T tilt_cyl_ext_map_lift_ext[40];
  real32_T tilt_cyl_ext_max_map_output[40];
  real32_T tilt_cyl_ext_min_map_output[40];
  real32_T tilt_cyl_he_area;
  real32_T tilt_cyl_len_max_mm;
  real32_T tilt_cyl_len_min_mm;
  real32_T tilt_cyl_re_area;
  real32_T tilt_flow_map_lever_cmd[21];
  real32_T tilt_flow_map_output[21];
} demo_sim_a6n2_catParameters_si_RAM_t;

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
#endif                                 /* RTW_HEADER_demo_sim_a6n2_variant_h_ */
