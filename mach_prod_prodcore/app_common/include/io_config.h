/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 1994-1995 CATERPILLAR INC.   ALL RIGHTS RESERVED.       %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
***
*** DESCRIPTION :
***	IO channel info for discrete inputs 
***
*** LANGUAGE :
***    ANSI C
***
*** MACRO LIST:
***
*******************************************************************************/
#ifndef __APP_IO_CONFIG_H__
#define __APP_IO_CONFIG_H__

#include <scl_vi2_pulse.h>
#include <scl_vi2_pwm.h>
#include <scl_vi2_discrete.h>
#include <scl_vio2.h>
#include <hal_pulsei.h>
#include <hal_std_types.h>
#include <hal_defs.h>
#include <app_rtos_config.h>


/*************** Definitions of Raw Inputs Objects ***************************/
extern scl_vi2_t* raw_bc_head_pres_frq;		 /* raw headend pressure object  */

extern scl_vi2_t* raw_bc_rod_pres_frq;		 /* raw rodend pressure object   */

/* INTEGRATION */    
extern scl_vi2_t* raw_bowl_cyl_pos;			 /* raw bowl position object  */
extern scl_vi2_t* raw_apron_cyl_pos;			 /* raw apron position object  */

//extern scl_vi2_t* raw_position_dc;			 /* raw position dutycle object  */

extern scl_vi2_t* raw_apron_rod_pres_frq;	 /* raw rodend pressure object   */

extern scl_vi2_t* raw_imp_lock_sw;         /* raw implement lock out switch*/

extern scl_vi2_t* raw_prk_brk_sw;          /* raw park brake sw */

extern scl_vi2_t* raw_none_sw;       /* this is spare used for apron valve state*/

/*****************************************************************************/

/*****************************************************************************/
/*****                   Raw Inputs Initialization Prototypes            *****/
/*****************************************************************************/

/* Called in app_pre_irq_init.c */
void init_raw_bc_head_frequency(void);
/* Called in app_pre_irq_init.c */
void init_raw_bc_rod_frequency(void);
/* Called in app_pre_irq_init.c */
/* INTEGRATION */    
void init_raw_bowl_pos(void);
void init_raw_apron_cyl_pos(void);
void init_prk_brk_sw(void);
void init_raw_imp_lock_sw(void);
void init_raw_none_sw(void);
//void init_raw_pos_dutycycle(void);
/* Called in app_pre_irq_init.c */
void init_raw_apron_rod_frequency(void);


#endif /* __APP_IO_CONFIG_H__ */




