//test_lps_lib.cc
#include <gtest/gtest.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <LPSCommonTypeDef.h> /* Contains type definitions of standard datatypes */
#include <LpsCommonStructures.h> /* Contains structures which are common between all LPS
                                  * system libraries */
#include <LpsCommonLookUpTblUtility.h>
#include <LpsPrivate.h> /*******************************************************/
                        /* Contains prototypes of interfaces and functions    */
                        /* which are used within the payload computation       */
                        /* library                                             */
                        /*******************************************************/
#include <LpsPublic.h> /*******************************************************/
                       /* Contains prototypes of interfaces and functions    */
                       /* which are exported to the application using the     */
                       /* library                                             */
                       /*******************************************************/
					   
LpsMachSpecificCfg_t cfg;
LpsCalib_t cal;
LpsInitTbl_t tbl;
LpsUpdtTbl_t lpsUpdateTbl;
extern LpsWrkTbl_t LpsWrk;
LpsUpdtErrorTypes_t ret;

//////////////////////////////////////////////////////////////////////////////////
//LOW LIFT WEIGHT CALCULATION
TEST(LPSLlwTest, LPSLlwFunctional)
{	
lpsUpdateTbl.LiftCylHePres.Val  = 6000;
lpsUpdateTbl.LiftCylHePres.Stat = LPS_PRES_STATUS_OK;

lpsUpdateTbl.LiftCylRePres.Val  = 3000;
lpsUpdateTbl.LiftCylRePres.Stat = LPS_PRES_STATUS_OK;
	
lpsUpdateTbl.LiftCylExt.Val 	= 40;
lpsUpdateTbl.LiftCylExt.Stat 	= LPS_CYL_EXT_STAT_OK;
	
lpsUpdateTbl.LiftCylVel.Val 	= 40;
lpsUpdateTbl.LiftCylVel.Stat 	= LPS_CYL_VEL_STATUS_OK;
	
lpsUpdateTbl.HydOilTemp.Val  	= 50;
lpsUpdateTbl.HydOilTemp.Stat 	= LPS_HYD_OIL_TEMP_STATUS_OK;  

lpsUpdateTbl.TiltCylExt.Val		= 75;    
lpsUpdateTbl.TiltCylExt.Stat 	= LPS_CYL_EXT_STAT_OK;

lpsUpdateTbl.BktAngle.Val		= 41;
lpsUpdateTbl.BktAngle.Stat   	= LPS_BKT_ANGLE_STATUS_OK;

//calibration status
cal.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;

//machine specific config
cfg.NoOfLiftCyls = 2;
cfg.LiftCylBoreDia = 140;
cfg.LiftCylRodDia = 85;
cfg.HydOilType = LPS_OIL_TYPE_SAE_10W;
cfg.CalibTbl = cal;

cfg.LlwTbl.FilterFactorMean = 0.927407213;
cfg.LlwTbl.FilterFactorVariance = 0.927407213;
cfg.LlwTbl.ErrorBand = 1;
cfg.LlwTbl.MinimumConfidenceTime = 1.25;
cfg.LlwTbl.AutoWeighRangeConfThr = 0.997;
cfg.LlwTbl.AutoWeighMinLiftHt = 30;
cfg.LlwTbl.WtCf = 10;
cfg.LlwTbl.StageOneCf = 10;
cfg.LlwTbl.StageTwoCf = 10;
cfg.LlwTbl.StageThreeCf = 10;
cfg.LlwTbl.DampingRate = 1;
cfg.DigConfig.DigTargetWt = 120;

//init table
tbl.InstallStat = 1;
tbl.ExecRate = 0.02;
tbl.MachSpecificCfg = cfg;

LpsWrk.UpdtTbl = &lpsUpdateTbl;
LpsWrk.InitTbl = tbl;
LpsWrk.LpsStallDetect.LiftStallStat = LPS_LIFT_STALL_NOT_STALLED;
LpsWrk.DumpStateStatus = LPS_WEIGHT_BKT_FULLY_RACKED;
LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.FullDumpBktAngleThreshold = -35;
LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.PartDumpBktAngleThreshold =  40;
LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.FullRackBktAngleThreshold =  35;
LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold       =  90;
LpsWrk.DigDetectData.DigState = LPS_WEIGHT_BKT_NOT_DIGGING;

unsigned int count = 0;

LpsWrk.LowLiftWt.LastInput = 10.0;
LpsLlwInit();
EXPECT_EQ(LPS_INIT_SUCCESS,LpsWrk.InitErr);

PayloadDumpStateInit();
LpsWeighDumpWtChangeUpdate();
LpsWeighDumpDetectUpdate();

/*case 1 - With some instantaneous weight value */
for(count = 0; count < 20000; count++)
{
LpsWrk.InstWtRaw.Val = 12.0;
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(12.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 2 - changing the instantaneous weight to see if the Llw changes */
for(count = 0; count < 20000; count++)
{
LpsWrk.InstWtRaw.Val = 5.0;
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(5.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 3 - Dig target weight less than 0 */
for(count = 0; count < 20000; count++)
{
LpsWrk.InitTbl.MachSpecificCfg.DigConfig.DigTargetWt = -10;
LpsWrk.InstWtRaw.Val = 5.0;
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(5.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 4 - Dig target weight equal to 0 */
for(count = 0; count < 20000; count++)
{
LpsWrk.InitTbl.MachSpecificCfg.DigConfig.DigTargetWt = 0.0;
LpsWrk.InstWtRaw.Val = 5.0;
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(5.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 5 - lift cylinder velocity value greater than 0 */
for(count = 0; count < 20000; count++)
{
LpsWrk.InitTbl.MachSpecificCfg.DigConfig.DigTargetWt = 80;
LpsWrk.InstWtRaw.Val = 5.0;
lpsUpdateTbl.LiftCylVel.Val = 40;
lpsUpdateTbl.LiftCylVel.Stat = LPS_CYL_VEL_STATUS_OK;
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(5.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 6 - lift cylinder velocity value less than 0 */
for(count = 0; count < 20000; count++)
{
LpsWrk.InitTbl.MachSpecificCfg.DigConfig.DigTargetWt = 80;
LpsWrk.InstWtRaw.Val = 20.0;
lpsUpdateTbl.LiftCylVel.Val = -10;
lpsUpdateTbl.LiftCylVel.Stat = LPS_CYL_VEL_STATUS_BAD;
ret = LpsUpdt(&lpsUpdateTbl);
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(5.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 7 - lift cylinder extension less than auto weigh minimum lift height */
for(count = 0; count < 20000; count++)
{
LpsWrk.InitTbl.MachSpecificCfg.DigConfig.DigTargetWt = 80;
LpsWrk.InstWtRaw.Val = 5.0;
lpsUpdateTbl.LiftCylExt.Val = 25;
lpsUpdateTbl.LiftCylExt.Stat = LPS_CYL_EXT_STAT_OK;
ret = LpsUpdt(&lpsUpdateTbl);
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(5.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 8 - lift cylinder extension greater than auto weigh minimum lift height */
for(count = 0; count < 20000; count++)
{
LpsWrk.InitTbl.MachSpecificCfg.DigConfig.DigTargetWt = 80;
lpsUpdateTbl.LiftCylExt.Val = 34;
lpsUpdateTbl.LiftCylExt.Stat = LPS_CYL_EXT_STAT_OK;
ret = LpsUpdt(&lpsUpdateTbl);
LpsWrk.InstWtRaw.Val = 5.0;
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(5.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 9 - Dump detect full rack status set to full rack detected */
for(count = 0; count < 20000; count++)
{
LpsWrk.DumpStateStatus = LPS_WEIGHT_BKT_FULLY_RACKED;
LpsWrk.InstWtRaw.Val = 5.0;
lpsUpdateTbl.LiftCylVel.Val = 40;
lpsUpdateTbl.LiftCylVel.Stat = LPS_CYL_VEL_STATUS_OK;
lpsUpdateTbl.LiftCylExt.Val = 40;
lpsUpdateTbl.LiftCylExt.Stat = LPS_CYL_EXT_STAT_OK;
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(5.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 10 - Dump detect full rack status set to full rack not detected */
for(count = 0; count < 20000; count++)
{
LpsWrk.DumpStateStatus = LPS_WEIGHT_BKT_NOT_RACKED_AND_NOT_DUMPED;
LpsWrk.InitTbl.MachSpecificCfg.DigConfig.DigTargetWt = 80;
LpsWrk.InstWtRaw.Val = 5.0;
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(5.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 11 - Stall detect status set to lift stall stalled */
for(count = 0; count < 20000; count++)
{
LpsWrk.LpsStallDetect.LiftStallStat = LPS_LIFT_STALL_STALLED;
LpsWrk.DumpStateStatus = LPS_WEIGHT_BKT_FULLY_RACKED;
LpsWrk.InstWtRaw.Val = 5.0;
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(5.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 12 - Stall detect status set to lift stall not stalled */
for(count = 0; count < 20000; count++)
{
LpsWrk.LpsStallDetect.LiftStallStat = LPS_LIFT_STALL_NOT_STALLED;
LpsWrk.InstWtRaw.Val = 20.0;

LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(20.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 13 - dig detect status set to dig detected */
for(count = 0; count < 20000; count++)
{
LpsWrk.DigDetectData.DigState = LPS_WEIGHT_BKT_NOT_DIGGING;
LpsWrk.InstWtRaw.Val = 20.0;
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(20.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 14 - dig detect status set to dig not detected */
for(count = 0; count < 20000; count++)
{
LpsWrk.DigDetectData.DigState = LPS_WEIGHT_BKT_DIGGING;
LpsWrk.InstWtRaw.Val = 20.0;
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(20.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 15 - calibration status set to lps calibrated */
for(count = 0; count < 20000; count++)
{
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
LpsWrk.InstWtRaw.Val = 20.0;
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(20.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 16 - calibration status set to lps not calibrated */
for(count = 0; count < 20000; count++)
{
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_UNCALIBRATED;
LpsWrk.InstWtRaw.Val = 20.0;
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(20.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 17 - sensor inputs good */
for(count = 0; count < 20000; count++)
{
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_UNCALIBRATED;
LpsWrk.InstWtRaw.Val = 20.0;
lpsUpdateTbl.HydOilTemp.Val = 50;
lpsUpdateTbl.HydOilTemp.Stat= LPS_HYD_OIL_TEMP_STATUS_OK;
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(20.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 18 - sensor inputs faulted */
for(count = 0; count < 20000; count++)
{
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_UNCALIBRATED;
LpsWrk.InstWtRaw.Val = 16.0;
lpsUpdateTbl.HydOilTemp.Val = 50;
lpsUpdateTbl.HydOilTemp.Stat= LPS_HYD_OIL_TEMP_STATUS_BAD;
ret = LpsUpdt(&lpsUpdateTbl);
LpsLowLiftWeighCalcUpdate();
}
EXPECT_NEAR(20.0, LpsWrk.LowLiftWt.Wt,1);
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_VALID,LpsWrk.LowLiftWt.Stat);

/*case 19 - Resetting the Low lift weight */
for(count = 0; count < 20000; count++)
{
LpsWeighResetLlwWt();
LpsLowLiftWeighCalcUpdate();
}
EXPECT_EQ(LPS_WEIGH_LLW_STATUS_INVALID,LpsWrk.LowLiftWt.Stat);

/*case 20 - Get the lify cylynder weight (code coverage )*/
LpsWrk.LiftCylPres = 12.0;
EXPECT_EQ(LpsGetLiftCylPres(),12.0);
}
