/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: toa_wl00_private.h
 **
 ** Real-Time Workshop code generated for Simulink model toa_wl00.
 **
 ** Model version                        : 1.44
 ** Real-Time Workshop file version      : 8.13 (R2017b) 24-Jul-2017
 ** TLC version                          : 8.13 (Jul 25 2017)
 ** CATutils_MatLab version              : CATUTILS_MATLAB_4.6.1
 **
 ******************************************************************************/

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#ifndef RTW_HEADER_toa_wl00_private_h_
#define RTW_HEADER_toa_wl00_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "toa_wl00.h"

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if 0

/* Skip this size verification because of preprocessor limitation */
#if ( ULONG_MAX != (0xFFFFFFFFFFFFFFFFUL) ) || ( LONG_MAX != (0x7FFFFFFFFFFFFFFFL) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif
#endif

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/
extern void toa_wl00_MATLABFunction(real_T rtu_timestep, real_T
  rtu_lowPassFilterCutoffHz, real_T *rty_lowPassFilterFactor);
extern void toa_wl00_Filter_Init(real32_T *rty_filtered, rtDW_Filter_toa_wl00
  *localDW);
extern void toa_wl00_Filter(real32_T rtu_raw, boolean_T rtu_reset, real32_T
  rtu_ts, real32_T rtu_cf, real32_T *rty_filtered, rtDW_Filter_toa_wl00 *localDW);
extern void toa_wl00_MATLABFunction_nat1_Init(rtDW_MATLABFunction_toa_wl00_flu5 *
  localDW);
extern void toa_wl00_MATLABFunction_fw1r(real32_T rtu_newSample, real_T
  rtu_filterFactor, boolean_T rtu_reset, real32_T rtu_resetVariance, real32_T
  *rty_meanEst, real32_T *rty_stdevEst, rtDW_MATLABFunction_toa_wl00_flu5
  *localDW);
extern void toa_wl00_TwoSidedStDevfromBound(real32_T rtu_confidence, real32_T
  rtu_bound, real32_T *rty_stdev);
extern void toa_wl00_OneSidedConfidenceLimit(real_T rtu_confidence, real32_T
  rtu_stdev, real32_T *rty_bound);
extern void toa_wl00_TwoSidedConfidenceLimit(real_T rtu_confidence, real32_T
  rtu_stdev, real32_T *rty_bound);

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
#endif                                 /* RTW_HEADER_toa_wl00_private_h_ */
