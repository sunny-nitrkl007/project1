/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: DigDetect
DESCRIPTION: Dig Detection logic


*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
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
#define LPS_WEIGH_MIN_WEIGHT_STABILITY_INDEX (float_32)1.0
#define PCS_DUMP_WT_CHANGE_STARTUP_DELAY (1.2)
#define PCS_DUMP_WT_CHANGE_STABILITY_GAIN (2.0)
#define PCS_DUMP_WT_CHANGE_STABILITY_THRESHOLD (0.03)

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
void LpsWeighDumpWtChangeUpdate(void)
{
    LpsWeighWtRateChangePtrs_t* pWtRateChangePtrs = &LpsWrk.WtRateChangePtrs;
    LpsWeighDumpWtChange_t* pDumpWtChangeData = &LpsWrk.DumpWtChangeData;
    LpsWeighDigCfg_t* pDigConfig = &LpsWrk.InitTbl.MachSpecificCfg.DigConfig;

    LpsStat_t rawStatus = LpsWrk.InputStatus.rawStatus;
    LpsStat_t debouncedStatus = LpsWrk.InputStatus.debouncedStatus;

    if (LPS_WEIGH_SYSTEM_UNCALIBRATED == LpsGetCalibStatus()) {
        rawStatus = LPS_STATUS_BAD;
        debouncedStatus = LPS_STATUS_BAD;
    }

    if (LPS_STATUS_OK == rawStatus) {
        if (FALSE == pDumpWtChangeData->Initialized) {
            pDumpWtChangeData->StartupDelay = (unsigned_16)(((float_32)PCS_DUMP_WT_CHANGE_STARTUP_DELAY / LpsWrk.InitTbl.ExecRate) + (float_32)1.0);
            pDumpWtChangeData->NumSamples = 0;
            pWtRateChangePtrs->StartPtr = pWtRateChangePtrs->FixedStartPtr;
            pWtRateChangePtrs->EndPtr = pWtRateChangePtrs->FixedStartPtr;
            pDumpWtChangeData->DumpCumulativeWtChange = 0.0;
            pDumpWtChangeData->WtStabilityGain = PCS_DUMP_WT_CHANGE_STABILITY_GAIN;
            pDumpWtChangeData->WtStabilityThreshold = PCS_DUMP_WT_CHANGE_STABILITY_THRESHOLD;
            pDumpWtChangeData->WtStabilityIndex = 0.0;
            pDumpWtChangeData->Initialized = TRUE;
        }

        if (pDumpWtChangeData->StartupDelay > 0) {
            pDumpWtChangeData->StartupDelay--;
        }
        else {
            /* Update dump cumulative weight change */
            if (pDumpWtChangeData->NumSamples < pWtRateChangePtrs->MaxSamples) {
                pDumpWtChangeData->DumpCumulativeWtChange = 0.0;
                if (pDumpWtChangeData->NumSamples > 0) {
                    pWtRateChangePtrs->EndPtr++;
                }
                *pWtRateChangePtrs->EndPtr = LpsWrk.InstWtFilt;
                pDumpWtChangeData->NumSamples++;
            }
            else {
                /* Forget the oldest sample and replace it with the newest sample */
                pWtRateChangePtrs->EndPtr = pWtRateChangePtrs->StartPtr;
                if (pWtRateChangePtrs->StartPtr >= pWtRateChangePtrs->FixedEndPtr) {
                    pWtRateChangePtrs->StartPtr = pWtRateChangePtrs->FixedStartPtr;
                }
                else {
                    pWtRateChangePtrs->StartPtr++;
                }

                /* Save the newest sample */
                *pWtRateChangePtrs->EndPtr = LpsWrk.InstWtFilt;

                /* Calculate the dumped weight over the length of the buffer */
                pDumpWtChangeData->DumpCumulativeWtChange = *pWtRateChangePtrs->StartPtr - *pWtRateChangePtrs->EndPtr;
            }

            { /* Update weight stability index */
                float_32 stabilityIncrement;
                float_32 stabilityIndex;
                if (pDigConfig->DigTargetWt > 0) {
                    float_32 tonnesPerSecond = LpsWrk.InstWtDer; /* Rate of change of weight */
                    float_32 pctWtPerSecond = (float_32)(tonnesPerSecond / pDigConfig->DigTargetWt); /* Normalize it to reference weight */
                    if (pctWtPerSecond < 0) {
                        pctWtPerSecond = (float_32)-1.0 * pctWtPerSecond;
                    }

                    stabilityIncrement = (pDumpWtChangeData->WtStabilityGain * ((float_32)1.0 - pctWtPerSecond/ pDumpWtChangeData->WtStabilityThreshold) * LpsWrk.InitTbl.ExecRate);
                }
                else {
                    /* No stability in one loop */
                    stabilityIncrement = -1.0;
                }

                stabilityIndex = pDumpWtChangeData->WtStabilityIndex + stabilityIncrement;
                if (stabilityIndex > (float_32)1.0) {
                    stabilityIndex = 1.0;
                }
                else if (stabilityIndex < (float_32)0.0) {
                    stabilityIndex = 0.0;
                }
                pDumpWtChangeData->WtStabilityIndex = stabilityIndex;
            }
        }
    }
    else if (LPS_STATUS_BAD == debouncedStatus) {
        pDumpWtChangeData->DumpCumulativeWtChange = 0.0;
        pDumpWtChangeData->WtStabilityIndex = 0.0;
        pDumpWtChangeData->Initialized = FALSE;
    }
}



