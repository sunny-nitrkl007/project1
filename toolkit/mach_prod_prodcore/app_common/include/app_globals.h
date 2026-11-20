/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 2014 CATERPILLAR INC.   ALL RIGHTS RESERVED.       %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
***
*** DESCRIPTION :
***	Global variables used by the application 
***
*** LANGUAGE :
***    ANSI C
***
*** MACRO LIST:
***
*******************************************************************************/
#ifndef __APP_GLOBALS_H__
#define __APP_GLOBALS_H__

#include <std_types.h>
#include <prt_public.h>
#include <prt_report_public.h>
#include <mt_public.h>
#include <ob_totals_public.h>
#include <pd_public.h>
#include <prod_core_public.h>
#include <pdlib_public.h>
/* defines used by application */
/* return values for wts_pe init func */
#define TEST_APP_INIT_SUCCESS   0
#define TEST_APP_INVALID_NVM    1


/*ADAPTER DATA ACTION values*/  
#define ADA_NO_ACTION           0x00
#define ADA_SEND_LOAD_BLK       0x01
#define ADA_SEND_CYCLE_BLK      0x02
#define ADA_SEND_STATUS_BLK     0x03
#define ADA_MOD_LOAD_BLK        0x04
#define ADA_MOD_STATUS_BLK      0x05
#define ADA_MOD_CYCLE_BLK       0x06


/* Material Totals DATA ACTION values  */
#define MTOT_NO_ACTION          0x00
#define MTOT_ACT_01             0x01
#define MTOT_ACT_02             0x02
#define MTOT_ACT_03             0x03
#define MTOT_ACT_04             0x04
#define MTOT_ACT_05             0x05
#define MTOT_ACT_06             0x06

#define ADA_SEND_DATA_NOW		0x10

/* MACHINE SPECIFIC ADAPTER DATA ACTION values  */
#define MSA_NO_ACTION           0x40
#define MSA_SEND_PCS_CYCLE_BLK 	0x41
#define MSA_SEND_CT_CYCLE_BLK   0x42
#define MSA_MOD_PCS_CYCLE_BLK   0x47
#define MSA_MOD_CT_CYCLE_BLK    0x48


#define APP_TYPE 52
//#define APP_VERSION 48
/* keep the version the same as PCS for sharing ECM in lab */
#define APP_VERSION 49
#define APP_CHECKSUM_ADJUST 1
/*!ISSUE! all values listed need to be verified for PD app -jtwite 11/14/13 */
//#define CPM_PRT_MID 0x52
#define CPM_PRT_MID  0x52
#define MTOT_MID 0x52
#define CPM_PD_MID 0x52

#define FLASH_APPLICATION_ID	195		/* Wheel Loader */
#define FLASH_COMPONENT_ID		52		/* Monitoring System */

#define CUM_PAYLOAD_WEIGHT_ID 99        /* just a test number */

#define WTS_BLOCK_VERSION 4

#define SERIAL_NUM_SIZE		20
#define EQUIPMENT_NUM_SIZE	16


#define PD_LOAD_BLK_SIZE (sizeof(pd_load_data_block))
#define PD_CYCLE_BLK_SIZE (sizeof(pd_cycle_data_block))
#define PD_STATUS_BLK_SIZE (sizeof(pd_status_data_block) + PROD_SIZE_OF_STATUS_STR)
#define PD_SEGMENT_BLK_SIZE (sizeof(pd_segment_data_block))
#define PD_UID_INFO_SIZE (sizeof(pd_uid_info))

#define PD_MISC_DATA_BLK_SIZE (sizeof(pd_store_pdrec_data))
 
#define PD_MAX_LOAD_RECORDS 5
#define PD_MAX_CYCLE_RECORDS 25
#define PD_MAX_STATUS_RECORDS 25
#define PD_MAX_SEGMENT_RECORDS 9   // per cycle

#define PD_LOAD_UID_CNT 0
#define PD_CYCLE_UID_CNT 0
#define PD_SEGMENT_UID_CNT 0 
#define PD_STATUS_UID_CNT 0
#define PD_SIZEOF_SEGMENT_BLOCK (sizeof(prt_segment_data_block))

#define SERIAL_NUM_SIZE		20
#define EQUIPMENT_NUM_SIZE	16

extern unsigned_8 num_supported_models;
extern unsigned_8 model_specific_values_index;

extern unsigned_16 mat_id;
extern unsigned_8 truck_name[PROD_SIZE_OF_TRUCK_NAME];
extern pd_timestamp ldb_start_tm;
extern pd_timestamp ldb_end_tm;
extern pd_timestamp cdb_start_tm;
extern pd_timestamp sdb_start_tm;

extern pd_uid_info ldb_uidMatID;
extern pd_uid_info ldb_uidMatDenID;
extern pd_uid_info ldb_uidTruckID;
extern pd_uid_info uid_segment_1;
extern pd_uid_info uid_segment_2;
extern pd_uid_info uid_segment_3;
extern pd_uid_info uid_segment_4;
extern pd_uid_info uid_gps_1;
extern pd_uid_info uid_gps_2;
extern pd_uid_info uid_gps_3;
extern pd_uid_info uid_gps_4;


/*cdl2 application side variables*/
extern unsigned_32  cdl2_test_connect_called;
extern unsigned_32  cdl2_test_periodic_count;

extern char software_group_part_number[10];
extern char software_group_description[22];
extern char software_group_release_date[5];
extern unsigned_8 service_support_level[2];
extern unsigned_8 application_level[2];
extern PRT_TRUCK_TICKET app_ticket;
extern PRT_MATERIAL_REPORT app_mat_report;
extern unsigned_32 truckname;
extern unsigned_32 opidname;
extern float ticket_total_cycle_weight;
extern unsigned_8 ticket_pass_count;
extern float mat_report_total_loaded;
extern unsigned_16 mat_report_num_loaded_mats;
extern unsigned_16 mat_report_num_loads ;
extern float passes_weight[25];
extern float passes_weight_50[50];
extern PRT_MATERIAL_TYPE material_records[3];
extern unsigned_8 materialname[PROD_SIZE_OF_MAT_NAME];
//extern unsigned_8  materialname1;
extern pd_uid_info cdb_uid_fuel_used;
extern pd_uid_info cdb_truckhash;
extern pd_uid_info ldb_truckhash;
extern pd_uid_info cdb_ct_truckhash;
extern unsigned_8 cdb_uidtruckhash[16];
extern unsigned_8 cdb_ctuidtruckhash[12];
/*
extern pd_segment_data_block test_segment[2];
extern pd_segment_data_block test_segment2[2];
extern pd_segment_data_block test_segment3[3];
*/

extern pd_uid_info total_uid_stuff[6];
extern pd_uid_info total_segment_stuff[4];
extern pd_uid_info total_gps_stuff[4];

extern unsigned_8 *load_block_uidData;
extern unsigned_8 *cycle_block_uidData;
extern unsigned_8 *status_block_uidData;
extern unsigned_8 *seg_block_uidData;
extern unsigned_8 *seg_block_Data;
extern unsigned_8 *payload_block_uidData;
extern unsigned_8 * gps_block_uidData;

extern unsigned_8 matID[32];
extern unsigned_16 matDenId;
extern unsigned_8 TruckID[16];
extern unsigned_8 segment_data_1[8];

extern unsigned_8 pd_started;

pd_timestamp pd_get_real_time_clock(void);


/* flag used for shutdown management */
extern unsigned_8 prt_started;
extern unsigned_8 mtot_started;
extern unsigned_8 ob_totals_started;


/* Application NVM update flag */
extern boolean	app_nvm_update_flag;

extern unsigned_32 clock_counter;

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

extern PRT_TIMESTAMP load_block_start;
extern unsigned_32 load_block_start_shm;
extern mt_material_report_data_rec mt_data_rec_in;
extern mt_material_type add_to_existing_mat;
extern mt_material_type reset_mat;
extern mt_material_type add_new_mat;
extern mt_material_type replace_mat;

extern char added_mat1[PROD_SIZE_OF_MAT_NAME];
extern char added_mat2[PROD_SIZE_OF_MAT_NAME];
extern char added_mat3[PROD_SIZE_OF_MAT_NAME];
extern char added_mat4[PROD_SIZE_OF_MAT_NAME];
extern char added_mat5[PROD_SIZE_OF_MAT_NAME];
extern unsigned_32 lifetime_cummulative_total_weight;
/* test app cycle timer install status function */
unsigned_8 app_ct_get_install_status(void);
unsigned_8 app_pd_get_keyoff_status(void);
unsigned_8 app_mt_get_keyoff_status(void);
unsigned_8 app_pcs_get_install_status(void);

void app_prt_reset_material_report(void);


#endif /* __APP_GLOBALS_H__ */

