/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsCalAppPublic.h
DESCRIPTION:
*******************************************************************************/
#ifndef __LPS_CAL_APP_PUBLIC_H__
#define __LPS_CAL_APP_PUBLIC_H__
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#ifndef CAL_MGR_H_
#include <cal_mgr.h>
#endif

#include <time.h>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
#define LPS_CAL_CURVE_FIT_NUM_POINTS (11)
#define LPS_CAL_ADV_CAL_ADJUST_NUM_POINTS (5)

//#define LPS_CAL_EMPTY_CAL_ID (0x03A9)
//#define LPS_CAL_FULL_CAL_ID (0x03AA)
#define LPS_CAL_EMPTY_CAL_ID (0x0256)
#define LPS_CAL_FULL_CAL_ID (0x0257)

#define LPS_CAL_EMPTY_CAL { LPS_CAL_EMPTY_CAL_ID, LpsCalEmptyCalMain, NIL, NIL }
#define LPS_CAL_FULL_CAL { LPS_CAL_FULL_CAL_ID, LpsCalFullCalMain, NIL, NIL }


/*
 * The calibration version is meant to control the usage of the calibration data
 * and not necessarily the storage format of the data.  Serialization format
 * version control can be used to control proper defaulting of new fields and
 * converting between old and new data structures and storage formats.  That is
 * not what this is used for.  This is used to version control the calibration
 * process and signal processing.  The intended use will become more apparent
 * by example.
 *
 * LPS_CAL_VERSION_0:
 * - The temperature compensation strategy was broken and the sign of the
 *   rod-end lift pressure sensor pressure drop was incorrect.  The calibration
 *   was performed with this issue, making the resulting calibration data
 *   dependent upon this bug.  We must keep the bug in place when using
 *   the results of a calibration that was performed while the bug existed.
 * - Also, the kinematic acceleration compensation did not exist for this
 *   version of calibration, so the results of a calibration that was performed
 *   with this version must be used without kinematic acceleration compensation.
 *
 * LPS_CAL_VERSION_1:
 * - The temperature compensation strategy was fixed.
 * - Kinematic acceleration compensation was added.
 *
 */
#define LPS_CAL_VERSION_0 (0)
#define LPS_CAL_VERSION_1 (1)
#define LPS_CAL_VERSION_LATEST LPS_CAL_VERSION_1

typedef struct {
    float_32 FullSlowImuOffsetTemp1;
    float_32 FullSlowImuOffsetTemp2;
    float_32 FullSlowImuOffsetTemp3;
    float_32 FullSlowLumpedWeightTemp1;
    float_32 FullSlowLumpedWeightTemp2;
    float_32 FullSlowLumpedWeightTemp3;
    float_32 EmptySlowImuOffsetTemp1;
    float_32 EmptySlowImuOffsetTemp2;
    float_32 EmptySlowImuOffsetTemp3;
    float_32 EmptySlowLumpedWeightTemp1;
    float_32 EmptySlowLumpedWeightTemp2;
    float_32 EmptySlowLumpedWeightTemp3;
    float_32 FullSlowImuOffsetFinal;
    float_32 EmptySlowImuOffsetFinal;
    float_32 FullSlowLumpedWeightFinal;
    float_32 EmptySlowLumpedWeightFinal;
} LpsCalIMUResults_t;

/*
NOTE: Only new items can be added.
Existing items cannot be changed.
*/
typedef struct  {
    unsigned_16 CalStatus;
    float_32 SlowRaiseEmptyBktLiftHt[LPS_CAL_CURVE_FIT_NUM_POINTS];
    float_32 SlowRaiseEmptyBktLiftPres[LPS_CAL_CURVE_FIT_NUM_POINTS];
    float_32 SlowRaiseFullBktLiftHt[LPS_CAL_CURVE_FIT_NUM_POINTS];
    float_32 SlowRaiseFullBktLiftPres[LPS_CAL_CURVE_FIT_NUM_POINTS];
    float_32 SlowLowerEmptyBktLiftHt[LPS_CAL_CURVE_FIT_NUM_POINTS];
    float_32 SlowLowerEmptyBktLiftPres[LPS_CAL_CURVE_FIT_NUM_POINTS];
    float_32 SlowLowerFullBktLiftHt[LPS_CAL_CURVE_FIT_NUM_POINTS];
    float_32 SlowLowerFullBktLiftPres[LPS_CAL_CURVE_FIT_NUM_POINTS];
    float_32 FastRaiseEmptyBktDeltaPres;
    float_32 FastRaiseFullBktDeltaPres;
    float_32 EmptyBktSlowRaiseSpd;
    float_32 EmptyBktFastRaiseSpd;
    float_32 FullBktSlowRaiseSpd;
    float_32 FullBktFastRaiseSpd;
    float_32 CalWeight;
    unsigned_32 ShmEmptyMain;
    unsigned_32 ShmFullMain;
    float_32 EmptyTemp; // Hydraulic oil temperature during empty calibration.
    float_32 FullTemp; // Hydraulic oil temperature during full calibration.
    float_32 EmptyBucketWeightEst;
    float_32 CalAdjust;
    float_32 ZeroWeight;
    float_32 SlowRaiseEmptyIMUAccel[3]; // x, y, z
    float_32 SlowRaiseFullIMUAccel[3]; // x, y, z
    unsigned_16 CalVersion;
    float_32 SlowRaiseEmptyPitch;
    float_32 SlowRaiseEmptyRoll;
    float_32 SlowRaiseFullPitch;
    float_32 SlowRaiseFullRoll;
    float_32 AdvCalAdjustX[LPS_CAL_ADV_CAL_ADJUST_NUM_POINTS];
    float_32 AdvCalAdjustY[LPS_CAL_ADV_CAL_ADJUST_NUM_POINTS];
} LpsCalNvmTbl_t;

typedef struct {
    float_32 ValveCmdPercent;
    boolean InRaiseDetent;
    boolean InLowerDetent;
    boolean InCenter;
    boolean Faulted;
    boolean LeverInfoAvailable;
} LpsLeverInfo_t;

typedef struct{
    signed_16 RaiseCmdLmt;
    signed_16 LowerCmdLmt;
    signed_8 RackCmd;
    signed_8 DumpCmd;
    signed_16 EngSpdLmt;
    boolean CalOvrActive;
} LpsCalAppInfCmdLmt_t;

typedef struct {
    float_32 RaiseCalPercDiffAbsLimit;
    float_32 RaiseCalPercDiffRangeLimit;
    float_32 LowerCalPercDiffAbsLimit;
    float_32 LowerCalPercDiffRangeLimit;
} LpsCalDiffLimits_t;

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

extern void LpsCalAppInfGetCalOvActiveAndCmdLmts(LpsCalAppInfCmdLmt_t* CmdLmts);
extern boolean LpsCalAppInfCalOvActive(void);

/*
extern CAL_MGR_MR_E LpsCalEmptyCalMain(CAL_MGR_MC_E Cmd,
                                CAL_MGR_Work_t* Cmw,
                                CAL_MGR_Cnfg_t const* Cmc,
                                CAL_MGR_Cal_t* Cal);

extern CAL_MGR_MR_E LpsCalFullCalMain(CAL_MGR_MC_E Cmd,
                                        CAL_MGR_Work_t* Cmw,
                                        CAL_MGR_Cnfg_t const* Cmc,
                                        CAL_MGR_Cal_t* Cal);

*/


extern CAL_MGR_MR_E LpsCalEmptyCalMain(CAL_MGR_MC_E Cmd,
                                        unsigned_16 CalId,
                                        unsigned_8* StepNo,
                                        unsigned_16* CalError
                                        );

extern CAL_MGR_MR_E LpsCalFullCalMain(CAL_MGR_MC_E Cmd,
                                        unsigned_16 CalId,
                                        unsigned_8* StepNo,
                                        unsigned_16* CalError
                                        );

#ifdef __cplusplus
}
#endif

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/

//Implement this function app side. Pointer of implemented function will be sent in the init function (init table).
typedef void LpsCalGetAppCalOvCtrl(boolean enable);
typedef void LpsEnableDisableQualRead(unsigned_8 cmd, signed_16* minvalue);


#endif /* #ifndef __LPS_CAL_APP_PUBLIC_H__ */
