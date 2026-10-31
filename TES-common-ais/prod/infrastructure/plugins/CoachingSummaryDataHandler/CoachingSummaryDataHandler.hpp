///////////////////////////////////////////////////////////////////////////////
// @attention COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
//
// @file    CoachingSummaryDataHandler.hpp
//
// @brief   Send coaching data to ET.
///////////////////////////////////////////////////////////////////////////////
#ifndef COACHINGSUMMARYDATAHANDLER_HPP_
#define COACHINGSUMMARYDATAHANDLER_HPP_

///////////////////////////////////////////////////////////////////////////////
// -- #Include's --
///////////////////////////////////////////////////////////////////////////////

#include "task/AutonomyTask.h"

#include <taskPlugins/base/TaskPlugin.hpp>
#include <plugins/DataLinkBridgeApplicationInterface/DataLinkBridgeApplicationInterface.hpp>
#include <interfaces/CoachingSummaryData/InterfaceTypes.h>
#include <catdl/BMI_CDL_PID_Coaching.h>

///////////////////////////////////////////////////////////////////////////////
// -- #Define, Struct's, Typedef's, Enum's --
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// -- Class Definition
///////////////////////////////////////////////////////////////////////////////
class CoachingSummaryDataHandler : public TaskPlugin
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor request a reference to the parent task
    ///////////////////////////////////////////////////////////////////////////////
    CoachingSummaryDataHandler() = delete;
    CoachingSummaryDataHandler(DataLinkBridgeApplicationInterface& j1939TxHandler) :
        m_j1939TxHandler{j1939TxHandler},
        m_pCoachingSummaryDataInput{nullptr}
    {}

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the plugin name (used for configuring update rate)
    /// @return name of the plugin
    ///////////////////////////////////////////////////////////////////////////////
    std::string getName() override { return "CoachingSummaryDataHandler"; }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes the plugin.
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool initialize() override
    {
        // ConfigSection pluginConfig;
        // if (!m_parent.getTaskParser().getSection(getName(), pluginConfig))
        // {
        //     AIS_LOG_ERROR("Config section for %s not found", getName().c_str());
        //     return false;
        // }

        // Bind SCS channels
        if (!task::InterfaceDb::bind("CoachingSummaryDataInput", m_pCoachingSummaryDataInput))
        {
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
        CoachingSummaryData coachingSummaryData;
        while (m_pCoachingSummaryDataInput->get(coachingSummaryData))
        {
            m_j1939TxHandler.SetParamTxValue(BMI_CDL_PID_OPERATOR_COACHING_TIP_PROGRESS_INDICATOR_PERCENTAGE, coachingSummaryData.getProgressIndicatorPercentageInt());
            m_j1939TxHandler.SetParamTxValue(BMI_CDL_PID_OPERATOR_COACHING_TIP_SUMMARY_DISPLAY_REQUIREMENT_STATUS, coachingSummaryData.displayRequired ? BMI_CDL_OPERATOR_COACHING_TIP_SUMMARY_DISPLAY_REQUIRED : BMI_CDL_OPERATOR_COACHING_TIP_SUMMARY_DISPLAY_NOT_REQUIRED);
            m_j1939TxHandler.SetParamTxValue(BMI_CDL_PID_OPERATOR_COACHING_TIP_SNOOZE_TIMER, static_cast<uint16_t>(SecondsToHours(coachingSummaryData.tipAutoEnableTimeSeconds) + 0.5));
            m_j1939TxHandler.SetParamTxValue(BMI_CDL_PID_OPERATOR_COACHING_TIP_INFO_CHANGE_COUNT_SINCE_LAST_VIEW, coachingSummaryData.countOfBadges);
        }

        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Called during cleanup of the parent task.
    ///////////////////////////////////////////////////////////////////////////////
    void cleanup() override {};

private:
    DataLinkBridgeApplicationInterface& m_j1939TxHandler;
    CoachingSummaryDataInput* m_pCoachingSummaryDataInput;
};

#endif
