/******************************************************************************
 **
 ** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 ** %%                                                                       %%
 ** %%  COPYRIGHT (C) 1999 CATERPILLAR INC.  ALL RIGHTS RESERVED.            %%
 ** %%      This work contains proprietary information which may             %%
 ** %%      constitute a trade secret and/or be confidential.                %%
 ** %%                                                                       %%
 ** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 **
 ** DESCRIPTION:
 **     Payload Control System VIMSPC support.
 **
 ** LANGUAGE:
 **     ANSI C
 **
 ** PORTABILITY ISSUES:
 **     None.
 **
 *****************************************************************************/
#ifndef __PCS_OFFBOARD_PUBLIC_H__
#define __PCS_OFFBOARD_PUBLIC_H__

/*******************************************************************************
***
***    Referenced Functions, Data, & Symbols
***    -- #Include's --
***
*******************************************************************************/
#include <pcs_public.h>

/*******************************************************************************
***
***    Constants defined for this file
***    -- #Define's --
***
*******************************************************************************/
/* pcs print commands */
#define PCS_PRINT_MATERIALS	1
#define PCS_PRINT_TRUCKS 2
#define PCS_PRINT_DATALOGGER 3
#define PCS_PRINT_ADDITIONAL_TICKETS 4

/* Pcs printer unit definitions */
#define PCS_PRINTER_METRIC			0
#define PCS_PRINTER_ENGLISH_TONS	1
#define PCS_PRITNER_METRIC_KGS		2
#define PCS_PRINTER_ENGLISH_LBS		3

#define PCS_PRINTER_ENGLISH			0
#define PCS_PRINTER_SPANISH	        1
#define PCS_PRITNER_FRENCH	        2



		   										
/*******************************************************************************
***
***    Structure definitions for this file
***    -- typedefs --
***
*******************************************************************************/
typedef int_32  pcs_can_tx_callback_fn_t(char * buffer, unsigned_32 size);
typedef int_32  pcs_get_rx_can_message_t(char * packet);
typedef boolean pcs_wait_rx_can_message_t(void);
typedef char *	pcs_set_serial_number_t(char * serial_number);
typedef char *	pcs_set_equipment_number_t(char * equipment_number);

typedef struct	
{
	pcs_can_tx_callback_fn_t*   pcs_can_tx;	
	pcs_get_rx_can_message_t* 	pcs_get_rx_can_message;
	pcs_wait_rx_can_message_t*	pcs_get_rx_queue_status;
	pcs_set_serial_number_t*	pcs_set_serial_number;
	pcs_set_equipment_number_t*	pcs_set_equipment_number;
}	PCS_OFFBOARD_FUNC;

typedef struct
{
	unsigned_8		hardware_partnumber[12];
	unsigned_8		software_partnumber[12];
	unsigned_8		release_data[6];
	unsigned_8		unused[2];
}	PCS_OFFBOARD_INFO;		

/*******************************************************************************
***
***    Prototypes
***    
***
*******************************************************************************/
int_32	pcs_offboard_communications_init(NVM_BLOCK	nvm_block,
										 PCS_OFFBOARD_FUNC*	func_ptr,
										 PCS_OFFBOARD_INFO* info_ptr);
void pcs_offboard_communications_update(oel_rtos_task_context_t* task_context);

/* Access functions */
void pcs_print_totals(unsigned_16 setting);
void print_tickets(STORE* store_data);
void pcs_print_additional_ticket(void);
void pcs_printer_set_units(unsigned_8 unit_type);
unsigned_8 pcs_printer_get_units(void);
void pcs_printer_set_language(unsigned_8 language_type);
unsigned_8 pcs_printer_get_language(void);

/*******************************************************************************
***
***    Internal Data for this file
***    -- Global Symbols --
***
*******************************************************************************/

#endif