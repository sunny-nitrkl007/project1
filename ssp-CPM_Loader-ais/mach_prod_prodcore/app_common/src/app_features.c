/*******************************************************************************
**
**   COPYRIGHT (C) 2010 CATERPILLAR INC.   ALL RIGHTS RESERVED.
**
*******************************************************************************/

/*
**  --- Include's ---
*/

#include <scl_blk.h>
#include <scl_blk_composite.h>
#include <app_public.h>

/*
**  --- Local Static Variables ---
*/
static bool_least_t dummy_input;
static scl_blk_qu16_signal_t dummy_output;

/* 
**Static function prototypes
**/
static void feature_init ( FeatureObj_t * p_this );
static void feature_update ( FeatureObj_t * p_this );

/* Data variables */
const scl_blk_vtbl_t feature_vtbl =
{
    (scl_blk_init_t*)feature_init,
    (scl_blk_update_t*)feature_update,
};

/* Object definition */
FeatureObj_t sample_feat_obj =
{
    &feature_vtbl, /* base   */
	&dummy_input,  /* Input  */
    &dummy_output, /* Output */
    /* Config */
    /* Workspace */
};

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
<<<<<<<<<<<<                                            >>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<        Start of Code for this file         >>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<                                            >>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

static void feature_init ( FeatureObj_t * p_this )
{
    (void)p_this; /* Touched the var to remove warning */
    {/* Initialize workspace variable */
    }
    {/* Initialize output */
    }
}

static void feature_update ( FeatureObj_t * p_this )
{
    bool_least_t run;
    /* Output */
    SData_t out_des;

    if (0 != p_this->in.p_run){
        run = get_BData(p_this->in.p_run);
    }
    else{
        run = TRUE;
    }

    if (run && p_this){ 
    }
    else{ /* Don't run this module */ 
    }

    /* Set Output */
    set_SData(p_this->out.p_output, &out_des);

}
/**************************************************************************************/


/*
**  --- Public Global Variables ---
*/
/******************************************************************************************
// 1x features 
******************************************************************************************/
static const scl_blk_t* app_features_1x_00[] =
{
    /* Axle Oil Cooler */
    OEL_BASE(&sample_feat_obj),
};

const scl_blk_composite_t app_features_1x_obj =
    SCL_BLK_COMPOSITE( sizeof(app_features_1x_00)/sizeof(scl_blk_t*),
                       &app_features_1x_00[0] );

/******************************************************************************************
// 2x features 
******************************************************************************************/
static const scl_blk_t* app_features_2x_00[] =
{
    /* Axle Oil Cooler */
    OEL_BASE(&sample_feat_obj),
};

const scl_blk_composite_t app_features_2x_obj =
    SCL_BLK_COMPOSITE( sizeof(app_features_2x_00)/sizeof(scl_blk_t*),
                       &app_features_2x_00[0] );

/****************************************************************************************
// 4x features 
*****************************************************************************************/
static const scl_blk_t* app_features_4x_00[] =
{
    /* Ride Control Request */
    OEL_BASE(&sample_feat_obj),
};

const scl_blk_composite_t app_features_4x_obj =
    SCL_BLK_COMPOSITE( sizeof(app_features_4x_00)/sizeof(scl_blk_t*),
                       &app_features_4x_00[0] );


/****************************************************************************************
// 8x features 
*****************************************************************************************/
static const scl_blk_t* app_features_8x_00[] =
{
    OEL_BASE(&sample_feat_obj),
};

const scl_blk_composite_t app_features_8x_obj =
    SCL_BLK_COMPOSITE( sizeof(app_features_8x_00)/sizeof(scl_blk_t*),
                       &app_features_8x_00[0] );


