/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include "dummyTip.h"
#include "octip_mach00_out.h"
/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/

/*******************************************************************************
** -- Function definitions --
*******************************************************************************/

#define TIP_COUNT 5 

octip_mach00_out_t tipArray[TIP_COUNT];

unsigned int num1;
unsigned int count;

void dummyTipInit()
{
    num1 = 0; 
    size_t i;
    for (i = 0; i < TIP_COUNT; ++i)
    {
        tipArray[i].trigger = 0;
        tipArray[i].severity = 0;
    }
}


void dummyTipUpdate()
{
    octip_mach00_out.trigger = 0;
    octip_mach00_out.severity = 0;
    octip_mach00_out.status = 1;

    size_t i = octip_tip_select - 1;
    if (i < TIP_COUNT)
    {
        count = num1/TIP_COUNT;

        tipArray[i].trigger = 0;
        tipArray[i].severity = 0;

        if (count > 0)
        {
            if((count % 25 == 0) && (i == 0))
            {
                tipArray[i].trigger = 1;
                tipArray[i].severity = 0.1;        // severity ranges 0.0 to 1.0
            }
            else if((count % 50 == 0) && (i == 1))
            {
                tipArray[i].trigger = 1;
                tipArray[i].severity = 0.3;
            }
            else if((count % 75 == 0) && (i == 2))
            {
                tipArray[i].trigger = 1;
                tipArray[i].severity = 0.5;
            }
            else if((count % 100 == 0) && (i == 3))
            {
                tipArray[i].trigger = 1;
                tipArray[i].severity = 0.7;
            }
            else if((count % 125 == 0) && (i == 4))
            {
                tipArray[i].trigger = 1;
                tipArray[i].severity = 1.0;
            }
        }
        tipArray[i].status = (i % 2 == 0) ? 0 : 1;   // Alternate DSI

        octip_mach00_out = tipArray[i];
    }
    octip_mach00_out.stat_data[0] = num1;
    octip_mach00_out.stat_data[1] = count;
    octip_mach00_out.stat_data_sz = 2;
    num1++;
}
