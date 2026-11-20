//test_lps_lib.cc

#include "gtest/gtest.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

/*
#ifndef __TYPE_DEF_H__
#include "TypeDef.h" // Contains type definitions of standard datatypes 
#endif
*/
#include "LpsPublic.h" /*******************************************************/
                       /* Has prototypes of interfaces and functions which are*/
                       /* exported to the application using the library       */
                       /*******************************************************/
#include "LpsPrivate.h"

#define HUNDRED 100.0
#define MINUS_ONE -1
#define ZERO 0
#define TWO_HUNDRED 200
#define FOURTY 40



typedef struct  UPDATE_DATA
{
	float hePress;
	float rePress;
	float cylExt;
	float cylVel;
	float oilTemp;
	float exp_weight;
}updateData_t;
updateData_t *updateData;
//////////////////////////////////////////////////////////////////
//to read the raw input data from the file and update into structure
int readRawInputData(std::string RawInputPath);
//to read the machine specific input data from the file and update into structure
int readMachineSpecificData(std::string MachSpecificPath);
//to read the calibration input data from the file and update into structure
int readCalibrationData(std::string CalibrationPath);
//calculate  expected difference pressure
float expDiffPressureCalc();
//calculate  expected response calculation
LpsUpdtErrorTypes_t expResponseCalc();
//calculate  expected difference pressure
float expWeightCalc();


extern LpsWrkTbl_t LpsWrk;

int status=ZERO;
float head_presure,rod_presure,exp_diff_presure,currDiff_presure;

//which will use for test cases
LpsInitTbl_t InitTbl;
LpsUpdtTbl_t UpdtTbl;




//to read the raw input data from the file and update into structure
int readRawInputData(std::string RawInputPath)
{
	status=ZERO;
	FILE *fp;
	fp=NULL;
	//float i;
	float j[7];
	fp=fopen(RawInputPath.c_str(),"r");
	if(NULL==fp)
	{
		status=MINUS_ONE;
	}
	else//file open successfully
	{
	  char a[TWO_HUNDRED];
	  char b[TWO_HUNDRED];
	  char c[TWO_HUNDRED]; char d[TWO_HUNDRED]; char e[TWO_HUNDRED]; char f[TWO_HUNDRED];char g[TWO_HUNDRED];
	fscanf(fp,"%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],\n",a,b,c,d,e,f,g);
	//int count;

	//printf(" %s %s %s %s %s %s %s \n",a,b,c,d,e,f,g);//for testing

	fscanf(fp,"%f,%f,%f,%f,%f,%f,%f, \n",&j[0],&j[1],&j[2],&j[3],&j[4],&j[5],&j[6]);

//	for(count=0;count<7;count++)//for testing
//	printf("%f\n",j[count]);

	UpdtTbl.LiftCylHePres.Val = j[0];
	UpdtTbl.LiftCylRePres.Val = j[1];
	UpdtTbl.LiftCylExt.Val = j[2];
	UpdtTbl.LiftCylVel.Val = j[3];
	UpdtTbl.HydOilTemp.Val = j[4];

	if(j[5]==1.0)
	{
		//printf("IF\n");
		UpdtTbl.LiftCylExt.Stat = LPS_CYL_EXT_STAT_OK;
		UpdtTbl.LiftCylHePres.Stat =LPS_PRES_STATUS_OK;
		UpdtTbl.LiftCylRePres.Stat =LPS_PRES_STATUS_OK;
		UpdtTbl.LiftCylVel.Stat = LPS_CYL_VEL_STATUS_OK;
		UpdtTbl.HydOilTemp.Stat= LPS_HYD_OIL_TEMP_STATUS_OK;
	}
	else
	{
		//printf("ELSE\n");
		UpdtTbl.LiftCylExt.Stat = LPS_CYL_EXT_STAT_BAD;
		UpdtTbl.LiftCylHePres.Stat =LPS_PRES_STATUS_BAD;
		UpdtTbl.LiftCylRePres.Stat =LPS_PRES_STATUS_BAD;
		UpdtTbl.LiftCylVel.Stat = LPS_CYL_VEL_STATUS_BAD;
		UpdtTbl.HydOilTemp.Stat= LPS_HYD_OIL_TEMP_STATUS_BAD;
	}


	InitTbl.InstallStat = j[5];
	InitTbl.ExecRate = j[6];


	fclose(fp);
	}
	return status;
}


//to read the machine specific input data from the file and update into structure
int readMachineSpecificData(std::string MachSpecificPath)
{
	status = ZERO;
	FILE *fp;
	fp=NULL;
	//float i;
	float j[8];


	fp=fopen(MachSpecificPath.c_str(),"r");
	if(NULL == fp)
		{
			//printf("MAC-SPEC-FILE FAIL\n");
			status=MINUS_ONE;
		}
	else//file open successfully
	{

	  char a[FOURTY][TWO_HUNDRED];
	fscanf(fp,"%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],\n",a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7]);
	//int count;

//	printf(" %s %s  \n",a[0],a[7]);//for testing

	fscanf(fp,"%f,%f ,%f ,%f ,%f ,%f ,%f ,%f, \n",&j[0],&j[1],&j[2],&j[3],&j[4],&j[5],&j[6],&j[7]);


//	for(count=0;count<8;count++)//for testing
//	printf("%f\n",j[count]);


	InitTbl.MachSpecificCfg.NoOfLiftCyls = (unsigned_8)j[0];
	InitTbl.MachSpecificCfg.LiftCylBoreDia = j[1];
	InitTbl.MachSpecificCfg.LiftCylRodDia  = j[2];
		if(j[3]==0.0)
			InitTbl.MachSpecificCfg.HydOilType = LPS_OIL_TYPE_SAE_10W;
		else
			InitTbl.MachSpecificCfg.HydOilType = LPS_OIL_TYPE_SAE_0W20;

		InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylHeLineLoss2ndOrdrCoeff = j[4];
		InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylHeLineLoss1stOrdrCoeff = j[5];
		InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylReLineLoss2ndOrdrCoeff = j[6];
		InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylReLineLoss1stOrdrCoeff = j[7];

	fclose(fp);
	}
	
	return status;
}


//to read the calibration input data from the file and update into structure
int readCalibrationData(std::string CalibrationPath)
{
	status = ZERO;
	FILE *fp;
	fp = NULL;
	//float i;
	float j[FOURTY];


	fp = fopen(CalibrationPath.c_str(),"r");
	if(NULL == fp)
	{
		status = MINUS_ONE;
	}
	else//file open successfully
	{
	char a[FOURTY][TWO_HUNDRED];
	fscanf(fp,"%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],%199[^,],\n",a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19],a[20],a[21],a[22],a[23],a[24],a[25],a[26],a[27],a[28],a[29],a[30],a[31],a[32],a[33],a[34],a[35],a[36],a[37],a[38],a[39]);
	int count;

	//printf(" %s %s  \n",a[0],a[39]);//for testing

	fscanf(fp,"%f,%f ,%f ,%f ,%f, %f,%f ,%f ,%f ,%f ,%f,%f ,%f ,%f ,%f, %f,%f ,%f ,%f ,%f ,%f,%f ,%f ,%f ,%f ,%f,%f ,%f ,%f ,%f ,%f,%f ,%f ,%f ,%f, %f,%f ,%f ,%f ,%f, \n",&j[0],&j[1],&j[2],&j[3],&j[4],&j[5],&j[6],&j[7],&j[8],&j[9],&j[10],&j[11],&j[12],&j[13],&j[14],&j[15],&j[16],&j[17],&j[18],&j[19],&j[20],&j[21],&j[22],&j[23],&j[24],&j[25],&j[26],&j[27],&j[28],&j[29],&j[30],&j[31],&j[32],&j[33],&j[34],&j[35],&j[36],&j[37],&j[38],&j[39]);


	//for(count=0;count<FOURTY;count++)//for testing
	//printf("%f\n",j[count]);


	int iCount=0;
	for( iCount=0;iCount<11;iCount++) // set Full/Empty bucket slow raise lift cylinder extension points in mm
	{
		InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseEmptyBktLiftHt[iCount] = j[iCount];
		InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseFullBktLiftHt[iCount] = j[iCount];
		InitTbl.MachSpecificCfg.CalibTbl.SlowLowerEmptyBktLiftHt[iCount] = j[iCount];
		InitTbl.MachSpecificCfg.CalibTbl.SlowLowerFullBktLiftHt[iCount] = j[iCount];
	}

	for( iCount=0;iCount<11;iCount++) //set empty bucket raise/lower pressure curve in Kpa
	{
		InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseEmptyBktLiftPres[iCount] = j[iCount+11];
		InitTbl.MachSpecificCfg.CalibTbl.SlowLowerEmptyBktLiftPres[iCount] = j[iCount+11];

	}

	for( iCount=0;iCount<11;iCount++) //set full bucket raise/lower pressure curve in Kpa
	{
		InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseFullBktLiftPres[iCount] = j[iCount+22];
		InitTbl.MachSpecificCfg.CalibTbl.SlowLowerFullBktLiftPres[iCount] = j[iCount+22];
		}

	InitTbl.MachSpecificCfg.CalibTbl.FastRaiseEmptyBktDeltaPres = j[33];
	InitTbl.MachSpecificCfg.CalibTbl.FastRaiseFullBktDeltaPres = j[34];
	InitTbl.MachSpecificCfg.CalibTbl.EmptyBktSlowRaiseSpd = j[35];
	InitTbl.MachSpecificCfg.CalibTbl.EmptyBktFastRaiseSpd = j[36];
	InitTbl.MachSpecificCfg.CalibTbl.FullBktSlowRaiseSpd = j[37];
	InitTbl.MachSpecificCfg.CalibTbl.FullBktFastRaiseSpd =j[38];
	InitTbl.MachSpecificCfg.CalibTbl.Calwt = j[39];

	fclose(fp);
	}
	return status;
}



/******************************************************************************
FUNCTION NAME:expDiffPressureCalc
DESCRIPTION: This function will generate the expected value ,and it is depends on LPS Lib,
if LPS Library changes in future ,this will also need to change according to that.
PARAMETER DESCRIPTION: NULL
RETURN VALUE: expDiffPres
*******************************************************************************/
//calculate  expected difference pressure
float expDiffPressureCalc()

{


	float cylnBoreArea,cylnRodArea,heFlowConst,reToHeFlwRatio,heOilflow,reOilFlow,hydOilVisc,hydOilDensity,
	 oilFlowSquaredCoeff,OilFlowCoeff,oilPresLoss,expDiffPres;


	cylnBoreArea= (3.14 * (InitTbl.MachSpecificCfg.LiftCylBoreDia/(float)2.0) *
							(InitTbl.MachSpecificCfg.LiftCylBoreDia/(float)2.0));
	cylnRodArea= (3.14 * (InitTbl.MachSpecificCfg.LiftCylRodDia/(float)2.0) *
			(InitTbl.MachSpecificCfg.LiftCylRodDia/(float)2.0));

	heFlowConst = ((float)60.0 * cylnBoreArea * InitTbl.MachSpecificCfg.NoOfLiftCyls / (float)1000000.0);
	reToHeFlwRatio = (cylnBoreArea - cylnRodArea)/cylnBoreArea;

	 /* Hydraulic oil temperature Vs Viscosity map x = temp in DegC ,y = Viscosity in Kg/m-3 */
		static const float test_tempSAE10W_1[]  = { 0, 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100 }; /* Degrees C */
	    static const float test_viscSAE10W[]  = { 0.401163657, 0.271392082, 0.189249493, 0.135629739, 0.099636096, 0.074851526, 0.057384532, 0.035582067, 0.023450402, 0.016257589, 0.01175743, 0.008809872, 0.006801861, 0.005386759 }; /* kg/m-s */
	    static const float test_tempSAE0W20_1[] = { -40, -32, -18, 0, 21, 50, 80 };
	    static const float test_viscSAE0W20[] = { 4.16344705, 1.899216267, 0.600904802, 0.188654307, 0.067443573, 0.023985969, 0.011154169 };



	    if (LPS_OIL_TYPE_SAE_0W20 == InitTbl.MachSpecificCfg.HydOilType)
	    {
	    	hydOilVisc = LpsLookup(UpdtTbl.HydOilTemp.Val, test_tempSAE0W20_1, test_viscSAE0W20, sizeof(test_tempSAE0W20_1)/sizeof(float));
	    }
	    else
	    { /* Assume Standard Oil as default */
	    	hydOilVisc = LpsLookup(UpdtTbl.HydOilTemp.Val, test_tempSAE10W_1, test_viscSAE10W, sizeof(test_tempSAE10W_1)/sizeof(float));
	    }

	/* Hydraulic oil temperature Vs Viscosity map x = temp in DegC ,y = Density in Kg/m^3 */
		//static const float test_tempSAE10W_2[]  = { -20, 0, 20, 30, 40, 50, 60, 70, 80, 90, 100 }; /* Degrees C */
		static const float test_densSAE10W[]  = { 903.1, 891.1, 877.7, 871, 864.4, 857.8, 851.2, 844.7, 838.2, 831.7, 825.2 }; /* kg/m3 */
		//static const float test_tempSAE0W20_2[] = { -40, -32, -18, 0, 21, 50, 80 };
		static const float test_densSAE0W20[] = { 909.7, 904.1, 894.3, 881.7, 867, 846.7, 825.7 };



		if (LPS_OIL_TYPE_SAE_0W20 == InitTbl.MachSpecificCfg.HydOilType)
		{
			hydOilDensity = LpsLookup(UpdtTbl.HydOilTemp.Val, test_tempSAE0W20_1, test_densSAE0W20, sizeof(test_tempSAE0W20_1)/sizeof(float));
		}
		else
		{ /* Assume Standard Oil as default */
			hydOilDensity = LpsLookup(UpdtTbl.HydOilTemp.Val, test_tempSAE10W_1, test_densSAE10W, sizeof(test_tempSAE10W_1)/sizeof(float));
		}

	heOilflow=UpdtTbl.LiftCylVel.Val*heFlowConst;
	reOilFlow=heOilflow*reToHeFlwRatio;


	expDiffPres=UpdtTbl.LiftCylHePres.Val-(UpdtTbl.LiftCylRePres.Val*reToHeFlwRatio);

	   /* Determining Lift Cylinder Head End pressure drop */
	     oilFlowSquaredCoeff = (InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylHeLineLoss2ndOrdrCoeff * hydOilDensity);
	     OilFlowCoeff        = (InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylHeLineLoss1stOrdrCoeff * hydOilVisc);


	     if(heOilflow >= 0)
	     {
	       	oilPresLoss   = (heOilflow * heOilflow * oilFlowSquaredCoeff + heOilflow * OilFlowCoeff);
	       	UpdtTbl.LiftCylHePres.Val = (UpdtTbl.LiftCylHePres.Val - oilPresLoss);

	     }
	     else
	     {
	      	oilPresLoss   = (heOilflow * heOilflow * oilFlowSquaredCoeff - heOilflow * OilFlowCoeff);
	       	UpdtTbl.LiftCylHePres.Val = (UpdtTbl.LiftCylHePres.Val + oilPresLoss);

	     }

	     /* Determining Lift Cylinder Rod End pressure drop */
	     oilFlowSquaredCoeff = (InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylReLineLoss2ndOrdrCoeff * hydOilDensity);
	     OilFlowCoeff        = (InitTbl.MachSpecificCfg.HydPressLossCoeff.LiftCylReLineLoss1stOrdrCoeff * hydOilVisc);

	     if(reOilFlow >= 0)
	     {
	        oilPresLoss   = (reOilFlow * reOilFlow * oilFlowSquaredCoeff + reOilFlow * OilFlowCoeff);
	        UpdtTbl.LiftCylRePres.Val = (UpdtTbl.LiftCylRePres.Val - oilPresLoss);
	     }
	     else
	     {
	        oilPresLoss   = (reOilFlow * reOilFlow * oilFlowSquaredCoeff - reOilFlow * OilFlowCoeff);
	        UpdtTbl.LiftCylRePres.Val = (UpdtTbl.LiftCylRePres.Val + oilPresLoss);
	     }

	     /* Determining/calculating Lift cylinder Rod End Pressure by eleminating the Rod area */
	     if( (reToHeFlwRatio > (float) 0.0) &&
	         (reToHeFlwRatio <= 1.0) )
	      {
	       	UpdtTbl.LiftCylRePres.Val = (UpdtTbl.LiftCylRePres.Val * reToHeFlwRatio);
	      }

	      if(UpdtTbl.LiftCylHePres.Val > UpdtTbl.LiftCylRePres.Val)
	      {
	    	  expDiffPres = UpdtTbl.LiftCylHePres.Val - UpdtTbl.LiftCylRePres.Val;
	      }
	      else
	      {
	    	  expDiffPres = 0.0;
	      }





	return expDiffPres;
}

//calculate  expected response calculation
LpsUpdtErrorTypes_t expResponseCalc()
{
	LpsUpdtErrorTypes_t expRes;

	if(LPS_INIT_SUCCESS != LpsWrk.InitErr)
	{
		expRes = LPS_UPDT_NOT_INIT;
		return expRes;
	}

	if(STATUS_GOOD != LpsChkInputStat())
		expRes  = LPS_UPDT_FAIL;
	else
		expRes  = LPS_UPDT_SUCCESS;

	return expRes;

}
/******************************************************************************
FUNCTION NAME:expWeightCalc
DESCRIPTION: This function will generate the expected value ,and it is depends on LPS Lib,
if LPS Library changes in future ,this will also need to change according to that.
PARAMETER DESCRIPTION: NULL
RETURN VALUE: expDiffPres
*******************************************************************************/
//calculate  expected difference pressure
float expWeightCalc()
{

	float emptyBktPres;
	float fullBktPres;
	float linkageSpd;
	float emptyBktVelCompPres;
	float fullBktVelCompPres;
	float emptyBktRaisePres;
	float fullBktRaisePres;
	float emptyBktLowerPres;
	float fullBktLowerPres;
	float instRawWtSlope;
	static boolean staticWtMode       = 0;
	static float staticWtFactorStr    = 0.5;
	static float staticWtFactorTau    = 1.93;
    static float staticWtFactorOlRaw  = 0.3;
	static float staticWtFactorOlFilt = 0.0;
	static float staticWtFactorCurr   = 0.0;

	LpsInstWtRaw_t wt;

	if(UpdtTbl.LiftCylVel.Val > 0.0)
	 {
		linkageSpd   = UpdtTbl.LiftCylVel.Val;


		emptyBktPres = LpsLookupExtrap(UpdtTbl.LiftCylExt.Val,InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseEmptyBktLiftHt,
			                           InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseEmptyBktLiftPres,(sizeof(InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseEmptyBktLiftHt)/4));

		fullBktPres  = LpsLookupExtrap(UpdtTbl.LiftCylExt.Val,InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseFullBktLiftHt,
				                       InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseFullBktLiftPres,(sizeof(InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseFullBktLiftHt)/4));

		if(linkageSpd < InitTbl.MachSpecificCfg.CalibTbl.EmptyBktSlowRaiseSpd)
		{
			emptyBktVelCompPres = 0.0;
		}
	    else if(linkageSpd > InitTbl.MachSpecificCfg.CalibTbl.EmptyBktFastRaiseSpd)
		{
			emptyBktVelCompPres = InitTbl.MachSpecificCfg.CalibTbl.FastRaiseEmptyBktDeltaPres;
		}
		else if (InitTbl.MachSpecificCfg.CalibTbl.EmptyBktFastRaiseSpd > InitTbl.MachSpecificCfg.CalibTbl.EmptyBktSlowRaiseSpd)
		{
			emptyBktVelCompPres = ((InitTbl.MachSpecificCfg.CalibTbl.FastRaiseEmptyBktDeltaPres/(InitTbl.MachSpecificCfg.CalibTbl.EmptyBktFastRaiseSpd - InitTbl.MachSpecificCfg.CalibTbl.EmptyBktSlowRaiseSpd)) *
					               (linkageSpd - InitTbl.MachSpecificCfg.CalibTbl.EmptyBktSlowRaiseSpd));
		}
		else
		{
			emptyBktVelCompPres = 0.0;
		}

		if(linkageSpd < InitTbl.MachSpecificCfg.CalibTbl.FullBktSlowRaiseSpd)
		{
		    fullBktVelCompPres = 0.0;
        }
		else if(linkageSpd > InitTbl.MachSpecificCfg.CalibTbl.FullBktFastRaiseSpd)
		{
			fullBktVelCompPres = InitTbl.MachSpecificCfg.CalibTbl.FastRaiseFullBktDeltaPres;
		}
		else if (InitTbl.MachSpecificCfg.CalibTbl.FullBktFastRaiseSpd > InitTbl.MachSpecificCfg.CalibTbl.FullBktSlowRaiseSpd)
		{
			fullBktVelCompPres = ((InitTbl.MachSpecificCfg.CalibTbl.FastRaiseFullBktDeltaPres/(InitTbl.MachSpecificCfg.CalibTbl.FullBktFastRaiseSpd - InitTbl.MachSpecificCfg.CalibTbl.FullBktSlowRaiseSpd)) *
		    		              (linkageSpd - InitTbl.MachSpecificCfg.CalibTbl.FullBktSlowRaiseSpd));
		}
		else
		{
			fullBktVelCompPres = 0.0;
        }

		emptyBktPres = (emptyBktPres + emptyBktVelCompPres);
		fullBktPres  = (fullBktPres + fullBktVelCompPres);

		staticWtFactorStr = 0.5;
		staticWtMode      = 0;

	 }
	else if(UpdtTbl.LiftCylVel.Val < 0.0)
	{
		emptyBktPres = LpsLookupExtrap(UpdtTbl.LiftCylExt.Val,InitTbl.MachSpecificCfg.CalibTbl.SlowLowerEmptyBktLiftHt,
				                       InitTbl.MachSpecificCfg.CalibTbl.SlowLowerEmptyBktLiftPres,sizeof(InitTbl.MachSpecificCfg.CalibTbl.SlowLowerEmptyBktLiftHt)/sizeof(float));

        fullBktPres  = LpsLookupExtrap(UpdtTbl.LiftCylExt.Val,InitTbl.MachSpecificCfg.CalibTbl.SlowLowerFullBktLiftHt,
				                       InitTbl.MachSpecificCfg.CalibTbl.SlowLowerFullBktLiftPres,sizeof(InitTbl.MachSpecificCfg.CalibTbl.SlowLowerFullBktLiftHt)/sizeof(float));
        staticWtFactorStr = 0.0;
        staticWtMode      = 0;
	}
	else
	{
		emptyBktRaisePres = LpsLookupExtrap(UpdtTbl.LiftCylExt.Val,InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseEmptyBktLiftHt,
                                            InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseEmptyBktLiftPres,sizeof(InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseEmptyBktLiftHt)/sizeof(float));

		emptyBktLowerPres = LpsLookupExtrap(UpdtTbl.LiftCylExt.Val,InitTbl.MachSpecificCfg.CalibTbl.SlowLowerEmptyBktLiftHt,
                                            InitTbl.MachSpecificCfg.CalibTbl.SlowLowerEmptyBktLiftPres,sizeof(InitTbl.MachSpecificCfg.CalibTbl.SlowLowerEmptyBktLiftHt)/sizeof(float));

		fullBktRaisePres  = LpsLookupExtrap(UpdtTbl.LiftCylExt.Val,InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseFullBktLiftHt,
                                            InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseFullBktLiftPres,sizeof(InitTbl.MachSpecificCfg.CalibTbl.SlowRaiseFullBktLiftHt)/sizeof(float));

        fullBktLowerPres  = LpsLookupExtrap(UpdtTbl.LiftCylExt.Val,InitTbl.MachSpecificCfg.CalibTbl.SlowLowerFullBktLiftHt,
                                            InitTbl.MachSpecificCfg.CalibTbl.SlowLowerFullBktLiftPres,sizeof(InitTbl.MachSpecificCfg.CalibTbl.SlowLowerFullBktLiftHt)/sizeof(float));

        if (!(staticWtMode))
        {
           staticWtFactorOlFilt = staticWtFactorStr;
           staticWtMode = 1;
        }

        staticWtFactorOlFilt += ((InitTbl.ExecRate)/staticWtFactorTau) * (staticWtFactorOlRaw - staticWtFactorOlFilt);
        staticWtFactorCurr    = staticWtFactorOlFilt;

        emptyBktPres = ((emptyBktRaisePres - emptyBktLowerPres) * staticWtFactorCurr) + emptyBktLowerPres;
        fullBktPres  = ((fullBktRaisePres  -  fullBktLowerPres) * staticWtFactorCurr) + fullBktLowerPres;
	}

	/* Determining Instantaneous Weight based on calibration payload weight */
    if(fullBktPres > emptyBktPres)
     {
       	instRawWtSlope        = (InitTbl.MachSpecificCfg.CalibTbl.Calwt / (fullBktPres - emptyBktPres));
       	wt.Val  = (instRawWtSlope * (LpsWrk.LiftCylPres - emptyBktPres));
       	wt.Stat = LPS_INST_RAW_WT_STATUS_OK;
     }
    else
     {
    	wt.Val = 0.0;
    	wt.Stat = LPS_INST_RAW_WT_STATUS_BAD;
     }

  return wt.Val;

}

/******************************************************************************
CLASS NAME:LPSTest
DESCRIPTION:The LPSTest class is the test fixture for test the LPS library
 Note :
	1. The current behavior of the LPS Weighing Lib, not checking for out of range values

PARAMETER DESCRIPTION: NULL
RETURN VALUE: expDiffPres
*******************************************************************************/
// The fixture for testing class LPSTest.

class LPSTest : public ::testing::Test {

 protected:
	//set the default values for all test cases
	int setDefaultValues(std::string CalibrationPath, std::string MachSpecificPath, std::string RawInputPath)
	{
		int readStatus = 0;

		if(readCalibrationData(CalibrationPath) != 0)
			readStatus = MINUS_ONE;

		if(readRawInputData(RawInputPath) != 0)
			readStatus = MINUS_ONE;

		if(readMachineSpecificData(MachSpecificPath) != 0)
			readStatus = MINUS_ONE;
		
	    return readStatus;
	}
  // Objects declared here can be used by all tests in the test case for DiffPressureTest.

};


TEST_F(LPSTest, LPSTest1)
{
	int result;
	float DumpWtBuf;
	InitTbl.DumpWtBuffer.PtrDumpWtBuffer = &DumpWtBuf;
	InitTbl.DumpWtBuffer.bufferSize      = sizeof(DumpWtBuf);
    // this function will set data into InitTbl struct
	result =  setDefaultValues("calibrationData3.csv", "machineSpecData3.csv", "rawInputData3.csv");
    EXPECT_EQ(result, 0);
    LpsInitErrorTypes_t res=LpsInit(&InitTbl);
    EXPECT_EQ(res, LPS_INIT_SUCCESS);

    LpsInstWtRaw_t Wt;
    LpsUpdtErrorTypes_t ret, expectedResponse;
    float expDiffPres; //actualDiffPressure;
    float expectedWeight;
    float hePress;
    float rePress;
    float cylExt;
    float cylVel;
    float oilTemp;

    for(hePress=6000;hePress<=6500;hePress+=100)
    {
        for(rePress=3000;rePress<=3500;rePress+=100)
        {
            for(cylExt=0;cylExt<=100;cylExt+=20)
            {
                for(cylVel=0;cylVel<=100;cylVel+=20)
                {
                    for(oilTemp=-20;oilTemp<=80;oilTemp+=20)
                    {
                    	//set the inputs
						UpdtTbl.LiftCylHePres.Val = hePress;
						UpdtTbl.LiftCylRePres.Val = rePress;
						UpdtTbl.LiftCylExt.Val = cylExt;
						UpdtTbl.LiftCylVel.Val = cylVel;
						UpdtTbl.HydOilTemp.Val = oilTemp;
                        ret = LpsUpdt(&UpdtTbl);

                        expectedResponse = expResponseCalc();    // new function for Alternative flows
                        EXPECT_EQ(expectedResponse, ret);

                        expDiffPres = expDiffPressureCalc(); // this function uses UpdtTbl to calc Expected Diff.Pressure
                        EXPECT_NEAR (expDiffPres, LpsWrk.LiftCylPres,0.02);

                        Wt = LpsGetRawInstWt();
                        expectedWeight=expWeightCalc(); // new function using UpdtTbl values to calculate Expected InstWeight
                        EXPECT_NEAR (expectedWeight, Wt.Val, 0.1);
                    }
                }
            }
        }
    }
}

//InitTbl error sinario test case
TEST_F(LPSTest, LPSTest2)
{
	LpsInitTbl_t *InitTbl_1 = NULL;
	LpsInitErrorTypes_t res;
	int result;
	float DumpWtBuf;
    // check whether lib is giving NULL error
    res = LpsInit(InitTbl_1);
    EXPECT_EQ(res, LPS_INIT_CONFIG_ERROR);

    // check whether lib is giving status  error
	result =  setDefaultValues("calibrationData3.csv", "machineSpecData3.csv", "rawInputData3.csv");
    EXPECT_EQ(result, 0);
    InitTbl.InstallStat = FALSE;
    res = LpsInit(&InitTbl);
    EXPECT_EQ(res, LPS_INIT_DISABLED);

    InitTbl.InstallStat = TRUE;
    InitTbl.ExecRate = 0;
    res=LpsInit(&InitTbl);
    EXPECT_EQ(res, LPS_INIT_CONFIG_ERROR);

	InitTbl.ExecRate = 2;
	InitTbl.DumpWtBuffer.PtrDumpWtBuffer = NULL;
	res=LpsInit(&InitTbl);
	EXPECT_EQ(res, LPS_INIT_FAIL);
	InitTbl.DumpWtBuffer.PtrDumpWtBuffer = &DumpWtBuf;
	
   //this function will set data into InitTbl struct
    result =  setDefaultValues("calibrationData.csv", "machineSpecData5.csv", "rawInputData4.csv");
     EXPECT_EQ(result, -1);

      //this function will set data into InitTbl struct
    result =  setDefaultValues("calibrationData10.csv", "machineSpecData3.csv", "rawInputData3.csv");
     EXPECT_EQ(result, -1);

      //this function will set data into InitTbl struct
    result =  setDefaultValues("calibrationData3.csv", "machineSpecData3.csv", "rawInputData10.csv");
    EXPECT_EQ(result, -1);
}


//UpdtTbl error sinario test case
TEST_F(LPSTest, LPSTest3)
{
	int result;

   //  this function will set data into InitTbl struct
	result =  setDefaultValues("calibrationData3.csv", "machineSpecData3.csv", "rawInputData3.csv");
    EXPECT_EQ(result, 0);

	 //this function will check whether updtTbl is  NULL table or not
	LpsUpdtErrorTypes_t res;
	LpsUpdtTbl_t *UpdtTbl_1 = NULL;
	res = LpsUpdt(UpdtTbl_1);
	EXPECT_EQ(res, LPS_UPDT_INPUT_ERROR);

	 //this function will check init status
	res = LpsUpdt(&UpdtTbl);
	EXPECT_EQ(res, LPS_UPDT_NOT_INIT);

	 //this function will check channel status
	LpsInitErrorTypes_t res1 = LpsInit(&InitTbl);
	EXPECT_EQ(res1, LPS_INIT_SUCCESS);
	
	UpdtTbl.LiftCylExt.Stat = LPS_CYL_EXT_STAT_BAD;
	res = LpsUpdt(&UpdtTbl);
	EXPECT_EQ(res, LPS_UPDT_FAIL);

    //error in expectedResponse

    LpsUpdtErrorTypes_t expectedResponse = expResponseCalc();    // new function for Alternative flows
    EXPECT_EQ(expectedResponse, LPS_UPDT_FAIL);

    LpsWrk.InitErr = LPS_INIT_FAIL;
    expectedResponse = expResponseCalc();    // new function for Alternative flows
    EXPECT_EQ(expectedResponse,LPS_UPDT_NOT_INIT);
    
}

//test the lib if rodEndPressure>HePressure,and change oil type ,for code coverage and see the behaver of library
TEST_F(LPSTest, LPSTest4)
{
	int result;
   //  this function will set data into InitTbl struct
	result =  setDefaultValues("calibrationData3.csv", "machineSpecData3.csv", "rawInputData3.csv");
   EXPECT_EQ(result, 0);
	InitTbl.MachSpecificCfg.LiftCylBoreDia = 45;
	InitTbl.MachSpecificCfg.LiftCylRodDia  = 60;
    InitTbl.MachSpecificCfg.HydOilType =LPS_OIL_TYPE_SAE_0W20;
    LpsInitErrorTypes_t res=LpsInit(&InitTbl);
   EXPECT_EQ(res, LPS_INIT_SUCCESS);

    LpsInstWtRaw_t Wt;
    LpsUpdtErrorTypes_t ret, expectedResponse;
    float expDiffPres; //float actualDiffPressure;
    float expectedWeight;
    float hePress;
    float rePress;
    float cylExt;
    float cylVel ;
    float oilTemp;

    for(hePress=3000;hePress<=3100;hePress+=100)
    {
        for(rePress=6000;rePress<=6100;rePress+=100)
        {
            for(cylExt=-100;cylExt<=100;cylExt+=20)
            {
                for(cylVel=-60;cylVel<=40;cylVel+=10)
                {
                    for(oilTemp=-20;oilTemp<=80;oilTemp+=20)
                    {
                    	//set the inputs
						UpdtTbl.LiftCylHePres.Val = hePress;
						UpdtTbl.LiftCylRePres.Val = rePress;
						UpdtTbl.LiftCylExt.Val = cylExt;
						UpdtTbl.LiftCylVel.Val = cylVel;
						UpdtTbl.HydOilTemp.Val = oilTemp;
                       ret = LpsUpdt(&UpdtTbl);

                        expectedResponse = expResponseCalc();    // new function for Alternative flows
                      EXPECT_EQ(expectedResponse, ret);

                       expDiffPres=expDiffPressureCalc(); // this function uses UpdtTbl to calc Expected Diff.Pressure
                       EXPECT_NEAR (expDiffPres,LpsWrk.LiftCylPres,0.02);

                       Wt = LpsGetRawInstWt();
                        expectedWeight=expWeightCalc(); // new function using UpdtTbl values to calculate Expected InstWeight
                        EXPECT_NEAR (expectedWeight, Wt.Val, 0.1);
                    }
                }
            }
        }
    }
}




TEST_F(LPSTest, LPSTest5)
{
	int result;
    // this function will set data into InitTbl struct
	result =  setDefaultValues("calibrationData3.csv", "machineSpecData3.csv", "rawInputData3.csv");
    EXPECT_EQ(result, 0);

    InitTbl.MachSpecificCfg.CalibTbl.EmptyBktSlowRaiseSpd = 30;
	InitTbl.MachSpecificCfg.CalibTbl.EmptyBktFastRaiseSpd = 30;
	InitTbl.MachSpecificCfg.CalibTbl.FullBktSlowRaiseSpd  = 30;
	InitTbl.MachSpecificCfg.CalibTbl.FullBktFastRaiseSpd  = 30;

    LpsInitErrorTypes_t res=LpsInit(&InitTbl);
    EXPECT_EQ(res, LPS_INIT_SUCCESS);

    LpsInstWtRaw_t Wt;
    LpsUpdtErrorTypes_t ret, expectedResponse;
    float expDiffPres;//float actualDiffPressure;
    float expectedWeight;
    float hePress;
    float rePress;
    float cylExt;
    float cylVel;
    float oilTemp;

    

    for(hePress=3000;hePress<=3500;hePress+=100)
    {
        for(rePress=6000;rePress<=6500;rePress+=100)
        {
            for(cylExt=0;cylExt<=100;cylExt+=20)
            {
               for(cylVel=-60;cylVel<=40;cylVel+=10)
                {
                    for(oilTemp=-100;oilTemp<=80;oilTemp+=20)
                    {
                    	//set the inputs
						UpdtTbl.LiftCylHePres.Val = hePress;
						UpdtTbl.LiftCylRePres.Val = rePress;
						UpdtTbl.LiftCylExt.Val = cylExt;
						UpdtTbl.LiftCylVel.Val = cylVel;
						UpdtTbl.HydOilTemp.Val = oilTemp;
                        ret = LpsUpdt(&UpdtTbl);

                        expectedResponse = expResponseCalc();    // new function for Alternative flows
                        EXPECT_EQ(expectedResponse, ret);

                        expDiffPres=expDiffPressureCalc(); // this function uses UpdtTbl to calc Expected Diff.Pressure
                        EXPECT_NEAR (expDiffPres,LpsWrk.LiftCylPres,0.02);

                        Wt = LpsGetRawInstWt();
                        expectedWeight=expWeightCalc(); // new function using UpdtTbl values to calculate Expected InstWeight
                        EXPECT_NEAR (expectedWeight, Wt.Val, 0.1);
                    }
               }
            }
        }
    }
}

TEST_F(LPSTest, LPSTest6)
{
	int result;
    // this function will set data into InitTbl struct
	result =  setDefaultValues("calibrationData3.csv", "machineSpecData3.csv", "rawInputData3.csv");
    EXPECT_EQ(result, 0);

    InitTbl.MachSpecificCfg.CalibTbl.EmptyBktSlowRaiseSpd = 30;
	InitTbl.MachSpecificCfg.CalibTbl.EmptyBktFastRaiseSpd = 30;
	InitTbl.MachSpecificCfg.CalibTbl.FullBktSlowRaiseSpd  = 30;
	InitTbl.MachSpecificCfg.CalibTbl.FullBktFastRaiseSpd  = 30;

    LpsInitErrorTypes_t res=LpsInit(&InitTbl);
    EXPECT_EQ(res, LPS_INIT_SUCCESS);

    LpsInstWtRaw_t Wt;
    LpsUpdtErrorTypes_t ret, expectedResponse;
    float expDiffPres; //actualDiffPressure;
    float expectedWeight;
    float hePress;
    float rePress;
    float cylExt;
    float cylVel=-10;
    float oilTemp;

    

    for(hePress=3000;hePress<=3500;hePress+=100)
    {
        for(rePress=6000;rePress<=6500;rePress+=100)
        {
            for(cylExt=0;cylExt<=100;cylExt+=20)
            {
              
                    for(oilTemp=-100;oilTemp<=80;oilTemp+=20)
                    {
                    	//set the inputs
						UpdtTbl.LiftCylHePres.Val = hePress;
						UpdtTbl.LiftCylRePres.Val = rePress;
						UpdtTbl.LiftCylExt.Val = cylExt;
						UpdtTbl.LiftCylVel.Val = cylVel;
						UpdtTbl.HydOilTemp.Val = oilTemp;
                        ret = LpsUpdt(&UpdtTbl);

                        expectedResponse = expResponseCalc();    // new function for Alternative flows
                        EXPECT_EQ(expectedResponse, ret);

                        expDiffPres=expDiffPressureCalc(); // this function uses UpdtTbl to calc Expected Diff.Pressure
                        EXPECT_NEAR (expDiffPres,LpsWrk.LiftCylPres,0.02);

                        Wt = LpsGetRawInstWt();
                        expectedWeight=expWeightCalc(); // new function using UpdtTbl values to calculate Expected InstWeight
                        EXPECT_NEAR (expectedWeight, Wt.Val, 0.1);
                    }
                
            }
        }
    }
}
