**EthernetPortStatistics Plugin**

    0. Add a TaskPluginMgr to the ACD per the README in plugins/TaskPlugin.

    1. Update ACD_DIR/SConscript to add the necessary sourceFiles and libs (use SConscript.ACD as a reference)


        pluginDir = localEnv[ 'TES_COMMON_DIR' ] + '/prod/infrastructure/plugins/'

        # sourceFiles
        pluginDir + 'EthernetPortStatistics/scl_stat_db_config.c',

        # Add platform specific libraries for Ethernet Port Statistics (may be dependent on hal libraries)
        if ( localEnv[ 'PLATFORM' ] in [ 'A6N2' ] ):
            ethStatsList = [ 'scl_stat_db', 'bdt', 'hal_eth_statistics', 'bcm89501', 'micrel_ksz8567' ]
        elif ( localEnv[ 'PLATFORM' ] in [ 'A6N1' ] ):
            ethStatsList = [ 'scl_stat_db', 'bdt', 'hal_eth_statistics', 'sja1105', 'sja1105_a6n1' ]
        else:
            ethStatsList = []

        libList = [
            ...
            ethStatsList,
            'hal_canv3',

    2. Move `extern const oel_rtos_resource_config_t *app_hal_canv3_resource_config;` from ACD_DIR/src_app/app_rtos_config.h to  ACD_DIR/src_j939/app_can_init.h

        Configurable parameters are described here: https://catedocs.ecorp.cat.com/23/scl_stat_db/index.html
