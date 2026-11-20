/*******************************************************************************
Copyright 2015 Caterpillar Inc.  All rights reserved.
--------------------------------------------------------------------------------
File name:  csf_eth_health_tune.h

Description:
The application will copy this file and adjust the health #defines to meet
their needs
*******************************************************************************/
#ifndef CSF_ETH_HEALTH_TUNE_H_
#define CSF_ETH_HEALTH_TUNE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Maximum number of links  , In most of cases there will be only one link.
   Link will allow to differentiate between VLANs or physical links.*/
#define  CSF_ETH_HEALTH_MAX_LINK_COUNT        1

/* Maximum number of clients , usually there will be one client per link. It must be at least one   */
#define  CSF_ETH_HEALTH_MAX_CLIENT_COUNT      10

/* Maximum number of peers  */
#define  CSF_ETH_HEALTH_MAX_PEER_COUNT        15

/*Maximum number of parameters per SPL( Server parameter list) , update this value
if you are using PGT feature it must be at least 1,else the value of this Macro will be zero.  */
#define  CSF_ETH_HEALTH_MAX_PARAM_PER_SPL     50

/* Maximum number of  PGT parameter monitored by Ethernet health */
#define  CSF_ETH_HEALTH_MAX_PGT_PARAM_COUNT   70

/* Maximum number of  External parameter added to Ethernet health library,  */
#define  CSF_ETH_HEALTH_MAX_EXT_PARAM        4

/* Maximum number of list of External parameters added to Ethernet health library,  */
#define  CSF_ETH_HEALTH_MAX_EXT_PARAM_LIST   4

/* Maximum number of GPC parameters added to Ethernet health library,  */
#define  CSF_ETH_HEALTH_MAX_APFGPC_LIST      4

#ifdef __cplusplus
}
#endif
#endif /* CSF_ETH_HEALTH_TUNE_H_ */
