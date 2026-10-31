/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsPublic.h
DESCRIPTION:
*******************************************************************************/
#ifndef __LPS_PUBLIC_H__
#define __LPS_PUBLIC_H__
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <LpsCommonTypeDef.h>
#include <LpsCommonStructures.h>
#include <LpsCommonLookUpTblUtility.h>
#include <LpsCalAppPublic.h>
#include <LpsCommonWeight.h>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
//Only for weighing lib internal usage set by the wrapper / app.
#define STATUS_GOOD ((boolean)0)
#define STATUS_BAD ((boolean)1)

typedef enum
{
    LPS_WEIGH_SYSTEM_CALIBRATED = 0,
    LPS_WEIGH_SYSTEM_UNCALIBRATED
} LpsWeighCalStatus_t;

//PCM - PAYLOAD CALC METHOD
#define LPS_WEIGH_PCM_PRIMARY_FILTER_TYPE_DYNAMIC_AVG 0x1
#define LPS_WEIGH_PCM_PRIMARY_FILTER_TYPE_BUTTERWORTH_LP 0x2
#define GET_ACCURACY(PayloadCalcMethod) (((PayloadCalcMethod) & 0x0F00) >> 8)
#define SET_ACCURACY(PayloadCalcMethod, WeightBktAccuracy) (((PayloadCalcMethod) & ~0x0F00) | (((WeightBktAccuracy) & 0x000F) << 8))

//Hydraulic Pressure Sensors, both Head End and Rod End
#define LPS_WEIGH_PCM_SENSOR_TYPE_HPS_HE_RE 0x1

typedef enum {
    LPS_OIL_TYPE_SAE_10W = 0,
    LPS_OIL_TYPE_SAE_0W20
} LpsHydOilType_t;

typedef enum{
    LPS_INIT_SUCCESS = 0,
    LPS_INIT_FAIL,
    LPS_INIT_CONFIG_ERROR,
    LPS_INIT_DISABLED,
    LPS_INIT_UNKNOWN_ERROR
} LpsInitErrorTypes_t;

typedef enum{
    LPS_UPDT_SUCCESS = 0,
    LPS_UPDT_FAIL,
    LPS_UPDT_INPUT_ERROR,
    LPS_UPDT_DISABLED,
    LPS_UPDT_NOT_INIT,
    LPS_UPDT_UNKNOWN_ERROR
} LpsUpdtErrorTypes_t;

typedef enum{
    LPS_INST_RAW_WT_STATUS_OK = 0,
    LPS_INST_RAW_WT_STATUS_BAD = 1,
    LPS_INST_RAW_WT_STATUS_RAISE_STALL = 2,
    LPS_INST_RAW_WT_STATUS_LOWER_STALL = 3
} LpsInstWtRawStat_t;

typedef enum{
    LPS_WEIGH_WARNING_ACTIVE = 0,
    LPS_WEIGH_NO_WARNING_ACTIVE
} LpsWeighRangeWarning_t;

typedef enum{
    LPS_WEIGH_WRW_STATUS_VALID = 0,
    LPS_WEIGH_WRW_STATUS_INVALID
} LpsWeighRangeLatched_t;

typedef enum {
    LPS_WEIGH_LLW_STATUS_VALID = 0,
    LPS_WEIGH_LLW_STATUS_INVALID
} LpsLlwStat_t;

typedef enum {
    LPS_BELOW_WEIGH_RANGE = 0x0323,
    LPS_IN_WEIGH_RANGE_WEIGHING = 0x0325,
    LPS_ABOVE_WEIGH_RANGE = 0x0326,
    LPS_IN_WEIGH_RANGE_NOT_WEIGHING = 0x06CD
} LpsWeighRangeIndicator_t;

typedef struct {
    unsigned_32 numPoints;
    float_32 const* angleDeg;
    float_32 const* cylLenMm;
    float_32 const* gainDegPerMm;
    float_32 const* presNoBucketkPa;
    float_32 const* accelDegPerSec2;
    float_32 refVelMmPerSec;
} LpsWeighLiftLinkageMap_t;

typedef struct
{
    float_32 TiltCompGainScalar;
    float_32 TiltCompEmptyBktWtGain;
    float_32 TiltCompMaxGain;
} LpsTiltCompTbl_t;

typedef struct
{
    unsigned_32     NumColumns;
    unsigned_32     NumRows;
    float_32 const *ColumnAxis;
    float_32 const *RowAxis;
    float_32 const *Data;
} LpsTiltMap_t;

typedef enum {
    LPS_ZERO_UPDATE_SUCCESS = 0,
    LPS_ZERO_UPDATE_NOT_CALIBRATED,
    LPS_ZERO_UPDATE_BUCKET_WT_NOT_ACCURATE,
    LPS_ZERO_UPDATE_HYD_OIL_ERROR,
    LPS_ZERO_UPDATE_TOO_HEAVY_TO_ZERO,
    LPS_ZERO_UPDATE_UNKNOWN_ERROR
} LpsZeroErrorTypes_t;

typedef enum {
    LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED = 0,
    LPS_ZERO_UPDATE_TIMER_EXPIRED_ZERO_REQUIRED,
    LPS_ZERO_UPDATE_TEMPERATURE_CHANGE_ZERO_REQUIRED
} LpsZeroNeededStatus_t;

typedef enum    /* PDI D0 0E9B */   /* Bit Field masks */
{   LPS_WEIGHT_WRW_REWEIGH_WARN_STATUS_NONE = 0x0000,
    LPS_WEIGHT_WRW_REWEIGH_WARN_STATUS_SLOW = 0x8000,
    LPS_WEIGHT_WRW_REWEIGH_WARN_STATUS_STOPPED = 0x4000,
    LPS_WEIGHT_WRW_REWEIGH_WARN_STATUS_NOT_RACKED = 0x2000,
    LPS_WEIGHT_WRW_REWEIGH_WARN_STATUS_JERKY = 0x1000,
    LPS_WEIGHT_WRW_REWEIGH_WARN_STATUS_INCST = 0x0800,
    LPS_WEIGHT_WRW_REWEIGH_WARN_STATUS_CHG2HI = 0x0400,
    LPS_WEIGHT_WRW_REWEIGH_WARN_STATUS_REWEIGH_BUCKET =0x0200,
    LPS_WEIGHT_WRW_REWEIGH_WARN_STATUS_LIFT_TOO_HIGH =0x0100,
    LPS_WEIGHT_WRW_REWEIGH_WARN_STATUS_LIFT_TOO_LOW =0x0080
} LpsWeighWrwReweighWarningStatus_t;

typedef enum   /* Bit Field masks */
{   LPS_WEIGHT_WRW_INFO_POPUP_WARN_STATUS_NONE = 0x00000000,
    LPS_WEIGHT_WRW_INFO_POPUP_WARN_UPPER_STALL = 0x00000008,
    LPS_WEIGHT_WRW_INFO_POPUP_WARN_LOWER_STALL = 0x00000004,
    LPS_WEIGHT_WRW_INFO_POPUP_WARN_BUCKET_NOT_RACKED = 0x00000002,
    LPS_WEIGHT_WRW_INFO_POPUP_WARN_STOPPED_IN_WRG = 0x00000001,
    LPS_WEIGHT_WRW_INFO_POPUP_WARN_PRESS_CHG2HI = 0x00000080,
    LPS_WEIGHT_WRW_INFO_POPUP_WARN_SPEED_CHG2HI = 0x00000040,
    LPS_WEIGHT_WRW_INFO_POPUP_WARN_ZERO_ACCEPTED = 0x00000020,
    LPS_WEIGHT_WRW_INFO_POPUP_WARN_SIMPLE_CAL_ACCEPTED = 0x00000010,
    LPS_WEIGHT_WRW_INFO_POPUP_WARN_INCONSISTENT = 0x00000800,
    LPS_WEIGHT_WRW_INFO_POPUP_WARN_LIFT_TOO_SLOW = 0x00000400,
    LPS_WEIGHT_WRW_INFO_POPUP_WARN_ZERO_UPDATE_NOT_CALIBRATED = 0x00000200,
    LPS_WEIGHT_WRW_INFO_POPUP_WARN_ZERO_UPDATE_BUCKET_WT_NOT_ACCURATE = 0x00000100,
    LPS_WEIGHT_WRW_INFO_POPUP_WARN_ZERO_UPDATE_HYD_OIL_ERROR = 0x00008000,
    LPS_WEIGHT_WRW_INFO_POPUP_WARN_ZERO_UPDATE_TOO_HEAVY_TO_ZERO = 0x00004000,
    LPS_WEIGHT_WRW_INFO_POPUP_WARN_ZERO_UPDATE_UNKNOWN_ERROR = 0x00002000
} LpsInfoPopUpWarningStatus_t;

typedef enum {
    LPS_WEIGH_OVERLOAD_LEVEL_NONE = 0,
    LPS_WEIGH_OVERLOAD_LEVEL_WARNING,
    LPS_WEIGH_OVERLOAD_LEVEL_SEVERE,
} LpsWeighOverloadLevel_t;

typedef struct {
    LpsFloatIO_t LiftCylHePres;
    LpsFloatIO_t LiftCylRePres;
    LpsFloatIO_t LiftAngle;
    LpsFloatIO_t LiftCylLength;
    LpsFloatIO_t LiftCylLengthNorm;
    LpsFloatIO_t LiftCylVel;
    LpsFloatIO_t LiftValveCommand;
    LpsHydOilTemp_t HydOilTemp;
    unsigned_32 ClockKeyonSec;
    unsigned_32 PassCount;
    LpsFloatIO_t TiltCylLengthNorm;
    LpsFloatIO_t TiltCylVel;
    LpsFloatIO_t TiltValveCommand;
    LpsFloatIO_t BktAngle;
    LpsIMUData_t ReferenceIMUData;
    LpsRequestedGear_t RequestedGear;
    float_32 LoaderBktPayldTrgtWt;
    boolean UseFilterDataFlag;
    boolean VoltageEventActive;
    LpsFloatIO_t TiltAngleABCPercent;
    char StandbyActiveState;
    LpsTipoffWeight_t TipoffWeight;
    float_32 GroundSpeed;
    boolean LoadCheckValveInstalled;
    boolean LegalForTradeInstalled;
    boolean LegalForTradeSealed;
    boolean InVerificationMode;
    float_32 WeightInterval; // Display weight interval in tonnes
    float_32 WeightCapacity; // Scale capacity in tonnes
    boolean CalInProgress; // TRUE if calibration is currently being performed
    boolean IMUCompEnabled;
} LpsUpdtTbl_t;

typedef struct {
    float_32 LiftCylHeLineLoss2ndOrdrCoeff;
    float_32 LiftCylHeLineLoss1stOrdrCoeff;
    float_32 LiftCylReLineLoss2ndOrdrCoeff;
    float_32 LiftCylReLineLoss1stOrdrCoeff;
} LpsHydPressLossCoeff_t;

 typedef struct {
    unsigned_16 TooSlow:1;
    unsigned_16 Stopped:1;
    unsigned_16 NotRacked:1;
    unsigned_16 Jerky:1;
    unsigned_16 Inconsistent:1;
    unsigned_16 RateOfChangeHi:1;
    unsigned_16 ReweighBucket:1;
    unsigned_16 ExcessivePitch:1;
    unsigned_16 WarmUpLift:1;
    unsigned_16 Unused:7;
} LpsWeighWrwReweighStatus_t;

typedef struct {
   float_32 FilterFactorMean;
   float_32 FilterFactorVariance;
   float_32 ErrorBand;
   float_32 MinimumConfidenceTime;
   float_32 AutoWeighRangeConfThr;
   float_32 AutoWeighMinLiftHt;
   float_32 WtCf;
   float_32 StageOneCf;
   float_32 StageTwoCf;
   float_32 StageThreeCf;   
   float_32 DampingRate;
   boolean WtLpsOptional;
   float_32 WtLpsOptionalCf;
} LpsLlwConf_t;

/******* Dig State ************/
typedef struct{
    float_32 DigTargetWt;
    float_32 DigDurationMaxLimit;
    float_32 DigDurationMinLimit;
    float_32 DigStartLimit;
    float_32 DigEndLimit;
    float_32 LiftLowerVelocityLimit;
} LpsWeighDigCfg_t;

/******* Dump State ************/
typedef struct{
    float_32 TiltCylExtThreshold;
    float_32 TiltCylExtThresholdStrict;
    float_32 FullDumpBktAngleThreshold;
    float_32 PartDumpBktAngleThreshold;
    float_32 FullRackBktAngleThreshold;
    float_32 TiltAngleABCThreshold;
} LpsWeighDumpCfg_t;

/******* Live Weight ************/
typedef  struct {
    float_32 FastFiltWtCf;
    float_32 SlowFiltWtCf;
} LpsWeighLiveWtCfg_t;

typedef  struct {
    unsigned_8 NoOfLiftCyls;
    float_32 LiftCylBoreDia;
    float_32 LiftCylRodDia;
    float_32 LiftArmAbLength;
    LpsWeighLiftLinkageMap_t LiftLinkageMap; /* Lift linkage maps, angle, cylinder length and gain. */
    float_32 KgPerLiftKpaAtMidExtension;
    float_32 LiftKpaNoBucketMidExtension;
    float_32 LiftVelFilterCf; /* Corner frequency for velocity low pass filter (rad/s) */
    boolean AccelCompSupported;
    boolean IMUCompSupported;
    float_32 IMUCompLoadCGAngleOffset;
    LpsHydOilType_t HydOilType;
    LpsCalNvmTbl_t CalibTbl;
    LpsHydPressLossCoeff_t HydPressLossCoeff;
    float_32 StartOfWeigh;
    float_32 EndOfWeigh;
    float_32 ReweighMaxPitch; // Maximum allowed pitch up-hill for green box, in degrees
    float_32 ReweighMinPitch; // Minimum allowed pitch down-hill for green box, in degrees
    float_32 ReweighMaxAbsRoll; // Maximum allowed absolute value of roll for green box, in degrees
    float_32 ReweighMinLiftCylVel; // Minimum allowed lift cylinder velocity for green box, in mm/s
    LpsLlwConf_t LlwTbl;
    LpsWeighBktWtAccuracy_t ZeroBktWtAccuracyLimit;
    float_32 ZeroRangeLimit;
    unsigned_32 ZeroAdjInitTimeInterval;
    unsigned_32 ZeroAdjAutoTimeInterval;
    unsigned_32 ZeroAdjAutoTimeIntervalFast;
    float_32 ZeroAdjOilTempWarnThreshold;
    float_32 ZeroAdjOilTempDelta;
    LpsTiltCompTbl_t TiltComp;
    LpsTiltMap_t TiltMap;
    LpsWeighDigCfg_t DigConfig;
    LpsWeighDumpCfg_t DumpConfig;
    LpsWeighLiveWtCfg_t LiveWeighConfig;
} LpsMachSpecificCfg_t;


typedef struct
{
    float_32 Val;
    LpsInstWtRawStat_t Stat;
} LpsInstWtRaw_t;

typedef struct
{
    float* PtrDumpWtBuffer;
    unsigned_8 bufferSize;
} LpsWeighDumpWtBuffer_t;

typedef struct 
{
    float_32 ExecRate;
    LpsMachSpecificCfg_t MachSpecificCfg;
    LpsWeighDumpWtBuffer_t DumpWtBuffer;
} LpsInitTbl_t;

typedef struct 
{
    float_32 Wt;
    unsigned_16  PayloadCalcMeth;
    LpsWeighBktWtAccuracy_t Accuracy;
    boolean Latched; /* indicates if we have a latched bucket weight */
    boolean LatchConditionsOK; /* indicates if latch conditions are ok */
    boolean TipoffLiveWeightInUse; /* indicates if live weight is Tipoff weight */
} LpsWeighBestBktWt_t;

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

extern LpsInitErrorTypes_t LpsInit(LpsInitTbl_t *LpsAppInitTbl);
extern LpsUpdtErrorTypes_t LpsUpdt(LpsUpdtTbl_t *LpsAppUpdtTbl);
extern boolean LpsChkInputStat(void);

extern LpsInstWtRawStat_t LpsGetPayloadRatio(float* raw, float* filtered);
extern LpsInstWtRaw_t LpsGetRawInstWt(void);
extern float_32 LpsGetLiftCylPressure(void);
extern float_32 LpsGetLiftCylPressureV0(void);
void LpsSetCalAdjustFactor(float_32 CalAdjust);
extern boolean LpsGetExcessivePitchStatus(void);

boolean LpsWeighEstimateFrictionCoefficient(float* mu, float* offset);

/******* Weigh Range weight ************/
extern unsigned_16 LpsGetWeighRangeIndicator(void);
extern LpsWeighWrwReweighStatus_t LpsGetWrwReweighWarning(void);
extern float_32 LpsGetWeighRangeWeight(void);
extern LpsWeighRangeIndicator_t LpsWeighGetWeighRangeIndicator(void);
extern unsigned_16 LpsRemainingWarmupLiftsRequired(void);

/******* Zero function ************/
extern LpsZeroNeededStatus_t LpsWeighGetAutoZeroUpdateStatus(void);
extern boolean LpsWeighIsZeroWeightAvailable(void);
extern LpsZeroErrorTypes_t LpsWeighGetZeroAdjStatus(void);
extern float_32 LpsWeighGetZeroWeight(void);
extern boolean LpsWeighZeroAdjust(void);
extern boolean LpsInitialZeroRequired(void);

/******* Best bucket weight ************/
extern LpsWeighBestBktWt_t LpsWeighGetBestAvailableBktWt(void);
extern void LpsWeighResetBestAvailableBktWt(void);
LpsWeighOverloadLevel_t LpsWeighOverloadWarningLevel(void);
boolean LpsWeighRaiseStallWarningActive(void);
boolean LpsWeighLowerStallWarningActive(void);

/******* Dump State ************/
extern LpsWeighBktDumpStat_t LpsWeighGetDumpState(void);
extern void LpsWeighSetTiltExtensionThreshold(void);

/******* Dig State ************/
extern LpsWeighBktDigStat_t LpsWeighGetDigState(void);
extern void LpsWeighEndDig(void);

/* *** BucketLoadFactor**********/
extern float LpsWeighGetBucketLoadFactor();

#ifdef __cplusplus
}
#endif

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
#endif /* #ifndef __LPS_PUBLIC_H__ */
