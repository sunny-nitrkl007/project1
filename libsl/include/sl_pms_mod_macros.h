#ifndef SL_PMS_MOD_MACROS_H_
#define SL_PMS_MOD_MACROS_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains internal private macros needed for the pms system.

FILE NAME : sl_pms_mod_macros.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>
#include <sl_pms_types.h>
#include <sl_pms_macros.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/

/* Swap bytes of a 2byte value */
#define ROL(src, dst) {                                     				  \
   memcpy((dst), (src)+1, 1);                               				  \
   memcpy((dst)+1, (src), 1); }


/* Get the value of an element in the PMS NVM datatbase */
#define SL_PMS_GET_NVM_VAL(nvm_base, offset, dt) \
	*( (dt *) &(nvm_base)[(offset)])





/*******************************************************************************
 * Base Data Macros
 ******************************************************************************/
/* Location of data w/in base */
#define SL_PMS_NUM_EVENTS_OFFSET ( 0 )

#define SL_PMS_NUM_LEVELS_OFFSET ( SL_PMS_NUM_EVENTS_OFFSET + \
                                    sizeof(uint_least8_t) )

#define SL_PMS_TATTLETALE_OFFSET ( SL_PMS_NUM_LEVELS_OFFSET + \
                                   sizeof(uint_least8_t) )

#define SL_PMS_NO_ONE_FREE_PROGRAM_OFFSET ( SL_PMS_TATTLETALE_OFFSET + \
                                            sizeof(uint_least8_t) )

#define SL_PMS_CHECKSUM_OFFSET ( SL_PMS_NO_ONE_FREE_PROGRAM_OFFSET + \
                                 sizeof(uint_least8_t) )

#if defined(__arm) && defined(__TARGET_ARCH_4T)
/* Insert word alignment padding for MAC71XX ARM processor targets */
#define SL_PMS_EVENT_OFFSET(event_num, num_levels) ( SL_PMS_CHECKSUM_OFFSET + \
                                                     sizeof(uint_least8_t) + \
                                                     sizeof(uint_least8_t) + \
                                                     (event_num)* \
                                                     SL_PMS_EVENT_SIZE(num_levels) )
#else
#define SL_PMS_EVENT_OFFSET(event_num, num_levels) ( SL_PMS_CHECKSUM_OFFSET + \
                                                     sizeof(uint_least8_t) + \
                                                     (event_num)* \
                                                     SL_PMS_EVENT_SIZE(num_levels) )
#endif

/* Access to data w/in base */
#define SL_PMS_NUM_EVENTS(nvm_data) \
	SL_PMS_GET_NVM_VAL((nvm_data), SL_PMS_NUM_EVENTS_OFFSET, uint_least8_t)

#define SL_PMS_NUM_LEVELS(nvm_data) \
	SL_PMS_GET_NVM_VAL((nvm_data), SL_PMS_NUM_LEVELS_OFFSET, uint_least8_t)

#define SL_PMS_TATTLETALE(nvm_data) \
	SL_PMS_GET_NVM_VAL((nvm_data), SL_PMS_TATTLETALE_OFFSET, uint_least8_t)

#define SL_PMS_NO_ONE_FREE_PROGRAM(nvm_data) \
	SL_PMS_GET_NVM_VAL((nvm_data), SL_PMS_NO_ONE_FREE_PROGRAM_OFFSET, uint_least8_t)

#define SL_PMS_CHECKSUM(nvm_data) \
	SL_PMS_GET_NVM_VAL((nvm_data), SL_PMS_CHECKSUM_OFFSET, uint_least8_t)





/*******************************************************************************
 * Event Data Macros
 ******************************************************************************/
/* Location of data w/in event */
#define SL_PMS_EVENT_PACKET_ID_OFFSET ( 0 )

#define SL_PMS_EVENT_INSTANCE_ID_OFFSET ( sizeof(uint_least16_t)  )

#if defined(__arm) && defined(__TARGET_ARCH_4T)
#define SL_PMS_EVENT_LEVEL_OFFSET(level_idx) \
	( SL_PMS_EVENT_INSTANCE_ID_OFFSET + sizeof(uint_least8_t) + \
	  (level_idx)*SL_PMS_LEVEL_SIZE )
#else
#define SL_PMS_EVENT_LEVEL_OFFSET(level_idx) \
	( SL_PMS_EVENT_INSTANCE_ID_OFFSET + sizeof(uint_least16_t) + \
	  (level_idx)*SL_PMS_LEVEL_SIZE )
#endif

#define SL_PMS_EVENT_CHECKSUM_OFFSET(num_levels) \
	( SL_PMS_EVENT_LEVEL_OFFSET(num_levels) )


/* Access to data w/in event */
#define SL_PMS_EVENT_PACKET_ID(nvm_packet_data) \
	SL_PMS_GET_NVM_VAL((nvm_packet_data), SL_PMS_EVENT_PACKET_ID_OFFSET, \
	                   uint_least16_t)

#define SL_PMS_EVENT_INSTANCE_ID(nvm_packet_data) \
	SL_PMS_GET_NVM_VAL((nvm_packet_data), SL_PMS_EVENT_INSTANCE_ID_OFFSET, \
	                    uint_least8_t)

#define SL_PMS_EVENT_LEVEL(nvm_packet_data, level_idx) \
	SL_PMS_GET_NVM_VAL((nvm_packet_data), \
	                   SL_PMS_EVENT_LEVEL_OFFSET((level_idx), uint_least8_t)

#define SL_PMS_EVENT_CHECKSUM(nvm_packet_data, level_idx) \
	SL_PMS_GET_NVM_VAL((nvm_packet_data), \
	                    SL_PMS_EVENT_CHECKSUM_OFFSET(level_idx), uint_least8_t)



/*******************************************************************************
 * Level Data Macros
 ******************************************************************************/
/* Location of data w/in level */
#define SL_PMS_LEVEL_MODE_OFFSET(level_idx) \
	( SL_PMS_EVENT_LEVEL_OFFSET(level_idx) )

#define SL_PMS_LEVEL_TRIPPOINT_OFFSET(level_idx) \
	( SL_PMS_LEVEL_MODE_OFFSET(level_idx) + sizeof(uint_least8_t) )

#define SL_PMS_LEVEL_DEBOUNCE_OFFSET(level_idx) \
	( SL_PMS_LEVEL_TRIPPOINT_OFFSET(level_idx) + sizeof(uint_least16_t) )

#define SL_PMS_LEVEL_TATTLETALE_OFFSET(level_idx) \
	( SL_PMS_LEVEL_DEBOUNCE_OFFSET(level_idx) + sizeof(uint_least16_t) )


/* Access to data w/in level */
#define SL_PMS_LEVEL_MODE(nvm_event_data, level_idx) \
	SL_PMS_GET_NVM_VAL((nvm_event_data), \
					   SL_PMS_LEVEL_MODE_OFFSET(level_idx), uint_least8_t)

#define SL_PMS_LEVEL_TRIPPOINT(nvm_event_data, level_idx) \
	SL_PMS_GET_NVM_VAL((nvm_event_data), \
					   SL_PMS_LEVEL_TRIPPOINT_OFFSET(level_idx), uint_least16_t)

#define SL_PMS_LEVEL_DEBOUNCE(nvm_event_data, level_idx) \
	SL_PMS_GET_NVM_VAL((nvm_event_data), \
					   SL_PMS_LEVEL_DEBOUNCE_OFFSET(level_idx), uint_least16_t)

#define SL_PMS_LEVEL_TATTLETALE(nvm_event_data, level_idx) \
	SL_PMS_GET_NVM_VAL((nvm_event_data), \
					   SL_PMS_LEVEL_TATTLETALE_OFFSET(level_idx),uint_least8_t)



/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/


#endif /* SL_PMS_MOD_MACROS_H_ */
