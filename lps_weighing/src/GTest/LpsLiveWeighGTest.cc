//test_lps_lib.cc
#include <gtest/gtest.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <LpsCommonTypeDef.h> /* Contains type definitions of standard datatypes */
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
					   


LpsMachSpecificCfg_t cfg1;
LpsCalib_t cal1;
LpsInitTbl_t tbl1;
LpsUpdtTbl_t lpsUpdateTbl1;
		   
//////////////////////////////////////////////////////////////////////////////////
//LOW LIFT WEIGHT CALCULATION
TEST(LPSLivewtTest, LPSLivewtFunctional)
{
	int i;
	
	lpsUpdateTbl1.LiftCylHePres.Val = 6000;
	lpsUpdateTbl1.LiftCylHePres.Stat =LPS_PRES_STATUS_OK;

	lpsUpdateTbl1.LiftCylRePres.Val = 3000;
	lpsUpdateTbl1.LiftCylRePres.Stat =LPS_PRES_STATUS_OK;

	lpsUpdateTbl1.LiftCylExt.Val = 40;
	lpsUpdateTbl1.LiftCylExt.Stat = LPS_CYL_EXT_STAT_OK;

	lpsUpdateTbl1.LiftCylVel.Val = 40;
	lpsUpdateTbl1.LiftCylVel.Stat = LPS_CYL_VEL_STATUS_OK;

	lpsUpdateTbl1.HydOilTemp.Val = 50;
	lpsUpdateTbl1.HydOilTemp.Stat= LPS_HYD_OIL_TEMP_STATUS_OK;

	//machine specific config
	cfg1.NoOfLiftCyls = 2;
	cfg1.LiftCylBoreDia = 140;
	cfg1.LiftCylRodDia = 85;
	cfg1.HydOilType = LPS_OIL_TYPE_SAE_10W;
	cal1.CalAdjust = 1.0;
	cal1.ZeroWeight = 0.0;
	cal1.TopOfLift = 1;
	//calibration status
	cfg1.CalibTbl = cal1;

	cfg1.LlwTbl.FilterFactorMean = 0.927407213;
	cfg1.LlwTbl.FilterFactorVariance = 0.927407213;
	cfg1.LlwTbl.ErrorBand = 1;
	cfg1.LlwTbl.MinimumConfidenceTime = 1.25;
	cfg1.LlwTbl.AutoWeighRangeConfThr = 0.997;
	cfg1.LlwTbl.AutoWeighMinLiftHt = 30;
	cfg1.LlwTbl.WtCf = 10;
	cfg1.LlwTbl.StageOneCf = 10;
	cfg1.LlwTbl.StageTwoCf = 10;
	cfg1.LlwTbl.StageThreeCf = 10;
	cfg1.LlwTbl.DampingRate = 1;
	cfg1.LiveWeighConfig.SlowFiltWtCf   = 3.5;
	cfg1.LiveWeighConfig.FastFiltWtCf   = 1.0;

	//init table
	tbl1.InstallStat = 1;
	tbl1.ExecRate = 0.02;
	tbl1.MachSpecificCfg = cfg1;

	lpsUpdateTbl1.UseFastFilter = TRUE;
	
	LpsCalib_t* pCalTbl = &LpsWrk.InitTbl.MachSpecificCfg.CalibTbl;	
	LpsWrk.UpdtTbl = &lpsUpdateTbl1;
	LpsWrk.InitTbl = tbl1;

	LpsWrk.InstWtRaw.Val = 10.0;	

	//Test Case 1

	LpsLlwInit();
	LpsLiveWeighInit();
	LpsWrk.UpdtTbl->UseFastFilter = TRUE;
	for (i = 0;i < 1000;i++)
	{
		LpsLowLiftWeighCalcUpdate();
		LpsLiveWeighCalc();
	}	
	EXPECT_NEAR(10,LpsWrk.LiveWeighTbl.Wt,0.1);
	
	//Test Case 2
	LpsWrk.UpdtTbl->UseFastFilter = FALSE;
	
	for (i = 0;i < 1000;i++)
	{
		LpsLowLiftWeighCalcUpdate();
		LpsLiveWeighCalc();
	}

	EXPECT_NEAR(10,LpsWrk.LiveWeighTbl.Wt,0.1);
	LpsWeighResetLiveWt();

	//Test Case 3
	LpsWrk.UpdtTbl->UseFastFilter = FALSE;
	pCalTbl->ZeroWeight = 5;
	
	for (i = 0;i < 1000;i++)
	{
		LpsLowLiftWeighCalcUpdate();
		LpsLiveWeighCalc();
	}

	EXPECT_NEAR(5,LpsWrk.LiveWeighTbl.Wt,0.1);
	LpsWeighResetLiveWt();

	//Test Case 4
	LpsWrk.UpdtTbl->UseFastFilter = FALSE;
	pCalTbl->ZeroWeight = 20;
	
	for (i = 0;i < 1000;i++)
	{
		LpsLowLiftWeighCalcUpdate();
		LpsLiveWeighCalc();
	}

	EXPECT_NEAR(-10,LpsWrk.LiveWeighTbl.Wt,0.1);
	LpsWeighResetLiveWt();

	//Test Case 5
	LpsWrk.UpdtTbl->UseFastFilter = FALSE;
	pCalTbl->ZeroWeight = 5;
	LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalAdjust = 0.7;
	
	for (i = 0;i < 1000;i++)
	{
		LpsLowLiftWeighCalcUpdate();
		LpsLiveWeighCalc();
	}

	EXPECT_NEAR(1.5,LpsWrk.LiveWeighTbl.Wt,0.1);
	LpsWeighResetLiveWt();

	//Test Case 6
	LpsWrk.UpdtTbl->UseFastFilter = FALSE;
	pCalTbl->ZeroWeight = 5;
	LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalAdjust = 2;
	
	for (i = 0;i < 1000;i++)
	{
		LpsLowLiftWeighCalcUpdate();
		LpsLiveWeighCalc();
	}

	EXPECT_NEAR(5,LpsWrk.LiveWeighTbl.Wt,0.1);
	LpsWeighResetLiveWt();
	
	//Test Case 7
	LpsWrk.UpdtTbl->UseFastFilter = TRUE;
	pCalTbl->ZeroWeight = 5;
	LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalAdjust = 2;
	
	for (i = 0;i < 1000;i++)
	{
		LpsLowLiftWeighCalcUpdate();
		LpsLiveWeighCalc();
	}
	LpsWrk.UpdtTbl->UseFastFilter = FALSE;
	LpsLowLiftWeighCalcUpdate();
	LpsLiveWeighCalc();
	EXPECT_NEAR(-5,LpsWrk.LiveWeighTbl.Wt,0.1);
	LpsWeighResetLiveWt();
}
