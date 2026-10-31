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

//LpsWrkTbl_t LpsWrk;
LpsUpdtTbl_t DumpUpdtTbl;
extern float_32 NewTiltExtThreshold;

TEST(LpsDumpTest, FullDump)
{

	unsigned_32 i;
	LpsWrk.UpdtTbl = &DumpUpdtTbl;	
	
	/* Setting Machine Specific Configuration Values */
	LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.FullDumpBktAngleThreshold = -35;
	LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.PartDumpBktAngleThreshold =  40;
	LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.FullRackBktAngleThreshold =  35;
	LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold       =  90;
	
	//Test Case 1
	PayloadDumpStateInit();
	EXPECT_EQ(LPS_INIT_SUCCESS ,LpsWrk.InitErr);
	
	//Test Case 2
	DumpUpdtTbl.BktAngle.Val 	= 25;
	DumpUpdtTbl.BktAngle.Stat 	= LPS_BKT_ANGLE_STATUS_OK;
	DumpUpdtTbl.TiltCylExt.Val 	= 40;
	DumpUpdtTbl.TiltCylExt.Stat = LPS_CYL_EXT_STAT_OK;
	
	LpsWeighDumpDetectUpdate();
	
	EXPECT_EQ(FALSE, GetReferenceCaptured());
	EXPECT_EQ(LPS_WEIGHT_BKT_PARTIALLY_DUMPED ,GetDumpStateStatus());
	
	
	/* Transition from Wait for Latch to Wait for Dump */
	//Test Case 3
	DumpUpdtTbl.BktAngle.Val 	= 41;
	DumpUpdtTbl.BktAngle.Stat 	= LPS_BKT_ANGLE_STATUS_OK;
	DumpUpdtTbl.TiltCylExt.Val 	= 65;
	DumpUpdtTbl.TiltCylExt.Stat = LPS_CYL_EXT_STAT_OK;
	
	/* This function is to be called whenever the transition 
		from Wait for latch to wait for Dump happens*/
	SetTiltExtensionThreshold();
	
	LpsWeighDumpDetectUpdate();
	
	EXPECT_EQ(TRUE, GetReferenceCaptured());
	EXPECT_EQ(LPS_WEIGHT_BKT_FULLY_RACKED ,GetDumpStateStatus());
	

	/****************** Fully racked *********************/
	//Test Case 4
	DumpUpdtTbl.BktAngle.Val 	= 45;
	DumpUpdtTbl.BktAngle.Stat 	= LPS_BKT_ANGLE_STATUS_OK;
	DumpUpdtTbl.TiltCylExt.Val 	= 70;
	DumpUpdtTbl.TiltCylExt.Stat = LPS_CYL_EXT_STAT_OK;
			
	LpsWeighDumpDetectUpdate();

	EXPECT_EQ(TRUE, GetReferenceCaptured());
	EXPECT_EQ(LPS_WEIGHT_BKT_FULLY_RACKED ,GetDumpStateStatus());

	//Test Case 5
	DumpUpdtTbl.BktAngle.Val 	= 37;
	DumpUpdtTbl.BktAngle.Stat 	= LPS_BKT_ANGLE_STATUS_OK;
	DumpUpdtTbl.TiltCylExt.Val 	= 97;
	DumpUpdtTbl.TiltCylExt.Stat = LPS_CYL_EXT_STAT_OK;
			
	LpsWeighDumpDetectUpdate();
	
	EXPECT_EQ(TRUE, GetReferenceCaptured());
	EXPECT_EQ(LPS_WEIGHT_BKT_FULLY_RACKED ,GetDumpStateStatus());
	/******************** Partially Dumped ******************/
	//Test Case 6
	DumpUpdtTbl.BktAngle.Val 	= 20;
	DumpUpdtTbl.BktAngle.Stat 	= LPS_BKT_ANGLE_STATUS_OK;
	DumpUpdtTbl.TiltCylExt.Val 	= 35;
	DumpUpdtTbl.TiltCylExt.Stat = LPS_CYL_EXT_STAT_OK;
	
	LpsWeighDumpDetectUpdate();
	
	EXPECT_EQ(FALSE, GetReferenceCaptured());
	EXPECT_EQ(LPS_WEIGHT_BKT_PARTIALLY_DUMPED ,GetDumpStateStatus());
	
	
	/********************* Fully Dumped ******************/
	//Test Case 7
	DumpUpdtTbl.BktAngle.Val 	= -40;
	DumpUpdtTbl.BktAngle.Stat 	= LPS_BKT_ANGLE_STATUS_OK;
	DumpUpdtTbl.TiltCylExt.Val 	= 10;
	DumpUpdtTbl.TiltCylExt.Stat = LPS_CYL_EXT_STAT_OK;
	
	LpsWeighDumpDetectUpdate();
	
	EXPECT_EQ(FALSE, GetReferenceCaptured());
	EXPECT_EQ(LPS_WEIGHT_BKT_FULLY_DUMPED ,GetDumpStateStatus());
	
	/********************* Checking NewTiltExtThreshold values ******************/
	//Test Case 8
	DumpUpdtTbl.BktAngle.Val 	= 41;
	DumpUpdtTbl.BktAngle.Stat 	= LPS_BKT_ANGLE_STATUS_OK;
	DumpUpdtTbl.TiltCylExt.Val 	= 65;
	DumpUpdtTbl.TiltCylExt.Stat = LPS_CYL_EXT_STAT_OK;
	SetTiltExtensionThreshold();
	for(i=0;DumpUpdtTbl.TiltCylExt.Val 	<= 90;i++)
	{
		DumpUpdtTbl.TiltCylExt.Val 	= DumpUpdtTbl.TiltCylExt.Val + i;
		DumpUpdtTbl.BktAngle.Val 	= DumpUpdtTbl.BktAngle.Val + 0.5;
		
		LpsWeighDumpDetectUpdate();
		
		EXPECT_EQ(TRUE, GetReferenceCaptured());
		EXPECT_EQ((DumpUpdtTbl.TiltCylExt.Val - (float_32)LPS_TILT_CYL_EXT_DUMP_DELTA) ,NewTiltExtThreshold);
	}
	
	//Test Case 9
	DumpUpdtTbl.BktAngle.Val 	= 41;
	DumpUpdtTbl.BktAngle.Stat 	= LPS_BKT_ANGLE_STATUS_OK;
	DumpUpdtTbl.TiltCylExt.Val 	= 95;
	DumpUpdtTbl.TiltCylExt.Stat = LPS_CYL_EXT_STAT_OK;
	
	for(i=0;DumpUpdtTbl.TiltCylExt.Val 	<= 100;i++)
	{
		DumpUpdtTbl.TiltCylExt.Val 	= DumpUpdtTbl.TiltCylExt.Val + i;
		DumpUpdtTbl.BktAngle.Val 	= DumpUpdtTbl.BktAngle.Val + 0.5;
		
		LpsWeighDumpDetectUpdate();
		
		EXPECT_EQ(TRUE, GetReferenceCaptured());
		EXPECT_EQ(LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold ,NewTiltExtThreshold);
	}
	
	//Test Case 10
	DumpUpdtTbl.BktAngle.Val 	= 55;
	DumpUpdtTbl.BktAngle.Stat 	= LPS_BKT_ANGLE_STATUS_OK;
	DumpUpdtTbl.TiltCylExt.Val 	= 65;
	DumpUpdtTbl.TiltCylExt.Stat = LPS_CYL_EXT_STAT_OK;
	SetTiltExtensionThreshold();
	for(i=0;DumpUpdtTbl.TiltCylExt.Val 	>= 2;i++)
	{
		DumpUpdtTbl.TiltCylExt.Val 	= DumpUpdtTbl.TiltCylExt.Val - i;
		DumpUpdtTbl.BktAngle.Val 	= DumpUpdtTbl.BktAngle.Val - 0.5;
		
		LpsWeighDumpDetectUpdate();
		
		EXPECT_EQ(TRUE, GetReferenceCaptured());
		EXPECT_EQ(60 ,NewTiltExtThreshold);
	}
	
	//Test Case 11
	DumpUpdtTbl.BktAngle.Val 	= 55;
	DumpUpdtTbl.BktAngle.Stat 	= LPS_BKT_ANGLE_STATUS_OK;
	DumpUpdtTbl.TiltCylExt.Val 	= 6;
	DumpUpdtTbl.TiltCylExt.Stat = LPS_CYL_EXT_STAT_OK;
	SetTiltExtensionThreshold();
	
	LpsWeighDumpDetectUpdate();
		
	EXPECT_EQ(TRUE, GetReferenceCaptured());
	EXPECT_EQ(LPS_TILT_EXT_FULL_DUMP_LIMIT ,NewTiltExtThreshold);	
	
	//Test Case 12
	DumpUpdtTbl.BktAngle.Val 	= 55;
	DumpUpdtTbl.BktAngle.Stat 	= LPS_BKT_ANGLE_STATUS_BAD;
	DumpUpdtTbl.TiltCylExt.Val 	= 6;
	DumpUpdtTbl.TiltCylExt.Stat = LPS_CYL_EXT_STAT_OK;
	
	SetTiltExtensionThreshold();
	
	LpsWeighDumpDetectUpdate();
		
	EXPECT_EQ(FALSE, GetReferenceCaptured());
	EXPECT_EQ(LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold ,NewTiltExtThreshold);
	EXPECT_EQ(LPS_WEIGHT_BKT_DUMP_STATE_UNKNOWN ,GetDumpStateStatus());
	
	//Test Case 13
	DumpUpdtTbl.BktAngle.Val 	= 55;
	DumpUpdtTbl.BktAngle.Stat 	= LPS_BKT_ANGLE_STATUS_OK;
	DumpUpdtTbl.TiltCylExt.Val 	= 6;
	DumpUpdtTbl.TiltCylExt.Stat = LPS_CYL_EXT_STAT_BAD;
	
	LpsWeighDumpDetectUpdate();
		
	EXPECT_EQ(FALSE, GetReferenceCaptured());
	EXPECT_EQ(LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold ,NewTiltExtThreshold);
	EXPECT_EQ(LPS_WEIGHT_BKT_DUMP_STATE_UNKNOWN ,GetDumpStateStatus());
	
	//Test Case 14
	DumpUpdtTbl.BktAngle.Val 	= 55;
	DumpUpdtTbl.BktAngle.Stat 	= LPS_BKT_ANGLE_STATUS_BAD;
	DumpUpdtTbl.TiltCylExt.Val 	= 6;
	DumpUpdtTbl.TiltCylExt.Stat = LPS_CYL_EXT_STAT_BAD;
		
	LpsWeighDumpDetectUpdate();
		
	EXPECT_EQ(FALSE, GetReferenceCaptured());
	EXPECT_EQ(LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold ,NewTiltExtThreshold);
	EXPECT_EQ(LPS_WEIGHT_BKT_DUMP_STATE_UNKNOWN ,GetDumpStateStatus());
	
	
}