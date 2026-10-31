/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include "dummyTip2.h"
#include "octip_mach01_out.h"
/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/

/*******************************************************************************
** -- Function definitions --
*******************************************************************************/

int num3;
int num4;

void dummyTip2Init()
{
    num3 = 0; 
    num4 = 0;
}


void dummyTip2Update()
{
    octip_mach01_out.trigger = 0;
    octip_mach01_out.severity = 0;
    if((num3 + num4) == 50)
    {
        octip_mach01_out.trigger = 1;
        octip_mach01_out.severity = 0.5;
    }
    
    if((num3 + num4) == 100)
    {
        octip_mach01_out.trigger = 1;
        octip_mach01_out.severity = 1.0;
    }

    octip_mach01_out.stat_data[0] = num3+num4;
    octip_mach01_out.stat_data_sz = 1;
}
