////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Caterpillar Inc.  All Rights Reserved.
//
//     Class: bmi_ethernet_parser
//
// File Name: bmi_ethernet_parser.h
//
//  Abstract: Declarations for the class that handles
//            the application configuration, including
//            parameter tables
//
////////////////////////////////////////////////////////

#ifndef BMIETHERNETPARSER_H_
#define BMIETHERNETPARSER_H_

#include <string>          // std::string
#include <vector>          // std::vector
#include <std_types.h>
#include <ais/config/ConfigSection.h>
#include <stdint.h>
#include "interfaces/DataLinkData/InterfaceTypes.h"
#include "interfaces/DataLinkData/DataLinkParamInfo.h"

extern "C"
{
    #include <cdl2_proto.h>
    #include <cdl2_struct.h>
    #include <cdl2_mod_globals.h>
    #include <cdl2_mod_proto.h>
    #include <scl_pdb.h>
    #include <csf_pgt_client.h>
}

namespace tes_common_ais
{
namespace bmi_config_parser {

//BmiEthernet config tables.
struct BmiEthEcmCfg_t
{
    std::string EcmId;
    uint32_t Fid;
    uint32_t IPAddress;
    uint16_t Cid;
};

struct BmiEthPidCfgTbl_t
{
    std::string ParamName;
    DataLinkParamInfo::DlpParamIdentifierType_t ParameterIdentifierType;
    unsigned_32 data_ID;
    unsigned_8 data_size;
    unsigned_8 flags;
    uint32_t RequestPeriod;
    uint32_t SourceFid;
    std::string ByteOrder;
    cdl2_parameter_type_t ParameterType;
    std::string DsiSupport;
    uint8_t DiagSupport;
    uint8_t VarLengthDataType;
    float Scaling;
    float Offset;
    DataLinkParamInfo::DlpUnits_t Units;//0
};

struct BmiEthSpnCfgTbl_t
{
    std::string ParamName;
    DataLinkParamInfo::DlpParamIdentifierType_t ParameterIdentifierType;
    uint_least32_t spn;
    uint_least16_t size_in_bits;
// ENM     bool_least_t status_conv;
// ENM     scl_pdb_param_byte_order_t byte_order;
    uint32_t RequestPeriod;
    uint32_t SourceFid;
    uint8_t DiagSupport;
    float Scaling;//1
    float Offset;//0
};

struct BmiEthCatExtIdCfgTbl_t
{
    std::string ParamName;
    DataLinkParamInfo::DlpParamIdentifierType_t ParameterIdentifierType;
    uint_least16_t cat_ext_id;
    uint_least16_t data_size;
    uint32_t RequestPeriod;
    uint32_t SourceFid;
    uint8_t DiagSupport;
};

struct BmiEthcfg_t
{
    std::vector<BmiEthPidCfgTbl_t> PidCfg;
    std::vector<BmiEthSpnCfgTbl_t> SpnCfg;
    std::vector<BmiEthCatExtIdCfgTbl_t> ExtIdCfg;
    std::vector<BmiEthEcmCfg_t> EcmSrcCfg;
};

inline bool isLsbFirst(const BmiEthPidCfgTbl_t& bmiConfig) { return (bmiConfig.flags & SCL_PDB_PID_LSB) == SCL_PDB_PID_LSB; }
inline bool isSigned(const BmiEthPidCfgTbl_t& bmiConfig) { return (bmiConfig.flags & SCL_PDB_PID_SIGNED) == SCL_PDB_PID_SIGNED; }
inline bool isDsiSupported(const BmiEthPidCfgTbl_t& bmiConfig) { return bmiConfig.ParameterType <= CDL2_I32_DSI; }

///////////////////////////////////////////////////////////////////////////////
/// @brief Parse a BmiEthernet JSON file
/// @return true if successful and false otherwise
/// @param jsonConfigFileName - name of the json file
/// @param BmiEthCfgTbl - [out] Parsed configuration table
///////////////////////////////////////////////////////////////////////////////
bool ParseJSONFile(const std::string& jsonConfigFileName, BmiEthcfg_t& BmiEthCfgTbl);

///////////////////////////////////////////////////////////////////////////////
/// @brief Add parsed parameters to DataLinkDataWrapper
/// @return true if successful and false otherwise
/// @param const bmi_ethernet_parser::BmiEthcfg_t& bmiEthcfg
///////////////////////////////////////////////////////////////////////////////
bool AddToDataLinkDataWrapper(const BmiEthcfg_t& bmiEthcfg);

// STL containers for common services Rx/Tx structs
using RxPidConfigTable_t = std::unordered_map<unsigned_32, scl_pdb_pid_rx_config_t>;
using RxSpnConfigTable_t = std::unordered_map<uint_least32_t, scl_pdb_spn_rx_config_t>;
using RxCatExtIdConfigTable_t = std::unordered_map<uint_least16_t, scl_pdb_cat_ext_id_rx_config_t>;

using TxSpnConfigTable_t = std::unordered_map<uint_least32_t, scl_pdb_spn_tx_config_t>;
using TxCatExtIdConfigTable_t = std::unordered_map<uint_least16_t, scl_pdb_cat_ext_id_tx_config_t>;

///////////////////////////////////////////////////////////////////////////////
/// @brief Removes entries where the SourceFid does not match the provided fid
/// @param bmiEthcfg
/// @param fid
///////////////////////////////////////////////////////////////////////////////
void RemoveEntriesByFid(BmiEthcfg_t& bmiEthcfg, uint32_t fid);

bool GetRxPidConfigTable(const BmiEthcfg_t& bmiEthcfg, RxPidConfigTable_t& rxPidConfigTable);
bool GetRxSpnConfigTable(const BmiEthcfg_t& bmiEthcfg, RxSpnConfigTable_t& rxSpnConfigTable);
bool GetRxCatExtIdConfigTable(const BmiEthcfg_t& bmiEthcfg, RxCatExtIdConfigTable_t& rxCatExtIdConfigTable);

bool GetTxSpnConfigTable(const BmiEthcfg_t& bmiEthcfg, TxSpnConfigTable_t& txSpnConfigTable);
bool GetTxCatExtIdConfigTable(const BmiEthcfg_t& bmiEthcfg, TxCatExtIdConfigTable_t& txCatExtIdConfigTable);

void PrintConfigTables( const BmiEthcfg_t& appEthCfgTbl );

} // namespace bmi_config_parser
}
#endif
