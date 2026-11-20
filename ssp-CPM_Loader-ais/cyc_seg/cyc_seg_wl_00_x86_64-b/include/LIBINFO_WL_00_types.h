/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: LIBINFO_WL_00_types.h
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
#ifndef RTW_HEADER_LIBINFO_WL_00_types_h_
#define RTW_HEADER_LIBINFO_WL_00_types_h_
#include "R2012b_rtwtypes.h"

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/
#ifndef SS_LONG
#define SS_LONG                        59
#endif

#ifndef SS_ULONG
#define SS_ULONG                       60
#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_MachSpdKPH_Signed_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_MachSpdKPH_Signed_

/* Data type used to represent signed machine speed in kph */
typedef int16_t dt_libinfo_MachSpdKPH_Signed;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_single_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_single_

/* Data type for floating point single precision */
typedef real32_T dt_libinfo_single;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_Ratio_hiRes_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_Ratio_hiRes_

/* Data type used to represent unitless number with high resolution */
typedef int16_t dt_libinfo_Ratio_hiRes;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_ValveCmd_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_ValveCmd_

/* Data type used to represent an valve command. */
typedef int16_t dt_libinfo_ValveCmd;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_Angle_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_Angle_

/* Data type used to represent degrees of an angle or pitch */
typedef int16_t dt_libinfo_Angle;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_TransmissionGear_int16_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_TransmissionGear_int16_

/* Actual Transmission Gear (ex: -4, -3, -2, -1, 0, 1, 2, 3., 4) */
typedef int16_t dt_libinfo_TransmissionGear_int16;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_EngSpd_Signed_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_EngSpd_Signed_

/* Data type used to represent signed desired engine speed */
typedef int16_t dt_libinfo_EngSpd_Signed;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_modulation_pct_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_modulation_pct_

/* pedal modulation variable type */
typedef uint16_t dt_libinfo_modulation_pct;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_Unsigned16_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_Unsigned16_

/* Unsigned, 16-bit data type with radix 0 */
typedef uint16_t dt_libinfo_Unsigned16;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_Unsigned32_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_Unsigned32_

/* Unsigned, 32-bit data type with radix 0 */
typedef uint32_t dt_libinfo_Unsigned32;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_fuel_high_res_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_fuel_high_res_

/* Data type used to represent total fuel in gallons with high resolution */
typedef uint32_t dt_libinfo_fuel_high_res;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_fuel_low_res_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_fuel_low_res_

/* Data type used to represent total fuel in gallons with a 0.125gal resolution */
typedef uint32_t dt_libinfo_fuel_low_res;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_FuelRate_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_FuelRate_

/* Data type used to represent fuel rate in L/hr */
typedef uint16_t dt_libinfo_FuelRate;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_ARDfuel_Rate_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_ARDfuel_Rate_

/* Data type used to represent fuel rate in l/sec */
typedef uint16_t dt_libinfo_ARDfuel_Rate;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_Flag_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_Flag_

/* Data type used to represent a boolean flag value */
typedef uint8_t dt_libinfo_Flag;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_gps_latitude_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_gps_latitude_

/* Unsigned, 32-bit data type with radix 17 */
typedef uint32_t dt_libinfo_gps_latitude;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_Ratio_Unsigned32_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_Ratio_Unsigned32_

/* Data type used to represent high res ratio */
typedef uint32_t dt_libinfo_Ratio_Unsigned32;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_Flag_u16_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_Flag_u16_

/* Data type used to represent a boolean flag value */
typedef uint16_t dt_libinfo_Flag_u16;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_tz_offset_mins_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_tz_offset_mins_

/* Data type used to represent time zone offset in minutes */
typedef int16_t dt_libinfo_tz_offset_mins;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_Time20msLong_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_Time20msLong_

/* Data type used to represent time for 20 msec task */
typedef uint32_t dt_libinfo_Time20msLong;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_Status_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_Status_

/* Data type used to represent the Status of the Sink */
typedef uint8_t dt_libinfo_Status;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_Unsigned8_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_Unsigned8_

/* Unsigned, 8-bit data type with radix 0 */
typedef uint8_t dt_libinfo_Unsigned8;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_Count_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_Count_

/* 16-bit Data type used to represent a number of software loops */
typedef uint16_t dt_libinfo_Count;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_FilterFactor_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_FilterFactor_

/* Data type used to represent a low-pass filter factor (range is 0-1) */
typedef uint16_t dt_libinfo_FilterFactor;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_dt_libinfo_Time20ms_
#define _DEFINED_TYPEDEF_FOR_dt_libinfo_Time20ms_

/* Data type used to represent time for 20 msec task */
typedef uint16_t dt_libinfo_Time20ms;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_st_PayloadRatioStatus_t_
#define _DEFINED_TYPEDEF_FOR_st_PayloadRatioStatus_t_

/* Used to represent the payload ratio status */
typedef uint16_t st_PayloadRatioStatus_t;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_LIBINFO_WL_00 RT_MODEL_LIBINFO_WL_00;

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
#endif                                 /* RTW_HEADER_LIBINFO_WL_00_types_h_ */
