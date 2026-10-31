///////////////////////////////////////////////////////////////////////////////
// @attention COPYRIGHT (C) 2020 CATERPILLAR INC. ALL RIGHTS RESERVED.
//
// @file    EthernetPgtServer.cpp
//
// @brief   Implement Ethernet PGT Server
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// -- #Include's --
///////////////////////////////////////////////////////////////////////////////

#include "EthernetPgtServer.h"
#include <arpa/inet.h>
#include <bmi/bmi_ethernet_util.h>

using namespace tes_common_ais;

// Define static class members
std::mutex EthernetPgtServer::m_Mutex;

std::vector<scl_pdb_t> EthernetPgtServer::m_SclPdbTable;

std::unordered_map<uint32_t, EthernetPgtServer::PidTxData_t> EthernetPgtServer::m_PidTxDataTable;

bmi_config_parser::TxSpnConfigTable_t EthernetPgtServer::m_SpnTxConfigTable;
std::unordered_map<uint_least32_t, EthernetPgtServer::SpnTxData_t> EthernetPgtServer::m_SpnTxDataTable;

bmi_config_parser::TxCatExtIdConfigTable_t EthernetPgtServer::m_CatExtIdTxConfigTable;
std::unordered_map<uint_least32_t, EthernetPgtServer::CatExtIdTxData_t> EthernetPgtServer::m_CatExtIdTxDataTable;

bmi_config_parser::BmiEthcfg_t EthernetPgtServer::m_BmiEthConfigTable;

bool EthernetPgtServer::postInitialize()
{
    ConfigSection pluginConfig;
    if (!getTaskParser().getSection(getName(), pluginConfig))
    {
        AIS_LOG_ERROR("Config section for %s not found", getName().c_str());
        return false;
    }

    if (!pluginConfig.get("serverFid", m_Fid))
    {
        AIS_LOG_ERROR("serverFid in config section for %s not found", getName().c_str());
        return false;
    }

    if (!pluginConfig.get("jsonConfigFile", m_JsonConfigFile))
    {
        AIS_LOG_ERROR("jsonConfigFile in config section for %s not found", getName().c_str());
        return false;
    }

    uint_least8_t httpdNumConnections = 1;
    if (!pluginConfig.get("httpdNumConnections", httpdNumConnections))
    {
        AIS_LOG_WARN("httpdNumConnections in config section for %s not found, using default %u", getName().c_str(), httpdNumConnections);
    }

    int_least16_t httpdTaskPeriodMs = 100;
    if (!pluginConfig.get("httpdTaskPeriodMs", httpdTaskPeriodMs))
    {
        AIS_LOG_WARN("httpdTaskPeriodMs in config section for %s not found, using default %u ms", getName().c_str(), httpdTaskPeriodMs);
    }

    uint16_t httpdPort = 80;
    if (!pluginConfig.get("httpdPort", httpdPort))
    {
        AIS_LOG_WARN("httpdPort in config section for %s not found, using default %u", getName().c_str(), httpdPort);
    }

    // Read PID and PGN values from JSON.
    // If parsing is successful, initialize Pgt server
    if (bmi_config_parser::ParseJSONFile(getConfigFileDirectory() + '/' + m_JsonConfigFile, m_BmiEthConfigTable))
    {
        // HTTP Server initialization
        m_HttpdConfig.its_heap_id = OEL_HEAP_1_ID;
        m_HttpdConfig.sockAddr = reinterpret_cast<sockaddr_storage*>(&m_SockAddr);
        m_HttpdConfig.num_connections = httpdNumConnections;

        m_SockAddr.sin_family = PF_INET;
        std::string ipAddress = bmi_ethernet_util::GetIpAddressString();
        if (0 == inet_aton(ipAddress.c_str(), &m_SockAddr.sin_addr))
        {
            AIS_LOG_ERROR("Malformed IP Address %s", ipAddress.c_str());
            return false;
        }
        m_SockAddr.sin_port = htons(httpdPort);

        m_pHttpdServer = csf_httpd_server_init(&m_HttpdConfig);
        if (m_pHttpdServer == nullptr)
        {
            AIS_LOG_ERROR("csf_httpd_server_init failed");
            return false;
        }
        AIS_LOG_INFO("HTTP server configured: sin_family = %u | sin_addr = 0x%08X (%s) | sin_port = %u", m_SockAddr.sin_family, m_SockAddr.sin_addr.s_addr, ipAddress.c_str(), m_SockAddr.sin_port);

        // Linux http init
        csf_httpd_linux_http_init(m_pHttpdServer);
 
        // Set the task period
        csf_httpd_set_task_period(m_pHttpdServer, httpdTaskPeriodMs);

        // Set Number of URI handlers - arbitrary number based on test_csf_pgt_srv_regression_linux
        if (csf_httpd_set_num_of_uri_handlers(m_pHttpdServer, 800) != TRUE)
        {
            AIS_LOG_ERROR("csf_httpd_set_num_of_uri_handlers failed");
            return false;
        }

        // Pgt Server initialization
        AIS_LOG_INFO("Initializing Pgt Server with fid 0x%08X", m_Fid);
        m_PgtServerConfig.server_fid = m_Fid;
        m_PgtServerConfig.httpd_ptr = m_pHttpdServer;

        csf_pgt_server_init(&m_PgtServerConfig);

        // Remove parameters from other FIDs
        RemoveEntriesByFid(m_BmiEthConfigTable, m_Fid);

        // Add TX PIDs to cdl2_pit database
        for (auto& pidInfo : m_BmiEthConfigTable.PidCfg)
        {
            m_PidTxDataTable.emplace(pidInfo.data_ID, PidTxData_t {pidInfo, 0, false});
            m_PidTxDataTable.at(pidInfo.data_ID).clearData();
        }

        // Add TX SPNs and cat-ext-ids  to common parameters data base. For additional information about common parameter data base configuration Refer to lib_scl\scl_pdb\doc\reference_manual
        GetTxSpnConfigTable(m_BmiEthConfigTable, m_SpnTxConfigTable);
        GetTxCatExtIdConfigTable(m_BmiEthConfigTable, m_CatExtIdTxConfigTable);

        // Create SPN TX Data Tables
        for (auto& bmiConfig : m_BmiEthConfigTable.SpnCfg)
        {
            auto it = m_SpnTxConfigTable.find(bmiConfig.spn);
            if (it == m_SpnTxConfigTable.end())
            {
                AIS_LOG_ERROR("SPN 0x%X not found in SpnTxConfigTable", bmiConfig.spn);
                continue;
            }
            auto &txConfig = it->second;

            std::vector<uint_least8_t> txDataValue;
            if (txConfig.size_in_bits <= 8)
            {
                txDataValue.resize(1);
            }
            else if (txConfig.size_in_bits <= 16)
            {
                txDataValue.resize(2);
            }
            else if (txConfig.size_in_bits <= 24)
            {
                txDataValue.resize(3);
            }
            else
            {
                txDataValue.resize(4);
            }
            // m_SpnTxDataValues[txConfig.first] = std::move(txDataValue);
            txConfig.tx_hdlr = &scl_pdb_spn_tx_hdlr;
            m_SpnTxDataTable.emplace(txConfig.spn, SpnTxData_t{bmiConfig, std::move(txDataValue)});
            m_SpnTxDataTable.at(txConfig.spn).clearData();
        }

        for (auto& txConfig : m_SpnTxConfigTable)
        {
            txConfig.second.hdlr_context = static_cast<void*>(&m_SpnTxDataTable.at(txConfig.first));
            m_SclPdbTable.push_back(scl_pdb_t{SCL_PDB_SPN_PARAM, static_cast<void*>(&txConfig.second)});
        }

        // Create CAT Ext ID TX Data Tables
        for (auto& bmiConfig : m_BmiEthConfigTable.ExtIdCfg)
        {
            auto it = m_CatExtIdTxConfigTable.find(bmiConfig.cat_ext_id);
            if (it == m_CatExtIdTxConfigTable.end())
            {
                AIS_LOG_ERROR("CAT Ext ID 0x%X not found in SpnTxConfigTable", bmiConfig.cat_ext_id);
                continue;
            }
            auto &txConfig = it->second;

            std::vector<uint_least8_t> txDataValue(bmiConfig.data_size);
            m_CatExtIdTxDataTable.emplace(txConfig.cat_ext_id, CatExtIdTxData_t{bmiConfig, std::move(txDataValue)});
            m_CatExtIdTxDataTable.at(txConfig.cat_ext_id).clearData();
            txConfig.tx_hdlr = &scl_pdb_cat_ext_id_tx_hdlr;
        }

        // Now that data is finalized, assign pointers
        for (auto& txConfig : m_CatExtIdTxConfigTable)
        {
            txConfig.second.hdlr_context = static_cast<void*>(&m_CatExtIdTxDataTable.at(txConfig.first));
            m_SclPdbTable.push_back(scl_pdb_t{SCL_PDB_CAT_EXT_ID, static_cast<void*>(&txConfig.second)});
        }

        // Register SPNs and CAT Ext IDs with SCL
        scl_pdb_add_tx_param_list(m_SclPdbTable.size(), m_SclPdbTable.data());

        AIS_LOG_INFO("postInitialize complete");
        m_InitDone = true;

        return true;
    }

    return false;
}

bool EthernetPgtServer::update()
{
    if (m_InitDone == false)
    {
        AIS_LOG_INFO("update requested before initialization is complete");
        return true;
    }

    std::lock_guard<std::mutex> lock(m_Mutex);
    csf_httpd_update(m_pHttpdServer);
    return true;
}

bool EthernetPgtServer::setPidValueEng(uint32_t paramId, double value)
{
    std::lock_guard<std::mutex> lock(m_Mutex);

    auto it = m_PidTxDataTable.find(paramId);
    if (it != m_PidTxDataTable.end())
    {
        float offset = value > 0 ? 0.5 : -0.5;
        it->second.setData(static_cast<uint32_t>(static_cast<int32_t>(value / it->second.bmiConfig.Scaling - it->second.bmiConfig.Offset + offset)));
        AIS_LOG_DEBUG("Setting PID $%X to Eng value %f (raw %u / 0x%X)", paramId, value, it->second.getData(), it->second.getData());
        return true;
    }
    else
    {
        AIS_LOG_WARN("PID $%X not found", paramId);
    }
    return false;
}

bool EthernetPgtServer::setPidValueRaw(uint32_t paramId, uint32_t value)
{
    std::lock_guard<std::mutex> lock(m_Mutex);

    auto it = m_PidTxDataTable.find(paramId);
    if (it != m_PidTxDataTable.end())
    {
        it->second.setData(value);
        AIS_LOG_DEBUG("Setting PID $%X to Raw value %u / 0x%X", paramId, value, it->second.getData(), it->second.getData());
        return true;
    }
    else
    {
        AIS_LOG_WARN("PID $%X not found", paramId);
    }
    return false;
}

bool EthernetPgtServer::setPidDsi(uint32_t paramId, uint8_t dsi)
{
    std::lock_guard<std::mutex> lock(m_Mutex);

    auto it = m_PidTxDataTable.find(paramId);
    if (it != m_PidTxDataTable.end())
    {
        it->second.setDsi(dsi);
        AIS_LOG_DEBUG("Setting PID $%X DSI to %u (Raw value %u / 0x%X)", paramId, dsi, it->second.getData(), it->second.getData());
        return true;
    }
    else
    {
        AIS_LOG_WARN("PID $%X not found", paramId);
    }
    return false;
}

bool EthernetPgtServer::setSpnValueEng(uint32_t spnId, double valueEng)
{
    std::lock_guard<std::mutex> lock(m_Mutex);

    auto it = m_SpnTxDataTable.find(spnId);
    if (it != m_SpnTxDataTable.end())
    {
        it->second.setValueEng(valueEng);
        AIS_LOG_DEBUG("Setting SPN $%X to %f", spnId, valueEng);
        return true;
    }
    else
    {
        AIS_LOG_WARN("SPN 0x%X not found", spnId);
    }
    return false;
}

bool EthernetPgtServer::setCatExtIdValue(uint32_t catExtId, uint32_t value)
{
    std::lock_guard<std::mutex> lock(m_Mutex);

    auto it = m_CatExtIdTxDataTable.find(catExtId);
    if (it != m_CatExtIdTxDataTable.end())
    {
        it->second.setValue(value);
        AIS_LOG_DEBUG("Setting CAT EXT ID $%X to %u", catExtId, value);
        return true;
    }
    else
    {
        AIS_LOG_WARN("CAT EXT ID 0x%X not found", catExtId);
    }
    return false;
}

int_16 EthernetPgtServer::cdl_tx_hdlr(void *tx_pie, unsigned_8 *data)
{
    // TODO: DSI?

    auto pPidTxData = static_cast<PidTxData_t*>(tx_pie);

    if (pPidTxData == nullptr)
    {
        AIS_LOG_ERROR("Unable to recast pie pointer");
        return -1;
    }

    AIS_LOG_DEBUG("Received request for PID $%X", pPidTxData->bmiConfig.data_ID);

    if (!pPidTxData->isDataValid())
    {
        AIS_LOG_WARN("No valid data for $%X has been set", pPidTxData->bmiConfig.data_ID);
        return 0;
    }

    if (pPidTxData->isLsbFirst())
    {
        switch (pPidTxData->bmiConfig.data_size) {
        case 1: {
            OEL_PACK_LE_8_NO_INCR(data, static_cast<unsigned_8>(pPidTxData->getData()));
            break;
        }
        case 2: {
            OEL_PACK_LE_16_NO_INCR(data, static_cast<unsigned_16>(pPidTxData->getData()));
            break;
        }
        case 4: {
            OEL_PACK_LE_32_NO_INCR(data, pPidTxData->getData());
            break;
        }
        default: {
            AIS_LOG_ERROR("Invalid data size for $%X", pPidTxData->bmiConfig.data_ID);
            return -1;
        }
        }
    }
    else
    {
        switch (pPidTxData->getDataSizeBytes()) {
        case 1: {
            OEL_PACK_BE_8_NO_INCR(data, static_cast<unsigned_8>(pPidTxData->getData()));
            break;
        }
        case 2: {
            OEL_PACK_BE_16_NO_INCR(data, static_cast<unsigned_16>(pPidTxData->getData()));
            break;
        }
        case 4: {
            OEL_PACK_BE_32_NO_INCR(data, pPidTxData->getData());
            break;
        }
        default: {
            AIS_LOG_ERROR("Invalid data size for $%X", pPidTxData->bmiConfig.data_ID);
            return -1;
        }
        }
    }

    for (size_t i = 0; i < pPidTxData->getDataSizeBytes(); i++)
    {
        AIS_LOG_DEBUG("PID $%X Byte #%u = 0x%02X", pPidTxData->bmiConfig.data_ID, i, data[i]);
    }

    return pPidTxData->getDataSizeBytes();
}

uint_least16_t EthernetPgtServer::scl_pdb_spn_tx_hdlr(uint_least8_t datalink_type, uint_least8_t datalink_instance, 
                                                     uint_least32_t src_id, uint_least32_t dest_id, void* datalink_info, uint_least8_t* data_buf,
                                                     uint_least16_t data_buf_size, const scl_pdb_spn_tx_config_t* spn_config)
{
    // TODO: DSI?
    AIS_LOG_DEBUG("Received request for SPN 0x%X", spn_config->spn);
    auto txDataEntry = static_cast<SpnTxData_t*>(const_cast<void*>(spn_config->hdlr_context));
    if (txDataEntry == nullptr)
    {
        AIS_LOG_ERROR("SPN 0x%X not found", spn_config->spn);
        data_buf = nullptr;
        return 0;
    }

    auto& txData = txDataEntry->getData();

    for (size_t i = 0; i < txData.size(); i++)
    {
        AIS_LOG_DEBUG("SPN 0x%X Byte #%u = 0x%02X", spn_config->spn, i, txData[i]);
    }
    data_buf = txData.data();

    return txData.size();
}

uint_least16_t EthernetPgtServer::scl_pdb_cat_ext_id_tx_hdlr(uint_least8_t datalink_type,uint_least8_t datalink_instance,uint_least32_t src_id,
                                                    uint_least32_t dest_id, void* datalink_info,uint_least8_t* data,uint_least16_t data_size,
                                                    const scl_pdb_cat_ext_id_tx_config_t *cat_ext_id_config)
{
    // TODO: DSI?
    AIS_LOG_DEBUG("Received request for CAT EXT ID 0x%X", cat_ext_id_config->cat_ext_id);
    auto txDataEntry = static_cast<CatExtIdTxData_t*>(cat_ext_id_config->hdlr_context);
    if (txDataEntry == nullptr)
    {
        AIS_LOG_ERROR("CAT Ext ID 0x%X not found", cat_ext_id_config->cat_ext_id);
        return 0;
    }

    auto dataLen =  txDataEntry->getData(data);

    for (size_t i = 0; i < dataLen; i++)
    {
        AIS_LOG_DEBUG("CAT EXT ID 0x%X Byte #%u = 0x%02X", cat_ext_id_config->cat_ext_id, i, data[i]);
    }

    return dataLen;
}
