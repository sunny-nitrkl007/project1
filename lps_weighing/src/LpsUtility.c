/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsUtility.c
DESCRIPTION:This files provide utility functions to be used by LPS library for
            internal processing.
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#ifndef __LPS_COMMON_TYPE_DEF_H__
 /* Contains type definitions of standard datatypes */
#include <LpsCommonTypeDef.h>
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
 /* Contains structures which are common between all LPS system libraries */
#include <LpsCommonStructures.h>
#endif

#ifndef __LPS_PUBLIC_H__
/*******************************************************/ 
/* Containes prototypes of interfaces and functions    */
/* which are exported to the application using the     */
/* library                                             */
/*******************************************************/
#include <LpsPublic.h> 
#endif

/*******************************************************/ 
/* Contains prototypes of interfaces and functions     */
/* which are used within the payload computation       */
/* library                                             */
/*******************************************************/
#include "LpsPrivate.h"

#include <string.h>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
#define REQUESTED_GEAR_FWD        0x4000
#define REQUESTED_GEAR_REV        0x07FF
#define REQUESTED_GEAR_MATCH     0x17FF
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
/******************************************************************************
FUNCTION NAME:LpsResetWrkTbl
DESCRIPTION:Utility function to reset work table
PARAMETER DESCRIPTION:NULL
RETURN VALUE:LpsWrk
*******************************************************************************/
void LpsResetWrkTbl(void)
{
    memset((void *)&LpsWrk,0,sizeof(LpsWrkTbl_t));

    LpsWrk.StaticWtFactor.Tau    = 1.93;        
    LpsWrk.StaticWtFactor.OlRaw  = 0.3;      
    LpsWrk.StaticWtFactor.OlFilt = 0.3;     
    LpsWrk.StaticWtFactor.Curr   = 0.3; 

    return;
}

/******************************************************************************
FUNCTION NAME:LpsCopyAppInitTbl
DESCRIPTION:Utility function to copy new configuration to work table
PARAMETER DESCRIPTION:NewInitTbl -> LPS configuration table to be copied to work table for
                      library processing
RETURN VALUE: LpsWrk.InitTbl-> application configuration copy for LPS library computation
*******************************************************************************/
void LpsCopyAppInitTbl(LpsInitTbl_t *newInitTbl)
{
    memcpy(&LpsWrk.InitTbl,newInitTbl,sizeof(LpsInitTbl_t));

    return;
}

/******************************************************************************
FUNCTION NAME:LpsChkInputStat
DESCRIPTION:This utility function checks all the inputs to LPS library for faulty condition.
PARAMETER DESCRIPTION:LpsWrk.UpdtTbl -> LPS library inputs passed by application software
RETURN VALUE:STATUS_GOOD->LPS library Inputs are good and ok to for further processing,
             STATUS_BAD->LPS library Inputs are faulty.
*******************************************************************************/
boolean LpsChkInputStat(void)
{
    if (NULL == LpsWrk.UpdtTbl) {
        return STATUS_BAD;
    }
    else if ((LPS_STATUS_OK == LpsWrk.UpdtTbl->LiftCylHePres.Stat) &&
            (LPS_STATUS_OK == LpsWrk.UpdtTbl->LiftCylRePres.Stat) &&
            (LPS_HYD_OIL_TEMP_STATUS_BAD != LpsWrk.UpdtTbl->HydOilTemp.Stat) &&
            (LPS_STATUS_OK == LpsWrk.UpdtTbl->LiftCylVel.Stat) &&
            (LPS_STATUS_OK == LpsWrk.UpdtTbl->LiftCylLengthNorm.Stat) &&
            (LPS_STATUS_OK == LpsWrk.UpdtTbl->LiftCylLength.Stat) &&
            (LPS_STATUS_OK == LpsWrk.UpdtTbl->TiltCylLengthNorm.Stat) &&
            (LPS_STATUS_OK == LpsWrk.UpdtTbl->BktAngle.Stat) &&
            (LPS_STATUS_OK == LpsWrk.UpdtTbl->LiftAngle.Stat) /*&& 
            (FALSE == LpsWrk.UpdtTbl->VoltageEventActive)*/) {
        if ((LpsWrk.UpdtTbl->LegalForTradeInstalled) || (LpsWrk.UpdtTbl->IMUCompEnabled)) {
            // When LFT is installed or IMU compensation is enabled, IMU is required.
            if (LPS_STATUS_OK == LpsWrk.UpdtTbl->ReferenceIMUData.Stat) {
                return (STATUS_GOOD);
            }
            else {
                return (STATUS_BAD);
            }
        }
        else {
            return (STATUS_GOOD);
        }
    }
    else {
        return (STATUS_BAD);
    }
}

/******************************************************************************
FUNCTION LpsSetCalAdjustFactor
DESCRIPTION: Sets the Simple Cal Adjust Factor
PARAMETER DESCRIPTION: None
RETURN VALUE: float_32 CalAdjust
*******************************************************************************/
void LpsSetCalAdjustFactor(float_32 CalAdjust)
{
    LpsCalNvmTbl_t* pCalTbl;
    LpsMachSpecificCfg_t* pMachSpecConf;

    pMachSpecConf = &LpsWrk.InitTbl.MachSpecificCfg;
    pCalTbl = &pMachSpecConf->CalibTbl;

    pCalTbl->CalAdjust = CalAdjust;

    return;
}

float_32 LpsAdvCalAdjust(float_32 unadjustedWeight)
{
    float_32 adjustedWeight;

    /* Apply the advanced calibration adjustment if available */
    if ((LpsWrk.AdvCalAdjust.numPoints > 0) &&
            (LpsWrk.AdvCalAdjust.numPoints <= LPS_ADV_CAL_ADJUST_MAP_MAX_POINTS)) {
        adjustedWeight = LpsLookupExtrap(unadjustedWeight, LpsWrk.AdvCalAdjust.calibratedWeight,
                LpsWrk.AdvCalAdjust.adjustedWeight, LpsWrk.AdvCalAdjust.numPoints);
    }
    else {
        adjustedWeight = unadjustedWeight;
    }

    return adjustedWeight;
}

float_32 LpsZeroSpanAdjust(float_32 unadjustedWeight)
{
    float_32 adjustedWeight = unadjustedWeight - LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.ZeroWeight;

    if (LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalAdjust > (float_32)0.0) {
        adjustedWeight =  adjustedWeight * LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalAdjust;
    }

    return adjustedWeight;
}

/******************************************************************************
FUNCTION NAME:LpsWeighIsRequestedGearForward
DESCRIPTION: Determines if the machine is in Forward Gear or not
PARAMETER DESCRIPTION: None
RETURN VALUE: boolean isPossiblyForward
*******************************************************************************/
boolean LpsWeighIsRequestedGearForward(void)
{
    boolean isPossiblyForward;
    LpsUpdtTbl_t *pUpdateTbl = LpsWrk.UpdtTbl;

    if (LPS_STATUS_OK == pUpdateTbl->RequestedGear.Stat)
    {
        if (0 != (pUpdateTbl->RequestedGear.Val & REQUESTED_GEAR_FWD))
        {
            isPossiblyForward = TRUE;
        }
        else
        {
            isPossiblyForward = FALSE;
        }
    }
    else
    {
        isPossiblyForward = TRUE;
    }
    return isPossiblyForward;
}


/******************************************************************************
FUNCTION NAME:LpsWeighIsRequestedGearReverse
DESCRIPTION: Determines if the machine is in Reverse Gear or not
PARAMETER DESCRIPTION: None
RETURN VALUE: boolean isReverse
*******************************************************************************/
boolean LpsWeighIsRequestedGearReverse(void)
{
    boolean isReverse;
    LpsUpdtTbl_t *pUpdateTbl = LpsWrk.UpdtTbl;

    if (LPS_STATUS_OK == pUpdateTbl->RequestedGear.Stat)
    {
        if (REQUESTED_GEAR_MATCH == (pUpdateTbl->RequestedGear.Val | REQUESTED_GEAR_REV))
        {
            isReverse = TRUE;
        }
        else
        {
            isReverse = FALSE;
        }
    }
    else
    {
        isReverse = TRUE;
    }
    return isReverse;
}


/*
 * Calculates a friction coefficient estimate based on the existing calibration tables.
 */
boolean LpsWeighEstimateFrictionCoefficient(float* mu, float* offset)
{
    static const float testLiftHeights[] = { 30.f, 40.f, 50.f, 60.f, 70.f };
    LpsCalNvmTbl_t* calib = &LpsWrk.InitTbl.MachSpecificCfg.CalibTbl;

    // Set up for linear fit
    float Sx = 0.f;
    float Sxx = 0.f;
    float Sxy = 0.f;
    float Sy = 0.f;
    float n = 0.f;

    int ii;

    // Consider empty bucket calibration points.
    for (ii = 0; ii < sizeof(testLiftHeights)/sizeof(testLiftHeights[0]); ++ii) {
        float liftHeight = testLiftHeights[ii];

        float raisePressure = LpsLookupExtrap(liftHeight, calib->SlowRaiseEmptyBktLiftHt,
                calib->SlowRaiseEmptyBktLiftPres, sizeof(calib->SlowRaiseEmptyBktLiftHt) / sizeof(calib->SlowRaiseEmptyBktLiftHt[0]));

        float lowerPressure = LpsLookupExtrap(liftHeight, calib->SlowLowerEmptyBktLiftHt,
                calib->SlowLowerEmptyBktLiftPres, sizeof(calib->SlowLowerEmptyBktLiftHt) / sizeof(calib->SlowLowerEmptyBktLiftHt[0]));

        if ((raisePressure + lowerPressure) <= 0.f) {
            continue;
        }

        // Use geometric mean to find no friction point.
        float pressure = (2.f * raisePressure * lowerPressure) / (raisePressure + lowerPressure);

        float frictionPressure = raisePressure - pressure;

        if (frictionPressure <= 0.f) {
            continue;
        }

        Sx += raisePressure;
        Sxx += (raisePressure * raisePressure);
        Sxy += (raisePressure * frictionPressure);
        Sy += frictionPressure;
        n += 1.f;
    }

    // Consider full bucket calibration points.
    for (ii = 0; ii < sizeof(testLiftHeights)/sizeof(testLiftHeights[0]); ++ii) {
        float liftHeight = testLiftHeights[ii];

        float raisePressure = LpsLookupExtrap(liftHeight, calib->SlowRaiseFullBktLiftHt,
                calib->SlowRaiseFullBktLiftPres, sizeof(calib->SlowRaiseFullBktLiftHt) / sizeof(calib->SlowRaiseFullBktLiftHt[0]));

        float lowerPressure = LpsLookupExtrap(liftHeight, calib->SlowLowerFullBktLiftHt,
                calib->SlowLowerFullBktLiftPres, sizeof(calib->SlowLowerFullBktLiftHt) / sizeof(calib->SlowLowerFullBktLiftHt[0]));

        if ((raisePressure + lowerPressure) <= 0.f) {
            continue;
        }

        // Use geometric mean to find no friction point.
        float pressure = (2.f * raisePressure * lowerPressure) / (raisePressure + lowerPressure);

        float frictionPressure = raisePressure - pressure;

        if (frictionPressure <= 0.f) {
            continue;
        }

        Sx += raisePressure;
        Sxx += (raisePressure * raisePressure);
        Sxy += (raisePressure * frictionPressure);
        Sy += frictionPressure;
        n += 1.f;
    }

    // Calculate the best fit
    if (n > 0.f) {
        float num = Sxy - ((Sx * Sy) / n);
        float den = Sxx - ((Sx * Sx) / n);
        if (0.f != den) {
            float m = num / den;
            float b = (Sy - (m * Sx)) / n;

            if (NULL != mu) {
                *mu = m;
            }

            if (NULL != offset) {
                *offset = b;
            }

            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else {
        return FALSE;
    }
}
