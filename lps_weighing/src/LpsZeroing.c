/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsZeroing.c
DESCRIPTION:This file provides the method to process the request to adjust the 
            Tare weight of the implement. 
            This is referred to as the zero value or zero function in previous 
            PCS library.
******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <string.h>
#include <math.h>
#include <stdio.h>

#ifndef __LPS_COMMON_TYPE_DEF_H__
/* Contains type definitions of standard datatypes */
#include <LpsCommonTypeDef.h>
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
/* Contains structures which are common between all LPS system libraries  */
#include <LpsCommonStructures.h> 
#endif

#ifndef  __LPS_COMMON_LOOKUP_TBL_UTILITY_H__
#include <LpsCommonLookUpTblUtility.h>
#endif

#ifndef __CPM_FILTER_H__
/* Contains the functions from CPM Filter library of MAAL */
#include <cpm_filter.h>
#endif

#ifndef __LPS_PUBLIC_H__
/* Containes prototypes of interfaces and functions    */
/* which are exported to the application using the     */
/* library                                             */
#include <LpsPublic.h> 
#endif

#include "LpsPrivate.h"

static void LpsWeighZeroNotify(LpsZeroNeededStatus_t zeroNeededStatus);
static boolean LpsWeighHydraulicOilTempChanged();


// Initialize zero function required vairables.
void LpsWeighZeroInit(void)
{
    LpsWrk.ZeroAdjTbl.ZeroTemp = HYDRAULIC_OIL_TEMP_INVALID_DATA;
    LpsWrk.ZeroAdjTbl.ZeroAdjStatus = LPS_ZERO_UPDATE_UNKNOWN_ERROR;
    LpsWrk.ZeroAdjTbl.AutoZeroStatus = LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED;
    LpsWrk.ZeroAdjTbl.InitialZeroRequired = TRUE;

    LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.LastZeroTime = 0;
    LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.PwrOn = TRUE;
    LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.ZeroRequired = FALSE;
    LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.LastSnoozedTime = 0;
    LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.SnoozedStatus = LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED;
}

// Performs the zero adjustment
boolean LpsWeighZeroAdjust(void)
{
    LpsZeroErrorTypes_t ZAStatus;
    boolean zeroAccepted = FALSE;

    // check for calibration complete, can't adjust if not calibrated
    if (LPS_WEIGH_SYSTEM_UNCALIBRATED == LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStatus) {
        ZAStatus = LPS_ZERO_UPDATE_NOT_CALIBRATED;
    }
    // check accuracy of bucket weight, need to be at accepted level to adjust
    else if (!LpsWeighIsZeroWeightAvailable()) {
        ZAStatus = LPS_ZERO_UPDATE_BUCKET_WT_NOT_ACCURATE;
    }
    else {
        // We are calibrated and we have a weight.
        float unzeroedWeight = LpsAdvCalAdjust(LpsWrk.WrwTbl.WkTbl.result.weightAve);
        float zeroMaxLimit = 0.f;
        float zeroMinLimit = 0.f;

        // Calculate the limit
        if (LpsWrk.UpdtTbl->LegalForTradeInstalled) {
            if (LpsInitialZeroRequired()) {
                float previousZeroWeight = 0.f;
                zeroMaxLimit = previousZeroWeight + LpsWrk.UpdtTbl->WeightCapacity * 0.1; // +10%
                zeroMinLimit = previousZeroWeight - LpsWrk.UpdtTbl->WeightCapacity * 0.1; // -10%
            }
            else {
            	float previousZeroWeight = LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.ZeroWeight;
                zeroMaxLimit = previousZeroWeight + LpsWrk.UpdtTbl->WeightCapacity * 0.02; // +2%
                zeroMinLimit = previousZeroWeight - LpsWrk.UpdtTbl->WeightCapacity * 0.02; // -2%
            }
        }
        else {
            zeroMaxLimit = LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalWeight * LpsWrk.InitTbl.MachSpecificCfg.ZeroRangeLimit;
            zeroMinLimit = -LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalWeight * LpsWrk.InitTbl.MachSpecificCfg.ZeroRangeLimit;
        }

        // If the un-zeroed weight is within +/- Max Zero Weight then we can accept this lift
        if ((unzeroedWeight <= zeroMaxLimit) && (unzeroedWeight >= zeroMinLimit)) {
            LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.ZeroWeight = unzeroedWeight;

            // Initial zero has been applied
            LpsWrk.ZeroAdjTbl.InitialZeroRequired = FALSE;

            // Set the last temperature zero variable to the current temperature
            if (LPS_HYD_OIL_TEMP_STATUS_OK == LpsWrk.UpdtTbl->HydOilTemp.Stat) {
                LpsWrk.ZeroAdjTbl.ZeroTemp = LpsWrk.UpdtTbl->HydOilTemp.Val;
            }

            /* Added to stop the ZeroAdjAutoSnooze.PowrOn timer */
            LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.PwrOn = FALSE;
            LpsWeighZeroNotify(LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED); /* Remove zero lift needed EID and reset 4 hour timer */

            LpsWeighResetBestAvailableBktWt();

            zeroAccepted = TRUE;
            ZAStatus = LPS_ZERO_UPDATE_SUCCESS;
        }
        else {
            ZAStatus = LPS_ZERO_UPDATE_TOO_HEAVY_TO_ZERO;
        }
    }

    LpsWrk.ZeroAdjTbl.ZeroAdjStatus = ZAStatus;
    return zeroAccepted;
}

// Calculates when to alert the operator that a zero lift is needed
void LpsWeighAutoZeroUpdate(void)
{
    // Get the current keyon sec clock
    unsigned_32 CurrentTimeSec = LpsWrk.UpdtTbl->ClockKeyonSec;

    // Initialize the powerup time to drive the powerup zero required timer.
    if ((LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.PwrOn) && (0 == LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.LastZeroTime)) {
        LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.LastZeroTime = CurrentTimeSec;
    }

    // Check for calibration complete, can't adjust if not calibrated
    if (LPS_WEIGH_SYSTEM_CALIBRATED == LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStatus) {
        // Is a zero already required?
        if (LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.ZeroRequired) {
            // Zero is already required
            // if warmup lifts are required or initial zero is required, then delay the zero snooze processing
            if (LpsRemainingWarmupLiftsRequired() || LpsInitialZeroRequired()) {
                // do nothing, until warmup lifts are completed and initial zero is completed
            }
            // Snooze it if we are either currently weighing or we are in standby.
            else if ((LpsWrk.WrwTbl.WkTbl.Weighing) || (0 == LpsWrk.UpdtTbl->StandbyActiveState)) {
                /* If there is something to snooze */
                if (LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED != LpsWrk.ZeroAdjTbl.AutoZeroStatus) {
                    /* Snooze this */
                    LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.SnoozedStatus = LpsWrk.ZeroAdjTbl.AutoZeroStatus;
                    LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.LastSnoozedTime = LpsWrk.UpdtTbl->ClockKeyonSec;
                    LpsWrk.ZeroAdjTbl.AutoZeroStatus = LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED;
                }
            }
            // Is there something to unsnooze?
            else if (LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED != LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.SnoozedStatus) {
                // Allow unsnoozing if we are at 0 pass count and the timer has expired
                if (0 == LpsWrk.UpdtTbl->PassCount) {
                    if ((LpsWrk.UpdtTbl->LegalForTradeInstalled) ||
                            (CurrentTimeSec >= (LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.LastSnoozedTime + LPS_ZERO_SNOOZE_INTERVAL))) {
                        // Snooze has expired so restore the snoozed status
                        LpsWrk.ZeroAdjTbl.AutoZeroStatus = LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.SnoozedStatus;
                        LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.SnoozedStatus = LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED;
                    }
                }
            }
        }
        // A zero is not already required, should a new zero be required?
        else if (0 == LpsWrk.UpdtTbl->PassCount) {
            if (LpsWeighHydraulicOilTempChanged()) {
                // Notify operator they needs to zero bucket
                LpsWeighZeroNotify(LPS_ZERO_UPDATE_TEMPERATURE_CHANGE_ZERO_REQUIRED);
            }
            else {
                // Do we need a zero based on time since the last zero?
                unsigned_32 timeInterval;
                if (LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.PwrOn) {
                    if (LpsWrk.UpdtTbl->LegalForTradeInstalled) {
                        timeInterval = 0; // Require zeroing on powerup
                    }
                    else {
                        timeInterval = LpsWrk.InitTbl.MachSpecificCfg.ZeroAdjInitTimeInterval;
                    }
                }
                else if ((LPS_HYD_OIL_TEMP_STATUS_DISABLED == LpsWrk.UpdtTbl->HydOilTemp.Stat) ||
                        (LpsWrk.ZeroAdjTbl.ZeroTemp < HYDRAULIC_OIL_TEMP_MIN_VALID_DATA) ||
                        (LpsWrk.UpdtTbl->LegalForTradeInstalled)) {
                    // Use a faster time interval when hydraulic oil temperature is disabled.
                    // or if the last zero temperature is unknown.
                    timeInterval = LpsWrk.InitTbl.MachSpecificCfg.ZeroAdjAutoTimeIntervalFast;
                }
                else {
                    timeInterval = LpsWrk.InitTbl.MachSpecificCfg.ZeroAdjAutoTimeInterval;
                }

                if (CurrentTimeSec >= (LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.LastZeroTime + timeInterval)) {
                    /* Notify operator they need to zero bucket */
                    LpsWeighZeroNotify(LPS_ZERO_UPDATE_TIMER_EXPIRED_ZERO_REQUIRED);
                }
            }
        }
    }
    else {
        /* zero update is not required */
        LpsWeighZeroNotify(LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED);
    }
}

// Is a zero weight available?
boolean LpsWeighIsZeroWeightAvailable(void)
{
    if (LPS_WEIGH_WRW_STATUS_VALID == LpsWrk.WrwTbl.OpTbl.Status) {
        if (LpsWrk.InitTbl.MachSpecificCfg.ZeroBktWtAccuracyLimit >= LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_HIGH) {
            if (LPS_WEIGH_NO_WARNING_ACTIVE == LpsWrk.WrwTbl.OpTbl.Warning) {
                return TRUE;
            }
        }
        else {
            return TRUE;
        }
    }
    return FALSE;
}

// Get the result of the last zero adjustment
LpsZeroErrorTypes_t LpsWeighGetZeroAdjStatus(void)
{    
    return LpsWrk.ZeroAdjTbl.ZeroAdjStatus;
}

// Get the current zero needed status
LpsZeroNeededStatus_t LpsWeighGetAutoZeroUpdateStatus(void)
{    
    if (!LpsRemainingWarmupLiftsRequired())
    {
        return LpsWrk.ZeroAdjTbl.AutoZeroStatus;
    }
    else
    {
        // if warmup lifts are required, don't show zero
        return LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED;
    }
}

// Get the current zero weight
float_32 LpsWeighGetZeroWeight(void)
{
    return LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.ZeroWeight;
}

// Notify of an updated zero needed status
static void LpsWeighZeroNotify(LpsZeroNeededStatus_t zeroNeededStatus)
{
    LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.LastZeroTime = LpsWrk.UpdtTbl->ClockKeyonSec;

    if (LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED == zeroNeededStatus) {
        LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.ZeroRequired = FALSE;
    }
    else {
        LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.ZeroRequired = TRUE;
    }

    LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.SnoozedStatus = LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED;

    LpsWrk.ZeroAdjTbl.AutoZeroStatus = zeroNeededStatus;
}

// Determine if it is time to zero based on a change in hydraulic oil temperature.
static boolean LpsWeighHydraulicOilTempChanged()
{
    float_32 hydOilTemp = LpsWrk.UpdtTbl->HydOilTemp.Val;

    // Only do this is hydraulic oil temperature is not disabled and not faulted.
    if ((hydOilTemp > HYDRAULIC_OIL_TEMP_MIN_VALID_DATA) &&
            (LPS_HYD_OIL_TEMP_STATUS_OK == LpsWrk.UpdtTbl->HydOilTemp.Stat) &&
            (LpsWrk.ZeroAdjTbl.ZeroTemp > HYDRAULIC_OIL_TEMP_MIN_VALID_DATA)) {

        // Oil is considered cold if it is 5 degrees below the empty calibration temperature
        float_32 coldTemp = LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.EmptyTemp - LPS_EMPTY_CAL_OIL_TEMP_DELTA;

        // Oil is also considered cold if it is below the configured threshold
        if (coldTemp < LpsWrk.InitTbl.MachSpecificCfg.ZeroAdjOilTempWarnThreshold) {
            coldTemp = LpsWrk.InitTbl.MachSpecificCfg.ZeroAdjOilTempWarnThreshold;
        }

        // If the last zero hydraulic oil temp was "cold" or the current hydraulic oil temp is "cold"
        if ((LpsWrk.ZeroAdjTbl.ZeroTemp < coldTemp) || (hydOilTemp < coldTemp)) {
            // If the hydraulic oil temperature has changed enough
            if ((hydOilTemp >= LpsWrk.ZeroAdjTbl.ZeroTemp + LpsWrk.InitTbl.MachSpecificCfg.ZeroAdjOilTempDelta) ||
                    (hydOilTemp <= LpsWrk.ZeroAdjTbl.ZeroTemp - LpsWrk.InitTbl.MachSpecificCfg.ZeroAdjOilTempDelta)) {
                // Require a zero
                return TRUE;
            }
        }
    }

    return FALSE;
}

boolean LpsInitialZeroRequired(void)
{
    // only required for legal for trade
    if (LpsWrk.ZeroAdjTbl.InitialZeroRequired && LpsWrk.UpdtTbl->LegalForTradeInstalled)
    {
        return TRUE;
    }

    return FALSE;
}
