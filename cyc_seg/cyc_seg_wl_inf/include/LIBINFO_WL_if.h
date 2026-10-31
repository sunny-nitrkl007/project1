/******************************************************************************
**
**  COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
***
*** DESCRIPTION:
***     Application level interfaces.
***
*** FILE:
***     LIBINFO_WL_if.h
***
******************************************************************************/

/******************************************************************************
***
***    External function prototypes, data, & symbols
***    -- #Include's --
***
******************************************************************************/

/******************************************************************************
***
***    Constants defined for this file
***    -- #Define's --
***
******************************************************************************/

/******************************************************************************
***
***    Enumerations/Unions/Macros for this file
***    -- enum/union --
***
******************************************************************************/

/******************************************************************************
***
***    Structure Definitions for this file
***    -- typedefs --
***
******************************************************************************/

/******************************************************************************
***
***    File scope functions defined for this file
***    -- Function Prototypes --
***
******************************************************************************/
#ifndef __LIBINFO_WL_IF_H__
#define __LIBINFO_WL_IF_H__

#include <cat_std_types.h>

/******************************************************************************
***
***    Global data symbols defined in this file
***    -- data type definitions --
***
******************************************************************************/

/******************************************************************************
***    STATE INTERFACE VARIABLES
******************************************************************************/


/******************************************************************************
  INTERFACES REMAINING AT REQUEST OF EMSD TOP LEVEL POWERTRAIN
******************************************************************************/
/*LIBPROD_app_number
//     This is the variable that is populated by the upper level
//     for picking the right data table. Following values shall be
//		populated for the corresponding machines.  Other machine 
//		configurations such as block handler, forestry etc., shall 
//		be added at a later time. Until then all of them shall be treated
// 		like a regular loader by this library. - velams: Sept 02 2015
*/
	/*	8600	-	986 HRC & LRC 	*/
  	/*	9400	-	994 HRC & LRC 	*/

extern 	unsigned_16  	LIBPROD_app_number;

/*LIBPROD_ground_spd_kph
//     This is the variable that is populated by the upper level
//     for the ground speed based on the transmission output speed.
//     it is scaled as 0.00390625 kph/bit
//		dt_libinfo_MachSpdKPH_Signed
*/
extern	int_16    LIBPROD_ground_spd_kph;

/*LIBPROD_payload_ratio
//     This is the variable that is populated by the upper level
//     for the payload ratio with the notch filters from PCS.
//     load ratio = filtered instantaneous weight / target weight
//     it is scaled as 0.000244 units/bit
*/
extern	float    LIBPROD_payload_ratio;

/*LIBPROD_payload_ratio_status
//     This is the variable that is populated by the upper level
//     for the payload ratio with the notch filters from PCS.
//     load ratio = filtered instantaneous weight / target weight
*/
extern	 unsigned_16   LIBPROD_payload_ratio_status;

/*LIBPROD_payload_ratio_raw
//     This is the variable that is populated by the upper level
//     for the payload ratio without the notch filters from PCS.
//     raw load ratio = instantaneous weight (non filtered weight) / target weight
//     it is scaled as 0.000244 units/bit
*/
extern	float    LIBPROD_payload_ratio_raw;

/*LIBPROD_payload_ratio_raw_status
//     This is the variable that is populated by the upper level
//     for the payload ratio with the notch filters from PCS.
//     load ratio = filtered instantaneous weight / target weight
*/
extern	unsigned_16    LIBPROD_payload_ratio_raw_status;

/*LIBPROD_lift_valve_cmd
//     This is the variable that is populated by the upper level
//     for the percent valve command that actually gets commanded to the valve.
//     Raise > 0 
//     Lower < 0 
//     -100 -> 100
//     0.0625 %/bit
*/
extern	int_16    LIBPROD_lift_valve_cmd;

/*LIBPROD_tilt_valve_cmd
//     This is the variable that is populated by the upper level
//     for the percent valve command that actually gets commanded to the valve.
//     Rack > 0 
//     Dump < 0 
//     -100 -> 100
//     it is scaled as 0.0625 %/bit
*/
extern	int_16    LIBPROD_tilt_valve_cmd;

/*LIBPROD_bucket_angle
//     This is the variable that is populated by the upper level
//     for the angle of the bucket w.r.t machine.
//     it is scaled as 0.015625 degrees/bit
*/
extern	int_16    LIBPROD_bucket_angle;

/*LIBPROD_lift_angle
//     This is the variable that is populated by the upper level
//     for the angle of the lift arms w.r.t machine.
//     it is scaled as 0.015625 degrees/bit
*/
extern	int_16    LIBPROD_lift_angle;

/*LIBPROD_desired_gear
//     This is the variable that is populated by the upper level
//     for the current transmission gear with direction
//     -3, -2, -1, 0, 1, 2, 3..
//     it is scaled as 1 gear/bit
*/
extern	int_16    LIBPROD_desired_gear;

/*LIBPROD_engine_spd_rpm
//     This is the variable that is populated by the upper level
//     for the actual engine speed in rpm
//     it is scaled as 0.125 rpm/bit
*/
extern	int_16    LIBPROD_engine_spd_rpm;

/*LIBPROD_tilt_lever_cmd
//     This is the variable that is populated by the upper level
//     for the percent lever command that the operator is commanding from the lever
//     Rack > 0
//     Dump < 0 
//     -100 -> 100
//     it is scaled as 0.0625 %/bit
*/
extern	int_16    LIBPROD_tilt_lever_cmd;

/*LIBPROD_tilt_cyl_pos
//     This is the variable that is populated by the upper level
//     for the normalized tilt cylinder position where 100% is rack and 0% is dump. 
//     it is scaled as 1% /bit
*/
extern	unsigned_16    LIBPROD_tilt_cyl_pos;

/*LIBPROD_machine_idle_status
//     This is the variable that is populated by the upper level
//     for the proverbial machine idle status. the machine idle time refers to this.
*/
extern	unsigned_16    LIBPROD_machine_idle_status;

/*LIBPROD_keyswitch_state
//		This is the variable that is populated by the upper level
//		whether the key switch is off or not.
*/
extern	unsigned_16    LIBPROD_keyswitch_state;

/*LIBPROD_real_time
//		This is the variable that is populated by the upper level
//		for the real time (UTC + local time offset, or similar )
//      it is scaled as 1 sec /bit
*/
extern	unsigned_32    LIBPROD_real_time;

/*LIBPROD_realTime_status
//     This is the variable that is populated by the upper level
//     for the status of the real time.
*/
extern	unsigned_8    LIBPROD_realTime_status;

/*LIBPROD_timezone_offset
//     This is the number of minutes from the UTC time for local time adjustments
//     1 min/bit
*/
extern  int_16     LIBPROD_timezone_offset;

/*LIBPROD_total_fuel_high_res
//     This is the variable that is populated by the upper level
//     for the high resolution of the total fuel used.
//     0.001 gal/bit
*/
extern	unsigned_32    LIBPROD_total_fuel_high_res;

/*LIBPROD_total_fuel_low_res
//     	This is the variable that is populated by the upper level
//     	for the low resolution of the total fuel used.
//      0.125 gal/bit
*/
extern	unsigned_32    LIBPROD_total_fuel_low_res;

/*LIBPROD_fuel_rate
//     This is the variable that is populated by the upper level
//     for the current engine fuel rate,  excluding the ARD. 
//     it is scaled as 0.05 l/hr/bit
*/
extern	unsigned_16    LIBPROD_fuel_rate;

/*LIBPROD_ARD_fuel_rate
//     	This is the variable that is populated by the upper level
//     	for the current ARD fuel rate.
//      it is scaled as 1E-06 l/sec/bit
*/
extern	unsigned_16    LIBPROD_ARD_fuel_rate;

/*LIBPROD_GPS_latitude
//      This is the variable that is populated by the upper level
//      for the current machine Latitude.
//      it is scaled as 7.62939E-06 degrees /bit
*/
extern unsigned_32    LIBPROD_GPS_latitude;

/* LIBPROD_GPS_longitude
//      This is the variable that is populated by the upper level
//      for the current machine Longitude.
//      it is scaled as 1.52588E-05 degrees / bit
*/
extern unsigned_32    LIBPROD_GPS_longitude;

/* LIBPROD_GPS_status
//      This is the variable that is populated by the upper level
//      for the current GPS position status.
*/
extern unsigned_8    LIBPROD_GPS_status;

/* LIBPROD_service_hour_meter
//      This is the variable that is populated by the upper level
//      for the current Service Hour meter (SHM)
//      it is scaled as 1 sec/bit
*/
extern unsigned_32    LIBPROD_service_hour_meter;

/* LIBPROD_payload_weight
//      This is the variable that is populated by the upper level
//      to determine the payload weight from the PCS library.
*/
extern float    LIBPROD_payload_weight;

/* LIBPROD_payload_weight_status
//     This is the variable that is populated by the upper level
//     to determine the payload weight status.
//     0 = Unavailable
//     1 = available
*/
extern  unsigned_16     LIBPROD_payload_weight_status;

/* LIBPROD_payload_calc_method
//      This is the variable that is populated by the upper level
//      to determine the payload calculation method from the PCS library.
//      0 = NONE
//      1 = LOW
//      2 = MEDIUM
//      3 = HIGH 
*/
extern unsigned_16    LIBPROD_payload_calc_method;


/* LIBPROD_extForceNormalized
//      This is the variable that is populated by the upper level 
//      to determine the Fore-Aft external machine force ,normalized to
//      ratio of the machine weight * g
//      it is scaled as  0.0005 g/bit
*/
extern int_16    LIBPROD_extForceNormalized;


/*LIBPROD_impl_operation_status
//     This is the variable that is populated by the upper level
//     for the proverbial machine idle status. the machine idle time refers to this.
*/
extern	unsigned_16    LIBPROD_impl_operation_status;

/* LIBPROD_Engine_Load_Factor
//      This is the variable that is populated by the upper level 
//      to determine the Engine load factor.
*/
extern int_16    LIBPROD_Engine_Load_Factor;

/***********************************************************************************/
/* OUTPUTS */
/***********************************************************************************/
/*commit_segment_record
//     	This variable is the trigger to commit the new segment record.
//      it is scaled as 1 status/bit
*/
extern	unsigned_8    commit_segment_record;

/*segment_record_id
//     	This variable is the Segment ID to commit to a record.
//      it is scaled as 1 id/bit
*/
extern	unsigned_8    segment_record_id;

/*segment_rec_start_simTime
//     	This variable is the powerup start time.
//      it is scaled as 1 sec/bit
*/
extern	unsigned_32    segment_rec_start_simTime;

/*segment_rec_duration
//     	This variable is the duration to commit to the record.
//      it is scaled as 1 sec/bit
*/
extern	unsigned_32    segment_rec_duration;

/*segment_rec_distance
//     	This variable is the total travel distance to commit to the record.
*/
extern	float    segment_rec_distance;

/*segment_rec_start_real_time
//     	This variable is the real start time to commit to the record.
*/
extern	unsigned_32    segment_rec_start_real_time;

/*segment_rec_fuel_used
//     	This variable is the total fuel used to commit to the record.
*/
extern	float    segment_rec_fuel_used;

/*segment_rec_latitude
//     	This variable is the start latitude to commit to the record.
//      it is scaled as 7.62939E-06 degrees/bit
*/
extern	unsigned_32    segment_rec_latitude;

/*segment_rec_longitude
//     	This variable is the start longitude to commit to the record.
// 		It is scaled as 1.52588E-05 degrees/bit
*/
extern	unsigned_32    segment_rec_longitude;

/*segment_rec_idle_time
//     	This variable is the idle time to commit to the record. 
// 		It is scaled as 1 sec/bit
*/
extern	unsigned_32    segment_rec_idle_time;

/*segment_rec_hour_meter
//     	This variable is the start SHM to commit to the record. 
// 		It is scaled as 
*/
extern	unsigned_32    segment_rec_hour_meter;

/*segment_rec_payload
//     	This variable is the payload to commit to the record. NAN is no payload captured. 
*/
extern	float    segment_rec_payload;

/*segment_rec_payload_calc_method
//     	This variable is the payload calculation method to commit to the record.
*/
extern	unsigned_16    segment_rec_payload_calc_method;

/*commit_rec_gps
//      This variable is if the latitude and longitude are not going to be included in segment 
//      records, then this is a flag to the GPS record algorithm to include a record at the 
//      current time and location.
//      It is scaled as 1 record/bit
*/ 
extern unsigned_8    commit_rec_gps;

/*segment_dig_state
//      This variable is needed for operator coaching.
//      0 = Inactive
//      1 = Tentatively Active
//      2 = Active
//      It is scaled as 1 state/bit
*/
extern unsigned_8    segment_dig_state;

/*segment_last_completed_id
//      when a new segment is confirmed , this parameter is set to the ID of the segment that just ended. 
//      it is scaled as 1 id/bit
*/
extern unsigned_8    segment_last_completed_id;

/*segment_time_since_last_end
//      This parameter is continuously updated to indicate how long ago the last completed segment ended.
//      It is scaled as 50 sec/bit
*/
extern unsigned_32    segment_time_since_last_end;

/*segment_sequence_number
//      This variable increments with each new segment confirmation and rolls over.
//      it is scaled as 1 seq num/bit
*/
extern unsigned_8    segment_sequence_number;

/*keyswitch_override_flag 
    	This flag is set when Key-Off/Engine-Off Segment is committed, which indicates the point at which
    	PD can ask Implement to safely shut down
*/
extern unsigned_8	 keyswitch_override_flag;

/*segment_active_segment_id
//      Active segment id
//      it is scaled as 1 seq num/bit
*/
extern unsigned_8    segment_active_segment_id;


#endif //__LIBINFO_WL_IF_H__

