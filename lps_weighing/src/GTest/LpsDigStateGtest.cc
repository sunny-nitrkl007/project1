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



LpsUpdtTbl_t GTestUpdtPt;

void SetDefaultValues(void)
{
    
    LpsWrk.UpdtTbl = &GTestUpdtPt;
		
    LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_CALIBRATED;
	
	LpsWrk.DumpWtChangeData.WtStabilityIndex        = 0;
	
	LpsWrk.DumpWtChangeData.DumpCumulativeWtChange = 90.0;
	
	LpsWrk.InitTbl.MachSpecificCfg.DigConfig.DigStartLimit = 20;
	
	LpsWrk.InitTbl.MachSpecificCfg.DigConfig.DigEndLimit = 10;
	
	LpsWrk.InitTbl.MachSpecificCfg.DigConfig.DigTargetWt =5;
	
	LpsWrk.InitTbl.MachSpecificCfg.DigConfig.DigDurationMinLimit = 1;
	
	LpsWrk.InitTbl.MachSpecificCfg.StartOfWeigh = 10; 
	
	LpsWrk.InitTbl.MachSpecificCfg.DigConfig.LiftLowerVelocityLimit = 8;
	
	LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.FullDumpBktAngleThreshold = -35;
	
	LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.PartDumpBktAngleThreshold =  40;
	
	LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.FullRackBktAngleThreshold =  35;
	
	LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold       =  90;
	
	LpsWrk.InitTbl.MachSpecificCfg.DigConfig.DigDurationMaxLimit        =  100;
	
	LpsWrk.InitTbl.ExecRate = 1;
	
	LpsWrk.UpdtTbl->RequestedGear.Stat = LPS_REQUESTED_GEAR_STAT_OK;
	
	LpsWrk.UpdtTbl->RequestedGear.Val  = 0x4000;
	
	LpsWrk.UpdtTbl->LiftCylExt.Val = 8;
	
	LpsWrk.UpdtTbl->LiftCylVel.Val = 10;
	
	LpsWrk.DigDetectData.DigDetected = FALSE;
	
	LpsWrk.DigDetectData.DigStarted  = FALSE;
	
	LpsWrk.DigDetectData.DigDuration = 0;
	
	GTestUpdtPt.BktAngle.Val 	= 30;
	
	GTestUpdtPt.BktAngle.Stat 	= LPS_BKT_ANGLE_STATUS_BAD;
	
	GTestUpdtPt.TiltCylExt.Val 	= 35;
	
	GTestUpdtPt.TiltCylExt.Stat = LPS_CYL_EXT_STAT_BAD;
}


TEST(LpsDigDetectTest,DigDetect)
{
	float GTInitPtr;
	unsigned int i;
	
	LpsUpdtErrorTypes_t    GTestUptEr;
	
	LpsWeighDumpWtBuffer_t GTestWtBuffer;
	
	GTestWtBuffer.PtrDumpWtBuffer = &GTInitPtr;
	
	GTestWtBuffer.bufferSize = sizeof(GTInitPtr);
	
	LpsInitErrorTypes_t    GTestInitEr;
	
	LpsWrk.UpdtTbl = &GTestUpdtPt;
	
	
	//CASE 1

    GTestInitEr = PayloadDigDetectInit(GTestWtBuffer);
	
	EXPECT_EQ(GTestInitEr,LPS_INIT_SUCCESS);
	
	//CASE 2
	
	SetDefaultValues();
	
	for(i=0;i<10000;i++)
	{
	
	GTestUptEr = PayloadDigDetectUpdate();
	}
	
	EXPECT_EQ(GTestUptEr,LPS_UPDT_SUCCESS);
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigState,LPS_WEIGHT_BKT_DIGGING);
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigDetected,TRUE);

	
	//CASE 3
	
	SetDefaultValues();
	
	LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.CalStat = LPS_WEIGH_SYSTEM_UNCALIBRATED;
	
	for(i=0;i<10000;i++)
	{
	
	GTestUptEr = PayloadDigDetectUpdate();
	}
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigState,LPS_WEIGHT_BKT_DIG_STATE_UNKNOWN);
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigDetected,FALSE);
	
	//CASE 4
	
	SetDefaultValues();
	
	LpsWrk.DumpWtChangeData.WtStabilityIndex  = 5;
	
	for(i=0;i<10000;i++)
	{
	
	GTestUptEr = PayloadDigDetectUpdate();
	}
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigState,LPS_WEIGHT_BKT_NOT_DIGGING);
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigDetected,FALSE);
	
	//CASE 5
	
	SetDefaultValues();
	
    GTestUpdtPt.BktAngle.Val 	= 41;
	GTestUpdtPt.BktAngle.Stat 	= LPS_BKT_ANGLE_STATUS_OK;
	GTestUpdtPt.TiltCylExt.Val 	= 35;
	GTestUpdtPt.TiltCylExt.Stat = LPS_CYL_EXT_STAT_OK;
    
	LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.FullDumpBktAngleThreshold = -35;
	LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.PartDumpBktAngleThreshold =  40;
	LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.FullRackBktAngleThreshold =  35;
	LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold       =  90;
	
	for(i=0;i<10000;i++)
	{
	
	GTestUptEr = PayloadDigDetectUpdate();
	}
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigState,LPS_WEIGHT_BKT_NOT_DIGGING);
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigDetected,FALSE);
	
	//CASE 6
	
	SetDefaultValues();
	
	LpsWrk.DumpWtChangeData.DumpCumulativeWtChange = 110.0;
	
	for(i=0;i<10000;i++)
	{
	
	GTestUptEr = PayloadDigDetectUpdate();
	}
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigState,LPS_WEIGHT_BKT_NOT_DIGGING);
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigDetected,FALSE);
	
	//CASE 7
	
	SetDefaultValues();
	
	LpsWrk.UpdtTbl->RequestedGear.Val  = 0x0000;
	
	for(i=0;i<10000;i++)
	{
	
	GTestUptEr = PayloadDigDetectUpdate();
	}
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigState,LPS_WEIGHT_BKT_NOT_DIGGING);
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigDetected,FALSE);
	
	//CASE 8
	
	SetDefaultValues();
	
	GTestUpdtPt.LiftCylExt.Val = 20;
	
	for(i=0;i<10000;i++)
	{
	
	GTestUptEr = PayloadDigDetectUpdate();
	}
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigState,LPS_WEIGHT_BKT_NOT_DIGGING);
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigDetected,FALSE);
	
	//CASE 9
	
	SetDefaultValues();
	
	GTestUpdtPt.LiftCylVel.Val = 5;
	
	for(i=0;i<10000;i++)
	{
	
	GTestUptEr = PayloadDigDetectUpdate();
	}
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigState,LPS_WEIGHT_BKT_NOT_DIGGING);
	
	EXPECT_EQ(LpsWrk.DigDetectData.DigDetected,FALSE);
	
	


}