/*******************************************************************************
** COPYRIGHT (C) 2018 CATERPILLAR INC. ALL RIGHTS RESERVED.
*****************************************************************************
File name: octip_mach00_out.h

Description: Public cycle segmentation interfaces.
*******************************************************************************/

#ifndef OCTIP_MACH00_OUT_H__
#define OCTIP_MACH00_OUT_H__


/*Target Where The File std_types.h Is Provided By Caterpillar
**     For this target, there is no AUTOSAR content, so there is
**     no conflict.
*/
#include <stdint.h>
#include <std_types.h>


#ifdef __cplusplus
extern "C" {
#endif

/*
** Maximum number of statistics data per tip
*/
#define MAX_STATS_DATA (5u)  

/*
** Tip select. At this point the Tips are invoked individually via updating variable with appropriate
** input. The Tips are executeda with 'Switch-Case' statement.
** Tip index: 
*/
extern uint32_t octip_tip_select;

/*
**
** Output structure for Machine00 is defined as follows
**
** Output structure for 'coaching tip'.
** As per the Application Requirement this output structure gets overwritten by each tip.
** In general the Tip is detected/tripped/triggered at the beggining of the NEXT segment.
** This means the detection is for the Previous segment manuver, operator function.
** 
** 
*/
typedef struct {
    uint16_t status;  /* 0 = OK, 1 = DSI */
    uint8_t trigger;  /* have the tip been detected/tripped/activated */
    double  severity;  /* the degree/level of severity  */
    double  stat_data[MAX_STATS_DATA]; /* set of data points for future debugging/tuning analysis */
    uint8_t stat_data_sz;
}octip_mach00_out_t;

extern octip_mach00_out_t  octip_mach00_out;

extern float octip_gnd_spd;

#ifdef __cplusplus
}
#endif
#endif /* OCTIP_MACH00_OUT_H__ */

