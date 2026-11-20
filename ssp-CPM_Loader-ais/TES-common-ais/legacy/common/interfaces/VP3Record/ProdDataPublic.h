/*******************************************************************************
** COPYRIGHT (C) 2018 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: ProdDataPublic.h
DESCRIPTION:
*******************************************************************************/
#ifndef __PRODDATAPUBLIC_H__
#define __PRODDATAPUBLIC_H__
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <string.h>
#include <std_types.h>
#include <stdlib.h>
#include <stdio.h>

#define TABLE_SIZE 20
#define FALSE 0
#define TRUE 1
#define RECORD_MAX_SIZE 13  //13 bytes data 

#define BUFFER_SIZE_EXCEEDED_ERROR 0
#define NULL_POINTER_ERROR 1
#define SEND_REC_SUCCESS 2

#define TIMESTAMP_UID_FIRST_BYTE 0x81
#define TIMESTAMP_UID_SECOND_BYTE 0x01
#define TIMESTAMP_UID_THIRD_BYTE 0x00
#define TIMESTAMP_UID_FOURTH_BYTE 0x07

#define SIZE_OF_UTC 4
#define SIZE_OF_TZOFFSET 2
#define SIZE_OF_SHM 4

typedef uint32_t TIMESTAMP_UTC;
/*
typedef struct __attribute__((packed))
{
    unsigned_8  sec;
    unsigned_8  min;
    unsigned_8  hour;
    unsigned_8  day;
    unsigned_8  mon;
    unsigned_8  year;
}TIMESTAMP;*/

typedef void (PD_FUNC_PTR)(uint8_t* address,uint16_t length);

typedef struct __attribute__((packed))
{
    uint8_t uid[4]; 
    uint8_t uid_id; 
    uint8_t uid_size;
    uint8_t uid_dataype;
    uint8_t uid_color;
    uint8_t uid_dataSource[2]; 
}pd_uid_info;

typedef enum {    
    REG_SUCCESS,
    REG_ERROR,
    REG_NULL_FUNC_PTR,
    REG_INVALID_BLOCK,
    REG_DUPLICATE_BLOCK,
    REG_SIZE_OVER_FLOW,
    REG_UID_SIZE_INVALID
}REG_RET_T;

typedef enum {
    PROD_BLOCK_TYPE_LOAD = 4724,
    PROD_BLOCK_TYPE_CYCLE = 4725,
    PROD_BLOCK_TYPE_SEGMENT = 4726,
    PROD_BLOCK_TYPE_STATUS = 4727,
    PROD_BLOCK_TYPE_PAYLOAD = 4728,
    PROD_BLOCK_TYPE_GPS = 4729
}BLOCK_TYPE_T;

typedef struct __attribute__((packed)) 
{     
     pd_uid_info block_uid;
     PD_FUNC_PTR* func_ptr;
} TABLE_T;

typedef struct __attribute__((packed)) 
{
    TABLE_T table_array[TABLE_SIZE];
    uint16_t curr_array_size;
    uint16_t num_required_fields;
} TABLE_ARRAY_T;

extern boolean init_complete;

extern TABLE_ARRAY_T load;
extern TABLE_ARRAY_T cycle;
extern TABLE_ARRAY_T segment;
extern TABLE_ARRAY_T status;
extern TABLE_ARRAY_T payload;
extern TABLE_ARRAY_T gps;

#ifdef __cplusplus
extern "C" {
#endif

/*Function prototypes */
REG_RET_T register_to_provide_block_info(pd_uid_info uidInfo,
                                         BLOCK_TYPE_T blockType,
                                         PD_FUNC_PTR* pFunction);
uint8_t send_gps_record_block();
uint8_t send_load_record_block();
uint8_t send_payload_record_block();
uint8_t send_segment_record_block();
uint8_t send_cycle_record_block();

#ifdef __cplusplus
}
#endif

#endif /* #ifndef __PRODDATAPUBLIC_H__ */

