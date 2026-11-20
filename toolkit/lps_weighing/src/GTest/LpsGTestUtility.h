/*
 * LpsGTestUtility.h
 *
 *  Created on: 29-Jul-2016
 *      Author: paneek
 */

#ifndef LPSGTESTUTILITY_H_
#define LPSGTESTUTILITY_H_

#ifndef __LPS_COMMON_TYPE_DEF_H__
#include <LPSCommonTypeDef.h>
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCommonStructures.h>
#endif

#ifndef  __LPS_COMMON_LOOKUP_TBL_UTILITY_H__
#include <LpsCommonLookUpTblUtility.h>
#endif

#ifndef __LPS_PUBLIC_H__
#include <LpsPublic.h>
#endif

#ifndef __LPS_PRIVATE_H__
#include <LpsPrivate.h>
#endif

#define EXC_RATE_SEC  0.02

typedef enum
{
	MOVE_UPWARDS= 0,
	MOVE_DOWNWARDS,
}bucket_mov;


unsigned_8 PosSimulation(float_32 ,float_32,bucket_mov,double);


#if defined (__cplusplus) //updated by Melvin for Gtest
extern "C"
{
#endif

#if defined (__cplusplus)

class LPSTest : public ::testing::Test
{
protected:
    int setDefaultValues(std::string CalibrationPath, std::string MachSpecificPath, std::string RawInputPath);
};

}
#endif	



#endif /* LPSGTESTUTILITY_H_ */
