/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: LIBINFO_WL_00_private.h
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
#ifndef RTW_HEADER_LIBINFO_WL_00_private_h_
#define RTW_HEADER_LIBINFO_WL_00_private_h_
#include "R2012b_rtwtypes.h"

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error "Code was generated for compiler with different sized uchar/char. Consider adjusting Emulation Hardware word size settings on the Hardware Implementation pane to match your compiler word sizes as defined in the compiler's limits.h header file. Alternatively, you can select 'None' for Emulation Hardware and select the 'Enable portable word sizes' option for ERT based targets, which will disable the preprocessor word size checks."
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error "Code was generated for compiler with different sized ushort/short. Consider adjusting Emulation Hardware word size settings on the Hardware Implementation pane to match your compiler word sizes as defined in the compilers limits.h header file. Alternatively, you can select 'None' for Emulation Hardware and select the 'Enable portable word sizes' option for ERT based targets, this will disable the preprocessor word size checks."
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error "Code was generated for compiler with different sized uint/int. Consider adjusting Emulation Hardware word size settings on the Hardware Implementation pane to match your compiler word sizes as defined in the compilers limits.h header file. Alternatively, you can select 'None' for Emulation Hardware and select the 'Enable portable word sizes' option for ERT based targets, this will disable the preprocessor word size checks."
#endif

#if 0

/* Skip this size verification because of preprocessor limitation */
#if ( ULONG_MAX != (0xFFFFFFFFFFFFFFFFUL) ) || ( LONG_MAX != (0x7FFFFFFFFFFFFFFFL) )
#error "Code was generated for compiler with different sized ulong/long. Consider adjusting Emulation Hardware word size settings on the Hardware Implementation pane to match your compiler word sizes as defined in the compilers limits.h header file. Alternatively, you can select 'None' for Emulation Hardware and select the 'Enable portable word sizes' option for ERT based targets, this will disable the preprocessor word size checks."
#endif
#endif

#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else

/* Check for inclusion of an incorrect version of rtwtypes.h */
#ifndef RTWTYPES_ID_C08S16I32L64N64F1
#error This code was generated with a different "rtwtypes.h" than the file included
#endif                                 /* RTWTYPES_ID_C08S16I32L64N64F1 */
#endif                                 /* TMWTYPES_PREVIOUSLY_INCLUDED */
#endif                                 /* __RTWTYPES_H__ */

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/
extern void LIBINFO_WL_DumpThresholdCapture(dt_libinfo_modulation_pct rtu_0,
  dt_libinfo_modulation_pct rtu_tiltCylExtDelta, dt_libinfo_modulation_pct
  *rty_dumpCylExtCapture, dt_libinfo_modulation_pct *rty_dumpCylExtThreshold);
extern void LIBINFO_WL_RackThresholdCapture(dt_libinfo_modulation_pct rtu_0,
  dt_libinfo_modulation_pct rtu_tiltCylExtDelta, dt_libinfo_modulation_pct
  *rty_rackCylExtCapture, dt_libinfo_modulation_pct *rty_rackCylExtThreshold);
extern void LIBINFO_WL_00_x0_is_min(dt_libinfo_MachSpdKPH_Signed rtu_x1,
  dt_libinfo_MachSpdKPH_Signed rtu_x2, dt_libinfo_MachSpdKPH_Signed *rty_out);
extern void LIBINFO_WL_00_x1_is_min(dt_libinfo_MachSpdKPH_Signed rtu_x0,
  dt_libinfo_MachSpdKPH_Signed rtu_x2, dt_libinfo_MachSpdKPH_Signed *rty_out);
extern void LIBINFO_WL_00_x2_is_min(dt_libinfo_MachSpdKPH_Signed rtu_x0,
  dt_libinfo_MachSpdKPH_Signed rtu_x1, dt_libinfo_MachSpdKPH_Signed *rty_out);
extern void LIBINFO_WL_00_BoundedSelection(boolean_T rtu_0, const
  dt_libinfo_Unsigned8 rtu_vector[7], int32_t rtu_indexOneBased,
  dt_libinfo_Unsigned8 *rty_value);
extern void LIBINFO_WL_00_AppendFunc(const real32_T rtu_inAccumulatorBuffer[10],
  int32_t rtu_bufferDepth, real32_T rty_outAccumulatorBuffer[10]);
extern void LIBINFO_WL_00_AppendFunc_ddqd(const dt_libinfo_Unsigned32
  rtu_inAccumulatorBuffer[10], int32_t rtu_bufferDepth, dt_libinfo_Unsigned32
  rtu_parameter, dt_libinfo_Unsigned32 rty_outAccumulatorBuffer[10]);
extern void LIBINFO_WL_00_FuncCallSplit4(const int32_t rtu_0[10], int32_t rtu_1,
  int32_t rtu_2, const dt_libinfo_Time20msLong rtu_3[10], const
  dt_libinfo_Time20msLong rtu_4[10], const dt_libinfo_gps_latitude rtu_5[10],
  dt_libinfo_gps_latitude rtu_6, const dt_libinfo_Ratio_Unsigned32 rtu_7[10],
  dt_libinfo_Ratio_Unsigned32 rtu_8, const dt_libinfo_single rtu_9[10], const
  dt_libinfo_Flag_u16 rtu_10[10], const real32_T rtu_11[10], const
  dt_libinfo_Unsigned32 rtu_12[10], dt_libinfo_Unsigned32 rtu_13, const real32_T
  rtu_14[10], const real32_T rtu_15[10], const dt_libinfo_Unsigned32 rtu_16[10],
  dt_libinfo_Unsigned32 rtu_17, int32_t rty_0[10], dt_libinfo_Time20msLong
  rty_1[10], dt_libinfo_Time20msLong rty_2[10], dt_libinfo_gps_latitude rty_3[10],
  dt_libinfo_Ratio_Unsigned32 rty_4[10], dt_libinfo_single rty_5[10],
  dt_libinfo_Flag_u16 rty_6[10], real32_T rty_7[10], dt_libinfo_Unsigned32
  rty_8[10], real32_T rty_9[10], real32_T rty_10[10], dt_libinfo_Unsigned32
  rty_11[10], RT_MODEL_LIBINFO_WL_00 * const LIBINFO_WL_00_M);
extern void LIBINFO_WL_00_UpdateFunc(const real32_T rtu_inAccumulatorBuffer[10],
  int32_t rtu_bufferDepth, real32_T rtu_parameter, real32_T
  rty_outAccumulatorBuffer[10]);
extern void LIBINFO_WL_00_UpdateFunc_lydr(const dt_libinfo_Unsigned32
  rtu_inAccumulatorBuffer[10], dt_libinfo_Unsigned32 rty_outAccumulatorBuffer[10]);
extern void LIBINFO_WL_00_FuncCallSplit1(const int32_t rtu_0[10], const
  dt_libinfo_Time20msLong rtu_1[10], int32_t rtu_2, dt_libinfo_Time20msLong
  rtu_3, const dt_libinfo_Time20msLong rtu_4[10], dt_libinfo_Time20msLong rtu_5,
  const dt_libinfo_gps_latitude rtu_6[10], const dt_libinfo_Ratio_Unsigned32
  rtu_7[10], const dt_libinfo_single rtu_8[10], const dt_libinfo_Flag_u16 rtu_9
  [10], dt_libinfo_Flag_u16 rtu_10, dt_libinfo_single rtu_11, const real32_T
  rtu_12[10], real32_T rtu_13, const dt_libinfo_Unsigned32 rtu_14[10], const
  real32_T rtu_15[10], real32_T rtu_16, const real32_T rtu_17[10], real32_T
  rtu_18, const dt_libinfo_Unsigned32 rtu_19[10], int32_t rty_0[10],
  dt_libinfo_Time20msLong rty_1[10], dt_libinfo_Time20msLong rty_2[10],
  dt_libinfo_gps_latitude rty_3[10], dt_libinfo_Ratio_Unsigned32 rty_4[10],
  dt_libinfo_single rty_5[10], dt_libinfo_Flag_u16 rty_6[10], real32_T rty_7[10],
  dt_libinfo_Unsigned32 rty_8[10], real32_T rty_9[10], real32_T rty_10[10],
  dt_libinfo_Unsigned32 rty_11[10]);
extern void LIBINFO_WL_00_DoShift(int32_t rtu_bufferDepth, int32_t
  rtu_indexToShiftBackOneBased, const int32_t rtu_inBuffer[10], int32_t
  rty_outBuffer[10]);
extern void LIBINFO_WL_00_DoNothing(const int32_t rtu_0[10], int32_t
  rty_outBuffer[10]);
extern void LIBINFO_WL_00_DoShift_kcfw(int32_t rtu_bufferDepth, int32_t
  rtu_indexToShiftBackOneBased, const dt_libinfo_Time20msLong rtu_inBuffer[10],
  dt_libinfo_Time20msLong rty_outBuffer[10]);
extern void LIBINFO_WL_00_DoNothing_aohe(const dt_libinfo_Time20msLong rtu_0[10],
  dt_libinfo_Time20msLong rty_outBuffer[10]);
extern void LIBINFO_WL_00_ShiftBufferBack(int32_t rtu_indexToShiftBackOneBased,
  const dt_libinfo_Time20msLong rtu_inBuffer[10], int32_t rtu_bufferDepth,
  dt_libinfo_Time20msLong rty_outBuffer[10], rtC_ShiftBufferBack_LIBINFO_WL_
  *localC);
extern void LIBINFO_WL_00_DoShift_bx2h(int32_t rtu_bufferDepth, int32_t
  rtu_indexToShiftBackOneBased, const real32_T rtu_inBuffer[10], real32_T
  rty_outBuffer[10]);
extern void LIBINFO_WL_00_DoNothing_n0wb(const real32_T rtu_0[10], real32_T
  rty_outBuffer[10]);
extern void LIBINFO_WL_ShiftBufferBack_afxg(int32_t rtu_indexToShiftBackOneBased,
  const real32_T rtu_inBuffer[10], int32_t rtu_bufferDepth, real32_T
  rty_outBuffer[10], rtC_ShiftBufferBack_LIBINF_pzts *localC);
extern void LIBINFO_WL_00_MergeFunc(const real32_T rtu_inAccumulatorBuffer[10],
  int32_t rtu_mergeFromIndexOneBased, int32_t rtu_bufferDepth, real32_T
  rty_outAccumulatorBuffer[10], rtC_MergeFunc_LIBINFO_WL_00 *localC);
extern void LIBINFO_WL_00_DoShift_g0d2(int32_t rtu_bufferDepth, int32_t
  rtu_indexToShiftBackOneBased, const dt_libinfo_Unsigned32 rtu_inBuffer[10],
  dt_libinfo_Unsigned32 rty_outBuffer[10]);
extern void LIBINFO_WL_00_DoNothing_i3r3(const dt_libinfo_Unsigned32 rtu_0[10],
  dt_libinfo_Unsigned32 rty_outBuffer[10]);
extern void LIBINFO_WL_00_MergeFunc_oer2(const dt_libinfo_Unsigned32
  rtu_inAccumulatorBuffer[10], int32_t rtu_mergeFromIndexOneBased, int32_t
  rtu_bufferDepth, dt_libinfo_Unsigned32 rty_outAccumulatorBuffer[10],
  rtC_MergeFunc_LIBINFO_WL_0_e0nk *localC);
extern void LIBINFO_WL_00_DoShift_etzq(int32_t rtu_bufferDepth, int32_t
  rtu_indexToShiftBackOneBased, const dt_libinfo_gps_latitude rtu_inBuffer[10],
  dt_libinfo_gps_latitude rty_outBuffer[10]);
extern void LIBINFO_WL_00_DoNothing_b1m5(const dt_libinfo_gps_latitude rtu_0[10],
  dt_libinfo_gps_latitude rty_outBuffer[10]);
extern void LIBINFO_WL_00_DoShift_ihkh(int32_t rtu_bufferDepth, int32_t
  rtu_indexToShiftBackOneBased, const dt_libinfo_Ratio_Unsigned32 rtu_inBuffer
  [10], dt_libinfo_Ratio_Unsigned32 rty_outBuffer[10]);
extern void LIBINFO_WL_00_DoNothing_acyu(const dt_libinfo_Ratio_Unsigned32
  rtu_0[10], dt_libinfo_Ratio_Unsigned32 rty_outBuffer[10]);
extern void LIBINFO_WL_00_DoShift_cq4g(int32_t rtu_bufferDepth, int32_t
  rtu_indexToShiftBackOneBased, const dt_libinfo_Flag_u16 rtu_inBuffer[10],
  dt_libinfo_Flag_u16 rty_outBuffer[10]);
extern void LIBINFO_WL_00_DoNothing_keuk(const dt_libinfo_Flag_u16 rtu_0[10],
  dt_libinfo_Flag_u16 rty_outBuffer[10]);
extern void LIBINFO_WL_00_FuncCallSplit2(const int32_t rtu_0[10], int32_t rtu_1,
  int32_t rtu_2, const dt_libinfo_Time20msLong rtu_3[10], const
  dt_libinfo_Time20msLong rtu_4[10], const dt_libinfo_gps_latitude rtu_5[10],
  const dt_libinfo_Ratio_Unsigned32 rtu_6[10], const dt_libinfo_single rtu_7[10],
  const dt_libinfo_Flag_u16 rtu_8[10], const real32_T rtu_9[10], const
  dt_libinfo_Unsigned32 rtu_10[10], const real32_T rtu_11[10], const real32_T
  rtu_12[10], const dt_libinfo_Unsigned32 rtu_13[10], int32_t rty_0[10],
  dt_libinfo_gps_latitude rty_1[10], dt_libinfo_Ratio_Unsigned32 rty_2[10],
  dt_libinfo_Flag_u16 rty_3[10], dt_libinfo_Time20msLong rty_6[10],
  dt_libinfo_Time20msLong rty_9[10], real32_T rty_12[10], dt_libinfo_Unsigned32
  rty_15[10], real32_T rty_18[10], real32_T rty_25[10], dt_libinfo_Unsigned32
  rty_28[10], dt_libinfo_single rty_31[10], rtC_FuncCallSplit2_LIBINFO_WL_0
  *localC);
extern void LIBINFO_WL_ShiftBufferBack_nhsx(int32_t rtu_indexToShiftBackOneBased,
  const dt_libinfo_Time20msLong rtu_inBuffer[10], int32_t rtu_bufferDepth,
  dt_libinfo_Time20msLong rty_outBuffer[10], rtC_ShiftBufferBack_LIBINF_h3x4
  *localC);
extern void LIBINFO_WL_ShiftBufferBack_frny(int32_t rtu_indexToShiftBackOneBased,
  const real32_T rtu_inBuffer[10], int32_t rtu_bufferDepth, real32_T
  rty_outBuffer[10], rtC_ShiftBufferBack_LIBINF_enc2 *localC);
extern void LIBINFO_WL_00_CommitFunc(const real32_T rtu_inAccumulatorBuffer[10],
  int32_t rtu_bufferDepth, real32_T rty_commitAccumulation[10], real32_T
  rty_outAccumulatorBuffer[10], rtC_CommitFunc_LIBINFO_WL_00 *localC);
extern void LIBINFO_WL_00_CommitFunc_ibfk(const dt_libinfo_Unsigned32
  rtu_inAccumulatorBuffer[10], int32_t rtu_bufferDepth, dt_libinfo_Unsigned32
  rty_commitAccumulation[10], dt_libinfo_Unsigned32 rty_outAccumulatorBuffer[10],
  rtC_CommitFunc_LIBINFO_WL__juir *localC);

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
#endif                                 /* RTW_HEADER_LIBINFO_WL_00_private_h_ */
