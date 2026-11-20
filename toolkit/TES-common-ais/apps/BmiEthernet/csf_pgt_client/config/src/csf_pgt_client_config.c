/******************************************************************************************************************
 Copyright 2018 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: csf_pgt_client_config.c

Description:  PGT client  static allocations and static constant configuration. 
              Applications have to build this file 
******************************************************************************************************************/

#include <csf_pgt_client.h>
#include <csf_pgt_client_alloc.h>
#include <csf_pgt_client_tune.h>

/*Maximum number of clients supported.*/
const uint_least8_t csf_pgt_max_client_count = CSF_PGT_MAX_CLIENT_COUNT;

/*Maximum number of servers supported. */
const uint_least8_t csf_pgt_client_max_server_count = CSF_PGT_CLIENT_MAX_SERVER_COUNT;

/*Maximum number of SPLs supported.*/
const uint_least8_t csf_pgt_client_max_spl_count = CSF_PGT_CLIENT_MAX_SPL_COUNT;

/*Maximum number of session supported.*/
const uint_least8_t csf_pgt_client_max_session_count = CSF_PGT_CLIENT_MAX_SESSION_COUNT;

/*Maximum number of groups supported for all session*/
const uint_least16_t csf_pgt_client_max_grp_count = CSF_PGT_CLIENT_MAX_GRP_COUNT;

/*Maximum number of params supported for all groups of all sessions.*/
const uint_least16_t csf_pgt_client_max_param_count = CSF_PGT_CLIENT_MAX_PARAM_COUNT;

/*This allocates maximum number of clients supported.*/
csf_pgt_client_t csf_pgt_client_array[CSF_PGT_MAX_CLIENT_COUNT];

/*Maximum number of servers supported.*/
csf_pgt_client_server_t csf_pgt_server_array[CSF_PGT_CLIENT_MAX_SERVER_COUNT];

/*This allocates maximum number of SPL supported.*/
csf_pgt_client_spl_t csf_pgt_client_spl_array[CSF_PGT_CLIENT_MAX_SPL_COUNT];

/*This allocates maximum number of session supported.*/
csf_pgt_client_session_t csf_pgt_client_session_array[CSF_PGT_CLIENT_MAX_SESSION_COUNT];

/*This allocates maximum number of groups supported.*/
csf_pgt_client_grp_t csf_pgt_client_grp_array[CSF_PGT_CLIENT_MAX_GRP_COUNT];

/*This allocates maximum number of parameters supported for all groups of all sessions.*/
csf_pgt_client_param_entry_t csf_pgt_client_grp_param_config_array[CSF_PGT_CLIENT_MAX_PARAM_COUNT];

/* UDP data buffer length - Need to be assigned in tune.h based on application requiremnt*/
uint_least16_t csf_pgt_client_max_grp_udp_rx_bytes = CSF_PGT_CLIENT_MAX_GRP_UDP_RX_BYTES;

/* Buffer to receive UDP data - User configurable length */
uint_least8_t csf_pgt_client_grp_rx_buf[CSF_PGT_CLIENT_MAX_GRP_UDP_RX_BYTES];
