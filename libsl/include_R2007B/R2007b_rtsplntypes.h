#ifndef RTSPLNTYPES_H
#define RTSPLNTYPES_H

/* 
 * File: rtsplntypes.h
 * 
 * Abstract: 
 *
 *   Typedefs for spline lookup table algorithms.
 *
 *   Copyright 1994-2006 The MathWorks, Inc.
 *
 *   $Revision: 1.1.6.1 $
 *
 */

#include "R2007b_rtwtypes.h"

/***************************************************************
 *                n-D Table Work Data Structures               *
 ***************************************************************/

typedef struct rt_LUTnWork_tag 
{
    const uint32_T  *dimSizes;
    void     *tableData;
    void    **bpDataSet;
    uint32_T  *bpIndex;
    void     *bpLambda;
    const uint32_T  *maxIndex;
} rt_LUTnWork;

typedef struct rt_LUTSplineWork_tag 
{
    rt_LUTnWork *TWork;
    void        *yyA;
    void        *yyB;
    void        *yy2;
    void        *up;
    void        *y2;
    const uint32_T     *numYWorkElts;
} rt_LUTSplineWork;

/* double precision variant */

typedef struct rt_LUTnWorkd_tag 
{
    const uint32_T  *dimSizes;
    const real_T   *tableData;
    real_T  **bpDataSet;
    uint32_T  *bpIndex;
    real_T   *bpLambda;
    const uint32_T  *maxIndex;
} rt_LUTnWorkd;

typedef struct rt_LUTSplineWorkd_tag 
{
    rt_LUTnWorkd  *TWork;
    real_T        *yyA;
    real_T        *yyB;
    real_T        *yy2;
    real_T        *up;
    real_T        *y2;
    const uint32_T *numYWorkElts;
} rt_LUTSplineWorkd;

/* single precision variant */

typedef struct rt_LUTnWorkf_tag 
{
    const uint32_T   *dimSizes;
    const real32_T  *tableData;
    real32_T **bpDataSet;
    uint32_T   *bpIndex;
    real32_T  *bpLambda;
    const uint32_T   *maxIndex;
} rt_LUTnWorkf;

typedef struct rt_LUTSplineWorkf_tag 
{
    rt_LUTnWorkf  *TWork;
    real32_T      *yyA;
    real32_T      *yyB;
    real32_T      *yy2;
    real32_T      *up;
    real32_T      *y2;
    const uint32_T *numYWorkElts;
} rt_LUTSplineWorkf;

#endif  /* RTSPLNTYPES_H */
