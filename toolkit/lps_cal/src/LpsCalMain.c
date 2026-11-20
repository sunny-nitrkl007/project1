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

#include <string.h>
#include <math.h>

#include <std_types.h> // TRUE and FALSE

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/



/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
static void  	LpsCalLiftCalOvrCtrlSetReqLimits(float_32 ReqRaiseCommandLimit, float_32 ReqLowerCommandLimit);
static void  	LpsCalGetCurveFitResults(LpsCalCurveFitData_t const *FitData, LpsCalCurveFitResults_t *Results);
static void  	LpsCalLiftCalUpdateImplOverrides(void);
static void     LpsCalTiltCalUpdateImplOverrides(void);
static void  	LpsCalLiftCalOvrCtrlInit(float_32 InitRaiseCommand, float_32 InitLowerCommand);
static float_32 LpsCalOvrCtrlGetRaiseCmdLimit(void);
static float_32 LpsCalOvrCtrlGetLowerCmdLimit(void);
static void  	LpsCalLiftCalOvrCtrlUpdate(float_32 LiftHeight);
static void 	LpsCalUpdateInfo(void);

static void LpsCalCurveFitDataReset(LpsCalCurveFitData_t* FitData, LpsCalCurveFitResults_t const * ReferenceResults);
static void LpsCalCurveFitDataUpdate(LpsCalCurveFitData_t* FitData, float_32 Pos, float_32 Press);
static void LpsCalCurveFitDataCollect(LpsCalCurveFitData_t* FitData, float_32 Pos, float_32 Press, float_32 Vel, float_32 TiltAngleABCPct,
        LpsIMUData_t const * ReferenceIMUData);

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/


/******************************************************************************
FUNCTION NAME: pcs_empty_cal3_main
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalStartLiftOverrides(void)
{
	LpsCalInfo_t *pCalInfo = &LpsCalWrkTbl.Info;
    pCalInfo->LpsCalOvrStartRequest = TRUE;
    pCalInfo->LpsCalOvrStopRequest = FALSE;
    LpsCalLiftCalOvrCtrlSetReqLimits(100.0, -100.0);
}

/******************************************************************************
FUNCTION NAME: pcs_empty_cal3_main
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalResetTiltOverrides(void)
{
    LpsCalOv_t *pCalOv = &LpsCalWrkTbl.Ov;
    LpsCalInfo_t *pCalInfo = &LpsCalWrkTbl.Info;
    pCalOv->LpsCalTiltOv.LpsCalTiltOvrStartRequest = FALSE;
    pCalOv->LpsCalTiltOv.LpsCalTiltOvrStopRequest = FALSE;
    pCalInfo->CalTiltOverrideFail = FALSE;
    pCalInfo->CalTiltOverrideComplete = FALSE;
    LpsCalAppInfSetTiltCmdOvr(LPS_CAL_APP_MIN_RACK_CMD, LPS_CAL_APP_MIN_DUMP_CMD);
}

/******************************************************************************
FUNCTION NAME: pcs_empty_cal3_main
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalStartTiltOverrides(void)
{
    LpsCalOv_t *pCalOv = &LpsCalWrkTbl.Ov;
    pCalOv->LpsCalTiltOv.LpsCalTiltOvrStartRequest = TRUE;
    pCalOv->LpsCalTiltOv.LpsCalTiltOvrStopRequest = FALSE;
    LpsCalAppInfSetTiltCmdOvr(LPS_CAL_APP_MIN_RACK_CMD, LPS_CAL_APP_MIN_DUMP_CMD);
}

/******************************************************************************
FUNCTION NAME: pcs_empty_cal3_main
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalStopTiltOverrides(void)
{
    LpsCalOv_t *pCalOv = &LpsCalWrkTbl.Ov;
    pCalOv->LpsCalTiltOv.LpsCalTiltOvrStopRequest = TRUE;
    pCalOv->LpsCalTiltOv.LpsCalTiltOvrStartRequest = FALSE;
    LpsCalAppInfSetTiltCmdOvr(LPS_CAL_APP_MIN_RACK_CMD, LPS_CAL_APP_MIN_DUMP_CMD);
}

/******************************************************************************
FUNCTION NAME: pcs_empty_cal3_main
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalStopLiftOverrides(void)
{
	LpsCalInfo_t *pCalInfo = &LpsCalWrkTbl.Info;
    pCalInfo->LpsCalOvrStartRequest = FALSE;
    pCalInfo->LpsCalOvrStopRequest = TRUE;
    LpsCalLiftCalOvrCtrlSetReqLimits(100.0, -100.0);

}

/******************************************************************************
FUNCTION NAME: pcs_empty_cal3_main
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalSetLiftOverrides(float_32 RaiseCommandLimit, float_32 LowerCommandLimit)
{
    LpsCalLiftCalOvrCtrlSetReqLimits(RaiseCommandLimit, LowerCommandLimit);
}

/******************************************************************************
FUNCTION NAME: pcs_empty_cal3_main
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
static void LpsCalLiftCalOvrCtrlSetReqLimits(float_32 ReqRaiseCommandLimit, float_32 ReqLowerCommandLimit)
{
    LpsCalWrkTbl.CurveFitInfo.LpsCalOvrCtrlRaiseData.ReqCommandLimit = ReqRaiseCommandLimit;
    LpsCalWrkTbl.CurveFitInfo.LpsCalOvrCtrlLowerData.ReqCommandLimit = ReqLowerCommandLimit;
}

/******************************************************************************
FUNCTION NAME: pcs_empty_cal3_main
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalStartRaiseCalData(float_32 CalBottomHeight, float_32 CalTopHeight, LpsCalCurveFitResults_t const *ReferenceResults)
{
	LpsCalInfo_t   		 *pCalInfo   	= &LpsCalWrkTbl.Info;
	LpsCalCurveFitInfo_t *pCurveFitInfo = &LpsCalWrkTbl.CurveFitInfo;

    //LpsCalWrkTbl.Status.CalLiftActive = FALSE;
    //LpsCalWrkTbl.Status.CalLiftComplete = FALSE;
    //LpsCalWrkTbl.Info.calLiftStatus = 0xFF;
    //pcs_reset_cal_raise_data();

    pCalInfo->CalRaiseActive = FALSE;
    pCalInfo->CalRaiseComplete = FALSE;
    pCalInfo->CalRaiseStatus = 0xFF;
    LpsCalIMUResetData(LpsCalIMURaise);
    LpsCalCurveFitDataReset(&pCurveFitInfo->LpsCalRaiseCurveFitData, ReferenceResults);

    pCalInfo->CalTopOfCalLiftHt = CalTopHeight;
    pCalInfo->CalBottomOfCalLiftHt = CalBottomHeight;
}

/******************************************************************************
FUNCTION NAME: pcs_empty_cal3_main
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalStartLowerCalData(float_32 CalBottomHeight, float_32 CalTopHeight, LpsCalCurveFitResults_t const *ReferenceResults)
{
	LpsCalInfo_t   *pCalInfo   = &LpsCalWrkTbl.Info;
	LpsCalCurveFitInfo_t *pCurveFitInfo = &LpsCalWrkTbl.CurveFitInfo;

    pCalInfo->CalLowerActive = FALSE;
    pCalInfo->CalLowerComplete = FALSE;
    pCalInfo->CalLowerStatus = 0xFF;
    LpsCalIMUResetData(LpsCalIMULower);
    LpsCalCurveFitDataReset(&pCurveFitInfo->LpsCalLowerCurveFitData, ReferenceResults);

    pCalInfo->CalTopOfCalLiftHt 	= CalTopHeight;
    pCalInfo->CalBottomOfCalLiftHt 	= CalBottomHeight;
}


/******************************************************************************
FUNCTION NAME: LpsCalGetRaiseCurveFitResults
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE: LPS_CAL_CURVE_FIT_STAT - Status of the curve fit.
*******************************************************************************/
LPS_CAL_CURVE_FIT_STAT LpsCalGetRaiseCurveFitResults(LpsCalCurveFitResults_t *Results)
{
    LpsCalGetCurveFitResults(&LpsCalWrkTbl.CurveFitInfo.LpsCalRaiseCurveFitData, Results);

    { // Check pressure
        float_32 pressure = LpsLookupExtrap(50.0, Results->AryPosition, Results->AryPressure, LPS_CAL_CURVE_FIT_NUM_POINTS);
        if (pressure <= 0.f) {
            return LPS_CAL_CURVE_FIT_STAT_PRESS_0;
        }
    }

    return LPS_CAL_CURVE_FIT_STAT_OK;
}

/******************************************************************************
FUNCTION NAME: pcs_empty_cal3_main
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
static void LpsCalGetCurveFitResults(LpsCalCurveFitData_t const *FitData, LpsCalCurveFitResults_t *Results)
{
    float_32 TotalNumPoints = FitData->TotalNumPoints;

    if (TotalNumPoints > 0) {
        Results->AverageVelocity = FitData->SumVelocity / TotalNumPoints;
        Results->AverageReferencePressure = FitData->SumReferencePressure / TotalNumPoints;
        Results->AverageDeltaPFromReference = FitData->SumDeltaPFromReference / TotalNumPoints;
        Results->AryAverageIMUAccel[0] = FitData->ArySumIMUAccel[0] / TotalNumPoints;
        Results->AryAverageIMUAccel[1] = FitData->ArySumIMUAccel[1] / TotalNumPoints;
        Results->AryAverageIMUAccel[2] = FitData->ArySumIMUAccel[2] / TotalNumPoints;
        Results->AveragePitch = FitData->SumPitch / TotalNumPoints;
        Results->AverageRoll = FitData->SumRoll / TotalNumPoints;
    }
    else {
        Results->AverageVelocity = 0;
        Results->AverageReferencePressure = 0;
        Results->AverageDeltaPFromReference = 0;
        Results->AryAverageIMUAccel[0] = 0;
        Results->AryAverageIMUAccel[1] = 0;
        Results->AryAverageIMUAccel[2] = 0;
        Results->AveragePitch = 0;
        Results->AverageRoll = 0;
    }

    {
        float_32 arySlope[LPS_CAL_CURVE_FIT_NUM_POINTS-1];
        float_32 aryOffset[LPS_CAL_CURVE_FIT_NUM_POINTS-1];
        unsigned_16 ii;
        LpsCalWrkTbl.Info.OffRackEndIndex = 0;

        /* Fit each line segment to the data */
        for (ii = 0; ii < LPS_CAL_CURVE_FIT_NUM_POINTS-1; ii++)
        {
            if (FitData->AryNumPoints[ii] >= 2)
            {
                float_32 num = FitData->ArySumXY[ii] - ((FitData->ArySumX[ii]) * (FitData->ArySumY[ii]) / (FitData->AryNumPoints[ii]));
                float_32 den = FitData->ArySumXX[ii] - ((FitData->ArySumX[ii]) * (FitData->ArySumX[ii]) / (FitData->AryNumPoints[ii]));
                if (den != (float_32)0.0)
                {
                    arySlope[ii] = num / den;
                }
                else
                {
                    arySlope[ii] = 0;
                }

                aryOffset[ii] = (FitData->ArySumY[ii] - (arySlope[ii] * FitData->ArySumX[ii])) / (FitData->AryNumPoints[ii]);
            }
            else
            {
                arySlope[ii] = 0;
                aryOffset[ii] = 0;
            }
        }

        /* Average the dependent axis results from the linear fits that surround it. */
        for (ii = 0; ii < LPS_CAL_CURVE_FIT_NUM_POINTS; ii++)
        {
            float_32 position = FitData->AryPosition[ii];

            Results->AryPosition[ii] = position;

            if (0 == ii)
            {
                Results->AryPressure[ii] = position * arySlope[ii] + aryOffset[ii];
            }
            else if ((LPS_CAL_CURVE_FIT_NUM_POINTS-1) == ii)
            {
                Results->AryPressure[ii] = position * arySlope[ii-1] + aryOffset[ii-1];
            }
            else
            {
                float_32 lowerPoint = position * arySlope[ii-1] + aryOffset[ii-1];
                float_32 upperPoint = position * arySlope[ii] + aryOffset[ii];
                Results->AryPressure[ii] = (lowerPoint + upperPoint) / (float_32)2;
            }
        }

        /* Find point above the off rack height */
        LpsCalWrkTbl.Info.OffRackEndIndex = 0;

        for (ii = 0; ii < LPS_CAL_CURVE_FIT_NUM_POINTS; ii++)
        {
            if (Results->AryPosition[ii] >= FitData->LiftPositionOffRack)
            {
                LpsCalWrkTbl.Info.OffRackEndIndex = ii;
                break;
            }
        }

        if (LpsCalWrkTbl.Info.OffRackEndIndex >= 3)
        {
            /* Free up the 4th point from effects of the 3rd line segment. */
            Results->AryPressure[3] = Results->AryPosition[3] * arySlope[3] + aryOffset[3];

            { /* Extrapolate to get the 3rd point by keeping a constant second derivative */
                float_32 slope1 = (Results->AryPressure[4] - Results->AryPressure[3])/(Results->AryPosition[4] - Results->AryPosition[3]);
                float_32 slope2 = (Results->AryPressure[5] - Results->AryPressure[4])/(Results->AryPosition[5] - Results->AryPosition[4]);
                float_32 slope = slope1 - (slope2 - slope1);
                if (slope < (float_32)0.0)
                {
                    slope = 0.0;
                }
                else if (slope > slope1)
                {
                    slope = slope1;
                }
                Results->AryPressure[2] = slope*(Results->AryPosition[2] - Results->AryPosition[3]) + Results->AryPressure[3];
            }

            { /* Extrapolate to get the 2nd point by keeping a constant second derivative */
                float_32 slope1 = (Results->AryPressure[3] - Results->AryPressure[2])/(Results->AryPosition[3] - Results->AryPosition[2]);
                float_32 slope2 = (Results->AryPressure[4] - Results->AryPressure[3])/(Results->AryPosition[4] - Results->AryPosition[3]);
                float_32 slope = slope1 - (slope2 - slope1);
                if (slope < (float_32)0.0)
                {
                    slope = 0.0;
                }
                else if (slope > slope1)
                {
                    slope = slope1;
                }
                Results->AryPressure[1] = slope*(Results->AryPosition[1] - Results->AryPosition[2]) + Results->AryPressure[2];
            }

            { /* Don't continue extrapolating a 3rd time, just call it a flat line */
                Results->AryPressure[0] = Results->AryPressure[1];
            }
        }
        else if (LpsCalWrkTbl.Info.OffRackEndIndex >= 2)
        {
            /* Free up the 3rd point from effects of the 2nd line segment. */
            Results->AryPressure[2] = Results->AryPosition[2] * arySlope[2] + aryOffset[2];

            { /* Extrapolate to get the 2nd point by keeping a constant second derivative */
                float_32 slope1 = (Results->AryPressure[3] - Results->AryPressure[2])/(Results->AryPosition[3] - Results->AryPosition[2]);
                float_32 slope2 = (Results->AryPressure[4] - Results->AryPressure[3])/(Results->AryPosition[4] - Results->AryPosition[3]);
                float_32 slope = slope1 - (slope2 - slope1);
                if (slope < (float_32)0.0)
                {
                    slope = 0.0;
                }
                else if (slope > slope1)
                {
                    slope = slope1;
                }
                Results->AryPressure[1] = slope*(Results->AryPosition[1] - Results->AryPosition[2]) + Results->AryPressure[2];
            }
            { /* Extrapolate to get the 1st point by keeping a constant second derivative */
                float_32 slope1 = (Results->AryPressure[2] - Results->AryPressure[1])/(Results->AryPosition[2] - Results->AryPosition[1]);
                float_32 slope2 = (Results->AryPressure[3] - Results->AryPressure[2])/(Results->AryPosition[3] - Results->AryPosition[2]);
                float_32 slope = slope1 - (slope2 - slope1);
                if (slope < (float_32)0.0)
                {
                    slope = 0.0;
                }
                else if (slope > slope1)
                {
                    slope = slope1;
                }
                Results->AryPressure[0] = slope*(Results->AryPosition[0] - Results->AryPosition[1]) + Results->AryPressure[1];
            }
        }
        else
        {
            /* Free up the 2nd point from effects of the 1st line segment. */
            Results->AryPressure[1] = Results->AryPosition[1] * arySlope[1] + aryOffset[1];

            { /* Extrapolate to get the 1st point by keeping a constant second derivative */
                float_32 slope1 = (Results->AryPressure[2] - Results->AryPressure[1])/(Results->AryPosition[2] - Results->AryPosition[1]);
                float_32 slope2 = (Results->AryPressure[3] - Results->AryPressure[2])/(Results->AryPosition[3] - Results->AryPosition[2]);
                float_32 slope = slope1 - (slope2 - slope1);
                if (slope < (float_32)0.0)
                {
                    slope = 0.0;
                }
                else if (slope > slope1)
                {
                    slope = slope1;
                }
                Results->AryPressure[0] = slope*(Results->AryPosition[0] - Results->AryPosition[1]) + Results->AryPressure[1];
            }
        }

        /* Free up the 2nd to last point from effects of the last line segment. */
        ii = LPS_CAL_CURVE_FIT_NUM_POINTS-2;

        Results->AryPressure[ii] = Results->AryPosition[ii] * arySlope[ii-1] + aryOffset[ii-1];

        { /* Extrapolate to find the last point based on simplified model of math to extrapolate linkage kinematics. */
            float_32 x1 = Results->AryPosition[LPS_CAL_CURVE_FIT_NUM_POINTS-2];
            float_32 y1 = Results->AryPressure[LPS_CAL_CURVE_FIT_NUM_POINTS-2];
            float_32 x2 = Results->AryPosition[LPS_CAL_CURVE_FIT_NUM_POINTS-3];
            float_32 y2 = Results->AryPressure[LPS_CAL_CURVE_FIT_NUM_POINTS-3];
            float_32 x3 = Results->AryPosition[LPS_CAL_CURVE_FIT_NUM_POINTS-4];
            float_32 y3 = Results->AryPressure[LPS_CAL_CURVE_FIT_NUM_POINTS-4];
            float_32 x = Results->AryPosition[LPS_CAL_CURVE_FIT_NUM_POINTS-1];

            float_32 K4;
            float_32 K3;
            float_32 yest1 = 0.0;
            float_32 yest2 = 0.0;

            if (y1 > y2)
            {
                K4 = ((x1*x1*y1*y1) - (x2*x2*y2*y2)) / (y1*y1-y2*y2);
                K3 = K4*y1*y1 - x1*x1*y1*y1;
                if (K4 > x*x)
                {
                    yest1 = (float_32)sqrt((double_64)(K3/(K4 - x*x)));
                }
            }

            if (y1 > y3)
            {
                K4 = ((x1*x1*y1*y1) - (x3*x3*y3*y3)) / (y1*y1-y3*y3);
                K3 = K4*y1*y1 - x1*x1*y1*y1;
                if (K4 > x*x)
                {
                    yest2 = (float_32)sqrt((double_64)(K3/(K4 - x*x)));
                }
            }

            if (yest1 > (float_32)0.0)
            {
                if (yest2 > (float_32)0.0)
                {
                    Results->AryPressure[LPS_CAL_CURVE_FIT_NUM_POINTS-1] = (yest1 + yest2)/(float_32)2.0;
                }
                else
                {
                    Results->AryPressure[LPS_CAL_CURVE_FIT_NUM_POINTS-1] = yest1;
                }
            }
            else
            {
                float_32 slope1 = (y1-y2)/(x1-x2);
                float_32 slope2 = (y2-y3)/(x2-x3);
                float_32 slopeNew = slope1 + (slope1 - slope2);
                Results->AryPressure[LPS_CAL_CURVE_FIT_NUM_POINTS-1] = slopeNew*(x-x1)+y1;
            }
        }
    }
}

/******************************************************************************
FUNCTION NAME: pcs_empty_cal3_main
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalGetLowerCurveFitResults(LpsCalCurveFitResults_t *Results)
{
    LpsCalGetCurveFitResults(&LpsCalWrkTbl.CurveFitInfo.LpsCalLowerCurveFitData, Results);
}

/******************************************************************************
FUNCTION NAME: LpsCalCompareCurveFitResults
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
boolean LpsCalCompareCurveFitResults(LpsCalCurveFitResults_t const * Results1,
        LpsCalCurveFitResults_t const * Results2, boolean IsRaise)
{
    unsigned_16 ii;
    float_32 pctDeltaAbsMax = 0.0;
    float_32 pctDeltaRangeMax = -100.0;
    float_32 pctDeltaRangeMin = 100.0;
    float_32 absLimit, rangeLimit;

	LpsCalCfg_t *pCalCfg = &LpsCalWrkTbl.Cfg;

    /* Average the dependent axis results from the linear fits that surround it. */
    for (ii = 0; ii < LPS_CAL_CURVE_FIT_NUM_POINTS; ii++)
    {
        float_32 position = Results1->AryPosition[ii];
        float_32 pressure1 = Results1->AryPressure[ii];
        /* Check on Pressure above 0 removed - due to LWL pressure/pos curve */

        float_32 pressure2 = LpsLookupExtrap(position, Results2->AryPosition, Results2->AryPressure, LPS_CAL_CURVE_FIT_NUM_POINTS);
        float_32 pctDelta = ((pressure2 / pressure1) - (float_32)1.0) * (float_32)100.0;
        float_32 pctDeltaAbs = pctDelta;

        if (pctDeltaAbs < 0)
        {
            pctDeltaAbs = (float_32)-1.0 * pctDeltaAbs;
        }

        /* Only include the inner points for the range check because
            the outer points are extrapolated and dependent upon the inner points.
        */
        if ((ii > 2) && (ii < (LPS_CAL_CURVE_FIT_NUM_POINTS - 1)))
        {
            if (ii <= 3)
            {
                pctDeltaRangeMax = pctDelta;
                pctDeltaRangeMin = pctDelta;
            }
            else if (pctDelta > pctDeltaRangeMax)
            {
                pctDeltaRangeMax = pctDelta;
            }
            else if (pctDelta < pctDeltaRangeMin)
            {
                pctDeltaRangeMin = pctDelta;
            }

            if (pctDeltaAbs > pctDeltaAbsMax)
            {
                pctDeltaAbsMax = pctDeltaAbs;
            }
            /* Canape / Debug purposes */
            LpsCalWrkTbl.Info.LpsCalPctAbsCopy = pctDeltaAbsMax;
        }

    }

    if (IsRaise)
    {
        absLimit = pCalCfg->LiftCylDiffLimits.RaiseCalPercDiffAbsLimit;
        rangeLimit = pCalCfg->LiftCylDiffLimits.RaiseCalPercDiffRangeLimit;
    }
    else
    {
        absLimit = pCalCfg->LiftCylDiffLimits.LowerCalPercDiffRangeLimit;
        rangeLimit = pCalCfg->LiftCylDiffLimits.LowerCalPercDiffRangeLimit;
    }

    { /* Check results against the limits */
        float_32 pctDeltaRange = pctDeltaRangeMax - pctDeltaRangeMin;
        LpsCalWrkTbl.Info.LpsCalPctDiffRangeCopy = pctDeltaRange;

        if (pctDeltaAbsMax > absLimit)
        {
            return FALSE;
        }
        else if (pctDeltaRange > rangeLimit)
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
}

/******************************************************************************
FUNCTION NAME: LpsCalCompareCurveFitResultRatios
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
boolean LpsCalCompareCurveFitResultRatios(LpsCalCurveFitResults_t const * Results1,
        LpsCalCurveFitResults_t const * Results2, boolean IsRaise)
{
    float_32 rangeLimit;
    LpsCalCfg_t *pCalCfg = &LpsCalWrkTbl.Cfg;

    if (TRUE == IsRaise)
    {
        rangeLimit = pCalCfg->LiftCylDiffLimits.RaiseCalPercDiffRangeLimit;
    }
    else
    {
        rangeLimit = pCalCfg->LiftCylDiffLimits.LowerCalPercDiffRangeLimit;
    }

    if ((Results1->AverageReferencePressure > (float_32)0.0) &&
        (Results2->AverageReferencePressure > (float_32)0.0))
    {
        float_32 pctDelta = (Results1->AverageDeltaPFromReference / Results1->AverageReferencePressure) - (Results2->AverageDeltaPFromReference / Results2->AverageReferencePressure);

        if (pctDelta < 0)
        {
            pctDelta = (float_32)-100.0 * pctDelta;
        }
        else
        {
            pctDelta = (float_32)100.0 * pctDelta;
        }

        if (pctDelta > rangeLimit)
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
    else
    {
        return FALSE;
    }
}

/******************************************************************************
FUNCTION NAME: LpsCalCombineCurveFitResults
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalCombineCurveFitResults(LpsCalCurveFitResults_t const * Results1,
        LpsCalCurveFitResults_t const * Results2, LpsCalCurveFitResults_t* FinalResults)
{
    unsigned_16 ii;

    for (ii = 0; ii < LPS_CAL_CURVE_FIT_NUM_POINTS; ++ii) {
        float_32 position = Results1->AryPosition[ii];
        float_32 pressure1 = Results1->AryPressure[ii];
        float_32 pressure2 = LpsLookupExtrap(position, Results2->AryPosition, Results2->AryPressure, LPS_CAL_CURVE_FIT_NUM_POINTS);

        FinalResults->AryPosition[ii] = position;
        FinalResults->AryPressure[ii] = (pressure1 + pressure2) / 2.f;
    }

    FinalResults->AverageVelocity = (Results1->AverageVelocity + Results2->AverageVelocity) / 2.f;
    FinalResults->AverageReferencePressure = (Results1->AverageReferencePressure + Results2->AverageReferencePressure) / 2.f;
    FinalResults->AverageDeltaPFromReference = (Results1->AverageDeltaPFromReference + Results2->AverageDeltaPFromReference) / 2.f;

    FinalResults->AryAverageIMUAccel[0] = (Results1->AryAverageIMUAccel[0] + Results2->AryAverageIMUAccel[0]) / 2.f;
    FinalResults->AryAverageIMUAccel[1] = (Results1->AryAverageIMUAccel[1] + Results2->AryAverageIMUAccel[1]) / 2.f;
    FinalResults->AryAverageIMUAccel[2] = (Results1->AryAverageIMUAccel[2] + Results2->AryAverageIMUAccel[2]) / 2.f;
    FinalResults->AveragePitch = (Results1->AveragePitch + Results2->AveragePitch) / 2.f;
    FinalResults->AverageRoll = (Results1->AverageRoll + Results2->AverageRoll) / 2.f;
}


void LpsCalRunUpdate(void)
{
	LpsCalLiftCalUpdateImplOverrides();
	LpsCalTiltCalUpdateImplOverrides();
	LpsCalUpdateInfo();
}

static void LpsCalTiltCalUpdateImplOverrides(void)
{
    LpsCalStatus_t   *pStatus   = &LpsCalWrkTbl.Status;
    LpsCalUpdate_t   *pUpdate   = &LpsCalWrkTbl.Update;
    LpsCalOv_t       *pCalOv    = &LpsCalWrkTbl.Ov;
    LpsCalInfo_t     *pCalInfo  = &LpsCalWrkTbl.Info;

    if (FALSE == pStatus->CalInProgress)
    {
        LpsCalStopTiltOverrides();
    }

    switch (pCalOv->LpsCalTiltOv.LpsCalTiltOvrState) {
    case (LPS_CAL_OVR_STATE_INACTIVE):
    {
        LpsCalAppInfSetTiltCmdOvr(0.f, 0.f);

        if ((pCalOv->LpsCalTiltOv.LpsCalTiltOvrStartRequest) && (!pCalInfo->CalTiltOverrideComplete) ) {
            // Ensure valve commands are zero, we are at bottom of lift and in full detent
            if ((pUpdate->LiftLeverInfo.ValveCmdPercent != 0.f) || (pUpdate->TiltValveCmdPercent !=0.f) ||
                    (!pCalOv->LiftBottomFlag) || (!pUpdate->LiftLeverInfo.InRaiseDetent)) {
                // wait until command is zero and we are at the bottom of lift
            }
            else {
                // Reset workspace and Start to Override
                clock_gettime(CLOCK_MONOTONIC, &pCalOv->LpsCalTiltOv.StartTime);
                pCalOv->LpsCalTiltOv.LpsCalTiltOvrState = LPS_CAL_OVR_STATE_PENDING_ACTIVE;
                pCalOv->LpsCalTiltOv.TiltNoiseMin = pCalOv->LpsCalTiltOv.TiltNoiseMax = pUpdate->TiltExtension;
                pCalOv->LpsCalTiltOv.LpsCalTiltOvrStartRequest = FALSE;
                pCalInfo->CalTiltOverrideComplete = FALSE;
                pCalInfo->CalTiltOverrideFail = FALSE;
            }
        }
        break;
    }
    case (LPS_CAL_OVR_STATE_PENDING_ACTIVE):
    {
        /* while we wait before starting tilt override, check to see if it is time to collect min/max
         * tilt extension noise
         */
        struct timespec now, start;
        start = pCalOv->LpsCalTiltOv.StartTime;
        clock_gettime(CLOCK_MONOTONIC, &now);

        float elapsed_secs = (now.tv_sec - start.tv_sec) + 1e-9 * (now.tv_nsec - start.tv_nsec);
        float_32 tilt_ext_max = pCalOv->LpsCalTiltOv.TiltNoiseMax;
        float_32 tilt_ext_min = pCalOv->LpsCalTiltOv.TiltNoiseMin;
        float_32 tilt_ext_cur = pUpdate->TiltExtension;

        if (pCalOv->LpsCalTiltOv.LpsCalTiltOvrStopRequest) {
            pCalOv->LpsCalTiltOv.LpsCalTiltOvrState = LPS_CAL_OVR_STATE_INACTIVE;
            pCalOv->LpsCalTiltOv.LpsCalTiltOvrStopRequest = FALSE;
        }
        else if (elapsed_secs > LpsCalTiltOvrCfg.WaitSecondsBeforeDump) {
            // we are done waiting and collecting data
            pCalOv->LpsCalTiltOv.LpsCalTiltOvrState = LPS_CAL_OVR_STATE_ACTIVE;

            //capture new start time
            pCalOv->LpsCalTiltOv.StartTime = now;

            // calculate desired tilt extension
            float distace_mm = 0;
            distace_mm = LpsCalTiltOvrCfg.DesiredTiltExtensionFactor * (tilt_ext_max-tilt_ext_min);

            //limit desired tilt extension
            if (distace_mm < LpsCalTiltOvrCfg.MinTiltExtensionLimit) {
                distace_mm = LpsCalTiltOvrCfg.MinTiltExtensionLimit;
            }
            else if (distace_mm > LpsCalTiltOvrCfg.MaxTiltExtensionLimit) {
                distace_mm = LpsCalTiltOvrCfg.MaxTiltExtensionLimit;
            }
            else {
                // do nothing
            }

            pCalOv->LpsCalTiltOv.DesiredTiltExtmm = tilt_ext_min - distace_mm;

            // reset count of samples at desired tilt extension
            pCalOv->LpsCalTiltOv.CountOfSamples = 0;

            // start commanding dump at initial dump %
            LpsCalAppInfSetTiltCmdOvr(0.0, LpsCalTiltOvrCfg.DumpStartCmd);

            // reset the command to start command
            pCalOv->LpsCalTiltOv.TiltDumpCmdOvr = LpsCalTiltOvrCfg.DumpStartCmd;
        }
        else if (elapsed_secs >= (LpsCalTiltOvrCfg.WaitSecondsBeforeDump - LpsCalTiltOvrCfg.TiltExtensionNoiseWindowSeconds) ) {
            // start windowing for min/max tilt extension
            if (tilt_ext_cur > tilt_ext_max) {
                pCalOv->LpsCalTiltOv.TiltNoiseMax = tilt_ext_cur;
            }
            else if (tilt_ext_cur < tilt_ext_min) {
                pCalOv->LpsCalTiltOv.TiltNoiseMin = tilt_ext_cur;
            }
            else {
                // do nothing
            }
        }
        else {
            //still waiting, keep updating tilt extension min/max
            pCalOv->LpsCalTiltOv.TiltNoiseMin = tilt_ext_cur;
            pCalOv->LpsCalTiltOv.TiltNoiseMax = tilt_ext_cur;
        }
        break;
    }

    case LPS_CAL_OVR_STATE_ACTIVE:
    {
        struct timespec now, start;
        start = pCalOv->LpsCalTiltOv.StartTime;
        clock_gettime(CLOCK_MONOTONIC, &now);

        float elapsed_secs = (now.tv_sec - start.tv_sec) + 1e-9 * (now.tv_nsec - start.tv_nsec);

        if (pCalOv->LpsCalTiltOv.LpsCalTiltOvrStopRequest) {
            pCalOv->LpsCalTiltOv.LpsCalTiltOvrState = LPS_CAL_OVR_STATE_INACTIVE;
            pCalOv->LpsCalTiltOv.LpsCalTiltOvrStopRequest = FALSE;

            /* Since we are in active tilt override, we will fail the cal so that it would need to be restarted
             * if for some reason it was stopped before completing tilt overides control */
            pCalInfo->CalTiltOverrideComplete = TRUE;
            pCalInfo->CalTiltOverrideFail = TRUE;
        }
        else if (pUpdate->TiltExtension < pCalOv->LpsCalTiltOv.DesiredTiltExtmm)
        {
            // increment count at or greater than desired tilt ext and check if we are stable
            pCalOv->LpsCalTiltOv.CountOfSamples++;
            if (pCalOv->LpsCalTiltOv.CountOfSamples >= LpsCalTiltOvrCfg.NumberofSamplesAtDesiredExt){
                // we are done successfully, set override commands to 0
                pCalOv->LpsCalTiltOv.LpsCalTiltOvrState = LPS_CAL_OVR_STATE_INACTIVE;
                LpsCalAppInfSetTiltCmdOvr(0.f, 0.f);
                pCalInfo->CalTiltOverrideComplete = TRUE;
                pCalInfo->CalTiltOverrideFail = FALSE;
            }
        }
        else if (elapsed_secs > LpsCalTiltOvrCfg.DumpTimeoutSeconds)
        {
            // fail, we timed out, set override commands to 0
            LpsCalAppInfSetTiltCmdOvr(0.f, 0.f);
            pCalOv->LpsCalTiltOv.LpsCalTiltOvrState = LPS_CAL_OVR_STATE_INACTIVE;
            pCalInfo->CalTiltOverrideComplete = TRUE;
            pCalInfo->CalTiltOverrideFail = TRUE;
        }
        else if (pCalOv->LpsCalTiltOv.TiltDumpCmdOvr < LpsCalTiltOvrCfg.MaxDumpCommandLimit) {
            // fail, we reached maximum command limit without getting to desired extension, set override to 0
            LpsCalAppInfSetTiltCmdOvr(0.f, 0.f);
            pCalOv->LpsCalTiltOv.LpsCalTiltOvrState = LPS_CAL_OVR_STATE_INACTIVE;
            pCalInfo->CalTiltOverrideComplete = TRUE;
            pCalInfo->CalTiltOverrideFail = TRUE;
        }
        else {
            // reset count at desired tilt ext
            pCalOv->LpsCalTiltOv.CountOfSamples = 0;

            // calculate new command override at the configured rate
            pCalOv->LpsCalTiltOv.TiltDumpCmdOvr = LpsCalTiltOvrCfg.DumpStartCmd +
                    (LpsCalTiltOvrCfg.DumpCommandIncRateLimit * elapsed_secs);

            LpsCalAppInfSetTiltCmdOvr(0.f, pCalOv->LpsCalTiltOv.TiltDumpCmdOvr );
        }
        break;
    }

    default:
        pCalOv->LpsCalTiltOv.LpsCalTiltOvrState = LPS_CAL_OVR_STATE_INACTIVE;
        pCalOv->LpsCalTiltOv.LpsCalTiltOvrStartRequest = FALSE;
        break;
    }
}

static void LpsCalLiftCalUpdateImplOverrides(void)
{
	LpsCalStatus_t	 *pStatus 	= &LpsCalWrkTbl.Status;
	LpsCalUpdate_t	 *pUpdate 	= &LpsCalWrkTbl.Update;
        LpsCalOv_t	 *pCalOv  	= &LpsCalWrkTbl.Ov;
        LpsCalInfo_t 	 *pCalInfo 	= &LpsCalWrkTbl.Info;
        LpsCalCfg_t      *pCalCfg       = &LpsCalWrkTbl.Cfg;

    if (FALSE == pStatus->CalInProgress)
    {
        LpsCalStopLiftOverrides();
    }

    switch (pCalOv->LpsCalOvrState) {

        case (LPS_CAL_OVR_STATE_INACTIVE):
        {
            if (pCalInfo->LpsCalOvrStartRequest)
            {
                float_32 curRaiseCommandLimit = 0.0;
                float_32 curLowerCommandLimit = 0.0;

                if (pUpdate->LiftLeverInfo.ValveCmdPercent > 0)
                {
                    curRaiseCommandLimit = pUpdate->LiftLeverInfo.ValveCmdPercent;
                }
                else if (pUpdate->LiftLeverInfo.ValveCmdPercent < 0)
                {
                    curLowerCommandLimit = pUpdate->LiftLeverInfo.ValveCmdPercent;
                }

                LpsCalLiftCalOvrCtrlInit(curRaiseCommandLimit, curLowerCommandLimit);

                LpsCalAppInfSetCalOvrActive();
                LpsCalAppInfSetLiftCmdLimit(curRaiseCommandLimit, curLowerCommandLimit);
                pCalInfo->LpsCalOvrStartRequest = FALSE;
                pCalOv->LpsCalOvrState = LPS_CAL_OVR_STATE_PENDING_ACTIVE;
            }
            break;
        }
        case (LPS_CAL_OVR_STATE_PENDING_ACTIVE):
        {
            float_32 curRaiseCommandLimit = LpsCalOvrCtrlGetRaiseCmdLimit();
            float_32 curLowerCommandLimit = LpsCalOvrCtrlGetLowerCmdLimit();

            /* Wait until operator commands go to 0 and lever centered prior to transitioning out */
            if (pUpdate->LiftLeverInfo.ValveCmdPercent > 0.f)
            {
                if (pUpdate->LiftLeverInfo.ValveCmdPercent < curRaiseCommandLimit)
                {
                    curRaiseCommandLimit = pUpdate->LiftLeverInfo.ValveCmdPercent;
                }
                curLowerCommandLimit = 0.0f;
            }
            else if (pUpdate->LiftLeverInfo.ValveCmdPercent < 0.f)
            {
                if (pUpdate->LiftLeverInfo.ValveCmdPercent > curLowerCommandLimit)
                {
                    curLowerCommandLimit = pUpdate->LiftLeverInfo.ValveCmdPercent;
                }
                curRaiseCommandLimit = 0.0f;
            }
            else
            {
                curRaiseCommandLimit = 0.0f;
                curLowerCommandLimit = 0.0f;
            }

            LpsCalLiftCalOvrCtrlInit(curRaiseCommandLimit, curLowerCommandLimit);

            LpsCalAppInfSetLiftCmdLimit(curRaiseCommandLimit, curLowerCommandLimit);

            /* If the outputs command limits have reached zero, and the lever is centered
             * and we have acknowledge that override is active */
            if (((float_32)0.0f == curRaiseCommandLimit) &&
                ((float_32)0.0f == curLowerCommandLimit) &&
                (TRUE == pUpdate->LiftLeverInfo.InCenter) &&
                (pUpdate->CalOvrAcknowledge) )
            {
                {
                    /* Transition to active. */
                    pCalOv->LpsCalOvrState = LPS_CAL_OVR_STATE_ACTIVE;
                }
            }

            /* If a stop was requested while pending active, disable overrides and
                transition back to inactive
            */
            if (TRUE == pCalInfo->LpsCalOvrStopRequest)
            {
                LpsCalAppInfSetCalOvrInactive();
                pCalInfo->LpsCalOvrStopRequest = FALSE;
                pCalOv->LpsCalOvrState = LPS_CAL_OVR_STATE_INACTIVE;
            }

            pCalInfo->LpsCalOvrStartRequest = FALSE;
            break;
        }
        case (LPS_CAL_OVR_STATE_ACTIVE):
        {
            float_32 curRaiseCommandLimit = 0.0;
            float_32 curLowerCommandLimit = 0.0;

            /* Overrides are active */
            if (pCalInfo->LpsCalOvrStopRequest)
            {
                /* Stop was requested, limit the valve commands to the current values
                    and transition to pending inactive
                */
                if (pUpdate->LiftLeverInfo.ValveCmdPercent > 0.f)
                {
                    curRaiseCommandLimit = pUpdate->LiftLeverInfo.ValveCmdPercent;
                }
                else if (pUpdate->LiftLeverInfo.ValveCmdPercent < 0.f)
                {
                    curLowerCommandLimit = pUpdate->LiftLeverInfo.ValveCmdPercent;
                }

                LpsCalLiftCalOvrCtrlInit(curRaiseCommandLimit, curLowerCommandLimit);

                pCalInfo->LpsCalOvrStopRequest = FALSE;
                pCalOv->LpsCalOvrState = LPS_CAL_OVR_STATE_PENDING_INACTIVE;
            }
            else
            {
                /* Overrides continue to be active, calculate the command limits */
                LpsCalLiftCalOvrCtrlUpdate(pUpdate->LiftCylLengthNorm.Val);

                curRaiseCommandLimit = LpsCalOvrCtrlGetRaiseCmdLimit();
                curLowerCommandLimit = LpsCalOvrCtrlGetLowerCmdLimit();
            }

            LpsCalAppInfSetLiftCmdLimit(curRaiseCommandLimit, curLowerCommandLimit);

            pCalInfo->LpsCalOvrStartRequest = FALSE;
            break;
        }
        case (LPS_CAL_OVR_STATE_PENDING_INACTIVE):
        {
            float_32 curRaiseCommandLimit = LpsCalOvrCtrlGetRaiseCmdLimit();
            float_32 curLowerCommandLimit = LpsCalOvrCtrlGetLowerCmdLimit();

            /* Wait until operator commands go to 0 and lever centered prior to transitioning out */
            if (pUpdate->LiftLeverInfo.ValveCmdPercent > 0.f)
            {
                float_32 rampStep = LpsCalOvrCtrlRaiseCfg.CommandDecRateLimit * pCalCfg->ExecPeriodSec;

                // Ramp down until current raise limit is 0
                if (curRaiseCommandLimit > rampStep)
                {
                    curRaiseCommandLimit = curRaiseCommandLimit - rampStep;
                }
                // If ramping below 0, set limit to 0
                else {
                    curRaiseCommandLimit = 0;
                }
                // If op ramps down faster, set new limit to that
                if (pUpdate->LiftLeverInfo.ValveCmdPercent < curRaiseCommandLimit)
                {
                    curRaiseCommandLimit = pUpdate->LiftLeverInfo.ValveCmdPercent;
                }
                curLowerCommandLimit = 0.0;
            }
            else if (pUpdate->LiftLeverInfo.ValveCmdPercent < 0.f)
            {
                float_32 rampStep = LpsCalOvrCtrlLowerCfg.CommandDecRateLimit * pCalCfg->ExecPeriodSec;

                // Ramp up until current lower limit is 0
                if (curLowerCommandLimit < rampStep)
                {
                    curLowerCommandLimit = curLowerCommandLimit + rampStep;
                }
                // If ramping above 0, set limit to 0
                else {
                    curLowerCommandLimit = 0;
                }
                // If op ramps up faster, set new limit to that
                if (pUpdate->LiftLeverInfo.ValveCmdPercent > curLowerCommandLimit)
                {
                    curLowerCommandLimit = pUpdate->LiftLeverInfo.ValveCmdPercent;
                }
                curRaiseCommandLimit = 0.0f;
            }
            else
            {
                curRaiseCommandLimit = 0.0f;
                curLowerCommandLimit = 0.0f;
            }

            LpsCalLiftCalOvrCtrlInit(curRaiseCommandLimit, curLowerCommandLimit);
            LpsCalAppInfSetLiftCmdLimit(curRaiseCommandLimit, curLowerCommandLimit);

            /* If the outputs command limits have reached zero, and the lever is centered,
                disable the overrides and transition to the inactive state.
            */
            if (((float_32)0.0f == curRaiseCommandLimit) &&
                ((float_32)0.0f == curLowerCommandLimit) &&
                (TRUE == pUpdate->LiftLeverInfo.InCenter))
            {
                LpsCalAppInfSetCalOvrInactive();
                pCalOv->LpsCalOvrState = LPS_CAL_OVR_STATE_INACTIVE;
            }
            break;
        }
        default:
        {
            LpsCalAppInfSetCalOvrInactive();
            pCalOv->LpsCalOvrState = LPS_CAL_OVR_STATE_INACTIVE;
            pCalInfo->LpsCalOvrStartRequest = FALSE;
            break;
        }
    }
}

static void LpsCalUpdateInfo(void)
{
	LpsCalUpdate_t 	*pCalUpdate 	= &LpsCalWrkTbl.Update;
	LpsCalStatus_t 	*pCalStatus 	= &LpsCalWrkTbl.Status;
	LpsCalInfo_t   	*pCalInfo   	= &LpsCalWrkTbl.Info;
	LpsCalOv_t 		*pCalOv 		= &LpsCalWrkTbl.Ov;
	LpsCalCurveFitInfo_t *pCurveFitInfo = &LpsCalWrkTbl.CurveFitInfo;

    if (TRUE == pCalStatus->CalInProgress) {
        float_32 pos = pCalUpdate->LiftCylLengthNorm.Val;
        float_32 press = pCalUpdate->LiftDiffPress.Val;
        float_32 vel = pCalUpdate->LiftCylVel.Val;

        // Update curve fit data when calibration is in progress.
        LpsCalCurveFitDataUpdate(&pCurveFitInfo->LpsCalRaiseCurveFitData, pos, press);
        LpsCalCurveFitDataUpdate(&pCurveFitInfo->LpsCalLowerCurveFitData, pos, press);

        if (pos < pCalInfo->CalBottomOfCalLiftHt) {
            if (pCalInfo->CalLowerActive) {
                pCalInfo->CalLowerComplete = TRUE;
                pCalInfo->CalLowerActive = FALSE;

                if (0xFF == pCalInfo->CalLowerStatus) {
                     pCalInfo->CalLowerStatus = LPS_CAL_LIFT_GOOD;
                }
            }

            pCalOv->LiftBottomFlag = TRUE;
            pCalOv->LiftTopFlag = FALSE;
        }
        else if (pos <= pCalInfo->CalTopOfCalLiftHt) {
            if (TRUE == pCalOv->LiftBottomFlag) {
                /* Transition from bottom to in range */
                if (FALSE == pCalInfo->CalRaiseComplete) {
                    pCalInfo->CalRaiseActive = TRUE;
                    pCalInfo->CalRaiseStatus = 0xFF;
                }
            }


            if (TRUE == pCalInfo->CalRaiseActive) {
                // Collect curve fit data when in range.
                LpsCalCurveFitDataCollect(&pCurveFitInfo->LpsCalRaiseCurveFitData,
                        pos, press, vel, pCalUpdate->TiltAngleABCPercent.Val,
                        &pCalUpdate->ReferenceIMUData);

                /* Update IMU Cals */
                LpsCalIMUUpdate(LpsCalIMURaise, pCalUpdate->LiftCylLengthNorm.Val,
                        pCalUpdate->TiltHePressure.Val, pCalUpdate->TiltRePressure.Val,
                        pCalUpdate->LiftDiffPress.Val, &pCalUpdate->EEFIMUData,
                        pCalUpdate->LiftAngle, pCalUpdate->TiltExtension,
                        pCalUpdate->SteeringAngle);

            }

            if (TRUE == pCalOv->LiftTopFlag) {
                /* Transition from top to in range */
                if (FALSE == pCalInfo->CalLowerComplete) {
                    pCalInfo->CalLowerActive = TRUE;
                    pCalInfo->CalLowerStatus = 0xFF;
                }
            }

            if (TRUE == pCalInfo->CalLowerActive) {
                // Collect curve fit data when in range.
                LpsCalCurveFitDataCollect(&pCurveFitInfo->LpsCalLowerCurveFitData,
                        pos, press, vel, pCalUpdate->TiltAngleABCPercent.Val,
                        &pCalUpdate->ReferenceIMUData);

                /* Update IMU Cals */
                LpsCalIMUUpdate(LpsCalIMULower, pCalUpdate->LiftCylLengthNorm.Val,
                        pCalUpdate->TiltHePressure.Val, pCalUpdate->TiltRePressure.Val,
                        pCalUpdate->LiftDiffPress.Val, &pCalUpdate->EEFIMUData,
                        pCalUpdate->LiftAngle, pCalUpdate->TiltExtension,
                        pCalUpdate->SteeringAngle);

            }

            pCalOv->LiftBottomFlag = FALSE;
            pCalOv->LiftTopFlag = FALSE;
        }
        else {
            if (pCalInfo->CalRaiseActive) {
                pCalInfo->CalRaiseComplete = TRUE;
                pCalInfo->CalRaiseActive = FALSE;

                if (0xFF == pCalInfo->CalRaiseStatus) {
                    pCalInfo->CalRaiseStatus = LPS_CAL_LIFT_GOOD;
                }
            }

            pCalOv->LiftBottomFlag = FALSE;
            pCalOv->LiftTopFlag = TRUE;
        }
    }
    else {
        pCalInfo->CalRaiseActive = FALSE;
        pCalInfo->CalRaiseComplete = FALSE;

        pCalInfo->CalLowerActive = FALSE;
        pCalInfo->CalLowerComplete = FALSE;

        pCalInfo->CalRaiseStatus = 0xFF;
        pCalInfo->CalLowerStatus = 0xFF;

        pCalOv->LiftBottomFlag = FALSE;
        pCalOv->LiftTopFlag = FALSE;
    }
}

/******************************************************************************
FUNCTION NAME: LpsCalCurveFitDataReset
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
static void LpsCalCurveFitDataReset(LpsCalCurveFitData_t* FitData, LpsCalCurveFitResults_t const * ReferenceResults)
{
    static const LpsCalCurveFitData_t zeroFitData = {0};

    *FitData = zeroFitData;

    FitData->MaxTiltAngleABCPct = -1.0;
    FitData->LiftPositionOffRack = -1.0;

    {
        unsigned_16 ii;

        for (ii = 0; ii < LPS_CAL_CURVE_FIT_NUM_POINTS; ++ii) {
            FitData->AryPosition[ii] = LpsCalWrkTbl.Info.LpsCalPositionsDefault[ii];
        }
    }

    FitData->ReferenceResults = ReferenceResults;

    // Initialize the filters
    cpm_filter_band_stop_filter_init(&FitData->DeltaPFilter1,
            LpsCalWrkTbl.Cfg.StageOneCf, LpsCalWrkTbl.Cfg.DampingRatio, LpsCalWrkTbl.Cfg.ExecPeriodSec);

    cpm_filter_band_stop_filter_init(&FitData->DeltaPFilter2,
            LpsCalWrkTbl.Cfg.StageTwoCf, LpsCalWrkTbl.Cfg.DampingRatio, LpsCalWrkTbl.Cfg.ExecPeriodSec);

    cpm_filter_band_stop_filter_init(&FitData->DeltaPFilter3,
            LpsCalWrkTbl.Cfg.StageThreeCf, LpsCalWrkTbl.Cfg.DampingRatio, LpsCalWrkTbl.Cfg.ExecPeriodSec);
}

/******************************************************************************
FUNCTION NAME: LpsCalCurveFitDataUpdate
DESCRIPTION: Update every loop during calibration.
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
static void LpsCalCurveFitDataUpdate(LpsCalCurveFitData_t* FitData, float_32 Pos, float_32 Press)
{
    if (NULL != FitData->ReferenceResults) {
        float_32 referencePress = LpsLookupExtrap(Pos, FitData->ReferenceResults->AryPosition,
                FitData->ReferenceResults->AryPressure, LPS_CAL_CURVE_FIT_NUM_POINTS);
        float_32 deltaP = Press - referencePress;

        // Filter deltaP
        deltaP = cpm_filter_band_stop_filter(&FitData->DeltaPFilter1, deltaP);
        deltaP = cpm_filter_band_stop_filter(&FitData->DeltaPFilter2, deltaP);
        deltaP = cpm_filter_band_stop_filter(&FitData->DeltaPFilter3, deltaP);

        FitData->ReferencePressure = referencePress;
        FitData->DeltaPFromReference = deltaP;
    }
    else {
        cpm_filter_band_stop_filter_reset(&FitData->DeltaPFilter1);
        cpm_filter_band_stop_filter_reset(&FitData->DeltaPFilter2);
        cpm_filter_band_stop_filter_reset(&FitData->DeltaPFilter3);

        FitData->ReferencePressure = 0.f;
        FitData->DeltaPFromReference = 0.f;
    }
}

/******************************************************************************
FUNCTION NAME: LpsCalCurveFitDataCollect
DESCRIPTION: Collect data only when in the correct range.
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
static void LpsCalCurveFitDataCollect(LpsCalCurveFitData_t* FitData, float_32 Pos,
        float_32 Press, float_32 Vel, float_32 TiltAngleABCPct,
        LpsIMUData_t const * ReferenceIMUData)
{
    FitData->TotalNumPoints += (float_32)1.0;
    FitData->SumVelocity += Vel;

    // Accumulate the reference IMU data
    FitData->ArySumIMUAccel[0] += ReferenceIMUData->LinAcc[0];
    FitData->ArySumIMUAccel[1] += ReferenceIMUData->LinAcc[1];
    FitData->ArySumIMUAccel[2] += ReferenceIMUData->LinAcc[2];
    FitData->SumPitch += ReferenceIMUData->Pitch;
    FitData->SumRoll += ReferenceIMUData->Roll;

    // Accumulate the velocity compensation data
    FitData->SumDeltaPFromReference += FitData->DeltaPFromReference;
    FitData->SumReferencePressure += FitData->ReferencePressure;

    /* Determine the Off-Rack Lift Position */
    if (FitData->MaxTiltAngleABCPct < 0) {
        FitData->MaxTiltAngleABCPct = TiltAngleABCPct;
    }

    if (Vel > 0) {
        if (TiltAngleABCPct > FitData->MaxTiltAngleABCPct) {
            FitData->MaxTiltAngleABCPct = TiltAngleABCPct;
        }

        if (TiltAngleABCPct > (FitData->MaxTiltAngleABCPct - (float_32)0.5)) {
            FitData->LiftPositionOffRack = Pos;
        }
    }
    else if (Vel < 0) {
        if (TiltAngleABCPct >= (FitData->MaxTiltAngleABCPct + (float_32)0.5)) {
            FitData->LiftPositionOffRack = Pos;
            FitData->MaxTiltAngleABCPct = TiltAngleABCPct;
        }
    }

    /* Grab the new data points */
    if ((Pos >= FitData->AryPosition[0]) &&
        (Pos <= FitData->AryPosition[LPS_CAL_CURVE_FIT_NUM_POINTS-1])) {
        unsigned_16 dataIndex = LPS_CAL_CURVE_FIT_NUM_POINTS - 2;
        unsigned_16 ii;
        for (ii = 1; ii < LPS_CAL_CURVE_FIT_NUM_POINTS; ii++) {
            if (Pos <= FitData->AryPosition[ii]) {
                dataIndex = (unsigned_16)(ii - 1);
                break;
            }
        }

        FitData->AryNumPoints[dataIndex] += (float_32)1.0;
        FitData->ArySumX[dataIndex] += Pos;
        FitData->ArySumXX[dataIndex] += (Pos*Pos);
        FitData->ArySumXY[dataIndex] += (Pos*Press);
        FitData->ArySumY[dataIndex] += Press;

        LpsCalPrint(LPSCAL_LOG_INFO, "AryNumPoints %f ArySumX %f ArySumXX %f ArySumXY %f ArySumY %f",
              FitData->AryNumPoints[dataIndex],
              FitData->ArySumX[dataIndex],
              FitData->ArySumXX[dataIndex],
              FitData->ArySumXY[dataIndex],
              FitData->ArySumY[dataIndex]);
    }
}


static void LpsCalLiftCalOvrCtrlInit(float_32 initRaiseCommand, float_32 initLowerCommand)
{
	LpsCalCurveFitInfo_t *pCurveFitInfo = &LpsCalWrkTbl.CurveFitInfo;
    pCurveFitInfo->LpsCalOvrCtrlRaiseData.CurCommandLimit = initRaiseCommand;
    pCurveFitInfo->LpsCalOvrCtrlRaiseData.MinCommandLimit = 0.0;
    pCurveFitInfo->LpsCalOvrCtrlLowerData.CurCommandLimit = initLowerCommand;
    pCurveFitInfo->LpsCalOvrCtrlLowerData.MinCommandLimit = 0.0;
}

void LpsCalAppInfSetCalOvrActive(void)
{
	LpsCalOv_t		*pCalOv = &LpsCalWrkTbl.Ov;

    pCalOv->LpsCalAppInfRaiseCmdLmt = LPS_CAL_APP_MAX_RAISE_CMD;
    pCalOv->LpsCalAppInfLowerCmdLmt = LPS_CAL_APP_MAX_LOWER_CMD;
    pCalOv->LpsCalAppInfRackCmd = LPS_CAL_APP_MIN_RACK_CMD;
    pCalOv->LpsCalAppInfDumpCmd = LPS_CAL_APP_MIN_DUMP_CMD;
    pCalOv->LpsCalAppInfEngSpdLmt = LPS_CAL_APP_MAX_ENG_SPD*(1UL<<3);
    pCalOv->LpsCalAppInfCalOvrActive = TRUE;

}

void LpsCalAppInfSetCalOvrInactive(void)
{
    LpsCalOv_t		*pCalOv = &LpsCalWrkTbl.Ov;

    pCalOv->LpsCalAppInfCalOvrActive = FALSE;
    pCalOv->LpsCalAppInfRaiseCmdLmt = LPS_CAL_APP_MAX_RAISE_CMD;
    pCalOv->LpsCalAppInfLowerCmdLmt = LPS_CAL_APP_MAX_LOWER_CMD;
    pCalOv->LpsCalAppInfRackCmd = LPS_CAL_APP_MIN_RACK_CMD;
    pCalOv->LpsCalAppInfDumpCmd = LPS_CAL_APP_MIN_DUMP_CMD;
    pCalOv->LpsCalAppInfEngSpdLmt = LPS_CAL_APP_MAX_ENG_SPD*(1UL<<3);
}

void LpsCalAppInfSetTiltCmdOvr(float_32 RackCommand, float_32 DumpCommand)
{
    LpsCalOv_t      *pCalOv = &LpsCalWrkTbl.Ov;

    if (TRUE == pCalOv->LpsCalAppInfCalOvrActive)
    {
        // Rack Command (0 to 100)
        if (RackCommand > LPS_CAL_APP_MAX_RACK_CMD) {
            pCalOv->LpsCalAppInfRackCmd = LPS_CAL_APP_MAX_RACK_CMD;
        }
        else if (RackCommand < LPS_CAL_APP_MIN_RACK_CMD){
            pCalOv->LpsCalAppInfRackCmd = LPS_CAL_APP_MIN_RACK_CMD;
        }
        else {
            pCalOv->LpsCalAppInfRackCmd = (signed_8)RackCommand;
        }

        // Dump Command (-100 to 0)
        if (DumpCommand < LPS_CAL_APP_MAX_DUMP_CMD) {
            pCalOv->LpsCalAppInfDumpCmd = LPS_CAL_APP_MAX_DUMP_CMD;
        }
        else if (DumpCommand > LPS_CAL_APP_MIN_DUMP_CMD){
            pCalOv->LpsCalAppInfDumpCmd = LPS_CAL_APP_MIN_DUMP_CMD;
        }
        else {
            pCalOv->LpsCalAppInfDumpCmd = (signed_8)DumpCommand;
        }
    }
    else {
        // reset to minimum command
        pCalOv->LpsCalAppInfRackCmd = LPS_CAL_APP_MIN_RACK_CMD;
        pCalOv->LpsCalAppInfDumpCmd = LPS_CAL_APP_MIN_DUMP_CMD;
    }
}

void LpsCalAppInfSetLiftCmdLimit(float_32 RaiseCommandLimit, float_32 LowerCommandLimit)
{
	 LpsCalOv_t		*pCalOv = &LpsCalWrkTbl.Ov;

    if (TRUE == pCalOv->LpsCalAppInfCalOvrActive)
    {
        /* Raise limit */
        if (RaiseCommandLimit < (float_32)0.0)
        {
            // Raise command limit cannot be less than zero
            pCalOv->LpsCalAppInfRaiseCmdLmt = 0.f;
        }
        else if (RaiseCommandLimit > LPS_CAL_APP_MAX_RAISE_CMD)
        {
            pCalOv->LpsCalAppInfRaiseCmdLmt = LPS_CAL_APP_MAX_RAISE_CMD;
        }
        else
        {
            pCalOv->LpsCalAppInfRaiseCmdLmt = (signed_8)roundf(RaiseCommandLimit * LPS_CAL_APP_MAX_RAISE_CMD /100);
        }

        /* Lower limit */
        if (LowerCommandLimit > (float_32)0.0)
        {
            // Lower command limit cannot be greater than zero
            pCalOv->LpsCalAppInfLowerCmdLmt = 0.f;
        }
        else if (LowerCommandLimit < LPS_CAL_APP_MAX_LOWER_CMD)
        {
            pCalOv->LpsCalAppInfLowerCmdLmt = LPS_CAL_APP_MAX_LOWER_CMD;
        }
        else
        {
            pCalOv->LpsCalAppInfLowerCmdLmt = (signed_8)roundf(-1 * LowerCommandLimit * LPS_CAL_APP_MAX_LOWER_CMD /100);
        }
    }
    else
    {
        pCalOv->LpsCalAppInfRaiseCmdLmt = LPS_CAL_APP_MAX_RAISE_CMD;
        pCalOv->LpsCalAppInfLowerCmdLmt = LPS_CAL_APP_MAX_LOWER_CMD;
    }
}

static float_32 LpsCalOvrCtrlGetRaiseCmdLimit(void)
{
    return LpsCalWrkTbl.CurveFitInfo.LpsCalOvrCtrlRaiseData.CurCommandLimit;
}

static float_32 LpsCalOvrCtrlGetLowerCmdLimit(void)
{
    return LpsCalWrkTbl.CurveFitInfo.LpsCalOvrCtrlLowerData.CurCommandLimit;
}

static void LpsCalLiftCalOvrCtrlUpdate(float_32 LiftHeight)
{
	LpsCalCfg_t 		 *pCalCfg = &LpsCalWrkTbl.Cfg;
	LpsCalCurveFitInfo_t *pCurveFitInfo = &LpsCalWrkTbl.CurveFitInfo;

    { /* Update Raise */
        float_32 commandLimitMax;
        float_32 commandLimit = pCurveFitInfo->LpsCalOvrCtrlRaiseData.ReqCommandLimit;
        float_32 commandLimitPrevious = pCurveFitInfo->LpsCalOvrCtrlRaiseData.CurCommandLimit;
        float_32 commandLimitMin = pCurveFitInfo->LpsCalOvrCtrlRaiseData.MinCommandLimit;

        /* Calculate the maximum command limit */
        if (LiftHeight > LpsCalOvrCtrlRaiseCfg.RampStartHeight)
        {
           float_32 commandScalar = ((float_32)100.0 - LiftHeight)/((float_32)100.0 - LpsCalOvrCtrlRaiseCfg.RampStartHeight);
           commandLimitMax = (float_32)100.0 * commandScalar;
        }
        else
        {
           commandLimitMax = 100.0;
        }

        /* Calculate the minimum command limit */
        if (commandLimit > commandLimitMax)
        {
           /* We are max limited, update the minimum command limit */
           commandLimitMin += LpsCalOvrCtrlRaiseCfg.MinCommandIncRateLimit * pCalCfg->ExecPeriodSec;
           if (commandLimitMin > commandLimit)
           {
               /* Don't allow minimum to drive the command higher than the requested limit */
               commandLimitMin = commandLimit;
           }
		}
		else
		{
			/* We are not lift position limited yet, so reset the min command */
			commandLimitMin = 0.0;
		}


        /* Apply the limits */
        if (commandLimit > commandLimitMax)
        {
            commandLimit = commandLimitMax;
        }
        if (commandLimit < commandLimitMin)
        {
            commandLimit = commandLimitMin;
        }

        /* Apply the rate limits */
        if (commandLimit > commandLimitPrevious)
        {
            float_32 commandLimitRL = commandLimitPrevious + LpsCalOvrCtrlRaiseCfg.CommandIncRateLimit * pCalCfg->ExecPeriodSec;
            if (commandLimit > commandLimitRL)
            {
                commandLimit = commandLimitRL;
            }
        }
        else
        {
            float_32 commandLimitRL = commandLimitPrevious - LpsCalOvrCtrlRaiseCfg.CommandDecRateLimit * pCalCfg->ExecPeriodSec;
            if (commandLimit < commandLimitRL)
            {
                commandLimit = commandLimitRL;
            }
        }


        pCurveFitInfo->LpsCalOvrCtrlRaiseData.MinCommandLimit = commandLimitMin;
        pCurveFitInfo->LpsCalOvrCtrlRaiseData.CurCommandLimit = commandLimit;
    }

    { /* Update Lower */
        float_32 commandLimitMax;
        float_32 commandLimit = pCurveFitInfo->LpsCalOvrCtrlLowerData.ReqCommandLimit;
        float_32 commandLimitPrevious = pCurveFitInfo->LpsCalOvrCtrlLowerData.CurCommandLimit;
        float_32 commandLimitMin = pCurveFitInfo->LpsCalOvrCtrlLowerData.MinCommandLimit;

        /* Calculate maximim command limit */
           if (LiftHeight < LpsCalOvrCtrlLowerCfg.RampStartHeight)
           {
               float_32 commandScalar = LiftHeight / LpsCalOvrCtrlLowerCfg.RampStartHeight;
               commandLimitMax = (float_32)-100.0 * commandScalar;
           }
           else
           {
               commandLimitMax = (float_32)-100.0;
           }

           /* Calculate the minimum command limit */
           if (commandLimit < commandLimitMax)
           {
               /* We are max limited, update the minimum command limit */
               commandLimitMin -= LpsCalOvrCtrlLowerCfg.MinCommandIncRateLimit * pCalCfg->ExecPeriodSec;
               if (commandLimitMin < commandLimit)
               {
                   /* Don't allow minimum to drive the command higher than the requested limit */
                   commandLimitMin = commandLimit;
               }
           }
           else
           {
               /* We are not lift position limited yet, so reset the min command */
               commandLimitMin = 0.0;
           }

           /* Apply the limits */
           if (commandLimit < commandLimitMax)
           {
               commandLimit = commandLimitMax;
           }
           if (commandLimit > commandLimitMin)
           {
               commandLimit = commandLimitMin;
           }

           /* Apply the rate limits */
           if (commandLimit < commandLimitPrevious)
           {
               float_32 commandLimitRL = commandLimitPrevious - LpsCalOvrCtrlLowerCfg.CommandIncRateLimit * pCalCfg->ExecPeriodSec;
               if (commandLimit < commandLimitRL)
               {
                   commandLimit = commandLimitRL;
               }
           }
           else
           {
               float_32 commandLimitRL = commandLimitPrevious + LpsCalOvrCtrlLowerCfg.CommandDecRateLimit * pCalCfg->ExecPeriodSec;
               if (commandLimit > commandLimitRL)
               {
                   commandLimit = commandLimitRL;
               }
           }


        pCurveFitInfo->LpsCalOvrCtrlLowerData.MinCommandLimit = commandLimitMin;
        pCurveFitInfo->LpsCalOvrCtrlLowerData.CurCommandLimit = commandLimit;
    }
}
