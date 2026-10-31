/*******************************************************************************
** COPYRIGHT (C) 2016-2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:BestBktWt
DESCRIPTION: Finds best bucket weight available for the given weights.


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
#define CALC_METHOD_CONCAT(FilterType, Accracy, SensorType) (((FilterType)<<12) | ((Accracy)<<8) | (0<<4) | (SensorType))

#define CALC_METHOD_NONE (CALC_METHOD_CONCAT(LPS_WEIGH_PCM_PRIMARY_FILTER_TYPE_BUTTERWORTH_LP, LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE, LPS_WEIGH_PCM_SENSOR_TYPE_HPS_HE_RE))
#define CALC_METHOD_WRW (CALC_METHOD_CONCAT(LPS_WEIGH_PCM_PRIMARY_FILTER_TYPE_DYNAMIC_AVG, LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_HIGH, LPS_WEIGH_PCM_SENSOR_TYPE_HPS_HE_RE))
#define CALC_METHOD_WRW_WARN (CALC_METHOD_CONCAT(LPS_WEIGH_PCM_PRIMARY_FILTER_TYPE_DYNAMIC_AVG, LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_MED, LPS_WEIGH_PCM_SENSOR_TYPE_HPS_HE_RE))
#define CALC_METHOD_LLW (CALC_METHOD_CONCAT(LPS_WEIGH_PCM_PRIMARY_FILTER_TYPE_BUTTERWORTH_LP, LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_MED, LPS_WEIGH_PCM_SENSOR_TYPE_HPS_HE_RE))
#define CALC_METHOD_PFW (CALC_METHOD_CONCAT(LPS_WEIGH_PCM_PRIMARY_FILTER_TYPE_BUTTERWORTH_LP, LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_LOW, LPS_WEIGH_PCM_SENSOR_TYPE_HPS_HE_RE))
#define CALC_METHOD_LIVE (CALC_METHOD_CONCAT(LPS_WEIGH_PCM_PRIMARY_FILTER_TYPE_BUTTERWORTH_LP, LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_LOW, LPS_WEIGH_PCM_SENSOR_TYPE_HPS_HE_RE))


/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
LpsWeighBestBktWt_t LpsWeighGetBestAvailableBktWt(void) {
    return LpsWrk.BestBktWt;
}

/*
 * This is continually called during tipoff when not racked so that
 * we can continually look for a new live weight while tipping.
 *
 * This is also called when transitioning weigh states based on user
 * interaction.
 */
void LpsWeighResetBestAvailableBktWt(void)
{
    /*
     * We are just unlatching any latched weights here.
     * We don't need to clear out the weights, we just need
     * to stop holding onto them if given a new weight.
     */
//    LpsWrk.BestBktWt.Wt = 0;
//    LpsWrk.BestBktWt.PayloadCalcMeth = CALC_METHOD_NONE;
//    LpsWrk.BestBktWt.TipoffLiveWeightInUse = FALSE;
    LpsWrk.BestBktWt.Latched = FALSE;

    LpsWeighResetWeighRangeWeight();
    LpsWeighResetLlwWt();
}

void LpsOverloadWeightInit(void)
{
    LpsWrk.OverloadWarnTbl.BucketLoadFactor = 0;
    LpsWrk.OverloadWarnTbl.PrevDigState = LPS_WEIGHT_BKT_NOT_DIGGING;
    LpsWrk.OverloadWarnTbl.DigReverseFlag = FALSE;
    LpsWrk.OverloadWarnTbl.Level = LPS_WEIGH_OVERLOAD_LEVEL_NONE;
    LpsWrk.OverloadWarnTbl.InOverloadRange = FALSE;
}

LpsWeighOverloadLevel_t LpsWeighOverloadWarningLevel(void)
{
    return LpsWrk.OverloadWarnTbl.Level;
}

void LpsWeighBestBktWtInit(void)
{
    LpsWrk.BestBktWt.Wt = 0;
    LpsWrk.BestBktWt.PayloadCalcMeth = CALC_METHOD_NONE;
    LpsWrk.BestBktWt.Accuracy = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE;
    LpsWrk.BestBktWt.Latched = FALSE;
    LpsWrk.BestBktWt.LatchConditionsOK = FALSE;
    LpsWrk.BestBktWt.TipoffLiveWeightInUse = FALSE;
    LpsWeighResetBestAvailableBktWt();
}

void LpsWeighBestBktWtUpdate(void)
{
    LpsWeighOverloadLevel_t OverloadLevel = LPS_WEIGH_OVERLOAD_LEVEL_NONE;
    LpsWeighBestBktWt_t BestBktWt = LpsWrk.BestBktWt;
    LpsStat_t rawStatus = LpsWrk.InputStatus.rawStatus;
    LpsStat_t debouncedStatus = LpsWrk.InputStatus.debouncedStatus;

    if (LPS_WEIGH_SYSTEM_UNCALIBRATED == LpsGetCalibStatus()) {
        rawStatus = LPS_STATUS_BAD;
        debouncedStatus = LPS_STATUS_BAD;
    }

    if (LPS_STATUS_OK == rawStatus) {
        /*
         * if (WRW or LLW are available) {
         *     weight = WRW or LLW
         *     accuracy = high or medium
         *     held = true
         * }
         * else if (TOA has a PFW weight) {
         *     weight = TOA PFW
         *     accuracy = low
         *     held = true
         * }
         * else if (lift is stalled) {
         *     if (have a held weight) {
         *         weight = held weight
         *         accuracy = held accuracy
         *     }
         *     else {
         *         weight = CPM Live Weight
         *         accuracy = none
         *     }
         * }
         * else if ((dumping) or (fully dumped) or (?digging?)) {
         *     if (have a held weight) {
         *         weight = held weight
         *         accuracy = held accuracy
         *     }
         *     else if (TOA has a weight and not RACKED) {
         *         weight = TOA Live Weight
         *         accuracy = low
         *     }
         *     else if (CPM has a weight) {
         *         weight = CPM Live Weight
         *         accuracy = low
         *     }
         *     else {
         *         weight = CPM Live Weight
         *         accuracy = none
         *     }
         * }
         * else if (TOA has a weight and not RACKED) {
         *     weight = TOA Live Weight
         *     accuracy = low
         *     held = true
         * }
         * else if (CPM has a weight) {
         *     weight = CPM Live Weight
         *     accuracy = low
         *     held = true
         * }
         * else if (have a held weight) {
         *     weight = held weight
         *     accuracy = held accuracy
         * }
         * else {
         *     // Don't have a held weight and nobody has a weight to offer
         *     weight = CPM Live Weight
         *     accuracy = none
         * }
         */
        if (LPS_WEIGH_WRW_STATUS_VALID == LpsWrk.WrwTbl.OpTbl.Status) {
            if (LPS_WEIGH_NO_WARNING_ACTIVE == LpsWrk.WrwTbl.OpTbl.Warning) {
                // We use Weigh Range Weigh (WRW) if there are no warnings active
                BestBktWt.Wt = LpsWrk.WrwTbl.OpTbl.Wt;
                BestBktWt.PayloadCalcMeth = CALC_METHOD_WRW;

                if (LpsInitialZeroRequired()) {
                    // If initial zero is required, then don't show high accuracy weight
                    BestBktWt.PayloadCalcMeth = CALC_METHOD_WRW_WARN;
                }
            }
            else if (LPS_WEIGH_LLW_STATUS_VALID == LpsWrk.LowLiftWt.Stat) {
                // We use Low Lift Weigh (LLW) if it is available.
                BestBktWt.Wt = LpsWrk.LowLiftWt.Wt;
                BestBktWt.PayloadCalcMeth = CALC_METHOD_LLW;
            }
            else {
                // Otherwise we use the Weigh Range Weigh (WRW) with warnings.
                BestBktWt.Wt = LpsWrk.WrwTbl.OpTbl.Wt;
                BestBktWt.PayloadCalcMeth = CALC_METHOD_WRW_WARN;
            }

            BestBktWt.TipoffLiveWeightInUse = FALSE;
            BestBktWt.Latched = TRUE;
        }
        else if (LPS_WEIGH_LLW_STATUS_VALID == LpsWrk.LowLiftWt.Stat) {
            // We use Low Lift Weigh (LLW) if it is available.
            BestBktWt.Wt = LpsWrk.LowLiftWt.Wt;
            BestBktWt.PayloadCalcMeth = CALC_METHOD_LLW;
            BestBktWt.TipoffLiveWeightInUse = FALSE;
            BestBktWt.Latched = TRUE;
        }
        else if (LPS_TIPOFF_WEIGHT_PFW == LpsWrk.UpdtTbl->TipoffWeight.Stat) {
            // We are have a Pseudo-Frictionless Weight, use it.
            BestBktWt.Wt = LpsWrk.UpdtTbl->TipoffWeight.Val;
            BestBktWt.PayloadCalcMeth = CALC_METHOD_PFW;
            BestBktWt.TipoffLiveWeightInUse = TRUE;
            BestBktWt.Latched = TRUE;
        }
        else if (FALSE != LpsWrk.LpsStallDetect.liftStalled) {
            // We are stalled... no kind of live weight will do
            if (TRUE == BestBktWt.Latched) {
                // keep the held weight
                // TODO: Why can't we change the weight accuracy to NONE if stalled with live weight?
                // This will keep the pass tracker from having to handle it.
                // This change is not being made at this point in the program, maybe later?
                // BestBktWt.PayloadCalcMeth = CALC_METHOD_NONE;
            }
            else {
                // If we don't have a held weight, we don't know the weight.
                BestBktWt.Wt = LpsWrk.LiveWeighTbl.Wt;
                BestBktWt.PayloadCalcMeth = CALC_METHOD_NONE;
                BestBktWt.TipoffLiveWeightInUse = FALSE;
            }
        }
        else if ((LPS_LINKAGE_MOVEMENT_NEGATIVE == LpsWrk.LinkageMovement.tilt) ||
                (LPS_WEIGHT_BKT_FULLY_DUMPED == LpsWeighGetDumpState()) /* || digging? */) {
            // We are dumping or dumped.  Until we enter tip-off, which drops the currently
            // held weight, we need to hold onto the weight so that we have a "start weight"
            // for the bucket before material starts coming out.
            if (TRUE == BestBktWt.Latched) {
                // keep the held weight
            }
            else if ((LPS_TIPOFF_WEIGHT_INVALID != LpsWrk.UpdtTbl->TipoffWeight.Stat) &&
                    (LPS_WEIGHT_BKT_FULLY_RACKED != LpsWeighGetDumpState())) {
                // We have a TOA live weight
                BestBktWt.Wt = LpsWrk.UpdtTbl->TipoffWeight.Val;
                BestBktWt.PayloadCalcMeth = CALC_METHOD_LIVE;
                BestBktWt.TipoffLiveWeightInUse = TRUE;
            }
            else if (LPS_WEIGH_LIVE_WEIGH_STATUS_VALID == LpsWrk.LiveWeighTbl.Stat) {
                // We have a CPM live weight
                BestBktWt.Wt = LpsWrk.LiveWeighTbl.Wt;
                BestBktWt.PayloadCalcMeth = CALC_METHOD_LIVE;
                BestBktWt.TipoffLiveWeightInUse = FALSE;
            }
            else {
                // We don't have a weight
                BestBktWt.Wt = LpsWrk.LiveWeighTbl.Wt;
                BestBktWt.PayloadCalcMeth = CALC_METHOD_NONE;
                BestBktWt.TipoffLiveWeightInUse = FALSE;
            }
        }
        else if ((LPS_TIPOFF_WEIGHT_INVALID != LpsWrk.UpdtTbl->TipoffWeight.Stat) &&
                (LPS_WEIGHT_BKT_FULLY_RACKED != LpsWeighGetDumpState())) {
            // We have a TOA live weight
            BestBktWt.Wt = LpsWrk.UpdtTbl->TipoffWeight.Val;
            BestBktWt.PayloadCalcMeth = CALC_METHOD_LIVE;
            BestBktWt.TipoffLiveWeightInUse = TRUE;
            BestBktWt.Latched = TRUE;
        }
        else if (LPS_WEIGH_LIVE_WEIGH_STATUS_VALID == LpsWrk.LiveWeighTbl.Stat) {
            // We have a CPM live weight
            BestBktWt.Wt = LpsWrk.LiveWeighTbl.Wt;
            BestBktWt.PayloadCalcMeth = CALC_METHOD_LIVE;
            BestBktWt.TipoffLiveWeightInUse = FALSE;
            BestBktWt.Latched = TRUE;
        }
        else if (TRUE == BestBktWt.Latched) {
            // Keep the held weight
        }
        else {
            // We don't have any weight and we don't have one held.
            // We ran out of sources for weight.
            BestBktWt.Wt = LpsWrk.LiveWeighTbl.Wt;
            BestBktWt.PayloadCalcMeth = CALC_METHOD_NONE;
            BestBktWt.TipoffLiveWeightInUse = FALSE;
        }
    }
    else if (LPS_STATUS_BAD == debouncedStatus) {
        BestBktWt.Wt = 0;
        BestBktWt.PayloadCalcMeth = CALC_METHOD_NONE;
        BestBktWt.TipoffLiveWeightInUse = FALSE;
        BestBktWt.Latched = FALSE;
    }

    // Update the accuracy
    BestBktWt.Accuracy = GET_ACCURACY(BestBktWt.PayloadCalcMeth);

    /*
     * If the weight were dropped right now, would we have a fall-back weight
     * to hold on to?
     *
     * This may lead to a race condition because the conditions may change the
     * very next time we evaluate them, leaving us without any weight.
     *
     * We are guaranteed to get a new held weight if these conditions are true:
     *  - Calibrated and not faulted
     *  - lift is not stalled
     *  - not dumping
     *  - not fully dumped
     *  - CPM has a weight
     */
    if ((LPS_STATUS_OK == rawStatus) &&
            (FALSE == LpsWrk.LpsStallDetect.liftStalled) &&
            (LPS_LINKAGE_MOVEMENT_NEGATIVE != LpsWrk.LinkageMovement.tilt) &&
            (LPS_WEIGHT_BKT_FULLY_DUMPED != LpsWeighGetDumpState()) &&
            (LPS_WEIGH_LIVE_WEIGH_STATUS_VALID == LpsWrk.LiveWeighTbl.Stat)) {
        BestBktWt.LatchConditionsOK = TRUE;
    }
    else {
        BestBktWt.LatchConditionsOK = FALSE;
    }

    { /****** CHECK FOR OVERLOAD WARNINGS ******/
        /*
         * If we are going from Not Digging to Digging, reset the logic for looking for
         * the reverse after the dig.
         */
        if ((LPS_WEIGHT_BKT_DIGGING == LpsWrk.DigDetectData.DigState) &&
                (LPS_WEIGHT_BKT_DIGGING != LpsWrk.OverloadWarnTbl.PrevDigState)) {
            LpsWrk.OverloadWarnTbl.DigReverseFlag = FALSE;
        }
        if (LpsWeighIsRequestedGearReverse()) {
            LpsWrk.OverloadWarnTbl.DigReverseFlag = TRUE;
        }
        /* Assigning current dig state to the previous dig state for next loop */
        LpsWrk.OverloadWarnTbl.PrevDigState = LpsWrk.DigDetectData.DigState;

        //FIX THIS DIVIDE BY ZERO
        if (LpsWrk.UpdtTbl->LoaderBktPayldTrgtWt <= 0.0) {
            LpsWrk.OverloadWarnTbl.BucketLoadFactor = 0.0;
        }
        else {
            LpsWrk.OverloadWarnTbl.BucketLoadFactor = ((BestBktWt.Wt/LpsWrk.UpdtTbl->LoaderBktPayldTrgtWt)*100);
        }

        /* Checking if WRW or LLW */
        if (BestBktWt.Accuracy >= LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_MED) {
            /* Check if there are any reweigh warnings, bucket not racked is a reweigh warning */
            if ((LPS_WEIGH_WRW_STATUS_VALID == LpsWrk.WrwTbl.OpTbl.Status) &&
                    (LPS_WEIGH_WARNING_ACTIVE == LpsWrk.WrwTbl.OpTbl.Warning)) {
                /* don't activate overload with reweigh warnings */
                LpsWrk.OverloadWarnTbl.BucketLoadFactor = 0.0;
            }
            else {
                /*
                 * Either a LLW or a WRW without reweigh warnings,
                 * use calculated bucket load factor for overload detection
                 */
            }
        }
        else if ((LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_LOW == BestBktWt.Accuracy) &&
                (!LpsWrk.OverloadWarnTbl.InOverloadRange)) {
            /* Currently displaying live weight and we were not already overloaded, reset bucket load factor */
            LpsWrk.OverloadWarnTbl.BucketLoadFactor = 0.0;
        }
        else if (LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE == BestBktWt.Accuracy) {
            LpsWrk.OverloadWarnTbl.BucketLoadFactor = 0.0;
        }
        else {
            /*
             * We would get here if we have low accuracy weight and we are already overloaded, we will use
             * the low accuracy weight bucket load factor to see if we still are overloaded
             */
        }

        /*
            Set overload event if bucket weight > 116.5% of Target Weight & Machine in Reverse
            Clear overload event bucket weight < 110% of Target Weight

            PS: We need to make sure that the warnings are not cleared once the
                bucket weight goes above 116.5% till it goes below 110%
         */
        LpsWrk.OverloadWarnTbl.InOverloadRange = ((LpsWrk.OverloadWarnTbl.BucketLoadFactor >= LPS_OVERLOAD_DISABLE_THRESHOLD) &&
                ((LpsWrk.OverloadWarnTbl.BucketLoadFactor > LPS_OVERLOAD_WT_THRESHOLD) ||
                        (TRUE == LpsWrk.OverloadWarnTbl.InOverloadRange))) ? TRUE : FALSE;

        if ((TRUE == LpsWrk.OverloadWarnTbl.DigReverseFlag) &&
                (TRUE == LpsWrk.OverloadWarnTbl.InOverloadRange)) {
            OverloadLevel = LPS_WEIGH_OVERLOAD_LEVEL_WARNING;
        }
    }

    /*
     *  Legal For Trade
     *      Adjust the output bucket weight if Legal For Trade (LFT) is installed
     */
    if (LpsWrk.UpdtTbl->LegalForTradeInstalled) {
        // LFT change Accuracy level from 3 to 2 when LFT installed but not sealed.
        if (!LpsWrk.UpdtTbl->LegalForTradeSealed) {
            if (BestBktWt.Accuracy >= LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_HIGH) {
                BestBktWt.PayloadCalcMeth = SET_ACCURACY(BestBktWt.PayloadCalcMeth, LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_MED);
                BestBktWt.Accuracy = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_MED;
            }
        }

        /*
         * Now we have the weight in tonnes, unrounded.
         * The scale interval (e) in tonnes.
         * The scale capacity in tonnes.
         * The minimum capacity is 10 * e.
         * The maximum high accuracy weight is Max + 9 * e
         */

        // We cannot allow indication > Max + 9 * e
        // In verification mode, we skip this warning because 'e' is so small so +9*e is too limiting
        if ((FALSE == LpsWrk.UpdtTbl->InVerificationMode) &&
                (BestBktWt.Wt > (LpsWrk.UpdtTbl->WeightCapacity + 9 * LpsWrk.UpdtTbl->WeightInterval))) {
            // This is to show to pop-up under any condition that results in
            if (BestBktWt.Accuracy >= LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_MED) {
                /*
                 * Show why we didn't get a weight measurement when expected.
                 * We don't want to show it for live weight because then it could show even when digging.
                 * We don't want to reset the LLW and WRW measurements because this warning would go away immediately.
                 *
                 * NOTE:
                 * - We would like to show it for live weight when in Wait for Dump or tip-off, however, we don't know that here.
                 * - We do want to show overload warning when not in wait for latch.
                 */
                OverloadLevel = LPS_WEIGH_OVERLOAD_LEVEL_SEVERE;
            }

            // If we didn't want it to result in a weight measurement, then we shouldn't have produced
            // a weight measurement to begin with.  If we didn't produce a weight measurement to begin with
            // then we couldn't determine if it was an overload.

            // If we have a pass already in the truck, this weight will get reflected in the truck, leave this alone.
            //BestBktWt.Wt = BestBktWt.Wt;

            // We still have a weight measurement latched, leave it alone.
            //BestBktWt.Latched = BestBktWt.Latched;

            // This is for a few reasons:
            // - The weight measurement is OK, we just can't show it because it is beyond the verified range of the scale.
            // - Don't increment pass count automatically based on MEDIUM or HIGH accuracy.
            // - Show *'s in the bucket (disable weigh indication)
            BestBktWt.PayloadCalcMeth = SET_ACCURACY(BestBktWt.PayloadCalcMeth, LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE);
            BestBktWt.Accuracy = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE;

            // This is so pass count cannot be incremented when reweigh is requested under this conditions.
            // In other words, the reweigh button cannot take you out of "Wait For Latch"
            BestBktWt.LatchConditionsOK = TRUE;
        }

    }

    // Round it to the nearest configured interval
    BestBktWt.Wt = lps_common_weight_round_f(BestBktWt.Wt, LpsWrk.UpdtTbl->WeightInterval);

    // Update final best bucket weight and overload level
    LpsWrk.OverloadWarnTbl.Level = OverloadLevel;
    LpsWrk.BestBktWt = BestBktWt;
}


void LpsLiftStallDetectUpdate()
{
    LpsStat_t rawStatus = LpsWrk.UpdtTbl->LiftCylLengthNorm.Stat;
    LpsStat_t debouncedStatus = LpsWrk.InputStatus.debouncedStatus;

    if (LPS_WEIGH_SYSTEM_UNCALIBRATED == LpsGetCalibStatus()) {
        rawStatus = LPS_STATUS_BAD;
        debouncedStatus = LPS_STATUS_BAD;
    }

    if (LPS_STATUS_OK == rawStatus) {
        /*
         * Check for raise stall
         */
        if (TRUE == LpsWrk.LpsStallDetect.liftRaiseStalled) {
            if (LpsWrk.UpdtTbl->LiftCylLengthNorm.Val < LPS_LIFT_HT_NOT_FULL_RAISE) {
                LpsWrk.LpsStallDetect.liftRaiseStalled = FALSE;
            }
        }
        else {
            if (LpsWrk.UpdtTbl->LiftCylLengthNorm.Val >= LPS_LIFT_HT_CLOSE_TO_FULL_RAISE) {
                LpsWrk.LpsStallDetect.liftRaiseStalled = TRUE;
            }
        }

        /*
         * Check for lower stall
         */
        if (TRUE == LpsWrk.LpsStallDetect.liftLowerStalled) {
            if (LpsWrk.UpdtTbl->LiftCylLengthNorm.Val > LPS_LIFT_HT_NOT_FULL_LOWER) {
                LpsWrk.LpsStallDetect.liftLowerStalled = FALSE;
            }
        }
        else {
            if (LpsWrk.UpdtTbl->LiftCylLengthNorm.Val <= LPS_LIFT_HT_CLOSE_TO_FULL_LOWER) {
                LpsWrk.LpsStallDetect.liftLowerStalled = TRUE;
            }
        }

        /*
         * If either raise or lower are stalled, then lift is stalled
         */
        if ((TRUE == LpsWrk.LpsStallDetect.liftRaiseStalled) ||
                (TRUE == LpsWrk.LpsStallDetect.liftLowerStalled)) {
            LpsWrk.LpsStallDetect.liftStalled = TRUE;
        }
        else {
            LpsWrk.LpsStallDetect.liftStalled = FALSE;
        }
    }
    else if (LPS_STATUS_BAD == debouncedStatus) {
        LpsWrk.LpsStallDetect.liftRaiseStalled = FALSE;
        LpsWrk.LpsStallDetect.liftLowerStalled = FALSE;
        LpsWrk.LpsStallDetect.liftStalled = FALSE;
    }
}

boolean LpsWeighRaiseStallWarningActive(void)
{
    // If we are possible raise stalled...
    if (TRUE == LpsWrk.LpsStallDetect.liftRaiseStalled) {
        // Only warn if we don't have a weight.
        if (LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE == LpsWrk.BestBktWt.Accuracy) {
            return TRUE;
        }
    }

    return FALSE;
}

boolean LpsWeighLowerStallWarningActive(void)
{
    // If we are possible raise stalled...
    if (TRUE == LpsWrk.LpsStallDetect.liftLowerStalled) {
        // Only warn if we don't have a weight.
        if (LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE == LpsWrk.BestBktWt.Accuracy) {
            return TRUE;
        }
    }

    return FALSE;
}


float LpsWeighGetBucketLoadFactor()
{
    return LpsWrk.OverloadWarnTbl.BucketLoadFactor;
}




