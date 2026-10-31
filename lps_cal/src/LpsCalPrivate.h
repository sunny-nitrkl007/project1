/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsPrivate.h
DESCRIPTION:
*******************************************************************************/
#ifndef __LPS_CAL_PRIVATE_H__
#define __LPS_CAL_PRIVATE_H__
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <stdarg.h> // Required for LpsCalPrint

#include <cpm_filter.h>

#include "LpsCalIMU.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
#define LPS_CAL_QUAL_READ_ENABLE	1
#define LPS_CAL_QUAL_READ_DISABLE	0

#define LPS_CAL_ERROR_ACTIVE_DIAG 0x0002
#define LPS_CAL_NOT_SUPPORTED     0x000B
#define LPS_CAL_MACHINE_MODEL_NOT_SET	0x1041
#define LPS_CAL_ERROR_LIFT_PRESS_0 (0x107C)
#define LPS_CAL_PAYLOAD_LEGAL_FOR_TRADE_SEALED  0x136C

#define LPS_CAL_OIL_TEMP_MIN	        30.0        /* Degrees C */
#define PCS_CAL_ENGINE_HIGH_IDLE_RPM    1300        /* RPM */

#define LPS_CAL_MAX_WEIGHT 327.67
#define LPS_CAL_MIN_WEIGHT -327.36

#define LPS_CAL_OVR_STATE_INACTIVE (0)
#define LPS_CAL_OVR_STATE_ACTIVE (1)
#define LPS_CAL_OVR_STATE_PENDING_ACTIVE (2)
#define LPS_CAL_OVR_STATE_PENDING_INACTIVE (3)

#define LPS_CAL_APP_MAX_RAISE_CMD (100)
#define LPS_CAL_APP_MAX_LOWER_CMD (-100)
#define LPS_CAL_APP_MAX_RACK_CMD (100)
#define LPS_CAL_APP_MAX_DUMP_CMD (-100)
#define LPS_CAL_APP_MIN_RACK_CMD (0)
#define LPS_CAL_APP_MIN_DUMP_CMD (-0)
#define LPS_CAL_APP_MAX_ENG_SPD (3000)

/* PCS Cal Lift Data Statuses */
#define LPS_CAL_LIFT_GOOD 0
#define LPS_CAL_LIFT_JERKY 1
#define LPS_CAL_LIFT_TOO_SLOW 2
#define LPS_CAL_LIFT_LOW_IDLE 3
#define LPS_CAL_LIFT_DATA_ERROR 4

#define LPS_CAL_TASK_PERIOD_MIN 10  /* min period in ms */
#define LPS_CAL_TASK_PERIOD_MAX 40 /* max period in ms */

#define LPS_CAL_TASK_PERIOD_MIN_SEC (float_32)0.01
#define LPS_CAL_TASK_PERIOD_MAX_SEC (float_32)0.04

// Calibration Definitions
#define LPS_CAL_TOP_OF_CAL 80
#define LPS_CAL_BOTTOM_OF_CAL 35

/* Manual Calibrations (Standalone) */
#define LPS_MANUAL_CAL_EMPTY_WT_CAL_ID  0x0256
#define LPS_MANUAL_CAL_FULL_WT_CAL_ID   0x0257

/* Auto Calibrations (AU2020) */
#define LPS_AUTO_CAL_EMPTY_WT_CAL_ID    0x03A9
#define LPS_AUTO_CAL_FULL_WT_CAL_ID     0x03AA


#define LPS_CAL_CALINFO_CAL_SUCCESS_WITHOUT_ERR 2
#define LPS_CAL_CALINFO_ERROR_LIST_SZ 5


/* Number of samples above the desired tilt extension before proceeding with calibration */
#define LPS_CAL_IMU_CAL_UNRACK_STABLE_SAMPLES       3

typedef struct {
    float_32 RampStartHeight;
    float_32 MinCommandIncRateLimit;
    float_32 CommandIncRateLimit;
    float_32 CommandDecRateLimit;
} LpsCalOvrCtrlCnfg_t;

typedef struct {
    float_32 DumpStartCmd;
    float_32 DumpCommandIncRateLimit;
    float_32 MaxDumpCommandLimit;
    float_32 MinTiltExtensionLimit;
    float_32 MaxTiltExtensionLimit;
    float_32 DesiredTiltExtensionFactor;
    float_32 WaitSecondsBeforeDump;
    float_32 DumpTimeoutSeconds;
    float_32 TiltExtensionNoiseWindowSeconds;
    unsigned_8 NumberofSamplesAtDesiredExt;
} LpsCalTiltOvrCtrlCnfg_t;

typedef struct {
    unsigned_8 InternalStep;
    unsigned_8 CalStep;
} LpsCalStepsMapping_t;


/* Manual Empty Calibration Steps - Communication Step Numbers from ET - Standalone */
typedef enum
{
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_START = 1,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_HYD_OIL = 2,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_RACK_POS = 3,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_LOWER_POS = 4,
    //LPS_CAL_EMPTY_CAL_STEP_ENG_SPD = 5,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_CENTER_LVR_1 = 5,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_RAISE_FAST_VEL_1 = 6,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_LOWER_FAST_VEL_1 = 7,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_CENTER_LVR_2 = 8,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_RAISE_SLOW_1 = 9,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_LOWER_SLOW_1 = 10,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_RAISE_SLOW_2 = 11,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_LOWER_SLOW_2 = 12,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_CENTER_LVR_3 = 13,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_RAISE_FAST_1 = 14,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_LOWER_FAST_1 = 15,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_RAISE_FAST_2 = 16,
    LPS_MANUAL_CAL_EMPTY_CAL_STEP_LOWER_FAST_2 = 17
} LPS_MANUAl_CAL_EMPTY_CAL_STEP;

/* AUTO Calibration Steps - Communication Step Numbers from ET - AU2020 */
typedef enum
{
    LPS_AUTO_CAL_EMPTY_CAL_STEP_START = 1,
    LPS_AUTO_CAL_EMPTY_CAL_STEP_HYD_OIL = 2,
    LPS_AUTO_CAL_EMPTY_CAL_STEP_RACK_POS = 3,
    LPS_AUTO_CAL_EMPTY_CAL_STEP_LOWER_POS = 4,
    LPS_AUTO_CAL_EMPTY_CAL_STEP_ENG_SPD = 5,
    LPS_AUTO_CAL_EMPTY_CAL_STEP_CENTER_LVR_1 = 6,
    LPS_AUTO_CAL_EMPTY_CAL_STEP_RAISE_SLOW_1 = 7,
    LPS_AUTO_CAL_EMPTY_CAL_STEP_LOWER_SLOW_1 = 8,
    LPS_AUTO_CAL_EMPTY_CAL_STEP_RAISE_SLOW_2 = 9,
    LPS_AUTO_CAL_EMPTY_CAL_STEP_LOWER_SLOW_2 = 10,
    LPS_AUTO_CAL_EMPTY_CAL_STEP_CENTER_LVR_2 = 11,
    LPS_AUTO_CAL_EMPTY_CAL_STEP_RAISE_FAST_1 = 12,
    LPS_AUTO_CAL_EMPTY_CAL_STEP_LOWER_FAST_1 = 13,
    LPS_AUTO_CAL_EMPTY_CAL_STEP_RAISE_FAST_2 = 14,
    LPS_AUTO_CAL_EMPTY_CAL_STEP_LOWER_FAST_2 = 15
} LPS_AUTO_CAL_EMPTY_CAL_STEP;


/* Manual Full Calibration Steps - Communication Step Numbers from ET - Standalone */
typedef enum
{
    LPS_MANUAL_CAL_FULL_CAL_STEP_START = 1,
    LPS_MANUAL_CAL_FULL_CAL_STEP_HYD_OIL = 2,
    LPS_MANUAL_CAL_FULL_CAL_STEP_RACK_POS = 3,
    LPS_MANUAL_CAL_FULL_CAL_STEP_LOWER_POS = 4,
    LPS_MANUAL_CAL_FULL_CAL_STEP_CENTER_LVR_1 = 5,
    LPS_MANUAL_CAL_FULL_CAL_STEP_RAISE_FAST_VEL_1 = 6,
    LPS_MANUAL_CAL_FULL_CAL_STEP_LOWER_FAST_VEL_1 = 7,
    LPS_MANUAL_CAL_FULL_CAL_STEP_CENTER_LVR_2 = 8,
    LPS_MANUAL_CAL_FULL_CAL_STEP_RAISE_SLOW_1 = 9,
    LPS_MANUAL_CAL_FULL_CAL_STEP_LOWER_SLOW_1 = 10,
    LPS_MANUAL_CAL_FULL_CAL_STEP_RAISE_SLOW_2 = 11,
    LPS_MANUAL_CAL_FULL_CAL_STEP_LOWER_SLOW_2 = 12,
    LPS_MANUAL_CAL_FULL_CAL_STEP_CENTER_LVR_3 = 13,
    LPS_MANUAL_CAL_FULL_CAL_STEP_RAISE_FAST_1 = 14,
    LPS_MANUAL_CAL_FULL_CAL_STEP_LOWER_FAST_1 = 15,
    LPS_MANUAL_CAL_FULL_CAL_STEP_RAISE_FAST_2 = 16,
    LPS_MANUAL_CAL_FULL_CAL_STEP_LOWER_FAST_2 = 17
} LPS_MANUAL_CAL_FULL_CAL_STEP;


/* Auto Full Calibration Steps - Communication Step Numbers from ET - AU2020 */
typedef enum
{
    LPS_AUTO_CAL_FULL_CAL_STEP_START = 1,
    LPS_AUTO_CAL_FULL_CAL_STEP_HYD_OIL = 2,
    LPS_AUTO_CAL_FULL_CAL_STEP_RACK_POS = 3,
    LPS_AUTO_CAL_FULL_CAL_STEP_LOWER_POS = 4,
    LPS_AUTO_CAL_FULL_CAL_STEP_ENG_SPD = 5,
    LPS_AUTO_CAL_FULL_CAL_STEP_CENTER_LVR_1 = 6,
    LPS_AUTO_CAL_FULL_CAL_STEP_RAISE_SLOW_1 = 7,
    LPS_AUTO_CAL_FULL_CAL_STEP_LOWER_SLOW_1 = 8,
    LPS_AUTO_CAL_FULL_CAL_STEP_RAISE_SLOW_2 = 9,
    LPS_AUTO_CAL_FULL_CAL_STEP_LOWER_SLOW_2 = 10,
    LPS_AUTO_CAL_FULL_CAL_STEP_CENTER_LVR_2 = 11,
    LPS_AUTO_CAL_FULL_CAL_STEP_RAISE_FAST_1 = 12,
    LPS_AUTO_CAL_FULL_CAL_STEP_LOWER_FAST_1 = 13,
    LPS_AUTO_CAL_FULL_CAL_STEP_RAISE_FAST_2 = 14,
    LPS_AUTO_CAL_FULL_CAL_STEP_LOWER_FAST_2 = 15
} LPS_AUTO_CAL_FULL_CAL_STEP;


/* Internal Step Numbers - Used in lps_cal software only */
typedef enum
{
    LPS_CAL_EMPTY_CAL_INT_STEP_START = 0,
    LPS_CAL_EMPTY_CAL_INT_STEP_HYD_OIL = 1,
    LPS_CAL_EMPTY_CAL_INT_STEP_RACK_POS = 2,
    LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_POS = 3,
    LPS_CAL_EMPTY_CAL_INT_STEP_ENG_SPD = 4,
    LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_1 = 5, // mapped to the lever 1 in ET
    LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_VEL_1 = 6,
    LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_VEL_1 = 7,
    LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_2 = 8, // mapped to the lever 2 in ET
    LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_1 = 9,
    LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_1 = 10,
    LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_2 = 11,
    LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_2 = 12,
    LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_SLOW_3 = 13,
    LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_SLOW_3 = 14,
    LPS_CAL_EMPTY_CAL_INT_STEP_CENTER_LVR_3 = 15, //map to lever 1 in ET
    LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_1 = 16,
    LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_1 = 17,
    LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_2 = 18,
    LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_2 = 19,
    LPS_CAL_EMPTY_CAL_INT_STEP_RAISE_FAST_3 = 20,
    LPS_CAL_EMPTY_CAL_INT_STEP_LOWER_FAST_3 = 21,
    LPS_CAL_EMPTY_CAL_INT_STEP_END = 22
} LPS_CAL_EMPTY_CAL_INT_STEP;

typedef enum
{
    LPS_CAL_FULL_CAL_INT_STEP_START = 0,
    LPS_CAL_FULL_CAL_INT_STEP_HYD_OIL = 1,
    LPS_CAL_FULL_CAL_INT_STEP_RACK_POS = 2,
    LPS_CAL_FULL_CAL_INT_STEP_LOWER_POS = 3,
    LPS_CAL_FULL_CAL_INT_STEP_ENG_SPD = 4,
    LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_1 = 5,
    LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_VEL_1 = 6,
    LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_VEL_1 = 7,
    LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_2 = 8, // mapped to the lever 2 in ET
    LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_1 = 9,
    LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_1 = 10,
    LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_2 = 11,
    LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_2 = 12,
    LPS_CAL_FULL_CAL_INT_STEP_RAISE_SLOW_3 = 13,
    LPS_CAL_FULL_CAL_INT_STEP_LOWER_SLOW_3 = 14,
    LPS_CAL_FULL_CAL_INT_STEP_CENTER_LVR_3 = 15,
    LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_1 = 16,
    LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_1 = 17,
    LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_2 = 18,
    LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_2 = 19,
    LPS_CAL_FULL_CAL_INT_STEP_RAISE_FAST_3 = 20,
    LPS_CAL_FULL_CAL_INT_STEP_LOWER_FAST_3 = 21,
    LPS_CAL_FULL_CAL_INT_STEP_END = 22
} LPS_CAL_FULL_CAL_INT_STEP;

typedef enum {
    LPS_CAL_CURVE_FIT_STAT_OK = 0,
    LPS_CAL_CURVE_FIT_STAT_PRESS_0
} LPS_CAL_CURVE_FIT_STAT;

typedef struct {
    float_32 AryPosition[LPS_CAL_CURVE_FIT_NUM_POINTS];
    float_32 AryPressure[LPS_CAL_CURVE_FIT_NUM_POINTS];
    float_32 AverageVelocity;
    float_32 AverageReferencePressure;
    float_32 AverageDeltaPFromReference;
    float_32 AryAverageIMUAccel[3]; // x, y, z
    float_32 AveragePitch;
    float_32 AverageRoll;
} LpsCalCurveFitResults_t;

typedef struct {
    float_32 TotalNumPoints;
    float_32 SumVelocity;
    float_32 SumReferencePressure;
    float_32 SumDeltaPFromReference;
    float_32 ArySumIMUAccel[3]; // x, y, z
    float_32 SumPitch;
    float_32 SumRoll;
    float_32 MaxTiltAngleABCPct;
    float_32 LiftPositionOffRack;
    float_32 AryPosition[LPS_CAL_CURVE_FIT_NUM_POINTS];
    float_32 AryNumPoints[LPS_CAL_CURVE_FIT_NUM_POINTS-1];
    float_32 ArySumX[LPS_CAL_CURVE_FIT_NUM_POINTS-1];
    float_32 ArySumY[LPS_CAL_CURVE_FIT_NUM_POINTS-1];
	float_32 ArySumXX[LPS_CAL_CURVE_FIT_NUM_POINTS-1];
    float_32 ArySumXY[LPS_CAL_CURVE_FIT_NUM_POINTS-1];
    LpsCalCurveFitResults_t const *ReferenceResults;
    BSFILT DeltaPFilter1;
    BSFILT DeltaPFilter2;
    BSFILT DeltaPFilter3;
    float_32 ReferencePressure;
    float_32 DeltaPFromReference;
} LpsCalCurveFitData_t;

typedef struct {
    float_32 CurCommandLimit;
    float_32 ReqCommandLimit;
    float_32 MinCommandLimit;
} LpsCalOvrCtrl_t;

/*
This the structure commonly used for both empty and full cal.
This structure variable resets to defaults in LAST_INIT command.
*/
typedef struct{
	unsigned_8           			InternalStep;
	unsigned_16          			OldCalFlags;
	boolean  						HydOilTempMet;
	boolean  						EnforceRaiseDetent;
	boolean  						EnforceLowerDetent;
	boolean  						RaiseFastVelDone;
	boolean  						RaiseSlowFitDone;
	boolean  						RaiseFastFitDone;
	boolean  						LowerSlowFitDone;
	LpsCalOvrCtrl_t 				LpsCalOvrCtrlRaiseData;
	LpsCalOvrCtrl_t 				LpsCalOvrCtrlLowerData;
	LpsCalCurveFitData_t 			LpsCalRaiseCurveFitData;
	LpsCalCurveFitData_t 			LpsCalLowerCurveFitData;
	LpsCalCurveFitResults_t 		RaiseFitResultsTemp1;
	LpsCalCurveFitResults_t 		RaiseFitResultsTemp2;
	LpsCalCurveFitResults_t 		RaiseFitResultsTemp3;
	LpsCalCurveFitResults_t 		RaiseSlowFitResultsFinal;
	LpsCalCurveFitResults_t 		RaiseFastFitResultsFinal;
	LpsCalCurveFitResults_t 		LowerFitResultsTemp1;
	LpsCalCurveFitResults_t 		LowerFitResultsTemp2;
	LpsCalCurveFitResults_t 		LowerFitResultsTemp3;
	LpsCalCurveFitResults_t 		LowerSlowFitResultsFinal;
	LpsCalIMUResults_t              LpsCalIMUResultsData;
}LpsCalCurveFitInfo_t;

typedef struct{
	unsigned_8  					CalRaiseStatus;
	unsigned_8  					CalLowerStatus;
	unsigned_16 					OffRackEndIndex;
	float_32 						LpsCalPctAbsCopy;
	float_32 						LpsCalPctDiffRangeCopy;
	float_32 						CalTopOfCalLiftHt;
	float_32 						CalBottomOfCalLiftHt;
	float_32 						LpsCalPositionsDefault[LPS_CAL_CURVE_FIT_NUM_POINTS];
	float_32 						LastPayloadWeight;
	boolean							LpsCalOvrStartRequest;
	boolean							LpsCalOvrStopRequest;
	boolean  						CalRaiseActive;
    boolean  						CalRaiseComplete;
    boolean  						CalLowerActive;
    boolean  						CalLowerComplete;
    boolean                         CalUnRackComplete;
    boolean                         CalTiltOverrideComplete;
    boolean                         CalTiltOverrideFail;
} LpsCalInfo_t;

typedef struct{
    boolean     LpsCalTiltOvrStartRequest;
    boolean     LpsCalTiltOvrStopRequest;
    unsigned_8  LpsCalTiltOvrState;
    float_32    TiltNoiseMax;
    float_32    TiltNoiseMin;
    struct timespec StartTime;
    float_32    DesiredTiltExtmm;
    unsigned_8  CountOfSamples;
    float_32    TiltDumpCmdOvr;
}LpsCalTiltOv_t;

typedef struct{
	unsigned_8	LpsCalOvrState;
	signed_8 	LpsCalAppInfRaiseCmdLmt;
	signed_8 	LpsCalAppInfLowerCmdLmt;
	signed_8 	LpsCalAppInfRackCmd;
	signed_8 	LpsCalAppInfDumpCmd;
	signed_16 	LpsCalAppInfEngSpdLmt;
	boolean 	LpsCalAppInfCalOvrActive;
	boolean 	LiftBottomFlag;
    boolean 	LiftTopFlag;
    LpsCalTiltOv_t  LpsCalTiltOv;
}LpsCalOv_t;

typedef struct{
	cal_last_stat_t      		EmptyWtCal;
	cal_last_stat_t 			FullWtCal;
	LpsCalInitErrorTypes_t  	InitErr;
	LpsCalUpdtErrorTypes_t  	UpdateErr;
	LpsCalCfg_t                 Cfg;
	LpsCalNvmTbl_t              Nvm;
	LpsCalUpdate_t     	 		Update;
	LpsCalStatus_t 		 		Status;
	LpsCalInfo_t 				Info;
	LpsCalCurveFitInfo_t		CurveFitInfo;
	LpsCalOv_t					Ov;
	unsigned_8					EnableQualRead;
} LpsCalWrkTbl_t;

typedef enum LpsCalPrintLogLevel_e {
   LPSCAL_LOG_EVERYTHING = 0,
   LPSCAL_LOG_INFO,
   LPSCAL_LOG_WAYPOINT, /* Higher level Info for phase start/completions (e.g. "Initialization complete" message) */
   LPSCAL_LOG_WARNING,
   LPSCAL_LOG_ERROR,
   LPSCAL_LOG_FATAL,
   LPSCAL_LOG_NOTHING
} LpsCalPrintLogLevel_t;

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

void LpsCalPrint( LpsCalPrintLogLevel_t logLevel, char *msg, ... );

unsigned_8 	LpsCalLstatEmptyWtHndlr(unsigned_8 Cmd, struct CAL_LSTAT_T *Work);
unsigned_8 	LpsCalLstatFullWtHndlr(unsigned_8 Cmd, struct CAL_LSTAT_T *Work);
unsigned_8 	LpsCalTranslateStep(unsigned_8 InternalStep,
									const LpsCalStepsMapping_t StepsMapping[],
									unsigned_8 NumMappings);

boolean LpsCalCompareCurveFitResults(LpsCalCurveFitResults_t const * Results1,
        LpsCalCurveFitResults_t const * Results2,
        boolean IsRaise);

boolean LpsCalCompareCurveFitResultRatios(LpsCalCurveFitResults_t const * Results1,
        LpsCalCurveFitResults_t const * Results2,
        boolean IsRaise);

void LpsCalCombineCurveFitResults(LpsCalCurveFitResults_t const * Results1,
        LpsCalCurveFitResults_t const * Results2, LpsCalCurveFitResults_t* FinalResults);

void LpsCalStartLiftOverrides(void);
void LpsCalStartTiltOverrides(void);
void LpsCalResetTiltOverrides(void);
void LpsCalSetLiftOverrides(float_32 RaiseCommandLmt, float_32 LowerCommandLmt);
void LpsCalStopLiftOverrides(void);
void LpsCalStopTiltOverrides(void);
void LpsCalStartRaiseCalData(float_32 CalBottomHeight,
								float_32 CalTopHeight,
								LpsCalCurveFitResults_t const *ReferenceResults);
void LpsCalStartLowerCalData(float_32 CalBottomHeight,
								float_32 CalTopHeight,
								LpsCalCurveFitResults_t const *ReferenceResults);
LPS_CAL_CURVE_FIT_STAT LpsCalGetRaiseCurveFitResults(LpsCalCurveFitResults_t* Results);
void LpsCalGetLowerCurveFitResults(LpsCalCurveFitResults_t  *Results);

void LpsCalAppInfSetCalOvrActive(void);
void LpsCalAppInfSetLiftCmdLimit(float_32 RaiseCommandLmt, float_32 LowerCommandLmt);
void LpsCalAppInfSetCalOvrInactive(void);

void LpsCalAppInfSetTiltCmdOvr(float_32 RackCommand, float_32 DumpCommand);

void LpsCalCopyCfgToWrkTbl(const LpsCalCfg_t* pCalCfg);
void LpsCalCopyNvmToWrkTbl(const LpsCalNvmTbl_t* pCalData);
void LpsCalCopyUpdateToWrkTbl(const LpsCalUpdate_t* pLpsCalUpdate);
void LpsCalResetWrkTbl(void);
void LpsCalResetCurveFitInfo(void);
void LpsCalRunUpdate(void);

LpsCalInitErrorTypes_t	LpsCalSetWrkTblDefaults(void);

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
extern LpsCalWrkTbl_t LpsCalWrkTbl;
extern const float_32 LpsCalBottomStagingHeight;
extern const float_32 LpsCalTopStagingHeight;
extern const float_32 LpsCalSlowBottomHeight;
extern const float_32 LpsCalSlowTopHeight;
extern const float_32 LpsCalFastBottomHeight;
extern const float_32 LpsCalFastTopHeight;
extern const float_32 LpsCalPositionsDefaultVals[LPS_CAL_CURVE_FIT_NUM_POINTS];
extern const LpsCalOvrCtrlCnfg_t LpsCalOvrCtrlRaiseCfg;
extern const LpsCalOvrCtrlCnfg_t LpsCalOvrCtrlLowerCfg;
extern LpsCalStepsMapping_t LpsCalCullCalStepsMapping[];
extern LpsCalStepsMapping_t LpsCalCmptyCalStepsMapping[];
extern const LpsCalTiltOvrCtrlCnfg_t LpsCalTiltOvrCfg;

extern LpsCalPrintLogLevel_t currentLogLevel;

#endif /* #ifndef __LPS_CAL_PRIVATE_H__ */
