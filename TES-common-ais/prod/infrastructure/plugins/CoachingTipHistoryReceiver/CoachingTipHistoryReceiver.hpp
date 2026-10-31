///////////////////////////////////////////////////////////////////////////////
// @attention COPYRIGHT (C) 2020 CATERPILLAR INC. ALL RIGHTS RESERVED.
//
// @file    CoachingTipHistoryReceiver.hpp
//
// @brief   Plugin to manage BDT $CA11 for Coaching Tip History
///////////////////////////////////////////////////////////////////////////////
#ifndef CoachingTipHistoryReceiver_H_
#define CoachingTipHistoryReceiver_H_

///////////////////////////////////////////////////////////////////////////////
// -- #Include's --
///////////////////////////////////////////////////////////////////////////////
#include <mutex>
#include <vector>

#include <taskPlugins/base/TaskPlugin.hpp>
#include <taskPlugins/interfaces/BdtManagerInterface.h>
#include <interfaces/CoachingTipHistory/InterfaceTypes.h>

///////////////////////////////////////////////////////////////////////////////
// -- #Define, Struct's, Typedef's, Enum's --
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// -- Class Definitions
///////////////////////////////////////////////////////////////////////////////

class CoachingTipHistoryReceiver : public TaskPlugin
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor request a reference to the parent task
    ///////////////////////////////////////////////////////////////////////////////
    CoachingTipHistoryReceiver() = delete;
    CoachingTipHistoryReceiver(task::Task &parent, TaskInfo& taskInfo, BdtManagerInterface& bdtManager) :
        TaskPlugin{parent, taskInfo},
        m_BdtManager{bdtManager},
        m_pCoachingTipHistoryInput{nullptr}
    {};

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the plugin name (used for configuring update rate)
    /// @return name of the plugin
    ///////////////////////////////////////////////////////////////////////////////
    std::string getName() override { return "CoachingTipHistoryReceiver"; }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes the plugin.
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool initialize() override
    {
        if (!task::InterfaceDb::bind("CoachingTipHistoryInput", m_pCoachingTipHistoryInput))
        {
            return false;
        }

        m_BdtManager.connectOnFileReadRequestReceived(bdt::ApplicationHistoryDataType, boost::bind(&CoachingTipHistoryReceiver::onBlockDataReadRequestReceived, boost::ref(*this), _1, _2, _3));

        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Updates the plugin, expected to be called every executive loop of the
    ///        parent task.
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool update() override
    {
        std::lock_guard<std::mutex> lock(m_bdtMutex);
        while (m_pCoachingTipHistoryInput->get(tipHistory)) {}
        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Wrapper for appendSubFile to allow use of mutex
    ///////////////////////////////////////////////////////////////////////////////
    void onBlockDataReadRequestReceived(bdt::FileContentsType_t fileContentsType, bdt::BlockData_t& blockData, BdtManagerInterface::SubFileCount_t& subFileCount)
    {
        std::lock_guard<std::mutex> lock(m_bdtMutex);
        AIS_LOG_DEBUG("Read Request received for File Type 0x%04X", fileContentsType);
        tipHistory.appendSubFile(blockData, subFileCount);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Called during cleanup of the parent task.
    ///////////////////////////////////////////////////////////////////////////////
    void cleanup() override {};

protected:
private:
    CoachingTipHistory tipHistory;
    BdtManagerInterface& m_BdtManager;
    CoachingTipHistoryInput* m_pCoachingTipHistoryInput;
    std::mutex m_bdtMutex;
};

#endif
