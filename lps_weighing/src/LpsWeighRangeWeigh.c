/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsWeighRange.c
DESCRIPTION:This file provides functionality for various calculations/algorithms
            performed by WRW functionality in LPS library.
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <math.h>
#include <string.h>

#include <std_types.h>

#include <LpsCommonTypeDef.h>
#include <LpsCommonStructures.h>
#include <LpsCommonLookUpTblUtility.h>
#include <LpsPublic.h>

#include "LpsPrivate.h"

#define PI (3.14159)
#define G  (9.80665)

static void ClearReweighWarningStatus();
static void ClearWeighRangeData();
static void UpdateWeighRangeData(float liftHeight, float liftLenFilt,
        float liftVelFilt, float liftAngFilt, float weightFilt, float weightFiltOld,
        const LpsIMUData_t* ReferenceIMUData);
static void WeighRangeCalcWeight(void);

static boolean AccelerationCompensation(float estPayloadMass,
        float startAngFilt, float startVelFilt,
        float endAngFilt, float endVelFilt,
        float* pPayloadMass);

static float ApplyAccelerationCompensationFactor(float rawPayloadMass, float accelCompFactor);

static void LpsWarmupLiftsRequiredInit();
static void LpsWarmupLiftsRequiredUpdate();

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
/******************************************************************************
FUNCTION NAME: ClearReweighWarningStatus
DESCRIPTION: Clears all the reweigh warning parameters
PARAMETER DESCRIPTION: None
RETURN VALUE: None
*******************************************************************************/
static void ClearReweighWarningStatus()
{
    /* We are Resetting the Reweigh Warning Structure here */
    memset(&LpsWrk.WrwTbl.ReweighWarn, 0x00, sizeof(LpsWrk.WrwTbl.ReweighWarn));

    /* Reweigh Posted has to be reset before WRW core computations. Hence done here */
    LpsWrk.WrwTbl.WkTbl.ReweighPosted = FALSE;
}

/******************************************************************************
FUNCTION NAME: ClearWeighRangeData
DESCRIPTION: Clears all the weigh range data parameters
PARAMETER DESCRIPTION: None
RETURN VALUE: None
*******************************************************************************/
static void ClearWeighRangeData()
{
    LpsWeighWrwWkTbl_t* pWrwWkTbl = &LpsWrk.WrwTbl.WkTbl;

    pWrwWkTbl->BeenBelowRange = FALSE;
    pWrwWkTbl->Weighing = FALSE;

    pWrwWkTbl->count = 0;
    pWrwWkTbl->weightSum = 0.f;
    pWrwWkTbl->weightSumIMUComp = 0.f;
    pWrwWkTbl->imuLinAccSum[0] = pWrwWkTbl->imuLinAccSum[1] = pWrwWkTbl->imuLinAccSum[2] = 0.f;
    pWrwWkTbl->imuAngVelSum[0] = pWrwWkTbl->imuAngVelSum[1] = pWrwWkTbl->imuAngVelSum[2] = 0.f;
    pWrwWkTbl->pitchSum = 0.f;
    pWrwWkTbl->rollSum = 0.f;

    pWrwWkTbl->weightMax = 0.f;
    pWrwWkTbl->weightMin = 0.f;

    pWrwWkTbl->liftAngFiltStart = 0.f;
    pWrwWkTbl->liftAngFiltEnd = 0.f;
    pWrwWkTbl->liftVelFiltSum = 0.f;
    pWrwWkTbl->liftVelFiltCountSum = 0.f;

    pWrwWkTbl->inc.weightMean = 0.f;
    pWrwWkTbl->inc.liftLengthFiltMean = 0.f;
    pWrwWkTbl->inc.liftAngleFiltMean = 0.f;
    pWrwWkTbl->inc.weightSumVar = 0.f;
    pWrwWkTbl->inc.weightLiftLengthSumCov = 0.f;

    pWrwWkTbl->result.weightAveRaw = 0.f;
    pWrwWkTbl->result.weightAveRawIMUComp = 0.f;
    pWrwWkTbl->result.weightAve = 0.f;
    pWrwWkTbl->result.weightRange = 0.f;
    pWrwWkTbl->result.weightStd = 0.f;
    pWrwWkTbl->result.weightStdErr = 0.f;
    pWrwWkTbl->result.weightChangePerLiftLength = 0.f;
}

static void UpdateWeighRangeData(float liftHeight, float liftLenFilt,
        float liftVelFilt, float liftAngFilt, float weightFilt, float weightFiltIMUComp,
        const LpsIMUData_t* ReferenceIMUData) {

    LpsWeighWrwWkTbl_t* pWrwWkTbl = &LpsWrk.WrwTbl.WkTbl;

    pWrwWkTbl->liftAngFiltEnd = liftAngFilt;

    if (0 == pWrwWkTbl->count) {
        pWrwWkTbl->count = 1;
        pWrwWkTbl->weightSum = weightFilt;
        pWrwWkTbl->weightSumIMUComp = weightFiltIMUComp;
        pWrwWkTbl->imuLinAccSum[0] = ReferenceIMUData->LinAcc[0];
        pWrwWkTbl->imuLinAccSum[1] = ReferenceIMUData->LinAcc[1];
        pWrwWkTbl->imuLinAccSum[2] = ReferenceIMUData->LinAcc[2];
        pWrwWkTbl->imuAngVelSum[0] = ReferenceIMUData->AngVel[0];
        pWrwWkTbl->imuAngVelSum[1] = ReferenceIMUData->AngVel[1];
        pWrwWkTbl->imuAngVelSum[2] = ReferenceIMUData->AngVel[2];
        pWrwWkTbl->pitchSum = ReferenceIMUData->Pitch;
        pWrwWkTbl->rollSum = ReferenceIMUData->Roll;

        pWrwWkTbl->weightMax = weightFilt;
        pWrwWkTbl->weightMin = weightFilt;

        pWrwWkTbl->liftAngFiltStart = liftAngFilt;
        pWrwWkTbl->liftVelFiltSum = liftVelFilt;
        pWrwWkTbl->liftVelFiltCountSum = 0.f;

        pWrwWkTbl->inc.weightMean = weightFilt;
        pWrwWkTbl->inc.liftLengthFiltMean = liftLenFilt;
        pWrwWkTbl->inc.liftAngleFiltMean = liftAngFilt;
        pWrwWkTbl->inc.weightSumVar = 0.f;
        pWrwWkTbl->inc.weightLiftLengthSumCov = 0.f;
    }
    else {
        pWrwWkTbl->count++;
        pWrwWkTbl->weightSum += weightFilt;
        pWrwWkTbl->weightSumIMUComp += weightFiltIMUComp;
        pWrwWkTbl->imuLinAccSum[0] += ReferenceIMUData->LinAcc[0];
        pWrwWkTbl->imuLinAccSum[1] += ReferenceIMUData->LinAcc[1];
        pWrwWkTbl->imuLinAccSum[2] += ReferenceIMUData->LinAcc[2];
        pWrwWkTbl->imuAngVelSum[0] += ReferenceIMUData->AngVel[0];
        pWrwWkTbl->imuAngVelSum[1] += ReferenceIMUData->AngVel[1];
        pWrwWkTbl->imuAngVelSum[2] += ReferenceIMUData->AngVel[2];
        pWrwWkTbl->pitchSum += ReferenceIMUData->Pitch;
        pWrwWkTbl->rollSum += ReferenceIMUData->Roll;

        if (weightFilt > pWrwWkTbl->weightMax) {
            pWrwWkTbl->weightMax = weightFilt;
        }

        if (weightFilt < pWrwWkTbl->weightMin) {
            pWrwWkTbl->weightMin = weightFilt;
        }

        pWrwWkTbl->liftVelFiltSum += liftVelFilt;
        pWrwWkTbl->liftVelFiltCountSum += ((float)pWrwWkTbl->count - 1.f) * liftVelFilt;

        { // Update incremental stats
            float count = (float)pWrwWkTbl->count;

            float previousWeightMean = pWrwWkTbl->inc.weightMean;
            float weightMean = previousWeightMean + (weightFilt - previousWeightMean) / count;
            pWrwWkTbl->inc.weightMean = weightMean;

            float previousLiftLengthFiltMean = pWrwWkTbl->inc.liftLengthFiltMean;
            float liftLengthFiltMean = previousLiftLengthFiltMean + (liftLenFilt - previousLiftLengthFiltMean) / count;
            pWrwWkTbl->inc.liftLengthFiltMean = liftLengthFiltMean;

            pWrwWkTbl->inc.weightSumVar += (weightFilt - previousWeightMean) * (weightFilt - weightMean);
            pWrwWkTbl->inc.weightLiftLengthSumCov += (liftLenFilt - previousLiftLengthFiltMean) * (weightFilt - weightMean);

            { // Update mean lift angle filtered
                float previousLiftAngleFiltMean = pWrwWkTbl->inc.liftAngleFiltMean;
                float liftAngleFiltMean = previousLiftAngleFiltMean + (liftAngFilt - previousLiftAngleFiltMean) / count;
                pWrwWkTbl->inc.liftAngleFiltMean = liftAngleFiltMean;
            }
        }
    }
}

/******************************************************************************
FUNCTION NAME: WeighRangeCalcWeight
DESCRIPTION: Computes the final WRW weight and based on the condition of lift in weigh range, warnings are raised
PARAMETER DESCRIPTION: None
RETURN VALUE: None
*******************************************************************************/
static void WeighRangeCalcWeight()
{
    LpsWeighWrwWkTbl_t* pWrwWkTbl = &LpsWrk.WrwTbl.WkTbl;

    /*
     * We need to ascertain if the number of samples in the weigh range taken is greater than 0, failing which
     * it essentially indicates that there was an issue that we were not in the weigh range and hence no weight
     * computations be done
     */
    if (pWrwWkTbl->count > 2) {
        LpsWeighWrwOpTbl_t* pWrwOpTbl = &LpsWrk.WrwTbl.OpTbl;
        LpsMachSpecificCfg_t const * pMachSpecConf = &LpsWrk.InitTbl.MachSpecificCfg;
        LpsWeighWrwErrorLimits_t* pWrwErrLimits = &LpsWrk.WrwTbl.ErrLmt;
        LpsWeighWrwReweighStatus_t* pWrwReweighTbl = &LpsWrk.WrwTbl.ReweighWarn;

        boolean highAccuracyWeight = TRUE;

        boolean inStandby = (0 == LpsWrk.UpdtTbl->StandbyActiveState);

        float count = (float)pWrwWkTbl->count;

        float weightAveRaw = pWrwWkTbl->weightSum / count;

        float weightAveRawIMUComp = pWrwWkTbl->weightSumIMUComp / count;

        float weightRange = pWrwWkTbl->weightMax - pWrwWkTbl->weightMin;

        float weightVar = pWrwWkTbl->inc.weightSumVar / (count - 1.f);

        float weightStd = (float)sqrt((double)weightVar);

        /*
         * The standard error gives you information on how close your mean estimate
         * is to the actual population mean.
         */
        float weightStdErr = (float)sqrt((double)weightVar / (double)count);

        /*
         * Calculate the slope of the best fit line for weight as a function of
         * lift height.  This is the covariance of lift height and weight divided
         * by the variance of weight.  In other words, how much does weight change as
         * a function of lift height divided by how much does weight change by itself.
         */
        float weightChangePerLiftLength = 0.f;
        if (pWrwWkTbl->inc.weightSumVar > 0.f) {
            /*
             * This parameter is currently not used, but could be used if we get
             * reweigh warnings that could describe the situation.
             *
             * If the standard error is high then check this to describe why it is high.
             * If the slope is high, maybe we are accelerating in the weigh range.
             * If the slope is low, maybe we accelerated too close to the start of weigh range.
             * If the slope is flat, then we just have jerky operation.
             *
             * A weight slope could also be due to machine pitch, which we currently do not measure.
             */
            weightChangePerLiftLength = pWrwWkTbl->inc.weightLiftLengthSumCov / pWrwWkTbl->inc.weightSumVar;
        }

        pWrwWkTbl->result.weightAveRaw = weightAveRaw;
        pWrwWkTbl->result.weightAveRawIMUComp = weightAveRawIMUComp;
        pWrwWkTbl->result.weightRange = weightRange;
        pWrwWkTbl->result.weightStd = weightStd;
        pWrwWkTbl->result.weightStdErr = weightStdErr;
        pWrwWkTbl->result.weightChangePerLiftLength = weightChangePerLiftLength;

        float weightAve = weightAveRaw;

        /*
         * Calculate and apply acceleration compensation.
         */
        if (pMachSpecConf->AccelCompSupported) {
            // Find best fit for start and end velocity
            // Do the least squares fit of a line representing cylinder velocity vs. time.
            float n = pWrwWkTbl->count;

            float T = LpsWrk.InitTbl.ExecRate;

            float Sx = (n*(n-1)/2) * T;

            float Sy = pWrwWkTbl->liftVelFiltSum;

            float Sxx = ((n*n-n)*(2*n-1)/6) * T * T;

            float Sxy = pWrwWkTbl->liftVelFiltCountSum * T;

            float den = Sxx - (Sx*Sx/n);

            float m = 0.f;
            if (den > 0.f) {
                float num = Sxy - (Sx*Sy/n);
                m = num / den;
            }

            float b = (Sy - m * Sx) / n;

            float liftVelFiltStart = b;

            float liftVelFiltEnd = m * n * T + b;

            //printf("n = %f\n", n);
            //printf("T = %f\n", T);
            //printf("Sx = %f\n", Sx);
            //printf("Sy = %f\n", Sy);
            //printf("Sxx = %f\n", Sxx);
            //printf("Sxy = %f\n", Sxx);
            //printf("den = %f\n", den);
            //printf("num = %f\n", Sxy - (Sx*Sy/n));
            //printf("m = %f\n", m);
            //printf("b = %f\n", b);
            //printf("liftVelFiltStart = %f\n", liftVelFiltStart);
            //printf("liftVelFiltEnd = %f\n", liftVelFiltEnd);
            //printf("liftAngFiltStart = %f\n", pWrwWkTbl->liftAngFiltStart);
            //printf("liftAngFiltEnd = %f\n", pWrwWkTbl->liftAngFiltEnd);

            if (AccelerationCompensation(weightAveRaw,
                    pWrwWkTbl->liftAngFiltStart, liftVelFiltStart,
                    pWrwWkTbl->liftAngFiltEnd, liftVelFiltEnd,
                    &weightAve)) {
                pWrwReweighTbl->Inconsistent = TRUE;
            }
        }

        pWrwWkTbl->result.weightAve = weightAve;

        /*
         * Calculate the angle difference between the acceleration vector during the weight measurement
         * and the acceleration vector during the calibration conditions.
         */
        float pitchAngle = pWrwWkTbl->pitchSum / count;
        float rollAngle = pWrwWkTbl->rollSum / count;
        float imuAngle = 180.f; // initialize to 180 degrees (upside down)
        {
            /*
             * Angle Between Two Vectors Using Dot Product
             * By the definition of dot product, a · b = |a| |b| cos θ.
             * Let us solve this for cos θ. Dividing both sides by |a| |b|.
             *
             * cos θ = (a · b) / (|a| |b|)
             *
             * θ = cos-1 [ (a · b) / (|a| |b|) ]
             */
            float a_x, a_y, a_z;
            float a_p, a_r;

            // Using the full calibration condition as reference.
            a_x = pMachSpecConf->CalibTbl.SlowRaiseFullIMUAccel[0];
            a_y = pMachSpecConf->CalibTbl.SlowRaiseFullIMUAccel[1];
            a_z = pMachSpecConf->CalibTbl.SlowRaiseFullIMUAccel[2];
            a_p = pMachSpecConf->CalibTbl.SlowRaiseFullPitch;
            a_r = pMachSpecConf->CalibTbl.SlowRaiseFullRoll;

            pitchAngle -= a_p;
            rollAngle -= a_r;

            float a_mag = sqrtf((a_x * a_x) + (a_y * a_y) + (a_z * a_z));

            float b_x = pWrwWkTbl->imuLinAccSum[0] / count;
            float b_y = pWrwWkTbl->imuLinAccSum[1] / count;
            float b_z = pWrwWkTbl->imuLinAccSum[2] / count;

            float b_mag = sqrtf((b_x * b_x) + (b_y * b_y) + (b_z * b_z));

            // Ensure neither magnitude is 0 and they are close enough to each other
            // for a stable calculation.
            if ((a_mag < 2*b_mag) && (b_mag < 2*a_mag)) {
                float a_dot_b = (a_x * b_x) + (a_y * b_y) + (a_z * b_z);
                imuAngle = acosf(a_dot_b / (a_mag * b_mag)) * (float)(180.0/PI);
            }
        }

        pWrwWkTbl->result.imuAngle = imuAngle;
        pWrwWkTbl->result.pitchAngle = pitchAngle;
        pWrwWkTbl->result.rollAngle = rollAngle;

        /*
         * Only raise the excessive pitch reweigh warning if legal for trade is installed
         */
        if (LpsWrk.UpdtTbl->LegalForTradeInstalled) {
            // If the angle is greater than the limit, raise the reweigh warning.
            if ((pitchAngle > pMachSpecConf->ReweighMaxPitch) ||
                    (pitchAngle < pMachSpecConf->ReweighMinPitch) ||
                    (fabs(rollAngle) > pMachSpecConf->ReweighMaxAbsRoll)) {
                pWrwReweighTbl->ExcessivePitch = TRUE;
            }
        }

        /*
         * If IMU Compensation is enabled and angular velocity is too much, then raise a reweigh warning
         * Only do this if pitch and roll are not already determined to be too high.
         */
        if ((LpsWrk.UpdtTbl->IMUCompEnabled) && (!(pWrwReweighTbl->ExcessivePitch))) {
            { // Roll
                float angVel = pWrwWkTbl->imuAngVelSum[0] / count;

                if (angVel < 0.f) {
                    angVel = -angVel;
                }

                if (angVel > pWrwErrLimits->maxImuAngVel[0]) {
                    pWrwReweighTbl->RateOfChangeHi = TRUE;
                }
            }

            { // Pitch
                float angVel = pWrwWkTbl->imuAngVelSum[1] / count;

                if (angVel < 0.f) {
                    angVel = -angVel;
                }

                if (angVel > pWrwErrLimits->maxImuAngVel[1]) {
                    pWrwReweighTbl->RateOfChangeHi = TRUE;
                }
            }

            { // Yaw
                float angVel = pWrwWkTbl->imuAngVelSum[2] / count;

                if (angVel < 0.f) {
                    angVel = -angVel;
                }

                if (angVel > pWrwErrLimits->maxImuAngVel[2]) {
                    pWrwReweighTbl->RateOfChangeHi = TRUE;
                }
            }
        }

        /*
         * If the statistics are beyond acceptable limits, call it bad.
         *  - only issue this reweigh warning if we don't already have
         *    the "Jerky" reweigh warning.
         */
        if (!(pWrwReweighTbl->Inconsistent)) {
            if ((weightStdErr > pWrwErrLimits->maxWeightStdErr) ||
                    (weightRange > pWrwErrLimits->maxWeightRange)) {
                pWrwReweighTbl->RateOfChangeHi = TRUE;
            }
        }

        if ((pWrwReweighTbl->Stopped) ||
                (pWrwReweighTbl->TooSlow) ||
                (pWrwReweighTbl->NotRacked) ||
                (pWrwReweighTbl->ExcessivePitch) ||
                (pWrwReweighTbl->RateOfChangeHi) ||
                (pWrwReweighTbl->Inconsistent) ||
                (LpsRemainingWarmupLiftsRequired()) ) {
            highAccuracyWeight = FALSE;

            if (LpsRemainingWarmupLiftsRequired()) {
                // clear all other reweigh warnings, we will show warmup lift only
                ClearReweighWarningStatus();

                pWrwReweighTbl->WarmUpLift = TRUE;
            }

            if (!inStandby) {
                pWrwWkTbl->ReweighPosted = TRUE;
            }
        }

        /* Apply the advanced calibration adjust and the zero/span adjust */
        pWrwOpTbl->Wt = LpsZeroSpanAdjust(LpsAdvCalAdjust(weightAve));

        /*
         * If any one of the reweigh warning flags are true, we are going to say that warning is ACTIVE
         */
        if (highAccuracyWeight) {
            pWrwOpTbl->Warning = LPS_WEIGH_NO_WARNING_ACTIVE;
        }
        else {
            pWrwOpTbl->Warning = LPS_WEIGH_WARNING_ACTIVE;
        }

        pWrwOpTbl->Status = LPS_WEIGH_WRW_STATUS_VALID;
    }
}

/******************************************************************************
FUNCTION NAME: AccelerationCompensation
DESCRIPTION: Performs acceleration compensation
PARAMETER DESCRIPTION:
    estPayloadMass - The estimated mass, in tonnes, before acceleration compensation.
    startAngFilt - The filtered lift angle at the start of weight range, in deg.
    startVelFilt - The filtered lift cylinder velocity at the start of the weigh range, in mm/sec.
    endAngFilt - The filtered lift angle at the end of weight range, in deg.
    endVelFilt - The filtered lift cylinder velocity at the end of the weigh range, in mm/sec.
    pPayloadMass - Pointer to the resulting mass, in tonnes, after acceleration compensation.
RETURN VALUE: boolean - TRUE if unable to calculate, otherwise FALSE
*******************************************************************************/
static boolean AccelerationCompensation(float estPayloadMass,
        float startAngFilt, float startVelFilt,
        float endAngFilt, float endVelFilt,
        float* pPayloadMass)
{
    static const float bucketCgFactor = 1.1f;
    boolean warning = FALSE;
    LpsMachSpecificCfg_t const * pMachCfg = &LpsWrk.InitTbl.MachSpecificCfg;

    /*
     * We estimate linkage mass from the pressure and moment arm at
     * mid-extension of the lift cylinders.  It is multiplied by 2
     * because the moment arm (kg/kPa) is given for mass added in the
     * bucket, at the end of the lift arms, however, the linkage CG
     * is assumed to be half the distance, therefore, twice the mass.
     */
    float linkageMassKg = 2 *
            pMachCfg->KgPerLiftKpaAtMidExtension *
            pMachCfg->LiftKpaNoBucketMidExtension;

    float emptyBucketMassKg = pMachCfg->CalibTbl.EmptyBucketWeightEst * 1000.f;

    float liftArmAbLengthMeters = pMachCfg->LiftArmAbLength / 1000.f;

    /* Check to make sure we have empty bucket weight estimate, everything else is checked at initialization. */
    if (emptyBucketMassKg <= 0.f) {
        *pPayloadMass = estPayloadMass;
        warning = TRUE;
        return warning;
    }

    float payloadMassKg = estPayloadMass / 1000.f;

    float startDegPerMm = LpsLookup(startAngFilt, pMachCfg->LiftLinkageMap.angleDeg,
            pMachCfg->LiftLinkageMap.gainDegPerMm, pMachCfg->LiftLinkageMap.numPoints);

    float startAngVelFilt = startVelFilt * startDegPerMm;

    float endDegPerMm = LpsLookup(endAngFilt, pMachCfg->LiftLinkageMap.angleDeg,
            pMachCfg->LiftLinkageMap.gainDegPerMm, pMachCfg->LiftLinkageMap.numPoints);

    float endAngVelFilt = endVelFilt * endDegPerMm;

    /*
     * Calculate the change in potential energy through the weigh range.
     *
     * We estimate that the CG of the linkage (without bucket) is at the middle
     * of the lift arms.
     *
     * We estimate that the CGs of the bucket and payload are at the end of the
     * lift arms.  bucketCgFactor is used to extend the bucket and payload slightly
     * beyond the end of the lift arms.
     */
    float deltaPotentialEnergyJoules;
    {
        float startHeightMeters = liftArmAbLengthMeters *
                sinf(startAngFilt*(float)(PI/180));

        float endHeightMeters = liftArmAbLengthMeters *
                sinf(endAngFilt*(float)(PI/180));

        /*
         * The linkage (without bucket) goes half as high since it is in the middle
         * of the lift arms, that's why it is multiplied by 0.5.
         */
        deltaPotentialEnergyJoules =
                (0.5f * linkageMassKg + bucketCgFactor * (emptyBucketMassKg + payloadMassKg)) *
                (float)G *
                (endHeightMeters - startHeightMeters);
    }
    //printf("deltaPotentialEnergyJoules = %f\n", deltaPotentialEnergyJoules);

    /* Sanity check. */
    if (deltaPotentialEnergyJoules <= 0.f) {
        /* Things changed too fast (too much acceleration) and the filtering can't keep up */
        *pPayloadMass = estPayloadMass;
        warning = TRUE;
        return warning;
    }

    /*
     * Calculate the natural acceleration of the linkage that has already
     * been accounted for during the calibration.  This is done in a format
     * that can be used to modify the kinetic energy calculation.
     *
     * E_gross = 1/2 * I * w^2
     * dE_gross = 1/2 * I * (w1^2 - w0^2)
     * dE_gross = dE_net + dE_0
     * dE_net = dE_gross - dE_0
     * dE_net = 1/2 * I * ((w1^2 - w0^2) - (w1_0^2 - w0_0^2))
     *
     * dw2_0 = w1_0^2 - w0_0^2
     */
    float dw2_0;
    {
        /*
         * If we were to continue at the same cylinder velocity through the entire
         * weigh range, then what would the angular velocity have been at the end
         * of the weigh range?  This represents the natural acceleration of the
         * linkage.
         */
        float endAngVelDegPerSec_0 = startVelFilt * endDegPerMm;

        /* Convert to radians / second */
        float startAngVelRadPerSec_0 = startAngVelFilt * (float)(PI/180);
        float endAngVelRadPerSec_0 = endAngVelDegPerSec_0 * (float)(PI/180);

        /* dw2_0 = w1_0^2 - w0_0^2 */
        dw2_0 = copysignf(endAngVelRadPerSec_0 * endAngVelRadPerSec_0, endAngVelRadPerSec_0) -
                copysignf(startAngVelRadPerSec_0 * startAngVelRadPerSec_0, startAngVelRadPerSec_0);
    }

    /*
     * Calculate the change in kinetic energy through the weigh range.
     *
     * We estimate that the CG of the linkage (without bucket) is at the middle
     * of the lift arms and we model it as a rod.
     *
     * We estimate that the CGs of the bucket and payload are at the end of the
     * lift arms and we model then as point masses. bucketCgFactor is used to extend
     * the CG of the bucket and payload slightly beyond the end of the lift arms.
     */
    float deltaKineticEnergyJoules;
    {
        float startAngVelRadPerSec = startAngVelFilt * (float)(PI/180);
        float endAngVelRadPerSec = endAngVelFilt * (float)(PI/180);

        /* w_end^2 - w_start^2 */
        float dw2 = copysignf(endAngVelRadPerSec * endAngVelRadPerSec, endAngVelRadPerSec) -
                copysignf(startAngVelRadPerSec * startAngVelRadPerSec, startAngVelRadPerSec);

        deltaKineticEnergyJoules = 0.5f *
                (linkageMassKg / 3.f +
                        bucketCgFactor * bucketCgFactor * (emptyBucketMassKg + payloadMassKg)) *
                liftArmAbLengthMeters * liftArmAbLengthMeters * (dw2 - dw2_0);
    }
    //printf("deltaKineticEnergyJoules = %f\n", deltaKineticEnergyJoules);

    float deltaTotalEnergyJoules = deltaKineticEnergyJoules + deltaPotentialEnergyJoules;
    //printf("deltaTotalEnergyJoules = %f\n", deltaTotalEnergyJoules);

    /* Sanity check. */
    if (deltaTotalEnergyJoules <= 0.f) {
        /* The calculation is unstable if we are decelerating this much */
        *pPayloadMass = estPayloadMass;
        warning = TRUE;
        return warning;
    }

    /*
     * If the initial filtered velocity was negative, this is in the middle of
     * a direction reversal and there is too much to compensate for.  The math
     * still works, so we can do it, but it should come with a warning.
     */
    if (startVelFilt < 0.f) {
        warning = TRUE;
    }

    /*
     * The acceleration compensation factor is 1.0 if there is no change
     * in kinetic energy (no acceleration).  Otherwise, it represents the
     * change in potential energy relative to to the total change in energy.
     */
    float factor = deltaPotentialEnergyJoules / deltaTotalEnergyJoules;

    /*
     * If too much correction is needed, issue a warning
     */
    if (factor > 1.05f) {
        warning = TRUE;
        if (factor > 1.1f) {
            factor = 1.1f;
        }
    }
    else if (factor < 0.95f) {
        warning = TRUE;
        if (factor < 0.9f) {
            factor = 0.9f;
        }
    }

    *pPayloadMass = ApplyAccelerationCompensationFactor(estPayloadMass, factor);

    return warning;
}

/******************************************************************************
FUNCTION NAME: ApplyAccelerationCompensationFactor
DESCRIPTION: Applied acceleration compensation.
PARAMETER DESCRIPTION:
    rawPayloadMass - The raw mass, in tonnes, before acceleration compensation.
    accelCompFactor - The accaleration compensation factor.
RETURN VALUE: float - The acceleration compensated mass, in tonnes.
*******************************************************************************/
static float ApplyAccelerationCompensationFactor(float rawPayloadMass, float accelCompFactor)
{
    LpsMachSpecificCfg_t const * pMachCfg = &LpsWrk.InitTbl.MachSpecificCfg;
    LpsCalNvmTbl_t const * pCalibData = &pMachCfg->CalibTbl;

    /* Recalculate the payload for a single point in the middle of the weigh range. */
    float liftPosition = (pMachCfg->EndOfWeigh + pMachCfg->StartOfWeigh) / 2.f;

    /*
     * Determine calibration empty and full bucket pressure (for raise) based
     * on linkage height/lift cylinder extension
     */
    float emptyPressure = LpsLookupExtrap(liftPosition,
            pCalibData->SlowRaiseEmptyBktLiftHt, pCalibData->SlowRaiseEmptyBktLiftPres,
            sizeof(pCalibData->SlowRaiseEmptyBktLiftHt) / sizeof(pCalibData->SlowRaiseEmptyBktLiftHt[0]));

    float fullPressure = LpsLookupExtrap(liftPosition,
            pCalibData->SlowRaiseFullBktLiftHt, pCalibData->SlowRaiseFullBktLiftPres,
            sizeof(pCalibData->SlowRaiseFullBktLiftHt) / sizeof(pCalibData->SlowRaiseFullBktLiftHt[0]));

    /* Sanity check... */
    if (fullPressure <= emptyPressure) {
        return rawPayloadMass;
    }

    float tonnesPerKpa = pCalibData->CalWeight / (fullPressure - emptyPressure);

    /* Sanity check... */
    if (tonnesPerKpa <= 0.f) {
        return rawPayloadMass;
    }

    /* What pressure lead to the estimated payload mass. */
    float pressure = (rawPayloadMass / tonnesPerKpa) + emptyPressure;

    /* Modify that pressure to account for acceleration. */
    pressure *= accelCompFactor;

    /* Return the payload calculated from the compensated pressure. */
    return tonnesPerKpa * (pressure - emptyPressure);
}

/******************************************************************************
FUNCTION NAME:LpsWeighResetWeighRangeWeight
DESCRIPTION: Clears the latched status to FALSE 
PARAMETER DESCRIPTION: None
RETURN VALUE: NONE
*******************************************************************************/
void LpsWeighResetWeighRangeWeight()
{
    LpsWrk.WrwTbl.OpTbl.Status = LPS_WEIGH_WRW_STATUS_INVALID;
    LpsWrk.WrwTbl.OpTbl.Warning = LPS_WEIGH_NO_WARNING_ACTIVE;
    LpsWrk.WrwTbl.OpTbl.Wt = 0;

    ClearReweighWarningStatus();
    ClearWeighRangeData();
}

/******************************************************************************
FUNCTION NAME:LpsSetDefaultErrLimits
DESCRIPTION: Defaults the error limits for WRW parameters 
PARAMETER DESCRIPTION: None
RETURN VALUE: NONE
*******************************************************************************/
void LpsSetDefaultErrLimits()
{
    float referenceWeight = LpsWrk.InitTbl.MachSpecificCfg.DigConfig.DigTargetWt;

    {
        /*
         * Currently - 99% confidence (2.58 sigma) for interval of +/-1% (0.01) of reference weight.
         * Previously - 99.9% confidence (3.29 sigma) for interval of +/-1% (0.01) of reference weight.
         *              This resulted in too many reweigh warnings being observed based on Caterpillar
         *              operator feedback.
         */
        float maxWeightStdErr = (referenceWeight * 0.01f) / 2.58f;
        LpsWrk.WrwTbl.ErrLmt.maxWeightStdErr = maxWeightStdErr;
    }

    {
        /*
         * Max range of weight seen in weigh range.
         * Don't go less than 2 tonnes which is the old value.
         */
        float maxWeightRange = referenceWeight * 0.2f;
        if (maxWeightRange < 2.0f) {
            maxWeightRange = 2.0f;
        }
        LpsWrk.WrwTbl.ErrLmt.maxWeightRange = maxWeightRange;
    }

    LpsWrk.WrwTbl.ErrLmt.maxImuAngVel[0] = 0.3; // Roll, rad/s
    LpsWrk.WrwTbl.ErrLmt.maxImuAngVel[1] = 0.03; // Pitch, rad/s
    LpsWrk.WrwTbl.ErrLmt.maxImuAngVel[2] = 0.3; // Yaw, rad/s
}

/******************************************************************************
FUNCTION NAME:LpsGetWrwReweighWarning
DESCRIPTION: Returns the reweigh warning flags' status
PARAMETER DESCRIPTION: None
RETURN VALUE: NONE
*******************************************************************************/
LpsWeighWrwReweighStatus_t LpsGetWrwReweighWarning()
{
    if (LpsWrk.WrwTbl.WkTbl.ReweighPosted) {
        return LpsWrk.WrwTbl.ReweighWarn;
    }
    else {
       LpsWeighWrwReweighStatus_t tempWarning = {0};
       return tempWarning;
    }
}

/******************************************************************************
FUNCTION NAME:LpsGetWeighRangeWeight
DESCRIPTION: Returns the final latched weight 
PARAMETER DESCRIPTION: None
RETURN VALUE: NONE
*******************************************************************************/
float_32 LpsGetWeighRangeWeight()
{
    return LpsWrk.WrwTbl.OpTbl.Wt;
}

/******************************************************************************
FUNCTION NAME:LpsWeighRangeWeighInit
DESCRIPTION: This initializes the basic filter parameters and default error limits
RETURN VALUE: None
*******************************************************************************/
void LpsWeighRangeWeighInit()
{
    LpsSetDefaultErrLimits();
    LpsWeighResetWeighRangeWeight();
    LpsWarmupLiftsRequiredInit();
}


/******************************************************************************
FUNCTION NAME:LpsWeighRangeWeighUpdate
DESCRIPTION: Weigh Range weigh Position Determination is done here.The Current Bucket Position is determined with 
regards to the App Defined Weigh Ranges and the current weigh range status is set. 
RETURN VALUE: None
*******************************************************************************/
void LpsWeighRangeWeighUpdate()
{
    LpsWeighWrwWkTbl_t* pWrwWkTbl = &LpsWrk.WrwTbl.WkTbl;
    LpsMachSpecificCfg_t const * pWrwMachTbl = &LpsWrk.InitTbl.MachSpecificCfg;
    LpsCalNvmTbl_t const * pCalibData = &pWrwMachTbl->CalibTbl;
    LpsWeighWrwOpTbl_t* pWrwOpTbl = &LpsWrk.WrwTbl.OpTbl;
    LpsWeighWrwReweighStatus_t* pWrwReweighTbl = &LpsWrk.WrwTbl.ReweighWarn;
    LpsUpdtTbl_t* pUpdtTbl = LpsWrk.UpdtTbl;
    LpsStat_t rawStatus = LpsWrk.InputStatus.rawStatus;
    LpsStat_t debouncedStatus = LpsWrk.InputStatus.debouncedStatus;

    if (LPS_WEIGH_SYSTEM_UNCALIBRATED == LpsGetCalibStatus()) {
        rawStatus = LPS_STATUS_BAD;
        debouncedStatus = LPS_STATUS_BAD;
    }

    if (LPS_STATUS_OK == rawStatus) {
        /*
         * When we are below the start of Weigh Range, indicate that we are so and that
         * we have been below the weigh range
         */
        if (pUpdtTbl->LiftCylLengthNorm.Val < pWrwMachTbl->StartOfWeigh) {
            pWrwOpTbl->Indicator = LPS_BELOW_WEIGH_RANGE;
            pWrwWkTbl->BeenBelowRange = TRUE;
        }
        else if (pUpdtTbl->LiftCylLengthNorm.Val > pWrwMachTbl->EndOfWeigh) {
            pWrwOpTbl->Indicator = LPS_ABOVE_WEIGH_RANGE;
        }

        /*
         * We are checking here if we have entered the weigh range from below the weigh range
         */
        if (!(pWrwWkTbl->Weighing)) {
            if ((pUpdtTbl->LiftCylLengthNorm.Val >= pWrwMachTbl->StartOfWeigh) &&
                    (pUpdtTbl->LiftCylLengthNorm.Val < pWrwMachTbl->EndOfWeigh)) {
                /*
                 * We are in the weigh range and not weighing.
                 */
                if (pWrwWkTbl->BeenBelowRange) {
                    if (pUpdtTbl->LiftCylVel.Val > MIN_LIFT_VELOCITY) {
                        /*
                         * We are going to start WRW computations once we exit the weigh range
                         * by moving up. Hence as a precursor, clear out all the warning status
                         * and computation parameters from the previous weigh
                         */
                        ClearReweighWarningStatus();
                        ClearWeighRangeData();

                        /*
                         * We have entered the weigh range with proper bucket velocity.
                         * So, set the Weighing flag to TRUE
                         */
                        pWrwOpTbl->Indicator = LPS_IN_WEIGH_RANGE_WEIGHING;
                        pWrwWkTbl->Weighing = TRUE;
                        pWrwWkTbl->BeenBelowRange = FALSE;
                    }
                }
                else {
                    /*
                     * We have moved in here from above the weigh range. Hence We are in the weigh
                     * range but not weighing
                     */
                    pWrwOpTbl->Indicator = LPS_IN_WEIGH_RANGE_NOT_WEIGHING;
                }
            }
        }

        if (pWrwWkTbl->Weighing) {
            /* We have entered into the weigh range and are checking if we have moved above the weigh range */
            if (pUpdtTbl->LiftCylLengthNorm.Val > pWrwMachTbl->EndOfWeigh) {
                /* We have moved above the weigh range and are going to record the final weight */
                WeighRangeCalcWeight();
                pWrwWkTbl->Weighing = FALSE;
            }
            else if (pUpdtTbl->LiftCylLengthNorm.Val < pWrwMachTbl->StartOfWeigh) {
                /* We haved moved from within the weigh range to below the weigh range. So we are not weighing now */
                pWrwOpTbl->Indicator = LPS_BELOW_WEIGH_RANGE;
                pWrwWkTbl->Weighing = FALSE;
            }
            else if (LPS_WEIGHT_BKT_FULLY_DUMPED == LpsWeighGetDumpState()) {
                pWrwWkTbl->Weighing = FALSE;
            }
            else {
                /*
                 * We compute the WRW weight only if the bucket is not under full dump and if
                 * all the inputs are good
                 */
                if (LPS_STATUS_OK == debouncedStatus) {
                    /*
                     * Update weigh range statistics
                     */
                    UpdateWeighRangeData(pUpdtTbl->LiftCylLengthNorm.Val, LpsWrk.LiftPositionFilt.length,
                            LpsWrk.LiftPositionFilt.velocity, LpsWrk.LiftPositionFilt.angle,
                            LpsWrk.InstWtFilt, LpsWrk.InstWtFiltIMUComp, &(pUpdtTbl->ReferenceIMUData));

                    /*
                     * If the bucket velocity in weigh range at any point becomes less than 1.0,
                     * then we raise Stopped Warning.
                     */
                    if (pUpdtTbl->LiftCylVel.Val < MIN_LIFT_VELOCITY) {
                        pWrwReweighTbl->Stopped = TRUE;
                    }


                    /*
                     * If the bucket velocity in weigh range at any point becomes less than
                     * the slow calibration speeds, then we raise the Slow Warning.
                     */
                    if ((pUpdtTbl->LiftCylVel.Val < pCalibData->EmptyBktSlowRaiseSpd) ||
                            (pUpdtTbl->LiftCylVel.Val < pCalibData->FullBktSlowRaiseSpd) ||
                            ((pUpdtTbl->LiftCylVel.Val < pWrwMachTbl->ReweighMinLiftCylVel) &&
                                    (pUpdtTbl->LegalForTradeInstalled))) {
                        pWrwReweighTbl->TooSlow = TRUE;
                    }

                    /*
                     * If the bucket movement within the weigh range is having greater than 32766
                     * position samples, then it approximately indicates more than 10 minutes within
                     * the weigh range at 20ms task rate.
                     */
                    if (pWrwWkTbl->count > TOO_SLOW_NUMBER_OF_SAMPLES) {
                        pWrwReweighTbl->TooSlow = TRUE;
                    }

                    /*
                     * Stopped and Too Slow are mutually exclusive
                     */
                    if (TRUE == pWrwReweighTbl->Stopped) {
                        pWrwReweighTbl->TooSlow = FALSE;
                    }

                    /*
                     * We should be fully racked back within the weigh range for sure, otherwise
                     * the weight calculations might not be accurate enough. So we raise a reweigh
                     * warning for the same.
                     */
                    if (!LpsWeighFullRackDetectStrict()) {
                        pWrwReweighTbl->NotRacked = TRUE;
                    }
                }
            }
        }
    }
    else if (LPS_STATUS_BAD == debouncedStatus) {
        LpsWeighResetWeighRangeWeight();
    }

    { /* If we are in standby, do not report reweigh warnings. */
        boolean inStandby = (0 == LpsWrk.UpdtTbl->StandbyActiveState);
        if (inStandby) {
            LpsWrk.WrwTbl.WkTbl.ReweighPosted = FALSE;
        }
    }

    // Call update for warm-up required
    LpsWarmupLiftsRequiredUpdate();
}

LpsWeighRangeIndicator_t LpsWeighGetWeighRangeIndicator()
{
    return LpsWrk.WrwTbl.OpTbl.Indicator;
}

static void LpsWarmupLiftsRequiredInit()
{
    // Don't force more warmup lifts just because we are re-initializing the weighing library
    static boolean hasBeenInitialized = FALSE;

    if (!hasBeenInitialized) {
        LpsWrk.WarmupLifts.maxLiftsRequired = 3;
        LpsWrk.WarmupLifts.remaininingLiftsRequired = LpsWrk.WarmupLifts.maxLiftsRequired;
        LpsWrk.WarmupLifts.timeIntervalInMins = 15;
        LpsWrk.WarmupLifts.elapsedMins = 0;
        hasBeenInitialized = TRUE;
    }
}

unsigned_16 LpsRemainingWarmupLiftsRequired()
{
    unsigned_16 remaininingLiftsRequired = 0;

    // only required for legal for trade and while not in standby and we are installed and calibrated
    if (LpsWrk.UpdtTbl && LpsWrk.UpdtTbl->LegalForTradeInstalled)
    {
        remaininingLiftsRequired = LpsWrk.WarmupLifts.remaininingLiftsRequired;
    }

    return remaininingLiftsRequired;
}

static void LpsWarmupLiftsRequiredUpdate()
{
    static boolean hasBeenBelowRange = FALSE;

    // Check if we need to reset the lifts required to max
    if (((LpsWrk.UpdtTbl->ClockKeyonSec)/60) >
        (LpsWrk.WarmupLifts.elapsedMins + LpsWrk.WarmupLifts.timeIntervalInMins))
    {
        LpsWrk.WarmupLifts.remaininingLiftsRequired = LpsWrk.WarmupLifts.maxLiftsRequired;
        hasBeenBelowRange = FALSE;

        // capture reset time elapsed in mins
        LpsWrk.WarmupLifts.elapsedMins = (LpsWrk.UpdtTbl->ClockKeyonSec)/60;
    }

    // save off previous weighing status
    if (LpsWrk.WrwTbl.OpTbl.Indicator == LPS_BELOW_WEIGH_RANGE ) {
        hasBeenBelowRange = TRUE;
    }
    else if ((LpsWrk.WrwTbl.OpTbl.Indicator == LPS_ABOVE_WEIGH_RANGE ) &&
            hasBeenBelowRange)
    {
        if (LpsRemainingWarmupLiftsRequired()) {
            --LpsWrk.WarmupLifts.remaininingLiftsRequired;
        }

        // capture reset time elapsed in mins
        LpsWrk.WarmupLifts.elapsedMins = (LpsWrk.UpdtTbl->ClockKeyonSec)/60;

        hasBeenBelowRange = FALSE;
    }
}

// Check for Excessive Pitch for Measurement Status
void LpsWeighExcessivePitchDetect()
{
    LpsUpdtTbl_t* pUpdtTbl = LpsWrk.UpdtTbl;
    LpsMachSpecificCfg_t const * pMachSpecConf = &LpsWrk.InitTbl.MachSpecificCfg;
    boolean excessivePitch;

    if (LPS_WEIGH_SYSTEM_CALIBRATED == LpsGetCalibStatus()) {

        float pitchAngle = pUpdtTbl->ReferenceIMUData.Pitch;
        float rollAngle = pUpdtTbl->ReferenceIMUData.Roll;

        float a_p = pMachSpecConf->CalibTbl.SlowRaiseFullPitch;
        float a_r = pMachSpecConf->CalibTbl.SlowRaiseFullRoll;

        pitchAngle -= a_p;
        rollAngle -= a_r;

        if (LPS_STATUS_OK == pUpdtTbl->ReferenceIMUData.Stat) {
            if ((pitchAngle > pMachSpecConf->ReweighMaxPitch) ||
                    (pitchAngle < pMachSpecConf->ReweighMinPitch) ||
                    (fabs(rollAngle) > pMachSpecConf->ReweighMaxAbsRoll)) {
                excessivePitch = TRUE;
            }
            else {
                excessivePitch = FALSE;
            }
        }
        else {
            excessivePitch = FALSE;
        }

        /* Update the raw status */
        if (!excessivePitch) {
            if (LpsWrk.PitchIconDebounce.rawStatus) {
                LpsWrk.PitchIconDebounce.debounceCount = (unsigned_32)(((float_32) PITCH_DEBOUNCE_TIME_TO_OK / LpsWrk.InitTbl.ExecRate) + 0.5f);
            }
        }
        else {
            if (!LpsWrk.PitchIconDebounce.rawStatus) {
                LpsWrk.PitchIconDebounce.debounceCount = (unsigned_32)(((float_32) PITCH_DEBOUNCE_TIME_TO_BAD / LpsWrk.InitTbl.ExecRate) + 0.5f);
            }
        }

        LpsWrk.PitchIconDebounce.rawStatus = excessivePitch;

        /* Once we are debounced, update the debounced status */
        if (LpsWrk.PitchIconDebounce.debounceCount <= 0) {
            LpsWrk.PitchIconDebounce.debouncedStatus = LpsWrk.PitchIconDebounce.rawStatus;
        }

        /* Decrement the debounce counter */
        if (LpsWrk.PitchIconDebounce.debounceCount > 0) {
            LpsWrk.PitchIconDebounce.debounceCount--;
        }
    }
    else {
        LpsWrk.PitchIconDebounce.rawStatus = FALSE;
        LpsWrk.PitchIconDebounce.debouncedStatus = FALSE;
        LpsWrk.PitchIconDebounce.debounceCount = 0;
    }
}
