#ifndef SL_PMS_MOD_PROTO_H_
#define SL_PMS_MOD_PROTO_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains internal private prototypes for the pms system.

FILE NAME : sl_pms_mod_proto.h

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
sl_pms_event_config_t *sl_pms_event_config_get(sl_pms_config_t *pms_config,
                                               uint_least16_t packet_id);

bool_least_t sl_pms_level_setup_authenticity_check(const sl_pms_event_config_t *pms_event_config,
                                                   uint_least16_t action_id,
                                                   uint_least16_t level_idx);

bool_least_t sl_pms_level_setup_modifiable_check(sl_pms_config_t *pms_config,
	                                               const sl_pms_event_config_t *pms_event_config,
	                                               uint_least16_t level_idx);

sl_pms_access_code_t sl_pms_level_access_code_get(sl_pms_config_t *pms_config,
	                                                const sl_pms_event_config_t *pms_event_config,
	                                                uint_least16_t level_idx);

bool_least_t sl_pms_nvm_event_check_read(sl_pms_config_t *pms_config,
                                         uint_least16_t packet_id,
                                         uint_least8_t instance_id,
                                         uint_least8_t **nvm_event_data);

uint_least8_t sl_pms_nvm_event_checksum(sl_pms_config_t *pms_config,
                                        uint_least8_t *nvm_event_data);

bool_least_t sl_pms_nvm_level_write(sl_pms_config_t *pms_config,
						            const sl_pms_event_config_t *pms_event_config,
                                    uint_least16_t action_id,
                                    uint_least8_t mode,
                                    uint_least16_t trip_point,
                                    uint_least16_t debounce_time);


/******************************************************************************
** -- Data Declarations --
******************************************************************************/


#endif /* SL_PMS_MOD_PROTO_H_ */
