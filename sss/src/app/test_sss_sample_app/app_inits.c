/******************************************************************************************************************
 Copyright 2016 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: app_inits.c

Description: This file provides application initialization functions that are called from 
             oel during application startup.
******************************************************************************************************************/

/******************************************************************************************************************
-- #Include's --
******************************************************************************************************************/
#include <SssSubsys.h>
#include <sss_oel_proto.h>
#include <sss_oel_types.h>
#include <sss_types.h>
#include <sss_macros.h>
#include <SssPackD.h>
#include <hal_canv3_port.h>
#include "task_set_01_global.h"

#if defined(A6P1)
#include <hal_init_A6P1.h>
#else
#include <hal_init.h>
#endif

static oel_rtos_woc_init_t app_pre_irq_init;
static oel_rtos_woc_init_t app_startup_init;
extern SssPackD_t HalCanv3ResourcePackD_config;

/******************************************************************************************************************
** -- Data Definitions
*****************************************************************************************************************/
 
/* define init objects 
   In general the objects combine the function and config constants. The functions are called through the objects.
   These app_pre_irq_init_o and app_startup_init_o objects have no config constants.
*/

static const oel_rtos_woc_init_object_t app_pre_irq_init_o =
{
   &app_pre_irq_init /* address of init function */
};

static const oel_rtos_woc_init_object_t app_startup_init_o =
{
   &app_startup_init /* address of init function */
};

/* define pre-irq init list. This is a list of pointers to init objects.*/
oel_rtos_init_object_t const* const app_pre_irq_init_list[]= { /* insert pre-irq init objects here */
                                                              OEL_BASE(&app_pre_irq_init_o),
                                                              NULL};                      /* MUST end with NULL */

 /* define startup init list. This is a list of pointers to init objects.*/
oel_rtos_init_object_t const* const app_startup_init_list[]= { /* insert startup init objects here */
                                                              #ifdef A5M4I1
                                                                  HAL_INIT_A5M4I1,
                                                              #endif /* A5M4I1 */
															  #ifdef A6P1
                                                              /* insert startup init objects here */
                                                                  HAL_INIT_A6P1,
                                                              #endif
                                                              OEL_BASE(&app_startup_init_o),
                                                              NULL};                       /* MUST end with NULL */
						
                                                        
/******************************************************************************************************************
FUNCTION NAME:  app_pre_irq_init
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*****************************************************************************************************************/

static void app_pre_irq_init(oel_rtos_woc_init_object_t const* never_used)
{
   (void) never_used;   /* touch arg to avoid warning */
   /*Insert application and legacy library init code here.New components should provide init object that can be 
   directly added to the app_pre_irq_init_list[].

   NOTE!!! The OS is not running yet and most oel services, OS services and some C standard library services 
   are not available at this point. The hardware watchdog is not periodically strobed yet and can time out.
   Execution is single threaded at this point and will delay startup of critical tasks.  Design initialization for
   startup_init.*/ 
}

/******************************************************************************************************************
FUNCTION NAME:  app_startup_init
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*****************************************************************************************************************/

static void app_startup_init(oel_rtos_woc_init_object_t const* never_used)
{
   (void) never_used;   /* touch arg to avoid warning */

   oel_u_init(NULL);
      
#if ((!defined A5M4I1)&& (!defined(A6P1)))
   hal_init(NULL); 
#endif

  /* Call OEL related initialization functions.
    ------------------------------------------------------------------------- */
  sss_oel_init_task(&task_set_01_config);

  /* init hal_canv3 resource, This package sets resource to the CAN port and so 
  has to be placed before any package that uses these ports 
  ---------------------------------------------------------------------------*/

  SssPackD_init(&HalCanv3ResourcePackD_config);
  
}
