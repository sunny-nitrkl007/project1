/*******************************************************************************
** COPYRIGHT (C) 2005-2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar’s proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  LpsPtBucket.c
DESCRIPTION:

   This file contains the calibration routines used by PCS

*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/

#include <LpsCommonTypeDef.h>

#include "LpsPtPrivate.h"

typedef struct {

    float startWeight;
    unsigned_8 startWeightAccuracy;

    float splitWeight;
    unsigned_8 splitWeightAccuracy;

    float currentWeight;
    unsigned_8 currentWeightAccuracy;
    boolean currentWeightLatched;

    boolean previousDigDetected;

} pcs_bucket_t;

static pcs_bucket_t pcs_bucket_data = {0};

void pcs_bucket_set_current_weight(unsigned_8 accuracy, float weight)
{
	pcs_bucket_data.currentWeightAccuracy = accuracy;
	pcs_bucket_data.currentWeight = weight;
}

float pcs_bucket_get_current_weight(unsigned_8* accuracy)
{
    if (NULL != accuracy)
    {
        *accuracy = pcs_bucket_data.currentWeightAccuracy;
    }
    return pcs_bucket_data.currentWeight;
}

void pcs_bucket_capture_start_weight(void)
{
    pcs_bucket_data.startWeight = pcs_bucket_data.currentWeight;
    pcs_bucket_data.startWeightAccuracy = pcs_bucket_data.currentWeightAccuracy;
    pcs_bucket_data.splitWeight = pcs_bucket_data.currentWeight;
    pcs_bucket_data.splitWeightAccuracy = pcs_bucket_data.currentWeightAccuracy;
}

float pcs_bucket_get_start_weight(unsigned_8* accuracy)
{
    if (NULL != accuracy)
    {
        *accuracy = pcs_bucket_data.startWeightAccuracy;
    }
    return pcs_bucket_data.startWeight;
}

void pcs_bucket_capture_split_weight(void)
{
    pcs_bucket_data.splitWeight = pcs_bucket_data.currentWeight;
    pcs_bucket_data.splitWeightAccuracy = pcs_bucket_data.currentWeightAccuracy;
}

float pcs_bucket_get_split_weight(unsigned_8* accuracy)
{
    if (NULL != accuracy)
    {
        *accuracy = pcs_bucket_data.splitWeightAccuracy;
    }
    return pcs_bucket_data.splitWeight;
}


