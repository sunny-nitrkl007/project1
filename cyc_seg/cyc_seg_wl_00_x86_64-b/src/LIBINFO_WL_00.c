/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: LIBINFO_WL_00.c
 **
 ** Real-Time Workshop code generated for Simulink model LIBINFO_WL_00.
 **
 ** Model version                        : 1.118
 ** Real-Time Workshop file version      : 8.3 (R2012b) 20-Jul-2012
 ** TLC version                          : 8.3 (Jul 21 2012)
 ** CATutils_MatLab version              : CATUTILS_MATLAB_4.3.3
 **
 ******************************************************************************/

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#include "LIBINFO_WL_00.h"
#include "LIBINFO_WL_00_private.h"

#include <sl_unused_param_macro.h>

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/* Named constants for Chart: '<S93>/Classifier' */
#define LIBINFO_WL_00_IN_Active        ((uint8_t)1U)
#define LIBINFO_WL_00_IN_Digging       ((uint8_t)1U)
#define LIBINFO_WL_00_IN_Idle          ((uint8_t)2U)
#define LIBINFO_WL_00_IN_IdleDebounce  ((uint8_t)3U)
#define LIBINFO_WL_00_IN_Inactive      ((uint8_t)2U)
#define LIBINFO_WL_0_IN_NO_ACTIVE_CHILD ((uint8_t)0U)

/* Named constants for Chart: '<S93>/MaterialEngagementDetection' */
#define LIBINFO_WL_00_IN_Confirmed     ((uint8_t)1U)
#define LIBINFO_WL_00_IN_Debounce      ((uint8_t)2U)
#define LIBINFO_WL_00_IN_Decel         ((uint8_t)1U)
#define LIBINFO_WL_00_IN_Forward       ((uint8_t)1U)
#define LIBINFO_WL_00_IN_Neutral       ((uint8_t)2U)
#define LIBINFO_WL_00_IN_NotDecel      ((uint8_t)2U)
#define LIBINFO_WL_00_IN_Reverse       ((uint8_t)3U)
#define LIBINFO_WL_00_IN_Tentative     ((uint8_t)3U)
#define LIBINFO_WL_00_IN_Transition    ((uint8_t)4U)
#define LIBINFO_WL_00_IN_WaitForPayload ((uint8_t)3U)
#define LIBINFO_WL_IN_PayloadIncreasing ((uint8_t)2U)
#define LIBINFO_WL__IN_PayloadConfirmed ((uint8_t)1U)

/* Named constants for Chart: '<S94>/DumpState' */
#define LIBINFO_WL_00_IN_ConfirmedDump ((uint8_t)1U)
#define LIBINFO_WL_00_IN_Dumping       ((uint8_t)1U)
#define LIBINFO_WL_00_IN_FinishRacking ((uint8_t)2U)
#define LIBINFO_WL_00_IN_NotDump       ((uint8_t)2U)
#define LIBINFO_WL_00_IN_TentativeDump ((uint8_t)3U)
#define LIBINFO_WL__IN_TentativeNotDump ((uint8_t)3U)

/* Named constants for Chart: '<S94>/DumpType' */
#define LIBINFO_WL_00_IN_FullDump      ((uint8_t)1U)
#define LIBINFO_WL_00_IN_NotDumping    ((uint8_t)2U)
#define LIBINFO_WL_00_IN_PartialDump   ((uint8_t)2U)

/* Named constants for Chart: '<S139>/DetectMovement' */
#define LIBINFO_WL_00_IN_Armed         ((uint8_t)1U)
#define LIBINFO_WL_00_IN_DumpDetected  ((uint8_t)2U)
#define LIBINFO_WL_00_IN_Known         ((uint8_t)1U)
#define LIBINFO_WL_00_IN_RackDetected  ((uint8_t)3U)
#define LIBINFO_WL_00_IN_Unknown       ((uint8_t)2U)

/* Named constants for Chart: '<S95>/RunState' */
#define LIBINFO_WL_00_IN_ActiveDES     ((uint8_t)1U)
#define LIBINFO_WL_00_IN_EngineOff     ((uint8_t)1U)
#define LIBINFO_WL_00_IN_EngineOff_itep ((uint8_t)2U)
#define LIBINFO_WL_00_IN_EngineOn      ((uint8_t)2U)
#define LIBINFO_WL_00_IN_FinishCommit  ((uint8_t)2U)
#define LIBINFO_WL_00_IN_KeyOff        ((uint8_t)1U)
#define LIBINFO_WL_00_IN_KeyOn         ((uint8_t)2U)
#define LIBINFO_WL_00_IN_NotRunning    ((uint8_t)1U)
#define LIBINFO_WL_00_IN_Running       ((uint8_t)2U)
#define LIBINFO_WL_00_IN_Starting      ((uint8_t)3U)
#define LIBINFO_WL_00_IN_Stopping      ((uint8_t)4U)
#define LIBINFO_WL_00_IN_TentativeDES  ((uint8_t)3U)
#define LIBINFO_WL_0_IN_CommitEngineOff ((uint8_t)1U)
#define LIBINFO_W_IN_TentativeEngineOff ((uint8_t)3U)

/* Named constants for Chart: '<S96>/Loaded' */
#define LIBINFO_WL_00_IN_Loaded        ((uint8_t)1U)
#define LIBINFO_WL_00_IN_Unloaded      ((uint8_t)2U)

/* Named constants for Chart: '<S97>/IdleState' */
#define LIBINFO_WL_00_IN_NotStopped    ((uint8_t)1U)
#define LIBINFO_WL_00_IN_Stopped       ((uint8_t)2U)
#define LIBINFO_W_IN_TentativelyStopped ((uint8_t)4U)
#define LIBINF_IN_TentativelyNotStopped ((uint8_t)3U)

/* Named constants for Chart: '<S97>/LoadState' */
#define LIBINFO_WL_00_IN_Empty         ((uint8_t)1U)
#define LIBINFO_WL_00_IN_Loaded_a1mm   ((uint8_t)2U)

/* Named constants for Chart: '<S98>/LoadedState' */
#define LIBINFO_WL_00_IN_Backdrag      ((uint8_t)1U)
#define LIBINFO_WL_00_IN_Empty_gv30    ((uint8_t)2U)
#define LIBINFO_WL_00_IN_Loaded_ddwb   ((uint8_t)3U)

/* Named constants for Chart: '<S98>/TravellingState' */
#define LIBINFO_WL_00_IN_Confirm       ((uint8_t)1U)
#define LIBINFO_WL_00_IN_ForwardInit   ((uint8_t)1U)
#define LIBINFO_WL_00_IN_Hold          ((uint8_t)2U)
#define LIBINFO_WL_00_IN_NotTravelling ((uint8_t)1U)
#define LIBINFO_WL_00_IN_ReverseInit   ((uint8_t)3U)
#define LIBINFO_WL_00_IN_Reverse_inos  ((uint8_t)2U)
#define LIBINFO_WL_00_IN_Travelling    ((uint8_t)4U)
#define LIBINF_IN_TentativelyTravelling ((uint8_t)3U)
#define LIB_IN_TentativelyNotTravelling ((uint8_t)2U)

/* Named constants for Chart: '<S99>/UnknownState' */
#define LIBINFO_WL_00_IN_NotUnknown    ((uint8_t)1U)

/* Named constants for Chart: '<S309>/Chart' */
#define LIBINFO_WL_00_IN_Update        ((uint8_t)1U)

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/* Forward declaration for local functions */
static void LIBINFO_WL_00_RunState(BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B,
  D_Work_LIBINFO_WL_00 *LIBINFO_WL_00_DWork);
static boolean_T LIBINFO_WL_00_GroundSpeedExit(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static boolean_T LIBINFO_WL_00_RackExit(BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static boolean_T LIBINFO_WL_00_GroundSpeedRemain(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static boolean_T LIBINF_PayloadDerivativeTrigger(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static boolean_T LIBINFO_WL_0_ExternalForceReset(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static boolean_T LIBINFO_WL_00_PayloadConfirm(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static boolean_T LIBINFO__PayloadDerivativeReset(BlockIO_LIBINFO_WL_00
  *LIBINFO_WL_00_B);
static boolean_T LIBINFO_WL_00_LiftAngleTrigger(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static boolean_T LIBINFO_WL_0_BucketAngleTrigger(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static boolean_T LIBINFO_WL_0_GroundSpeedTrigger(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static boolean_T LIBINFO_WL_00_DecelTrigger(D_Work_LIBINFO_WL_00
  *LIBINFO_WL_00_DWork);
static boolean_T LIBINFO_WL_ExternalForceTrigger(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B, D_Work_LIBINFO_WL_00
  *LIBINFO_WL_00_DWork);
static boolean_T PayloadDerivativeOverrideTrigge(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static void LIBINFO_WL_00_DecLoadedCounter(D_Work_LIBINFO_WL_00
  *LIBINFO_WL_00_DWork);
static void LIBINFO_WL_0_IncUnloadedCounter(BlockIO_LIBINFO_WL_00
  *LIBINFO_WL_00_B, D_Work_LIBINFO_WL_00 *LIBINFO_WL_00_DWork);
static void LIBINFO_WL_00_IncLoadedCounter(BlockIO_LIBINFO_WL_00
  *LIBINFO_WL_00_B, D_Work_LIBINFO_WL_00 *LIBINFO_WL_00_DWork);
static void LIBINFO_WL_0_DecUnloadedCounter(D_Work_LIBINFO_WL_00
  *LIBINFO_WL_00_DWork);
static boolean_T LIBINFO_WL_00_DumpThresholdMet(BlockIO_LIBINFO_WL_00
  *LIBINFO_WL_00_B);
static boolean_T LIBINFO_WL_00_GroundSpeedSlow(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static boolean_T LIBINFO_WL_00_RackThresholdMet(BlockIO_LIBINFO_WL_00
  *LIBINFO_WL_00_B);
static boolean_T LIBINFO_W_OperatorCommandedDump(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static void LIBINFO_WL_00_TryToCommit_lksz(BlockIO_LIBINFO_WL_00
  *LIBINFO_WL_00_B, D_Work_LIBINFO_WL_00 *LIBINFO_WL_00_DWork);
static void LIBINFO_WL_00_Main(BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B,
  D_Work_LIBINFO_WL_00 *LIBINFO_WL_00_DWork);
static void LIBINFO_WL_00_TryToCommit(BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B,
  D_Work_LIBINFO_WL_00 *LIBINFO_WL_00_DWork);
static void LIBINFO_WL_00_findActiveIndex(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static void LIBINFO_WL_00_maskTentatives(RT_MODEL_LIBINFO_WL_00 *LIBINFO_WL_00_M,
  BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static void LIBINFO__commitPreviouslyActive(BlockIO_LIBINFO_WL_00
  *LIBINFO_WL_00_B);
static boolean_T LIBINFO_WL_00_appendActive(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static void LIBINFO_WL_00_purgeInactives(BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static boolean_T LIBINFO_WL_00_isAlreadyInBuffer(int32_t segmentIndexOneBased,
  BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);
static boolean_T LIBINFO_WL_00_addTentatives(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B);

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/

/* Output and update for function-call system: '<S139>/DumpThresholdCapture' */
void LIBINFO_WL_DumpThresholdCapture(dt_libinfo_modulation_pct rtu_0,
  dt_libinfo_modulation_pct rtu_tiltCylExtDelta, dt_libinfo_modulation_pct
  *rty_dumpCylExtCapture, dt_libinfo_modulation_pct *rty_dumpCylExtThreshold)
{
  uint32_t qY;

  /* Inport: '<S142>/tiltCylExt' */
  *rty_dumpCylExtCapture = rtu_0;

  /* Sum: '<S142>/Subtract' */
  qY = ((uint32_t)(*rty_dumpCylExtCapture)) - ((uint32_t)rtu_tiltCylExtDelta);
  if (qY > (*rty_dumpCylExtCapture)) {
    qY = 0U;
  }

  *rty_dumpCylExtThreshold = (dt_libinfo_modulation_pct)((int32_t)qY);

  /* End of Sum: '<S142>/Subtract' */
}

/* Output and update for function-call system: '<S139>/RackThresholdCapture' */
void LIBINFO_WL_RackThresholdCapture(dt_libinfo_modulation_pct rtu_0,
  dt_libinfo_modulation_pct rtu_tiltCylExtDelta, dt_libinfo_modulation_pct
  *rty_rackCylExtCapture, dt_libinfo_modulation_pct *rty_rackCylExtThreshold)
{
  uint32_t tmp;

  /* Inport: '<S143>/tiltCylExt' */
  *rty_rackCylExtCapture = rtu_0;

  /* Sum: '<S143>/Add' */
  tmp = ((uint32_t)(*rty_rackCylExtCapture)) + ((uint32_t)rtu_tiltCylExtDelta);
  if (tmp > 65535U) {
    tmp = 65535U;
  }

  *rty_rackCylExtThreshold = (dt_libinfo_modulation_pct)tmp;

  /* End of Sum: '<S143>/Add' */
}

/*
 * Output and update for action system:
 *    '<S160>/x0_is_min'
 *    '<S171>/x0_is_min'
 */
void LIBINFO_WL_00_x0_is_min(dt_libinfo_MachSpdKPH_Signed rtu_x1,
  dt_libinfo_MachSpdKPH_Signed rtu_x2, dt_libinfo_MachSpdKPH_Signed *rty_out)
{
  /* MinMax: '<S161>/min' */
  if (rtu_x1 <= rtu_x2) {
    *rty_out = rtu_x1;
  } else {
    *rty_out = rtu_x2;
  }

  /* End of MinMax: '<S161>/min' */
}

/*
 * Output and update for action system:
 *    '<S160>/x1_is_min'
 *    '<S171>/x1_is_min'
 */
void LIBINFO_WL_00_x1_is_min(dt_libinfo_MachSpdKPH_Signed rtu_x0,
  dt_libinfo_MachSpdKPH_Signed rtu_x2, dt_libinfo_MachSpdKPH_Signed *rty_out)
{
  /* MinMax: '<S162>/min' */
  if (rtu_x0 <= rtu_x2) {
    *rty_out = rtu_x0;
  } else {
    *rty_out = rtu_x2;
  }

  /* End of MinMax: '<S162>/min' */
}

/*
 * Output and update for action system:
 *    '<S160>/x2_is_min'
 *    '<S171>/x2_is_min'
 */
void LIBINFO_WL_00_x2_is_min(dt_libinfo_MachSpdKPH_Signed rtu_x0,
  dt_libinfo_MachSpdKPH_Signed rtu_x1, dt_libinfo_MachSpdKPH_Signed *rty_out)
{
  /* MinMax: '<S163>/min' */
  if (rtu_x0 <= rtu_x1) {
    *rty_out = rtu_x0;
  } else {
    *rty_out = rtu_x1;
  }

  /* End of MinMax: '<S163>/min' */
}

/*
 * Output and update for enable system:
 *    '<S269>/Bounded Selection'
 *    '<S263>/Bounded Selection'
 *    '<S260>/Bounded Selection'
 *    '<S218>/Bounded Selection'
 */
void LIBINFO_WL_00_BoundedSelection(boolean_T rtu_0, const dt_libinfo_Unsigned8
  rtu_vector[7], int32_t rtu_indexOneBased, dt_libinfo_Unsigned8 *rty_value)
{
  /* Outputs for Enabled SubSystem: '<S269>/Bounded Selection' incorporates:
   *  EnablePort: '<S270>/Enable'
   */
  if (rtu_0) {
    /* Selector: '<S270>/Selector' */
    *rty_value = rtu_vector[rtu_indexOneBased - 1];
  }

  /* End of Outputs for SubSystem: '<S269>/Bounded Selection' */
}

/*
 * Output and update for function-call system:
 *    '<S219>/AppendFunc'
 *    '<S235>/AppendFunc'
 *    '<S400>/AppendFunc'
 */
void LIBINFO_WL_00_AppendFunc(const real32_T rtu_inAccumulatorBuffer[10],
  int32_t rtu_bufferDepth, real32_T rty_outAccumulatorBuffer[10])
{
  /* local block i/o variables */
  real32_T rtb_TmpLatchAtinAccumulato_bcj2[10];
  int32_t i;
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S220>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumulato_bcj2[i] = rtu_inAccumulatorBuffer[i];

    /* Assignment: '<S220>/Assignment' */
    rty_outAccumulatorBuffer[i] = rtb_TmpLatchAtinAccumulato_bcj2[i];
  }

  /* Assignment: '<S220>/Assignment' incorporates:
   *  Bias: '<S220>/Bias'
   *  Constant: '<S220>/Constant'
   */
  rty_outAccumulatorBuffer[rtu_bufferDepth] = 0.0F;
}

/*
 * Output and update for function-call system:
 *    '<S468>/AppendFunc'
 *    '<S416>/AppendFunc'
 */
void LIBINFO_WL_00_AppendFunc_ddqd(const dt_libinfo_Unsigned32
  rtu_inAccumulatorBuffer[10], int32_t rtu_bufferDepth, dt_libinfo_Unsigned32
  rtu_parameter, dt_libinfo_Unsigned32 rty_outAccumulatorBuffer[10])
{
  /* local block i/o variables */
  dt_libinfo_Unsigned32 rtb_TmpLatchAtinAccumulato_hky2[10];
  int32_t i;
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S469>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumulato_hky2[i] = rtu_inAccumulatorBuffer[i];

    /* Assignment: '<S469>/Assignment' */
    rty_outAccumulatorBuffer[i] = rtb_TmpLatchAtinAccumulato_hky2[i];
  }

  /* Assignment: '<S469>/Assignment' incorporates:
   *  Bias: '<S469>/Bias'
   */
  rty_outAccumulatorBuffer[rtu_bufferDepth] = rtu_parameter;
}

/* Output and update for function-call system: '<S349>/FuncCallSplit4' */
void LIBINFO_WL_00_FuncCallSplit4(const int32_t rtu_0[10], int32_t rtu_1,
  int32_t rtu_2, const dt_libinfo_Time20msLong rtu_3[10], const
  dt_libinfo_Time20msLong rtu_4[10], const dt_libinfo_gps_latitude rtu_5[10],
  dt_libinfo_gps_latitude rtu_6, const dt_libinfo_Ratio_Unsigned32 rtu_7[10],
  dt_libinfo_Ratio_Unsigned32 rtu_8, const dt_libinfo_single rtu_9[10], const
  dt_libinfo_Flag_u16 rtu_10[10], const real32_T rtu_11[10], const
  dt_libinfo_Unsigned32 rtu_12[10], dt_libinfo_Unsigned32 rtu_13, const real32_T
  rtu_14[10], const real32_T rtu_15[10], const dt_libinfo_Unsigned32 rtu_16[10],
  dt_libinfo_Unsigned32 rtu_17, int32_t rty_0[10], dt_libinfo_Time20msLong
  rty_1[10], dt_libinfo_Time20msLong rty_2[10], dt_libinfo_gps_latitude rty_3[10],
  dt_libinfo_Ratio_Unsigned32 rty_4[10], dt_libinfo_single rty_5[10],
  dt_libinfo_Flag_u16 rty_6[10], real32_T rty_7[10], dt_libinfo_Unsigned32
  rty_8[10], real32_T rty_9[10], real32_T rty_10[10], dt_libinfo_Unsigned32
  rty_11[10], RT_MODEL_LIBINFO_WL_00 * const LIBINFO_WL_00_M)
{
  /* local block i/o variables */
  dt_libinfo_single rtb_TmpLatchAtinParamBufferOutp[10];
  int32_t rtb_TmpLatchAtinIndexBuffe_ispy[10];
  dt_libinfo_gps_latitude rtb_TmpLatchAtinAccumulatorBuff[10];
  dt_libinfo_Ratio_Unsigned32 rtb_TmpLatchAtinAccumulato_edhm[10];
  dt_libinfo_Time20msLong rtb_TmpLatchAtinAccumulato_ofwt[10];
  dt_libinfo_Time20msLong rtb_TmpLatchAtinAccumulato_hpld[10];
  dt_libinfo_Flag_u16 rtb_TmpLatchAtinParamConfBuffer[10];
  int32_t i;

  /* S-Function (fcncallgen): '<S367>/Function-Call Generator' incorporates:
   *  SubSystem: '<S348>/AppendFunc'
   */
  /* S-Function (fcncallgen): '<S367>/Function-Call Generator' incorporates:
   *  SubSystem: '<S307>/FuncCallSplit4'
   */
  /* S-Function (fcncallgen): '<S342>/Function-Call Generator' incorporates:
   *  SubSystem: '<S305>/AppendFunc'
   */
  /* S-Function (fcncallgen): '<S342>/Function-Call Generator' incorporates:
   *  SubSystem: '<S308>/FuncCallSplit4'
   */
  /* S-Function (fcncallgen): '<S346>/Function-Call Generator' incorporates:
   *  SubSystem: '<S306>/AppendFunc'
   */
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S350>/TmpLatchAtinIndexBufferOutport1' */
    rtb_TmpLatchAtinIndexBuffe_ispy[i] = rtu_0[i];

    /* Assignment: '<S350>/Assignment' */
    rty_0[i] = rtb_TmpLatchAtinIndexBuffe_ispy[i];

    /* SignalConversion: '<S311>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumulato_hpld[i] = rtu_3[i];

    /* Assignment: '<S311>/Assignment' */
    rty_1[i] = rtb_TmpLatchAtinAccumulato_hpld[i];

    /* SignalConversion: '<S325>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumulato_ofwt[i] = rtu_4[i];

    /* Assignment: '<S325>/Assignment' */
    rty_2[i] = rtb_TmpLatchAtinAccumulato_ofwt[i];
  }

  /* Assignment: '<S350>/Assignment' incorporates:
   *  Bias: '<S350>/Bias'
   */
  rty_0[rtu_1] = rtu_2;

  /* S-Function (fcncallgen): '<S367>/Function-Call Generator' incorporates:
   *  SubSystem: '<S307>/FuncCallSplit4'
   */
  /* S-Function (fcncallgen): '<S342>/Function-Call Generator' incorporates:
   *  SubSystem: '<S305>/AppendFunc'
   */
  /* Assignment: '<S311>/Assignment' incorporates:
   *  Bias: '<S311>/Bias'
   *  Constant: '<S311>/Constant'
   */
  rty_1[rtu_1] = 0U;

  /* S-Function (fcncallgen): '<S342>/Function-Call Generator' incorporates:
   *  SubSystem: '<S308>/FuncCallSplit4'
   */
  /* S-Function (fcncallgen): '<S346>/Function-Call Generator' incorporates:
   *  SubSystem: '<S306>/AppendFunc'
   */
  /* Assignment: '<S325>/Assignment' incorporates:
   *  Bias: '<S325>/Bias'
   *  Constant: '<S325>/Constant'
   */
  rty_2[rtu_1] =
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_Totalizer_00_calcompfix_mi_ROM_p->ST_TotSlave_Maxvalue;

  /* S-Function (fcncallgen): '<S346>/Function-Call Generator' incorporates:
   *  SubSystem: '<S211>/FuncCallSplit4'
   */
  /* S-Function (fcncallgen): '<S391>/Function-Call Generator' incorporates:
   *  SubSystem: '<S219>/AppendFunc'
   */
  LIBINFO_WL_00_AppendFunc(rtu_11, rtu_1, rty_7);

  /* S-Function (fcncallgen): '<S391>/Function-Call Generator' incorporates:
   *  SubSystem: '<S207>/FuncCallSplit4'
   */
  /* S-Function (fcncallgen): '<S375>/Function-Call Generator' incorporates:
   *  SubSystem: '<S468>/AppendFunc'
   */
  LIBINFO_WL_00_AppendFunc_ddqd(rtu_12, rtu_1, rtu_13, rty_8);

  /* S-Function (fcncallgen): '<S375>/Function-Call Generator' incorporates:
   *  SubSystem: '<S208>/FuncCallSplit4'
   */
  /* S-Function (fcncallgen): '<S379>/Function-Call Generator' incorporates:
   *  SubSystem: '<S235>/AppendFunc'
   */
  LIBINFO_WL_00_AppendFunc(rtu_14, rtu_1, rty_9);

  /* S-Function (fcncallgen): '<S379>/Function-Call Generator' incorporates:
   *  SubSystem: '<S209>/FuncCallSplit4'
   */
  /* S-Function (fcncallgen): '<S383>/Function-Call Generator' incorporates:
   *  SubSystem: '<S434>/FuncCallSplit4'
   */
  /* S-Function (fcncallgen): '<S466>/Function-Call Generator' incorporates:
   *  SubSystem: '<S432>/AppendFunc'
   */
  /* S-Function (fcncallgen): '<S466>/Function-Call Generator' incorporates:
   *  SubSystem: '<S433>/AppendFunc'
   */
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S435>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumulatorBuff[i] = rtu_5[i];

    /* Assignment: '<S435>/Assignment' */
    rty_3[i] = rtb_TmpLatchAtinAccumulatorBuff[i];

    /* SignalConversion: '<S449>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumulato_edhm[i] = rtu_7[i];

    /* Assignment: '<S449>/Assignment' */
    rty_4[i] = rtb_TmpLatchAtinAccumulato_edhm[i];
  }

  /* Assignment: '<S435>/Assignment' incorporates:
   *  Bias: '<S435>/Bias'
   */
  rty_3[rtu_1] = rtu_6;

  /* S-Function (fcncallgen): '<S466>/Function-Call Generator' incorporates:
   *  SubSystem: '<S433>/AppendFunc'
   */
  /* Assignment: '<S449>/Assignment' incorporates:
   *  Bias: '<S449>/Bias'
   */
  rty_4[rtu_1] = rtu_8;

  /* S-Function (fcncallgen): '<S383>/Function-Call Generator' incorporates:
   *  SubSystem: '<S210>/FuncCallSplit4'
   */
  /* S-Function (fcncallgen): '<S387>/Function-Call Generator' incorporates:
   *  SubSystem: '<S400>/AppendFunc'
   */
  LIBINFO_WL_00_AppendFunc(rtu_15, rtu_1, rty_10);

  /* S-Function (fcncallgen): '<S387>/Function-Call Generator' incorporates:
   *  SubSystem: '<S212>/FuncCallSplit4'
   */
  /* S-Function (fcncallgen): '<S395>/Function-Call Generator' incorporates:
   *  SubSystem: '<S416>/AppendFunc'
   */
  LIBINFO_WL_00_AppendFunc_ddqd(rtu_16, rtu_1, rtu_17, rty_11);

  /* S-Function (fcncallgen): '<S395>/Function-Call Generator' incorporates:
   *  SubSystem: '<S213>/FuncCallSplit4'
   */
  /* S-Function (fcncallgen): '<S399>/Function-Call Generator' incorporates:
   *  SubSystem: '<S275>/AppendFunc'
   */
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S276>/TmpLatchAtinParamBufferOutport1' */
    rtb_TmpLatchAtinParamBufferOutp[i] = rtu_9[i];

    /* SignalConversion: '<S276>/TmpLatchAtinParamConfBufferOutport1' */
    rtb_TmpLatchAtinParamConfBuffer[i] = rtu_10[i];

    /* Assignment: '<S276>/Assignment' */
    rty_5[i] = rtb_TmpLatchAtinParamBufferOutp[i];

    /* Assignment: '<S276>/Assignment1' */
    rty_6[i] = rtb_TmpLatchAtinParamConfBuffer[i];
  }

  /* Assignment: '<S276>/Assignment' incorporates:
   *  Bias: '<S276>/Bias'
   *  Constant: '<S276>/Constant'
   *  DataTypeConversion: '<S276>/Data Type Conversion'
   */
  rty_5[rtu_1] = (dt_libinfo_single)R2012b_rtNan;

  /* Assignment: '<S276>/Assignment1' incorporates:
   *  Bias: '<S276>/Bias'
   *  Constant: '<S276>/Constant1'
   */
  rty_6[rtu_1] = 0U;
}

/*
 * Output and update for function-call system:
 *    '<S219>/UpdateFunc'
 *    '<S235>/UpdateFunc'
 *    '<S400>/UpdateFunc'
 */
void LIBINFO_WL_00_UpdateFunc(const real32_T rtu_inAccumulatorBuffer[10],
  int32_t rtu_bufferDepth, real32_T rtu_parameter, real32_T
  rty_outAccumulatorBuffer[10])
{
  /* local block i/o variables */
  real32_T rtb_TmpLatchAtinAccumulat_bcj2j[10];
  int32_t i;
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S223>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumulat_bcj2j[i] = rtu_inAccumulatorBuffer[i];

    /* Assignment: '<S223>/Assignment' */
    rty_outAccumulatorBuffer[i] = rtb_TmpLatchAtinAccumulat_bcj2j[i];
  }

  /* Assignment: '<S223>/Assignment' incorporates:
   *  Selector: '<S223>/Selector'
   *  Sum: '<S223>/Add'
   */
  rty_outAccumulatorBuffer[rtu_bufferDepth - 1] =
    rtb_TmpLatchAtinAccumulat_bcj2j[rtu_bufferDepth - 1] + rtu_parameter;
}

/*
 * Output and update for function-call system:
 *    '<S468>/UpdateFunc'
 *    '<S416>/UpdateFunc'
 */
void LIBINFO_WL_00_UpdateFunc_lydr(const dt_libinfo_Unsigned32
  rtu_inAccumulatorBuffer[10], dt_libinfo_Unsigned32 rty_outAccumulatorBuffer[10])
{
  /* local block i/o variables */
  dt_libinfo_Unsigned32 rtb_TmpLatchAtinAccumulat_hky24[10];
  int32_t i;
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S473>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumulat_hky24[i] = rtu_inAccumulatorBuffer[i];

    /* SignalConversion: '<S473>/Signal Conversion' */
    rty_outAccumulatorBuffer[i] = rtb_TmpLatchAtinAccumulat_hky24[i];
  }
}

/* Output and update for function-call system: '<S349>/FuncCallSplit1' */
void LIBINFO_WL_00_FuncCallSplit1(const int32_t rtu_0[10], const
  dt_libinfo_Time20msLong rtu_1[10], int32_t rtu_2, dt_libinfo_Time20msLong
  rtu_3, const dt_libinfo_Time20msLong rtu_4[10], dt_libinfo_Time20msLong rtu_5,
  const dt_libinfo_gps_latitude rtu_6[10], const dt_libinfo_Ratio_Unsigned32
  rtu_7[10], const dt_libinfo_single rtu_8[10], const dt_libinfo_Flag_u16 rtu_9
  [10], dt_libinfo_Flag_u16 rtu_10, dt_libinfo_single rtu_11, const real32_T
  rtu_12[10], real32_T rtu_13, const dt_libinfo_Unsigned32 rtu_14[10], const
  real32_T rtu_15[10], real32_T rtu_16, const real32_T rtu_17[10], real32_T
  rtu_18, const dt_libinfo_Unsigned32 rtu_19[10], int32_t rty_0[10],
  dt_libinfo_Time20msLong rty_1[10], dt_libinfo_Time20msLong rty_2[10],
  dt_libinfo_gps_latitude rty_3[10], dt_libinfo_Ratio_Unsigned32 rty_4[10],
  dt_libinfo_single rty_5[10], dt_libinfo_Flag_u16 rty_6[10], real32_T rty_7[10],
  dt_libinfo_Unsigned32 rty_8[10], real32_T rty_9[10], real32_T rty_10[10],
  dt_libinfo_Unsigned32 rty_11[10])
{
  /* local block i/o variables */
  dt_libinfo_single rtb_TmpLatchAtinParamBuffe_k5vi[10];
  int32_t rtb_TmpLatchAtinIndexBuff_ispy3[10];
  dt_libinfo_gps_latitude rtb_TmpLatchAtinAccumulato_pdov[10];
  dt_libinfo_Ratio_Unsigned32 rtb_TmpLatchAtinAccumulat_edhmi[10];
  dt_libinfo_Time20msLong rtb_TmpLatchAtinAccumulat_ofwtm[10];
  dt_libinfo_Time20msLong rtb_TmpLatchAtinAccumulat_hpldf[10];
  dt_libinfo_Flag_u16 rtb_TmpLatchAtinParamConfB_odkg[10];
  uint16_t rtb_ShiftArithmetic;
  boolean_T rtb_LogicalOperator_jvb3;
  int32_t i;
  uint64_T tmp;

  /* S-Function (fcncallgen): '<S364>/Function-Call Generator' incorporates:
   *  SubSystem: '<S348>/UpdateFunc'
   */
  /* S-Function (fcncallgen): '<S364>/Function-Call Generator' incorporates:
   *  SubSystem: '<S307>/FuncCallSplit1'
   */
  /* S-Function (fcncallgen): '<S339>/Function-Call Generator' incorporates:
   *  SubSystem: '<S305>/UpdateFunc'
   */
  /* S-Function (fcncallgen): '<S339>/Function-Call Generator' incorporates:
   *  SubSystem: '<S308>/FuncCallSplit1'
   */
  /* S-Function (fcncallgen): '<S343>/Function-Call Generator' incorporates:
   *  SubSystem: '<S306>/UpdateFunc'
   */
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S353>/TmpLatchAtinIndexBufferOutport1' */
    rtb_TmpLatchAtinIndexBuff_ispy3[i] = rtu_0[i];

    /* SignalConversion: '<S353>/Signal Conversion' */
    rty_0[i] = rtb_TmpLatchAtinIndexBuff_ispy3[i];

    /* SignalConversion: '<S314>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumulat_hpldf[i] = rtu_1[i];

    /* Assignment: '<S314>/Assignment' */
    rty_1[i] = rtb_TmpLatchAtinAccumulat_hpldf[i];

    /* SignalConversion: '<S328>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumulat_ofwtm[i] = rtu_4[i];

    /* Assignment: '<S328>/Assignment' */
    rty_2[i] = rtb_TmpLatchAtinAccumulat_ofwtm[i];
  }

  /* Sum: '<S314>/Add' incorporates:
   *  Selector: '<S314>/Selector'
   */
  tmp = ((uint64_T)rtb_TmpLatchAtinAccumulat_hpldf[rtu_2 - 1]) + ((uint64_T)
    rtu_3);
  if (tmp > 4294967295UL) {
    tmp = 4294967295UL;
  }

  /* Assignment: '<S314>/Assignment' incorporates:
   *  Sum: '<S314>/Add'
   */
  rty_1[rtu_2 - 1] = (uint32_t)tmp;

  /* S-Function (fcncallgen): '<S339>/Function-Call Generator' incorporates:
   *  SubSystem: '<S308>/FuncCallSplit1'
   */
  /* S-Function (fcncallgen): '<S343>/Function-Call Generator' incorporates:
   *  SubSystem: '<S306>/UpdateFunc'
   */
  /* MinMax: '<S328>/Min' incorporates:
   *  Selector: '<S328>/Selector'
   */
  if (rtu_5 <= rtb_TmpLatchAtinAccumulat_ofwtm[rtu_2 - 1]) {
    /* Assignment: '<S328>/Assignment' */
    rty_2[rtu_2 - 1] = rtu_5;
  } else {
    /* Assignment: '<S328>/Assignment' */
    rty_2[rtu_2 - 1] = rtb_TmpLatchAtinAccumulat_ofwtm[rtu_2 - 1];
  }

  /* End of MinMax: '<S328>/Min' */

  /* S-Function (fcncallgen): '<S343>/Function-Call Generator' incorporates:
   *  SubSystem: '<S211>/FuncCallSplit1'
   */
  /* S-Function (fcncallgen): '<S388>/Function-Call Generator' incorporates:
   *  SubSystem: '<S219>/UpdateFunc'
   */
  LIBINFO_WL_00_UpdateFunc(rtu_12, rtu_2, rtu_13, rty_7);

  /* S-Function (fcncallgen): '<S388>/Function-Call Generator' incorporates:
   *  SubSystem: '<S207>/FuncCallSplit1'
   */
  /* S-Function (fcncallgen): '<S372>/Function-Call Generator' incorporates:
   *  SubSystem: '<S468>/UpdateFunc'
   */
  LIBINFO_WL_00_UpdateFunc_lydr(rtu_14, rty_8);

  /* S-Function (fcncallgen): '<S372>/Function-Call Generator' incorporates:
   *  SubSystem: '<S208>/FuncCallSplit1'
   */
  /* S-Function (fcncallgen): '<S376>/Function-Call Generator' incorporates:
   *  SubSystem: '<S235>/UpdateFunc'
   */
  LIBINFO_WL_00_UpdateFunc(rtu_15, rtu_2, rtu_16, rty_9);

  /* S-Function (fcncallgen): '<S376>/Function-Call Generator' incorporates:
   *  SubSystem: '<S209>/FuncCallSplit1'
   */
  /* S-Function (fcncallgen): '<S380>/Function-Call Generator' incorporates:
   *  SubSystem: '<S434>/FuncCallSplit1'
   */
  /* S-Function (fcncallgen): '<S463>/Function-Call Generator' incorporates:
   *  SubSystem: '<S432>/UpdateFunc'
   */
  /* S-Function (fcncallgen): '<S463>/Function-Call Generator' incorporates:
   *  SubSystem: '<S433>/UpdateFunc'
   */
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S438>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumulato_pdov[i] = rtu_6[i];

    /* SignalConversion: '<S438>/Signal Conversion' */
    rty_3[i] = rtb_TmpLatchAtinAccumulato_pdov[i];

    /* SignalConversion: '<S452>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumulat_edhmi[i] = rtu_7[i];

    /* SignalConversion: '<S452>/Signal Conversion' */
    rty_4[i] = rtb_TmpLatchAtinAccumulat_edhmi[i];
  }

  /* S-Function (fcncallgen): '<S380>/Function-Call Generator' incorporates:
   *  SubSystem: '<S210>/FuncCallSplit1'
   */
  /* S-Function (fcncallgen): '<S384>/Function-Call Generator' incorporates:
   *  SubSystem: '<S400>/UpdateFunc'
   */
  LIBINFO_WL_00_UpdateFunc(rtu_17, rtu_2, rtu_18, rty_10);

  /* S-Function (fcncallgen): '<S384>/Function-Call Generator' incorporates:
   *  SubSystem: '<S212>/FuncCallSplit1'
   */
  /* S-Function (fcncallgen): '<S392>/Function-Call Generator' incorporates:
   *  SubSystem: '<S416>/UpdateFunc'
   */
  LIBINFO_WL_00_UpdateFunc_lydr(rtu_19, rty_11);

  /* S-Function (fcncallgen): '<S392>/Function-Call Generator' incorporates:
   *  SubSystem: '<S213>/FuncCallSplit1'
   */
  /* S-Function (fcncallgen): '<S396>/Function-Call Generator' incorporates:
   *  SubSystem: '<S275>/UpdateFunc'
   */
  /* ArithShift: '<S280>/Shift Arithmetic' incorporates:
   *  S-Function (sfix_bitop): '<S280>/Bitwise Operator'
   */
  rtb_ShiftArithmetic = (uint16_t)((rtu_10 & 3840) >> 8);
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S280>/TmpLatchAtinParamBufferOutport1' */
    rtb_TmpLatchAtinParamBuffe_k5vi[i] = rtu_8[i];

    /* SignalConversion: '<S280>/TmpLatchAtinParamConfBufferOutport1' */
    rtb_TmpLatchAtinParamConfB_odkg[i] = rtu_9[i];

    /* Assignment: '<S280>/Assignment' */
    rty_5[i] = rtb_TmpLatchAtinParamBuffe_k5vi[i];

    /* Assignment: '<S280>/Assignment1' */
    rty_6[i] = rtb_TmpLatchAtinParamConfB_odkg[i];
  }

  /* Logic: '<S280>/Logical Operator' incorporates:
   *  ArithShift: '<S280>/Shift Arithmetic1'
   *  Constant: '<S301>/Constant'
   *  RelationalOperator: '<S280>/Relational Operator'
   *  RelationalOperator: '<S301>/Compare'
   *  S-Function (sfix_bitop): '<S280>/Bitwise Operator1'
   *  Selector: '<S280>/Selector'
   */
  rtb_LogicalOperator_jvb3 = ((rtb_ShiftArithmetic > 0) && (rtb_ShiftArithmetic >=
                               ((rtb_TmpLatchAtinParamConfB_odkg[rtu_2 - 1] &
    3840) >> 8)));

  /* Switch: '<S280>/Switch1' incorporates:
   *  Switch: '<S280>/Switch'
   */
  if (rtb_LogicalOperator_jvb3) {
    /* Assignment: '<S280>/Assignment' */
    rty_5[rtu_2 - 1] = rtu_11;

    /* Assignment: '<S280>/Assignment1' */
    rty_6[rtu_2 - 1] = rtu_10;
  } else {
    /* Assignment: '<S280>/Assignment' incorporates:
     *  Selector: '<S280>/Selector1'
     */
    rty_5[rtu_2 - 1] = rtb_TmpLatchAtinParamBuffe_k5vi[rtu_2 - 1];

    /* Assignment: '<S280>/Assignment1' incorporates:
     *  Selector: '<S280>/Selector'
     */
    rty_6[rtu_2 - 1] = rtb_TmpLatchAtinParamConfB_odkg[rtu_2 - 1];
  }

  /* End of Switch: '<S280>/Switch1' */
}

/*
 * Output and update for action system:
 *    '<S359>/DoShift'
 *    '<S354>/DoShift'
 */
void LIBINFO_WL_00_DoShift(int32_t rtu_bufferDepth, int32_t
  rtu_indexToShiftBackOneBased, const int32_t rtu_inBuffer[10], int32_t
  rty_outBuffer[10])
{
  int32_t rtb_PlusOne;
  int32_t s363_iter;
  int32_t rtb_Sum_lie4;
  int32_t i;

  /* Bias: '<S362>/PlusOne' incorporates:
   *  Sum: '<S362>/Sum1'
   */
  rtb_PlusOne = rtu_bufferDepth - rtu_indexToShiftBackOneBased;

  /* Outputs for Iterator SubSystem: '<S362>/ShiftBackOne' incorporates:
   *  ForIterator: '<S363>/For Iterator'
   */
  /* Bias: '<S362>/PlusOne' */
  for (s363_iter = 0; s363_iter < (rtb_PlusOne + 1); s363_iter++) {
    /* Sum: '<S363>/Sum' incorporates:
     *  Assignment: '<S363>/Assignment'
     *  Bias: '<S363>/BackOne'
     *  Selector: '<S363>/Selector'
     */
    rtb_Sum_lie4 = (s363_iter + rtu_indexToShiftBackOneBased) - 2;

    /* Assignment: '<S363>/Assignment' incorporates:
     *  Bias: '<S363>/BackOne'
     *  Selector: '<S363>/Selector'
     */
    if (s363_iter == 0) {
      for (i = 0; i < 10; i++) {
        rty_outBuffer[i] = rtu_inBuffer[i];
      }
    }

    rty_outBuffer[rtb_Sum_lie4] = rtu_inBuffer[rtb_Sum_lie4 + 1];
  }

  /* End of Outputs for SubSystem: '<S362>/ShiftBackOne' */
}

/*
 * Output and update for action system:
 *    '<S359>/DoNothing'
 *    '<S354>/DoNothing'
 */
void LIBINFO_WL_00_DoNothing(const int32_t rtu_0[10], int32_t rty_outBuffer[10])
{
  int32_t i;

  /* Inport: '<S361>/inBuffer' */
  for (i = 0; i < 10; i++) {
    rty_outBuffer[i] = rtu_0[i];
  }

  /* End of Inport: '<S361>/inBuffer' */
}

/*
 * Output and update for action system:
 *    '<S320>/DoShift'
 *    '<S334>/DoShift'
 *    '<S315>/DoShift'
 *    '<S329>/DoShift'
 */
void LIBINFO_WL_00_DoShift_kcfw(int32_t rtu_bufferDepth, int32_t
  rtu_indexToShiftBackOneBased, const dt_libinfo_Time20msLong rtu_inBuffer[10],
  dt_libinfo_Time20msLong rty_outBuffer[10])
{
  int32_t rtb_PlusOne_bref;
  int32_t s324_iter;
  int32_t rtb_Sum_eijo;
  int32_t i;

  /* Bias: '<S323>/PlusOne' incorporates:
   *  Sum: '<S323>/Sum1'
   */
  rtb_PlusOne_bref = rtu_bufferDepth - rtu_indexToShiftBackOneBased;

  /* Outputs for Iterator SubSystem: '<S323>/ShiftBackOne' incorporates:
   *  ForIterator: '<S324>/For Iterator'
   */
  /* Bias: '<S323>/PlusOne' */
  for (s324_iter = 0; s324_iter < (rtb_PlusOne_bref + 1); s324_iter++) {
    /* Sum: '<S324>/Sum' incorporates:
     *  Assignment: '<S324>/Assignment'
     *  Bias: '<S324>/BackOne'
     *  Selector: '<S324>/Selector'
     */
    rtb_Sum_eijo = (s324_iter + rtu_indexToShiftBackOneBased) - 2;

    /* Assignment: '<S324>/Assignment' incorporates:
     *  Bias: '<S324>/BackOne'
     *  Selector: '<S324>/Selector'
     */
    if (s324_iter == 0) {
      for (i = 0; i < 10; i++) {
        rty_outBuffer[i] = rtu_inBuffer[i];
      }
    }

    rty_outBuffer[rtb_Sum_eijo] = rtu_inBuffer[rtb_Sum_eijo + 1];
  }

  /* End of Outputs for SubSystem: '<S323>/ShiftBackOne' */
}

/*
 * Output and update for action system:
 *    '<S320>/DoNothing'
 *    '<S334>/DoNothing'
 *    '<S315>/DoNothing'
 *    '<S329>/DoNothing'
 */
void LIBINFO_WL_00_DoNothing_aohe(const dt_libinfo_Time20msLong rtu_0[10],
  dt_libinfo_Time20msLong rty_outBuffer[10])
{
  int32_t i;

  /* Inport: '<S322>/inBuffer' */
  for (i = 0; i < 10; i++) {
    rty_outBuffer[i] = rtu_0[i];
  }

  /* End of Inport: '<S322>/inBuffer' */
}

/*
 * Output and update for atomic system:
 *    '<S313>/ShiftBufferBack'
 *    '<S327>/ShiftBufferBack1'
 */
void LIBINFO_WL_00_ShiftBufferBack(int32_t rtu_indexToShiftBackOneBased, const
  dt_libinfo_Time20msLong rtu_inBuffer[10], int32_t rtu_bufferDepth,
  dt_libinfo_Time20msLong rty_outBuffer[10], rtC_ShiftBufferBack_LIBINFO_WL_
  *localC)
{
  /* local block i/o variables */
  int32_t rtb_Min_as5y;

  /* MinMax: '<S320>/Min' */
  if (rtu_bufferDepth <= localC->Width) {
    rtb_Min_as5y = rtu_bufferDepth;
  } else {
    rtb_Min_as5y = localC->Width;
  }

  /* End of MinMax: '<S320>/Min' */

  /* If: '<S320>/If' incorporates:
   *  Constant: '<S321>/Constant'
   *  Logic: '<S320>/Logical Operator'
   *  RelationalOperator: '<S320>/Relational Operator'
   *  RelationalOperator: '<S321>/Compare'
   */
  if ((rtu_indexToShiftBackOneBased > 1) && (rtu_indexToShiftBackOneBased <=
       rtb_Min_as5y)) {
    /* Outputs for IfAction SubSystem: '<S320>/DoShift' incorporates:
     *  ActionPort: '<S323>/Action Port'
     */
    LIBINFO_WL_00_DoShift_kcfw(rtb_Min_as5y, rtu_indexToShiftBackOneBased,
      rtu_inBuffer, rty_outBuffer);

    /* End of Outputs for SubSystem: '<S320>/DoShift' */
  } else {
    /* Outputs for IfAction SubSystem: '<S320>/DoNothing' incorporates:
     *  ActionPort: '<S322>/Action Port'
     */
    LIBINFO_WL_00_DoNothing_aohe(rtu_inBuffer, rty_outBuffer);

    /* End of Outputs for SubSystem: '<S320>/DoNothing' */
  }

  /* End of If: '<S320>/If' */
}

/*
 * Output and update for action system:
 *    '<S229>/DoShift'
 *    '<S245>/DoShift'
 *    '<S410>/DoShift'
 *    '<S291>/DoShift'
 *    '<S224>/DoShift'
 *    '<S240>/DoShift'
 *    '<S405>/DoShift'
 *    '<S281>/DoShift'
 */
void LIBINFO_WL_00_DoShift_bx2h(int32_t rtu_bufferDepth, int32_t
  rtu_indexToShiftBackOneBased, const real32_T rtu_inBuffer[10], real32_T
  rty_outBuffer[10])
{
  int32_t rtb_PlusOne_f3w4;
  int32_t s233_iter;
  int32_t rtb_Sum_flga;
  int32_t i;

  /* Bias: '<S232>/PlusOne' incorporates:
   *  Sum: '<S232>/Sum1'
   */
  rtb_PlusOne_f3w4 = rtu_bufferDepth - rtu_indexToShiftBackOneBased;

  /* Outputs for Iterator SubSystem: '<S232>/ShiftBackOne' incorporates:
   *  ForIterator: '<S233>/For Iterator'
   */
  /* Bias: '<S232>/PlusOne' */
  for (s233_iter = 0; s233_iter < (rtb_PlusOne_f3w4 + 1); s233_iter++) {
    /* Sum: '<S233>/Sum' incorporates:
     *  Assignment: '<S233>/Assignment'
     *  Bias: '<S233>/BackOne'
     *  Selector: '<S233>/Selector'
     */
    rtb_Sum_flga = (s233_iter + rtu_indexToShiftBackOneBased) - 2;

    /* Assignment: '<S233>/Assignment' incorporates:
     *  Bias: '<S233>/BackOne'
     *  Selector: '<S233>/Selector'
     */
    if (s233_iter == 0) {
      for (i = 0; i < 10; i++) {
        rty_outBuffer[i] = rtu_inBuffer[i];
      }
    }

    rty_outBuffer[rtb_Sum_flga] = rtu_inBuffer[rtb_Sum_flga + 1];
  }

  /* End of Outputs for SubSystem: '<S232>/ShiftBackOne' */
}

/*
 * Output and update for action system:
 *    '<S229>/DoNothing'
 *    '<S245>/DoNothing'
 *    '<S410>/DoNothing'
 *    '<S291>/DoNothing'
 *    '<S224>/DoNothing'
 *    '<S240>/DoNothing'
 *    '<S405>/DoNothing'
 *    '<S281>/DoNothing'
 */
void LIBINFO_WL_00_DoNothing_n0wb(const real32_T rtu_0[10], real32_T
  rty_outBuffer[10])
{
  int32_t i;

  /* Inport: '<S231>/inBuffer' */
  for (i = 0; i < 10; i++) {
    rty_outBuffer[i] = rtu_0[i];
  }

  /* End of Inport: '<S231>/inBuffer' */
}

/*
 * Output and update for atomic system:
 *    '<S222>/ShiftBufferBack'
 *    '<S238>/ShiftBufferBack'
 *    '<S403>/ShiftBufferBack'
 *    '<S279>/ShiftBufferBack'
 */
void LIBINFO_WL_ShiftBufferBack_afxg(int32_t rtu_indexToShiftBackOneBased, const
  real32_T rtu_inBuffer[10], int32_t rtu_bufferDepth, real32_T rty_outBuffer[10],
  rtC_ShiftBufferBack_LIBINF_pzts *localC)
{
  /* local block i/o variables */
  int32_t rtb_Min_j1e2;

  /* MinMax: '<S229>/Min' */
  if (rtu_bufferDepth <= localC->Width) {
    rtb_Min_j1e2 = rtu_bufferDepth;
  } else {
    rtb_Min_j1e2 = localC->Width;
  }

  /* End of MinMax: '<S229>/Min' */

  /* If: '<S229>/If' incorporates:
   *  Constant: '<S230>/Constant'
   *  Logic: '<S229>/Logical Operator'
   *  RelationalOperator: '<S229>/Relational Operator'
   *  RelationalOperator: '<S230>/Compare'
   */
  if ((rtu_indexToShiftBackOneBased > 1) && (rtu_indexToShiftBackOneBased <=
       rtb_Min_j1e2)) {
    /* Outputs for IfAction SubSystem: '<S229>/DoShift' incorporates:
     *  ActionPort: '<S232>/Action Port'
     */
    LIBINFO_WL_00_DoShift_bx2h(rtb_Min_j1e2, rtu_indexToShiftBackOneBased,
      rtu_inBuffer, rty_outBuffer);

    /* End of Outputs for SubSystem: '<S229>/DoShift' */
  } else {
    /* Outputs for IfAction SubSystem: '<S229>/DoNothing' incorporates:
     *  ActionPort: '<S231>/Action Port'
     */
    LIBINFO_WL_00_DoNothing_n0wb(rtu_inBuffer, rty_outBuffer);

    /* End of Outputs for SubSystem: '<S229>/DoNothing' */
  }

  /* End of If: '<S229>/If' */
}

/*
 * Output and update for function-call system:
 *    '<S219>/MergeFunc'
 *    '<S235>/MergeFunc'
 *    '<S400>/MergeFunc'
 */
void LIBINFO_WL_00_MergeFunc(const real32_T rtu_inAccumulatorBuffer[10], int32_t
  rtu_mergeFromIndexOneBased, int32_t rtu_bufferDepth, real32_T
  rty_outAccumulatorBuffer[10], rtC_MergeFunc_LIBINFO_WL_00 *localC)
{
  /* local block i/o variables */
  real32_T rtb_TmpLatchAtinAccumula_bcj2jk[10];
  real32_T rtb_Assignment_ps4j[10];
  int32_t i;
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S222>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumula_bcj2jk[i] = rtu_inAccumulatorBuffer[i];

    /* Assignment: '<S222>/Assignment' */
    rtb_Assignment_ps4j[i] = rtb_TmpLatchAtinAccumula_bcj2jk[i];
  }

  /* Assignment: '<S222>/Assignment' incorporates:
   *  Bias: '<S222>/BackOne'
   *  Selector: '<S222>/Selector'
   *  Selector: '<S222>/Selector1'
   *  Sum: '<S222>/Add'
   */
  rtb_Assignment_ps4j[rtu_mergeFromIndexOneBased - 1] =
    rtb_TmpLatchAtinAccumula_bcj2jk[rtu_mergeFromIndexOneBased - 1] +
    rtb_TmpLatchAtinAccumula_bcj2jk[rtu_mergeFromIndexOneBased - 2];

  /* Outputs for Atomic SubSystem: '<S222>/ShiftBufferBack' */
  LIBINFO_WL_ShiftBufferBack_afxg(rtu_mergeFromIndexOneBased,
    rtb_Assignment_ps4j, rtu_bufferDepth, rty_outAccumulatorBuffer,
    (rtC_ShiftBufferBack_LIBINF_pzts *)(&localC->ShiftBufferBack));

  /* End of Outputs for SubSystem: '<S222>/ShiftBufferBack' */
}

/*
 * Output and update for action system:
 *    '<S479>/DoShift'
 *    '<S427>/DoShift'
 *    '<S474>/DoShift'
 *    '<S422>/DoShift'
 */
void LIBINFO_WL_00_DoShift_g0d2(int32_t rtu_bufferDepth, int32_t
  rtu_indexToShiftBackOneBased, const dt_libinfo_Unsigned32 rtu_inBuffer[10],
  dt_libinfo_Unsigned32 rty_outBuffer[10])
{
  int32_t rtb_PlusOne_dkl0;
  int32_t s483_iter;
  int32_t rtb_Sum_lbdp;
  int32_t i;

  /* Bias: '<S482>/PlusOne' incorporates:
   *  Sum: '<S482>/Sum1'
   */
  rtb_PlusOne_dkl0 = rtu_bufferDepth - rtu_indexToShiftBackOneBased;

  /* Outputs for Iterator SubSystem: '<S482>/ShiftBackOne' incorporates:
   *  ForIterator: '<S483>/For Iterator'
   */
  /* Bias: '<S482>/PlusOne' */
  for (s483_iter = 0; s483_iter < (rtb_PlusOne_dkl0 + 1); s483_iter++) {
    /* Sum: '<S483>/Sum' incorporates:
     *  Assignment: '<S483>/Assignment'
     *  Bias: '<S483>/BackOne'
     *  Selector: '<S483>/Selector'
     */
    rtb_Sum_lbdp = (s483_iter + rtu_indexToShiftBackOneBased) - 2;

    /* Assignment: '<S483>/Assignment' incorporates:
     *  Bias: '<S483>/BackOne'
     *  Selector: '<S483>/Selector'
     */
    if (s483_iter == 0) {
      for (i = 0; i < 10; i++) {
        rty_outBuffer[i] = rtu_inBuffer[i];
      }
    }

    rty_outBuffer[rtb_Sum_lbdp] = rtu_inBuffer[rtb_Sum_lbdp + 1];
  }

  /* End of Outputs for SubSystem: '<S482>/ShiftBackOne' */
}

/*
 * Output and update for action system:
 *    '<S479>/DoNothing'
 *    '<S427>/DoNothing'
 *    '<S474>/DoNothing'
 *    '<S422>/DoNothing'
 */
void LIBINFO_WL_00_DoNothing_i3r3(const dt_libinfo_Unsigned32 rtu_0[10],
  dt_libinfo_Unsigned32 rty_outBuffer[10])
{
  int32_t i;

  /* Inport: '<S481>/inBuffer' */
  for (i = 0; i < 10; i++) {
    rty_outBuffer[i] = rtu_0[i];
  }

  /* End of Inport: '<S481>/inBuffer' */
}

/*
 * Output and update for function-call system:
 *    '<S468>/MergeFunc'
 *    '<S416>/MergeFunc'
 */
void LIBINFO_WL_00_MergeFunc_oer2(const dt_libinfo_Unsigned32
  rtu_inAccumulatorBuffer[10], int32_t rtu_mergeFromIndexOneBased, int32_t
  rtu_bufferDepth, dt_libinfo_Unsigned32 rty_outAccumulatorBuffer[10],
  rtC_MergeFunc_LIBINFO_WL_0_e0nk *localC)
{
  /* local block i/o variables */
  int32_t rtb_Min_fqri;
  dt_libinfo_Unsigned32 rtb_TmpLatchAtinAccumula_hky241[10];
  dt_libinfo_Unsigned32 rtb_Assignment_ih51[10];
  int32_t i;
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S472>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumula_hky241[i] = rtu_inAccumulatorBuffer[i];

    /* Assignment: '<S472>/Assignment' */
    rtb_Assignment_ih51[i] = rtb_TmpLatchAtinAccumula_hky241[i];
  }

  /* Assignment: '<S472>/Assignment' incorporates:
   *  Bias: '<S472>/BackOne'
   *  Selector: '<S472>/Selector'
   */
  rtb_Assignment_ih51[rtu_mergeFromIndexOneBased - 1] =
    rtb_TmpLatchAtinAccumula_hky241[rtu_mergeFromIndexOneBased - 2];

  /* Outputs for Atomic SubSystem: '<S472>/ShiftBufferBack' */
  /* MinMax: '<S479>/Min' */
  if (rtu_bufferDepth <= localC->Width) {
    rtb_Min_fqri = rtu_bufferDepth;
  } else {
    rtb_Min_fqri = localC->Width;
  }

  /* End of MinMax: '<S479>/Min' */

  /* If: '<S479>/If' incorporates:
   *  Constant: '<S480>/Constant'
   *  Logic: '<S479>/Logical Operator'
   *  RelationalOperator: '<S479>/Relational Operator'
   *  RelationalOperator: '<S480>/Compare'
   */
  if ((rtu_mergeFromIndexOneBased > 1) && (rtu_mergeFromIndexOneBased <=
       rtb_Min_fqri)) {
    /* Outputs for IfAction SubSystem: '<S479>/DoShift' incorporates:
     *  ActionPort: '<S482>/Action Port'
     */
    LIBINFO_WL_00_DoShift_g0d2(rtb_Min_fqri, rtu_mergeFromIndexOneBased,
      rtb_Assignment_ih51, rty_outAccumulatorBuffer);

    /* End of Outputs for SubSystem: '<S479>/DoShift' */
  } else {
    /* Outputs for IfAction SubSystem: '<S479>/DoNothing' incorporates:
     *  ActionPort: '<S481>/Action Port'
     */
    LIBINFO_WL_00_DoNothing_i3r3(rtb_Assignment_ih51, rty_outAccumulatorBuffer);

    /* End of Outputs for SubSystem: '<S479>/DoNothing' */
  }

  /* End of If: '<S479>/If' */
  /* End of Outputs for SubSystem: '<S472>/ShiftBufferBack' */
}

/*
 * Output and update for action system:
 *    '<S444>/DoShift'
 *    '<S439>/DoShift'
 */
void LIBINFO_WL_00_DoShift_etzq(int32_t rtu_bufferDepth, int32_t
  rtu_indexToShiftBackOneBased, const dt_libinfo_gps_latitude rtu_inBuffer[10],
  dt_libinfo_gps_latitude rty_outBuffer[10])
{
  int32_t rtb_PlusOne_jfhk;
  int32_t s448_iter;
  int32_t rtb_Sum_c4ir;
  int32_t i;

  /* Bias: '<S447>/PlusOne' incorporates:
   *  Sum: '<S447>/Sum1'
   */
  rtb_PlusOne_jfhk = rtu_bufferDepth - rtu_indexToShiftBackOneBased;

  /* Outputs for Iterator SubSystem: '<S447>/ShiftBackOne' incorporates:
   *  ForIterator: '<S448>/For Iterator'
   */
  /* Bias: '<S447>/PlusOne' */
  for (s448_iter = 0; s448_iter < (rtb_PlusOne_jfhk + 1); s448_iter++) {
    /* Sum: '<S448>/Sum' incorporates:
     *  Assignment: '<S448>/Assignment'
     *  Bias: '<S448>/BackOne'
     *  Selector: '<S448>/Selector'
     */
    rtb_Sum_c4ir = (s448_iter + rtu_indexToShiftBackOneBased) - 2;

    /* Assignment: '<S448>/Assignment' incorporates:
     *  Bias: '<S448>/BackOne'
     *  Selector: '<S448>/Selector'
     */
    if (s448_iter == 0) {
      for (i = 0; i < 10; i++) {
        rty_outBuffer[i] = rtu_inBuffer[i];
      }
    }

    rty_outBuffer[rtb_Sum_c4ir] = rtu_inBuffer[rtb_Sum_c4ir + 1];
  }

  /* End of Outputs for SubSystem: '<S447>/ShiftBackOne' */
}

/*
 * Output and update for action system:
 *    '<S444>/DoNothing'
 *    '<S439>/DoNothing'
 */
void LIBINFO_WL_00_DoNothing_b1m5(const dt_libinfo_gps_latitude rtu_0[10],
  dt_libinfo_gps_latitude rty_outBuffer[10])
{
  int32_t i;

  /* Inport: '<S446>/inBuffer' */
  for (i = 0; i < 10; i++) {
    rty_outBuffer[i] = rtu_0[i];
  }

  /* End of Inport: '<S446>/inBuffer' */
}

/*
 * Output and update for action system:
 *    '<S458>/DoShift'
 *    '<S453>/DoShift'
 */
void LIBINFO_WL_00_DoShift_ihkh(int32_t rtu_bufferDepth, int32_t
  rtu_indexToShiftBackOneBased, const dt_libinfo_Ratio_Unsigned32 rtu_inBuffer
  [10], dt_libinfo_Ratio_Unsigned32 rty_outBuffer[10])
{
  int32_t rtb_PlusOne_ou3o;
  int32_t s462_iter;
  int32_t rtb_Sum_fzyy;
  int32_t i;

  /* Bias: '<S461>/PlusOne' incorporates:
   *  Sum: '<S461>/Sum1'
   */
  rtb_PlusOne_ou3o = rtu_bufferDepth - rtu_indexToShiftBackOneBased;

  /* Outputs for Iterator SubSystem: '<S461>/ShiftBackOne' incorporates:
   *  ForIterator: '<S462>/For Iterator'
   */
  /* Bias: '<S461>/PlusOne' */
  for (s462_iter = 0; s462_iter < (rtb_PlusOne_ou3o + 1); s462_iter++) {
    /* Sum: '<S462>/Sum' incorporates:
     *  Assignment: '<S462>/Assignment'
     *  Bias: '<S462>/BackOne'
     *  Selector: '<S462>/Selector'
     */
    rtb_Sum_fzyy = (s462_iter + rtu_indexToShiftBackOneBased) - 2;

    /* Assignment: '<S462>/Assignment' incorporates:
     *  Bias: '<S462>/BackOne'
     *  Selector: '<S462>/Selector'
     */
    if (s462_iter == 0) {
      for (i = 0; i < 10; i++) {
        rty_outBuffer[i] = rtu_inBuffer[i];
      }
    }

    rty_outBuffer[rtb_Sum_fzyy] = rtu_inBuffer[rtb_Sum_fzyy + 1];
  }

  /* End of Outputs for SubSystem: '<S461>/ShiftBackOne' */
}

/*
 * Output and update for action system:
 *    '<S458>/DoNothing'
 *    '<S453>/DoNothing'
 */
void LIBINFO_WL_00_DoNothing_acyu(const dt_libinfo_Ratio_Unsigned32 rtu_0[10],
  dt_libinfo_Ratio_Unsigned32 rty_outBuffer[10])
{
  int32_t i;

  /* Inport: '<S460>/inBuffer' */
  for (i = 0; i < 10; i++) {
    rty_outBuffer[i] = rtu_0[i];
  }

  /* End of Inport: '<S460>/inBuffer' */
}

/*
 * Output and update for action system:
 *    '<S292>/DoShift'
 *    '<S282>/DoShift'
 */
void LIBINFO_WL_00_DoShift_cq4g(int32_t rtu_bufferDepth, int32_t
  rtu_indexToShiftBackOneBased, const dt_libinfo_Flag_u16 rtu_inBuffer[10],
  dt_libinfo_Flag_u16 rty_outBuffer[10])
{
  int32_t rtb_PlusOne_cg5n;
  int32_t s300_iter;
  int32_t rtb_Sum_hj04;
  int32_t i;

  /* Bias: '<S299>/PlusOne' incorporates:
   *  Sum: '<S299>/Sum1'
   */
  rtb_PlusOne_cg5n = rtu_bufferDepth - rtu_indexToShiftBackOneBased;

  /* Outputs for Iterator SubSystem: '<S299>/ShiftBackOne' incorporates:
   *  ForIterator: '<S300>/For Iterator'
   */
  /* Bias: '<S299>/PlusOne' */
  for (s300_iter = 0; s300_iter < (rtb_PlusOne_cg5n + 1); s300_iter++) {
    /* Sum: '<S300>/Sum' incorporates:
     *  Assignment: '<S300>/Assignment'
     *  Bias: '<S300>/BackOne'
     *  Selector: '<S300>/Selector'
     */
    rtb_Sum_hj04 = (s300_iter + rtu_indexToShiftBackOneBased) - 2;

    /* Assignment: '<S300>/Assignment' incorporates:
     *  Bias: '<S300>/BackOne'
     *  Selector: '<S300>/Selector'
     */
    if (s300_iter == 0) {
      for (i = 0; i < 10; i++) {
        rty_outBuffer[i] = rtu_inBuffer[i];
      }
    }

    rty_outBuffer[rtb_Sum_hj04] = rtu_inBuffer[rtb_Sum_hj04 + 1];
  }

  /* End of Outputs for SubSystem: '<S299>/ShiftBackOne' */
}

/*
 * Output and update for action system:
 *    '<S292>/DoNothing'
 *    '<S282>/DoNothing'
 */
void LIBINFO_WL_00_DoNothing_keuk(const dt_libinfo_Flag_u16 rtu_0[10],
  dt_libinfo_Flag_u16 rty_outBuffer[10])
{
  int32_t i;

  /* Inport: '<S298>/inBuffer' */
  for (i = 0; i < 10; i++) {
    rty_outBuffer[i] = rtu_0[i];
  }

  /* End of Inport: '<S298>/inBuffer' */
}

/* Output and update for function-call system: '<S349>/FuncCallSplit2' */
void LIBINFO_WL_00_FuncCallSplit2(const int32_t rtu_0[10], int32_t rtu_1,
  int32_t rtu_2, const dt_libinfo_Time20msLong rtu_3[10], const
  dt_libinfo_Time20msLong rtu_4[10], const dt_libinfo_gps_latitude rtu_5[10],
  const dt_libinfo_Ratio_Unsigned32 rtu_6[10], const dt_libinfo_single rtu_7[10],
  const dt_libinfo_Flag_u16 rtu_8[10], const real32_T rtu_9[10], const
  dt_libinfo_Unsigned32 rtu_10[10], const real32_T rtu_11[10], const real32_T
  rtu_12[10], const dt_libinfo_Unsigned32 rtu_13[10], int32_t rty_0[10],
  dt_libinfo_gps_latitude rty_1[10], dt_libinfo_Ratio_Unsigned32 rty_2[10],
  dt_libinfo_Flag_u16 rty_3[10], dt_libinfo_Time20msLong rty_6[10],
  dt_libinfo_Time20msLong rty_9[10], real32_T rty_12[10], dt_libinfo_Unsigned32
  rty_15[10], real32_T rty_18[10], real32_T rty_25[10], dt_libinfo_Unsigned32
  rty_28[10], dt_libinfo_single rty_31[10], rtC_FuncCallSplit2_LIBINFO_WL_0
  *localC)
{
  /* local block i/o variables */
  dt_libinfo_single rtb_TmpLatchAtinParamBuff_k5vim[10];
  dt_libinfo_single rtb_Assignment[10];
  int32_t rtb_Min_fzne;
  int32_t rtb_Min_knky;
  int32_t rtb_Min_lv2e;
  int32_t rtb_TmpLatchAtinIndexBuf_ispy3o[10];
  int32_t rtb_Assignment_l3th[10];
  int32_t rtb_Min_agcz;
  dt_libinfo_gps_latitude rtb_TmpLatchAtinAccumulat_pdovz[10];
  dt_libinfo_gps_latitude rtb_Assignment_agyh[10];
  dt_libinfo_Ratio_Unsigned32 rtb_TmpLatchAtinAccumula_edhmig[10];
  dt_libinfo_Ratio_Unsigned32 rtb_Assignment_cp3j[10];
  dt_libinfo_Time20msLong rtb_TmpLatchAtinAccumula_ofwtmq[10];
  dt_libinfo_Time20msLong rtb_Assignment_g04e[10];
  dt_libinfo_Time20msLong rtb_TmpLatchAtinAccumula_hpldf3[10];
  dt_libinfo_Time20msLong rtb_Assignment_oavc[10];
  dt_libinfo_Flag_u16 rtb_TmpLatchAtinParamConf_odkgz[10];
  dt_libinfo_Flag_u16 rtb_Assignment1[10];
  int32_t rtb_BackOne_gc44;
  boolean_T rtb_RelationalOperator_gbbz;
  int32_t i;
  uint64_T tmp;

  /* S-Function (fcncallgen): '<S365>/Function-Call Generator' incorporates:
   *  SubSystem: '<S348>/MergeFunc'
   */
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S352>/TmpLatchAtinIndexBufferOutport1' */
    rtb_TmpLatchAtinIndexBuf_ispy3o[i] = rtu_0[i];

    /* Assignment: '<S352>/Assignment' */
    rtb_Assignment_l3th[i] = rtb_TmpLatchAtinIndexBuf_ispy3o[i];
  }

  /* Assignment: '<S352>/Assignment' incorporates:
   *  Bias: '<S352>/BackOne'
   *  Selector: '<S352>/Selector'
   */
  rtb_Assignment_l3th[rtu_1 - 1] = rtb_TmpLatchAtinIndexBuf_ispy3o[rtu_1 - 2];

  /* Outputs for Atomic SubSystem: '<S352>/ShiftBufferBack1' */
  /* MinMax: '<S359>/Min' */
  if (rtu_2 <= localC->Width_kzgs) {
    rtb_Min_agcz = rtu_2;
  } else {
    rtb_Min_agcz = localC->Width_kzgs;
  }

  /* End of MinMax: '<S359>/Min' */

  /* If: '<S359>/If' incorporates:
   *  Constant: '<S360>/Constant'
   *  Logic: '<S359>/Logical Operator'
   *  RelationalOperator: '<S359>/Relational Operator'
   *  RelationalOperator: '<S360>/Compare'
   */
  if ((rtu_1 > 1) && (rtu_1 <= rtb_Min_agcz)) {
    /* Outputs for IfAction SubSystem: '<S359>/DoShift' incorporates:
     *  ActionPort: '<S362>/Action Port'
     */
    LIBINFO_WL_00_DoShift(rtb_Min_agcz, rtu_1, rtb_Assignment_l3th, rty_0);

    /* End of Outputs for SubSystem: '<S359>/DoShift' */
  } else {
    /* Outputs for IfAction SubSystem: '<S359>/DoNothing' incorporates:
     *  ActionPort: '<S361>/Action Port'
     */
    LIBINFO_WL_00_DoNothing(rtb_Assignment_l3th, rty_0);

    /* End of Outputs for SubSystem: '<S359>/DoNothing' */
  }

  /* End of Outputs for SubSystem: '<S352>/ShiftBufferBack1' */

  /* S-Function (fcncallgen): '<S365>/Function-Call Generator' incorporates:
   *  SubSystem: '<S307>/FuncCallSplit2'
   */
  /* S-Function (fcncallgen): '<S340>/Function-Call Generator' incorporates:
   *  SubSystem: '<S305>/MergeFunc'
   */
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S313>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumula_hpldf3[i] = rtu_3[i];

    /* Assignment: '<S313>/Assignment' */
    rtb_Assignment_oavc[i] = rtb_TmpLatchAtinAccumula_hpldf3[i];
  }

  /* End of If: '<S359>/If' */

  /* Sum: '<S313>/Add' incorporates:
   *  Bias: '<S313>/BackOne'
   *  Selector: '<S313>/Selector'
   *  Selector: '<S313>/Selector1'
   */
  tmp = ((uint64_T)rtb_TmpLatchAtinAccumula_hpldf3[rtu_1 - 1]) + ((uint64_T)
    rtb_TmpLatchAtinAccumula_hpldf3[rtu_1 - 2]);
  if (tmp > 4294967295UL) {
    tmp = 4294967295UL;
  }

  /* Assignment: '<S313>/Assignment' incorporates:
   *  Sum: '<S313>/Add'
   */
  rtb_Assignment_oavc[rtu_1 - 1] = (uint32_t)tmp;

  /* Outputs for Atomic SubSystem: '<S313>/ShiftBufferBack' */
  LIBINFO_WL_00_ShiftBufferBack(rtu_1, rtb_Assignment_oavc, rtu_2, rty_6,
    (rtC_ShiftBufferBack_LIBINFO_WL_ *)(&localC->ShiftBufferBack));

  /* End of Outputs for SubSystem: '<S313>/ShiftBufferBack' */

  /* S-Function (fcncallgen): '<S340>/Function-Call Generator' incorporates:
   *  SubSystem: '<S308>/FuncCallSplit2'
   */
  /* S-Function (fcncallgen): '<S344>/Function-Call Generator' incorporates:
   *  SubSystem: '<S306>/MergeFunc'
   */
  /* Bias: '<S327>/BackOne' incorporates:
   *  Selector: '<S327>/Selector1'
   */
  rtb_BackOne_gc44 = rtu_1 - 2;
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S327>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumula_ofwtmq[i] = rtu_4[i];

    /* Assignment: '<S327>/Assignment' */
    rtb_Assignment_g04e[i] = rtb_TmpLatchAtinAccumula_ofwtmq[i];
  }

  /* MinMax: '<S327>/Min' incorporates:
   *  Selector: '<S327>/Selector'
   *  Selector: '<S327>/Selector1'
   */
  if (rtb_TmpLatchAtinAccumula_ofwtmq[rtu_1 - 1] <=
      rtb_TmpLatchAtinAccumula_ofwtmq[rtb_BackOne_gc44]) {
    /* Assignment: '<S327>/Assignment' */
    rtb_Assignment_g04e[rtu_1 - 1] = rtb_TmpLatchAtinAccumula_ofwtmq[rtu_1 - 1];
  } else {
    /* Assignment: '<S327>/Assignment' */
    rtb_Assignment_g04e[rtu_1 - 1] =
      rtb_TmpLatchAtinAccumula_ofwtmq[rtb_BackOne_gc44];
  }

  /* End of MinMax: '<S327>/Min' */

  /* Outputs for Atomic SubSystem: '<S327>/ShiftBufferBack1' */
  LIBINFO_WL_00_ShiftBufferBack(rtu_1, rtb_Assignment_g04e, rtu_2, rty_9,
    (rtC_ShiftBufferBack_LIBINFO_WL_ *)(&localC->ShiftBufferBack1_m2r3));

  /* End of Outputs for SubSystem: '<S327>/ShiftBufferBack1' */

  /* S-Function (fcncallgen): '<S344>/Function-Call Generator' incorporates:
   *  SubSystem: '<S211>/FuncCallSplit2'
   */
  /* S-Function (fcncallgen): '<S389>/Function-Call Generator' incorporates:
   *  SubSystem: '<S219>/MergeFunc'
   */
  LIBINFO_WL_00_MergeFunc(rtu_9, rtu_1, rtu_2, rty_12,
    (rtC_MergeFunc_LIBINFO_WL_00 *)(&localC->MergeFunc_hwhi));

  /* S-Function (fcncallgen): '<S389>/Function-Call Generator' incorporates:
   *  SubSystem: '<S207>/FuncCallSplit2'
   */
  /* S-Function (fcncallgen): '<S373>/Function-Call Generator' incorporates:
   *  SubSystem: '<S468>/MergeFunc'
   */
  LIBINFO_WL_00_MergeFunc_oer2(rtu_10, rtu_1, rtu_2, rty_15,
    (rtC_MergeFunc_LIBINFO_WL_0_e0nk *)(&localC->MergeFunc_oer2));

  /* S-Function (fcncallgen): '<S373>/Function-Call Generator' incorporates:
   *  SubSystem: '<S208>/FuncCallSplit2'
   */
  /* S-Function (fcncallgen): '<S377>/Function-Call Generator' incorporates:
   *  SubSystem: '<S235>/MergeFunc'
   */
  LIBINFO_WL_00_MergeFunc(rtu_11, rtu_1, rtu_2, rty_18,
    (rtC_MergeFunc_LIBINFO_WL_00 *)(&localC->MergeFunc_hlkr));

  /* S-Function (fcncallgen): '<S377>/Function-Call Generator' incorporates:
   *  SubSystem: '<S209>/FuncCallSplit2'
   */
  /* S-Function (fcncallgen): '<S381>/Function-Call Generator' incorporates:
   *  SubSystem: '<S434>/FuncCallSplit2'
   */
  /* S-Function (fcncallgen): '<S464>/Function-Call Generator' incorporates:
   *  SubSystem: '<S432>/MergeFunc'
   */
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S437>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumulat_pdovz[i] = rtu_5[i];

    /* Assignment: '<S437>/Assignment' */
    rtb_Assignment_agyh[i] = rtb_TmpLatchAtinAccumulat_pdovz[i];
  }

  /* Assignment: '<S437>/Assignment' incorporates:
   *  Bias: '<S437>/BackOne'
   *  Selector: '<S437>/Selector'
   */
  rtb_Assignment_agyh[rtu_1 - 1] = rtb_TmpLatchAtinAccumulat_pdovz[rtu_1 - 2];

  /* Outputs for Atomic SubSystem: '<S437>/ShiftBufferBack' */
  /* MinMax: '<S444>/Min' */
  if (rtu_2 <= localC->Width_p4oi) {
    rtb_Min_lv2e = rtu_2;
  } else {
    rtb_Min_lv2e = localC->Width_p4oi;
  }

  /* End of MinMax: '<S444>/Min' */

  /* If: '<S444>/If' incorporates:
   *  Constant: '<S445>/Constant'
   *  Logic: '<S444>/Logical Operator'
   *  RelationalOperator: '<S444>/Relational Operator'
   *  RelationalOperator: '<S445>/Compare'
   */
  if ((rtu_1 > 1) && (rtu_1 <= rtb_Min_lv2e)) {
    /* Outputs for IfAction SubSystem: '<S444>/DoShift' incorporates:
     *  ActionPort: '<S447>/Action Port'
     */
    LIBINFO_WL_00_DoShift_etzq(rtb_Min_lv2e, rtu_1, rtb_Assignment_agyh, rty_1);

    /* End of Outputs for SubSystem: '<S444>/DoShift' */
  } else {
    /* Outputs for IfAction SubSystem: '<S444>/DoNothing' incorporates:
     *  ActionPort: '<S446>/Action Port'
     */
    LIBINFO_WL_00_DoNothing_b1m5(rtb_Assignment_agyh, rty_1);

    /* End of Outputs for SubSystem: '<S444>/DoNothing' */
  }

  /* End of Outputs for SubSystem: '<S437>/ShiftBufferBack' */

  /* S-Function (fcncallgen): '<S464>/Function-Call Generator' incorporates:
   *  SubSystem: '<S433>/MergeFunc'
   */
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S451>/TmpLatchAtinAccumulatorBufferOutport1' */
    rtb_TmpLatchAtinAccumula_edhmig[i] = rtu_6[i];

    /* Assignment: '<S451>/Assignment' */
    rtb_Assignment_cp3j[i] = rtb_TmpLatchAtinAccumula_edhmig[i];
  }

  /* End of If: '<S444>/If' */

  /* Assignment: '<S451>/Assignment' incorporates:
   *  Bias: '<S451>/BackOne'
   *  Selector: '<S451>/Selector'
   */
  rtb_Assignment_cp3j[rtu_1 - 1] = rtb_TmpLatchAtinAccumula_edhmig[rtu_1 - 2];

  /* Outputs for Atomic SubSystem: '<S451>/ShiftBufferBack' */
  /* MinMax: '<S458>/Min' */
  if (rtu_2 <= localC->Width_kcio) {
    rtb_Min_knky = rtu_2;
  } else {
    rtb_Min_knky = localC->Width_kcio;
  }

  /* End of MinMax: '<S458>/Min' */

  /* If: '<S458>/If' incorporates:
   *  Constant: '<S459>/Constant'
   *  Logic: '<S458>/Logical Operator'
   *  RelationalOperator: '<S458>/Relational Operator'
   *  RelationalOperator: '<S459>/Compare'
   */
  if ((rtu_1 > 1) && (rtu_1 <= rtb_Min_knky)) {
    /* Outputs for IfAction SubSystem: '<S458>/DoShift' incorporates:
     *  ActionPort: '<S461>/Action Port'
     */
    LIBINFO_WL_00_DoShift_ihkh(rtb_Min_knky, rtu_1, rtb_Assignment_cp3j, rty_2);

    /* End of Outputs for SubSystem: '<S458>/DoShift' */
  } else {
    /* Outputs for IfAction SubSystem: '<S458>/DoNothing' incorporates:
     *  ActionPort: '<S460>/Action Port'
     */
    LIBINFO_WL_00_DoNothing_acyu(rtb_Assignment_cp3j, rty_2);

    /* End of Outputs for SubSystem: '<S458>/DoNothing' */
  }

  /* End of If: '<S458>/If' */
  /* End of Outputs for SubSystem: '<S451>/ShiftBufferBack' */

  /* S-Function (fcncallgen): '<S381>/Function-Call Generator' incorporates:
   *  SubSystem: '<S210>/FuncCallSplit2'
   */
  /* S-Function (fcncallgen): '<S385>/Function-Call Generator' incorporates:
   *  SubSystem: '<S400>/MergeFunc'
   */
  LIBINFO_WL_00_MergeFunc(rtu_12, rtu_1, rtu_2, rty_25,
    (rtC_MergeFunc_LIBINFO_WL_00 *)(&localC->MergeFunc_ezkx));

  /* S-Function (fcncallgen): '<S385>/Function-Call Generator' incorporates:
   *  SubSystem: '<S212>/FuncCallSplit2'
   */
  /* S-Function (fcncallgen): '<S393>/Function-Call Generator' incorporates:
   *  SubSystem: '<S416>/MergeFunc'
   */
  LIBINFO_WL_00_MergeFunc_oer2(rtu_13, rtu_1, rtu_2, rty_28,
    (rtC_MergeFunc_LIBINFO_WL_0_e0nk *)(&localC->MergeFunc_kdks));

  /* S-Function (fcncallgen): '<S393>/Function-Call Generator' incorporates:
   *  SubSystem: '<S213>/FuncCallSplit2'
   */
  /* S-Function (fcncallgen): '<S397>/Function-Call Generator' incorporates:
   *  SubSystem: '<S275>/MergeFunc'
   */
  /* Bias: '<S279>/BackOne' incorporates:
   *  Selector: '<S279>/Selector'
   *  Selector: '<S279>/Selector5'
   *  Switch: '<S279>/Switch1'
   */
  rtb_BackOne_gc44 = rtu_1 - 2;
  for (i = 0; i < 10; i++) {
    /* SignalConversion: '<S279>/TmpLatchAtinParamBufferOutport1' */
    rtb_TmpLatchAtinParamBuff_k5vim[i] = rtu_7[i];

    /* SignalConversion: '<S279>/TmpLatchAtinParamConfBufferOutport1' */
    rtb_TmpLatchAtinParamConf_odkgz[i] = rtu_8[i];

    /* Assignment: '<S279>/Assignment' */
    rtb_Assignment[i] = rtb_TmpLatchAtinParamBuff_k5vim[i];

    /* Assignment: '<S279>/Assignment1' */
    rtb_Assignment1[i] = rtb_TmpLatchAtinParamConf_odkgz[i];
  }

  /* RelationalOperator: '<S279>/Relational Operator' incorporates:
   *  Selector: '<S279>/Selector1'
   *  Selector: '<S279>/Selector5'
   */
  rtb_RelationalOperator_gbbz =
    (rtb_TmpLatchAtinParamConf_odkgz[rtb_BackOne_gc44] >
     rtb_TmpLatchAtinParamConf_odkgz[rtu_1 - 1]);

  /* Switch: '<S279>/Switch1' incorporates:
   *  Switch: '<S279>/Switch'
   */
  if (rtb_RelationalOperator_gbbz) {
    /* Assignment: '<S279>/Assignment' incorporates:
     *  Selector: '<S279>/Selector'
     */
    rtb_Assignment[rtu_1 - 1] = rtb_TmpLatchAtinParamBuff_k5vim[rtb_BackOne_gc44];

    /* Assignment: '<S279>/Assignment1' incorporates:
     *  Selector: '<S279>/Selector5'
     */
    rtb_Assignment1[rtu_1 - 1] =
      rtb_TmpLatchAtinParamConf_odkgz[rtb_BackOne_gc44];
  } else {
    /* Assignment: '<S279>/Assignment' incorporates:
     *  Selector: '<S279>/Selector6'
     */
    rtb_Assignment[rtu_1 - 1] = rtb_TmpLatchAtinParamBuff_k5vim[rtu_1 - 1];

    /* Assignment: '<S279>/Assignment1' incorporates:
     *  Selector: '<S279>/Selector1'
     */
    rtb_Assignment1[rtu_1 - 1] = rtb_TmpLatchAtinParamConf_odkgz[rtu_1 - 1];
  }

  /* Outputs for Atomic SubSystem: '<S279>/ShiftBufferBack' */
  LIBINFO_WL_ShiftBufferBack_afxg(rtu_1, rtb_Assignment, rtu_2, rty_31,
    (rtC_ShiftBufferBack_LIBINF_pzts *)(&localC->ShiftBufferBack_pqrw));

  /* End of Outputs for SubSystem: '<S279>/ShiftBufferBack' */

  /* Outputs for Atomic SubSystem: '<S279>/ShiftBufferBack1' */
  /* MinMax: '<S292>/Min' */
  if (rtu_2 <= localC->Width) {
    rtb_Min_fzne = rtu_2;
  } else {
    rtb_Min_fzne = localC->Width;
  }

  /* End of MinMax: '<S292>/Min' */

  /* If: '<S292>/If' incorporates:
   *  Constant: '<S297>/Constant'
   *  Logic: '<S292>/Logical Operator'
   *  RelationalOperator: '<S292>/Relational Operator'
   *  RelationalOperator: '<S297>/Compare'
   */
  if ((rtu_1 > 1) && (rtu_1 <= rtb_Min_fzne)) {
    /* Outputs for IfAction SubSystem: '<S292>/DoShift' incorporates:
     *  ActionPort: '<S299>/Action Port'
     */
    LIBINFO_WL_00_DoShift_cq4g(rtb_Min_fzne, rtu_1, rtb_Assignment1, rty_3);

    /* End of Outputs for SubSystem: '<S292>/DoShift' */
  } else {
    /* Outputs for IfAction SubSystem: '<S292>/DoNothing' incorporates:
     *  ActionPort: '<S298>/Action Port'
     */
    LIBINFO_WL_00_DoNothing_keuk(rtb_Assignment1, rty_3);

    /* End of Outputs for SubSystem: '<S292>/DoNothing' */
  }

  /* End of If: '<S292>/If' */
  /* End of Outputs for SubSystem: '<S279>/ShiftBufferBack1' */
}

/*
 * Output and update for atomic system:
 *    '<S312>/ShiftBufferBack'
 *    '<S326>/ShiftBufferBack1'
 */
void LIBINFO_WL_ShiftBufferBack_nhsx(int32_t rtu_indexToShiftBackOneBased, const
  dt_libinfo_Time20msLong rtu_inBuffer[10], int32_t rtu_bufferDepth,
  dt_libinfo_Time20msLong rty_outBuffer[10], rtC_ShiftBufferBack_LIBINF_h3x4
  *localC)
{
  /* local block i/o variables */
  int32_t rtb_Min_hlzi;

  /* MinMax: '<S315>/Min' */
  if (rtu_bufferDepth <= localC->Width) {
    rtb_Min_hlzi = rtu_bufferDepth;
  } else {
    rtb_Min_hlzi = localC->Width;
  }

  /* End of MinMax: '<S315>/Min' */

  /* If: '<S315>/If' incorporates:
   *  Logic: '<S315>/Logical Operator'
   *  RelationalOperator: '<S315>/Relational Operator'
   */
  if ((localC->Compare) && (rtu_indexToShiftBackOneBased <= rtb_Min_hlzi)) {
    /* Outputs for IfAction SubSystem: '<S315>/DoShift' incorporates:
     *  ActionPort: '<S318>/Action Port'
     */
    LIBINFO_WL_00_DoShift_kcfw(rtb_Min_hlzi, rtu_indexToShiftBackOneBased,
      rtu_inBuffer, rty_outBuffer);

    /* End of Outputs for SubSystem: '<S315>/DoShift' */
  } else {
    /* Outputs for IfAction SubSystem: '<S315>/DoNothing' incorporates:
     *  ActionPort: '<S317>/Action Port'
     */
    LIBINFO_WL_00_DoNothing_aohe(rtu_inBuffer, rty_outBuffer);

    /* End of Outputs for SubSystem: '<S315>/DoNothing' */
  }

  /* End of If: '<S315>/If' */
}

/*
 * Output and update for atomic system:
 *    '<S221>/ShiftBufferBack'
 *    '<S237>/ShiftBufferBack'
 *    '<S402>/ShiftBufferBack'
 *    '<S278>/ShiftBufferBack'
 */
void LIBINFO_WL_ShiftBufferBack_frny(int32_t rtu_indexToShiftBackOneBased, const
  real32_T rtu_inBuffer[10], int32_t rtu_bufferDepth, real32_T rty_outBuffer[10],
  rtC_ShiftBufferBack_LIBINF_enc2 *localC)
{
  /* local block i/o variables */
  int32_t rtb_Min_k1m1;

  /* MinMax: '<S224>/Min' */
  if (rtu_bufferDepth <= localC->Width) {
    rtb_Min_k1m1 = rtu_bufferDepth;
  } else {
    rtb_Min_k1m1 = localC->Width;
  }

  /* End of MinMax: '<S224>/Min' */

  /* If: '<S224>/If' incorporates:
   *  Logic: '<S224>/Logical Operator'
   *  RelationalOperator: '<S224>/Relational Operator'
   */
  if ((localC->Compare) && (rtu_indexToShiftBackOneBased <= rtb_Min_k1m1)) {
    /* Outputs for IfAction SubSystem: '<S224>/DoShift' incorporates:
     *  ActionPort: '<S227>/Action Port'
     */
    LIBINFO_WL_00_DoShift_bx2h(rtb_Min_k1m1, rtu_indexToShiftBackOneBased,
      rtu_inBuffer, rty_outBuffer);

    /* End of Outputs for SubSystem: '<S224>/DoShift' */
  } else {
    /* Outputs for IfAction SubSystem: '<S224>/DoNothing' incorporates:
     *  ActionPort: '<S226>/Action Port'
     */
    LIBINFO_WL_00_DoNothing_n0wb(rtu_inBuffer, rty_outBuffer);

    /* End of Outputs for SubSystem: '<S224>/DoNothing' */
  }

  /* End of If: '<S224>/If' */
}

/*
 * Output and update for function-call system:
 *    '<S219>/CommitFunc'
 *    '<S235>/CommitFunc'
 *    '<S400>/CommitFunc'
 */
void LIBINFO_WL_00_CommitFunc(const real32_T rtu_inAccumulatorBuffer[10],
  int32_t rtu_bufferDepth, real32_T rty_commitAccumulation[10], real32_T
  rty_outAccumulatorBuffer[10], rtC_CommitFunc_LIBINFO_WL_00 *localC)
{
  int32_t i;

  /* SignalConversion: '<S221>/TmpLatchAtinAccumulatorBufferOutport1' */
  for (i = 0; i < 10; i++) {
    rty_commitAccumulation[i] = rtu_inAccumulatorBuffer[i];
  }

  /* End of SignalConversion: '<S221>/TmpLatchAtinAccumulatorBufferOutport1' */

  /* Outputs for Atomic SubSystem: '<S221>/ShiftBufferBack' */

  /* Constant: '<S221>/Constant' */
  LIBINFO_WL_ShiftBufferBack_frny(2, rty_commitAccumulation, rtu_bufferDepth,
    rty_outAccumulatorBuffer, (rtC_ShiftBufferBack_LIBINF_enc2 *)
    (&localC->ShiftBufferBack));

  /* End of Outputs for SubSystem: '<S221>/ShiftBufferBack' */
}

/*
 * Output and update for function-call system:
 *    '<S468>/CommitFunc'
 *    '<S416>/CommitFunc'
 */
void LIBINFO_WL_00_CommitFunc_ibfk(const dt_libinfo_Unsigned32
  rtu_inAccumulatorBuffer[10], int32_t rtu_bufferDepth, dt_libinfo_Unsigned32
  rty_commitAccumulation[10], dt_libinfo_Unsigned32 rty_outAccumulatorBuffer[10],
  rtC_CommitFunc_LIBINFO_WL__juir *localC)
{
  /* local block i/o variables */
  int32_t rtb_Min_aoon;
  int32_t i;

  /* SignalConversion: '<S471>/TmpLatchAtinAccumulatorBufferOutport1' */
  for (i = 0; i < 10; i++) {
    rty_commitAccumulation[i] = rtu_inAccumulatorBuffer[i];
  }

  /* End of SignalConversion: '<S471>/TmpLatchAtinAccumulatorBufferOutport1' */

  /* Outputs for Atomic SubSystem: '<S471>/ShiftBufferBack' */
  /* MinMax: '<S474>/Min' */
  if (rtu_bufferDepth <= localC->Width) {
    rtb_Min_aoon = rtu_bufferDepth;
  } else {
    rtb_Min_aoon = localC->Width;
  }

  /* End of MinMax: '<S474>/Min' */

  /* If: '<S474>/If' incorporates:
   *  Constant: '<S471>/Constant'
   *  RelationalOperator: '<S474>/Relational Operator'
   */
  if (2 <= rtb_Min_aoon) {
    /* Outputs for IfAction SubSystem: '<S474>/DoShift' incorporates:
     *  ActionPort: '<S477>/Action Port'
     */
    LIBINFO_WL_00_DoShift_g0d2(rtb_Min_aoon, 2, rty_commitAccumulation,
      rty_outAccumulatorBuffer);

    /* End of Outputs for SubSystem: '<S474>/DoShift' */
  } else {
    /* Outputs for IfAction SubSystem: '<S474>/DoNothing' incorporates:
     *  ActionPort: '<S476>/Action Port'
     */
    LIBINFO_WL_00_DoNothing_i3r3(rty_commitAccumulation,
      rty_outAccumulatorBuffer);

    /* End of Outputs for SubSystem: '<S474>/DoNothing' */
  }

  /* End of If: '<S474>/If' */
  /* End of Outputs for SubSystem: '<S471>/ShiftBufferBack' */
}

/* Function for Chart: '<S95>/RunState' */
static void LIBINFO_WL_00_RunState(BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B,
  D_Work_LIBINFO_WL_00 *LIBINFO_WL_00_DWork)
{
  /* During 'RunState': '<S144>:51' */
  if (LIBINFO_WL_00_DWork->is_RunState == LIBINFO_WL_00_IN_KeyOff) {
    /* During 'KeyOff': '<S144>:6' */
    switch (LIBINFO_WL_00_DWork->is_KeyOff) {
     case LIBINFO_WL_00_IN_ActiveDES:
      /* During 'ActiveDES': '<S144>:19' */
      if ((!LIBINFO_WL_00_DWork->EngineRunningRaw) ||
          (LIBINFO_WL_00_B->EngineSpeedUnknown != 0)) {
        /* Transition: '<S144>:20' */
        LIBINFO_WL_00_B->ST_KeyStatus_Commit = TRUE;
        LIBINFO_WL_00_DWork->is_KeyOff = LIBINFO_WL_00_IN_EngineOff_itep;

        /* Entry Internal 'EngineOff': '<S144>:16' */
        /* Transition: '<S144>:84' */
        LIBINFO_WL_00_B->keyswitchOverride = TRUE;
        LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;
        if (LIBINFO_WL_00_B->ST_KeyStatus_Commit) {
          /* Transition: '<S144>:89' */
          LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_00_IN_FinishCommit;
        } else {
          /* Transition: '<S144>:86' */
          /* Transition: '<S144>:91' */
          LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_0_IN_CommitEngineOff;

          /* Entry 'CommitEngineOff': '<S144>:90' */
          LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;

          /* Constant: '<S95>/Constant4' */
          LIBINFO_WL_00_B->ST_KeyStatus_ID = 27U;
          LIBINFO_WL_00_B->ST_KeyStatus_Commit = TRUE;
        }
      } else {
        if (LIBINFO_WL_00_B->DataTypeConversion) {
          /* Transition: '<S144>:58' */
          LIBINFO_WL_00_DWork->is_KeyOff = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
          LIBINFO_WL_00_DWork->is_RunState = LIBINFO_WL_00_IN_KeyOn;
          LIBINFO_WL_00_DWork->is_KeyOn = LIBINFO_WL_00_IN_EngineOn;

          /* Entry 'EngineOn': '<S144>:11' */
          LIBINFO_WL_00_B->ST_KeyStatus_State = 0U;
          LIBINFO_WL_00_B->keyswitchOverride = TRUE;
        }
      }
      break;

     case LIBINFO_WL_00_IN_EngineOff_itep:
      /* During 'EngineOff': '<S144>:16' */
      if (LIBINFO_WL_00_B->DataTypeConversion) {
        /* Transition: '<S144>:9' */
        LIBINFO_WL_00_B->ST_KeyStatus_Commit = TRUE;

        /* Exit Internal 'EngineOff': '<S144>:16' */
        if (LIBINFO_WL_00_DWork->is_EngineOff == LIBINFO_WL_0_IN_CommitEngineOff)
        {
          /* Constant: '<S95>/Constant4' */
          /* Exit 'CommitEngineOff': '<S144>:90' */
          LIBINFO_WL_00_B->ST_KeyStatus_ID = 27U;
          LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        } else {
          LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        }

        LIBINFO_WL_00_DWork->is_KeyOff = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        LIBINFO_WL_00_DWork->is_RunState = LIBINFO_WL_00_IN_KeyOn;
        LIBINFO_WL_00_DWork->is_KeyOn = LIBINFO_WL_00_IN_EngineOff;

        /* Entry 'EngineOff': '<S144>:13' */
        LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;
        LIBINFO_WL_00_B->keyswitchOverride = TRUE;
      } else if ((LIBINFO_WL_00_DWork->EngineRunningRaw) &&
                 (!(LIBINFO_WL_00_B->EngineSpeedUnknown != 0))) {
        /* Transition: '<S144>:52' */
        /* Exit Internal 'EngineOff': '<S144>:16' */
        if (LIBINFO_WL_00_DWork->is_EngineOff == LIBINFO_WL_0_IN_CommitEngineOff)
        {
          /* Constant: '<S95>/Constant4' */
          /* Exit 'CommitEngineOff': '<S144>:90' */
          LIBINFO_WL_00_B->ST_KeyStatus_ID = 27U;
          LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        } else {
          LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        }

        LIBINFO_WL_00_DWork->is_KeyOff = LIBINFO_WL_00_IN_TentativeDES;

        /* Entry 'TentativeDES': '<S144>:18' */
        LIBINFO_WL_00_B->keyswitchOverride = TRUE;
        LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;

        /* Constant: '<S95>/Constant3' */
        LIBINFO_WL_00_B->ST_KeyStatus_ID = 28U;
        LIBINFO_WL_00_B->ST_KeyStatus_Commit = FALSE;
        LIBINFO_WL_00_DWork->DESCounter = 1U;
      } else if (LIBINFO_WL_00_DWork->is_EngineOff ==
                 LIBINFO_WL_0_IN_CommitEngineOff) {
        /* During 'CommitEngineOff': '<S144>:90' */
        LIBINFO_WL_00_B->ST_KeyStatus_Commit = FALSE;
        LIBINFO_WL_00_B->keyswitchOverride = FALSE;
      } else {
        /* During 'FinishCommit': '<S144>:88' */
        /* Transition: '<S144>:92' */
        LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_0_IN_CommitEngineOff;

        /* Entry 'CommitEngineOff': '<S144>:90' */
        LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;

        /* Constant: '<S95>/Constant4' */
        LIBINFO_WL_00_B->ST_KeyStatus_ID = 27U;
        LIBINFO_WL_00_B->ST_KeyStatus_Commit = TRUE;
      }
      break;

     default:
      /* During 'TentativeDES': '<S144>:18' */
      if ((!LIBINFO_WL_00_DWork->EngineRunningRaw) ||
          (LIBINFO_WL_00_B->EngineSpeedUnknown != 0)) {
        /* Constant: '<S95>/Constant4' */
        /* Transition: '<S144>:22' */
        LIBINFO_WL_00_B->ST_KeyStatus_ID = 27U;
        LIBINFO_WL_00_DWork->is_KeyOff = LIBINFO_WL_00_IN_EngineOff_itep;

        /* Entry Internal 'EngineOff': '<S144>:16' */
        /* Transition: '<S144>:84' */
        LIBINFO_WL_00_B->keyswitchOverride = TRUE;
        LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;
        if (LIBINFO_WL_00_B->ST_KeyStatus_Commit) {
          /* Transition: '<S144>:89' */
          LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_00_IN_FinishCommit;
        } else {
          /* Transition: '<S144>:86' */
          /* Transition: '<S144>:91' */
          LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_0_IN_CommitEngineOff;

          /* Entry 'CommitEngineOff': '<S144>:90' */
          LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;
          LIBINFO_WL_00_B->ST_KeyStatus_Commit = TRUE;
        }
      } else if (LIBINFO_WL_00_DWork->DESCounter >= LIBINFO_WL_00_B->Divide) {
        /* Transition: '<S144>:24' */
        LIBINFO_WL_00_DWork->is_KeyOff = LIBINFO_WL_00_IN_ActiveDES;

        /* Entry 'ActiveDES': '<S144>:19' */
        LIBINFO_WL_00_B->keyswitchOverride = TRUE;
        LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;

        /* Constant: '<S95>/Constant3' */
        LIBINFO_WL_00_B->ST_KeyStatus_ID = 28U;
        LIBINFO_WL_00_B->ST_KeyStatus_Commit = FALSE;
      } else if (LIBINFO_WL_00_B->DataTypeConversion) {
        /* Transition: '<S144>:57' */
        LIBINFO_WL_00_DWork->is_KeyOff = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        LIBINFO_WL_00_DWork->is_RunState = LIBINFO_WL_00_IN_KeyOn;
        LIBINFO_WL_00_DWork->is_KeyOn = LIBINFO_WL_00_IN_EngineOn;

        /* Entry 'EngineOn': '<S144>:11' */
        LIBINFO_WL_00_B->ST_KeyStatus_State = 0U;
        LIBINFO_WL_00_B->keyswitchOverride = TRUE;
      } else {
        LIBINFO_WL_00_DWork->DESCounter++;
      }
      break;
    }
  } else {
    /* During 'KeyOn': '<S144>:5' */
    switch (LIBINFO_WL_00_DWork->is_KeyOn) {
     case LIBINFO_WL_00_IN_EngineOff:
      /* During 'EngineOff': '<S144>:13' */
      if (!LIBINFO_WL_00_B->DataTypeConversion) {
        /* Transition: '<S144>:55' */
        LIBINFO_WL_00_B->ST_KeyStatus_Commit = TRUE;

        /* Constant: '<S95>/Constant2' */
        /* Exit 'EngineOff': '<S144>:13' */
        LIBINFO_WL_00_B->ST_KeyStatus_ID = 26U;
        LIBINFO_WL_00_DWork->is_KeyOn = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        LIBINFO_WL_00_DWork->is_RunState = LIBINFO_WL_00_IN_KeyOff;
        LIBINFO_WL_00_DWork->is_KeyOff = LIBINFO_WL_00_IN_EngineOff_itep;

        /* Entry Internal 'EngineOff': '<S144>:16' */
        /* Transition: '<S144>:84' */
        LIBINFO_WL_00_B->keyswitchOverride = TRUE;
        LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;
        if (LIBINFO_WL_00_B->ST_KeyStatus_Commit) {
          /* Transition: '<S144>:89' */
          LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_00_IN_FinishCommit;
        } else {
          /* Transition: '<S144>:86' */
          /* Transition: '<S144>:91' */
          LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_0_IN_CommitEngineOff;

          /* Entry 'CommitEngineOff': '<S144>:90' */
          LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;

          /* Constant: '<S95>/Constant4' */
          LIBINFO_WL_00_B->ST_KeyStatus_ID = 27U;
          LIBINFO_WL_00_B->ST_KeyStatus_Commit = TRUE;
        }
      } else if (LIBINFO_WL_00_DWork->EngineRunningDebounced) {
        /* Constant: '<S95>/Constant2' */
        /* Transition: '<S144>:48' */
        /* Exit 'EngineOff': '<S144>:13' */
        LIBINFO_WL_00_B->ST_KeyStatus_ID = 26U;
        LIBINFO_WL_00_DWork->is_KeyOn = LIBINFO_WL_00_IN_EngineOn;

        /* Entry 'EngineOn': '<S144>:11' */
        LIBINFO_WL_00_B->ST_KeyStatus_State = 0U;
        LIBINFO_WL_00_B->keyswitchOverride = TRUE;
      } else {
        /* Constant: '<S95>/Constant2' */
        LIBINFO_WL_00_B->ST_KeyStatus_ID = 26U;
        LIBINFO_WL_00_B->ST_KeyStatus_Commit = FALSE;
      }
      break;

     case LIBINFO_WL_00_IN_EngineOn:
      /* During 'EngineOn': '<S144>:11' */
      if (!LIBINFO_WL_00_B->DataTypeConversion) {
        /* Transition: '<S144>:7' */
        /* Exit 'EngineOn': '<S144>:11' */
        LIBINFO_WL_00_DWork->is_KeyOn = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        LIBINFO_WL_00_DWork->is_RunState = LIBINFO_WL_00_IN_KeyOff;
        LIBINFO_WL_00_DWork->is_KeyOff = LIBINFO_WL_00_IN_TentativeDES;

        /* Entry 'TentativeDES': '<S144>:18' */
        LIBINFO_WL_00_B->keyswitchOverride = TRUE;
        LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;

        /* Constant: '<S95>/Constant3' */
        LIBINFO_WL_00_B->ST_KeyStatus_ID = 28U;
        LIBINFO_WL_00_B->ST_KeyStatus_Commit = FALSE;
        LIBINFO_WL_00_DWork->DESCounter = 1U;
      } else if (!LIBINFO_WL_00_DWork->EngineRunningRaw) {
        /* Transition: '<S144>:15' */
        /* Exit 'EngineOn': '<S144>:11' */
        LIBINFO_WL_00_DWork->is_KeyOn = LIBINFO_W_IN_TentativeEngineOff;

        /* Entry 'TentativeEngineOff': '<S144>:14' */
        LIBINFO_WL_00_B->keyswitchOverride = TRUE;
        LIBINFO_WL_00_B->ST_KeyStatus_State = 1U;

        /* Constant: '<S95>/Constant2' */
        LIBINFO_WL_00_B->ST_KeyStatus_ID = 26U;
        LIBINFO_WL_00_B->ST_KeyStatus_Commit = FALSE;
      } else {
        /* Constant: '<S95>/Constant2' */
        LIBINFO_WL_00_B->ST_KeyStatus_ID = 26U;
        LIBINFO_WL_00_B->ST_KeyStatus_Commit = FALSE;
      }
      break;

     default:
      /* During 'TentativeEngineOff': '<S144>:14' */
      if (!LIBINFO_WL_00_B->DataTypeConversion) {
        /* Constant: '<S95>/Constant4' */
        /* Transition: '<S144>:54' */
        LIBINFO_WL_00_B->ST_KeyStatus_ID = 27U;
        LIBINFO_WL_00_DWork->is_KeyOn = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        LIBINFO_WL_00_DWork->is_RunState = LIBINFO_WL_00_IN_KeyOff;
        LIBINFO_WL_00_DWork->is_KeyOff = LIBINFO_WL_00_IN_EngineOff_itep;

        /* Entry Internal 'EngineOff': '<S144>:16' */
        /* Transition: '<S144>:84' */
        LIBINFO_WL_00_B->keyswitchOverride = TRUE;
        LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;
        if (LIBINFO_WL_00_B->ST_KeyStatus_Commit) {
          /* Transition: '<S144>:89' */
          LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_00_IN_FinishCommit;
        } else {
          /* Transition: '<S144>:86' */
          /* Transition: '<S144>:91' */
          LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_0_IN_CommitEngineOff;

          /* Entry 'CommitEngineOff': '<S144>:90' */
          LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;
          LIBINFO_WL_00_B->ST_KeyStatus_Commit = TRUE;
        }
      } else if (LIBINFO_WL_00_DWork->EngineRunningRaw) {
        /* Transition: '<S144>:50' */
        LIBINFO_WL_00_DWork->is_KeyOn = LIBINFO_WL_00_IN_EngineOn;

        /* Entry 'EngineOn': '<S144>:11' */
        LIBINFO_WL_00_B->ST_KeyStatus_State = 0U;
        LIBINFO_WL_00_B->keyswitchOverride = TRUE;
      } else {
        if (!LIBINFO_WL_00_DWork->EngineRunningDebounced) {
          /* Transition: '<S144>:49' */
          LIBINFO_WL_00_DWork->is_KeyOn = LIBINFO_WL_00_IN_EngineOff;

          /* Entry 'EngineOff': '<S144>:13' */
          LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;
          LIBINFO_WL_00_B->keyswitchOverride = TRUE;
        }
      }
      break;
    }
  }
}

/* Function for Chart: '<S93>/Classifier' */
static boolean_T LIBINFO_WL_00_GroundSpeedExit(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  boolean_T result;

  /* Constant: '<S93>/Constant20' incorporates:
   *  Constant: '<S93>/Constant19'
   */
  /* Graphical Function 'GroundSpeedExit': '<S106>:20' */
  /* Transition: '<S106>:22' */
  if ((LIBINFO_WL_00_B->GroundSpeed_iutz <
       LIBINFO_WL_00_M->
       LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_GroundSpeedMax)
      && (LIBINFO_WL_00_B->GroundSpeed_iutz >=
          LIBINFO_WL_00_M->
          LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_GroundSpeedMin))
  {
    /* Transition: '<S106>:37' */
    /* Transition: '<S106>:41' */
    result = FALSE;

    /* Transition: '<S106>:42' */
  } else {
    /* Transition: '<S106>:39' */
    result = TRUE;
  }

  /* End of Constant: '<S93>/Constant20' */
  return result;
}

/* Function for Chart: '<S93>/Classifier' */
static boolean_T LIBINFO_WL_00_RackExit(BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  boolean_T result;

  /* Graphical Function 'RackExit': '<S106>:64' */
  /* Transition: '<S106>:65' */
  if (((LIBINFO_WL_00_B->DesiredGear <= 0) && (LIBINFO_WL_00_B->IsFullRack_ou1b))
      && (LIBINFO_WL_00_B->TiltValveCmd_bbs3 == 0)) {
    /* Transition: '<S106>:68' */
    /* Transition: '<S106>:70' */
    result = TRUE;
  } else {
    /* Transition: '<S106>:73' */
    result = FALSE;

    /* Transition: '<S106>:72' */
  }

  return result;
}

/* Function for Chart: '<S93>/MaterialEngagementDetection' */
static boolean_T LIBINFO_WL_00_GroundSpeedRemain(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  boolean_T result;

  /* Constant: '<S93>/Constant7' incorporates:
   *  Constant: '<S93>/Constant6'
   */
  /* Graphical Function 'GroundSpeedRemain': '<S108>:34' */
  /* Transition: '<S108>:104' */
  if ((LIBINFO_WL_00_B->GroundSpeed_iutz <
       LIBINFO_WL_00_M->
       LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_GroundSpeedMax)
      && (LIBINFO_WL_00_B->GroundSpeed_iutz >=
          LIBINFO_WL_00_M->
          LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_GroundSpeedMin))
  {
    /* Transition: '<S108>:107' */
    /* Transition: '<S108>:111' */
    result = TRUE;

    /* Transition: '<S108>:112' */
  } else {
    /* Transition: '<S108>:109' */
    result = FALSE;
  }

  /* End of Constant: '<S93>/Constant7' */
  return result;
}

/* Function for Chart: '<S93>/MaterialEngagementDetection' */
static boolean_T LIBINF_PayloadDerivativeTrigger(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  boolean_T result;

  /* Constant: '<S93>/Constant23' */
  /* Graphical Function 'PayloadDerivativeTrigger': '<S108>:264' */
  /* Transition: '<S108>:266' */
  if ((LIBINFO_WL_00_B->PayloadRatioDerivative_f44j >=
       LIBINFO_WL_00_M->
       LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_PyldRtioDrvtHighThrshld)
      && (!LIBINFO_WL_00_B->Merge1_mlst)) {
    /* Transition: '<S108>:269' */
    /* Transition: '<S108>:273' */
    result = TRUE;
  } else {
    /* Transition: '<S108>:271' */
    result = FALSE;

    /* Transition: '<S108>:274' */
  }

  /* End of Constant: '<S93>/Constant23' */
  return result;
}

/* Function for Chart: '<S93>/MaterialEngagementDetection' */
static boolean_T LIBINFO_WL_0_ExternalForceReset(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  boolean_T result;

  /* Constant: '<S93>/Constant11' */
  /* Graphical Function 'ExternalForceReset': '<S108>:183' */
  /* Transition: '<S108>:185' */
  if (((LIBINFO_WL_00_B->ExternalForceNormalized_p2pg <
        LIBINFO_WL_00_M->
        LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_ExtFrceNrmlzdLowThrshld)
       || (LIBINFO_WL_00_B->ExternalForceNormalizedDelta < 0)) &&
      (!LIBINFO_WL_00_B->DataTypeConversion2_o1n1)) {
    /* Transition: '<S108>:188' */
    /* Transition: '<S108>:190' */
    result = TRUE;

    /* Transition: '<S108>:192' */
  } else {
    /* Transition: '<S108>:193' */
    result = FALSE;
  }

  /* End of Constant: '<S93>/Constant11' */
  return result;
}

/* Function for Chart: '<S93>/MaterialEngagementDetection' */
static boolean_T LIBINFO_WL_00_PayloadConfirm(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  boolean_T result;

  /* Constant: '<S93>/Constant4' */
  /* Graphical Function 'PayloadConfirm': '<S108>:136' */
  /* Transition: '<S108>:138' */
  if ((LIBINFO_WL_00_B->PayloadRatio >=
       LIBINFO_WL_00_M->
       LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_PayloadRatioHighThrshld)
      && (!LIBINFO_WL_00_B->Merge1_mlst)) {
    /* Transition: '<S108>:141' */
    /* Transition: '<S108>:145' */
    result = TRUE;

    /* Transition: '<S108>:146' */
  } else {
    /* Transition: '<S108>:143' */
    result = FALSE;
  }

  /* End of Constant: '<S93>/Constant4' */
  return result;
}

/* Function for Chart: '<S93>/MaterialEngagementDetection' */
static boolean_T LIBINFO__PayloadDerivativeReset(BlockIO_LIBINFO_WL_00
  *LIBINFO_WL_00_B)
{
  boolean_T result;

  /* Graphical Function 'PayloadDerivativeReset': '<S108>:276' */
  /* Transition: '<S108>:278' */
  if ((LIBINFO_WL_00_B->PayloadRatioDerivative_f44j < 0.0F) &&
      (!LIBINFO_WL_00_B->Merge1_mlst)) {
    /* Transition: '<S108>:282' */
    /* Transition: '<S108>:286' */
    result = TRUE;
  } else {
    /* Transition: '<S108>:284' */
    result = FALSE;

    /* Transition: '<S108>:287' */
  }

  return result;
}

/* Function for Chart: '<S93>/MaterialEngagementDetection' */
static boolean_T LIBINFO_WL_00_LiftAngleTrigger(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  boolean_T result;

  /* Constant: '<S93>/Constant2' */
  /* Graphical Function 'LiftAngleTrigger': '<S108>:84' */
  /* Transition: '<S108>:86' */
  if (LIBINFO_WL_00_B->LiftAngle_bgyb <
      LIBINFO_WL_00_M->
      LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_LiftAngleMaxStart)
  {
    /* Transition: '<S108>:89' */
    /* Transition: '<S108>:91' */
    result = TRUE;

    /* Transition: '<S108>:93' */
  } else {
    /* Transition: '<S108>:94' */
    result = FALSE;
  }

  /* End of Constant: '<S93>/Constant2' */
  return result;
}

/* Function for Chart: '<S93>/MaterialEngagementDetection' */
static boolean_T LIBINFO_WL_0_BucketAngleTrigger(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  boolean_T result;
  int32_t tmp;

  /* Graphical Function 'BucketAngleTrigger': '<S108>:73' */
  /* Transition: '<S108>:75' */
  if (LIBINFO_WL_00_B->BucketAngle_bg5r < 0) {
    tmp = -LIBINFO_WL_00_B->BucketAngle_bg5r;
  } else {
    tmp = LIBINFO_WL_00_B->BucketAngle_bg5r;
  }

  /* Constant: '<S93>/Constant3' */
  if (((int16_t)tmp) <
      LIBINFO_WL_00_M->
      LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_BucketAngleMaxStart)
  {
    /* Transition: '<S108>:78' */
    /* Transition: '<S108>:82' */
    result = TRUE;

    /* Transition: '<S108>:83' */
  } else {
    /* Transition: '<S108>:80' */
    result = FALSE;
  }

  /* End of Constant: '<S93>/Constant3' */
  return result;
}

/* Function for Chart: '<S93>/MaterialEngagementDetection' */
static boolean_T LIBINFO_WL_0_GroundSpeedTrigger(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  boolean_T result;

  /* Constant: '<S93>/Constant5' */
  /* Graphical Function 'GroundSpeedTrigger': '<S108>:32' */
  /* Transition: '<S108>:95' */
  if ((LIBINFO_WL_00_GroundSpeedRemain(LIBINFO_WL_00_M, LIBINFO_WL_00_B)) &&
      (LIBINFO_WL_00_B->GroundSpeed_iutz >=
       LIBINFO_WL_00_M->
       LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_GroundSpeedTriggerMin))
  {
    /* Transition: '<S108>:98' */
    /* Transition: '<S108>:102' */
    result = TRUE;

    /* Transition: '<S108>:103' */
  } else {
    /* Transition: '<S108>:100' */
    result = FALSE;
  }

  /* End of Constant: '<S93>/Constant5' */
  return result;
}

/* Function for Chart: '<S93>/MaterialEngagementDetection' */
static boolean_T LIBINFO_WL_00_DecelTrigger(D_Work_LIBINFO_WL_00
  *LIBINFO_WL_00_DWork)
{
  /* Graphical Function 'DecelTrigger': '<S108>:35' */
  /* Transition: '<S108>:38' */
  return LIBINFO_WL_00_DWork->Decelerating;
}

/* Function for Chart: '<S93>/MaterialEngagementDetection' */
static boolean_T LIBINFO_WL_ExternalForceTrigger(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B, D_Work_LIBINFO_WL_00
  *LIBINFO_WL_00_DWork)
{
  boolean_T result;

  /* Constant: '<S93>/Constant10' incorporates:
   *  Constant: '<S93>/Constant11'
   */
  /* Graphical Function 'ExternalForceTrigger': '<S108>:171' */
  /* Transition: '<S108>:173' */
  if ((((LIBINFO_WL_00_B->ExternalForceNormalized_p2pg >=
         LIBINFO_WL_00_M->
         LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_ExtFrceNrmlzdHghThrshld)
        && (LIBINFO_WL_00_B->ExternalForceNormalizedDelta >=
            LIBINFO_WL_00_M->
            LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_ExtFrceNrmlzdLowThrshld))
       && (!LIBINFO_WL_00_B->DataTypeConversion2_o1n1)) &&
      (!LIBINFO_WL_00_DWork->GearTriggerInhibit)) {
    /* Transition: '<S108>:176' */
    /* Transition: '<S108>:180' */
    result = TRUE;

    /* Transition: '<S108>:182' */
  } else {
    /* Transition: '<S108>:178' */
    result = FALSE;
  }

  /* End of Constant: '<S93>/Constant10' */
  return result;
}

/* Function for Chart: '<S93>/MaterialEngagementDetection' */
static boolean_T PayloadDerivativeOverrideTrigge(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  boolean_T result;

  /* Constant: '<S93>/Constant24' */
  /* Graphical Function 'PayloadDerivativeOverrideTrigger': '<S108>:327' */
  /* Transition: '<S108>:329' */
  if ((LIBINFO_WL_00_B->PayloadRatioDerivative_f44j >=
       LIBINFO_WL_00_M->
       LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_PyldRtioDrvtOvridTrshld)
      && (!LIBINFO_WL_00_B->Merge1_mlst)) {
    /* Transition: '<S108>:332' */
    /* Transition: '<S108>:336' */
    result = TRUE;
  } else {
    /* Transition: '<S108>:334' */
    result = FALSE;

    /* Transition: '<S108>:337' */
  }

  /* End of Constant: '<S93>/Constant24' */
  return result;
}

/* Function for Chart: '<S96>/Loaded' */
static void LIBINFO_WL_00_DecLoadedCounter(D_Work_LIBINFO_WL_00
  *LIBINFO_WL_00_DWork)
{
  /* Graphical Function 'DecLoadedCounter': '<S147>:272' */
  /* Transition: '<S147>:277' */
  if (LIBINFO_WL_00_DWork->loadedCounter > 0) {
    /* Transition: '<S147>:278' */
    /* Transition: '<S147>:280' */
    LIBINFO_WL_00_DWork->loadedCounter--;
  } else {
    /* Transition: '<S147>:279' */
    /* Transition: '<S147>:281' */
  }
}

/* Function for Chart: '<S96>/Loaded' */
static void LIBINFO_WL_0_IncUnloadedCounter(BlockIO_LIBINFO_WL_00
  *LIBINFO_WL_00_B, D_Work_LIBINFO_WL_00 *LIBINFO_WL_00_DWork)
{
  /* Graphical Function 'IncUnloadedCounter': '<S147>:262' */
  /* Transition: '<S147>:267' */
  if (LIBINFO_WL_00_DWork->unloadedCounter < LIBINFO_WL_00_B->Divide1_bcq5) {
    /* Transition: '<S147>:268' */
    /* Transition: '<S147>:270' */
    LIBINFO_WL_00_DWork->unloadedCounter++;
  } else {
    /* Transition: '<S147>:269' */
    /* Transition: '<S147>:271' */
  }
}

/* Function for Chart: '<S96>/Loaded' */
static void LIBINFO_WL_00_IncLoadedCounter(BlockIO_LIBINFO_WL_00
  *LIBINFO_WL_00_B, D_Work_LIBINFO_WL_00 *LIBINFO_WL_00_DWork)
{
  /* Graphical Function 'IncLoadedCounter': '<S147>:251' */
  /* Transition: '<S147>:252' */
  if (LIBINFO_WL_00_DWork->loadedCounter < LIBINFO_WL_00_B->Divide1_bcq5) {
    /* Transition: '<S147>:257' */
    /* Transition: '<S147>:261' */
    LIBINFO_WL_00_DWork->loadedCounter++;
  } else {
    /* Transition: '<S147>:258' */
    /* Transition: '<S147>:260' */
  }
}

/* Function for Chart: '<S96>/Loaded' */
static void LIBINFO_WL_0_DecUnloadedCounter(D_Work_LIBINFO_WL_00
  *LIBINFO_WL_00_DWork)
{
  /* Graphical Function 'DecUnloadedCounter': '<S147>:282' */
  /* Transition: '<S147>:287' */
  if (LIBINFO_WL_00_DWork->unloadedCounter > 0) {
    /* Transition: '<S147>:288' */
    /* Transition: '<S147>:290' */
    LIBINFO_WL_00_DWork->unloadedCounter--;
  } else {
    /* Transition: '<S147>:289' */
    /* Transition: '<S147>:291' */
  }
}

/* Function for Chart: '<S94>/DumpState' */
static boolean_T LIBINFO_WL_00_DumpThresholdMet(BlockIO_LIBINFO_WL_00
  *LIBINFO_WL_00_B)
{
  boolean_T result;

  /* Graphical Function 'DumpThresholdMet': '<S137>:9' */
  /* Transition: '<S137>:11' */
  if (((LIBINFO_WL_00_B->BucketAngle_bg5r <= LIBINFO_WL_00_B->Switch_iyvp) ||
       (LIBINFO_WL_00_B->IsFullDump)) && (LIBINFO_WL_00_B->dumpMovementConfirmed))
  {
    /* Transition: '<S137>:63' */
    /* Transition: '<S137>:67' */
    result = TRUE;

    /* Transition: '<S137>:68' */
  } else {
    /* Transition: '<S137>:65' */
    result = FALSE;
  }

  return result;
}

/* Function for Chart: '<S94>/DumpState' */
static boolean_T LIBINFO_WL_00_GroundSpeedSlow(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  boolean_T result;
  int32_t tmp;

  /* Graphical Function 'GroundSpeedSlow': '<S137>:13' */
  /* Transition: '<S137>:15' */
  if (LIBINFO_WL_00_B->GroundSpeed_iutz < 0) {
    tmp = -LIBINFO_WL_00_B->GroundSpeed_iutz;
  } else {
    tmp = LIBINFO_WL_00_B->GroundSpeed_iutz;
  }

  /* Constant: '<S94>/Constant' */
  if (((int16_t)tmp) <
      LIBINFO_WL_00_M->
      LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dump_GroundSpeedThreshold)
  {
    /* Transition: '<S137>:18' */
    /* Transition: '<S137>:22' */
    result = TRUE;

    /* Transition: '<S137>:23' */
  } else {
    /* Transition: '<S137>:20' */
    result = FALSE;
  }

  /* End of Constant: '<S94>/Constant' */
  return result;
}

/* Function for Chart: '<S94>/DumpState' */
static boolean_T LIBINFO_WL_00_RackThresholdMet(BlockIO_LIBINFO_WL_00
  *LIBINFO_WL_00_B)
{
  boolean_T result;

  /* Graphical Function 'RackThresholdMet': '<S137>:45' */
  /* Transition: '<S137>:53' */
  if ((!LIBINFO_WL_00_B->IsFullDump) && (LIBINFO_WL_00_B->rackMovementConfirmed))
  {
    /* Transition: '<S137>:56' */
    /* Transition: '<S137>:60' */
    result = TRUE;

    /* Transition: '<S137>:61' */
  } else {
    /* Transition: '<S137>:58' */
    result = FALSE;
  }

  return result;
}

/* Function for Chart: '<S94>/DumpState' */
static boolean_T LIBINFO_W_OperatorCommandedDump(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  boolean_T result;

  /* Constant: '<S94>/Constant1' */
  /* Graphical Function 'OperatorCommandedDump': '<S137>:96' */
  /* Transition: '<S137>:98' */
  if ((LIBINFO_WL_00_B->TiltLeverCmd <=
       (-LIBINFO_WL_00_M->
        LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dump_LeverDeadband))
      && (LIBINFO_WL_00_B->TiltValveCmd_bbs3 < 0)) {
    /* Transition: '<S137>:101' */
    /* Transition: '<S137>:105' */
    result = TRUE;

    /* Transition: '<S137>:106' */
  } else {
    /* Transition: '<S137>:103' */
    result = FALSE;
  }

  /* End of Constant: '<S94>/Constant1' */
  return result;
}

/* Function for Chart: '<S98>/LoadedState' */
static void LIBINFO_WL_00_TryToCommit_lksz(BlockIO_LIBINFO_WL_00
  *LIBINFO_WL_00_B, D_Work_LIBINFO_WL_00 *LIBINFO_WL_00_DWork)
{
  /* Graphical Function 'TryToCommit': '<S166>:68' */
  /* Transition: '<S166>:90' */
  if (LIBINFO_WL_00_DWork->segmentTimeCounter >= LIBINFO_WL_00_B->Divide2_dnc1)
  {
    /* Transition: '<S166>:93' */
    /* Transition: '<S166>:97' */
    LIBINFO_WL_00_B->ST_Travel_Commit = TRUE;

    /* Transition: '<S166>:98' */
    LIBINFO_WL_00_DWork->segmentTimeCounter = 0U;
  } else {
    /* Transition: '<S166>:95' */
    LIBINFO_WL_00_DWork->segmentTimeCounter = 0U;
  }
}

/* Function for Chart: '<S98>/TravellingState' */
static void LIBINFO_WL_00_Main(BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B,
  D_Work_LIBINFO_WL_00 *LIBINFO_WL_00_DWork)
{
  /* During 'Main': '<S168>:42' */
  switch (LIBINFO_WL_00_DWork->is_Main_ko0u) {
   case LIBINFO_WL_00_IN_NotTravelling:
    /* During 'NotTravelling': '<S168>:1' */
    /*  Started moving right away  */
    if ((LIBINFO_WL_00_B->RelationalOperator) && (LIBINFO_WL_00_B->DesiredGear
         != 0)) {
      /* Transition: '<S168>:7' */
      LIBINFO_WL_00_DWork->tentativeCounter = 0U;

      /* Transition: '<S168>:62' */
      /* Exit Internal 'NotTravelling': '<S168>:1' */
      LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
      LIBINFO_WL_00_DWork->is_Main_ko0u = LIBINFO_WL_00_IN_Travelling;

      /* Entry Internal 'Travelling': '<S168>:4' */
      /* Transition: '<S168>:152' */
      /*  Hold off for at least the min time  */
      if (LIBINFO_WL_00_DWork->tentativeCounter < LIBINFO_WL_00_B->Divide2_dnc1)
      {
        /* Transition: '<S168>:156' */
        LIBINFO_WL_00_DWork->is_Travelling = LIBINFO_WL_00_IN_Hold;

        /* Entry 'Hold': '<S168>:154' */
        LIBINFO_WL_00_B->ST_Travel_State = 1U;
      } else {
        /* Transition: '<S168>:159' */
        /* Transition: '<S168>:160' */
        LIBINFO_WL_00_DWork->is_Travelling = LIBINFO_WL_00_IN_Confirm;

        /* Entry 'Confirm': '<S168>:155' */
        LIBINFO_WL_00_B->ST_Travel_State = 2U;
      }
    } else {
      switch (LIBINFO_WL_00_DWork->is_NotTravelling) {
       case LIBINFO_WL_00_IN_ForwardInit:
        /* During 'ForwardInit': '<S168>:64' */
        if (LIBINFO_WL_00_B->DesiredGear <= 0) {
          /* Transition: '<S168>:66' */
          /* Transition: '<S168>:72' */
          /* Transition: '<S168>:78' */
          /*  Just went into gear  */
          if (LIBINFO_WL_00_B->DesiredGear != 0) {
            /* Transition: '<S168>:13' */
            LIBINFO_WL_00_DWork->tentativeCounter = 0U;
            LIBINFO_WL_00_DWork->is_NotTravelling =
              LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
            LIBINFO_WL_00_DWork->is_Main_ko0u = LIBINF_IN_TentativelyTravelling;

            /* Entry 'TentativelyTravelling': '<S168>:2' */
            LIBINFO_WL_00_B->ST_Travel_State = 1U;

            /* Entry Internal 'TentativelyTravelling': '<S168>:2' */
            /* Transition: '<S168>:90' */
            if (LIBINFO_WL_00_B->DesiredGear > 0) {
              /* Transition: '<S168>:91' */
              LIBINFO_WL_00_DWork->is_TentativelyTravelling =
                LIBINFO_WL_00_IN_Forward;
            } else {
              /* Transition: '<S168>:94' */
              /* Transition: '<S168>:93' */
              LIBINFO_WL_00_DWork->is_TentativelyTravelling =
                LIBINFO_WL_00_IN_Reverse_inos;
            }
          } else {
            /* Transition: '<S168>:81' */
            /* Transition: '<S168>:84' */
            /* Transition: '<S168>:85' */
            LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_Neutral;
          }
        }
        break;

       case LIBINFO_WL_00_IN_Neutral:
        /* During 'Neutral': '<S168>:10' */
        /* Transition: '<S168>:79' */
        /*  Just went into gear  */
        if (LIBINFO_WL_00_B->DesiredGear != 0) {
          /* Transition: '<S168>:13' */
          LIBINFO_WL_00_DWork->tentativeCounter = 0U;
          LIBINFO_WL_00_DWork->is_NotTravelling =
            LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
          LIBINFO_WL_00_DWork->is_Main_ko0u = LIBINF_IN_TentativelyTravelling;

          /* Entry 'TentativelyTravelling': '<S168>:2' */
          LIBINFO_WL_00_B->ST_Travel_State = 1U;

          /* Entry Internal 'TentativelyTravelling': '<S168>:2' */
          /* Transition: '<S168>:90' */
          if (LIBINFO_WL_00_B->DesiredGear > 0) {
            /* Transition: '<S168>:91' */
            LIBINFO_WL_00_DWork->is_TentativelyTravelling =
              LIBINFO_WL_00_IN_Forward;
          } else {
            /* Transition: '<S168>:94' */
            /* Transition: '<S168>:93' */
            LIBINFO_WL_00_DWork->is_TentativelyTravelling =
              LIBINFO_WL_00_IN_Reverse_inos;
          }
        } else {
          /* Transition: '<S168>:81' */
          /* Transition: '<S168>:84' */
          /* Transition: '<S168>:85' */
          LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_Neutral;
        }
        break;

       default:
        /* During 'ReverseInit': '<S168>:11' */
        if (LIBINFO_WL_00_B->DesiredGear >= 0) {
          /* Transition: '<S168>:75' */
          /* Transition: '<S168>:78' */
          /*  Just went into gear  */
          if (LIBINFO_WL_00_B->DesiredGear != 0) {
            /* Transition: '<S168>:13' */
            LIBINFO_WL_00_DWork->tentativeCounter = 0U;
            LIBINFO_WL_00_DWork->is_NotTravelling =
              LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
            LIBINFO_WL_00_DWork->is_Main_ko0u = LIBINF_IN_TentativelyTravelling;

            /* Entry 'TentativelyTravelling': '<S168>:2' */
            LIBINFO_WL_00_B->ST_Travel_State = 1U;

            /* Entry Internal 'TentativelyTravelling': '<S168>:2' */
            /* Transition: '<S168>:90' */
            if (LIBINFO_WL_00_B->DesiredGear > 0) {
              /* Transition: '<S168>:91' */
              LIBINFO_WL_00_DWork->is_TentativelyTravelling =
                LIBINFO_WL_00_IN_Forward;
            } else {
              /* Transition: '<S168>:94' */
              /* Transition: '<S168>:93' */
              LIBINFO_WL_00_DWork->is_TentativelyTravelling =
                LIBINFO_WL_00_IN_Reverse_inos;
            }
          } else {
            /* Transition: '<S168>:81' */
            /* Transition: '<S168>:84' */
            /* Transition: '<S168>:85' */
            LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_Neutral;
          }
        }
        break;
      }
    }
    break;

   case LIB_IN_TentativelyNotTravelling:
    /* During 'TentativelyNotTravelling': '<S168>:3' */
    /*  Started moving again  */
    if (LIBINFO_WL_00_B->RelationalOperator) {
      /* Transition: '<S168>:34' */
      /* Exit Internal 'TentativelyNotTravelling': '<S168>:3' */
      LIBINFO_WL_00_DWork->is_TentativelyNotTravelling =
        LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
      LIBINFO_WL_00_DWork->is_Main_ko0u = LIBINFO_WL_00_IN_Travelling;

      /* Entry Internal 'Travelling': '<S168>:4' */
      /* Transition: '<S168>:152' */
      /*  Hold off for at least the min time  */
      if (LIBINFO_WL_00_DWork->tentativeCounter < LIBINFO_WL_00_B->Divide2_dnc1)
      {
        /* Transition: '<S168>:156' */
        LIBINFO_WL_00_DWork->is_Travelling = LIBINFO_WL_00_IN_Hold;

        /* Entry 'Hold': '<S168>:154' */
        LIBINFO_WL_00_B->ST_Travel_State = 1U;
      } else {
        /* Transition: '<S168>:159' */
        /* Transition: '<S168>:160' */
        LIBINFO_WL_00_DWork->is_Travelling = LIBINFO_WL_00_IN_Confirm;

        /* Entry 'Confirm': '<S168>:155' */
        LIBINFO_WL_00_B->ST_Travel_State = 2U;
      }
    } else if ((LIBINFO_WL_00_DWork->notTravellingCounter >=
                LIBINFO_WL_00_B->Divide_h3xr) ||
               (LIBINFO_WL_00_B->ST_Travel_Commit)) {
      /* Transition: '<S168>:37' */
      /* Exit Internal 'TentativelyNotTravelling': '<S168>:3' */
      LIBINFO_WL_00_DWork->is_TentativelyNotTravelling =
        LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
      LIBINFO_WL_00_DWork->is_Main_ko0u = LIBINFO_WL_00_IN_NotTravelling;

      /* Entry 'NotTravelling': '<S168>:1' */
      LIBINFO_WL_00_B->ST_Travel_State = 0U;
      LIBINFO_WL_00_DWork->tentativeCounter = 0U;

      /* Entry Internal 'NotTravelling': '<S168>:1' */
      /* Transition: '<S168>:17' */
      if (LIBINFO_WL_00_B->DesiredGear == 0) {
        /* Transition: '<S168>:15' */
        LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_Neutral;
      } else {
        /* Transition: '<S168>:60' */
        if (LIBINFO_WL_00_B->DesiredGear < 0) {
          /* Transition: '<S168>:69' */
          LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_ReverseInit;
        } else {
          /* Transition: '<S168>:68' */
          /* Transition: '<S168>:16' */
          LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_ForwardInit;
        }
      }
    } else {
      switch (LIBINFO_WL_00_DWork->is_TentativelyNotTravelling) {
       case LIBINFO_WL_00_IN_Forward:
        /* During 'Forward': '<S168>:101' */
        if (LIBINFO_WL_00_B->DesiredGear < 0) {
          /* Transition: '<S168>:117' */
          LIBINFO_WL_00_DWork->is_TentativelyNotTravelling =
            LIBINFO_WL_00_IN_Reverse;

          /* Entry 'Reverse': '<S168>:100' */
          LIBINFO_WL_00_DWork->notTravellingCounter = 1U;
        } else if (LIBINFO_WL_00_B->DesiredGear == 0) {
          /* Transition: '<S168>:113' */
          /* Transition: '<S168>:120' */
          /* Transition: '<S168>:130' */
          /* Transition: '<S168>:132' */
          LIBINFO_WL_00_DWork->is_TentativelyNotTravelling =
            LIBINFO_WL_00_IN_Neutral;

          /* Entry 'Neutral': '<S168>:99' */
          LIBINFO_WL_00_DWork->notTravellingCounter++;
        } else {
          LIBINFO_WL_00_DWork->notTravellingCounter++;
        }
        break;

       case LIBINFO_WL_00_IN_Neutral:
        /* During 'Neutral': '<S168>:99' */
        if (LIBINFO_WL_00_B->DesiredGear != 0) {
          /* Transition: '<S168>:124' */
          /* Transition: '<S168>:126' */
          if (LIBINFO_WL_00_B->DesiredGear < 0) {
            /* Transition: '<S168>:107' */
            LIBINFO_WL_00_DWork->is_TentativelyNotTravelling =
              LIBINFO_WL_00_IN_Reverse;

            /* Entry 'Reverse': '<S168>:100' */
            LIBINFO_WL_00_DWork->notTravellingCounter = 1U;
          } else {
            /* Transition: '<S168>:109' */
            /* Transition: '<S168>:110' */
            LIBINFO_WL_00_DWork->is_TentativelyNotTravelling =
              LIBINFO_WL_00_IN_Forward;

            /* Entry 'Forward': '<S168>:101' */
            LIBINFO_WL_00_DWork->notTravellingCounter = 1U;
          }
        } else {
          LIBINFO_WL_00_DWork->notTravellingCounter++;
        }
        break;

       default:
        /* During 'Reverse': '<S168>:100' */
        if (LIBINFO_WL_00_B->DesiredGear > 0) {
          /* Transition: '<S168>:116' */
          LIBINFO_WL_00_DWork->is_TentativelyNotTravelling =
            LIBINFO_WL_00_IN_Forward;

          /* Entry 'Forward': '<S168>:101' */
          LIBINFO_WL_00_DWork->notTravellingCounter = 1U;
        } else if (LIBINFO_WL_00_B->DesiredGear == 0) {
          /* Transition: '<S168>:119' */
          /* Transition: '<S168>:130' */
          /* Transition: '<S168>:132' */
          LIBINFO_WL_00_DWork->is_TentativelyNotTravelling =
            LIBINFO_WL_00_IN_Neutral;

          /* Entry 'Neutral': '<S168>:99' */
          LIBINFO_WL_00_DWork->notTravellingCounter++;
        } else {
          LIBINFO_WL_00_DWork->notTravellingCounter++;
        }
        break;
      }
    }
    break;

   case LIBINF_IN_TentativelyTravelling:
    /* During 'TentativelyTravelling': '<S168>:2' */
    /*  Back to neutral prior to moving  */
    if ((LIBINFO_WL_00_B->DesiredGear == 0) ||
        (LIBINFO_WL_00_DWork->tentativeCounter >= LIBINFO_WL_00_B->Divide1_gfci))
    {
      /* Transition: '<S168>:32' */
      /* Exit Internal 'TentativelyTravelling': '<S168>:2' */
      LIBINFO_WL_00_DWork->is_TentativelyTravelling =
        LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
      LIBINFO_WL_00_DWork->is_Main_ko0u = LIBINFO_WL_00_IN_NotTravelling;

      /* Entry 'NotTravelling': '<S168>:1' */
      LIBINFO_WL_00_B->ST_Travel_State = 0U;
      LIBINFO_WL_00_DWork->tentativeCounter = 0U;

      /* Entry Internal 'NotTravelling': '<S168>:1' */
      /* Transition: '<S168>:17' */
      if (LIBINFO_WL_00_B->DesiredGear == 0) {
        /* Transition: '<S168>:15' */
        LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_Neutral;
      } else {
        /* Transition: '<S168>:60' */
        if (LIBINFO_WL_00_B->DesiredGear < 0) {
          /* Transition: '<S168>:69' */
          LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_ReverseInit;
        } else {
          /* Transition: '<S168>:68' */
          /* Transition: '<S168>:16' */
          LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_ForwardInit;
        }
      }
    } else {
      /*  Started moving  */
      if (LIBINFO_WL_00_B->RelationalOperator) {
        /* Transition: '<S168>:33' */
        /* Exit Internal 'TentativelyTravelling': '<S168>:2' */
        LIBINFO_WL_00_DWork->is_TentativelyTravelling =
          LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        LIBINFO_WL_00_DWork->is_Main_ko0u = LIBINFO_WL_00_IN_Travelling;

        /* Entry Internal 'Travelling': '<S168>:4' */
        /* Transition: '<S168>:152' */
        /*  Hold off for at least the min time  */
        if (LIBINFO_WL_00_DWork->tentativeCounter <
            LIBINFO_WL_00_B->Divide2_dnc1) {
          /* Transition: '<S168>:156' */
          LIBINFO_WL_00_DWork->is_Travelling = LIBINFO_WL_00_IN_Hold;

          /* Entry 'Hold': '<S168>:154' */
          LIBINFO_WL_00_B->ST_Travel_State = 1U;
        } else {
          /* Transition: '<S168>:159' */
          /* Transition: '<S168>:160' */
          LIBINFO_WL_00_DWork->is_Travelling = LIBINFO_WL_00_IN_Confirm;

          /* Entry 'Confirm': '<S168>:155' */
          LIBINFO_WL_00_B->ST_Travel_State = 2U;
        }
      } else if (LIBINFO_WL_00_DWork->is_TentativelyTravelling ==
                 LIBINFO_WL_00_IN_Forward) {
        /* During 'Forward': '<S168>:87' */
        if (LIBINFO_WL_00_B->DesiredGear < 0) {
          /* Transition: '<S168>:98' */
          LIBINFO_WL_00_DWork->tentativeCounter = 0U;
          LIBINFO_WL_00_DWork->is_TentativelyTravelling =
            LIBINFO_WL_00_IN_Reverse_inos;
        }
      } else {
        /* During 'Reverse': '<S168>:88' */
        if (LIBINFO_WL_00_B->DesiredGear > 0) {
          /* Transition: '<S168>:96' */
          LIBINFO_WL_00_DWork->tentativeCounter = 0U;
          LIBINFO_WL_00_DWork->is_TentativelyTravelling =
            LIBINFO_WL_00_IN_Forward;
        }
      }
    }
    break;

   default:
    /* During 'Travelling': '<S168>:4' */
    /*  Stopped moving and still tentative  */
    if ((!LIBINFO_WL_00_B->RelationalOperator) &&
        (LIBINFO_WL_00_B->ST_Travel_State == 1)) {
      /* Transition: '<S168>:165' */
      /*  Stopped moving and in neutral prior minimum segment time  */
      if ((LIBINFO_WL_00_B->DesiredGear == 0) ||
          (LIBINFO_WL_00_DWork->tentativeCounter >=
           LIBINFO_WL_00_B->Divide1_gfci)) {
        /* Transition: '<S168>:166' */
        /* Exit Internal 'Travelling': '<S168>:4' */
        LIBINFO_WL_00_DWork->is_Travelling = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        LIBINFO_WL_00_DWork->is_Main_ko0u = LIBINFO_WL_00_IN_NotTravelling;

        /* Entry 'NotTravelling': '<S168>:1' */
        LIBINFO_WL_00_B->ST_Travel_State = 0U;
        LIBINFO_WL_00_DWork->tentativeCounter = 0U;

        /* Entry Internal 'NotTravelling': '<S168>:1' */
        /* Transition: '<S168>:17' */
        if (LIBINFO_WL_00_B->DesiredGear == 0) {
          /* Transition: '<S168>:15' */
          LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_Neutral;
        } else {
          /* Transition: '<S168>:60' */
          if (LIBINFO_WL_00_B->DesiredGear < 0) {
            /* Transition: '<S168>:69' */
            LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_ReverseInit;
          } else {
            /* Transition: '<S168>:68' */
            /* Transition: '<S168>:16' */
            LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_ForwardInit;
          }
        }
      } else {
        /* Transition: '<S168>:167' */
        /* Exit Internal 'Travelling': '<S168>:4' */
        LIBINFO_WL_00_DWork->is_Travelling = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        LIBINFO_WL_00_DWork->is_Main_ko0u = LIBINF_IN_TentativelyTravelling;

        /* Entry 'TentativelyTravelling': '<S168>:2' */
        LIBINFO_WL_00_B->ST_Travel_State = 1U;

        /* Entry Internal 'TentativelyTravelling': '<S168>:2' */
        /* Transition: '<S168>:90' */
        if (LIBINFO_WL_00_B->DesiredGear > 0) {
          /* Transition: '<S168>:91' */
          LIBINFO_WL_00_DWork->is_TentativelyTravelling =
            LIBINFO_WL_00_IN_Forward;
        } else {
          /* Transition: '<S168>:94' */
          /* Transition: '<S168>:93' */
          LIBINFO_WL_00_DWork->is_TentativelyTravelling =
            LIBINFO_WL_00_IN_Reverse_inos;
        }
      }
    } else {
      /*  Stopped moving  */
      if (!LIBINFO_WL_00_B->RelationalOperator) {
        /* Transition: '<S168>:18' */
        if (LIBINFO_WL_00_B->ST_Travel_Commit) {
          /* Transition: '<S168>:57' */
          /* Exit Internal 'Travelling': '<S168>:4' */
          LIBINFO_WL_00_DWork->is_Travelling = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
          LIBINFO_WL_00_DWork->is_Main_ko0u = LIBINFO_WL_00_IN_NotTravelling;

          /* Entry 'NotTravelling': '<S168>:1' */
          LIBINFO_WL_00_B->ST_Travel_State = 0U;
          LIBINFO_WL_00_DWork->tentativeCounter = 0U;

          /* Entry Internal 'NotTravelling': '<S168>:1' */
          /* Transition: '<S168>:17' */
          if (LIBINFO_WL_00_B->DesiredGear == 0) {
            /* Transition: '<S168>:15' */
            LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_Neutral;
          } else {
            /* Transition: '<S168>:60' */
            if (LIBINFO_WL_00_B->DesiredGear < 0) {
              /* Transition: '<S168>:69' */
              LIBINFO_WL_00_DWork->is_NotTravelling =
                LIBINFO_WL_00_IN_ReverseInit;
            } else {
              /* Transition: '<S168>:68' */
              /* Transition: '<S168>:16' */
              LIBINFO_WL_00_DWork->is_NotTravelling =
                LIBINFO_WL_00_IN_ForwardInit;
            }
          }
        } else {
          /* Transition: '<S168>:58' */
          /* Exit Internal 'Travelling': '<S168>:4' */
          LIBINFO_WL_00_DWork->is_Travelling = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
          LIBINFO_WL_00_DWork->is_Main_ko0u = LIB_IN_TentativelyNotTravelling;

          /* Entry 'TentativelyNotTravelling': '<S168>:3' */
          LIBINFO_WL_00_B->ST_Travel_State = 2U;

          /* Entry Internal 'TentativelyNotTravelling': '<S168>:3' */
          /* Transition: '<S168>:103' */
          LIBINFO_WL_00_DWork->notTravellingCounter = 0U;
          if (LIBINFO_WL_00_B->DesiredGear == 0) {
            /* Transition: '<S168>:104' */
            /* Transition: '<S168>:132' */
            LIBINFO_WL_00_DWork->is_TentativelyNotTravelling =
              LIBINFO_WL_00_IN_Neutral;

            /* Entry 'Neutral': '<S168>:99' */
            LIBINFO_WL_00_DWork->notTravellingCounter++;
          } else {
            /* Transition: '<S168>:106' */
            /* Transition: '<S168>:125' */
            /* Transition: '<S168>:126' */
            if (LIBINFO_WL_00_B->DesiredGear < 0) {
              /* Transition: '<S168>:107' */
              LIBINFO_WL_00_DWork->is_TentativelyNotTravelling =
                LIBINFO_WL_00_IN_Reverse;

              /* Entry 'Reverse': '<S168>:100' */
              LIBINFO_WL_00_DWork->notTravellingCounter = 1U;
            } else {
              /* Transition: '<S168>:109' */
              /* Transition: '<S168>:110' */
              LIBINFO_WL_00_DWork->is_TentativelyNotTravelling =
                LIBINFO_WL_00_IN_Forward;

              /* Entry 'Forward': '<S168>:101' */
              LIBINFO_WL_00_DWork->notTravellingCounter = 1U;
            }
          }
        }
      } else {
        switch (LIBINFO_WL_00_DWork->is_Travelling) {
         case LIBINFO_WL_00_IN_Confirm:
          break;

         default:
          /* During 'Hold': '<S168>:154' */
          /*  Been moving long enough  */
          if (LIBINFO_WL_00_DWork->tentativeCounter >=
              LIBINFO_WL_00_B->Divide2_dnc1) {
            /* Transition: '<S168>:157' */
            LIBINFO_WL_00_DWork->is_Travelling = LIBINFO_WL_00_IN_Confirm;

            /* Entry 'Confirm': '<S168>:155' */
            LIBINFO_WL_00_B->ST_Travel_State = 2U;
          }
          break;
        }
      }
    }
    break;
  }
}

/* Function for Chart: '<S97>/LoadState' */
static void LIBINFO_WL_00_TryToCommit(BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B,
  D_Work_LIBINFO_WL_00 *LIBINFO_WL_00_DWork)
{
  /* Graphical Function 'TryToCommit': '<S158>:68' */
  /* Transition: '<S158>:90' */
  if (LIBINFO_WL_00_DWork->segmentTimeCounter_mxc2 >=
      LIBINFO_WL_00_B->Divide3_ikji) {
    /* Transition: '<S158>:93' */
    /* Transition: '<S158>:97' */
    LIBINFO_WL_00_B->commit = TRUE;

    /* Transition: '<S158>:98' */
    LIBINFO_WL_00_DWork->segmentTimeCounter_mxc2 = 0U;
  } else {
    /* Transition: '<S158>:95' */
    LIBINFO_WL_00_DWork->segmentTimeCounter_mxc2 = 0U;
  }
}

/* Function for Chart: '<S250>/Chart' */
static void LIBINFO_WL_00_findActiveIndex(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  int32_t ii;
  int32_t exitg;

  /* Graphical Function 'findActiveIndex': '<S252>:35' */
  /* Transition: '<S252>:38' */
  ii = 0;
  do {
    exitg = 0;
    if (ii < 7) {
      /* Constant: '<S250>/Constant1' */
      /* Transition: '<S252>:41' */
      if (LIBINFO_WL_00_B->VectorConcatenate[ii] ==
          LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_Totalizer_00_calcompfix_mi_ROM_p
          ->ST_Tot_ActiveStateValue) {
        /* Transition: '<S252>:45' */
        /* Transition: '<S252>:46' */
        LIBINFO_WL_00_B->activeSegmentIndex = ii;
        exitg = 1;
      } else {
        /* Transition: '<S252>:48' */
        /* Transition: '<S252>:50' */
        ii++;

        /* Transition: '<S252>:51' */
      }

      /* End of Constant: '<S250>/Constant1' */
    } else {
      /* Transition: '<S252>:43' */
      LIBINFO_WL_00_B->activeSegmentIndex = 6;
      exitg = 1;
    }
  } while (exitg == 0);
}

/* Function for Chart: '<S250>/Chart' */
static void LIBINFO_WL_00_maskTentatives(RT_MODEL_LIBINFO_WL_00 *LIBINFO_WL_00_M,
  BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  int32_t ii;

  /* Graphical Function 'maskTentatives': '<S252>:52' */
  /* Transition: '<S252>:54' */
  for (ii = 0; ii < 7; ii++) {
    /* Constant: '<S250>/Constant2' */
    /* Transition: '<S252>:57' */
    if ((ii >= LIBINFO_WL_00_B->activeSegmentIndex) ||
        (!(LIBINFO_WL_00_B->VectorConcatenate[ii] ==
           LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_Totalizer_00_calcompfix_mi_ROM_p
           ->ST_Tot_TentativeStateValue))) {
      /* Transition: '<S252>:63' */
      /* Transition: '<S252>:76' */
      /* Transition: '<S252>:77' */
      /* Transition: '<S252>:66' */
      LIBINFO_WL_00_B->segmentTentativeLogicalVector[ii] = FALSE;
    } else {
      /* Transition: '<S252>:69' */
      /* Transition: '<S252>:71' */
      /* Transition: '<S252>:79' */
      LIBINFO_WL_00_B->segmentTentativeLogicalVector[ii] = TRUE;

      /* Transition: '<S252>:80' */
    }

    /* End of Constant: '<S250>/Constant2' */
    /* Transition: '<S252>:64' */
    /* Transition: '<S252>:61' */
  }

  /* Transition: '<S252>:59' */
}

/* Function for Chart: '<S309>/Chart' */
static void LIBINFO__commitPreviouslyActive(BlockIO_LIBINFO_WL_00
  *LIBINFO_WL_00_B)
{
  /* local block i/o variables */
  int32_t rtb_Min;
  int32_t rtb_Min_bwgi;
  int32_t rtb_Min_cspk;
  int32_t rtb_TmpLatchAtinIndexBufferOutp[10];
  int32_t rtb_Min_jron;
  int32_t i;

  /* Graphical Function 'commitPreviouslyActive': '<S347>:52' */
  /* Transition: '<S347>:74' */
  if (LIBINFO_WL_00_B->bufferDepth > 0) {
    /* Transition: '<S347>:78' */
    while ((LIBINFO_WL_00_B->bufferDepth > 1) && (LIBINFO_WL_00_B->Merge_i0jw[1]
            != LIBINFO_WL_00_B->ToOneBased)) {
      /* Transition: '<S347>:86' */
      /* Transition: '<S347>:89' */
      /* Transition: '<S347>:91' */
      LIBINFO_WL_00_B->mergeFromIndexOneBased = 2;

      /* Outputs for Function Call SubSystem: '<S349>/FuncCallSplit2' */

      /* Event: '<S347>:14' */
      LIBINFO_WL_00_FuncCallSplit2(LIBINFO_WL_00_B->Merge_i0jw,
        LIBINFO_WL_00_B->mergeFromIndexOneBased, LIBINFO_WL_00_B->bufferDepth,
        LIBINFO_WL_00_B->Merge_cxcm, LIBINFO_WL_00_B->Merge_jhvc,
        LIBINFO_WL_00_B->Merge_haaq, LIBINFO_WL_00_B->Merge_a2nn,
        LIBINFO_WL_00_B->Merge_obd1, LIBINFO_WL_00_B->Merge1,
        LIBINFO_WL_00_B->Merge, LIBINFO_WL_00_B->Merge_oe45,
        LIBINFO_WL_00_B->Merge_bash, LIBINFO_WL_00_B->Merge_dfdv,
        LIBINFO_WL_00_B->Merge_labi, LIBINFO_WL_00_B->Merge_i0jw,
        LIBINFO_WL_00_B->Merge_haaq, LIBINFO_WL_00_B->Merge_a2nn,
        LIBINFO_WL_00_B->Merge1, LIBINFO_WL_00_B->Merge_cxcm,
        LIBINFO_WL_00_B->Merge_jhvc, LIBINFO_WL_00_B->Merge,
        LIBINFO_WL_00_B->Merge_oe45, LIBINFO_WL_00_B->Merge_bash,
        LIBINFO_WL_00_B->Merge_dfdv, LIBINFO_WL_00_B->Merge_labi,
        LIBINFO_WL_00_B->Merge_obd1, (rtC_FuncCallSplit2_LIBINFO_WL_0 *)
        (&LIBINFO_WL_00_ConstB.FuncCallSplit2));

      /* End of Outputs for SubSystem: '<S349>/FuncCallSplit2' */
      LIBINFO_WL_00_B->bufferDepth--;

      /* Transition: '<S347>:100' */
    }

    /* Outputs for Function Call SubSystem: '<S349>/FuncCallSplit3' */
    /* S-Function (fcncallgen): '<S366>/Function-Call Generator' incorporates:
     *  SubSystem: '<S348>/CommitFunc'
     */
    /* SignalConversion: '<S351>/TmpLatchAtinIndexBufferOutport1' */
    /* Transition: '<S347>:87' */
    /* Transition: '<S347>:93' */
    /* Transition: '<S347>:94' */
    /* Transition: '<S347>:81' */
    /* Event: '<S347>:15' */
    for (i = 0; i < 10; i++) {
      rtb_TmpLatchAtinIndexBufferOutp[i] = LIBINFO_WL_00_B->Merge_i0jw[i];
    }

    /* End of SignalConversion: '<S351>/TmpLatchAtinIndexBufferOutport1' */

    /* Outputs for Atomic SubSystem: '<S351>/ShiftBufferBack1' */
    /* MinMax: '<S354>/Min' */
    if (LIBINFO_WL_00_B->bufferDepth <= 10) {
      rtb_Min_jron = LIBINFO_WL_00_B->bufferDepth;
    } else {
      rtb_Min_jron = 10;
    }

    /* End of MinMax: '<S354>/Min' */

    /* If: '<S354>/If' incorporates:
     *  Constant: '<S351>/Constant'
     *  RelationalOperator: '<S354>/Relational Operator'
     */
    if (2 <= rtb_Min_jron) {
      /* Outputs for IfAction SubSystem: '<S354>/DoShift' incorporates:
       *  ActionPort: '<S357>/Action Port'
       */
      LIBINFO_WL_00_DoShift(rtb_Min_jron, 2, rtb_TmpLatchAtinIndexBufferOutp,
                            LIBINFO_WL_00_B->Merge_i0jw);

      /* End of Outputs for SubSystem: '<S354>/DoShift' */
    } else {
      /* Outputs for IfAction SubSystem: '<S354>/DoNothing' incorporates:
       *  ActionPort: '<S356>/Action Port'
       */
      LIBINFO_WL_00_DoNothing(rtb_TmpLatchAtinIndexBufferOutp,
        LIBINFO_WL_00_B->Merge_i0jw);

      /* End of Outputs for SubSystem: '<S354>/DoNothing' */
    }

    /* End of If: '<S354>/If' */
    /* End of Outputs for SubSystem: '<S351>/ShiftBufferBack1' */

    /* S-Function (fcncallgen): '<S366>/Function-Call Generator' incorporates:
     *  SubSystem: '<S307>/FuncCallSplit3'
     */
    /* S-Function (fcncallgen): '<S341>/Function-Call Generator' incorporates:
     *  SubSystem: '<S305>/CommitFunc'
     */
    /* SignalConversion: '<S312>/TmpLatchAtinAccumulatorBufferOutport1' */
    for (i = 0; i < 10; i++) {
      LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_hpld[i] =
        LIBINFO_WL_00_B->Merge_cxcm[i];
    }

    /* End of SignalConversion: '<S312>/TmpLatchAtinAccumulatorBufferOutport1' */

    /* Outputs for Atomic SubSystem: '<S312>/ShiftBufferBack' */

    /* Constant: '<S312>/Constant' */
    LIBINFO_WL_ShiftBufferBack_nhsx(2,
      LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_hpld,
      LIBINFO_WL_00_B->bufferDepth, LIBINFO_WL_00_B->Merge_cxcm,
      (rtC_ShiftBufferBack_LIBINF_h3x4 *)(&LIBINFO_WL_00_ConstB.ShiftBufferBack));

    /* End of Outputs for SubSystem: '<S312>/ShiftBufferBack' */

    /* S-Function (fcncallgen): '<S341>/Function-Call Generator' incorporates:
     *  SubSystem: '<S308>/FuncCallSplit3'
     */
    /* S-Function (fcncallgen): '<S345>/Function-Call Generator' incorporates:
     *  SubSystem: '<S306>/CommitFunc'
     */
    /* SignalConversion: '<S326>/TmpLatchAtinAccumulatorBufferOutport1' */
    for (i = 0; i < 10; i++) {
      LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_ofwt[i] =
        LIBINFO_WL_00_B->Merge_jhvc[i];
    }

    /* End of SignalConversion: '<S326>/TmpLatchAtinAccumulatorBufferOutport1' */

    /* Outputs for Atomic SubSystem: '<S326>/ShiftBufferBack1' */

    /* Constant: '<S326>/Constant' */
    LIBINFO_WL_ShiftBufferBack_nhsx(2,
      LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_ofwt,
      LIBINFO_WL_00_B->bufferDepth, LIBINFO_WL_00_B->Merge_jhvc,
      (rtC_ShiftBufferBack_LIBINF_h3x4 *)
      (&LIBINFO_WL_00_ConstB.ShiftBufferBack1_nskr));

    /* End of Outputs for SubSystem: '<S326>/ShiftBufferBack1' */

    /* S-Function (fcncallgen): '<S345>/Function-Call Generator' incorporates:
     *  SubSystem: '<S211>/FuncCallSplit3'
     */
    /* S-Function (fcncallgen): '<S390>/Function-Call Generator' incorporates:
     *  SubSystem: '<S219>/CommitFunc'
     */
    LIBINFO_WL_00_CommitFunc(LIBINFO_WL_00_B->Merge,
      LIBINFO_WL_00_B->bufferDepth,
      LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_bcj2, LIBINFO_WL_00_B->Merge,
                             (rtC_CommitFunc_LIBINFO_WL_00 *)
      (&LIBINFO_WL_00_ConstB.CommitFunc_bgbo));

    /* S-Function (fcncallgen): '<S390>/Function-Call Generator' incorporates:
     *  SubSystem: '<S207>/FuncCallSplit3'
     */
    /* S-Function (fcncallgen): '<S374>/Function-Call Generator' incorporates:
     *  SubSystem: '<S468>/CommitFunc'
     */
    LIBINFO_WL_00_CommitFunc_ibfk(LIBINFO_WL_00_B->Merge_oe45,
      LIBINFO_WL_00_B->bufferDepth,
      LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_hky2,
      LIBINFO_WL_00_B->Merge_oe45, (rtC_CommitFunc_LIBINFO_WL__juir *)
      (&LIBINFO_WL_00_ConstB.CommitFunc_ibfk));

    /* S-Function (fcncallgen): '<S374>/Function-Call Generator' incorporates:
     *  SubSystem: '<S208>/FuncCallSplit3'
     */
    /* S-Function (fcncallgen): '<S378>/Function-Call Generator' incorporates:
     *  SubSystem: '<S235>/CommitFunc'
     */
    LIBINFO_WL_00_CommitFunc(LIBINFO_WL_00_B->Merge_bash,
      LIBINFO_WL_00_B->bufferDepth,
      LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_oicb,
      LIBINFO_WL_00_B->Merge_bash, (rtC_CommitFunc_LIBINFO_WL_00 *)
      (&LIBINFO_WL_00_ConstB.CommitFunc_garn));

    /* S-Function (fcncallgen): '<S378>/Function-Call Generator' incorporates:
     *  SubSystem: '<S209>/FuncCallSplit3'
     */
    /* S-Function (fcncallgen): '<S382>/Function-Call Generator' incorporates:
     *  SubSystem: '<S434>/FuncCallSplit3'
     */
    /* S-Function (fcncallgen): '<S465>/Function-Call Generator' incorporates:
     *  SubSystem: '<S432>/CommitFunc'
     */
    /* SignalConversion: '<S436>/TmpLatchAtinAccumulatorBufferOutport1' */
    for (i = 0; i < 10; i++) {
      LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_pdov[i] =
        LIBINFO_WL_00_B->Merge_haaq[i];
    }

    /* End of SignalConversion: '<S436>/TmpLatchAtinAccumulatorBufferOutport1' */

    /* Outputs for Atomic SubSystem: '<S436>/ShiftBufferBack' */
    /* MinMax: '<S439>/Min' */
    if (LIBINFO_WL_00_B->bufferDepth <= 10) {
      rtb_Min_cspk = LIBINFO_WL_00_B->bufferDepth;
    } else {
      rtb_Min_cspk = 10;
    }

    /* End of MinMax: '<S439>/Min' */

    /* If: '<S439>/If' incorporates:
     *  Constant: '<S436>/Constant'
     *  RelationalOperator: '<S439>/Relational Operator'
     */
    if (2 <= rtb_Min_cspk) {
      /* Outputs for IfAction SubSystem: '<S439>/DoShift' incorporates:
       *  ActionPort: '<S442>/Action Port'
       */
      LIBINFO_WL_00_DoShift_etzq(rtb_Min_cspk, 2,
        LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_pdov,
        LIBINFO_WL_00_B->Merge_haaq);

      /* End of Outputs for SubSystem: '<S439>/DoShift' */
    } else {
      /* Outputs for IfAction SubSystem: '<S439>/DoNothing' incorporates:
       *  ActionPort: '<S441>/Action Port'
       */
      LIBINFO_WL_00_DoNothing_b1m5
        (LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_pdov,
         LIBINFO_WL_00_B->Merge_haaq);

      /* End of Outputs for SubSystem: '<S439>/DoNothing' */
    }

    /* End of If: '<S439>/If' */
    /* End of Outputs for SubSystem: '<S436>/ShiftBufferBack' */

    /* S-Function (fcncallgen): '<S465>/Function-Call Generator' incorporates:
     *  SubSystem: '<S433>/CommitFunc'
     */
    /* SignalConversion: '<S450>/TmpLatchAtinAccumulatorBufferOutport1' */
    for (i = 0; i < 10; i++) {
      LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_edhm[i] =
        LIBINFO_WL_00_B->Merge_a2nn[i];
    }

    /* End of SignalConversion: '<S450>/TmpLatchAtinAccumulatorBufferOutport1' */

    /* Outputs for Atomic SubSystem: '<S450>/ShiftBufferBack' */
    /* MinMax: '<S453>/Min' */
    if (LIBINFO_WL_00_B->bufferDepth <= 10) {
      rtb_Min_bwgi = LIBINFO_WL_00_B->bufferDepth;
    } else {
      rtb_Min_bwgi = 10;
    }

    /* End of MinMax: '<S453>/Min' */

    /* If: '<S453>/If' incorporates:
     *  Constant: '<S450>/Constant'
     *  RelationalOperator: '<S453>/Relational Operator'
     */
    if (2 <= rtb_Min_bwgi) {
      /* Outputs for IfAction SubSystem: '<S453>/DoShift' incorporates:
       *  ActionPort: '<S456>/Action Port'
       */
      LIBINFO_WL_00_DoShift_ihkh(rtb_Min_bwgi, 2,
        LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_edhm,
        LIBINFO_WL_00_B->Merge_a2nn);

      /* End of Outputs for SubSystem: '<S453>/DoShift' */
    } else {
      /* Outputs for IfAction SubSystem: '<S453>/DoNothing' incorporates:
       *  ActionPort: '<S455>/Action Port'
       */
      LIBINFO_WL_00_DoNothing_acyu
        (LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_edhm,
         LIBINFO_WL_00_B->Merge_a2nn);

      /* End of Outputs for SubSystem: '<S453>/DoNothing' */
    }

    /* End of If: '<S453>/If' */
    /* End of Outputs for SubSystem: '<S450>/ShiftBufferBack' */

    /* S-Function (fcncallgen): '<S382>/Function-Call Generator' incorporates:
     *  SubSystem: '<S210>/FuncCallSplit3'
     */
    /* S-Function (fcncallgen): '<S386>/Function-Call Generator' incorporates:
     *  SubSystem: '<S400>/CommitFunc'
     */
    LIBINFO_WL_00_CommitFunc(LIBINFO_WL_00_B->Merge_dfdv,
      LIBINFO_WL_00_B->bufferDepth,
      LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBufferOu,
      LIBINFO_WL_00_B->Merge_dfdv, (rtC_CommitFunc_LIBINFO_WL_00 *)
      (&LIBINFO_WL_00_ConstB.CommitFunc_bf0u));

    /* S-Function (fcncallgen): '<S386>/Function-Call Generator' incorporates:
     *  SubSystem: '<S212>/FuncCallSplit3'
     */
    /* S-Function (fcncallgen): '<S394>/Function-Call Generator' incorporates:
     *  SubSystem: '<S416>/CommitFunc'
     */
    LIBINFO_WL_00_CommitFunc_ibfk(LIBINFO_WL_00_B->Merge_labi,
      LIBINFO_WL_00_B->bufferDepth,
      LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_mbyo,
      LIBINFO_WL_00_B->Merge_labi, (rtC_CommitFunc_LIBINFO_WL__juir *)
      (&LIBINFO_WL_00_ConstB.CommitFunc_lx2e));

    /* S-Function (fcncallgen): '<S394>/Function-Call Generator' incorporates:
     *  SubSystem: '<S213>/FuncCallSplit3'
     */
    /* S-Function (fcncallgen): '<S398>/Function-Call Generator' incorporates:
     *  SubSystem: '<S275>/CommitFunc'
     */
    for (i = 0; i < 10; i++) {
      /* SignalConversion: '<S278>/TmpLatchAtinParamBufferOutport1' */
      LIBINFO_WL_00_B->TmpLatchAtinParamBufferOutport1[i] =
        LIBINFO_WL_00_B->Merge_obd1[i];

      /* SignalConversion: '<S278>/TmpLatchAtinParamConfBufferOutport1' */
      LIBINFO_WL_00_B->TmpLatchAtinParamConfBufferOutp[i] =
        LIBINFO_WL_00_B->Merge1[i];
    }

    /* Outputs for Atomic SubSystem: '<S278>/ShiftBufferBack' */

    /* Constant: '<S278>/Constant' */
    LIBINFO_WL_ShiftBufferBack_frny(2,
      LIBINFO_WL_00_B->TmpLatchAtinParamBufferOutport1,
      LIBINFO_WL_00_B->bufferDepth, LIBINFO_WL_00_B->Merge_obd1,
      (rtC_ShiftBufferBack_LIBINF_enc2 *)
      (&LIBINFO_WL_00_ConstB.ShiftBufferBack_mzqk));

    /* End of Outputs for SubSystem: '<S278>/ShiftBufferBack' */

    /* Outputs for Atomic SubSystem: '<S278>/ShiftBufferBack1' */
    /* MinMax: '<S282>/Min' */
    if (LIBINFO_WL_00_B->bufferDepth <= 10) {
      rtb_Min = LIBINFO_WL_00_B->bufferDepth;
    } else {
      rtb_Min = 10;
    }

    /* End of MinMax: '<S282>/Min' */

    /* If: '<S282>/If' incorporates:
     *  Constant: '<S278>/Constant'
     *  RelationalOperator: '<S282>/Relational Operator'
     */
    if (2 <= rtb_Min) {
      /* Outputs for IfAction SubSystem: '<S282>/DoShift' incorporates:
       *  ActionPort: '<S289>/Action Port'
       */
      LIBINFO_WL_00_DoShift_cq4g(rtb_Min, 2,
        LIBINFO_WL_00_B->TmpLatchAtinParamConfBufferOutp,
        LIBINFO_WL_00_B->Merge1);

      /* End of Outputs for SubSystem: '<S282>/DoShift' */
    } else {
      /* Outputs for IfAction SubSystem: '<S282>/DoNothing' incorporates:
       *  ActionPort: '<S288>/Action Port'
       */
      LIBINFO_WL_00_DoNothing_keuk
        (LIBINFO_WL_00_B->TmpLatchAtinParamConfBufferOutp,
         LIBINFO_WL_00_B->Merge1);

      /* End of Outputs for SubSystem: '<S282>/DoNothing' */
    }

    /* End of If: '<S282>/If' */
    /* End of Outputs for SubSystem: '<S278>/ShiftBufferBack1' */
    /* End of Outputs for SubSystem: '<S349>/FuncCallSplit3' */
    LIBINFO_WL_00_B->bufferDepth--;
  } else {
    /* Transition: '<S347>:79' */
  }
}

/* Function for Chart: '<S309>/Chart' */
static boolean_T LIBINFO_WL_00_appendActive(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  boolean_T appended;

  /* Graphical Function 'appendActive': '<S347>:26' */
  /* Transition: '<S347>:29' */
  if (0 == LIBINFO_WL_00_B->bufferDepth) {
    /* Transition: '<S347>:32' */
    /* Transition: '<S347>:38' */
    LIBINFO_WL_00_B->indexToAppend = LIBINFO_WL_00_B->ToOneBased;

    /* Outputs for Function Call SubSystem: '<S349>/FuncCallSplit4' */

    /* Event: '<S347>:12' */
    LIBINFO_WL_00_FuncCallSplit4(LIBINFO_WL_00_B->Merge_i0jw,
      LIBINFO_WL_00_B->bufferDepth, LIBINFO_WL_00_B->indexToAppend,
      LIBINFO_WL_00_B->Merge_cxcm, LIBINFO_WL_00_B->Merge_jhvc,
      LIBINFO_WL_00_B->Merge_haaq, LIBINFO_WL_00_B->Switch_nrdg,
      LIBINFO_WL_00_B->Merge_a2nn, LIBINFO_WL_00_B->Switch1_jkyk,
      LIBINFO_WL_00_B->Merge_obd1, LIBINFO_WL_00_B->Merge1,
      LIBINFO_WL_00_B->Merge, LIBINFO_WL_00_B->Merge_oe45,
      LIBINFO_WL_00_B->globalTime, LIBINFO_WL_00_B->Merge_bash,
      LIBINFO_WL_00_B->Merge_dfdv, LIBINFO_WL_00_B->Merge_labi,
      LIBINFO_WL_00_B->Switch_bxww, LIBINFO_WL_00_B->Merge_i0jw,
      LIBINFO_WL_00_B->Merge_cxcm, LIBINFO_WL_00_B->Merge_jhvc,
      LIBINFO_WL_00_B->Merge_haaq, LIBINFO_WL_00_B->Merge_a2nn,
      LIBINFO_WL_00_B->Merge_obd1, LIBINFO_WL_00_B->Merge1,
      LIBINFO_WL_00_B->Merge, LIBINFO_WL_00_B->Merge_oe45,
      LIBINFO_WL_00_B->Merge_bash, LIBINFO_WL_00_B->Merge_dfdv,
      LIBINFO_WL_00_B->Merge_labi, LIBINFO_WL_00_M);

    /* End of Outputs for SubSystem: '<S349>/FuncCallSplit4' */
    LIBINFO_WL_00_B->bufferDepth++;
    appended = TRUE;

    /* Transition: '<S347>:82' */
  } else {
    /* Transition: '<S347>:40' */
    appended = FALSE;
  }

  return appended;
}

/* Function for Chart: '<S309>/Chart' */
static void LIBINFO_WL_00_purgeInactives(BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  int32_t ii;

  /* Graphical Function 'purgeInactives': '<S347>:62' */
  /* Transition: '<S347>:103' */
  ii = 1;
  while (ii < LIBINFO_WL_00_B->bufferDepth) {
    /* Transition: '<S347>:106' */
    if ((LIBINFO_WL_00_B->Merge_i0jw[ii] <= 7) && ((LIBINFO_WL_00_B->
          Merge_i0jw[ii] > 0) && (LIBINFO_WL_00_B->
          segmentTentativeLogicalVector[LIBINFO_WL_00_B->Merge_i0jw[ii] - 1])))
    {
      /* Transition: '<S347>:110' */
      /* Transition: '<S347>:130' */
      /* Transition: '<S347>:112' */
      /* Transition: '<S347>:114' */
      ii++;

      /* Transition: '<S347>:116' */
      /* Transition: '<S347>:122' */
    } else {
      /* Transition: '<S347>:124' */
      /* Transition: '<S347>:128' */
      /* Transition: '<S347>:132' */
      /* Transition: '<S347>:134' */
      /* Transition: '<S347>:129' */
      /* Transition: '<S347>:125' */
      LIBINFO_WL_00_B->mergeFromIndexOneBased = ii + 1;

      /* Outputs for Function Call SubSystem: '<S349>/FuncCallSplit2' */

      /* Event: '<S347>:14' */
      LIBINFO_WL_00_FuncCallSplit2(LIBINFO_WL_00_B->Merge_i0jw,
        LIBINFO_WL_00_B->mergeFromIndexOneBased, LIBINFO_WL_00_B->bufferDepth,
        LIBINFO_WL_00_B->Merge_cxcm, LIBINFO_WL_00_B->Merge_jhvc,
        LIBINFO_WL_00_B->Merge_haaq, LIBINFO_WL_00_B->Merge_a2nn,
        LIBINFO_WL_00_B->Merge_obd1, LIBINFO_WL_00_B->Merge1,
        LIBINFO_WL_00_B->Merge, LIBINFO_WL_00_B->Merge_oe45,
        LIBINFO_WL_00_B->Merge_bash, LIBINFO_WL_00_B->Merge_dfdv,
        LIBINFO_WL_00_B->Merge_labi, LIBINFO_WL_00_B->Merge_i0jw,
        LIBINFO_WL_00_B->Merge_haaq, LIBINFO_WL_00_B->Merge_a2nn,
        LIBINFO_WL_00_B->Merge1, LIBINFO_WL_00_B->Merge_cxcm,
        LIBINFO_WL_00_B->Merge_jhvc, LIBINFO_WL_00_B->Merge,
        LIBINFO_WL_00_B->Merge_oe45, LIBINFO_WL_00_B->Merge_bash,
        LIBINFO_WL_00_B->Merge_dfdv, LIBINFO_WL_00_B->Merge_labi,
        LIBINFO_WL_00_B->Merge_obd1, (rtC_FuncCallSplit2_LIBINFO_WL_0 *)
        (&LIBINFO_WL_00_ConstB.FuncCallSplit2));

      /* End of Outputs for SubSystem: '<S349>/FuncCallSplit2' */
      LIBINFO_WL_00_B->bufferDepth--;
    }

    /* Transition: '<S347>:120' */
  }

  /* Transition: '<S347>:108' */
}

/* Function for Chart: '<S309>/Chart' */
static boolean_T LIBINFO_WL_00_isAlreadyInBuffer(int32_t segmentIndexOneBased,
  BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  boolean_T result;
  int32_t ii;
  int32_t exitg;

  /* Graphical Function 'isAlreadyInBuffer': '<S347>:135' */
  /* Transition: '<S347>:139' */
  ii = 0;
  do {
    exitg = 0;
    if (ii < LIBINFO_WL_00_B->bufferDepth) {
      /* Transition: '<S347>:142' */
      if (LIBINFO_WL_00_B->Merge_i0jw[ii] != segmentIndexOneBased) {
        /* Transition: '<S347>:146' */
        /* Transition: '<S347>:151' */
        ii++;

        /* Transition: '<S347>:152' */
      } else {
        /* Transition: '<S347>:148' */
        result = TRUE;

        /* Transition: '<S347>:149' */
        exitg = 1;
      }
    } else {
      /* Transition: '<S347>:144' */
      result = FALSE;
      exitg = 1;
    }
  } while (exitg == 0);

  return result;
}

/* Function for Chart: '<S309>/Chart' */
static boolean_T LIBINFO_WL_00_addTentatives(RT_MODEL_LIBINFO_WL_00
  *LIBINFO_WL_00_M, BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B)
{
  boolean_T appended;
  int32_t ii;

  /* Graphical Function 'addTentatives': '<S347>:63' */
  /* Transition: '<S347>:154' */
  ii = 0;
  appended = FALSE;

  /* Constant: '<S309>/Constant' */
  while ((LIBINFO_WL_00_B->bufferDepth < 10) && (ii < 7)) {
    /* Transition: '<S347>:168' */
    /* Transition: '<S347>:157' */
    if (LIBINFO_WL_00_B->segmentTentativeLogicalVector[ii]) {
      /* Transition: '<S347>:163' */
      if (!LIBINFO_WL_00_isAlreadyInBuffer(ii + 1, LIBINFO_WL_00_B)) {
        /* Transition: '<S347>:181' */
        /* Transition: '<S347>:183' */
        LIBINFO_WL_00_B->indexToAppend = ii + 1;

        /* Outputs for Function Call SubSystem: '<S349>/FuncCallSplit4' */

        /* Event: '<S347>:12' */
        LIBINFO_WL_00_FuncCallSplit4(LIBINFO_WL_00_B->Merge_i0jw,
          LIBINFO_WL_00_B->bufferDepth, LIBINFO_WL_00_B->indexToAppend,
          LIBINFO_WL_00_B->Merge_cxcm, LIBINFO_WL_00_B->Merge_jhvc,
          LIBINFO_WL_00_B->Merge_haaq, LIBINFO_WL_00_B->Switch_nrdg,
          LIBINFO_WL_00_B->Merge_a2nn, LIBINFO_WL_00_B->Switch1_jkyk,
          LIBINFO_WL_00_B->Merge_obd1, LIBINFO_WL_00_B->Merge1,
          LIBINFO_WL_00_B->Merge, LIBINFO_WL_00_B->Merge_oe45,
          LIBINFO_WL_00_B->globalTime, LIBINFO_WL_00_B->Merge_bash,
          LIBINFO_WL_00_B->Merge_dfdv, LIBINFO_WL_00_B->Merge_labi,
          LIBINFO_WL_00_B->Switch_bxww, LIBINFO_WL_00_B->Merge_i0jw,
          LIBINFO_WL_00_B->Merge_cxcm, LIBINFO_WL_00_B->Merge_jhvc,
          LIBINFO_WL_00_B->Merge_haaq, LIBINFO_WL_00_B->Merge_a2nn,
          LIBINFO_WL_00_B->Merge_obd1, LIBINFO_WL_00_B->Merge1,
          LIBINFO_WL_00_B->Merge, LIBINFO_WL_00_B->Merge_oe45,
          LIBINFO_WL_00_B->Merge_bash, LIBINFO_WL_00_B->Merge_dfdv,
          LIBINFO_WL_00_B->Merge_labi, LIBINFO_WL_00_M);

        /* End of Outputs for SubSystem: '<S349>/FuncCallSplit4' */
        LIBINFO_WL_00_B->bufferDepth++;
        appended = TRUE;

        /* Transition: '<S347>:184' */
      } else {
        /* Transition: '<S347>:165' */
      }

      /* Transition: '<S347>:175' */
    } else {
      /* Transition: '<S347>:176' */
    }

    /* Transition: '<S347>:178' */
    ii++;

    /* Transition: '<S347>:179' */
  }

  /* End of Constant: '<S309>/Constant' */
  /* Transition: '<S347>:160' */
  /* Transition: '<S347>:171' */
  /* Transition: '<S347>:172' */
  return appended;
}

/* Model step function */
void LIBINFO_WL_00_step(RT_MODEL_LIBINFO_WL_00 *const LIBINFO_WL_00_M,
  BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B, D_Work_LIBINFO_WL_00
  *LIBINFO_WL_00_DWork, dt_libinfo_MachSpdKPH_Signed
  LIBINFO_WL_00_U_ground_speed, dt_libinfo_single LIBINFO_WL_00_U_payload_ratio,
  dt_libinfo_single LIBINFO_WL_00_U_payload_ratio_raw, dt_libinfo_Ratio_hiRes
  LIBINFO_WL_00_U_ext_force_normalized, dt_libinfo_ValveCmd
  LIBINFO_WL_00_U_lift_valve_cmd, dt_libinfo_ValveCmd
  LIBINFO_WL_00_U_tilt_valve_cmd, dt_libinfo_Angle LIBINFO_WL_00_U_bucket_angle,
  dt_libinfo_Angle LIBINFO_WL_00_U_lift_angle, dt_libinfo_TransmissionGear_int16
  LIBINFO_WL_00_U_desired_gear, dt_libinfo_EngSpd_Signed
  LIBINFO_WL_00_U_engine_speed, dt_libinfo_ValveCmd
  LIBINFO_WL_00_U_tilt_lever_cmd, dt_libinfo_modulation_pct
  LIBINFO_WL_00_U_tilt_cyl_position, dt_libinfo_Unsigned16
  LIBINFO_WL_00_U_machine_idle, dt_libinfo_Unsigned16 LIBINFO_WL_00_U_key_switch,
  dt_libinfo_Unsigned32 LIBINFO_WL_00_U_real_time, dt_libinfo_fuel_high_res
  LIBINFO_WL_00_U_fuel_high_res, dt_libinfo_fuel_low_res LIBINFO_WL_00_U_fuel,
  dt_libinfo_FuelRate LIBINFO_WL_00_U_fuel_rate, dt_libinfo_ARDfuel_Rate
  LIBINFO_WL_00_U_fuel_rate_ard, dt_libinfo_Flag LIBINFO_WL_00_U_realTime_status,
  dt_libinfo_gps_latitude LIBINFO_WL_00_U_gps_latitude,
  dt_libinfo_Ratio_Unsigned32 LIBINFO_WL_00_U_gps_longitude, dt_libinfo_Flag
  LIBINFO_WL_00_U_gps_lat_long_status, dt_libinfo_single
  LIBINFO_WL_00_U_payload_weight, dt_libinfo_Flag_u16
  LIBINFO_WL_00_U_payloadCalcMethod, dt_libinfo_Unsigned32
  LIBINFO_WL_00_U_service_hour_meter, dt_libinfo_tz_offset_mins
  LIBINFO_WL_00_U_timezone_offset, dt_libinfo_Flag_u16
  LIBINFO_WL_00_U_payload_weight_status, dt_libinfo_Unsigned16
  LIBINFO_WL_00_U_payload_ratio_status, dt_libinfo_Unsigned16
  LIBINFO_WL_00_U_payload_ratio_raw_status, dt_libinfo_Unsigned16
  LIBINFO_WL_00_U_Impl_operation_status, dt_libinfo_Flag
  *LIBINFO_WL_00_Y_commit_segment_record, uint8_t
  *LIBINFO_WL_00_Y_segment_record_id, dt_libinfo_Unsigned32
  *LIBINFO_WL_00_Y_segment_rec_start_simTime, dt_libinfo_Time20msLong
  *LIBINFO_WL_00_Y_segment_rec_duration, dt_libinfo_single
  *LIBINFO_WL_00_Y_segment_rec_distance, dt_libinfo_Unsigned32
  *LIBINFO_WL_00_Y_segment_rec_start_real_time, dt_libinfo_single
  *LIBINFO_WL_00_Y_segment_rec_fuel_used, dt_libinfo_gps_latitude
  *LIBINFO_WL_00_Y_segment_rec_latitude, dt_libinfo_Ratio_Unsigned32
  *LIBINFO_WL_00_Y_segment_rec_longitude, dt_libinfo_Unsigned32
  *LIBINFO_WL_00_Y_segment_rec_idle_time, dt_libinfo_Unsigned32
  *LIBINFO_WL_00_Y_segment_rec_hour_meter, dt_libinfo_single
  *LIBINFO_WL_00_Y_segment_rec_payload, dt_libinfo_Flag_u16
  *LIBINFO_WL_00_Y_segment_rec_payload_calc_method, dt_libinfo_Flag
  *LIBINFO_WL_00_Y_commit_rec_gps, uint8_t *LIBINFO_WL_00_Y_segment_dig_state,
  uint8_t *LIBINFO_WL_00_Y_segment_last_completed_id, dt_libinfo_Time20msLong
  *LIBINFO_WL_00_Y_segment_time_since_last_end, uint8_t
  *LIBINFO_WL_00_Y_segment_sequence_number, uint8_t
  *LIBINFO_WL_00_Y_keyswitch_override_flag, uint8_t
  *LIBINFO_WL_00_Y_segment_active_segment_id)
{
  /* local block i/o variables */
  int32_t rtb_Switch1_mtge;
  dt_libinfo_MachSpdKPH_Signed rtb_UnitDelay1_la4n;
  dt_libinfo_MachSpdKPH_Signed rtb_UnitDelay_pt3t;
  dt_libinfo_MachSpdKPH_Signed rtb_Merge_eyqe;
  dt_libinfo_MachSpdKPH_Signed rtb_UnitDelay1_awom;
  dt_libinfo_MachSpdKPH_Signed rtb_UnitDelay_lqy0;
  dt_libinfo_MachSpdKPH_Signed rtb_Merge_e5fa;
  dt_libinfo_Angle rtb_LookupTable;
  dt_libinfo_Unsigned8 rtb_VectorConcatenate1[7];
  boolean_T rtb_LogicalOperator_n2oa;
  boolean_T rtb_LogicalOperator_bepi;
  boolean_T rtb_LogicalOperator_dmm0;
  boolean_T rtb_LogicalOperator_fbxv;
  boolean_T rtb_LogicalOperator;
  boolean_T rtb_LogicalOperator_inbd;
  boolean_T rtb_DataTypeConversion2;
  boolean_T rtb_DataTypeConversion3_js1i;
  boolean_T rtb_DataTypeConversion4;
  boolean_T rtb_DataTypeConversion5;
  boolean_T rtb_DataTypeConversion6;
  boolean_T rtb_DataTypeConversion7;
  boolean_T rtb_DataTypeConversion8;
  real32_T rtb_DataTypeConversion;
  real32_T rtb_Product_fggn;
  real32_T rtb_Sum3;
  real32_T rtb_Sum1_kflo;
  dt_libinfo_single rtb_Merge;
  real32_T rtb_Switch;
  dt_libinfo_Count rtb_Divide_k0qy;
  dt_libinfo_Count rtb_Divide1;
  dt_libinfo_Count rtb_Divide2;
  boolean_T rtb_VectorConcatenate2[7];
  dt_libinfo_Flag rtb_Merge1_mrd3;
  int8_t rtPrevAction;
  boolean_T rtb_UnitDelay_cxus;
  dt_libinfo_Flag rtb_UnitDelay_hhl4;
  boolean_T rtb_UnitDelay_mtyr;
  real32_T rtb_Sum1;
  real32_T rtb_UnitDelay2_dmbr;
  real32_T rtb_Sum1_m10g;
  dt_libinfo_Flag rtb_UnitDelay1_kz4h;
  int32_t rtb_Add_ltmq;
  uint32_t rtb_MinMax;
  int32_t rtb_Sum1_klni;
  dt_libinfo_Ratio_hiRes rtb_Switch_lbk1;
  int32_t rtb_InitToInput;
  dt_libinfo_Time20msLong rtb_Sum_hn32;
  int16_t rtb_Switch_fod;
  int64_T tmp;

  /* UnitDelay: '<S310>/Unit Delay' */
  rtb_UnitDelay_cxus = LIBINFO_WL_00_DWork->UnitDelay_DSTATE_irpf;

  /* UnitDelay: '<S304>/Unit Delay' */
  rtb_UnitDelay_hhl4 = LIBINFO_WL_00_DWork->UnitDelay_DSTATE_lqwq;

  /* UnitDelay: '<S261>/Unit Delay' */
  rtb_UnitDelay_mtyr = LIBINFO_WL_00_DWork->UnitDelay_DSTATE_btkl;

  /* Outputs for Atomic SubSystem: '<S1>/LIBINFO_WL_00_InPrc' */
  /* SignalConversion: '<S6>/Copy' incorporates:
   *  Inport: '<Root>/ground_speed'
   */
  LIBINFO_WL_00_B->GroundSpeed_iutz = LIBINFO_WL_00_U_ground_speed;

  /* MinMax: '<S63>/MinMax' incorporates:
   *  Inport: '<Root>/ground_speed'
   */
  if (LIBINFO_WL_00_U_ground_speed <= -2) {
    rtb_Switch_lbk1 = LIBINFO_WL_00_U_ground_speed;
  } else {
    rtb_Switch_lbk1 = -2;
  }

  /* Sum: '<S63>/Sum' incorporates:
   *  Constant: '<S63>/Constant2'
   *  MinMax: '<S63>/MinMax'
   */
  rtb_InitToInput = rtb_Switch_lbk1 + 32769;

  /* Switch: '<S63>/Switch' incorporates:
   *  Constant: '<S63>/Valid'
   *  Sum: '<S63>/Sum'
   */
  if (((int16_t)rtb_InitToInput) > 32) {
    LIBINFO_WL_00_B->GroundSpeedUnknown = 0U;
  } else {
    LIBINFO_WL_00_B->GroundSpeedUnknown = (dt_libinfo_Status)((int16_t)
      rtb_InitToInput);
  }

  /* Saturate: '<S3>/Saturation1' */
  if (!(LIBINFO_WL_00_B->GroundSpeedUnknown <= 1)) {
    /* Switch: '<S63>/Switch' incorporates:
     *  SignalConversion: '<S7>/Copy'
     */
    LIBINFO_WL_00_B->GroundSpeedUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation1' */

  /* SignalConversion: '<S18>/Copy' incorporates:
   *  Inport: '<Root>/payload_ratio'
   */
  LIBINFO_WL_00_B->LoadRatio = LIBINFO_WL_00_U_payload_ratio;

  /* SignalConversion: '<S29>/Copy' incorporates:
   *  Inport: '<Root>/payload_ratio_status'
   */
  LIBINFO_WL_00_B->LoadRatioStatus = LIBINFO_WL_00_U_payload_ratio_status;

  /* SignalConversion: '<S40>/Copy' incorporates:
   *  Inport: '<Root>/payload_ratio_raw'
   */
  LIBINFO_WL_00_B->LoadRatioRaw = LIBINFO_WL_00_U_payload_ratio_raw;

  /* SignalConversion: '<S49>/Copy' incorporates:
   *  Inport: '<Root>/payload_ratio_raw_status'
   */
  LIBINFO_WL_00_B->LoadRatioRawStatus = LIBINFO_WL_00_U_payload_ratio_raw_status;

  /* SignalConversion: '<S50>/Copy' incorporates:
   *  Inport: '<Root>/ext_force_normalized'
   */
  LIBINFO_WL_00_B->ExternalForceNormalized_p2pg =
    LIBINFO_WL_00_U_ext_force_normalized;

  /* MinMax: '<S58>/MinMax' incorporates:
   *  Inport: '<Root>/ext_force_normalized'
   */
  if (LIBINFO_WL_00_U_ext_force_normalized <= -2) {
    rtb_Switch_lbk1 = LIBINFO_WL_00_U_ext_force_normalized;
  } else {
    rtb_Switch_lbk1 = -2;
  }

  /* Sum: '<S58>/Sum' incorporates:
   *  Constant: '<S58>/Constant2'
   *  MinMax: '<S58>/MinMax'
   */
  rtb_InitToInput = rtb_Switch_lbk1 + 32769;

  /* Switch: '<S58>/Switch' incorporates:
   *  Constant: '<S58>/Valid'
   *  Sum: '<S58>/Sum'
   */
  if (((int16_t)rtb_InitToInput) > 32) {
    LIBINFO_WL_00_B->ExternalForceunknown = 0U;
  } else {
    LIBINFO_WL_00_B->ExternalForceunknown = (dt_libinfo_Status)((int16_t)
      rtb_InitToInput);
  }

  /* Saturate: '<S3>/Saturation20' */
  if (!(LIBINFO_WL_00_B->ExternalForceunknown <= 1)) {
    /* Switch: '<S58>/Switch' incorporates:
     *  SignalConversion: '<S51>/Copy'
     */
    LIBINFO_WL_00_B->ExternalForceunknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation20' */

  /* SignalConversion: '<S52>/Copy' incorporates:
   *  Inport: '<Root>/lift_valve_cmd'
   */
  LIBINFO_WL_00_B->LiftValveCmd_lf5w = LIBINFO_WL_00_U_lift_valve_cmd;

  /* MinMax: '<S70>/MinMax' incorporates:
   *  Inport: '<Root>/lift_valve_cmd'
   */
  if (LIBINFO_WL_00_U_lift_valve_cmd <= -2) {
    rtb_Switch_lbk1 = LIBINFO_WL_00_U_lift_valve_cmd;
  } else {
    rtb_Switch_lbk1 = -2;
  }

  /* Sum: '<S70>/Sum' incorporates:
   *  Constant: '<S70>/Constant2'
   *  MinMax: '<S70>/MinMax'
   */
  rtb_InitToInput = rtb_Switch_lbk1 + 32769;

  /* Switch: '<S70>/Switch' incorporates:
   *  Constant: '<S70>/Valid'
   *  Sum: '<S70>/Sum'
   */
  if (((int16_t)rtb_InitToInput) > 32) {
    LIBINFO_WL_00_B->LiftValveCmdUnknown = 0U;
  } else {
    LIBINFO_WL_00_B->LiftValveCmdUnknown = (dt_libinfo_Status)((int16_t)
      rtb_InitToInput);
  }

  /* Saturate: '<S3>/Saturation19' */
  if (!(LIBINFO_WL_00_B->LiftValveCmdUnknown <= 1)) {
    /* Switch: '<S70>/Switch' incorporates:
     *  SignalConversion: '<S53>/Copy'
     */
    LIBINFO_WL_00_B->LiftValveCmdUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation19' */

  /* MinMax: '<S69>/MinMax' incorporates:
   *  Inport: '<Root>/tilt_valve_cmd'
   */
  if (LIBINFO_WL_00_U_tilt_valve_cmd <= -2) {
    rtb_Switch_lbk1 = LIBINFO_WL_00_U_tilt_valve_cmd;
  } else {
    rtb_Switch_lbk1 = -2;
  }

  /* Sum: '<S69>/Sum' incorporates:
   *  Constant: '<S69>/Constant2'
   *  MinMax: '<S69>/MinMax'
   */
  rtb_InitToInput = rtb_Switch_lbk1 + 32769;

  /* Switch: '<S69>/Switch' incorporates:
   *  Constant: '<S69>/Valid'
   *  Sum: '<S69>/Sum'
   */
  if (((int16_t)rtb_InitToInput) > 32) {
    LIBINFO_WL_00_B->TiltValveCmdUnknown = 0U;
  } else {
    LIBINFO_WL_00_B->TiltValveCmdUnknown = (dt_libinfo_Status)((int16_t)
      rtb_InitToInput);
  }

  /* Saturate: '<S3>/Saturation18' */
  if (!(LIBINFO_WL_00_B->TiltValveCmdUnknown <= 1)) {
    /* Switch: '<S69>/Switch' incorporates:
     *  SignalConversion: '<S8>/Copy'
     */
    LIBINFO_WL_00_B->TiltValveCmdUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation18' */

  /* SignalConversion: '<S9>/Copy' incorporates:
   *  Inport: '<Root>/tilt_valve_cmd'
   */
  LIBINFO_WL_00_B->TiltValveCmd_bbs3 = LIBINFO_WL_00_U_tilt_valve_cmd;

  /* SignalConversion: '<S10>/Copy' incorporates:
   *  Inport: '<Root>/bucket_angle'
   */
  LIBINFO_WL_00_B->BucketAngle_bg5r = LIBINFO_WL_00_U_bucket_angle;

  /* MinMax: '<S65>/MinMax' incorporates:
   *  Inport: '<Root>/bucket_angle'
   */
  if (LIBINFO_WL_00_U_bucket_angle <= -2) {
    rtb_Switch_lbk1 = LIBINFO_WL_00_U_bucket_angle;
  } else {
    rtb_Switch_lbk1 = -2;
  }

  /* Sum: '<S65>/Sum' incorporates:
   *  Constant: '<S65>/Constant2'
   *  MinMax: '<S65>/MinMax'
   */
  rtb_InitToInput = rtb_Switch_lbk1 + 32769;

  /* Switch: '<S65>/Switch' incorporates:
   *  Constant: '<S65>/Valid'
   *  Sum: '<S65>/Sum'
   */
  if (((int16_t)rtb_InitToInput) > 32) {
    LIBINFO_WL_00_B->BucketAngleUnknown = 0U;
  } else {
    LIBINFO_WL_00_B->BucketAngleUnknown = (dt_libinfo_Status)((int16_t)
      rtb_InitToInput);
  }

  /* Saturate: '<S3>/Saturation17' */
  if (!(LIBINFO_WL_00_B->BucketAngleUnknown <= 1)) {
    /* Switch: '<S65>/Switch' incorporates:
     *  SignalConversion: '<S11>/Copy'
     */
    LIBINFO_WL_00_B->BucketAngleUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation17' */

  /* SignalConversion: '<S12>/Copy' incorporates:
   *  Inport: '<Root>/lift_angle'
   */
  LIBINFO_WL_00_B->LiftAngle_bgyb = LIBINFO_WL_00_U_lift_angle;

  /* MinMax: '<S67>/MinMax' incorporates:
   *  Inport: '<Root>/lift_angle'
   */
  if (LIBINFO_WL_00_U_lift_angle <= -2) {
    rtb_Switch_lbk1 = LIBINFO_WL_00_U_lift_angle;
  } else {
    rtb_Switch_lbk1 = -2;
  }

  /* Sum: '<S67>/Sum' incorporates:
   *  Constant: '<S67>/Constant2'
   *  MinMax: '<S67>/MinMax'
   */
  rtb_InitToInput = rtb_Switch_lbk1 + 32769;

  /* Switch: '<S67>/Switch' incorporates:
   *  Constant: '<S67>/Valid'
   *  Sum: '<S67>/Sum'
   */
  if (((int16_t)rtb_InitToInput) > 32) {
    LIBINFO_WL_00_B->LiftAngleUnknown = 0U;
  } else {
    LIBINFO_WL_00_B->LiftAngleUnknown = (dt_libinfo_Status)((int16_t)
      rtb_InitToInput);
  }

  /* Saturate: '<S3>/Saturation16' */
  if (!(LIBINFO_WL_00_B->LiftAngleUnknown <= 1)) {
    /* Switch: '<S67>/Switch' incorporates:
     *  SignalConversion: '<S13>/Copy'
     */
    LIBINFO_WL_00_B->LiftAngleUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation16' */

  /* SignalConversion: '<S14>/Copy' incorporates:
   *  Inport: '<Root>/desired_gear'
   */
  LIBINFO_WL_00_B->DesiredGear = LIBINFO_WL_00_U_desired_gear;

  /* MinMax: '<S55>/MinMax' incorporates:
   *  Inport: '<Root>/desired_gear'
   */
  if (LIBINFO_WL_00_U_desired_gear <= -2) {
    rtb_Switch_lbk1 = LIBINFO_WL_00_U_desired_gear;
  } else {
    rtb_Switch_lbk1 = -2;
  }

  /* Sum: '<S55>/Sum' incorporates:
   *  Constant: '<S55>/Constant2'
   *  MinMax: '<S55>/MinMax'
   */
  rtb_InitToInput = rtb_Switch_lbk1 + 32769;

  /* Switch: '<S55>/Switch' incorporates:
   *  Constant: '<S55>/Valid'
   *  Sum: '<S55>/Sum'
   */
  if (((int16_t)rtb_InitToInput) > 32) {
    LIBINFO_WL_00_B->DesiredGearUnknown = 0U;
  } else {
    LIBINFO_WL_00_B->DesiredGearUnknown = (dt_libinfo_Status)((int16_t)
      rtb_InitToInput);
  }

  /* Saturate: '<S3>/Saturation15' */
  if (!(LIBINFO_WL_00_B->DesiredGearUnknown <= 1)) {
    /* Switch: '<S55>/Switch' incorporates:
     *  SignalConversion: '<S15>/Copy'
     */
    LIBINFO_WL_00_B->DesiredGearUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation15' */

  /* SignalConversion: '<S16>/Copy' incorporates:
   *  Inport: '<Root>/engine_speed'
   */
  LIBINFO_WL_00_B->EngineSpeed = LIBINFO_WL_00_U_engine_speed;

  /* MinMax: '<S66>/MinMax' incorporates:
   *  Inport: '<Root>/engine_speed'
   */
  if (LIBINFO_WL_00_U_engine_speed <= -2) {
    rtb_Switch_lbk1 = LIBINFO_WL_00_U_engine_speed;
  } else {
    rtb_Switch_lbk1 = -2;
  }

  /* Sum: '<S66>/Sum' incorporates:
   *  Constant: '<S66>/Constant2'
   *  MinMax: '<S66>/MinMax'
   */
  rtb_InitToInput = rtb_Switch_lbk1 + 32769;

  /* Switch: '<S66>/Switch' incorporates:
   *  Constant: '<S66>/Valid'
   *  Sum: '<S66>/Sum'
   */
  if (((int16_t)rtb_InitToInput) > 32) {
    LIBINFO_WL_00_B->EngineSpeedUnknown = 0U;
  } else {
    LIBINFO_WL_00_B->EngineSpeedUnknown = (dt_libinfo_Status)((int16_t)
      rtb_InitToInput);
  }

  /* Saturate: '<S3>/Saturation14' */
  if (!(LIBINFO_WL_00_B->EngineSpeedUnknown <= 1)) {
    /* Switch: '<S66>/Switch' incorporates:
     *  SignalConversion: '<S17>/Copy'
     */
    LIBINFO_WL_00_B->EngineSpeedUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation14' */

  /* SignalConversion: '<S19>/Copy' incorporates:
   *  Inport: '<Root>/tilt_lever_cmd'
   */
  LIBINFO_WL_00_B->TiltLeverCmd = LIBINFO_WL_00_U_tilt_lever_cmd;

  /* MinMax: '<S68>/MinMax' incorporates:
   *  Inport: '<Root>/tilt_lever_cmd'
   */
  if (LIBINFO_WL_00_U_tilt_lever_cmd <= -2) {
    rtb_Switch_lbk1 = LIBINFO_WL_00_U_tilt_lever_cmd;
  } else {
    rtb_Switch_lbk1 = -2;
  }

  /* Sum: '<S68>/Sum' incorporates:
   *  Constant: '<S68>/Constant2'
   *  MinMax: '<S68>/MinMax'
   */
  rtb_InitToInput = rtb_Switch_lbk1 + 32769;

  /* Switch: '<S68>/Switch' incorporates:
   *  Constant: '<S68>/Valid'
   *  Sum: '<S68>/Sum'
   */
  if (((int16_t)rtb_InitToInput) > 32) {
    LIBINFO_WL_00_B->TiltLeverCmdUnknown = 0U;
  } else {
    LIBINFO_WL_00_B->TiltLeverCmdUnknown = (dt_libinfo_Status)((int16_t)
      rtb_InitToInput);
  }

  /* Saturate: '<S3>/Saturation' */
  if (!(LIBINFO_WL_00_B->TiltLeverCmdUnknown <= 1)) {
    /* Switch: '<S68>/Switch' incorporates:
     *  SignalConversion: '<S20>/Copy'
     */
    LIBINFO_WL_00_B->TiltLeverCmdUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation' */

  /* SignalConversion: '<S21>/Copy' incorporates:
   *  Inport: '<Root>/tilt_cyl_position'
   */
  LIBINFO_WL_00_B->TiltCylinderPosition = LIBINFO_WL_00_U_tilt_cyl_position;

  /* MinMax: '<S64>/MinMax' incorporates:
   *  Inport: '<Root>/tilt_cyl_position'
   */
  if (LIBINFO_WL_00_U_tilt_cyl_position >= 65503) {
    rtb_Divide_k0qy = LIBINFO_WL_00_U_tilt_cyl_position;
  } else {
    rtb_Divide_k0qy = 65503U;
  }

  /* Sum: '<S64>/Sum' incorporates:
   *  Constant: '<S64>/Constant1'
   *  MinMax: '<S64>/MinMax'
   */
  rtb_InitToInput = rtb_Divide_k0qy - 65503;

  /* Switch: '<S64>/Switch' incorporates:
   *  Constant: '<S64>/Valid'
   *  Sum: '<S64>/Sum'
   */
  if (((uint16_t)rtb_InitToInput) > 0) {
    LIBINFO_WL_00_B->TiltCylinderPositionUnknown = (dt_libinfo_Status)((uint16_t)
      rtb_InitToInput);
  } else {
    LIBINFO_WL_00_B->TiltCylinderPositionUnknown = 0U;
  }

  /* Saturate: '<S3>/Saturation13' */
  if (!(LIBINFO_WL_00_B->TiltCylinderPositionUnknown <= 1)) {
    /* Switch: '<S64>/Switch' incorporates:
     *  SignalConversion: '<S22>/Copy'
     */
    LIBINFO_WL_00_B->TiltCylinderPositionUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation13' */

  /* SignalConversion: '<S23>/Copy' incorporates:
   *  Constant: '<S71>/Constant'
   *  Constant: '<S72>/Constant'
   *  DataTypeConversion: '<S3>/Data Type Conversion2'
   *  Inport: '<Root>/machine_idle'
   *  Logic: '<S3>/Logical Operator'
   *  RelationalOperator: '<S71>/Compare'
   *  RelationalOperator: '<S72>/Compare'
   */
  LIBINFO_WL_00_B->MachineIdle = (dt_libinfo_Unsigned16)
    ((LIBINFO_WL_00_U_machine_idle == 174) || (LIBINFO_WL_00_U_machine_idle ==
      1081));

  /* MinMax: '<S57>/MinMax' incorporates:
   *  Inport: '<Root>/machine_idle'
   */
  if (LIBINFO_WL_00_U_machine_idle >= 65503) {
    rtb_Divide_k0qy = LIBINFO_WL_00_U_machine_idle;
  } else {
    rtb_Divide_k0qy = 65503U;
  }

  /* Sum: '<S57>/Sum' incorporates:
   *  Constant: '<S57>/Constant1'
   *  MinMax: '<S57>/MinMax'
   */
  rtb_InitToInput = rtb_Divide_k0qy - 65503;

  /* Switch: '<S57>/Switch' incorporates:
   *  Constant: '<S57>/Valid'
   *  Sum: '<S57>/Sum'
   */
  if (((uint16_t)rtb_InitToInput) > 0) {
    LIBINFO_WL_00_B->MachineIdleUnknown = (dt_libinfo_Status)((uint16_t)
      rtb_InitToInput);
  } else {
    LIBINFO_WL_00_B->MachineIdleUnknown = 0U;
  }

  /* Saturate: '<S3>/Saturation12' */
  if (!(LIBINFO_WL_00_B->MachineIdleUnknown <= 1)) {
    /* Switch: '<S57>/Switch' incorporates:
     *  SignalConversion: '<S24>/Copy'
     */
    LIBINFO_WL_00_B->MachineIdleUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation12' */

  /* SignalConversion: '<S25>/Copy' incorporates:
   *  Inport: '<Root>/key_switch'
   */
  LIBINFO_WL_00_B->KeySwitchOn = LIBINFO_WL_00_U_key_switch;

  /* SignalConversion: '<S26>/Copy' incorporates:
   *  Inport: '<Root>/real_time'
   */
  LIBINFO_WL_00_B->GlobalTime_bjze = LIBINFO_WL_00_U_real_time;

  /* SignalConversion: '<S27>/Copy' incorporates:
   *  Inport: '<Root>/fuel_high_res'
   */
  LIBINFO_WL_00_B->FuelHighRes = LIBINFO_WL_00_U_fuel_high_res;

  /* MinMax: '<S59>/MinMax' incorporates:
   *  Inport: '<Root>/fuel_high_res'
   */
  if (LIBINFO_WL_00_U_fuel_high_res >= 4294967263U) {
    rtb_MinMax = LIBINFO_WL_00_U_fuel_high_res;
  } else {
    rtb_MinMax = 4294967263U;
  }

  /* Sum: '<S59>/Sum' incorporates:
   *  Constant: '<S59>/Constant1'
   *  MinMax: '<S59>/MinMax'
   */
  tmp = ((int64_T)rtb_MinMax) - 4294967263L;
  if (tmp < 0L) {
    tmp = 0L;
  } else {
    if (tmp > 4294967295L) {
      tmp = 4294967295L;
    }
  }

  rtb_MinMax = (uint32_t)tmp;

  /* End of Sum: '<S59>/Sum' */

  /* Switch: '<S59>/Switch' incorporates:
   *  Constant: '<S59>/Valid'
   */
  if (rtb_MinMax > 0U) {
    LIBINFO_WL_00_B->TotalFuelUnknown = (uint8_t)rtb_MinMax;
  } else {
    LIBINFO_WL_00_B->TotalFuelUnknown = 0U;
  }

  /* Saturate: '<S3>/Saturation10' */
  if (!(LIBINFO_WL_00_B->TotalFuelUnknown <= 1)) {
    /* Switch: '<S59>/Switch' incorporates:
     *  SignalConversion: '<S47>/Copy'
     */
    LIBINFO_WL_00_B->TotalFuelUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation10' */

  /* SignalConversion: '<S28>/Copy' incorporates:
   *  Inport: '<Root>/fuel'
   */
  LIBINFO_WL_00_B->TotalFuel_gal = LIBINFO_WL_00_U_fuel;

  /* MinMax: '<S62>/MinMax' incorporates:
   *  Inport: '<Root>/fuel'
   */
  if (LIBINFO_WL_00_U_fuel >= 4294967263U) {
    rtb_MinMax = LIBINFO_WL_00_U_fuel;
  } else {
    rtb_MinMax = 4294967263U;
  }

  /* Sum: '<S62>/Sum' incorporates:
   *  Constant: '<S62>/Constant1'
   *  MinMax: '<S62>/MinMax'
   */
  tmp = ((int64_T)rtb_MinMax) - 4294967263L;
  if (tmp < 0L) {
    tmp = 0L;
  } else {
    if (tmp > 4294967295L) {
      tmp = 4294967295L;
    }
  }

  rtb_MinMax = (uint32_t)tmp;

  /* End of Sum: '<S62>/Sum' */

  /* Switch: '<S62>/Switch' incorporates:
   *  Constant: '<S62>/Valid'
   */
  if (rtb_MinMax > 0U) {
    LIBINFO_WL_00_B->TotalFuelLowResUnknown = (uint8_t)rtb_MinMax;
  } else {
    LIBINFO_WL_00_B->TotalFuelLowResUnknown = 0U;
  }

  /* Saturate: '<S3>/Saturation9' */
  if (!(LIBINFO_WL_00_B->TotalFuelLowResUnknown <= 1)) {
    /* Switch: '<S62>/Switch' incorporates:
     *  SignalConversion: '<S42>/Copy'
     */
    LIBINFO_WL_00_B->TotalFuelLowResUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation9' */

  /* SignalConversion: '<S30>/Copy' incorporates:
   *  Inport: '<Root>/fuel_rate'
   */
  LIBINFO_WL_00_B->FuelRate_LtrsPerHr = LIBINFO_WL_00_U_fuel_rate;

  /* MinMax: '<S60>/MinMax' incorporates:
   *  Inport: '<Root>/fuel_rate'
   */
  if (LIBINFO_WL_00_U_fuel_rate >= 65503) {
    rtb_Divide_k0qy = LIBINFO_WL_00_U_fuel_rate;
  } else {
    rtb_Divide_k0qy = 65503U;
  }

  /* Sum: '<S60>/Sum' incorporates:
   *  Constant: '<S60>/Constant1'
   *  MinMax: '<S60>/MinMax'
   */
  rtb_InitToInput = rtb_Divide_k0qy - 65503;

  /* Switch: '<S60>/Switch' incorporates:
   *  Constant: '<S60>/Valid'
   *  Sum: '<S60>/Sum'
   */
  if (((uint16_t)rtb_InitToInput) > 0) {
    LIBINFO_WL_00_B->FuelRateUnknown = (dt_libinfo_Status)((uint16_t)
      rtb_InitToInput);
  } else {
    LIBINFO_WL_00_B->FuelRateUnknown = 0U;
  }

  /* Saturate: '<S3>/Saturation8' */
  if (!(LIBINFO_WL_00_B->FuelRateUnknown <= 1)) {
    /* Switch: '<S60>/Switch' incorporates:
     *  SignalConversion: '<S33>/Copy'
     */
    LIBINFO_WL_00_B->FuelRateUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation8' */

  /* SignalConversion: '<S31>/Copy' incorporates:
   *  Inport: '<Root>/fuel_rate_ard'
   */
  LIBINFO_WL_00_B->FuelRateARD_LtrsPerSec = LIBINFO_WL_00_U_fuel_rate_ard;

  /* MinMax: '<S61>/MinMax' incorporates:
   *  Inport: '<Root>/fuel_rate_ard'
   */
  if (LIBINFO_WL_00_U_fuel_rate_ard >= 65503) {
    rtb_Divide_k0qy = LIBINFO_WL_00_U_fuel_rate_ard;
  } else {
    rtb_Divide_k0qy = 65503U;
  }

  /* Sum: '<S61>/Sum' incorporates:
   *  Constant: '<S61>/Constant1'
   *  MinMax: '<S61>/MinMax'
   */
  rtb_InitToInput = rtb_Divide_k0qy - 65503;

  /* Switch: '<S61>/Switch' incorporates:
   *  Constant: '<S61>/Valid'
   *  Sum: '<S61>/Sum'
   */
  if (((uint16_t)rtb_InitToInput) > 0) {
    LIBINFO_WL_00_B->FuelRateARDUnknown = (dt_libinfo_Status)((uint16_t)
      rtb_InitToInput);
  } else {
    LIBINFO_WL_00_B->FuelRateARDUnknown = 0U;
  }

  /* Saturate: '<S3>/Saturation7' */
  if (!(LIBINFO_WL_00_B->FuelRateARDUnknown <= 1)) {
    /* Switch: '<S61>/Switch' incorporates:
     *  SignalConversion: '<S34>/Copy'
     */
    LIBINFO_WL_00_B->FuelRateARDUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation7' */

  /* Saturate: '<S3>/Saturation11' incorporates:
   *  Inport: '<Root>/realTime_status'
   */
  if (LIBINFO_WL_00_U_realTime_status <= 1) {
    /* SignalConversion: '<S32>/Copy' */
    LIBINFO_WL_00_B->GlobalTimeUnknown = LIBINFO_WL_00_U_realTime_status;
  } else {
    /* SignalConversion: '<S32>/Copy' */
    LIBINFO_WL_00_B->GlobalTimeUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation11' */

  /* SignalConversion: '<S35>/Copy' incorporates:
   *  Inport: '<Root>/gps_latitude'
   */
  LIBINFO_WL_00_B->GPSLatitude = LIBINFO_WL_00_U_gps_latitude;

  /* SignalConversion: '<S36>/Copy' incorporates:
   *  Inport: '<Root>/gps_longitude'
   */
  LIBINFO_WL_00_B->GPSLongitude = LIBINFO_WL_00_U_gps_longitude;

  /* Saturate: '<S3>/Saturation21' incorporates:
   *  Inport: '<Root>/gps_lat_long_status'
   */
  if (LIBINFO_WL_00_U_gps_lat_long_status <= 1) {
    /* SignalConversion: '<S37>/Copy' */
    LIBINFO_WL_00_B->GPSLatLongUnknown = LIBINFO_WL_00_U_gps_lat_long_status;
  } else {
    /* SignalConversion: '<S37>/Copy' */
    LIBINFO_WL_00_B->GPSLatLongUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation21' */

  /* SignalConversion: '<S38>/Copy' incorporates:
   *  Inport: '<Root>/payload_weight'
   */
  LIBINFO_WL_00_B->PayloadWeight = LIBINFO_WL_00_U_payload_weight;

  /* SignalConversion: '<S39>/Copy' incorporates:
   *  Inport: '<Root>/payloadCalcMethod'
   */
  LIBINFO_WL_00_B->PayloadCalcMethod = LIBINFO_WL_00_U_payloadCalcMethod;

  /* SignalConversion: '<S43>/Copy' incorporates:
   *  Constant: '<S54>/Constant'
   *  DataTypeConversion: '<S3>/Data Type Conversion1'
   *  Inport: '<Root>/payload_weight_status'
   *  RelationalOperator: '<S54>/Compare'
   */
  LIBINFO_WL_00_B->PayloadWeightUnknown = (dt_libinfo_Status)
    (LIBINFO_WL_00_U_payload_weight_status == 0);

  /* SignalConversion: '<S45>/Copy' incorporates:
   *  Inport: '<Root>/service_hour_meter'
   */
  LIBINFO_WL_00_B->ServiceHourMeter_f3nw = LIBINFO_WL_00_U_service_hour_meter;

  /* MinMax: '<S56>/MinMax' incorporates:
   *  Inport: '<Root>/service_hour_meter'
   */
  if (LIBINFO_WL_00_U_service_hour_meter >= 4294967263U) {
    rtb_MinMax = LIBINFO_WL_00_U_service_hour_meter;
  } else {
    rtb_MinMax = 4294967263U;
  }

  /* Sum: '<S56>/Sum' incorporates:
   *  Constant: '<S56>/Constant1'
   *  MinMax: '<S56>/MinMax'
   */
  tmp = ((int64_T)rtb_MinMax) - 4294967263L;
  if (tmp < 0L) {
    tmp = 0L;
  } else {
    if (tmp > 4294967295L) {
      tmp = 4294967295L;
    }
  }

  rtb_MinMax = (uint32_t)tmp;

  /* End of Sum: '<S56>/Sum' */

  /* Switch: '<S56>/Switch' incorporates:
   *  Constant: '<S56>/Valid'
   */
  if (rtb_MinMax > 0U) {
    LIBINFO_WL_00_B->ServiceHourMeterUnknown = (uint8_t)rtb_MinMax;
  } else {
    LIBINFO_WL_00_B->ServiceHourMeterUnknown = 0U;
  }

  /* Saturate: '<S3>/Saturation4' */
  if (!(LIBINFO_WL_00_B->ServiceHourMeterUnknown <= 1)) {
    /* Switch: '<S56>/Switch' incorporates:
     *  SignalConversion: '<S46>/Copy'
     */
    LIBINFO_WL_00_B->ServiceHourMeterUnknown = 1U;
  }

  /* End of Saturate: '<S3>/Saturation4' */

  /* SignalConversion: '<S44>/Copy' incorporates:
   *  Inport: '<Root>/timezone_offset'
   */
  LIBINFO_WL_00_B->TimeZoneOffset = LIBINFO_WL_00_U_timezone_offset;

  /* SignalConversion: '<S48>/Copy' incorporates:
   *  Constant: '<S73>/Constant'
   *  DataTypeConversion: '<S3>/Data Type Conversion3'
   *  Inport: '<Root>/Impl_operation_status'
   *  RelationalOperator: '<S73>/Compare'
   */
  LIBINFO_WL_00_B->ImplOperationStatus = (dt_libinfo_Unsigned16)
    (LIBINFO_WL_00_U_Impl_operation_status != 15);

  /* DataTypeConversion: '<S95>/Data Type Conversion' */
  LIBINFO_WL_00_B->DataTypeConversion = (LIBINFO_WL_00_B->KeySwitchOn != 0);

  /* Product: '<S95>/Divide' incorporates:
   *  Constant: '<S95>/Constant'
   */
  LIBINFO_WL_00_B->Divide = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_KeyStatus_MinDESTime)
    / 6U);

  /* Product: '<S95>/Divide1' incorporates:
   *  Constant: '<S95>/Constant1'
   */
  LIBINFO_WL_00_B->Divide1 = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_KeyStat_EngRunStateDebounce)
    / 6U);

  /* Chart: '<S95>/RunState' incorporates:
   *  Constant: '<S95>/Constant2'
   *  Constant: '<S95>/Constant4'
   */
  /* Gateway: ST_KeyStatus/RunState */
  /* During: ST_KeyStatus/RunState */
  if (LIBINFO_WL_00_DWork->is_active_c1_ST_Lib_KeyStatus == 0U) {
    /* Entry: ST_KeyStatus/RunState */
    LIBINFO_WL_00_DWork->is_active_c1_ST_Lib_KeyStatus = 1U;

    /* Entry Internal: ST_KeyStatus/RunState */
    LIBINFO_WL_00_DWork->is_active_EngineState = 1U;

    /* Entry Internal 'EngineState': '<S144>:25' */
    /* Transition: '<S144>:40' */
    if ((LIBINFO_WL_00_B->EngineSpeed <= 0) ||
        (LIBINFO_WL_00_B->EngineSpeedUnknown != 0)) {
      /* Transition: '<S144>:42' */
      LIBINFO_WL_00_DWork->is_EngineState = LIBINFO_WL_00_IN_NotRunning;

      /* Entry 'NotRunning': '<S144>:29' */
      LIBINFO_WL_00_DWork->EngineRunningRaw = FALSE;
      LIBINFO_WL_00_DWork->EngineRunningDebounced = FALSE;
    } else {
      /* Transition: '<S144>:47' */
      /* Transition: '<S144>:46' */
      /* Transition: '<S144>:45' */
      LIBINFO_WL_00_DWork->is_EngineState = LIBINFO_WL_00_IN_Running;

      /* Entry 'Running': '<S144>:28' */
      LIBINFO_WL_00_DWork->EngineRunningRaw = TRUE;
      LIBINFO_WL_00_DWork->EngineRunningDebounced = TRUE;
    }

    LIBINFO_WL_00_DWork->is_active_RunState = 1U;

    /* Entry Internal 'RunState': '<S144>:51' */
    /* Transition: '<S144>:64' */
    LIBINFO_WL_00_B->ST_KeyStatus_Commit = FALSE;
    if (LIBINFO_WL_00_B->DataTypeConversion) {
      /* Transition: '<S144>:66' */
      LIBINFO_WL_00_DWork->is_RunState = LIBINFO_WL_00_IN_KeyOn;

      /* Entry Internal 'KeyOn': '<S144>:5' */
      /* Transition: '<S144>:71' */
      LIBINFO_WL_00_B->ST_KeyStatus_ID = 26U;
      LIBINFO_WL_00_B->ST_KeyStatus_Commit = FALSE;
      if (LIBINFO_WL_00_DWork->EngineRunningDebounced) {
        /* Transition: '<S144>:74' */
        /* Transition: '<S144>:75' */
        LIBINFO_WL_00_DWork->is_KeyOn = LIBINFO_WL_00_IN_EngineOn;

        /* Entry 'EngineOn': '<S144>:11' */
        LIBINFO_WL_00_B->ST_KeyStatus_State = 0U;
        LIBINFO_WL_00_B->keyswitchOverride = TRUE;
      } else {
        /* Transition: '<S144>:72' */
        LIBINFO_WL_00_DWork->is_KeyOn = LIBINFO_WL_00_IN_EngineOff;

        /* Entry 'EngineOff': '<S144>:13' */
        LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;
        LIBINFO_WL_00_B->keyswitchOverride = TRUE;
      }
    } else {
      /* Transition: '<S144>:68' */
      /* Transition: '<S144>:69' */
      LIBINFO_WL_00_DWork->is_RunState = LIBINFO_WL_00_IN_KeyOff;

      /* Entry Internal 'KeyOff': '<S144>:6' */
      /* Transition: '<S144>:77' */
      LIBINFO_WL_00_B->ST_KeyStatus_ID = 27U;
      LIBINFO_WL_00_B->ST_KeyStatus_Commit = FALSE;
      LIBINFO_WL_00_DWork->is_KeyOff = LIBINFO_WL_00_IN_EngineOff_itep;

      /* Entry Internal 'EngineOff': '<S144>:16' */
      /* Transition: '<S144>:84' */
      LIBINFO_WL_00_B->keyswitchOverride = TRUE;
      LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;
      if (LIBINFO_WL_00_B->ST_KeyStatus_Commit) {
        /* Transition: '<S144>:89' */
        LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_00_IN_FinishCommit;
      } else {
        /* Transition: '<S144>:86' */
        /* Transition: '<S144>:91' */
        LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_0_IN_CommitEngineOff;

        /* Entry 'CommitEngineOff': '<S144>:90' */
        LIBINFO_WL_00_B->ST_KeyStatus_State = 2U;
        LIBINFO_WL_00_B->ST_KeyStatus_Commit = TRUE;
      }
    }
  } else {
    /* During 'EngineState': '<S144>:25' */
    switch (LIBINFO_WL_00_DWork->is_EngineState) {
     case LIBINFO_WL_00_IN_NotRunning:
      /* During 'NotRunning': '<S144>:29' */
      if ((LIBINFO_WL_00_B->EngineSpeed > 0) &&
          (!(LIBINFO_WL_00_B->EngineSpeedUnknown != 0))) {
        /* Transition: '<S144>:32' */
        LIBINFO_WL_00_DWork->is_EngineState = LIBINFO_WL_00_IN_Starting;

        /* Entry 'Starting': '<S144>:30' */
        LIBINFO_WL_00_DWork->EngineRunningRaw = TRUE;
        LIBINFO_WL_00_DWork->EngineRunningDebounced = FALSE;
        LIBINFO_WL_00_DWork->EngineRunningCounter = 1U;
      }
      break;

     case LIBINFO_WL_00_IN_Running:
      /* During 'Running': '<S144>:28' */
      if ((LIBINFO_WL_00_B->EngineSpeed <= 0) &&
          (!(LIBINFO_WL_00_B->EngineSpeedUnknown != 0))) {
        /* Transition: '<S144>:35' */
        LIBINFO_WL_00_DWork->is_EngineState = LIBINFO_WL_00_IN_Stopping;

        /* Entry 'Stopping': '<S144>:31' */
        LIBINFO_WL_00_DWork->EngineRunningRaw = FALSE;
        LIBINFO_WL_00_DWork->EngineRunningDebounced = TRUE;
        LIBINFO_WL_00_DWork->EngineRunningCounter = 1U;
      }
      break;

     case LIBINFO_WL_00_IN_Starting:
      /* During 'Starting': '<S144>:30' */
      if ((LIBINFO_WL_00_B->EngineSpeed <= 0) &&
          (!(LIBINFO_WL_00_B->EngineSpeedUnknown != 0))) {
        /* Transition: '<S144>:33' */
        LIBINFO_WL_00_DWork->is_EngineState = LIBINFO_WL_00_IN_NotRunning;

        /* Entry 'NotRunning': '<S144>:29' */
        LIBINFO_WL_00_DWork->EngineRunningRaw = FALSE;
        LIBINFO_WL_00_DWork->EngineRunningDebounced = FALSE;
      } else if (LIBINFO_WL_00_DWork->EngineRunningCounter >=
                 LIBINFO_WL_00_B->Divide1) {
        /* Transition: '<S144>:34' */
        LIBINFO_WL_00_DWork->is_EngineState = LIBINFO_WL_00_IN_Running;

        /* Entry 'Running': '<S144>:28' */
        LIBINFO_WL_00_DWork->EngineRunningRaw = TRUE;
        LIBINFO_WL_00_DWork->EngineRunningDebounced = TRUE;
      } else {
        LIBINFO_WL_00_DWork->EngineRunningCounter++;
      }
      break;

     default:
      /* During 'Stopping': '<S144>:31' */
      if ((LIBINFO_WL_00_B->EngineSpeed > 0) &&
          (!(LIBINFO_WL_00_B->EngineSpeedUnknown != 0))) {
        /* Transition: '<S144>:36' */
        LIBINFO_WL_00_DWork->is_EngineState = LIBINFO_WL_00_IN_Running;

        /* Entry 'Running': '<S144>:28' */
        LIBINFO_WL_00_DWork->EngineRunningRaw = TRUE;
        LIBINFO_WL_00_DWork->EngineRunningDebounced = TRUE;
      } else if (LIBINFO_WL_00_DWork->EngineRunningCounter >=
                 LIBINFO_WL_00_B->Divide1) {
        /* Transition: '<S144>:37' */
        LIBINFO_WL_00_DWork->is_EngineState = LIBINFO_WL_00_IN_NotRunning;

        /* Entry 'NotRunning': '<S144>:29' */
        LIBINFO_WL_00_DWork->EngineRunningRaw = FALSE;
        LIBINFO_WL_00_DWork->EngineRunningDebounced = FALSE;
      } else {
        LIBINFO_WL_00_DWork->EngineRunningCounter++;
      }
      break;
    }

    LIBINFO_WL_00_RunState(LIBINFO_WL_00_B, LIBINFO_WL_00_DWork);
  }

  /* End of Chart: '<S95>/RunState' */

  /* SignalConversion: '<S4>/ConcatBufferAtVector ConcatenateIn1' */
  LIBINFO_WL_00_B->VectorConcatenate[0] = LIBINFO_WL_00_B->ST_KeyStatus_State;

  /* Logic: '<S176>/Logical Operator' incorporates:
   *  Constant: '<S180>/Constant'
   *  Constant: '<S181>/Constant'
   *  RelationalOperator: '<S180>/Compare'
   *  RelationalOperator: '<S181>/Compare'
   */
  rtb_LogicalOperator = ((LIBINFO_WL_00_B->LoadRatioStatus == 1) ||
    (LIBINFO_WL_00_B->LoadRatioStatus == 4));

  /* Logic: '<S175>/Logical Operator' incorporates:
   *  Constant: '<S178>/Constant'
   *  Constant: '<S179>/Constant'
   *  RelationalOperator: '<S178>/Compare'
   *  RelationalOperator: '<S179>/Compare'
   */
  rtb_LogicalOperator_inbd = ((LIBINFO_WL_00_B->LoadRatioRawStatus == 1) ||
    (LIBINFO_WL_00_B->LoadRatioRawStatus == 4));

  /* DataTypeConversion: '<S99>/Data Type Conversion2' */
  rtb_DataTypeConversion2 = (LIBINFO_WL_00_B->BucketAngleUnknown != 0);

  /* DataTypeConversion: '<S99>/Data Type Conversion3' */
  rtb_DataTypeConversion3_js1i = (LIBINFO_WL_00_B->LiftAngleUnknown != 0);

  /* DataTypeConversion: '<S99>/Data Type Conversion4' */
  rtb_DataTypeConversion4 = (LIBINFO_WL_00_B->TiltCylinderPositionUnknown != 0);

  /* DataTypeConversion: '<S99>/Data Type Conversion5' */
  rtb_DataTypeConversion5 = (LIBINFO_WL_00_B->EngineSpeedUnknown != 0);

  /* DataTypeConversion: '<S99>/Data Type Conversion6' */
  rtb_DataTypeConversion6 = (LIBINFO_WL_00_B->DesiredGearUnknown != 0);

  /* DataTypeConversion: '<S99>/Data Type Conversion7' */
  rtb_DataTypeConversion7 = (LIBINFO_WL_00_B->TiltLeverCmdUnknown != 0);

  /* DataTypeConversion: '<S99>/Data Type Conversion8' */
  rtb_DataTypeConversion8 = (LIBINFO_WL_00_B->GroundSpeedUnknown != 0);

  /* Chart: '<S99>/UnknownState' incorporates:
   *  Constant: '<S99>/Constant'
   *  Constant: '<S99>/Constant1'
   *  Constant: '<S99>/Constant2'
   *  Product: '<S99>/Divide'
   *  Product: '<S99>/Product'
   */
  /* Gateway: ST_Unknown/UnknownState */
  /* During: ST_Unknown/UnknownState */
  if (LIBINFO_WL_00_DWork->is_active_c1_ST_Lib_Unknown_MWL == 0U) {
    /* Entry: ST_Unknown/UnknownState */
    LIBINFO_WL_00_DWork->is_active_c1_ST_Lib_Unknown_MWL = 1U;

    /* Entry Internal: ST_Unknown/UnknownState */
    LIBINFO_WL_00_DWork->is_active_Main = 1U;

    /* Entry Internal 'Main': '<S177>:130' */
    /* Transition: '<S177>:132' */
    LIBINFO_WL_00_DWork->is_Main = LIBINFO_WL_00_IN_NotUnknown;

    /* Entry 'NotUnknown': '<S177>:135' */
    LIBINFO_WL_00_B->ST_Unknown_Commit = FALSE;
    LIBINFO_WL_00_B->ST_Unknown_State = 0U;
    LIBINFO_WL_00_DWork->DebounceCounter = 0U;
  } else {
    /* During 'Main': '<S177>:130' */
    if (LIBINFO_WL_00_DWork->is_Main == LIBINFO_WL_00_IN_NotUnknown) {
      /* During 'NotUnknown': '<S177>:135' */
      if ((((((((rtb_LogicalOperator || rtb_LogicalOperator_inbd) ||
                rtb_DataTypeConversion2) || rtb_DataTypeConversion3_js1i) ||
              rtb_DataTypeConversion4) || rtb_DataTypeConversion5) ||
            rtb_DataTypeConversion6) || rtb_DataTypeConversion7) ||
          rtb_DataTypeConversion8) {
        /* Transition: '<S177>:136' */
        LIBINFO_WL_00_DWork->is_Main = LIBINFO_WL_00_IN_Unknown;

        /* Entry 'Unknown': '<S177>:33' */
        LIBINFO_WL_00_B->ST_Unknown_State = 2U;
        rtb_InitToInput = LIBINFO_WL_00_DWork->DebounceCounter + 1;
        if (rtb_InitToInput > 65535) {
          rtb_InitToInput = 65535;
        }

        LIBINFO_WL_00_DWork->DebounceCounter = (uint16_t)rtb_InitToInput;
      }
    } else {
      /* During 'Unknown': '<S177>:33' */
      if (((((((((!rtb_LogicalOperator) && (!rtb_LogicalOperator_inbd)) &&
                (!rtb_DataTypeConversion2)) && (!rtb_DataTypeConversion3_js1i)) &&
              (!rtb_DataTypeConversion4)) && (!rtb_DataTypeConversion5)) &&
            (!rtb_DataTypeConversion6)) && (!rtb_DataTypeConversion7)) &&
          (!rtb_DataTypeConversion8)) {
        /* Transition: '<S177>:138' */
        LIBINFO_WL_00_DWork->is_Main = LIBINFO_WL_00_IN_NotUnknown;

        /* Entry 'NotUnknown': '<S177>:135' */
        LIBINFO_WL_00_B->ST_Unknown_Commit = FALSE;
        LIBINFO_WL_00_B->ST_Unknown_State = 0U;
        LIBINFO_WL_00_DWork->DebounceCounter = 0U;
      } else if (LIBINFO_WL_00_DWork->DebounceCounter >= ((int32_t)(((uint32_t)
                    ((uint16_t)(((((real_T)
          LIBINFO_WL_00_M->
          LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_Unknown_CommitTime)
        * 0.02) * 60.0) / 0.02))) / 6U))) {
        /* Transition: '<S177>:140' */
        /* Transition: '<S177>:144' */
        /* Transition: '<S177>:145' */
        /*  Periodic Commit every 5 min  */
        LIBINFO_WL_00_B->ST_Unknown_Commit = TRUE;
        LIBINFO_WL_00_DWork->DebounceCounter = 0U;

        /* Transition: '<S177>:146' */
        LIBINFO_WL_00_DWork->is_Main = LIBINFO_WL_00_IN_Unknown;

        /* Entry 'Unknown': '<S177>:33' */
        LIBINFO_WL_00_B->ST_Unknown_State = 2U;
        rtb_InitToInput = LIBINFO_WL_00_DWork->DebounceCounter + 1;
        if (rtb_InitToInput > 65535) {
          rtb_InitToInput = 65535;
        }

        LIBINFO_WL_00_DWork->DebounceCounter = (uint16_t)rtb_InitToInput;
      } else {
        LIBINFO_WL_00_B->ST_Unknown_ID = 14U;
        LIBINFO_WL_00_B->ST_Unknown_Commit = FALSE;
        rtb_InitToInput = LIBINFO_WL_00_DWork->DebounceCounter + 1;
        if (rtb_InitToInput > 65535) {
          rtb_InitToInput = 65535;
        }

        LIBINFO_WL_00_DWork->DebounceCounter = (uint16_t)rtb_InitToInput;
      }
    }
  }

  /* End of Chart: '<S99>/UnknownState' */

  /* SignalConversion: '<S4>/ConcatBufferAtVector ConcatenateIn2' */
  LIBINFO_WL_00_B->VectorConcatenate[1] = LIBINFO_WL_00_B->ST_Unknown_State;

  /* DataTypeConversion: '<S94>/Data Type Conversion4' */
  LIBINFO_WL_00_B->DataTypeConversion4 =
    (LIBINFO_WL_00_B->TiltCylinderPositionUnknown != 0);

  /* DataTypeConversion: '<S94>/Data Type Conversion1' */
  LIBINFO_WL_00_B->DataTypeConversion1 = (LIBINFO_WL_00_B->BucketAngleUnknown !=
    0);

  /* Logic: '<S92>/Logical Operator' incorporates:
   *  DataTypeConversion: '<S92>/Data Type Conversion'
   */
  rtb_LogicalOperator = !(LIBINFO_WL_00_B->BucketAngleUnknown != 0);

  /* Logic: '<S92>/Logical Operator2' incorporates:
   *  Constant: '<S92>/Constant'
   *  RelationalOperator: '<S92>/Relational Operator1'
   */
  LIBINFO_WL_00_B->IsFullDump = (rtb_LogicalOperator &&
    (LIBINFO_WL_00_B->BucketAngle_bg5r <=
     LIBINFO_WL_00_M->
     LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_BucketPos_FullDumpBucketAng));

  /* DataTypeConversion: '<S94>/Data Type Conversion2' */
  LIBINFO_WL_00_B->DataTypeConversion2 = (LIBINFO_WL_00_B->GroundSpeedUnknown !=
    0);

  /* DataTypeConversion: '<S93>/Data Type Conversion' */
  rtb_DataTypeConversion = ((real32_T)LIBINFO_WL_00_B->GroundSpeed_iutz) *
    0.00390625F;

  /* Switch: '<S105>/Switch' incorporates:
   *  DataTypeConversion: '<S93>/Data Type Conversion'
   *  UnitDelay: '<S105>/Unit Delay'
   *  UnitDelay: '<S105>/Unit Delay2'
   */
  if (LIBINFO_WL_00_DWork->UnitDelay_DSTATE_jcgr) {
    rtb_Product_fggn = ((real32_T)LIBINFO_WL_00_B->GroundSpeed_iutz) *
      0.00390625F;
  } else {
    rtb_Product_fggn = LIBINFO_WL_00_DWork->UnitDelay2_DSTATE;
  }

  /* End of Switch: '<S105>/Switch' */

  /* SampleTimeMath: '<S105>/Weighted Sample Time' incorporates:
   *  DataTypeConversion: '<S93>/Data Type Conversion'
   *  Sum: '<S105>/Subtract'
   *
   * About '<S105>/Weighted Sample Time':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_Sum3 = ((((real32_T)LIBINFO_WL_00_B->GroundSpeed_iutz) * 0.00390625F) -
              rtb_Product_fggn) * 8.33333302F;

  /* Switch: '<S111>/InitToInput' incorporates:
   *  Logic: '<S114>/Logical Operator'
   *  UnitDelay: '<S111>/Unit Delay1'
   *  UnitDelay: '<S113>/Unit Delay'
   */
  if (LIBINFO_WL_00_DWork->UnitDelay_DSTATE_mffg != 0) {
    rtb_Product_fggn = LIBINFO_WL_00_DWork->UnitDelay1_DSTATE;
  } else {
    rtb_Product_fggn = rtb_Sum3;
  }

  /* End of Switch: '<S111>/InitToInput' */

  /* Sum: '<S111>/Sum3' */
  rtb_Sum3 -= rtb_Product_fggn;

  /* Sum: '<S111>/Sum1' incorporates:
   *  Constant: '<S93>/Constant1'
   *  Product: '<S111>/Product'
   */
  rtb_Sum1 = ((((real32_T)
                LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p
                ->ST_Dig_AccelerationFiltrFactor) * 3.05175781E-5F) * rtb_Sum3)
    + rtb_Product_fggn;

  /* Switch: '<S112>/InitToInput' incorporates:
   *  Logic: '<S116>/Logical Operator'
   *  UnitDelay: '<S112>/Unit Delay1'
   *  UnitDelay: '<S115>/Unit Delay'
   */
  if (LIBINFO_WL_00_DWork->UnitDelay_DSTATE_ozyd != 0) {
    rtb_Product_fggn = LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_eht0;
  } else {
    rtb_Product_fggn = rtb_Sum1;
  }

  /* End of Switch: '<S112>/InitToInput' */

  /* Sum: '<S112>/Sum1' incorporates:
   *  Constant: '<S93>/Constant1'
   *  Product: '<S112>/Product'
   *  Sum: '<S112>/Sum3'
   */
  rtb_Sum1_kflo = ((rtb_Sum1 - rtb_Product_fggn) * (((real32_T)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_AccelerationFiltrFactor)
    * 3.05175781E-5F)) + rtb_Product_fggn;

  /* DataTypeConversion: '<S112>/Data Type Conversion' */
  LIBINFO_WL_00_B->MachineAccel = rtb_Sum1_kflo;

  /* Product: '<S93>/Divide' incorporates:
   *  Constant: '<S93>/Constant13'
   */
  LIBINFO_WL_00_B->Divide_ajge = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_DecelerationTriggerTime)
    / 6U);

  /* Product: '<S93>/Divide1' incorporates:
   *  Constant: '<S93>/Constant12'
   */
  LIBINFO_WL_00_B->Divide1_cxwl = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_DecelerationResetTime)
    / 6U);

  /* Product: '<S93>/Divide2' incorporates:
   *  Constant: '<S93>/Constant14'
   */
  LIBINFO_WL_00_B->Divide2 = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_DirShiftInhibitTime)
    / 6U);

  /* If: '<S109>/If' incorporates:
   *  Constant: '<S121>/Constant'
   *  Constant: '<S122>/Constant'
   *  Inport: '<S121>/payloadRatioIn'
   *  Inport: '<S122>/payloadRatioIn'
   */
  if (LIBINFO_WL_00_B->LoadRatioStatus == 0) {
    /* Outputs for IfAction SubSystem: '<S109>/ok' incorporates:
     *  ActionPort: '<S122>/Action Port'
     */
    rtb_Merge = LIBINFO_WL_00_B->LoadRatio;
    LIBINFO_WL_00_B->Merge1_mlst = FALSE;

    /* End of Outputs for SubSystem: '<S109>/ok' */
  } else if (LIBINFO_WL_00_B->LoadRatioStatus == 3) {
    /* Outputs for IfAction SubSystem: '<S109>/lowerStall' incorporates:
     *  ActionPort: '<S120>/Action Port'
     */
    /* RelationalOperator: '<S123>/Compare' incorporates:
     *  Constant: '<S123>/Constant'
     */
    LIBINFO_WL_00_B->Merge1_mlst = (LIBINFO_WL_00_B->LoadRatio < 0.0F);

    /* SignalConversion: '<S120>/Merge Assist' */
    rtb_Merge = LIBINFO_WL_00_B->LoadRatio;

    /* End of Outputs for SubSystem: '<S109>/lowerStall' */
  } else {
    /* Outputs for IfAction SubSystem: '<S109>/notOk' incorporates:
     *  ActionPort: '<S121>/Action Port'
     */
    rtb_Merge = LIBINFO_WL_00_B->LoadRatio;
    LIBINFO_WL_00_B->Merge1_mlst = TRUE;

    /* End of Outputs for SubSystem: '<S109>/notOk' */
  }

  /* End of If: '<S109>/If' */

  /* SignalConversion: '<S102>/Copy' */
  LIBINFO_WL_00_B->PayloadRatio = rtb_Merge;

  /* UnitDelay: '<S127>/Unit Delay' */
  rtb_DataTypeConversion5 = LIBINFO_WL_00_DWork->UnitDelay_DSTATE_avwe;

  /* Logic: '<S124>/Logical Operator' incorporates:
   *  Logic: '<S127>/Logical Operator1'
   *  UnitDelay: '<S127>/Unit Delay'
   */
  rtb_DataTypeConversion6 = ((!LIBINFO_WL_00_DWork->UnitDelay_DSTATE_avwe) ||
    (LIBINFO_WL_00_B->Merge1_mlst));

  /* UnitDelay: '<S127>/Unit Delay2' */
  rtb_UnitDelay2_dmbr = LIBINFO_WL_00_DWork->UnitDelay2_DSTATE_jo4u;

  /* Switch: '<S124>/Switch' incorporates:
   *  Bias: '<S127>/Bias'
   *  Constant: '<S124>/Constant'
   *  Product: '<S124>/Divide'
   *  SampleTimeMath: '<S124>/Weighted Sample Time'
   *  Sum: '<S124>/Subtract'
   *  UnitDelay: '<S127>/Unit Delay2'
   *
   * About '<S124>/Weighted Sample Time':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  if (rtb_DataTypeConversion6) {
    rtb_Product_fggn = 0.0F;
  } else {
    /* Bias: '<S127>/Bias' incorporates:
     *  UnitDelay: '<S127>/Unit Delay1'
     */
    tmp = ((int64_T)LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_phum) + 1L;
    if (tmp > 2147483647L) {
      tmp = 2147483647L;
    } else {
      if (tmp < -2147483648L) {
        tmp = -2147483648L;
      }
    }

    rtb_Product_fggn = ((real32_T)(((real_T)(rtb_Merge -
      LIBINFO_WL_00_DWork->UnitDelay2_DSTATE_jo4u)) / ((real_T)((int32_t)tmp))))
      * 8.33333302F;
  }

  /* End of Switch: '<S124>/Switch' */

  /* Logic: '<S110>/Logical Operator' incorporates:
   *  UnitDelay: '<S110>/Unit Delay1'
   */
  rtb_LogicalOperator_inbd = (rtb_DataTypeConversion6 ||
    (LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_fr1p));

  /* Switch: '<S125>/InitToInput' incorporates:
   *  Logic: '<S131>/Logical Operator'
   *  Logic: '<S131>/Logical Operator1'
   *  UnitDelay: '<S125>/Unit Delay1'
   *  UnitDelay: '<S130>/Unit Delay'
   */
  if ((LIBINFO_WL_00_DWork->UnitDelay_DSTATE_nciw != 0) &&
      (!rtb_LogicalOperator_inbd)) {
    rtb_Sum3 = LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_peb2;
  } else {
    rtb_Sum3 = rtb_Product_fggn;
  }

  /* End of Switch: '<S125>/InitToInput' */

  /* Sum: '<S125>/Sum3' */
  rtb_Product_fggn -= rtb_Sum3;

  /* Sum: '<S125>/Sum1' incorporates:
   *  Constant: '<S93>/Constant22'
   *  Product: '<S125>/Product'
   */
  rtb_Sum1_m10g = ((((real32_T)
                     LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p
                     ->ST_Dig_PyldRtioDrvtFiltrFactor) * 3.05175781E-5F) *
                   rtb_Product_fggn) + rtb_Sum3;

  /* Switch: '<S126>/InitToInput' incorporates:
   *  Logic: '<S133>/Logical Operator'
   *  Logic: '<S133>/Logical Operator1'
   *  UnitDelay: '<S126>/Unit Delay1'
   *  UnitDelay: '<S132>/Unit Delay'
   */
  if ((LIBINFO_WL_00_DWork->UnitDelay_DSTATE_b0xn != 0) &&
      (!rtb_LogicalOperator_inbd)) {
    rtb_Product_fggn = LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_mlq0;
  } else {
    rtb_Product_fggn = rtb_Sum1_m10g;
  }

  /* End of Switch: '<S126>/InitToInput' */

  /* Sum: '<S126>/Sum1' incorporates:
   *  Constant: '<S93>/Constant22'
   *  Product: '<S126>/Product'
   *  Sum: '<S126>/Sum3'
   */
  rtb_Sum3 = ((rtb_Sum1_m10g - rtb_Product_fggn) * (((real32_T)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_PyldRtioDrvtFiltrFactor)
    * 3.05175781E-5F)) + rtb_Product_fggn;

  /* DataTypeConversion: '<S126>/Data Type Conversion' */
  LIBINFO_WL_00_B->PayloadRatioDerivative = rtb_Sum3;

  /* SignalConversion: '<S100>/Copy' */
  LIBINFO_WL_00_B->PayloadRatioDerivative_f44j =
    LIBINFO_WL_00_B->PayloadRatioDerivative;

  /* DataTypeConversion: '<S93>/Data Type Conversion2' */
  LIBINFO_WL_00_B->DataTypeConversion2_o1n1 =
    (LIBINFO_WL_00_B->ExternalForceunknown != 0);

  /* Switch: '<S107>/Switch' incorporates:
   *  Constant: '<S107>/Constant'
   */
  if (LIBINFO_WL_00_B->ExternalForceunknown != 0) {
    rtb_Switch_lbk1 = 0;
  } else {
    rtb_Switch_lbk1 = LIBINFO_WL_00_B->ExternalForceNormalized_p2pg;
  }

  /* End of Switch: '<S107>/Switch' */

  /* Switch: '<S117>/InitToInput' incorporates:
   *  DataTypeConversion: '<S107>/Data Type Conversion'
   *  DataTypeConversion: '<S117>/Data Type Conversion1'
   *  Logic: '<S119>/Logical Operator'
   *  Logic: '<S119>/Logical Operator1'
   *  UnitDelay: '<S117>/Unit Delay1'
   *  UnitDelay: '<S118>/Unit Delay'
   */
  if ((LIBINFO_WL_00_DWork->UnitDelay_DSTATE_j315 != 0) &&
      (!(LIBINFO_WL_00_B->ExternalForceunknown != 0))) {
    rtb_InitToInput = LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_nof1;
  } else {
    rtb_InitToInput = (rtb_Switch_lbk1 << 15);
  }

  /* End of Switch: '<S117>/InitToInput' */

  /* Sum: '<S117>/Sum3' */
  tmp = (((((int64_T)rtb_Switch_lbk1) << 15) - ((int64_T)rtb_InitToInput)) >> 15);
  if (tmp > 32767L) {
    tmp = 32767L;
  } else {
    if (tmp < -32768L) {
      tmp = -32768L;
    }
  }

  /* Sum: '<S117>/Sum1' incorporates:
   *  Constant: '<S93>/Constant9'
   *  Product: '<S117>/Product'
   *  Sum: '<S117>/Sum3'
   */
  rtb_Sum1_klni = (((int16_t)tmp) *
                   LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p
                   ->ST_Dig_ExtrnlFrceSlwFiltrFactr) + rtb_InitToInput;

  /* DataTypeConversion: '<S117>/Data Type Conversion' */
  rtb_InitToInput = (rtb_Sum1_klni >> 15);
  if (rtb_InitToInput > 32767) {
    rtb_InitToInput = 32767;
  } else {
    if (rtb_InitToInput < -32768) {
      rtb_InitToInput = -32768;
    }
  }

  /* Sum: '<S107>/Subtract1' incorporates:
   *  DataTypeConversion: '<S117>/Data Type Conversion'
   */
  LIBINFO_WL_00_B->ExternalForceNormalizedDelta = (int16_t)(rtb_Switch_lbk1 -
    rtb_InitToInput);

  /* SignalConversion: '<S101>/Copy' incorporates:
   *  SampleTimeMath: '<S93>/Weighted Sample Time'
   *
   * About '<S93>/Weighted Sample Time':
   *  y = K where K = ( w * Ts )
   */
  LIBINFO_WL_00_B->SampleTime = 6U;

  /* Product: '<S93>/Divide3' incorporates:
   *  Constant: '<S93>/Constant15'
   */
  LIBINFO_WL_00_B->Divide3 = (uint16_t)((LIBINFO_WL_00_B->SampleTime ==
    ((uint32_t)0)) ? MAX_uint32_T : (((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_TentativeConfirmatnTime)
    / ((uint32_t)LIBINFO_WL_00_B->SampleTime)));

  /* Product: '<S93>/Divide4' incorporates:
   *  Constant: '<S93>/Constant16'
   */
  LIBINFO_WL_00_B->Divide4 = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_TentativeMaxTime)
    / 6U);

  /* UnitDelay: '<S4>/Unit Delay' */
  LIBINFO_WL_00_B->ST_Dump_State = LIBINFO_WL_00_DWork->UnitDelay_1_DSTATE;

  /* SignalConversion: '<S103>/Copy' */
  LIBINFO_WL_00_B->DumpState = LIBINFO_WL_00_B->ST_Dump_State;

  /* Logic: '<S92>/Logical Operator1' incorporates:
   *  Constant: '<S92>/Constant1'
   *  RelationalOperator: '<S92>/Relational Operator'
   */
  LIBINFO_WL_00_B->IsFullRack = (rtb_LogicalOperator &&
    (LIBINFO_WL_00_B->BucketAngle_bg5r >
     LIBINFO_WL_00_M->
     LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_BucketPos_FullRackBucketAng));

  /* SignalConversion: '<S104>/Copy' */
  LIBINFO_WL_00_B->IsFullRack_ou1b = LIBINFO_WL_00_B->IsFullRack;

  /* Product: '<S93>/Divide5' incorporates:
   *  Constant: '<S93>/Constant25'
   */
  LIBINFO_WL_00_B->Divide5 = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_ImplementsIdleTime)
    / 6U);

  /* UnitDelay: '<S93>/Unit Delay' */
  LIBINFO_WL_00_B->UnitDelay_jymm = LIBINFO_WL_00_DWork->UnitDelay_DSTATE_fwtf;

  /* Chart: '<S93>/Classifier' */
  /* Gateway: ST_Dig/Classifier */
  /* During: ST_Dig/Classifier */
  if (LIBINFO_WL_00_DWork->is_active_c6_ST_Lib_Dig_MWL == 0U) {
    /* Entry: ST_Dig/Classifier */
    LIBINFO_WL_00_DWork->is_active_c6_ST_Lib_Dig_MWL = 1U;

    /* Entry Internal: ST_Dig/Classifier */
    LIBINFO_WL_00_DWork->is_active_NotWorking_gji1 = 1U;

    /* Entry 'NotWorking': '<S106>:52' */
    LIBINFO_WL_00_DWork->notWorkingCounter_cq2l = 0U;

    /* Entry Internal 'NotWorking': '<S106>:52' */
    /* Transition: '<S106>:58' */
    LIBINFO_WL_00_DWork->is_NotWorking_pqry = LIBINFO_WL_00_IN_Idle;

    /* Entry 'Idle': '<S106>:56' */
    LIBINFO_WL_00_DWork->notWorking_mksr = TRUE;
    LIBINFO_WL_00_DWork->is_active_Main_f0rl = 1U;

    /* Entry Internal 'Main': '<S106>:51' */
    /* Transition: '<S106>:46' */
    LIBINFO_WL_00_DWork->is_Main_ibas = LIBINFO_WL_00_IN_Inactive;

    /* Entry 'Inactive': '<S106>:1' */
    LIBINFO_WL_00_B->complete = TRUE;
  } else {
    /* During 'NotWorking': '<S106>:52' */
    switch (LIBINFO_WL_00_DWork->is_NotWorking_pqry) {
     case LIBINFO_WL_00_IN_Active:
      /* During 'Active': '<S106>:55' */
      if (((LIBINFO_WL_00_B->LiftValveCmd_lf5w == 0) &&
           (LIBINFO_WL_00_B->TiltValveCmd_bbs3 == 0)) &&
          (LIBINFO_WL_00_B->GroundSpeed_iutz == 0)) {
        /* Transition: '<S106>:61' */
        LIBINFO_WL_00_DWork->is_NotWorking_pqry = LIBINFO_WL_00_IN_IdleDebounce;

        /* Entry 'IdleDebounce': '<S106>:57' */
        LIBINFO_WL_00_DWork->notWorkingCounter_cq2l = 1U;
      }
      break;

     case LIBINFO_WL_00_IN_Idle:
      /* During 'Idle': '<S106>:56' */
      if (((LIBINFO_WL_00_B->LiftValveCmd_lf5w != 0) ||
           (LIBINFO_WL_00_B->TiltValveCmd_bbs3 != 0)) ||
          (LIBINFO_WL_00_B->GroundSpeed_iutz != 0)) {
        /* Transition: '<S106>:60' */
        LIBINFO_WL_00_DWork->is_NotWorking_pqry = LIBINFO_WL_00_IN_Active;

        /* Entry 'Active': '<S106>:55' */
        LIBINFO_WL_00_DWork->notWorking_mksr = FALSE;
      }
      break;

     default:
      /* During 'IdleDebounce': '<S106>:57' */
      if (((LIBINFO_WL_00_B->LiftValveCmd_lf5w != 0) ||
           (LIBINFO_WL_00_B->TiltValveCmd_bbs3 != 0)) ||
          (LIBINFO_WL_00_B->GroundSpeed_iutz != 0)) {
        /* Transition: '<S106>:62' */
        LIBINFO_WL_00_DWork->is_NotWorking_pqry = LIBINFO_WL_00_IN_Active;

        /* Entry 'Active': '<S106>:55' */
        LIBINFO_WL_00_DWork->notWorking_mksr = FALSE;
      } else if (LIBINFO_WL_00_DWork->notWorkingCounter_cq2l >=
                 LIBINFO_WL_00_B->Divide5) {
        /* Transition: '<S106>:63' */
        LIBINFO_WL_00_DWork->is_NotWorking_pqry = LIBINFO_WL_00_IN_Idle;

        /* Entry 'Idle': '<S106>:56' */
        LIBINFO_WL_00_DWork->notWorking_mksr = TRUE;
      } else {
        LIBINFO_WL_00_DWork->notWorkingCounter_cq2l++;
      }
      break;
    }

    /* During 'Main': '<S106>:51' */
    if (LIBINFO_WL_00_DWork->is_Main_ibas == LIBINFO_WL_00_IN_Active) {
      /* During 'Active': '<S106>:2' */
      if ((LIBINFO_WL_00_B->UnitDelay_jymm != 2) || (LIBINFO_WL_00_B->DumpState ==
           2)) {
        /* Transition: '<S106>:4' */
        /* Exit Internal 'Active': '<S106>:2' */
        LIBINFO_WL_00_DWork->is_Active = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        LIBINFO_WL_00_DWork->is_Main_ibas = LIBINFO_WL_00_IN_Inactive;

        /* Entry 'Inactive': '<S106>:1' */
        LIBINFO_WL_00_B->complete = TRUE;
      } else {
        /* During 'Digging': '<S106>:43' */
        if (((LIBINFO_WL_00_GroundSpeedExit(LIBINFO_WL_00_M, LIBINFO_WL_00_B)) ||
             (LIBINFO_WL_00_RackExit(LIBINFO_WL_00_B))) ||
            (LIBINFO_WL_00_DWork->notWorking_mksr)) {
          /* Transition: '<S106>:44' */
          LIBINFO_WL_00_DWork->is_Active = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
          LIBINFO_WL_00_DWork->is_Main_ibas = LIBINFO_WL_00_IN_Inactive;

          /* Entry 'Inactive': '<S106>:1' */
          LIBINFO_WL_00_B->complete = TRUE;
        }
      }
    } else {
      /* During 'Inactive': '<S106>:1' */
      if (LIBINFO_WL_00_B->UnitDelay_jymm == 2) {
        /* Transition: '<S106>:3' */
        /* Exit 'Inactive': '<S106>:1' */
        LIBINFO_WL_00_B->complete = FALSE;
        LIBINFO_WL_00_DWork->is_Main_ibas = LIBINFO_WL_00_IN_Active;

        /* Entry 'Active': '<S106>:2' */
        /*  This is where we would progress through different types of material engagement, like dig or doze.
           For now, we only support dig */
        /* Entry Internal 'Active': '<S106>:2' */
        /* Transition: '<S106>:45' */
        LIBINFO_WL_00_DWork->is_Active = LIBINFO_WL_00_IN_Digging;
      }
    }
  }

  /* End of Chart: '<S93>/Classifier' */

  /* Chart: '<S93>/MaterialEngagementDetection' incorporates:
   *  Constant: '<S93>/Constant8'
   */
  /* Gateway: ST_Dig/MaterialEngagementDetection */
  /* During: ST_Dig/MaterialEngagementDetection */
  if (LIBINFO_WL_00_DWork->is_active_c7_ST_Lib_Dig_MWL == 0U) {
    /* Entry: ST_Dig/MaterialEngagementDetection */
    LIBINFO_WL_00_DWork->is_active_c7_ST_Lib_Dig_MWL = 1U;

    /* Entry Internal: ST_Dig/MaterialEngagementDetection */
    LIBINFO_WL_00_DWork->is_active_Deceleration = 1U;

    /* Entry 'Deceleration': '<S108>:6' */
    /* Entry Internal 'Deceleration': '<S108>:6' */
    /* Transition: '<S108>:28' */
    LIBINFO_WL_00_DWork->Decelerating = FALSE;
    LIBINFO_WL_00_DWork->is_Deceleration = LIBINFO_WL_00_IN_NotDecel;

    /* Entry Internal 'NotDecel': '<S108>:7' */
    /* Transition: '<S108>:30' */
    LIBINFO_WL_00_DWork->is_NotDecel = LIBINFO_WL_00_IN_Debounce;

    /* Entry 'Debounce': '<S108>:13' */
    LIBINFO_WL_00_DWork->DecelCounter = 1U;
    LIBINFO_WL_00_DWork->is_active_DirectionShiftInhibit = 1U;

    /* Entry 'DirectionShiftInhibit': '<S108>:52' */
    LIBINFO_WL_00_DWork->DirShiftCounter = 0U;

    /* Entry Internal 'DirectionShiftInhibit': '<S108>:52' */
    /* Transition: '<S108>:60' */
    LIBINFO_WL_00_DWork->is_DirectionShiftInhibit = LIBINFO_WL_00_IN_Neutral;

    /* Entry 'Neutral': '<S108>:53' */
    LIBINFO_WL_00_DWork->GearTriggerInhibit = FALSE;
    LIBINFO_WL_00_DWork->is_active_Main_fpt2 = 1U;

    /* Entry 'Main': '<S108>:5' */
    LIBINFO_WL_00_DWork->TentativeCounter = 0U;

    /* Entry Internal 'Main': '<S108>:5' */
    /* Transition: '<S108>:256' */
    LIBINFO_WL_00_DWork->is_Main_nwt5 = LIBINFO_WL_00_IN_Inactive;

    /* Entry 'Inactive': '<S108>:1' */
    LIBINFO_WL_00_B->ST_Dig_State_prjn = 0U;
  } else {
    /* During 'Deceleration': '<S108>:6' */
    if (LIBINFO_WL_00_DWork->is_Deceleration == LIBINFO_WL_00_IN_Decel) {
      /* During 'Decel': '<S108>:8' */
      if (LIBINFO_WL_00_B->MachineAccel >
          LIBINFO_WL_00_M->
          LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_DecelerationTrigger)
      {
        /* Transition: '<S108>:24' */
        /* Exit Internal 'Decel': '<S108>:8' */
        LIBINFO_WL_00_DWork->is_Decel = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        LIBINFO_WL_00_DWork->is_Deceleration = LIBINFO_WL_00_IN_NotDecel;

        /* Entry Internal 'NotDecel': '<S108>:7' */
        /* Transition: '<S108>:30' */
        LIBINFO_WL_00_DWork->is_NotDecel = LIBINFO_WL_00_IN_Debounce;

        /* Entry 'Debounce': '<S108>:13' */
        LIBINFO_WL_00_DWork->DecelCounter = 1U;
      } else {
        switch (LIBINFO_WL_00_DWork->is_Decel) {
         case LIBINFO_WL_00_IN_Confirmed:
          break;

         default:
          /* During 'Debounce': '<S108>:10' */
          if (LIBINFO_WL_00_DWork->DecelCounter >= LIBINFO_WL_00_B->Divide_ajge)
          {
            /* Transition: '<S108>:26' */
            LIBINFO_WL_00_DWork->is_Decel = LIBINFO_WL_00_IN_Confirmed;

            /* Entry 'Confirmed': '<S108>:14' */
            LIBINFO_WL_00_DWork->Decelerating = TRUE;
          } else {
            LIBINFO_WL_00_DWork->DecelCounter++;
          }
          break;
        }
      }
    } else {
      /* During 'NotDecel': '<S108>:7' */
      if (LIBINFO_WL_00_B->MachineAccel <=
          LIBINFO_WL_00_M->
          LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dig_DecelerationTrigger)
      {
        /* Transition: '<S108>:23' */
        /* Exit Internal 'NotDecel': '<S108>:7' */
        LIBINFO_WL_00_DWork->is_NotDecel = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        LIBINFO_WL_00_DWork->is_Deceleration = LIBINFO_WL_00_IN_Decel;

        /* Entry Internal 'Decel': '<S108>:8' */
        /* Transition: '<S108>:27' */
        LIBINFO_WL_00_DWork->is_Decel = LIBINFO_WL_00_IN_Debounce;

        /* Entry 'Debounce': '<S108>:10' */
        LIBINFO_WL_00_DWork->DecelCounter = 1U;
      } else {
        switch (LIBINFO_WL_00_DWork->is_NotDecel) {
         case LIBINFO_WL_00_IN_Confirmed:
          break;

         default:
          /* During 'Debounce': '<S108>:13' */
          if (LIBINFO_WL_00_DWork->DecelCounter >= LIBINFO_WL_00_B->Divide1_cxwl)
          {
            /* Transition: '<S108>:31' */
            LIBINFO_WL_00_DWork->is_NotDecel = LIBINFO_WL_00_IN_Confirmed;

            /* Entry 'Confirmed': '<S108>:9' */
            LIBINFO_WL_00_DWork->Decelerating = FALSE;
          } else {
            LIBINFO_WL_00_DWork->DecelCounter++;
          }
          break;
        }
      }
    }

    /* During 'DirectionShiftInhibit': '<S108>:52' */
    switch (LIBINFO_WL_00_DWork->is_DirectionShiftInhibit) {
     case LIBINFO_WL_00_IN_Forward:
      /* During 'Forward': '<S108>:54' */
      if (LIBINFO_WL_00_B->DesiredGear < 0) {
        /* Transition: '<S108>:58' */
        LIBINFO_WL_00_DWork->is_DirectionShiftInhibit =
          LIBINFO_WL_00_IN_Transition;

        /* Entry 'Transition': '<S108>:57' */
        LIBINFO_WL_00_DWork->GearTriggerInhibit = TRUE;

        /* Entry Internal 'Transition': '<S108>:57' */
        /* Transition: '<S108>:165' */
        LIBINFO_WL_00_DWork->DirShiftCounter = 0U;
        if (LIBINFO_WL_00_DWork->DirShiftCounter < LIBINFO_WL_00_B->Divide2) {
          /* Transition: '<S108>:164' */
          /* Transition: '<S108>:167' */
          LIBINFO_WL_00_DWork->DirShiftCounter++;

          /* Transition: '<S108>:169' */
        } else {
          /* Transition: '<S108>:170' */
        }
      } else {
        if (LIBINFO_WL_00_B->DesiredGear == 0) {
          /* Transition: '<S108>:56' */
          LIBINFO_WL_00_DWork->is_DirectionShiftInhibit =
            LIBINFO_WL_00_IN_Neutral;

          /* Entry 'Neutral': '<S108>:53' */
          LIBINFO_WL_00_DWork->GearTriggerInhibit = FALSE;
        }
      }
      break;

     case LIBINFO_WL_00_IN_Neutral:
      /* During 'Neutral': '<S108>:53' */
      if (LIBINFO_WL_00_B->DesiredGear > 0) {
        /* Transition: '<S108>:55' */
        if (LIBINFO_WL_00_B->GroundSpeed_iutz < 0) {
          /* Transition: '<S108>:150' */
          LIBINFO_WL_00_DWork->is_DirectionShiftInhibit =
            LIBINFO_WL_00_IN_Transition;

          /* Entry 'Transition': '<S108>:57' */
          LIBINFO_WL_00_DWork->GearTriggerInhibit = TRUE;

          /* Entry Internal 'Transition': '<S108>:57' */
          /* Transition: '<S108>:165' */
          LIBINFO_WL_00_DWork->DirShiftCounter = 0U;
          if (LIBINFO_WL_00_DWork->DirShiftCounter < LIBINFO_WL_00_B->Divide2) {
            /* Transition: '<S108>:164' */
            /* Transition: '<S108>:167' */
            LIBINFO_WL_00_DWork->DirShiftCounter++;

            /* Transition: '<S108>:169' */
          } else {
            /* Transition: '<S108>:170' */
          }
        } else {
          /* Transition: '<S108>:151' */
          LIBINFO_WL_00_DWork->is_DirectionShiftInhibit =
            LIBINFO_WL_00_IN_Forward;

          /* Entry 'Forward': '<S108>:54' */
          LIBINFO_WL_00_DWork->GearTriggerInhibit = FALSE;
        }
      } else {
        if (LIBINFO_WL_00_B->DesiredGear < 0) {
          /* Transition: '<S108>:156' */
          if (LIBINFO_WL_00_B->GroundSpeed_iutz > 0) {
            /* Transition: '<S108>:157' */
            LIBINFO_WL_00_DWork->is_DirectionShiftInhibit =
              LIBINFO_WL_00_IN_Transition;

            /* Entry 'Transition': '<S108>:57' */
            LIBINFO_WL_00_DWork->GearTriggerInhibit = TRUE;

            /* Entry Internal 'Transition': '<S108>:57' */
            /* Transition: '<S108>:165' */
            LIBINFO_WL_00_DWork->DirShiftCounter = 0U;
            if (LIBINFO_WL_00_DWork->DirShiftCounter < LIBINFO_WL_00_B->Divide2)
            {
              /* Transition: '<S108>:164' */
              /* Transition: '<S108>:167' */
              LIBINFO_WL_00_DWork->DirShiftCounter++;

              /* Transition: '<S108>:169' */
            } else {
              /* Transition: '<S108>:170' */
            }
          } else {
            /* Transition: '<S108>:158' */
            LIBINFO_WL_00_DWork->is_DirectionShiftInhibit =
              LIBINFO_WL_00_IN_Reverse;

            /* Entry 'Reverse': '<S108>:152' */
            LIBINFO_WL_00_DWork->GearTriggerInhibit = FALSE;
          }
        }
      }
      break;

     case LIBINFO_WL_00_IN_Reverse:
      /* During 'Reverse': '<S108>:152' */
      if (LIBINFO_WL_00_B->DesiredGear > 0) {
        /* Transition: '<S108>:153' */
        LIBINFO_WL_00_DWork->is_DirectionShiftInhibit =
          LIBINFO_WL_00_IN_Transition;

        /* Entry 'Transition': '<S108>:57' */
        LIBINFO_WL_00_DWork->GearTriggerInhibit = TRUE;

        /* Entry Internal 'Transition': '<S108>:57' */
        /* Transition: '<S108>:165' */
        LIBINFO_WL_00_DWork->DirShiftCounter = 0U;
        if (LIBINFO_WL_00_DWork->DirShiftCounter < LIBINFO_WL_00_B->Divide2) {
          /* Transition: '<S108>:164' */
          /* Transition: '<S108>:167' */
          LIBINFO_WL_00_DWork->DirShiftCounter++;

          /* Transition: '<S108>:169' */
        } else {
          /* Transition: '<S108>:170' */
        }
      } else {
        if (LIBINFO_WL_00_B->DesiredGear == 0) {
          /* Transition: '<S108>:154' */
          LIBINFO_WL_00_DWork->is_DirectionShiftInhibit =
            LIBINFO_WL_00_IN_Neutral;

          /* Entry 'Neutral': '<S108>:53' */
          LIBINFO_WL_00_DWork->GearTriggerInhibit = FALSE;
        }
      }
      break;

     default:
      /* During 'Transition': '<S108>:57' */
      if ((LIBINFO_WL_00_DWork->DirShiftCounter >= LIBINFO_WL_00_B->Divide2) &&
          (LIBINFO_WL_00_B->DesiredGear == 0)) {
        /* Transition: '<S108>:59' */
        LIBINFO_WL_00_DWork->is_DirectionShiftInhibit = LIBINFO_WL_00_IN_Neutral;

        /* Entry 'Neutral': '<S108>:53' */
        LIBINFO_WL_00_DWork->GearTriggerInhibit = FALSE;
      } else if (((LIBINFO_WL_00_DWork->DirShiftCounter >=
                   LIBINFO_WL_00_B->Divide2) && (LIBINFO_WL_00_B->DesiredGear >
                   0)) && (LIBINFO_WL_00_B->GroundSpeed_iutz >= 0)) {
        /* Transition: '<S108>:159' */
        LIBINFO_WL_00_DWork->is_DirectionShiftInhibit = LIBINFO_WL_00_IN_Forward;

        /* Entry 'Forward': '<S108>:54' */
        LIBINFO_WL_00_DWork->GearTriggerInhibit = FALSE;
      } else if (((LIBINFO_WL_00_DWork->DirShiftCounter >=
                   LIBINFO_WL_00_B->Divide2) && (LIBINFO_WL_00_B->DesiredGear <
                   0)) && (LIBINFO_WL_00_B->GroundSpeed_iutz <= 0)) {
        /* Transition: '<S108>:160' */
        LIBINFO_WL_00_DWork->is_DirectionShiftInhibit = LIBINFO_WL_00_IN_Reverse;

        /* Entry 'Reverse': '<S108>:152' */
        LIBINFO_WL_00_DWork->GearTriggerInhibit = FALSE;
      } else {
        /* Transition: '<S108>:162' */
        if (LIBINFO_WL_00_DWork->DirShiftCounter < LIBINFO_WL_00_B->Divide2) {
          /* Transition: '<S108>:164' */
          /* Transition: '<S108>:167' */
          LIBINFO_WL_00_DWork->DirShiftCounter++;

          /* Transition: '<S108>:169' */
        } else {
          /* Transition: '<S108>:170' */
        }
      }
      break;
    }

    /* During 'Main': '<S108>:5' */
    switch (LIBINFO_WL_00_DWork->is_Main_nwt5) {
     case LIBINFO_WL_00_IN_Active:
      /* During 'Active': '<S108>:3' */
      if (LIBINFO_WL_00_B->complete) {
        /* Transition: '<S108>:4' */
        LIBINFO_WL_00_DWork->is_Main_nwt5 = LIBINFO_WL_00_IN_Inactive;

        /* Entry 'Inactive': '<S108>:1' */
        LIBINFO_WL_00_B->ST_Dig_State_prjn = 0U;
      }
      break;

     case LIBINFO_WL_00_IN_Inactive:
      /* During 'Inactive': '<S108>:1' */
      if (((((LIBINFO_WL_00_LiftAngleTrigger(LIBINFO_WL_00_M, LIBINFO_WL_00_B)) &&
             (LIBINFO_WL_0_BucketAngleTrigger(LIBINFO_WL_00_M, LIBINFO_WL_00_B)))
            && (LIBINFO_WL_0_GroundSpeedTrigger(LIBINFO_WL_00_M, LIBINFO_WL_00_B)))
           && (LIBINFO_WL_00_DecelTrigger(LIBINFO_WL_00_DWork))) &&
          ((LIBINFO_WL_ExternalForceTrigger(LIBINFO_WL_00_M, LIBINFO_WL_00_B,
             LIBINFO_WL_00_DWork)) || (PayloadDerivativeOverrideTrigge
            (LIBINFO_WL_00_M, LIBINFO_WL_00_B)))) {
        /* Transition: '<S108>:127' */
        LIBINFO_WL_00_DWork->is_Main_nwt5 = LIBINFO_WL_00_IN_Tentative;

        /* Entry 'Tentative': '<S108>:2' */
        LIBINFO_WL_00_B->ST_Dig_State_prjn = 1U;

        /* Entry Internal 'Tentative': '<S108>:2' */
        /* Transition: '<S108>:196' */
        LIBINFO_WL_00_DWork->TentativeCounter = 0U;
        if (LIBINF_PayloadDerivativeTrigger(LIBINFO_WL_00_M, LIBINFO_WL_00_B)) {
          /* Transition: '<S108>:295' */
          if (LIBINFO_WL_00_PayloadConfirm(LIBINFO_WL_00_M, LIBINFO_WL_00_B)) {
            /* Transition: '<S108>:309' */
            /* Transition: '<S108>:323' */
            LIBINFO_WL_00_DWork->is_Tentative = LIBINFO_WL__IN_PayloadConfirmed;

            /* Entry 'PayloadConfirmed': '<S108>:199' */
            LIBINFO_WL_00_DWork->TentativeCounter++;
          } else {
            /* Transition: '<S108>:311' */
            LIBINFO_WL_00_DWork->is_Tentative = LIBINFO_WL_IN_PayloadIncreasing;

            /* Entry 'PayloadIncreasing': '<S108>:288' */
            LIBINFO_WL_00_DWork->TentativeCounter++;
          }
        } else {
          /* Transition: '<S108>:293' */
          LIBINFO_WL_00_DWork->is_Tentative = LIBINFO_WL_00_IN_WaitForPayload;

          /* Entry 'WaitForPayload': '<S108>:195' */
          LIBINFO_WL_00_DWork->TentativeCounter++;
        }
      }
      break;

     default:
      /* During 'Tentative': '<S108>:2' */
      if ((!LIBINFO_WL_00_GroundSpeedRemain(LIBINFO_WL_00_M, LIBINFO_WL_00_B)) ||
          (LIBINFO_WL_00_DWork->TentativeCounter >= LIBINFO_WL_00_B->Divide4)) {
        /* Transition: '<S108>:130' */
        /* Exit Internal 'Tentative': '<S108>:2' */
        LIBINFO_WL_00_DWork->is_Tentative = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        LIBINFO_WL_00_DWork->is_Main_nwt5 = LIBINFO_WL_00_IN_Inactive;

        /* Entry 'Inactive': '<S108>:1' */
        LIBINFO_WL_00_B->ST_Dig_State_prjn = 0U;
      } else {
        switch (LIBINFO_WL_00_DWork->is_Tentative) {
         case LIBINFO_WL__IN_PayloadConfirmed:
          /* During 'PayloadConfirmed': '<S108>:199' */
          if (LIBINFO_WL_00_DWork->TentativeCounter >= LIBINFO_WL_00_B->Divide3)
          {
            /* Transition: '<S108>:303' */
            /* Transition: '<S108>:223' */
            LIBINFO_WL_00_DWork->is_Tentative = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
            LIBINFO_WL_00_DWork->is_Main_nwt5 = LIBINFO_WL_00_IN_Active;

            /* Entry 'Active': '<S108>:3' */
            LIBINFO_WL_00_B->ST_Dig_State_prjn = 2U;
          } else {
            LIBINFO_WL_00_DWork->TentativeCounter++;
          }
          break;

         case LIBINFO_WL_IN_PayloadIncreasing:
          /* During 'PayloadIncreasing': '<S108>:288' */
          if (LIBINFO_WL_00_PayloadConfirm(LIBINFO_WL_00_M, LIBINFO_WL_00_B)) {
            /* Transition: '<S108>:299' */
            if (LIBINFO_WL_00_DWork->TentativeCounter >=
                LIBINFO_WL_00_B->Divide3) {
              /* Transition: '<S108>:317' */
              /* Transition: '<S108>:321' */
              /* Transition: '<S108>:223' */
              LIBINFO_WL_00_DWork->is_Tentative =
                LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
              LIBINFO_WL_00_DWork->is_Main_nwt5 = LIBINFO_WL_00_IN_Active;

              /* Entry 'Active': '<S108>:3' */
              LIBINFO_WL_00_B->ST_Dig_State_prjn = 2U;
            } else {
              /* Transition: '<S108>:318' */
              LIBINFO_WL_00_DWork->is_Tentative =
                LIBINFO_WL__IN_PayloadConfirmed;

              /* Entry 'PayloadConfirmed': '<S108>:199' */
              LIBINFO_WL_00_DWork->TentativeCounter++;
            }
          } else if (LIBINFO__PayloadDerivativeReset(LIBINFO_WL_00_B)) {
            /* Transition: '<S108>:300' */
            LIBINFO_WL_00_DWork->is_Tentative = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
            LIBINFO_WL_00_DWork->is_Main_nwt5 = LIBINFO_WL_00_IN_Inactive;

            /* Entry 'Inactive': '<S108>:1' */
            LIBINFO_WL_00_B->ST_Dig_State_prjn = 0U;
          } else {
            LIBINFO_WL_00_DWork->TentativeCounter++;
          }
          break;

         default:
          /* During 'WaitForPayload': '<S108>:195' */
          if (LIBINF_PayloadDerivativeTrigger(LIBINFO_WL_00_M, LIBINFO_WL_00_B))
          {
            /* Transition: '<S108>:209' */
            if (LIBINFO_WL_00_PayloadConfirm(LIBINFO_WL_00_M, LIBINFO_WL_00_B))
            {
              /* Transition: '<S108>:219' */
              /* Transition: '<S108>:319' */
              if (LIBINFO_WL_00_DWork->TentativeCounter >=
                  LIBINFO_WL_00_B->Divide3) {
                /* Transition: '<S108>:317' */
                /* Transition: '<S108>:321' */
                /* Transition: '<S108>:223' */
                LIBINFO_WL_00_DWork->is_Tentative =
                  LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
                LIBINFO_WL_00_DWork->is_Main_nwt5 = LIBINFO_WL_00_IN_Active;

                /* Entry 'Active': '<S108>:3' */
                LIBINFO_WL_00_B->ST_Dig_State_prjn = 2U;
              } else {
                /* Transition: '<S108>:318' */
                LIBINFO_WL_00_DWork->is_Tentative =
                  LIBINFO_WL__IN_PayloadConfirmed;

                /* Entry 'PayloadConfirmed': '<S108>:199' */
                LIBINFO_WL_00_DWork->TentativeCounter++;
              }
            } else {
              /* Transition: '<S108>:314' */
              LIBINFO_WL_00_DWork->is_Tentative =
                LIBINFO_WL_IN_PayloadIncreasing;

              /* Entry 'PayloadIncreasing': '<S108>:288' */
              LIBINFO_WL_00_DWork->TentativeCounter++;
            }
          } else if (LIBINFO_WL_0_ExternalForceReset(LIBINFO_WL_00_M,
                      LIBINFO_WL_00_B)) {
            /* Transition: '<S108>:291' */
            LIBINFO_WL_00_DWork->is_Tentative = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
            LIBINFO_WL_00_DWork->is_Main_nwt5 = LIBINFO_WL_00_IN_Inactive;

            /* Entry 'Inactive': '<S108>:1' */
            LIBINFO_WL_00_B->ST_Dig_State_prjn = 0U;
          } else {
            LIBINFO_WL_00_DWork->TentativeCounter++;
          }
          break;
        }
      }
      break;
    }
  }

  /* End of Chart: '<S93>/MaterialEngagementDetection' */

  /* RelationalOperator: '<S135>/Compare' incorporates:
   *  Constant: '<S135>/Constant'
   */
  rtb_DataTypeConversion4 = (LIBINFO_WL_00_B->ST_Dig_State_prjn >= 1);

  /* Logic: '<S94>/Logical Operator1' incorporates:
   *  Logic: '<S94>/Logical Operator'
   *  UnitDelay: '<S94>/Unit Delay'
   */
  LIBINFO_WL_00_B->DigTrigger = (rtb_DataTypeConversion4 &&
    (!LIBINFO_WL_00_DWork->UnitDelay_DSTATE_jnup));

  /* RelationalOperator: '<S145>/Compare' incorporates:
   *  Constant: '<S145>/Constant'
   */
  LIBINFO_WL_00_B->Compare = (LIBINFO_WL_00_B->LoadRatioStatus != 0);

  /* UnitDelay: '<S4>/Unit Delay' */
  LIBINFO_WL_00_B->ST_Dig_State = LIBINFO_WL_00_DWork->UnitDelay_3_DSTATE;

  /* UnitDelay: '<S4>/Unit Delay' */
  LIBINFO_WL_00_B->ST_Dump_StateIsFull = LIBINFO_WL_00_DWork->UnitDelay_5_DSTATE;

  /* Product: '<S96>/Divide1' incorporates:
   *  Constant: '<S96>/Constant3'
   */
  LIBINFO_WL_00_B->Divide1_bcq5 = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_LoadStat_LoadStatusDebounce)
    / 6U);

  /* Chart: '<S96>/Loaded' incorporates:
   *  Constant: '<S96>/Constant'
   *  Constant: '<S96>/Constant1'
   */
  /* Gateway: ST_Loaded/Loaded */
  /* During: ST_Loaded/Loaded */
  if (LIBINFO_WL_00_DWork->is_active_c5_ST_Lib_Loaded_MWL == 0U) {
    /* Entry: ST_Loaded/Loaded */
    LIBINFO_WL_00_DWork->is_active_c5_ST_Lib_Loaded_MWL = 1U;

    /* Entry Internal: ST_Loaded/Loaded */
    LIBINFO_WL_00_DWork->is_active_LoadStatus = 1U;

    /* Entry Internal 'LoadStatus': '<S147>:193' */
    /* Transition: '<S147>:194' */
    LIBINFO_WL_00_DWork->loadedCounter = 0U;
    LIBINFO_WL_00_DWork->unloadedCounter = 0U;
    if ((LIBINFO_WL_00_B->Compare) || (LIBINFO_WL_00_B->LoadRatio <
         (-LIBINFO_WL_00_M->
          LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_LoadStatus_UnloadedRatio)))
    {
      /* Transition: '<S147>:323' */
      /* Transition: '<S147>:322' */
      LIBINFO_WL_00_DWork->loadedCounter = 0U;
      LIBINFO_WL_00_DWork->unloadedCounter = 0U;
    } else {
      /* Transition: '<S147>:318' */
      if (LIBINFO_WL_00_B->LoadRatio >=
          LIBINFO_WL_00_M->
          LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_LoadStatus_LoadedRatio)
      {
        /* Transition: '<S147>:199' */
        LIBINFO_WL_00_IncLoadedCounter(LIBINFO_WL_00_B, LIBINFO_WL_00_DWork);
        LIBINFO_WL_0_DecUnloadedCounter(LIBINFO_WL_00_DWork);

        /* Transition: '<S147>:296' */
        /* Transition: '<S147>:299' */
        /* Transition: '<S147>:303' */
      } else {
        /* Transition: '<S147>:201' */
        if (LIBINFO_WL_00_B->LoadRatio <=
            LIBINFO_WL_00_M->
            LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_LoadStatus_UnloadedRatio)
        {
          /* Transition: '<S147>:203' */
          LIBINFO_WL_00_DecLoadedCounter(LIBINFO_WL_00_DWork);
          LIBINFO_WL_0_IncUnloadedCounter(LIBINFO_WL_00_B, LIBINFO_WL_00_DWork);

          /* Transition: '<S147>:299' */
          /* Transition: '<S147>:303' */
        } else {
          /* Transition: '<S147>:205' */
          /* Transition: '<S147>:301' */
          /* Transition: '<S147>:304' */
        }
      }

      /* Transition: '<S147>:320' */
    }

    LIBINFO_WL_00_DWork->is_active_Main_b3l0 = 1U;

    /* Entry Internal 'Main': '<S147>:192' */
    /* Transition: '<S147>:8' */
    LIBINFO_WL_00_DWork->is_Main_ezny = LIBINFO_WL_00_IN_Unloaded;

    /* Entry Internal 'Unloaded': '<S147>:5' */
    /* Transition: '<S147>:325' */
    LIBINFO_WL_00_B->Loaded_dsd1 = FALSE;
    if ((LIBINFO_WL_00_B->ST_Dump_State == 2) &&
        (((LIBINFO_WL_00_B->ST_Dump_StateIsFull) || (LIBINFO_WL_00_B->Compare)) ||
         (LIBINFO_WL_00_B->LoadRatio <=
          LIBINFO_WL_00_M->
          LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_LoadStatus_UnloadedRatio)))
    {
      /* Transition: '<S147>:329' */
      /* Transition: '<S147>:333' */
      LIBINFO_WL_00_DWork->loadedCounter = 0U;
    } else {
      /* Transition: '<S147>:331' */
      /* Transition: '<S147>:334' */
    }
  } else {
    /* During 'LoadStatus': '<S147>:193' */
    /* Transition: '<S147>:196' */
    if ((LIBINFO_WL_00_B->Compare) || (LIBINFO_WL_00_B->LoadRatio <
         (-LIBINFO_WL_00_M->
          LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_LoadStatus_UnloadedRatio)))
    {
      /* Transition: '<S147>:323' */
      /* Transition: '<S147>:322' */
      LIBINFO_WL_00_DWork->loadedCounter = 0U;
      LIBINFO_WL_00_DWork->unloadedCounter = 0U;
    } else {
      /* Transition: '<S147>:318' */
      if (LIBINFO_WL_00_B->LoadRatio >=
          LIBINFO_WL_00_M->
          LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_LoadStatus_LoadedRatio)
      {
        /* Transition: '<S147>:199' */
        LIBINFO_WL_00_IncLoadedCounter(LIBINFO_WL_00_B, LIBINFO_WL_00_DWork);
        LIBINFO_WL_0_DecUnloadedCounter(LIBINFO_WL_00_DWork);

        /* Transition: '<S147>:296' */
        /* Transition: '<S147>:299' */
        /* Transition: '<S147>:303' */
      } else {
        /* Transition: '<S147>:201' */
        if (LIBINFO_WL_00_B->LoadRatio <=
            LIBINFO_WL_00_M->
            LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_LoadStatus_UnloadedRatio)
        {
          /* Transition: '<S147>:203' */
          LIBINFO_WL_00_DecLoadedCounter(LIBINFO_WL_00_DWork);
          LIBINFO_WL_0_IncUnloadedCounter(LIBINFO_WL_00_B, LIBINFO_WL_00_DWork);

          /* Transition: '<S147>:299' */
          /* Transition: '<S147>:303' */
        } else {
          /* Transition: '<S147>:205' */
          /* Transition: '<S147>:301' */
          /* Transition: '<S147>:304' */
        }
      }

      /* Transition: '<S147>:320' */
    }

    /* During 'Main': '<S147>:192' */
    if (LIBINFO_WL_00_DWork->is_Main_ezny == LIBINFO_WL_00_IN_Loaded) {
      /* During 'Loaded': '<S147>:6' */
      if ((LIBINFO_WL_00_B->ST_Dump_State == 2) &&
          (((LIBINFO_WL_00_B->ST_Dump_StateIsFull) || (LIBINFO_WL_00_B->Compare))
           || (LIBINFO_WL_00_B->LoadRatio <=
               LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p
               ->ST_LoadStatus_UnloadedRatio))) {
        /* Transition: '<S147>:12' */
        LIBINFO_WL_00_DWork->is_Main_ezny = LIBINFO_WL_00_IN_Unloaded;

        /* Entry Internal 'Unloaded': '<S147>:5' */
        /* Transition: '<S147>:325' */
        LIBINFO_WL_00_B->Loaded_dsd1 = FALSE;
        if ((LIBINFO_WL_00_B->ST_Dump_State == 2) &&
            (((LIBINFO_WL_00_B->ST_Dump_StateIsFull) ||
              (LIBINFO_WL_00_B->Compare)) || (LIBINFO_WL_00_B->LoadRatio <=
              LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p
              ->ST_LoadStatus_UnloadedRatio))) {
          /* Transition: '<S147>:329' */
          /* Transition: '<S147>:333' */
          LIBINFO_WL_00_DWork->loadedCounter = 0U;
        } else {
          /* Transition: '<S147>:331' */
          /* Transition: '<S147>:334' */
        }
      } else if ((LIBINFO_WL_00_B->ST_Dump_State != 1) &&
                 (LIBINFO_WL_00_DWork->unloadedCounter >=
                  LIBINFO_WL_00_B->Divide1_bcq5)) {
        /* Transition: '<S147>:311' */
        LIBINFO_WL_00_DWork->is_Main_ezny = LIBINFO_WL_00_IN_Unloaded;

        /* Entry Internal 'Unloaded': '<S147>:5' */
        /* Transition: '<S147>:325' */
        LIBINFO_WL_00_B->Loaded_dsd1 = FALSE;
        if ((LIBINFO_WL_00_B->ST_Dump_State == 2) &&
            (((LIBINFO_WL_00_B->ST_Dump_StateIsFull) ||
              (LIBINFO_WL_00_B->Compare)) || (LIBINFO_WL_00_B->LoadRatio <=
              LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p
              ->ST_LoadStatus_UnloadedRatio))) {
          /* Transition: '<S147>:329' */
          /* Transition: '<S147>:333' */
          LIBINFO_WL_00_DWork->loadedCounter = 0U;
        } else {
          /* Transition: '<S147>:331' */
          /* Transition: '<S147>:334' */
        }
      } else {
        /* Transition: '<S147>:336' */
        if (LIBINFO_WL_00_B->ST_Dig_State == 2) {
          /* Transition: '<S147>:341' */
          /* Transition: '<S147>:343' */
          LIBINFO_WL_00_DWork->unloadedCounter = 0U;
        } else {
          /* Transition: '<S147>:340' */
          /* Transition: '<S147>:344' */
        }
      }
    } else {
      /* During 'Unloaded': '<S147>:5' */
      if (LIBINFO_WL_00_B->ST_Dig_State == 2) {
        /* Transition: '<S147>:11' */
        LIBINFO_WL_00_DWork->is_Main_ezny = LIBINFO_WL_00_IN_Loaded;

        /* Entry Internal 'Loaded': '<S147>:6' */
        /* Transition: '<S147>:337' */
        LIBINFO_WL_00_B->Loaded_dsd1 = TRUE;
        if (LIBINFO_WL_00_B->ST_Dig_State == 2) {
          /* Transition: '<S147>:341' */
          /* Transition: '<S147>:343' */
          LIBINFO_WL_00_DWork->unloadedCounter = 0U;
        } else {
          /* Transition: '<S147>:340' */
          /* Transition: '<S147>:344' */
        }
      } else if ((LIBINFO_WL_00_B->ST_Dig_State != 1) &&
                 (LIBINFO_WL_00_DWork->loadedCounter >=
                  LIBINFO_WL_00_B->Divide1_bcq5)) {
        /* Transition: '<S147>:313' */
        LIBINFO_WL_00_DWork->is_Main_ezny = LIBINFO_WL_00_IN_Loaded;

        /* Entry Internal 'Loaded': '<S147>:6' */
        /* Transition: '<S147>:337' */
        LIBINFO_WL_00_B->Loaded_dsd1 = TRUE;
        if (LIBINFO_WL_00_B->ST_Dig_State == 2) {
          /* Transition: '<S147>:341' */
          /* Transition: '<S147>:343' */
          LIBINFO_WL_00_DWork->unloadedCounter = 0U;
        } else {
          /* Transition: '<S147>:340' */
          /* Transition: '<S147>:344' */
        }
      } else {
        /* Transition: '<S147>:327' */
        if ((LIBINFO_WL_00_B->ST_Dump_State == 2) &&
            (((LIBINFO_WL_00_B->ST_Dump_StateIsFull) ||
              (LIBINFO_WL_00_B->Compare)) || (LIBINFO_WL_00_B->LoadRatio <=
              LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p
              ->ST_LoadStatus_UnloadedRatio))) {
          /* Transition: '<S147>:329' */
          /* Transition: '<S147>:333' */
          LIBINFO_WL_00_DWork->loadedCounter = 0U;
        } else {
          /* Transition: '<S147>:331' */
          /* Transition: '<S147>:334' */
        }
      }
    }
  }

  /* End of Chart: '<S96>/Loaded' */

  /* SignalConversion: '<S91>/Copy' */
  LIBINFO_WL_00_B->Loaded = LIBINFO_WL_00_B->Loaded_dsd1;

  /* Product: '<S94>/Divide1' incorporates:
   *  Constant: '<S94>/Constant2'
   */
  LIBINFO_WL_00_B->Divide1_fq1g = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dump_ValveCmdZeroTime)
    / 6U);

  /* Product: '<S94>/Divide2' incorporates:
   *  Constant: '<S94>/Constant5'
   */
  LIBINFO_WL_00_B->Divide2_fpa0 = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dump_ImplementsIdleTime)
    / 6U);

  /* DataTypeConversion: '<S94>/Data Type Conversion3' */
  rtb_LogicalOperator = (LIBINFO_WL_00_B->TiltCylinderPositionUnknown != 0);

  /* Chart: '<S139>/DetectMovement' incorporates:
   *  Constant: '<S94>/Constant7'
   */
  /* Gateway: ST_Dump/TiltMovementDetection/DetectMovement */
  /* During: ST_Dump/TiltMovementDetection/DetectMovement */
  if (LIBINFO_WL_00_DWork->is_active_c10_ST_Lib_Dump_MWL == 0U) {
    /* Entry: ST_Dump/TiltMovementDetection/DetectMovement */
    LIBINFO_WL_00_DWork->is_active_c10_ST_Lib_Dump_MWL = 1U;

    /* Entry Internal: ST_Dump/TiltMovementDetection/DetectMovement */
    LIBINFO_WL_00_DWork->is_active_Capture = 1U;

    /* Entry Internal 'Capture': '<S141>:26' */
    /* Transition: '<S141>:28' */
    if (LIBINFO_WL_00_B->TiltCylinderPosition > LIBINFO_WL_00_B->tiltCylExt_n0bt)
    {
      /* Outputs for Function Call SubSystem: '<S139>/DumpThresholdCapture' */

      /* Transition: '<S141>:36' */
      /* Transition: '<S141>:38' */
      /* Event: '<S141>:7' */
      LIBINFO_WL_DumpThresholdCapture(LIBINFO_WL_00_B->TiltCylinderPosition,
        LIBINFO_WL_00_M->
        LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dump_CylMovementDelta,
        &LIBINFO_WL_00_B->tiltCylExt_n0bt, &LIBINFO_WL_00_B->Subtract);

      /* End of Outputs for SubSystem: '<S139>/DumpThresholdCapture' */

      /* Transition: '<S141>:39' */
    } else {
      /* Transition: '<S141>:34' */
    }

    /* Transition: '<S141>:41' */
    if (LIBINFO_WL_00_B->TiltCylinderPosition < LIBINFO_WL_00_B->tiltCylExt) {
      /* Outputs for Function Call SubSystem: '<S139>/RackThresholdCapture' */

      /* Transition: '<S141>:43' */
      /* Transition: '<S141>:45' */
      /* Event: '<S141>:8' */
      LIBINFO_WL_RackThresholdCapture(LIBINFO_WL_00_B->TiltCylinderPosition,
        LIBINFO_WL_00_M->
        LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dump_CylMovementDelta,
        &LIBINFO_WL_00_B->tiltCylExt, &LIBINFO_WL_00_B->Add);

      /* End of Outputs for SubSystem: '<S139>/RackThresholdCapture' */

      /* Transition: '<S141>:47' */
    } else {
      /* Transition: '<S141>:48' */
    }

    LIBINFO_WL_00_DWork->is_active_Main_hnap = 1U;

    /* Entry Internal 'Main': '<S141>:23' */
    /* Transition: '<S141>:10' */
    LIBINFO_WL_00_DWork->is_Main_erzc = LIBINFO_WL_00_IN_Unknown;

    /* Entry 'Unknown': '<S141>:9' */
    LIBINFO_WL_00_B->dumpMovementConfirmed = FALSE;
    LIBINFO_WL_00_B->rackMovementConfirmed = FALSE;
  } else {
    /* During 'Capture': '<S141>:26' */
    /* Transition: '<S141>:28' */
    if (LIBINFO_WL_00_B->TiltCylinderPosition > LIBINFO_WL_00_B->tiltCylExt_n0bt)
    {
      /* Outputs for Function Call SubSystem: '<S139>/DumpThresholdCapture' */

      /* Transition: '<S141>:36' */
      /* Transition: '<S141>:38' */
      /* Event: '<S141>:7' */
      LIBINFO_WL_DumpThresholdCapture(LIBINFO_WL_00_B->TiltCylinderPosition,
        LIBINFO_WL_00_M->
        LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dump_CylMovementDelta,
        &LIBINFO_WL_00_B->tiltCylExt_n0bt, &LIBINFO_WL_00_B->Subtract);

      /* End of Outputs for SubSystem: '<S139>/DumpThresholdCapture' */

      /* Transition: '<S141>:39' */
    } else {
      /* Transition: '<S141>:34' */
    }

    /* Transition: '<S141>:41' */
    if (LIBINFO_WL_00_B->TiltCylinderPosition < LIBINFO_WL_00_B->tiltCylExt) {
      /* Outputs for Function Call SubSystem: '<S139>/RackThresholdCapture' */

      /* Transition: '<S141>:43' */
      /* Transition: '<S141>:45' */
      /* Event: '<S141>:8' */
      LIBINFO_WL_RackThresholdCapture(LIBINFO_WL_00_B->TiltCylinderPosition,
        LIBINFO_WL_00_M->
        LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dump_CylMovementDelta,
        &LIBINFO_WL_00_B->tiltCylExt, &LIBINFO_WL_00_B->Add);

      /* End of Outputs for SubSystem: '<S139>/RackThresholdCapture' */

      /* Transition: '<S141>:47' */
    } else {
      /* Transition: '<S141>:48' */
    }

    /* During 'Main': '<S141>:23' */
    if (LIBINFO_WL_00_DWork->is_Main_erzc == LIBINFO_WL_00_IN_Known) {
      /* During 'Known': '<S141>:50' */
      if (rtb_LogicalOperator) {
        /* Transition: '<S141>:15' */
        /* Exit Internal 'Known': '<S141>:50' */
        LIBINFO_WL_00_DWork->is_Known = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        LIBINFO_WL_00_DWork->is_Main_erzc = LIBINFO_WL_00_IN_Unknown;

        /* Entry 'Unknown': '<S141>:9' */
        LIBINFO_WL_00_B->dumpMovementConfirmed = FALSE;
        LIBINFO_WL_00_B->rackMovementConfirmed = FALSE;
      } else {
        switch (LIBINFO_WL_00_DWork->is_Known) {
         case LIBINFO_WL_00_IN_Armed:
          /* During 'Armed': '<S141>:13' */
          if (LIBINFO_WL_00_B->TiltCylinderPosition <= LIBINFO_WL_00_B->Subtract)
          {
            /* Transition: '<S141>:53' */
            LIBINFO_WL_00_DWork->is_Known = LIBINFO_WL_00_IN_DumpDetected;

            /* Entry 'DumpDetected': '<S141>:11' */
            LIBINFO_WL_00_B->dumpMovementConfirmed = TRUE;
            LIBINFO_WL_00_B->rackMovementConfirmed = FALSE;

            /* Outputs for Function Call SubSystem: '<S139>/RackThresholdCapture' */

            /* Event: '<S141>:8' */
            LIBINFO_WL_RackThresholdCapture
              (LIBINFO_WL_00_B->TiltCylinderPosition,
               LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p
               ->ST_Dump_CylMovementDelta, &LIBINFO_WL_00_B->tiltCylExt,
               &LIBINFO_WL_00_B->Add);

            /* End of Outputs for SubSystem: '<S139>/RackThresholdCapture' */
          } else {
            if (LIBINFO_WL_00_B->TiltCylinderPosition >= LIBINFO_WL_00_B->Add) {
              /* Transition: '<S141>:52' */
              LIBINFO_WL_00_DWork->is_Known = LIBINFO_WL_00_IN_RackDetected;

              /* Entry 'RackDetected': '<S141>:12' */
              LIBINFO_WL_00_B->dumpMovementConfirmed = FALSE;

              /* Outputs for Function Call SubSystem: '<S139>/DumpThresholdCapture' */

              /* Event: '<S141>:7' */
              LIBINFO_WL_DumpThresholdCapture
                (LIBINFO_WL_00_B->TiltCylinderPosition,
                 LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p
                 ->ST_Dump_CylMovementDelta, &LIBINFO_WL_00_B->tiltCylExt_n0bt,
                 &LIBINFO_WL_00_B->Subtract);

              /* End of Outputs for SubSystem: '<S139>/DumpThresholdCapture' */
              LIBINFO_WL_00_B->rackMovementConfirmed = TRUE;
            }
          }
          break;

         case LIBINFO_WL_00_IN_DumpDetected:
          /* During 'DumpDetected': '<S141>:11' */
          if (LIBINFO_WL_00_B->TiltCylinderPosition >= LIBINFO_WL_00_B->Add) {
            /* Transition: '<S141>:54' */
            LIBINFO_WL_00_DWork->is_Known = LIBINFO_WL_00_IN_RackDetected;

            /* Entry 'RackDetected': '<S141>:12' */
            LIBINFO_WL_00_B->dumpMovementConfirmed = FALSE;

            /* Outputs for Function Call SubSystem: '<S139>/DumpThresholdCapture' */

            /* Event: '<S141>:7' */
            LIBINFO_WL_DumpThresholdCapture
              (LIBINFO_WL_00_B->TiltCylinderPosition,
               LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p
               ->ST_Dump_CylMovementDelta, &LIBINFO_WL_00_B->tiltCylExt_n0bt,
               &LIBINFO_WL_00_B->Subtract);

            /* End of Outputs for SubSystem: '<S139>/DumpThresholdCapture' */
            LIBINFO_WL_00_B->rackMovementConfirmed = TRUE;
          }
          break;

         default:
          /* During 'RackDetected': '<S141>:12' */
          if (LIBINFO_WL_00_B->TiltCylinderPosition <= LIBINFO_WL_00_B->Subtract)
          {
            /* Transition: '<S141>:55' */
            LIBINFO_WL_00_DWork->is_Known = LIBINFO_WL_00_IN_DumpDetected;

            /* Entry 'DumpDetected': '<S141>:11' */
            LIBINFO_WL_00_B->dumpMovementConfirmed = TRUE;
            LIBINFO_WL_00_B->rackMovementConfirmed = FALSE;

            /* Outputs for Function Call SubSystem: '<S139>/RackThresholdCapture' */

            /* Event: '<S141>:8' */
            LIBINFO_WL_RackThresholdCapture
              (LIBINFO_WL_00_B->TiltCylinderPosition,
               LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p
               ->ST_Dump_CylMovementDelta, &LIBINFO_WL_00_B->tiltCylExt,
               &LIBINFO_WL_00_B->Add);

            /* End of Outputs for SubSystem: '<S139>/RackThresholdCapture' */
          }
          break;
        }
      }
    } else {
      /* During 'Unknown': '<S141>:9' */
      if (!rtb_LogicalOperator) {
        /* Transition: '<S141>:14' */
        LIBINFO_WL_00_DWork->is_Main_erzc = LIBINFO_WL_00_IN_Known;

        /* Entry Internal 'Known': '<S141>:50' */
        /* Transition: '<S141>:51' */
        LIBINFO_WL_00_DWork->is_Known = LIBINFO_WL_00_IN_Armed;

        /* Entry 'Armed': '<S141>:13' */
        LIBINFO_WL_00_B->dumpMovementConfirmed = FALSE;

        /* Outputs for Function Call SubSystem: '<S139>/DumpThresholdCapture' */

        /* Event: '<S141>:7' */
        LIBINFO_WL_DumpThresholdCapture(LIBINFO_WL_00_B->TiltCylinderPosition,
          LIBINFO_WL_00_M->
          LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dump_CylMovementDelta,
          &LIBINFO_WL_00_B->tiltCylExt_n0bt, &LIBINFO_WL_00_B->Subtract);

        /* End of Outputs for SubSystem: '<S139>/DumpThresholdCapture' */
        LIBINFO_WL_00_B->rackMovementConfirmed = FALSE;

        /* Outputs for Function Call SubSystem: '<S139>/RackThresholdCapture' */

        /* Event: '<S141>:8' */
        LIBINFO_WL_RackThresholdCapture(LIBINFO_WL_00_B->TiltCylinderPosition,
          LIBINFO_WL_00_M->
          LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dump_CylMovementDelta,
          &LIBINFO_WL_00_B->tiltCylExt, &LIBINFO_WL_00_B->Add);

        /* End of Outputs for SubSystem: '<S139>/RackThresholdCapture' */
      }
    }
  }

  /* End of Chart: '<S139>/DetectMovement' */

  /* RelationalOperator: '<S136>/Compare' incorporates:
   *  Constant: '<S136>/Constant'
   */
  rtb_LogicalOperator = (LIBINFO_WL_00_B->LoadRatioStatus != 0);

  /* Chart: '<S94>/DumpState' incorporates:
   *  Constant: '<S94>/Constant'
   */
  /* Gateway: ST_Dump/DumpState */
  /* During: ST_Dump/DumpState */
  if (LIBINFO_WL_00_DWork->is_active_c8_ST_Lib_Dump_MWL == 0U) {
    /* Entry: ST_Dump/DumpState */
    LIBINFO_WL_00_DWork->is_active_c8_ST_Lib_Dump_MWL = 1U;

    /* Entry Internal: ST_Dump/DumpState */
    LIBINFO_WL_00_DWork->is_active_TiltCommandZero = 1U;

    /* Entry 'TiltCommandZero': '<S137>:113' */
    LIBINFO_WL_00_DWork->valveCmdZeroCounter = 0U;

    /* Entry Internal 'TiltCommandZero': '<S137>:113' */
    /* Transition: '<S137>:121' */
    LIBINFO_WL_00_DWork->is_TiltCommandZero = LIBINFO_WL_00_IN_Idle;

    /* Entry 'Idle': '<S137>:115' */
    LIBINFO_WL_00_DWork->valveCmdZero = TRUE;
    LIBINFO_WL_00_DWork->is_active_NotWorking = 1U;

    /* Entry 'NotWorking': '<S137>:134' */
    LIBINFO_WL_00_DWork->notWorkingCounter = 0U;

    /* Entry Internal 'NotWorking': '<S137>:134' */
    /* Transition: '<S137>:136' */
    LIBINFO_WL_00_DWork->is_NotWorking = LIBINFO_WL_00_IN_Idle;

    /* Entry 'Idle': '<S137>:135' */
    LIBINFO_WL_00_DWork->notWorking = TRUE;
    LIBINFO_WL_00_DWork->is_active_Main_i1bh = 1U;

    /* Entry Internal 'Main': '<S137>:112' */
    /* Transition: '<S137>:44' */
    LIBINFO_WL_00_DWork->is_Main_pm2j = LIBINFO_WL_00_IN_NotDump;

    /* Entry 'NotDump': '<S137>:1' */
    LIBINFO_WL_00_B->ST_Dump_State_exsh = 0U;
  } else {
    /* During 'TiltCommandZero': '<S137>:113' */
    switch (LIBINFO_WL_00_DWork->is_TiltCommandZero) {
     case LIBINFO_WL_00_IN_Active:
      /* During 'Active': '<S137>:114' */
      if (LIBINFO_WL_00_B->TiltValveCmd_bbs3 == 0) {
        /* Transition: '<S137>:118' */
        LIBINFO_WL_00_DWork->is_TiltCommandZero = LIBINFO_WL_00_IN_IdleDebounce;

        /* Entry 'IdleDebounce': '<S137>:116' */
        LIBINFO_WL_00_DWork->valveCmdZeroCounter = 1U;
      }
      break;

     case LIBINFO_WL_00_IN_Idle:
      /* During 'Idle': '<S137>:115' */
      if (LIBINFO_WL_00_B->TiltValveCmd_bbs3 != 0) {
        /* Transition: '<S137>:117' */
        LIBINFO_WL_00_DWork->is_TiltCommandZero = LIBINFO_WL_00_IN_Active;

        /* Entry 'Active': '<S137>:114' */
        LIBINFO_WL_00_DWork->valveCmdZero = FALSE;
      }
      break;

     default:
      /* During 'IdleDebounce': '<S137>:116' */
      if (LIBINFO_WL_00_B->TiltValveCmd_bbs3 != 0) {
        /* Transition: '<S137>:119' */
        LIBINFO_WL_00_DWork->is_TiltCommandZero = LIBINFO_WL_00_IN_Active;

        /* Entry 'Active': '<S137>:114' */
        LIBINFO_WL_00_DWork->valveCmdZero = FALSE;
      } else if (LIBINFO_WL_00_DWork->valveCmdZeroCounter >=
                 LIBINFO_WL_00_B->Divide1_fq1g) {
        /* Transition: '<S137>:120' */
        LIBINFO_WL_00_DWork->is_TiltCommandZero = LIBINFO_WL_00_IN_Idle;

        /* Entry 'Idle': '<S137>:115' */
        LIBINFO_WL_00_DWork->valveCmdZero = TRUE;
      } else {
        LIBINFO_WL_00_DWork->valveCmdZeroCounter++;
      }
      break;
    }

    /* During 'NotWorking': '<S137>:134' */
    switch (LIBINFO_WL_00_DWork->is_NotWorking) {
     case LIBINFO_WL_00_IN_Active:
      /* During 'Active': '<S137>:137' */
      if ((LIBINFO_WL_00_B->TiltValveCmd_bbs3 == 0) &&
          (LIBINFO_WL_00_B->LiftValveCmd_lf5w <= 0)) {
        /* Transition: '<S137>:140' */
        LIBINFO_WL_00_DWork->is_NotWorking = LIBINFO_WL_00_IN_IdleDebounce;

        /* Entry 'IdleDebounce': '<S137>:139' */
        LIBINFO_WL_00_DWork->notWorkingCounter = 1U;
      }
      break;

     case LIBINFO_WL_00_IN_Idle:
      /* During 'Idle': '<S137>:135' */
      if (LIBINFO_WL_00_B->TiltValveCmd_bbs3 != 0) {
        /* Transition: '<S137>:138' */
        LIBINFO_WL_00_DWork->is_NotWorking = LIBINFO_WL_00_IN_Active;

        /* Entry 'Active': '<S137>:137' */
        LIBINFO_WL_00_DWork->notWorking = FALSE;
      }
      break;

     default:
      /* During 'IdleDebounce': '<S137>:139' */
      if ((LIBINFO_WL_00_B->TiltValveCmd_bbs3 != 0) ||
          (LIBINFO_WL_00_B->LiftValveCmd_lf5w > 0)) {
        /* Transition: '<S137>:141' */
        LIBINFO_WL_00_DWork->is_NotWorking = LIBINFO_WL_00_IN_Active;

        /* Entry 'Active': '<S137>:137' */
        LIBINFO_WL_00_DWork->notWorking = FALSE;
      } else if (LIBINFO_WL_00_DWork->notWorkingCounter >=
                 LIBINFO_WL_00_B->Divide2_fpa0) {
        /* Transition: '<S137>:142' */
        LIBINFO_WL_00_DWork->is_NotWorking = LIBINFO_WL_00_IN_Idle;

        /* Entry 'Idle': '<S137>:135' */
        LIBINFO_WL_00_DWork->notWorking = TRUE;
      } else {
        LIBINFO_WL_00_DWork->notWorkingCounter++;
      }
      break;
    }

    /* During 'Main': '<S137>:112' */
    switch (LIBINFO_WL_00_DWork->is_Main_pm2j) {
     case LIBINFO_WL_00_IN_ConfirmedDump:
      /* During 'ConfirmedDump': '<S137>:148' */
      if ((LIBINFO_WL_00_B->DigTrigger) || (LIBINFO_WL_00_DWork->notWorking)) {
        /* Transition: '<S137>:149' */
        /* Exit Internal 'ConfirmedDump': '<S137>:148' */
        LIBINFO_WL_00_DWork->is_ConfirmedDump = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
        LIBINFO_WL_00_DWork->is_Main_pm2j = LIBINFO_WL_00_IN_NotDump;

        /* Entry 'NotDump': '<S137>:1' */
        LIBINFO_WL_00_B->ST_Dump_State_exsh = 0U;
      } else {
        switch (LIBINFO_WL_00_DWork->is_ConfirmedDump) {
         case LIBINFO_WL_00_IN_Dumping:
          /* During 'Dumping': '<S137>:3' */
          if (((LIBINFO_WL_00_B->TiltValveCmd_bbs3 > 0) ||
               (LIBINFO_WL_00_DWork->valveCmdZero)) &&
              ((!LIBINFO_WL_00_GroundSpeedSlow(LIBINFO_WL_00_M, LIBINFO_WL_00_B))
               || (LIBINFO_WL_00_B->DataTypeConversion2))) {
            /* Transition: '<S137>:28' */
            /* Transition: '<S137>:127' */
            /* Transition: '<S137>:133' */
            /* Transition: '<S137>:37' */
            LIBINFO_WL_00_DWork->is_ConfirmedDump =
              LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
            LIBINFO_WL_00_DWork->is_Main_pm2j = LIBINFO_WL_00_IN_NotDump;

            /* Entry 'NotDump': '<S137>:1' */
            LIBINFO_WL_00_B->ST_Dump_State_exsh = 0U;
          } else if (((LIBINFO_WL_00_B->TiltValveCmd_bbs3 > 0) ||
                      (LIBINFO_WL_00_DWork->valveCmdZero)) &&
                     ((LIBINFO_WL_00_B->DataTypeConversion1) ||
                      (LIBINFO_WL_00_B->DataTypeConversion4))) {
            /* Transition: '<S137>:147' */
            LIBINFO_WL_00_DWork->is_ConfirmedDump =
              LIBINFO_WL_00_IN_FinishRacking;
          } else {
            if ((LIBINFO_WL_00_B->TiltValveCmd_bbs3 > 0) ||
                (LIBINFO_WL_00_DWork->valveCmdZero)) {
              /* Transition: '<S137>:129' */
              LIBINFO_WL_00_DWork->is_ConfirmedDump =
                LIBINFO_WL__IN_TentativeNotDump;
            }
          }
          break;

         case LIBINFO_WL_00_IN_FinishRacking:
          /* During 'FinishRacking': '<S137>:41' */
          if (LIBINFO_WL_00_B->TiltValveCmd_bbs3 < 0) {
            /* Transition: '<S137>:155' */
            LIBINFO_WL_00_DWork->is_ConfirmedDump = LIBINFO_WL_00_IN_Dumping;
          } else {
            if (((LIBINFO_WL_00_DWork->valveCmdZero) ||
                 (!LIBINFO_WL_00_GroundSpeedSlow(LIBINFO_WL_00_M,
                   LIBINFO_WL_00_B))) || (LIBINFO_WL_00_B->DataTypeConversion2))
            {
              /* Transition: '<S137>:43' */
              /* Transition: '<S137>:37' */
              LIBINFO_WL_00_DWork->is_ConfirmedDump =
                LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
              LIBINFO_WL_00_DWork->is_Main_pm2j = LIBINFO_WL_00_IN_NotDump;

              /* Entry 'NotDump': '<S137>:1' */
              LIBINFO_WL_00_B->ST_Dump_State_exsh = 0U;
            }
          }
          break;

         default:
          /* During 'TentativeNotDump': '<S137>:40' */
          if (LIBINFO_WL_00_B->TiltValveCmd_bbs3 < 0) {
            /* Transition: '<S137>:31' */
            LIBINFO_WL_00_DWork->is_ConfirmedDump = LIBINFO_WL_00_IN_Dumping;
          } else if ((!LIBINFO_WL_00_GroundSpeedSlow(LIBINFO_WL_00_M,
                       LIBINFO_WL_00_B)) ||
                     (LIBINFO_WL_00_B->DataTypeConversion2)) {
            /* Transition: '<S137>:145' */
            /* Transition: '<S137>:133' */
            /* Transition: '<S137>:37' */
            LIBINFO_WL_00_DWork->is_ConfirmedDump =
              LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
            LIBINFO_WL_00_DWork->is_Main_pm2j = LIBINFO_WL_00_IN_NotDump;

            /* Entry 'NotDump': '<S137>:1' */
            LIBINFO_WL_00_B->ST_Dump_State_exsh = 0U;
          } else {
            if (((LIBINFO_WL_00_RackThresholdMet(LIBINFO_WL_00_B)) ||
                 (LIBINFO_WL_00_B->DataTypeConversion1)) ||
                (LIBINFO_WL_00_B->DataTypeConversion4)) {
              /* Transition: '<S137>:42' */
              LIBINFO_WL_00_DWork->is_ConfirmedDump =
                LIBINFO_WL_00_IN_FinishRacking;
            }
          }
          break;
        }
      }
      break;

     case LIBINFO_WL_00_IN_NotDump:
      /* During 'NotDump': '<S137>:1' */
      if (((LIBINFO_W_OperatorCommandedDump(LIBINFO_WL_00_M, LIBINFO_WL_00_B)) &&
           (!LIBINFO_WL_00_B->DataTypeConversion1)) &&
          (!LIBINFO_WL_00_B->DataTypeConversion4)) {
        /* Transition: '<S137>:6' */
        LIBINFO_WL_00_DWork->is_Main_pm2j = LIBINFO_WL_00_IN_TentativeDump;

        /* Entry 'TentativeDump': '<S137>:2' */
        LIBINFO_WL_00_B->ST_Dump_State_exsh = 1U;

        /* Outputs for Function Call SubSystem: '<S94>/CaptureBucketAngleDumpThreshold' */
        /* Switch: '<S134>/Switch' incorporates:
         *  Constant: '<S140>/Constant'
         *  Logic: '<S134>/Logical Operator'
         *  RelationalOperator: '<S140>/Compare'
         */
        /* Event: '<S137>:5' */
        if ((LIBINFO_WL_00_B->ST_Dig_State_prjn >= 1) || rtb_LogicalOperator) {
          /* MinMax: '<S134>/Min' incorporates:
           *  Constant: '<S134>/Constant1'
           */
          LIBINFO_WL_00_B->Switch_iyvp =
            LIBINFO_WL_00_M->
            LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p->ST_Dump_DumpAngleAxis
            [0];
          if (!(LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p
                ->ST_Dump_DumpAngleAxis[0] <=
                LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p
                ->ST_Dump_DumpAngleAxis[1])) {
            LIBINFO_WL_00_B->Switch_iyvp =
              LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p
              ->ST_Dump_DumpAngleAxis[1];
          }
        } else {
          /* Lookup: '<S134>/Lookup Table'
           * About '<S134>/Lookup Table':
           * Input0  Data Type:  Floating Point real32_T
           * Output0 Data Type:  Fixed Point    S16  2^-6
           * Lookup Method: Linear_Endpoint
           *
           * XData parameter uses the same data type and scaling as Input0
           * YData parameter uses the same data type and scaling as Output0
           */
          R2012b_LookUp_S16_real32_T( &(rtb_LookupTable),
                              &(LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p
                                ->ST_Dump_DumpAngleAxis[0]),
                              LIBINFO_WL_00_B->LoadRatio,
                              &(LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p
                                ->ST_Dump_LoadRatioAxis[0]), 1U);

          /* MinMax: '<S134>/Min' incorporates:
           *  Lookup: '<S134>/Lookup Table'
           */
          LIBINFO_WL_00_B->Switch_iyvp = rtb_LookupTable;
        }

        /* End of Switch: '<S134>/Switch' */
        /* End of Outputs for SubSystem: '<S94>/CaptureBucketAngleDumpThreshold' */
      }
      break;

     default:
      /* During 'TentativeDump': '<S137>:2' */
      if (((((LIBINFO_WL_00_B->TiltValveCmd_bbs3 > 0) ||
             (LIBINFO_WL_00_B->DigTrigger)) ||
            (LIBINFO_WL_00_DWork->valveCmdZero)) ||
           (LIBINFO_WL_00_B->DataTypeConversion1)) ||
          (LIBINFO_WL_00_B->DataTypeConversion4)) {
        /* Transition: '<S137>:33' */
        LIBINFO_WL_00_DWork->is_Main_pm2j = LIBINFO_WL_00_IN_NotDump;

        /* Entry 'NotDump': '<S137>:1' */
        LIBINFO_WL_00_B->ST_Dump_State_exsh = 0U;
      } else {
        if ((LIBINFO_WL_00_DumpThresholdMet(LIBINFO_WL_00_B)) &&
            (((LIBINFO_WL_00_B->GroundSpeed_iutz <
               LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p
               ->ST_Dump_GroundSpeedThreshold) ||
              (LIBINFO_WL_00_B->DataTypeConversion2)) ||
             (LIBINFO_WL_00_B->Loaded))) {
          /* Transition: '<S137>:8' */
          LIBINFO_WL_00_DWork->is_Main_pm2j = LIBINFO_WL_00_IN_ConfirmedDump;

          /* Entry 'ConfirmedDump': '<S137>:148' */
          LIBINFO_WL_00_B->ST_Dump_State_exsh = 2U;

          /* Entry Internal 'ConfirmedDump': '<S137>:148' */
          /* Transition: '<S137>:153' */
          LIBINFO_WL_00_DWork->is_ConfirmedDump = LIBINFO_WL_00_IN_Dumping;
        }
      }
      break;
    }
  }

  /* End of Chart: '<S94>/DumpState' */

  /* SignalConversion: '<S4>/ConcatBufferAtVector ConcatenateIn3' */
  LIBINFO_WL_00_B->VectorConcatenate[2] = LIBINFO_WL_00_B->ST_Dump_State_exsh;

  /* SignalConversion: '<S4>/ConcatBufferAtVector ConcatenateIn4' */
  LIBINFO_WL_00_B->VectorConcatenate[3] = LIBINFO_WL_00_B->ST_Dig_State_prjn;

  /* UnitDelay: '<S171>/IsFirstOrSecondLoop' */
  rtb_LogicalOperator = LIBINFO_WL_00_DWork->IsFirstOrSecondLoop_DSTATE;

  /* UnitDelay: '<S171>/Unit Delay1' */
  rtb_UnitDelay1_la4n = LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_asxt;

  /* UnitDelay: '<S171>/Unit Delay' */
  rtb_UnitDelay_pt3t = LIBINFO_WL_00_DWork->UnitDelay_DSTATE_ogmk;

  /* MinMax: '<S171>/Min' */
  if (rtb_UnitDelay1_la4n <= rtb_UnitDelay_pt3t) {
    rtb_Switch_lbk1 = rtb_UnitDelay1_la4n;
  } else {
    rtb_Switch_lbk1 = rtb_UnitDelay_pt3t;
  }

  if (!(rtb_Switch_lbk1 <= LIBINFO_WL_00_B->GroundSpeed_iutz)) {
    rtb_Switch_lbk1 = LIBINFO_WL_00_B->GroundSpeed_iutz;
  }

  /* If: '<S171>/If' incorporates:
   *  MinMax: '<S171>/Min'
   *  RelationalOperator: '<S171>/Relational Operator'
   *  RelationalOperator: '<S171>/Relational Operator1'
   */
  if (LIBINFO_WL_00_B->GroundSpeed_iutz == rtb_Switch_lbk1) {
    /* Outputs for IfAction SubSystem: '<S171>/x0_is_min' incorporates:
     *  ActionPort: '<S172>/Action Port'
     */
    LIBINFO_WL_00_x0_is_min(rtb_UnitDelay_pt3t, rtb_UnitDelay1_la4n,
      &rtb_Merge_eyqe);

    /* End of Outputs for SubSystem: '<S171>/x0_is_min' */
  } else if (rtb_UnitDelay_pt3t == rtb_Switch_lbk1) {
    /* Outputs for IfAction SubSystem: '<S171>/x1_is_min' incorporates:
     *  ActionPort: '<S173>/Action Port'
     */
    LIBINFO_WL_00_x1_is_min(LIBINFO_WL_00_B->GroundSpeed_iutz,
      rtb_UnitDelay1_la4n, &rtb_Merge_eyqe);

    /* End of Outputs for SubSystem: '<S171>/x1_is_min' */
  } else {
    /* Outputs for IfAction SubSystem: '<S171>/x2_is_min' incorporates:
     *  ActionPort: '<S174>/Action Port'
     */
    LIBINFO_WL_00_x2_is_min(LIBINFO_WL_00_B->GroundSpeed_iutz,
      rtb_UnitDelay_pt3t, &rtb_Merge_eyqe);

    /* End of Outputs for SubSystem: '<S171>/x2_is_min' */
  }

  /* End of If: '<S171>/If' */

  /* Switch: '<S171>/Switch' */
  if (rtb_LogicalOperator) {
    rtb_Switch_lbk1 = LIBINFO_WL_00_B->GroundSpeed_iutz;
  } else {
    rtb_Switch_lbk1 = rtb_Merge_eyqe;
  }

  /* End of Switch: '<S171>/Switch' */

  /* Abs: '<S167>/Abs' */
  if (rtb_Switch_lbk1 < 0) {
    rtb_Switch_fod = (int16_t)(-rtb_Switch_lbk1);
  } else {
    rtb_Switch_fod = rtb_Switch_lbk1;
  }

  /* End of Abs: '<S167>/Abs' */

  /* RelationalOperator: '<S167>/Relational Operator' incorporates:
   *  Constant: '<S98>/Constant5'
   */
  LIBINFO_WL_00_B->RelationalOperator = (rtb_Switch_fod >
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_Travel_GroundSpeedThreshold);

  /* Product: '<S98>/Divide' incorporates:
   *  Constant: '<S98>/Constant3'
   */
  LIBINFO_WL_00_B->Divide_h3xr = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_Travel_NotTravelingDebounce)
    / 6U);

  /* Product: '<S98>/Divide1' incorporates:
   *  Constant: '<S98>/Constant4'
   */
  LIBINFO_WL_00_B->Divide1_gfci = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_Travel_MaxTentativeTime)
    / 6U);

  /* Product: '<S98>/Divide2' incorporates:
   *  Constant: '<S98>/Constant7'
   */
  LIBINFO_WL_00_B->Divide2_dnc1 = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_Travel_MinSegmentTime)
    / 6U);

  /* Logic: '<S167>/Logical Operator1' incorporates:
   *  RelationalOperator: '<S170>/Compare'
   */
  LIBINFO_WL_00_B->LogicalOperator1 = ((rtb_Switch_lbk1 > 0) &&
    (LIBINFO_WL_00_B->RelationalOperator));

  /* Logic: '<S167>/Logical Operator' incorporates:
   *  RelationalOperator: '<S169>/Compare'
   */
  LIBINFO_WL_00_B->LogicalOperator = ((rtb_Switch_lbk1 < 0) &&
    (LIBINFO_WL_00_B->RelationalOperator));

  /* SignalConversion: '<S165>/Copy' */
  LIBINFO_WL_00_B->loaded = LIBINFO_WL_00_B->Loaded;

  /* Logic: '<S146>/Logical Operator' incorporates:
   *  Constant: '<S149>/Constant'
   *  Constant: '<S150>/Constant'
   *  Logic: '<S146>/Logical Operator1'
   *  RelationalOperator: '<S149>/Compare'
   *  RelationalOperator: '<S150>/Compare'
   */
  rtb_DataTypeConversion3_js1i = ((((LIBINFO_WL_00_B->LoadRatioStatus != 0) &&
    (LIBINFO_WL_00_B->LoadRatioStatus != 3)) || (LIBINFO_WL_00_B->IsFullRack)) ||
                                  (LIBINFO_WL_00_B->Loaded_dsd1));

  /* Switch: '<S148>/Switch' incorporates:
   *  Constant: '<S146>/Constant2'
   *  Constant: '<S148>/Constant'
   *  Logic: '<S148>/Logical Operator'
   *  Product: '<S146>/Product'
   *  SampleTimeMath: '<S146>/Weighted Sample Time1'
   *  Sum: '<S146>/Add'
   *  Sum: '<S148>/Sum'
   *  UnitDelay: '<S148>/Unit Delay'
   *  UnitDelay: '<S148>/Unit Delay1'
   *
   * About '<S146>/Weighted Sample Time1':
   *  y = K where K = ( w * Ts )
   */
  if ((LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_juby) ||
      rtb_DataTypeConversion3_js1i) {
    rtb_Switch = 0.0F;
  } else {
    rtb_Switch = ((LIBINFO_WL_00_B->LoadRatioRaw -
                   LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p
                   ->ST_LoadStat_DwnFrcLdRatioOfset) * 0.12F) +
      LIBINFO_WL_00_DWork->UnitDelay_DSTATE;
  }

  /* End of Switch: '<S148>/Switch' */

  /* If: '<S148>/If' incorporates:
   *  Constant: '<S146>/Constant3'
   *  Constant: '<S146>/Constant5'
   *  Constant: '<S153>/Not Saturated'
   *  Constant: '<S154>/Saturated High'
   *  Constant: '<S155>/Saturated Low'
   *  Inport: '<S154>/maxLimit'
   *  Inport: '<S155>/minLimit'
   *  RelationalOperator: '<S148>/Relational Operator'
   *  RelationalOperator: '<S148>/Relational Operator1'
   */
  if (rtb_Switch >= 0.0F) {
    /* Outputs for IfAction SubSystem: '<S148>/Saturated High' incorporates:
     *  ActionPort: '<S154>/Action Port'
     */
    rtb_Switch = 0.0F;
    rtb_InitToInput = 1;

    /* End of Outputs for SubSystem: '<S148>/Saturated High' */
  } else if (rtb_Switch <=
             LIBINFO_WL_00_M->
             LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_LoadStat_DwnFrceTrgrThrshld)
  {
    /* Outputs for IfAction SubSystem: '<S148>/Saturated Low' incorporates:
     *  ActionPort: '<S155>/Action Port'
     */
    rtb_Switch =
      LIBINFO_WL_00_M->
      LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_LoadStat_DwnFrceTrgrThrshld;
    rtb_InitToInput = -1;

    /* End of Outputs for SubSystem: '<S148>/Saturated Low' */
  } else {
    /* Outputs for IfAction SubSystem: '<S148>/Not Saturated' incorporates:
     *  ActionPort: '<S153>/Action Port'
     */
    rtb_InitToInput = 0;

    /* End of Outputs for SubSystem: '<S148>/Not Saturated' */
  }

  /* End of If: '<S148>/If' */

  /* Switch: '<S146>/Switch' incorporates:
   *  Constant: '<S146>/Constant'
   *  Constant: '<S146>/Constant3'
   *  Constant: '<S146>/Constant4'
   *  Constant: '<S151>/Constant'
   *  Constant: '<S152>/Constant'
   *  Logic: '<S146>/Reset'
   *  Logic: '<S146>/Trigger'
   *  RelationalOperator: '<S146>/Relational Operator'
   *  RelationalOperator: '<S146>/Relational Operator1'
   *  RelationalOperator: '<S151>/Compare'
   *  RelationalOperator: '<S152>/Compare'
   *  Switch: '<S146>/Switch1'
   *  UnitDelay: '<S146>/Unit Delay'
   */
  if ((rtb_Switch >=
       LIBINFO_WL_00_M->
       LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_LoadStat_DwnFrceRstThreshld)
      || (rtb_InitToInput > 0)) {
    LIBINFO_WL_00_B->DownForce = FALSE;
  } else if ((rtb_Switch <=
              LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p
              ->ST_LoadStat_DwnFrceTrgrThrshld) || (rtb_InitToInput < 0)) {
    /* Switch: '<S146>/Switch1' incorporates:
     *  Constant: '<S146>/Constant1'
     */
    LIBINFO_WL_00_B->DownForce = TRUE;
  } else {
    LIBINFO_WL_00_B->DownForce = LIBINFO_WL_00_DWork->UnitDelay_DSTATE_bozj;
  }

  /* End of Switch: '<S146>/Switch' */

  /* SignalConversion: '<S90>/Copy' */
  LIBINFO_WL_00_B->DownForce_ptmd = LIBINFO_WL_00_B->DownForce;

  /* SignalConversion: '<S164>/Copy' */
  LIBINFO_WL_00_B->downForce = LIBINFO_WL_00_B->DownForce_ptmd;

  /* Chart: '<S98>/LoadedState' incorporates:
   *  Constant: '<S98>/Constant1'
   *  Constant: '<S98>/Constant2'
   *  Constant: '<S98>/Constant6'
   */
  /* Gateway: ST_Travel/LoadedState */
  /* During: ST_Travel/LoadedState */
  if (LIBINFO_WL_00_DWork->is_active_c2_ST_Lib_Travel_MWL == 0U) {
    /* Entry: ST_Travel/LoadedState */
    LIBINFO_WL_00_DWork->is_active_c2_ST_Lib_Travel_MWL = 1U;

    /* Entry Internal: ST_Travel/LoadedState */
    LIBINFO_WL_00_DWork->is_active_Counter = 1U;

    /* Entry Internal 'Counter': '<S166>:70' */
    /* Transition: '<S166>:71' */
    LIBINFO_WL_00_DWork->segmentTimeCounter = LIBINFO_WL_00_B->Divide2_dnc1;
    if (LIBINFO_WL_00_DWork->segmentTimeCounter < LIBINFO_WL_00_B->Divide2_dnc1)
    {
      /* Transition: '<S166>:77' */
      /* Transition: '<S166>:82' */
      LIBINFO_WL_00_DWork->segmentTimeCounter++;
    } else {
      /* Transition: '<S166>:79' */
      /* Transition: '<S166>:83' */
    }

    /* Transition: '<S166>:85' */
    LIBINFO_WL_00_B->ST_Travel_Commit = FALSE;
    LIBINFO_WL_00_DWork->is_active_Main_hmss = 1U;

    /* Entry Internal 'Main': '<S166>:66' */
    /* Transition: '<S166>:39' */
    if (!LIBINFO_WL_00_B->loaded) {
      /* Transition: '<S166>:42' */
      /* Transition: '<S166>:43' */
      LIBINFO_WL_00_B->ST_Travel_ID = 3U;
      LIBINFO_WL_00_DWork->is_Main_bd3y = LIBINFO_WL_00_IN_Empty_gv30;
    } else {
      /* Transition: '<S166>:40' */
      LIBINFO_WL_00_B->ST_Travel_ID = 1U;
      LIBINFO_WL_00_DWork->is_Main_bd3y = LIBINFO_WL_00_IN_Loaded_ddwb;
    }
  } else {
    /* During 'Counter': '<S166>:70' */
    /* Transition: '<S166>:80' */
    if (LIBINFO_WL_00_DWork->segmentTimeCounter < LIBINFO_WL_00_B->Divide2_dnc1)
    {
      /* Transition: '<S166>:77' */
      /* Transition: '<S166>:82' */
      LIBINFO_WL_00_DWork->segmentTimeCounter++;
    } else {
      /* Transition: '<S166>:79' */
      /* Transition: '<S166>:83' */
    }

    /* Transition: '<S166>:85' */
    LIBINFO_WL_00_B->ST_Travel_Commit = FALSE;

    /* During 'Main': '<S166>:66' */
    switch (LIBINFO_WL_00_DWork->is_Main_bd3y) {
     case LIBINFO_WL_00_IN_Backdrag:
      /* During 'Backdrag': '<S166>:51' */
      if (LIBINFO_WL_00_B->loaded) {
        /* Transition: '<S166>:60' */
        LIBINFO_WL_00_TryToCommit_lksz(LIBINFO_WL_00_B, LIBINFO_WL_00_DWork);

        /* Transition: '<S166>:61' */
        LIBINFO_WL_00_DWork->is_Main_bd3y = LIBINFO_WL_00_IN_Loaded_ddwb;
      } else if (((!LIBINFO_WL_00_B->downForce) || (LIBINFO_WL_00_B->DesiredGear
        > 0)) || (LIBINFO_WL_00_B->LogicalOperator1)) {
        /* Transition: '<S166>:62' */
        LIBINFO_WL_00_TryToCommit_lksz(LIBINFO_WL_00_B, LIBINFO_WL_00_DWork);
        LIBINFO_WL_00_DWork->is_Main_bd3y = LIBINFO_WL_00_IN_Empty_gv30;
      } else {
        LIBINFO_WL_00_B->ST_Travel_ID = 25U;
      }
      break;

     case LIBINFO_WL_00_IN_Empty_gv30:
      /* During 'Empty': '<S166>:24' */
      if (LIBINFO_WL_00_B->loaded) {
        /* Transition: '<S166>:26' */
        LIBINFO_WL_00_TryToCommit_lksz(LIBINFO_WL_00_B, LIBINFO_WL_00_DWork);
        LIBINFO_WL_00_DWork->is_Main_bd3y = LIBINFO_WL_00_IN_Loaded_ddwb;
      } else if (((LIBINFO_WL_00_B->downForce) && (LIBINFO_WL_00_B->DesiredGear <
        0)) && (LIBINFO_WL_00_B->LogicalOperator)) {
        /* Transition: '<S166>:58' */
        LIBINFO_WL_00_TryToCommit_lksz(LIBINFO_WL_00_B, LIBINFO_WL_00_DWork);
        LIBINFO_WL_00_DWork->is_Main_bd3y = LIBINFO_WL_00_IN_Backdrag;
      } else {
        LIBINFO_WL_00_B->ST_Travel_ID = 3U;
      }
      break;

     default:
      /* During 'Loaded': '<S166>:23' */
      if (!LIBINFO_WL_00_B->loaded) {
        /* Transition: '<S166>:25' */
        LIBINFO_WL_00_TryToCommit_lksz(LIBINFO_WL_00_B, LIBINFO_WL_00_DWork);
        if (((LIBINFO_WL_00_B->downForce) && (LIBINFO_WL_00_B->DesiredGear < 0))
            && (LIBINFO_WL_00_B->LogicalOperator)) {
          /* Transition: '<S166>:55' */
          /* Transition: '<S166>:56' */
          LIBINFO_WL_00_DWork->is_Main_bd3y = LIBINFO_WL_00_IN_Backdrag;
        } else {
          /* Transition: '<S166>:57' */
          LIBINFO_WL_00_DWork->is_Main_bd3y = LIBINFO_WL_00_IN_Empty_gv30;
        }
      } else {
        LIBINFO_WL_00_B->ST_Travel_ID = 1U;
      }
      break;
    }
  }

  /* End of Chart: '<S98>/LoadedState' */

  /* Chart: '<S98>/TravellingState' */
  /* Gateway: ST_Travel/TravellingState */
  /* During: ST_Travel/TravellingState */
  if (LIBINFO_WL_00_DWork->is_active_c1_ST_Lib_Travel_MWL == 0U) {
    /* Entry: ST_Travel/TravellingState */
    LIBINFO_WL_00_DWork->is_active_c1_ST_Lib_Travel_MWL = 1U;

    /* Entry Internal: ST_Travel/TravellingState */
    LIBINFO_WL_00_DWork->is_active_TentativeTimer = 1U;

    /* Entry Internal 'TentativeTimer': '<S168>:135' */
    /* Transition: '<S168>:136' */
    /*  Tentative  */
    if (LIBINFO_WL_00_B->ST_Travel_State == 1) {
      /* Transition: '<S168>:140' */
      /*  Not Saturated  */
      if ((LIBINFO_WL_00_DWork->tentativeCounter < LIBINFO_WL_00_B->Divide1_gfci)
          || (LIBINFO_WL_00_DWork->tentativeCounter <
              LIBINFO_WL_00_B->Divide2_dnc1)) {
        /* Transition: '<S168>:145' */
        /* Transition: '<S168>:150' */
        LIBINFO_WL_00_DWork->tentativeCounter++;

        /* Transition: '<S168>:151' */
      } else {
        /* Transition: '<S168>:147' */
      }

      /* Transition: '<S168>:148' */
    } else {
      /* Transition: '<S168>:142' */
    }

    LIBINFO_WL_00_DWork->is_active_Main_i2cf = 1U;

    /* Entry Internal 'Main': '<S168>:42' */
    /* Transition: '<S168>:36' */
    LIBINFO_WL_00_DWork->is_Main_ko0u = LIBINFO_WL_00_IN_NotTravelling;

    /* Entry 'NotTravelling': '<S168>:1' */
    LIBINFO_WL_00_B->ST_Travel_State = 0U;
    LIBINFO_WL_00_DWork->tentativeCounter = 0U;

    /* Entry Internal 'NotTravelling': '<S168>:1' */
    /* Transition: '<S168>:17' */
    if (LIBINFO_WL_00_B->DesiredGear == 0) {
      /* Transition: '<S168>:15' */
      LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_Neutral;
    } else {
      /* Transition: '<S168>:60' */
      if (LIBINFO_WL_00_B->DesiredGear < 0) {
        /* Transition: '<S168>:69' */
        LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_ReverseInit;
      } else {
        /* Transition: '<S168>:68' */
        /* Transition: '<S168>:16' */
        LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_00_IN_ForwardInit;
      }
    }
  } else {
    /* During 'TentativeTimer': '<S168>:135' */
    /* Transition: '<S168>:136' */
    /*  Tentative  */
    if (LIBINFO_WL_00_B->ST_Travel_State == 1) {
      /* Transition: '<S168>:140' */
      /*  Not Saturated  */
      if ((LIBINFO_WL_00_DWork->tentativeCounter < LIBINFO_WL_00_B->Divide1_gfci)
          || (LIBINFO_WL_00_DWork->tentativeCounter <
              LIBINFO_WL_00_B->Divide2_dnc1)) {
        /* Transition: '<S168>:145' */
        /* Transition: '<S168>:150' */
        LIBINFO_WL_00_DWork->tentativeCounter++;

        /* Transition: '<S168>:151' */
      } else {
        /* Transition: '<S168>:147' */
      }

      /* Transition: '<S168>:148' */
    } else {
      /* Transition: '<S168>:142' */
    }

    LIBINFO_WL_00_Main(LIBINFO_WL_00_B, LIBINFO_WL_00_DWork);
  }

  /* End of Chart: '<S98>/TravellingState' */

  /* SignalConversion: '<S4>/ConcatBufferAtVector ConcatenateIn5' */
  LIBINFO_WL_00_B->VectorConcatenate[4] = LIBINFO_WL_00_B->ST_Travel_State;

  /* UnitDelay: '<S160>/IsFirstOrSecondLoop' */
  rtb_LogicalOperator = LIBINFO_WL_00_DWork->IsFirstOrSecondLoop_DSTATE_m13y;

  /* UnitDelay: '<S160>/Unit Delay1' */
  rtb_UnitDelay1_awom = LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_fpb3;

  /* UnitDelay: '<S160>/Unit Delay' */
  rtb_UnitDelay_lqy0 = LIBINFO_WL_00_DWork->UnitDelay_DSTATE_dqoa;

  /* MinMax: '<S160>/Min' */
  if (rtb_UnitDelay1_awom <= rtb_UnitDelay_lqy0) {
    rtb_Switch_lbk1 = rtb_UnitDelay1_awom;
  } else {
    rtb_Switch_lbk1 = rtb_UnitDelay_lqy0;
  }

  if (!(rtb_Switch_lbk1 <= LIBINFO_WL_00_B->GroundSpeed_iutz)) {
    rtb_Switch_lbk1 = LIBINFO_WL_00_B->GroundSpeed_iutz;
  }

  /* If: '<S160>/If' incorporates:
   *  MinMax: '<S160>/Min'
   *  RelationalOperator: '<S160>/Relational Operator'
   *  RelationalOperator: '<S160>/Relational Operator1'
   */
  if (LIBINFO_WL_00_B->GroundSpeed_iutz == rtb_Switch_lbk1) {
    /* Outputs for IfAction SubSystem: '<S160>/x0_is_min' incorporates:
     *  ActionPort: '<S161>/Action Port'
     */
    LIBINFO_WL_00_x0_is_min(rtb_UnitDelay_lqy0, rtb_UnitDelay1_awom,
      &rtb_Merge_e5fa);

    /* End of Outputs for SubSystem: '<S160>/x0_is_min' */
  } else if (rtb_UnitDelay_lqy0 == rtb_Switch_lbk1) {
    /* Outputs for IfAction SubSystem: '<S160>/x1_is_min' incorporates:
     *  ActionPort: '<S162>/Action Port'
     */
    LIBINFO_WL_00_x1_is_min(LIBINFO_WL_00_B->GroundSpeed_iutz,
      rtb_UnitDelay1_awom, &rtb_Merge_e5fa);

    /* End of Outputs for SubSystem: '<S160>/x1_is_min' */
  } else {
    /* Outputs for IfAction SubSystem: '<S160>/x2_is_min' incorporates:
     *  ActionPort: '<S163>/Action Port'
     */
    LIBINFO_WL_00_x2_is_min(LIBINFO_WL_00_B->GroundSpeed_iutz,
      rtb_UnitDelay_lqy0, &rtb_Merge_e5fa);

    /* End of Outputs for SubSystem: '<S160>/x2_is_min' */
  }

  /* End of If: '<S160>/If' */

  /* Switch: '<S160>/Switch' */
  if (rtb_LogicalOperator) {
    rtb_Switch_lbk1 = LIBINFO_WL_00_B->GroundSpeed_iutz;
  } else {
    rtb_Switch_lbk1 = rtb_Merge_e5fa;
  }

  /* End of Switch: '<S160>/Switch' */

  /* Abs: '<S159>/Abs' */
  if (rtb_Switch_lbk1 < 0) {
    rtb_Switch_lbk1 = (int16_t)(-rtb_Switch_lbk1);
  }

  /* End of Abs: '<S159>/Abs' */

  /* RelationalOperator: '<S159>/Relational Operator' incorporates:
   *  Constant: '<S97>/Constant9'
   */
  rtb_LogicalOperator = (rtb_Switch_lbk1 <=
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_Stopped_GroundSpeedThreshold);

  /* Product: '<S97>/Divide' incorporates:
   *  Constant: '<S97>/Constant5'
   */
  rtb_Divide_k0qy = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_Stopped_ActiveTime) /
    6U);

  /* Product: '<S97>/Divide1' incorporates:
   *  Constant: '<S97>/Constant8'
   */
  rtb_Divide1 = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_Stopped_InactiveTime)
    / 6U);

  /* Product: '<S97>/Divide2' incorporates:
   *  Constant: '<S97>/Constant11'
   *  Product: '<S97>/Product'
   */
  rtb_Divide2 = (dt_libinfo_Count)(((uint32_t)((uint16_t)((((uint32_t)((uint16_t)
    ((((uint32_t)
       LIBINFO_WL_00_M->
       LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_Stopped_CommitTime)
      * 375U) >> 3))) * 41943U) >> 15))) / 6U);

  /* Product: '<S97>/Divide3' incorporates:
   *  Constant: '<S97>/Constant7'
   */
  LIBINFO_WL_00_B->Divide3_ikji = (dt_libinfo_Count)(((uint32_t)
    LIBINFO_WL_00_M->
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p->ST_Travel_MinSegmentTime)
    / 6U);

  /* SignalConversion: '<S156>/Copy' */
  LIBINFO_WL_00_B->loaded_oaen = LIBINFO_WL_00_B->Loaded;

  /* Chart: '<S97>/LoadState' incorporates:
   *  Constant: '<S97>/Constant10'
   *  Constant: '<S97>/Constant3'
   */
  /* Gateway: ST_MachineIdle/LoadState */
  /* During: ST_MachineIdle/LoadState */
  if (LIBINFO_WL_00_DWork->is_active_c2_ST_Lib_MachineIdle == 0U) {
    /* Entry: ST_MachineIdle/LoadState */
    LIBINFO_WL_00_DWork->is_active_c2_ST_Lib_MachineIdle = 1U;

    /* Entry Internal: ST_MachineIdle/LoadState */
    LIBINFO_WL_00_DWork->is_active_Counter_c1rm = 1U;

    /* Entry Internal 'Counter': '<S158>:70' */
    /* Transition: '<S158>:71' */
    LIBINFO_WL_00_DWork->segmentTimeCounter_mxc2 = LIBINFO_WL_00_B->Divide3_ikji;
    if (LIBINFO_WL_00_DWork->segmentTimeCounter_mxc2 <
        LIBINFO_WL_00_B->Divide3_ikji) {
      /* Transition: '<S158>:77' */
      /* Transition: '<S158>:82' */
      LIBINFO_WL_00_DWork->segmentTimeCounter_mxc2++;
    } else {
      /* Transition: '<S158>:79' */
      /* Transition: '<S158>:83' */
    }

    /* Transition: '<S158>:85' */
    LIBINFO_WL_00_B->commit = FALSE;
    LIBINFO_WL_00_DWork->is_active_Main_avkc = 1U;

    /* Entry Internal 'Main': '<S158>:66' */
    /* Transition: '<S158>:39' */
    if (!LIBINFO_WL_00_B->loaded_oaen) {
      /* Transition: '<S158>:42' */
      /* Transition: '<S158>:43' */
      LIBINFO_WL_00_B->ST_Stopped_ID = 22U;
      LIBINFO_WL_00_DWork->is_Main_ij3t = LIBINFO_WL_00_IN_Empty;
    } else {
      /* Transition: '<S158>:40' */
      LIBINFO_WL_00_B->ST_Stopped_ID = 21U;
      LIBINFO_WL_00_DWork->is_Main_ij3t = LIBINFO_WL_00_IN_Loaded_a1mm;
    }
  } else {
    /* During 'Counter': '<S158>:70' */
    /* Transition: '<S158>:80' */
    if (LIBINFO_WL_00_DWork->segmentTimeCounter_mxc2 <
        LIBINFO_WL_00_B->Divide3_ikji) {
      /* Transition: '<S158>:77' */
      /* Transition: '<S158>:82' */
      LIBINFO_WL_00_DWork->segmentTimeCounter_mxc2++;
    } else {
      /* Transition: '<S158>:79' */
      /* Transition: '<S158>:83' */
    }

    /* Transition: '<S158>:85' */
    LIBINFO_WL_00_B->commit = FALSE;

    /* During 'Main': '<S158>:66' */
    if (LIBINFO_WL_00_DWork->is_Main_ij3t == LIBINFO_WL_00_IN_Empty) {
      /* During 'Empty': '<S158>:24' */
      if (LIBINFO_WL_00_B->loaded_oaen) {
        /* Transition: '<S158>:26' */
        LIBINFO_WL_00_TryToCommit(LIBINFO_WL_00_B, LIBINFO_WL_00_DWork);
        LIBINFO_WL_00_DWork->is_Main_ij3t = LIBINFO_WL_00_IN_Loaded_a1mm;
      } else {
        LIBINFO_WL_00_B->ST_Stopped_ID = 22U;
      }
    } else {
      /* During 'Loaded': '<S158>:23' */
      if (!LIBINFO_WL_00_B->loaded_oaen) {
        /* Transition: '<S158>:25' */
        LIBINFO_WL_00_TryToCommit(LIBINFO_WL_00_B, LIBINFO_WL_00_DWork);
        LIBINFO_WL_00_DWork->is_Main_ij3t = LIBINFO_WL_00_IN_Empty;
      } else {
        LIBINFO_WL_00_B->ST_Stopped_ID = 21U;
      }
    }
  }

  /* End of Chart: '<S97>/LoadState' */

  /* Chart: '<S97>/IdleState' */
  /* Gateway: ST_MachineIdle/IdleState */
  /* During: ST_MachineIdle/IdleState */
  if (LIBINFO_WL_00_DWork->is_active_c1_ST_Lib_MachineIdle == 0U) {
    /* Entry: ST_MachineIdle/IdleState */
    LIBINFO_WL_00_DWork->is_active_c1_ST_Lib_MachineIdle = 1U;

    /* Entry Internal: ST_MachineIdle/IdleState */
    LIBINFO_WL_00_DWork->is_active_Main_fhmh = 1U;

    /* Entry Internal 'Main': '<S157>:185' */
    /* Transition: '<S157>:189' */
    LIBINFO_WL_00_DWork->is_Main_nw5d = LIBINFO_WL_00_IN_NotStopped;

    /* Entry 'NotStopped': '<S157>:214' */
    LIBINFO_WL_00_B->ST_Stopped_State = 0U;
    LIBINFO_WL_00_B->commitOut = FALSE;
  } else {
    /* During 'Main': '<S157>:185' */
    switch (LIBINFO_WL_00_DWork->is_Main_nw5d) {
     case LIBINFO_WL_00_IN_NotStopped:
      /* During 'NotStopped': '<S157>:214' */
      /*  Tentatively Stopped Condition  */
      if (rtb_LogicalOperator && (LIBINFO_WL_00_B->ImplOperationStatus == 0)) {
        /* Transition: '<S157>:289' */
        LIBINFO_WL_00_DWork->is_Main_nw5d = LIBINFO_W_IN_TentativelyStopped;

        /* Entry 'TentativelyStopped': '<S157>:203' */
        LIBINFO_WL_00_B->ST_Stopped_State = 1U;
        LIBINFO_WL_00_B->commitOut = FALSE;
        LIBINFO_WL_00_DWork->ActiveDebounceCounter = 0U;
      }
      break;

     case LIBINFO_WL_00_IN_Stopped:
      /* During 'Stopped': '<S157>:240' */
      if ((!rtb_LogicalOperator) || (LIBINFO_WL_00_B->ImplOperationStatus != 0))
      {
        /* Transition: '<S157>:292' */
        if (LIBINFO_WL_00_B->commit) {
          /* Transition: '<S157>:301' */
          LIBINFO_WL_00_DWork->is_Main_nw5d = LIBINFO_WL_00_IN_NotStopped;

          /* Entry 'NotStopped': '<S157>:214' */
          LIBINFO_WL_00_B->ST_Stopped_State = 0U;
          LIBINFO_WL_00_B->commitOut = FALSE;
        } else {
          /* Transition: '<S157>:300' */
          LIBINFO_WL_00_DWork->is_Main_nw5d = LIBINF_IN_TentativelyNotStopped;

          /* Entry 'TentativelyNotStopped': '<S157>:250' */
          LIBINFO_WL_00_B->ST_Stopped_State = 2U;
          LIBINFO_WL_00_B->commitOut = FALSE;
          LIBINFO_WL_00_DWork->InactiveDebounceCounter = 1U;
        }
      } else if (LIBINFO_WL_00_DWork->ActiveDebounceCounter >= rtb_Divide2) {
        /* Transition: '<S157>:284' */
        /* Transition: '<S157>:283' */
        /* Transition: '<S157>:288' */
        /*  Periodic Commit every 5 min  */
        LIBINFO_WL_00_B->commitOut = TRUE;
        LIBINFO_WL_00_DWork->ActiveDebounceCounter = 0U;

        /* Transition: '<S157>:298' */
        LIBINFO_WL_00_DWork->is_Main_nw5d = LIBINFO_WL_00_IN_Stopped;

        /* Entry 'Stopped': '<S157>:240' */
        LIBINFO_WL_00_B->ST_Stopped_State = 2U;
        LIBINFO_WL_00_DWork->ActiveDebounceCounter++;
      } else {
        LIBINFO_WL_00_B->commitOut = FALSE;
        LIBINFO_WL_00_DWork->ActiveDebounceCounter++;
      }
      break;

     case LIBINF_IN_TentativelyNotStopped:
      /* During 'TentativelyNotStopped': '<S157>:250' */
      if (rtb_LogicalOperator && (LIBINFO_WL_00_B->ImplOperationStatus == 0)) {
        /* Transition: '<S157>:293' */
        LIBINFO_WL_00_DWork->is_Main_nw5d = LIBINFO_WL_00_IN_Stopped;

        /* Entry 'Stopped': '<S157>:240' */
        LIBINFO_WL_00_B->ST_Stopped_State = 2U;
        LIBINFO_WL_00_DWork->ActiveDebounceCounter++;
      } else if ((LIBINFO_WL_00_DWork->InactiveDebounceCounter >= rtb_Divide1) ||
                 (LIBINFO_WL_00_B->commit)) {
        /* Transition: '<S157>:294' */
        LIBINFO_WL_00_DWork->is_Main_nw5d = LIBINFO_WL_00_IN_NotStopped;

        /* Entry 'NotStopped': '<S157>:214' */
        LIBINFO_WL_00_B->ST_Stopped_State = 0U;
        LIBINFO_WL_00_B->commitOut = FALSE;
      } else {
        LIBINFO_WL_00_DWork->InactiveDebounceCounter++;
      }
      break;

     default:
      /* During 'TentativelyStopped': '<S157>:203' */
      if ((!rtb_LogicalOperator) || (LIBINFO_WL_00_B->ImplOperationStatus != 0))
      {
        /* Transition: '<S157>:295' */
        LIBINFO_WL_00_DWork->is_Main_nw5d = LIBINFO_WL_00_IN_NotStopped;

        /* Entry 'NotStopped': '<S157>:214' */
        LIBINFO_WL_00_B->ST_Stopped_State = 0U;
        LIBINFO_WL_00_B->commitOut = FALSE;
      } else {
        /*  Confirmed Stopped */
        if (LIBINFO_WL_00_DWork->ActiveDebounceCounter >= rtb_Divide_k0qy) {
          /* Transition: '<S157>:286' */
          LIBINFO_WL_00_DWork->is_Main_nw5d = LIBINFO_WL_00_IN_Stopped;

          /* Entry 'Stopped': '<S157>:240' */
          LIBINFO_WL_00_B->ST_Stopped_State = 2U;
          LIBINFO_WL_00_DWork->ActiveDebounceCounter++;
        } else {
          LIBINFO_WL_00_DWork->ActiveDebounceCounter++;
        }
      }
      break;
    }
  }

  /* End of Chart: '<S97>/IdleState' */

  /* SignalConversion: '<S4>/ConcatBufferAtVector ConcatenateIn6' */
  LIBINFO_WL_00_B->VectorConcatenate[5] = LIBINFO_WL_00_B->ST_Stopped_State;

  /* SignalConversion: '<S4>/ConcatBufferAtVector ConcatenateIn7' incorporates:
   *  Constant: '<S4>/ST_Misc_State'
   */
  LIBINFO_WL_00_B->VectorConcatenate[6] = 2U;

  /* Chart: '<S250>/Chart' */
  /* Gateway: Supervisor/Chart */
  /* During: Supervisor/Chart */
  /* Entry Internal: Supervisor/Chart */
  /* Transition: '<S252>:82' */
  LIBINFO_WL_00_findActiveIndex(LIBINFO_WL_00_M, LIBINFO_WL_00_B);

  /* Transition: '<S252>:85' */
  LIBINFO_WL_00_maskTentatives(LIBINFO_WL_00_M, LIBINFO_WL_00_B);

  /* Bias: '<S250>/To One Based' */
  LIBINFO_WL_00_B->ToOneBased = LIBINFO_WL_00_B->activeSegmentIndex + 1;

  /* Switch: '<S254>/Switch' incorporates:
   *  Constant: '<S254>/False'
   *  RelationalOperator: '<S254>/Relational Operator'
   *  UnitDelay: '<S254>/Unit Delay'
   */
  if (rtb_UnitDelay_mtyr) {
    rtb_LogicalOperator_inbd = FALSE;
  } else {
    rtb_LogicalOperator_inbd = (LIBINFO_WL_00_B->ToOneBased !=
      LIBINFO_WL_00_DWork->UnitDelay_DSTATE_hhbx);
  }

  /* End of Switch: '<S254>/Switch' */

  /* SignalConversion: '<S4>/ConcatBufferAtVector Concatenate2In1' */
  rtb_VectorConcatenate2[0] = LIBINFO_WL_00_B->ST_KeyStatus_Commit;

  /* SignalConversion: '<S4>/ConcatBufferAtVector Concatenate2In2' */
  rtb_VectorConcatenate2[1] = LIBINFO_WL_00_B->ST_Unknown_Commit;

  /* SignalConversion: '<S4>/ConcatBufferAtVector Concatenate2In3' */
  rtb_VectorConcatenate2[2] = FALSE;

  /* SignalConversion: '<S4>/ConcatBufferAtVector Concatenate2In4' */
  rtb_VectorConcatenate2[3] = FALSE;

  /* SignalConversion: '<S4>/ConcatBufferAtVector Concatenate2In5' */
  rtb_VectorConcatenate2[4] = LIBINFO_WL_00_B->ST_Travel_Commit;

  /* Logic: '<S97>/Logical Operator' */
  LIBINFO_WL_00_B->ST_Stopped_Commit = ((LIBINFO_WL_00_B->commitOut) ||
    (LIBINFO_WL_00_B->commit));

  /* SignalConversion: '<S4>/ConcatBufferAtVector Concatenate2In6' */
  rtb_VectorConcatenate2[5] = LIBINFO_WL_00_B->ST_Stopped_Commit;

  /* SignalConversion: '<S4>/ConcatBufferAtVector Concatenate2In7' incorporates:
   *  Constant: '<S4>/False'
   */
  rtb_VectorConcatenate2[6] = FALSE;

  /* Outputs for Enabled SubSystem: '<S258>/Bounded Selection' incorporates:
   *  EnablePort: '<S266>/Enable'
   */
  /* Logic: '<S258>/Logical Operator' incorporates:
   *  RelationalOperator: '<S258>/Relational Operator'
   *  RelationalOperator: '<S267>/Compare'
   */
  if ((7 >= LIBINFO_WL_00_B->ToOneBased) && (LIBINFO_WL_00_B->ToOneBased > 0)) {
    /* Selector: '<S266>/Selector' */
    LIBINFO_WL_00_B->Selector_dwy1 = rtb_VectorConcatenate2
      [LIBINFO_WL_00_B->ToOneBased - 1];
  }

  /* End of Logic: '<S258>/Logical Operator' */
  /* End of Outputs for SubSystem: '<S258>/Bounded Selection' */

  /* UnitDelay: '<S251>/Unit Delay1' */
  rtb_UnitDelay1_kz4h = LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_nqrv;

  /* Switch: '<S254>/Switch1' incorporates:
   *  UnitDelay: '<S254>/Unit Delay'
   */
  if (rtb_UnitDelay_mtyr) {
    rtb_Switch1_mtge = LIBINFO_WL_00_B->ToOneBased;
  } else {
    rtb_Switch1_mtge = LIBINFO_WL_00_DWork->UnitDelay_DSTATE_hhbx;
  }

  /* End of Switch: '<S254>/Switch1' */

  /* SignalConversion: '<S4>/ConcatBufferAtVector Concatenate1In1' */
  rtb_VectorConcatenate1[0] = LIBINFO_WL_00_B->ST_KeyStatus_ID;

  /* SignalConversion: '<S4>/ConcatBufferAtVector Concatenate1In2' */
  rtb_VectorConcatenate1[1] = LIBINFO_WL_00_B->ST_Unknown_ID;

  /* Chart: '<S94>/DumpType' incorporates:
   *  Constant: '<S94>/Constant3'
   *  Constant: '<S94>/Constant6'
   */
  /* Gateway: ST_Dump/DumpType */
  /* During: ST_Dump/DumpType */
  if (LIBINFO_WL_00_DWork->is_active_c9_ST_Lib_Dump_MWL == 0U) {
    /* Entry: ST_Dump/DumpType */
    LIBINFO_WL_00_DWork->is_active_c9_ST_Lib_Dump_MWL = 1U;

    /* Entry Internal: ST_Dump/DumpType */
    /* Transition: '<S138>:22' */
    LIBINFO_WL_00_B->ST_Dump_ID = 2U;
    if (LIBINFO_WL_00_B->ST_Dump_State_exsh == 2) {
      /* Transition: '<S138>:25' */
      /* Transition: '<S138>:26' */
      LIBINFO_WL_00_DWork->is_c9_ST_Lib_Dump_MWL = LIBINFO_WL_00_IN_Dumping;

      /* Entry Internal 'Dumping': '<S138>:8' */
      /* Transition: '<S138>:13' */
      if (LIBINFO_WL_00_B->IsFullDump) {
        /* Transition: '<S138>:18' */
        /* Transition: '<S138>:19' */
        LIBINFO_WL_00_DWork->is_Dumping = LIBINFO_WL_00_IN_FullDump;

        /* Entry 'FullDump': '<S138>:10' */
        LIBINFO_WL_00_B->ST_Dump_StateIsFull_neg0 = TRUE;
      } else {
        /* Transition: '<S138>:15' */
        LIBINFO_WL_00_DWork->is_Dumping = LIBINFO_WL_00_IN_PartialDump;

        /* Entry 'PartialDump': '<S138>:9' */
        LIBINFO_WL_00_B->ST_Dump_ID = 24U;
        LIBINFO_WL_00_B->ST_Dump_StateIsFull_neg0 = FALSE;
      }
    } else {
      /* Transition: '<S138>:27' */
      LIBINFO_WL_00_DWork->is_c9_ST_Lib_Dump_MWL = LIBINFO_WL_00_IN_NotDumping;

      /* Entry 'NotDumping': '<S138>:7' */
      LIBINFO_WL_00_B->ST_Dump_StateIsFull_neg0 = FALSE;
    }
  } else if (LIBINFO_WL_00_DWork->is_c9_ST_Lib_Dump_MWL ==
             LIBINFO_WL_00_IN_Dumping) {
    /* During 'Dumping': '<S138>:8' */
    if (LIBINFO_WL_00_B->ST_Dump_State_exsh != 2) {
      /* Transition: '<S138>:12' */
      /* Exit Internal 'Dumping': '<S138>:8' */
      LIBINFO_WL_00_DWork->is_Dumping = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
      LIBINFO_WL_00_DWork->is_c9_ST_Lib_Dump_MWL = LIBINFO_WL_00_IN_NotDumping;

      /* Entry 'NotDumping': '<S138>:7' */
      LIBINFO_WL_00_B->ST_Dump_StateIsFull_neg0 = FALSE;
    } else {
      switch (LIBINFO_WL_00_DWork->is_Dumping) {
       case LIBINFO_WL_00_IN_FullDump:
        break;

       default:
        /* During 'PartialDump': '<S138>:9' */
        if (LIBINFO_WL_00_B->IsFullDump) {
          /* Transition: '<S138>:16' */
          LIBINFO_WL_00_DWork->is_Dumping = LIBINFO_WL_00_IN_FullDump;

          /* Entry 'FullDump': '<S138>:10' */
          LIBINFO_WL_00_B->ST_Dump_ID = 2U;
          LIBINFO_WL_00_B->ST_Dump_StateIsFull_neg0 = TRUE;
        }
        break;
      }
    }
  } else {
    /* During 'NotDumping': '<S138>:7' */
    if (LIBINFO_WL_00_B->ST_Dump_State_exsh == 2) {
      /* Transition: '<S138>:11' */
      LIBINFO_WL_00_DWork->is_c9_ST_Lib_Dump_MWL = LIBINFO_WL_00_IN_Dumping;

      /* Entry Internal 'Dumping': '<S138>:8' */
      /* Transition: '<S138>:13' */
      if (LIBINFO_WL_00_B->IsFullDump) {
        /* Transition: '<S138>:18' */
        /* Transition: '<S138>:19' */
        LIBINFO_WL_00_DWork->is_Dumping = LIBINFO_WL_00_IN_FullDump;

        /* Entry 'FullDump': '<S138>:10' */
        LIBINFO_WL_00_B->ST_Dump_ID = 2U;
        LIBINFO_WL_00_B->ST_Dump_StateIsFull_neg0 = TRUE;
      } else {
        /* Transition: '<S138>:15' */
        LIBINFO_WL_00_DWork->is_Dumping = LIBINFO_WL_00_IN_PartialDump;

        /* Entry 'PartialDump': '<S138>:9' */
        LIBINFO_WL_00_B->ST_Dump_ID = 24U;
        LIBINFO_WL_00_B->ST_Dump_StateIsFull_neg0 = FALSE;
      }
    }
  }

  /* End of Chart: '<S94>/DumpType' */

  /* SignalConversion: '<S4>/ConcatBufferAtVector Concatenate1In3' */
  rtb_VectorConcatenate1[2] = LIBINFO_WL_00_B->ST_Dump_ID;

  /* SignalConversion: '<S4>/ConcatBufferAtVector Concatenate1In4' */
  rtb_VectorConcatenate1[3] = 0U;

  /* SignalConversion: '<S4>/ConcatBufferAtVector Concatenate1In5' */
  rtb_VectorConcatenate1[4] = LIBINFO_WL_00_B->ST_Travel_ID;

  /* SignalConversion: '<S4>/ConcatBufferAtVector Concatenate1In6' */
  rtb_VectorConcatenate1[5] = LIBINFO_WL_00_B->ST_Stopped_ID;

  /* SignalConversion: '<S4>/ConcatBufferAtVector Concatenate1In7' incorporates:
   *  Constant: '<S4>/MiscID'
   */
  rtb_VectorConcatenate1[6] = 15U;

  /* Logic: '<S260>/Logical Operator' incorporates:
   *  RelationalOperator: '<S260>/Relational Operator'
   *  RelationalOperator: '<S273>/Compare'
   */
  rtb_LogicalOperator_n2oa = ((7 >= LIBINFO_WL_00_B->ToOneBased) &&
    (LIBINFO_WL_00_B->ToOneBased > 0));

  /* Outputs for Enabled SubSystem: '<S260>/Bounded Selection' */
  LIBINFO_WL_00_BoundedSelection(rtb_LogicalOperator_n2oa,
    rtb_VectorConcatenate1, LIBINFO_WL_00_B->ToOneBased,
    &LIBINFO_WL_00_B->Selector_jui4);

  /* End of Outputs for SubSystem: '<S260>/Bounded Selection' */

  /* If: '<S251>/If' incorporates:
   *  Switch: '<S251>/Switch'
   *  UnitDelay: '<S257>/Unit Delay'
   */
  if (rtb_LogicalOperator_inbd) {
    /* Outputs for IfAction SubSystem: '<S251>/If Index Changed' incorporates:
     *  ActionPort: '<S259>/Action Port'
     */
    /* Switch: '<S268>/Switch' incorporates:
     *  Constant: '<S268>/Constant'
     *  Constant: '<S268>/Constant1'
     *  RelationalOperator: '<S268>/Relational Operator'
     *  Sum: '<S268>/Sum'
     */
    if (rtb_UnitDelay1_kz4h >=
        LIBINFO_WL_00_M->
        LIBINFO_WL_00_LIBINFO_Totalizer_00_calcompfix_mi_ROM_p->ST_Tot_MaxSeqNum)
    {
      rtb_UnitDelay1_kz4h = 0U;
    } else {
      rtb_UnitDelay1_kz4h = (dt_libinfo_Flag)(((uint32_t)rtb_UnitDelay1_kz4h) +
        1U);
    }

    /* End of Switch: '<S268>/Switch' */

    /* Logic: '<S269>/Logical Operator' incorporates:
     *  RelationalOperator: '<S269>/Relational Operator'
     *  RelationalOperator: '<S271>/Compare'
     */
    rtb_LogicalOperator_fbxv = ((7 >= rtb_Switch1_mtge) && (rtb_Switch1_mtge > 0));

    /* Outputs for Enabled SubSystem: '<S269>/Bounded Selection' */
    LIBINFO_WL_00_BoundedSelection(rtb_LogicalOperator_fbxv,
      rtb_VectorConcatenate1, rtb_Switch1_mtge, &LIBINFO_WL_00_B->Merge2);

    /* End of Outputs for SubSystem: '<S269>/Bounded Selection' */

    /* End of Outputs for SubSystem: '<S251>/If Index Changed' */
  } else if (LIBINFO_WL_00_B->Selector_dwy1) {
    /* Outputs for IfAction SubSystem: '<S251>/ElseIf Forced Commit' incorporates:
     *  ActionPort: '<S256>/Action Port'
     */
    /* Switch: '<S262>/Switch' incorporates:
     *  Constant: '<S262>/Constant'
     *  Constant: '<S262>/Constant1'
     *  RelationalOperator: '<S262>/Relational Operator'
     *  Sum: '<S262>/Sum'
     */
    if (rtb_UnitDelay1_kz4h >=
        LIBINFO_WL_00_M->
        LIBINFO_WL_00_LIBINFO_Totalizer_00_calcompfix_mi_ROM_p->ST_Tot_MaxSeqNum)
    {
      rtb_UnitDelay1_kz4h = 0U;
    } else {
      rtb_UnitDelay1_kz4h = (dt_libinfo_Flag)(((uint32_t)rtb_UnitDelay1_kz4h) +
        1U);
    }

    /* End of Switch: '<S262>/Switch' */

    /* Logic: '<S263>/Logical Operator' incorporates:
     *  RelationalOperator: '<S263>/Relational Operator'
     *  RelationalOperator: '<S265>/Compare'
     */
    rtb_LogicalOperator_dmm0 = ((7 >= LIBINFO_WL_00_B->ToOneBased) &&
      (LIBINFO_WL_00_B->ToOneBased > 0));

    /* Outputs for Enabled SubSystem: '<S263>/Bounded Selection' */
    LIBINFO_WL_00_BoundedSelection(rtb_LogicalOperator_dmm0,
      rtb_VectorConcatenate1, LIBINFO_WL_00_B->ToOneBased,
      &LIBINFO_WL_00_B->Merge2);

    /* End of Outputs for SubSystem: '<S263>/Bounded Selection' */

    /* End of Outputs for SubSystem: '<S251>/ElseIf Forced Commit' */
  } else if (LIBINFO_WL_00_DWork->UnitDelay_DSTATE_grmj) {
    /* Outputs for IfAction SubSystem: '<S251>/Else' incorporates:
     *  ActionPort: '<S255>/Action Port'
     */
    /* Switch: '<S251>/Switch' incorporates:
     *  Inport: '<S255>/prevCommitSegmentID'
     */
    LIBINFO_WL_00_B->Merge2 = LIBINFO_WL_00_B->Selector_jui4;

    /* End of Outputs for SubSystem: '<S251>/Else' */
  } else {
    /* Outputs for IfAction SubSystem: '<S251>/Else' incorporates:
     *  ActionPort: '<S255>/Action Port'
     */
    /* Switch: '<S251>/Switch' incorporates:
     *  Inport: '<S255>/prevCommitSegmentID'
     *  UnitDelay: '<S251>/Unit Delay3'
     */
    LIBINFO_WL_00_B->Merge2 = LIBINFO_WL_00_DWork->UnitDelay3_DSTATE;

    /* End of Outputs for SubSystem: '<S251>/Else' */
  }

  /* End of If: '<S251>/If' */

  /* Switch: '<S304>/Switch' */
  if (rtb_UnitDelay_cxus) {
    rtb_UnitDelay_hhl4 = rtb_UnitDelay1_kz4h;
  }

  /* End of Switch: '<S304>/Switch' */

  /* RelationalOperator: '<S304>/Relational Operator' */
  LIBINFO_WL_00_B->RelationalOperator_idu2 = (rtb_UnitDelay1_kz4h !=
    rtb_UnitDelay_hhl4);

  /* SignalConversion: '<S191>/Copy' */
  LIBINFO_WL_00_B->GlobalTime = LIBINFO_WL_00_B->GlobalTime_bjze;

  /* SignalConversion: '<S467>/Copy' */
  LIBINFO_WL_00_B->globalTime = LIBINFO_WL_00_B->GlobalTime;

  /* Switch: '<S216>/Switch1' incorporates:
   *  Constant: '<S216>/Constant1'
   */
  if (LIBINFO_WL_00_B->GPSLatLongUnknown != 0) {
    LIBINFO_WL_00_B->Switch1_jkyk = 0U;
  } else {
    LIBINFO_WL_00_B->Switch1_jkyk = LIBINFO_WL_00_B->GPSLongitude;
  }

  /* End of Switch: '<S216>/Switch1' */

  /* Switch: '<S216>/Switch' incorporates:
   *  Constant: '<S216>/Constant'
   */
  if (LIBINFO_WL_00_B->GPSLatLongUnknown != 0) {
    LIBINFO_WL_00_B->Switch_nrdg = 0U;
  } else {
    LIBINFO_WL_00_B->Switch_nrdg = LIBINFO_WL_00_B->GPSLatitude;
  }

  /* End of Switch: '<S216>/Switch' */

  /* SignalConversion: '<S192>/Copy' */
  LIBINFO_WL_00_B->ServiceHourMeter = LIBINFO_WL_00_B->ServiceHourMeter_f3nw;

  /* SignalConversion: '<S415>/Copy' */
  LIBINFO_WL_00_B->hourMeter = LIBINFO_WL_00_B->ServiceHourMeter;

  /* Switch: '<S215>/Switch' incorporates:
   *  Constant: '<S215>/Constant'
   */
  if (LIBINFO_WL_00_B->ServiceHourMeterUnknown != 0) {
    LIBINFO_WL_00_B->Switch_bxww = 0U;
  } else {
    LIBINFO_WL_00_B->Switch_bxww = LIBINFO_WL_00_B->hourMeter;
  }

  /* End of Switch: '<S215>/Switch' */

  /* Switch: '<S214>/Switch1' incorporates:
   *  Constant: '<S214>/Constant'
   *  Constant: '<S214>/Constant1'
   *  Switch: '<S214>/Switch'
   */
  if (LIBINFO_WL_00_B->MachineIdleUnknown != 0) {
    LIBINFO_WL_00_B->Switch1 = (R2012b_rtNaNF);
  } else if (LIBINFO_WL_00_B->MachineIdle != 0) {
    /* Switch: '<S214>/Switch' incorporates:
     *  SampleTimeMath: '<S214>/Weighted Sample Time'
     *
     * About '<S214>/Weighted Sample Time':
     *  y = K where K = ( w * Ts )
     */
    LIBINFO_WL_00_B->Switch1 = 0.12F;
  } else {
    LIBINFO_WL_00_B->Switch1 = 0.0F;
  }

  /* End of Switch: '<S214>/Switch1' */

  /* UnitDelay: '<S303>/Unit Delay' */
  LIBINFO_WL_00_B->UnitDelay = LIBINFO_WL_00_DWork->UnitDelay_DSTATE_a1en;

  /* SampleTimeMath: '<S303>/Weighted Sample Time'
   *
   * About '<S303>/Weighted Sample Time':
   *  y = K where K = ( w * Ts )
   */
  LIBINFO_WL_00_B->WeightedSampleTime_p1jr = 6U;

  /* SignalConversion: '<S274>/Copy' */
  LIBINFO_WL_00_B->payloadWeight = LIBINFO_WL_00_B->PayloadWeight;

  /* Switch: '<S204>/Switch' incorporates:
   *  DataTypeConversion: '<S204>/Data Type Conversion'
   *  S-Function (sfix_bitop): '<S204>/Bitwise Operator'
   */
  if (LIBINFO_WL_00_B->PayloadWeightUnknown != 0) {
    LIBINFO_WL_00_B->Switch_ew4n = (dt_libinfo_Flag_u16)
      (LIBINFO_WL_00_B->PayloadCalcMethod & 61695);
  } else {
    LIBINFO_WL_00_B->Switch_ew4n = LIBINFO_WL_00_B->PayloadCalcMethod;
  }

  /* End of Switch: '<S204>/Switch' */

  /* Switch: '<S202>/Switch' incorporates:
   *  Constant: '<S202>/Constant'
   */
  if (LIBINFO_WL_00_B->TotalFuelUnknown != 0) {
    LIBINFO_WL_00_B->Switch = 0.0F;
  } else {
    /* Gain: '<S202>/to Liters' incorporates:
     *  DataTypeConversion: '<S202>/Data Type Conversion'
     *  Sum: '<S202>/Subtract'
     *  UnitDelay: '<S202>/Unit Delay'
     */
    LIBINFO_WL_00_B->Switch = (((real32_T)(LIBINFO_WL_00_B->FuelHighRes -
      LIBINFO_WL_00_DWork->UnitDelay_DSTATE_c01m)) * 0.001F) * 3.78541207F;

    /* Switch: '<S202>/Switch1' incorporates:
     *  Constant: '<S202>/Constant1'
     *  Constant: '<S202>/Constant2'
     *  Constant: '<S234>/Constant'
     *  DataTypeConversion: '<S202>/Data Type Conversion1'
     *  Gain: '<S202>/Gain'
     *  Logic: '<S202>/Logical Operator'
     *  RelationalOperator: '<S202>/NotTooBig'
     *  RelationalOperator: '<S234>/Compare'
     */
    if (!((LIBINFO_WL_00_B->Switch > 0.0F) && (LIBINFO_WL_00_B->Switch <
          (((real32_T)
            (LIBINFO_WL_00_M->LIBINFO_WL_00_LIBINFO_Totalizer_00_calcompfix_mi_ROM_p
             ->ST_FuelUsed_HighResIntgrlResol << 1)) * 0.001F)))) {
      LIBINFO_WL_00_B->Switch = 0.0F;
    }

    /* End of Switch: '<S202>/Switch1' */
  }

  /* End of Switch: '<S202>/Switch' */

  /* Switch: '<S201>/Switch' incorporates:
   *  Constant: '<S201>/Constant'
   *  DataTypeConversion: '<S201>/Data Type Conversion'
   */
  if (LIBINFO_WL_00_B->GroundSpeedUnknown != 0) {
    rtb_Product_fggn = (R2012b_rtNaNF);
  } else {
    rtb_Product_fggn = ((real32_T)LIBINFO_WL_00_B->GroundSpeed_iutz) *
      0.00390625F;
  }

  /* End of Switch: '<S201>/Switch' */

  /* SampleTimeMath: '<S201>/Weighted Sample Time' incorporates:
   *  Abs: '<S201>/Abs'
   *  Gain: '<S201>/Gain'
   *
   * About '<S201>/Weighted Sample Time':
   *  y = u * K where K = ( w * Ts )
   */
  LIBINFO_WL_00_B->WeightedSampleTime = (0.000277777785F * ((real32_T)fabs
    (rtb_Product_fggn))) * 0.12F;

  /* Chart: '<S309>/Chart' */
  /* Gateway: TotalizerUnionableStatManager_00_lib/Chart */
  /* During: TotalizerUnionableStatManager_00_lib/Chart */
  if (LIBINFO_WL_00_DWork->is_active_c1_TotalizerUnionable == 0U) {
    /* Entry: TotalizerUnionableStatManager_00_lib/Chart */
    LIBINFO_WL_00_DWork->is_active_c1_TotalizerUnionable = 1U;

    /* Entry Internal: TotalizerUnionableStatManager_00_lib/Chart */
    /* Transition: '<S347>:24' */
    LIBINFO_WL_00_B->bufferDepth = 0;
    LIBINFO_WL_00_appendActive(LIBINFO_WL_00_M, LIBINFO_WL_00_B);
    LIBINFO_WL_00_B->potentialSegmentStart = TRUE;
    LIBINFO_WL_00_DWork->is_c1_TotalizerUnionableStatMgr =
      LIBINFO_WL_00_IN_Update;

    /* Entry Internal 'Update': '<S347>:18' */
    /* Transition: '<S347>:43' */
    if (LIBINFO_WL_00_B->RelationalOperator_idu2) {
      /* Transition: '<S347>:46' */
      /* Transition: '<S347>:48' */
      LIBINFO__commitPreviouslyActive(LIBINFO_WL_00_B);

      /* Transition: '<S347>:50' */
    } else {
      /* Transition: '<S347>:51' */
    }

    /* Transition: '<S347>:54' */
    if (0 == LIBINFO_WL_00_B->bufferDepth) {
      /* Transition: '<S347>:56' */
      if (LIBINFO_WL_00_B->potentialSegmentStart) {
        /* Transition: '<S347>:190' */
        /* Transition: '<S347>:192' */
        LIBINFO_WL_00_appendActive(LIBINFO_WL_00_M, LIBINFO_WL_00_B);

        /* Transition: '<S347>:193' */
      } else {
        /* Transition: '<S347>:58' */
        LIBINFO_WL_00_B->potentialSegmentStart = LIBINFO_WL_00_appendActive
          (LIBINFO_WL_00_M, LIBINFO_WL_00_B);
      }

      /* Transition: '<S347>:60' */
    } else {
      /* Transition: '<S347>:61' */
    }

    /* Transition: '<S347>:65' */
    LIBINFO_WL_00_purgeInactives(LIBINFO_WL_00_B);
    if (LIBINFO_WL_00_B->potentialSegmentStart) {
      /* Transition: '<S347>:195' */
      /* Transition: '<S347>:197' */
      LIBINFO_WL_00_addTentatives(LIBINFO_WL_00_M, LIBINFO_WL_00_B);

      /* Transition: '<S347>:198' */
    } else {
      /* Transition: '<S347>:67' */
      LIBINFO_WL_00_B->potentialSegmentStart = LIBINFO_WL_00_addTentatives
        (LIBINFO_WL_00_M, LIBINFO_WL_00_B);
    }

    /* Outputs for Function Call SubSystem: '<S349>/FuncCallSplit1' */

    /* Transition: '<S347>:69' */
    /* Event: '<S347>:13' */
    LIBINFO_WL_00_FuncCallSplit1(LIBINFO_WL_00_B->Merge_i0jw,
      LIBINFO_WL_00_B->Merge_cxcm, LIBINFO_WL_00_B->bufferDepth,
      LIBINFO_WL_00_B->WeightedSampleTime_p1jr, LIBINFO_WL_00_B->Merge_jhvc,
      LIBINFO_WL_00_B->UnitDelay, LIBINFO_WL_00_B->Merge_haaq,
      LIBINFO_WL_00_B->Merge_a2nn, LIBINFO_WL_00_B->Merge_obd1,
      LIBINFO_WL_00_B->Merge1, LIBINFO_WL_00_B->Switch_ew4n,
      LIBINFO_WL_00_B->payloadWeight, LIBINFO_WL_00_B->Merge,
      LIBINFO_WL_00_B->WeightedSampleTime, LIBINFO_WL_00_B->Merge_oe45,
      LIBINFO_WL_00_B->Merge_bash, LIBINFO_WL_00_B->Switch,
      LIBINFO_WL_00_B->Merge_dfdv, LIBINFO_WL_00_B->Switch1,
      LIBINFO_WL_00_B->Merge_labi, LIBINFO_WL_00_B->Merge_i0jw,
      LIBINFO_WL_00_B->Merge_cxcm, LIBINFO_WL_00_B->Merge_jhvc,
      LIBINFO_WL_00_B->Merge_haaq, LIBINFO_WL_00_B->Merge_a2nn,
      LIBINFO_WL_00_B->Merge_obd1, LIBINFO_WL_00_B->Merge1,
      LIBINFO_WL_00_B->Merge, LIBINFO_WL_00_B->Merge_oe45,
      LIBINFO_WL_00_B->Merge_bash, LIBINFO_WL_00_B->Merge_dfdv,
      LIBINFO_WL_00_B->Merge_labi);

    /* End of Outputs for SubSystem: '<S349>/FuncCallSplit1' */
  } else {
    /* During 'Update': '<S347>:18' */
    /* Transition: '<S347>:188' */
    LIBINFO_WL_00_B->potentialSegmentStart = FALSE;
    if (LIBINFO_WL_00_B->RelationalOperator_idu2) {
      /* Transition: '<S347>:46' */
      /* Transition: '<S347>:48' */
      LIBINFO__commitPreviouslyActive(LIBINFO_WL_00_B);

      /* Transition: '<S347>:50' */
    } else {
      /* Transition: '<S347>:51' */
    }

    /* Transition: '<S347>:54' */
    if (0 == LIBINFO_WL_00_B->bufferDepth) {
      /* Transition: '<S347>:56' */
      if (LIBINFO_WL_00_B->potentialSegmentStart) {
        /* Transition: '<S347>:190' */
        /* Transition: '<S347>:192' */
        LIBINFO_WL_00_appendActive(LIBINFO_WL_00_M, LIBINFO_WL_00_B);

        /* Transition: '<S347>:193' */
      } else {
        /* Transition: '<S347>:58' */
        LIBINFO_WL_00_B->potentialSegmentStart = LIBINFO_WL_00_appendActive
          (LIBINFO_WL_00_M, LIBINFO_WL_00_B);
      }

      /* Transition: '<S347>:60' */
    } else {
      /* Transition: '<S347>:61' */
    }

    /* Transition: '<S347>:65' */
    LIBINFO_WL_00_purgeInactives(LIBINFO_WL_00_B);
    if (LIBINFO_WL_00_B->potentialSegmentStart) {
      /* Transition: '<S347>:195' */
      /* Transition: '<S347>:197' */
      LIBINFO_WL_00_addTentatives(LIBINFO_WL_00_M, LIBINFO_WL_00_B);

      /* Transition: '<S347>:198' */
    } else {
      /* Transition: '<S347>:67' */
      LIBINFO_WL_00_B->potentialSegmentStart = LIBINFO_WL_00_addTentatives
        (LIBINFO_WL_00_M, LIBINFO_WL_00_B);
    }

    /* Outputs for Function Call SubSystem: '<S349>/FuncCallSplit1' */

    /* Transition: '<S347>:69' */
    /* Event: '<S347>:13' */
    LIBINFO_WL_00_FuncCallSplit1(LIBINFO_WL_00_B->Merge_i0jw,
      LIBINFO_WL_00_B->Merge_cxcm, LIBINFO_WL_00_B->bufferDepth,
      LIBINFO_WL_00_B->WeightedSampleTime_p1jr, LIBINFO_WL_00_B->Merge_jhvc,
      LIBINFO_WL_00_B->UnitDelay, LIBINFO_WL_00_B->Merge_haaq,
      LIBINFO_WL_00_B->Merge_a2nn, LIBINFO_WL_00_B->Merge_obd1,
      LIBINFO_WL_00_B->Merge1, LIBINFO_WL_00_B->Switch_ew4n,
      LIBINFO_WL_00_B->payloadWeight, LIBINFO_WL_00_B->Merge,
      LIBINFO_WL_00_B->WeightedSampleTime, LIBINFO_WL_00_B->Merge_oe45,
      LIBINFO_WL_00_B->Merge_bash, LIBINFO_WL_00_B->Switch,
      LIBINFO_WL_00_B->Merge_dfdv, LIBINFO_WL_00_B->Switch1,
      LIBINFO_WL_00_B->Merge_labi, LIBINFO_WL_00_B->Merge_i0jw,
      LIBINFO_WL_00_B->Merge_cxcm, LIBINFO_WL_00_B->Merge_jhvc,
      LIBINFO_WL_00_B->Merge_haaq, LIBINFO_WL_00_B->Merge_a2nn,
      LIBINFO_WL_00_B->Merge_obd1, LIBINFO_WL_00_B->Merge1,
      LIBINFO_WL_00_B->Merge, LIBINFO_WL_00_B->Merge_oe45,
      LIBINFO_WL_00_B->Merge_bash, LIBINFO_WL_00_B->Merge_dfdv,
      LIBINFO_WL_00_B->Merge_labi);

    /* End of Outputs for SubSystem: '<S349>/FuncCallSplit1' */
  }

  /* End of Chart: '<S309>/Chart' */

  /* Logic: '<S205>/Logical Operator' incorporates:
   *  RelationalOperator: '<S302>/Compare'
   */
  rtb_LogicalOperator_inbd = ((LIBINFO_WL_00_B->RelationalOperator_idu2) &&
    (LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_hpld[0] > 0U));

  /* SignalConversion: '<S186>/Copy' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion5'
   */
  LIBINFO_WL_00_B->ST_commit_segment_record = (dt_libinfo_Flag)
    rtb_LogicalOperator_inbd;

  /* Outport: '<Root>/commit_segment_record' */
  *LIBINFO_WL_00_Y_commit_segment_record =
    LIBINFO_WL_00_B->ST_commit_segment_record;

  /* SignalConversion: '<S187>/Copy' */
  LIBINFO_WL_00_B->ST_segment_record_id = LIBINFO_WL_00_B->Merge2;

  /* Outport: '<Root>/segment_record_id' */
  *LIBINFO_WL_00_Y_segment_record_id = LIBINFO_WL_00_B->ST_segment_record_id;

  /* SignalConversion: '<S189>/Copy' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion10'
   */
  LIBINFO_WL_00_B->ST_segment_rec_start_simTime = (uint32_t)((((uint64_T)
    LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_ofwt[0]) * 2748779069UL) >> 37);

  /* Outport: '<Root>/segment_rec_start_simTime' */
  *LIBINFO_WL_00_Y_segment_rec_start_simTime =
    LIBINFO_WL_00_B->ST_segment_rec_start_simTime;

  /* SignalConversion: '<S190>/Copy' */
  LIBINFO_WL_00_B->ST_segment_rec_duration =
    LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_hpld[0];

  /* Outport: '<Root>/segment_rec_duration' */
  *LIBINFO_WL_00_Y_segment_rec_duration =
    LIBINFO_WL_00_B->ST_segment_rec_duration;

  /* SignalConversion: '<S182>/Copy' */
  LIBINFO_WL_00_B->ST_segment_rec_distance =
    LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_bcj2[0];

  /* Outport: '<Root>/segment_rec_distance' */
  *LIBINFO_WL_00_Y_segment_rec_distance =
    LIBINFO_WL_00_B->ST_segment_rec_distance;

  /* SignalConversion: '<S470>/Copy' */
  LIBINFO_WL_00_B->globalTime1 =
    LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_hky2[0];

  /* SignalConversion: '<S199>/Copy' */
  LIBINFO_WL_00_B->ST_segment_rec_start_realTime = LIBINFO_WL_00_B->globalTime1;

  /* Outport: '<Root>/segment_rec_start_real_time' */
  *LIBINFO_WL_00_Y_segment_rec_start_real_time =
    LIBINFO_WL_00_B->ST_segment_rec_start_realTime;

  /* SignalConversion: '<S183>/Copy' */
  LIBINFO_WL_00_B->ST_segment_rec_fuel_used =
    LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_oicb[0];

  /* Outport: '<Root>/segment_rec_fuel_used' */
  *LIBINFO_WL_00_Y_segment_rec_fuel_used =
    LIBINFO_WL_00_B->ST_segment_rec_fuel_used;

  /* SignalConversion: '<S195>/Copy' */
  LIBINFO_WL_00_B->ST_segment_rec_latitude =
    LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_pdov[0];

  /* Outport: '<Root>/segment_rec_latitude' */
  *LIBINFO_WL_00_Y_segment_rec_latitude =
    LIBINFO_WL_00_B->ST_segment_rec_latitude;

  /* SignalConversion: '<S196>/Copy' */
  LIBINFO_WL_00_B->ST_segment_rec_longitude =
    LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_edhm[0];

  /* Outport: '<Root>/segment_rec_longitude' */
  *LIBINFO_WL_00_Y_segment_rec_longitude =
    LIBINFO_WL_00_B->ST_segment_rec_longitude;

  /* SignalConversion: '<S197>/Copy' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion1'
   */
  LIBINFO_WL_00_B->ST_segment_rec_idle_time = (uint32_t)
    LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBufferOu[0];

  /* Outport: '<Root>/segment_rec_idle_time' */
  *LIBINFO_WL_00_Y_segment_rec_idle_time =
    LIBINFO_WL_00_B->ST_segment_rec_idle_time;

  /* SignalConversion: '<S418>/Copy' */
  LIBINFO_WL_00_B->globalTime1_hhgy =
    LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_mbyo[0];

  /* SignalConversion: '<S193>/Copy' */
  LIBINFO_WL_00_B->ST_segment_rec_hour_meter = LIBINFO_WL_00_B->globalTime1_hhgy;

  /* Outport: '<Root>/segment_rec_hour_meter' */
  *LIBINFO_WL_00_Y_segment_rec_hour_meter =
    LIBINFO_WL_00_B->ST_segment_rec_hour_meter;

  /* SignalConversion: '<S277>/Copy' */
  LIBINFO_WL_00_B->payloadWeight1 =
    LIBINFO_WL_00_B->TmpLatchAtinParamBufferOutport1[0];

  /* SignalConversion: '<S194>/Copy' */
  LIBINFO_WL_00_B->ST_segment_rec_payload = LIBINFO_WL_00_B->payloadWeight1;

  /* Outport: '<Root>/segment_rec_payload' */
  *LIBINFO_WL_00_Y_segment_rec_payload = LIBINFO_WL_00_B->ST_segment_rec_payload;

  /* SignalConversion: '<S198>/Copy' */
  LIBINFO_WL_00_B->ST_segment_rec_payload_calc_met =
    LIBINFO_WL_00_B->TmpLatchAtinParamConfBufferOutp[0];

  /* Outport: '<Root>/segment_rec_payload_calc_method' */
  *LIBINFO_WL_00_Y_segment_rec_payload_calc_method =
    LIBINFO_WL_00_B->ST_segment_rec_payload_calc_met;

  /* SignalConversion: '<S188>/Copy' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion4'
   */
  LIBINFO_WL_00_B->ST_commit_rec_gps = (dt_libinfo_Flag)rtb_LogicalOperator_inbd;

  /* Outport: '<Root>/commit_rec_gps' */
  *LIBINFO_WL_00_Y_commit_rec_gps = LIBINFO_WL_00_B->ST_commit_rec_gps;

  /* Outport: '<Root>/segment_dig_state' */
  *LIBINFO_WL_00_Y_segment_dig_state = LIBINFO_WL_00_B->ST_Dig_State_prjn;

  /* If: '<S206>/If' incorporates:
   *  Inport: '<S368>/commitSegmentID'
   *  Inport: '<S370>/prevLastSegmentID'
   *  Inport: '<S370>/prevSeqNum'
   *  UnitDelay: '<S206>/Unit Delay'
   *  UnitDelay: '<S206>/Unit Delay2'
   */
  if (rtb_LogicalOperator_inbd) {
    /* Outputs for IfAction SubSystem: '<S206>/Commit' incorporates:
     *  ActionPort: '<S368>/Action Port'
     */
    rtb_UnitDelay_hhl4 = LIBINFO_WL_00_B->Merge2;

    /* Sum: '<S368>/Sum' incorporates:
     *  Inport: '<S368>/commitSegmentID'
     */
    rtb_MinMax = LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_ofwt[0] +
      LIBINFO_WL_00_B->TmpLatchAtinAccumulatorBuf_hpld[0];

    /* Switch: '<S371>/Switch' incorporates:
     *  Constant: '<S371>/Constant'
     *  Constant: '<S371>/Constant1'
     *  RelationalOperator: '<S371>/Relational Operator'
     *  Sum: '<S371>/Sum'
     *  UnitDelay: '<S206>/Unit Delay2'
     */
    if (LIBINFO_WL_00_DWork->UnitDelay2_DSTATE_lhye >=
        LIBINFO_WL_00_M->
        LIBINFO_WL_00_LIBINFO_Totalizer_00_calcompfix_mi_ROM_p->ST_Tot_MaxSeqNum)
    {
      rtb_Merge1_mrd3 = 0U;
    } else {
      rtb_Merge1_mrd3 = (uint8_t)(((uint32_t)
        LIBINFO_WL_00_DWork->UnitDelay2_DSTATE_lhye) + 1U);
    }

    /* End of Switch: '<S371>/Switch' */
    /* End of Outputs for SubSystem: '<S206>/Commit' */
  } else {
    /* Outputs for IfAction SubSystem: '<S206>/No Commit' incorporates:
     *  ActionPort: '<S370>/Action Port'
     */
    rtb_UnitDelay_hhl4 = LIBINFO_WL_00_DWork->UnitDelay_DSTATE_leoe;

    /* End of Outputs for SubSystem: '<S206>/No Commit' */

    /* Switch: '<S206>/Switch' incorporates:
     *  Inport: '<S370>/prevLastSegmentEndTime'
     *  Inport: '<S370>/prevLastSegmentID'
     *  UnitDelay: '<S206>/Unit Delay'
     *  UnitDelay: '<S206>/Unit Delay1'
     *  UnitDelay: '<S369>/Unit Delay'
     */
    if (LIBINFO_WL_00_DWork->UnitDelay_DSTATE_nv4u) {
      /* Outputs for IfAction SubSystem: '<S206>/No Commit' incorporates:
       *  ActionPort: '<S370>/Action Port'
       */
      rtb_MinMax = LIBINFO_WL_00_B->UnitDelay;

      /* End of Outputs for SubSystem: '<S206>/No Commit' */
    } else {
      /* Outputs for IfAction SubSystem: '<S206>/No Commit' incorporates:
       *  ActionPort: '<S370>/Action Port'
       */
      rtb_MinMax = LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_loyz;

      /* End of Outputs for SubSystem: '<S206>/No Commit' */
    }

    /* End of Switch: '<S206>/Switch' */

    /* Outputs for IfAction SubSystem: '<S206>/No Commit' incorporates:
     *  ActionPort: '<S370>/Action Port'
     */
    rtb_Merge1_mrd3 = LIBINFO_WL_00_DWork->UnitDelay2_DSTATE_lhye;

    /* End of Outputs for SubSystem: '<S206>/No Commit' */
  }

  /* End of If: '<S206>/If' */

  /* SignalConversion: '<S200>/Copy' */
  LIBINFO_WL_00_B->segment_last_completed_id = rtb_UnitDelay_hhl4;

  /* Outport: '<Root>/segment_last_completed_id' */
  *LIBINFO_WL_00_Y_segment_last_completed_id =
    LIBINFO_WL_00_B->segment_last_completed_id;

  /* SignalConversion: '<S184>/Copy' incorporates:
   *  Sum: '<S206>/Subtract'
   */
  LIBINFO_WL_00_B->segment_time_since_last_end = LIBINFO_WL_00_B->UnitDelay -
    rtb_MinMax;

  /* Outport: '<Root>/segment_time_since_last_end' */
  *LIBINFO_WL_00_Y_segment_time_since_last_end =
    LIBINFO_WL_00_B->segment_time_since_last_end;

  /* SignalConversion: '<S185>/Copy' */
  LIBINFO_WL_00_B->segment_sequence_number = rtb_Merge1_mrd3;

  /* Outport: '<Root>/segment_sequence_number' */
  *LIBINFO_WL_00_Y_segment_sequence_number =
    LIBINFO_WL_00_B->segment_sequence_number;

  /* Outport: '<Root>/keyswitch_override_flag' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion1'
   */
  *LIBINFO_WL_00_Y_keyswitch_override_flag = (uint8_t)
    LIBINFO_WL_00_B->keyswitchOverride;

  /* Logic: '<S218>/Logical Operator' incorporates:
   *  RelationalOperator: '<S218>/Relational Operator'
   *  RelationalOperator: '<S485>/Compare'
   */
  rtb_LogicalOperator_bepi = ((7 >= LIBINFO_WL_00_B->ToOneBased) &&
    (LIBINFO_WL_00_B->ToOneBased > 0));

  /* Outputs for Enabled SubSystem: '<S218>/Bounded Selection' */
  LIBINFO_WL_00_BoundedSelection(rtb_LogicalOperator_bepi,
    rtb_VectorConcatenate1, LIBINFO_WL_00_B->ToOneBased,
    LIBINFO_WL_00_Y_segment_active_segment_id);

  /* End of Outputs for SubSystem: '<S218>/Bounded Selection' */

  /* SignalConversion: '<S101>/Copy' */
  LIBINFO_WL_00_B->GroundSpeed = LIBINFO_WL_00_B->GroundSpeed_iutz;

  /* SignalConversion: '<S101>/Copy' */
  LIBINFO_WL_00_B->ExternalForceNormalized =
    LIBINFO_WL_00_B->ExternalForceNormalized_p2pg;

  /* SignalConversion: '<S101>/Copy' */
  LIBINFO_WL_00_B->ExternalForceNormalizedDel_cvju =
    LIBINFO_WL_00_B->ExternalForceNormalizedDelta;

  /* SignalConversion: '<S101>/Copy' */
  LIBINFO_WL_00_B->ExternalForceUnknown = LIBINFO_WL_00_B->ExternalForceunknown;

  /* SignalConversion: '<S101>/Copy' */
  LIBINFO_WL_00_B->DumpState_msq3 = LIBINFO_WL_00_B->DumpState;

  /* SignalConversion: '<S101>/Copy' */
  LIBINFO_WL_00_B->LiftValveCmd = LIBINFO_WL_00_B->LiftValveCmd_lf5w;

  /* SignalConversion: '<S101>/Copy' */
  LIBINFO_WL_00_B->TiltValveCmd = LIBINFO_WL_00_B->TiltValveCmd_bbs3;

  /* SignalConversion: '<S101>/Copy' */
  LIBINFO_WL_00_B->IsFullRack_jg4o = LIBINFO_WL_00_B->IsFullRack_ou1b;

  /* SignalConversion: '<S101>/Copy' */
  LIBINFO_WL_00_B->MachineAccel_b5i2 = LIBINFO_WL_00_B->MachineAccel;

  /* SignalConversion: '<S101>/Copy' */
  LIBINFO_WL_00_B->TransGear = LIBINFO_WL_00_B->DesiredGear;

  /* SignalConversion: '<S101>/Copy' */
  LIBINFO_WL_00_B->LiftAngle = LIBINFO_WL_00_B->LiftAngle_bgyb;

  /* SignalConversion: '<S101>/Copy' */
  LIBINFO_WL_00_B->BucketAngle = LIBINFO_WL_00_B->BucketAngle_bg5r;

  /* SignalConversion: '<S101>/Copy' */
  LIBINFO_WL_00_B->PayloadRatio_ge2j = rtb_Merge;

  /* SignalConversion: '<S101>/Copy' */
  LIBINFO_WL_00_B->PayloadRatioDerivative_hn5m =
    LIBINFO_WL_00_B->PayloadRatioDerivative;

  /* SignalConversion: '<S101>/Copy' */
  LIBINFO_WL_00_B->PayloadRatioUnknown = LIBINFO_WL_00_B->Merge1_mlst;

  /* If: '<S127>/If' incorporates:
   *  Constant: '<S128>/Constant'
   */
  rtPrevAction = LIBINFO_WL_00_DWork->If_ActiveSubsystem;
  if (LIBINFO_WL_00_B->Merge1_mlst) {
    LIBINFO_WL_00_DWork->If_ActiveSubsystem = 0;
  } else {
    LIBINFO_WL_00_DWork->If_ActiveSubsystem = 1;
  }

  switch (LIBINFO_WL_00_DWork->If_ActiveSubsystem) {
   case 0:
    if (LIBINFO_WL_00_DWork->If_ActiveSubsystem != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S127>/Unknown' incorporates:
       *  InitializeConditions for ActionPort: '<S129>/Action Port'
       */
      /* InitializeConditions for If: '<S127>/If' incorporates:
       *  InitializeConditions for UnitDelay: '<S129>/Unit Delay'
       */
      LIBINFO_WL_00_DWork->UnitDelay_DSTATE_hamv = 0;

      /* End of InitializeConditions for SubSystem: '<S127>/Unknown' */
    }

    /* Outputs for IfAction SubSystem: '<S127>/Unknown' incorporates:
     *  ActionPort: '<S129>/Action Port'
     */
    /* Sum: '<S129>/Add' incorporates:
     *  Constant: '<S129>/Constant'
     *  UnitDelay: '<S129>/Unit Delay'
     */
    tmp = 1L + ((int64_T)LIBINFO_WL_00_DWork->UnitDelay_DSTATE_hamv);
    if (tmp > 2147483647L) {
      tmp = 2147483647L;
    } else {
      if (tmp < -2147483648L) {
        tmp = -2147483648L;
      }
    }

    rtb_Add_ltmq = (int32_t)tmp;

    /* End of Sum: '<S129>/Add' */

    /* Update for UnitDelay: '<S129>/Unit Delay' */
    LIBINFO_WL_00_DWork->UnitDelay_DSTATE_hamv = rtb_Add_ltmq;

    /* End of Outputs for SubSystem: '<S127>/Unknown' */
    break;

   case 1:
    /* Outputs for IfAction SubSystem: '<S127>/Known' incorporates:
     *  ActionPort: '<S128>/Action Port'
     */
    rtb_Add_ltmq = 0;

    /* End of Outputs for SubSystem: '<S127>/Known' */
    break;
  }

  /* End of If: '<S127>/If' */

  /* Logic: '<S127>/Logical Operator2' */
  rtb_LogicalOperator = !LIBINFO_WL_00_B->Merge1_mlst;

  /* Switch: '<S127>/Switch1' */
  if (LIBINFO_WL_00_B->Merge1_mlst) {
    rtb_Merge = rtb_UnitDelay2_dmbr;
  }

  /* End of Switch: '<S127>/Switch1' */

  /* UnitDelay: '<S160>/IsFirstLoop' */
  rtb_LogicalOperator_inbd = LIBINFO_WL_00_DWork->IsFirstLoop_DSTATE;

  /* UnitDelay: '<S171>/IsFirstLoop' */
  rtb_DataTypeConversion2 = LIBINFO_WL_00_DWork->IsFirstLoop_DSTATE_nsmc;

  /* Sum: '<S303>/Sum' */
  rtb_Sum_hn32 = LIBINFO_WL_00_B->WeightedSampleTime_p1jr +
    LIBINFO_WL_00_B->UnitDelay;

  /* Update for UnitDelay: '<S310>/Unit Delay' incorporates:
   *  Constant: '<S310>/False'
   */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_irpf = FALSE;

  /* Update for UnitDelay: '<S304>/Unit Delay' */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_lqwq = rtb_UnitDelay1_kz4h;

  /* Update for UnitDelay: '<S261>/Unit Delay' incorporates:
   *  Constant: '<S261>/False'
   */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_btkl = FALSE;

  /* Update for UnitDelay: '<S105>/Unit Delay' incorporates:
   *  Constant: '<S105>/Constant'
   */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_jcgr = FALSE;

  /* Update for UnitDelay: '<S105>/Unit Delay2' */
  LIBINFO_WL_00_DWork->UnitDelay2_DSTATE = rtb_DataTypeConversion;

  /* Update for UnitDelay: '<S111>/Unit Delay1' */
  LIBINFO_WL_00_DWork->UnitDelay1_DSTATE = rtb_Sum1;

  /* Update for UnitDelay: '<S113>/Unit Delay' incorporates:
   *  Constant: '<S113>/FirstLoop'
   */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_mffg = 1U;

  /* Update for UnitDelay: '<S112>/Unit Delay1' */
  LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_eht0 = rtb_Sum1_kflo;

  /* Update for UnitDelay: '<S115>/Unit Delay' incorporates:
   *  Constant: '<S115>/FirstLoop'
   */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_ozyd = 1U;

  /* Update for UnitDelay: '<S127>/Unit Delay' incorporates:
   *  Logic: '<S127>/Logical Operator'
   */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_avwe = (rtb_DataTypeConversion5 ||
    rtb_LogicalOperator);

  /* Update for UnitDelay: '<S127>/Unit Delay2' */
  LIBINFO_WL_00_DWork->UnitDelay2_DSTATE_jo4u = rtb_Merge;

  /* Update for UnitDelay: '<S127>/Unit Delay1' */
  LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_phum = rtb_Add_ltmq;

  /* Update for UnitDelay: '<S125>/Unit Delay1' */
  LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_peb2 = rtb_Sum1_m10g;

  /* Update for UnitDelay: '<S130>/Unit Delay' incorporates:
   *  Constant: '<S130>/FirstLoop'
   */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_nciw = 1U;

  /* Update for UnitDelay: '<S110>/Unit Delay1' */
  LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_fr1p = rtb_DataTypeConversion6;

  /* Update for UnitDelay: '<S126>/Unit Delay1' */
  LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_mlq0 = rtb_Sum3;

  /* Update for UnitDelay: '<S132>/Unit Delay' incorporates:
   *  Constant: '<S132>/FirstLoop'
   */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_b0xn = 1U;

  /* Update for UnitDelay: '<S117>/Unit Delay1' */
  LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_nof1 = rtb_Sum1_klni;

  /* Update for UnitDelay: '<S118>/Unit Delay' incorporates:
   *  Constant: '<S118>/FirstLoop'
   */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_j315 = 1U;

  /* Update for UnitDelay: '<S4>/Unit Delay' */
  LIBINFO_WL_00_DWork->UnitDelay_1_DSTATE = LIBINFO_WL_00_B->ST_Dump_State_exsh;

  /* Update for UnitDelay: '<S93>/Unit Delay' */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_fwtf =
    LIBINFO_WL_00_B->ST_Dig_State_prjn;

  /* Update for UnitDelay: '<S94>/Unit Delay' */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_jnup = rtb_DataTypeConversion4;

  /* Update for UnitDelay: '<S4>/Unit Delay' */
  LIBINFO_WL_00_DWork->UnitDelay_3_DSTATE = LIBINFO_WL_00_B->ST_Dig_State_prjn;

  /* Update for UnitDelay: '<S4>/Unit Delay' */
  LIBINFO_WL_00_DWork->UnitDelay_5_DSTATE =
    LIBINFO_WL_00_B->ST_Dump_StateIsFull_neg0;

  /* Update for UnitDelay: '<S171>/IsFirstOrSecondLoop' */
  LIBINFO_WL_00_DWork->IsFirstOrSecondLoop_DSTATE = rtb_DataTypeConversion2;

  /* Update for UnitDelay: '<S171>/Unit Delay1' */
  LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_asxt = rtb_UnitDelay_pt3t;

  /* Update for UnitDelay: '<S171>/Unit Delay' */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_ogmk = LIBINFO_WL_00_B->GroundSpeed_iutz;

  /* Update for UnitDelay: '<S148>/Unit Delay1' */
  LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_juby = rtb_DataTypeConversion3_js1i;

  /* Update for UnitDelay: '<S148>/Unit Delay' */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE = rtb_Switch;

  /* Update for UnitDelay: '<S146>/Unit Delay' */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_bozj = LIBINFO_WL_00_B->DownForce;

  /* Update for UnitDelay: '<S160>/IsFirstOrSecondLoop' */
  LIBINFO_WL_00_DWork->IsFirstOrSecondLoop_DSTATE_m13y =
    rtb_LogicalOperator_inbd;

  /* Update for UnitDelay: '<S160>/Unit Delay1' */
  LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_fpb3 = rtb_UnitDelay_lqy0;

  /* Update for UnitDelay: '<S160>/Unit Delay' */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_dqoa = LIBINFO_WL_00_B->GroundSpeed_iutz;

  /* Update for UnitDelay: '<S254>/Unit Delay' */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_hhbx = LIBINFO_WL_00_B->ToOneBased;

  /* Update for UnitDelay: '<S251>/Unit Delay1' */
  LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_nqrv = rtb_UnitDelay1_kz4h;

  /* Update for UnitDelay: '<S257>/Unit Delay' incorporates:
   *  Constant: '<S257>/False'
   */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_grmj = FALSE;

  /* Update for UnitDelay: '<S251>/Unit Delay3' */
  LIBINFO_WL_00_DWork->UnitDelay3_DSTATE = LIBINFO_WL_00_B->Merge2;

  /* Update for UnitDelay: '<S303>/Unit Delay' */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_a1en = rtb_Sum_hn32;

  /* Update for UnitDelay: '<S202>/Unit Delay' */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_c01m = LIBINFO_WL_00_B->FuelHighRes;

  /* Update for UnitDelay: '<S206>/Unit Delay' */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_leoe = rtb_UnitDelay_hhl4;

  /* Update for UnitDelay: '<S369>/Unit Delay' incorporates:
   *  Constant: '<S369>/Constant'
   */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_nv4u = FALSE;

  /* Update for UnitDelay: '<S206>/Unit Delay1' */
  LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_loyz = rtb_MinMax;

  /* Update for UnitDelay: '<S206>/Unit Delay2' */
  LIBINFO_WL_00_DWork->UnitDelay2_DSTATE_lhye = rtb_Merge1_mrd3;

  /* Update for UnitDelay: '<S160>/IsFirstLoop' incorporates:
   *  Constant: '<S160>/Constant'
   */
  LIBINFO_WL_00_DWork->IsFirstLoop_DSTATE = FALSE;

  /* Update for UnitDelay: '<S171>/IsFirstLoop' incorporates:
   *  Constant: '<S171>/Constant'
   */
  LIBINFO_WL_00_DWork->IsFirstLoop_DSTATE_nsmc = FALSE;
}

/* Model initialize function */
void LIBINFO_WL_00_initialize(RT_MODEL_LIBINFO_WL_00 *const LIBINFO_WL_00_M,
  BlockIO_LIBINFO_WL_00 *LIBINFO_WL_00_B, D_Work_LIBINFO_WL_00
  *LIBINFO_WL_00_DWork, dt_libinfo_MachSpdKPH_Signed
  *LIBINFO_WL_00_U_ground_speed, dt_libinfo_single
  *LIBINFO_WL_00_U_payload_ratio, dt_libinfo_single
  *LIBINFO_WL_00_U_payload_ratio_raw, dt_libinfo_Ratio_hiRes
  *LIBINFO_WL_00_U_ext_force_normalized, dt_libinfo_ValveCmd
  *LIBINFO_WL_00_U_lift_valve_cmd, dt_libinfo_ValveCmd
  *LIBINFO_WL_00_U_tilt_valve_cmd, dt_libinfo_Angle
  *LIBINFO_WL_00_U_bucket_angle, dt_libinfo_Angle *LIBINFO_WL_00_U_lift_angle,
  dt_libinfo_TransmissionGear_int16 *LIBINFO_WL_00_U_desired_gear,
  dt_libinfo_EngSpd_Signed *LIBINFO_WL_00_U_engine_speed, dt_libinfo_ValveCmd
  *LIBINFO_WL_00_U_tilt_lever_cmd, dt_libinfo_modulation_pct
  *LIBINFO_WL_00_U_tilt_cyl_position, dt_libinfo_Unsigned16
  *LIBINFO_WL_00_U_machine_idle, dt_libinfo_Unsigned16
  *LIBINFO_WL_00_U_key_switch, dt_libinfo_Unsigned32 *LIBINFO_WL_00_U_real_time,
  dt_libinfo_fuel_high_res *LIBINFO_WL_00_U_fuel_high_res,
  dt_libinfo_fuel_low_res *LIBINFO_WL_00_U_fuel, dt_libinfo_FuelRate
  *LIBINFO_WL_00_U_fuel_rate, dt_libinfo_ARDfuel_Rate
  *LIBINFO_WL_00_U_fuel_rate_ard, dt_libinfo_Flag
  *LIBINFO_WL_00_U_realTime_status, dt_libinfo_gps_latitude
  *LIBINFO_WL_00_U_gps_latitude, dt_libinfo_Ratio_Unsigned32
  *LIBINFO_WL_00_U_gps_longitude, dt_libinfo_Flag
  *LIBINFO_WL_00_U_gps_lat_long_status, dt_libinfo_single
  *LIBINFO_WL_00_U_payload_weight, dt_libinfo_Flag_u16
  *LIBINFO_WL_00_U_payloadCalcMethod, dt_libinfo_Unsigned32
  *LIBINFO_WL_00_U_service_hour_meter, dt_libinfo_tz_offset_mins
  *LIBINFO_WL_00_U_timezone_offset, dt_libinfo_Flag_u16
  *LIBINFO_WL_00_U_payload_weight_status, dt_libinfo_Unsigned16
  *LIBINFO_WL_00_U_payload_ratio_status, dt_libinfo_Unsigned16
  *LIBINFO_WL_00_U_payload_ratio_raw_status, dt_libinfo_Unsigned16
  *LIBINFO_WL_00_U_Impl_operation_status, dt_libinfo_Flag
  *LIBINFO_WL_00_Y_commit_segment_record, uint8_t
  *LIBINFO_WL_00_Y_segment_record_id, dt_libinfo_Unsigned32
  *LIBINFO_WL_00_Y_segment_rec_start_simTime, dt_libinfo_Time20msLong
  *LIBINFO_WL_00_Y_segment_rec_duration, dt_libinfo_single
  *LIBINFO_WL_00_Y_segment_rec_distance, dt_libinfo_Unsigned32
  *LIBINFO_WL_00_Y_segment_rec_start_real_time, dt_libinfo_single
  *LIBINFO_WL_00_Y_segment_rec_fuel_used, dt_libinfo_gps_latitude
  *LIBINFO_WL_00_Y_segment_rec_latitude, dt_libinfo_Ratio_Unsigned32
  *LIBINFO_WL_00_Y_segment_rec_longitude, dt_libinfo_Unsigned32
  *LIBINFO_WL_00_Y_segment_rec_idle_time, dt_libinfo_Unsigned32
  *LIBINFO_WL_00_Y_segment_rec_hour_meter, dt_libinfo_single
  *LIBINFO_WL_00_Y_segment_rec_payload, dt_libinfo_Flag_u16
  *LIBINFO_WL_00_Y_segment_rec_payload_calc_method, dt_libinfo_Flag
  *LIBINFO_WL_00_Y_commit_rec_gps, uint8_t *LIBINFO_WL_00_Y_segment_dig_state,
  uint8_t *LIBINFO_WL_00_Y_segment_last_completed_id, dt_libinfo_Time20msLong
  *LIBINFO_WL_00_Y_segment_time_since_last_end, uint8_t
  *LIBINFO_WL_00_Y_segment_sequence_number, uint8_t
  *LIBINFO_WL_00_Y_keyswitch_override_flag, uint8_t
  *LIBINFO_WL_00_Y_segment_active_segment_id)
{
  /* Registration code */

  /* initialize non-finites */
  R2012b_rt_InitInfAndNaN(sizeof(real_T));

  /* Removed initialize of real-time model
 *   because only members were CATutils
 *   pointers that needed to be preserved */
SL_UNUSED_PARAM(LIBINFO_WL_00_M);


  /* block I/O */
  (void) memset(((void *) LIBINFO_WL_00_B), 0,
                sizeof(BlockIO_LIBINFO_WL_00));

  {
    LIBINFO_WL_00_B->ST_Dig_ID = ((uint8_t)0U);
    LIBINFO_WL_00_B->PayloadCalcMethodUnknown = ((uint8_t)0U);
    LIBINFO_WL_00_B->ST_Dump_Commit = FALSE;
    LIBINFO_WL_00_B->ST_Dig_Commit = FALSE;
  }

  /* states (dwork) */
  (void) memset((void *)LIBINFO_WL_00_DWork, 0,
                sizeof(D_Work_LIBINFO_WL_00));

  /* external inputs */
  (*LIBINFO_WL_00_U_ground_speed) = 0;
  (*LIBINFO_WL_00_U_payload_ratio) = 0.0F;
  (*LIBINFO_WL_00_U_payload_ratio_raw) = 0.0F;
  (*LIBINFO_WL_00_U_ext_force_normalized) = 0;
  (*LIBINFO_WL_00_U_lift_valve_cmd) = 0;
  (*LIBINFO_WL_00_U_tilt_valve_cmd) = 0;
  (*LIBINFO_WL_00_U_bucket_angle) = 0;
  (*LIBINFO_WL_00_U_lift_angle) = 0;
  (*LIBINFO_WL_00_U_desired_gear) = 0;
  (*LIBINFO_WL_00_U_engine_speed) = 0;
  (*LIBINFO_WL_00_U_tilt_lever_cmd) = 0;
  (*LIBINFO_WL_00_U_tilt_cyl_position) = 0U;
  (*LIBINFO_WL_00_U_machine_idle) = 0U;
  (*LIBINFO_WL_00_U_key_switch) = 0U;
  (*LIBINFO_WL_00_U_real_time) = 0U;
  (*LIBINFO_WL_00_U_fuel_high_res) = 0U;
  (*LIBINFO_WL_00_U_fuel) = 0U;
  (*LIBINFO_WL_00_U_fuel_rate) = 0U;
  (*LIBINFO_WL_00_U_fuel_rate_ard) = 0U;
  (*LIBINFO_WL_00_U_realTime_status) = 0U;
  (*LIBINFO_WL_00_U_gps_latitude) = 0U;
  (*LIBINFO_WL_00_U_gps_longitude) = 0U;
  (*LIBINFO_WL_00_U_gps_lat_long_status) = 0U;
  (*LIBINFO_WL_00_U_payload_weight) = 0.0F;
  (*LIBINFO_WL_00_U_payloadCalcMethod) = 0U;
  (*LIBINFO_WL_00_U_service_hour_meter) = 0U;
  (*LIBINFO_WL_00_U_timezone_offset) = 0;
  (*LIBINFO_WL_00_U_payload_weight_status) = 0U;
  (*LIBINFO_WL_00_U_payload_ratio_status) = 0U;
  (*LIBINFO_WL_00_U_payload_ratio_raw_status) = 0U;
  (*LIBINFO_WL_00_U_Impl_operation_status) = 0U;

  /* external outputs */
  (*LIBINFO_WL_00_Y_commit_segment_record) = 0U;
  (*LIBINFO_WL_00_Y_segment_record_id) = 0U;
  (*LIBINFO_WL_00_Y_segment_rec_start_simTime) = 0U;
  (*LIBINFO_WL_00_Y_segment_rec_duration) = 0U;
  (*LIBINFO_WL_00_Y_segment_rec_distance) = 0.0F;
  (*LIBINFO_WL_00_Y_segment_rec_start_real_time) = 0U;
  (*LIBINFO_WL_00_Y_segment_rec_fuel_used) = 0.0F;
  (*LIBINFO_WL_00_Y_segment_rec_latitude) = 0U;
  (*LIBINFO_WL_00_Y_segment_rec_longitude) = 0U;
  (*LIBINFO_WL_00_Y_segment_rec_idle_time) = 0U;
  (*LIBINFO_WL_00_Y_segment_rec_hour_meter) = 0U;
  (*LIBINFO_WL_00_Y_segment_rec_payload) = 0.0F;
  (*LIBINFO_WL_00_Y_segment_rec_payload_calc_method) = 0U;
  (*LIBINFO_WL_00_Y_commit_rec_gps) = 0U;
  (*LIBINFO_WL_00_Y_segment_dig_state) = 0U;
  (*LIBINFO_WL_00_Y_segment_last_completed_id) = 0U;
  (*LIBINFO_WL_00_Y_segment_time_since_last_end) = 0U;
  (*LIBINFO_WL_00_Y_segment_sequence_number) = 0U;
  (*LIBINFO_WL_00_Y_keyswitch_override_flag) = 0U;
  (*LIBINFO_WL_00_Y_segment_active_segment_id) = 0U;

  /* ConstCode for SignalConversion: '<S41>/Copy' incorporates:
   *  Constant: '<S3>/Constant'
   */
  LIBINFO_WL_00_B->PayloadCalcMethodUnknown = 0U;

  /* End of Start for SubSystem: '<S1>/LIBINFO_WL_00_InPrc' */

  /* Start for IfAction SubSystem: '<S109>/notOk' */
  /* VirtualOutportStart for Outport: '<S121>/payloadRatioUnknown' */
  LIBINFO_WL_00_B->Merge1_mlst = TRUE;

  /* End of Start for SubSystem: '<S109>/notOk' */

  /* Start for If: '<S127>/If' */
  LIBINFO_WL_00_DWork->If_ActiveSubsystem = -1;

  /* InitializeConditions for IfAction SubSystem: '<S127>/Unknown' */
  /* InitializeConditions for UnitDelay: '<S129>/Unit Delay' */
  LIBINFO_WL_00_DWork->UnitDelay_DSTATE_hamv = 0;

  /* End of InitializeConditions for SubSystem: '<S127>/Unknown' */
  /* ConstCode for Constant: '<S94>/Constant4' */
  LIBINFO_WL_00_B->ST_Dump_Commit = FALSE;

  /* ConstCode for Constant: '<S93>/Constant18' */
  LIBINFO_WL_00_B->ST_Dig_Commit = FALSE;

  /* ConstCode for Constant: '<S93>/Constant17' */
  LIBINFO_WL_00_B->ST_Dig_ID = 0U;

  {
    int32_t i;

    /* InitializeConditions for UnitDelay: '<S310>/Unit Delay' */
    LIBINFO_WL_00_DWork->UnitDelay_DSTATE_irpf = TRUE;

    /* InitializeConditions for UnitDelay: '<S261>/Unit Delay' */
    LIBINFO_WL_00_DWork->UnitDelay_DSTATE_btkl = TRUE;

    /* InitializeConditions for Chart: '<S95>/RunState' */
    LIBINFO_WL_00_DWork->is_active_EngineState = 0U;
    LIBINFO_WL_00_DWork->is_EngineState = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_RunState = 0U;
    LIBINFO_WL_00_DWork->is_RunState = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_KeyOff = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_EngineOff = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_KeyOn = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_c1_ST_Lib_KeyStatus = 0U;
    LIBINFO_WL_00_DWork->EngineRunningRaw = FALSE;
    LIBINFO_WL_00_DWork->EngineRunningDebounced = FALSE;
    LIBINFO_WL_00_DWork->EngineRunningCounter = 0U;
    LIBINFO_WL_00_DWork->DESCounter = 0U;
    LIBINFO_WL_00_B->ST_KeyStatus_State = 0U;
    LIBINFO_WL_00_B->ST_KeyStatus_ID = 0U;
    LIBINFO_WL_00_B->ST_KeyStatus_Commit = FALSE;
    LIBINFO_WL_00_B->keyswitchOverride = FALSE;

    /* InitializeConditions for Chart: '<S99>/UnknownState' */
    LIBINFO_WL_00_DWork->is_active_Main = 0U;
    LIBINFO_WL_00_DWork->is_Main = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_c1_ST_Lib_Unknown_MWL = 0U;
    LIBINFO_WL_00_DWork->DebounceCounter = 0U;
    LIBINFO_WL_00_B->ST_Unknown_State = 0U;
    LIBINFO_WL_00_B->ST_Unknown_ID = 0U;
    LIBINFO_WL_00_B->ST_Unknown_Commit = FALSE;

    /* InitializeConditions for UnitDelay: '<S105>/Unit Delay' */
    LIBINFO_WL_00_DWork->UnitDelay_DSTATE_jcgr = TRUE;

    /* InitializeConditions for UnitDelay: '<S110>/Unit Delay1' */
    LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_fr1p = TRUE;

    /* InitializeConditions for Chart: '<S93>/Classifier' */
    LIBINFO_WL_00_DWork->is_active_Main_f0rl = 0U;
    LIBINFO_WL_00_DWork->is_Main_ibas = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_Active = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_NotWorking_gji1 = 0U;
    LIBINFO_WL_00_DWork->is_NotWorking_pqry = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_c6_ST_Lib_Dig_MWL = 0U;
    LIBINFO_WL_00_DWork->notWorking_mksr = FALSE;
    LIBINFO_WL_00_DWork->notWorkingCounter_cq2l = 0U;
    LIBINFO_WL_00_B->complete = FALSE;

    /* InitializeConditions for Chart: '<S93>/MaterialEngagementDetection' */
    LIBINFO_WL_00_DWork->is_active_Deceleration = 0U;
    LIBINFO_WL_00_DWork->is_Deceleration = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_Decel = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_NotDecel = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_DirectionShiftInhibit = 0U;
    LIBINFO_WL_00_DWork->is_DirectionShiftInhibit =
      LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_Main_fpt2 = 0U;
    LIBINFO_WL_00_DWork->is_Main_nwt5 = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_Tentative = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_c7_ST_Lib_Dig_MWL = 0U;
    LIBINFO_WL_00_DWork->Decelerating = FALSE;
    LIBINFO_WL_00_DWork->GearTriggerInhibit = FALSE;
    LIBINFO_WL_00_DWork->DecelCounter = 0U;
    LIBINFO_WL_00_DWork->DirShiftCounter = 0U;
    LIBINFO_WL_00_DWork->TentativeCounter = 0U;
    LIBINFO_WL_00_B->ST_Dig_State_prjn = 0U;

    /* InitializeConditions for Chart: '<S96>/Loaded' */
    LIBINFO_WL_00_DWork->is_active_LoadStatus = 0U;
    LIBINFO_WL_00_DWork->is_active_Main_b3l0 = 0U;
    LIBINFO_WL_00_DWork->is_Main_ezny = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_c5_ST_Lib_Loaded_MWL = 0U;
    LIBINFO_WL_00_DWork->loadedCounter = 0U;
    LIBINFO_WL_00_DWork->unloadedCounter = 0U;
    LIBINFO_WL_00_B->Loaded_dsd1 = FALSE;

    /* InitializeConditions for Chart: '<S139>/DetectMovement' */
    LIBINFO_WL_00_DWork->is_active_Capture = 0U;
    LIBINFO_WL_00_DWork->is_active_Main_hnap = 0U;
    LIBINFO_WL_00_DWork->is_Main_erzc = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_Known = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_c10_ST_Lib_Dump_MWL = 0U;
    LIBINFO_WL_00_B->dumpMovementConfirmed = FALSE;
    LIBINFO_WL_00_B->rackMovementConfirmed = FALSE;

    /* InitializeConditions for Chart: '<S94>/DumpState' */
    LIBINFO_WL_00_DWork->is_active_Main_i1bh = 0U;
    LIBINFO_WL_00_DWork->is_Main_pm2j = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_ConfirmedDump = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_NotWorking = 0U;
    LIBINFO_WL_00_DWork->is_NotWorking = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_TiltCommandZero = 0U;
    LIBINFO_WL_00_DWork->is_TiltCommandZero = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_c8_ST_Lib_Dump_MWL = 0U;
    LIBINFO_WL_00_DWork->valveCmdZero = FALSE;
    LIBINFO_WL_00_DWork->notWorking = FALSE;
    LIBINFO_WL_00_DWork->valveCmdZeroCounter = 0U;
    LIBINFO_WL_00_DWork->notWorkingCounter = 0U;
    LIBINFO_WL_00_B->ST_Dump_State_exsh = 0U;

    /* InitializeConditions for UnitDelay: '<S171>/IsFirstOrSecondLoop' */
    LIBINFO_WL_00_DWork->IsFirstOrSecondLoop_DSTATE = TRUE;

    /* InitializeConditions for UnitDelay: '<S148>/Unit Delay1' */
    LIBINFO_WL_00_DWork->UnitDelay1_DSTATE_juby = TRUE;

    /* InitializeConditions for Chart: '<S98>/LoadedState' */
    LIBINFO_WL_00_DWork->is_active_Counter = 0U;
    LIBINFO_WL_00_DWork->is_active_Main_hmss = 0U;
    LIBINFO_WL_00_DWork->is_Main_bd3y = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_c2_ST_Lib_Travel_MWL = 0U;
    LIBINFO_WL_00_DWork->segmentTimeCounter = 0U;
    LIBINFO_WL_00_B->ST_Travel_Commit = FALSE;
    LIBINFO_WL_00_B->ST_Travel_ID = 0U;

    /* InitializeConditions for Chart: '<S98>/TravellingState' */
    LIBINFO_WL_00_DWork->is_active_Main_i2cf = 0U;
    LIBINFO_WL_00_DWork->is_Main_ko0u = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_NotTravelling = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_TentativelyNotTravelling =
      LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_TentativelyTravelling =
      LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_Travelling = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_TentativeTimer = 0U;
    LIBINFO_WL_00_DWork->is_active_c1_ST_Lib_Travel_MWL = 0U;
    LIBINFO_WL_00_DWork->notTravellingCounter = 0U;
    LIBINFO_WL_00_DWork->tentativeCounter = 0U;
    LIBINFO_WL_00_B->ST_Travel_State = 0U;

    /* InitializeConditions for UnitDelay: '<S160>/IsFirstOrSecondLoop' */
    LIBINFO_WL_00_DWork->IsFirstOrSecondLoop_DSTATE_m13y = TRUE;

    /* InitializeConditions for Chart: '<S97>/LoadState' */
    LIBINFO_WL_00_DWork->is_active_Counter_c1rm = 0U;
    LIBINFO_WL_00_DWork->is_active_Main_avkc = 0U;
    LIBINFO_WL_00_DWork->is_Main_ij3t = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_c2_ST_Lib_MachineIdle = 0U;
    LIBINFO_WL_00_DWork->segmentTimeCounter_mxc2 = 0U;
    LIBINFO_WL_00_B->commit = FALSE;
    LIBINFO_WL_00_B->ST_Stopped_ID = 0U;

    /* InitializeConditions for Chart: '<S97>/IdleState' */
    LIBINFO_WL_00_DWork->is_active_Main_fhmh = 0U;
    LIBINFO_WL_00_DWork->is_Main_nw5d = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_c1_ST_Lib_MachineIdle = 0U;
    LIBINFO_WL_00_DWork->ActiveDebounceCounter = 0U;
    LIBINFO_WL_00_DWork->InactiveDebounceCounter = 0U;
    LIBINFO_WL_00_B->ST_Stopped_State = 0U;
    LIBINFO_WL_00_B->commitOut = FALSE;

    /* InitializeConditions for Chart: '<S250>/Chart' */
    LIBINFO_WL_00_B->activeSegmentIndex = 0;
    for (i = 0; i < 7; i++) {
      LIBINFO_WL_00_B->segmentTentativeLogicalVector[i] = FALSE;
    }

    /* End of InitializeConditions for Chart: '<S250>/Chart' */

    /* InitializeConditions for Chart: '<S94>/DumpType' */
    LIBINFO_WL_00_DWork->is_Dumping = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_DWork->is_active_c9_ST_Lib_Dump_MWL = 0U;
    LIBINFO_WL_00_DWork->is_c9_ST_Lib_Dump_MWL = LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_B->ST_Dump_ID = 0U;
    LIBINFO_WL_00_B->ST_Dump_StateIsFull_neg0 = FALSE;

    /* InitializeConditions for UnitDelay: '<S257>/Unit Delay' */
    LIBINFO_WL_00_DWork->UnitDelay_DSTATE_grmj = TRUE;

    /* InitializeConditions for Chart: '<S309>/Chart' */
    LIBINFO_WL_00_DWork->is_active_c1_TotalizerUnionable = 0U;
    LIBINFO_WL_00_DWork->is_c1_TotalizerUnionableStatMgr =
      LIBINFO_WL_0_IN_NO_ACTIVE_CHILD;
    LIBINFO_WL_00_B->indexToAppend = 0;
    LIBINFO_WL_00_B->bufferDepth = 0;
    LIBINFO_WL_00_B->mergeFromIndexOneBased = 0;

    /* InitializeConditions for UnitDelay: '<S206>/Unit Delay' */
    LIBINFO_WL_00_DWork->UnitDelay_DSTATE_leoe = 27U;

    /* InitializeConditions for UnitDelay: '<S369>/Unit Delay' */
    LIBINFO_WL_00_DWork->UnitDelay_DSTATE_nv4u = TRUE;

    /* InitializeConditions for UnitDelay: '<S160>/IsFirstLoop' */
    LIBINFO_WL_00_DWork->IsFirstLoop_DSTATE = TRUE;

    /* InitializeConditions for UnitDelay: '<S171>/IsFirstLoop' */
    LIBINFO_WL_00_DWork->IsFirstLoop_DSTATE_nsmc = TRUE;
  }
}
