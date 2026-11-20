/******************************************************************************************************************
 Copyright 2012-2016 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: scl_adt_j1939_alloc.h

Description: This file contains the ADT J1939 allocation types internal for library

Change History:
         16-Mar-2012 - Initial Draft version - Thirumalaiselvan Kannan
		 02-May-2014 - Changes for the functionality Termiate all on power up and for the FIFO issue and for the 
					   Issue for more number of groups
******************************************************************************************************************/
#ifndef SCL_ADT_J1939_ALLOC_H_
#define SCL_ADT_J1939_ALLOC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <scl_adt_j1939.h>

/* Maximum data of the ADT message */
#define SCL_ADT_J1939_DATA_MAX_SIZE      5
/* Default Server group FIFO size */
#define SCL_ADT_J1939_DEFAULT_SRV_GRP_FIFO  6


/* Base structure for ADT J1939 Link */
typedef struct scl_adt_j1939_link_s
{
   /* This holds the number of virtual ecms has adt j1939 */
   oel_u_sllist_t ecms;
   /* Double linked list for free available adt j1939 server group objects */
   oel_u_dl_list_t free_server_groups;
   /* Double linked list for free available adt j1939 client group objects */
   oel_u_dl_list_t free_client_groups;
   /* Double linked list for free available adt j1939 server objects */
   oel_u_dl_list_t free_servers;
   /* Double linked list for free available adt j1939 client objects */
   oel_u_dl_list_t free_clients;
   /* J1939 link handle */
   scl_j1939_link_t link;
   /* This is minimum time period to check for any change/update for ADT CDL PID J1939 at library level
      User can update this through API */ 
   oel_second_u32_l20_t pid_data_check_period;
   /*Minimum period to send data report*/
   oel_second_u32_l20_t pid_data_update_period;
   /* This attribute indicates the number of times library has to retry before notifying time out 
     event */
   uint_least8_t timeout_event_retry_cnt;
   
}scl_adt_j1939_link_t;

/* Structure for ADT J1939 ECM which has the list of connected clients and server for the particular ECM Link */
typedef struct scl_adt_j1939_ecm_s
{
   /* Base object */
   oel_u_sllelmnt_t base;
   /* Double linked list to store the registered adt j1939 client objects */
   oel_u_dl_list_t clients;
   /* Double linked list to store the registered adt j1939 server objects */
   oel_u_dl_list_t servers;
   /* Virtual ECM index number for this object */
   int_least8_t ecm_index;   
}scl_adt_j1939_ecm_t;

/* Different Server state of the ADT J1939 link */
enum scl_adt_j1939_server_state_e
{
   /* ADT J1939 server is in active, sending data report state */
   SCL_ADT_J1939_SERVER_ACTIVE,
   /* ADT J1939 server is in receiving request state */
   SCL_ADT_J1939_SERVER_RX_RQST,
   /* ADT J1939 server is in transmitting the response state */
   SCL_ADT_J1939_SERVER_TX_RESPONSE,
   /* ADT J1939 server is in closed state where no communication occurs */
   SCL_ADT_J1939_SERVER_CLOSED
};
/* This is to store the enum value of different server states */
typedef uint_least8_t scl_adt_j1939_server_state_t;

/* Enum for different data report states in the ADT  */
enum scl_adt_j1939_server_data_report_state_s
{
   /* Data report is in IDLE state */
   SCL_ADT_J1939_SERVER_DR_STATE_IDLE,
   /* Data report has been sent and waiting for the acknowledgement from the client */
   SCL_ADT_J1939_SERVER_DR_STATE_SENT
};
typedef uint_least8_t scl_adt_j1939_server_data_report_state_t; 


/* Structure to store the ADT group message in the fifo */
typedef struct scl_adt_j1939_server_grp_msg_s
{
   uint_least8_t data[SCL_ADT_J1939_DATA_MAX_SIZE];
   uint_least8_t group_id;
   uint_least8_t sequence_number_and_overflow;
}scl_adt_j1939_server_grp_msg_t;

/* Structure for ADT J1939 server connection */
typedef struct scl_adt_j1939_server_s
{
   /* Base object */
   oel_u_dl_element_t base;
   /* This is to store the number of overflows occured during the server data report */
   uint_least32_t num_overflows;
   /* This is to store the address of the remote ECM/client ECM*/
   uint_least8_t remote_addr;
   /* This attribute has the counter for number of retries happened for the ADT request  */
   uint_least8_t retry_count;
   /* This attribute has the server data report state */
   scl_adt_j1939_server_data_report_state_t data_report_state;
   /* This attribute is used to identify the DM13 message reception */   
   bool_least_t stop_bcast_received;
   /* This is to store the index of the requested server group*/
   uint_least16_t requested_server_group;
   /* This stores the current server state */
   scl_adt_j1939_server_state_t state;
   /* Double linked list to store the different group request for the server */
   oel_u_dl_list_t server_groups;
   /* This fifo will have the data report message to be transmitted */
   oel_u_fifo_t server_grp_message_fifo;
   /* This is used to store the time of last check happened for the ADT to check any change in data */
   uint_least32_t pid_data_check_tick_cnt;
   /* This is the tick count to track the minimum update period as per the ADT J1939 protocol spec */
   uint_least32_t min_update_period_tick_count;
   /* This has the tick count when the server object has last updated it state*/ 
   uint_least32_t tick_count; 
   /* This is used to store the last ADT data message which has not transmitted in th enetwork for retries */
   scl_adt_j1939_server_grp_msg_t send_grp;
}scl_adt_j1939_server_t;

/******************************************************************************************************************
Function name: scl_adt_j1939_server_grp_tx_pid_hdlr_t

Description: This interface provides a means for the library to read the data to be transmitted from the 
             application.  It follows the format for cdl2_tx_hdlr_t, so that an application can use one function 
             for both the scl_adt_j1939 and cdl2 libraries.

Parameter Description: void *context: This parameter points to the context data that has been setup in the tx pid 
                       configuration.
                       
                       uint_least8_t *data: This parameter points to the buffer to be
                       filled in by this handler.

Return Description:  int_least16_t - The data size of the parameter to be transmitted.
******************************************************************************************************************/
typedef int_least16_t (scl_adt_j1939_server_grp_tx_pid_hdlr_t)( void* context, uint_least8_t* data );

/* 
 This class provides the configuration for an ADT PID over J1939 at server side
*/
typedef struct scl_adt_j1939_server_grp_pid_config_s
{
   /* This attribute points to the context pointer that will be passed to the function when obtaining the data. */
   void* context;
   /* This attribute has the previous value */
   uint_least32_t last_data_value;
   /* This attribute is the PID that will be transmitted. */
   uint_least32_t pid;
   /* This attribute points to the function that will be used to obtain the data to be transmitted */
   scl_adt_j1939_server_grp_tx_pid_hdlr_t *tx_hdlr;
}scl_adt_j1939_server_grp_pid_config_t;


/* Structure for ADT J1939 server group */
typedef struct scl_adt_j1939_server_grp_s
{
   /* Base element object */
   oel_u_dl_element_t base;
   /* configuration structure for ADT PID over J1939 at server side */
   scl_adt_j1939_server_grp_pid_config_t group_array[SCL_ADT_J1939_DATA_MAX_SIZE];
   /* This attribute has the running sequence number for the ADT J1939 data message */
   uint_least8_t sequence_number;
   /* This attribute has the number of pids requested for ADT J1939*/
   uint_least8_t num_of_pids;
   /* This attribute has the group identification number for the ADT J1939 data message */
   uint_least8_t group_id;   
   /* This attribute indicates whether the group currently has a message outbound to the client. */
   bool_least_t outbound;
   /* This attribute has the  time where the last ADT data message has sent */
   uint_least32_t last_sent_tick_cnt;
}scl_adt_j1939_server_grp_t;

/* Different ADT client connection state */
enum scl_adt_j1939_client_state_e
{
   /*ADT Client at Terminate all State*/
   SCL_ADT_J1939_CLIENT_TERM_ALL_RQST,
   /*ADT Client at Terminate all Requested State*/
   SCL_ADT_J1939_CLIENT_TERM_ALL_RESPONSE,
   /* ADT Client at Initilization state  */
   SCL_ADT_J1939_CLIENT_INIT,
   /* ADT Client at feature request state  */
   SCL_ADT_J1939_CLIENT_FEATURE_REQUEST,
   /* ADT Client at waiting state  */
   SCL_ADT_J1939_CLIENT_WAIT,
   /* ADT Client at active/data report receiving state  */
   SCL_ADT_J1939_CLIENT_ACTIVE,
   /* ADT Client at terminated or closed state  */
   SCL_ADT_J1939_CLIENT_CLOSED 
};
typedef uint_least8_t scl_adt_j1939_client_state_t;


/* Different ADT client group connection state */
enum scl_adt_j1939_client_grp_state_e
{   
   /* Client Group in Init state */
   SCL_ADT_J1939_CLIENT_GRP_INIT,
   /* Client Group in the Transmit request state */
   SCL_ADT_J1939_CLIENT_GRP_TX_RQST,
   /* Client Group has completed the request state */
   SCL_ADT_J1939_CLIENT_GRP_REQUESTED,
   /* Client Group in the Waiting state */
   SCL_ADT_J1939_CLIENT_GRP_WAIT,
   /* Client Group in the active rx data state */
   SCL_ADT_J1939_CLIENT_GRP_ACTIVE,
   /* Client Group in the removal state */
   SCL_ADT_J1939_CLIENT_GRP_REMOVE,
   /* Client Group in the stop broadcast state */
   SCL_ADT_J1939_CLIENT_GRP_STOP_BCAST,
   /* Client Group in the Inactive state */  
    SCL_ADT_J1939_CLIENT_GRP_INACTIVE
};
typedef uint_least8_t scl_adt_j1939_client_grp_state_t;

/* Structure for the client group with diagnostic */
typedef struct scl_adt_j1939_client_grp_struct_s
{
   /* This attribute points to a client pid configuration. */
   const scl_adt_j1939_client_grp_pid_config_t *client_grp_pid_config;
   /* This attribute points to a diagnostic context pointer to be used by the client
      PID in the event of a timeout or not available status. */
   void *diag_context;
} scl_adt_j1939_client_grp_struct_t;

/* Structure for the client group  */
typedef struct scl_adt_j1939_client_grp_s
{
   /* Base object for the client group */
   oel_u_dl_element_t base;
   /* This attribute has the event callback application function */
   scl_adt_j1939_event_clbk_t* event_clbk;
   /* This attribute has the context data for the callback function */
   void* event_context;
    /* This attribute has the array of group data, hdlr and pid info*/
   scl_adt_j1939_client_grp_struct_t group_array[SCL_ADT_J1939_DATA_MAX_SIZE];
   /* This attribute has the boolean to select DM13 support */
   bool_least_t dm13_support;
   /* This attribute has the number of pids in the group */
   uint_least8_t num_of_pids;
    /* This attribute has the group id number */
   uint_least8_t group_id;
    /* This attribute has the sequenc number of the current group data */
   uint_least8_t sequence_number;
    /* This attribute has the retry counter for the client request message*/
   uint_least8_t client_grp_req_retry_cnt;
    /* This attribute has the current state of the client */
   scl_adt_j1939_client_grp_state_t state;
    /* This attribute has the current tick count of the client */
   uint_least32_t tick_cnt;   
}scl_adt_j1939_client_grp_t;

/* Structure for ADT J1939 client */
typedef struct scl_adt_j1939_client_s
{
   /* Base client object element */
   oel_u_dl_element_t base;
   /* Double linked list for the client group objects*/
   oel_u_dl_list_t client_groups;
   /* This attribute has the address of the remote node  */
   uint_least8_t remote_addr;
   /* This attribute has the current state of the client object */
   scl_adt_j1939_client_state_t state;
   /* This attribute has the address of the remote node  */
   scl_adt_j1939_client_grp_t *requested_client_grp;
   /* This attribute has the current tick count for checking the timeouts  */
   uint_least32_t tick_cnt;
   /* This attribute has the current requested ECM instance  */
   scl_adt_j1939_ecm_t *requested_ecm;
   /* This attribute has the application callback for notifying the group removal */
   scl_adt_j1939_remove_grp_notify_t* remove_grp_notify; 
   /* This attribute has the application callback argument */
   void* remove_grp_notify_context;  
   /* This attribute has the retry counter for the client feature request message*/
   uint_least8_t client_feat_req_retry_cnt;
   /*This attribute has the retry counter for terminate all feature of client*/
   uint_least8_t term_all_retry_count;
}scl_adt_j1939_client_t;


#ifdef __cplusplus
}
#endif
#endif /* #ifndef SCL_ADT_J1939_ALLOC_H_ */
