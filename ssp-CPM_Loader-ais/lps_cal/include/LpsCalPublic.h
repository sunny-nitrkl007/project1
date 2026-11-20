/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsCalPublic.h
DESCRIPTION:
*******************************************************************************/
#ifndef __LPS_CAL_PUBLIC_H__
#define __LPS_CAL_PUBLIC_H__
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCommonStructures.h>
#endif

#ifndef __LPS_COMMON_TYPE_DEF_H__
#include <LpsCommonTypeDef.h>
#endif

#ifndef __LPS_CAL_APP_PUBLIC_H__
#include <LpsCalAppPublic.h> /* Contains type definitions of standard datatypes */
#endif

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

typedef void LpsCalNvmUpdate(const LpsCalNvmTbl_t* pCalNvmTbl);

typedef enum{
    LPS_CAL_INIT_SUCCESS,
    LPS_CAL_INIT_FAIL,
    LPS_CAL_INIT_CONFIG_ERROR,
    LPS_CAL_INIT_DISABLED,
    LPS_CAL_INIT_FAILED,
    LPS_CAL_INVALID_TIME_STEP,
    LPS_CAL_INIT_UNKNOWN_ERROR,
}LpsCalInitErrorTypes_t;

typedef enum{
    LPS_CAL_UPDT_SUCCESS,
    LPS_CAL_UPDT_FAIL,
    LPS_CAL_UPDT_CONFIG_ERROR,
    LPS_CAL_UPDT_DISABLED,
    LPS_CAL_UPDT_CAL_NOT_SUPPORTED,
    LPS_CAL_UPDT_CAL_INIT_FUNC_FAIL,
    LPS_CAL_UPDT_UNKNOWN_ERROR,
}LpsCalUpdtErrorTypes_t;

typedef struct {
    uint32_t internal_msn;
    uint8_t num_of_tilt_cylinders;
    float tool_bc_length;
    float tilt_bore_diameter;
    float tilt_rod_diameter;
    float lift_bore_diameter;
    float lift_rod_diameter;
}LpsCalIMUCfgData;

typedef struct
{    /* tunable commands */
    float_32                  CalSlowRaiseCmd;
    float_32                  CalFastRaiseCmd;
    float_32                  CalSlowLowerCmd;
    float_32                  CalFastLowerCmd;
    float_32                  KgPerKpaAtMidExtension;
    float_32                  LiftCylHeKpaWithoutBktAtMidExtn;
    float_32                  ExecPeriodSec; //pcs_time_step
    boolean                  *CalEnableFlg;  /*FALSE = dis,TRUE = Enable  */
    LpsCalDiffLimits_t        LiftCylDiffLimits;
    LpsEnableDisableQualRead *QualReadEnableOrDisable;
    LpsCalNvmUpdate          *UpdateNvm;
    unsigned_16               SlowRaiseTargetPercent;
    LpsStat_t                 MachineModelCfg;
    boolean                   EEFIMUCalEnable;
    LpsCalIMUCfgData          EEFIMUCalCfgData;
    boolean                   AutoCalsEnabled;  /* default to Manual Cals*/
    float_32 StageOneCf; // First band-stop filter center frequency
    float_32 StageTwoCf; // Second band-stop filter center frequency
    float_32 StageThreeCf; // Third band-stop filter center frequency
    float_32 DampingRatio; // The damping ratio of the band-stop filters
} LpsCalCfg_t;

//get these from update task
typedef struct {
    /*LpsDiffPress replaces unsigned_8 HeadEndStatus and unsigned_8 RodEndStatus*/
    /*LpsDiffPress = HE - RE*/
    LpsFloatIO_t          LiftDiffPress;
    LpsFloatIO_t          LiftCylLengthNorm;
    LpsFloatIO_t          LiftCylVel;
    LpsHydOilTemp_t       HydOilTemp;
    LpsLeverInfo_t        LiftLeverInfo;
    unsigned_32           ServiceHourMeter;         /* Hour meter value.  */
    LpsWeighBktDumpStat_t DumpState;
    LpsFloatIO_t          TiltCylLengthNorm;
    LpsFloatIO_t          TiltAngleABCPercent;
    LpsFloatIO_t          BktAngle;

    // Machine Reference Inertial Measurement Unit (IMU) Data
    // - This is required and used to capture the machine orientation during calibration
    // - The calibrations will fail if faulted is TRUE
    // - If the sensor is required and data is available, faulted = FALSE
    // - If the sensor is required and data is unavailable, faulted = TRUE
    // - If the sensor is not required, data should be default and faulted = FALSE
    LpsIMUData_t ReferenceIMUData;

    // Engine-End-Frame (EEF), Inertial Measurement Unit (IMU) Data
    // - This is only used for calibrating the EEF IMU.
    // - This in only used if EEFIMUCalEnable is true
    LpsIMUData_t EEFIMUData;

    float                 LiftAngle;
    float                 TiltExtension;
    float                 SteeringAngle;
    LpsFloatIO_t          TiltHePressure;
    LpsFloatIO_t          TiltRePressure;
    boolean               CalOvrAcknowledge;
    LpsEngineSpeedRPM_t   EngineSpeed;
    float                 TiltValveCmdPercent;
    boolean               VoltageEventActive;
    boolean               LegalForTradeSealed;

} LpsCalUpdate_t;

typedef struct {
    boolean  CalInProgress;
    boolean  EmptyBktCalDone;
    boolean  FullBktCalDone;
} LpsCalStatus_t;

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

extern LpsCalInitErrorTypes_t LpsCalInit(const LpsCalCfg_t* pCalCfg, const LpsCalNvmTbl_t* pCalData);
extern void LpsCalReinitNvmData(const LpsCalNvmTbl_t* pCalData);
extern LpsCalUpdtErrorTypes_t LpsCalUpdate(const LpsCalUpdate_t* pLpsCalUptTbl);
extern void LpsCalGetCalStatus(LpsCalStatus_t* CalStatus);
extern boolean LpsCalCalInProgress(void);
extern float_32 LpsCalGetLastPayloadWeight(void);
extern unsigned_8 LpsCalGetQualReadStatus(void);
extern void LpsCalDisableLogging();
extern float_32 LpsCalGetIMUCalOffset(void);
extern signed_16 LpsCalAppInfGetEngSpdLmt(void);
extern signed_8 LpsCalAppInfGetRaiseCmdLmt(void);
extern signed_8 LpsCalAppInfGetLowerCmdLmt(void);
extern signed_8 LpsCalAppInfGetRackCmd(void);
extern signed_8 LpsCalAppInfGetDumpCmd(void);

#ifdef __cplusplus
}
#endif
/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/


#endif /* #ifndef __LPS_CAL_PUBLIC_H__ */
