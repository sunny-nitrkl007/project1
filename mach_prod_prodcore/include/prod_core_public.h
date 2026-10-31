 /*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 2015-2016 CATERPILLAR INC.   ALL RIGHTS RESERVED.       %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
*** FILE NAME:  prod_core_public.h
***
*** DESCRIPTION :
***     Shared structures, defines, and functions for the following components:
***             MaterialTotals
***             OnBoardTotals
***             Printer
***             ProductivityData
***             PCS
***
*** MACRO LIST:
***
*******************************************************************************/
#ifndef __PROD_CORE_PUBLIC_H__
#define __PROD_CORE_PUBLIC_H__

#if defined (__cplusplus)
extern "C"
{
#endif

/*******************************************************************************
***
*** External function prototypes, data, & symbols
*** -- #Include's, #Define's --
***
*******************************************************************************/
#include <cat_std_types.h>
#include <nvm.h>
#include <prod_core_packed_struct.h>

#define PROD_SIZE_OF_MAT_NAME           24
#define PROD_SIZE_OF_OP_ID_DESC         11
#define PROD_SIZE_OF_TRUCK_NAME         16
#define PROD_SIZE_OF_STATUS_STR         32


#define PROD_ERROR_ALLOC_FAILURE        2
/* Invalid values in the config passed to the init */
#define PROD_ERROR_INVALID_CONFIG       3
/* Some of the non-optional functional pointers in the config are NULL */
#define PROD_ERROR_INVALID_FNPTR        4
#define PROD_SUCCESS                                    0

// NVM related defines
#define PROD_ERROR_INVALID_NVM          1
#define PROD_NVM_READ_SUCCESS           0
#define PROD_NVM_WRITE_SUCCESS          0
#define PROD_NVM_READ_FAILURE           0xFFFF
#define PROD_NVM_WRITE_FAILURE          0xFFFF

// BDT related defines
#define PROD_PROTOCOL_READ_OK 0
#define PROD_PROTOCOL_READ_ERROR 0xFF
#define PROD_PROTOCOL_BUSY_ERROR 0x01
#define PROD_PROTOCOL_SIZE_OVERFLOW_ERROR 0x02
#define PROD_PROTOCOL_SIZE_0_ERROR 0x03
#define PROD_PROTOCOL_CONNECTION_KEYOFF_DETECTED 0x05   // key off detected so didnt get the connection

// Key Status
#define PROD_KEYSW_STATUS_OFF 0
#define PROD_KEYSW_STATUS_ON  1

// CA14 Autostore Data Control
#define PROD_AUTOSTORE_DATA_CTRL_HOLD 1
#define PROD_AUTOSTORE_DATA_CTRL_RESUME 2


/*******************************************************************************
***
*** Data types defined for this file
*** -- Struct's, Typedef's, Enum's --
***
*******************************************************************************/

typedef unsigned_32  TIMESTAMP_UTC;

typedef enum {
 PROD_BLOCK_TYPE_LOAD = 4724,
 PROD_BLOCK_TYPE_CYCLE = 4725,
 PROD_BLOCK_TYPE_SEGMENT = 4726,
 PROD_BLOCK_TYPE_STATUS = 4727,
 PROD_BLOCK_TYPE_PAYLOAD = 4728,
 PROD_BLOCK_TYPE_GPS = 4729
}PROD_BLOCK_TYPE_T;

/* this is  */
typedef enum {
    RET_SUCCESS,
    RET_ERROR,
    RET_NULL_FUNC_PTR,
    RET_INVALID_BLOCK,
    RET_DUPLICATE_BLOCK,
    RET_SIZE_OVER_FLOW,
    RET_UID_SIZE_INVALID

}PROD_REG_RET_T;

typedef enum {
    KSO_RET_ERROR,
    KSO_RET_SUCCESS,
    KSO_RET_NULL_FUNC_PTR,
    KSO_RET_SIZE_OVER_FLOW
}PROD_KSO_REG_RET_T;


/* TODO: IS this needed? */
typedef enum {
    CURRENT_TIME,
    STALE_TIME
}PROD_REALTIME_STATUS_T;

/*******************************************************************************
***     MATERIAL_TYPE - Stucture containing information for a single material
*** Used By: MaterialTotals, Printer, PCS
*******************************************************************************/

typedef struct
{
    char            material_name[PROD_SIZE_OF_MAT_NAME];       // Material Name
    float           material_wt;                                // Weight loaded for this material type -  0.1 metric ton/bit
    unsigned_16     num_loads;                                                      // Total number of loads for this material type
    unsigned_8      index;                                                              // Index of this material
    unsigned_8      mat_type_padding;                                       // Padding for 4 byte alignment
} MATERIAL_TYPE;

/*******************************************************************************
***     MATERIAL_REPORT_DATA_REC - Stucture containing information for all materials
*** Used By: MaterialTotals, Printer
*******************************************************************************/

typedef struct
{
    float               total_mat_wt_loaded;            // Total weight of all materials loaded
    unsigned_16         total_num_loads;                // Total number of loads for all materials in list
    unsigned_16         num_materials;                 // Number of Materials
    MATERIAL_TYPE       *mat_list;                     // Pointer to list of materials
} MATERIAL_REPORT_DATA_REC;

/*******************************************************************************
***     CONNECTION_INFO - Stucture containing Data Link connection information
*** Used By: MaterialTotals, Printer, ProductivityData, PCS
*******************************************************************************/

typedef struct
{
    unsigned_32 data_index;                     // Data associated with the type of the file eg: specific cal identifiers
    unsigned_16 data_type;                      // Type of data contained in the file - CAL, ECL etc
    unsigned_16 did;                            // destination module identifier
    unsigned_8  access_mode;                    // Read / Write
    unsigned_8  link_type;                      // Type of datalink cdl, ATA or 1939
    unsigned_8  command_type;                   // Connect or Abort the connection
    unsigned_8  conn_info_padding;              // Padding for 4 byte alignment
}CONNECTION_INFO;

/*******************************************************************************
***     NVM_BLOCK_T - Stucture containing information for NVM
*** Used By: MaterialTotals, Printer, ProductivityData, OnBoardTotals, PCS
*******************************************************************************/

typedef struct {
    unsigned_32                 block_id;                      // Block id number for nvm module
    unsigned_8                  *cache_pointer;                // Cache pointer for nvm module
    NVM_block_handle_t          *block_handle;                 // Block handle for nvm module
    unsigned_32                 size;                          // Number of bytes in block
    unsigned_8                  type;
    char                        nvm_block_padding[3];          // Padding for 4 byte alignment
} NVM_BLOCK_T;

/*******************************************************************************
***     TIMESTAMP - Stucture containing format for time
*** Used By: Printer, ProductivityData, OnBoardTotals, PCS
*******************************************************************************/

PROD_CORE_PRAGMA_PACK_PUSH(1)
typedef PROD_CORE_PACKED struct
{
    unsigned_8  sec;
    unsigned_8  min;
    unsigned_8  hour;
    unsigned_8  day;
    unsigned_8  mon;
    unsigned_8  year;
}TIMESTAMP;
PROD_CORE_PRAGMA_PACK_POP()

/*******************************************************************************
***     TIMESTAMP - Stucture containing format for time and associated status (Available, Stale)
*** Used By: ProductivityData, PCS
*******************************************************************************/

/* TODO: is this needed? */
PROD_CORE_PRAGMA_PACK_PUSH(1)
typedef PROD_CORE_PACKED struct
{
    unsigned_32             value;
    PROD_REALTIME_STATUS_T  status;
}REALTIME_STAMP;
PROD_CORE_PRAGMA_PACK_POP()

/*******************************************************************************
***     TRUCK_TICKET - Stucture containing truck information for printer ticket
*** Used By: Printer, PCS
*******************************************************************************/

typedef struct
{
    float               total_cycle_weight;
    unsigned_16         matID;
    unsigned_16         truckID;
    char                matIDname[PROD_SIZE_OF_MAT_NAME];
    char                truckIDname[PROD_SIZE_OF_TRUCK_NAME];
    unsigned_16         opID;
    char                opIDname[PROD_SIZE_OF_OP_ID_DESC];
    TIMESTAMP           time;
    unsigned_8          pass_count;
    unsigned_8          matID_status;
    unsigned_8          truckID_status;
    char                truck_ticket_padding[22];
}TRUCK_TICKET;

/*******************************************************************************
***     CT CYCLE RECORD - Stucture containing status information for PCS and ProductivityData
*** Used By: ProductivityData, PCS
*******************************************************************************/

/**********************************************************************************
General UID information structure
***********************************************************************************/
PROD_CORE_PRAGMA_PACK_PUSH(1)
typedef PROD_CORE_PACKED struct
{
    unsigned_32 uid;
    unsigned_8 uid_id;
    unsigned_8 uid_size;
    unsigned_8 uid_dataype;
    unsigned_8 uid_color;
    unsigned_16 uid_dataSource;
}UID_INFO;
PROD_CORE_PRAGMA_PACK_POP()

/*******************************************************************************
*** ProdCore Common Typedefs
*******************************************************************************/


/* OnBoardTotals */
typedef TIMESTAMP ob_timestamp;

typedef NVM_BLOCK_T ob_nvm_block_t;

/* Materia Totals */
typedef MATERIAL_TYPE mt_material_type;
typedef MATERIAL_REPORT_DATA_REC mt_material_report_data_rec;
typedef CONNECTION_INFO mt_connection_info;
typedef NVM_BLOCK_T mt_nvm_block_t;

/* Printer */
typedef NVM_BLOCK_T prt_nvm_block_t;
typedef CONNECTION_INFO prt_connection_info;
typedef TIMESTAMP PRT_TIMESTAMP;
typedef MATERIAL_TYPE PRT_MATERIAL_TYPE;
typedef MATERIAL_REPORT_DATA_REC PRT_MATERIAL_REPORT;
typedef TRUCK_TICKET PRT_TRUCK_TICKET;

/* Productivity Data */
typedef TIMESTAMP pd_timestamp;
typedef CONNECTION_INFO pd_connection_info;
typedef NVM_BLOCK_T pd_nvm_block_t;
typedef void (PD_FUNC_PTR)(unsigned_8* pLocation, unsigned_16 size);
typedef REALTIME_STAMP pd_realtime_stamp;

/* PCS */
typedef TIMESTAMP clock_stamp;
typedef CONNECTION_INFO bdt_connection_t;
typedef NVM_BLOCK_T NVM_BLOCK;
typedef TRUCK_TICKET PCS_TRUCK_TICKET;
typedef MATERIAL_TYPE pcs_material_type;
typedef UID_INFO pcs_uid_info;
typedef REALTIME_STAMP pcs_realtime_stamp;

/*******************************************************************************
***
*** ProdCore Public Functions
***
*******************************************************************************/

/* OnBoardTotals */
void ob_set_lifetime_load_count(unsigned_32 count);
unsigned_32 ob_get_lifetime_load_count(void);
void ob_set_lifetime_loading_duration(unsigned_32 duration);
unsigned_32 ob_get_lifetime_loading_duration(void);
void ob_set_lifetime_delay_count(unsigned_32 count);
unsigned_32 ob_get_lifetime_delay_count(void);
void ob_set_lifetime_delay_duration(unsigned_32 duration);
unsigned_32 ob_get_lifetime_delay_duration(void);
void ob_set_lifetime_cycle_count(unsigned_32 count);
unsigned_32 ob_get_lifetime_cycle_count(void);
void ob_set_lifetime_cycle_duration(unsigned_32 duration);
unsigned_32 ob_get_lifetime_cycle_duration(void);
unsigned_32 ob_get_totPayload(void);
unsigned_8  ob_set_totPayload(unsigned_32 payload);
unsigned_8  ob_calc_cycle_duration (unsigned_32 cycle_duration);


unsigned_8 send_cycle_record_block(void);
unsigned_8 send_load_record_block(void);
unsigned_8 send_status_record_block(void);
unsigned_8 send_segment_record_block(void);
unsigned_8 send_payload_record_block(void);
unsigned_8 send_gps_record_block(void);

unsigned_8 remove_cycle_record_block(void);
unsigned_8 remove_payload_record_block(void);
unsigned_8 clear_payload_records(void);
void send_data_ctrl_command(unsigned_8 data_ctrl);

/* Dummy function*/

extern unsigned_8 remove_payload_record_block(void);
extern unsigned_8 clear_payload_records(void);

/* PCS */
boolean pcs_is_auto_ids_enabled(void);
void payload_update_load_start_time(unsigned_32 current_utc_time);


/* Prototypes */
typedef unsigned_8 prod_get_keyoff_status(void);


#if defined (__cplusplus)
}
#endif

#endif /* __PROD_CORE_PUBLIC_H__ */
