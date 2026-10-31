/*******************************************************************************
** COPYRIGHT (C) 2016-2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsUpdate.c
DESCRIPTION:This file provides the update routines for the application software
            for LPS library.
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include<stdio.h>

#ifndef __LPS_COMMON_TYPE_DEF_H__
#include <LpsCommonTypeDef.h> /* Contains type definitions of standard datatypes */
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCommonStructures.h> /* Contains structures which are common between all LPS
                                  * system libraries
                                  */
#endif

#ifndef __LPS_PUBLIC_H__
#include <LpsPublic.h> /*******************************************************/ 
                       /* Containes prototypes of interfaces and functions    */
                       /* which are exported to the application using the     */
                       /* library                                             */
                       /*******************************************************/
#endif

#include "LpsPrivate.h" /*******************************************************/ 
                        /* Containes prototypes of interfaces and functions    */
                        /* which are used within the payload computation       */
                        /* library                                             */
                        /*******************************************************/

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
/******************************************************************************
FUNCTION NAME:LpsUpdt
DESCRIPTION: This function is an API interface for the application software. Application software
             invokes this API at predetermined intervals. LPS library performs the algorithms/functionalities
             to compute instantaneous weight when this API is invoked.The algorithm goes through various
             stages like hydraulic flow calculation, Difference pressure computation, Pressure loss calculation,
             hydraulic Oil temperature compensation and calibration adjustments to output instantaneous weight.
             Computations from one stage to other is interfaced through work table. 
PARAMETER DESCRIPTION: LpsAppUpdtTbl-> Application software provides inputs to the LPS 
                       library through this interface. It holds values of pressure sensors,hydraulic oil
                       temperature, Cylinder extention percentage, operator input, etc.
RETURN VALUE: LpsUpdtErrorTypes_t-> This enum interface reports various error types reported by
              LpsUpdt function to the application software.
*******************************************************************************/
LpsUpdtErrorTypes_t LpsUpdt(LpsUpdtTbl_t *LpsAppUpdtTbl)
{
    LpsUpdtErrorTypes_t updateError;

    if (LPS_INIT_SUCCESS != LpsWrk.InitErr) {
        updateError = LPS_UPDT_NOT_INIT;
    }
    else if (NULL == LpsAppUpdtTbl) {
        updateError = LPS_UPDT_NOT_INIT;
    }
    else {
        LpsWrk.UpdtTbl = LpsAppUpdtTbl;

        LpsInputStatusUpdate();

        LpsLiftPositionFiltUpdate();

        LpsUpdateLinkageMovement();

        LpsWeighDumpDetectUpdate();

        /*
         * Determining Lift Cylinder head end to rod end difference pressure after compensating
         * for hydraulic oil (temperature compensated) pressure loss
         */
        LpsCalcDiffPres();

        LpsCalcInstantWtUpdate();

        LpsWeighDumpWtChangeUpdate();

        LpsWeighDigDetectUpdate();

        LpsLowLiftWeighCalcUpdate();

        /*
         * Weigh Range Weight Calculation - This function should follow LLW as bandstop filtering
         * is applied there
         */
        LpsWeighRangeWeighUpdate();

        /* Live Weight Calculation - This function should follow LLW as InstWtLlwFilt is used */
        LpsLiveWeighCalc();

        /* Check for conditions to alert the operator that a zero lift is needed */
        LpsWeighAutoZeroUpdate();

        LpsLiftStallDetectUpdate();

        LpsWeighExcessivePitchDetect();

        /*
         * Call best bucket weight update function.
         *  This is dependent upon all of the weights being calculated, live weight,
         *  weigh range weight, and low lift weigh.  This is also dependent upon
         *  determination of the lift stall state.
         */
        LpsWeighBestBktWtUpdate();

        /* Update instantaneous weight status if stalled */
        if (LPS_INST_RAW_WT_STATUS_OK == LpsWrk.InstWtRaw.Stat) {
            if (LpsWrk.LpsStallDetect.liftRaiseStalled) {
                LpsWrk.InstWtRaw.Stat = LPS_INST_RAW_WT_STATUS_RAISE_STALL;
            }
            else if (LpsWrk.LpsStallDetect.liftLowerStalled) {
                LpsWrk.InstWtRaw.Stat = LPS_INST_RAW_WT_STATUS_LOWER_STALL;
            }
        }

        if (LPS_STATUS_BAD == LpsWrk.InputStatus.rawStatus) {
            updateError = LPS_UPDT_INPUT_ERROR;
        }
        else {
            updateError = LPS_UPDT_SUCCESS;
        }
    }

    LpsWrk.UpdtErr = updateError;
    return LpsWrk.UpdtErr;
}

/*
 * FUNCTION NAME: See function
 * DESCRIPTION: Gets raw and filtered payload ratios and returns their status
 *              If not NULL, both raw and filtered will be written independent
 *              of the status.
 * PARAMETER DESCRIPTION:
 *  raw - pointer to where the raw payload ratio will be stored.
 *  filtered - pointer to where the filtered payload ratio will be stored.
 * RETURN VALUE: InstWtRaw.Stat (the status of the instantaneous weight)
 */
LpsInstWtRawStat_t LpsGetPayloadRatio(float* raw, float* filtered) {
    float ratedPayload = LpsWrk.InitTbl.MachSpecificCfg.DigConfig.DigTargetWt;

    /* Update raw payload ratio */
    if (NULL != raw) {
        if (ratedPayload > 0) {
            *raw = LpsWrk.InstWtRaw.Val / ratedPayload;
        }
        else {
            *raw = 0.f;
        }
    }

    /* Update filtered payload ratio */
    if (NULL != filtered) {
        if (ratedPayload > 0) {
            *filtered = LpsWrk.InstWtFilt / ratedPayload;
        }
        else {
            *filtered = 0.f;
        }
    }

    /* Return instantaneous weight raw status */
    return LpsWrk.InstWtRaw.Stat;
}


/******************************************************************************
FUNCTION NAME:LpsGetRawInstWt
DESCRIPTION: This API function gets/returns the raw instantaneous weight computed by the 
             LPS library.
PARAMETER DESCRIPTION: NULL
RETURN VALUE: InstWtRaw.Val->Instantaneous Weight in Tonnes,InstWtRaw.Stat-> Status
*******************************************************************************/
LpsInstWtRaw_t LpsGetRawInstWt(void)
{
    return LpsWrk.InstWtRaw;
}

/******************************************************************************
FUNCTION NAME:LpsGetLiftCylPressure
DESCRIPTION: This API function gets/returns the hydraulic oil temperature compensated
             Lift Cylinder pressure (Difference presseure between Head end and Rod end
             of lift cylinder piston)computed by the LPS library.
PARAMETER DESCRIPTION: NULL
RETURN VALUE: liftCylPres->Lift Cylinder pressure (Difference pressure) in Kpa
*******************************************************************************/
float_32 LpsGetLiftCylPressure(void)
{
    return LpsWrk.LiftCylPressure;
}

/******************************************************************************
FUNCTION NAME:LpsGetLiftCylPressureV0
DESCRIPTION: This API function gets/returns the hydraulic oil temperature compensated
             Lift Cylinder pressure (Difference presseure between Head end and Rod end
             of lift cylinder piston)computed by the LPS library.
             This pressure is also compensated kinematic induced acceleration.
PARAMETER DESCRIPTION: NULL
RETURN VALUE: liftCylPres->Lift Cylinder pressure (Difference pressure) in Kpa
*******************************************************************************/
float_32 LpsGetLiftCylPressureV0(void)
{
    return LpsWrk.LiftCylPressureV0;
}

/******************************************************************************
FUNCTION NAME:LpsGetExcessivePitchStatus
DESCRIPTION: Return pitch icon debounce status.
PARAMETER DESCRIPTION: NULL
RETURN VALUE: Icon debounce status
*******************************************************************************/
boolean LpsGetExcessivePitchStatus(void)
{
    LpsUpdtTbl_t* updtTbl = LpsWrk.UpdtTbl;

    if (NULL == updtTbl) {
        return FALSE;
    }

    if (updtTbl->LegalForTradeInstalled) {
        return LpsWrk.PitchIconDebounce.debouncedStatus;
    }
    else {
        return FALSE;
    }
}
