/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LPSCommonLookUpTblUtility.h
DESCRIPTION:
*******************************************************************************/
#ifndef  __LPS_COMMON_LOOKUP_TBL_UTILITY_H__
#define __LPS_COMMON_LOOKUP_TBL_UTILITY_H__
/*******************************************************************************
** -- #Include's --
*******************************************************************************/

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/


/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
#if defined (__cplusplus)
extern "C"
{
#endif

extern float_32 LpsLookup(const float_32 input, const float_32 x[], const float_32 y[], const unsigned_8 numPoints);
extern float_32 LpsLookupExtrap(const float_32 input, const float_32 x[], const float_32 y[], const unsigned_8 numPoints);
extern float_32 LpsLookup2d(const float_32 inColumnValue, const float_32 inRowValue, const float_32 columnAxis[], const float_32 rowAxis[], const float_32 outData[], const int numColumns, const int numRows);
extern unsigned_32 LpsCommonGetTimeDiffSec(unsigned_32 a, unsigned_32 b);

#if defined (__cplusplus)
}
#endif

#endif /* #ifndef __LPS_COMMON_LOOKUP_TBL_UTILITY_H__ */
