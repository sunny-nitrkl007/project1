/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsPrivate.h
DESCRIPTION:
*******************************************************************************/
#ifndef __LPS_PRIVATE_H__
#define __LPS_PRIVATE_H__
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <LpsPublic.h>
#ifndef __CPM_FILTER_H__
#include <cpm_filter.h>
#endif
/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
#define PI_CONST  (float_32) 3.1415926535897932384626433832795
#define HYDRAULIC_OIL_TEMP_MIN_VALID_DATA (-32736.0) /* PID data */
#define HYDRAULIC_OIL_TEMP_INVALID_DATA (HYDRAULIC_OIL_TEMP_MIN_VALID_DATA - 1)

/* Input Status Debounce Times (seconds) */
#define LPS_INPUT_STATUS_TIME_TO_OK (5.0)
#define LPS_INPUT_STATUS_TIME_TO_BAD (1.0)

/* Pitch Icon Debounce Times (seconds) */
#define PITCH_DEBOUNCE_TIME_TO_OK (0.5)
#define PITCH_DEBOUNCE_TIME_TO_BAD (0.5)

/* Auto Zero Timer */
#define LPS_INIT_ZERO_INTERVAL          (300)       /*  seconds */
#define LPS_AUTO_ZERO_INTERVAL          (7200)     /*  seconds */
#define LPS_ZERO_SNOOZE_INTERVAL        (600)      /*  seconds */
#define LPS_EMPTY_CAL_OIL_TEMP_DELTA    (5.0)       /* 5.0 degrees C */
#define LPS_OIL_TEMP_DELTA              (10.0)      /* 10.0 degrees C */

#define TOO_SLOW_NUMBER_OF_SAMPLES 32766
#define MIN_LIFT_VELOCITY 1.0

#define LPS_TILT_CYL_EXT_DUMP_DELTA 5.0
#define LPS_TILT_EXT_FULL_DUMP_LIMIT 2.0
#define PCS_TILT_ANG_ABC_PCT_FULL_DUMP_LIMIT 2.0

#define LPS_OVERLOAD_DISABLE_THRESHOLD 110.0
#define LPS_OVERLOAD_WT_THRESHOLD 116.5

#define LPS_OVERLOAD_DISABLE_THRESHOLD 110.0
#define LPS_OVERLOAD_WT_THRESHOLD 116.5

/* Linkage Movement Thresholds */

/*
 * Integrated payload system used valve command and accounted for the deadband like so:
 *  511 bits -> 0% and 32000 bits -> 100%
 * When we get the valve commands over the datalink, they are mapped like so:
 *  0 bits -> 0% and 32767 bits -> 100%
 * In order to replicate integrated payload system functionality, we need to map 511 bits
 * onto the datalink range and use that as the threshold for commanding motion:
 *  511 / 32767 = 0.0156 ~= 2%
 */
#define LPS_LINKAGE_MOVEMENT_COMMAND_PCT (2.0)
#define LPS_LINKAGE_MOVEMENT_VELOCITY_MMPS (20.0)

/*
 * The maximum number of points is the configured table plus the initial and final point.
 */
#define LPS_ADV_CAL_ADJUST_MAP_MAX_POINTS (LPS_CAL_ADV_CAL_ADJUST_NUM_POINTS + 2)

/* Stall Detect Lift Height Thresholds */
#define LPS_LIFT_HT_CLOSE_TO_FULL_RAISE (98.0)
#define LPS_LIFT_HT_NOT_FULL_RAISE (97.0)
#define LPS_LIFT_HT_CLOSE_TO_FULL_LOWER (2.0)
#define LPS_LIFT_HT_NOT_FULL_LOWER (3.0)

typedef struct
{
    float_32 LiftHeFlowConst;
    float_32 LiftReToHeFlowRatio;
}LpsCylFlowConst_t;

typedef enum {
  LPS_WEIGH_LIVE_WEIGH_STATUS_VALID = 0,
  LPS_WEIGH_LIVE_WEIGH_STATUS_INVALID
}LpsLiveWeighStat_t;

typedef struct
{
    boolean liftRaiseStalled;
    boolean liftLowerStalled;
    boolean liftStalled;
} LpsStallDetect_t;

typedef enum {
    LPS_LINKAGE_MOVEMENT_STOPPED = 0,
    LPS_LINKAGE_MOVEMENT_POSITIVE,
    LPS_LINKAGE_MOVEMENT_NEGATIVE
} LpsLinkageMovementStat_t;

typedef struct {
    LpsLinkageMovementStat_t lift;
    LpsLinkageMovementStat_t tilt;
} LpsLinkageMovement_t;

typedef struct {
    float_32 calibratedWeight[LPS_ADV_CAL_ADJUST_MAP_MAX_POINTS];
    float_32 adjustedWeight[LPS_ADV_CAL_ADJUST_MAP_MAX_POINTS];
    unsigned_8 numPoints;
} LpsAdvCalAdjust_t;

typedef struct
{
    float_32 lastInput;
    float_32 meanEst;
    float_32 meanEstComp;
    float_32 varianceEst;
    float_32 stdevEst;
    float_32 confidenceEst;
    float_32 confidenceTimer;
} LpsLlwFactors_t;

typedef struct
{
    float_32 Wt;
    LpsWeighRangeWarning_t Warning;
    LpsWeighRangeLatched_t Status;
    LpsWeighRangeIndicator_t Indicator;
} LpsWeighWrwOpTbl_t;

typedef struct
{
    boolean BeenBelowRange;
    boolean Weighing;
    boolean ReweighPosted;

    unsigned_16 count;
    float weightSum; // Used to calculate the final average
    float weightSumIMUComp; // Used to calculate the average IMU compensation weight adjustment
    float imuLinAccSum[3]; // x, y, z used to find average linear acceleration vector
    float imuAngVelSum[3]; // x, y, z used to find average angular velocity vector
    float pitchSum; // degrees
    float rollSum; // degrees

    float weightMax; // tonnes
    float weightMin; // tonnes

    float liftAngFiltStart; // deg
    float liftAngFiltEnd; // deg
    float liftVelFiltSum; // mm/s, Use to fit a line through cylinder velocity
    float liftVelFiltCountSum; // mm/s * n, Use to fit a line through cylinder velocity

    struct {
        float weightMean; // tonnes
        float liftLengthFiltMean; // mm lift cylinder length
        float liftAngleFiltMean; // degrees lift angle
        float weightSumVar;
        float weightLiftLengthSumCov;
    } inc;

    struct {
        float weightAveRaw; // tonnes
        float weightAveRawIMUComp; // tonnes
        float weightAve; // tonnes
        float weightRange; // tonnes
        float weightStd; // tonnes
        float weightStdErr; // tonnes
        float weightChangePerLiftLength; // tonnes per mm lift cylinder length
        float imuAngle; // degrees different from the calibration imu angle
        float pitchAngle; // degrees of pitch
        float rollAngle; // degrees of roll
    } result;
} LpsWeighWrwWkTbl_t;

typedef struct
{
    float maxWeightStdErr;
    float maxWeightRange;
    float maxImuAngVel[3]; // rad/sec, maximum angular velocities, x, y, z.
} LpsWeighWrwErrorLimits_t;

typedef struct
{
    LpsWeighWrwOpTbl_t OpTbl;
    LpsWeighWrwWkTbl_t WkTbl;
    LpsWeighWrwErrorLimits_t ErrLmt;
    LpsWeighWrwReweighStatus_t ReweighWarn;
} LpsWeighWrwTbl_t;

typedef struct
{
    float_32 Tau;
    float_32 OlRaw;
    float_32 OlFilt;
    float_32 Curr;
} LpsStaticWtFactor_t;

typedef struct
{
    unsigned_32 LastZeroTime; // Time of last auto zero timer reset
    boolean PwrOn;
    boolean ZeroRequired;
    unsigned_32 LastSnoozedTime; // The time the zero needed status was last snoozed
    LpsZeroNeededStatus_t SnoozedStatus; // The snoozed zero needed status
} LpsZeroAdjAutoSnooze_t;

typedef struct            
{
    float_32 ZeroTemp;
    LpsZeroErrorTypes_t ZeroAdjStatus; // The result of the last zero adjustment attempt
    LpsZeroNeededStatus_t AutoZeroStatus; // The current zero needed status
    LpsZeroAdjAutoSnooze_t ZeroAdjAutoSnooze;
    boolean InitialZeroRequired;
} LpsZeroAdjTbl_t;

typedef struct
{
    BSFILT BSOne;
    BSFILT BSTwo;
    BSFILT BSThree;
    LPFILT WtFilter;
    LPFILT2 OptionalWtFilter;
    float_32 LastInput;
    float_32 MeanEst;
    float_32 MeanEstComp;
    float_32 VarianceEst;
    float_32 StdevEst;
    float_32 Confidence;
    float_32 ConfidenceEst;
    float_32 ConfidenceTimer;
    float_32 Wt;
    LpsLlwStat_t Stat;
} LpsWeighLlw_t;

/******* Dig State ************/
typedef struct {
    boolean Initialized;
    unsigned_16 StartupDelay;
    unsigned_8 NumSamples;
    float_32 DumpCumulativeWtChange;
    float_32 WtStabilityGain;
    float_32 WtStabilityThreshold;
    float_32 WtStabilityIndex;
} LpsWeighDumpWtChange_t;

typedef struct {
    boolean DigStarted;
    boolean DigDetected;
    LpsWeighBktDigStat_t DigState;
    boolean WtStabilized;
    unsigned_32 DigDuration;
} LpsWeighDigDetect_t;

typedef struct
{
    float_32* StartPtr;
    float_32* EndPtr;
    float_32* FixedEndPtr;
    float_32* FixedStartPtr;
    float_32* IndexPtr;
    unsigned_8 MaxSamples;
} LpsWeighWtRateChangePtrs_t;

/******* Live Weight ************/
typedef struct
{
    LPFILT FastFilter;
    LPFILT SlowFilter;
    float_32 Wt;
    LpsLiveWeighStat_t Stat;
    boolean UseFastFilter;
} LpsWeighLiveWeigh_t;

/**********Overload Warnings**********/
typedef struct
{
    float_32 BucketLoadFactor;
    unsigned_8 PrevDigState;
    boolean DigReverseFlag;
    boolean InOverloadRange;
    LpsWeighOverloadLevel_t Level;
} LpsWeighOverloadWarnings_t;

typedef struct
{
    BSFILT lenFilter1;
    BSFILT lenFilter2;
    BSFILT lenFilter3;
    DERFILT velFilter;
    float_32 length;
    float_32 velocity;
    float_32 angle;
} LpsWeighLiftPositionFilt_t;

typedef struct
{
    LpsStat_t rawStatus;
    LpsStat_t debouncedStatus;
    unsigned_32 debounceCount;
} LpsWeighInputStatus_t;

typedef struct
{
    boolean rawStatus;
    boolean debouncedStatus;
    unsigned_32 debounceCount;
} LpsWeighExcessivePitchDebounce_t;

typedef struct
{
    unsigned_16 timeIntervalInMins;
    unsigned_16 elapsedMins;
    unsigned_16 maxLiftsRequired;
    unsigned_16 remaininingLiftsRequired;
} LpsWarmupLiftsRequired_t;

typedef struct
{
    float_32 LiftCylPressure; // Lift cylinder pressure, resolved to head-end
    float_32 LiftCylPressureV0; // Lift cylinder pressure estimate @ 0 velocity
    float_32 LiftCylPressureIMUAdjusted; // Lift cylinder pressure estimate adjusted for frame accel and rotations.
    float_32 InstWtLlwFilt;
    float_32 InstWtDer;
    float_32 InstWrRawIMUComp;
    float_32 InstWtRawPreTiltComp;
    float_32 InstWtRawPostTiltComp;
    LpsInstWtRaw_t InstWtRaw;
    float_32 InstWtFiltIMUComp;
    float_32 InstWtFilt;
    LpsInitErrorTypes_t InitErr;
    LpsUpdtErrorTypes_t UpdtErr;
    LpsInitTbl_t InitTbl;
    LpsUpdtTbl_t* UpdtTbl;
    LpsCylFlowConst_t CylFlowConst;
    LpsLinkageMovement_t LinkageMovement;
    LpsAdvCalAdjust_t AdvCalAdjust;
    LpsStaticWtFactor_t StaticWtFactor;
    LpsLlwFactors_t LlwFactors;
    LpsWeighWrwTbl_t WrwTbl;
    LpsStallDetect_t LpsStallDetect;
    LpsWeighBktDumpStat_t DumpStateStatus;
    LpsWeighBestBktWt_t BestBktWt;
    LpsWeighLlw_t LowLiftWt;
    LpsZeroAdjTbl_t ZeroAdjTbl;
    LpsWeighDumpWtChange_t DumpWtChangeData;
    LpsWeighDigDetect_t DigDetectData;
    LpsWeighWtRateChangePtrs_t WtRateChangePtrs;
    LpsWeighLiveWeigh_t LiveWeighTbl;
    LpsWeighOverloadWarnings_t OverloadWarnTbl;
    LpsWeighLiftPositionFilt_t LiftPositionFilt;
    LpsWeighInputStatus_t InputStatus;
    LpsWeighExcessivePitchDebounce_t PitchIconDebounce;
    LpsWarmupLiftsRequired_t WarmupLifts;
} LpsWrkTbl_t;

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif
void LpsResetWrkTbl(void);
void LpsCopyAppInitTbl(LpsInitTbl_t* newInitTbl);
void LpsCalcCylFlowConst(void);
void LpsUpdateLinkageMovement(void);
void LpsCalcDiffPres(void);

void LpsCalcInstantWtInit(void);
void LpsCalcInstantWtUpdate(void);

LpsWeighCalStatus_t LpsGetCalibStatus();

void LpsInputStatusInit(void);
void LpsInputStatusUpdate(void);

void LpsLiftPositionFiltInit(void);
void LpsLiftPositionFiltUpdate(void);

void LpsLlwInit(void);
void LpsLowLiftWeighCalcUpdate(void);
void LpsWeighResetLlwWt(void);

void LpsAutoWeighRangeUnlatchWt(void);
void LpsWeighRangeWeighInit(void);
void LpsWeighRangeWeighUpdate(void);
void LpsWeighResetWeighRangeWeight(void);
void LpsWeighExcessivePitchDetect(void);

void LpsWeighZeroInit(void);
void LpsWeighAutoZeroUpdate(void);

float_32 LpsAdvCalAdjust(float_32 unadjustedWeight);
float_32 LpsZeroSpanAdjust(float_32 unadjustedWeight);
void LpsWeighResetLowLiftWeight(void);
void LpsSetDefaultErrLimits(void);

/******* Finding out the Gear Status **********/
boolean LpsWeighIsRequestedGearForward(void);
boolean LpsWeighIsRequestedGearReverse(void);

float_32 LpsTiltCompensation(float_32 instRawWt, float_32 instRawWtSlope);
void LpsTiltCylExtPercentStatus(void);

/******* Best bucket weight ************/
void LpsWeighBestBktWtInit(void);
void LpsWeighBestBktWtUpdate(void);

/******* Dig State ************/
LpsInitErrorTypes_t LpsWeighDigDetectInit(LpsWeighDumpWtBuffer_t DumpWtBuffer);
void LpsWeighDigDetectUpdate(void);
void LpsWeighDumpWtChangeUpdate(void);

/******* Dump State ************/
boolean LpsWeighFullRackDetect(void);
boolean LpsWeighFullRackDetectStrict(void);
boolean LpsWeighFullDumpDetect(void);
boolean LpsWeighPartialDumpDetect(void);
void LpsWeighDumpDetectUpdate(void);
void LpsWeighDumpDetectInit(void);

/******* Live Weight ************/
void LpsLiveWeighInit(void);
void LpsLiveWeighCalc(void);
void LpsWeighResetLiveWt(void);

/**********Overload Warnings***********/
void LpsOverloadWeightInit(void);

/**********Stall detect***********/
void LpsLiftStallDetectUpdate(void);

#ifdef __cplusplus
}
#endif

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
extern LpsWrkTbl_t LpsWrk;
extern LpsWeighBktDumpStat_t DumpStateStatus;


#endif /* #ifndef __LPS_PRIVATE_H__ */
