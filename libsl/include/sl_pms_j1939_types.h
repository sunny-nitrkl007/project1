#ifndef SL_PMS_J1939_TYPES_H_
#define SL_PMS_J1939_TYPES_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains types needed for the Simulink Programmable Monitoring
System (PMS) interface to the service tool for J1939.

FILE NAME : sl_pms_types.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <sl_pms_types.h>
/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
typedef struct
{
  uint8_t                  * msg_buf;                               /* Pointer to buffer for datalink message. */
  sl_pms_event_config_t       * pms_event_config;
  uint16_t                   curr_select_packetID;                   /* Current selected packet ID. */
  uint8_t                    client_address;                         /* Source address of client. */

} sl_pms_j1939_tx_ppgnA_client_t;

typedef struct
{
  uint8_t                  num_clients;        /* Number of clients that are in the client list. */

} sl_pms_j1939_tx_ppgnA_work_t;

typedef struct
{
  sl_pms_j1939_tx_ppgnA_work_t   *work;              /* Pointer to common work structure. */
  sl_pms_j1939_tx_ppgnA_client_t *client_data;       /* Pointer to array of client data (client work structures). */
  sl_pms_config_t             *pms_global_config; /* Pointer to Global Configuration structure for PMS. */
  uint8_t                  max_num_clients;    /* Max number of source addresses that can access PMS protocol. */
  uint8_t                  msg_buf_size;       /* Size of buffer for datalink message (All client buffers are the same size). */

} sl_pms_j1939_tx_ppgnA_config_t;

#endif /* SL_PMS_J1939_TYPES_H_ */
