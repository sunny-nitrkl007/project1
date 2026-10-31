/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsInit.c
DESCRIPTION:This file provides the initialization routines for the application software
            for LPS library.
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
/* Has prototypes of interfaces and functions which are*/
/* exported to the application using the library       */
/*******************************************************/
#include <LpsPublic.h>
#endif

/*******************************************************/ 
/* Has prototypes of interfaces and functions which are*/
/* used within the payload computation library         */
/*******************************************************/
#include "LpsPrivate.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
LpsWrkTbl_t LpsWrk = {0};
 
/******************************************************************************
FUNCTION NAME: LpsInit
DESCRIPTION: This function is an API interface for the application software to initialize
             the LPS library.The function accepts machine configuration                       
PARAMETER DESCRIPTION: LpsAppInitTbl ->This interface holds the application configurations
                       for the LPS library.It consists of various machine specific 
                       parameters like cylinder bore area,rod radius,Oil temperature
                       coefficients etc.LPS library configures the internal algorithm
                       based this interface.LPS library makes a local copy of this interface
                       in the work table for further refernec during payload computation.
                       Any change to this interface by application software will not be recognized
                       by the library until a re-init request or ECM key cycle.
                       
RETURN VALUE: LpsInitErrorTypes_t-> This enum interface reports various error types reported by
              LpsInit function to the application software.
*******************************************************************************/
LpsInitErrorTypes_t LpsInit(LpsInitTbl_t  *LpsAppInitTbl)
{
    LpsResetWrkTbl();

    LpsWrk.InitErr = LPS_INIT_UNKNOWN_ERROR;

    if (NULL == LpsAppInitTbl) {
        LpsWrk.InitErr =  LPS_INIT_CONFIG_ERROR;
        return LpsWrk.InitErr;
    }

    if ((0 == LpsAppInitTbl->MachSpecificCfg.NoOfLiftCyls) ||
            (0.0 == LpsAppInitTbl->ExecRate) ||
            (0.0 == LpsAppInitTbl->MachSpecificCfg.LiftCylBoreDia) ||
            (0.0 == LpsAppInitTbl->MachSpecificCfg.LiftCylRodDia) ||
            (NULL == LpsAppInitTbl->MachSpecificCfg.LiftLinkageMap.angleDeg) ||
            (NULL == LpsAppInitTbl->MachSpecificCfg.LiftLinkageMap.cylLenMm) ||
            (LpsAppInitTbl->MachSpecificCfg.LiftLinkageMap.numPoints < 2)) {
        LpsWrk.InitErr =  LPS_INIT_CONFIG_ERROR;
        return LpsWrk.InitErr;
    }

    // Check all of the things required by acceleration compensation.
    if (LpsAppInitTbl->MachSpecificCfg.AccelCompSupported) {
        if ((LpsAppInitTbl->MachSpecificCfg.KgPerLiftKpaAtMidExtension <= 0.f) ||
                (LpsAppInitTbl->MachSpecificCfg.LiftKpaNoBucketMidExtension <= 0.f) ||
                (LpsAppInitTbl->MachSpecificCfg.LiftArmAbLength <= 0.f) ||
                (NULL == LpsAppInitTbl->MachSpecificCfg.LiftLinkageMap.gainDegPerMm) ||
                (NULL == LpsAppInitTbl->MachSpecificCfg.LiftLinkageMap.accelDegPerSec2) ||
                (LpsAppInitTbl->MachSpecificCfg.LiftLinkageMap.refVelMmPerSec <= 0.f)) {
            LpsWrk.InitErr =  LPS_INIT_CONFIG_ERROR;
            return LpsWrk.InitErr;
        }
    }

    // Check all of the things required by IMU-based compensation.
    if (LpsAppInitTbl->MachSpecificCfg.IMUCompSupported) {
        /*
         * Currently, no additional model specific parameters are needed for IMU-based compensation.
         * This could change in the future if we need to be more specific about IMU mounting location
         * in relation to the load.
         */
    }

    /*
     * As LPS application configurations are
     * validated,the configurations are copied into the
     * LPS library work table for processing.The LPS library is
     * designed to work on local copy of application configurations
     * rather than using the actual configuration interface of the application.
     */
    LpsCopyAppInitTbl(LpsAppInitTbl);

    /*
     * If IMU-based compensation is supported, then make sure we have the calibration
     * values necessary to actually perform it.
     * In the case where LFT is installed, when IMU-based compensation is required, the system
     * will be considered out of calibration if the values are not available.
     */
    if (LPS_WEIGH_SYSTEM_UNCALIBRATED == LpsGetCalibStatus()) {
        LpsWrk.InitTbl.MachSpecificCfg.IMUCompSupported = FALSE;
    }
    else if ((0.f == LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseEmptyIMUAccel[0]) &&
            (0.f == LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseEmptyIMUAccel[1]) &&
            (0.f == LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseEmptyIMUAccel[2])) {
        LpsWrk.InitTbl.MachSpecificCfg.IMUCompSupported = FALSE;
    }
    else if ((0.f == LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseFullIMUAccel[0]) &&
            (0.f == LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseFullIMUAccel[1]) &&
            (0.f == LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseFullIMUAccel[2])) {
        LpsWrk.InitTbl.MachSpecificCfg.IMUCompSupported = FALSE;
    }

    /*
     * Calculating hydraulic oil flow constands for lift cyclinder
     * based on machine specific values passed by application software
     */
    LpsCalcCylFlowConst();

    LpsInputStatusInit();

    LpsLiftPositionFiltInit();

    LpsCalcInstantWtInit();

    LpsLiveWeighInit(); /* Initializing Live Weight parameters */

    /*
     * Initializing the band stop and low pass filter configurations
     * used in the low lift weigh calculation
     */
    LpsLlwInit();

    LpsWeighRangeWeighInit();

    LpsOverloadWeightInit();

    LpsWeighZeroInit();

    LpsWrk.InitErr = LpsWeighDigDetectInit(LpsAppInitTbl->DumpWtBuffer);
    if (LPS_INIT_SUCCESS != LpsWrk.InitErr) {
        return LpsWrk.InitErr;
    }

    LpsWeighDumpDetectInit();

    LpsWrk.LpsStallDetect.liftRaiseStalled = FALSE;
    LpsWrk.LpsStallDetect.liftLowerStalled = FALSE;
    LpsWrk.LpsStallDetect.liftStalled = FALSE;

    LpsWeighBestBktWtInit();

    LpsWrk.InitErr = LPS_INIT_SUCCESS;

    return LpsWrk.InitErr;
}
