/* wl_interface_utilities.h */
#ifndef __WL_INTERFACE_UTILITIES_H__
#define __WL_INTERFACE_UTILITIES_H__


#include <prod_core_public.h>

#include <wl_interface_utilities_externs.h>

#include <adapter_register.h>

#include <string.h>

#include <clock_proto.h>
#include <prod_core_packed_struct.h>



/* *******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
***     SEGMENT_DATA_BLOCK - Stucture containing segment information for ProductivityData
***
*******************************************************************************/
/* offset in seconds for time stamp from Jan 6th 1980 and jan 1st 2000 */
#define REAL_TIME_OFFSET   ((unsigned_32)630720000U)

#define STATUS_REALTIME_AVAILABLE  0

PROD_CORE_PRAGMA_PACK_PUSH(1)
typedef PROD_CORE_PACKED struct
{   unsigned_32       start_tm_utc;
    int_16            tmZoneOffset;
    unsigned_32       start_shm;

}SEGMENT_DATA_BLOCK_TIME_INFO;
PROD_CORE_PRAGMA_PACK_POP()

PROD_CORE_PRAGMA_PACK_PUSH(1)
typedef PROD_CORE_PACKED struct
{
    unsigned_8                    seg_id;
    unsigned_32                   seg_duration;
    float                         fuel_consumed;
    float                         distance_traveled;
    float                         payload;
    unsigned_16                   payload_method;
    unsigned_32                   machine_idle_time;
    SEGMENT_DATA_BLOCK_TIME_INFO  segment_block_time;

}SEGMENT_DATA_BLOCK_LOCAL;
PROD_CORE_PRAGMA_PACK_POP()


/***************************************************************************************
***     MODEL_OUPUTS - Stucture to data from model
***
*******************************************************************************/

PROD_CORE_PRAGMA_PACK_PUSH(1)
typedef PROD_CORE_PACKED struct
{
    unsigned_8  segment_record_commit_seg_record;
    unsigned_8  segment_record_identifier;
    unsigned_32 segment_record_start_sim_time;
    unsigned_32 segment_record_duration;
    float       segment_record_distance_travelled;
    unsigned_32 segment_record_start_real_time;
    float       segment_record_fuel_consumed;
    unsigned_32 segment_record_machine_idle_time;
    unsigned_32 segment_record_service_hour_meter;
    int_16      segment_timezone_offset;
    float       segment_record_payload;
    unsigned_16 segment_rec_payload_calc_method;
    unsigned_32 segment_common_clock_count;


}   MODEL_OUTPUTS;
PROD_CORE_PRAGMA_PACK_POP()

/********************************************************************/
/*UID Information*/
/********************************************************************/

/* UID 0x8101002F Segment Identifier */
#define CS_SEGMENT_ID_UID_UID                               0x8101002F
#define CS_SEGMENT_ID_UID_ID                                0x00
#define CS_SEGMENT_ID_UID_SIZE                              0x01
#define CS_SEGMENT_ID_UID_DATATYPE                          0x06
#define CS_SEGMENT_ID_UID_COLOR                             0x05
#define CS_SEGMENT_ID_UID_DATASOURCE                        0x0052

/* UID 0x81010007 Segment Start Time */
#define CS_SEGMENT_START_TIME_UTC_UID_UID                   0x81010007
#define CS_SEGMENT_START_TIME_UTC_UID_ID                    0x19
#define CS_SEGMENT_START_TIME_UTC_UID_SIZE                  0x0A
#define CS_SEGMENT_START_TIME_UTC_UID_DATATYPE              0x13
#define CS_SEGMENT_START_TIME_UTC_UID_COLOR                 0x05
#define CS_SEGMENT_START_TIME_UTC_UID_DATASOURCE            0x0052

/* UID 0x81010074 Segment Duration */
#define CS_SEGMENT_DURATION_UID_UID                         0x81010074
#define CS_SEGMENT_DURATION_UID_ID                          0x00
#define CS_SEGMENT_DURATION_UID_SIZE                        0x04
#define CS_SEGMENT_DURATION_UID_DATATYPE                    0x15
#define CS_SEGMENT_DURATION_UID_COLOR                       0x05
#define CS_SEGMENT_DURATION_UID_DATASOURCE                  0x0052

/* UID 0x8101004D Fuel consumed */
#define CS_SEGMENT_FUEL_CONSUMED_UID_UID                    0x8101004D
#define CS_SEGMENT_FUEL_CONSUMED_UID_ID                     0x00
#define CS_SEGMENT_FUEL_CONSUMED_UID_SIZE                   0x04
#define CS_SEGMENT_FUEL_CONSUMED_UID_DATATYPE               0x15
#define CS_SEGMENT_FUEL_CONSUMED_UID_COLOR                  0x05
#define CS_SEGMENT_FUEL_CONSUMED_UID_DATASOURCE             0x0052

/* UID 0x8101004C Distance Travelled */
#define CS_SEGMENT_DISTANCE_TRAVELLED_UID_UID               0x8101004C
#define CS_SEGMENT_DISTANCE_TRAVELLED_UID_ID                0x00
#define CS_SEGMENT_DISTANCE_TRAVELLED_UID_SIZE              0x04
#define CS_SEGMENT_DISTANCE_TRAVELLED_UID_DATATYPE          0x15
#define CS_SEGMENT_DISTANCE_TRAVELLED_UID_COLOR             0x05
#define CS_SEGMENT_DISTANCE_TRAVELLED_UID_DATASOURCE        0x0052

/* UID 0x81010074 Machine Idle Duration */
#define CS_SEGMENT_MACHINE_IDLE_DURATION_UID_UID            0x81010074
#define CS_SEGMENT_MACHINE_IDLE_DURATION_UID_ID             0x01
#define CS_SEGMENT_MACHINE_IDLE_DURATION_UID_SIZE           0x04
#define CS_SEGMENT_MACHINE_IDLE_DURATION_UID_DATATYPE       0x15
#define CS_SEGMENT_MACHINE_IDLE_DURATION_UID_COLOR          0x05
#define CS_SEGMENT_MACHINE_IDLE_DURATION_UID_DATASOURCE     0x0052

/* UID 0x8101004E Payload weight */
#define CS_SEGMENT_PAYLOAD_WEIGHT_UID_UID                   0x8101004E
#define CS_SEGMENT_PAYLOAD_WEIGHT_UID_ID                    0x00
#define CS_SEGMENT_PAYLOAD_WEIGHT_UID_SIZE                  0x04
#define CS_SEGMENT_PAYLOAD_WEIGHT_UID_DATATYPE              0x15
#define CS_SEGMENT_PAYLOAD_WEIGHT_UID_COLOR                 0x00
#define CS_SEGMENT_PAYLOAD_WEIGHT_UID_DATASOURCE            0x0190

/* UID 0x00011A78 Payload Calculation Method */
#define CS_SEGMENT_PAYLOAD_CALC_METHOD_UID_UID              0x00011A78
#define CS_SEGMENT_PAYLOAD_CALC_METHOD_UID_ID               0x00
#define CS_SEGMENT_PAYLOAD_CALC_METHOD_UID_SIZE             0x02
#define CS_SEGMENT_PAYLOAD_CALC_METHOD_UID_DATATYPE         0x09
#define CS_SEGMENT_PAYLOAD_CALC_METHOD_UID_COLOR            0x05
#define CS_SEGMENT_PAYLOAD_CALC_METHOD_UID_DATASOURCE       0x0052


/********************************************************************/
/* Function Pointer*/
/********************************************************************/
PD_FUNC_PTR *cs_get_segment_id_ptr;
PD_FUNC_PTR *cs_get_segment_time_stamp_ptr;
PD_FUNC_PTR *cs_get_segment_duration_ptr;
PD_FUNC_PTR *cs_get_segment_fuel_consumed_ptr;
PD_FUNC_PTR *cs_get_segment_distance_travelled_ptr;

/* Function pointer for controlled shutdown of Implement ECM after key off */
override_callback_func *cs_get_shutdown_override_ptr;

/********************************************************************/
/*segment - Functional pointers for Optinal UID's*/
/********************************************************************/
PD_FUNC_PTR *cs_get_segment_machine_idle_duration_ptr;
PD_FUNC_PTR *cs_get_segment_payload_wt_ptr;
PD_FUNC_PTR *cs_get_segment_payload_calc_method_ptr;

/********************************************************************/
/*segment call back functions*/
/********************************************************************/
void cs_get_segment_id(unsigned_8* pLocation, unsigned_16 size);
void cs_get_segment_time_stamp(unsigned_8* pLocation, unsigned_16 size);
void cs_get_segment_duration(unsigned_8* pLocation, unsigned_16 size);
void cs_get_segment_fuel_consumed(unsigned_8* pLocation, unsigned_16 size);
void cs_get_segment_distance_travelled(unsigned_8* pLocation, unsigned_16 size);
void cs_get_segment_machine_idle_duration(unsigned_8* pLocation, unsigned_16 size);
void cs_get_segment_payload_wt(unsigned_8* pLocation, unsigned_16 size);
void cs_get_segment_payload_calc_method(unsigned_8* pLocation, unsigned_16 size);

/* Key switch override callback function */
boolean cs_get_shutdown_override(void);

/********************************************************************/
/*Return Flags for UID registration     */
/********************************************************************/
PROD_REG_RET_T CS_SEGMENT_ID_UID_flag;
PROD_REG_RET_T CS_SEGMENT_START_TIME_UTC_UID_flag;
PROD_REG_RET_T CS_SEGMENT_DURATION_UID_flag;
PROD_REG_RET_T CS_SEGMENT_FUEL_CONSUMED_UID_flag;
PROD_REG_RET_T CS_SEGMENT_DISTANCE_TRAVELLED_UID_flag;
PROD_REG_RET_T CS_SEGMENT_MACHINE_IDLE_DURATION_flag;
PROD_REG_RET_T CS_SEGMENT_PAYLOAD_WEIGHT_flag;
PROD_REG_RET_T CS_SEGMENT_PAYLOAD_CALCULATION_METHOD_flag;
PROD_REG_RET_T CS_SEGMENT_GPS_LATITUDE_flag;
PROD_REG_RET_T CS_SEGMENT_GPS_LONGITUDE_flag;
PROD_REG_RET_T CS_SEGMENT_GPS_STATUS_flag;

/********************************************************************/
/*Current Data from model*/
static MODEL_OUTPUTS model_outputs_work ;

/*Buffer to model output data if real time is not available from Implement*/
static MODEL_OUTPUTS *model_outputs_buffer;
static unsigned_32 model_outputs_buffer_address;

/*Data That should be sent to Productivity*/
static SEGMENT_DATA_BLOCK_LOCAL segment_block;

static bool_t buffer_empty = TRUE;
static unsigned_8 PD_buffer_size;

/*Destination address*/
unsigned_8 *pLocation  =NULL;

/* Flag to make sure all UID's needed for segment block are registered with Productivity Data and returned Success*/
static bool_t seg_registration_done = FALSE;

/* Number of segment records pushed into buffer*/
static unsigned_8   seg_count    = 0;
static unsigned_8   curr_buff = 0;     /*Local variable used when pushing buffer data to Productivity Data */
static unsigned_32 previous_stale_time = 0;
static boolean_t realtime_first_available = FALSE;
static unsigned_32 first_valid_realtime = 0;
static unsigned_32 first_rec_after_buff_start_time = 0;
static boolean_t first_record_when_time_available = FALSE;


#endif






