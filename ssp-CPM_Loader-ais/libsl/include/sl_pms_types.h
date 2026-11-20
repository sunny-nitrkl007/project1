#ifndef SL_PMS_TYPES_H_
#define SL_PMS_TYPES_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains datatypes needed for the Simulink Programmable Monitoring
System (PMS) interface to the service tool.

FILE NAME : sl_pms_types.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>
#include <nvm_struct.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
typedef uint_least16_t sl_pms_debounce_seconds_t;
typedef struct sl_pms_level_config_s * sl_pms_event_link_t;

typedef struct
{
	/* These pointers keep track of the beginning(head)
	 * and end(tail) of the linked list of PMS configs
	 */
	sl_pms_event_link_t head;
	sl_pms_event_link_t tail;
} sl_pms_event_list_t;


typedef enum {
	SL_PMS_MODE_OFF = 0,
	SL_PMS_MODE_ON = 1,
	SL_PMS_MODE_ALWAYS_ON = 2
} sl_pms_mode_t;

typedef struct
{
   uint_least8_t writable       : 1;
   uint_least8_t security_level : 7;
} sl_pms_access_code_t;


/* NVM Data */
typedef struct {
	uint_least8_t  mode;
	uint_least16_t trip_point;
	uint_least16_t debounce_time;
} sl_pms_nvm_level_t;


/* Config Data */

/* This structure defines the values needed to configure the delay
 *   - value - The default value used for the debounce time (sec)
 *   - min_limit - The minimum value that the debounce time can be (sec)
 *   - max_limit - The maximum value that the debounce time can be (sec)
 */
typedef struct {
   uint_least16_t min_limit; /* max limit for active debounce time */
   uint_least16_t value;     /* debounce time to activate event  */
   uint_least16_t max_limit; /* min limit for active debounce time */
} sl_pms_delay_t;

/* This structure defines the values needed to configure the trip point
 *   - value - The default value used for the trip point
 *             (units depend on packet_id)
 *   - min_limit - The minimum value that the trip point can be
 *                 (units depend on packet_id)
 *   - max_limit - The maximum value that the trip point be
 *                 (units depend on packet_id)
 */
typedef struct {
   uint_least16_t min_limit; /* max limit for trip point value */
   uint_least16_t value;     /* trip point value */
   uint_least16_t max_limit; /* min limit for trip point value */

} sl_pms_trip_point_t;

/* This structure defines the values required for a specific level.
 * A separate instance of this structure is required for each level of a event.
 *   - action_id - Specifies the action_id (Warning Category Indicator) for this
 *                 level
 *   - trip point - Specifies the trip point parameters for this level
 *   - debounce time - Specifies the amount of time to debounce (sec) before
 *                     activating diagnostic
 *   - mode - Specifies the initial mode for this level:
 *            - On:        Action monitor is initially on but can be turned off
 *                         by service tool.
 *            - Off:       Action monitor is initially off but can be turned on
 *                         by service tool.
 *            - Always On: Action monitor is initially on and cannot be turned
 *                         off by service tool.
 *   - Security Level: Specifies the Security Level required to modify any
 *                     aspect of the level.
 */
typedef struct sl_pms_level_config_s
{
	uint_least8_t					action_id;
	sl_pms_trip_point_t		trip_point;
	sl_pms_delay_t      	debounce_time;
	sl_pms_mode_t					mode;
	uint_least8_t					security_level;
}
sl_pms_level_config_t;


/* This structure defines the workspace for a specific event.
 *   - *next - Pointer to the next event configuration.  This is used to
 *             provide a linked list configurations so that a particular
 *             event configuration can be found in the entire list.  The
 *             list is linked together in sl_pms_cdl_submit_event().
 *   - *nvm_event_data - Pointer to the data for this event in nvm.  This
 *                       is populated at initialization to allow faster
 *                       finding of the nvm event data at run-time.
 */
typedef struct
{
	sl_pms_event_link_t		previous;
	sl_pms_event_link_t		next;
	uint_least8_t					*nvm_event_data;
} sl_pms_event_work_t;


/* This structure defines the values required for a specific event.
 * A separate instance of this structure is required for each event.
 *   - packet_id - The identifier for this event.
 *   - instance_id - Indicates unique instance identifier for this
 *                   event.  Allows multiple configurations of the
 *                   same packet to occur.
 *   - num_levels - The number of levels defined by this event.
 *   - is_signed - Specifies if the trip_point data for this packet
 *                 contains signed data.
 *   - disable_irqs - Specifies if interrupts should be disabled while
 *                    read/writing to nvm levels for this event.
 *   - *level - Array of level configurations.  Number of level
 *               configurations must match that specified by
 *               num_levels above.
 *   - *work - Pointer to the workspace for this configuration;
 */
typedef struct
{
	uint_least16_t				packet_id;
	uint_least8_t					instance_id;
	uint_least8_t					num_levels;
	bool_least_t					is_signed;
	bool_least_t					disable_irqs;
	sl_pms_level_config_t	*level;
	sl_pms_event_work_t		*work;
} sl_pms_event_config_t;


typedef struct
{
	uint_least16_t				active_packet_id;
	uint_least16_t				active_action_id;
	bool_least_t					one_free_program;
	uint_least8_t					num_submitted_events;
	NVM_block_handle_t 		nvm_block_handle;
	sl_pms_event_list_t		event_list;
} sl_pms_work_t;


/* This structure defines common values required for the pms system.
 *   - free_program_time free configurable time (1hr/bit)
 *   - *nvm_table        Pointer to the nvm table containing all data
 *                       to be saved in non-volatile memory.
 *   - *work             Pointer to the pms work structure.
 */
typedef const struct
{
	uint_least8_t					num_events;
	uint_least8_t					num_levels;
	uint_least8_t					free_program_time;
	uint_least8_t					*nvm_data;
	uint_least32_t				nvm_block_id;
	sl_pms_work_t					*work;
} sl_pms_config_t;


/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/


#endif /* SL_PMS_TYPES_H_ */

