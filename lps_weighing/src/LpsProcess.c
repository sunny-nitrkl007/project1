/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsProcess.c
DESCRIPTION:This file provides functionality for various calculations/algorithms
            performed by LPS library.
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <string.h>
#include <math.h>

#include <LpsCommonTypeDef.h>
#include <LpsCommonStructures.h>
#include <cpm_filter.h>

#include "LpsPrivate.h"

#define PI (3.14159)
#define G  (9.80665)


/*
 * Updates the linkage movement detection state machine.
 */
static LpsLinkageMovementStat_t LpsUpdateLinkageMovementState(
        LpsLinkageMovementStat_t currentState,
        LpsFloatIO_t const * cylinderVelocity,
        LpsFloatIO_t const * valveCommand);

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
/******************************************************************************
FUNCTION NAME:LpsCalcCylFlowConst
DESCRIPTION: This function calculates the lift cylinder hydraulic oil flow constand
             based on machine specific configuration table passed on to the library
             by the application.
             
PARAMETER DESCRIPTION: LpsWrk.InitTbl.MachSpecificCfg.LiftCylBoreDia,
                       LpsWrk.InitTbl.MachSpecificCfg.LiftCylRodDia -> Lift cylinder bore
                       and rod diameter.
RETURN VALUE: LpsWrk.CylFlowConst.LiftHeFlowConst,LpsWrk.CylFlowConst.LiftReToHeFlowRatio
*******************************************************************************/
void LpsCalcCylFlowConst(void)
{
    float_32 liftCylBoreArea;
    float_32 liftCylRodArea;
  
    /* Calculating lift cylinder and lift piston rod areas for determining flow constand  - Cylinder area = (Pi * cylinder radius^2) */
    liftCylBoreArea  =  (PI_CONST * (LpsWrk.InitTbl.MachSpecificCfg.LiftCylBoreDia/(float_32)2.0) * 
                        (LpsWrk.InitTbl.MachSpecificCfg.LiftCylBoreDia/(float_32)2.0));
    liftCylRodArea   =  (PI_CONST * (LpsWrk.InitTbl.MachSpecificCfg.LiftCylRodDia/(float_32)2.0)  * 
                        (LpsWrk.InitTbl.MachSpecificCfg.LiftCylRodDia/(float_32)2.0));
  
    if( (liftCylRodArea > 0.0) &&
        (liftCylBoreArea > liftCylRodArea)
      )
    {
        LpsWrk.CylFlowConst.LiftHeFlowConst     = ((float_32)60.0 * liftCylBoreArea * LpsWrk.InitTbl.MachSpecificCfg.NoOfLiftCyls / (float_32)1000000.0);
        LpsWrk.CylFlowConst.LiftReToHeFlowRatio = (liftCylBoreArea - liftCylRodArea)/liftCylBoreArea;
    }
    else
    {
        LpsWrk.CylFlowConst.LiftHeFlowConst     = (float_32) 0.0;
        LpsWrk.CylFlowConst.LiftReToHeFlowRatio = (float_32)1.0;      
    }
  
    return;
}

/******************************************************************************
FUNCTION NAME:LpsGetHydOilVisc
DESCRIPTION: This function accepts hydraulic oil temperature as input and outputs the corresponding
             oil viscosity.The interpolation between the temperature and viscosity is determined using
             predefined maps for corresponding oil types. 
PARAMETER DESCRIPTION: hydOilTemp-> This interface holds the hydraulic oil temperature in degC
RETURN VALUE: Viscosity-> hold hydraulic oil viscosity for a particular temperature in Kg/m-3
*******************************************************************************/
static float_32 LpsGetHydOilVisc(float_32 hydOilTemp)
{
    /* Hydraulic oil temperature Vs Viscosity map x = temp in DegC ,y = Viscosity in Kg/m-3 */
    static const float_32 tempSAE10W[]  = { 0, 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100 }; /* Degrees C */
    static const float_32 viscSAE10W[]  = { 0.401163657, 0.271392082, 0.189249493, 0.135629739, 0.099636096, 0.074851526, 0.057384532, 0.035582067, 0.023450402, 0.016257589, 0.01175743, 0.008809872, 0.006801861, 0.005386759 }; /* kg/m-s */
    static const float_32 tempSAE0W20[] = { -40, -32, -18, 0, 21, 50, 80 };
    static const float_32 viscSAE0W20[] = { 4.16344705, 1.899216267, 0.600904802, 0.188654307, 0.067443573, 0.023985969, 0.011154169 };
    float_32 viscosity;
    

    if (LPS_OIL_TYPE_SAE_0W20 == LpsWrk.InitTbl.MachSpecificCfg.HydOilType)
    {
        viscosity = LpsLookup(hydOilTemp, tempSAE0W20, viscSAE0W20, sizeof(tempSAE0W20)/sizeof(float_32));
    }
    else
    { /* Assume Standard Oil as default */
        viscosity = LpsLookup(hydOilTemp, tempSAE10W, viscSAE10W, sizeof(tempSAE10W)/sizeof(float_32));
    }

    return viscosity;
}

/******************************************************************************
FUNCTION NAME:LpsGetHydOilDensity
DESCRIPTION: This function accepts hydraulic oil temperature as input and outputs the corresponding
             oil density.The interpolation between the temperature and density is determined using
             predefined maps for corresponding oil types. 
PARAMETER DESCRIPTION: hydOilTemp-> This interface holds the hydraulic oil temperature in degC
RETURN VALUE:  Density-> hold hydraulic oil density for a particular temperature in Kg/m^3
*******************************************************************************/
static float_32 LpsGetHydOilDensity(float_32 hydOilTemp)
{
  /* Hydraulic oil temperature Vs Viscosity map x = temp in DegC ,y = Density in Kg/m^3 */
    static const float_32 tempSAE10W[]  = { -20, 0, 20, 30, 40, 50, 60, 70, 80, 90, 100 }; /* Degrees C */
    static const float_32 densSAE10W[]  = { 903.1, 891.1, 877.7, 871, 864.4, 857.8, 851.2, 844.7, 838.2, 831.7, 825.2 }; /* kg/m3 */
    static const float_32 tempSAE0W20[] = { -40, -32, -18, 0, 21, 50, 80 };
    static const float_32 densSAE0W20[] = { 909.7, 904.1, 894.3, 881.7, 867, 846.7, 825.7 };
    float_32 density;
    

    if (LPS_OIL_TYPE_SAE_0W20 == LpsWrk.InitTbl.MachSpecificCfg.HydOilType)
    {
        density = LpsLookup(hydOilTemp, tempSAE0W20, densSAE0W20, sizeof(tempSAE0W20)/sizeof(float_32));
    }
    else
    { /* Assume Standard Oil as default */
        density = LpsLookup(hydOilTemp, tempSAE10W, densSAE10W, sizeof(tempSAE10W)/sizeof(float_32));
    }

    return density;
}

/******************************************************************************
FUNCTION NAME:LpsCalcDiffPres
DESCRIPTION: This function computes the lift cylinder effective pressure.The pressure
             is calculated taking into considerations of the head end and rod end
             hydraulic pressure difference.Hrdraulic line losses are calculated by
             determining orfice loss and line loss based on machine physics which
             are acquired through machine specfic configuration inputs from application
             software.  
 
PARAMETER DESCRIPTION: LpsWrk.CylFlowConst.LiftHeFlowConst-> predetermined Head end 
                       flow constand to calculate lift cylinder head end oil flow.
                       LpsWrk.CylFlowConst.LiftReToHeFlowRatio) -> predetermined head end 
                       to rod end ratio for rod end oil flow computation
                       LpsWrk.InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylHeLineLoss2ndOrdrCoeff,
                       LpsWrk.InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylHeLineLoss1stOrdrCoeff
                       LpsWrk.InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylHeLineLoss2ndOrdrCoeff,
                       LpsWrk.InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylHeLineLoss1stOrdrCoeff
                       -> hydraulic Line loss coefficients calulated for a particular machine.
RETURN VALUE: LpsWrk.LiftCylPres-> Hold the hydraulic pressure loss compensated
              lift cylinder pressure in Kpa      
*******************************************************************************/
void LpsCalcDiffPres(void)
{
    LpsStat_t rawStatus = LpsWrk.InputStatus.rawStatus;
    LpsStat_t debouncedStatus = LpsWrk.InputStatus.debouncedStatus;

    if (LPS_STATUS_OK == rawStatus) {
        LpsUpdtTbl_t* updtTbl = LpsWrk.UpdtTbl;
        LpsCalNvmTbl_t* calib = &LpsWrk.InitTbl.MachSpecificCfg.CalibTbl;

        float_32 diffPres;
        float_32 liftCylHePres = updtTbl->LiftCylHePres.Val;
        float_32 liftCylRePres = updtTbl->LiftCylRePres.Val;
        unsigned_16 calVersion = calib->CalVersion;

        // If the calibration is currently active, use the latest version.
        if (updtTbl->CalInProgress) {
            calVersion = LPS_CAL_VERSION_LATEST;
        }

        if ((LPS_HYD_OIL_TEMP_STATUS_DISABLED != LpsWrk.UpdtTbl->HydOilTemp.Stat) &&
                (!LpsWrk.UpdtTbl->LoadCheckValveInstalled)) {
            float_32 hydOilTemp = updtTbl->HydOilTemp.Val;
            float_32 hydOilVisc = LpsGetHydOilVisc(hydOilTemp);
            float_32 hydOilDensity = LpsGetHydOilDensity(hydOilTemp);
            float_32 liftCylVel = updtTbl->LiftCylVel.Val;

            /* Calculating the Head End and Rod End cylinder hydraulic oil flow*/
            float_32 liftCylHeOilFlow = (liftCylVel * LpsWrk.CylFlowConst.LiftHeFlowConst);
            float_32 liftCylReOilFlow = (liftCylHeOilFlow * LpsWrk.CylFlowConst.LiftReToHeFlowRatio);

            /*
             * The temperature compensation strategy models the pressure losses with a quadratic equation in flow
             *  P = Orifice Loss + Line Loss
             *  Orifice Loss = (rho * Q^2) / (2 * Cd^2 * pi^2 * R^4)
             *  Line Loss = (8 * Kg * mu * Q * l) / (pi * R^4)
             *
             *  rho = Density (kg/m^3)
             *  Q = Flow (LPM)
             *  Cd = Discharge Coefficient
             *  R = Effective Radius of Line
             *  Kg = Line Loss Geometry Coefficient
             *  mu = Viscosity (kg/m-s)
             *  l = Line Length
             *
             *  rho, mu are determined from oil type and hydraulic oil temperature
             *  Q is measured
             *  R and l are calculated from the lines geometry
             *  Cd and Kg are determined by regression analysis on test machine data where we have the pressures
             *      measured at the cylinders as well as the production location of the pressure sensors.
             *      An alternative method of determining Cd and Kg is to estimate them from CFD analysis.
             *      (CFD - Computational Fluid Dynamics)
             *
             *  In the end, it doesn't matter much what you pick for R and l because the regression coefficients
             *      Cd and Kg will account for any error there.  The coefficients are lumped up together for
             *      implementation in the PCS code.
             */

            { /* Determining Lift Cylinder Head End pressure drop */
                float_32 oilFlowSquaredCoeff = (LpsWrk.InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylHeLineLoss2ndOrdrCoeff * hydOilDensity);
                float_32 oilFlowCoeff = (LpsWrk.InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylHeLineLoss1stOrdrCoeff * hydOilVisc);

                if (liftCylHeOilFlow >= 0) {
                    /* Flow is going from the valve to cylinder, so the pressure at the cylinder is lower */
                    float_32 oilPresLoss = (liftCylHeOilFlow * liftCylHeOilFlow * oilFlowSquaredCoeff + liftCylHeOilFlow * oilFlowCoeff);
                    liftCylHePres = (liftCylHePres - oilPresLoss);
                }
                else {
                    /* Flow is going from cylinder to valve, so the pressure at the cylinder is higher */
                    float_32 oilPresLoss = (liftCylHeOilFlow * liftCylHeOilFlow * oilFlowSquaredCoeff - liftCylHeOilFlow * oilFlowCoeff);
                    liftCylHePres = (liftCylHePres + oilPresLoss);
                }
            }

            { /* Determining Lift Cylinder Rod End pressure drop */
                float_32 oilFlowSquaredCoeff = (LpsWrk.InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylReLineLoss2ndOrdrCoeff * hydOilDensity);
                float_32 oilFlowCoeff = (LpsWrk.InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylReLineLoss1stOrdrCoeff * hydOilVisc);

                if (liftCylReOilFlow >= 0) {
                    float_32 oilPresLoss = (liftCylReOilFlow * liftCylReOilFlow * oilFlowSquaredCoeff + liftCylReOilFlow * oilFlowCoeff);
                    if (calVersion >= LPS_CAL_VERSION_1) {
                        /* Flow is going from cylinder to valve, so the pressure at the cylinder is higher */
                        liftCylRePres = (liftCylRePres + oilPresLoss);
                    }
                    else {
                        /* This is wrong, but this is the way it used to be with old calibrations. */
                        liftCylRePres = (liftCylRePres - oilPresLoss);
                    }
                }
                else {
                    float_32 oilPresLoss = (liftCylReOilFlow * liftCylReOilFlow * oilFlowSquaredCoeff - liftCylReOilFlow * oilFlowCoeff);
                    if (calVersion >= LPS_CAL_VERSION_1) {
                        /* Flow is going from valve to cylinder, so the pressure at the cylinder is lower */
                        liftCylRePres = (liftCylRePres - oilPresLoss);
                    }
                    else {
                        /* This is wrong, but this is the way it used to be with old calibrations. */
                        liftCylRePres = (liftCylRePres + oilPresLoss);
                    }
                }
            }
        }

        /* Determining/calculating Lift cylinder Rod End Pressure by eliminating the Rod area */
        if ((LpsWrk.CylFlowConst.LiftReToHeFlowRatio > 0.0) &&
                (LpsWrk.CylFlowConst.LiftReToHeFlowRatio <= 1.0)) {
            liftCylRePres = (liftCylRePres * LpsWrk.CylFlowConst.LiftReToHeFlowRatio);
        }

        if (liftCylHePres > liftCylRePres) {
            diffPres = liftCylHePres - liftCylRePres;
        }
        else {
            diffPres = 0.0;
        }

        LpsWrk.LiftCylPressure = diffPres;

        // Perform acceleration compensation for the base linkage excluding bucket and payload
        if ((LPS_LINKAGE_MOVEMENT_STOPPED != LpsWrk.LinkageMovement.lift) &&
                (LpsWrk.InitTbl.MachSpecificCfg.AccelCompSupported) &&
                (calVersion >= LPS_CAL_VERSION_1)) {

            float liftAngle = updtTbl->LiftAngle.Val;

            // Default to the pressure at mid-extension
            float lift_pres0 = LpsWrk.InitTbl.MachSpecificCfg.LiftKpaNoBucketMidExtension;

            // If a map is provided, use it
            if (NULL != LpsWrk.InitTbl.MachSpecificCfg.LiftLinkageMap.presNoBucketkPa) {
                lift_pres0 = LpsLookup(liftAngle,
                        LpsWrk.InitTbl.MachSpecificCfg.LiftLinkageMap.angleDeg,
                        LpsWrk.InitTbl.MachSpecificCfg.LiftLinkageMap.presNoBucketkPa,
                        LpsWrk.InitTbl.MachSpecificCfg.LiftLinkageMap.numPoints);
            }

            // Stay positive
            if (lift_pres0 <= 0.f) {
                lift_pres0 = 0.f;
            }

            // Calculate the acceleration factor
            float accelFactor;
            if ((liftAngle > -90.f) && (liftAngle < 90.f)) {
                float liftVelocity = updtTbl->LiftCylVel.Val;

                float liftRefVelocity = LpsWrk.InitTbl.MachSpecificCfg.LiftLinkageMap.refVelMmPerSec;

                float liftRefAngAccel = LpsLookup(liftAngle,
                        LpsWrk.InitTbl.MachSpecificCfg.LiftLinkageMap.angleDeg,
                        LpsWrk.InitTbl.MachSpecificCfg.LiftLinkageMap.accelDegPerSec2,
                        LpsWrk.InitTbl.MachSpecificCfg.LiftLinkageMap.numPoints);

                float liftAngAccel = (liftRefAngAccel * copysignf(liftVelocity * liftVelocity, liftVelocity)) / (liftRefVelocity * liftRefVelocity); // deg/s^2

                float liftArmAbLengthMeters = LpsWrk.InitTbl.MachSpecificCfg.LiftArmAbLength / 1000.f;

                accelFactor = (liftAngAccel * (float)(PI/180.0) * liftArmAbLengthMeters) / ((float)G * cosf(liftAngle * (float)(PI/180.0)));
            }
            else {
                accelFactor = 0.f;
            }

            // Apply the compensation
            LpsWrk.LiftCylPressureV0 = (LpsWrk.LiftCylPressure + (accelFactor * lift_pres0 / 3.f)) / (1.f + accelFactor);
        }
        else {
            LpsWrk.LiftCylPressureV0 = LpsWrk.LiftCylPressure;
        }

        /*
         * Perform IMU-based compensation for pitch/roll and other source of acceleration.
         * - If IMU compensation is required (LFT installed) and the IMU data is not OK, then we would not get here because
         *   the input status check would have caught it.
         * - If IMU compensation is supported and the IMU data is OK, then use it.
         *
         * - If IMU compensation is supported, but not required, and the IMU data is not OK, then we just turn it off.
         *
         *   On machines where the IMU is diagnosed, like the "Advanced" machine configuration, even if LFT is not installed
         *   there will be an active diagnostic on the IMU is it is not present.
         *
         *   On machines where the IMU is only diagnosed when LFT is installed, like the "Standalone" GC machine configuration,
         *   There could be scenarios where IMU compensation is supported and calibrated, but the IMU data is not OK, in which
         *   case you would not get a diagnostic, and you would not get IMU compensation.  If you calibrate with LFT installed,
         *   then you uninstall LFT, you will still get IMU compensation.  If you calibrate with LFT not installed, you will,
         *   then not get IMU compensation.
         */
        if ((LPS_STATUS_OK == LpsWrk.UpdtTbl->ReferenceIMUData.Stat) &&
                (LpsWrk.InitTbl.MachSpecificCfg.IMUCompSupported) &&
                (!(updtTbl->CalInProgress)) &&
                (LPS_WEIGH_SYSTEM_CALIBRATED == calib->CalStatus)) {
            /*
             * p1 - pressure at calibration conditions
             * ax1 & az1 - acceleration components under calibration conditions
             * p2 - pressure that we actually read now.
             * ax2 & az2 - acceleration components now.
             */
            float p2 = LpsWrk.LiftCylPressureV0;

            // Get the current linear accelerations
            float ax2 = LpsWrk.UpdtTbl->ReferenceIMUData.LinAcc[0];
            float az2 = LpsWrk.UpdtTbl->ReferenceIMUData.LinAcc[2];

            float ax1, az1;
            { // Calculate the linear accelerations during calibration
                /*
                 * Using the raise calibration values for reference.
                 * Using the current uncompensated pressure to look up calibration acceleration vector.
                 * If the acceleration during the calibration is the same as now, then the uncompensated and
                 * compensated pressure would be the same.
                 */
                float scalar;
                float emptyBktPres = LpsLookupExtrap(updtTbl->LiftCylLengthNorm.Val, calib->SlowRaiseEmptyBktLiftHt,
                        calib->SlowRaiseEmptyBktLiftPres,
                        sizeof(calib->SlowRaiseEmptyBktLiftHt) / sizeof(calib->SlowRaiseEmptyBktLiftHt[0]));

                if (p2 <= emptyBktPres) {
                    scalar = 0.f;
                }
                else {
                    float fullBktPres  = LpsLookupExtrap(updtTbl->LiftCylLengthNorm.Val, calib->SlowRaiseFullBktLiftHt,
                            calib->SlowRaiseFullBktLiftPres,
                            sizeof(calib->SlowRaiseFullBktLiftHt) / sizeof(calib->SlowRaiseFullBktLiftHt[0]));

                    if (p2 >= fullBktPres) {
                        scalar = 1.f;
                    }
                    else {
                        scalar = (p2 - emptyBktPres) / (fullBktPres - emptyBktPres);
                    }
                }

                /*
                 * Here we should rotate the full IMU accel vector towards the empty IMU accel vector
                 * the closer we are to empty.  There are complex ways of doing this, and simplified
                 * ways of doing this.
                 *
                 * Complex way:
                 * 1 - find the normalized cross product between the empty and full vectors.
                 * 2 - find the angle between the empty and full vectors.
                 * 3 - Use Rodrigues' rotation formula to rotate the empty vector towards the
                 *     full vector by an amount based on how close the pressure is to the full pressure.
                 *     This would be a portion of the total change in angle between empty and full.
                 * 4 - Adjust the magnitude of the resulting vector based on the weighted average
                 *     of the magnitudes of the empty and full vectors.
                 *
                 * Simplified way:
                 * 1 - Use the y-axis as the vector to rotate around.
                 * 2 - Use the difference between the empty and full calibration pitch as the angle
                 *     between the empty and full vectors.
                 * 3 - Rotate the full vector towards the empty vector by an amount based on how
                 *     close the pressure is to the empty pressure.  A portion of the total change in pitch.
                 * 4 - Leave the resulting magnitude alone since calibrations are done sitting still.
                 *
                 * Even more simplified way:
                 * Do a weighted average of the X and Z components of the empty and full vectors.
                 * For small differences in angle, this is not a bad approximation (~0.1% error @ 5 degrees @ 50% weight).
                 */
                float emptyX = calib->SlowRaiseEmptyIMUAccel[0];
                float emptyZ = calib->SlowRaiseEmptyIMUAccel[2];
                float fullX = calib->SlowRaiseFullIMUAccel[0];
                float fullZ = calib->SlowRaiseFullIMUAccel[2];

                ax1 = emptyX + scalar * (fullX - emptyX);
                az1 = emptyZ + scalar * (fullZ - emptyZ);
            }

            float loadAngle; // Load angle in radians
            { // Calculate the load angle
                float liftAngle = updtTbl->LiftAngle.Val;

                // 2 degrees (tested on WL900100, 962 STD)
                float loadOffsetAngle = LpsWrk.InitTbl.MachSpecificCfg.IMUCompLoadCGAngleOffset;

                loadAngle = (liftAngle + loadOffsetAngle) * (float)(PI/180.0);
            }

            if ((loadAngle > (float)(-PI/2.0)) && (loadAngle < (float)(PI/2.0))) {
                float factor = 1.f;
                float sa = sinf(loadAngle);
                float ca = cosf(loadAngle);
                float den = ax2*sa+az2*ca;

                if (0.f != den) {
                    float num = ax1*sa+az1*ca;
                    factor = num / den;
                }

                // Limit to reasonable values
                if (factor > 1.5f) {
                    factor = 1.5f;
                }
                else if (factor < 0.667f) {
                    factor = 0.667f;
                }

                // p2 = LiftCylPressureV0
                // p1 = LiftCylPressureIMUAdjusted
                LpsWrk.LiftCylPressureIMUAdjusted = LpsWrk.LiftCylPressureV0 * factor;
            }
            else {
                LpsWrk.LiftCylPressureIMUAdjusted = LpsWrk.LiftCylPressureV0;
            }
        }
        else {
            LpsWrk.LiftCylPressureIMUAdjusted = LpsWrk.LiftCylPressureV0;
        }
    }
    else if (LPS_STATUS_BAD == debouncedStatus) {
        LpsWrk.LiftCylPressure = 0.f;
        LpsWrk.LiftCylPressureV0 = 0.f;
        LpsWrk.LiftCylPressureIMUAdjusted = 0.f;
    }
}

/******************************************************************************
FUNCTION NAME: LpsUpdateLinkageMovement
DESCRIPTION: Calculates the state of linkage movement.
             Lift could be Raising (Positive), Lowering (Negative), or Stopped
             Tilt could be Racking (Positive), Dumping (Negative), or Stopped
******************************************************************************/
void LpsUpdateLinkageMovement(void) {
    LpsUpdtTbl_t* updtTbl = LpsWrk.UpdtTbl;
    
    if (NULL != updtTbl) {
        // Update lift movement state
        LpsWrk.LinkageMovement.lift = LpsUpdateLinkageMovementState(
                LpsWrk.LinkageMovement.lift, &(updtTbl->LiftCylVel), &(updtTbl->LiftValveCommand));
        
        // Update tilt movement state
        LpsWrk.LinkageMovement.tilt = LpsUpdateLinkageMovementState(
                LpsWrk.LinkageMovement.tilt, &(updtTbl->TiltCylVel), &(updtTbl->TiltValveCommand));
    } else {
        // Default to 'stopped'.
        LpsWrk.LinkageMovement.lift = LPS_LINKAGE_MOVEMENT_STOPPED;
        LpsWrk.LinkageMovement.tilt = LPS_LINKAGE_MOVEMENT_STOPPED;
    }
}

void LpsCalcInstantWtInit(void)
{
    LpsCalNvmTbl_t const * const calib = &LpsWrk.InitTbl.MachSpecificCfg.CalibTbl;
    float minPoint = -0.5f * calib->CalWeight;
    float maxPoint = 2.0f * calib->CalWeight;
    float previousCalibratedWeight = minPoint;
    float previousAdjustedWeight = minPoint;
    unsigned_8 numPoints = 0;
    unsigned_8 ii;

    /*
     * Make sure both X and Y components of the map are always increasing so we can use the map
     * both forwards and backwards.
     */
    for (ii = 0; ii < LPS_CAL_ADV_CAL_ADJUST_NUM_POINTS; ++ii) {
        float calibratedWeight = calib->AdvCalAdjustX[ii];
        float adjustedWeight = calib->AdvCalAdjustY[ii];

        if (isfinite(calibratedWeight) && (calibratedWeight > previousCalibratedWeight) && (calibratedWeight < maxPoint) &&
                isfinite(adjustedWeight) && (adjustedWeight > previousAdjustedWeight) && (adjustedWeight < maxPoint)) {
            ++numPoints; /* Increment before so we can reserve the first point in the table. */

            LpsWrk.AdvCalAdjust.calibratedWeight[numPoints] = calibratedWeight;
            previousCalibratedWeight = calibratedWeight;

            LpsWrk.AdvCalAdjust.adjustedWeight[numPoints] = adjustedWeight;
            previousAdjustedWeight = adjustedWeight;
        }
    }

    if (numPoints > 0) {
        LpsWrk.AdvCalAdjust.calibratedWeight[0] = minPoint;
        LpsWrk.AdvCalAdjust.adjustedWeight[0] = minPoint;
        ++numPoints;
        LpsWrk.AdvCalAdjust.calibratedWeight[numPoints] = maxPoint;
        LpsWrk.AdvCalAdjust.adjustedWeight[numPoints] = maxPoint;
        ++numPoints;
    }

    LpsWrk.AdvCalAdjust.numPoints = numPoints;
}

/******************************************************************************
FUNCTION LpsCalcInstantWtUpdate
DESCRIPTION: Instantaneous Weight is computed in this function.The function uses
             various calibration maps passed by application to interpolate the
             difference pressure based on lift cylinder extension percentage.
             Lift cylinder velocity is used to determine the direction of movement
             of the linkage and velocity compensation is done to difference pressure
             to determine the weight. 
PARAMETER DESCRIPTION:LpsCalib_t -> calibration table passed by application.
                      LpsWrk.UpdtTbl.LiftCylVel->Lift cylinder velocity.
RETURN VALUE: LpsWrk.InstWtRaw.Val,LpsWrk.InstWtRaw.Stat->Instantaneous weight in Tonnes
              and status.
*******************************************************************************/
void LpsCalcInstantWtUpdate(void)
{
    LpsStat_t rawStatus = LpsWrk.InputStatus.rawStatus;
    LpsStat_t debouncedStatus = LpsWrk.InputStatus.debouncedStatus;

    if (LPS_WEIGH_SYSTEM_UNCALIBRATED == LpsGetCalibStatus()) {
        rawStatus = LPS_STATUS_BAD;
        debouncedStatus = LPS_STATUS_BAD;
    }

    if (LPS_STATUS_OK == rawStatus) {
        float_32 emptyBktPres;
        float_32 fullBktPres;
        float_32 instRawWtSlope = 0;

        LpsUpdtTbl_t *updtTbl;
        LpsCalNvmTbl_t *calib;
      
        updtTbl = LpsWrk.UpdtTbl;
        calib   = &LpsWrk.InitTbl.MachSpecificCfg.CalibTbl;

        { // Update the static weigh factor
            float_32 raw;
    
            if (LPS_LINKAGE_MOVEMENT_POSITIVE == LpsWrk.LinkageMovement.lift) {
                raw = 0.5;
            } else if (LPS_LINKAGE_MOVEMENT_NEGATIVE == LpsWrk.LinkageMovement.lift) {
                raw = 0.0;
            } else {
                raw = 0.3;
            }

            LpsWrk.StaticWtFactor.OlRaw = raw;
            LpsWrk.StaticWtFactor.OlFilt += ((LpsWrk.InitTbl.ExecRate)/LpsWrk.StaticWtFactor.Tau) * (raw - LpsWrk.StaticWtFactor.OlFilt);
            LpsWrk.StaticWtFactor.Curr = LpsWrk.StaticWtFactor.OlFilt;
        }

        if (LPS_LINKAGE_MOVEMENT_POSITIVE == LpsWrk.LinkageMovement.lift) {
            /* Checking if the linkage is raising */
            float_32 emptyBktVelCompPres;
            float_32 fullBktVelCompPres;
            float_32 linkageSpd = updtTbl->LiftCylVel.Val;

            /* Determining calibration empty and full bucket pressure (for raise) based on linkage height/lift cylinder extension */
            emptyBktPres = LpsLookupExtrap(updtTbl->LiftCylLengthNorm.Val,calib->SlowRaiseEmptyBktLiftHt,
                    calib->SlowRaiseEmptyBktLiftPres,
                    sizeof(calib->SlowRaiseEmptyBktLiftHt) / sizeof(calib->SlowRaiseEmptyBktLiftHt[0]));

            fullBktPres  = LpsLookupExtrap(updtTbl->LiftCylLengthNorm.Val,calib->SlowRaiseFullBktLiftHt,
                    calib->SlowRaiseFullBktLiftPres,
                    sizeof(calib->SlowRaiseFullBktLiftHt) / sizeof(calib->SlowRaiseFullBktLiftHt[0]));

            /* Velocity compensation */
            if (linkageSpd < calib->EmptyBktSlowRaiseSpd) {
                emptyBktVelCompPres = 0.0;
            }
            else if (linkageSpd > calib->EmptyBktFastRaiseSpd) {
                emptyBktVelCompPres = calib->FastRaiseEmptyBktDeltaPres;
            }
            else if (calib->EmptyBktFastRaiseSpd > calib->EmptyBktSlowRaiseSpd) {
                emptyBktVelCompPres = ((calib->FastRaiseEmptyBktDeltaPres/(calib->EmptyBktFastRaiseSpd - calib->EmptyBktSlowRaiseSpd)) *
                             (linkageSpd - calib->EmptyBktSlowRaiseSpd));
            }
            else {
                emptyBktVelCompPres = 0.0;
            }

            if (linkageSpd < calib->FullBktSlowRaiseSpd) {
                fullBktVelCompPres = 0.0;
            }
            else if (linkageSpd > calib->FullBktFastRaiseSpd) {
                fullBktVelCompPres = calib->FastRaiseFullBktDeltaPres;
            }
            else if (calib->FullBktFastRaiseSpd > calib->FullBktSlowRaiseSpd) {
                fullBktVelCompPres = ((calib->FastRaiseFullBktDeltaPres/(calib->FullBktFastRaiseSpd - calib->FullBktSlowRaiseSpd)) *
                        (linkageSpd - calib->FullBktSlowRaiseSpd));
            }
            else {
                fullBktVelCompPres = 0.0;
            }

            emptyBktPres = (emptyBktPres + emptyBktVelCompPres);
            fullBktPres  = (fullBktPres + fullBktVelCompPres);
        }
        else if (LPS_LINKAGE_MOVEMENT_NEGATIVE == LpsWrk.LinkageMovement.lift) {
            /* Checking if the linkage is lowering */
            emptyBktPres = LpsLookupExtrap(updtTbl->LiftCylLengthNorm.Val,calib->SlowLowerEmptyBktLiftHt,
                    calib->SlowLowerEmptyBktLiftPres,
                    sizeof(calib->SlowLowerEmptyBktLiftHt) / sizeof(calib->SlowLowerEmptyBktLiftHt[0]));

            fullBktPres  = LpsLookupExtrap(updtTbl->LiftCylLengthNorm.Val,calib->SlowLowerFullBktLiftHt,
                    calib->SlowLowerFullBktLiftPres,
                    sizeof(calib->SlowLowerFullBktLiftHt) / sizeof(calib->SlowLowerFullBktLiftHt[0]));
        }
        else {
            /* Linkage is not moving */
            float_32 emptyBktRaisePres;
            float_32 fullBktRaisePres;
            float_32 emptyBktLowerPres;
            float_32 fullBktLowerPres;

            emptyBktRaisePres = LpsLookupExtrap(updtTbl->LiftCylLengthNorm.Val,calib->SlowRaiseEmptyBktLiftHt,
                    calib->SlowRaiseEmptyBktLiftPres,
                    sizeof(calib->SlowRaiseEmptyBktLiftHt) / sizeof(calib->SlowRaiseEmptyBktLiftHt[0]));

            emptyBktLowerPres = LpsLookupExtrap(updtTbl->LiftCylLengthNorm.Val,calib->SlowLowerEmptyBktLiftHt,
                    calib->SlowLowerEmptyBktLiftPres,
                    sizeof(calib->SlowLowerEmptyBktLiftHt) / sizeof(calib->SlowLowerEmptyBktLiftHt[0]));

            fullBktRaisePres  = LpsLookupExtrap(updtTbl->LiftCylLengthNorm.Val,calib->SlowRaiseFullBktLiftHt,
                    calib->SlowRaiseFullBktLiftPres,
                    sizeof(calib->SlowRaiseFullBktLiftHt) / sizeof(calib->SlowRaiseFullBktLiftHt[0]));

            fullBktLowerPres  = LpsLookupExtrap(updtTbl->LiftCylLengthNorm.Val,calib->SlowLowerFullBktLiftHt,
                    calib->SlowLowerFullBktLiftPres,
                    sizeof(calib->SlowLowerFullBktLiftHt) / sizeof(calib->SlowLowerFullBktLiftHt[0]));

            emptyBktPres = ((emptyBktRaisePres - emptyBktLowerPres) * LpsWrk.StaticWtFactor.Curr) + emptyBktLowerPres;
            fullBktPres  = ((fullBktRaisePres  -  fullBktLowerPres) * LpsWrk.StaticWtFactor.Curr) + fullBktLowerPres;
        }

        /* Determining Instantaneous Weight based on calibration payload weight */
        if (fullBktPres > emptyBktPres) {
            float_32 InstWrRawV0;
            float_32 InstWrRawIMUAdjusted;

            instRawWtSlope = (calib->CalWeight / (fullBktPres - emptyBktPres));

            InstWrRawV0 = (instRawWtSlope * (LpsWrk.LiftCylPressureV0 - emptyBktPres));
            InstWrRawIMUAdjusted = (instRawWtSlope * (LpsWrk.LiftCylPressureIMUAdjusted - emptyBktPres));

            LpsWrk.InstWrRawIMUComp = InstWrRawIMUAdjusted - InstWrRawV0;

            // Use the IMU adjusted weight if IMU compensation is enabled
            if (updtTbl->IMUCompEnabled) {
                LpsWrk.InstWtRaw.Val  = InstWrRawIMUAdjusted;
            }
            else {
                LpsWrk.InstWtRaw.Val  = InstWrRawV0;
            }

            LpsWrk.InstWtRaw.Stat = LPS_INST_RAW_WT_STATUS_OK;

        }
        else {
            LpsWrk.InstWrRawIMUComp = 0.0;
            LpsWrk.InstWtRaw.Val  = 0.0;
            LpsWrk.InstWtRaw.Stat = LPS_INST_RAW_WT_STATUS_BAD;
        }

        LpsWrk.InstWtRawPreTiltComp = LpsWrk.InstWtRaw.Val;
        LpsWrk.InstWtRawPostTiltComp = LpsTiltCompensation(LpsWrk.InstWtRaw.Val, instRawWtSlope);

        // Only do tilt compensation if we are not racked.
        if (LPS_WEIGHT_BKT_FULLY_RACKED == LpsWeighGetDumpState()) {
            LpsWrk.InstWtRaw.Val = LpsWrk.InstWtRawPreTiltComp;
        }
        else {
            LpsWrk.InstWtRaw.Val = LpsWrk.InstWtRawPostTiltComp;
        }
    }
    else if (LPS_STATUS_BAD == debouncedStatus) {
        LpsWrk.InstWrRawIMUComp = 0.0;
        LpsWrk.InstWtRawPreTiltComp = 0.0;
        LpsWrk.InstWtRawPostTiltComp = 0.0;

        /* Raw and Debounced are BAD, set status. */
        LpsWrk.InstWtRaw.Val  = 0.0;
        LpsWrk.InstWtRaw.Stat = LPS_INST_RAW_WT_STATUS_BAD;
    }
}

/******************************************************************************
FUNCTION NAME:LpsTiltCompensation
DESCRIPTION: This function computes the Tilt Compensation factor to be scaled on 
             the raw instantaneous weight. 
PARAMETER DESCRIPTION:
    InstRawWr -> This is the Raw Weight calculated prior to applying tilt compensation
    InstRawWtSlope -> This is the Raw Weight Slope which is
              ((Cal Weight)/(Full pressure - empty pressure))*(Current pressure - empty pressure)
RETURN VALUE: float_32 the tilt compensation value
*******************************************************************************/
float_32 LpsTiltCompensation(float_32 instRawWt, float_32 instRawWtSlope)
{
    float_32 tiltcompH;
    float_32 tiltcompGain;
    float_32 compWt;
    LpsMachSpecificCfg_t* LpsMachSpecConfTbl = &LpsWrk.InitTbl.MachSpecificCfg;

    /*
     * In the case that any of the compensation maps are NULL, then we need go to Lookup2d and we can
     * safely assume that the tilt compensation gain to be 0
     */
    if ((NULL == LpsMachSpecConfTbl->TiltMap.ColumnAxis) ||
            (NULL == LpsMachSpecConfTbl->TiltMap.RowAxis) ||
            (NULL == LpsMachSpecConfTbl->TiltMap.Data)) {
        tiltcompH = 0;
    }
    else {
        tiltcompH = LpsLookup2d(LpsWrk.UpdtTbl->LiftCylLengthNorm.Val,LpsWrk.UpdtTbl->TiltCylLengthNorm.Val,
                LpsMachSpecConfTbl->TiltMap.ColumnAxis,LpsMachSpecConfTbl->TiltMap.RowAxis,
                LpsMachSpecConfTbl->TiltMap.Data,LpsMachSpecConfTbl->TiltMap.NumColumns,
                LpsMachSpecConfTbl->TiltMap.NumRows);
    }

    /*
     * We are obtaining the tilt compensation gain by scaling on the Raw Weight Slope based on the
     * tunable factor to reduce/increase the effect of tilt compensation from the app side and
     * Lookup tilt compensation gain
     */
    tiltcompGain = instRawWtSlope * tiltcompH * LpsMachSpecConfTbl->TiltComp.TiltCompGainScalar;

    /* We want to limit the range of the calculated tilt gain value to the maximum limiting value */
    if (tiltcompGain > LpsMachSpecConfTbl->TiltComp.TiltCompMaxGain) {
        tiltcompGain = LpsMachSpecConfTbl->TiltComp.TiltCompMaxGain;
    }
    /*
     * Here we want to limit the range of the calculated tilt gain value not only to the positive
     * maximum limit, but also to the negative minimum limit
     */
    else if(tiltcompGain < ((float_32)-1.0 * LpsMachSpecConfTbl->TiltComp.TiltCompMaxGain)) {
        tiltcompGain = (float_32)-1.0 * LpsMachSpecConfTbl->TiltComp.TiltCompMaxGain;
    }

    /* If the Tilt Compensation gain is at the highest limit, then retain the old weight */
    if (((float_32)0.0 == ((float_32)1.0 - tiltcompGain)) ||
            (LpsMachSpecConfTbl->CalibTbl.EmptyBucketWeightEst <= (float_32)0.0)) {
        /* Retain the old weight */
        compWt = instRawWt;
    }
    else {
        /* Here the actual scaling factor is added to the raw instantaneous weight */
        float_32 num = instRawWt +
                tiltcompGain * LpsMachSpecConfTbl->CalibTbl.EmptyBucketWeightEst *
                LpsMachSpecConfTbl->TiltComp.TiltCompEmptyBktWtGain;

        compWt = num / ((float_32)1.0 - tiltcompGain);
    }

    return compWt;
}

/*
 * Update the linkage movement state machine.
 * Given the current state, the cylinder velocity and the valve command,
 * determines the state of movement.  Positive, Negative or Stopped.
 */
static LpsLinkageMovementStat_t LpsUpdateLinkageMovementState(
        LpsLinkageMovementStat_t currentState,
        LpsFloatIO_t const * cylinderVelocity,
        LpsFloatIO_t const * valveCommand)
{

    LpsLinkageMovementStat_t state = currentState;

    // Default each to 0, stopped
    float velocity = (LPS_STATUS_OK == cylinderVelocity->Stat) ? cylinderVelocity->Val : 0.f;
    float command = (LPS_STATUS_OK == valveCommand->Stat) ? valveCommand->Val : 0.f;;

    // For detecting motion, command, if available, takes precedence over velocity
    if (command >= LPS_LINKAGE_MOVEMENT_COMMAND_PCT) {
        state = LPS_LINKAGE_MOVEMENT_POSITIVE;
    }
    else if (command <= -(LPS_LINKAGE_MOVEMENT_COMMAND_PCT)) {
        state = LPS_LINKAGE_MOVEMENT_NEGATIVE;
    }
    else if (velocity > LPS_LINKAGE_MOVEMENT_VELOCITY_MMPS) {
        state = LPS_LINKAGE_MOVEMENT_POSITIVE;
    }
    else if (velocity < -(LPS_LINKAGE_MOVEMENT_VELOCITY_MMPS)) {
        state = LPS_LINKAGE_MOVEMENT_NEGATIVE;
    }
    else {
        // When coming to a stop, both command and velocity have to agree.
        if (LPS_LINKAGE_MOVEMENT_POSITIVE == state) {
            // Have we come to a stop?
            if ((command <= 0.f) && (velocity <= 0.f)) {
                state = LPS_LINKAGE_MOVEMENT_STOPPED;
            }
        }
        else if (LPS_LINKAGE_MOVEMENT_NEGATIVE == state) {
            // Have we come to a stop?
            if ((command >= 0.f) && (velocity >= 0.f)) {
                state = LPS_LINKAGE_MOVEMENT_STOPPED;
            }
        }
        else {
            // We are stopped and still stopped
            state = LPS_LINKAGE_MOVEMENT_STOPPED;
        }
    }

    return state;
}

void LpsLiftPositionFiltInit(void)
{
    /*
     * Initialize lift position filtering
     * This has to be the same filtering used for weight so that it has the same delay
     * characteristics.
     */
    cpm_filter_band_stop_filter_init(&LpsWrk.LiftPositionFilt.lenFilter1,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.StageOneCf,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.DampingRate,
            LpsWrk.InitTbl.ExecRate);

    cpm_filter_band_stop_filter_init(&LpsWrk.LiftPositionFilt.lenFilter2,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.StageTwoCf,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.DampingRate,
            LpsWrk.InitTbl.ExecRate);

    cpm_filter_band_stop_filter_init(&LpsWrk.LiftPositionFilt.lenFilter3,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.StageThreeCf,
            LpsWrk.InitTbl.MachSpecificCfg.LlwTbl.DampingRate,
            LpsWrk.InitTbl.ExecRate);

    /* Initialize cylinder velocity calculation */

    /* Calculate the filter factor using the matched pole method kff = 1-e^(-wT) */
    float kff = 1 - expf(-LpsWrk.InitTbl.MachSpecificCfg.LiftVelFilterCf*LpsWrk.InitTbl.ExecRate);

    cpm_filter_derivative_filter_init(&LpsWrk.LiftPositionFilt.velFilter, kff, LpsWrk.InitTbl.ExecRate);

    LpsWrk.LiftPositionFilt.length = 0.f;
    LpsWrk.LiftPositionFilt.velocity = 0.f;
    LpsWrk.LiftPositionFilt.angle = 0.f;
}

void LpsLiftPositionFiltUpdate(void)
{
    /* Update angular velocity calculation */
    if (LPS_STATUS_OK == LpsWrk.UpdtTbl->LiftCylLength.Stat) {
        float len = LpsWrk.UpdtTbl->LiftCylLength.Val;
        len = cpm_filter_band_stop_filter(&LpsWrk.LiftPositionFilt.lenFilter1, len);
        len = cpm_filter_band_stop_filter(&LpsWrk.LiftPositionFilt.lenFilter2, len);
        len = cpm_filter_band_stop_filter(&LpsWrk.LiftPositionFilt.lenFilter3, len);
        float vel = cpm_filter_derivative_filter(&LpsWrk.LiftPositionFilt.velFilter, len);

        LpsWrk.LiftPositionFilt.length = LpsWrk.LiftPositionFilt.velFilter.y[1]; // delayed by 1 loop to align with velocity
        LpsWrk.LiftPositionFilt.velocity = vel;
        LpsWrk.LiftPositionFilt.angle = LpsLookup(LpsWrk.LiftPositionFilt.length,
                LpsWrk.InitTbl.MachSpecificCfg.LiftLinkageMap.cylLenMm,
                LpsWrk.InitTbl.MachSpecificCfg.LiftLinkageMap.angleDeg,
                LpsWrk.InitTbl.MachSpecificCfg.LiftLinkageMap.numPoints);
    }
    else if (LPS_STATUS_BAD == LpsWrk.InputStatus.debouncedStatus) {
        cpm_filter_band_stop_filter_reset(&LpsWrk.LiftPositionFilt.lenFilter1);
        cpm_filter_band_stop_filter_reset(&LpsWrk.LiftPositionFilt.lenFilter2);
        cpm_filter_band_stop_filter_reset(&LpsWrk.LiftPositionFilt.lenFilter3);
        cpm_filter_derivative_filter_reset(&LpsWrk.LiftPositionFilt.velFilter);

        LpsWrk.LiftPositionFilt.length = 0.f;
        LpsWrk.LiftPositionFilt.velocity = 0.f;
        LpsWrk.LiftPositionFilt.angle = 0.f;
    }
}

void LpsInputStatusInit()
{
    LpsWrk.InputStatus.rawStatus = LPS_STATUS_BAD;
    LpsWrk.InputStatus.debouncedStatus = LPS_STATUS_BAD;;
    LpsWrk.InputStatus.debounceCount = 0;
}

void LpsInputStatusUpdate()
{
    /* Update the raw status */
    if (STATUS_GOOD == LpsChkInputStat()) {
        if (LPS_STATUS_OK != LpsWrk.InputStatus.rawStatus) {
            LpsWrk.InputStatus.debounceCount = (unsigned_32)(((float_32)LPS_INPUT_STATUS_TIME_TO_OK / LpsWrk.InitTbl.ExecRate) + 0.5f);
            LpsWrk.InputStatus.rawStatus = LPS_STATUS_OK;
        }
    }
    else {
        if (LPS_STATUS_BAD != LpsWrk.InputStatus.rawStatus) {
            LpsWrk.InputStatus.debounceCount = (unsigned_32)(((float_32)LPS_INPUT_STATUS_TIME_TO_BAD / LpsWrk.InitTbl.ExecRate) + 0.5f);
            LpsWrk.InputStatus.rawStatus = LPS_STATUS_BAD;
        }
    }

    if (TRUE == LpsWrk.UpdtTbl->UseFilterDataFlag) {
        /* Once we are debounced, update the debounced status */
        if (LpsWrk.InputStatus.debounceCount <= 0) {
            LpsWrk.InputStatus.debouncedStatus = LpsWrk.InputStatus.rawStatus;
        }
    }
    else {
        /* Application says hold off */
        LpsWrk.InputStatus.debouncedStatus = LPS_STATUS_BAD;
    }

    /* Decrement the debounce counter */
    if (LpsWrk.InputStatus.debounceCount > 0) {
        LpsWrk.InputStatus.debounceCount--;
    }
}

/******************************************************************************
FUNCTION NAME: LpsGetCalibStatus
DESCRIPTION: Returns the calibration status
PARAMETER DESCRIPTION: None
RETURN VALUE: unsigned_8 CalStat
*******************************************************************************/
LpsWeighCalStatus_t LpsGetCalibStatus()
{
    return LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStatus;
}

