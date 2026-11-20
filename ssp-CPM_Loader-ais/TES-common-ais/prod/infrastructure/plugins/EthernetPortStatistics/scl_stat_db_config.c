/******************************************************************************************************************
 Copyright 2018 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: scl_stat_db_config.c

Description:Configuration file for scl_stat_db
******************************************************************************************************************/
#include <taskPlugins/interfaces/PlatformDefinesC.h>

#if HAL_ETH_STATISTICS_SUPPORTED

#include <scl_stat_db.h>
#include <hal_eth_statistics.h>
#include <scl_stat_db_tune.h>


const scl_stat_db_hal_comp_t scl_stat_db_halcomp_list[] = {{SCL_STAT_DB_HAL_ETH, HAL_ETH_STATISTICS}};


const uint_least8_t scl_stat_db_hal_cmp_cnt = (sizeof(scl_stat_db_halcomp_list)/sizeof(scl_stat_db_hal_comp_t));

/*****************************************************************************************************************
This variable contains the description type of the Owner ECU.
IMPORTANT NOTE:
This should be defined by the application. This is required so that the application
may customize the library.
*****************************************************************************************************************/
const scl_stat_db_ecu_description_type_t scl_stat_db_owner_ecu_description_type = SCL_STAT_DB_OWNER_DESCRIPTION_TYPE;

/*****************************************************************************************************************
This variable contains the description ID of the Owner ECU.
IMPORTANT NOTE:
This should be defined by the application. This is required so that the application
may customize the library.
*****************************************************************************************************************/
const uint_least64_t scl_stat_db_owner_ecu_description_id = SCL_STAT_DB_OWNER_DESCRIPTION_ID;

#endif
