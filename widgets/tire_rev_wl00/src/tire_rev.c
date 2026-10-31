/*******************************************************************************
 ** COPYRIGHT (C) 2000 - 2021 CATERPILLAR INC. ALL RIGHTS RESERVED.
 ** CATERPILLAR: CONFIDENTIAL YELLOW
--------------------------------------------------------------------------------
FILE NAME: tire_rev.c
DESCRIPTION: Implementation for all tire_rev interfaces
 *******************************************************************************/

/*******************************************************************************
 ** -- #Include's --
 *******************************************************************************/
//#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <oel_timestamp.h>
#include "tire_rev_private.h"

/*******************************************************************************
 ** -- #Define, Struct's, Typedef's, Enum's --
 *******************************************************************************/

#define TIRE_REV_TARGET_PERIOD_MS 240
#define TIRE_REV_FORWARD_MASK   0x4000
#define TIRE_REV_REVERSE_MASK   0x1000
#define TIRE_REV_GEAR_FAULT     0x8000
#define TIRE_REV_LOADING_DISTANCE_THRESHOLD_DEFAULT 40*1000 /* 40 meters*/
#define TIRE_REV_OK 			0
#define TIRE_REV_NOT_AVAILABLE 	1

typedef enum {
    Waiting,
    Waiting_Reverse,
    Active_Reverse,
    Waiting_Forward,
    Active_Forward
}tire_rev_state_t;

/*******************************************************************************
 ** -- Function Prototypes --
 *******************************************************************************/

static uint32_t distance_travelled(float tire_rev_prev_ground_speed, float ground_speed,
        uint32_t ms_elapsed);

static void tire_rev_timer_start(void);
static uint32_t tire_rev_get_time_delta(void);
static void tire_rev_reset_data(void);

/*******************************************************************************
 ** -- Data Declarations --
 *******************************************************************************/

/* current state of tire rev module */
static tire_rev_state_t tire_rev_state;

/* previous ground speed in km/hr */
static float tire_rev_prev_ground_speed;

/* forward distance traveled in mm */
static uint32_t tire_rev_forward_dist;

/* reverse distance traveled in mm */
static uint32_t tire_rev_reverse_dist;

/* number of tire rotations in forward direction */
static float tire_rev_forward_tire_revs;

/* number of tire rotations in reverse direction */
static float tire_rev_reverse_tire_revs;

/* threshold for travel distance(reverse + forward) in millimeters for truck loading cycle */
static uint32_t tire_rev_loading_distance_threshold_mm;

/* status of the tire rev module, 0 - is OK, 1 is DSI */
static boolean tire_rev_status;

/* used to capture start time to calculate time diff between calls */
static oel_timestamp64_t tire_rev_begin_timestamp;

/******************************************************************************
FUNCTION NAME: distance_travelled
DESCRIPTION: Calculates the distance in millimeters traveled given the ground
               speed (previous and current) and the time elapsed in milliseconds
               between the two ground speed samples
PARAMETER DESCRIPTION: n/a
RETURN VALUE: n/a
 *******************************************************************************/
static uint32_t distance_travelled(float prev_ground_speed, float ground_speed,
        uint32_t ms_elapsed)
{
    /* convert speed from km/hr to mm/s */
	float prev_speed_mms = prev_ground_speed * 1000000/3600;
	float current_speed_mms = ground_speed * 1000000/3600;

    /* first-order trapezoidal integration */
	float distance_mm = ms_elapsed/1000.0 * (prev_speed_mms + current_speed_mms)/2;

    return (uint32_t)abs((int)(distance_mm));
}

/******************************************************************************
FUNCTION NAME: tire_rev_timer_start
DESCRIPTION: Starts a timer
PARAMETER DESCRIPTION: n/a
RETURN VALUE: n/a
 *******************************************************************************/
static void tire_rev_timer_start(void)
{
	tire_rev_begin_timestamp = oel_timestamp_get64();
}

/******************************************************************************
FUNCTION NAME: tire_rev_get_time_delta
DESCRIPTION: Returns the time delta from start of timer to now in milliseconds
PARAMETER DESCRIPTION:
RETURN VALUE:
 *******************************************************************************/
static uint32_t tire_rev_get_time_delta(void)
{
	uint64_t elapsed;
    uint32_t delta_ms;

	elapsed = oel_timestamp_get64() - tire_rev_begin_timestamp;

	/* elapsed time in milliseconds ( ticks divide by freq in milliseconds) */
	delta_ms = (uint32_t)(elapsed / (oel_timestamp_get_freq()/1000));

	return delta_ms;
}

/******************************************************************************
FUNCTION NAME: tire_rev_init
DESCRIPTION: Initializes the tire rev module
PARAMETER DESCRIPTION: n/a
RETURN VALUE: n/a
 *******************************************************************************/
void tire_rev_init(void)
{
    tire_rev_reset_data();
    tire_rev_loading_distance_threshold_mm = TIRE_REV_LOADING_DISTANCE_THRESHOLD_DEFAULT;
}

/******************************************************************************
FUNCTION NAME: tire_rev_reset_data
DESCRIPTION: Resets the tire_rev internal data and outputs
PARAMETER DESCRIPTION:
RETURN VALUE:
 *******************************************************************************/
static void tire_rev_reset_data(void)
{
    tire_rev_state = Waiting;
    tire_rev_status = TIRE_REV_NOT_AVAILABLE;
    tire_rev_reverse_dist = 0;
    tire_rev_forward_dist = 0;
    tire_rev_prev_ground_speed = 0.f;
    tire_rev_forward_tire_revs = 0.f;
    tire_rev_reverse_tire_revs = 0.f;
}

/******************************************************************************
FUNCTION NAME: tire_rev_20ms_update
DESCRIPTION: Periodic update wrapper for tire_rev module call at 20ms
PARAMETER DESCRIPTION: pcs_dig_state_t - as defined in pcs
                       GROUNDSPEED_INFO - as defined in pcs
                       	   speed scaled at 0.0036km/hr/bit
                       GEAR_INFO - as defined in pcs
RETURN VALUE: n/a
*******************************************************************************/
void tire_rev_20ms_update(pcs_dig_state_t dig_state, GROUNDSPEED_INFO *ground_speed_info, GEAR_INFO *gear_info)
{
    static uint8_t counter = TIRE_REV_TARGET_PERIOD_MS;
    if (TIRE_REV_TARGET_PERIOD_MS == counter)
	{
		tire_rev_update(dig_state, ground_speed_info, gear_info);

		/* reset counter */
		counter = 0;
	}

	/* increment the counter */
	counter+=20;
}

/******************************************************************************
FUNCTION NAME: tire_rev_update
DESCRIPTION: Periodic update for tire_rev module. Recommend call rate at 250ms
PARAMETER DESCRIPTION: pcs_dig_state_t - as defined in pcs
                       GROUNDSPEED_INFO - as defined in pcs
                       	   speed scaled at 0.0036km/hr/bit
                       GEAR_INFO - as defined in pcs
RETURN VALUE: n/a
 *******************************************************************************/

void tire_rev_update(pcs_dig_state_t dig_state, GROUNDSPEED_INFO *ground_speed_info, GEAR_INFO *gear_info)
{
    float ground_speed = ground_speed_info->speed * 0.0036;
    uint16_t gear = gear_info->gear;
    uint32_t ms_elapsed;

    if ((ground_speed_info->data_status) || (gear_info->gear_status) ||
            (gear & TIRE_REV_GEAR_FAULT)) {
        /* bad data, reset data */
        tire_rev_reset_data();
        return;
    }

    if (dig_state == PCS_DIGGING)
    {
        /* reset the distances traveled for new load cycle */
        tire_rev_forward_dist = 0;
        tire_rev_reverse_dist = 0;
        tire_rev_status = TIRE_REV_NOT_AVAILABLE;

        tire_rev_state = Waiting_Reverse;
        tire_rev_timer_start();
    }

    if (tire_rev_state == Waiting_Reverse)
    {
        if ((ground_speed < 0) && (gear & TIRE_REV_REVERSE_MASK))
        {
        	tire_rev_status = TIRE_REV_OK;
        	tire_rev_state = Active_Reverse;

            /* calculate reverse distance */
            ms_elapsed = tire_rev_get_time_delta();
            tire_rev_reverse_dist += distance_travelled(tire_rev_prev_ground_speed, ground_speed, ms_elapsed);
            tire_rev_timer_start();
        }
        else
        {
            /* reset and start timer */
            tire_rev_timer_start();
        }
    }
    else if (tire_rev_state == Active_Reverse)
    {
        if ((ground_speed > 0) && (gear & TIRE_REV_FORWARD_MASK))
        {
            tire_rev_state = Active_Forward;

            /* add to forward distance also since we have started moving in forward direction*/
            ms_elapsed = tire_rev_get_time_delta();
            tire_rev_forward_dist = distance_travelled(tire_rev_prev_ground_speed, ground_speed, ms_elapsed);
        }

        if (tire_rev_prev_ground_speed >= 0 && ground_speed >= 0)
        {
            /* no reverse distance in this update*/
            tire_rev_timer_start();
        }
        else
        {
            /* calculate reverse distance*/
            ms_elapsed = tire_rev_get_time_delta();
            tire_rev_reverse_dist += distance_travelled(tire_rev_prev_ground_speed, ground_speed, ms_elapsed);
            tire_rev_timer_start();
        }

        /* if we have traveled greater the max loading cycle distance threshold cumulative
         * in both directions, reset the data and go back to waiting */
        if ((tire_rev_forward_dist + tire_rev_reverse_dist) > tire_rev_loading_distance_threshold_mm)
        {
            tire_rev_reset_data();
        }
    }
    else if (tire_rev_state == Active_Forward)
    {
        if ((ground_speed <0) && (gear & TIRE_REV_REVERSE_MASK))
        {
            tire_rev_state = Waiting;
        }

        if (tire_rev_prev_ground_speed <=0 && ground_speed <=0)
        {
            /* no forward distance in this update*/
            tire_rev_timer_start();
        }
        else
        {
            /* calculate forward direction*/
            ms_elapsed = tire_rev_get_time_delta();
            tire_rev_forward_dist += distance_travelled(tire_rev_prev_ground_speed, ground_speed, ms_elapsed);
            tire_rev_timer_start();
        }

        /* if we have traveled greater the max loading cycle distance threshold cumulative
         * in both directions, reset the data and go back to waiting */
        if ((tire_rev_forward_dist + tire_rev_reverse_dist) > tire_rev_loading_distance_threshold_mm)
        {
            tire_rev_reset_data();
        }
    }

    /* save off ground speed */
    tire_rev_prev_ground_speed = ground_speed;
}


/******************************************************************************
FUNCTION NAME: tire_rev_get_distance
DESCRIPTION: Provides the forward and reverse distances for either the last
                completed dig cycle or an on-going dig cycle
PARAMETER DESCRIPTION: Pointer to tire_rev_distance_t
RETURN VALUE: n/a
 *******************************************************************************/
void tire_rev_get_distance(tire_rev_distance_t *distance)
{
    if (distance)
    {
        distance->forward_mm = tire_rev_forward_dist;
        distance->reverse_mm = tire_rev_reverse_dist;
        distance->status = tire_rev_status;
    }
}

/******************************************************************************
FUNCTION NAME: tire_rev_get_rotations
DESCRIPTION: Provides the forward and reverse number of tire rotations
PARAMETER DESCRIPTION: Pointer to tire_rev_rotations_t
RETURN VALUE: n/a
 *******************************************************************************/
void tire_rev_get_rotations(tire_rev_rotations_t *rotations, uint32_t tire_radius_mm)
{
    /* check for null ptr */
	if (rotations)
    {
    	/* check of non-zero tire radius */
		if (tire_radius_mm)
    	{
    		rotations->forward = (float)tire_rev_forward_dist/(2*M_PI *tire_radius_mm);
    		rotations->reverse = (float)tire_rev_reverse_dist/(2*M_PI *tire_radius_mm);
    		rotations->status = tire_rev_status;
    	}
    	else
    	{
    		/* invalid tire radius */
    		rotations->status = TIRE_REV_NOT_AVAILABLE;
    	}
    }
}

/******************************************************************************
FUNCTION NAME: tire_rev_set_loading_distance_threshold
DESCRIPTION: Set the loading distance travel threshold in meters.
PARAMETER DESCRIPTION: Distance in meters
RETURN VALUE: n/a
 *******************************************************************************/
void tire_rev_set_loading_distance_threshold(uint32_t distance_m)
{
    tire_rev_loading_distance_threshold_mm = distance_m*1000;
}
