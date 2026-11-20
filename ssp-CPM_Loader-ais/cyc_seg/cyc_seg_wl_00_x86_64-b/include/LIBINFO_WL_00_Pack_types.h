/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: LIBINFO_WL_00_Pack_types.h
 **
 ** Real-Time Workshop code generated for Simulink model LIBINFO_WL_00.
 **
 ** Model version                        : 1.118
 ** Real-Time Workshop file version      : 8.3 (R2012b) 20-Jul-2012
 ** TLC version                          : 8.3 (Jul 21 2012)
 ** CATutils_MatLab version              : CATUTILS_MATLAB_4.3.3
 **
 ******************************************************************************/
/*
 ** This file contains the type definitions for the package object data structures
 */

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#ifndef RTW_HEADER_LIBINFO_WL_00_Pack_types_h_
#define RTW_HEADER_LIBINFO_WL_00_Pack_types_h_
#include <LIBINFO_WL_00.h>
#include <sl_cal.h>
#include <applib_public.h>

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/* Package Interface inport mapping: LIBINFO_WL_00 */
typedef struct _LIBINFO_WL_00_PackIF_u
{
  dt_libinfo_MachSpdKPH_Signed *ground_speed;
  dt_libinfo_single *payload_ratio;
  dt_libinfo_single *payload_ratio_raw;
  dt_libinfo_Ratio_hiRes *ext_force_normalized;
  dt_libinfo_ValveCmd *lift_valve_cmd;
  dt_libinfo_ValveCmd *tilt_valve_cmd;
  dt_libinfo_Angle *bucket_angle;
  dt_libinfo_Angle *lift_angle;
  dt_libinfo_TransmissionGear_int16 *desired_gear;
  dt_libinfo_EngSpd_Signed *engine_speed;
  dt_libinfo_ValveCmd *tilt_lever_cmd;
  dt_libinfo_modulation_pct *tilt_cyl_position;
  dt_libinfo_Unsigned16 *machine_idle;
  dt_libinfo_Unsigned16 *key_switch;
  dt_libinfo_Unsigned32 *real_time;
  dt_libinfo_fuel_high_res *fuel_high_res;
  dt_libinfo_fuel_low_res *fuel;
  dt_libinfo_FuelRate *fuel_rate;
  dt_libinfo_ARDfuel_Rate *fuel_rate_ard;
  dt_libinfo_Flag *realTime_status;
  dt_libinfo_gps_latitude *gps_latitude;
  dt_libinfo_Ratio_Unsigned32 *gps_longitude;
  dt_libinfo_Flag *gps_lat_long_status;
  dt_libinfo_single *payload_weight;
  dt_libinfo_Flag_u16 *payloadCalcMethod;
  dt_libinfo_Unsigned32 *service_hour_meter;
  dt_libinfo_tz_offset_mins *timezone_offset;
  dt_libinfo_Flag_u16 *payload_weight_status;
  dt_libinfo_Unsigned16 *payload_ratio_status;
  dt_libinfo_Unsigned16 *payload_ratio_raw_status;
  dt_libinfo_Unsigned16 *Impl_operation_status;
} LIBINFO_WL_00_PackIF_u_t;

/* Package Interface outport mapping: LIBINFO_WL_00 */
typedef struct _LIBINFO_WL_00_PackIF_y
{
  dt_libinfo_Flag *commit_segment_record;
  uint8_t *segment_record_id;
  dt_libinfo_Unsigned32 *segment_rec_start_simTime;
  dt_libinfo_Time20msLong *segment_rec_duration;
  dt_libinfo_single *segment_rec_distance;
  dt_libinfo_Unsigned32 *segment_rec_start_real_time;
  dt_libinfo_single *segment_rec_fuel_used;
  dt_libinfo_gps_latitude *segment_rec_latitude;
  dt_libinfo_Ratio_Unsigned32 *segment_rec_longitude;
  dt_libinfo_Unsigned32 *segment_rec_idle_time;
  dt_libinfo_Unsigned32 *segment_rec_hour_meter;
  dt_libinfo_single *segment_rec_payload;
  dt_libinfo_Flag_u16 *segment_rec_payload_calc_method;
  dt_libinfo_Flag *commit_rec_gps;
  uint8_t *segment_dig_state;
  uint8_t *segment_last_completed_id;
  dt_libinfo_Time20msLong *segment_time_since_last_end;
  uint8_t *segment_sequence_number;
  uint8_t *keyswitch_override_flag;
  uint8_t *segment_active_segment_id;
} LIBINFO_WL_00_PackIF_y_t;

/* Package Interface inport/outport mapping: LIBINFO_WL_00 */
typedef struct _LIBINFO_WL_00_PackIF
{
  LIBINFO_WL_00_PackIF_u_t u;
  LIBINFO_WL_00_PackIF_y_t y;
} LIBINFO_WL_00_PackIF_t;

/* Package work definition: LIBINFO_WL_00 */
typedef struct {
  uint_least8_t runState;
  Application_t applibState;
  RT_MODEL_LIBINFO_WL_00 LIBINFO_WL_00_M;
  D_Work_LIBINFO_WL_00 D_Work;
  BlockIO_LIBINFO_WL_00 BlockIO;
} LIBINFO_WL_00_work_t;

/* Package config struct definition: LIBINFO_WL_00 */
typedef struct {
  LIBINFO_WL_00_PackIF_t PackIF;
  const sl_cal_t* const variantObj;
} LIBINFO_WL_00_config_t;

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
#endif                                 /* RTW_HEADER_LIBINFO_WL_00_Pack_types_h_ */
