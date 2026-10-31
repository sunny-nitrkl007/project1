#include <gtest/gtest.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
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

LpsWeighBestBktWt_t result;

/* Uncalibrated test cases */
TEST(LpsWeighBestBktWt, Uncalibrated)
{
	LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_UNCALIBRATED;
	LpsUpdtTbl_t testUpdateTbl;
	testUpdateTbl.RequestedGear.Val  = 1000;
	testUpdateTbl.RequestedGear.Stat = LPS_REQUESTED_GEAR_STAT_OK;
	
	LpsWrk.UpdtTbl = &testUpdateTbl;
	
							/*Test Case 1*/	
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_VALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_NO_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_VALID;
	
	SetBucketStateWaitForLatch(TRUE);
	LpsWeighBestBktWtUpdate();
	result = LpsWeighGetBestAvailableBktWt();
		
	EXPECT_EQ(result.Wt,0);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth), LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE);
	
	
							/*Test Case 2*/ 
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_VALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_NO_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_INVALID;
	
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_EQ(result.Wt,0);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth), LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE);

	
							/*Test Case 3*/ 
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_VALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_INVALID;
	
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_EQ(result.Wt,0);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth), LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE);


							/*Test Case 4*/ 
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_VALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_VALID;
	
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_EQ(result.Wt,0);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth), LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE);


							/*Test Case 5*/ 
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_INVALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_VALID;
	
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_EQ(result.Wt,0);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth), LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE);


							/*Test Case 6*/ 
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_INVALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_NO_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_VALID;
	
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_EQ(result.Wt,0);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth),LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE);


							/*Test Case 7*/ 
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_INVALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_NO_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_INVALID;
	
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_EQ(result.Wt,0);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth),LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE);


							/*Test Case 8*/ 
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_INVALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_INVALID;
	
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_EQ(result.Wt,0);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth),LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE);
}

/* Calibrated test cases */
TEST(LpsWeighBestBktWt, Calibrated)
{
	LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
	
							/*Test Case 1*/	
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_VALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_NO_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_VALID;
	
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_EQ(result.Wt,10);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth),LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_HIGH);
	

	
							/*Test Case 2*/ 
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_VALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_NO_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_INVALID;
	
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_EQ(result.Wt,10);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth),LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_HIGH);

	
	
							/*Test Case 3*/ 
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_VALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_INVALID;
	
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_EQ(result.Wt,10);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth),LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_MED);


							/*Test Case 4*/ 
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_VALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_VALID;
	
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_EQ(result.Wt,5);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth), LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_MED);


							/*Test Case 5*/ 
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_INVALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5.1;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_VALID;
	
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_NEAR(result.Wt,5.1,0.1);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth), LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_MED);


							/*Test Case 6*/ 
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_INVALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_NO_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5.2;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_VALID;
	
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_NEAR(result.Wt,5.2,0.1);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth), LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_MED);


							/*Test Case 7*/ 
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_INVALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_NO_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_INVALID;
	
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_EQ(result.Wt,0);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth), LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE);


							/*Test Case 8*/ 
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_INVALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_INVALID;
	
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_EQ(result.Wt,0);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth), LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE);

		/* Extra test case for resetting the Best Available Bucket Weight */
	LpsWrk.WrwTbl.OpTbl.Wt          = 10;
	LpsWrk.WrwTbl.OpTbl.Status      = LPS_WEIGH_WRW_STATUS_INVALID;
	LpsWrk.WrwTbl.OpTbl.Warning 	= LPS_WEIGH_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             = 5;
	LpsWrk.LowLiftWt.Stat           = LPS_WEIGH_LLW_STATUS_INVALID;
	
	LpsWeighResetBestAvailableBktWt();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_EQ(result.Wt,0);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth), LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE);	
} 

/* Test cases for Overload warnings */
TEST(LpsWeighBestBktWt, OverloadWarnings)
{	
	LpsWrk.InitTbl.MachSpecificCfg.DigConfig.DigTargetWt = 10;
	LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
	
	LpsWrk.WrwTbl.OpTbl.Wt          	= 11.66;
	LpsWrk.WrwTbl.OpTbl.Status      	= LPS_WEIGH_WRW_STATUS_VALID;
	LpsWrk.WrwTbl.OpTbl.Warning 		= LPS_WEIGH_NO_WARNING_ACTIVE;
	
	LpsWrk.LowLiftWt.Wt             	= 5;
	LpsWrk.LowLiftWt.Stat           	= LPS_WEIGH_LLW_STATUS_VALID;
		
	LpsUpdtTbl_t testUpdateTbl;
	
	/* The machine is in reverse, which is a necessary condition for Overload warnings */
	testUpdateTbl.RequestedGear.Val  = 4096; // = 0x1000
	testUpdateTbl.RequestedGear.Stat = LPS_REQUESTED_GEAR_STAT_OK;
	
	LpsWrk.UpdtTbl = &testUpdateTbl;
	
	SetBucketStateWaitForLatch(FALSE);
	LpsWeighBestBktWtUpdate();	
	result = LpsWeighGetBestAvailableBktWt();
	
	EXPECT_NEAR(11.60,result.Wt,0.1);
	EXPECT_EQ(GET_ACCURACY(result.PayloadCalcMeth),LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_HIGH);
	EXPECT_EQ(TRUE, LpsWeighOverloadWarningActive());
}