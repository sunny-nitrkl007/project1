/*******************************************************************************
** COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
** CATERPILLAR: CONFIDENTIAL YELLOW
--------------------------------------------------------------------------------
FILE NAME: dig_timer.h
DESCRIPTION: Public interface for the dig_timer module
*******************************************************************************/

#ifndef __DIG_TIMER_H__
#define __DIG_TIMER_H__

#if defined (__cplusplus)
extern "C"
{
#endif

/*******************************************************************************
** -- #Include's --
*******************************************************************************/

#include <std_t.h>
#include <pcs_public.h>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

typedef uint32_t dig_timer_milliseconds_u32_t;

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

/******************************************************************************
FUNCTION NAME: dig_timer_init
DESCRIPTION: Initializes the dig timer module
PARAMETER DESCRIPTION: n/a
RETURN VALUE: n/a
*******************************************************************************/
void dig_timer_init(void);

/******************************************************************************
FUNCTION NAME: dig_timer_20ms_update
DESCRIPTION: Periodic update wrapper for dig_timer module call at 20ms
PARAMETER DESCRIPTION: pcs_dig_state_t - as defined in pcs
RETURN VALUE: n/a
*******************************************************************************/
void dig_timer_update(pcs_dig_state_t dig_state);

/******************************************************************************
FUNCTION NAME: dig_timer_20ms_update
DESCRIPTION: Periodic update wrapper for dig_timer module call at 20ms
PARAMETER DESCRIPTION: pcs_dig_state_t - as defined in pcs
RETURN VALUE: n/a
*******************************************************************************/
void dig_timer_20ms_update(pcs_dig_state_t dig_state);

/******************************************************************************
FUNCTION NAME: dig_timer_get_current
DESCRIPTION: Gets the dig timer value in milliseconds for the last completed dig
PARAMETER DESCRIPTION: 0 - dsi (not available)
                       non-zero - dig timer value in milliseconds of the last
                                  dig completed.
RETURN VALUE:
*******************************************************************************/
dig_timer_milliseconds_u32_t dig_timer_get_current(void);

/******************************************************************************
FUNCTION NAME: dig_timer_set_target
DESCRIPTION: Sets the target dig time in milliseconds
PARAMETER DESCRIPTION: target dig time in milliseconds
RETURN VALUE:
*******************************************************************************/
void dig_timer_set_target(dig_timer_milliseconds_u32_t target_ms);

/******************************************************************************
FUNCTION NAME: dig_timer_get_target
DESCRIPTION: Gets the target dig time in milliseconds
PARAMETER DESCRIPTION: n/a
RETURN VALUE: target dig time in milliseconds
*******************************************************************************/
dig_timer_milliseconds_u32_t dig_timer_get_target(void);

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/

#if defined (__cplusplus)
}
#endif

#endif /* __CPM_DIG_TIMER_H__ */
