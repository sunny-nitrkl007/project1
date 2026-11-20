/*******************************************************************************
** COPYRIGHT (C) 2015-2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:   gps_public.h
DESCRIPTION: Provides the global interfaces for the GPS library
*******************************************************************************/
#ifndef GPS_PUBLIC_H_
#define GPS_PUBLIC_H_
/*******************************************************************************
** -- #Includes --
*******************************************************************************/
#include <ProdDataPublic.h>

#include <math.h>
/* there is no cross platform definition of pi. The following ifndef handles the 
 * case where M_PI is not defined in math.h
 */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*******************************************************************************
** -- #Define, Structs, Typedefs, Enums --
*******************************************************************************/
/* PID GPS Time Information from PID F835 through PID F84D */

typedef struct __attribute__((packed))
{
    unsigned_8  sec;
    unsigned_8  min;
    unsigned_8  hour;
    unsigned_8  day;
    unsigned_8  mon;
    unsigned_8  year;
}TIMESTAMP_t;

/* PID GPS Information from PID F84D */
typedef struct __attribute__((packed)) 
{
    unsigned_8  	pos_cmd;
    TIMESTAMP_t         timest;  /* UTC, zero based from 1/1/1985 */ 
    unsigned_8  	pos_status;
    unsigned_8  	GPS_Lat[3];
    unsigned_8  	GPS_Long[3];
} gps_struct;

typedef unsigned_8  gps_get_keyoff_status(void);
typedef unsigned_32 gps_get_shm(void);
typedef int_16 gps_get_tz_offset(void);
typedef unsigned_32 gps_get_utc(void);
typedef gps_struct gps_get_gps_data(void);

extern gps_get_keyoff_status* gps_get_keyoff_stat;
extern gps_get_shm* gps_get_service_hour_meter;
extern gps_get_tz_offset* gps_get_tz_off;
extern gps_get_utc* gps_get_utc_timestamp;
extern gps_get_gps_data* gps_get_data;


/* Function pointers for application */
typedef struct 
{
    gps_get_keyoff_status    *get_keyoff_status;
    gps_get_shm              *get_shm;
    gps_get_tz_offset        *get_timezone_offset;
    gps_get_utc              *get_utc;
    gps_get_gps_data         *get_gps;
} GPS_FUNC_INFO;


/* GPS Configuration */
/* This is for the application to give inputs to the library */
typedef struct 
{
    GPS_FUNC_INFO    *func_ptrs;
    unsigned_32       gps_distance_threshold;
    unsigned_32       gps_time_threshold;
}gps_config;

/* GPS TimeStamp UID info */
typedef struct __attribute__((packed)) 
{
    unsigned_32 gps_start_utc; 			/* number of seconds since 1/1/2000 */
    int_16      timezone_start_offset;
    unsigned_32 shm_start;
}GPS_TIMESTAMP;


/* GPS information */
typedef struct __attribute__((packed))
{
    unsigned_8  	key_status;
    unsigned_8  	ext_trigger;			/* application sw gps record request */
	GPS_TIMESTAMP 	gps_time_info;
    gps_struct  	gps_pid_info;			/* info from PID $F84D, includes timestamp since 1/1/1985 */
}GPS_INFO;


/* UID 0x000105E0 GPS Latitude */
#define GPS_LATITUDE_UID_UID             0x00,0x01,0x05,0xE0
#define GPS_LATITUDE_UID_ID              0x00
#define GPS_LATITUDE_UID_SIZE            0x03
#define GPS_LATITUDE_UID_DATATYPE        0x18
#define GPS_LATITUDE_UID_COLOR           0x05
#define GPS_LATITUDE_UID_DATASOURCE      0x01,0x90

/* UID 0x000105E1 GPS Longitude */
#define GPS_LONGITUDE_UID_UID            0x00,0x01,0x05,0xE1
#define GPS_LONGITUDE_UID_ID             0x00
#define GPS_LONGITUDE_UID_SIZE           0x03
#define GPS_LONGITUDE_UID_DATATYPE       0x18
#define GPS_LONGITUDE_UID_COLOR          0x05
#define GPS_LONGITUDE_UID_DATASOURCE     0x01,0x90

/* UID 0x000105DE GPS Position status */
#define GPS_POS_STATUS_UID_UID           0x00,0x01,0x05,0xDE
#define GPS_POS_STATUS_UID_ID            0x00
#define GPS_POS_STATUS_UID_SIZE          0x01
#define GPS_POS_STATUS_UID_DATATYPE      0x06
#define GPS_POS_STATUS_UID_COLOR         0x05
#define GPS_POS_STATUS_UID_DATASOURCE    0x01,0x90

/* UID 0x81010007 GPS Start time */
#define GPS_START_TIME_UID_UID           0x81,0x01,0x00,0x07
#define GPS_START_TIME_UID_ID            0x1D
#define GPS_START_TIME_UID_SIZE          0x0A
#define GPS_START_TIME_UID_DATATYPE      0x13
#define GPS_START_TIME_UID_COLOR         0x05
#define GPS_START_TIME_UID_DATASOURCE    0x00,0x52

/* return values for gps init func */
#define GPS_INIT_SUCCESS         0
#define GPS_INVALID_NVM          1
#define GPS_INVALID_FUNC         2
#define GPS_DISABLED             3
#define GPS_MEM_ALLOC_ERR        4

/* GPD PID F84D position status */
#define INVALID_POS_STATUS  0xFF
#define POS_VALID           0
#define POS_INVALID         1
#define POS_CALC_INCOMPLETE 2
#define POS_TYPE_UNAVAIL    3
#define POS_TIMECHK_FAILED  4

#define EPOCH_1980_OFFSET_SEC 630720000 /*01/06/1980, 00:00:00 to 01/01/2000, 00:00:00*/
#define EPOCH_1985_OFFSET_SEC 473299200 /*01/01/1985, 00:00:00 to 01/01/2000, 00:00:00*/

/* Applying PID scaling and converting angles from degrees to radians for GPS coordinates.
  2**24 == 16777216 is the degree/bit scaling of data from PID
*/
#define CONV_LAT(lat) ((90.0-(lat*180.0/16777216))*M_PI/180.0);
#define CONV_LON(lon) (((lon*360.0/16777216)-360.0)*M_PI/180.0);


/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/* Public */
extern unsigned_8 gps_init(gps_config *cfg);
extern void gps_update(void);
extern void gps_ext_trigger(void);

/* Private */
void gps_trigger_check(void);
void gps_get_start_time(unsigned_8* pLocation, unsigned_16 size);
void gps_get_latitude(unsigned_8* pLocation, unsigned_16 size);
void gps_get_longitude(unsigned_8* pLocation, unsigned_16 size);
void gps_get_status(unsigned_8* pLocation, unsigned_16 size);
//extern const gps_uid_info gps_lib_uids[];

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/

extern unsigned_8 gps_init_status;
//extern GPS_SAMPLE_BLK  gps_rec_sample;
extern GPS_INFO curr_gps_info;
extern GPS_INFO gps_last_sample;
extern unsigned_32 dist_threshold;
extern unsigned_32 time_threshold;

extern unsigned_8 gps_send_command;

#endif /* #ifndef GPS_PUBLIC_H_ */
