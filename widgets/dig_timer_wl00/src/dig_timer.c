/*******************************************************************************
** COPYRIGHT (C) 2000-2021 CATERPILLAR INC. ALL RIGHTS RESERVED.
** CATERPILLAR: CONFIDENTIAL YELLOW
--------------------------------------------------------------------------------
FILE NAME: dig_timer.c
DESCRIPTION: Implementation for all dig_timer interfaces
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <oel_timestamp.h>
#include "dig_timer_private.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

#define DIG_TIMER_TARGET_PERIOD_MS 120

static void dig_timer_start(void);
static void dig_timer_stop(void);

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/

/* dig timer of an in-progress dig cycle in milliseconds */
static dig_timer_milliseconds_u32_t current_dig_time_msecs=0;

/* dig timer of the most recent completed dig cycle in milliseconds */
static dig_timer_milliseconds_u32_t prev_dig_time_msecs=0;

/* dig time target required by the app in milliseconds. This could be used  */
static dig_timer_milliseconds_u32_t target_dig_time_msecs=0;

/* initilize dig state to not digging */
static pcs_dig_state_t prev_dig_state = PCS_NOT_DIGGING;

/* used to capture start time of dig */
static oel_timestamp64_t dig_timer_begin_timestamp;

/******************************************************************************
FUNCTION NAME: dig_timer_init
DESCRIPTION: Initializes the dig timer module
PARAMETER DESCRIPTION: n/a
RETURN VALUE: n/a
*******************************************************************************/
void dig_timer_init(void)
{
	current_dig_time_msecs=0;
	prev_dig_time_msecs=0;
	target_dig_time_msecs=0;
	prev_dig_state = PCS_NOT_DIGGING;
}

/******************************************************************************
FUNCTION NAME: dig_timer_start
DESCRIPTION: Captures current wall time in milliseconds
PARAMETER DESCRIPTION: n/a
RETURN VALUE: n/a
*******************************************************************************/
static void dig_timer_start(void)
{
	dig_timer_begin_timestamp = oel_timestamp_get64();
}

/******************************************************************************
FUNCTION NAME: dig_timer_stop
DESCRIPTION: Captures the time difference from dig_timer_start to
             dig_timer_stop
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
static void dig_timer_stop(void)
{
	uint64_t elapsed;
	elapsed = (oel_timestamp_get64() - dig_timer_begin_timestamp);

	/* elapsed time in milliseconds ( ticks divide by freq in milliseconds) */
	current_dig_time_msecs = (uint32_t)(elapsed / (oel_timestamp_get_freq()/1000));
}

/******************************************************************************
FUNCTION NAME: dig_timer_20ms_update
DESCRIPTION: Periodic update wrapper for dig_timer module call at 20ms
PARAMETER DESCRIPTION: pcs_dig_state_t - as defined in pcs
RETURN VALUE: n/a
*******************************************************************************/
void dig_timer_20ms_update(pcs_dig_state_t dig_state)
{
	static uint8_t counter=DIG_TIMER_TARGET_PERIOD_MS;
	if (DIG_TIMER_TARGET_PERIOD_MS == counter)
	{
		dig_timer_update(dig_state);

		/* reset counter */
		counter = 0;
	}

	/* increment the counter */
	counter+=20;
}
/******************************************************************************
FUNCTION NAME: dig_timer_update
DESCRIPTION: Periodic update for dig_timer module, recommended call at 120ms
PARAMETER DESCRIPTION: pcs_dig_state_t - as defined in pcs
RETURN VALUE: n/a
*******************************************************************************/
void dig_timer_update(pcs_dig_state_t dig_state)
{
    if (prev_dig_state == PCS_NOT_DIGGING)
    {
        if (dig_state == PCS_TENTATIVE_DIGGING)
        {
            /* start new timer */
            dig_timer_start();
        }
        else if (dig_state == PCS_DIGGING)
        {
            /* reset dig timer value */
            prev_dig_time_msecs = 0;

            /* start new timer */
            dig_timer_start();
        }
        else
        {
            /* no change to dig state, do nothing */
        }
    }
    else if (prev_dig_state == PCS_TENTATIVE_DIGGING)
    {
        if (dig_state == PCS_DIGGING)
        {
            /* reset dig timer value */
            prev_dig_time_msecs = 0;
        }
        else if (dig_state == PCS_NOT_DIGGING)
        {
            /* stop timer */
            dig_timer_stop();

            /* if you have reset the prev dig time(confirmed dig), then use new dig time */
            if (prev_dig_time_msecs == 0)
            {
                prev_dig_time_msecs = current_dig_time_msecs;
            }
            else
            {
                /* we have not reset prev dig time, so have not confirmed dig, keep previous dig time */
            }
        }
        else
        {
            /* no change to dig state, do nothing */
        }
    }
    else if  (prev_dig_state == PCS_DIGGING)
    {
        if (dig_state == PCS_TENTATIVE_DIGGING)
        {
            /* no change */
        }
        else if (dig_state == PCS_NOT_DIGGING)
        {
            /* stop timer */
            dig_timer_stop();

            /* use new dig time */
            prev_dig_time_msecs = current_dig_time_msecs;
        }
        else
        {
            /* no change to dig state, do nothing */
        }
    }
    else
    {
        /* dig state is unknown, reset timer, hold prev dig time */
        current_dig_time_msecs = 0;
    }

    prev_dig_state = dig_state;
}

/******************************************************************************
FUNCTION NAME: dig_timer_get_current
DESCRIPTION: Gets the dig timer value in milliseconds for the last completed dig
PARAMETER DESCRIPTION: 0 - dsi (not available)
                       non-zero - dig timer value in milliseconds of the last
                                  dig completed.
RETURN VALUE:
*******************************************************************************/
dig_timer_milliseconds_u32_t dig_timer_get_current(void)
{
	return prev_dig_time_msecs;
}

/******************************************************************************
FUNCTION NAME: dig_timer_set_target
DESCRIPTION: Sets the target dig time in milliseconds
PARAMETER DESCRIPTION: target dig time in milliseconds
RETURN VALUE:
*******************************************************************************/
void dig_timer_set_target(dig_timer_milliseconds_u32_t target_milliseconds)
{
	target_dig_time_msecs = target_milliseconds;
}

/******************************************************************************
FUNCTION NAME: dig_timer_get_target
DESCRIPTION: Gets the target dig time in milliseconds
PARAMETER DESCRIPTION: n/a
RETURN VALUE: target dig time in milliseconds
*******************************************************************************/
dig_timer_milliseconds_u32_t dig_timer_get_target(void)
{
	return target_dig_time_msecs;
}
