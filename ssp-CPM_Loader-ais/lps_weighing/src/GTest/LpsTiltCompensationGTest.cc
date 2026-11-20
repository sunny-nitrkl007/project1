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

extern LpsWrkTbl_t LpsWrk;
LpsInitTbl_t GT_InitTbl;
LpsUpdtTbl_t GT_UpdtTbl;

static const float lift_cyl_ext_pct_axis[] = {0, 13.205282, 26.770708, 44.417767, 59.903962, 68.667467, 74.909964, 80.072029, 84.393758, 87.995198, 91.116447, 93.877551, 96.278511, 98.319328, 100}; 
static const float tilt_cyl_ext_pct_axis[] = {0, 5.925926, 11.111111, 15.925926, 20.37037, 24.444444, 28.333333, 32.037037, 35.555556, 38.888889, 42.037037, 45.185185, 48.518519, 52.592593, 58.703704, 67.407407, 75, 82.777778, 91.851852, 100}; 
static const float tilt_comp_gain_data[] = { 
    -67.255123, -131.090664, -99.496445, 40.616837, 194.023328, 225.611093, 170.015079, 55.717142, -88.073357, -242.852856, -410.566582, -598.242022, -809.531418, -1047.332864, -1311.270308, 
    -100.212826, -151.23269, -118.831976, 18.905857, 201.333501, 295.382853, 305.506475, 235.471871, 104.872104, -54.096753, -228.149788, -416.290681, -618.42106, -835.224302, -1064.132474, 
    -116.733373, -162.704203, -133.025089, -4.720368, 180.660382, 309.058451, 377.130002, 372.559868, 288.500021, 146.736368, -29.257412, -225.071497, -431.408093, -644.940536, -862.145727, 
    -125.378543, -169.509224, -143.540468, -26.596386, 148.964724, 289.422402, 394.489998, 450.628522, 433.227392, 339.923476, 185.607529, -9.334155, -223.088298, -442.500511, -659.849899, 
    -129.477329, -173.213631, -150.919929, -44.921219, 115.802165, 254.280442, 375.68224, 472.506094, 516.866181, 488.798639, 384.944786, 215.442897, 5.551978, -219.698817, -443.044274, 
    -130.912862, -174.840936, -155.794238, -59.419531, 85.734544, 215.398112, 339.226149, 456.529024, 544.15375, 576.462169, 537.05712, 419.029084, 236.434288, 17.785116, -208.896259, 
    -130.746698, -175.069157, -158.865691, -70.965168, 59.149787, 177.060431, 295.472948, 419.049552, 531.668289, 609.75893, 632.878876, 581.610128, 451.850112, 262.576938, 45.688982, 
    -129.510285, -174.248865, -160.459292, -79.850643, 36.587886, 142.08546, 251.131657, 371.812625, 494.419206, 600.621402, 672.411155, 686.446488, 624.186082, 487.95502, 302.260815, 
    -127.554719, -172.642638, -160.860514, -86.446419, 17.961529, 111.601883, 209.847556, 322.6088, 445.016665, 564.250134, 667.379278, 733.514495, 737.771251, 667.904488, 534.110273, 
    -125.118712, -170.451262, -160.313253, -91.126686, 2.894897, 85.790321, 173.245306, 275.890436, 392.142135, 513.741382, 632.946666, 734.109082, 792.661503, 788.331348, 717.439019, 
    -122.369576, -167.831458, -159.023209, -94.236232, -9.089956, 64.355721, 141.76563, 233.811475, 340.980306, 458.379856, 582.480733, 703.158256, 799.675356, 849.790452, 840.559212, 
    -119.233917, -164.711211, -157.026933, -96.160619, -19.006658, 45.786843, 113.666877, 194.938765, 291.368323, 400.506869, 522.001639, 650.630838, 770.832033, 862.291597, 907.627557, 
    -115.530139, -160.888424, -154.184127, -97.00004, -27.407364, 29.133679, 87.711247, 157.979239, 242.428846, 340.3441, 453.603991, 580.952465, 712.188851, 831.145622, 920.011311, 
    -110.504345, -155.515822, -149.739177, -96.485568, -35.000524, 12.691452, 61.147809, 119.052522, 189.206304, 272.118998, 371.105999, 487.979089, 617.75094, 749.796293, 869.12298, 
    -101.979936, -146.02816, -141.148331, -92.843389, -41.553245, -4.827837, 31.026927, 73.186205, 124.283804, 185.531517, 260.681764, 353.350055, 463.109584, 585.624402, 711.709651, 
    -87.741334, -129.39608, -124.944017, -82.397867, -42.654945, -17.709606, 4.856252, 30.32545, 60.67169, 97.068594, 142.388042, 199.888683, 271.06451, 355.572963, 449.866299, 
    -72.992052, -111.35411, -106.661198, -68.747183, -37.444069, -20.174572, -5.793638, 9.633823, 27.507159, 48.696064, 75.068599, 108.809864, 151.266903, 202.916315, 262.399556, 
    -54.904789, -88.177057, -82.919558, -50.596963, -27.640708, -16.705286, -8.448444, -0.145161, 9.105774, 19.855437, 33.132584, 50.128416, 71.66026, 98.169656, 129.199875, 
    -27.989371, -50.770504, -45.401573, -24.1157, -12.451422, -7.920854, -4.906675, -2.123454, 0.817035, 4.139181, 8.19225, 13.365802, 19.941549, 28.097641, 37.742985, 
    3.483616, 11.061913, 8.155074, 3.057972, 1.411075, 0.908177, 0.607072, 0.345292, 0.077317, -0.221811, -0.586287, -1.05346, -1.651306, -2.398773, -3.290139 
};
static const float tilt_comp_gain_data_zeroed[] = { 
    0.5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
};

LpsTiltMap_t Map = { (int)(sizeof( lift_cyl_ext_pct_axis ) / sizeof( lift_cyl_ext_pct_axis[0])), 
					(int)( sizeof( tilt_cyl_ext_pct_axis ) / sizeof( tilt_cyl_ext_pct_axis[0] ) ), 
					(const float*)&lift_cyl_ext_pct_axis, (const float*)&tilt_cyl_ext_pct_axis, 
					(const float*)&tilt_comp_gain_data_zeroed };

unsigned char ArgStatus;
unsigned char GetArgStatus(void)
{
	return ArgStatus;
}

float_32 ArgCheck(const float_32 inColumnValue, const float_32 inRowValue, const float_32 columnAxis[], const float_32 rowAxis[], const float_32 outData[], const int numColumns, const int numRows)
{
	if ((columnAxis == lift_cyl_ext_pct_axis) && (rowAxis == tilt_cyl_ext_pct_axis) && (outData == tilt_comp_gain_data_zeroed))
	{
		ArgStatus = 1;
	}
}

void SetDefaultValuesTilt(void)
{
	LpsWrk.InitTbl.MachSpecificCfg.TiltComp.TiltCompGainScalar 		= 0;
	LpsWrk.InitTbl.MachSpecificCfg.TiltComp.TiltCompEmptyBktWtGain 	= 0.5;
	LpsWrk.InitTbl.MachSpecificCfg.TiltComp.TiltCompMaxGain 		= 1.0;
	LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.EmptyBktWtEst 			= 0.5;
	LpsWrk.InitTbl.MachSpecificCfg.TiltMap 							= Map;
	LpsWrk.UpdtTbl 													= &GT_UpdtTbl;
	GT_UpdtTbl.TiltCylExt.Val 										= 0.0;
	GT_UpdtTbl.TiltCylExt.Stat 										= LPS_CYL_EXT_STAT_OK ;
	GT_UpdtTbl.LiftCylExt.Val 										= 0.0;
	GT_UpdtTbl.LiftCylExt.Stat 										= LPS_CYL_EXT_STAT_OK;	
	GT_UpdtTbl.LiftCylHePres.Stat 									= LPS_PRES_STATUS_OK;
	GT_UpdtTbl.LiftCylRePres.Stat 									= LPS_PRES_STATUS_OK;
	GT_UpdtTbl.LiftCylVel.Stat 										= LPS_CYL_VEL_STATUS_OK;
	GT_UpdtTbl.HydOilTemp.Stat 										= LPS_HYD_OIL_TEMP_STATUS_OK;
}

TEST(TiltTest,LPSWeighingTest)
{		
	SetDefaultValuesTilt();
	 
	LpsWrk.InstWtRaw.Val = 10.0;
		
	//Test case 1           Tilt Compensation gain factor is 0
	LpsWrk.InstWtRaw.Val = LpsTiltCompensation(LpsWrk.InstWtRaw.Val, 0.02);
	EXPECT_NEAR(10.00, LpsWrk.InstWtRaw.Val,0);
	
	//Test Case 2           Tilt Compensation gain factor is 0.5
	LpsWrk.InitTbl.MachSpecificCfg.TiltComp.TiltCompGainScalar = 0.5;
	LpsWrk.InstWtRaw.Val = 10.0;
	LpsWrk.InstWtRaw.Val = LpsTiltCompensation(LpsWrk.InstWtRaw.Val, 0.02);
	EXPECT_NEAR(10.05, LpsWrk.InstWtRaw.Val,0.01);
	
	//Test Case 3           Instantaneous Raw Weight Slope is 4.5 
	LpsWrk.InstWtRaw.Val = LpsTiltCompensation(LpsWrk.InstWtRaw.Val, 4.5);
	EXPECT_NEAR(10.05, LpsWrk.InstWtRaw.Val,0.01);
	
	//Test Case 4           Setting Instantaneous Raw Weight Slope as 110 and Instantaneous Raw Weight Slope as -0.02 to get negative tiltcompGain
	LpsWrk.InstWtRaw.Val = LpsTiltCompensation(LpsWrk.InstWtRaw.Val, -4.4);
	EXPECT_NEAR(4.9, LpsWrk.InstWtRaw.Val,0.01);	
			
	//Test case 5           
	LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.EmptyBktWtEst = 0;
	LpsWrk.InstWtRaw.Val = LpsTiltCompensation(LpsWrk.InstWtRaw.Val, 0.02);
	EXPECT_NEAR(4.9, LpsWrk.InstWtRaw.Val,0.01);
	
	//Test case 6          This case is to check weight when the Tilt map is NULL
	LpsWrk.InitTbl.MachSpecificCfg.CalibTbl.EmptyBktWtEst = 0.5;
	LpsWrk.InitTbl.MachSpecificCfg.TiltMap.ColumnAxis = NULL;
	LpsWrk.InitTbl.MachSpecificCfg.TiltMap.RowAxis = NULL;
	LpsWrk.InitTbl.MachSpecificCfg.TiltMap.Data = NULL;
	LpsWrk.InstWtRaw.Val = LpsTiltCompensation(LpsWrk.InstWtRaw.Val, 0.02);
	EXPECT_NEAR(4.9, LpsWrk.InstWtRaw.Val,0.01);
	
	//Test case 7          This case is to check weight when the Sensor status is BAD
	LpsWrk.UpdtTbl->LiftCylExt.Stat = LPS_CYL_EXT_STAT_BAD;
	LpsWrk.InitTbl.MachSpecificCfg.TiltMap.ColumnAxis = lift_cyl_ext_pct_axis;
	LpsWrk.InitTbl.MachSpecificCfg.TiltMap.RowAxis = tilt_cyl_ext_pct_axis;
	LpsWrk.InitTbl.MachSpecificCfg.TiltMap.Data = tilt_comp_gain_data_zeroed;
	LpsWrk.InstWtRaw.Val = LpsTiltCompensation(LpsWrk.InstWtRaw.Val, 0.02);
	EXPECT_NEAR(4.9, LpsWrk.InstWtRaw.Val,0.01);
	
	//Test case 8           this test case is to test all the agrugument  of Lookup2d fuction be in correct order
	ArgCheck(LpsWrk.UpdtTbl->LiftCylExt.Val,LpsWrk.UpdtTbl->TiltCylExt.Val,
                             LpsWrk.InitTbl.MachSpecificCfg.TiltMap.ColumnAxis,LpsWrk.InitTbl.MachSpecificCfg.TiltMap.RowAxis,
                             LpsWrk.InitTbl.MachSpecificCfg.TiltMap.Data,LpsWrk.InitTbl.MachSpecificCfg.TiltMap.NumColumns,
                             LpsWrk.InitTbl.MachSpecificCfg.TiltMap.NumRows);
	LpsWrk.InstWtRaw.Val = LpsTiltCompensation(LpsWrk.InstWtRaw.Val, 0.02);
	EXPECT_EQ(GetArgStatus(),1);
}
































