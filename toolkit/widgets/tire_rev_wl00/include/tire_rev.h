/*******************************************************************************
** COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
** CATERPILLAR: CONFIDENTIAL YELLOW
--------------------------------------------------------------------------------
FILE NAME: tire_rev.h
DESCRIPTION: Public interface for the tire_rev module
*******************************************************************************/

#ifndef __TIRE_REV_H__
#define __TIRE_REV_H__

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

#define TIRE_REV_OK             0
#define TIRE_REV_NOT_AVAILABLE  1

/* contains the distances traveled in each direction in mm */
typedef struct {
    uint32_t forward_mm;
    uint32_t reverse_mm;
    boolean status;
}tire_rev_distance_t;

/* contains the number of tire rotations in each direction */
typedef struct {
    float forward;
    float reverse;
    boolean status;
}tire_rev_rotations_t;


/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

/******************************************************************************
FUNCTION NAME: tire_rev_init
DESCRIPTION: Initializes the tire rev module
PARAMETER DESCRIPTION: n/a
RETURN VALUE: n/a
 *******************************************************************************/
void tire_rev_init(void);

/******************************************************************************
FUNCTION NAME: tire_rev_20ms_update
DESCRIPTION: Periodic update wrapper for tire_rev module call at 20ms
PARAMETER DESCRIPTION: pcs_dig_state_t - as defined in pcs
                       GROUNDSPEED_INFO - as defined in pcs
                       	   speed scaled at 0.0036km/hr/bit
                       GEAR_INFO - as defined in pcs
RETURN VALUE: n/a
*******************************************************************************/
void tire_rev_20ms_update(pcs_dig_state_t dig_state, GROUNDSPEED_INFO *ground_speed, GEAR_INFO *gear);

/******************************************************************************
FUNCTION NAME: tire_rev_update
DESCRIPTION: Periodic update for tire_rev module. Recommend call rate at 250ms
PARAMETER DESCRIPTION: pcs_dig_state_t - as defined in pcs
                       GROUNDSPEED_INFO - as defined in pcs
                       	   speed scaled at 0.0036km/hr/bit
                       GEAR_INFO - as defined in pcs
RETURN VALUE: n/a
 *******************************************************************************/
void tire_rev_update(pcs_dig_state_t dig_state, GROUNDSPEED_INFO *ground_speed, GEAR_INFO *gear);

/******************************************************************************
FUNCTION NAME: tire_rev_get_distance
DESCRIPTION: Provides the forward and reverse distances for either the last
                completed dig cycle or an on-going dig cycle
PARAMETER DESCRIPTION: Pointer to tire_rev_distance_t
RETURN VALUE: n/a
 *******************************************************************************/
void tire_rev_get_distance(tire_rev_distance_t *distance);

/******************************************************************************
FUNCTION NAME: tire_rev_get_rotations
DESCRIPTION: Provides the forward and reverse number of tire rotations
PARAMETER DESCRIPTION: Pointer to tire_rev_rotations_t, tire radius in millimeters
RETURN VALUE: n/a
 *******************************************************************************/
void tire_rev_get_rotations(tire_rev_rotations_t *rotations, uint32_t tire_radius_mm);

/******************************************************************************
FUNCTION NAME: tire_rev_set_loading_distance_threshold
DESCRIPTION: Set the loading distance travel threshold in meters.
PARAMETER DESCRIPTION: Distance in meters
RETURN VALUE: n/a
 *******************************************************************************/
void tire_rev_set_loading_distance_threshold(uint32_t distance_m);

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/

#if defined (__cplusplus)
}
#endif

#endif /* __CPM_TIRE_REV_H__ */
