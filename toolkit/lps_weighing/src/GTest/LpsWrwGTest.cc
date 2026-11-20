//test_lps_lib.cc

#include <gtest/gtest.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cpm_filter.h>
#include<LpsGTestUtility.h>
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

#include <math.h>

#define HUNDRED 100.0
#define MINUS_ONE -1
#define ZERO 0
#define TWO_HUNDRED 200
#define FOURTY 40
#define FILTER_DIFF_FAC 1.5


void set_current_pos(float_32 cur_pos,float_32 AppVel);
unsigned_8 PosSimulation(float_32 AppVel,float_32 AppWeight,bucket_mov SwitchSpecificOperation,float_32 precentage,double weigh_inc);



extern LpsInitTbl_t GT_InitTbl;
extern LpsUpdtTbl_t GT_UpdtTbl;

class WrwTest : public LPSTest
{
	
};

void set_current_pos(float_32 cur_pos,float_32 AppVel)
{
	unsigned_32 i = 0;

	float_32 current_pos = 0;

	float_32 pos_inc = AppVel * EXC_RATE_SEC;

	float_32 loop_cnt = cur_pos/EXC_RATE_SEC;

	for(i=0;i<loop_cnt;i++)
	{
		GT_UpdtTbl.LiftCylExt.Val = current_pos;
		GT_UpdtTbl.LiftCylVel.Val = 2;
		LpsWrk.UpdtTbl = &GT_UpdtTbl;
		LpsWeighRangeWeighUpdate();
		current_pos = current_pos + pos_inc;
	}

}
unsigned_8 PosSimulation(float_32 AppVel,float_32 AppWeight,bucket_mov SwitchSpecificOperation,float_32 precentage,double weigh_inc)
{
	      unsigned_32 i = 0;


		if (SwitchSpecificOperation == MOVE_UPWARDS)
		{
			float_32 weigh = AppWeight;
			float_32 current_pos = LpsWrk.UpdtTbl->LiftCylExt.Val;
			LpsWrk.InstWtFilt = weigh ;


				float_32 pos_inc = AppVel * EXC_RATE_SEC;

				float_32 loop_cnt = (precentage/pos_inc);

				for(i=0;i<loop_cnt;i++)
				{
					LpsWrk.InstWtFilt = weigh;
					GT_UpdtTbl.LiftCylExt.Val = current_pos;
					LpsWrk.UpdtTbl = &GT_UpdtTbl;
					LpsWeighRangeWeighUpdate();
					current_pos = current_pos + pos_inc;
					weigh = weigh + weigh_inc;
				}

	       }


		if (SwitchSpecificOperation == MOVE_DOWNWARDS)
		{
			float_32 current_pos = LpsWrk.UpdtTbl->LiftCylExt.Val;
			LpsWrk.InstWtFilt = AppWeight;


				float_32 pos_inc = AppVel * EXC_RATE_SEC;

				float_32 loop_cnt = (precentage/pos_inc);

				for(i=0;i<loop_cnt;i++)
				{
					GT_UpdtTbl.LiftCylExt.Val = current_pos;
					LpsWrk.UpdtTbl = &GT_UpdtTbl;
					LpsWeighRangeWeighUpdate();
					current_pos = current_pos - pos_inc;
				}

		 }
	
	return 1;

}


TEST_F(WrwTest,WRW_CAL_WEIGH_RANGE_POSITION)
{
	LpsInitErrorTypes_t IntRst;
	int result;
	float DumpWtBuf;

	result =  setDefaultValues("calibrationData.csv", "machineSpecData.csv", "rawInputData.csv");
	EXPECT_EQ(result, 0);
	
	GT_InitTbl.InstallStat 						  = TRUE;
	GT_InitTbl.ExecRate                           = EXC_RATE_SEC;
	GT_InitTbl.DumpWtBuffer.PtrDumpWtBuffer       = &DumpWtBuf;
	GT_InitTbl.DumpWtBuffer.bufferSize            = sizeof(DumpWtBuf);
	GT_InitTbl.MachSpecificCfg.CalibTbl.CalStat   = LPS_WEIGH_SYSTEM_CALIBRATED;
	GT_InitTbl.MachSpecificCfg.CalibTbl.TopOfLift = 1;
	GT_InitTbl.MachSpecificCfg.StartOfWeigh       = 50;
	GT_InitTbl.MachSpecificCfg.EndOfWeigh         = 65;
	GT_InitTbl.MachSpecificCfg.NoOfLiftCyls 	  = 2;
	GT_InitTbl.MachSpecificCfg.LiftCylBoreDia 	  = 1;
	GT_InitTbl.MachSpecificCfg.LiftCylRodDia 	  = 1;
	GT_InitTbl.MachSpecificCfg.DumpConfig.FullDumpBktAngleThreshold = -35;
	GT_InitTbl.MachSpecificCfg.DumpConfig.PartDumpBktAngleThreshold = 40;
	GT_InitTbl.MachSpecificCfg.DumpConfig.FullRackBktAngleThreshold = 35; 
	GT_InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold		= 90;
	GT_UpdtTbl.BktAngle.Val                       = 41;
	GT_UpdtTbl.LiftCylHePres.Stat                 = LPS_PRES_STATUS_OK;
    GT_UpdtTbl.LiftCylRePres.Stat                 = LPS_PRES_STATUS_OK;
    GT_UpdtTbl.HydOilTemp.Stat                    = LPS_HYD_OIL_TEMP_STATUS_OK;
    GT_UpdtTbl.LiftCylVel.Stat                    = LPS_CYL_VEL_STATUS_OK;
    GT_UpdtTbl.LiftCylExt.Stat                    = LPS_CYL_EXT_STAT_OK;
    GT_UpdtTbl.TiltCylExt.Stat                    = LPS_CYL_EXT_STAT_OK;
	GT_UpdtTbl.BktAngle.Stat                      = LPS_BKT_ANGLE_STATUS_OK;
	
    IntRst = LpsInit(&GT_InitTbl);
    EXPECT_EQ(IntRst, LPS_INIT_SUCCESS);

    LpsWrk.UpdtTbl = &GT_UpdtTbl;
	LpsWrk.InstWtFilt = 10.0;

    LpsWeighResetWeighRangeWeight();
    set_current_pos(10,1.05);
	
    //case 1

    LpsWeighResetWeighRangeWeight();
	
	LpsWrk.UpdtTbl->LiftCylVel.Val = 1.05;

    set_current_pos(10,1.05);

    EXPECT_EQ(LPS_BELOW_WEIGH_RANGE, LpsWrk.WrwTbl.OpTbl.Indicator);

    EXPECT_EQ(FALSE,LpsWrk.WrwTbl.WkTbl.Weighing);

    //case 2
    LpsWeighResetWeighRangeWeight();
	
	LpsWrk.UpdtTbl->LiftCylVel.Val = 1.05;

    PosSimulation(1.05,10.000000,MOVE_UPWARDS,45,0);
	
	EXPECT_EQ(LPS_IN_WEIGH_RANGE_WEIGHING, LpsWrk.WrwTbl.OpTbl.Indicator);
    EXPECT_EQ(TRUE,LpsWrk.WrwTbl.WkTbl.Weighing);

    //case 3

    LpsWeighResetWeighRangeWeight();
	
	LpsWrk.UpdtTbl->LiftCylVel.Val = 1.05;

    PosSimulation(1.05,10.000000,MOVE_UPWARDS,30,0);

    EXPECT_EQ(LPS_ABOVE_WEIGH_RANGE, LpsWrk.WrwTbl.OpTbl.Indicator);
    EXPECT_EQ(FALSE,LpsWrk.WrwTbl.WkTbl.Weighing);

    //case 4

    LpsWeighResetWeighRangeWeight();
	
	LpsWrk.UpdtTbl->LiftCylVel.Val = 1.05;

    PosSimulation(1.05,10.000000,MOVE_DOWNWARDS,30,0);

    EXPECT_EQ(LPS_IN_WEIGH_RANGE_NOT_WEIGHING, LpsWrk.WrwTbl.OpTbl.Indicator);
    EXPECT_EQ(FALSE,LpsWrk.WrwTbl.WkTbl.Weighing);

    //case 5

    LpsWeighResetWeighRangeWeight();
	
	LpsWrk.UpdtTbl->LiftCylVel.Val = 1.05;

    PosSimulation(1.05,10.000000,MOVE_DOWNWARDS,45,0);

    EXPECT_EQ(LPS_BELOW_WEIGH_RANGE, LpsWrk.WrwTbl.OpTbl.Indicator);
    EXPECT_EQ(FALSE,LpsWrk.WrwTbl.WkTbl.Weighing);

    //case 6

    LpsWeighResetWeighRangeWeight();

    LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_UNCALIBRATED;
	
	LpsWrk.UpdtTbl->LiftCylVel.Val = 1.05;

    PosSimulation(1.05,10.000000,MOVE_UPWARDS,50,0);

    EXPECT_EQ(LPS_IN_WEIGH_RANGE_NOT_WEIGHING, LpsWrk.WrwTbl.OpTbl.Indicator);
    EXPECT_EQ(FALSE,LpsWrk.WrwTbl.WkTbl.Weighing);
}


TEST_F(WrwTest,WRW_CAL_WEIGH_RANGE_AVG_CALCULATION)
{

	LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;

	LpsWeighResetWeighRangeWeight();
	
	LpsWrk.UpdtTbl->LiftCylVel.Val = 1.05;

	PosSimulation(1.05,10.000000,MOVE_DOWNWARDS,45,0);
	
	int i = 0;
	for (i = 0;i < 1000;i++)
	{
		LpsWeighRangeWeighUpdate();
	}
	PosSimulation(1.05,10.000000,MOVE_UPWARDS,50,0);
		
    EXPECT_NEAR(10,LpsWrk.WrwTbl.OpTbl.Wt,0.1);

    EXPECT_EQ(LPS_WEIGH_WRW_STATUS_VALID,LpsWrk.WrwTbl.OpTbl.Status);

    EXPECT_EQ(LPS_WEIGH_NO_WARNING_ACTIVE,LpsWrk.WrwTbl.OpTbl.Warning);

	//Case 2

    LpsWeighResetWeighRangeWeight();

    PosSimulation(1.05,10.000000,MOVE_DOWNWARDS,58,0.00000);
	
	for (i = 0;i < 1000;i++)
		LpsWeighRangeWeighUpdate();

    PosSimulation(1.05,10.000000,MOVE_UPWARDS,58,0.000009);

    EXPECT_NEAR(10,LpsWrk.WrwTbl.OpTbl.Wt,0.1);

    EXPECT_EQ(LPS_WEIGH_WRW_STATUS_VALID,LpsWrk.WrwTbl.OpTbl.Status);

    EXPECT_EQ(LPS_WEIGH_NO_WARNING_ACTIVE,LpsWrk.WrwTbl.OpTbl.Warning);
	
	//Case 3

	LpsWeighResetWeighRangeWeight();
	
	PosSimulation(1.05,10.000000,MOVE_DOWNWARDS,58,0.00000);
	
	PosSimulation(1.05,10.000000,MOVE_UPWARDS,42,0.000000);
	
	PosSimulation(1.05,10.000000,MOVE_UPWARDS,16,0.0002);
	
    EXPECT_NEAR(10,LpsWrk.WrwTbl.OpTbl.Wt,0.1);

    EXPECT_EQ(LPS_WEIGH_WRW_STATUS_VALID,LpsWrk.WrwTbl.OpTbl.Status);

    EXPECT_EQ(LPS_WEIGH_NO_WARNING_ACTIVE,LpsWrk.WrwTbl.OpTbl.Warning);
}

TEST_F(WrwTest,WRW_CAL_WARNINGS_REWEIGH)
{
	LpsWeighWrwReweighStatus_t local;
	PayloadDumpStateInit();
	LpsWeighResetWeighRangeWeight();
	
	unsigned_32 i = 0;
	
	for (i = 0;i < 1000;i++)
	{
		LpsWeighRangeWeighUpdate();
	}
	
	int checker;
	
	//Case 1
	LpsWrk.UpdtTbl->LiftCylVel.Val = 1.05;
	
	PosSimulation(1.05,10.000000,MOVE_DOWNWARDS,40,0.00000);
	
	PosSimulation(1.05,10.0,MOVE_UPWARDS,38,0.0);
	
	PosSimulation(1.05,10.000000,MOVE_UPWARDS,20,0.09);
	
	EXPECT_NEAR(10,LpsWrk.WrwTbl.OpTbl.Wt,1);

    EXPECT_EQ(LPS_WEIGH_WRW_STATUS_VALID,LpsWrk.WrwTbl.OpTbl.Status);

    EXPECT_EQ(LPS_WEIGH_WARNING_ACTIVE,LpsWrk.WrwTbl.OpTbl.Warning);
	
	checker = LpsWrk.WrwTbl.ReweighWarn.RateOfChangeHi;
	
	EXPECT_EQ(TRUE,checker);
	
	//Case 2
	
	PosSimulation(1.05,10.000000,MOVE_DOWNWARDS,50,0.00000);
	
	LpsWeighResetWeighRangeWeight();
	
	for (i = 0;i < 1000;i++)
	{
		LpsWeighRangeWeighUpdate();
	}
	
	PosSimulation(1.05,10.0,MOVE_UPWARDS,31,0.0);
	
	PosSimulation(1.05,10.000000,MOVE_UPWARDS,15,0.2);
	
    EXPECT_NEAR(10,LpsWrk.WrwTbl.OpTbl.Wt,1);

    EXPECT_EQ(LPS_WEIGH_WRW_STATUS_VALID,LpsWrk.WrwTbl.OpTbl.Status);

    EXPECT_EQ(LPS_WEIGH_WARNING_ACTIVE,LpsWrk.WrwTbl.OpTbl.Warning);
	
	EXPECT_EQ(TRUE,checker);
	
	//Case 3
	
	LpsWeighResetWeighRangeWeight();
	LpsWrk.WrwTbl.WkTbl.ReweighPosted = FALSE;
	
	for (i = 0;i < 1000;i++)
	{
		LpsWeighRangeWeighUpdate();
	}
	
	PosSimulation(1.05,10.000000,MOVE_DOWNWARDS,50,0.00000);
	
	LpsWrk.UpdtTbl->LiftCylVel.Val = 1.15;
	
	PosSimulation(1.2,10.0,MOVE_UPWARDS,35,0.00001);
	
	LpsWrk.UpdtTbl->LiftCylVel.Val = 1.05;
	
	PosSimulation(1.05,10.000000,MOVE_UPWARDS,20,1.8);
		
    EXPECT_NEAR(10,LpsWrk.WrwTbl.OpTbl.Wt,3.7);

    EXPECT_EQ(LPS_WEIGH_WRW_STATUS_VALID,LpsWrk.WrwTbl.OpTbl.Status);

    EXPECT_EQ(LPS_WEIGH_WARNING_ACTIVE,LpsWrk.WrwTbl.OpTbl.Warning);
	
	checker = LpsWrk.WrwTbl.ReweighWarn.Inconsistent;
	
	EXPECT_EQ(TRUE,checker);
	
	//Case 4
	LpsWeighDumpDetectUpdate();
	PosSimulation(1.05,10.000000,MOVE_DOWNWARDS,50,0.00000);
	LpsWrk.WrwTbl.WkTbl.ReweighPosted = FALSE;
	LpsWeighResetWeighRangeWeight();
	
	for (i = 0;i < 1000;i++)
	{
		LpsWeighRangeWeighUpdate();
	}
	
	LpsWrk.UpdtTbl->LiftCylVel.Val = 2.5;
	
	PosSimulation(3.5,10.0,MOVE_UPWARDS,20,0.0);
	
	LpsWrk.UpdtTbl->LiftCylVel.Val = 3.9;
	
	PosSimulation(3.7,10.0,MOVE_UPWARDS,30,0.0);
	
	EXPECT_NEAR(10,LpsWrk.WrwTbl.OpTbl.Wt,3.1);

    EXPECT_EQ(LPS_WEIGH_WRW_STATUS_VALID,LpsWrk.WrwTbl.OpTbl.Status);

    //EXPECT_EQ(LPS_WEIGH_WARNING_ACTIVE,LpsWrk.WrwTbl.OpTbl.Warning);
	
	//checker = LpsWrk.WrwTbl.ReweighWarn.Jerky;
	
	//EXPECT_EQ(TRUE,checker);
	//printf("\n Weighing  %d \n",LpsWrk.WrwTbl.WkTbl.Weighing);
	//printf("Current LiftCylVel %f\n",LpsWrk.UpdtTbl->LiftCylVel.Val);
	//printf("Current LiftCylExt %f\n",LpsWrk.UpdtTbl->LiftCylExt.Val);	
	//printf("Standard Deviation %f\n",LpsWrk.WrwTbl.WkTbl.WtSd);
	//printf("Weight Average %f\n",LpsWrk.WrwTbl.WkTbl.WtAvg);
	//Case 5
		
	LpsWrk.UpdtTbl->LiftCylVel.Val = 1.5;
	LpsWeighDumpDetectUpdate();
    PosSimulation(1.05,10.000000,MOVE_DOWNWARDS,50,0.00000);
	LpsWeighResetWeighRangeWeight();
	
	for (i = 0;i < 1000;i++)
	{
		LpsWeighRangeWeighUpdate();
	}
	
	LpsWrk.UpdtTbl->LiftCylVel.Val = 1.5;
	PosSimulation(1.05,10.0,MOVE_UPWARDS,30,0.0);
	LpsWrk.UpdtTbl->LiftCylVel.Val = 0.99;
	PosSimulation(0.7,10.0,MOVE_UPWARDS,20,0.0);
	
	EXPECT_NEAR(10,LpsWrk.WrwTbl.OpTbl.Wt,3.1);

    EXPECT_EQ(LPS_WEIGH_WRW_STATUS_VALID,LpsWrk.WrwTbl.OpTbl.Status);

    EXPECT_EQ(LPS_WEIGH_WARNING_ACTIVE,LpsWrk.WrwTbl.OpTbl.Warning);
	
	local = LpsGetWrwReweighWarning();
	checker = local.Stopped;
	
	EXPECT_EQ(TRUE,checker);

    //Case 6
	
	LpsWrk.UpdtTbl->LiftCylVel.Val = 1.5;
	LpsWrk.UpdtTbl->BktAngle.Val   = 30;
	LpsWrk.UpdtTbl->TiltCylExt.Val = 41;
	LpsWrk.WrwTbl.WkTbl.ReweighPosted = FALSE;
	
	LpsWeighDumpDetectUpdate();
	PosSimulation(1.05,10.000000,MOVE_DOWNWARDS,37,0.00000);
	LpsWeighResetWeighRangeWeight();
	PosSimulation(1.05,10.0,MOVE_UPWARDS,5.3,0.0);
	
    LpsWrk.UpdtTbl->LiftCylVel.Val = 1.5;
	
	for (i = 0;i < 32667;i++)
	{
		LpsWeighRangeWeighUpdate();
	}
	local = LpsGetWrwReweighWarning();
	checker = local.TooSlow;
	
	EXPECT_EQ(TRUE,checker);
	PosSimulation(0.02,10.0,MOVE_UPWARDS,20,0.0);
	
	EXPECT_NEAR(10,LpsGetWeighRangeWeight(),1.1);

    EXPECT_EQ(LPS_WEIGH_WRW_STATUS_VALID,LpsWrk.WrwTbl.OpTbl.Status);

    EXPECT_EQ(LPS_WEIGH_WARNING_ACTIVE,LpsWrk.WrwTbl.OpTbl.Warning);
   
    //Case 7

	LpsWrk.UpdtTbl->BktAngle.Val   = 30;
	LpsWrk.UpdtTbl->TiltCylExt.Val = 41;
	LpsWrk.UpdtTbl->LiftCylVel.Val = 1.05;
	LpsWrk.WrwTbl.WkTbl.ReweighPosted = FALSE;
	
	PosSimulation(1.05,10.000000,MOVE_DOWNWARDS,40,0.00000);
	LpsWeighResetWeighRangeWeight();
	LpsWeighDumpDetectUpdate();
	LpsWeighRangeWeighUpdate();
	PosSimulation(1.05,10.0,MOVE_UPWARDS,25,0.0);
	
    local = LpsGetWrwReweighWarning();
	
	checker = local.NotRacked;
	
	EXPECT_EQ(TRUE,checker);
    
	PosSimulation(1.05,10.0,MOVE_UPWARDS,30,0.0);
	
	EXPECT_NEAR(10,LpsGetWeighRangeWeight(),1.1);

    EXPECT_EQ(LPS_WEIGH_WRW_STATUS_VALID,LpsWrk.WrwTbl.OpTbl.Status);

    EXPECT_EQ(LPS_WEIGH_WARNING_ACTIVE,LpsWrk.WrwTbl.OpTbl.Warning);
    
    //Case 8
     LpsWrk.WrwTbl.WkTbl.FullyRackedStat = TRUE;

	LpsWrk.UpdtTbl->LiftCylVel.Val = 1.05;
	
	PosSimulation(1.05,10.000000,MOVE_DOWNWARDS,25,0.00000);
	
    LpsWeighResetWeighRangeWeight();

	for (i = 0;i < 1000;i++)
	{
		LpsWeighRangeWeighUpdate();
	}

    LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_UNCALIBRATED;

    PosSimulation(1.05,10.000000,MOVE_UPWARDS,30,0.00000);

    EXPECT_NEAR(0,LpsGetWeighRangeWeight(),0);

    EXPECT_EQ(LPS_WEIGH_WRW_STATUS_INVALID,LpsWrk.WrwTbl.OpTbl.Status);

    //Case 9
    LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;

    PosSimulation(1.05,10.000000,MOVE_DOWNWARDS,30,0.00000);

    LpsWeighResetWeighRangeWeight();

	for (i = 0;i < 1000;i++)
	{
		LpsWeighRangeWeighUpdate();
	}

    PosSimulation(1.05,10.000000,MOVE_UPWARDS,15,0.00000);

    PosSimulation(1.05,10.000000,MOVE_DOWNWARDS,15,0.00000);

    EXPECT_NEAR(0,LpsGetWeighRangeWeight(),0);

    EXPECT_EQ(LPS_WEIGH_WRW_STATUS_INVALID,LpsWrk.WrwTbl.OpTbl.Status);

    //Case 10
    LpsWeighResetWeighRangeWeight();

    LpsWrk.UpdtTbl->LiftCylVel.Val = 1.05;

    LpsWrk.WrwTbl.WkTbl.NotFullyDumpedStat = FALSE;

    PosSimulation(1.05,10.000000,MOVE_UPWARDS,40,0.00000);

    EXPECT_NEAR(0,LpsGetWeighRangeWeight(),0);

    EXPECT_EQ(LPS_WEIGH_WRW_STATUS_INVALID,LpsWrk.WrwTbl.OpTbl.Status);
	
    //Case 11 /*code coverage 
    LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalAdjust= 1;
    EXPECT_EQ(LpsCalAdjustWeight(0),0.0);
}
