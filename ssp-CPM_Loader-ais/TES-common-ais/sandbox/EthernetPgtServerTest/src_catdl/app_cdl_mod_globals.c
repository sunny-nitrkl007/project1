/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 1994-1995 CATERPILLAR INC.   ALL RIGHTS RESERVED.       %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
***
*** DESCRIPTION :
***	Declare the CDL global storage variables whose sizes are defined
***	by the application.
***
*** REQUIRED HEADER :
***	app_cdl_config.h
***	cdl2_proto.h
***
*** LANGUAGE :                  
***    ANSI C
***
*** COMPILE FLAGS :
***
*** METHOD:
***	Use identifiers defined by the application in app_cdl_config.h to
***	define the sizes of these global variables.
***
*** NOTES:
***
*** FUNCTIONS:
***
*** INTERRUPTS:
***
*******************************************************************************/

#include "app_cdl_config.h"
#include <cdl2_proto.h>
#include <cdl_struct.h>
#include <cdl_mod_struct.h>
#include <cdl_std_hdlr_struct.h>
#include "app_rtos_config.h"

/*******************************************************************************
***
***    Constants defined for this file
***    -- #Define's --
***
*******************************************************************************/
/* This defines the required number of report que entires to support each 
   reference entry made by a requestor ECM for ADT status reports
   */
#define CDL2_ADT_MAX_NUM_REPORT_ENTRIES (CDL2_ADT_MAX_NUM_REF_ENTRIES*CDL2_ADT_MAX_NUM_PENDING_REPORTS)

/*******************************************************************************
***
***    Data types defined for this file
***    -- Struct's, Typedef's, Enum's --
***
*******************************************************************************/

/*******************************************************************************
***
***    File scope functions defined for this file 
***    -- Function Prototypes --
***
*******************************************************************************/

/*******************************************************************************
***
***    File scope symbols defined for this file
***    -- Symbols --
***
*******************************************************************************/

/*************************************************************************/
/****************** The following is for CDL and CDL2 ********************/
/*************************************************************************/
/* Define the CDL interrupt receive message buffers based on the number of 
   buffers defined by the application. 
   Define a constant variable to hold the number of buffers.
   */
const unsigned_16	cdl_num_rxb = CDL_NUM_RXB;
Cdl_mbuf_t		cdl_rxmb[(CDL_NUM_RXB)];

/* Define the CDL allocatable transmit message buffers based on the number of 
   buffers defined by the application. 
   Define a constant variable to hold the number of buffers.
   */
const unsigned_16	cdl_num_txb = CDL_NUM_TXB;
Cdl_mbuf_t		cdl_txmb[(CDL_NUM_TXB)];


/*************************************************************************/
/****************** The following is for CDL *****************************/
/*************************************************************************/
/* Define the CDL receive parameter information table based on the number 
   of entries defined by the application. 
   Define a constant variable to hold the number of entries.
   */
const unsigned_16	cdl_num_rx_pit = CDL_NUM_RX_PIT;
Cdl_rx_pit_t 		cdl_rx_pit[(CDL_NUM_RX_PIT)];

/* Define the CDL transmit parameter information table based on the number 
   of entries defined by the application. 
   Define a constant variable to hold the number of entries.
   */
const unsigned_16	cdl_num_tx_pit = CDL_NUM_TX_PIT;
Cdl_tx_pit_t		cdl_tx_pit[(CDL_NUM_TX_PIT)];

/* Define the CDL queued receive parameter storage block area based on the 
   number of blocks defined by the application. 
   Define a constant variable to hold the number of blocks.
   */
const unsigned_16	cdl_num_qrpsb = CDL_NUM_QRPSB;
Cdl_queued_parm_t	cdl_queued_rx_parm[(CDL_NUM_QRPSB)];



/*************************************************************************/
/****************** The following is for CDL2 ****************************/
/*************************************************************************/
/* Define the CDL2 transmit parameter information tables based on the number 
   of entries defined by the application. 
   Define a constant variables to hold the number of entries.
   */
const unsigned_16	cdl2_num_tx_pit = CDL2_NUM_TX_PIT;

const unsigned_16	cdl2_sublist_D0_num_tx_pit = CDL2_SUBLIST_D0_NUM_TX_PIT;
const unsigned_16	cdl2_sublist_D1_num_tx_pit = CDL2_SUBLIST_D1_NUM_TX_PIT;
const unsigned_16	cdl2_sublist_D2_num_tx_pit = CDL2_SUBLIST_D2_NUM_TX_PIT;
const unsigned_16	cdl2_sublist_D3_num_tx_pit = CDL2_SUBLIST_D3_NUM_TX_PIT;
const unsigned_16	cdl2_sublist_F916_num_tx_pit = CDL2_SUBLIST_F916_NUM_TX_PIT;
cdl2_tx_pit_t		cdl2_tx_pit[CDL2_NUM_TX_PIT];
cdl2_tx_pit_t		cdl2_sublist_D0_tx_pit[CDL2_SUBLIST_D0_NUM_TX_PIT];
cdl2_tx_pit_t		cdl2_sublist_D1_tx_pit[CDL2_SUBLIST_D1_NUM_TX_PIT];
cdl2_tx_pit_t		cdl2_sublist_D2_tx_pit[CDL2_SUBLIST_D2_NUM_TX_PIT];
cdl2_tx_pit_t		cdl2_sublist_D3_tx_pit[CDL2_SUBLIST_D3_NUM_TX_PIT];
cdl2_tx_pit_t		cdl2_sublist_F916_tx_pit[CDL2_SUBLIST_F916_NUM_TX_PIT];

/* Define the CDL2 receive parameter information tables based on the number 
   of entries defined by the application. 
   Define a constant variables to hold the number of entries.
   */
const unsigned_16    cdl2_num_con_rx_pit = CDL2_NUM_CON_RX_PIT;
cdl2_con_rx_pit_t    cdl2_con_rx_pit[CDL2_NUM_CON_RX_PIT];

const unsigned_16		cdl2_num_rx_pit = CDL2_NUM_RX_PIT;
const unsigned_16		cdl2_num_rx_data_pit = CDL2_NUM_RX_DATA_PIT ;
const unsigned_16		cdl2_num_rx_data_pit_MID_table = CDL2_NUM_RX_DATA_PIT_MID_TABLE;
cdl2_rx_pit_t			cdl2_rx_pit[CDL2_NUM_RX_PIT];
cdl2_rx_data_pit_t		cdl2_rx_data_pit[CDL2_NUM_RX_DATA_PIT];
cdl2_rx_data_pit_MID_table_t	cdl2_rx_data_pit_MID_table[CDL2_NUM_RX_DATA_PIT_MID_TABLE];

/* Define the CDL2 write parameter information tables based on the number 
   of entries defined by the application. 
   Define a constant variables to hold the number of entries.
   */
const unsigned_16	cdl2_num_wr_pit = CDL2_NUM_WR_PIT;
const unsigned_16	cdl2_sublist_D0_num_wr_pit = CDL2_SUBLIST_D0_NUM_WR_PIT;
const unsigned_16	cdl2_sublist_D1_num_wr_pit = CDL2_SUBLIST_D1_NUM_WR_PIT;
const unsigned_16	cdl2_sublist_D2_num_wr_pit = CDL2_SUBLIST_D2_NUM_WR_PIT;
const unsigned_16	cdl2_sublist_D3_num_wr_pit = CDL2_SUBLIST_D3_NUM_WR_PIT;
const unsigned_16	cdl2_sublist_F916_num_wr_pit = CDL2_SUBLIST_F916_NUM_WR_PIT;
cdl2_wr_pit_t		cdl2_wr_pit[CDL2_NUM_WR_PIT];
cdl2_wr_pit_t		cdl2_sublist_D0_wr_pit[CDL2_SUBLIST_D0_NUM_WR_PIT];
cdl2_wr_pit_t		cdl2_sublist_D1_wr_pit[CDL2_SUBLIST_D1_NUM_WR_PIT];
cdl2_wr_pit_t		cdl2_sublist_D2_wr_pit[CDL2_SUBLIST_D2_NUM_WR_PIT];
cdl2_wr_pit_t		cdl2_sublist_D3_wr_pit[CDL2_SUBLIST_D3_NUM_WR_PIT];
cdl2_wr_pit_t		cdl2_sublist_F916_wr_pit[CDL2_SUBLIST_F916_NUM_WR_PIT];


/* Define the CDL queued receive parameter storage block area based on the 
   number of blocks defined by the application. 
   Define a constant variable to hold the number of blocks.
   */
const unsigned_16	cdl2_num_qrpsb = CDL2_NUM_QRPSB;
cdl2_queued_parm_t	cdl2_queued_rx_parm[(CDL2_NUM_QRPSB)];

/* Standard broadcast message table */
const unsigned_16 cdl2_spb_msg_max = CDL2_SPB_MSG_MAX;
cdl2_spb_tx_msg_t cdl2_spb_tx_msg[CDL2_SPB_MSG_MAX];

/* Group broadcast message table */
const unsigned_16 cdl2_pgb_msg_max = CDL2_PGB_MSG_MAX;
cdl2_pgb_tx_msg_t cdl2_pgb_tx_msg[CDL2_PGB_MSG_MAX];

/* Memory allocations for the cdl2_transmit function fifo */
const unsigned_16 cdl2_transmit_buf_size = CDL2_TRANSMIT_BUF_SIZE;
cdl2_transmit_fifo_t cdl2_transmit_fifo_buffer[CDL2_TRANSMIT_BUF_SIZE];

/**************************************************************************/
/* Memory allocation for CBS MID table */
cdl2_cbs_mid_entry_t  cdl2_cbs_control_mid_tbl[CDL2_CBS_MAX_NUM_ECM];
const unsigned_16     cdl2_cbs_max_num_ecm = CDL2_CBS_MAX_NUM_ECM;


/* Memory allocation for PGB reftag table */
cdl2_pgb_process_reftag_entry_t  cdl2_pgb_process_reftag_table[CDL2_PGB_MAX_NUM_REFTAG];
const unsigned_16     cdl2_pgb_max_num_reftag = CDL2_PGB_MAX_NUM_REFTAG;


/* Memory allocation for PGB parameter table */
cdl2_pgb_process_parm_entry_t    cdl2_pgb_process_parm_table[CDL2_PGB_MAX_NUM_REQ_PARM];
const unsigned_16     cdl2_pgb_max_num_req_parm = CDL2_PGB_MAX_NUM_REQ_PARM;


/* Memory allocation for ADT reftag table */
cdl2_adt_process_reftag_entry_t cdl2_adt_process_reftag_table[CDL2_ADT_MAX_NUM_REQ_PARM];
const unsigned_16               cdl2_adt_max_num_req_parm = CDL2_ADT_MAX_NUM_REQ_PARM;


/* Memory allocation for ADT requestor table */
cdl2_adt_status_mid_entry_t cdl2_adt_status_ecm_request_table[CDL2_ADT_MAX_NUM_REQUESTOR];
const unsigned_16           cdl2_adt_max_num_requestor = CDL2_ADT_MAX_NUM_REQUESTOR;


/* Memory allocation for ADT requestor data table */
cdl2_adt_status_data_entry_t  cdl2_adt_status_data_table[CDL2_ADT_MAX_NUM_DATA_STATUS];
const unsigned_16             cdl2_adt_max_num_data_status = CDL2_ADT_MAX_NUM_DATA_STATUS;


/* Memory allocation for ADT requestor data reference managment */
cdl2_adt_status_ref_entry_t cdl2_adt_status_ref_table[CDL2_ADT_MAX_NUM_REF_ENTRIES];
cdl2_adt_status_used_ref_t  cdl2_adt_status_used_ref_table[CDL2_ADT_MAX_NUM_REF_ENTRIES];
const unsigned_16           cdl2_adt_max_num_ref_entries = CDL2_ADT_MAX_NUM_REF_ENTRIES;


/* Memory allocation for ADT requestor data report que */
cdl2_adt_status_report_entry_t cdl2_adt_status_report_buffer[CDL2_ADT_MAX_NUM_REPORT_ENTRIES];
const unsigned_16              cdl2_adt_max_num_report_entries = CDL2_ADT_MAX_NUM_REPORT_ENTRIES;


/* Memory allocation for Read Poll request que */
cdl2_cbs_read_poll_entry_t cdl2_cbs_read_poll_buffer[CDL2_CBS_MAX_READ_POLL_ENTRIES];
const unsigned_16          cdl2_cbs_max_read_poll_entries = CDL2_CBS_MAX_READ_POLL_ENTRIES;


/* Memory allocation for INF request queue */
const int com_inf_input_que_size = COM_INF_INPUT_QUE_SIZE;
com_inf_input_request_t com_inf_input_fifo_buffer[COM_INF_INPUT_QUE_SIZE];


/* cdl2 cbs oel config */
#if 0
const cdl2_cbs_oel_config_t app_cdl2_cbs_oel_config = 
                CDL2_CBS_OEL_CONFIG(&cdl2_cbs_control_task_id,
                                    CDL2_CBS_TIME_EXPIRE_EVENT,
                                    CDL2_CBS_FIFO_INPUT_EVENT);
#endif
  