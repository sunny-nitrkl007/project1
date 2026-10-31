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
#include <LpsCommonTypeDef.h>
#endif

#ifndef CAL_MGR_H_
#include <cal_mgr.h>
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCalAppPublic.h>
#endif

#ifndef CAL_STRUCT_H_
#include <cal_struct.h>
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCommonStructures.h> /* Contains type definitions of standard datatypes */
#endif

#ifndef __LPS_CAL_PUBLIC_H__
#include <LpsCalPublic.h>
#endif

#ifndef __LPS_CAL_PRIVATE_H__
#include "LpsCalPrivate.h"
#endif

#include <string.h>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
LpsCalWrkTbl_t LpsCalWrkTbl = {0};

const float_32 LpsCalBottomStagingHeight = 2.0;
const float_32 LpsCalTopStagingHeight    = 98.0;
const float_32 LpsCalSlowBottomHeight	  = 10.0;
const float_32 LpsCalSlowTopHeight		  = 90.0;

/*
 * Using the same as the default weigh range here.
 * This is used for the velocity compensation calibration.
 * - high enough that we don't have pressure oscillations.
 * - low enough that we don't get into the high gain (deg/mm) portion of the kinematics.
 * - large enough that we get enough data points to get a good average.
 */
const float_32 LpsCalFastBottomHeight	  = 50.0;
const float_32 LpsCalFastTopHeight		  = 65.0;

const float_32 LpsCalPositionsDefaultVals[LPS_CAL_CURVE_FIT_NUM_POINTS] = { 0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0 };

const LpsCalOvrCtrlCnfg_t LpsCalOvrCtrlRaiseCfg = {
    80.0, /* Ramp Start Height (%) */
    5.0, /* Minimum Command Increasing Rate Limit (%/s) */
    50.0, /* Command Increasing Rate Limit (%/s) */
    80.0 /* Command Decreasing Rate Limit (%/s) */
};

const LpsCalOvrCtrlCnfg_t LpsCalOvrCtrlLowerCfg = {
    20.0, /* Ramp Start Height (%) */
    5.0, /* Minimum Command Increasing Rate Limit (%/s) */
    15.0, /* Command Increasing Rate Limit (%/s) */
    80.0 /* Command Decreasing Rate Limit (%/s) */
};

const LpsCalTiltOvrCtrlCnfg_t LpsCalTiltOvrCfg = {
    -1.0,   /* Dump Start Command (%)*/
    -5.0,   /* Dump Increasing Rate Limit (%/s)*/
    -25.0,  /* Dump Maximum Command Limit (%)*/
     4,     /* Minimum Tilt Extension to override (mm)*/
     8,     /* Maximum Tilt Extenstion to override (mm)*/
     2,     /* Factor to Calculate Desired Tilt Extension from Tilt Noise Range */
     3,     /* Wait for Ride Control to turn on before Tilt Override (seconds)*/
     5,     /* Dump Override Command Timeout (seconds)*/
     1,     /* Window for measuring Tilt Extension Noise Min/Max in seconds*/
     3,     /* Number of samples at desired tilt extension to consider success */
};


/* Default to log everything */
LpsCalPrintLogLevel_t currentLogLevel = LPSCAL_LOG_EVERYTHING;

/******************************************************************************
FUNCTION NAME: LpsCalDisableLogging
DESCRIPTION: Disables calibration library logging
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalDisableLogging() {
    currentLogLevel = LPSCAL_LOG_NOTHING;
}

/******************************************************************************
FUNCTION NAME: LpsCalInit
DESCRIPTION: Initializes cal library.
PARAMETER DESCRIPTION:
LpsCalInit - cal init config from wrapper.
RETURN VALUE: LpsCalInitErrorTypes_t
*******************************************************************************/
LpsCalInitErrorTypes_t LpsCalInit(const LpsCalCfg_t* pCalCfg, const LpsCalNvmTbl_t* pCalData)
{
	LpsCalWrkTbl.InitErr = LPS_CAL_INIT_UNKNOWN_ERROR;

	if ((NULL == pCalCfg) || (NULL == pCalData)) {
		LpsCalWrkTbl.InitErr =  LPS_CAL_INIT_CONFIG_ERROR;
		return LpsCalWrkTbl.InitErr;
	}

	//Reset work table to zero
	LpsCalResetWrkTbl();

    // Copy to WrkTbl.
    LpsCalCopyCfgToWrkTbl(pCalCfg);
    LpsCalCopyNvmToWrkTbl(pCalData);

	/* Initialize the IMU Cals */
	LpsCalIMUInit(pCalCfg->EEFIMUCalEnable, &pCalCfg->EEFIMUCalCfgData);

	//set WrkTbl defaults
    if (LPS_CAL_INIT_SUCCESS != LpsCalSetWrkTblDefaults()) {
		return LpsCalWrkTbl.InitErr;
	}

    /* Set Cal Ids */
    if (pCalCfg->AutoCalsEnabled) {
        LpsCalWrkTbl.EmptyWtCal.wId = LPS_AUTO_CAL_EMPTY_WT_CAL_ID;
        LpsCalWrkTbl.FullWtCal.wId = LPS_AUTO_CAL_FULL_WT_CAL_ID;
    }
    else {
        LpsCalWrkTbl.EmptyWtCal.wId = LPS_MANUAL_CAL_EMPTY_WT_CAL_ID;
        LpsCalWrkTbl.FullWtCal.wId = LPS_MANUAL_CAL_FULL_WT_CAL_ID;
    }

	LpsCalPrint(LPSCAL_LOG_WAYPOINT, "cal init success.");

	LpsCalWrkTbl.InitErr = LPS_CAL_INIT_SUCCESS;
	return LpsCalWrkTbl.InitErr;

}

void LpsCalReinitNvmData(const LpsCalNvmTbl_t* pCalData) {
    LpsCalCopyNvmToWrkTbl(pCalData);
}

