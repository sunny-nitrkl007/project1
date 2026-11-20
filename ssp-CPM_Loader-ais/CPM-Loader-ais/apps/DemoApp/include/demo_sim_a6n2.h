/******************************************************************************
 **          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 **         This work contains proprietary information, which may
 **         constitute a trade secret and/or be confidential.
 **-----------------------------------------------------------------------------
 ** File: demo_sim_a6n2.h
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
#ifndef RTW_HEADER_demo_sim_a6n2_h_
#define RTW_HEADER_demo_sim_a6n2_h_
#include <math.h>
#ifndef demo_sim_a6n2_COMMON_INCLUDES_
# define demo_sim_a6n2_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* demo_sim_a6n2_COMMON_INCLUDES_ */

#include "demo_sim_a6n2_types.h"
#include "demo_sim_a6n2_variant.h"
#include "demo_sim_a6n2_variant.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rt_defines.h"

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->blockIO = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->dwork = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  real32_T payload_desired_final;      /* '<S3>/Multiport Switch2' */
  real32_T payload_ratio;              /* '<S3>/Divide4' */
  real32_T lift_cyl_ext_mm;            /* '<S8>/Conversion' */
  real32_T lift_cyl_ext_norm;          /* '<S4>/Product' */
  real32_T pres_lift_he;               /* '<S3>/Sum1' */
  real32_T angle_lift;                 /* '<S4>/Lift cyl len to angle' */
  real32_T tilt_cyl_ext_mm;            /* '<S7>/Conversion' */
  real32_T angle_AFE;                  /* '<S4>/Calculate Angle AFE' */
  real32_T angle_ABC_supplement;       /* '<S4>/Calculate Angle ABC Supplement' */
  real32_T bucket_angle;               /* '<S4>/Calculate Bucket Angle' */
  real32_T pos_tilt_desired_final;     /* '<S1>/Multiport Switch6' */
  real32_T tilt_cyl_ext_norm;          /* '<S4>/Product1' */
  real32_T pos_tilt_desired_cmd;       /* '<S6>/Product' */
  real32_T pos_tilt_lever_pct;         /* '<S1>/Multiport Switch1' */
  real32_T flow_tilt_lpm;              /* '<S4>/Tilt cmd to flow in lpm' */
  real32_T velocity_tilt_mmps;         /* '<S10>/Divide2' */
  real32_T tilt_cyl_ext_max_mm;        /* '<S4>/Max tilt cyl extension at current lift position' */
  real32_T tilt_cyl_ext_min_mm;        /* '<S4>/Min tilt cyl extension at current lift position' */
  real32_T pos_lift_desired_final;     /* '<S1>/Multiport Switch4' */
  real32_T pos_lift_desired_cmd;       /* '<S5>/Product' */
  real32_T pos_lift_lever_pct;         /* '<S1>/Multiport Switch' */
  real32_T flow_lift_lpm;              /* '<S4>/Lift cmd to flow in lpm' */
  real32_T velocity_lift_mmps;         /* '<S9>/Divide2' */
} BlockIO_demo_sim_a6n2;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T UnitDelay_DSTATE;           /* '<S8>/Unit Delay' */
  real32_T UnitDelay_DSTATE_gxk4;      /* '<S7>/Unit Delay' */
} D_Work_demo_sim_a6n2;

/* Constant parameters (auto storage) */
typedef struct {
  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S4>/Calculate Angle ABC Supplement'
   *   '<S4>/Calculate Angle AFE'
   *   '<S4>/Calculate Bucket Angle'
   */
  uint32_t pooled6[2];
} ConstParam_demo_sim_a6n2;

/* Real-time Model Data Structure */
struct tag_RTM_demo_sim_a6n2 {
  BlockIO_demo_sim_a6n2 *blockIO;
  D_Work_demo_sim_a6n2 *dwork;
  demo_sim_a6n2_catParameters_si_RAM_t * demo_sim_a6n2_catParameters_si_RAM_p;
};

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/* Constant parameters (auto storage) */
extern const ConstParam_demo_sim_a6n2 demo_sim_a6n2_ConstP;

/* Model entry point functions */
extern void demo_sim_a6n2_initialize(RT_MODEL_demo_sim_a6n2 *const
  demo_sim_a6n2_M, real32_T *demo_sim_a6n2_Y_pres_lift_re);
extern void demo_sim_a6n2_step(RT_MODEL_demo_sim_a6n2 *const demo_sim_a6n2_M,
  real32_T demo_sim_a6n2_U_pos_lift_desired, real32_T
  demo_sim_a6n2_U_pos_lift_rate, real32_T demo_sim_a6n2_U_pos_tilt_desired,
  real32_T demo_sim_a6n2_U_pos_tilt_rate, real32_T
  demo_sim_a6n2_U_payload_desired, real32_T *demo_sim_a6n2_Y_pres_lift_he,
  real32_T *demo_sim_a6n2_Y_angle_lift, real32_T *demo_sim_a6n2_Y_angle_AFE,
  real32_T *demo_sim_a6n2_Y_angle_ABC_supplement);

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'demo_sim_a6n2'
 * '<S1>'   : 'demo_sim_a6n2/Machine Model1'
 * '<S2>'   : 'demo_sim_a6n2/Package Instance'
 * '<S3>'   : 'demo_sim_a6n2/Machine Model1/Calculate Pressures from Payload'
 * '<S4>'   : 'demo_sim_a6n2/Machine Model1/Flow and Kinematics'
 * '<S5>'   : 'demo_sim_a6n2/Machine Model1/Lift Position Control'
 * '<S6>'   : 'demo_sim_a6n2/Machine Model1/Tilt Position Control'
 * '<S7>'   : 'demo_sim_a6n2/Machine Model1/Flow and Kinematics/Integrator Forward Limited1'
 * '<S8>'   : 'demo_sim_a6n2/Machine Model1/Flow and Kinematics/Integrator Forward Limited2'
 * '<S9>'   : 'demo_sim_a6n2/Machine Model1/Flow and Kinematics/Lift lpm to mmps'
 * '<S10>'  : 'demo_sim_a6n2/Machine Model1/Flow and Kinematics/Tilt lpm to mmps'
 * '<S11>'  : 'demo_sim_a6n2/Machine Model1/Flow and Kinematics/Integrator Forward Limited1/Saturation Dynamic'
 * '<S12>'  : 'demo_sim_a6n2/Machine Model1/Flow and Kinematics/Integrator Forward Limited2/Saturation Dynamic'
 * '<S13>'  : 'demo_sim_a6n2/Machine Model1/Flow and Kinematics/Lift lpm to mmps/Compare To Zero'
 * '<S14>'  : 'demo_sim_a6n2/Machine Model1/Flow and Kinematics/Tilt lpm to mmps/Compare To Zero'
 */
#endif                                 /* RTW_HEADER_demo_sim_a6n2_h_ */
