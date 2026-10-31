///////////////////////////////////////////////////////////////////////////////
// @attention COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
//
// @file    CoachingSummaryDataForAcd2.hpp
//
// @brief   Send coaching data to ET.
///////////////////////////////////////////////////////////////////////////////
#ifndef COACHINGSUMMARYDATAFORACD2_HPP_
#define COACHINGSUMMARYDATAFORACD2_HPP_

///////////////////////////////////////////////////////////////////////////////
// -- #Include's --
///////////////////////////////////////////////////////////////////////////////

#include "task/AutonomyTask.h"
#include <taskPlugins/interfaces/DatalinkManagerInterface.h>
#include <interfaces/CoachingSummaryData/InterfaceTypes.h>
#include <interfaces/CoachingShowHideStatus/InterfaceTypes.h>
#include <catdl/BMI_CDL_PID_Coaching.h>

///////////////////////////////////////////////////////////////////////////////
// -- #Define, Struct's, Typedef's, Enum's --
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// -- Class Definition
///////////////////////////////////////////////////////////////////////////////
class CoachingSummaryDataForAcd2 : public TaskPlugin
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor request a reference to the parent task
    ///////////////////////////////////////////////////////////////////////////////
    CoachingSummaryDataForAcd2() = delete;
    CoachingSummaryDataForAcd2(DatalinkManagerInterface& datalinkManager) :
        m_datalinkManager(datalinkManager),
        m_pCoachingSummaryDataInput{nullptr}
    {}

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the plugin name (used for configuring update rate)
    /// @return name of the plugin
    ///////////////////////////////////////////////////////////////////////////////
    std::string getName() override { return "CoachingSummaryDataForAcd2"; }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes the plugin.
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool initialize() override
    {
        AIS_LOG_DEBUG("CoachingSummary::initialize");
       // Bind SCS channels
        if (!task::InterfaceDb::bind("CoachingSummaryDataInput", m_pCoachingSummaryDataInput))
        {
            AIS_LOG_ALERT("CoachingSummaryDataInput FAILED");
            return false;
        }

        if (!task::InterfaceDb::bind("CoachingShowHideStatusInput", m_pCoachingShowHideStatusInput))
        {
            AIS_LOG_ALERT("CoachingShowHideStatusInput FAILED");
            return false;
        }

        return true;
    }


    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes the plugin after j1939 initialization
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool postInitialize() override 
    {
        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Updates the plugin, expected to be called every executive loop of the
    ///        parent task.
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool update() override
    {
        uint16_t    progressIndicatorPercentage = 0xFFF4;   // DSI-20
        uint16_t    displayRequired             = 0xFFF4;   // DSI-20
        uint16_t    countOfBadges               = 0xFFF4;   // DSI-20

        AIS_LOG_DEBUG("CoachingSummary::update");

        CoachingShowHideStatus coachingShowHideStatus;
        while (m_pCoachingShowHideStatusInput->get(coachingShowHideStatus))
        {
            systemEnabled = false;
            AIS_LOG_DEBUG("Ins:%d  Ena:%d  Temp:%d  Time:%d", coachingShowHideStatus.coachingEnabled, coachingShowHideStatus.coachingInstalled, coachingShowHideStatus.coachingTempInstalled, coachingShowHideStatus.coachingTempTime);
            if (coachingShowHideStatus.coachingEnabled && coachingShowHideStatus.coachingInstalled && coachingShowHideStatus.coachingTempInstalled && (0 < coachingShowHideStatus.coachingTempTime))
            {
                systemEnabled = true;
            }
        }

        CoachingSummaryData coachingSummaryData;
        while (m_pCoachingSummaryDataInput->get(coachingSummaryData))
        {
            AIS_LOG_DEBUG("per:%d  req:%d  snooze:%d  badge:%d", coachingSummaryData.getProgressIndicatorPercentageInt(), coachingSummaryData.displayRequired, coachingSummaryData.tipAutoEnableTimeSeconds, coachingSummaryData.countOfBadges);

            if (systemEnabled)
            {
                progressIndicatorPercentage = coachingSummaryData.getProgressIndicatorPercentageInt();
                displayRequired             = coachingSummaryData.displayRequired;
                countOfBadges               = coachingSummaryData.countOfBadges;
            }

            // update only on change so DatalinkManager-callback isn't triggered by internal writes
            if (m_snoozeTime != static_cast<uint16_t>(SecondsToHours(coachingSummaryData.tipAutoEnableTimeSeconds) + 0.5))
            {
                m_snoozeTime = static_cast<uint16_t>(SecondsToHours(coachingSummaryData.tipAutoEnableTimeSeconds) + 0.5);
            }

            m_datalinkManager.setValueRaw(BMI_CDL_PID_OPERATOR_COACHING_TIP_PROGRESS_INDICATOR_PERCENTAGE, 
                                            datalink::ParameterType::PID, 
                                            static_cast<uint32_t>(progressIndicatorPercentage));
            m_datalinkManager.setValueRaw(BMI_CDL_PID_OPERATOR_COACHING_TIP_SUMMARY_DISPLAY_REQUIREMENT_STATUS, 
                                            datalink::ParameterType::PID, 
                                            static_cast<uint32_t>(displayRequired));
            m_datalinkManager.setValueRaw(BMI_CDL_PID_OPERATOR_COACHING_TIP_INFO_CHANGE_COUNT_SINCE_LAST_VIEW, 
                                            datalink::ParameterType::PID, 
                                            static_cast<uint32_t>(countOfBadges));
        }

        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Called during cleanup of the parent task.
    ///////////////////////////////////////////////////////////////////////////////
    void cleanup() override
    {
    }


private:
    DatalinkManagerInterface& m_datalinkManager;
    CoachingSummaryDataInput* m_pCoachingSummaryDataInput;
    CoachingShowHideStatusInput* m_pCoachingShowHideStatusInput;
    uint16_t m_snoozeTime = 0xFFF4;   // DSI-20
    bool systemEnabled = false; // default to false
};

#endif
