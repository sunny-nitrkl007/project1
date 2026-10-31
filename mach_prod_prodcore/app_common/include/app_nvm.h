/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 2014 CATERPILLAR INC.   ALL RIGHTS RESERVED.       %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
***
*** DESCRIPTION :
***	NVM include file 
***
*** LANGUAGE :
***    ANSI C
***
*** MACRO LIST:
***
*******************************************************************************/
#ifndef __APP_NVM_H__
#define __APP_NVM_H__

#include <nvm.h>
#include <bsp_nvm_defs.h>
#include <bsp_nvm_serial_defs.h>
#include <app_globals.h>
#include <mt_public.h>
#include <prtlib_public.h>
#include <prt_report_public.h>

//#include <adapter_nvm.h>

/* NVM block configuration definitions */
#define NVM_DATA_BLOCK_ID 0x00010010
/* assumed to be a raw block */
#define NVM_CORE_CLOCK_1_SIZE 22

/* assumed to be a 3-copy block */
//#define NVM_DIAG_BLOCK_ID 0x00010002
//#define NVM_DIAG_BLOCK_SIZE DIAGNOSTIC_CACHE_MEM_SIZE_W_REALTIME(DIAG_MAX_LOG_ENTRIES, SHM_SIZE)

/* assumed to be a 3-copy block */
//#define NVM_EVENT_BLOCK_ID 0x00010003
//#define NVM_EVENT_BLOCK_SIZE EVENT_CACHE_MEM_SIZE_W_REALTIME(EVENT_MAX_LOG_ENTRIES, SHM_SIZE)

/* assumed to be a checksum block */
#define NVM_WTS_PE_CAL_BLOCK_ID 0x00010014
#define NVM_WTS_PE_CALIBRATION_BLOCK_SIZE NVM_WTS_PE_CALIBRATION_SIZE
#define NVM_PD_ADAPTER_BLOCK_SIZE NVM_WTS_PE_CALIBRATION_SIZE

/* assumed a raw block */
#define NVM_SERIAL_NUM_BLOCK_ID		0x0001000C
#define NVM_SERIAL_NUM_BLOCK_SIZE	sizeof(PRMSW_NVM_t)

/* assumed a crc 16 block */
#define NVM_PRT_TICKET_DATA_SIZE sizeof(PRT_DATA_BLK)
#define NVM_PRT_TICKET_DATA_BLOCK_ID 0x00010017

/* assumed a crc 16 block */
#define NVM_PRT_CONFIG_DATA_SIZE sizeof(PRT_CONFIG_BLK)
#define NVM_PRT_CONFIG_DATA_BLOCK_ID 0x00010018

/* assumed a raw block */
//#define NVM_PRMSW_BLOCK_ID		0x0001000C
//#define NVM_PRMSW_BLOCK_SIZE	sizeof(PRMSW_NVM_t)

//#define NVM_PASSWD_BLOCK_ID		0x0001000D
//#define NVM_PASSWD_BLOCK_SIZE	sizeof(PASSWD_NVM_t)

/* assumed to be a 3-copy block */
#define NVM_SIG_BLOCK_ID 0x00000000
#define NVM_SIG_BLOCK_SIZE 10


/*!ISSUE! - for TEST purposes we need to use same (physical)ECM as PCS on the bench.
 * So, we are inserting a filler block to skip over PCS data in NVM and we are using the same 
 * signature block at the end of NVM.
 */
#define NVM_SKIP_PCS_MAIN_SIZE (6578)
#define NVM_SKIP_PCS_MAIN_ID    0x00010015
#define NVM_SKIP_PCS_MISC_SIZE (110) /* does not include SIG block size because WTS is reusing the block */
#define NVM_SKIP_PCS_MISC_ID    0x00010016

//#define NVM_STORAGE_SIZE ((NVM_SIG_BLOCK_SIZE) + (NVM_CORE_CLOCK_1_SIZE) + (NVM_WTS_PE_CALIBRATION_BLOCK_SIZE))
//#define NVM_WTS_PE_CALIBRATION_BLOCK_SIZE WTS_PE_CALIBRATION_BLOCK_STORAGE_SIZE(2)

/*!ISSUE! - for TEST purposes we need to use same (physon the bench.
 * So, we are inserting a filler block to skip over WTS data in NVM and we are using the same 
ical)ECM as PCS AND WTS  * signature block at the end of NVM.
 */
/*#define NVM_PD_DATA_BLOCK_ID    0x00010017*/

#define PD_STATUS_RB_SIZE		(PD_STATUS_BLK_SIZE * PD_MAX_STATUS_RECORDS)
#define PD_SEGMENT_RB_SIZE		(PD_SEGMENT_BLK_SIZE *	PD_MAX_SEGMENT_RECORDS)
#define PD_CYCLE_RB_SIZE 		((PD_CYCLE_BLK_SIZE + PD_SEGMENT_RB_SIZE) * PD_MAX_CYCLE_RECORDS)
#define PD_LOAD_RB_SIZE 		(PD_LOAD_BLK_SIZE * PD_MAX_LOAD_RECORDS)
#define PD_MISC_RB_SIZE			 PD_MISC_DATA_BLK_SIZE
/* future enhancement - need to be able to calculate NVM block size based on input of Productivty data */
//#define NVM_PD_DATA_SIZE        ( PD_STATUS_RB_SIZE + PD_CYCLE_RB_SIZE + PD_LOAD_RB_SIZE + PD_MISC_RB_SIZE  + PD_LAST_STORE_INFO_SIZE)


/****SHOULD BE CHANGED LATER!!!!*****/
/*Temporarily giving the max number of bytes that can be stored in the NVM.*/
#define NVM_PD_DATA_SIZE		1000 


/* Last store button information will be saved in NVM as follows : 
   unsigned_8  for total records 
   + unsigned_32 for total size 
   + 3 * unsigned_16 (number of load records, cycle records and status recs)  
   + unsigned_8 flag
*/
#define PD_LAST_STORE_INFO_SIZE 12  
/* future enhancement - need to be able to calculate NVM block size based on input of Productivty data */

#define NVM_SKIP_PD_DATA_SIZE        ( 5329 + PD_LAST_STORE_INFO_SIZE)

#define NVM_STORAGE_SIZE ((NVM_SIG_BLOCK_SIZE) + (NVM_CORE_CLOCK_1_SIZE) + (NVM_WTS_PE_CALIBRATION_BLOCK_SIZE +2) + (NVM_CLOCK_TIME_ZONE_SIZE + 1))

#define NVM_MTOT_DATA_BLOCK_ID 0x00010019
#define NVM_MTOT_DATA_SIZE   1000  

#define NVM_OB_DATA_BLOCK_ID1 0x00010020
#define NVM_OB_DATA_SIZE1   OB_TOTALS_KEYOFF_REC_SIZE

#define NVM_OB_DATA_BLOCK_ID2 0x00010021
#define NVM_OB_DATA_SIZE2   OB_TOTALS_LIFETIME_NVM_SIZE    

#define	NVM_CLOCK_TIME_ZONE_ID		0x0001000E
#define NVM_CLOCK_TIME_ZONE_SIZE	25

#define NVM_PD_DATA_BLOCK_ID 0x00010022



/* assumed to be a raw block */
#define NVM_FILLER_BLOCK_ID 0xFFFFFFFF
#define NVM_FILLER_BLOCK_SIZE (BSP_NVM_AT25256_SIZE_CORRECTED - \
                                ((NVM_SKIP_PCS_MAIN_SIZE) + (NVM_STORAGE_SIZE) + (NVM_SKIP_PCS_MISC_SIZE) + (NVM_MTOT_DATA_SIZE + 2) + (NVM_PRT_TICKET_DATA_SIZE + 2) + (NVM_PRT_CONFIG_DATA_SIZE + 2) + (NVM_OB_DATA_SIZE1 + 2) + (NVM_OB_DATA_SIZE2 + 2) + (NVM_PD_DATA_SIZE + 2)))

#define NVM_TOTAL_BLOCK_COUNT 13
#define SIG_WRITE_DELAY 0

/* NVM function return values */
#define NVM_INIT_SUCCESS    1
#define NVM_DEVICE_CFG_ERR  2
#define NVM_DEVICE_INIT_ERR 3
#define NVM_SIG_INIT_ERR    4
#define NVM_BLK_INIT_ERR    5
#define NVM_SIG_WRITE_ERR   6
#define NVM_BLK_WRITE_ERR   7
#define NVM_SIG_READ_ERR    8
#define NVM_BLK_READ_ERR    9

/* value for number of consecutive failures allowed before diag triggers */
#define PE_FAILURE_LIMIT 3
/***************************************************************************
 * TEMPORARY copy of NVM info from wts_pe_public.h 
 * just to get this to compile during makefile design
 *
 ***************************************************************************
 */
typedef struct	
{
	/* Calibrations States  */
	unsigned_16		steps_complete;
	unsigned_16 pad;			         /* Pad to maintain 32-bit alignment */ 
    /*  Cal outputs */
    struct 
    {
        float eb_apron_float_intercept;  /* payload vs bowl cyl resultant force apron in float */
        float eb_no_float_intercept;     /* payload vs bowl cyl resultant force apron not resting on bowl */
    } out;
} WTS_PE_CAL_INFO;

/* nonvolitile RAM data structure */
/* NOTE: total size of nvm storage can NOT change without signoff from WTS application sw group.
 * wts_pe_reserve[] array MUST be adjusted if any changes are made in the other parameters so
 * total size of WTS_PE_NVM_INFO remains the same. 
 */
typedef	struct	
{
    float           payload_last_load_wt;       /* payload weight of last known or current load */
    unsigned_8      nvm_block_signature;        /* block signature from application */
    unsigned_8      pad[3];                     /* maintain alignment */
    WTS_PE_CAL_INFO cal;
    unsigned_8      wts_pe_reserve[64];         /* reserve some space for nvm changes, see note above  */
} WTS_PE_NVM_INFO;
/******************************************************************/
/* Macros                                                         */
/******************************************************************/
 
 /* size of the library NVM data 
  * NOTE: The size of NVM storage can NOT change without permission
  * from the WTS application SW group
  */
#define NVM_WTS_PE_CALIBRATION_SIZE sizeof(WTS_PE_NVM_INFO)

/******************************************************************/
/* END of  TEMPORARY Copy of wts NVM info                         */
/******************************************************************/

/* NVM function prototypes */
unsigned_8 app_nvm_init_start(void);
unsigned_8 app_nvm_init_finish(void);
unsigned_8 app_get_nvm_sig_status(void);
unsigned_8 app_nvm_block_status(NVM_block_handle_t);
unsigned_8 app_nvm_block_init(unsigned_8, unsigned_8 *, unsigned_32, int, NVM_block_handle_t * );
unsigned_8 app_nvm_block_write(NVM_block_handle_t, unsigned_32, unsigned_32, unsigned_8  *, int);


/* NVM global variables */
extern NVM_block_handle_t nvm_core_clock_1;
extern NVM_block_handle_t nvm_wts_pe_cal_block;
extern NVM_block_handle_t nvm_pd_serial_num_block;
extern NVM_block_handle_t pd_nvm_block;
extern unsigned_8 clock_nvm_cache[];
extern unsigned_32 nvm_wts_pe_cal_block_cache[];
extern unsigned_32 nvm_wts_pd_serial_num_block_cache[];
extern NVM_block_handle_t mtot_nvm_block;


/*printers*/
extern NVM_block_handle_t nvm_prt_ticket_block;
extern NVM_block_handle_t nvm_prt_config_block;
extern unsigned_32 nvm_prt_ticket_block_cache[];


/*On Board Totals*/
extern NVM_block_handle_t nvm_ob_data_block1;
extern NVM_block_handle_t nvm_ob_data_block2;
extern NVM_block_handle_t nvm_clock_time_zone_block;

#endif /* __APP_NVM_H__ */
