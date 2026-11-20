#ifndef BMICDLPIDDEF_H
#define BMICDLPIDDEF_H

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <stdint.h>
/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
#define BMI_CDL_DRE_ADDRESS    	   		0x37   /* Address used for Data Requesting ECM */

/* ECM Address */
#define BMI_CDL_DSE_ADDRESS_ENG   				0x24   /* Address used for Data Source ECM */
#define BMI_CDL_DSE_ADDRESS_IMPL				0x52   /* Address used for Data Source ECM */
#define BMI_CDL_DSE_ADDRESS_CHASSIS				0x57   /* Address used for Data Source ECM */
#define BMI_CDL_DSE_ADDRESS_TRANS_CHASSIS		0x1B   /* Address used for Data Source ECM */
#define BMI_CDL_DSE_ADDRESS_STEERING			0x96
#define BMI_CDL_DSE_ADDRESS_COMM_GATEWAY_1      0xA1

#define BMI_CDL_SYS_TBL_ENTRIES_COUNT 	1

/*Number of PID entries in ECM table.*/
#define BMI_CDL_ECM_TBL_ENTRIES_COUNT 	5
/*Number of PID entries in PID param table.*/
#define BMI_CDL_PARAM_TBL_ENTRIES_COUNT 29

/*PID Definitions*/
const uint32_t BMI_CDL_PID_AUX_VAL_1_PORT_B_SOL_CURR_PER 	= 0xD009BA;
const uint32_t BMI_CDL_PID_AUX_VAL_1_PORT_A_SOL_CURR_PER 	= 0xD009BC;
const uint32_t BMI_CDL_PID_AUX_VAL_2_PORT_B_SOL_CURR_PER 	= 0xD009BE;
const uint32_t BMI_CDL_PID_AUX_VAL_2_PORT_A_SOL_CURR_PER 	= 0xD009C0;
const uint32_t BMI_CDL_PID_AUX_VAL_3_PORT_B_SOL_CURR_PER 	= 0xD009C2;
const uint32_t BMI_CDL_PID_AUX_VAL_3_PORT_A_SOL_CURR_PER 	= 0xD009C4;
const uint32_t BMI_CDL_PID_AUX_VAL_4_PORT_B_SOL_CURR_PER 	= 0xD009C6;
const uint32_t BMI_CDL_PID_AUX_VAL_4_PORT_A_SOL_CURR_PER 	= 0xD009C8;
const uint32_t BMI_CDL_PID_AUX_VAL_5_PORT_B_SOL_CURR_PER 	= 0xD009CA;
const uint32_t BMI_CDL_PID_AUX_VAL_5_PORT_A_SOL_CURR_PER 	= 0xD009CC;
const uint32_t BMI_CDL_PID_AUX_VAL_6_PORT_B_SOL_CURR_PER 	= 0xD009CE;
const uint32_t BMI_CDL_PID_AUX_VAL_6_PORT_A_SOL_CURR_PER 	= 0xD009D0;
const uint32_t BMI_CDL_PID_AUX_VAL_7_PORT_B_SOL_CURR_PER 	= 0xD009D2;
const uint32_t BMI_CDL_PID_AUX_VAL_7_PORT_A_SOL_CURR_PER 	= 0xD009D4;
const uint32_t BMI_CDL_PID_BLADE_SLOPE_PER 				 	= 0xD015DD;
const uint32_t BMI_CDL_PID_BALDE_LEFT_RAISE_SOL_CURR_PER 	= 0xD00959;
const uint32_t BMI_CDL_PID_BALDE_LEFT_LOWER_SOL_CURR_PER 	= 0xD0095A;
const uint32_t BMI_CDL_PID_BALDE_RIGHT_RAISE_SOL_CURR_PER	= 0xD0095B;
const uint32_t BMI_CDL_PID_BALDE_RIGHT_LOWER_SOL_CURR_PER	= 0xD0095C;
const uint32_t BMI_CDL_PID_ENG_LOAD_FACTOR 					= 0xF118;
const uint32_t BMI_CDL_PID_ENG_SPEED 						= 0x0040;
const uint32_t BMI_CDL_PID_STEERING_ANGLE 					= 0xF4F9;
const uint32_t BMI_CDL_PID_ACTUAL_GEAR 						= 0xF5D9;
const uint32_t BMI_CDL_PID_AMB_AIR_TEMP 					= 0xF477;
const uint32_t BMI_CDL_PID_AIR_INLET_TEMP 					= 0xF511;
const uint32_t BMI_CDL_PID_ARTIC_SENSOR_DUTY_CYCLE 			= 0xF22F;
const uint32_t BMI_CDL_PID_MACH_ARTIC_ANGLE 				= 0xF48C;
const uint32_t BMI_CDL_PID_MACH_IDLE_STATUS 				= 0xD10AB5;
const uint32_t BMI_CDL_PID_GPS                              = 0xF84D;
const uint32_t BMI_CDL_PID_BODY_UP 	        				= 0xF604;
const uint32_t BMI_CDL_PID_GROUND_SPEED 					= 0x18;
const uint32_t BMI_CDL_PID_FUEL_RATE 	      				= 0xF525;
const uint32_t BMI_CDL_PID_ENGINE_SPEED 					= 0x40;
const uint32_t BMI_CDL_PID_TOTAL_FUEL 	    			    = 0xC8;
const uint32_t BMI_CDL_PID_GEAR 	       					= 0xF002;
const uint32_t BMI_CDL_PID_TIME_ZONE          			    = 0xFA27;

const uint32_t ChannelIndex0 = 0;
const uint32_t ChannelIndex1 = 1;
const uint32_t ChannelIndex2 = 2;
const uint32_t ChannelIndex3 = 3;
const uint32_t ChannelIndex4 = 4;
const uint32_t ChannelIndex5 = 5;
const uint32_t ChannelIndex6 = 6;
const uint32_t ChannelIndex7 = 7;
const uint32_t ChannelIndex8 = 8;
const uint32_t ChannelIndex9 = 9;
const uint32_t ChannelIndex10 = 10;
const uint32_t ChannelIndex11 = 11;
const uint32_t ChannelIndex12 = 12;
const uint32_t ChannelIndex13 = 13;
const uint32_t ChannelIndex14 = 14;
const uint32_t ChannelIndex15 = 15;
const uint32_t ChannelIndex16 = 16;
const uint32_t ChannelIndex17 = 17;
const uint32_t ChannelIndex18 = 18;
const uint32_t ChannelIndex19 = 19;
const uint32_t ChannelIndex20 = 20;
const uint32_t ChannelIndex21 = 21;
const uint32_t ChannelIndex22 = 22;
const uint32_t ChannelIndex23 = 23;
const uint32_t ChannelIndex24 = 24;
const uint32_t ChannelIndex25 = 25;
const uint32_t ChannelIndex26 = 26;
const uint32_t ChannelIndex27 = 27;
const uint32_t ChannelIndex28 = 28;
const uint32_t ChannelIndex29 = 29;
const uint32_t ChannelIndex30 = 30;


/*PID Request Rates*/
#define BMI_CDL_PID_REQ_RATE_100_MS 100
#define BMI_CDL_PID_REQ_RATE_200_MS 200
#define BMI_CDL_PID_REQ_RATE_400_MS 400
#define BMI_CDL_PID_REQ_RATE_1000_MS 1000

/*Spl PIDs*/
#define BMI_CDL_MACH_GEAR_IN_REV 0x10

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/

#endif /* #ifndef BMICDLPIDDEF_H */
