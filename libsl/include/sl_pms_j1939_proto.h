#ifndef SL_PMS_J1939_PROTO_H_
#define SL_PMS_J1939_PROTO_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains prototypes needed for the Simulink Programmable Monitoring
System (PMS) interface to the service tool for J1939.

FILE NAME : sl_pms_j1939_proto.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <sl_pms_types.h>
#include <scl_j1939.h>
#include <sl_pms_j1939_types.h>
/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/

void sl_pms_j1939_tx_F05A_ppgnA_hdlr (
  scl_j1939_mbuf_hdr_t *mbuf_msg,    /* Pointer to message received over J1939 datalink. */
  sl_pms_j1939_tx_ppgnA_config_t *me );  /* Pointer to config structure for PMS protocol. */
  
void sl_pms_j1939_tx_F05B_ppgnA_hdlr (
  scl_j1939_mbuf_hdr_t *mbuf_msg,   /* Pointer to message received over J1939 datalink. */
  sl_pms_j1939_tx_ppgnA_config_t *me ); /* Pointer to config structure for PMS protocol. */
  
void sl_pms_j1939_tx_F05C_ppgnA_hdlr (
  scl_j1939_mbuf_hdr_t *mbuf_msg,    /* Pointer to message received over J1939 datalink. */
  sl_pms_j1939_tx_ppgnA_config_t *me ); /* Pointer to config structure for PMS protocol. */
  
void sl_pms_j1939_tx_F05D_ppgnA_hdlr (
  scl_j1939_mbuf_hdr_t *mbuf_msg,    /* Pointer to message received over J1939 datalink. */
  sl_pms_j1939_tx_ppgnA_config_t *me );  /* Pointer to config structure for PMS protocol. */
  
sl_pms_j1939_tx_ppgnA_client_t * sl_pms_j1939_get_client (
  sl_pms_j1939_tx_ppgnA_config_t *me,          /* Pointer to config structure for PMS protocol. */
  uint8_t                  src_address,  /* Source address of client. */
  uint8_t                  add_client    /* non-zero to add a new client to list */
  );
  
#endif /* SL_PMS_J1939_PROTO_H_ */
