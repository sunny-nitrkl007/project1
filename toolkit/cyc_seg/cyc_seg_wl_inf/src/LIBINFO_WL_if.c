/******************************************************************************
**
**  COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
***
*** DESCRIPTION:
***     Application level interfaces.
***
*** FILE:
***     LIBINFO_WL_if.c
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

#include <LIBINFO_WL_if.h>

/******************************************************************************
***
***    Global data symbols defined in this file
***    -- data type definitions --
***
******************************************************************************/

/******************************************************************************
***    STATE INTERFACE VARIABLES
******************************************************************************/

unsigned_16  	LIBPROD_app_number = 9400;          	//LIBINFO specific application number


int_16    		LIBPROD_ground_spd_kph = 0;

float    		LIBPROD_payload_ratio = 0;

unsigned_16     LIBPROD_payload_ratio_status = 0;

float    		LIBPROD_payload_ratio_raw = 0;

unsigned_16      LIBPROD_payload_ratio_raw_status = 0;

int_16    		LIBPROD_lift_valve_cmd = 0;

int_16    		LIBPROD_tilt_valve_cmd = 0;

int_16    		LIBPROD_bucket_angle = 0;

int_16    		LIBPROD_lift_angle = 0;

int_16    		LIBPROD_desired_gear = 0;

int_16    		LIBPROD_engine_spd_rpm = 0;

int_16    		LIBPROD_tilt_lever_cmd = 0;

unsigned_16    	LIBPROD_tilt_cyl_pos = 0;

unsigned_16    	LIBPROD_machine_idle_status = 0;

unsigned_16    	LIBPROD_keyswitch_state = 0;

unsigned_32    	LIBPROD_real_time = 0;

unsigned_8    	LIBPROD_realTime_status = 0;

int_16          LIBPROD_timezone_offset = 0;

unsigned_32    	LIBPROD_total_fuel_high_res = 0;

unsigned_32    	LIBPROD_total_fuel_low_res = 0;

unsigned_16    	LIBPROD_fuel_rate = 0;

unsigned_16    	LIBPROD_ARD_fuel_rate = 0;	

unsigned_32    	LIBPROD_GPS_latitude = 0;

unsigned_32    	LIBPROD_GPS_longitude = 0;

unsigned_8    	LIBPROD_GPS_status = 0;

unsigned_32    	LIBPROD_service_hour_meter = 0;

float    		LIBPROD_payload_weight = 0;

unsigned_16     LIBPROD_payload_weight_status = 0;

unsigned_16    	LIBPROD_payload_calc_method = 0;

int_16    		LIBPROD_extForceNormalized = 0;

unsigned_16    	LIBPROD_impl_operation_status = 0;

int_16          LIBPROD_Engine_Load_Factor = 0;

/***********************************************************************************/
/* OUTPUTS */
 /*Output Interfaces from LIBINFO_WL_01
These shall be populated from the model outputs external 
to this file!
*/
/***********************************************************************************/

unsigned_8    	commit_segment_record = 0;

unsigned_8    	segment_record_id = 0;

unsigned_32    	segment_rec_start_simTime = 0;

unsigned_32    	segment_rec_duration = 0;

float    		segment_rec_distance = 0;

unsigned_32    	segment_rec_start_real_time = 0;

float    		segment_rec_fuel_used = 0;

unsigned_32    	segment_rec_latitude = 0;

unsigned_32    	segment_rec_longitude = 0;

unsigned_32    	segment_rec_idle_time = 0;

unsigned_32    	segment_rec_hour_meter = 0;

float    		segment_rec_payload = 0;

unsigned_16    	segment_rec_payload_calc_method = 0;

unsigned_8    	commit_rec_gps = 0;

unsigned_8    	segment_dig_state = 0;

unsigned_8    	segment_last_completed_id = 0;

unsigned_32    	segment_time_since_last_end = 0;

unsigned_8    	segment_sequence_number = 0;

unsigned_8		keyswitch_override_flag = 1;

unsigned_8      segment_active_segment_id;


