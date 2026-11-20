///////////////////////////////////////////////////////////////////////////////
// @attention COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
//
// @file    DataLinkDataReceiver.hpp
//
// @brief   Plugin to package all received DataLinkData objects for use by other plugins.
///////////////////////////////////////////////////////////////////////////////
#ifndef DATALINKDATARECEIVER_HPP_
#define DATALINKDATARECEIVER_HPP_

///////////////////////////////////////////////////////////////////////////////
// -- #Include's --
///////////////////////////////////////////////////////////////////////////////
#include <vector>

#include "task/AutonomyTask.h"
#include <taskPlugins/base/TaskPlugin.hpp>
#include <interfaces/DataLinkData/InterfaceTypes.h>

///////////////////////////////////////////////////////////////////////////////
// -- #Define, Struct's, Typedef's, Enum's --
///////////////////////////////////////////////////////////////////////////////

using DataLinkDataRxContainer = std::vector<DataLinkData>;

///////////////////////////////////////////////////////////////////////////////
// -- Class Definitions
///////////////////////////////////////////////////////////////////////////////

// Interface to DataLinkPackage
class DataLinkDataRxProvider
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the DataLinkDataRxContainer
    /// @return reference to the DataLinkDataRxContainer
    ///////////////////////////////////////////////////////////////////////////////
    virtual DataLinkDataRxContainer& getRxPackage() = 0;
};

// Packages all received DataLinkData objects into a DataLinkDataRxContainer.
// Intended to be run sequentially with other plugins, i.e. access to DataLinkPackage
// is not thread safe
class DataLinkDataReceiver : public TaskPlugin, public DataLinkDataRxProvider
{
public:

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor request a reference to the parent task
    ///////////////////////////////////////////////////////////////////////////////
    DataLinkDataReceiver() = delete;
    DataLinkDataReceiver() :
        m_pDataLinkDataInput{nullptr},
        m_SkipParentDataLinkData{false},
        m_TaskSourceId{DataLinkData::GetTaskSourceId(parent)}
    {};

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the DataLinkDataRxContainer
    /// @return reference to the DataLinkDataRxContainer
    ///////////////////////////////////////////////////////////////////////////////
    DataLinkDataRxContainer& getRxPackage() override
    {
        return m_dataLinkDataVector;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the plugin name (used for configuring update rate)
    /// @return name of the plugin
    ///////////////////////////////////////////////////////////////////////////////
    std::string getName() override { return "DataLinkDataReceiver"; }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes the plugin.
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool initialize() override
    {
        if (!task::InterfaceDb::bind("DataLinkDataReceiverInput", m_pDataLinkDataInput))
        {
            return false;
        }

        ConfigSection pluginConfig;
        if (!m_parent.getTaskParser().getSection(getName(), pluginConfig))
        {
            AIS_LOG_WARN("Config section for %s not found", getName().c_str());
        }
        else
        {
            pluginConfig.get("skipParentDataLinkData", m_SkipParentDataLinkData);
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
        m_dataLinkDataVector.clear();
        DataLinkData dlData;

        while (m_pDataLinkDataInput->get(dlData))
        {
            if (!m_SkipParentDataLinkData || m_TaskSourceId != dlData.GetTaskSourceId())
            {
                m_dataLinkDataVector.push_back(std::move(dlData));
            }
        }

        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Called during cleanup of the parent task.
    ///////////////////////////////////////////////////////////////////////////////
    void cleanup() override{};

protected:
private:
    DataLinkDataInput* m_pDataLinkDataInput;
    DataLinkDataRxContainer m_dataLinkDataVector;
    bool m_SkipParentDataLinkData;
    DataLinkData::TaskSourceId_t m_TaskSourceId;
};

#endif
