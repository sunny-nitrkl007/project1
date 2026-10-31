/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: DigDetect
DESCRIPTION: Dig Detection logic


*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <string.h>

#ifndef __LPS_COMMON_TYPE_DEF_H__
#include <LpsCommonTypeDef.h>
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCommonStructures.h>
#endif

#ifndef __LPS_PUBLIC_H__
#include <LpsPublic.h>
#endif

#include "LpsPrivate.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
# define LPS_WEIGH_MIN_WEIGHT_STABILITY_INDEX (float)1.0
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
/******************************************************************************
FUNCTION NAME:
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
LpsInitErrorTypes_t LpsWeighDigDetectInit(LpsWeighDumpWtBuffer_t DumpWtBuffer)
{
    LpsWeighWtRateChangePtrs_t* pWtRateChangePtrs = &LpsWrk.WtRateChangePtrs;

    if (NULL != DumpWtBuffer.PtrDumpWtBuffer) {
        memset((unsigned_8*)DumpWtBuffer.PtrDumpWtBuffer, 0x00, (DumpWtBuffer.bufferSize * sizeof(float_32)));
    }
    else {
        return LPS_INIT_FAIL;
    }

    pWtRateChangePtrs->MaxSamples = (unsigned_8)(DumpWtBuffer.bufferSize);
    pWtRateChangePtrs->FixedStartPtr = DumpWtBuffer.PtrDumpWtBuffer;
    pWtRateChangePtrs->FixedEndPtr = pWtRateChangePtrs->FixedStartPtr + (pWtRateChangePtrs->MaxSamples - 1);
    pWtRateChangePtrs->StartPtr = DumpWtBuffer.PtrDumpWtBuffer;
    pWtRateChangePtrs->EndPtr = DumpWtBuffer.PtrDumpWtBuffer;

    return LPS_INIT_SUCCESS;
}

/* This is not my favorite code structure of state machine, this can be rewritten much better.
Porting pcs code over as is since not having given enough time to restructure code. */
void LpsWeighDigDetectUpdate(void)
{
    LpsWeighDumpWtChange_t* pDumpWtChangeData = &LpsWrk.DumpWtChangeData;
    LpsWeighDigDetect_t* pDigDetectData = &LpsWrk.DigDetectData;
    LpsWeighDigCfg_t* pDigConfig = &LpsWrk.InitTbl.MachSpecificCfg.DigConfig;
    LpsMachSpecificCfg_t* pMachConfig = &LpsWrk.InitTbl.MachSpecificCfg;
    LpsInitTbl_t* pInitTbl = &LpsWrk.InitTbl;
    LpsUpdtTbl_t* pUpdateTbl = LpsWrk.UpdtTbl;

    if ((LPS_WEIGH_SYSTEM_CALIBRATED == LpsGetCalibStatus()) &&
            (LPS_STATUS_OK == LpsWrk.InputStatus.debouncedStatus)) {
        /* Check if the weight is stable */
        if (pDumpWtChangeData->WtStabilityIndex >= (float_32)LPS_WEIGH_MIN_WEIGHT_STABILITY_INDEX) {
            pDigDetectData->WtStabilized = TRUE;
        }
        else {
            pDigDetectData->WtStabilized = FALSE;
        }

        if (LPS_WEIGHT_BKT_DIG_STATE_UNKNOWN == pDigDetectData->DigState) {
            pDigDetectData->DigState = LPS_WEIGHT_BKT_NOT_DIGGING;
            pDigDetectData->DigStarted = FALSE;
            pDigDetectData->DigDetected = FALSE;
            pDigDetectData->DigDuration = 0;
        }

        /* check if we are detecting a dig */
        else if (LPS_WEIGHT_BKT_NOT_DIGGING == pDigDetectData->DigState) {
            if ((pDumpWtChangeData->DumpCumulativeWtChange < ((pDigConfig->DigStartLimit)*(pDigConfig->DigTargetWt))) &&
                    (TRUE == LpsWeighIsRequestedGearForward()) &&
                    (pUpdateTbl->LiftCylLengthNorm.Val < pMachConfig->StartOfWeigh) &&
                    (pUpdateTbl->LiftCylVel.Val >= pDigConfig->LiftLowerVelocityLimit) &&
                    (FALSE == LpsWeighFullRackDetect())) {
                /* set flag that we might be in dig */
                pDigDetectData->DigState = LPS_WEIGHT_BKT_TENTATIVE_DIGGING;
                pDigDetectData->DigStarted = TRUE;
                pDigDetectData->DigDetected = FALSE;
                pDigDetectData->DigDuration = 0;
            }
        }

        /* if we have started a dig start counting how long before we think it might have ended */
        else if (LPS_WEIGHT_BKT_TENTATIVE_DIGGING == pDigDetectData->DigState) {
            pDigDetectData->DigDuration++;

            /* make sure it hasn't been too long */
            if (pDigDetectData->DigDuration > ((pDigConfig->DigDurationMaxLimit) / pInitTbl->ExecRate)) {
                /* too long, this is not a dig */
                pDigDetectData->DigState =  LPS_WEIGHT_BKT_NOT_DIGGING;
                pDigDetectData->DigStarted = FALSE;
                pDigDetectData->DigDetected = FALSE;
                pDigDetectData->DigDuration = 0;
            }
            else if (pDumpWtChangeData->DumpCumulativeWtChange > ((pDigConfig->DigEndLimit)* (pDigConfig->DigTargetWt))) {
                /* find out if it has been long enough for this to be a dig */
                if (pDigDetectData->DigDuration < ((pDigConfig->DigDurationMinLimit) / pInitTbl->ExecRate)) {
                    /* duration was not long enough, cancel the dig */
                    pDigDetectData->DigState = LPS_WEIGHT_BKT_NOT_DIGGING;
                    pDigDetectData->DigStarted = FALSE;
                    pDigDetectData->DigDetected = FALSE;
                    pDigDetectData->DigDuration = 0;
                }
                else {
                    /* has been the right amount of time, mark as a dig */
                    pDigDetectData->DigState = LPS_WEIGHT_BKT_DIGGING;
                    pDigDetectData->DigStarted = TRUE;
                    pDigDetectData->DigDetected = TRUE;
                    pDigDetectData->DigDuration = 0;
                }
            }
        }

        /* check if we have detected the end of a dig and wait for the weight to settle out or full dump */
        else if (LPS_WEIGHT_BKT_DIGGING == pDigDetectData->DigState) {
            pDigDetectData->DigDuration++;

            /* Check conditions for exiting dig. */
            if (pDigDetectData->WtStabilized || LpsWeighFullDumpDetect() || LpsWeighIsRequestedGearReverse()) {
                pDigDetectData->DigDetected = FALSE;
            }

            /* make sure it's been long enough */
            if (pDigDetectData->DigDuration < ((pDigConfig->DigDurationMinLimit) / pInitTbl->ExecRate)) {
                /*
                 * duration was not long enough, stay here until it's been long enough
                 * this will give a minimum duration in the LPS_WEIGHT_BKT_DIGGING state
                 */
            }
            /* It's been long enough, check exit conditions */
            else if (FALSE == pDigDetectData->DigDetected) {
                pDigDetectData->DigState = LPS_WEIGHT_BKT_NOT_DIGGING;
                pDigDetectData->DigStarted = FALSE;
                pDigDetectData->DigDetected = FALSE;
                pDigDetectData->DigDuration = 0;
            }
            /* make sure it hasn't been too long */
            else if (pDigDetectData->DigDuration > ((pDigConfig->DigDurationMaxLimit) / pInitTbl->ExecRate)) {
                /* too long, this is not a dig */
                pDigDetectData->DigState = LPS_WEIGHT_BKT_NOT_DIGGING;
                pDigDetectData->DigStarted = FALSE;
                pDigDetectData->DigDetected = FALSE;
                pDigDetectData->DigDuration = 0;
            }
        }
    }
    else {
        pDigDetectData->DigState = LPS_WEIGHT_BKT_DIG_STATE_UNKNOWN;
        pDigDetectData->DigStarted = FALSE;
        pDigDetectData->DigDetected = FALSE;
        pDigDetectData->DigDuration = 0;
        pDigDetectData->WtStabilized = FALSE;
    }
}

LpsWeighBktDigStat_t LpsWeighGetDigState(void)
{
    return LpsWrk.DigDetectData.DigState;
}

void LpsWeighEndDig(void)
{
    if (LPS_WEIGHT_BKT_DIG_STATE_UNKNOWN != LpsWrk.DigDetectData.DigState) {
        LpsWrk.DigDetectData.DigState = LPS_WEIGHT_BKT_NOT_DIGGING;
        LpsWrk.DigDetectData.DigDuration = 0;
        LpsWrk.DigDetectData.DigStarted = FALSE;
        LpsWrk.DigDetectData.DigDetected = FALSE;
    }
}
