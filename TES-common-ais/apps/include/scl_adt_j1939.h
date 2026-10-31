/******************************************************************************************************************
 Copyright 2012-2014 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: scl_adt_j1939.h

Description: This file contains the J1939 ADT feature public APIs, types and macros.

Change History:
         16-Mar-2012 - Initial Draft version - Thirumalaiselvan Kannan
		 02-May-2014 - Changes for the functionality Termiate all on power up and for the FIFO issue and for the 
					   Issue for more number of groups
******************************************************************************************************************/
#ifndef SCL_ADT_J1939_H_
#define SCL_ADT_J1939_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <oel_u_fifo.h>
#include <scl_j1939.h>
#include <std_t.h>
#include <oel_u_sllist.h>
#include <oel_u_sllelmnt.h>
#include <oel_u_dl_list.h>

/* This define indicates an invalid handle value in the scl_adt_j1939 library */
#define SCL_ADT_J1939_INVALID_HANDLE  UINT_LEAST16_MAX

/* Different Error handling for scl_error.h */
#define SCL_ADT_J1939_LINK_INIT_ERR             0x01
#define SCL_ADT_J1939_ECM_RX_SERVER_CTRL_ERR    0x02
#define SCL_ADT_J1939_LINK_STOP_BCAST_ERR       0x03
#define SCL_ADT_J1939_ECM_RX_RESPONSE_ERR       0x04
#define SCL_ADT_J1939_LINK_ADD_GROUP_ERR        0x05
#define SCL_ADT_J1939_CLIENT_GRP_UPDATE_ERR     0x06
#define SCL_ADT_J1939_FEATURE_CLBK_ERR          0x07
#define SCL_ADT_J1939_LINK_RX_SERVER_CTRL_ERR   0x08
#define SCL_ADT_J1939_CLIENT_GRP_ADD_GROUP_ERR  0x09
#define SCL_ADT_J1939_LINK_RX_REQUEST_ERR       0x10
#define SCL_ADT_J1939_SERVER_GRP_UPDATE_ERR     0x11
#define SCL_ADT_J1939_SERVER_TXREQ_RESPONSE_ERR 0x12
#define SCL_ADT_J1939_LINK_RX_RESPONSE_ERR      0x13
#define SCL_ADT_J1939_LINK_RX_DATA_REPORT_ERR   0x14
#define SCL_ADT_J1939_LINK_RX_DATA_REPORT_ACK_ERR 0x15
#define SCL_ADT_J1939_SERVER_UPDATE_ERR         0x16

/* Invalid GRoup id for the ADT J1939 protocol 0 to 0xFA is the valid group id*/
#define SCL_ADT_J1939_INVALID_GROUP_ID   0xFF


/* This type is for the scl_adt_j1939_link handle. */
typedef uint_least16_t scl_adt_j1939_link_handle_t;

/* This enum type defines the different event occurs during the data receive at the ADT client  */
enum scl_adt_j1939_event_s
{
   SCL_ADT_J1939_EVENT_PID_INVALID_SEQUENCE = 0,
   SCL_ADT_J1939_EVENT_PID_TIMEOUT,
   SCL_ADT_J1939_EVENT_PID_NA,
   SCL_ADT_J1939_EVENT_PID_RXED,
   SCL_ADT_J1939_EVENT_PID_OVERFLOW,
   SCL_ADT_J1939_EVENT_INVALID_REQUEST,
   SCL_ADT_J1939_EVENT_UNKOWN_ERROR,
   SCL_ADT_J1939_EVENT_NO_DATA_BUFFERS,
   SCL_ADT_J1939_EVENT_PID_TOO_LONG,
   SCL_ADT_J1939_EVENT_TP_NOT_AVAIL,
   SCL_ADT_J1939_EVENT_GRP_CONFIG_RETRY_FAILS   
};
typedef uint_least8_t scl_adt_j1939_event_t; 


/******************************************************************************************************************
Function name: scl_adt_j1939_client_grp_pid_hdlr_t

Description:  This interface provides a means for the library to write the received data to the application.  
             It follows the format for cdl2_rx_data_hdlr_t, so that an application can use one function for both 
             the scl_adt_j1939 and cdl2 libraries.

Parameter Description:  uint_least8_t *data: This parameter points to the buffer containing the received data.
                        
                        uint_least8_t data_len: This parameter contains the size of the buffer.
                        
                        void *grp_pid_hdlr_context: This parameter points to the context data that has been setup 
                        in the group pid configuration.
                        
                        uint_least16_t dsi_code: This parameter contains any DSI code that is received

Return Description:  int_least16_t
******************************************************************************************************************/
typedef int_least16_t (scl_adt_j1939_client_grp_pid_hdlr_t)
(
   uint_least8_t* data,
   uint_least8_t data_len,
   void* grp_pid_hdlr_context,
   uint_least16_t dsi_code
);

/* This typedef describes a table of diagnostic context pointers to be used in the event of a timeout or not 
available event at the client side pid.  This table has a one to one correspondence to the rx_pid table parameter
and contains unique diagnostic information for each PID.  This table will be passed in when adding client groups.
*/
typedef void* scl_adt_j1939_diag_contxt_tbl_t;

/* These defintions are the flags to be used by the Client pid configuration. */
#define SCL_ADT_J1939_RX_PID_DSI_AVAIL    0x01
#define SCL_ADT_J1939_RX_PID_DSI_NA       0x00
#define SCL_ADT_J1939_RX_PID_SWAP_DATA    0x02
#define SCL_ADT_J1939_RX_PID_NO_SWAP      0x00
#define SCL_ADT_J1939_RX_PID_SIGNED       0x04
#define SCL_ADT_J1939_RX_PID_UNSIGNED     0x00

/*
 This class provides the configuration for  an ADT PID over J1939 at client side.
*/
typedef struct scl_adt_j1939_client_grp_pid_config_s
{
   /* This attribute is the PID that will be received. */
   uint_least32_t pid;
   /* This attributes points to the function that be used to give the data to the application. */
   scl_adt_j1939_client_grp_pid_hdlr_t *rx_hndlr;
   /* This attribute points to the context data that will be passed to the rxhdlr when this PID has been received*/
   void* context;
   /* This attribute contains the size of the data to be received. */
   uint_least8_t data_size;
   /* This attribute indicates additional attributes for this PID. */
   uint_least8_t flags;
   
}scl_adt_j1939_client_grp_pid_config_t;


/******************************************************************************************************************
Function name: scl_adt_j1939_event_clbk_t

Description: This interface provides notification of a not available or timeout or overflow event for a rx PID

Parameter Description:  void *event_context: This parameter is a context pointer that will be passed to this 
                       function when an event occurs.
                       
                       void *diag_context: This parameter is a context pointer specific to the rx pid used for 
                       diagnostic purposes.
                       
                       const scl_pgb_j1939_rx_pid_config_t *rx_pid_config: This parameter points to the rx pid 
                       configuration used to identify which pid timed out.
                       
                       scl_j1939_link_t: The scl_j1939 link that the timeout occured on.
                       
                       int_least8_t ecm_idx: The virtual ecm who failed to receive a  message.
                       
                       uint_least8_t remote_addr: The remote address who failed to transmit  a message.
                       
                       scl_pgb_j1939_event_t: This parameter indicates the event that occured that triggered the 
                       callback.
                       
Return Description: void
******************************************************************************************************************/
typedef void (scl_adt_j1939_event_clbk_t)
(
   void* event_context,
   void* diagnostic_context, 
   const scl_adt_j1939_client_grp_pid_config_t* client_grp_pid_config,
   scl_j1939_link_t link,
   int_least8_t ecm_idx, 
   uint_least8_t remote_addr,
   scl_adt_j1939_event_t event
);

/* This typedef redefines a pointer to a client group pid configuration entry. */
typedef scl_adt_j1939_client_grp_pid_config_t* scl_adt_j1939_client_grp_pid_config_ptr_t;

/* This Enum defines the different DSI values for the ADT */
enum scl_adt_j1939_dsi_e 
{
   SCL_ADT_J1939_DSI_NOT_USED0 = 0,
   SCL_ADT_J1939_DSI_NOT_USED1,
   SCL_ADT_J1939_DSI_INTERMITTENT,
   SCL_ADT_J1939_DSI_SHORTED_HIGH,
   SCL_ADT_J1939_DSI_SHORTED_LOW,
   SCL_ADT_J1939_DSI_LOW_AMPS_OPEN,
   SCL_ADT_J1939_DSI_HI_AMPS_GROUNDED,
   SCL_ADT_J1939_DSI_NOT_USED7,
   SCL_ADT_J1939_DSI_OUT_OF_RANGE,
   SCL_ADT_J1939_DSI_ABNORMAL_UPDATE,
   SCL_ADT_J1939_DSI_NOT_USED10,
   SCL_ADT_J1939_DSI_UNKNOWN_FAILURE_MODE,
   SCL_ADT_J1939_DSI_BAD_DEVICE,
   SCL_ADT_J1939_DSI_OUT_OF_CAL,
   SCL_ADT_J1939_DSI_NOT_USED14,
   SCL_ADT_J1939_DSI_NOT_USED15,
   SCL_ADT_J1939_DSI_PARAM_NOT_AVAIL,
   SCL_ADT_J1939_DSI_NO_RESPONSE,
   SCL_ADT_J1939_DSI_SNSR_SUPPLY_FAULT,
   SCL_ADT_J1939_DSI_CONDITIONS_NOT_MET,
   SCL_ADT_J1939_DSI_DISABLED_NOT_INSTALLED
};
typedef uint_least16_t scl_adt_j1939_dsi_t;




/* These defintions are the base values used for assigning DSI values. */
#define SCL_ADT_J1939_U8_DSI_BASE_VALUE              0xE0
#define SCL_ADT_J1939_I8_DSI_BASE_VALUE              0x80
#define SCL_ADT_J1939_U16_DSI_BASE_VALUE           0xFFE0
#define SCL_ADT_J1939_I16_DSI_BASE_VALUE           0x8000
#define SCL_ADT_J1939_U32_DSI_BASE_VALUE       0xFFFFFFE0
#define SCL_ADT_J1939_I32_DSI_BASE_VALUE       0x80000000



/******************************************************************************************************************
Function name: scl_adt_j1939_link_init

Description: This function will allocate and initialize a single scl_adt_j1939_link class.Only one class should be 
             created and initialized per J1939 link.  This function will install a service in scl_j1939 so the 
             update function will automatically be called in the scl_j1939 periodic function.
             
             Note: This function must be called at initialization after J1939 and DM13 initialization

Parameter Description: scl_j1939_link_t link: The scl_j1939 link that this instantiation of scl_adt_j1939_link
                       will be operating on.

Return Description: The scl_adt_j1939_link_handle_t is an handle for scl_adt_j1939_link created instance.
******************************************************************************************************************/
extern scl_adt_j1939_link_handle_t scl_adt_j1939_link_init
(
   scl_j1939_link_t link
);

/******************************************************************************************************************
Function name:scl_adt_j1939_link_add_ecm 

Description: This operation will add a single virtual ecm to the scl_adt_j1939_link class.  The scl_adt_j1939_link 
             must already have been created and initialized with enough virtual ECMs configured to support this 
             ECM being added.
             Note: Once an ecm has been added, it can NOT be removed.  This function must be called at 
             initialization or in the same task that J1939 runs in after scl_adt_j1939_link_init.

Parameter Description: scl_adt_j1939_link_handle_t: This parameter points to the scl_adt_j1939_link handle.
                       uint_least8_t ecm_idx: The virtual ecm index to add

Return Description: bool_t : This function returns TRUE if the PID was successfully  added, otherwise FALSE
******************************************************************************************************************/
extern bool_t scl_adt_j1939_link_add_ecm
(
   scl_adt_j1939_link_handle_t adt_j1939_hndl,
   uint_least8_t ecm_idx
);

/******************************************************************************************************************
Function name: scl_adt_j1939_link_add_group

Description:  This operation will add a group of pointer to PIDs that can be received. The groups will be formed 
              in order, so an application should optimally pack the PIDs before submitting them.  If there are not 
              enough rx groups configured, then this function will create as many as possible before returning FALSE.
              
              Note: This function must be called at initialization or in the same task that J1939 runs in.

Parameter Description: scl_adt_j1939_link_handle_t: This parameter points to the scl_adt_j1939_link handle.
                       
                       int_least8_t ecm_idx: This paremeter is the scl_j1939 virtual ecm index number in which the
                        receive PID group will be added to.
                       
                       uint_least8_t remote_addr: This parameter is the remote address that the PIDs will be 
                       received from.
                       
                       uint_least16_t num_of_pids: This parameter is the number of PIDs listed in the following 
                       table.
                       
                       bool_t dm13_support: This parameter says TRUE or FALSE for DM13 support
                       
                       const scl_adt_j1939_client_grp_pid_config_ptr_t* client_grp_pid_configs: This parameter
                       points to a group of PIDs to be received.
                       
                       scl_adt_j1939_diag_contxt_tbl_t *diag_context_ptrs: This parameter points to a table of void
                       pointers to be used by the diagnostic functions handling timeouts and not available PIDs 
                       for rx PIDs. This table has a one to one correspondence to the rx_pid table parameter and 
                       contains unique diagnostic information for each PID.
                       
                       scl_adt_j1939_event_clbk_t *event_clbk: This parameter is a pointer to a function that will 
                       handle events for a rx PID.  This will generally be used by the J1939 health library.
                       
                       void *event_callback_context: This parameter is a pointer to a context pointer to be used 
                       by the event callback function.
                       
Return Description: uint_least8_t  This function returns group id if the groups were successfully
                                   added, otherwise 0xFF.
******************************************************************************************************************/
extern uint_least8_t scl_adt_j1939_link_add_group
(
   scl_adt_j1939_link_handle_t adt_j1939_hndl,
   uint_least8_t ecm_idx, 
   uint_least8_t remote_addr, 
   uint_least8_t num_of_pids, 
   bool_least_t dm13_support, 
   const scl_adt_j1939_client_grp_pid_config_ptr_t* client_grp_pid_configs,
   scl_adt_j1939_diag_contxt_tbl_t *diag_context_ptrs,
   scl_adt_j1939_event_clbk_t* event_callback, 
   void* event_callback_context
);

/******************************************************************************************************************
Function name: scl_adt_j1939_remove_grp_notify_t

Description: This operation is a function callback that will be used to notify the user when the groups have been 
             removed

Parameter Description: scl_adt_j1939_link_handle_t adt_hndl: This parameter points to the scl_adt_j1939_link handle 
                                              
                       scl_j1939_link_t link: This parameter is the scl_j1939 link number in which the receive PID
                       groups were removed from.
                       
                       int_least8_t ecm_idx: This parameter is the scl_j1939 virtual ecm index number of the client
                       in which the receive PID groups were removed from.
                       
                       uint_least8_t remote_addr: This parameter is the remote address of the server that the PIDs
                       were received from.
                       
                       void *rm_rx_grp_notify_context:  This parameter is a data context pointer for the remove 
                       group notification function.

Return Description: void
******************************************************************************************************************/
typedef void (scl_adt_j1939_remove_grp_notify_t)
(
   scl_adt_j1939_link_handle_t adt_hndlr,
   scl_j1939_link_t link,
   int_least8_t ecm_idx,
   uint_least8_t remote_addr,
   void *remove_grp_notify_context
);

/******************************************************************************************************************
Function name: scl_adt_j1939_link_remove_group

Description: This operation will remove the groups that are set to be received for the given virtual ecm from the 
             remote addr.  The notification function will be called when the group was successfully  removed.
             Note: This function must be called at initialization or in the same task that J1939 runs in.

Parameter Description: scl_adt_j1939_link_handle_t: This parameter points to the scl_adt_j1939_link handle.
                       
                       int_least8_t ecm_idx: This paremeter is the scl_j1939 virtual ecm index number in which the
                       rx PID groups will be removed from.
                       
                       uint_least8_t remote_addr: This parameter represents the remote address whose PIDs are 
                       being received that will be removed.
                       
                       uint_least8_t grp_ref_id: This is the reference ID of the group to be removed
                       
                       scl_adt_j1939_remove_grp_notify_t* remove_grp_notify: This parameter is a function 
                       callback to notify the user when the group  have been removed.
                       
                       void* remove_grp_notify_context: This parameter is a data context pointer to be used with 
                       the remove group notification function.

Return Description: bool_t: This function will return TRUE if this function was successful otherwise FALSE
******************************************************************************************************************/
extern bool_t scl_adt_j1939_link_remove_group
(
   scl_adt_j1939_link_handle_t adt_j1939_hndl,
   uint_least8_t ecm_idx, 
   uint_least8_t remote_addr, 
   uint_least8_t group_id,
   scl_adt_j1939_remove_grp_notify_t* remove_grp_notify, 
   void* remove_grp_notify_context
);
/******************************************************************************************************************
Function name: scl_adt_j1939_set_pid_data_check_period

Description: This function will set the time for the ADT J1939 library data check period.

Parameter Description: scl_adt_j1939_link_handle_t adt_handle:  ADT J1939 handle where ADT J1939 supposed to run
                      oel_second_u32_l20_t period: Period in millisecond (Use the follwing macro to 
					  OEL_RTOS_SECONDS_DBL_TO_U32_L20 to configure period for this unit i.e if you want to configure for 100ms
					  it should be like OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.100))   
                      This Function should be called  after calling the scl_adt_j1939_link_init()

Return Description: TRUE if success else FALSE on failure
******************************************************************************************************************/
extern bool_t scl_adt_j1939_set_pid_data_check_period
(
   scl_adt_j1939_link_handle_t adt_handle,
   oel_second_u32_l20_t period
);

/******************************************************************************************************************
Function name: scl_adt_j1939_set_pid_data_update_period

Description: This function will set the time for the ADT J1939 library data update period.

Parameter Description: scl_adt_j1939_link_handle_t adt_handle:  ADT J1939 handle where ADT J1939 supposed to run
                      oel_second_u32_l20_t period: Period in millisecond (Use the follwing macro  
					  OEL_RTOS_SECONDS_DBL_TO_U32_L20 to configure period for this unit i.e if you want to configure for 100ms
					  it should be like OEL_RTOS_SECONDS_DBL_TO_U32_L20(0.100))   
Return Description: TRUE if success else FALSE on failure
Note:  This Function should be called  after calling the scl_adt_j1939_link_init()
******************************************************************************************************************/
extern bool_t scl_adt_j1939_set_pid_data_update_period
(
   scl_adt_j1939_link_handle_t adt_handle,
   oel_second_u32_l20_t period
);
/******************************************************************************************************************
Function name: scl_adt_j1939_set_retry_count

Description: This function will set the retry count for terminate all operation.

Parameter Description:  uint_least8_t retry_count : Timeout retry count
						scl_adt_j1939_link_handle_t adt_handle :ADT J1939 handle where ADT J1939 supposed to run  						
Return Description:  bool_t : TRUE if success else FALSE on failure

Condition: This function has to be called during initialization and after initializing scl j1939 adt link
******************************************************************************************************************/
extern bool_t scl_adt_j1939_set_retry_count
(
   scl_adt_j1939_link_handle_t adt_handle,
   uint_least8_t retry_count
);
#ifdef __cplusplus
}
#endif
#endif /* #ifndef SCL_ADT_J1939_H_ */
