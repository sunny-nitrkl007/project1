/******************************************************************************
*** FILE:
*** app_nvm.c
***
*** COPYRIGHT NOTICE:
*** Copyright 2014.  Caterpillar Inc.  All Rights Reserved.
*** This work contains Caterpillar's proprietary information which
*** may constitute a trade secret and/or be confidential.  Copyright
*** notice is precautionary only and does not imply publication.
***
*** DESCRIPTION:
*** The routines that are needed for NVM
******************************************************************************/
#include <app_globals.h>
#include "app_nvm.h"
#include <bsp_qsmcm_types.h>
#include <clock_tm_zone_defs.h>
#include <clock_rtc_mod_globals.h>   /* to obtain block_info_addr */
#include <mt_public.h>
#include <prt_public.h>
#include <ob_totals_public.h>
#include <string.h>
#include <pd_public.h>
#include <platform_declaration.h>

#ifdef A5M4V1
#include <app_io.h>
#endif

unsigned_8 app_nvm_clock_time_zone_init(void);
unsigned_8 blockrepairedvariable = 0;

/* NVM block definition table */
/*!ISSUE! - for TEST purposes we need to use same (physical)ECM as PCS on the bench.
 * So, we are inserting a filler block to skip over PCS data in NVM and we are using the same 
 * signature block at the end of NVM.
 */
NVM_block_init_table_entry_t BIT_device0[] =
{ /* Block type      , block size                  , block ID                 , next block    , prev block */ 
    { NVM_RAW_BLK    , NVM_SKIP_PCS_MAIN_SIZE      , NVM_SKIP_PCS_MAIN_ID     , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,
    { NVM_RAW_BLK    , NVM_CORE_CLOCK_1_SIZE       , NVM_CORE_CLOCK_1_ID      , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,
    { NVM_CRC16_BLK  , NVM_WTS_PE_CALIBRATION_SIZE , NVM_WTS_PE_CAL_BLOCK_ID  , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,
    /*{ NVM_CRC16_BLK  , NVM_SKIP_PD_DATA_SIZE       , NVM_PD_DATA_BLOCK_ID     , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,*/
	{ NVM_CRC16_BLK  , NVM_PRT_TICKET_DATA_SIZE    , NVM_PRT_TICKET_DATA_BLOCK_ID    , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,
	{ NVM_CRC16_BLK  , NVM_PRT_CONFIG_DATA_SIZE    , NVM_PRT_CONFIG_DATA_BLOCK_ID    , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,
	{ NVM_CRC16_BLK  , NVM_MTOT_DATA_SIZE          , NVM_MTOT_DATA_BLOCK_ID   , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,
	{ NVM_CRC16_BLK  , NVM_OB_DATA_SIZE1           , NVM_OB_DATA_BLOCK_ID1     , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,
	{ NVM_CRC16_BLK  , NVM_OB_DATA_SIZE2           , NVM_OB_DATA_BLOCK_ID2     , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,
	{ NVM_CRC16_BLK  , NVM_PD_DATA_SIZE            , NVM_PD_DATA_BLOCK_ID     , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,
	{ NVM_CHK_SUM_BLK, NVM_CLOCK_TIME_ZONE_SIZE    , NVM_CLOCK_TIME_ZONE_ID   , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,
    { NVM_RAW_BLK    , NVM_FILLER_BLOCK_SIZE       , NVM_FILLER_BLOCK_ID      , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,
    { NVM_RAW_BLK    , NVM_SKIP_PCS_MISC_SIZE      , NVM_SKIP_PCS_MISC_ID     , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,
    { NVM_RAW_BLK    , NVM_SIG_BLOCK_SIZE          , NVM_SIG_BLOCK_ID         , {0xFF,0xFFFF} , {0xFF,0xFFFF} } 
};
/* undelete this block and remove block above if we get our own test ECM */
//NVM_block_init_table_entry_t BIT_device0[] =
//{ /* Block type      , block size                  , block ID                 , next block    , prev block */ 
//    { NVM_RAW_BLK    , NVM_CORE_CLOCK_1_SIZE       , NVM_CORE_CLOCK_1_ID      , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,
//    { NVM_CRC16_BLK  , NVM_WTS_PE_CALIBRATION_SIZE , NVM_WTS_PE_CAL_BLOCK_ID  , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,
//    { NVM_RAW_BLK    , NVM_FILLER_BLOCK_SIZE       , NVM_FILLER_BLOCK_ID      , {0xFF,0xFFFF} , {0xFF,0xFFFF} } ,
//    { NVM_RAW_BLK    , NVM_SIG_BLOCK_SIZE         , NVM_SIG_BLOCK_ID         , {0xFF,0xFFFF} , {0xFF,0xFFFF} } 
//};

/* NVM block handles */
NVM_block_handle_t 	nvm_core_clock_1;
NVM_block_handle_t 	nvm_wts_pe_cal_block;
NVM_block_handle_t 	nvm_wts_pe_serial_num_block;
NVM_block_handle_t 	nvm_filler_block;
NVM_block_handle_t 	nvm_sig_block;
NVM_block_handle_t 	pd_nvm_block;
NVM_block_handle_t 	mtot_nvm_block;
NVM_block_handle_t  nvm_prt_ticket_block;
NVM_block_handle_t  nvm_prt_config_block;
NVM_block_handle_t  nvm_ob_data_block1;
NVM_block_handle_t  nvm_ob_data_block2;
NVM_block_handle_t  nvm_clock_time_zone_block;


/* NVM device driver table */
NVM_driver_table_t eeprom_ddt_ptr=
{ 
	bsp_nvm_init,
	bsp_nvm_read,
	bsp_nvm_write,
	bsp_nvm_acquire,
	bsp_nvm_release
};

/* NVM cache arrays */
unsigned_32 nvm_wts_pe_cal_block_cache[NVM_WTS_PE_CALIBRATION_SIZE];
unsigned_32 nvm_wts_pe_serial_num_block_cache[SERIAL_NUM_SIZE];
unsigned_8 clock_nvm_cache[NVM_CORE_CLOCK_1_SIZE];
unsigned_32 nvm_prt_ticket_block_cache[NVM_PRT_TICKET_DATA_SIZE];
unsigned_8 nvm_app_clock_time_zone_cache[NVM_CLOCK_TIME_ZONE_SIZE];
unsigned_8 test;

/* This function is used to initialize the NVM on powerup */
unsigned_8 app_nvm_init_start(void)
{
	unsigned_8 func_value, signature_status;
	unsigned_32 nvm_free_space;
	static NVM_block_write_trigger_t nvm_block_write_trigger;

	/* configure and initialize nvm device */
	#ifdef A5M4V1

	func_value = nvm_device_cfg( 0, 1, 0, BSP_NVM_AT25256_SIZE_CORRECTED,&eeprom_ddt_ptr);

	#endif

	#ifdef A4M1V2

	func_value = nvm_device_cfg( 0, 1, ((unsigned_32) &QSMCM), BSP_NVM_AT25256_SIZE_CORRECTED,&eeprom_ddt_ptr);

	#endif
	if ( NVM_SUCCESS != func_value )
	{
		/* If not successful, return an error. */
		return NVM_DEVICE_CFG_ERR; 
	}
	func_value = nvm_device_init( NVM_TOTAL_BLOCK_COUNT, BIT_device0, &nvm_block_write_trigger, 0, 1, &nvm_free_space);
	if ( NVM_SUCCESS != func_value )
	{
		/* If not successful, return an error. */
		return NVM_DEVICE_INIT_ERR;
	}

	/* Initialize the NVM Signature Block */
	func_value = nvm_sig_init( APP_TYPE, APP_VERSION, APP_CHECKSUM_ADJUST, SIG_WRITE_DELAY, &signature_status);
	
	/* This function writes the signature information into the NVM upon a signature init failure*/
	test = app_nvm_init_finish();
	
	if (test != NVM_INIT_SUCCESS)
	{
	return NVM_SIG_INIT_ERR;
	}
	if (NVM_DATA_REPAIRED == func_value)
	{
	blockrepairedvariable = 1;
	}
	if ((NVM_SUCCESS != func_value) && (NVM_DATA_REPAIRED != func_value))
	{
		/* If not successful and not repaired, return an error. */ 
		return NVM_SIG_INIT_ERR;
	}	
	
	(void)app_nvm_clock_time_zone_init();
			
	return NVM_INIT_SUCCESS;
}
		
		
/* This functions initializes and configures the time zone nvm block */
unsigned_8 app_nvm_clock_time_zone_init(void)
{
	unsigned_8	ret_value;
	/* Initialize the premium software nvm block */
   	ret_value = nvm_block_init(NVM_BLOCK_CACHED, (unsigned_8*)nvm_app_clock_time_zone_cache, NVM_CLOCK_TIME_ZONE_ID, -1, &nvm_clock_time_zone_block);
	if(ret_value != NVM_SUCCESS)
	{
		memset((unsigned_8*)&nvm_app_clock_time_zone_cache, 0x00, NVM_CLOCK_TIME_ZONE_SIZE);
		nvm_block_write(nvm_clock_time_zone_block, NVM_CLOCK_TIME_ZONE_SIZE, 0, (unsigned_8*)nvm_app_clock_time_zone_cache, -1);
	}
	/* Set clock global variables */
   	block_table_addr.block_table_info = nvm_clock_time_zone_block;
   	block_table_addr.init_status = BLOCK_TABLE_INFO_INIT_OK;
	return(ret_value);
}
		
		
		
unsigned_8 app_nvm_init_finish(void)
{
	unsigned_8 signature_status;
			
	signature_status = nvm_sig_status();
	if (0 != (signature_status & (NVM_SIG_APP_TYPE_CHG | NVM_SIG_APP_VER_CHG | NVM_SIG_CORE_VER_CHG)))
	{
		/* If the signature block changed, write the new signature block.*/
		if (NVM_SUCCESS != nvm_sig_write_event())
		{
			return NVM_SIG_WRITE_ERR;
		}
// /* !ISSUE! */		app_nvm_update_flag = TRUE;

	}
		return NVM_INIT_SUCCESS;
}

unsigned_8 app_get_nvm_sig_status(void)
{
    return (nvm_sig_status());
}

unsigned_8 app_nvm_block_status( NVM_block_handle_t block_handle )
{
    unsigned_8 retval;
    retval = nvm_block_status(block_handle);
    return(retval);
}


unsigned_8 app_nvm_block_init(unsigned_8 block_type,
                                 unsigned_8 * block_cache_ptr,
                                 unsigned_32 data_id,
                                 int block_priority, 
                                 NVM_block_handle_t * block_handle_ptr)
{
    unsigned_8 retval;

     retval = nvm_block_init(block_type, block_cache_ptr, data_id, block_priority, block_handle_ptr);

    return(retval);
}

unsigned_8 app_nvm_block_write(NVM_block_handle_t block_handle,
	                              unsigned_32 write_size,
	                              unsigned_32 write_offset,
		                          unsigned_8  *source_ptr,
		                          int write_task_priority )
{
    unsigned_8 retval;

    retval =  nvm_block_write(block_handle, write_size, write_offset, source_ptr, write_task_priority );

    return(retval);
}
