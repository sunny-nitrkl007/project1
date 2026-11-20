///////////////////////////////////////////////////////////////////////////////
// @attention COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
//
// @file    EthernetPortStatistics.hpp
//
// @brief   ACD Plugin for Ethernet Port Statistics.
///////////////////////////////////////////////////////////////////////////////
#ifndef ETHERNETPORTSTATISTICS_HPP_
#define ETHERNETPORTSTATISTICS_HPP_

///////////////////////////////////////////////////////////////////////////////
// -- #Include's --
///////////////////////////////////////////////////////////////////////////////
#include <cmath>
#include "task/AutonomyTask.h"
#include <taskPlugins/base/TaskPlugin.hpp>

// scl_stat_db
#include "scl_stat_db_alloc.h"
#include "scl_stat_db.h"
#include "bdt_action.h"
#include "bdt_proto.h"

// ACD
#include "src_j1939/app_can_init.h"

///////////////////////////////////////////////////////////////////////////////
// -- #Define, Struct's, Typedef's, Enum's --
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// -- Class Definition
///////////////////////////////////////////////////////////////////////////////
class EthernetPortStatistics : public TaskPlugin
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor request a reference to the parent task
    ///////////////////////////////////////////////////////////////////////////////
    EthernetPortStatistics() = delete;
    EthernetPortStatistics(task::Task &parent, TaskInfo& pluginInfo) :
        action_config{2},    // max_simultaneous_clients
        m_numRxCon{4},
        m_rxBufSize{200},
        m_numTxCon{4},
        m_txBufSize{200},
        m_numDataLinkCon{3}
    {};

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the plugin name (used for configuring update rate)
    /// @return name of the plugin
    ///////////////////////////////////////////////////////////////////////////////
    std::string getName() override { return "EthernetPortStatistics"; }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes the plugin.
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool initialize() override
    {
        ConfigSection pluginConfig;
        if (!m_parent.getTaskParser().getSection(getName(), pluginConfig))
        {
            AIS_LOG_WARN("Config section for %s not found", getName().c_str());
        }
        else
        {
            pluginConfig.get("numRxCon", m_numRxCon);
            pluginConfig.get("rxBufSize", m_rxBufSize);
            pluginConfig.get("numTxCon", m_numTxCon);
            pluginConfig.get("txBufSize", m_txBufSize);
            pluginConfig.get("numDataLinkCon", m_numDataLinkCon);
            pluginConfig.get("maxSimultaneousClients", action_config.max_simultaneous_clients);
        }
        AIS_LOG_INFO("numRxCon: %u, rxBufSize: %u, numTxCon: %u, txBufSize: %u, numDataLinkCon: %u, max_simultaneous_clients: %u",
                m_numRxCon, m_rxBufSize, m_numTxCon, m_txBufSize, m_numDataLinkCon, action_config.max_simultaneous_clients);

        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes the plugin after j1939 initialization
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool postInitialize() override
    {
        // Initialize the bdt layer
        if (FALSE == bdt_init(m_numRxCon, m_rxBufSize, m_numTxCon, m_txBufSize, m_numDataLinkCon))
        {
            AIS_LOG_ERROR("bdt_init failed");
            return false;
        }
        // This operation will initialize the bdt action protocol.
        if (FALSE == bdt_action_init(&action_config))
        {
            AIS_LOG_ERROR("bdt_action_init failed");
            return false;
        }
        // This operation will set the BDT J1939 resource.
        bdt_j1939_set_resource(app_bdt_resource_config);
        // This assumes that BDT will be on the 1st J1939 link.
        uint8_t datalinkId = bdt_j1939_init(Ph_Link_app);
        AIS_LOG_NOTICE("bdt_j1939_init retuned data link id %d.", datalinkId);

        // A function to define the period (in microsec) at which the periodic BDT processing function will be called at
        bdt_set_period(static_cast<uint32_t>(1000000 / m_cycleRateHz + 0.5));
        // A function to reserve space for the number of callback blocks needed.
        bdt_set_callback_block_count(4); // Note: incremented by 1
        // A function to reserve space for the number of datatypes to be defined for BDT
        bdt_set_datatype_count(4); // Note: incremented by 1

        // Initialize the scl_state_db module
        if (FALSE == scl_stat_db_read_cs_bdt_init())
        {
            AIS_LOG_ERROR("scl_stat_db_read_cs_bdt_init failed");
            return false;
        }
        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Updates the plugin, expected to be called every executive loop of the
    ///        parent task.
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool update() override
    {
        bdt_main();
        scl_stat_db_update();
        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Called during cleanup of the parent task.
    ///////////////////////////////////////////////////////////////////////////////
    void cleanup() override{};

protected:
private:
    bdt_action_config_t action_config;

    // Configurable parameters, types are based on bdt function signatures
    unsigned_8 m_numRxCon;
    unsigned_32 m_rxBufSize;
    unsigned_8 m_numTxCon;
    unsigned_32 m_txBufSize;
    unsigned_8 m_numDataLinkCon;
};

#endif
