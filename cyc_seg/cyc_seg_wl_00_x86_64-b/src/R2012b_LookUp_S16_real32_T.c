/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: A:\ivy\cpm_cs_wl_00_2012b_dev1\lib\lib_info_products\cyc_seg_wl\wl_00\pkg_arch\slprj\cat_PkgArch\_sharedutils\R2012b_LookUp_S16_real32_T.c
 **
 ** Real-Time Workshop code generated for Simulink model LIBINFO_WL_00.
 **
 ** Model version                        : 1.118
 ** Real-Time Workshop file version      : 8.3 (R2012b) 20-Jul-2012
 ** TLC version                          : 8.3 (Jul 21 2012)
 ** CATutils_MatLab version              : CATUTILS_MATLAB_4.3.3
 **
 ******************************************************************************/

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
#include "R2012b_rtwtypes.h"
#include "R2012b_rtw_shared_utils.h"

/* Lookup Utility R2012b_LookUp_S16_real32_T */
void R2012b_LookUp_S16_real32_T(int16_T *pY, const int16_T *pYData, real32_T u, const
  real32_T *pUData, uint32_T iHi)
{
  uint32_T iLeft;
  uint32_T iRght;
  R2012b_BINARYSEARCH_real32_T( &(iLeft), &(iRght), u, pUData, iHi);

  {
    real_T lambda;
    if (pUData[iRght] > pUData[iLeft] ) {
      real_T num;
      real_T den;
      den = pUData[iRght];
      den = den - pUData[iLeft];
      num = u;
      num = num - pUData[iLeft];
      lambda = num / den;
    } else {
      lambda = 0.0;
    }

    {
      real_T yLeftCast;
      real_T yRghtCast;
      yLeftCast = ((real_T)pYData[iLeft]) * 0.015625;
      yRghtCast = ((real_T)pYData[iRght]) * 0.015625;
      yLeftCast += lambda * ( yRghtCast - yLeftCast );
      (*pY) = (int16_T)floor(yLeftCast * 64.0);
    }
  }
}
