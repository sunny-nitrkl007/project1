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
***	IO channel code 
***
*** LANGUAGE :
***    ANSI C
***
*** MACRO LIST:
***
*******************************************************************************/
#ifndef __APP_IO_H__
#define __APP_IO_H__

#include <std_types.h>
#include <prt_public.h>

#define SERIAL_NUM_SIZE		20
#define EQUIPMENT_NUM_SIZE	16

extern unsigned_8 num_supported_models;
extern unsigned_8 model_specific_values_index;

//extern int_16 ejector_position;
//extern int_16 apron_state;
//extern int_16 seq_assist_state;

/* function list */
/*
PRESSURE_INFO get_bowl_head_press(void);
PRESSURE_INFO get_bowl_rod_press(void);
PRESSURE_INFO get_aprn_cyl_rod_press(void);
POS_INFO get_bc_pos_mm(void);
unsigned_16 get_lcm_cycle(void);
unsigned_16 get_seq_ast_cycle(void);
POS_INFO get_apron_cyl_pos_mm(void);
unsigned_16 get_ejector_pos_state(void);
unsigned_16 get_apron_valve_state(void);
int get_raw_bc_head_frequency(void);
int get_raw_bc_rod_frequency(void);
int get_raw_bowl_pos_dutycycle(void);
int convert_freq_to_press(int fc);
MODEL_SPECIFIC_VALUES get_model_specific_numbers(void);
int_16 app_update_incAverage(unsigned_32 cum_id, unsigned_32 wght);
SPEED_INFO get_eng_spd_rpm(void);
unsigned_16 get_prk_brake_stat(void);
unsigned_16 get_imp_lockout(void);
*/
#endif /* __APP_IO_H__ */
