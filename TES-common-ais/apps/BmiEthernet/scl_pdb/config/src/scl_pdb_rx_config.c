/******************************************************************************************************************
 Copyright 2017 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: scl_pdb_rx_config.c

Description:  SCL PDB  static allocations and static constant configuration. 
              Applications has to build this file 
******************************************************************************************************************/

#include <scl_pdb.h>
#include <scl_pdb_rx_tune.h>

/* SPn Rx config */
const uint_least16_t scl_pdb_max_num_rx_spn = SCL_PDB_NUM_RX_SPN;
const scl_pdb_spn_rx_config_t* scl_pdb_spn_rx_config[SCL_PDB_NUM_RX_SPN];

/* Pgn Rx config */
const uint_least16_t scl_pdb_max_num_rx_pgn = SCL_PDB_NUM_RX_PGN;
const scl_pdb_pgn_rx_config_t* scl_pdb_pgn_rx_config[SCL_PDB_NUM_RX_PGN];

/* cat-ext-id Rx config */
const uint_least16_t scl_pdb_max_num_rx_cat_ext = SCL_PDB_NUM_RX_CAT_EXT;
const scl_pdb_cat_ext_id_rx_config_t *scl_pdb_cat_ext_rx_config[SCL_PDB_NUM_RX_CAT_EXT];
      
      
