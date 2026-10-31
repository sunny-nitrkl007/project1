/******************************************************************************************************************
 Copyright 2016 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: app_can_init.c

Description: All HAL_CANV3 components will be initialized
******************************************************************************************************************/

/******************************************************************************************************************
-- #Include's --
******************************************************************************************************************/
#include "app_rtos_config.h"
#include <hal_canv3_port.h>
#include <sss_oel_macros.h>
#include <SssPackD.h>
#include <SssMethodControl.h>
#include <std_types.h>
#include <sss_packd_types.h>
#include <sss_defs.h>
#include <sss_oel_defs.h>


/*****************************************************************************************************************
** -- Global Data Declarations -
*****************************************************************************************************************/
typedef struct
{
   volatile hal_canv3_port_t *hal_port1;
   volatile hal_canv3_port_t *hal_port2;
   volatile hal_canv3_port_t *hal_port3;
   volatile hal_canv3_port_t *hal_port4;
   oel_rtos_resource_config_t ** hal_canv3_resource;
}
hal_canv3_port_config_t;

/******************************************************************************************************************
Function Name: HalCanv3Resource_init

Description: This function checks if the CAN chip is supported and sets the number of objects needed by the 
             application. It then calls each component init function, passing the appropriate object numbers.

Parameter Description: hal_canv3_port_config_t *config : hal canv3 port configuration.
                       void *unused : used to avoid compiler warning.

Return Description: void
******************************************************************************************************************/
void HalCanv3Resource_init(void *unused, const hal_canv3_port_config_t *config)
{ 
   /* eliminate compiler warnings */
   (void)unused;

   /*  This operation sets the OEL resource to use.  The OEL resource is required to 
   protect shared resources within hal_canv3 from being access from multiple tasks.
   This operation must be called before hal_canv3_port_update().*/

   if(config->hal_port1 != NULL)
   {
      hal_canv3_port_set_resource(config->hal_port1, *(config->hal_canv3_resource)); 
   }
   if(config->hal_port2 != NULL)
   {
      hal_canv3_port_set_resource(config->hal_port2, *(config->hal_canv3_resource)); 
   }
   if(config->hal_port3 != NULL)
   {
      hal_canv3_port_set_resource(config->hal_port3, *(config->hal_canv3_resource));
   }
   if(config->hal_port4 != NULL)
   {
      hal_canv3_port_set_resource(config->hal_port4, *(config->hal_canv3_resource));
   }
}


hal_canv3_port_config_t hal_canv3_port_config =
{
   /* can port */
   HAL_CANV3_PORT_01,
   HAL_CANV3_PORT_02,
   NULL,
   NULL,
   &app_hal_canv3_resource_config
};
   
SssMethodControl_t method_config[] =
{
   SSS_TID_INIT,
   SSS_OEL_CAST_PACKAGE_METHOD(HalCanv3Resource_init),
};

SssPackD_t HalCanv3ResourcePackD_config =
{
   NULL,
   &hal_canv3_port_config,
   {
      sizeof(method_config)/sizeof(SssMethodControl_t),
      method_config
   }

};
