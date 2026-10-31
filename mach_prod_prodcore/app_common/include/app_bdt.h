#ifndef __APP_BDT_H__
#define __APP_BDT_H__
/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                       %%
*** %% COPYRIGHT (C) 2002 -2013 CATERPILLAR INC. ALL RIGHTS RESERVED.        %%
*** %% This work contains proprietary information which may                  %%
*** %% constitute a trade secret and/or be confidential.                     %%
*** %%                                                                       %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
**
*
* DESCRIPTION : Contains the block data transfer interface functions to use the 	
*				BML library component.
*
* LANGUAGE :
*    ANSI C
*
* PORTABILITY ISSUES :
*******************************************************************************/


/*******************************************************************************/
#ifndef __BDT_H__
#include <bdt.h>			/*  lib_monitor */
#endif
#include <prod_core_public.h>
/*------------------------------------------------------------------------------------
***	External Defines, enums, typedefs
------------------------------------------------------------------------------------*/
#define CDL_RX_BUFFER_SIZE	240
#define CDL_TX_BUFFER_SIZE	240

/*------------------------------------------
	14 bytes
-------------------------------------------*/
typedef struct				
{
	unsigned_16		parser_id;
	void*			parser_fn;
}app_bdt_parser_fn_table_t;


/*------------------------------------------------------------------------------------
***	External Symbols
------------------------------------------------------------------------------------*/
extern app_bdt_parser_fn_table_t parser_table[];
extern bdt_sys_cnf_t app_bdt_sys_config[];
extern bdt_comm_cnf_t app_bdt_comm_config[];
extern unsigned_16	sys_config_size;
extern unsigned_16 comm_config_size;
extern unsigned_16 parser_table_count;
/*extern app_bdt_onboard_file_header_t		onboard_header;	*/
/*------------------------------------------------------------------------------------
***	External Functions
------------------------------------------------------------------------------------*/
extern int_32 app_bdt_init(void);

extern int_32	app_bdt_get_connection(CONNECTION_INFO*	data);

extern unsigned_8 app_bdt_initialize_data_link(unsigned_16 dlink_id);
						   
#endif  /* __APP_BDT_H__ */


