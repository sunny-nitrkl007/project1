/******************************************************************************
 **          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 **         This work contains proprietary information, which may
 **         constitute a trade secret and/or be confidential.
 **-----------------------------------------------------------------------------
 ** File: demo_sim_a6n2.c
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
#include "demo_sim_a6n2.h"
#include "demo_sim_a6n2_private.h"
#include "look1_iflf_binlxpw.h"
#include "look2_iflf_binlxpw.h"

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

/* Model step function */
void demo_sim_a6n2_step(RT_MODEL_demo_sim_a6n2 *const demo_sim_a6n2_M, real32_T
  demo_sim_a6n2_U_pos_lift_desired, real32_T demo_sim_a6n2_U_pos_lift_rate,
  real32_T demo_sim_a6n2_U_pos_tilt_desired, real32_T
  demo_sim_a6n2_U_pos_tilt_rate, real32_T demo_sim_a6n2_U_payload_desired,
  real32_T *demo_sim_a6n2_Y_pres_lift_he, real32_T *demo_sim_a6n2_Y_angle_lift,
  real32_T *demo_sim_a6n2_Y_angle_AFE, real32_T
  *demo_sim_a6n2_Y_angle_ABC_supplement)
{
  BlockIO_demo_sim_a6n2 *demo_sim_a6n2_B = ((BlockIO_demo_sim_a6n2 *)
    demo_sim_a6n2_M->blockIO);
  D_Work_demo_sim_a6n2 *demo_sim_a6n2_DWork = ((D_Work_demo_sim_a6n2 *)
    demo_sim_a6n2_M->dwork);
  real32_T rtb_Sum_kinf;
  real32_T rtb_getting_close_cmd;
  real32_T rtb_Sum_dyj0;
  real32_T rtb_Sum_pydy;
  real32_T u1;

  /* MultiPortSwitch: '<S3>/Multiport Switch2' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Constant: '<S1>/Constant12'
   *  Constant: '<S3>/Constant2'
   *  Constant: '<S3>/Constant8'
   *  Inport: '<Root>/payload_desired'
   *  Inport: '<Root>/pos_tilt_rate'
   *  MultiPortSwitch: '<S1>/Multiport Switch5'
   *  Product: '<S1>/Divide3'
   */
  if (((int32_t)demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->manual_override) == 0) {
    demo_sim_a6n2_B->payload_desired_final = demo_sim_a6n2_U_payload_desired;
    demo_sim_a6n2_B->pos_tilt_lever_pct =
      demo_sim_a6n2_M->demo_sim_a6n2_catParameters_si_RAM_p->tilt_cycle_time *
      demo_sim_a6n2_U_pos_tilt_rate;

    /* MultiPortSwitch: '<S1>/Multiport Switch6' incorporates:
     *  Constant: '<S1>/Constant12'
     *  Inport: '<Root>/payload_desired'
     *  Inport: '<Root>/pos_tilt_desired'
     *  Inport: '<Root>/pos_tilt_rate'
     *  Product: '<S1>/Divide3'
     */
    demo_sim_a6n2_B->pos_tilt_desired_final = demo_sim_a6n2_U_pos_tilt_desired;
  } else {
    demo_sim_a6n2_B->payload_desired_final =
      demo_sim_a6n2_M->demo_sim_a6n2_catParameters_si_RAM_p->payload_desired_ov;
    demo_sim_a6n2_B->pos_tilt_lever_pct =
      demo_sim_a6n2_M->demo_sim_a6n2_catParameters_si_RAM_p->pos_tilt_lever_ov;

    /* MultiPortSwitch: '<S1>/Multiport Switch6' incorporates:
     *  Constant: '<S1>/Constant1'
     *  Constant: '<S1>/Constant6'
     *  Constant: '<S3>/Constant2'
     */
    demo_sim_a6n2_B->pos_tilt_desired_final =
      demo_sim_a6n2_M->demo_sim_a6n2_catParameters_si_RAM_p->pos_tilt_desired_ov;
  }

  /* End of MultiPortSwitch: '<S3>/Multiport Switch2' */

  /* Product: '<S3>/Divide4' incorporates:
   *  Constant: '<S3>/Constant14'
   */
  demo_sim_a6n2_B->payload_ratio = demo_sim_a6n2_B->payload_desired_final /
    demo_sim_a6n2_M->demo_sim_a6n2_catParameters_si_RAM_p->rated_payload;

  /* DataTypeConversion: '<S8>/Conversion' incorporates:
   *  UnitDelay: '<S8>/Unit Delay'
   */
  demo_sim_a6n2_B->lift_cyl_ext_mm = demo_sim_a6n2_DWork->UnitDelay_DSTATE;

  /* Sum: '<S4>/Sum' incorporates:
   *  Constant: '<S4>/Constant1'
   *  Constant: '<S4>/Constant3'
   */
  rtb_Sum_kinf = demo_sim_a6n2_M->
    demo_sim_a6n2_catParameters_si_RAM_p->lift_cyl_len_max_mm -
    demo_sim_a6n2_M->demo_sim_a6n2_catParameters_si_RAM_p->lift_cyl_len_min_mm;

  /* Product: '<S4>/Product' incorporates:
   *  Constant: '<S4>/Constant6'
   */
  demo_sim_a6n2_B->lift_cyl_ext_norm = (demo_sim_a6n2_B->lift_cyl_ext_mm *
    100.0F) / rtb_Sum_kinf;

  /* Lookup_n-D: '<S3>/Empty Lift Pressures' */
  rtb_getting_close_cmd = look1_iflf_binlxpw(demo_sim_a6n2_B->lift_cyl_ext_norm,
    &(demo_sim_a6n2_M->
      demo_sim_a6n2_catParameters_si_RAM_p->raise_slow_empty_lift_heights[0]),
    &(demo_sim_a6n2_M->
      demo_sim_a6n2_catParameters_si_RAM_p->raise_slow_empty_lift_pressures[0]),
    25U);

  /* Sum: '<S3>/Sum1' incorporates:
   *  Lookup_n-D: '<S3>/Loaded Lift Pressures'
   *  Product: '<S3>/Multiply'
   *  Sum: '<S3>/Sum'
   */
  demo_sim_a6n2_B->pres_lift_he = ((look1_iflf_binlxpw
    (demo_sim_a6n2_B->lift_cyl_ext_norm,
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->raise_slow_full_lift_heights[0]),
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->raise_slow_full_lift_pressures[0]),
     25U) - rtb_getting_close_cmd) * demo_sim_a6n2_B->payload_ratio) +
    rtb_getting_close_cmd;

  /* Outport: '<Root>/pres_lift_he' */
  *demo_sim_a6n2_Y_pres_lift_he = demo_sim_a6n2_B->pres_lift_he;

  /* Lookup_n-D: '<S4>/Lift cyl len to angle' */
  demo_sim_a6n2_B->angle_lift = look1_iflf_binlxpw
    (demo_sim_a6n2_B->lift_cyl_ext_mm,
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->lift_ang_map_lift_cyl_ext[0]),
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->lift_ang_map_output[0]), 39U);

  /* Outport: '<Root>/angle_lift' */
  *demo_sim_a6n2_Y_angle_lift = demo_sim_a6n2_B->angle_lift;

  /* DataTypeConversion: '<S7>/Conversion' incorporates:
   *  UnitDelay: '<S7>/Unit Delay'
   */
  demo_sim_a6n2_B->tilt_cyl_ext_mm = demo_sim_a6n2_DWork->UnitDelay_DSTATE_gxk4;

  /* Lookup_n-D: '<S4>/Calculate Angle AFE' */
  demo_sim_a6n2_B->angle_AFE = look2_iflf_binlxpw
    (demo_sim_a6n2_B->tilt_cyl_ext_mm, demo_sim_a6n2_B->lift_cyl_ext_mm,
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->angle_AFE_map_tilt_cyl_ext[0]),
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->angle_AFE_map_lift_cyl_ext[0]),
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->angle_AFE_map_output[0]),
     demo_sim_a6n2_ConstP.pooled6, 40U);

  /* Outport: '<Root>/angle_AFE' */
  *demo_sim_a6n2_Y_angle_AFE = demo_sim_a6n2_B->angle_AFE;

  /* Lookup_n-D: '<S4>/Calculate Angle ABC Supplement' */
  demo_sim_a6n2_B->angle_ABC_supplement = look2_iflf_binlxpw
    (demo_sim_a6n2_B->tilt_cyl_ext_mm, demo_sim_a6n2_B->lift_cyl_ext_mm,
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->angle_ABC_supplement_map_tilt_cyl_ext
       [0]), &(demo_sim_a6n2_M->
               demo_sim_a6n2_catParameters_si_RAM_p->angle_ABC_supplement_map_lift_cyl_ext
               [0]), &(demo_sim_a6n2_M->
                       demo_sim_a6n2_catParameters_si_RAM_p->angle_ABC_supplement_map_output
                       [0]), demo_sim_a6n2_ConstP.pooled6, 40U);

  /* Outport: '<Root>/angle_ABC_supplement' */
  *demo_sim_a6n2_Y_angle_ABC_supplement = demo_sim_a6n2_B->angle_ABC_supplement;

  /* Lookup_n-D: '<S4>/Calculate Bucket Angle' */
  demo_sim_a6n2_B->bucket_angle = look2_iflf_binlxpw
    (demo_sim_a6n2_B->tilt_cyl_ext_mm, demo_sim_a6n2_B->lift_cyl_ext_mm,
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->bucket_ang_map_tilt_cyl_ext[0]),
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->bucket_ang_map_lift_cyl_ext[0]),
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->bucket_ang_map_output[0]),
     demo_sim_a6n2_ConstP.pooled6, 40U);

  /* Product: '<S4>/Product1' incorporates:
   *  Constant: '<S4>/Constant2'
   *  Constant: '<S4>/Constant4'
   *  Constant: '<S4>/Constant7'
   *  Sum: '<S4>/Sum1'
   */
  demo_sim_a6n2_B->tilt_cyl_ext_norm = (100.0F /
    (demo_sim_a6n2_M->demo_sim_a6n2_catParameters_si_RAM_p->tilt_cyl_len_max_mm
     - demo_sim_a6n2_M->
     demo_sim_a6n2_catParameters_si_RAM_p->tilt_cyl_len_min_mm)) *
    demo_sim_a6n2_B->tilt_cyl_ext_mm;

  /* Sum: '<S6>/Sum' */
  rtb_getting_close_cmd = demo_sim_a6n2_B->pos_tilt_desired_final -
    demo_sim_a6n2_B->tilt_cyl_ext_norm;

  /* Abs: '<S6>/Abs1' */
  rtb_Sum_pydy = (real32_T)fabs(demo_sim_a6n2_B->pos_tilt_lever_pct);

  /* SampleTimeMath: '<S6>/Weighted Sample Time Divide' incorporates:
   *  Abs: '<S6>/Abs'
   *
   * About '<S6>/Weighted Sample Time Divide':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  u1 = ((real32_T)fabs(rtb_getting_close_cmd)) * 50.0F;

  /* MinMax: '<S6>/MinMax' */
  if ((rtb_Sum_pydy < u1) || (rtIsNaNF(u1))) {
    u1 = rtb_Sum_pydy;
  }

  /* End of MinMax: '<S6>/MinMax' */

  /* Signum: '<S6>/Sign' */
  if (rtb_getting_close_cmd < 0.0F) {
    rtb_getting_close_cmd = -1.0F;
  } else if (rtb_getting_close_cmd > 0.0F) {
    rtb_getting_close_cmd = 1.0F;
  } else if (rtb_getting_close_cmd == 0.0F) {
    rtb_getting_close_cmd = 0.0F;
  } else {
    rtb_getting_close_cmd = (rtNaNF);
  }

  /* End of Signum: '<S6>/Sign' */

  /* Product: '<S6>/Product' */
  demo_sim_a6n2_B->pos_tilt_desired_cmd = u1 * rtb_getting_close_cmd;

  /* MultiPortSwitch: '<S1>/Multiport Switch1' incorporates:
   *  Constant: '<S1>/Constant5'
   */
  if (((int32_t)demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->position_control) != 0) {
    demo_sim_a6n2_B->pos_tilt_lever_pct = demo_sim_a6n2_B->pos_tilt_desired_cmd;
  }

  /* End of MultiPortSwitch: '<S1>/Multiport Switch1' */

  /* Lookup_n-D: '<S4>/Tilt cmd to flow in lpm' */
  demo_sim_a6n2_B->flow_tilt_lpm = look1_iflf_binlxpw
    (demo_sim_a6n2_B->pos_tilt_lever_pct,
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->tilt_flow_map_lever_cmd[0]),
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->tilt_flow_map_output[0]), 20U);

  /* Switch: '<S10>/Switch1' incorporates:
   *  Constant: '<S10>/Constant1'
   *  Constant: '<S10>/Constant3'
   *  Constant: '<S14>/Constant'
   *  RelationalOperator: '<S14>/Compare'
   */
  if (demo_sim_a6n2_B->pos_tilt_lever_pct > 0.0F) {
    rtb_Sum_pydy = demo_sim_a6n2_M->
      demo_sim_a6n2_catParameters_si_RAM_p->tilt_cyl_he_area;
  } else {
    rtb_Sum_pydy = demo_sim_a6n2_M->
      demo_sim_a6n2_catParameters_si_RAM_p->tilt_cyl_re_area;
  }

  /* End of Switch: '<S10>/Switch1' */

  /* Product: '<S10>/Divide2' incorporates:
   *  Gain: '<S10>/liter//min to mm3//sec'
   */
  demo_sim_a6n2_B->velocity_tilt_mmps = (16666.666F *
    demo_sim_a6n2_B->flow_tilt_lpm) / rtb_Sum_pydy;

  /* Sum: '<S7>/Sum' incorporates:
   *  SampleTimeMath: '<S7>/Sample Time Multiply'
   *  UnitDelay: '<S7>/Unit Delay'
   *
   * About '<S7>/Sample Time Multiply':
   *  y = u * K where K = ( w * Ts )
   */
  rtb_getting_close_cmd = (demo_sim_a6n2_B->velocity_tilt_mmps * 0.02F) +
    demo_sim_a6n2_DWork->UnitDelay_DSTATE_gxk4;

  /* Lookup_n-D: '<S4>/Max tilt cyl extension at current lift position' */
  demo_sim_a6n2_B->tilt_cyl_ext_max_mm = look1_iflf_binlxpw
    (demo_sim_a6n2_B->lift_cyl_ext_mm,
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->tilt_cyl_ext_map_lift_ext[0]),
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->tilt_cyl_ext_max_map_output[0]),
     39U);

  /* Lookup_n-D: '<S4>/Min tilt cyl extension at current lift position' */
  demo_sim_a6n2_B->tilt_cyl_ext_min_mm = look1_iflf_binlxpw
    (demo_sim_a6n2_B->lift_cyl_ext_mm,
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->tilt_cyl_ext_map_lift_ext[0]),
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->tilt_cyl_ext_min_map_output[0]),
     39U);

  /* Switch: '<S11>/Switch2' incorporates:
   *  RelationalOperator: '<S11>/LowerRelop1'
   *  RelationalOperator: '<S11>/UpperRelop'
   *  Switch: '<S11>/Switch'
   */
  if (rtb_getting_close_cmd > demo_sim_a6n2_B->tilt_cyl_ext_max_mm) {
    rtb_getting_close_cmd = demo_sim_a6n2_B->tilt_cyl_ext_max_mm;
  } else {
    if (rtb_getting_close_cmd < demo_sim_a6n2_B->tilt_cyl_ext_min_mm) {
      /* Switch: '<S11>/Switch' */
      rtb_getting_close_cmd = demo_sim_a6n2_B->tilt_cyl_ext_min_mm;
    }
  }

  /* End of Switch: '<S11>/Switch2' */

  /* MultiPortSwitch: '<S1>/Multiport Switch3' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant11'
   *  Constant: '<S1>/Constant7'
   *  Inport: '<Root>/pos_lift_rate'
   *  Product: '<S1>/Divide2'
   */
  if (((int32_t)demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->manual_override) == 0) {
    demo_sim_a6n2_B->pos_lift_lever_pct =
      demo_sim_a6n2_M->demo_sim_a6n2_catParameters_si_RAM_p->lift_cycle_time *
      demo_sim_a6n2_U_pos_lift_rate;

    /* MultiPortSwitch: '<S1>/Multiport Switch4' incorporates:
     *  Constant: '<S1>/Constant11'
     *  Inport: '<Root>/pos_lift_desired'
     *  Inport: '<Root>/pos_lift_rate'
     *  Product: '<S1>/Divide2'
     */
    demo_sim_a6n2_B->pos_lift_desired_final = demo_sim_a6n2_U_pos_lift_desired;
  } else {
    demo_sim_a6n2_B->pos_lift_lever_pct =
      demo_sim_a6n2_M->demo_sim_a6n2_catParameters_si_RAM_p->pos_lift_lever_ov;

    /* MultiPortSwitch: '<S1>/Multiport Switch4' incorporates:
     *  Constant: '<S1>/Constant'
     *  Constant: '<S1>/Constant4'
     */
    demo_sim_a6n2_B->pos_lift_desired_final =
      demo_sim_a6n2_M->demo_sim_a6n2_catParameters_si_RAM_p->pos_lift_desired_ov;
  }

  /* End of MultiPortSwitch: '<S1>/Multiport Switch3' */

  /* Sum: '<S5>/Sum' */
  rtb_Sum_dyj0 = demo_sim_a6n2_B->pos_lift_desired_final -
    demo_sim_a6n2_B->lift_cyl_ext_norm;

  /* Abs: '<S5>/Abs1' */
  rtb_Sum_pydy = (real32_T)fabs(demo_sim_a6n2_B->pos_lift_lever_pct);

  /* SampleTimeMath: '<S5>/Weighted Sample Time Divide' incorporates:
   *  Abs: '<S5>/Abs'
   *
   * About '<S5>/Weighted Sample Time Divide':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  u1 = ((real32_T)fabs(rtb_Sum_dyj0)) * 50.0F;

  /* MinMax: '<S5>/MinMax' */
  if ((rtb_Sum_pydy < u1) || (rtIsNaNF(u1))) {
    u1 = rtb_Sum_pydy;
  }

  /* End of MinMax: '<S5>/MinMax' */

  /* Signum: '<S5>/Sign' */
  if (rtb_Sum_dyj0 < 0.0F) {
    rtb_Sum_dyj0 = -1.0F;
  } else if (rtb_Sum_dyj0 > 0.0F) {
    rtb_Sum_dyj0 = 1.0F;
  } else if (rtb_Sum_dyj0 == 0.0F) {
    rtb_Sum_dyj0 = 0.0F;
  } else {
    rtb_Sum_dyj0 = (rtNaNF);
  }

  /* End of Signum: '<S5>/Sign' */

  /* Product: '<S5>/Product' */
  demo_sim_a6n2_B->pos_lift_desired_cmd = u1 * rtb_Sum_dyj0;

  /* MultiPortSwitch: '<S1>/Multiport Switch' incorporates:
   *  Constant: '<S1>/Constant3'
   */
  if (((int32_t)demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->position_control) != 0) {
    demo_sim_a6n2_B->pos_lift_lever_pct = demo_sim_a6n2_B->pos_lift_desired_cmd;
  }

  /* End of MultiPortSwitch: '<S1>/Multiport Switch' */

  /* Lookup_n-D: '<S4>/Lift cmd to flow in lpm' */
  demo_sim_a6n2_B->flow_lift_lpm = look1_iflf_binlxpw
    (demo_sim_a6n2_B->pos_lift_lever_pct,
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->lift_flow_map_lever_cmd[0]),
     &(demo_sim_a6n2_M->
       demo_sim_a6n2_catParameters_si_RAM_p->lift_flow_map_output[0]), 20U);

  /* Switch: '<S9>/Switch1' incorporates:
   *  Constant: '<S13>/Constant'
   *  Constant: '<S9>/Constant1'
   *  Constant: '<S9>/Constant3'
   *  RelationalOperator: '<S13>/Compare'
   */
  if (demo_sim_a6n2_B->pos_lift_lever_pct > 0.0F) {
    rtb_Sum_pydy = demo_sim_a6n2_M->
      demo_sim_a6n2_catParameters_si_RAM_p->lift_cyl_he_area;
  } else {
    rtb_Sum_pydy = demo_sim_a6n2_M->
      demo_sim_a6n2_catParameters_si_RAM_p->lift_cyl_re_area;
  }

  /* End of Switch: '<S9>/Switch1' */

  /* Product: '<S9>/Divide2' incorporates:
   *  Gain: '<S9>/liter//min to mm3//sec'
   */
  demo_sim_a6n2_B->velocity_lift_mmps = (16666.666F *
    demo_sim_a6n2_B->flow_lift_lpm) / rtb_Sum_pydy;

  /* Sum: '<S8>/Sum' incorporates:
   *  SampleTimeMath: '<S8>/Sample Time Multiply'
   *  UnitDelay: '<S8>/Unit Delay'
   *
   * About '<S8>/Sample Time Multiply':
   *  y = u * K where K = ( w * Ts )
   */
  rtb_Sum_pydy = (demo_sim_a6n2_B->velocity_lift_mmps * 0.02F) +
    demo_sim_a6n2_DWork->UnitDelay_DSTATE;

  /* Switch: '<S12>/Switch2' incorporates:
   *  Constant: '<S4>/Constant5'
   *  RelationalOperator: '<S12>/LowerRelop1'
   *  RelationalOperator: '<S12>/UpperRelop'
   *  Switch: '<S12>/Switch'
   */
  if (rtb_Sum_pydy > rtb_Sum_kinf) {
    /* Update for UnitDelay: '<S8>/Unit Delay' */
    demo_sim_a6n2_DWork->UnitDelay_DSTATE = rtb_Sum_kinf;
  } else if (rtb_Sum_pydy < 0.0F) {
    /* Switch: '<S12>/Switch' incorporates:
     *  Constant: '<S4>/Constant5'
     *  UnitDelay: '<S8>/Unit Delay'
     */
    demo_sim_a6n2_DWork->UnitDelay_DSTATE = 0.0F;
  } else {
    /* Update for UnitDelay: '<S8>/Unit Delay' incorporates:
     *  Switch: '<S12>/Switch'
     */
    demo_sim_a6n2_DWork->UnitDelay_DSTATE = rtb_Sum_pydy;
  }

  /* End of Switch: '<S12>/Switch2' */

  /* Update for UnitDelay: '<S7>/Unit Delay' */
  demo_sim_a6n2_DWork->UnitDelay_DSTATE_gxk4 = rtb_getting_close_cmd;
}

/* Model initialize function */
void demo_sim_a6n2_initialize(RT_MODEL_demo_sim_a6n2 *const demo_sim_a6n2_M,
  real32_T *demo_sim_a6n2_Y_pres_lift_re)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* ConstCode for Outport: '<Root>/pres_lift_re' incorporates:
   *  Constant: '<S3>/Constant13'
   */
  *demo_sim_a6n2_Y_pres_lift_re = 101.0F;
  UNUSED_PARAMETER(demo_sim_a6n2_M);
}
