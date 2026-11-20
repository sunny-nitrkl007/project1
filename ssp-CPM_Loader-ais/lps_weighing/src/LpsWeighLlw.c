/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:LpsWeight
DESCRIPTION: Calculates the low lift weight
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#ifndef __LPS_COMMON_TYPE_DEF_H__
#include <LpsCommonTypeDef.h> /* Contains type definitions of standard datatypes */
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCommonStructures.h> /* Contains structures which are common between all LPS
                                  * system libraries
                  */
#endif

#ifndef  __LPS_COMMON_LOOKUP_TBL_UTILITY_H__
#include <LpsCommonLookUpTblUtility.h>
#endif

#ifndef __LPS_PUBLIC_H__
#include <LpsPublic.h> /*******************************************************/ 
                       /* Containes prototypes of interfaces and functions    */
                       /* which are exported to the application using the     */
                       /* library                                             */
                       /*******************************************************/
#endif

#include "LpsPrivate.h"

#ifndef __CPM_FILTER_H__
#include <cpm_filter.h> /* Contains the functions from CPM Filter library of MAAL */
#endif

#include <string.h>
#include <math.h>
/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
static float_32 LpsCalculateConfidence(float_32 tolerance, float_32 stdev);
/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
/*
 * Temporary Stuff for measuring weight without pitch and roll comp
 */
BSFILT LpsWeighBSOneIMUComp;
BSFILT LpsWeighBSTwoIMUComp;
BSFILT LpsWeighBSThreeIMUComp;
LPFILT2 LpsWeighOptionalWtFilterIMUComp;
/*
 * End temporary stuff
 */


/******************************************************************************
FUNCTION NAME:LpsLowLiftWeighCalc
DESCRIPTION: Low lift weigh calculation is done here. The instantaneous weight raw value is passed through 3 band stop filters to get the filtered instantaneous weight. Now mean and standard variation are calculated and from these values weight confidence is calculated. Upon the confidence value the auto weigh range data is determined, which is the low lift weigh data.
PARAMETER DESCRIPTION:None
RETURN VALUE: None
*******************************************************************************/
void LpsLowLiftWeighCalcUpdate(void)
{
    LpsWeighDigCfg_t *pDigCfg = &LpsWrk.InitTbl.MachSpecificCfg.DigConfig;
    LpsStat_t rawStatus = LpsWrk.InputStatus.rawStatus;
    LpsStat_t debouncedStatus = LpsWrk.InputStatus.debouncedStatus;

    if (LPS_WEIGH_SYSTEM_UNCALIBRATED == LpsGetCalibStatus()) {
        rawStatus = LPS_STATUS_BAD;
        debouncedStatus = LPS_STATUS_BAD;
    }

    if (LPS_STATUS_OK == rawStatus) {
        /* Bandstop filter the pressure to remove resonant frequencies caused by machine and tire mass resonance */
        cpm_filter_band_stop_filter(&LpsWrk.LowLiftWt.BSOne, LpsWrk.InstWtRaw.Val);
        cpm_filter_band_stop_filter(&LpsWrk.LowLiftWt.BSTwo, LpsWrk.LowLiftWt.BSOne.output[0]);
        cpm_filter_band_stop_filter(&LpsWrk.LowLiftWt.BSThree, LpsWrk.LowLiftWt.BSTwo.output[0]);

        /* Optional LPS filter for additional resonance filtering */
        if (LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.WtLpsOptional) {
            cpm_filter_low_pass_filter2(&LpsWrk.LowLiftWt.OptionalWtFilter, LpsWrk.LowLiftWt.BSThree.output[0]);

            /* Calculate the derivative */
            cpm_filter_low_pass_filter(&LpsWrk.LowLiftWt.WtFilter, LpsWrk.LowLiftWt.OptionalWtFilter.y);
            LpsWrk.InstWtDer = LpsWrk.LowLiftWt.WtFilter.yprimestate;

            /* Filtered weight */
            LpsWrk.InstWtLlwFilt = LpsWrk.LowLiftWt.OptionalWtFilter.y;
        }
        else { /* no additional low pass filtering on weight */
            /* Calculate the derivative */
            cpm_filter_low_pass_filter(&LpsWrk.LowLiftWt.WtFilter, LpsWrk.LowLiftWt.BSThree.output[0]);
            LpsWrk.InstWtDer = LpsWrk.LowLiftWt.WtFilter.yprimestate;

            /* Filtered weight */
            LpsWrk.InstWtLlwFilt = LpsWrk.LowLiftWt.BSThree.output[0];
        }

        /* Extract the filtered value */
        LpsWrk.InstWtFilt = LpsWrk.InstWtLlwFilt;

        /*
         * Temporary Stuff for measuring weight without pitch and roll comp
         */
        /* Bandstop filter the pressure to remove resonant frequencies caused by machine and tire mass resonance */
        cpm_filter_band_stop_filter(&LpsWeighBSOneIMUComp, LpsWrk.InstWrRawIMUComp);
        cpm_filter_band_stop_filter(&LpsWeighBSTwoIMUComp, LpsWeighBSOneIMUComp.output[0]);
        cpm_filter_band_stop_filter(&LpsWeighBSThreeIMUComp, LpsWeighBSTwoIMUComp.output[0]);

        /* Optional LPS filter for additional resonance filtering */
        if (LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.WtLpsOptional) {
            cpm_filter_low_pass_filter2(&LpsWeighOptionalWtFilterIMUComp, LpsWeighBSThreeIMUComp.output[0]);

            /* Filtered weight */
            LpsWrk.InstWtFiltIMUComp = LpsWeighOptionalWtFilterIMUComp.y;
        }
        else { /* no additional low pass filtering on weight */
            /* Filtered weight */
            LpsWrk.InstWtFiltIMUComp = LpsWeighBSThreeIMUComp.output[0];
        }
        /*
         * End temporary stuff
         */


        { /* Weight Confidence Calculation */
            /*
             * The prefilter is kind of a hack to try and protect against signal aliasing that was seen near low idle.
             * The calculation of the variance amplifies high frequency noise and if the signal is aliased such that we
             * unfairly get something that looks like high frequency noise (pump piston pass frequency) it makes the
             * variance calculation worse.  The pre-filter chosen just puts a zero at the nyquist frequency with minumum filter delay.
             * This is the same as averaging the most recent two samples.
             */
            float_32 newSample = (LpsWrk.InstWtLlwFilt + LpsWrk.LowLiftWt.LastInput) / (float_32)2.0;
            float_32 lastMeanEst = LpsWrk.LowLiftWt.MeanEst;
            LpsWrk.LowLiftWt.LastInput = LpsWrk.InstWtLlwFilt;
            LpsWrk.LowLiftWt.MeanEst = LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.FilterFactorMean * LpsWrk.LowLiftWt.MeanEst + ((float_32)1.0 - LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.FilterFactorMean) * newSample;
            LpsWrk.LowLiftWt.VarianceEst = LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.FilterFactorVariance * LpsWrk.LowLiftWt.VarianceEst + ((float_32)1.0 - LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.FilterFactorVariance) * ((float_32)1.0 + LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.FilterFactorMean) * (newSample - lastMeanEst) * (newSample - lastMeanEst) / (float_32)2.0;
            LpsWrk.LowLiftWt.StdevEst = (float_32)(sqrt((double_64)LpsWrk.LowLiftWt.VarianceEst));
        }
    
        /* calculation of dig target weight from the machine specific target weight */
        if ((pDigCfg->DigTargetWt >= (float_32)0.0) && (LPS_STATUS_OK == debouncedStatus)) {
            LpsWrk.LowLiftWt.ConfidenceEst = LpsCalculateConfidence(LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.ErrorBand, (LpsWrk.LowLiftWt.StdevEst * (float_32)100.0) / (pDigCfg->DigTargetWt));
        }
        else {
            LpsWrk.LowLiftWt.ConfidenceTimer = 0.0;
            LpsWrk.LowLiftWt.ConfidenceEst = 0.0;
        }

        if ((LPS_LINKAGE_MOVEMENT_STOPPED == LpsWrk.LinkageMovement.lift) ||
                (LPS_LINKAGE_MOVEMENT_NEGATIVE == LpsWrk.LinkageMovement.tilt)) {
            LpsWrk.LowLiftWt.ConfidenceTimer = 0.0;
            LpsWrk.LowLiftWt.ConfidenceEst = 0.0;
        }
        else if (LpsWrk.LowLiftWt.ConfidenceTimer < LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.MinimumConfidenceTime) {
            LpsWrk.LowLiftWt.ConfidenceTimer += LpsWrk.InitTbl.ExecRate;
            LpsWrk.LowLiftWt.ConfidenceEst = 0.0;
        }

        /* Capture the low lift weight */
        if ((LpsWrk.LowLiftWt.ConfidenceEst >= (float_32)LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.AutoWeighRangeConfThr) &&
                (LPS_LINKAGE_MOVEMENT_POSITIVE == LpsWrk.LinkageMovement.lift) &&
                (LpsWrk.UpdtTbl->LiftCylLengthNorm.Val >= (float_32)LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.AutoWeighMinLiftHt) &&
                (LPS_WEIGHT_BKT_FULLY_RACKED == LpsWeighGetDumpState()) &&
                (FALSE == LpsWrk.LpsStallDetect.liftStalled) &&
                (FALSE == LpsWrk.DigDetectData.DigDetected) &&
                (LPS_STATUS_OK == debouncedStatus)) {
            if ((LpsWrk.LowLiftWt.ConfidenceEst >= LpsWrk.LowLiftWt.Confidence) ||
                    (LPS_WEIGH_LLW_STATUS_INVALID == LpsWrk.LowLiftWt.Stat)) {
                LpsWrk.LowLiftWt.Confidence = LpsWrk.LowLiftWt.ConfidenceEst;

                /* Apply the advanced calibration adjust and the zero/span adjust */
                LpsWrk.LowLiftWt.MeanEstComp = LpsZeroSpanAdjust(LpsAdvCalAdjust(LpsWrk.LowLiftWt.MeanEst));
                LpsWrk.LowLiftWt.Wt = LpsWrk.LowLiftWt.MeanEstComp;
            }
            LpsWrk.LowLiftWt.Stat = LPS_WEIGH_LLW_STATUS_VALID;
        }
    }
    else if (LPS_STATUS_BAD == debouncedStatus) {
        cpm_filter_band_stop_filter_reset(&LpsWrk.LowLiftWt.BSOne);
        cpm_filter_band_stop_filter_reset(&LpsWrk.LowLiftWt.BSTwo);
        cpm_filter_band_stop_filter_reset(&LpsWrk.LowLiftWt.BSThree);
        cpm_filter_low_pass_filter2_reset(&LpsWrk.LowLiftWt.OptionalWtFilter);
        cpm_filter_low_pass_filter_reset(&LpsWrk.LowLiftWt.WtFilter, 0);
        LpsWrk.LowLiftWt.WtFilter.init = FALSE;

        /*
         * Temporary Stuff for measuring weight without pitch and roll comp
         */
        cpm_filter_band_stop_filter_reset(&LpsWeighBSOneIMUComp);
        cpm_filter_band_stop_filter_reset(&LpsWeighBSTwoIMUComp);
        cpm_filter_band_stop_filter_reset(&LpsWeighBSThreeIMUComp);
        cpm_filter_low_pass_filter2_reset(&LpsWeighOptionalWtFilterIMUComp);
        /*
         * End temporary stuff
         */

        LpsWrk.InstWtDer = 0.0;
        LpsWrk.InstWtLlwFilt = 0.0;
        LpsWrk.InstWtFilt = 0.0;

        LpsWeighResetLlwWt();
    }
}

/******************************************************************************
FUNCTION NAME:LpsCalculateConfidence
DESCRIPTION: Weight calculation confidence is determined here. Standard deviation is the reciprocal of confidence.
             Using lookup table, tolerance/standard deviation is interpolated with a 2D map.
PARAMETER DESCRIPTION: float_32 tolerance, float_32 stdev
RETURN VALUE: float_32 confidence
*******************************************************************************/
static float_32 LpsCalculateConfidence(float_32 tolerance, float_32 stdev)
{
    float_32 confidence,n;
    if (stdev <= (float_32)0.0) {
        confidence = 1.0;
    }
    else {
        static const float_32 xN[] = { 0.0, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9, 2.1, 2.3, 2.5, 2.7, 3.0, 3.5, 4.0 }; /* Sigma Level */
        static const float_32 yConfidence[] = { 0.0, 0.235822844, 0.382924922, 0.516072694, 0.631879747, 0.728667676, 0.806398927, 0.866385543, 0.910869057, 0.942566872, 0.964271153, 0.978551778, 0.987580668, 0.993066052, 0.997300204, 0.999534742, 1.0 }; /* Confidence */
        n = tolerance / stdev;
        confidence = LpsLookup(n, xN, yConfidence, sizeof(xN)/sizeof(float_32));
    }
    return confidence;
}

/******************************************************************************
FUNCTION NAME:LpsLlwInit
DESCRIPTION: Initializes the filter parameters used for LLW calculation
PARAMETER DESCRIPTION: None
RETURN VALUE: None
*******************************************************************************/



void LpsLlwInit()
{
    cpm_filter_band_stop_filter_init(&LpsWrk.LowLiftWt.BSOne,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.StageOneCf,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.DampingRate,
            LpsWrk.InitTbl.ExecRate);

    cpm_filter_band_stop_filter_init(&LpsWrk.LowLiftWt.BSTwo,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.StageTwoCf,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.DampingRate,
            LpsWrk.InitTbl.ExecRate);

    cpm_filter_band_stop_filter_init(&LpsWrk.LowLiftWt.BSThree,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.StageThreeCf,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.DampingRate,
            LpsWrk.InitTbl.ExecRate);

    cpm_filter_low_pass_filter_init(&LpsWrk.LowLiftWt.WtFilter,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.WtCf,
            LpsWrk.InitTbl.ExecRate);

    /* Optional LPS filter for llw Wt */
    if (LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.WtLpsOptional) {
        cpm_filter_low_pass_filter2_init(&LpsWrk.LowLiftWt.OptionalWtFilter,
                LP_FLT_CF_TO_KFF(LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.WtLpsOptionalCf,
                        LpsWrk.InitTbl.ExecRate));
    }

    /*
     * Temporary Stuff for measuring weight without pitch and roll comp
     */
    cpm_filter_band_stop_filter_init(&LpsWeighBSOneIMUComp,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.StageOneCf,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.DampingRate,
            LpsWrk.InitTbl.ExecRate);

    cpm_filter_band_stop_filter_init(&LpsWeighBSTwoIMUComp,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.StageTwoCf,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.DampingRate,
            LpsWrk.InitTbl.ExecRate);

    cpm_filter_band_stop_filter_init(&LpsWeighBSThreeIMUComp,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.StageThreeCf,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.DampingRate,
            LpsWrk.InitTbl.ExecRate);

    /* Optional LPS filter for llw Wt */
    if (LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.WtLpsOptional) {
        cpm_filter_low_pass_filter2_init(&LpsWeighOptionalWtFilterIMUComp,
                LP_FLT_CF_TO_KFF(LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.WtLpsOptionalCf,
                        LpsWrk.InitTbl.ExecRate));
    }
    /*
     * End temporary stuff
     */

    LpsWeighResetLlwWt();
}

/******************************************************************************
FUNCTION NAME:LpsWeighResetLlwWt
DESCRIPTION: Reset the low lift weigh data to unlatch the current weight
PARAMETER DESCRIPTION: None
RETURN VALUE: None
*******************************************************************************/
void LpsWeighResetLlwWt()
{
    LpsWrk.LowLiftWt.Wt = 0.0;
    LpsWrk.LowLiftWt.Stat = LPS_WEIGH_LLW_STATUS_INVALID;
    LpsWrk.LowLiftWt.ConfidenceTimer = 0.f;
}
