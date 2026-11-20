/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: LIBINFO_WL_00_variant.h
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
#ifndef RTW_HEADER_LIBINFO_WL_00_variant_h_
#define RTW_HEADER_LIBINFO_WL_00_variant_h_
#include "R2012b_rtwtypes.h"
#include "LIBINFO_WL_00_types.h"

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/
typedef struct LIBINFO_WL_00_LIBINFO_Totalizer_00_calcompfix_mi_ROM_tag {
  dt_libinfo_fuel_high_res ST_FuelUsed_HighResIntgrlResol;
  dt_libinfo_Time20msLong ST_TotSlave_Maxvalue;
  dt_libinfo_Unsigned8 ST_Tot_ActiveStateValue;
  dt_libinfo_Flag ST_Tot_MaxSeqNum;
  dt_libinfo_Unsigned8 ST_Tot_TentativeStateValue;
} LIBINFO_WL_00_LIBINFO_Totalizer_00_calcompfix_mi_ROM_t;

typedef struct LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_tag {
  dt_libinfo_single ST_LoadStat_DwnFrcLdRatioOfset;
  real32_T ST_LoadStat_DwnFrceRstThreshld;
  real32_T ST_LoadStat_DwnFrceTrgrThrshld;
  dt_libinfo_single ST_LoadStatus_LoadedRatio;
  dt_libinfo_single ST_LoadStatus_UnloadedRatio;
  dt_libinfo_Time20ms ST_KeyStat_EngRunStateDebounce;
  dt_libinfo_Time20ms ST_KeyStatus_MinDESTime;
  dt_libinfo_Time20ms ST_LoadStat_LoadStatusDebounce;
  dt_libinfo_Time20ms ST_Stopped_ActiveTime;
  dt_libinfo_Time20ms ST_Stopped_CommitTime;
  dt_libinfo_MachSpdKPH_Signed ST_Stopped_GroundSpeedThreshold;
  dt_libinfo_Time20ms ST_Stopped_InactiveTime;
  dt_libinfo_MachSpdKPH_Signed ST_Travel_GroundSpeedThreshold;
  dt_libinfo_Time20ms ST_Travel_MaxTentativeTime;
  dt_libinfo_Time20ms ST_Travel_MinSegmentTime;
  dt_libinfo_Time20ms ST_Travel_NotTravelingDebounce;
  dt_libinfo_Time20ms ST_Unknown_CommitTime;
} LIBINFO_WL_00_LIBINFO_cycleSeg_calcompfix_mi_ROM_t;

typedef struct LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_tag {
  real32_T ST_Dig_DecelerationTrigger;
  dt_libinfo_single ST_Dig_PayloadRatioHighThrshld;
  real32_T ST_Dig_PyldRtioDrvtHighThrshld;
  real32_T ST_Dig_PyldRtioDrvtOvridTrshld;
  dt_libinfo_single ST_Dump_LoadRatioAxis[2];
  dt_libinfo_Angle ST_BucketPos_FullDumpBucketAng;
  dt_libinfo_Angle ST_BucketPos_FullRackBucketAng;
  dt_libinfo_FilterFactor ST_Dig_AccelerationFiltrFactor;
  dt_libinfo_Angle ST_Dig_BucketAngleMaxStart;
  dt_libinfo_Time20ms ST_Dig_DecelerationResetTime;
  dt_libinfo_Time20ms ST_Dig_DecelerationTriggerTime;
  dt_libinfo_Time20ms ST_Dig_DirShiftInhibitTime;
  dt_libinfo_Ratio_hiRes ST_Dig_ExtFrceNrmlzdHghThrshld;
  dt_libinfo_Ratio_hiRes ST_Dig_ExtFrceNrmlzdLowThrshld;
  dt_libinfo_FilterFactor ST_Dig_ExtrnlFrceSlwFiltrFactr;
  dt_libinfo_MachSpdKPH_Signed ST_Dig_GroundSpeedMax;
  dt_libinfo_MachSpdKPH_Signed ST_Dig_GroundSpeedMin;
  dt_libinfo_MachSpdKPH_Signed ST_Dig_GroundSpeedTriggerMin;
  dt_libinfo_Time20ms ST_Dig_ImplementsIdleTime;
  dt_libinfo_Angle ST_Dig_LiftAngleMaxStart;
  dt_libinfo_FilterFactor ST_Dig_PyldRtioDrvtFiltrFactor;
  dt_libinfo_Time20ms ST_Dig_TentativeConfirmatnTime;
  dt_libinfo_Time20ms ST_Dig_TentativeMaxTime;
  dt_libinfo_modulation_pct ST_Dump_CylMovementDelta;
  dt_libinfo_Angle ST_Dump_DumpAngleAxis[2];
  dt_libinfo_MachSpdKPH_Signed ST_Dump_GroundSpeedThreshold;
  dt_libinfo_Time20ms ST_Dump_ImplementsIdleTime;
  dt_libinfo_ValveCmd ST_Dump_LeverDeadband;
  dt_libinfo_Time20ms ST_Dump_ValveCmdZeroTime;
} LIBINFO_WL_00_LIBINFO_cycleSeg_calcompvar_mi_ROM_t;

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
#endif                                 /* RTW_HEADER_LIBINFO_WL_00_variant_h_ */
