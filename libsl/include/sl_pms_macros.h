#ifndef SL_PMS_MACROS_H_
#define SL_PMS_MACROS_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains public macros needed for the pms system.

FILE NAME : sl_pms_macros.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>
#include <sl_pms_types.h>


/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/




/*
 * NVM Data Layout
 * 	If the checksum changes for an individual event, then only that event's
 *  data is invalidated.  If the overall checksum changes (this checksum is
 *  only based on the num_events, num_levels, tattletale, and one_free_program),
 *  then all events are invalidated and all current data is lost (default
 *  values are used).
 *
 *  Normally, the maximum number of levels for an event shouldn't change
 *  because it is based on the Programmable Monitoring System definition.
 *  However, if it does change (detected by the differnce between value in
 *  configuration and value in nvm) all events are invalidated and all current
 *  data is lost.
 *
 *  Use of the maximum number of levels instead of the actual number of levels
 *  in the nvm data layout was done so that if an individual event was
 *  invalidated, all subsequent events would not have to be invalidated.  This
 *  can be done because all event entries are the same size (because the number
 *  of levels is the same for each event); thus, if an event becomes
 *  invalidated, we still know where the next event starts.
 *
 *  Notes:
 *    - no_one_free_program: This was named as is instead of 'one_free_program'
 *                           because we are making use of the fact that when
 *                           nvm gets invalidated it will be set to all 0's.
 *                           Thus, on first startup after flash, or if the
 *                           entire nvm becomes invalidated causing the nvm
 *                           table to be wiped, no_one_free_program program will
 *                           be set to 0, (and by the law of double negatives)
 *                           the one_free_program will be allowed.
 * -----------------------------------------------------------------------------
 * 	- num_events 				(uint_least8_t)--------------- Start of NVM data
 * 	- num_levels 				(uint_least8_t)
 * 	- tattletale  				(uint_least8_t)
 *  - no_one_free_program  		(uint_least8_t)
 *  - checksum					(uint_least8_t)
 *  - word align pad            (uint_least8_t)---- Preserve word alignment on MAC71XX CPU
 *  	- packet_id				(uint_least16_t)-------------- Start Event #1
 *    - instance_id				(uint_least8_t)
 *  		- mode				(uint_least8_t)--------------- Start Level #1
 *  		- trip_point		(uint_least16_t)
 *  		- debounce_time		(uint_least16_t)
 *  		- tattletale		(uint_least8_t)
 *  		- mode				(uint_least8_t)--------------- Start Level #2
 *  		- trip_point		(uint_least16_t)
 *  		- debounce_time		(uint_least16_t)
 *  		- tattletale		(uint_least8_t)
 *  		- mode				(uint_least8_t)--------------- Start Level #3
 *  		- trip_point		(uint_least16_t)
 *  		- debounce_time		(uint_least16_t)
 *  		- tattletale		(uint_least8_t)
 *  		- mode				(uint_least8_t)--------------- Start Level #4
 *  		- trip_point		(uint_least16_t)
 *  		- debounce_time		(uint_least16_t)
 *  		- tattletale		(uint_least8_t)
 *  	- checksum				(uint_least8_t)
 *  	...
 *  	...
 *  	...
 *  	- packet_id				(uint_least16_t)-------------- Start Event #N
 *    - instance_id				(uint_least8_t)
 *  		- mode				(uint_least8_t)--------------- Start Level #1
 *  		- trip_point		(uint_least16_t)
 *  		- debounce_time		(uint_least16_t)
 *  		- tattletale		(uint_least8_t)
 *  		- mode				(uint_least8_t)--------------- Start Level #2
 *  		- trip_point		(uint_least16_t)
 *  		- debounce_time		(uint_least16_t)
 *  		- tattletale		(uint_least8_t)
 *  		- mode				(uint_least8_t)--------------- Start Level #3
 *  		- trip_point		(uint_least16_t)
 *  		- debounce_time		(uint_least16_t)
 *  		- tattletale		(uint_least8_t)
 *  		- mode				(uint_least8_t)--------------- Start Level #4
 *  		- trip_point		(uint_least16_t)
 *  		- debounce_time		(uint_least16_t)
 *  		- tattletale		(uint_least8_t)
 *  	- checksum				(uint_least8_t)
 */



/*******************************************************************************
 * Size Macros
 ******************************************************************************/
/* The following macros allow determination of the size of:
 *   - Each level
 *   - Each event
 *   - Entire NVM table
 */
#define SL_PMS_LEVEL_SIZE ( sizeof(uint_least8_t) + sizeof(uint_least16_t) + \
                            sizeof(uint_least16_t) + sizeof(uint_least8_t) )

#if defined(__arm) && defined(__TARGET_ARCH_4T)
#define SL_PMS_EVENT_SIZE(num_levels) ( sizeof(uint_least16_t) + \
                                        sizeof(uint_least8_t) + \
									    (num_levels)*(SL_PMS_LEVEL_SIZE) + \
                                        sizeof(uint_least8_t) )

#define SL_PMS_NVM_SIZE(num_events, num_levels) ( sizeof(uint_least8_t) + \
                                                  sizeof(uint_least8_t) + \
                                                  sizeof(uint_least8_t) + \
                                                  sizeof(uint_least8_t) + \
                                                  sizeof(uint_least8_t) + \
                                                  sizeof(uint_least8_t) + \
                                                  num_events*SL_PMS_EVENT_SIZE(num_levels) )
#else
#define SL_PMS_EVENT_SIZE(num_levels) ( sizeof(uint_least16_t) + \
                                        sizeof(uint_least16_t) + \
									    (num_levels)*(SL_PMS_LEVEL_SIZE) + \
                                        sizeof(uint_least8_t) )

#define SL_PMS_NVM_SIZE(num_events, num_levels) ( sizeof(uint_least8_t) + \
                                                  sizeof(uint_least8_t) + \
                                                  sizeof(uint_least8_t) + \
                                                  sizeof(uint_least8_t) + \
                                                  sizeof(uint_least8_t) + \
                                                  num_events*SL_PMS_EVENT_SIZE(num_levels) )
#endif


/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/


#endif /* SL_PMS_MACROS_H_ */
