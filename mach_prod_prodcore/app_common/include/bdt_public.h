/*******************************************************************************
**
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%
*** %% COPYRIGHT (C) 2001 - 2011 CATERPILLAR INC. ALL RIGHTS RESERVED.
*** %%     This work contains proprietary information which may
*** %%     constitute a trade secret and/or be confidential.
*** %%     Copyright notice is precautionary only and does not
*** %%     imply publication.
*** %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
*** FILE:
***	bdt_public.h
***
*** DESCRIPTION:
***	This is the definition include file for the bdt module. Currently only calibration data
*** type is supported by the ECM.
***	IMPORTANT NOTE:  All global variables should be considered read-only
***	                 by any external module that accesses them.
***	                 It is forbidden for any routines besides those
***	                 local to this module to alter these variables.
***
*** HISTORY:
*** Change 00  19NOV2002 (TCZ ) Initial Version
***
*** Change 01  12DEC2003 (BJV)
***   Changed and added variables necessary to allow calibration to be
***   transmitted using the correct protocol for Product Link.
***
******************************************************************************/
#ifndef __BDT_PUBLIC_H__
#define __BDT_PUBLIC_H__

#include <std_types.h>
#include <bdt_proto.h>



/*Data Type for calibration file as defined by Caterpillar System Standards
*/
#define CAL_DATATYPE 0xC280
#define ONBOARDHEADER 0xB100
#define ONBOARD_VER_LISTING 0x0000
#define ONBOARD_VER_NONLISTING  0x0002
#define CAL_AFTERMARKETID	0x3344
#define CAL_DATA_REP  0x00000101  /*   (CDL)     */
#define CAL_NUM_RECORD_BLOCKS  0x00000001
#define CAL_RECORD_VERSION  0x0002
#define CAL_SUBFILE_LISTING_ID  0x80000010
#define CAL_SUBFILE_NONLISTING_ID  0x00000010
#define CAL_RECORD_BLOCK_SIZE  sizeof(Cal_Record_Block_t)
#define CAL_TYPE  0x00
#define CAL_DATA_ACCESS  0x0000
#define MAX_NUM_CLUTCHES 5
#define MAX_NUM_HISTORY 5
#define CAL_NUM_SUBFILES 1
#define CAL_DATA_BLOCK 0xC290
#define CAL_ID 0x0010
#define CAL_VERSION 0x0002
#define CAL_COMPONENT_ID_BASE 1401
#define UNSTRUCTURED_DATA_BLOCK_ID  0x4100
#define UNSTRUCTURED_DATA_BLOCK_COUNT 12
#define CAL_LISTING                 0xFFFFFFFE
#define CAL_ALL                     0xFFFFFFFF
#define ONBOARD_HEADER              0x00  /* Calibration BDT State */
#define CALIBRATION_RECORD          0x02  /* Calibration BDT State */
#define CALIBRATION_DESC_BLOCK      0x04  /* Calibration BDT State */
#define CAL_UNSTRUCTURED_DATA_BLOCK 0x06  /* Calibration BDT State */
#define CAL_LIST_FILE_SIZE 0x22  

/* Unstructured data  in Calibration File. it is freeto have data as defined by 
** the application. I decide to stuff pulse time, hold level , ramp level , 
** temperature and sustain level in it
*/
typedef struct 
{
    unsigned_16 pulse_time;
    
    unsigned_16 hold_level;
    
    unsigned_16 ramp_level;
    
    unsigned_16 temp;
    
    unsigned_16 sustain_level;

    unsigned_16 packing_byte;  /* packing byte to make structure long word aligned */
    
} ECPC_Cal_Unstructured_Data_t;

/*Unstructured data block structure of Calibration File
*/
typedef struct
{
    unsigned_16 unstructured_data_block_id;
    
    unsigned_16 byte_count;
    
    ECPC_Cal_Unstructured_Data_t unstructured_data;
    
} Unstructured_Data_Block_t;

/*Calibration Data Block of Calibration File
*/
typedef struct 
{
   unsigned_16 cal_data_block_id;
    
    unsigned_16 cal_id;
    
    unsigned_16 cal_version;
    
    unsigned_16 app_id;
    
    unsigned_16 component_id;
    
    unsigned_16 cal_status;
    
    unsigned_32 hours;
    
    Unstructured_Data_Block_t  unstructured_data_block;
    
} Cal_Data_Block_t;

/* This is used to create the proper alignment for use with Product Link */
#pragma pack(1)

/*Cal Record Block of Calibration File
*/
typedef struct
{
    unsigned_16 cal_record_block_id;
    
    unsigned_16 cal_record_version;
    
    unsigned_32 cal_sub_file_id;
    
   // unsigned_16 cal_record_block_size;
    
    unsigned_16 cal_type;
    
    unsigned_16 security_access_level;
    
    unsigned_32 no_sub_files;
    
    Cal_Data_Block_t  cal_data_block[MAX_NUM_CLUTCHES * MAX_NUM_HISTORY];
            
} Cal_Record_Block_t;

/*On Board File portion of Calibration File
*/
typedef struct{
    unsigned_16 on_board_file_header_id;
    
    unsigned_16 on_board_file_header_ver;
    
    unsigned_16 aftermarket_id;
    
    unsigned_16 file_contents_type;
    
    unsigned_32 data_rep_type;
    
    unsigned_32 no_cal_sub_files;
    
    Cal_Record_Block_t cal_record_block;
    
}bdt_On_Board_File_t;                
        
#define CAL_FILE_SIZE sizeof(bdt_On_Board_File_t) 
#pragma pack(4)
        
/*Declaration of bdt functions based on prototypes already defined by bdt core
*/
bdt_query_index_supported_t bdt_app_query_index_supported;

bdt_obtain_data_access_t    bdt_app_obtain_data_access;

bdt_release_data_access_t   bdt_app_release_data_access;

bdt_get_data_size_t         bdt_app_get_data_size;

bdt_open_data_t             bdt_app_open_data;

bdt_close_data_t            bdt_app_close_data;

bdt_get_data_t              bdt_app_get_data;

bdt_set_data_t              bdt_app_set_data;

/*app_bdt_init is initialization function called by app_pre_irq_init()
*/
void app_bdt_init(void);

#endif
