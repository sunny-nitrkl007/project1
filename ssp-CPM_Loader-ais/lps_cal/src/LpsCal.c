/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:
DESCRIPTION:
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#ifndef __LPS_COMMON_TYPE_DEF_H__
#include <LpsCommonTypeDef.h> /* Contains type definitions of standard datatypes */
#endif

#ifndef CAL_MGR_H_
#include <cal_mgr.h>
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCalAppPublic.h> /* Contains type definitions of standard datatypes */
#endif

#ifndef CAL_STRUCT_H_
#include <cal_struct.h>
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCommonStructures.h> /* Contains type definitions of standard datatypes */
#endif

#ifndef __LPS_COMMON_LOOKUP_TBL_UTILITY__
#include <LpsCommonLookUpTblUtility.h>
#endif

#ifndef __LPS_CAL_PUBLIC_H__
#include <LpsCalPublic.h>
#endif

#ifndef __LPS_CAL_PRIVATE_H__
#include "LpsCalPrivate.h"
#endif

// Ignore this warning due to unused my_assert function in oel_assert.h
#pragma GCC diagnostic ignored "-Wunused-function"
#include <clock_proto.h>

#include <string.h>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
static float LpsCalCalculateIMUFinalOffset(float offset1, float offset2);

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
signed_16 HydOilTempMin = (signed_16)(LPS_CAL_OIL_TEMP_MIN + 10.0);

/* Empty-Bucket Manual Cals */
LpsCalStepsMapping_t LpsManualEmptyCalStepsMapping[] =
{
    { LPS_CAL_EMPTY_CAL_INT_STEP_START,        LPS_MANUAL_CAL_EMPTY_CAL_STEP_START },
    { LPS_CAL_EMPTY_CAL_INT_STEP_HYD_OIL,      LPS_MANUAL_CAL_EMPTY_CAL_STEP_HYD_OIL },
    { LPS_CAL_EMPTY_CAL_INT_STEP_RACK_POS,     LPS_MANUAL_CAL_EMPTY_CAL_STEP_RACK_POS },
    { LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_POS,    LPS_MANUAL_CAL_EMPTY_CAL_STEP_LOWER_POS },
    { LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_1, LPS_MANUAL_CAL_EMPTY_CAL_STEP_CENTER_LVR_1 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_VEL_1, LPS_MANUAL_CAL_EMPTY_CAL_STEP_RAISE_FAST_VEL_1 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_VEL_1, LPS_MANUAL_CAL_EMPTY_CAL_STEP_LOWER_FAST_VEL_1 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_2, LPS_MANUAL_CAL_EMPTY_CAL_STEP_CENTER_LVR_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_1, LPS_MANUAL_CAL_EMPTY_CAL_STEP_RAISE_SLOW_1 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_1, LPS_MANUAL_CAL_EMPTY_CAL_STEP_LOWER_SLOW_1 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_2, LPS_MANUAL_CAL_EMPTY_CAL_STEP_RAISE_SLOW_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_2, LPS_MANUAL_CAL_EMPTY_CAL_STEP_LOWER_SLOW_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_3, LPS_MANUAL_CAL_EMPTY_CAL_STEP_RAISE_SLOW_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_3, LPS_MANUAL_CAL_EMPTY_CAL_STEP_LOWER_SLOW_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_3, LPS_MANUAL_CAL_EMPTY_CAL_STEP_CENTER_LVR_3 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_1, LPS_MANUAL_CAL_EMPTY_CAL_STEP_RAISE_FAST_1 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_1, LPS_MANUAL_CAL_EMPTY_CAL_STEP_LOWER_FAST_1 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_2, LPS_MANUAL_CAL_EMPTY_CAL_STEP_RAISE_FAST_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_2, LPS_MANUAL_CAL_EMPTY_CAL_STEP_LOWER_FAST_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_3, LPS_MANUAL_CAL_EMPTY_CAL_STEP_RAISE_FAST_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_3, LPS_MANUAL_CAL_EMPTY_CAL_STEP_LOWER_FAST_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_END,          LPS_MANUAL_CAL_EMPTY_CAL_STEP_LOWER_FAST_2 }
};

/* Empty-Bucket Auto Cals */
LpsCalStepsMapping_t LpsAutoEmptyCalStepsMapping[] =
{
    { LPS_CAL_EMPTY_CAL_INT_STEP_START,        LPS_AUTO_CAL_EMPTY_CAL_STEP_START },
    { LPS_CAL_EMPTY_CAL_INT_STEP_HYD_OIL,      LPS_AUTO_CAL_EMPTY_CAL_STEP_HYD_OIL },
    { LPS_CAL_EMPTY_CAL_INT_STEP_RACK_POS,     LPS_AUTO_CAL_EMPTY_CAL_STEP_RACK_POS },
    { LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_POS,    LPS_AUTO_CAL_EMPTY_CAL_STEP_LOWER_POS },
    { LPS_CAL_EMPTY_CAL_INT_STEP_ENG_SPD,      LPS_AUTO_CAL_EMPTY_CAL_STEP_ENG_SPD },
    { LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_2, LPS_AUTO_CAL_EMPTY_CAL_STEP_CENTER_LVR_1 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_1, LPS_AUTO_CAL_EMPTY_CAL_STEP_RAISE_SLOW_1 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_1, LPS_AUTO_CAL_EMPTY_CAL_STEP_LOWER_SLOW_1 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_2, LPS_AUTO_CAL_EMPTY_CAL_STEP_RAISE_SLOW_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_2, LPS_AUTO_CAL_EMPTY_CAL_STEP_LOWER_SLOW_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_3, LPS_AUTO_CAL_EMPTY_CAL_STEP_RAISE_SLOW_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_3, LPS_AUTO_CAL_EMPTY_CAL_STEP_LOWER_SLOW_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_3, LPS_AUTO_CAL_EMPTY_CAL_STEP_CENTER_LVR_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_1, LPS_AUTO_CAL_EMPTY_CAL_STEP_RAISE_FAST_1 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_1, LPS_AUTO_CAL_EMPTY_CAL_STEP_LOWER_FAST_1 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_2, LPS_AUTO_CAL_EMPTY_CAL_STEP_RAISE_FAST_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_2, LPS_AUTO_CAL_EMPTY_CAL_STEP_LOWER_FAST_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_3, LPS_AUTO_CAL_EMPTY_CAL_STEP_RAISE_FAST_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_3, LPS_AUTO_CAL_EMPTY_CAL_STEP_LOWER_FAST_2 },
    { LPS_CAL_EMPTY_CAL_INT_STEP_END,          LPS_AUTO_CAL_EMPTY_CAL_STEP_LOWER_FAST_2 }
};

/* Full-Bucket Manual Cals */
LpsCalStepsMapping_t LpsManualFullCalStepsMapping[] =
{
    { LPS_CAL_FULL_CAL_INT_STEP_START,                LPS_MANUAL_CAL_FULL_CAL_STEP_START },
    { LPS_CAL_FULL_CAL_INT_STEP_HYD_OIL,              LPS_MANUAL_CAL_FULL_CAL_STEP_HYD_OIL },
    { LPS_CAL_FULL_CAL_INT_STEP_RACK_POS,             LPS_MANUAL_CAL_FULL_CAL_STEP_RACK_POS },
    { LPS_CAL_FULL_CAL_INT_STEP_LOWER_POS,           LPS_MANUAL_CAL_FULL_CAL_STEP_LOWER_POS },
    { LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_1,         LPS_MANUAL_CAL_FULL_CAL_STEP_CENTER_LVR_1 },
    { LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_VEL_1,     LPS_MANUAL_CAL_FULL_CAL_STEP_RAISE_FAST_VEL_1 },
    { LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_VEL_1,     LPS_MANUAL_CAL_FULL_CAL_STEP_LOWER_FAST_VEL_1 },
    { LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_2,         LPS_MANUAL_CAL_FULL_CAL_STEP_CENTER_LVR_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_1,         LPS_MANUAL_CAL_FULL_CAL_STEP_RAISE_SLOW_1 },
    { LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_1,         LPS_MANUAL_CAL_FULL_CAL_STEP_LOWER_SLOW_1 },
    { LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_2,         LPS_MANUAL_CAL_FULL_CAL_STEP_RAISE_SLOW_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_2,         LPS_MANUAL_CAL_FULL_CAL_STEP_LOWER_SLOW_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_3,         LPS_MANUAL_CAL_FULL_CAL_STEP_RAISE_SLOW_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_3,         LPS_MANUAL_CAL_FULL_CAL_STEP_LOWER_SLOW_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_3,         LPS_MANUAL_CAL_FULL_CAL_STEP_CENTER_LVR_3 },
    { LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_1,         LPS_MANUAL_CAL_FULL_CAL_STEP_RAISE_FAST_1 },
    { LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_1,         LPS_MANUAL_CAL_FULL_CAL_STEP_LOWER_FAST_1 },
    { LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_2,         LPS_MANUAL_CAL_FULL_CAL_STEP_RAISE_FAST_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_2,         LPS_MANUAL_CAL_FULL_CAL_STEP_LOWER_FAST_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_3,         LPS_MANUAL_CAL_FULL_CAL_STEP_RAISE_FAST_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_3,         LPS_MANUAL_CAL_FULL_CAL_STEP_LOWER_FAST_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_END,                  LPS_MANUAL_CAL_FULL_CAL_STEP_LOWER_FAST_2 }
};

/* Full-Bucket Auto Cals */
LpsCalStepsMapping_t LpsAutoFullCalStepsMapping[] =
{
    { LPS_CAL_FULL_CAL_INT_STEP_START,              LPS_AUTO_CAL_FULL_CAL_STEP_START },
    { LPS_CAL_FULL_CAL_INT_STEP_HYD_OIL,            LPS_AUTO_CAL_FULL_CAL_STEP_HYD_OIL },
    { LPS_CAL_FULL_CAL_INT_STEP_RACK_POS,           LPS_AUTO_CAL_FULL_CAL_STEP_RACK_POS },
    { LPS_CAL_FULL_CAL_INT_STEP_LOWER_POS,          LPS_AUTO_CAL_FULL_CAL_STEP_LOWER_POS },
    { LPS_CAL_FULL_CAL_INT_STEP_ENG_SPD,            LPS_AUTO_CAL_FULL_CAL_STEP_ENG_SPD },
    { LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_2,       LPS_AUTO_CAL_FULL_CAL_STEP_CENTER_LVR_1 },
    { LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_1,       LPS_AUTO_CAL_FULL_CAL_STEP_RAISE_SLOW_1 },
    { LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_1,       LPS_AUTO_CAL_FULL_CAL_STEP_LOWER_SLOW_1 },
    { LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_2,       LPS_AUTO_CAL_FULL_CAL_STEP_RAISE_SLOW_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_2,       LPS_AUTO_CAL_FULL_CAL_STEP_LOWER_SLOW_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_3,       LPS_AUTO_CAL_FULL_CAL_STEP_RAISE_SLOW_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_3,       LPS_AUTO_CAL_FULL_CAL_STEP_LOWER_SLOW_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_3,       LPS_AUTO_CAL_FULL_CAL_STEP_CENTER_LVR_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_1,       LPS_AUTO_CAL_FULL_CAL_STEP_RAISE_FAST_1 },
    { LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_1,       LPS_AUTO_CAL_FULL_CAL_STEP_LOWER_FAST_1 },
    { LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_2,       LPS_AUTO_CAL_FULL_CAL_STEP_RAISE_FAST_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_2,       LPS_AUTO_CAL_FULL_CAL_STEP_LOWER_FAST_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_3,       LPS_AUTO_CAL_FULL_CAL_STEP_RAISE_FAST_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_3,       LPS_AUTO_CAL_FULL_CAL_STEP_LOWER_FAST_2 },
    { LPS_CAL_FULL_CAL_INT_STEP_END,                LPS_AUTO_CAL_FULL_CAL_STEP_LOWER_FAST_2 }
};

/* Manual Cal */
#define LPS_MANUAL_CAL_EMPTY_CAL_STEPS_MAPPING_NUM_ENTRIES (sizeof(LpsManualEmptyCalStepsMapping)/sizeof(LpsCalStepsMapping_t))
#define LPS_MANUAL_CAL_FULL_CAL_STEPS_MAPPING_NUM_ENTRIES (sizeof(LpsManualFullCalStepsMapping)/sizeof(LpsCalStepsMapping_t))

/* Auto Cal */
#define LPS_AUTO_CAL_EMPTY_CAL_STEPS_MAPPING_NUM_ENTRIES (sizeof(LpsAutoEmptyCalStepsMapping)/sizeof(LpsCalStepsMapping_t))
#define LPS_AUTO_CAL_FULL_CAL_STEPS_MAPPING_NUM_ENTRIES (sizeof(LpsAutoFullCalStepsMapping)/sizeof(LpsCalStepsMapping_t))


static unsigned_32 CalCount = 0;

/******************************************************************************
FUNCTION NAME: LpsCalEmptyCalMain
DESCRIPTION: Empty bucket calibration main function called by the cal manager.
PARAMETER DESCRIPTION:
RETURN VALUE: CAL_MGR_MR_E
*******************************************************************************/
/*CAL_MGR_MR_E LpsCalEmptyCalMain(CAL_MGR_MC_E         Cmd,
                                CAL_MGR_Work_t       *Cmw,
                                CAL_MGR_Cnfg_t const *Cmc,
                                CAL_MGR_Cal_t        *Cal)*/

CAL_MGR_MR_E LpsCalEmptyCalMain(CAL_MGR_MC_E         Cmd,
                                unsigned_16             CalId,
                                unsigned_8*             StepNo,
                                unsigned_16*         CalError)
{
    CAL_MGR_Cal_t calMgrCal;
    calMgrCal.id = CalId;
    CAL_MGR_Cal_t* Cal = &calMgrCal;
    LpsCalCfg_t* pCalCfg = &LpsCalWrkTbl.Cfg;
    LpsCalNvmTbl_t* pCalNvm = &LpsCalWrkTbl.Nvm;
    LpsCalUpdate_t* pCalUpdate = &LpsCalWrkTbl.Update;
    LpsCalStatus_t* pCalStatus = &LpsCalWrkTbl.Status;
    LpsCalInfo_t* pCalInfo = &LpsCalWrkTbl.Info;
    LpsCalCurveFitInfo_t* pCurveFitInfo = &LpsCalWrkTbl.CurveFitInfo;
    boolean *pCalEnabled = LpsCalWrkTbl.Cfg.CalEnableFlg;
    float pitch_offset = 0.f;
    float lumped_weight = 0.f;

    //TODO - what should be done when udpate fails? losing points?
    /*if(LPS_CAL_UPDT_SUCCESS != LpsCalWrkTbl.UpdateErr)
    {
        return LpsCalWrkTbl.UpdateErr;
    }*/

    //(void)Cmc;

    *CalError = 0;

    LpsCalPrint(LPSCAL_LOG_WAYPOINT, "Cmd %d CalId %d StepNo %d iStep %d CalCount %d CalError %d",
            Cmd, CalId, StepNo, pCurveFitInfo->InternalStep, CalCount, *CalError);

     switch(Cmd)
     {
        /* This is the first thing called */
        case (CAL_MGR_MC_INIT_LAST_STAT):
        {
            if(Cal->id != LpsCalWrkTbl.EmptyWtCal.wId)
            {
                /* Cal cannot support CAL_ID (Not Supported) */
               LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INIT_LAST_STAT - CAL_MGR_MR_INIT_LAST_STAT_NS iStep %d", pCurveFitInfo->InternalStep);
               return (CAL_MGR_MR_INIT_LAST_STAT_NS);
            }
            else
            {
                LpsCalResetCurveFitInfo();
                ((CAL_MGR_LStat_t *)Cal)->stat = (cal_last_stat_t*)&LpsCalWrkTbl.EmptyWtCal;
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INIT_LAST_STAT - CAL_MGR_MR_INIT_LAST_STAT_OK iStep %d", pCurveFitInfo->InternalStep);
                return (CAL_MGR_MR_INIT_LAST_STAT_OK);
            }
        }

         /* This is the second thing called */
        case (CAL_MGR_MC_INITIALIZE):
        {
            LpsCalPrint(LPSCAL_LOG_INFO, "----------------- Empty Cal -----------------");

            if ((NULL != pCalEnabled) && (FALSE == *pCalEnabled))
            {
                *CalError = LPS_CAL_NOT_SUPPORTED;
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INITIALIZE - CAL_MGR_MR_INITIALIZE_NOT_OK iStep %d", pCurveFitInfo->InternalStep);
                return CAL_MGR_MR_INITIALIZE_NOT_OK;
            }

            if(LPS_CAL_INIT_SUCCESS != LpsCalWrkTbl.InitErr)
            {
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INITIALIZE - LpsCalWrkTbl.InitErr - CAL_MGR_MR_INITIALIZE_NOT_OK  iStep %d", pCurveFitInfo->InternalStep);
                return CAL_MGR_MR_INITIALIZE_NOT_OK;
            }

            /* Fail calibrations if machine/model is not selected */
            if(LPS_STATUS_BAD == LpsCalWrkTbl.Cfg.MachineModelCfg)
            {
                *CalError = LPS_CAL_MACHINE_MODEL_NOT_SET;
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INITIALIZE - pCalCfg->MachineModelCfg - CAL_MGR_MR_INITIALIZE_NOT_OK  iStep %d", pCurveFitInfo->InternalStep);
                return CAL_MGR_MR_INITIALIZE_NOT_OK;
            }

            /* Fail calibrations if Legal for Trade is Sealed */
            if (pCalUpdate->LegalForTradeSealed) {
                *CalError = LPS_CAL_PAYLOAD_LEGAL_FOR_TRADE_SEALED;
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INITIALIZE - pCalUpdate->LegalForTradeSealed - CAL_MGR_MR_INITIALIZE_NOT_OK  iStep %d", pCurveFitInfo->InternalStep);
                return CAL_MGR_MR_INITIALIZE_NOT_OK;
            }

            /* Set empty lift cal complete flag to FALSE */
            pCurveFitInfo->OldCalFlags = pCalNvm->CalStatus;
            pCalNvm->CalStatus &= ~CAL_EMPTY_BKT_CURVE_MASK;

            pCalStatus->EmptyBktCalDone = FALSE;
            pCalStatus->CalInProgress = TRUE;

            LpsCalWrkTbl.EnableQualRead = TRUE;

            if (NULL != pCalCfg->QualReadEnableOrDisable)
            {
                pCalCfg->QualReadEnableOrDisable(LPS_CAL_QUAL_READ_ENABLE, &HydOilTempMin);
            }

            pCurveFitInfo->HydOilTempMet = FALSE;
            pCurveFitInfo->EnforceRaiseDetent = FALSE;
            pCurveFitInfo->EnforceLowerDetent = FALSE;
            pCurveFitInfo->RaiseFastVelDone = FALSE;
            pCurveFitInfo->RaiseSlowFitDone = FALSE;
            pCurveFitInfo->RaiseFastFitDone = FALSE;
            pCurveFitInfo->LowerSlowFitDone = FALSE;

            /* Reset Tilt Overrides */
            LpsCalResetTiltOverrides();

            pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_START;

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INITIALIZE - CAL_MGR_MR_INITIALIZE_OK iStep %d", pCurveFitInfo->InternalStep);

            return (CAL_MGR_MR_INITIALIZE_OK);
        }

        /* Called at the beginning of setup check (conditional) and flow */
        case (CAL_MGR_MC_ADIAGCHK):
        {
            CAL_MGR_MR_E response = CAL_MGR_MR_ADIAGCHK_OK;

            if ((NULL != pCalEnabled) && (FALSE == *pCalEnabled))
            {
                //cal_add_error(LPS_CAL_NOT_SUPPORTED);
                *CalError = LPS_CAL_NOT_SUPPORTED;
                response = CAL_MGR_MR_ADIAGCHK_NOT_OK;
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_ADIAGCHK - CAL_MGR_MR_ADIAGCHK_NOT_OK iStep %d", pCurveFitInfo->InternalStep);
                return response;
            }

            if ((LPS_STATUS_BAD == pCalUpdate->LiftDiffPress.Stat) ||
                (LPS_STATUS_BAD == pCalUpdate->LiftCylLengthNorm.Stat) ||
                (LPS_HYD_OIL_TEMP_STATUS_BAD == pCalUpdate->HydOilTemp.Stat) ||
                (LPS_STATUS_BAD == pCalUpdate->LiftCylVel.Stat) ||
                (LPS_STATUS_BAD == pCalUpdate->TiltCylLengthNorm.Stat) ||
                (LPS_STATUS_BAD == pCalUpdate->TiltAngleABCPercent.Stat) ||
                (LPS_STATUS_BAD == pCalUpdate->BktAngle.Stat) ||
                (LPS_STATUS_BAD == pCalUpdate->ReferenceIMUData.Stat) ||
                (FALSE != pCalUpdate->VoltageEventActive) ||
                ((pCalCfg->AutoCalsEnabled) && LPS_STATUS_BAD == pCalUpdate->EngineSpeed.Stat) ||
                (TRUE == pCalUpdate->LiftLeverInfo.LeverInfoAvailable &&
                        TRUE == pCalUpdate->LiftLeverInfo.Faulted) ||
                (LpsCalWrkTbl.Cfg.EEFIMUCalEnable &&
                        (LPS_STATUS_BAD == pCalUpdate->EEFIMUData.Stat ||
                                LPS_STATUS_BAD == pCalUpdate->TiltHePressure.Stat ||
                                LPS_STATUS_BAD == pCalUpdate->TiltRePressure.Stat)))
                {
                    *CalError = LPS_CAL_ERROR_ACTIVE_DIAG;
                    LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_ADIAGCHK - CAL_MGR_MR_ADIAGCHK_NOT_OK iStep %d", pCurveFitInfo->InternalStep);
                    response = CAL_MGR_MR_ADIAGCHK_NOT_OK;
                }

            return response;
        }

        case (CAL_MGR_MC_SETUPCHK):
        {
            CAL_MGR_MR_E response;

            if (LPS_HYD_OIL_TEMP_STATUS_DISABLED == pCalUpdate->HydOilTemp.Stat) {
                pCurveFitInfo->HydOilTempMet = TRUE;
            }
            else {
                if (pCalUpdate->HydOilTemp.Val >= (float_32)(LPS_CAL_OIL_TEMP_MIN + 10.0)) {
                    pCurveFitInfo->HydOilTempMet = TRUE;
                    LpsCalPrint(LPSCAL_LOG_INFO, "pCurveFitInfo->HydOilTempMet %d", pCurveFitInfo->HydOilTempMet);
                }
                else if (pCalUpdate->HydOilTemp.Val < (float_32)(LPS_CAL_OIL_TEMP_MIN)) {
                    pCurveFitInfo->HydOilTempMet = FALSE;
                    LpsCalPrint(LPSCAL_LOG_INFO, "pCurveFitInfo->HydOilTempMet %d", pCurveFitInfo->HydOilTempMet);
                }
            }

            /* Stay here in setup check until all conditions are met */
            if (FALSE == pCurveFitInfo->HydOilTempMet)
            {
                pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_HYD_OIL;
                response = CAL_MGR_MR_SETUPCHK_NOT_OK;
            }
            else if ((pCalUpdate->DumpState != LPS_WEIGHT_BKT_FULLY_RACKED) && (!pCalInfo->CalTiltOverrideComplete))
            {
                pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_RACK_POS;
                response = CAL_MGR_MR_SETUPCHK_NOT_OK;
            }
            else if (pCalUpdate->LiftCylLengthNorm.Val > LpsCalBottomStagingHeight)
            {
                pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_POS;
                response = CAL_MGR_MR_SETUPCHK_NOT_OK;
            }
            else if ((pCalCfg->AutoCalsEnabled) &&
                    (pCalUpdate->EngineSpeed.Val < PCS_CAL_ENGINE_HIGH_IDLE_RPM))
            {
                pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_ENG_SPD;
                response = CAL_MGR_MR_SETUPCHK_NOT_OK;
            }
            else
            {
                if ((TRUE == pCurveFitInfo->RaiseSlowFitDone) && (TRUE == pCurveFitInfo->LowerSlowFitDone))
                {
                    pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_3;
                }
                else if(TRUE == pCurveFitInfo->RaiseFastVelDone || pCalCfg->AutoCalsEnabled)
                {
                    LpsCalPrint(LPSCAL_LOG_INFO, "pCurveFitInfo->RaiseFastVelDone %d CalCount %d LineNo %d",
                            pCurveFitInfo->RaiseFastVelDone, CalCount, __LINE__);
                    pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_2;
                }
                else
                {
                    pCurveFitInfo->RaiseSlowFitDone = FALSE;
                    pCurveFitInfo->RaiseFastFitDone = FALSE;
                    pCurveFitInfo->LowerSlowFitDone = FALSE;

                    /* Skipping the raise fast velocity step, it is not used. */
                    pCurveFitInfo->RaiseFastVelDone = TRUE;
                    pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_2;
                }

                response = CAL_MGR_MR_SETUPCHK_OK;
            }

            if (pCalCfg->AutoCalsEnabled) {
                *StepNo = LpsCalTranslateStep(pCurveFitInfo->InternalStep, LpsAutoEmptyCalStepsMapping, LPS_AUTO_CAL_EMPTY_CAL_STEPS_MAPPING_NUM_ENTRIES);
            }
            else {
                *StepNo = LpsCalTranslateStep(pCurveFitInfo->InternalStep, LpsManualEmptyCalStepsMapping, LPS_MANUAL_CAL_EMPTY_CAL_STEPS_MAPPING_NUM_ENTRIES);
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_SETUPCHK - resp %d step %d iStep %d CalCount %d HydOilTemp %f",
                    response, *StepNo, pCurveFitInfo->InternalStep, CalCount, pCalUpdate->HydOilTemp.Val);

            return response;
        }

        case (CAL_MGR_MC_INIT_FLOW):
        {
            /* Start the calibration overrides
                Once overrides are started, we do not allow normal, unlimited,
                operator control until the calibration routine is finished.
            */
            LpsCalStartLiftOverrides();

            /* Initialize override limits */
            LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalFastLowerCmd);

            pCurveFitInfo->EnforceRaiseDetent = FALSE;
            pCurveFitInfo->EnforceLowerDetent = FALSE;

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INIT_FLOW - CAL_MGR_MR_INIT_FLOW_OK iStep %d", pCurveFitInfo->InternalStep);

            return (CAL_MGR_MR_INIT_FLOW_OK);
        }

        case (CAL_MGR_MC_FLOW):
        {
            CAL_MGR_MR_E response;

            /* Check persistent setup conditions */
            if ((LPS_HYD_OIL_TEMP_STATUS_DISABLED != pCalUpdate->HydOilTemp.Stat) &&
                    (pCalUpdate->HydOilTemp.Val < (float_32)(LPS_CAL_OIL_TEMP_MIN)))
            {
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FLOW - Line no %d iStep %d", __LINE__, pCurveFitInfo->InternalStep);
                pCurveFitInfo->HydOilTempMet = FALSE;
                response = CAL_MGR_MR_FLOW_RESTART;
            }
            else if ((pCalUpdate->DumpState != LPS_WEIGHT_BKT_FULLY_RACKED) && (!LpsCalWrkTbl.Cfg.EEFIMUCalEnable))
            {
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FLOW - Line no %d iStep %d", __LINE__, pCurveFitInfo->InternalStep);
                response = CAL_MGR_MR_FLOW_RESTART;
            }
            else if ( (pCalCfg->AutoCalsEnabled) &&
                (pCalUpdate->EngineSpeed.Val < PCS_CAL_ENGINE_HIGH_IDLE_RPM))
            {
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FLOW - Line no %d iStep %d", __LINE__, pCurveFitInfo->InternalStep);
                response = CAL_MGR_MR_FLOW_RESTART;
            }
            else if (pCalInfo->CalTiltOverrideComplete && pCalInfo->CalTiltOverrideFail)
            {
                /* Tilt override was attempted but unsuccessful, fail the cal */
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FLOW - Line no %d iStep %d", __LINE__, pCurveFitInfo->InternalStep);
                response = CAL_MGR_MR_FLOW_ABORT;
            }
            else
            {
                if ((LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_1 == pCurveFitInfo->InternalStep) ||
                    (LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_2 == pCurveFitInfo->InternalStep) ||
                    (LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_3 == pCurveFitInfo->InternalStep))
                {
                    if (pCalUpdate->LiftCylLengthNorm.Val > LpsCalBottomStagingHeight)
                    {
                       LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FLOW %d - pCalUpdate->LiftCylLenghtNorm.Val > LpsCalBottomStagingHeight iStep %d", __LINE__, pCurveFitInfo->InternalStep);
                       response = CAL_MGR_MR_FLOW_RESTART;
                    }
                    else
                    {
                        response = CAL_MGR_MR_FLOW_OK;
                    }
                }
                else if ((TRUE ==  pCurveFitInfo->EnforceRaiseDetent) &&
                         (TRUE == pCalUpdate->LiftLeverInfo.LeverInfoAvailable &&
                          FALSE == pCalUpdate->LiftLeverInfo.InRaiseDetent))
                {
                   LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FLOW - Line no %d", __LINE__);

                   /* stop any tilt overrides that may be happening */
                   LpsCalStopTiltOverrides();

                   response = CAL_MGR_MR_FLOW_RESTART;
                }
                else if ((TRUE == pCurveFitInfo->EnforceLowerDetent) &&
                         (TRUE == pCalUpdate->LiftLeverInfo.LeverInfoAvailable &&
                          FALSE == pCalUpdate->LiftLeverInfo.InLowerDetent))
                {
                   LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FLOW - Line no %d  iStep %d", __LINE__, pCurveFitInfo->InternalStep);
                   response = CAL_MGR_MR_FLOW_RESTART;
                }
                else
                {
                    response = CAL_MGR_MR_FLOW_OK;
                }
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FLOW - resp %d iStep %d", response, pCurveFitInfo->InternalStep);
            return response;
        }

         /* All of the different ways to exit flow */
        case (CAL_MGR_MC_RESTART_FLOW):
        case (CAL_MGR_MC_EXIT_FLOW):
        {
            CAL_MGR_MR_E response;

            LpsCalStopLiftOverrides();
            LpsCalStopTiltOverrides();

            /* Re-initialize override limits */
            LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalFastLowerCmd);

            if (CAL_MGR_MC_EXIT_FLOW == Cmd)
            {
                response = CAL_MGR_MR_EXIT_FLOW_DONE;
            }
            else /* CAL_MGR_MC_RESTART_FLOW == cmd */
            {
                response = CAL_MGR_MR_RESTART_FLOW_OK;
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_RESTART_FLOW or CAL_MGR_MC_EXIT_FLOW - resp %d iStep %d", response, pCurveFitInfo->InternalStep);

            return response;
        }

        /* All of the different ways to exit the calibration */
        case (CAL_MGR_MC_STOP):
        case (CAL_MGR_MC_QUIT):
        case (CAL_MGR_MC_TERMINATE):
        case (CAL_MGR_MC_SUCCESS):
        {
            CAL_MGR_MR_E response;

            /* Stop the calibration overrides */
            LpsCalStopLiftOverrides();
            LpsCalStopTiltOverrides();

            /* Disable the qualified read */
            LpsCalWrkTbl.EnableQualRead = FALSE;

            if (NULL != pCalCfg->QualReadEnableOrDisable)
            {
                pCalCfg->QualReadEnableOrDisable(LPS_CAL_QUAL_READ_DISABLE, &HydOilTempMin);
            }

            if (CAL_MGR_MC_SUCCESS == Cmd)
            {
                pCalNvm->EmptyBktSlowRaiseSpd = pCurveFitInfo->RaiseSlowFitResultsFinal.AverageVelocity;
                pCalNvm->EmptyBktFastRaiseSpd = pCurveFitInfo->RaiseFastFitResultsFinal.AverageVelocity;
                pCalNvm->FastRaiseEmptyBktDeltaPres = pCurveFitInfo->RaiseFastFitResultsFinal.AverageDeltaPFromReference;

                // Store the x,y,z acceleration vector.
                pCalNvm->SlowRaiseEmptyIMUAccel[0] = pCurveFitInfo->RaiseFastFitResultsFinal.AryAverageIMUAccel[0];
                pCalNvm->SlowRaiseEmptyIMUAccel[1] = pCurveFitInfo->RaiseFastFitResultsFinal.AryAverageIMUAccel[1];
                pCalNvm->SlowRaiseEmptyIMUAccel[2] = pCurveFitInfo->RaiseFastFitResultsFinal.AryAverageIMUAccel[2];
                pCalNvm->SlowRaiseEmptyPitch = pCurveFitInfo->RaiseFastFitResultsFinal.AveragePitch;
                pCalNvm->SlowRaiseEmptyRoll = pCurveFitInfo->RaiseFastFitResultsFinal.AverageRoll;

                {
                    unsigned_8 ii;
                    for (ii = 0; ii < LPS_CAL_CURVE_FIT_NUM_POINTS; ii++)
                    {
                        pCalNvm->SlowRaiseEmptyBktLiftHt[ii] = pCurveFitInfo->RaiseSlowFitResultsFinal.AryPosition[ii];
                        pCalNvm->SlowRaiseEmptyBktLiftPres[ii] = pCurveFitInfo->RaiseSlowFitResultsFinal.AryPressure[ii];
                        pCalNvm->SlowLowerEmptyBktLiftHt[ii] = pCurveFitInfo->LowerSlowFitResultsFinal.AryPosition[ii];
                        pCalNvm->SlowLowerEmptyBktLiftPres[ii] = pCurveFitInfo->LowerSlowFitResultsFinal.AryPressure[ii];

                        LpsCalPrint(LPSCAL_LOG_INFO, "pCalNvm->SlowRaiseEmptyBktLiftHt[%d] %f \
                                                      pCalNvm->SlowRaiseEmptyBktLiftPres[%d] %f \
                                                      pCalNvm->SlowLowerEmptyBktLiftHt[%d] %f \
                                                      pCalNvm->SlowLowerEmptyBktLiftPres[%d] %f",
                                                      ii, pCalNvm->SlowRaiseEmptyBktLiftHt[ii],
                                                      ii, pCalNvm->SlowRaiseEmptyBktLiftPres[ii],
                                                      ii, pCalNvm->SlowLowerEmptyBktLiftHt[ii],
                                                      ii, pCalNvm->SlowLowerEmptyBktLiftPres[ii]);
                    }
                }

                if (LPS_HYD_OIL_TEMP_STATUS_DISABLED == pCalUpdate->HydOilTemp.Stat) {
                    pCalNvm->EmptyTemp = 0.0;
                }
                else {
                    pCalNvm->EmptyTemp = pCalUpdate->HydOilTemp.Val;
                }

                /* reset simple cal adjust and zero weight */
                pCalNvm->ZeroWeight = 0.0f;
                pCalNvm->CalAdjust = 0.0f;

                { /* Clear the advanced calibration adjustment table */
                    unsigned_8 ii;
                    for (ii = 0; ii < LPS_CAL_ADV_CAL_ADJUST_NUM_POINTS; ++ii) {
                        pCalNvm->AdvCalAdjustX[ii] = NAN;
                        pCalNvm->AdvCalAdjustY[ii] = NAN;
                    }
                }

                pCalNvm->CalStatus |= CAL_EMPTY_BKT_CURVE_MASK;

                /* On Successful Empty bucket cal, reset Full bucket cal and CalWt */
                pCalNvm->CalStatus &= ~CAL_FULL_BKT_CURVE_MASK;
                pCalNvm->CalStatus &= ~CAL_BKT_WT_MASK;
                pCalNvm->CalWeight = 0.0f;

                LpsCalWrkTbl.EmptyWtCal.lHourMeter = LpsCalWrkTbl.Update.ServiceHourMeter;
                pCalNvm->ShmEmptyMain = LpsCalWrkTbl.EmptyWtCal.lHourMeter;

                pCalNvm->CalVersion = LPS_CAL_VERSION_LATEST;
                pCalCfg->UpdateNvm(pCalNvm);

                pCalStatus->EmptyBktCalDone = TRUE;

                response = CAL_MGR_MR_SUCCESS_SAVED;
                CalCount++;
            }
            else
            {
                pCalNvm->CalStatus = pCurveFitInfo->OldCalFlags;
                if (CAL_MGR_MC_TERMINATE == Cmd)
                {
                    /* Exit flow is required next to turn off the overrides */
                    response = CAL_MGR_MR_TERMINATE_EXIT_REQ;
                }
                else if (CAL_MGR_MC_QUIT == Cmd)
                {
                    response = CAL_MGR_MR_QUIT_EXIT_REQ;
                }
                else if (CAL_MGR_MC_STOP == Cmd)
                {
                    response = CAL_MGR_MR_STOP_EXIT_REQ;
                }
                else
                {
                    response = CAL_MGR_MR_SUCCESS;
                }
            }

            pCalStatus->CalInProgress = FALSE;

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_STOP QUIT TERMINATE SUCCESS - resp %d iStep %d", response, pCurveFitInfo->InternalStep);

            return response;
        }
        case (CAL_MGR_MC_CLEANUP):
        {
            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_CLEANUP iStep %d", pCurveFitInfo->InternalStep);
            return (CAL_MGR_MR_CLEANUP_DONE);
        }

        case (CAL_MGR_MC_READY):
        {
            CAL_MGR_MR_E response;

            /* Wait for the operator to put the lever into the proper detent position */
            switch (pCurveFitInfo->InternalStep)
            {
                case (LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_2):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_3):
                {
                    LpsCalSetLiftOverrides(pCalCfg->CalSlowRaiseCmd, pCalCfg->CalFastLowerCmd);
                    response = CAL_MGR_MR_READY_YES;
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_VEL_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_2):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_3):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_2):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_3):
                {
                    /* Set the calibration overrides */
                    LpsCalSetLiftOverrides(0.0, pCalCfg->CalFastLowerCmd);
                    if(FALSE == pCalUpdate->LiftLeverInfo.LeverInfoAvailable)
                    {
                        response = CAL_MGR_MR_READY_YES;
                    }
                    else if (TRUE == pCalUpdate->LiftLeverInfo.InRaiseDetent)
                    {
                        pCurveFitInfo->EnforceRaiseDetent = TRUE;
                        response = CAL_MGR_MR_READY_YES;
                    }
                    else
                    {
                        response = CAL_MGR_MR_READY_NO;
                    }
                    break;
                }

                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_VEL_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_2):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_3):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_2):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_3):
                {
                    /* Set the calibration overrides */
                    LpsCalSetLiftOverrides(pCalCfg->CalSlowRaiseCmd, 0.0);
                    if(FALSE == pCalUpdate->LiftLeverInfo.LeverInfoAvailable)
                    {
                        response = CAL_MGR_MR_READY_YES;
                    }
                    else if (TRUE == pCalUpdate->LiftLeverInfo.InLowerDetent)
                    {
                        pCurveFitInfo->EnforceLowerDetent = TRUE;
                        response = CAL_MGR_MR_READY_YES;
                    }
                    else
                    {
                        response = CAL_MGR_MR_READY_NO;
                    }
                    break;
                }

                default:
                {
                    /* Set the calibration overrides */
                    LpsCalSetLiftOverrides(pCalCfg->CalSlowRaiseCmd, pCalCfg->CalFastLowerCmd);
                    response = CAL_MGR_MR_READY_YES;
                    break;
                }
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_READY - resp %d iStep %d", response, pCurveFitInfo->InternalStep);

            return response;
        }

        case (CAL_MGR_MC_SAMPLE_INIT):
        {
            switch (pCurveFitInfo->InternalStep)
            {
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_1):
                {
                    if (LpsCalWrkTbl.Cfg.EEFIMUCalEnable) {
                        // start tilt overrides
                        LpsCalStartTiltOverrides();

                    }
                    LpsCalStartRaiseCalData(LpsCalSlowBottomHeight, LpsCalSlowTopHeight, NULL);
                    break;
                    }

                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_2):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_3):
                {
                    LpsCalStartRaiseCalData(LpsCalSlowBottomHeight, LpsCalSlowTopHeight, NULL);
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_2):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_3):
                {
                    LpsCalStartLowerCalData(LpsCalSlowBottomHeight, LpsCalSlowTopHeight, NULL);
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_VEL_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_2):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_3):
                {
                    LpsCalStartRaiseCalData(LpsCalFastBottomHeight, LpsCalFastTopHeight, &pCurveFitInfo->RaiseSlowFitResultsFinal);
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_VEL_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_2):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_3):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_2):
                default:
                {
                    break;
                }
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_SAMPLE_INIT - CAL_MGR_MR_SAMPLE_INIT_OK iStep %d", pCurveFitInfo->InternalStep);

            return (CAL_MGR_MR_SAMPLE_INIT_OK);
        }

        case (CAL_MGR_MC_SAMPLE):
        {
            CAL_MGR_MR_E response;

            if (CAL_MGR_KEY_YES)
            {
                /* delete all current warnings */
                //cal_mgr_clear_warnings();
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "LeverInfoAvailable %d CAL_MGR_KEY_CONT %d iStep %d",
                    pCalUpdate->LiftLeverInfo.LeverInfoAvailable,
                    CAL_MGR_KEY_CONT,
                    pCurveFitInfo->InternalStep);

            switch (pCurveFitInfo->InternalStep)
            {
                case (LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_2):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_3):
                {
                    LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalFastLowerCmd);
                    if ((FALSE == pCalUpdate->LiftLeverInfo.LeverInfoAvailable ||
                         TRUE == pCalUpdate->LiftLeverInfo.InCenter) &&
                        (CAL_MGR_KEY_CONT))
                    {
                        response = CAL_MGR_MR_SAMPLE_PT_COLLECTED;
                    }
                    else
                    {
                        response = CAL_MGR_MR_SAMPLE_WAIT;
                    }
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_2):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_3):
                {
                    // wait for unrack to proceed if IMU cals are enabled
                    if ((LpsCalWrkTbl.Cfg.EEFIMUCalEnable) && (!pCalInfo->CalTiltOverrideComplete)) {
                            response = CAL_MGR_MR_SAMPLE_WAIT;
                            break;
                    }
                    else if ((LpsCalWrkTbl.Cfg.EEFIMUCalEnable) && (pCalInfo->CalTiltOverrideComplete) &&
                            (pCalInfo->CalTiltOverrideFail)) {
                        // we failed tilt override, proceed to validate to fail the cal
                        response = CAL_MGR_MR_SAMPLE_PT_COLLECTED;
                        break;
                    }
                    else {
                        LpsCalSetLiftOverrides(pCalCfg->CalSlowRaiseCmd, pCalCfg->CalFastLowerCmd);
                    }

                    if (TRUE == pCalInfo->CalRaiseComplete &&
                        (pCalUpdate->LiftCylLengthNorm.Val > LpsCalTopStagingHeight))
                    {
                        response = CAL_MGR_MR_SAMPLE_PT_COLLECTED;
                    }
                    else
                    {
                        response = CAL_MGR_MR_SAMPLE_WAIT;
                    }
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_VEL_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_2):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_3):
                {
                    LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalFastLowerCmd);
                    if (TRUE == pCalInfo->CalRaiseComplete &&
                        (pCalUpdate->LiftCylLengthNorm.Val > LpsCalTopStagingHeight))
                    {
                        response = CAL_MGR_MR_SAMPLE_PT_COLLECTED;
                    }
                    else
                    {
                        response = CAL_MGR_MR_SAMPLE_WAIT;
                    }
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_2):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_3):
                {
                    LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalSlowLowerCmd);
                    if (TRUE == pCalInfo->CalLowerComplete &&
                        (LpsCalWrkTbl.Update.LiftCylLengthNorm.Val < LpsCalBottomStagingHeight))
                    {
                        if (!LpsCalIMUDataCompute()) {
                            // compute is not done yet, wait
                            response = CAL_MGR_MR_SAMPLE_WAIT;
                        }
                        else {
                            // we are done or compute is not supported, continue
                            response = CAL_MGR_MR_SAMPLE_PT_COLLECTED;
                        }
                    }
                    else
                    {
                        response = CAL_MGR_MR_SAMPLE_WAIT;
                    }
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_VEL_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_1):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_2):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_3):
                {
                    LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalFastLowerCmd);
                    if (LpsCalWrkTbl.Update.LiftCylLengthNorm.Val <LpsCalBottomStagingHeight)
                    {
                        response = CAL_MGR_MR_SAMPLE_PT_COLLECTED;
                    }
                    else
                    {
                        response = CAL_MGR_MR_SAMPLE_WAIT;
                    }
                    break;
                }
                default:
                {
                    LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalFastLowerCmd);
                    response = CAL_MGR_MR_SAMPLE_PT_COLLECTED;
                    break;
                }
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_SAMPLE - resp %d iStep %d", response, pCurveFitInfo->InternalStep);

            return response;
        }

        case (CAL_MGR_MC_RESET_INIT):
        {
           LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_RESET_INIT iStep %d", pCurveFitInfo->InternalStep);
           return (CAL_MGR_MR_RESET_INIT_NONE);
        }

        case (CAL_MGR_MC_RESET):
        {
           LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_RESET iStep %d", pCurveFitInfo->InternalStep);
           return(CAL_MGR_MR_RESET_DONE);
        }

        case(CAL_MGR_MC_VALIDATE):
        {
            CAL_MGR_MR_E response;

            switch (pCurveFitInfo->InternalStep)
            {
                case (LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_1):
                {
                    pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_VEL_1; //LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_1;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_2):
                {
                    pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_1; //LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_1;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_3):
                {
                    pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_1; //LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_1;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_1):
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    if (pCalCfg->EEFIMUCalEnable && pCalInfo->CalTiltOverrideFail)
                    {
                        response = CAL_MGR_MR_VALIDATE_NOT_OK;
                    }
                    else
                    {
                        LPS_CAL_CURVE_FIT_STAT stat = LpsCalGetRaiseCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1);
                        if (LPS_CAL_CURVE_FIT_STAT_PRESS_0 == stat) {
                            *CalError = LPS_CAL_ERROR_LIFT_PRESS_0;
                            response = CAL_MGR_MR_VALIDATE_NOT_OK;
                        }
                        else {
                            pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_1;
                            response = CAL_MGR_MR_VALIDATE_OK;
                        }
                    }
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_2):
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    LpsCalGetRaiseCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp2);
                    if (LpsCalCompareCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp2, TRUE))
                    {
                        LpsCalCombineCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp2,
                                &pCurveFitInfo->RaiseSlowFitResultsFinal);

                        pCurveFitInfo->RaiseSlowFitDone = TRUE;
                    }
                    pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_2;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_3):
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    if (FALSE == pCurveFitInfo->RaiseSlowFitDone)
                    {
                        LpsCalGetRaiseCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp3);
                        if (LpsCalCompareCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp3, TRUE))
                        {
                            LpsCalCombineCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp3,
                                    &pCurveFitInfo->RaiseSlowFitResultsFinal);

                            pCurveFitInfo->RaiseSlowFitDone = TRUE;
                        }
                        else if (LpsCalCompareCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp2, &pCurveFitInfo->RaiseFitResultsTemp3, TRUE))
                        {
                            LpsCalCombineCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp2, &pCurveFitInfo->RaiseFitResultsTemp3,
                                    &pCurveFitInfo->RaiseSlowFitResultsFinal);

                            pCurveFitInfo->RaiseSlowFitDone = TRUE;
                        }
                        else
                        {
                            pCurveFitInfo->RaiseFitResultsTemp1 = pCurveFitInfo->RaiseFitResultsTemp2;
                            pCurveFitInfo->RaiseFitResultsTemp2 = pCurveFitInfo->RaiseFitResultsTemp3;
                        }
                    }
                    pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_3;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_1):
                {
                    pCurveFitInfo->EnforceLowerDetent = FALSE;
                    LpsCalIMUDataGet(&pitch_offset, &lumped_weight);
                    pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightTemp1 = lumped_weight;
                    pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetTemp1 = pitch_offset;
                    LpsCalGetLowerCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp1);
                    pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_2;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_2):
                {
                    pCurveFitInfo->EnforceLowerDetent = FALSE;
                    LpsCalIMUDataGet(&pitch_offset, &lumped_weight);
                    pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightTemp2 = lumped_weight;
                    pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetTemp2 = pitch_offset;
                    LpsCalGetLowerCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp2);
                    if (LpsCalCompareCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp1, &pCurveFitInfo->LowerFitResultsTemp2, FALSE))
                    {
                        LpsCalCombineCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp1, &pCurveFitInfo->LowerFitResultsTemp2,
                                &pCurveFitInfo->LowerSlowFitResultsFinal);

                        pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetFinal =
                                LpsCalCalculateIMUFinalOffset(pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetTemp1,
                                        pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetTemp2);

                        pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightFinal =
                                (pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightTemp1 +
                                        pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightTemp2)/2.f;

                        pCurveFitInfo->LowerSlowFitDone = TRUE;
                    }

                    if ((TRUE == pCurveFitInfo->RaiseSlowFitDone) && (TRUE == pCurveFitInfo->LowerSlowFitDone))
                    {
                        pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_3;
                    }
                    else
                    {
                        pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_3;
                    }
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_3):
                {
                    pCurveFitInfo->EnforceLowerDetent = FALSE;
                    if (FALSE == pCurveFitInfo->LowerSlowFitDone)
                    {
                        LpsCalIMUDataGet(&pitch_offset, &lumped_weight);
                        pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightTemp3 = lumped_weight;
                        pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetTemp3 = pitch_offset;
                        LpsCalGetLowerCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp3);
                        if (LpsCalCompareCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp1, &pCurveFitInfo->LowerFitResultsTemp3, FALSE))
                        {
                            LpsCalCombineCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp1, &pCurveFitInfo->LowerFitResultsTemp3,
                                    &pCurveFitInfo->LowerSlowFitResultsFinal);

                            pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetFinal =
                                    LpsCalCalculateIMUFinalOffset(pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetTemp1,
                                            pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetTemp3);

                            pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightFinal =
                                    (pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightTemp1 +
                                            pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightTemp3) / 2.f;

                            pCurveFitInfo->LowerSlowFitDone = TRUE;
                        }
                        else if (LpsCalCompareCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp2, &pCurveFitInfo->LowerFitResultsTemp3, FALSE))
                        {
                            LpsCalCombineCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp2, &pCurveFitInfo->LowerFitResultsTemp3,
                                    &pCurveFitInfo->LowerSlowFitResultsFinal);

                            pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetFinal =
                                    LpsCalCalculateIMUFinalOffset(pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetTemp2,
                                            pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetTemp3);

                            pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightFinal =
                                    (pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightTemp2 +
                                            pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightTemp3) / 2.f;

                            pCurveFitInfo->LowerSlowFitDone = TRUE;
                        }
                        else
                        {
                            pCurveFitInfo->LowerFitResultsTemp1 = pCurveFitInfo->LowerFitResultsTemp2;
                            pCurveFitInfo->LowerFitResultsTemp2 = pCurveFitInfo->LowerFitResultsTemp3;
                            pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetTemp1 = pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetTemp2;
                            pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetTemp2 = pCurveFitInfo->LpsCalIMUResultsData.EmptySlowImuOffsetTemp3;
                            pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightTemp1= pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightTemp2;
                            pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightTemp2 = pCurveFitInfo->LpsCalIMUResultsData.EmptySlowLumpedWeightTemp3;
                        }
                    }

                    if ((TRUE == pCurveFitInfo->RaiseSlowFitDone) && (TRUE == pCurveFitInfo->LowerSlowFitDone))
                    {
                        pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_3;
                    }
                    else
                    {
                        pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_3;
                    }

                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_VEL_1):
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    LpsCalGetRaiseCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1);
                    pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_VEL_1;
                    pCurveFitInfo->RaiseFastVelDone = TRUE;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_1):
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    LpsCalGetRaiseCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1);
                    pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_1;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_2):
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    LpsCalGetRaiseCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp2);
                    if (LpsCalCompareCurveFitResultRatios(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp2, TRUE))
                    {
                        LpsCalCombineCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp2,
                                &pCurveFitInfo->RaiseFastFitResultsFinal);

                        pCurveFitInfo->RaiseFastFitDone = TRUE;
                    }
                    pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_2;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_3):
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    LpsCalGetRaiseCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp3);
                    if (LpsCalCompareCurveFitResultRatios(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp3, TRUE))
                    {
                        LpsCalCombineCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp3,
                                &pCurveFitInfo->RaiseFastFitResultsFinal);

                        pCurveFitInfo->RaiseFastFitDone = TRUE;
                    }
                    else if (LpsCalCompareCurveFitResultRatios(&pCurveFitInfo->RaiseFitResultsTemp2, &pCurveFitInfo->RaiseFitResultsTemp3, TRUE))
                    {
                        LpsCalCombineCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp2, &pCurveFitInfo->RaiseFitResultsTemp3,
                                &pCurveFitInfo->RaiseFastFitResultsFinal);

                        pCurveFitInfo->RaiseFastFitDone = TRUE;
                    }
                    else
                    {
                        pCurveFitInfo->RaiseFitResultsTemp1 = pCurveFitInfo->RaiseFitResultsTemp2;
                        pCurveFitInfo->RaiseFitResultsTemp2 = pCurveFitInfo->RaiseFitResultsTemp3;
                    }
                    pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_3;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_VEL_1):
                {
                    pCurveFitInfo->EnforceLowerDetent = FALSE;
                    pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_2;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_1):
                {
                    pCurveFitInfo->EnforceLowerDetent = FALSE;
                    pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_2;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_2):
                case (LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_3):
                {
                    pCurveFitInfo->EnforceLowerDetent = FALSE;
                    if (TRUE == pCurveFitInfo->RaiseFastFitDone)
                    {
                        pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_END;
                    }
                    else
                    {
                        pCurveFitInfo->InternalStep = LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_3;
                    }
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                default:
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    pCurveFitInfo->EnforceLowerDetent = FALSE;
                    response = CAL_MGR_MR_VALIDATE_RESTART;
                    break;
                }
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_VALIDATE - resp %d iStep %d", response, pCurveFitInfo->InternalStep);

            return response;
        }

        case (CAL_MGR_MC_NEXT_PT):
        {
            CAL_MGR_MR_E response;

            if (LPS_CAL_EMPTY_CAL_INT_STEP_END == pCurveFitInfo->InternalStep)
            {
                response = CAL_MGR_MR_NEXT_PT_NO_MORE;
            }
            else
            {
                response = CAL_MGR_MR_NEXT_PT_MORE;
            }

            if (pCalCfg->AutoCalsEnabled) {
                *StepNo = LpsCalTranslateStep(pCurveFitInfo->InternalStep, LpsAutoEmptyCalStepsMapping, LPS_AUTO_CAL_EMPTY_CAL_STEPS_MAPPING_NUM_ENTRIES);
            }
            else {
                *StepNo = LpsCalTranslateStep(pCurveFitInfo->InternalStep, LpsManualEmptyCalStepsMapping, LPS_MANUAL_CAL_EMPTY_CAL_STEPS_MAPPING_NUM_ENTRIES);
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_NEXT_PT - resp %d step %d  iStep %d", response, *StepNo, pCurveFitInfo->InternalStep);

            return response;
        }

        case(CAL_MGR_MC_DONE):
        {
           LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_DONE iStep %d", pCurveFitInfo->InternalStep);
           return(CAL_MGR_MR_DONE_OK);
        }

        case(CAL_MGR_MC_FAIL):
        {
           LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FAIL iStep %d", pCurveFitInfo->InternalStep);
           return(CAL_MGR_MR_FAIL_OK);
        }

        default:
        {
           LpsCalPrint(LPSCAL_LOG_WARNING, "Unhandled command in LpsCalEmptyCalMain: %d", (int)Cmd);
           break;
        }

    } //end switch

    LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MR_SUCCESS iStep %d", pCurveFitInfo->InternalStep);
    return(CAL_MGR_MR_SUCCESS);

} // end cal main


/******************************************************************************
FUNCTION NAME: LpsCalFullCalMain
DESCRIPTION: Full bucket calibration main function called by the cal manager.
PARAMETER DESCRIPTION:
RETURN VALUE: CAL_MGR_MR_E
*******************************************************************************/
/*
CAL_MGR_MR_E LpsCalFullCalMain(CAL_MGR_MC_E            Cmd,
                                CAL_MGR_Work_t         *Cmw,
                                CAL_MGR_Cnfg_t   const *Cmc,
                                CAL_MGR_Cal_t          *Cal)
*/

CAL_MGR_MR_E LpsCalFullCalMain(CAL_MGR_MC_E          Cmd,
                                unsigned_16             CalId,
                                unsigned_8*             StepNo,
                                unsigned_16*         CalError)

{
    CAL_MGR_Cal_t calMgrCal;
    calMgrCal.id = CalId;
    CAL_MGR_Cal_t* Cal = &calMgrCal;
    LpsCalCfg_t* pCalCfg = &LpsCalWrkTbl.Cfg;
    LpsCalNvmTbl_t* pCalNvm = &LpsCalWrkTbl.Nvm;
    LpsCalUpdate_t* pCalUpdate = &LpsCalWrkTbl.Update;
    LpsCalStatus_t* pCalStatus = &LpsCalWrkTbl.Status;
    LpsCalInfo_t* pCalInfo = &LpsCalWrkTbl.Info;
    LpsCalCurveFitInfo_t* pCurveFitInfo = &LpsCalWrkTbl.CurveFitInfo;
    boolean *pCalEnabled = LpsCalWrkTbl.Cfg.CalEnableFlg;
    float pitch_offset = 0.f;
    float lumped_weight = 0.f;

    /*if(LPS_CAL_UPDT_SUCCESS != LpsCalWrkTbl.UpdateErr)
    {
        return LpsCalWrkTbl.UpdateErr;
    }*/

    //(void)Cmc;

    *CalError = 0;

    LpsCalPrint(LPSCAL_LOG_WAYPOINT, "Cmd %d CalId %d StepNo %d iStep %d CalCount %d CalError %d",
                Cmd, CalId, StepNo, pCurveFitInfo->InternalStep, CalCount, *CalError);

    switch(Cmd)
    {
        /* This is the first thing called */
        case (CAL_MGR_MC_INIT_LAST_STAT):
        {
            if (Cal->id != LpsCalWrkTbl.FullWtCal.wId)
            {
               LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INIT_LAST_STAT - CAL_MGR_MR_INIT_LAST_STAT_NS iStep %d", pCurveFitInfo->InternalStep);
               return (CAL_MGR_MR_INIT_LAST_STAT_NS);
            }
            else
            {
                LpsCalResetCurveFitInfo();
                ((CAL_MGR_LStat_t *)Cal)->stat = (cal_last_stat_t*)&LpsCalWrkTbl.FullWtCal;
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INIT_LAST_STAT - CAL_MGR_MR_INIT_LAST_STAT_OK iStep %d", pCurveFitInfo->InternalStep);
                return (CAL_MGR_MR_INIT_LAST_STAT_OK);
            }
        }

         /* This is the second thing called */
        case (CAL_MGR_MC_INITIALIZE):
        {
            LpsCalPrint(LPSCAL_LOG_INFO, "------------------FULL CAL---------------");

            if ((NULL != pCalEnabled) && (FALSE == *pCalEnabled))
            {
                //cal_add_error(LPS_CAL_NOT_SUPPORTED);
                *CalError = LPS_CAL_NOT_SUPPORTED;
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INITIALIZE - CAL_MGR_MR_INITIALIZE_NOT_OK iStep %d", pCurveFitInfo->InternalStep);
                return CAL_MGR_MR_INITIALIZE_NOT_OK;
            }

            if(LPS_CAL_INIT_SUCCESS != LpsCalWrkTbl.InitErr)
            {
                //cal_add_error(LpsCalWrkTbl.InitErr);
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INITIALIZE - LpsCalWrkTbl.InitErr - CAL_MGR_MR_INITIALIZE_NOT_OK  iStep %d", pCurveFitInfo->InternalStep);
                return  CAL_MGR_MR_INITIALIZE_NOT_OK;
            }

            /* Fail calibrations if machine/model is not selected */
            if(LPS_STATUS_BAD == LpsCalWrkTbl.Cfg.MachineModelCfg)
            {
                *CalError = LPS_CAL_MACHINE_MODEL_NOT_SET;
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INITIALIZE - pCalCfg->MachineModelCfg - CAL_MGR_MR_INITIALIZE_NOT_OK  iStep %d", pCurveFitInfo->InternalStep);
                return CAL_MGR_MR_INITIALIZE_NOT_OK;
            }

            /* Fail calibrations if Legal for Trade is Sealed */
            if (pCalUpdate->LegalForTradeSealed) {
                *CalError = LPS_CAL_PAYLOAD_LEGAL_FOR_TRADE_SEALED;
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INITIALIZE - pCalUpdate->LegalForTradeSealed - CAL_MGR_MR_INITIALIZE_NOT_OK  iStep %d", pCurveFitInfo->InternalStep);
                return CAL_MGR_MR_INITIALIZE_NOT_OK;
            }

            /* Set full lift cal complete flags to FALSE */
            pCurveFitInfo->OldCalFlags = pCalNvm->CalStatus;
            pCalNvm->CalStatus &= ~CAL_VELCAL;
            //pCalNvm->CalStat &= ~LPS_CAL_VELCAL_2PT;
            pCalNvm->CalStatus &= ~CAL_FULL_BKT_CURVE_MASK;

            pCalNvm->CalStatus &= ~CAL_BKT_WT_MASK;
            pCalStatus->FullBktCalDone = FALSE;

            pCalStatus->CalInProgress = TRUE;

            LpsCalWrkTbl.EnableQualRead = TRUE;

            if (NULL != pCalCfg->QualReadEnableOrDisable)
            {
                pCalCfg->QualReadEnableOrDisable(LPS_CAL_QUAL_READ_ENABLE, &HydOilTempMin);
            }

            pCurveFitInfo->HydOilTempMet = FALSE;
            pCurveFitInfo->EnforceRaiseDetent = FALSE;
            pCurveFitInfo->EnforceLowerDetent = FALSE;
            pCurveFitInfo->RaiseFastVelDone = FALSE;
            pCurveFitInfo->RaiseSlowFitDone = FALSE;
            pCurveFitInfo->RaiseFastFitDone = FALSE;
            pCurveFitInfo->LowerSlowFitDone = FALSE;

            /* Reset Tilt Overrides */
            LpsCalResetTiltOverrides();

            pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_START;

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INITIALIZE - CAL_MGR_MR_INITIALIZE_OK iStep %d", pCurveFitInfo->InternalStep);

            return (CAL_MGR_MR_INITIALIZE_OK);
        }

        /* Called at the beginning of setup check (conditional) and flow */
        case (CAL_MGR_MC_ADIAGCHK):
        {
            CAL_MGR_MR_E response = CAL_MGR_MR_ADIAGCHK_OK;

            if ((NULL != pCalEnabled) && (FALSE == *pCalEnabled))
            {
                *CalError = LPS_CAL_NOT_SUPPORTED;
                response = CAL_MGR_MR_ADIAGCHK_NOT_OK;
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_ADIAGCHK - CAL_MGR_MR_ADIAGCHK_NOT_OK iStep %d", pCurveFitInfo->InternalStep);
                return response;
            }

            if ((LPS_STATUS_BAD == pCalUpdate->LiftDiffPress.Stat) ||
                (LPS_STATUS_BAD == pCalUpdate->LiftCylLengthNorm.Stat) ||
                (LPS_HYD_OIL_TEMP_STATUS_BAD == pCalUpdate->HydOilTemp.Stat) ||
                (LPS_STATUS_BAD == pCalUpdate->LiftCylVel.Stat) ||
                (LPS_STATUS_BAD == pCalUpdate->TiltCylLengthNorm.Stat) ||
                (LPS_STATUS_BAD == pCalUpdate->TiltAngleABCPercent.Stat) ||
                (LPS_STATUS_BAD == pCalUpdate->BktAngle.Stat) ||
                (LPS_STATUS_BAD == pCalUpdate->ReferenceIMUData.Stat) ||
                (FALSE != pCalUpdate->VoltageEventActive) ||
                ((pCalCfg->AutoCalsEnabled) && LPS_STATUS_BAD == pCalUpdate->EngineSpeed.Stat) ||
                (TRUE == pCalUpdate->LiftLeverInfo.LeverInfoAvailable &&
                 TRUE == pCalUpdate->LiftLeverInfo.Faulted) ||
                 (LpsCalWrkTbl.Cfg.EEFIMUCalEnable &&
                         (LPS_STATUS_BAD == pCalUpdate->EEFIMUData.Stat ||
                                 LPS_STATUS_BAD == pCalUpdate->TiltHePressure.Stat ||
                                 LPS_STATUS_BAD == pCalUpdate->TiltRePressure.Stat)))
            {
                *CalError = LPS_CAL_ERROR_ACTIVE_DIAG;
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_ADIAGCHK - CAL_MGR_MR_ADIAGCHK_NOT_OK iStep %d", pCurveFitInfo->InternalStep);
                response = CAL_MGR_MR_ADIAGCHK_NOT_OK;
            }

            return response;
        }

        case (CAL_MGR_MC_SETUPCHK):
        {
            CAL_MGR_MR_E response;

            if (LPS_HYD_OIL_TEMP_STATUS_DISABLED == pCalUpdate->HydOilTemp.Stat) {
                pCurveFitInfo->HydOilTempMet = TRUE;
            }
            else {
                if (pCalUpdate->HydOilTemp.Val >= (float_32)(LPS_CAL_OIL_TEMP_MIN + 10.0)) {
                    pCurveFitInfo->HydOilTempMet = TRUE;
                }
                else if (pCalUpdate->HydOilTemp.Val < (float_32)(LPS_CAL_OIL_TEMP_MIN)) {
                    pCurveFitInfo->HydOilTempMet = FALSE;
                }
            }

            /* Stay here in setup check until all conditions are met */
            if (FALSE == pCurveFitInfo->HydOilTempMet)
            {
                pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_HYD_OIL;
                response = CAL_MGR_MR_SETUPCHK_NOT_OK;
            }
            else if ((pCalUpdate->DumpState != LPS_WEIGHT_BKT_FULLY_RACKED) && (!pCalInfo->CalTiltOverrideComplete))
            {
                pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_RACK_POS;
                response = CAL_MGR_MR_SETUPCHK_NOT_OK;
            }
            else if (pCalUpdate->LiftCylLengthNorm.Val > LpsCalBottomStagingHeight)
            {
                pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_LOWER_POS;
                response = CAL_MGR_MR_SETUPCHK_NOT_OK;
            }
            else if ( (pCalCfg->AutoCalsEnabled) &&
                (pCalUpdate->EngineSpeed.Val < PCS_CAL_ENGINE_HIGH_IDLE_RPM))
            {
                pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_ENG_SPD;
                response = CAL_MGR_MR_SETUPCHK_NOT_OK;
            }
            else
            {
                if ((TRUE == pCurveFitInfo->RaiseSlowFitDone) && (TRUE == pCurveFitInfo->LowerSlowFitDone))
                {
                    pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_3;
                }
                else if(TRUE == pCurveFitInfo->RaiseFastVelDone || pCalCfg->AutoCalsEnabled)
                {
                    pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_2;
                }
                else
                {
                    pCurveFitInfo->RaiseSlowFitDone = FALSE;
                    pCurveFitInfo->RaiseFastFitDone = FALSE;
                    pCurveFitInfo->LowerSlowFitDone = FALSE;

                    /* Skipping the raise fast velocity step, it is not used. */
                    pCurveFitInfo->RaiseFastVelDone = TRUE;
                    pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_2;
                }

                response = CAL_MGR_MR_SETUPCHK_OK;
            }

            if (pCalCfg->AutoCalsEnabled) {
                *StepNo = LpsCalTranslateStep(pCurveFitInfo->InternalStep, LpsAutoFullCalStepsMapping, LPS_AUTO_CAL_FULL_CAL_STEPS_MAPPING_NUM_ENTRIES);
            }
            else {
                *StepNo = LpsCalTranslateStep(pCurveFitInfo->InternalStep, LpsManualFullCalStepsMapping, LPS_MANUAL_CAL_FULL_CAL_STEPS_MAPPING_NUM_ENTRIES);
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_SETUPCHK - resp %d step %d iStep %d", response, *StepNo, pCurveFitInfo->InternalStep);

            return response;
        }

        case (CAL_MGR_MC_INIT_FLOW):
        {
            /* Start the calibration overrides
                Once overrides are started, we do not allow normal, unlimited,
                operator control until the calibration routine is finished.
            */
            LpsCalStartLiftOverrides();

            /* Initialize override limits */
            LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalFastLowerCmd);

            pCurveFitInfo->EnforceRaiseDetent = FALSE;
            pCurveFitInfo->EnforceLowerDetent = FALSE;

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_INIT_FLOW - CAL_MGR_MR_INIT_FLOW_OK iStep %d", pCurveFitInfo->InternalStep);

            return (CAL_MGR_MR_INIT_FLOW_OK);
        }

        case (CAL_MGR_MC_FLOW):
        {
            CAL_MGR_MR_E response;

            /* Check persistent setup conditions */
            if ((LPS_HYD_OIL_TEMP_STATUS_DISABLED != pCalUpdate->HydOilTemp.Stat) &&
                    (pCalUpdate->HydOilTemp.Val < (float_32)(LPS_CAL_OIL_TEMP_MIN)))
            {
                pCurveFitInfo->HydOilTempMet = FALSE;
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FLOW - Line no %d iStep %d", __LINE__, pCurveFitInfo->InternalStep);
                response = CAL_MGR_MR_FLOW_RESTART;
            }
            else if (pCalUpdate->DumpState != LPS_WEIGHT_BKT_FULLY_RACKED && !LpsCalWrkTbl.Cfg.EEFIMUCalEnable)
            {
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FLOW - Line no %d iStep %d", __LINE__, pCurveFitInfo->InternalStep);
                response = CAL_MGR_MR_FLOW_RESTART;
            }
            else if ( (pCalCfg->AutoCalsEnabled) &&
                (pCalUpdate->EngineSpeed.Val < PCS_CAL_ENGINE_HIGH_IDLE_RPM))
            {
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FLOW - Line no %d iStep %d", __LINE__, pCurveFitInfo->InternalStep);
                response = CAL_MGR_MR_FLOW_RESTART;
            }
            else if (pCalInfo->CalTiltOverrideComplete && pCalInfo->CalTiltOverrideFail)
            {
                /* Tilt override was attempted but unsuccessful, fail the cal */
                LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FLOW - Line no %d iStep %d", __LINE__, pCurveFitInfo->InternalStep);
                response = CAL_MGR_MR_FLOW_ABORT;
            }
            else
            {
                if ((LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_1 == pCurveFitInfo->InternalStep) ||
                    (LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_2 == pCurveFitInfo->InternalStep) ||
                    (LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_3 == pCurveFitInfo->InternalStep))
                {
                    if (pCalUpdate->LiftCylLengthNorm.Val > LpsCalBottomStagingHeight)
                    {
                       LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FLOW %d - pCalUpdate->LiftCylLenghtNorm.Val > LpsCalBottomStagingHeight iStep %d", __LINE__, pCurveFitInfo->InternalStep);
                       response = CAL_MGR_MR_FLOW_RESTART;
                    }
                    else
                    {
                        response = CAL_MGR_MR_FLOW_OK;
                    }
                }
                else if ((TRUE ==  pCurveFitInfo->EnforceRaiseDetent) &&
                         (TRUE == pCalUpdate->LiftLeverInfo.LeverInfoAvailable &&
                          FALSE == pCalUpdate->LiftLeverInfo.InRaiseDetent))
                {
                    LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FLOW - Line no %d  iStep %d", __LINE__, pCurveFitInfo->InternalStep);

                    /* stop any tilt overrides that may be happening */
                    LpsCalStopTiltOverrides();

                    response = CAL_MGR_MR_FLOW_RESTART;
                }
                else if ((TRUE == pCurveFitInfo->EnforceLowerDetent) &&
                         (TRUE == pCalUpdate->LiftLeverInfo.LeverInfoAvailable &&
                          FALSE == pCalUpdate->LiftLeverInfo.InLowerDetent))
                {
                   LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FLOW - Line no %d  iStep %d", __LINE__, pCurveFitInfo->InternalStep);
                   response = CAL_MGR_MR_FLOW_RESTART;
                }
                else
                {
                    response = CAL_MGR_MR_FLOW_OK;
                }
            }

            return response;
        }

         /* All of the different ways to exit flow */
        case (CAL_MGR_MC_RESTART_FLOW):
        case (CAL_MGR_MC_EXIT_FLOW):
        {
            CAL_MGR_MR_E response;

            LpsCalStopLiftOverrides();
            LpsCalStopTiltOverrides();

            /* Re-initialize override limits */
            LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalFastLowerCmd);

            if (CAL_MGR_MC_EXIT_FLOW == Cmd)
            {
                response = CAL_MGR_MR_EXIT_FLOW_DONE;
            }
            else /* CAL_MGR_MC_RESTART_FLOW == Cmd */
            {
                response = CAL_MGR_MR_RESTART_FLOW_OK;
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_RESTART_FLOW or CAL_MGR_MC_EXIT_FLOW - resp %d iStep %d", response, pCurveFitInfo->InternalStep);

            return response;
        }

        /* All of the different ways to exit the calibration */
        case (CAL_MGR_MC_STOP):
        case (CAL_MGR_MC_QUIT):
        case (CAL_MGR_MC_TERMINATE):
        case (CAL_MGR_MC_SUCCESS):
        {
            CAL_MGR_MR_E response;
            /* Estimate a default calibration weight and empty bucket weight */
            float_32 emptyPressure;
            float_32 fullPressure;
            float_32 deltaPressure;
            float_32 tempPressure;
            float_32 emptyRaisePressure;
            float_32 emptyLowerPressure;
            float_32 fullRaisePressure;
            float_32 fullLowerPressure;

            /* Stop the calibration overrides */
            LpsCalStopLiftOverrides();
            LpsCalStopTiltOverrides();

            /* Disable the qualified read */
            LpsCalWrkTbl.EnableQualRead = FALSE;

            if (NULL != pCalCfg->QualReadEnableOrDisable)
            {
                pCalCfg->QualReadEnableOrDisable(LPS_CAL_QUAL_READ_DISABLE, &HydOilTempMin);
            }

            if (CAL_MGR_MC_SUCCESS == Cmd)
            {
                pCalNvm->FullBktSlowRaiseSpd = pCurveFitInfo->RaiseSlowFitResultsFinal.AverageVelocity;
                pCalNvm->FullBktFastRaiseSpd = pCurveFitInfo->RaiseFastFitResultsFinal.AverageVelocity;
                pCalNvm->FastRaiseFullBktDeltaPres = pCurveFitInfo->RaiseFastFitResultsFinal.AverageDeltaPFromReference;

                // Store the x,y,z acceleration vector.
                pCalNvm->SlowRaiseFullIMUAccel[0] = pCurveFitInfo->RaiseFastFitResultsFinal.AryAverageIMUAccel[0];
                pCalNvm->SlowRaiseFullIMUAccel[1] = pCurveFitInfo->RaiseFastFitResultsFinal.AryAverageIMUAccel[1];
                pCalNvm->SlowRaiseFullIMUAccel[2] = pCurveFitInfo->RaiseFastFitResultsFinal.AryAverageIMUAccel[2];
                pCalNvm->SlowRaiseFullPitch = pCurveFitInfo->RaiseFastFitResultsFinal.AveragePitch;
                pCalNvm->SlowRaiseFullRoll = pCurveFitInfo->RaiseFastFitResultsFinal.AverageRoll;

                {
                    unsigned_8 ii;
                    for (ii = 0; ii < LPS_CAL_CURVE_FIT_NUM_POINTS; ii++)
                    {
                        pCalNvm->SlowRaiseFullBktLiftHt[ii] = pCurveFitInfo->RaiseSlowFitResultsFinal.AryPosition[ii];
                        pCalNvm->SlowRaiseFullBktLiftPres[ii] = pCurveFitInfo->RaiseSlowFitResultsFinal.AryPressure[ii];
                        pCalNvm->SlowLowerFullBktLiftHt[ii] = pCurveFitInfo->LowerSlowFitResultsFinal.AryPosition[ii];
                        pCalNvm->SlowLowerFullBktLiftPres[ii] = pCurveFitInfo->LowerSlowFitResultsFinal.AryPressure[ii];

                        LpsCalPrint(LPSCAL_LOG_INFO, "pCalNvm->SlowRaiseFullBktLiftHt[%d] %f \
                                                      pCalNvm->SlowRaiseFullBktLiftPres[%d] %f \
                                                      pCalNvm->SlowLowerFullBktLiftHt[%d] %f \
                                                      pCalNvm->SlowLowerFullBktLiftPres[%d] %f",
                                                      ii, pCalNvm->SlowRaiseFullBktLiftHt[ii],
                                                      ii, pCalNvm->SlowRaiseFullBktLiftPres[ii],
                                                      ii, pCalNvm->SlowLowerFullBktLiftHt[ii],
                                                      ii, pCalNvm->SlowLowerFullBktLiftPres[ii]);
                    }
                }

                if (LPS_HYD_OIL_TEMP_STATUS_DISABLED == pCalUpdate->HydOilTemp.Stat) {
                    pCalNvm->FullTemp = 0.0;
                }
                else {
                    pCalNvm->FullTemp = pCalUpdate->HydOilTemp.Val;
                }

                /* On successful Full bucket cal, reset Zero weight and Simple cal factor */
                pCalNvm->ZeroWeight = 0.0f;
                pCalNvm->CalAdjust = 0.0f;

                { /* Clear the advanced calibration adjustment table */
                    unsigned_8 ii;
                    for (ii = 0; ii < LPS_CAL_ADV_CAL_ADJUST_NUM_POINTS; ++ii)
                    {
                        pCalNvm->AdvCalAdjustX[ii] = NAN;
                        pCalNvm->AdvCalAdjustY[ii] = NAN;
                    }
                }

                pCalNvm->CalStatus |= CAL_VELCAL;
                pCalNvm->CalStatus |= CAL_FULL_BKT_CURVE_MASK;

                /* On successful Full bucket cal, reset CalWt */
                pCalNvm->CalStatus &= ~CAL_BKT_WT_MASK;

                emptyRaisePressure = LpsLookupExtrap(50.0, pCalNvm->SlowRaiseEmptyBktLiftHt,
                                    pCalNvm->SlowRaiseEmptyBktLiftPres, LPS_CAL_CURVE_FIT_NUM_POINTS);
                emptyLowerPressure = LpsLookupExtrap(50.0, pCalNvm->SlowLowerEmptyBktLiftHt,
                                    pCalNvm->SlowLowerEmptyBktLiftPres, LPS_CAL_CURVE_FIT_NUM_POINTS);
                fullRaisePressure = LpsLookupExtrap(50.0, pCalNvm->SlowRaiseFullBktLiftHt,
                                    pCalNvm->SlowRaiseFullBktLiftPres, LPS_CAL_CURVE_FIT_NUM_POINTS);
                fullLowerPressure = LpsLookupExtrap(50.0, pCalNvm->SlowLowerFullBktLiftHt,
                                    pCalNvm->SlowLowerFullBktLiftPres, LPS_CAL_CURVE_FIT_NUM_POINTS);
                pCalNvm->CalWeight = 0.0f;

                tempPressure = emptyRaisePressure + emptyLowerPressure;
                if (tempPressure > 0)
                {
                   emptyPressure = ((float_32)2.0 * emptyRaisePressure * emptyLowerPressure) / tempPressure;
                }
                else
                {
                   emptyPressure = 0.0;
                }

                tempPressure = fullRaisePressure + fullLowerPressure;
                if (tempPressure > 0)
                {
                   fullPressure = ((float_32)2.0 * fullRaisePressure * fullLowerPressure) / tempPressure;
                }
                else
                {
                   fullPressure = 0.0;
                }

                deltaPressure = fullPressure - emptyPressure;
                if (deltaPressure > 0)
                {
                    float_32 lastPayloadWeight = (pCalCfg->KgPerKpaAtMidExtension * deltaPressure) / (float_32)1000.0;

                    /* Limit to eventual data range */
                    if (lastPayloadWeight > LPS_CAL_MAX_WEIGHT) {
                        lastPayloadWeight = LPS_CAL_MAX_WEIGHT;
                    }
                    else if (lastPayloadWeight < LPS_CAL_MIN_WEIGHT) {
                        lastPayloadWeight = LPS_CAL_MIN_WEIGHT;
                    }

                    pCalInfo->LastPayloadWeight = lastPayloadWeight;
                }
                else {
                    pCalInfo->LastPayloadWeight = LPS_CAL_MIN_WEIGHT;
                }

                if (pCalCfg->LiftCylHeKpaWithoutBktAtMidExtn > 0)
                {
                    tempPressure = emptyPressure - pCalCfg->LiftCylHeKpaWithoutBktAtMidExtn;
                    if (tempPressure > 0)
                    {
                        pCalNvm->EmptyBucketWeightEst = (pCalCfg->KgPerKpaAtMidExtension * tempPressure) / (float_32)1000.0;
                    }
                    else
                    {
                        pCalNvm->EmptyBucketWeightEst = 0.0;
                    }
                }
                else
                {
                    pCalNvm->EmptyBucketWeightEst = 0.0;
                }

                LpsCalPrint(LPSCAL_LOG_INFO, "pCalNvm->EmptyBucketWeightEst %f", pCalNvm->EmptyBucketWeightEst);

                LpsCalWrkTbl.FullWtCal.lHourMeter = LpsCalWrkTbl.Update.ServiceHourMeter;
                pCalNvm->ShmFullMain = LpsCalWrkTbl.FullWtCal.lHourMeter;

                pCalNvm->CalVersion = LPS_CAL_VERSION_LATEST;
                pCalCfg->UpdateNvm(pCalNvm);

                LpsCalPrint(LPSCAL_LOG_INFO, "pCalNvm->EmptyBucketWeightEst %f pCalInfo->LastPayloadWeight %f",
                        pCalNvm->EmptyBucketWeightEst, pCalInfo->LastPayloadWeight);

                response = CAL_MGR_MR_SUCCESS_SAVED;

                pCalStatus->FullBktCalDone = TRUE;
            }
            else
            {
                pCalNvm->CalStatus = pCurveFitInfo->OldCalFlags;
                if (CAL_MGR_MC_TERMINATE == Cmd)
                {
                    /* Exit flow is required next to turn off the overrides */
                    response = CAL_MGR_MR_TERMINATE_EXIT_REQ;
                }
                else if (CAL_MGR_MC_QUIT == Cmd)
                {
                    response = CAL_MGR_MR_QUIT_EXIT_REQ;
                }
                else if (CAL_MGR_MC_STOP == Cmd)
                {
                    response = CAL_MGR_MR_STOP_EXIT_REQ;
                }
                else
                {
                    response = CAL_MGR_MR_SUCCESS;
                }
            }

            pCalStatus->CalInProgress = FALSE;

            return response;
        }
        case (CAL_MGR_MC_CLEANUP):
        {
           LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_CLEANUP Line no %d iStep %d", __LINE__, pCurveFitInfo->InternalStep);
           return (CAL_MGR_MR_CLEANUP_DONE);
        }

        case (CAL_MGR_MC_READY):
        {
            CAL_MGR_MR_E response;

            /* Wait for the operator to put the lever into the proper detent position */
            switch (pCurveFitInfo->InternalStep)
            {
                case (LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_2):
                case (LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_3):
                {
                   LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalFastLowerCmd);
                    response = CAL_MGR_MR_READY_YES;
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_VEL_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_2):
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_3):
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_2):
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_3):
                {
                    /* Set the calibration overrides */
                    LpsCalSetLiftOverrides(0.0, pCalCfg->CalFastLowerCmd);
                    if(FALSE == pCalUpdate->LiftLeverInfo.LeverInfoAvailable)
                    {
                        response = CAL_MGR_MR_READY_YES;
                    }
                    else if (TRUE == pCalUpdate->LiftLeverInfo.InRaiseDetent)
                    {
                        pCurveFitInfo->EnforceRaiseDetent = TRUE;
                        response = CAL_MGR_MR_READY_YES;
                    }
                    else
                    {
                        response = CAL_MGR_MR_READY_NO;
                    }
                    break;
                }

                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_VEL_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_2):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_3):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_2):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_3):
                {
                    /* Set the calibration overrides */
                    LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, 0.0);
                    if(FALSE == pCalUpdate->LiftLeverInfo.LeverInfoAvailable)
                    {
                        response = CAL_MGR_MR_READY_YES;
                    }
                    else if (TRUE == pCalUpdate->LiftLeverInfo.InLowerDetent)
                    {
                        pCurveFitInfo->EnforceLowerDetent = TRUE;
                        response = CAL_MGR_MR_READY_YES;
                    }
                    else
                    {
                        response = CAL_MGR_MR_READY_NO;
                    }
                    break;
                }

                default:
                {
                    /* Set the calibration overrides */
                    LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalFastLowerCmd);
                    response = CAL_MGR_MR_READY_YES;
                    break;
                }
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_READY - resp %d LeverInfoAvailable %d iStep %d",
                    response, pCalUpdate->LiftLeverInfo.LeverInfoAvailable, pCurveFitInfo->InternalStep);

            return response;
        }

        case (CAL_MGR_MC_SAMPLE_INIT):
        {
            switch (pCurveFitInfo->InternalStep)
            {
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_1):
                {
                    if (LpsCalWrkTbl.Cfg.EEFIMUCalEnable) {
                         // start tilt overrides
                         LpsCalStartTiltOverrides();
                     }
                     LpsCalStartRaiseCalData(LpsCalSlowBottomHeight, LpsCalSlowTopHeight, NULL);
                     break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_2):
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_3):
                {
                    LpsCalStartRaiseCalData(LpsCalSlowBottomHeight, LpsCalSlowTopHeight, NULL);
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_2):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_3):
                {
                    LpsCalStartLowerCalData(LpsCalSlowBottomHeight, LpsCalSlowTopHeight, NULL);
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_VEL_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_2):
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_3):
                {
                    LpsCalStartRaiseCalData(LpsCalFastBottomHeight, LpsCalFastTopHeight, &pCurveFitInfo->RaiseSlowFitResultsFinal);
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_VEL_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_2):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_3):
                case (LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_2):
                default:
                {
                    break;
                }
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_SAMPLE_INIT - CAL_MGR_MR_SAMPLE_INIT_OK iStep %d", pCurveFitInfo->InternalStep);

            return (CAL_MGR_MR_SAMPLE_INIT_OK);
        }

        case (CAL_MGR_MC_SAMPLE):
        {
            CAL_MGR_MR_E response;

            if (CAL_MGR_KEY_YES)
            {
                /* delete all current warnings */
                //cal_mgr_clear_warnings();
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "LeverInfoAvailable %d CAL_MGR_KEY_CONT %d iStep %d",
                                pCalUpdate->LiftLeverInfo.LeverInfoAvailable,
                                CAL_MGR_KEY_CONT,
                                pCurveFitInfo->InternalStep);

            switch (pCurveFitInfo->InternalStep)
            {
                case (LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_2):
                case (LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_3):
                {
                    LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalFastLowerCmd);

                    if ((FALSE == pCalUpdate->LiftLeverInfo.LeverInfoAvailable ||
                         TRUE == pCalUpdate->LiftLeverInfo.InCenter) &&
                        (CAL_MGR_KEY_CONT))
                    {
                        response = CAL_MGR_MR_SAMPLE_PT_COLLECTED;
                    }
                    else
                    {
                        response = CAL_MGR_MR_SAMPLE_WAIT;
                    }
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_2):
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_3):
                {
                    // wait for unrack to proceed if IMU cals are enabled
                    if ((LpsCalWrkTbl.Cfg.EEFIMUCalEnable) && (!pCalInfo->CalTiltOverrideComplete)) {
                            response = CAL_MGR_MR_SAMPLE_WAIT;
                            break;
                    }
                    else if ((LpsCalWrkTbl.Cfg.EEFIMUCalEnable) && (pCalInfo->CalTiltOverrideComplete) &&
                            (pCalInfo->CalTiltOverrideFail)) {
                        // we failed tilt override, proceed to validate to fail the cal
                        response = CAL_MGR_MR_SAMPLE_PT_COLLECTED;
                        break;
                    }
                    else {
                        LpsCalSetLiftOverrides(pCalCfg->CalSlowRaiseCmd, pCalCfg->CalFastLowerCmd);
                    }

                    if (TRUE == pCalInfo->CalRaiseComplete &&
                            (pCalUpdate->LiftCylLengthNorm.Val > LpsCalTopStagingHeight))
                    {
                        response = CAL_MGR_MR_SAMPLE_PT_COLLECTED;
                    }
                    else
                    {
                        response = CAL_MGR_MR_SAMPLE_WAIT;
                    }
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_VEL_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_2):
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_3):
                {
                    LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalFastLowerCmd);

                    if (TRUE == pCalInfo->CalRaiseComplete &&
                        (pCalUpdate->LiftCylLengthNorm.Val > LpsCalTopStagingHeight))
                    {
                        response = CAL_MGR_MR_SAMPLE_PT_COLLECTED;
                    }
                    else
                    {
                        response = CAL_MGR_MR_SAMPLE_WAIT;
                    }
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_2):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_3):
                {
                    LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalSlowLowerCmd);

                    if (TRUE == pCalInfo->CalLowerComplete &&
                        (LpsCalWrkTbl.Update.LiftCylLengthNorm.Val < LpsCalBottomStagingHeight))
                    {
                        if (!LpsCalIMUDataCompute()) {
                            // compute is not done yet, wait
                            response = CAL_MGR_MR_SAMPLE_WAIT;
                        }
                        else {
                            // we are done or compute is not supported, continue
                            response = CAL_MGR_MR_SAMPLE_PT_COLLECTED;
                        }
                    }
                    else
                    {
                        response = CAL_MGR_MR_SAMPLE_WAIT;
                    }
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_VEL_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_1):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_2):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_3):
                {
                    LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalFastLowerCmd);

                    if (LpsCalWrkTbl.Update.LiftCylLengthNorm.Val < LpsCalBottomStagingHeight)
                    {
                        response = CAL_MGR_MR_SAMPLE_PT_COLLECTED;
                    }
                    else
                    {
                        response = CAL_MGR_MR_SAMPLE_WAIT;
                    }
                    break;
                }
                default:
                {
                    LpsCalSetLiftOverrides(pCalCfg->CalFastRaiseCmd, pCalCfg->CalFastLowerCmd);
                    response = CAL_MGR_MR_SAMPLE_PT_COLLECTED;
                    break;
                }
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_SAMPLE - resp %d iStep %d", response, pCurveFitInfo->InternalStep);

            return response;
        }

        case (CAL_MGR_MC_RESET_INIT):
        {
           LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_RESET_INIT iStep %d", pCurveFitInfo->InternalStep);
           return (CAL_MGR_MR_RESET_INIT_NONE);
        }

        case (CAL_MGR_MC_RESET):
        {
           LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_RESET iStep %d", pCurveFitInfo->InternalStep);
           return(CAL_MGR_MR_RESET_DONE);
        }

        case(CAL_MGR_MC_VALIDATE):
        {
            CAL_MGR_MR_E response;

            switch (pCurveFitInfo->InternalStep)
            {
                case (LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_1):
                {
                    pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_VEL_1; //LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_1;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_2):
                {
                    pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_1; //LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_1;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_3):
                {
                    pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_1; //LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_1;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_1):
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    if (pCalCfg->EEFIMUCalEnable && pCalInfo->CalTiltOverrideFail)
                    {
                        response = CAL_MGR_MR_VALIDATE_NOT_OK;
                    }
                    else
                    {
                        LPS_CAL_CURVE_FIT_STAT stat = LpsCalGetRaiseCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1);
                        if (LPS_CAL_CURVE_FIT_STAT_PRESS_0 == stat) {
                            *CalError = LPS_CAL_ERROR_LIFT_PRESS_0;
                            response = CAL_MGR_MR_VALIDATE_NOT_OK;
                        }
                        else {
                            pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_1;
                            response = CAL_MGR_MR_VALIDATE_OK;
                        }
                    }
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_2):
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    LpsCalGetRaiseCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp2);
                    if (LpsCalCompareCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp2, TRUE))
                    {
                        LpsCalCombineCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp2,
                                &pCurveFitInfo->RaiseSlowFitResultsFinal);

                        pCurveFitInfo->RaiseSlowFitDone = TRUE;
                    }
                    pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_2;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_3):
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    if (FALSE == pCurveFitInfo->RaiseSlowFitDone)
                    {
                        LpsCalGetRaiseCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp3);

                        if (LpsCalCompareCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp3, TRUE))
                        {
                            LpsCalCombineCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp3,
                                    &pCurveFitInfo->RaiseSlowFitResultsFinal);

                            pCurveFitInfo->RaiseSlowFitDone = TRUE;
                        }
                        else if (LpsCalCompareCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp2, &pCurveFitInfo->RaiseFitResultsTemp3, TRUE))
                        {
                            LpsCalCombineCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp2, &pCurveFitInfo->RaiseFitResultsTemp3,
                                    &pCurveFitInfo->RaiseSlowFitResultsFinal);

                            pCurveFitInfo->RaiseSlowFitDone = TRUE;
                        }
                        else
                        {
                            pCurveFitInfo->RaiseFitResultsTemp1 = pCurveFitInfo->RaiseFitResultsTemp2;
                            pCurveFitInfo->RaiseFitResultsTemp2 = pCurveFitInfo->RaiseFitResultsTemp3;
                        }
                    }
                    pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_3;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_1):
                {
                    pCurveFitInfo->EnforceLowerDetent = FALSE;
                    LpsCalGetLowerCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp1);
                    LpsCalIMUDataGet(&pitch_offset, &lumped_weight);
                    pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetTemp1 = pitch_offset;
                    pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightTemp1 = lumped_weight;
                    pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_2;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_2):
                {
                    pCurveFitInfo->EnforceLowerDetent = FALSE;
                    LpsCalGetLowerCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp2);
                    LpsCalIMUDataGet(&pitch_offset, &lumped_weight);
                    pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetTemp2 = pitch_offset;
                    pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightTemp2 = lumped_weight;
                    if (LpsCalCompareCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp1, &pCurveFitInfo->LowerFitResultsTemp2, FALSE))
                    {
                        LpsCalCombineCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp1, &pCurveFitInfo->LowerFitResultsTemp2,
                                &pCurveFitInfo->LowerSlowFitResultsFinal);

                        pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetFinal =
                                LpsCalCalculateIMUFinalOffset(pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetTemp1,
                                        pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetTemp2);

                        pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightFinal =
                                (pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightTemp1 +
                                        pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightTemp2) / 2.f;

                        pCurveFitInfo->LowerSlowFitDone = TRUE;
                    }

                    if ((TRUE == pCurveFitInfo->RaiseSlowFitDone) && (TRUE == pCurveFitInfo->LowerSlowFitDone))
                    {
                        pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_3;
                    }
                    else
                    {
                        pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_3;
                    }
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_3):
                {
                    pCurveFitInfo->EnforceLowerDetent = FALSE;
                    if (FALSE == pCurveFitInfo->LowerSlowFitDone)
                    {
                        LpsCalGetLowerCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp3);
                        LpsCalIMUDataGet(&pitch_offset, &lumped_weight);
                        pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetTemp3 = pitch_offset;
                        pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightTemp3 = lumped_weight;
                        if (LpsCalCompareCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp1, &pCurveFitInfo->LowerFitResultsTemp3, FALSE))
                        {
                            LpsCalCombineCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp1, &pCurveFitInfo->LowerFitResultsTemp3,
                                    &pCurveFitInfo->LowerSlowFitResultsFinal);

                            pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetFinal =
                                    LpsCalCalculateIMUFinalOffset(pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetTemp1,
                                            pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetTemp3);

                            pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightFinal =
                                    (pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightTemp1 +
                                            pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightTemp3) / 2.f;

                            pCurveFitInfo->LowerSlowFitDone = TRUE;
                        }
                        else if (LpsCalCompareCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp2, &pCurveFitInfo->LowerFitResultsTemp3, FALSE))
                        {
                            LpsCalCombineCurveFitResults(&pCurveFitInfo->LowerFitResultsTemp2, &pCurveFitInfo->LowerFitResultsTemp3,
                                    &pCurveFitInfo->LowerSlowFitResultsFinal);

                            pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetFinal =
                                    LpsCalCalculateIMUFinalOffset(pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetTemp2,
                                            pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetTemp3);

                            pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightFinal =
                                    (pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightTemp2 +
                                            pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightTemp3) / 2.f;

                            pCurveFitInfo->LowerSlowFitDone = TRUE;
                        }
                        else
                        {
                            pCurveFitInfo->LowerFitResultsTemp1 = pCurveFitInfo->LowerFitResultsTemp2;
                            pCurveFitInfo->LowerFitResultsTemp2 = pCurveFitInfo->LowerFitResultsTemp3;

                            pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetTemp1 = pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetTemp2;
                            pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetTemp2 = pCurveFitInfo->LpsCalIMUResultsData.FullSlowImuOffsetTemp3;
                            pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightTemp1 = pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightTemp2;
                            pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightTemp2 = pCurveFitInfo->LpsCalIMUResultsData.FullSlowLumpedWeightTemp3;
                        }
                    }

                    if ((TRUE == pCurveFitInfo->RaiseSlowFitDone) && (TRUE == pCurveFitInfo->LowerSlowFitDone))
                    {
                        pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_3;
                    }
                    else
                    {
                        pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_3;
                    }

                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_VEL_1):
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    LpsCalGetRaiseCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1);
                    pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_VEL_1;
                    pCurveFitInfo->RaiseFastVelDone = TRUE;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_1):
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    LpsCalGetRaiseCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1);
                    pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_1;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_2):
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    LpsCalGetRaiseCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp2);
                    if (LpsCalCompareCurveFitResultRatios(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp2, TRUE))
                    {
                        LpsCalCombineCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp2,
                                &pCurveFitInfo->RaiseFastFitResultsFinal);

                        pCurveFitInfo->RaiseFastFitDone = TRUE;
                    }
                    pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_2;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_3):
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    LpsCalGetRaiseCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp3);
                    if (LpsCalCompareCurveFitResultRatios(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp3, TRUE))
                    {
                        LpsCalCombineCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp1, &pCurveFitInfo->RaiseFitResultsTemp3,
                                &pCurveFitInfo->RaiseFastFitResultsFinal);

                        pCurveFitInfo->RaiseFastFitDone = TRUE;
                    }
                    else if (LpsCalCompareCurveFitResultRatios(&pCurveFitInfo->RaiseFitResultsTemp2, &pCurveFitInfo->RaiseFitResultsTemp3, TRUE))
                    {
                        LpsCalCombineCurveFitResults(&pCurveFitInfo->RaiseFitResultsTemp2, &pCurveFitInfo->RaiseFitResultsTemp3,
                                &pCurveFitInfo->RaiseFastFitResultsFinal);

                        pCurveFitInfo->RaiseFastFitDone = TRUE;
                    }
                    else
                    {
                        pCurveFitInfo->RaiseFitResultsTemp1 =  pCurveFitInfo->RaiseFitResultsTemp2;
                        pCurveFitInfo->RaiseFitResultsTemp2 =  pCurveFitInfo->RaiseFitResultsTemp3;
                    }
                    pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_3;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_VEL_1):
                {
                    pCurveFitInfo->EnforceLowerDetent = FALSE;
                    pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_2;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_1):
                {
                    pCurveFitInfo->EnforceLowerDetent = FALSE;
                    pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_2;
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_2):
                case (LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_3):
                {
                    pCurveFitInfo->EnforceLowerDetent = FALSE;
                    if (TRUE == pCurveFitInfo->RaiseFastFitDone)
                    {
                        pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_END;
                    }
                    else
                    {
                        pCurveFitInfo->InternalStep = LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_3;
                    }
                    response = CAL_MGR_MR_VALIDATE_OK;
                    break;
                }
                default:
                {
                    pCurveFitInfo->EnforceRaiseDetent = FALSE;
                    pCurveFitInfo->EnforceLowerDetent = FALSE;
                    response = CAL_MGR_MR_VALIDATE_RESTART;
                    break;
                }
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_VALIDATE - resp %d iStep %d", response, pCurveFitInfo->InternalStep);

            return response;
        }

        case (CAL_MGR_MC_NEXT_PT):
        {
            CAL_MGR_MR_E response;

            if (LPS_CAL_FULL_CAL_INT_STEP_END == pCurveFitInfo->InternalStep)
            {
                response = CAL_MGR_MR_NEXT_PT_NO_MORE;
            }
            else
            {
                response = CAL_MGR_MR_NEXT_PT_MORE;
            }

            if (pCalCfg->AutoCalsEnabled) {
                *StepNo = LpsCalTranslateStep(pCurveFitInfo->InternalStep, LpsAutoFullCalStepsMapping, LPS_AUTO_CAL_FULL_CAL_STEPS_MAPPING_NUM_ENTRIES);
            }
            else {
                *StepNo = LpsCalTranslateStep(pCurveFitInfo->InternalStep, LpsManualFullCalStepsMapping, LPS_MANUAL_CAL_FULL_CAL_STEPS_MAPPING_NUM_ENTRIES);
            }

            LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_NEXT_PT - resp %d step %d  iStep %d", response, *StepNo, pCurveFitInfo->InternalStep);

            return response;
        }

        case(CAL_MGR_MC_DONE):
        {
           LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_DONE iStep %d", pCurveFitInfo->InternalStep);
           return(CAL_MGR_MR_DONE_OK);
        }

        case(CAL_MGR_MC_FAIL):
        {
           LpsCalPrint(LPSCAL_LOG_INFO, "CAL_MGR_MC_FAIL iStep %d", pCurveFitInfo->InternalStep);
           return(CAL_MGR_MR_FAIL_OK);
        }

        default:
        {
           LpsCalPrint(LPSCAL_LOG_WARNING, "Unhandled command in LpsCalFullCalMain: %d", (int)Cmd);
           break;
        }
    } //switch

    return(CAL_MGR_MR_SUCCESS);

} //cal_main

/******************************************************************************
FUNCTION NAME: LpsCalTranslateStep
DESCRIPTION: Retruns mapping cal mgr step for the internal step.
PARAMETER DESCRIPTION:
RETURN VALUE: unsigned_8
*******************************************************************************/
unsigned_8 LpsCalTranslateStep(unsigned_8 InternalStep, const LpsCalStepsMapping_t StepsMapping[], unsigned_8 NumMappings)
{
    unsigned_8 ii;
    unsigned_8 calStep = StepsMapping[NumMappings-1].CalStep;
    for (ii = 0; ii < NumMappings; ii++)
    {
        if (StepsMapping[ii].InternalStep == InternalStep)
        {
            calStep = StepsMapping[ii].CalStep;
            break;
        }
    }
    return calStep;
}

/******************************************************************************
FUNCTION NAME: LpsCalLstatEmptyWtHndlr
DESCRIPTION: Handler function for cal_last_stat_t of empty bucket calibration.
PARAMETER DESCRIPTION:
RETURN VALUE: unsigned_8
*******************************************************************************/
unsigned_8 LpsCalLstatEmptyWtHndlr(unsigned_8 Cmd, struct CAL_LSTAT_T *Work)
{
    (void)Work;
    if(Cmd == CAL_PUSH_STATUS)
    {
        LpsCalNvmTbl_t* pCalNvm = &LpsCalWrkTbl.Nvm;
        LpsCalWrkTbl.EmptyWtCal.lHourMeter = LpsCalWrkTbl.Update.ServiceHourMeter; //clock_getservice_sec();
        pCalNvm->ShmEmptyMain = LpsCalWrkTbl.EmptyWtCal.lHourMeter;
        //nvm_write(pcs_data.workspace.quad_fit, (unsigned_8*) &pcs_nvm_data.quad, sizeof(PCS_QUADRATIC_FIT_CAL), 0);
        //TODO
    }
    return 0;
}

/******************************************************************************
FUNCTION NAME: LpsCalLstatFullWtHndlr
DESCRIPTION: Handler function for cal_last_stat_t of full bucket calibration.
PARAMETER DESCRIPTION:
RETURN VALUE: unsigned_8
*******************************************************************************/
unsigned_8 LpsCalLstatFullWtHndlr(unsigned_8 Cmd, struct CAL_LSTAT_T *Work)
{
    (void)Work;

    if(Cmd == CAL_PUSH_STATUS)
    {
        LpsCalNvmTbl_t* pCalNvm = &LpsCalWrkTbl.Nvm;
        LpsCalWrkTbl.FullWtCal.lHourMeter = LpsCalWrkTbl.Update.ServiceHourMeter; //clock_getservice_sec();
        pCalNvm->ShmFullMain = LpsCalWrkTbl.FullWtCal.lHourMeter;
        //nvm_write(pcs_data.workspace.quad_fit, (unsigned_8*) &pcs_nvm_data.quad, sizeof(PCS_QUADRATIC_FIT_CAL), 0);
        //TODO
    }
    return 0;
}

/******************************************************************************
FUNCTION NAME: LpsCalGetCalStatus
DESCRIPTION: Retuns Calibration status variable structure.
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalGetCalStatus(LpsCalStatus_t *CalStatus)
{
    *CalStatus = LpsCalWrkTbl.Status;
}

/******************************************************************************
FUNCTION NAME: LpsCalCalInProgress
DESCRIPTION: Retuns true if Cal in progress, otherwise false
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
boolean LpsCalCalInProgress(void)
{
    return LpsCalWrkTbl.Status.CalInProgress;
}

/******************************************************************************
FUNCTION NAME: LpsCalGetLastPayloadWeight
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
float_32 LpsCalGetLastPayloadWeight(void)
{
    return LpsCalWrkTbl.Info.LastPayloadWeight;
}

/******************************************************************************
FUNCTION NAME: LpsCalGetQualReadStatus
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE: unsigned_8
*******************************************************************************/
unsigned_8 LpsCalGetQualReadStatus(void)
{
    return LpsCalWrkTbl.EnableQualRead;
}

/******************************************************************************
FUNCTION NAME: LpsCalGetIMUCalOffset
DESCRIPTION: Returns the IMU Calibration Offset after a successful full
             bucket calibration
PARAMETER DESCRIPTION:
RETURN VALUE: float_32
*******************************************************************************/
float_32 LpsCalGetIMUCalOffset(void)
{
    return LpsCalWrkTbl.CurveFitInfo.LpsCalIMUResultsData.FullSlowImuOffsetFinal;
}

static float LpsCalCalculateIMUFinalOffset(float offset1, float offset2)
{
    float final_offset = 0.f;

    if ((isfinite(offset1)) && (isfinite(offset2)))
    {
        // average
        final_offset = (offset1+offset2)/2;
    }
    else if (isfinite(offset1))
    {
        // offset2 is nan, so use offset1
        final_offset = offset1;
    }
    else if (isfinite(offset2)) {
        //offset1 is nan, so use offset2
        final_offset = offset2;
    }
    else
    {
        // both are nan, use 0
        final_offset = 0.f;
    }

    return final_offset;
}
