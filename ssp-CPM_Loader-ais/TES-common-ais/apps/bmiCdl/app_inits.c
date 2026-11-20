/******************************************************************************************************************
 Copyright 2009-2017 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: app_inits.c

Description: This file provides application initialization functions that are called from oel during application
             startup.
******************************************************************************************************************/
/******************************************************************************************************************
-- #Include's --
******************************************************************************************************************/

//#include <oel_rtos.h>
//#include <hal_types.h>
//#include <cdl2_proto.h>
//#include <hal_cdl.h>
#include "app_rtos_config.h"

//#include <cfc.h>

//#include <hal_init.h>

#include <oel_u.h>

#include <stdio.h>

/******************************************************************************************************************
-- #Define, Struct's, Typedef's, Enum's --
******************************************************************************************************************/
/******************************************************************************************************************
-- Function Prototypes --
******************************************************************************************************************/
extern void hal_init(void);

/* declare init functions */

static oel_rtos_woc_init_t app_pre_irq_init;
static oel_rtos_woc_init_t app_startup_init;

/******************************************************************************************************************
-- Data Declarations
******************************************************************************************************************/
/******************************************************************************************************************
-- Data Definitions
******************************************************************************************************************/

/*  define init objects
    In general the objects combine the function & config constants.The functions are called through the objects.
    These app_pre_irq_init_o and app_startup_init_o objects have no config constants.  */

static const oel_rtos_woc_init_object_t app_pre_irq_init_o =
{
    {&app_pre_irq_init} /* address of init function */
};

static const oel_rtos_woc_init_object_t app_startup_init_o =
{
    {&app_startup_init} /* address of init function */
};


/*  define pre-irq init list
    This is a list of pointers to init objects.*/

oel_rtos_init_object_t const* const app_pre_irq_init_list[]=
{
    /* insert pre-irq init objects here */
    OEL_BASE(&app_pre_irq_init_o),
    NULL                    /* MUST end with NULL */
};

/*   define startup init list
     This is a list of pointers to init objects.  */

oel_rtos_init_object_t const* const app_startup_init_list[]=
{
#if defined(A5E2)
    /* insert startup init objects here */
    HAL_INIT_A5E2,
#elif defined(A5E6I1)
    /* insert startup init objects here */
    HAL_INIT_A5E6I1,

#elif defined(A5E12I1)
    /* insert startup init objects here */
    HAL_INIT_A5E12I1,
#elif defined(A5E4V2I1)
    /* insert startup init objects here */
    HAL_INIT_A5E4V2I1,
#endif

#ifdef A5M4I1
    /* insert startup init objects here */
    HAL_INIT_A5M4I1,
#endif
#ifdef D5G1I1
    /* insert startup init objects here */
    HAL_INIT_D5G1I1,
#endif

#ifdef A5E2V2I1
    /* insert startup init objects here */
    HAL_INIT_A5E2V2I1,
#endif
#ifdef A5L3I1
    /* insert startup init objects here */
    HAL_INIT_A5L3I1,
#endif
#ifdef A5M12I1
    /* insert startup init objects here */
    HAL_INIT_A5M12I1,
#endif
#ifdef A5S3
    /* insert startup init objects here */
    HAL_INIT_A5S3,
#endif

#ifdef A6P1
    /* insert startup init objects here */
    HAL_INIT_A6P1,
#endif

    /* insert startup init objects here */
    OEL_BASE(&app_startup_init_o),
    NULL                    /* MUST end with NULL */
};

/*****************************************************************************************************************
Function name: app_pre_irq_init()

Description:

Parameter Description:
    oel_rtos_woc_init_object_t const* never_used :

Return Description: None.
*****************************************************************************************************************/
static void app_pre_irq_init(
    oel_rtos_woc_init_object_t const* never_used)
{
    (void) never_used;   /* touch arg to avoid warning */

    printf("\n******************************** app_pre_irq_init\n");

    /*  Insert application and legacy library init code here.New components should provide init object that can be
        directly added to the app_pre_irq_init_list[].

        NOTE!!! The OS is not running yet and most oel services, OS services and some C standard library services
        are not available at this point.   The hardware watchdog is not periodically strobed yet and can time out.
        Execution is single threaded at this point and will delay startup of critical tasks. Design initialization
        for startup_init.  */
}

/*****************************************************************************************************************
Function name: app_startup_init()

Description:

Parameter Description:
    oel_rtos_woc_init_object_t const* never_used

Return Description: None.
*****************************************************************************************************************/
static void app_startup_init(
    oel_rtos_woc_init_object_t const* never_used)
{
    (void) never_used;   /* touch arg to avoid warning */

    printf("\n******************************** app_startup_init\n");

    oel_u_init(NULL);

    hal_init();

}
