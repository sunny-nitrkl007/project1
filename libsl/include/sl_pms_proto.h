#ifndef SL_PMS_PROTO_H_
#define SL_PMS_PROTO_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains public prototypes for the pms system.

FILE NAME : sl_pms_proto.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>
#include <sl_pms_types.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/

/******************************************************************************
** -- Function Prototypes --
******************************************************************************/
void sl_pms_init(sl_pms_config_t *pms_config);

bool_least_t sl_pms_add_event(sl_pms_config_t *pms_config,
                           	  const sl_pms_event_config_t *new_event_config);

bool_least_t sl_pms_remove_event(sl_pms_config_t *pms_config,
                           	  const sl_pms_event_config_t *new_event_config);

bool_least_t sl_pms_nvm_level_read(const sl_pms_event_config_t *pms_event_config,
                                   uint_least16_t level_idx,
                                   sl_pms_nvm_level_t *level);


/******************************************************************************
** -- Data Declarations --
******************************************************************************/


#endif /* SL_PMS_PROTO_H_ */

