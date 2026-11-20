/******************************************************************************************************************
 Copyright (C) Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: csf_eth_health_config.c

Description:  Ethernet Health static allocations and static constant configuration.
              Applications have to build this file
******************************************************************************************************************/
#include <csf_eth_health_alloc.h>
#include <csf_eth_health_tune.h>

/*Maximum number of links supported.*/
const uint_least8_t csf_eth_health_max_link_count = CSF_ETH_HEALTH_MAX_LINK_COUNT;

/*Maximum number of servers supported. */
const uint_least8_t csf_eth_health_max_client_count = CSF_ETH_HEALTH_MAX_CLIENT_COUNT;

/*Maximum number of SPLs supported.*/
const uint_least8_t csf_eth_health_max_peer_count = CSF_ETH_HEALTH_MAX_PEER_COUNT;

/*Maximum number of links  supported.  Usually it should be single link*/
csf_eth_health_link_t csf_eth_health_link[CSF_ETH_HEALTH_MAX_LINK_COUNT];

/*This allocates maximum number of Client supported.*/
csf_eth_health_client_t csf_eth_health_client[CSF_ETH_HEALTH_MAX_CLIENT_COUNT];

/*This allocates maximum number of peers supported.*/
csf_eth_health_peer_t csf_eth_health_peer[CSF_ETH_HEALTH_MAX_PEER_COUNT];

/*This allocates maximum number of persistent peers supported.*/
csf_eth_health_peer_persistent_t csf_eth_health_persistent_peer[CSF_ETH_HEALTH_MAX_PEER_COUNT];

#ifdef CSF_ETH_HEALTH_MAX_PGT_PARAM_COUNT
/*Maximum number of session supported.*/
const uint_least16_t csf_eth_health_max_pgt_param_count = CSF_ETH_HEALTH_MAX_PGT_PARAM_COUNT;

/*This allocates maximum number of parameter supported.*/
csf_eth_health_pgt_param_t csf_eth_health_pgt_param[CSF_ETH_HEALTH_MAX_PGT_PARAM_COUNT];
#else
/*Maximum number of session supported.*/
const uint_least16_t csf_eth_health_max_pgt_param_count = 0;

/*This allocates maximum number of parameter supported.*/
csf_eth_health_pgt_param_t csf_eth_health_pgt_param[1];
#endif

#ifdef CSF_ETH_HEALTH_MAX_PARAM_PER_SPL
/*This allocates maximum number of PARAM supported for all groups of all sessions.*/
csf_eth_health_pgt_param_t* csf_eth_health_pgt_param_context[CSF_ETH_HEALTH_MAX_PARAM_PER_SPL];
#else
csf_eth_health_pgt_param_t* csf_eth_health_pgt_param_context[1];
#endif

#ifdef CSF_ETH_HEALTH_MAX_EXT_PARAM
/*Maximum number of External params supported.*/
const uint_least8_t csf_eth_health_max_ext_param_count = CSF_ETH_HEALTH_MAX_EXT_PARAM;

/*This allocates maximum number of External Parameters  supported by ethernet health.*/
csf_eth_ext_param_t csf_eth_health_ext_param_list[CSF_ETH_HEALTH_MAX_EXT_PARAM];
#else
/*Maximum number of External params supported.*/
const uint_least8_t csf_eth_health_max_ext_param_count = 0;

/*This allocates maximum number of External Parameters  supported by ethernet health.*/
csf_eth_ext_param_t csf_eth_health_ext_param_list[1];
#endif

#ifdef CSF_ETH_HEALTH_MAX_EXT_PARAM_LIST
/*Maximum number of list of External params supported.*/
const uint_least8_t csf_eth_health_max_ext_param_list_count = CSF_ETH_HEALTH_MAX_EXT_PARAM_LIST;

/*This allocates maximum number of list of External Parameters  supported by ethernet health.*/
csf_eth_ext_params_list_t csf_eth_health_ext_params_list[CSF_ETH_HEALTH_MAX_EXT_PARAM_LIST];
#else
/*Maximum number of list of External params supported.*/
const uint_least8_t csf_eth_health_max_ext_param_list_count = 0;

/*This allocates maximum number of list of External Parameters  supported by ethernet health.*/
csf_eth_ext_params_list_t csf_eth_health_ext_params_list[1];
#endif

#ifdef CSF_ETH_HEALTH_MAX_APFGPC_LIST
/*Maximum number of GPC params supported.*/
const uint_least8_t csf_eth_health_gpc_param_list_count = CSF_ETH_HEALTH_MAX_APFGPC_LIST;

/*This allocates maximum number of GPC Parameters  supported by ethernet health.*/
csf_eth_health_gpc_t  csf_eth_health_gpc_list[CSF_ETH_HEALTH_MAX_APFGPC_LIST];
#else
/*Maximum number of GPC params supported.*/
const uint_least8_t csf_eth_health_gpc_param_list_count = 0;

/*This allocates maximum number of GPC Parameters  supported by ethernet health.*/
csf_eth_health_gpc_t  csf_eth_health_gpc_list[1];
#endif
