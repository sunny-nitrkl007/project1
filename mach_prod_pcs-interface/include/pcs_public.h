/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 1994-2016 CATERPILLAR INC.   ALL RIGHTS RESERVED.       %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
***
*** DESCRIPTION :
*** Prototypes of functions in the PCS package
***
*** LANGUAGE :
***    ANSI C
***
*** MACRO LIST:
***
*******************************************************************************/
#ifndef __PCS_PUBLIC_H__
#define __PCS_PUBLIC_H__

#if defined (__cplusplus)
extern "C"
{
#endif

#include <nvm.h>
#include <cal_mgr.h>
#include <stddef.h>
#include <std_t.h>
#include <prod_core_public.h>
#include <prod_core_packed_struct.h>

#define PCS_DATA_STATUS_OK 0
#define PCS_DATA_STATUS_BAD 1

/******************************************************************/
/* Typedefs for function pointer return values                    */
/******************************************************************/
typedef struct {
    int pres; /* this should be in 0.001 kpa */
    unsigned_8 data_status; /* this is the value returned by core */
} PRESSURE_INFO;

typedef struct {
    int dc; /* this should be in 0.01% of full cyclinder extension (uncalibrated) */
    unsigned_8 data_status; /* this is the value returned by core */
} POS_INFO;

typedef struct {
    int_16 temp;
    unsigned_16 data_status;
}TEMP_INFO;

typedef struct {
    float speed;
    unsigned_16 data_status;
}GROUNDSPEED_INFO;

typedef struct {
    float rpm;
    bool_least_t rpm_faulted;
} ENGSPEED_INFO;

typedef struct {
    int_32 cylinder_velocity; /* 0.1 mm/s/bit */
    unsigned_16 data_status;
} CYL_VELOCITY_INFO;

typedef struct {
    float lift_valve_command_pct;
    bool_least_t lever_in_raise_detent;
    bool_least_t lever_in_lower_detent;
    bool_least_t lever_in_center;
    bool_least_t lever_faulted;
} LIFT_INFO;

typedef struct {
    float tilt_valve_command_pct;
} TILT_INFO;

typedef struct {
    unsigned_16 fuel_input;
    unsigned_16 fuel_status;
}FUEL_RATE_INFO;

typedef struct {
    unsigned_16 gear;
    unsigned_16 gear_status;
}GEAR_INFO;

typedef struct {
    float percentage;
    unsigned_16 percentage_status;
}PERCENT_INFO;

typedef struct
{
    char name[PROD_SIZE_OF_MAT_NAME];
    unsigned_8  length;
    unsigned_8  status;
}   MAT_NAME;

typedef struct
{
    char name[PROD_SIZE_OF_TRUCK_NAME];
    unsigned_8  length;
    unsigned_8  status;
}   TRUCK_NAME;

typedef struct {

    char name[PROD_SIZE_OF_OP_ID_DESC];
    unsigned_8 length;
    unsigned_8 status;

}OPERATOR_ID_DESC;


typedef struct
{
    char name[PROD_SIZE_OF_STATUS_STR];
    unsigned_8 length;
}   STATUS_NAME;

PROD_CORE_PRAGMA_PACK_PUSH(1)
typedef PROD_CORE_PACKED struct
{
   unsigned_8   sec;
   unsigned_8   min;
   unsigned_8   hour;
   unsigned_8   mon;
   unsigned_8   day;
   unsigned_8   year;
}bdt_clock_stamp;
PROD_CORE_PRAGMA_PACK_POP()


typedef struct  {
    struct {
      unsigned_8 quarter_sec;  /* range 0-63.75 s */
      unsigned_8 min;   /* range 0-255 min */
      unsigned_8 hour;  /* range 0-255 hours */
    } clock;
    struct {
      unsigned_8 quarter_day;   /* range 0-63.75 days */
      unsigned_8 month;  /* range 0-255 months, with 0=null, 1= Jan, etc */
      unsigned_8 year;  /* year- 1985.  Range is 0-255, or 1985-2240 AD. */
    } date;
}   PCS_TIME;

typedef struct {
    int numColumns;
    int numRows;
    float const * columnAxis;
    float const * rowAxis;
    float const * data;
} PCSMap_t;

typedef struct {
   char Model_Number[16];
   char Serial_No_Prefix[3];
   char Pad[1];
   float stage_one_cf;
   float stage_two_cf;
   float stage_three_cf;
   unsigned_16 target_weight;
   float start_of_weigh;
   float end_of_weigh;
   float weigh_range_min;
   float tilt_full_dump_threshold;
   float tilt_partial_threshold;
   float tilt_full_rack_bkt_angle;
   float dig_start_limit;
   float dig_end_limit;
   float dig_dur_min_limit;
   float dig_dur_max_limit;
   float wt_stable_limit;
   float wt_stable_dur_limit;
   float lift_lower_vel_limit;

   /* Lift Cylinder(s) Properties */
   float lift_bore_diameter; /* millimeters */
   float lift_rod_diameter; /* millimeters */
   unsigned_8 lift_num_cylidners;

   /* Temp Comp V2 line loss model coefficients */
   float lift_he_line_loss_2nd_ord_coeff; /* Q^2 term */
   float lift_he_line_loss_1st_ord_coeff; /* Q term */
   float lift_re_line_loss_2nd_ord_coeff; /* Q^2 term */
   float lift_re_line_loss_1st_ord_coeff; /* Q term */

   float tilt_cyl_ext_threshold;
   float tilt_angle_abc_threshold;

   float kg_per_kpa_at_mid_extension; /* kg/kPa, used to estimate calibration weight. */
   float lift_kpa_no_bucket_mid_extension; /* Effective lift head end pressure for linkage with no bucket at 50% cylinder extension */

   PCSMap_t tilt_compensation_map;
   float cal_slow_raise_command;
   float cal_fast_raise_command;
   float cal_slow_lower_command;
   float cal_fast_lower_command;

   float zero_range_limit;

} MODEL_SPECIFIC_VALUES;

typedef struct {

   unsigned_16 auto_delaycode_timeout_input;
   unsigned_16 auto_delaycode_timeout_status;

}AUTO_DELAYCODE_TIMEOUT_INFO;

typedef struct {

   unsigned_32 truck_index_input;
   unsigned_16 truck_index_status;

}TRUCK_INDEX_INFO;

typedef struct {

   float truck_target_weight_input;
   unsigned_16 truck_target_weight_status;

}TRUCK_TARGET_WEIGHT_INFO;

typedef struct {

    float raise_cal_pct_diff_abs_limit;
    float raise_cal_pct_diff_range_limit;
    float lower_cal_pct_diff_abs_limit;
    float lower_cal_pct_diff_range_limit;
}PCS_CAL_DIFF_LIMITS;

PROD_CORE_PRAGMA_PACK_PUSH(1)
typedef PROD_CORE_PACKED struct {

    unsigned_8 byte1;
    unsigned_8 byte2;
    unsigned_8 byte3;
    unsigned_8 byte4;
    unsigned_8 byte5;
    unsigned_8 byte6;
}PCS_GPS_STAMP;
PROD_CORE_PRAGMA_PACK_POP()

/*  ADDITION FOR SCALELESS CAL  */

typedef struct{
    float angle;        /*  Should be in 0.01 degrees   */
    unsigned_8 data_status;
}ANGLE_INFO;

typedef struct{
    float length;       /*  Should be in 0.1 mm */
    unsigned_8 data_status;
}CYL_LENGTH;

typedef struct{
    float pos_percent;      /*  Should be in 0.50%  */
    unsigned_8 data_status;
}LEV_POS_INFO;

typedef struct{
    unsigned_8 park_brake_status;   /*  Either 0 or 1   */
    unsigned_8 data_status;
}BRAKE_INFO;

typedef struct {

    float value;
    unsigned_16 data_status;
}LOAD_RATIO_INFO;

#define MAX_CYCLE_CNT 50
#define MAX_STATUS_CNT 50
#define MAX_STATUS_RECS_STORED_IN_BUFFER 5

/* Added a new structure for the Payload weight and Payload Calculation Method */
typedef struct {

    float weight; /* this should be in tonnes */
    unsigned_16 weight_status; /* this is for the Payload weight availability status*/
    //unsigned_16 accuracy; /* this is either 0,1,2,3 depending on none, low, medium and high accuarcy*/
    unsigned_16 payload_calc_method; /* In the 2 byte payload calculation method, accuracy is the 2nd MS nibble */
}PAYLOAD_INFO;


typedef struct {

   unsigned_32 truck_id_number;
   unsigned_8 status;

}TRUCK_ID_NUM;

typedef struct {

   unsigned_32 material_id_number;
   unsigned_8 status;

}MATERIAL_ID_NUM;

typedef struct {

   unsigned_32 material_index_input;
   unsigned_8 material_index_status;

}MATERIAL_ACTIVE_INDEX;

PROD_CORE_PRAGMA_PACK_PUSH(1)
typedef PROD_CORE_PACKED struct
{
    float payld_weight;     /* Payload weight of the most recent payload record */
    float payload_time_offset;     /* Payload time offset of the most recent payload record */
    unsigned_16 payld_calc_method;  /* Payload calculation method of the most recent payload record */
    unsigned_16 pad;
    // Payload start time is also part of payload record, but its not included in this structure since its already stored in NVM

}LAST_PAYLOAD_REC_DATA;
PROD_CORE_PRAGMA_PACK_POP()

/******************************************************************/
/* Typedefs for function pointers                                 */
/******************************************************************/
typedef PRESSURE_INFO pcs_get_head_pressure(void);
typedef PRESSURE_INFO pcs_get_rod_pressure(void);
typedef POS_INFO pcs_get_raw_pos_dutycycle(void);
typedef POS_INFO pcs_get_raw_tilt_dutycycle(void);
typedef GEAR_INFO pcs_get_operator_requested_gear(void);
typedef TEMP_INFO pcs_get_hydraulic_oil_temp(void);
typedef GROUNDSPEED_INFO pcs_get_ground_speed(void);
typedef ENGSPEED_INFO pcs_get_engine_speed(void);
typedef ENGSPEED_INFO pcs_get_engine_speed_high_idle(void);
typedef CYL_VELOCITY_INFO pcs_get_lift_cyl_velocity(void);
typedef PERCENT_INFO pcs_get_cylinder_extension_percent(void);
typedef PERCENT_INFO pcs_get_tilt_angle_abc_percent(void);
typedef FUEL_RATE_INFO pcs_get_fuel_rate(void);
typedef int pcs_get_store_switch(void);
typedef int pcs_get_reweigh_switch(void);
typedef int pcs_get_zero_switch(void);
typedef void pcs_cal_app_inf_cal_ovr_ctrl(bool_least_t enable);
typedef LIFT_INFO pcs_get_lift_info(void);
typedef TILT_INFO pcs_get_tilt_info(void);
typedef MAT_NAME pcs_get_mat_name(void);
typedef void pcs_start_status_delay(PCS_TIME start_time);
typedef void pcs_end_status_delay(PCS_TIME end_time);
typedef void pcs_start_truckload(PCS_TIME start_time);
typedef void pcs_end_truckload(PCS_TIME end_time, float end_weight);
typedef void pcs_calc_cycle_duration(unsigned_32 length);

typedef int_8 pcs_post_eddt(unsigned_8 type, unsigned_16 id, unsigned_8 modifier, unsigned_8 status);
typedef int_8 pcs_init_eddt(unsigned_16 id, unsigned_8 type, unsigned_8 fmi, unsigned_8 wci, \
                            unsigned_16 active_debounce, unsigned_16 inactive_debounce, unsigned_16 log_debounce);
typedef void pcs_init_dl(void);
typedef void pcs_update_dl(void);
typedef int_32 pcs_bdt_get_connection(bdt_connection_t* data);
typedef void pcs_set_payload_horn(void);
typedef PCS_TIME pcs_get_real_time_clock(void);
typedef PCS_TIME pcs_get_local_time(void);
typedef int_16 pcs_get_tz_offset (void);
typedef int_8 pcs_get_tz_offset_descp_index (void);
typedef TRUCK_NAME pcs_get_truck_name(void);
typedef MODEL_SPECIFIC_VALUES const * pcs_get_model_specific_values(void);
typedef AUTO_DELAYCODE_TIMEOUT_INFO pcs_get_auto_delaycode_timeout(void);
typedef TRUCK_INDEX_INFO    pcs_get_truck_index(void);
typedef TRUCK_TARGET_WEIGHT_INFO    pcs_get_truck_target_weight(void);
typedef void pcs_set_truck_index(unsigned_32 current_index);
typedef void pcs_enable_disable_qual_read(unsigned_8 cmd, int_16* minvalue);
typedef void pcs_get_mat_info(pcs_material_type *mat_info);
typedef void pcs_send_truck_ticket(PCS_TRUCK_TICKET *trck_ticket, float* weights, boolean autostore);
typedef PCS_CAL_DIFF_LIMITS pcs_get_pct_diff_limits(void);
typedef unsigned_32 pcs_get_operator_id(void);
typedef unsigned_16 pcs_get_matid_density(void);
typedef PCS_GPS_STAMP pcs_get_gps_stamp(void);
typedef STATUS_NAME pcs_get_status_name(void);
typedef boolean pcs_get_cpm_install_status(void);
typedef TRUCK_ID_NUM pcs_get_truck_ID_num(void);
typedef MATERIAL_ID_NUM pcs_get_material_ID_num(void);
typedef OPERATOR_ID_DESC pcs_get_operator_ID_desc(void);
typedef MATERIAL_ACTIVE_INDEX pcs_get_material_active_index(void);

/*  ADDITION FOR SCALELESS CAL  */

typedef PRESSURE_INFO pcs_get_tilt_head_pressure(void);
typedef PRESSURE_INFO pcs_get_tilt_rod_pressure(void);
typedef PRESSURE_INFO pcs_get_impl_valve_pressure(void);
typedef ANGLE_INFO pcs_get_lift_arm_angle(void);
typedef ANGLE_INFO pcs_get_mach_incl_angle(void);
typedef ANGLE_INFO pcs_get_tilt_link_angle_abc(void);
typedef POS_INFO pcs_get_normalized_tilt_sensor_pos(void);
typedef LEV_POS_INFO pcs_get_lift_lever_pos(void);
typedef LEV_POS_INFO pcs_get_tilt_lever_pos(void);
typedef CYL_LENGTH pcs_get_tilt_cyl_length(void);
typedef BRAKE_INFO pcs_get_park_brake_status(void);
typedef GEAR_INFO pcs_get_transmission_gear(void);
typedef CYL_VELOCITY_INFO pcs_get_tilt_cyl_velocity(void);

typedef REALTIME_STAMP pcs_get_utc_timestamp(void);


/******************************************************************/
/* Defines                                                        */
/******************************************************************/
/* timestep limits */
/* NOTE: the time step for the task period and the io period must be the same */
#define PCS_TASK_PERIOD_MIN 10  /* min period in ms */
#define PCS_TASK_PERIOD_MAX 40 /* max period in ms */
#define PCS_IO_PERIOD_MIN 10    /* min period in ms */
#define PCS_IO_PERIOD_MAX 40    /* max period in ms */

/* pcs library operation modes */
#define PCS_UNCALIBRATED 0
#define PCS_WEIGH_MODE 1
#define PCS_ADJUST_CAL_MODE 2
#define PCS_STANDBY_MODE 3
#define PCS_EXCESS_MODE 4

/* return values for pcs_init func */
#define PCS_INIT_SUCCESS 0
#define PCS_INVALID_NVM 1
#define PCS_INVALID_FUNC 2
#define PCS_INVALID_TSTEP 3
#define PCS_INVALID_SENSOR 4
#define PCS_INVALID_DATALINKS 5
#define PCS_DISABLED 6

/* size of NVM block for setup data PCS needs to store */
#define PCS_NVM_SIZE_SETTINGS sizeof(PCS_SETTINGS)
/* We need more blocks than just this one! */
#define PCS_NVM_SIZE_PIECEWISE_CAL sizeof(PCS_PIECEWISE_LIN_CAL)
#define PCS_NVM_SIZE_QUADRATIC_CAL sizeof(PCS_QUADRATIC_FIT_CAL)
#define PCS_NVM_SIZE_CUMS sizeof(PCS_CUMULATIVES)
#define PCS_NVM_SIZE_STORED_STATE sizeof(PCS_STORED_STATE)
#define PCS_NVM_SIZE_ELIM sizeof(PCS_ERROR_LIMITS)
#define PCS_NVM_SIZE_GEN_CAL sizeof(PCS_CAL_GENERAL)

#define SIZE_OF_MAT_ID 16
#define SIZE_OF_OP_ID 7
#define SIZE_OF_TRUCK_ID 8
#define SIZE_OF_TRUCK_MODEL 6
#define SIZE_OF_TRUCK_TYPE 2
#define SIZE_OF_SITE_ID 16
#define SIZE_OF_STATCODE_ID 16
#define SIZE_OF_TRUCK_HASH_UID 12
#define SIZE_OF_TRUCK_NAME_UID 16
#define SIZE_OF_MATID_NAME_UID 32
#define SIZE_OF_STATUS_NAME_PID 24   /* app use this #define to get the right number of valid bytes from the PID */
#define SIZE_OF_OPERATOR_ID 4
#define SIZE_OF_MATID_DENSITY 2
#define SIZE_OF_TOTAL_UIDS (SIZE_OF_MATID_NAME_UID+SIZE_OF_MATID_DENSITY+SIZE_OF_OPERATOR_ID+SIZE_OF_TRUCK_NAME_UID+SIZE_OF_TRUCK_HASH_UID)
#define SIZE_OF_STATUS_UIDS 54


#define MAX_MATERIAL_RECS   21
#define MAX_LOAD_SITE_RECS  41
#define MAX_DELAY_CODE_RECS 21
#define MAX_TRUCK_ID_RECS   50




/* values used for diag and event support */

/* This value is the total number of events and diagnostic that the PCs
   library initializes inside the component.  This value is to be used
   by the application to defined its config sizes. */
#define NUMBER_OF_PCS_DIAG_EVNT 15
#define PCS_DIAG 0
#define PCS_EVENT 1
#define PCS_INACTIVE 0
#define PCS_ACTIVE 1
#define PCS_NVM_CID 591
#define PCS_NVM_FMI 12
#define PCS_POS_SENSOR_CID 1964
#define PCS_OUT_OF_CAL_FMI 13
#define PCS_PAYLOAD_LOW_EID 2083
#define PCS_PAYLOAD_LOW_WCI 1
#define PCS_PAYLOAD_FULL_EID 2138
#define PCS_PAYLOAD_FULL_WCI 2
#define PCS_LIFT_TOO_SLOW_EID 1027
#define PCS_LIFT_TOO_SLOW_WCI 1
#define PCS_LIFT_TOO_JERKY_EID 1043
#define PCS_LIFT_TOO_JERKY_WCI 1
#define PCS_LIFT_SPD_ICSNT_EID 1042
#define PCS_LIFT_SPD_ICSNT_WCI 1
#define PCS_LIFT_STOPPED_EID 1028
#define PCS_LIFT_STOPPED_WCI 1
#define PCS_UNCALIBRATED_CID 2183
#define PCS_UNCALIBRATED_FMI 13
#define PCS_RATE_OF_CHANGE_TOO_HIGH_EID 782
#define PCS_RATE_OF_CHANGE_TOO_HIGH_WCI 1
#define PCS_NOT_RACKED_EXCESS_PITCH_EID 783
#define PCS_NOT_RACKED_EXCESS_PITCH_WCI 1
#define PCS_TOO_HEAVY_TO_ZERO_EID 784
#define PCS_TOO_HEAVY_TO_ZERO_WCI 2
#define PCS_CAL_ADJUST_TEMP_SLOPE_INCORRECT_EID 1996
#define PCS_CAL_ADJUST_TEMP_SLOPE_INCORRECT_WCI 2
#define PCS_ZERO_LIFT_NEEDED_EID    643
#define PCS_ZERO_LIFT_NEEDED_WCI    1
#define PCS_PAYLOAD_OVERLOAD_LIMIT_EXCEEDED_EID 2126
#define PCS_PAYLOAD_OVERLOAD_LIMIT_EXCEEDED_WCI 1

/* payload data states */
#define UNAVAILABLE 0
#define AVAILABLE   1

/* values used for datalogger settings */
#define DATALOGGER_ON 1
#define DATALOGGER_OFF 2
#define DATALOGGER_RESET 3
#define DATALOGGER_FULL 4
#define DATALOGGER_BUSY 5
#define DATALOGGER_FAIL 6

/* pcs dig states - these are updated to match cycle segmentation output */
#define DIG_UNKNOWN     0
#define NOT_DIGGING     0
#define TENTATIVE_DIG   1
#define DIGGING         2

/* pcs cal levels */
#define PCS_CAL_UNCAL_LEVEL 0
#define PCS_CAL_PROD_ONLY_LEVEL 1
#define PCS_CAL_SIMPLE_TRUCK_LEVEL 2
#define PCS_CAL_FULL_TRUCK_LEVEL 3

/* pcs skew config levels */
#define PCS_SKEW_LIMIT_OFF 0
#define PCS_SKEW_LIMIT_LOW 1
#define PCS_SKEW_LIMIT_MEDIUM 2
#define PCS_SKEW_LIMIT_HIGH 3

#define SERIAL_NUM_SIZE     20
#define EQUIPMENT_NUM_SIZE  16

/* Cal Adjust Status's */
#define PCS_CAL_ADJUST_INACTIVE     0
#define PCS_CAL_ADJUST_ACTIVE       1
#define PCS_CAL_ADJUST_READY        2
#define PCS_CAL_ADJUST_COMPLETED    3
#define PCS_CAL_ADJUST_SUCCESSFUL   4
#define PCS_CAL_ADJUST_UNSUCCESSFUL 5
#define PCS_CAL_ADJUST_SLOPE_INVALID 6

/* Hydrualic Oil Types */
#define PCS_OIL_TYPE_SAE_10W    0
#define PCS_OIL_TYPE_SAE_0W20   1

#define PCS_REWEIGH_CLEAR_ALL_WARNINGS  0x0000

/*Zero Needed States */
#define PCS_ZERO_NOT_REQUIRED         0
#define PCS_ZERO_REQUIRED_TEMPCHANGE  1
#define PCS_ZERO_REQUIRED_TIMELIMIT   2

#define ON_BOARD_ASCII_PRINTER_SUPPORT 0x01
#define DELAY_CODE_MANAGEMENT 0x02
#define AUTO_HORN_WITH_STORE_SWITCH_PRESS 0x04
#define BUCKET_WEIGHT_WARNINGS 0x08
#define LOW_LIFT_AND_CARRY 0x10

#define TRUCK_NVM_DATA_AND_BDT_CONTROL 0x20
#define TRUCK_ID_NVM 0x40
#define MATERIAL_ID_NVM 0x80
#define LOAD_DATA_NVM 0x100
#define LOADSITE_ID_NVM 0x200
#define PROD_DATA_NM_FT 0x400
#define AUTO_TRUCK_INCREMENT 0x800
#define REWEIGH_CLEAR_ZERO_SWITCHES 0x1000
#define POSITION_SENSOR 0x2000
#define POST_DIAG_EVENT 0x4000
#define OVERLOAD_DEFAULT_OFF 0x8000
#define TEMP_COMP_V2_ENABLE 0x10000
#define CAL_APP_OVERRIDES_SUPPORTED 0x20000
#define FILTER_WT_NOT_PRESS 0x40000
#define TILT_COMPENSATION_SUPPORTED 0x80000
#define MT_IN_PCS_FT 0x100000
#define OB_IN_PCS_FT 0x200000
#define PRT_IN_PCS_FT 0x400000
#define STATUS_UIDS 0x800000
#define SCALELESS_CAL_IN_PCS_FT 0x1000000 // flag for Scale less cal

/* Support for delay code */
#define PRODUCTION_STATUS 3
#define AUTO_DELAY_STATUS 0
#define KEYOFF_STATUS 1
#define KEYON_STATUS 2

/* Cycle Types */
#define PAYLOAD_ACCURACY_NORMAL 0x1001
#define PAYLOAD_ACCURACY_ESTIMATE 0x2001

/* Support for delay code (status mode) */
#define NORMAL_MODE 0

#define MATERIAL_INDEX  0x00000000
#define LOADSITE_INDEX  0x00000001
#define STATCODE_INDEX  0x00000002
#define TRUCK_ID_INDEX  0x00000003

#define NVM_READ_SUCCESS 0
#define NVM_WRITE_SUCCESS 0
#define NVM_READ_FAILURE 0xFFFF
#define NVM_WRITE_FAILURE 0xFFFF

/*loadratio status for ok, faulted, raise_stall and lower_stall. */
#define LOAD_RATIO_OK 0
#define LOAD_RATIO_FAULTED 1
#define LOAD_RATIO_RAISE_STALL 2
#define LOAD_RATIO_LOWER_STALL 3
#define LOAD_RATIO_OUT_OF_CAL 4

/*MACRO for UIDs*/
#define PCS_LOAD_START_TIME_UID_UID 0x81010007
#define PCS_LOAD_START_TIME_UID_ID 0x13
#define PCS_LOAD_START_TIME_UID_SIZE 0x0A
#define PCS_LOAD_START_TIME_UID_DATATYPE 0x13
#define PCS_LOAD_START_TIME_UID_COLOR 0x05
#define PCS_LOAD_START_TIME_UID_DATASOURCE 0x0052

#define PCS_LOAD_END_TIME_UID_UID 0x81010007
#define PCS_LOAD_END_TIME_UID_ID 0x14
#define PCS_LOAD_END_TIME_UID_SIZE 0x0A
#define PCS_LOAD_END_TIME_UID_DATATYPE 0x13
#define PCS_LOAD_END_TIME_UID_COLOR 0x05
#define PCS_LOAD_END_TIME_UID_DATASOURCE 0x0052

#define PCS_STATUS_START_TIME_UID_UID 0x81010007
#define PCS_STATUS_START_TIME_UID_ID 0x1B
#define PCS_STATUS_START_TIME_UID_SIZE 0x0A
#define PCS_STATUS_START_TIME_UID_DATATYPE 0x13
#define PCS_STATUS_START_TIME_UID_COLOR 0x05
#define PCS_STATUS_START_TIME_UID_DATASOURCE 0x0052

#define PCS_STATUS_TRUCK_DESCRIPTION_UID_UID 0x81010028
#define PCS_STATUS_TRUCK_DESCRIPTION_UID_ID 0x00
#define PCS_STATUS_TRUCK_DESCRIPTION_UID_SIZE 0x0C
#define PCS_STATUS_TRUCK_DESCRIPTION_UID_DATATYPE 0x03
#define PCS_STATUS_TRUCK_DESCRIPTION_UID_COLOR 0x19
#define PCS_STATUS_TRUCK_DESCRIPTION_UID_DATASOURCE 0x0190

#define PCS_STATUS_MAT_ID_UID_UID 0x81010027
#define PCS_STATUS_MAT_ID_UID_ID 0x00
#define PCS_STATUS_MAT_ID_UID_SIZE 0x0C
#define PCS_STATUS_MAT_ID_UID_DATATYPE 0x03
#define PCS_STATUS_MAT_ID_UID_COLOR 0x19
#define PCS_STATUS_MAT_ID_UID_DATASOURCE 0x0190

#define PCS_STATUS_MAT_DENSITY_UID_UID  0x81010032
#define PCS_STATUS_MAT_DENSITY_UID_ID 0x00
#define PCS_STATUS_MAT_DENSITY_UID_SIZE 0x02
#define PCS_STATUS_MAT_DENSITY_UID_DATATYPE 0x08
#define PCS_STATUS_MAT_DENSITY_UID_COLOR 0x05
#define PCS_STATUS_MAT_DENSITY_UID_DATASOURCE 0x0190

#define PCS_STATUS_OPERATOR_ID_DESC_UID_UID 0x810D000C
#define PCS_STATUS_OPERATOR_ID_DESC_UID_ID 0x00
#define PCS_STATUS_OPERATOR_ID_DESC_UID_SIZE 0x0C
#define PCS_STATUS_OPERATOR_ID_DESC_UID_DATATYPE 0x03
#define PCS_STATUS_OPERATOR_ID_DESC_UID_COLOR 0x05
#define PCS_STATUS_OPERATOR_ID_DESC_UID_DATASOURCE 0x0129

#define PCS_STATUS_TRUCK_ID_NUM_UID_UID 0x00010460
#define PCS_STATUS_TRUCK_ID_NUM_UID_ID 0x00
#define PCS_STATUS_TRUCK_ID_NUM_UID_SIZE 0x04
#define PCS_STATUS_TRUCK_ID_NUM_UID_DATATYPE 0x0D
#define PCS_STATUS_TRUCK_ID_NUM_UID_COLOR 0x00
#define PCS_STATUS_TRUCK_ID_NUM_UID_DATASOURCE 0x0190

#define PCS_STATUS_MAT_ID_NUM_UID_UID 0x00010462
#define PCS_STATUS_MAT_ID_NUM_UID_ID 0x00
#define PCS_STATUS_MAT_ID_NUM_UID_SIZE 0x04
#define PCS_STATUS_MAT_ID_NUM_UID_DATATYPE 0x0D
#define PCS_STATUS_MAT_ID_NUM_UID_COLOR 0x00
#define PCS_STATUS_MAT_ID_NUM_UID_DATASOURCE 0x0190

#define PCS_PAYLOAD_TIME_OFFSET_UID_UID 0x81010075
#define PCS_PAYLOAD_TIME_OFFSET_UID_ID 0x15
#define PCS_PAYLOAD_TIME_OFFSET_UID_SIZE 0x04
#define PCS_PAYLOAD_TIME_OFFSET_UID_DATATYPE 0x15
#define PCS_PAYLOAD_TIME_OFFSET_UID_COLOR 0x05
#define PCS_PAYLOAD_TIME_OFFSET_UID_DATASOURCE 0x0052

#define PCS_PAYLOAD_CAL_METHOD_UID_UID 0x00011A78
#define PCS_PAYLOAD_CAL_METHOD_UID_ID 0x00
#define PCS_PAYLOAD_CAL_METHOD_UID_SIZE 0x02
#define PCS_PAYLOAD_CAL_METHOD_UID_DATATYPE 0x09
#define PCS_PAYLOAD_CAL_METHOD_UID_COLOR 0x05
#define PCS_PAYLOAD_CAL_METHOD_UID_DATASOURCE 0x0052

#define PCS_PAYLOAD_WEIGHT_UID_UID 0x8101004E
#define PCS_PAYLOAD_WEIGHT_UID_ID 0x00
#define PCS_PAYLOAD_WEIGHT_UID_SIZE 0x04
#define PCS_PAYLOAD_WEIGHT_UID_DATATYPE 0x15
#define PCS_PAYLOAD_WEIGHT_UID_COLOR 0x05
#define PCS_PAYLOAD_WEIGHT_UID_DATASOURCE 0x0052

#define PCS_PAYLOAD_START_TIME_UID_UID 0x81010007
#define PCS_PAYLOAD_START_TIME_UID_ID 0x15
#define PCS_PAYLOAD_START_TIME_UID_SIZE 0x0A
#define PCS_PAYLOAD_START_TIME_UID_DATATYPE 0x13
#define PCS_PAYLOAD_START_TIME_UID_COLOR 0x05
#define PCS_PAYLOAD_START_TIME_UID_DATASOURCE 0x0052

/*For BDT config*/
#define PCS_BDT_CFG_1BYTE_ENCODING 0
#define PCS_BDT_CFG_2BYTE_ENCODING 1


/******************************************************************/
/* Structures                                                     */
/******************************************************************/

typedef enum
{
    PCS_DIG_UNKNOWN = DIG_UNKNOWN,
    PCS_NOT_DIGGING = NOT_DIGGING,
    PCS_TENTATIVE_DIGGING = TENTATIVE_DIG,
    PCS_DIGGING = DIGGING
} pcs_dig_state_t;

typedef struct {
    NVM_BLOCK load_data;
    NVM_BLOCK config_data;           /* repurposed to settings block */
    NVM_BLOCK op_id;
    NVM_BLOCK mat_id;
    NVM_BLOCK truck_id;
    NVM_BLOCK site_id;
    NVM_BLOCK truck_data;
    NVM_BLOCK cal_general;           /* pcs cal general */
    NVM_BLOCK quad_fit;              /* pcs quadratic fit cal */
    NVM_BLOCK piecewise_fit;         /* pcs piecewise linear fit cal */
    NVM_BLOCK error_lim;             /* pcs error limits */
    NVM_BLOCK stored_state;          /* pcs stored state */
    NVM_BLOCK cums;                  /* pcs cums */
    unsigned_8 no_cycle_records;
    unsigned_8 no_status_records;

} NVM_INFO;


typedef struct {
    pcs_init_dl *init_datalink;
    pcs_update_dl *update_datalink;
} DL_INFO;

typedef struct {
    unsigned_8 num_datalinks; /* the number of datalinks to be used */
    DL_INFO *datalinks; /* an array of datalinks to be used */
} DL_CONFIG;

/* NOTE: if you change the size of any of the id strings in the next 4 structs you must
         also change the PCS_LOAD_STORAGE_SIZE macro remember that these are 4 byte aligned */
typedef struct  {
    char        id[SIZE_OF_MAT_ID];
    float       cummulative_weight;
    unsigned_32 load_count;
    int_16      price;
    unsigned_16 pad;                //Pad to insure 32-bit alignment
}   MAT_TYPE;

typedef struct  {
    char        id[SIZE_OF_OP_ID];
    char   pad[1];               //Pad to insire 32-bit alignment
}   OP_TYPE;

typedef struct  {
    char  id[SIZE_OF_TRUCK_ID];
    char  model[SIZE_OF_TRUCK_MODEL];
    unsigned_16 pad;                  /* this is here because we know this structure will have to be padded 4 byte boundaries */
    float target_weight;
}   TRUCK_TYPE;


typedef struct  {
    unsigned_8 id[SIZE_OF_SITE_ID];
}   SITE_TYPE;

typedef struct  {
    unsigned_8 id[SIZE_OF_STATCODE_ID];
}  STAT_TYPE;

typedef struct
{
    unsigned_16 too_slow:1;
    unsigned_16 stopped:1;
    unsigned_16 not_racked:1;
    unsigned_16 jerky:1;
    unsigned_16 inconsistent:1;
    unsigned_16 rate_of_change_hi:1;
    unsigned_16 reweigh_bucket:1;
    unsigned_16 lift_pos_too_high:1;
    unsigned_16 lift_pos_too_low:1;
    unsigned_16 unused:7;
} reweigh_status_t;

/* Settings is used to store Information about the PCS System configuration */
typedef struct  {

    boolean  unused1;
    boolean  unused2;
    boolean  unused3;

    /* settings for various features */
    unsigned_8 unused4;
    unsigned_8 auto_mat_id;
    unsigned_8 auto_truck_id;

    unsigned_8 unused5;
    unsigned_8 unused6;

        /* Load Stats */
    float   loader_target_weight;

    // Weigh Range Limits
    float   start_of_weigh;     // Default at 50%
    float   end_of_weigh;       // Default at 80%

    //unsigned_16 statcode_id;    // Jeff had removed
    unsigned_8  payload_horn_setting;
    unsigned_8 payload_overload_limit_enable_indicator;             //Pad to insure 32-bit alignment
    unsigned_8 payload_loader_target_weight_set;


    unsigned_8 pad;
    unsigned_16 tip_off_mode;
    unsigned_32 load_number;
    unsigned_32 truck_hash_load_num;
    unsigned_32 truck_hash_utc;
    unsigned_32 truck_hash_shm;

    unsigned_32 cycle_fuel;

    /* Payload truck weight behavior */
    unsigned_16 payload_indicator_config;

    /* Payload tip off trigger - see user story 192527 */
    unsigned_16 tip_off_trigger;

    /* Payload display mode status */
    unsigned_16 display_mode_status;

    /* Reserved for future expansion */
    unsigned_8 unused7;
    unsigned_8 unused8;
    unsigned_32 unused[3];

} PCS_SETTINGS;

typedef struct  {
    /* current id's */
    unsigned_32 current_truck;
    unsigned_32 current_op;
    unsigned_32 current_mat;
    unsigned_32 current_site;
    reweigh_status_t reweigh_status;   /* We don't need this unless we need to store all current state including bucket */
    PCS_TIME load_start_time;
    unsigned_32 fuel_used;             /* added by jeff - fuelCumulative+fuel_uncommitted*/
    unsigned_16 payload_tz_offset_start;
    unsigned_16 unused_pad;
    unsigned_32 payload_shm_start;
    float truck_target_wt;
    float app_interface_target_wt;
    unsigned_16 active_truck_index;
    unsigned_16 pad;
    LAST_PAYLOAD_REC_DATA last_payld_rec;     /* most recent payload record data */
    float unused[2];

}  PCS_STORED_STATE;

/* CUMULATIVES is used to store Information about the PCS System */
typedef struct  {

    /* lifetime cummulatives - removed by jeff
    float       lifetime_cummulative_weight;
    unsigned_32 lifetime_load_count;
    unsigned_32 lifetime_loaded_travel_hours;
    unsigned_32 lifetime_pass_count;
    unsigned_32 lifetime_reweigh_request_count;
    unsigned_32 ticket_number;
    unsigned_32 reweigh_performed_count;
    */
    /* Resettable Load Stats */
    unsigned_32 load_count;
    float       cummulative_weight;
    //unsigned_32 loaded_travel_hours;
    unsigned_32 pass_count;
    //unsigned_32 reweigh_request_count;      // removed by Jeff
    float       intermediate_loaded_hours;  // added to properly calc lifetime travel loaded hours
    unsigned_32 unused[5];

} PCS_CUMULATIVES;

typedef struct  {

    /*Config for Simplecal BDT*/
    unsigned_16 bdt_cfg_char_encoding;               /* 0 for 1 byte ASCII ,1 for 2 byte ASCII */
} BDT_CONFIG;

// Cal Stuff
#define PCS_CAL3_CURVE_FIT_NUM_POINTS (11)

#define PCS_CALIBRATION_VERSION_QUAD_VELCOMP (0x11111111)
#define PCS_CALIBRATION_VERSION_PWLIN_VELSCALE (0x22222222)
#define PCS_CAL_ENGINE_HIGH_IDLE_RPM           ( (float)1500.0 )


typedef struct  {

    /* Cal Curve lift speeds */
    float raise_speed_empty_fast; /* lift speed when doing empty lift */
    float raise_speed_full_fast;  /* lift speed when doing a full lift */

    float raise_speed_empty_slow;
    float raise_speed_full_slow;

    float raise_fast_delta_p_empty;
    float raise_fast_delta_p_full;

    float raise_slow_empty_lift_heights[PCS_CAL3_CURVE_FIT_NUM_POINTS];
    float raise_slow_empty_pressures[PCS_CAL3_CURVE_FIT_NUM_POINTS];

    float raise_slow_full_lift_heights[PCS_CAL3_CURVE_FIT_NUM_POINTS];
    float raise_slow_full_pressures[PCS_CAL3_CURVE_FIT_NUM_POINTS];

    float lower_slow_empty_lift_heights[PCS_CAL3_CURVE_FIT_NUM_POINTS];
    float lower_slow_empty_pressures[PCS_CAL3_CURVE_FIT_NUM_POINTS];

    float lower_slow_full_lift_heights[PCS_CAL3_CURVE_FIT_NUM_POINTS];
    float lower_slow_full_pressures[PCS_CAL3_CURVE_FIT_NUM_POINTS];

    /* Empty Bucket Weight Estimate */
    float empty_bucket_weight_est;

    float cal_adjust_temp; /* Temporary cal adjustment to be applied when pass count is 0 */

    /* Unused variables for possible future extension */
    float unused1; /* Possibly friction coefficient */

    /* Indicates which hydraulic oil type is being used from the lookup table */
    unsigned_32 hyd_oil_type_index;

    unsigned_32 shm_empty_main;
    unsigned_32 shm_full_main;
    unsigned_32 shm_vel_main;

    /* reserved for future expansion */
    float unused[10];

}  PCS_PIECEWISE_LIN_CAL;

typedef struct  {
    // Calibrations States
    unsigned_16     steps_complete;

    // Lift Extension
    unsigned_16 bottom_of_lift;     // Raw bits Bottom
    unsigned_16 top_of_lift;        // Raw bits Top

    unsigned_16 pad;                // Pad to maintian 32-bit alignment
    uint32_t calibration_version;
    // Velocity Slope adjusts pressure as a function of lift speed to make it look like
    // a curve done at calibration speed
    float vel_slope;

    // Calibration Weight
    float cal_weight;
    // Zero Weight
    float zero_weight;
    // Wt and Temp Factors
    float   cal_adjust;             // Default 0.0
    float   temp_slope;         // Default 0.0

    /* hydraulic oil temps for empty and full calibration curves */
    float empty_temp;
    float full_temp;

    /* reserved for future expansion */
    float unused[5];

    unsigned_32 shm_pos_main;
    unsigned_32 block_signature;
} PCS_CAL_GENERAL;

/* Use only one of Quadratic fit / piecewise linear */
typedef struct  {
    // Cal Curves
    float ecurve[3];        // Empty Cal Curve
    float fcurve[3];        // Full Cal Curve
    float vcurve[3];        // Full Velocity Curve
    float lift_speed_empty;
    float lift_speed_full;
    unsigned_32 shm_empty_wt_main;
    unsigned_32 shm_full_wt_main;
    unsigned_32 shm_vel_cmp_main;
    unsigned_32 shm_vel_2pt_main;
}  PCS_QUADRATIC_FIT_CAL;        // lift speed empty - lift speed full - in jeffs doc, not existing in software

typedef struct  {
    float   min_std_prcnt;      // the minimum percent wt_std must be from calc weight for reweigh events to be checked (%)
    int_16      max_wt_std;         // Standard Deviation on Weight (Kg)
    int_16      max_wt_absdiff;     // Max Diff Highest to Lowest   (Kg)
    int_16      max_wt_skew;        // skew * 100 (no units)  gives some resolution
    int_16      max_vel_std;        // Standard Deviation of Velocity (%/s)
    unsigned_16 overload_percent;   // percent we trigger overload in 0.1%
    unsigned_16 pad;                // pad for 32-bit alignment
    unsigned_32 unused[3];          /* Unused for future expansion */
} PCS_ERROR_LIMITS;

typedef struct  {
    PCS_SETTINGS setup;
    PCS_CUMULATIVES cums;
    PCS_ERROR_LIMITS elim;
    PCS_STORED_STATE stored;
    PCS_CAL_GENERAL cal_gen;
    PCS_QUADRATIC_FIT_CAL quad;
    PCS_PIECEWISE_LIN_CAL cal;
}   NVMDATA;

typedef struct  {
    unsigned_8  op_id;
    unsigned_8  mat_id;
    unsigned_8  truck_id;
    unsigned_8  site_id;
    unsigned_32 ticket_number;
    unsigned_16 pass_count;
    PCS_TIME    timestamp;
    float       weight;
} STORE;

typedef struct  {
    char        op_id[SIZE_OF_OP_ID];
    char        mat_id[SIZE_OF_MAT_ID];
    char        truck_id[SIZE_OF_TRUCK_ID];
    char        site_id[SIZE_OF_SITE_ID];
    unsigned_32 ticket_number;
    int         pass_count;
    PCS_TIME    timestamp;
    float       weight;
} LOAD_DATA;

typedef struct  {
    int_32      head_press;     // In KPa
    int_32      rod_press;      // In Kpa
    int_16      unfil_pos;      // In 0.1%
    unsigned_16 diff_press;     // In KPa (plenty of resolution)
    unsigned_16 pos;            // In % * 10 so 0 - 1000
    int_16      vel;            // Velocity in % * 10/s
    unsigned_16 weight;         // In Metric Tons
    unsigned_8  temp;           // In degrees C
    unsigned_8  pad;            // this is to keep alignment
}   RECORD_PACKET;

typedef void pcs_print_ticket_t(STORE* store_data);
typedef void pcs_print_totals_t(unsigned_16 setting);

typedef struct
{
    pcs_print_ticket_t* pcs_print_ticket;
    pcs_print_totals_t* pcs_print_totals;
}   PCS_MAIN_OFFBOARD_FUNC;



typedef struct
{
    unsigned_8 on_board_ascii_printer;
    unsigned_8 delay_code_management;
    unsigned_8 auto_horn_store_sw;
    unsigned_8 bucket_weight_warnings;
    unsigned_8 low_lift_carry;
    unsigned_8 truck_nvm_data_bdt_control;
    unsigned_8 truck_id_nvm;
    unsigned_8 mat_id_nvm;
    unsigned_8 load_data_nvm;
    unsigned_8 loadsite_id_nvm;
    unsigned_8 delay_code_nvm;
    unsigned_8 auto_truck_inc;
    unsigned_8 reweigh_clear_zero_sw;
    unsigned_8 pos_snsr;
    unsigned_8 post_diag_event;
    unsigned_8 bucket_weight_default_off;
    unsigned_8 temp_comp_v2_enable;
    bool_least_t cal_app_overrides_supported;
    bool_least_t filter_wt_not_press;
    bool_least_t tilt_compensation_supported;
    bool_least_t prod_data_nm_ft;
    bool_least_t mt_in_pcs_ft;
    bool_least_t ob_in_pcs_ft;
    bool_least_t prt_in_pcs_ft;
    bool_least_t status_uids;
    bool_least_t scaleless_cal_in_pcs_ft;
} version_type_t;

typedef struct              /* DATA STORED PER TRUCK */
{

   unsigned_16 loadsite_id;     /* id (config index) of the load site */
   unsigned_16 blast_num;       /* the blast number */
   unsigned_16 mtl_id;          /* id (config index) of the material */
   unsigned_16 customer_id;
   unsigned_16 cycle_timer_cnt;
   unsigned_16 cycle_count;
   unsigned_16 operator_id[SIZE_OF_OP_ID + 1];
   unsigned_16 truck_name[SIZE_OF_TRUCK_ID + 1];
   unsigned_16 status_count;
   unsigned_16 truck_index;
   bdt_clock_stamp timestamp;
   unsigned_32 shm;


} TRUCK_RECORD_DATA;

typedef struct              /* DATA STORED PER LOAD CYCLE */
 {

   unsigned_16  record_number;
   int_16        bkt_wt;            /* the weight in the bucket */
   bdt_clock_stamp weigh_time;      /* cycle time */
   unsigned_32 fuel_used;           /* KJL June 29, 1998 Fuel used in cycle */
   unsigned_16 cycle_accuracy;
} CYCLE_RECORD_DATA;


typedef struct              /* STORED STATUS CHANGE INFORMATION */
{

   unsigned_16 record_number;
   unsigned_16 status_id;           /* the status code ID */
   unsigned_16 mode;            /* status specific mode */
   bdt_clock_stamp timestamp;           /* time the status change occured */
   unsigned_32 shm;
} STATUS_RECORD_DATA;

typedef struct
{
   TRUCK_RECORD_DATA truck_rec;     /* The current truck record */
   CYCLE_RECORD_DATA *cycle_lst;    /* The cycle records */
   STATUS_RECORD_DATA *status_lst;  /* The status records */
}STORE_PAYLOAD_DATA;

typedef struct
{
    float *start_ptr;
    float *end_ptr;
    float *fixed_end_ptr;
    float *fixed_start_ptr;
    float *index_ptr;
    unsigned_8 max_samples;
} WT_RATE_CHANGE_PTRS;

// time block that will be used by PD callback functions
PROD_CORE_PRAGMA_PACK_PUSH(1)
typedef PROD_CORE_PACKED struct
{
    unsigned_32 tm_utc;
    int_16 tmZoneOffset;
    unsigned_32 tm_shm;
}PCS_TIME_PD_BLOCKS;
PROD_CORE_PRAGMA_PACK_POP()

typedef void pcs_send_truck_data(unsigned_8 no_cycle_records,unsigned_8 no_status_records,STORE_PAYLOAD_DATA* data);

typedef struct {
   pcs_get_head_pressure *get_head_pressure;
   pcs_get_rod_pressure *get_rod_pressure;
   pcs_get_raw_pos_dutycycle *get_raw_pos_dutycycle;
   pcs_get_hydraulic_oil_temp *get_hydraulic_oil_temp;
   pcs_get_store_switch *get_store_switch;
   pcs_get_reweigh_switch *get_reweigh_switch;
   pcs_get_zero_switch *get_zero_switch;
   pcs_set_payload_horn *set_payload_horn;
   pcs_post_eddt *post_eddt;
   pcs_init_eddt *init_eddt;
   unsigned_16 pcs_task_period;     /* period (in ms) that pcs_task is called at */
   unsigned_8 pcs_io_period;        /* period (in ms) that io_task is called at */
   unsigned_32  data_logger_mem_size;   /* The amount of RAM the data logger will use in bytes */
   pcs_bdt_get_connection *bdt_get_connection;
   pcs_get_fuel_rate *get_fuel_rate_info;
   pcs_get_real_time_clock *get_real_time_clock;
   pcs_get_model_specific_values *get_model_specific_info;
   pcs_send_truck_data   *send_truck_info_data;
   pcs_get_auto_delaycode_timeout *get_auto_delaycode_timeout_info;
   pcs_get_truck_index *get_truck_index;
   pcs_get_truck_target_weight *get_truck_target_weight;
   pcs_set_truck_index *set_truck_index;
   pcs_enable_disable_qual_read *qual_read_enable_disable;
   pcs_get_raw_tilt_dutycycle *get_raw_tilt_dutycycle;
   pcs_get_ground_speed *get_ground_speed;
   pcs_get_operator_requested_gear *get_requested_gear;
   pcs_get_cylinder_extension_percent *get_tilt_cyl_ext_percent;
   pcs_get_tilt_angle_abc_percent *get_tilt_angle_abc_percent;
   pcs_get_lift_cyl_velocity* get_lift_cyl_velocity;
   pcs_cal_app_inf_cal_ovr_ctrl* cal_ovr_ctrl;
   pcs_get_lift_info* get_lift_info;
   pcs_get_tilt_info* get_tilt_info;
   pcs_get_engine_speed* get_engine_speed;
   pcs_get_mat_name* get_mat_name;
   pcs_get_mat_info* get_mat_info;
   pcs_start_status_delay *start_status_delay;
   pcs_end_status_delay *end_status_delay;
   pcs_start_truckload *start_truckload;
   pcs_end_truckload *end_truckload;
   pcs_send_truck_ticket *send_truck_ticket;
   pcs_calc_cycle_duration *calc_cycle_duration;
   pcs_get_operator_ID_desc *get_operator_ID_desc;
   pcs_get_pct_diff_limits *get_pct_diff_limits;
   pcs_get_operator_id *get_operator_id;
   pcs_get_matid_density *get_matid_density;
   pcs_get_gps_stamp *get_gps_stamp;
   pcs_get_status_name *get_status_name;
   pcs_get_local_time *get_local_time;
   pcs_get_cpm_install_status *get_cpm_install_status;
   pcs_get_tz_offset *get_timezone_offset;
   pcs_get_tz_offset_descp_index *get_timezone_offset_descp_index;
   pcs_get_truck_name* get_truck_name;
   pcs_get_truck_ID_num* get_truck_ID_num;
   pcs_get_material_ID_num* get_material_ID_num;
   pcs_get_material_active_index* get_material_active_index;

   /*   Addition for Scaleless Cal  */

   pcs_get_tilt_head_pressure* get_tilt_head_pressure;
   pcs_get_tilt_rod_pressure* get_tilt_rod_pressure;
   pcs_get_impl_valve_pressure* get_impl_valve_pressure;
   pcs_get_lift_arm_angle* get_lift_arm_angle;
   pcs_get_mach_incl_angle* get_mach_incl_angle;
   pcs_get_tilt_link_angle_abc* get_tilt_link_angle_abc;
   //pcs_get_tilt_link_angle_efb* get_tilt_link_angle_efb;
   pcs_get_normalized_tilt_sensor_pos* get_normalized_tilt_sensor_pos;
   pcs_get_lift_lever_pos* get_lift_lever_pos;
   pcs_get_tilt_lever_pos* get_tilt_lever_pos;
   pcs_get_tilt_cyl_length* get_tilt_cyl_length;
   pcs_get_park_brake_status* get_park_brake_status;
   pcs_get_transmission_gear* get_transmission_gear;
   pcs_get_tilt_cyl_velocity* get_tilt_cyl_velocity;

   pcs_get_utc_timestamp* get_utc_timestamp;

   prod_get_keyoff_status* pcs_get_keyoff_status;
   pcs_get_engine_speed* get_engine_speed_high_idle;

} FUNC_INFO;


/*function pointersof callback functions for Productivity data*/
/*Load block*/
//PD_FUNC_PTR *pcs_pd_get_load_start_time;

//extern PD_FUNC_PTR* pcs_pd_get_load_end_time;

/*status block*/
//extern PD_FUNC_PTR* pcs_pd_get_status_start_time;
//extern PD_FUNC_PTR* pcs_pd_get_truck_name;
//extern PD_FUNC_PTR* pcs_pd_get_material_name;
//extern PD_FUNC_PTR* pcs_pd_get_material_density;
//extern PD_FUNC_PTR* pcs_pd_get_operator_id;


/*payload block*/

//extern PD_FUNC_PTR* pcs_pd_get_payload_time_offset;
//extern PD_FUNC_PTR* pcs_pd_get_payload_cal_method;
//extern PD_FUNC_PTR* pcs_pd_get_payload_weight;
//extern PD_FUNC_PTR* pcs_pd_get_payload_start_time;



/*Ready to trigger flags extern*/
extern unsigned_8 load_trigger_flag;
extern unsigned_8 payload_trigger_flag;
extern unsigned_8 status_trigger_flag;

extern unsigned_8 PID_write_hdlr_target_weight_flag;
extern unsigned_8 App_truck_index_comparison_flag;

/*To use in printer ticket*/
extern MATERIAL_ACTIVE_INDEX curr_mat_index;
extern TRUCK_INDEX_INFO curr_trk_index_for_prt_tkt;

/******************************************************************/
/* Macros                                                         */
/******************************************************************/
/* size of NVM block for PCS load data */
#define PCS_LOAD_STORAGE_SIZE(MAX_LOADS) (sizeof(STORE) * MAX_LOADS) + 4
#define PCS_MAT_ID_STORAGE_SIZE(MAX_MATS) (sizeof(MAT_TYPE) * MAX_MATS) + 4
#define PCS_OP_ID_STORAGE_SIZE(MAX_OPS) (sizeof(OP_TYPE) * MAX_OPS) + 4
#define PCS_TRUCK_ID_STORAGE_SIZE(MAX_TRUCKS) (sizeof(TRUCK_TYPE) * MAX_TRUCKS) + 4
#define PCS_SITE_ID_STORAGE_SIZE(MAX_SITES) (sizeof(SITE_TYPE) * MAX_SITES) + 4
#define PCS_DATA_LOGGER_STORAGE_SIZE(NUM_RECORDS) sizeof(RECORD_PACKET) * NUM_RECORDS
#define PCS_DATA_TRUCK_ID_STORAGE_SIZE(MAX_CYCLES,MAX_STATUSES) (sizeof(TRUCK_RECORD_DATA) + (MAX_CYCLES * sizeof(CYCLE_RECORD_DATA)) + (MAX_STATUSES * sizeof(STATUS_RECORD_DATA)))

/******************************************************************/
/* Functions defined by the component to be used by the application */
/******************************************************************/


/* This is the recommended update function. It calls both io_task and pcs_task */
extern void pcs_20ms_update(void);

/* Keeping the following  for backward compatibility */
/* update functions - io_task must be called before pcs_task if these are put in the same task */
extern void pcs_task(void);
extern void io_task(void);


/* Since I have removed the compiler flag in the makefile, the following proto needs to be declared */
extern unsigned_8 pd_add_load_record_start_placeholder(unsigned_32 time, PROD_REALTIME_STATUS_T status);
extern boolean check_payload_rec_nvm_data(void);


unsigned_8 pcs_init(NVM_INFO *nvm_space,
                    FUNC_INFO *func_ptrs,
                    DL_CONFIG *coms,
                    PCS_MAIN_OFFBOARD_FUNC *offboard_func_ptrs,
                    unsigned_8 enable,
                    unsigned_32 version,
                    unsigned_32 block_signature,
                    MODEL_SPECIFIC_VALUES const * model_spec_vals_default,
                    BDT_CONFIG *bdt_config);

/* data access functions */
unsigned_8 get_pcs_config_2(void);
void set_pcs_config_2(unsigned_8 config);
unsigned_16 get_payload_indicator_config(void);
void set_payload_indicator_config(unsigned_16 config);
unsigned_8 get_datalogger_status(void);
unsigned_8 set_datalogger_status(unsigned_8 state);

unsigned_8 get_PID_write_hdlr_target_weight_flag(void);
unsigned_8 get_App_truck_index_comparison_flag(void);

unsigned_32 get_resettable_load_count(void);
void set_resettable_load_count(unsigned_32 count);

unsigned_32 get_truck_id(void);
void set_truck_id(unsigned_32 id);
unsigned_32 get_op_id(void);
void set_op_id(unsigned_32 id);
unsigned_32 get_mat_id(void);
void set_mat_id(unsigned_32 id);
unsigned_16 get_site_id(void);
void set_site_id(unsigned_16 id);
unsigned_16 get_excess_mat_ready(void);
void set_excess_mat_ready(unsigned_16 material_ready);
unsigned_16 get_excess_mat_location(void);
void set_excess_mat_location(unsigned_16 material_location);
unsigned_16 get_tip_off_mode(void);
void set_tip_off_mode(unsigned_16 tip_off_setting);

//unsigned_32 get_resettable_loaded_travel_hours(void);
//void set_resettable_loaded_travel_hours(unsigned_32 hours);

float get_resettable_cummulative_weight(void);
void set_resettable_cummulative_weight(float weight);

float get_cal_weight(void);
int_16 get_last_payload_weight(void);
void set_cal_weight(float weight);
float get_oil_temp_comp(void);
void set_oil_temp_comp(float comp);
bool_least_t pcs_is_calibrated(void);
unsigned_8 get_pcs_cal_level(void);
float get_weigh_range_start(void);
void set_weigh_range_start(float pos);
float get_weigh_range_end(void);
void set_weigh_range_end(float pos);
unsigned_8 is_position_cal(void);

float get_loader_target_weight(void);
void set_loader_target_weight(float weight);

unsigned_32 get_resettable_pass_count(void);
void set_resettable_pass_count(unsigned_32 count);

//unsigned_32 get_lifetime_reweigh_request_count(void);
//void set_lifetime_reweigh_request_count(unsigned_32 count);
//unsigned_32 get_resettable_reweigh_request_count(void);
//void set_resettable_reweigh_request_count(unsigned_32 count);
unsigned_32 get_reweigh_performed_count(void);
void set_reweigh_performed_count(unsigned_32 count);

int_16 get_max_lift_vel(void);
void set_max_lift_vel(int_16 vel);
unsigned_8 get_wt_skew_limit(void);
void set_wt_skew_limit(unsigned_8 level);

unsigned_8 get_payload_data_status(void);
float get_payload_free_mem(void);
float get_bucket_payload(void);
float get_lift_cylinder_pos(void);
float get_truck_weight(void);

float get_truck_target_weight(void);
void set_truck_target_weight(float weight);
unsigned_16 get_truck_pass_count(void);
PCS_TIME get_load_cycle_start_time_utc(void);
PCS_TIME get_load_cycle_end_time_utc(void);

void set_hydraulic_oil_temp(int_16 temp,unsigned_16 status);

unsigned_32 get_op_id_data(unsigned_8 **data);
void add_op_id_data(OP_TYPE *data);
unsigned_32 get_mat_id_data(unsigned_8 **data);
void add_mat_id_data(MAT_TYPE *data);
unsigned_32 get_truck_id_data(unsigned_8 **data);
void add_truck_id_data(TRUCK_TYPE *data);
unsigned_32 get_site_id_data(unsigned_8 **data);
void add_site_id_data(SITE_TYPE *data);
unsigned_32 get_statcode_id_data(unsigned_8 **data);

boolean get_load_data(STORE *data);
void reset_payload_memory(void);

float get_cal_adjust_weight(unsigned_32 id);
void set_cal_adjust_weight(float weight, unsigned_32 id);
unsigned_16 get_pcs_mode(void);
void set_pcs_mode(unsigned_16 mode);
void pcs_set_printer_setting(unsigned_8 setting);
unsigned_8  pcs_get_printer_setting(void);

void reset_mat_id_data(void);
void reset_truck_id_data(void);
unsigned_16 get_num_load_trucks(void);
unsigned_16 get_num_load_cycles(void);


void get_mat_id_string(unsigned_8   mat_id, char * string);
void get_oper_id_string(unsigned_8  op_id, char *   string);
void get_truck_id_string(unsigned_8 truck_id, char * string);
void get_site_id_string(unsigned_8  site_id, char * string);

float get_tot_load_weight(void);
void reset_material_cummulatives(void);
void reset_individual_material_cummulative(unsigned_8 index);
unsigned_32 get_oil_type(void);
void set_oil_type(unsigned_32   type);
float get_oil_viscosity(float hydOilTemp);
float get_oil_density(float hydOilTemp);

LOAD_RATIO_INFO get_load_ratio(void);
LOAD_RATIO_INFO get_load_ratio_raw(void);

reweigh_status_t  get_reweigh_warning_status(void);
boolean get_zero_accepted_status(void);
unsigned_8  get_zero_needed_status(void);
unsigned_8  get_enter_cal_wt_status(void);
void set_store_switch_status(boolean status);
boolean get_store_switch_status(void);
void set_clear_switch_status(boolean status);
boolean get_clear_switch_status(void);
void set_reweigh_switch_status(boolean status);
boolean get_reweigh_switch_status(void);
void set_zero_switch_status(boolean status);
boolean get_zero_switch_status(void);
void set_undo_switch_status(boolean status);
boolean get_undo_switch_status(void);
void set_minus_one_switch_status(bool_least_t status);
bool_least_t get_minus_one_switch_status(void);

void set_bottom_and_top_ranges_of_position(unsigned_16 bottomoflift , unsigned_16 topoflift);
void strncpy_2_2(unsigned_16 *dest, unsigned_16 *srce, size_t n);
void set_payload_horn_status(unsigned_8 status);
unsigned_8 get_payload_horn_status(void);
void set_statcode_id(unsigned_8 id , unsigned_8 mode);/* Support for delay code*/
unsigned_16 get_statcode_id(void);
void Auto_Statcode_Ctrl(unsigned_32 load_elapsed_time);
boolean is_rodendsensor_enabled(void);
unsigned_8 pcs_nvm_store_data(void);
unsigned_8 pcs_nvm_clear_truck_data(void);
void set_current_truck_string(unsigned_8* string, unsigned_8 size);
unsigned_16 pcs_get_payload_accuracy(void);
TIMESTAMP pcs_time_to_timestamp(PCS_TIME time);
unsigned_8 pcs_get_auto_ids_display(void);
void pcs_set_auto_ids_display(unsigned_8 display_status);
void pcs_set_payload_data_status(unsigned_8 status);
extern void pcs_check_truck_clear_flag(void);
extern boolean pcs_check_diag_too_heavy_to_zero(void);
extern boolean pcs_check_diag_payload_overload(void);
extern boolean pcs_check_diag_uncalibrated(void);
extern boolean pcs_check_diag_zero_lift_needed(void);
extern unsigned_8 pcs_get_dump_state_value(void);
extern unsigned_8 pcs_get_dig_state_value(void);


extern bool_least_t pcs_cal_app_inf_is_cal_ovr_active(void);
extern int_least16_t pcs_cal_app_inf_get_raise_cmd_lim(void);
extern int_least16_t pcs_cal_app_inf_get_lower_cmd_lim(void);
extern int_least16_t pcs_cal_app_inf_get_rack_cmd_lim(void);
extern int_least16_t pcs_cal_app_inf_get_dump_cmd_lim(void);
extern int_least16_t pcs_cal_app_inf_get_eng_spd_lim(void);

unsigned_16 get_tip_off_trigger(void);
void set_tip_off_trigger(unsigned_16 tip_off_trigger);
boolean compare_truck_mat_Op_ID(void);

PAYLOAD_INFO get_bucket_payload_wt_info(void);

void set_display_mode(unsigned_16 val);
unsigned_16 get_display_mode(void);
PCS_TIME pcs_convert_utc_to_pcs_time(unsigned_32 pd_utc_time);


/* Calibration ID structures */
extern CAL_MGR_Cal_t pcs_position_cal;
extern CAL_MGR_Cal_t pcs_empty_cal;
extern CAL_MGR_Cal_t pcs_full_cal;
extern CAL_MGR_Cal_t pcs_vel_cal;
extern CAL_MGR_Cal_t pcs_vel_2pt_cal;
extern CAL_MGR_Cal_t pcs_empty_wt_cal;
extern CAL_MGR_Cal_t pcs_full_wt_cal;
extern CAL_MGR_Cal_t pcs_vel_cmp_cal;
extern CAL_MGR_Cal_t pcs_empty_cal3;
extern CAL_MGR_Cal_t pcs_full_cal3;


/* Flag for the application to know to update the EEPROM */
extern boolean pcs_nvm_update_flag;
extern boolean pcs_clear_truck_data_nvm_flag;
extern boolean pcs_read_truck_data_nvm_complete;

extern STORE_PAYLOAD_DATA pcs_store_cache;
extern STORE_PAYLOAD_DATA *tmp_send_buf;
extern float *filt_i_weight_struct;
extern WT_RATE_CHANGE_PTRS wt_ptrs;
extern unsigned_8 *truck_hash_uid_data;
extern unsigned_8 *status_rec_uid_data;
extern float *prt_weights;
extern boolean autostore_flag;
extern unsigned_8 payload_status_available;
extern boolean First_time_check_flag;

extern unsigned_32 saved_stale_time;

extern PCS_TIME_PD_BLOCKS status_start_time;
extern TRUCK_NAME truck_name_pcs;
extern MAT_NAME mat_name_pcs;
extern unsigned_16 matid_density;
extern OPERATOR_ID_DESC op_id_description_pcs;
extern TRUCK_ID_NUM temp_curr_truck_ID_num;
extern MATERIAL_ID_NUM temp_curr_material_ID_num;
extern boolean status_buffer_empty;

extern const char default_trk_mat_op_id_desc_string[2];

#if defined (__cplusplus)
}
#endif

#endif /* __PCS_PUBLIC_H__ */
