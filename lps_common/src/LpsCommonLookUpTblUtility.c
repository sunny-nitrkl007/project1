/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsCommonLookUpTblUtility.c
DESCRIPTION:This file provide utility functions for look up table functionality used
            commonly among all LPS libraries.
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#ifndef __LPS_COMMON_TYPE_DEF_H__
#include <LpsCommonTypeDef.h> 
#endif

#ifndef __LPS_COMMON_LOOKUP_TBL_UTILITY_H__
#include <LpsCommonLookUpTblUtility.h>
#endif
/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/

/******************************************************************************
FUNCTION NAME:LpsLookup
DESCRIPTION:This function provides basic 2D map lookup functionality
PARAMETER DESCRIPTION:
RETURN VALUE: output ->Map interpolated value
*******************************************************************************/
float_32 LpsLookup(const float_32 input, const float_32 x[], const float_32 y[], const unsigned_8 numPoints)
{
    float_32 output;
	float_32 diff;
    
	if (input <= x[0])
    {
        output = y[0];
    }
    else if (input >= x[numPoints - 1])
    {
        output = y[numPoints - 1];
    }
    else
    {
        unsigned_8 index;
        for (index = 1; index < numPoints; index++)
        {
            if (input <= x[index])
            {
                break;
            }
        }
        if (index < numPoints)
        {
			diff = (x[index] - x[index-1]);
			if(diff == 0)
			{
				output = 0.0;
			}
			else
			{
				output = (((y[index] - y[index-1]) / (diff)) * (input - x[index-1]) + y[index-1]);
			}
        }
        else
        {
            output = 0.0;
        }
    }

    return output;
}



/******************************************************************************
FUNCTION NAME:Lpslookup_extrap
DESCRIPTION:This function provides basic 2D map extrapolation functionality
PARAMETER DESCRIPTION:
RETURN VALUE:output-> extrapolated value
*******************************************************************************/
float_32 LpsLookupExtrap(const float_32 input, const float_32 x[], const float_32 y[], const unsigned_8 numPoints)
{
    float_32 output;
	float_32 diff;
	
    if (input <= x[0])
    {
        output = ((y[1] - y[0])/(x[1] - x[0]))*(input - x[0]) + y[0];
    }
    else if (input >= x[numPoints - 1])
    {
		diff = (x[numPoints - 1] - x[numPoints - 2]);
		if(diff == 0)
		{
			output = 0.0;	
		}
		else
		{
			output = (((y[numPoints - 1] - y[numPoints - 2])/ (diff))*(input - x[numPoints - 2]) + y[numPoints - 2]);
		}
    }
    else
    {
        output = LpsLookup(input, x, y, numPoints);
    }
    
    return output;
}

/******************************************************************************
FUNCTION NAME:LpsLookup2d
DESCRIPTION:This function provides basic 2D map lookup functionality
PARAMETER DESCRIPTION:
RETURN VALUE: output ->Map interpolated value
*******************************************************************************/
float_32 LpsLookup2d(const float_32 inColumnValue, const float_32 inRowValue,
                    const float_32 columnAxis[], const float_32 rowAxis[],
                    const float_32 outData[],
                    const int numColumns, const int numRows)
{
    int rowRangeStartIndex = 0;
    float_32 rowRangeRatio = 0.0;
    int columnRangeStartIndex = 0;
    float_32 columnRangeRatio = 0.0;

    float_32 lowerRowInterpValue;
    float_32 upperRowInterpValue;

    float_32 output;

    if ((0 == numRows) ||
        (0 == numColumns) ||
        (NULL == columnAxis) ||
        (NULL == rowAxis) ||
        (NULL == outData))
    {
        return 0;
    }

    /* Find the column range start index and ratio */
    if (inColumnValue <= columnAxis[0])
    {
        columnRangeStartIndex = 0;
        columnRangeRatio = 0.0;
    }
    else if (inColumnValue >= columnAxis[numColumns - 1])
    {
        columnRangeStartIndex = numColumns - 2;
        columnRangeRatio = 1.0;
    }
    else
    {
        int index;
		float_32 diff;
        for (index = 1; index < numColumns; index++)
        {
            if (inColumnValue <= columnAxis[index])
            {
				diff = (columnAxis[index] - columnAxis[index-1]);
				if(diff == 0)
				{
					columnRangeStartIndex = 0;
					columnRangeRatio = 0.0;
				}
				else
				{
					columnRangeRatio = ((inColumnValue - columnAxis[index-1]) / (diff));
					columnRangeStartIndex = index - 1;
					break;
				}
            }
        }
    }

    /* Find the row range start index and ratio */
    if (inRowValue <= rowAxis[0])
    {
        rowRangeStartIndex = 0;
        rowRangeRatio = 0.0;
    }
    else if (inRowValue >= rowAxis[numRows - 1])
    {
        rowRangeStartIndex = numRows - 2;
        rowRangeRatio = 1.0;
    }
    else
    {
        int index;
		float_32 diff;
        for (index = 1; index < numRows; index++)
        {
            if (inRowValue <= rowAxis[index])
            {
				diff = (rowAxis[index] - rowAxis[index-1]);
				if(diff == 0)
				{
					rowRangeStartIndex = 0;
					rowRangeRatio = 0.0;
				}
				else
				{
					rowRangeRatio = ((inRowValue - rowAxis[index-1]) / (diff));
					rowRangeStartIndex = index - 1;
					break;	
				}                
            }
        }
    }

    { /* Interpolate between columns for the lower row */
        float_32 lower = outData[numColumns*rowRangeStartIndex + columnRangeStartIndex];
        float_32 upper = outData[numColumns*rowRangeStartIndex + columnRangeStartIndex + 1];
        lowerRowInterpValue = (columnRangeRatio * (upper - lower)) + lower;
    }

    { /* Interpolate between columns for the upper row */
        float_32 lower = outData[numColumns*(rowRangeStartIndex + 1) + columnRangeStartIndex];
        float_32 upper = outData[numColumns*(rowRangeStartIndex + 1) + columnRangeStartIndex + 1];
        upperRowInterpValue = (columnRangeRatio * (upper - lower)) + lower;
    }

    output = (rowRangeRatio * (upperRowInterpValue - lowerRowInterpValue)) + lowerRowInterpValue;

    return output;
}

unsigned_32 LpsCommonGetTimeDiffSec(unsigned_32 a, unsigned_32 b)
{
    unsigned_32 diff = a - b;
    return diff;	
}
