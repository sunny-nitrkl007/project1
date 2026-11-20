/*******************************************************************************
** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: SwitchInputApp.h
DESCRIPTION:
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#pragma once

#include "Ros2TaskWrapper.h"
#include "SwitchInputHealth.h"
#include <job_mgr_interfaces/msg/switch_input_scs.hpp>
#include <cpm_common_interfaces/msg/process_health.hpp>
#include <condition_variable>
#include <mutex>
#include <thread>

/*******************************************************************************
** -- #defines --
*******************************************************************************/

 

class SwitchInput: public ros2_wrapper::Ros2TaskWrapper
{
public:
    SwitchInput( const std::string& taskName );
    virtual ~SwitchInput( );
    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );
    void startExecutiveTimer() override;

protected:
private:
    static constexpr int NO_OF_STG_INPUTS = 4;
    enum STG { OPEN = 0, CLOSED = 1, UNKNOWN = 2 };
    using Clock = std::chrono::steady_clock;
    static double steadySeconds();
    void healthThreadBody();
    void publishHealth();

    double cycleRateHz_;
    double heartbeatPeriodSec_;
    uint32_t loggerPriority_;
    std::string host_;
    std::mutex healthMutex_;
    std::condition_variable healthWakeup_;
    std::thread healthThread_;
    bool stopHealth_;
    int taskState_;
    switch_input::HealthTracker healthTracker_;
    Clock::time_point lastExecutiveEnd_;
    bool haveExecutiveEnd_;
    rclcpp::Publisher<cpm_common_interfaces::msg::ProcessHealth>::SharedPtr healthOutput_;

    int openDebounceCount_;
    int closedDebounceCount_;
    int counts_[NO_OF_STG_INPUTS];
    int previousStates_[NO_OF_STG_INPUTS];
    job_mgr_interfaces::msg::SwitchInputScs debouncedStates_;
    bool publishState_;
    rclcpp::Publisher<job_mgr_interfaces::msg::SwitchInputScs>::SharedPtr switchInputScsOutput_;
};
