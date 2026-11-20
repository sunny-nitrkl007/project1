#include <gtest/gtest.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef __LPS_COMMON_TYPE_DEF_H__
#include <LPSCommonTypeDef.h> /* Contains type definitions of standard datatypes */
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCommonStructures.h> /* Contains structures which are common between all LPS
                                  * system libraries
                  */
#endif

#ifndef  __LPS_COMMON_LOOKUP_TBL_UTILITY_H__
#include <LpsCommonLookUpTblUtility.h>
#endif

#ifndef __LPS_PUBLIC_H__
#include <LpsPublic.h> /*******************************************************/
                       /* Containes prototypes of interfaces and functions    */
                       /* which are exported to the application using the     */
                       /* library                                             */
                       /*******************************************************/
#endif

#ifndef __LPS_PRIVATE_H__
#include <LpsPrivate.h> /*******************************************************/
                        /* Containes prototypes of interfaces and functions    */
                        /* which are used within the payload computation       */
                        /* library                                             */
                        /*******************************************************/
#endif


LpsUpdtTbl_t Exe;
LpsZeroErrorTypes_t ZAStatus;
LpsZeroErrorTypes_t AZUStat;
LpsWeighBestBktWt_t BktWt;
LpsUpdtErrorTypes_t UpdateError;

//Time difference calculation - Need to be removed when the actual function is created
/*unsigned_32 LpsCommonGetTimeDiffSec(unsigned a, unsigned b)
{
    unsigned_32 diff = a - b;
    return diff;	
}*/

//////////////////////////////////////////////////////////////////////////////////
//                          ZERO FUNCTION TEST CASES                            //
//////////////////////////////////////////////////////////////////////////////////
TEST(LpsZeroAdjTest, LpsZeroAdjFunctional)
{

LpsWrk.UpdtTbl = &Exe;

//Machine specific config
LpsWrk.InitTbl.MachSpecificCfg.ZeroBktWtAccuracyLimit = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_LOW;
LpsWrk.InitTbl.MachSpecificCfg.ZeroRangeLimit = 40;
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.Calwt = 1;

                                /*Test Case 1*/
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_UNCALIBRATED;	
LpsWeighZeroAdjust();
ZAStatus = LpsWeighGetZeroAdjStatus();
EXPECT_EQ(ZAStatus, LPS_ZERO_UPDATE_NOT_CALIBRATED);

                               /* Test Case 2 */
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
LpsWrk.BestBktWt.PayloadCalcMeth = (LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE<<8);
LpsWeighZeroAdjust();
ZAStatus = LpsWeighGetZeroAdjStatus();
EXPECT_EQ(ZAStatus, LPS_ZERO_UPDATE_BUCKET_WT_NOT_ACCURATE);

                              /* Test Case 3 */
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
LpsWrk.BestBktWt.PayloadCalcMeth = (LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_MED<<8);
LpsWrk.WrwTbl.WkTbl.WtAvg = 50;
LpsWeighZeroAdjust();
ZAStatus = LpsWeighGetZeroAdjStatus();
EXPECT_EQ(ZAStatus, LPS_ZERO_UPDATE_TOO_HEAVY_TO_ZERO);

                             /* Test Case 4 */
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
LpsWrk.BestBktWt.PayloadCalcMeth = (LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_HIGH<<8);
LpsWrk.WrwTbl.WkTbl.WtAvg = 10;
Exe.HydOilTemp.Stat = LPS_HYD_OIL_TEMP_STATUS_OK;
Exe.HydOilTemp.Val = 40;
LpsWeighZeroAdjust();
ZAStatus = LpsWeighGetZeroAdjStatus();
EXPECT_EQ(ZAStatus, LPS_ZERO_UPDATE_SUCCESS);
				
                            /* Test Case 5 */
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_UNCALIBRATED;
LpsWeighAutoZeroUpdate();
AZUStat = LpsWeighGetAutoZeroUpdateStatus();
EXPECT_EQ(AZUStat, LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED); // check this once ?????

                            /* Test Case 6 */
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
LpsWrk.WrwTbl.WkTbl.Weighing = TRUE;
LpsWeighAutoZeroUpdate();
AZUStat = LpsWeighGetAutoZeroUpdateStatus();
EXPECT_EQ(AZUStat, LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED);

                           /* Test Case 7 */
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
LpsWrk.WrwTbl.WkTbl.Weighing = FALSE;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.Snoozed = TRUE;
Exe.PassCount = 0;
Exe.ClockKeyonSec = 1500;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.LastSnoozedTime = 700;
LpsWeighAutoZeroUpdate();
AZUStat = LpsWeighGetAutoZeroUpdateStatus();
EXPECT_EQ(AZUStat, LPS_ZERO_UPDATE_TIMER_EXPIRED_ZERO_REQUIRED);

                           /* Test Case 8 */
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
LpsWrk.WrwTbl.WkTbl.Weighing = FALSE;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.Snoozed = FALSE;
Exe.PassCount = 0;
LpsWrk.ZeroAdjTbl.ZeroTemp = 80;
Exe.HydOilTemp.Val = 40;
Exe.HydOilTemp.Stat = LPS_HYD_OIL_TEMP_STATUS_OK;
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.EmptyTemp = 50;
LpsWrk.InitTbl.MachSpecificCfg.ZeroAdjOilTempWarnThreshold = 40;
LpsWeighAutoZeroUpdate();
AZUStat = LpsWeighGetAutoZeroUpdateStatus();
EXPECT_EQ(AZUStat, LPS_ZERO_UPDATE_TEMPERATURE_CHANGE_ZERO_REQUIRED);

                            /* Test Case 9 */
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
LpsWrk.WrwTbl.WkTbl.Weighing = FALSE;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.Snoozed = FALSE;
Exe.PassCount = 0;
LpsWrk.ZeroAdjTbl.ZeroTemp = 80;
Exe.HydOilTemp.Val = 40;
Exe.HydOilTemp.Stat = LPS_HYD_OIL_TEMP_STATUS_BAD;
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.EmptyTemp = 50;
LpsWrk.InitTbl.MachSpecificCfg.ZeroAdjOilTempWarnThreshold = 40;
LpsWeighAutoZeroUpdate();
AZUStat = LpsWeighGetAutoZeroUpdateStatus();
EXPECT_EQ(AZUStat, LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED);

                           /* Test Case 10 */
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
LpsWrk.WrwTbl.WkTbl.Weighing = FALSE;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.Snoozed = FALSE;
Exe.PassCount = 0;
Exe.HydOilTemp.Stat = LPS_HYD_OIL_TEMP_STATUS_BAD;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.LiftStatus = TRUE;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.PwrOn = TRUE;
LpsWrk.InitTbl.MachSpecificCfg.ZeroAdjInitTimeInterval = 300;
Exe.ClockKeyonSec = 900;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.LastSnoozedTime = 300;
LpsWeighAutoZeroUpdate();
AZUStat = LpsWeighGetAutoZeroUpdateStatus();
EXPECT_EQ(AZUStat, LPS_ZERO_UPDATE_TIMER_EXPIRED_ZERO_REQUIRED);

                           /* Test Case 11 */
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
LpsWrk.WrwTbl.WkTbl.Weighing = FALSE;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.Snoozed = FALSE;
Exe.PassCount = 0;
Exe.HydOilTemp.Stat = LPS_HYD_OIL_TEMP_STATUS_BAD;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.LiftStatus = TRUE;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.PwrOn = FALSE;
LpsWrk.InitTbl.MachSpecificCfg.ZeroAdjInitTimeInterval = 300;
Exe.ClockKeyonSec = 900;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.LastSnoozedTime = 300;
LpsWeighAutoZeroUpdate();
AZUStat = LpsWeighGetAutoZeroUpdateStatus();
EXPECT_EQ(AZUStat, LPS_ZERO_UPDATE_TIMER_EXPIRED_ZERO_REQUIRED);

                            /* Test Case 12 */
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
LpsWrk.WrwTbl.WkTbl.Weighing = FALSE;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.Snoozed = FALSE;
Exe.PassCount = 0;
LpsWrk.ZeroAdjTbl.ZeroTemp = -100;
Exe.HydOilTemp.Val = 40;
Exe.HydOilTemp.Stat = LPS_HYD_OIL_TEMP_STATUS_OK;
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.EmptyTemp = 50;
LpsWrk.InitTbl.MachSpecificCfg.ZeroAdjOilTempWarnThreshold = 40;
LpsWeighAutoZeroUpdate();
AZUStat = LpsWeighGetAutoZeroUpdateStatus();
EXPECT_EQ(AZUStat, LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED);

                           /* Test Case 13 */
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
LpsWrk.WrwTbl.WkTbl.Weighing = FALSE;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.Snoozed = FALSE;
Exe.PassCount = 0;
LpsWrk.ZeroAdjTbl.ZeroTemp = 80;
Exe.HydOilTemp.Val = 70;
Exe.HydOilTemp.Stat = LPS_HYD_OIL_TEMP_STATUS_OK;
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.EmptyTemp = 50;
LpsWrk.InitTbl.MachSpecificCfg.ZeroAdjOilTempWarnThreshold = 40;
LpsWeighAutoZeroUpdate();
AZUStat = LpsWeighGetAutoZeroUpdateStatus();
EXPECT_EQ(AZUStat, LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED);

                          /* Test Case 14 */
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
LpsWrk.WrwTbl.WkTbl.Weighing = FALSE;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.Snoozed = FALSE;
Exe.PassCount = 0;
LpsWrk.ZeroAdjTbl.ZeroTemp = 80;
Exe.HydOilTemp.Val = 60;
Exe.HydOilTemp.Stat = LPS_HYD_OIL_TEMP_STATUS_OK;
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.EmptyTemp = 50;
LpsWrk.InitTbl.MachSpecificCfg.ZeroAdjOilTempWarnThreshold = 40;
LpsWeighAutoZeroUpdate();
AZUStat = LpsWeighGetAutoZeroUpdateStatus();
EXPECT_EQ(AZUStat, LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED);

                         /* Test Case 15 */
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
LpsWrk.WrwTbl.WkTbl.Weighing = FALSE;
LpsWrk.ZeroAdjTbl.ZeroAdjAutoSnooze.Snoozed = FALSE;
Exe.PassCount = 0;
LpsWrk.ZeroAdjTbl.ZeroTemp = 80;
Exe.HydOilTemp.Val = 90;
Exe.HydOilTemp.Stat = LPS_HYD_OIL_TEMP_STATUS_OK;
LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.EmptyTemp = 50;
LpsWrk.InitTbl.MachSpecificCfg.ZeroAdjOilTempWarnThreshold = 40;
LpsWeighAutoZeroUpdate();
AZUStat = LpsWeighGetAutoZeroUpdateStatus();
EXPECT_EQ(AZUStat, LPS_ZERO_UPDATE_ZERO_NOT_REQUIRED);

                         /* Test Case 16 */
Exe.LiftCylHePres.Val = 6000;
Exe.LiftCylHePres.Stat =LPS_PRES_STATUS_OK;
Exe.LiftCylRePres.Val = 3000;
Exe.LiftCylRePres.Stat =LPS_PRES_STATUS_OK;
Exe.LiftCylExt.Val = 40;
Exe.LiftCylExt.Stat = LPS_CYL_EXT_STAT_OK;
Exe.LiftCylVel.Val = 40;
Exe.LiftCylVel.Stat = LPS_CYL_VEL_STATUS_OK;
Exe.HydOilTemp.Val = 50;
Exe.HydOilTemp.Stat= LPS_HYD_OIL_TEMP_STATUS_OK;
Exe.ClockKeyonSec = 234;
Exe.PassCount = 5;
Exe.ZeroButtonPress = TRUE;

LpsWrk.InitErr = LPS_INIT_SUCCESS;
UpdateError = LpsUpdt(&Exe);
EXPECT_EQ(UpdateError, LPS_UPDT_SUCCESS);
 
}
