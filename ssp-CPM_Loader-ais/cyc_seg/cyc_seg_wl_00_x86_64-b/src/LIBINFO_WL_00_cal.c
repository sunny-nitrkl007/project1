/*******************************************************************************
** COPYRIGHT (C) 2018 CATERPILLAR INC. ALL RIGHTS RESERVED.
**------------------------------------------------------------------------------

**  FILE NAME:  LIBINFO_WL_00_cal.c
**  DESCRIPTION:  System calibration.
**
**    !!!!!  AUTO-GENERATED, DO NOT EDIT  !!!!!
**
**  Code Generator:  com.cat.e.tool.sa.code.SACodeGen
**  Code Generator Version:  0.2.0
**  Package:  CAT.E.Information_Manage.pkg_arch.wl_00
**  Name:  libinfo_wl_00.ysa
**  Path:  lib_info_products\cyc_seg_wl\wl_00\pkg_arch\ysa\libinfo_wl_00.ysa
**  Artifact GUID:  0b36c35d-ddb6-494c-b8b5-d9e50c8265e8
**  Description:  
**  Version:  0.0.0
*******************************************************************************/


/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include "LIBINFO_WL_00_cal.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Definitions --
*******************************************************************************/



  /*
   * Calibration for LIBINFO_WL_00_LIBINFO_Totalizer_00_calcompfix_mi_ROM
   */

static LIBINFO_WL_00_LIBINFO_Totalizer_00_calcompfix_mi_ROM_t LIBINFO_WL_00_LIBINFO_Totalizer_00_calcompfix_mi_ROM[] =
{

  /**************************************************
   *  LIBINFO_Totalizer_00_calcompfix = wl_00_totalizer_fix
   **************************************************/
  {
    473,    /* ST_FuelUsed_HighResIntgrlResol    0.4731765 */
    4294967295,    /* ST_TotSlave_Maxvalue    8.58993459E7 */
    2,    /* ST_Tot_ActiveStateValue    2 */
    255,    /* ST_Tot_MaxSeqNum    255.0 */
    1    /* ST_Tot_TentativeStateValue    1 */
  }

};



  /*
   * Calibration for LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM
   */

static LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_t LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM[] =
{

  /**************************************************
   *  LIBINFO_cycleSeg_calcompfix = wl_00_segments_fix
   **************************************************/
  {
    -0.1,    /* ST_LoadStat_DwnFrcLdRatioOfset    -0.1 */
    -0.5,    /* ST_LoadStat_DwnFrceRstThreshld    -0.5 */
    -0.6,    /* ST_LoadStat_DwnFrceTrgrThrshld    -0.6 */
    0.5,    /* ST_LoadStatus_LoadedRatio    0.5 */
    0.15,    /* ST_LoadStatus_UnloadedRatio    0.15 */
    100,    /* ST_KeyStat_EngRunStateDebounce    2.0 */
    250,    /* ST_KeyStatus_MinDESTime    5.0 */
    100,    /* ST_LoadStat_LoadStatusDebounce    2.0 */
    250,    /* ST_Stopped_ActiveTime    5.0 */
    250,    /* ST_Stopped_CommitTime    5.0 */
    256,    /* ST_Stopped_GroundSpeedThreshold    1.0 */
    25,    /* ST_Stopped_InactiveTime    0.5 */
    256,    /* ST_Travel_GroundSpeedThreshold    1.0 */
    250,    /* ST_Travel_MaxTentativeTime    5.0 */
    100,    /* ST_Travel_MinSegmentTime    2.0 */
    250,    /* ST_Travel_NotTravelingDebounce    5.0 */
    250    /* ST_Unknown_CommitTime    5.0 */
  }

};



  /*
   * Calibration for LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM
   */

static LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_t LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM[] =
{

  /**************************************************
   *  LIBINFO_cycleSeg_calcompvar = wl_00_segments_var_00
   **************************************************/
  {
    1.0,    /* ST_Dig_DecelerationTrigger    1.0 */
    0.3,    /* ST_Dig_PayloadRatioHighThrshld    0.3 */
    0.15,    /* ST_Dig_PyldRtioDrvtHighThrshld    0.15 */
    0.25,    /* ST_Dig_PyldRtioDrvtOvridTrshld    0.25 */
    {    /* ST_Dump_LoadRatioAxis */
      0.25,0.75
      /* 0.25,0.75 */
    },
    -2240,    /* ST_BucketPos_FullDumpBucketAng    -35.0 */
    2560,    /* ST_BucketPos_FullRackBucketAng    40.0 */
    13881,    /* ST_Dig_AccelerationFiltrFactor    0.423618822870924 */
    1280,    /* ST_Dig_BucketAngleMaxStart    20.0 */
    5,    /* ST_Dig_DecelerationResetTime    0.1 */
    5,    /* ST_Dig_DecelerationTriggerTime    0.1 */
    100,    /* ST_Dig_DirShiftInhibitTime    2.0 */
    428,    /* ST_Dig_ExtFrceNrmlzdHghThrshld    0.214 */
    285,    /* ST_Dig_ExtFrceNrmlzdLowThrshld    0.1426 */
    1212,    /* ST_Dig_ExtrnlFrceSlwFiltrFactr    0.036993047642836 */
    2560,    /* ST_Dig_GroundSpeedMax    10.0 */
    -768,    /* ST_Dig_GroundSpeedMin    -3.0 */
    -256,    /* ST_Dig_GroundSpeedTriggerMin    -1.0 */
    100,    /* ST_Dig_ImplementsIdleTime    2.0 */
    0,    /* ST_Dig_LiftAngleMaxStart    0.0 */
    13881,    /* ST_Dig_PyldRtioDrvtFiltrFactor    0.423618822870924 */
    6,    /* ST_Dig_TentativeConfirmatnTime    0.12 */
    500,    /* ST_Dig_TentativeMaxTime    10.0 */
    2560,    /* ST_Dump_CylMovementDelta    10.0 */
    {    /* ST_Dump_DumpAngleAxis */
      -1280,2240
      /* -20.0,35.0 */
    },
    768,    /* ST_Dump_GroundSpeedThreshold    3.0 */
    100,    /* ST_Dump_ImplementsIdleTime    2.0 */
    128,    /* ST_Dump_LeverDeadband    8.0 */
    13    /* ST_Dump_ValveCmdZeroTime    0.25 */
  },

  /**************************************************
   *  LIBINFO_cycleSeg_calcompvar = wl_00_segments_var_01
   **************************************************/
  {
    1.0,    /* ST_Dig_DecelerationTrigger    1.0 */
    0.3,    /* ST_Dig_PayloadRatioHighThrshld    0.3 */
    0.15,    /* ST_Dig_PyldRtioDrvtHighThrshld    0.15 */
    0.25,    /* ST_Dig_PyldRtioDrvtOvridTrshld    0.25 */
    {    /* ST_Dump_LoadRatioAxis */
      0.25,0.75
      /* 0.25,0.75 */
    },
    -2240,    /* ST_BucketPos_FullDumpBucketAng    -35.0 */
    2560,    /* ST_BucketPos_FullRackBucketAng    40.0 */
    13881,    /* ST_Dig_AccelerationFiltrFactor    0.423618822870924 */
    1280,    /* ST_Dig_BucketAngleMaxStart    20.0 */
    5,    /* ST_Dig_DecelerationResetTime    0.1 */
    5,    /* ST_Dig_DecelerationTriggerTime    0.1 */
    100,    /* ST_Dig_DirShiftInhibitTime    2.0 */
    428,    /* ST_Dig_ExtFrceNrmlzdHghThrshld    0.214 */
    285,    /* ST_Dig_ExtFrceNrmlzdLowThrshld    0.1426 */
    1212,    /* ST_Dig_ExtrnlFrceSlwFiltrFactr    0.036993047642836 */
    2560,    /* ST_Dig_GroundSpeedMax    10.0 */
    -768,    /* ST_Dig_GroundSpeedMin    -3.0 */
    -256,    /* ST_Dig_GroundSpeedTriggerMin    -1.0 */
    100,    /* ST_Dig_ImplementsIdleTime    2.0 */
    0,    /* ST_Dig_LiftAngleMaxStart    0.0 */
    13881,    /* ST_Dig_PyldRtioDrvtFiltrFactor    0.423618822870924 */
    6,    /* ST_Dig_TentativeConfirmatnTime    0.12 */
    500,    /* ST_Dig_TentativeMaxTime    10.0 */
    2560,    /* ST_Dump_CylMovementDelta    10.0 */
    {    /* ST_Dump_DumpAngleAxis */
      -1280,2240
      /* -20.0,35.0 */
    },
    768,    /* ST_Dump_GroundSpeedThreshold    3.0 */
    100,    /* ST_Dump_ImplementsIdleTime    2.0 */
    128,    /* ST_Dump_LeverDeadband    8.0 */
    13    /* ST_Dump_ValveCmdZeroTime    0.25 */
  },

  /**************************************************
   *  LIBINFO_cycleSeg_calcompvar = wl_00_segments_var_02
   **************************************************/
  {
    1.0,    /* ST_Dig_DecelerationTrigger    1.0 */
    0.3,    /* ST_Dig_PayloadRatioHighThrshld    0.3 */
    0.15,    /* ST_Dig_PyldRtioDrvtHighThrshld    0.15 */
    0.25,    /* ST_Dig_PyldRtioDrvtOvridTrshld    0.25 */
    {    /* ST_Dump_LoadRatioAxis */
      0.25,0.75
      /* 0.25,0.75 */
    },
    -2240,    /* ST_BucketPos_FullDumpBucketAng    -35.0 */
    2560,    /* ST_BucketPos_FullRackBucketAng    40.0 */
    13881,    /* ST_Dig_AccelerationFiltrFactor    0.423618822870924 */
    1280,    /* ST_Dig_BucketAngleMaxStart    20.0 */
    5,    /* ST_Dig_DecelerationResetTime    0.1 */
    5,    /* ST_Dig_DecelerationTriggerTime    0.1 */
    100,    /* ST_Dig_DirShiftInhibitTime    2.0 */
    428,    /* ST_Dig_ExtFrceNrmlzdHghThrshld    0.214 */
    285,    /* ST_Dig_ExtFrceNrmlzdLowThrshld    0.1426 */
    1212,    /* ST_Dig_ExtrnlFrceSlwFiltrFactr    0.036993047642836 */
    2560,    /* ST_Dig_GroundSpeedMax    10.0 */
    -768,    /* ST_Dig_GroundSpeedMin    -3.0 */
    -256,    /* ST_Dig_GroundSpeedTriggerMin    -1.0 */
    100,    /* ST_Dig_ImplementsIdleTime    2.0 */
    0,    /* ST_Dig_LiftAngleMaxStart    0.0 */
    13881,    /* ST_Dig_PyldRtioDrvtFiltrFactor    0.423618822870924 */
    6,    /* ST_Dig_TentativeConfirmatnTime    0.12 */
    500,    /* ST_Dig_TentativeMaxTime    10.0 */
    2560,    /* ST_Dump_CylMovementDelta    10.0 */
    {    /* ST_Dump_DumpAngleAxis */
      -1280,2240
      /* -20.0,35.0 */
    },
    768,    /* ST_Dump_GroundSpeedThreshold    3.0 */
    100,    /* ST_Dump_ImplementsIdleTime    2.0 */
    128,    /* ST_Dump_LeverDeadband    8.0 */
    13    /* ST_Dump_ValveCmdZeroTime    0.25 */
  },

  /**************************************************
   *  LIBINFO_cycleSeg_calcompvar = wl_00_segments_var_03
   **************************************************/
  {
    1.0,    /* ST_Dig_DecelerationTrigger    1.0 */
    0.3,    /* ST_Dig_PayloadRatioHighThrshld    0.3 */
    0.15,    /* ST_Dig_PyldRtioDrvtHighThrshld    0.15 */
    0.25,    /* ST_Dig_PyldRtioDrvtOvridTrshld    0.25 */
    {    /* ST_Dump_LoadRatioAxis */
      0.25,0.75
      /* 0.25,0.75 */
    },
    -2240,    /* ST_BucketPos_FullDumpBucketAng    -35.0 */
    2560,    /* ST_BucketPos_FullRackBucketAng    40.0 */
    13881,    /* ST_Dig_AccelerationFiltrFactor    0.423618822870924 */
    1280,    /* ST_Dig_BucketAngleMaxStart    20.0 */
    5,    /* ST_Dig_DecelerationResetTime    0.1 */
    5,    /* ST_Dig_DecelerationTriggerTime    0.1 */
    100,    /* ST_Dig_DirShiftInhibitTime    2.0 */
    428,    /* ST_Dig_ExtFrceNrmlzdHghThrshld    0.214 */
    285,    /* ST_Dig_ExtFrceNrmlzdLowThrshld    0.1426 */
    1212,    /* ST_Dig_ExtrnlFrceSlwFiltrFactr    0.036993047642836 */
    2560,    /* ST_Dig_GroundSpeedMax    10.0 */
    -768,    /* ST_Dig_GroundSpeedMin    -3.0 */
    -256,    /* ST_Dig_GroundSpeedTriggerMin    -1.0 */
    100,    /* ST_Dig_ImplementsIdleTime    2.0 */
    0,    /* ST_Dig_LiftAngleMaxStart    0.0 */
    13881,    /* ST_Dig_PyldRtioDrvtFiltrFactor    0.423618822870924 */
    6,    /* ST_Dig_TentativeConfirmatnTime    0.12 */
    500,    /* ST_Dig_TentativeMaxTime    10.0 */
    2560,    /* ST_Dump_CylMovementDelta    10.0 */
    {    /* ST_Dump_DumpAngleAxis */
      -1280,2240
      /* -20.0,35.0 */
    },
    768,    /* ST_Dump_GroundSpeedThreshold    3.0 */
    100,    /* ST_Dump_ImplementsIdleTime    2.0 */
    128,    /* ST_Dump_LeverDeadband    8.0 */
    13    /* ST_Dump_ValveCmdZeroTime    0.25 */
  },

  /**************************************************
   *  LIBINFO_cycleSeg_calcompvar = wl_00_segments_var_04
   **************************************************/
  {
    1.0,    /* ST_Dig_DecelerationTrigger    1.0 */
    0.3,    /* ST_Dig_PayloadRatioHighThrshld    0.3 */
    0.15,    /* ST_Dig_PyldRtioDrvtHighThrshld    0.15 */
    0.25,    /* ST_Dig_PyldRtioDrvtOvridTrshld    0.25 */
    {    /* ST_Dump_LoadRatioAxis */
      0.25,0.75
      /* 0.25,0.75 */
    },
    -2240,    /* ST_BucketPos_FullDumpBucketAng    -35.0 */
    2560,    /* ST_BucketPos_FullRackBucketAng    40.0 */
    13881,    /* ST_Dig_AccelerationFiltrFactor    0.423618822870924 */
    1280,    /* ST_Dig_BucketAngleMaxStart    20.0 */
    5,    /* ST_Dig_DecelerationResetTime    0.1 */
    5,    /* ST_Dig_DecelerationTriggerTime    0.1 */
    100,    /* ST_Dig_DirShiftInhibitTime    2.0 */
    428,    /* ST_Dig_ExtFrceNrmlzdHghThrshld    0.214 */
    285,    /* ST_Dig_ExtFrceNrmlzdLowThrshld    0.1426 */
    1212,    /* ST_Dig_ExtrnlFrceSlwFiltrFactr    0.036993047642836 */
    2560,    /* ST_Dig_GroundSpeedMax    10.0 */
    -768,    /* ST_Dig_GroundSpeedMin    -3.0 */
    -256,    /* ST_Dig_GroundSpeedTriggerMin    -1.0 */
    100,    /* ST_Dig_ImplementsIdleTime    2.0 */
    0,    /* ST_Dig_LiftAngleMaxStart    0.0 */
    13881,    /* ST_Dig_PyldRtioDrvtFiltrFactor    0.423618822870924 */
    6,    /* ST_Dig_TentativeConfirmatnTime    0.12 */
    500,    /* ST_Dig_TentativeMaxTime    10.0 */
    2560,    /* ST_Dump_CylMovementDelta    10.0 */
    {    /* ST_Dump_DumpAngleAxis */
      -1280,2240
      /* -20.0,35.0 */
    },
    768,    /* ST_Dump_GroundSpeedThreshold    3.0 */
    100,    /* ST_Dump_ImplementsIdleTime    2.0 */
    128,    /* ST_Dump_LeverDeadband    8.0 */
    13    /* ST_Dump_ValveCmdZeroTime    0.25 */
  },

  /**************************************************
   *  LIBINFO_cycleSeg_calcompvar = wl_00_segments_var_05
   **************************************************/
  {
    1.0,    /* ST_Dig_DecelerationTrigger    1.0 */
    0.3,    /* ST_Dig_PayloadRatioHighThrshld    0.3 */
    0.15,    /* ST_Dig_PyldRtioDrvtHighThrshld    0.15 */
    0.25,    /* ST_Dig_PyldRtioDrvtOvridTrshld    0.25 */
    {    /* ST_Dump_LoadRatioAxis */
      0.25,0.75
      /* 0.25,0.75 */
    },
    -2240,    /* ST_BucketPos_FullDumpBucketAng    -35.0 */
    2560,    /* ST_BucketPos_FullRackBucketAng    40.0 */
    13881,    /* ST_Dig_AccelerationFiltrFactor    0.423618822870924 */
    1280,    /* ST_Dig_BucketAngleMaxStart    20.0 */
    5,    /* ST_Dig_DecelerationResetTime    0.1 */
    5,    /* ST_Dig_DecelerationTriggerTime    0.1 */
    100,    /* ST_Dig_DirShiftInhibitTime    2.0 */
    428,    /* ST_Dig_ExtFrceNrmlzdHghThrshld    0.214 */
    285,    /* ST_Dig_ExtFrceNrmlzdLowThrshld    0.1426 */
    1212,    /* ST_Dig_ExtrnlFrceSlwFiltrFactr    0.036993047642836 */
    2560,    /* ST_Dig_GroundSpeedMax    10.0 */
    -768,    /* ST_Dig_GroundSpeedMin    -3.0 */
    -256,    /* ST_Dig_GroundSpeedTriggerMin    -1.0 */
    100,    /* ST_Dig_ImplementsIdleTime    2.0 */
    0,    /* ST_Dig_LiftAngleMaxStart    0.0 */
    13881,    /* ST_Dig_PyldRtioDrvtFiltrFactor    0.423618822870924 */
    6,    /* ST_Dig_TentativeConfirmatnTime    0.12 */
    500,    /* ST_Dig_TentativeMaxTime    10.0 */
    2560,    /* ST_Dump_CylMovementDelta    10.0 */
    {    /* ST_Dump_DumpAngleAxis */
      -1280,2240
      /* -20.0,35.0 */
    },
    768,    /* ST_Dump_GroundSpeedThreshold    3.0 */
    100,    /* ST_Dump_ImplementsIdleTime    2.0 */
    128,    /* ST_Dump_LeverDeadband    8.0 */
    13    /* ST_Dump_ValveCmdZeroTime    0.25 */
  }

};



  /*
   * Internal state
   */

static sl_cal_state_t state;



  /*
   * Internal variant index for each component
   */

static sl_cal_variant_index_index_t variant_index_tbl[3];



  /*
   * Number of Variants for each Calibration Component
   */

static const uint_least8_t variant_counts[] =
{
  6,  /* variant Application */
  6,  /* variant LIBINFO_WL_00_Machine */
  6   /* variant LIBINFO_cycleSeg_calcompvar */
};



  /*
   * Constraints for Dependent Calibration Component LIBINFO_WL_00_Machine
   */

static const sl_cal_variant_index_constraints_t constraints_1[] =
{
  1,  /* controlled by 1 other components */
  0,  /* Controlled by Application */
  0,  /* Machine_950_HRC @ Application = Application_5000 */
  1,  /* Machine_962_HRC @ Application = Application_6200 */
  2,  /* Machine_966_HRC @ Application = Application_6600 */
  3,  /* Machine_972_HRC @ Application = Application_7200 */
  4,  /* Machine_980_HRC @ Application = Application_8000 */
  5  /* Machine_982_HRC @ Application = Application_8200 */
};



  /*
   * Constraints for Dependent Calibration Component LIBINFO_cycleSeg_calcompvar
   */

static const sl_cal_variant_index_constraints_t constraints_2[] =
{
  1,  /* controlled by 1 other components */
  1,  /* Controlled by LIBINFO_WL_00_Machine */
  0,  /* wl_00_segments_var_00 @ LIBINFO_WL_00_Machine = Machine_950_HRC */
  1,  /* wl_00_segments_var_01 @ LIBINFO_WL_00_Machine = Machine_962_HRC */
  2,  /* wl_00_segments_var_02 @ LIBINFO_WL_00_Machine = Machine_966_HRC */
  3,  /* wl_00_segments_var_03 @ LIBINFO_WL_00_Machine = Machine_972_HRC */
  4,  /* wl_00_segments_var_04 @ LIBINFO_WL_00_Machine = Machine_980_HRC */
  5  /* wl_00_segments_var_05 @ LIBINFO_WL_00_Machine = Machine_982_HRC */
};



  /*
   * Constraints for Dependent Calibration Components
   */

static const sl_cal_variant_index_constraints_t * const constraints[] =
{
  constraints_1,  /* constraints for variant LIBINFO_WL_00_Machine */
  constraints_2   /* constraints for variant LIBINFO_cycleSeg_calcompvar */
};



  /*
   * Variant Ids for Calibration Component Application
   */

static const sl_cal_variant_id_t variant_ids_component_0[] =
{
  5000,  /* variant Application_5000 */
  6200,  /* variant Application_6200 */
  6600,  /* variant Application_6600 */
  7200,  /* variant Application_7200 */
  8000,  /* variant Application_8000 */
  8200   /* variant Application_8200 */
};



  /*
   * Input Signals
   */

static const sl_cal_input_signal_ref_t input_signals[] =
{
  {
    variant_ids_component_0,  /* ids for variant Application */
    &(LIBPROD_app_number)   /* signal variable for variant Application */
  }
};



  /*
   * References to Instance Specifications (calibration pointers)
   */

static const sl_cal_instance_ref_t instance_refs[] =
{
  {
    ((255 << 24) | sizeof(LIBINFO_WL_00_LIBINFO_Totalizer_00_calcompfix_mi_ROM_t)),  /* component index and calibration element size for LIBINFO_Totalizer_00_calcompfix */
    LIBINFO_WL_00_LIBINFO_Totalizer_00_calcompfix_mi_ROM,  /* array of calibration for each variant */
    (const void **)&(LIBINFO_WL_00_work.LIBINFO_WL_00_M.LIBINFO_WL_00_LIBINFO_Totalizer_00_calcompfix_mi_ROM_p)   /* pointer to calibration for component LIBINFO_Totalizer_00_calcompfix */
  },
  {
    ((255 << 24) | sizeof(LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_t)),  /* component index and calibration element size for LIBINFO_cycleSeg_calcompfix */
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM,  /* array of calibration for each variant */
    (const void **)&(LIBINFO_WL_00_work.LIBINFO_WL_00_M.LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_p)   /* pointer to calibration for component LIBINFO_cycleSeg_calcompfix */
  },
  {
    ((2 << 24) | sizeof(LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_t)),  /* component index and calibration element size for LIBINFO_cycleSeg_calcompvar */
    LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM,  /* array of calibration for each variant */
    (const void **)&(LIBINFO_WL_00_work.LIBINFO_WL_00_M.LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_p)   /* pointer to calibration for component LIBINFO_cycleSeg_calcompvar */
  }
};



  /*
   * Synchronous Calibration for thread 120ms
   */

const sl_cal_thread_cal_t LIBINFO_WL_00_cal_thread_120ms =
{
  3,  /* instance reference starting index for this thread */
  0   /* number of pointers set in this thread  */
};



  /*
   * Synchronous Calibration for thread 1s
   */

const sl_cal_thread_cal_t LIBINFO_WL_00_cal_thread_1s =
{
  3,  /* instance reference starting index for this thread */
  0   /* number of pointers set in this thread  */
};



  /*
   * Synchronous Calibration for thread init
   */

const sl_cal_thread_cal_t LIBINFO_WL_00_cal_thread_init =
{
  3,  /* instance reference starting index for this thread */
  0   /* number of pointers set in this thread  */
};



  /*
   * Calibration
   */

const sl_cal_t LIBINFO_WL_00_cal =
{
  1,  /* number of independent startup calibration components */
  0,  /* number of independent runtime calibration components */
  2,  /* number of dependent startup calibration components */
  0,  /* number of dependent runtime calibration components */
  0,  /* number of output signals */
  3,  /* number of instance references */
  3,  /* number of startup instance references */
  0,  /* number of asynchronous runtime instance references */
  variant_counts,  /* number of variants for each component */
  NULL,  /* component id for each independent startup */
  input_signals,  /* input signals */
  NULL,  /* output signals */
  constraints,  /* dependencies */
  instance_refs,  /* calibration instance reference table */
  &state,  /* state (except indices) */
  variant_index_tbl,  /* index of variant for each component */
  NULL   /* mutable image */
};

