/*******************************************************************************
** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LEDOutput.cpp
DESCRIPTION:
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include "SwitchInputApp.h"
#include "SwitchInputDebounce.h"
#include <stdlib.h>
#include <stdio.h>
#include <climits>
#include <cmath>
#include <unistd.h>

/* WARNING: reading all 4 switch inputs takes longer than 20ms(loop time), so reading
 * only Store switch for right now*/
/*#define STG1_FILE_LOC     "/sys/class/tty/ttyS2/switch/sw_stg_1"
#define STG2_FILE_LOC     "/sys/class/tty/ttyS2/switch/sw_stg_2"
#define STG3_FILE_LOC     "/sys/class/tty/ttyS2/switch/sw_stg_3"*/
#define STG4_FILE_LOC     "/sys/class/tty/ttyS2/switch/sw_stg_4"





/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
int main(int argc, char** argv)
{
    return ros2_wrapper::Ros2TaskWrapper::run<SwitchInput>(argc, argv);
}

/******************************************************************************
FUNCTION NAME:SwitchInput constructor
DESCRIPTION: SwitchInput constructor for initializes an instance of its class     
PARAMETER DESCRIPTION:  task name is passed
RETURN VALUE:  No return Value form constructor           
*******************************************************************************/
SwitchInput::SwitchInput(const std::string& taskName) :
    Ros2TaskWrapper(taskName),
    cycleRateHz_(50.0),
    heartbeatPeriodSec_(1.0),
    loggerPriority_(31),
    stopHealth_(false),
    taskState_(switch_input::Initializing),
    healthTracker_(steadySeconds()),
    haveExecutiveEnd_(false),
    openDebounceCount_(0),
    closedDebounceCount_(0),
    counts_{0, 0, 0, 0},
    previousStates_{STG::UNKNOWN, STG::UNKNOWN, STG::UNKNOWN, STG::UNKNOWN},
    debouncedStates_(),
    publishState_(true),
    switchInputScsOutput_(nullptr)
{
    for (auto& state : debouncedStates_.stg_values) {
        state.value = STG::UNKNOWN;
    }
}

/******************************************************************************
FUNCTION NAME:SwitchInput destructorl
DESCRIPTION: SwitchInput destructor for deallocating an instance of its class
PARAMETER DESCRIPTION: No parameter
RETURN VALUE:   No return Value form destructor           
*******************************************************************************/
SwitchInput::~SwitchInput()
{
    cleanup();
}

/******************************************************************************
FUNCTION NAME:initialize
DESCRIPTION: SCS channel and PWM input buffer library is initialize
PARAMETER DESCRIPTION:  No parameter
RETURN VALUE:  Boolean           
*******************************************************************************/
bool SwitchInput::initialize()
{
    const auto threshold = declare_parameter<std::string>("logger_threshold", "error");
    ROS2Logger::Instance().SetFeatureName(get_name());
    ROS2Logger::Instance().SetLogLevel(threshold);
    const std::string levels[] = {"emerg", "fatal", "alert", "crit", "error",
                                  "warn", "notice", "info", "debug"};
    bool validThreshold = false;
    for (unsigned int i = 0; i < 9; ++i) {
        if (threshold == levels[i]) {
            loggerPriority_ = (1u << (i + 1)) - 1;
            validThreshold = true;
        }
    }
    if (!validThreshold) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Invalid logger_threshold");
        return false;
    }
    // ROS2Logger supports five levels; preserve the intermediate AIS threshold mask.
    if (threshold == "emerg") ROS2Logger::Instance().SetLogLevel("fatal");
    if (threshold == "alert" || threshold == "crit") ROS2Logger::Instance().SetLogLevel("error");
    if (threshold == "notice") ROS2Logger::Instance().SetLogLevel("warn");

    cycleRateHz_ = declare_parameter<double>("cycle_rate_hz", 50.0);
    heartbeatPeriodSec_ = declare_parameter<double>("heartbeat_period_sec", 1.0);
    const auto debounce = declare_parameter<int64_t>("debounce_count", 5);
    const auto open = declare_parameter<int64_t>("open_debounce_count", debounce);
    const auto closed = declare_parameter<int64_t>("closed_debounce_count", debounce);
    if (!std::isfinite(cycleRateHz_) || cycleRateHz_ <= 0.0 ||
        !std::isfinite(heartbeatPeriodSec_) || heartbeatPeriodSec_ <= 0.0 ||
        1.0 / cycleRateHz_ < 1e-9 || open < INT_MIN || open > INT_MAX ||
        closed < INT_MIN || closed > INT_MAX) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Invalid timing or debounce parameters");
        return false;
    }
    openDebounceCount_ = static_cast<int>(open);
    closedDebounceCount_ = static_cast<int>(closed);
    const bool autonomy = declare_parameter<bool>("autonomy_ecm", false);
    const auto scheduler = declare_parameter<std::string>("scheduler", autonomy ? "SCHED_RR" : "SCHED_OTHER");
    int64_t priority = declare_parameter<int64_t>("scheduler_priority", autonomy ? 1 : 0);
    if (scheduler == "SCHED_OTHER") priority = 0;
    if ((scheduler != "SCHED_RR" && scheduler != "SCHED_FIFO" && scheduler != "SCHED_OTHER") ||
        (scheduler != "SCHED_OTHER" && (priority < 1 || priority > 99))) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Invalid scheduler parameters");
        return false;
    }
    // AIS logs scheduling failures but continues initialization.
    applyRealtimeScheduling(scheduler, static_cast<int>(priority));
    switchInputScsOutput_ = create_publisher<job_mgr_interfaces::msg::SwitchInputScs>("switch_input_scs", 10);
    healthOutput_ = create_publisher<cpm_common_interfaces::msg::ProcessHealth>("process_health", 10);
    char host[256] = {};
    if (gethostname(host, sizeof(host) - 1) != 0) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Cannot determine host name");
        return false;
    }
    host_ = host;
    RCLCPP_INFO(ROS2Logger::Instance().GetLogger(), "OpenDebounceCount = %d", openDebounceCount_);
    RCLCPP_INFO(ROS2Logger::Instance().GetLogger(), "ClosedDebounceCount = %d", closedDebounceCount_);
    return true;
}

/******************************************************************************
FUNCTION NAME:executive
DESCRIPTION:   executive function is required to publish the data to SCS channel
PARAMETER DESCRIPTION: No parameter
RETURN VALUE: Boolean            
*******************************************************************************/
bool SwitchInput::executive()
{
    const auto start = Clock::now();
    {
        std::lock_guard<std::mutex> lock(healthMutex_);
        if (haveExecutiveEnd_) {
            healthTracker_.waited(std::chrono::duration<double>(start - lastExecutiveEnd_).count());
        }
    }
    /*
     * WARNING: reading all 4 switch inputs takes longer than 20ms(loop time), so reading
     * only Store switch for right now
     */
    int currentStates[NO_OF_STG_INPUTS] = {STG::UNKNOWN, STG::UNKNOWN, STG::UNKNOWN, STG::UNKNOWN};

    { // Read switch inputs
        FILE* fh = fopen(STG4_FILE_LOC, "r");
        if (nullptr != fh) {
            if (!fscanf(fh, "%d", &currentStates[3])) {
                RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Failed to read %s", STG4_FILE_LOC);
            }
            fclose(fh);
        }
    }

    switch_input::debounce(currentStates, counts_, previousStates_, debouncedStates_,
                           publishState_, openDebounceCount_, closedDebounceCount_);

    if ((publishState_) && (nullptr != switchInputScsOutput_)) {
        RCLCPP_INFO(ROS2Logger::Instance().GetLogger(), "Publishing switch states: %d, %d, %d, %d",
                debouncedStates_.stg_values[0].value, debouncedStates_.stg_values[1].value,
                debouncedStates_.stg_values[2].value, debouncedStates_.stg_values[3].value);
        try {
            switchInputScsOutput_->publish(debouncedStates_);
        }
        catch (const std::exception& error) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Switch publish failed: %s", error.what());
        }
        publishState_ = false;
    }

    const auto end = Clock::now();
    {
        std::lock_guard<std::mutex> lock(healthMutex_);
        healthTracker_.complete(std::chrono::duration<double>(end.time_since_epoch()).count(),
                                std::chrono::duration<double>(end - start).count(), 1.0 / cycleRateHz_);
        lastExecutiveEnd_ = end;
        haveExecutiveEnd_ = true;
    }
    return true;  
}

/******************************************************************************
FUNCTION NAME:cleanup
DESCRIPTION:      
PARAMETER DESCRIPTION:                        
RETURN VALUE:void             
*******************************************************************************/
void SwitchInput::cleanup( )
{
    if (executiveTimer_) {
        executiveTimer_->cancel();
        executiveTimer_.reset();
    }
    {
        std::lock_guard<std::mutex> lock(healthMutex_);
        taskState_ = switch_input::ShuttingDown;
        stopHealth_ = true;
    }
    healthWakeup_.notify_all();
    if (healthThread_.joinable()) {
        healthThread_.join();
        publishHealth();
    }
    RCLCPP_INFO(ROS2Logger::Instance().GetLogger(), "SwitchInput::cleanup");
}

double SwitchInput::steadySeconds()
{
    return std::chrono::duration<double>(Clock::now().time_since_epoch()).count();
}

void SwitchInput::startExecutiveTimer()
{
    {
        std::lock_guard<std::mutex> lock(healthMutex_);
        healthTracker_ = switch_input::HealthTracker(steadySeconds());
        taskState_ = switch_input::ExecutiveRunning;
    }
    healthThread_ = std::thread(&SwitchInput::healthThreadBody, this);
    createExecutiveTimer(cycleRateHz_);
    executive();
}

void SwitchInput::healthThreadBody()
{
    std::unique_lock<std::mutex> lock(healthMutex_);
    while (!stopHealth_) {
        if (healthWakeup_.wait_for(lock, std::chrono::duration<double>(heartbeatPeriodSec_),
                                 [this]() { return stopHealth_; })) {
            break;
        }
        lock.unlock();
        publishHealth();
        lock.lock();
    }
}

void SwitchInput::publishHealth()
{
    cpm_common_interfaces::msg::ProcessHealth report;
    {
        std::lock_guard<std::mutex> lock(healthMutex_);
        const auto statistics = healthTracker_.report(steadySeconds());
        report.cycle_rate_hz = statistics.rate;
        report.recent_executive_cycle_rate_hz = statistics.recentRate;
        report.longest_executive_thread_cycle_sec = statistics.lifetimeMaximum;
        report.longest_recent_executive_thread_cycle_sec = statistics.recentMaximum;
        report.total_executive_cycle_count = statistics.cycles;
        report.total_executive_late_cycle_count = statistics.late;
        report.total_executive_sleep_time_sec = statistics.sleep;
        report.intended_cycle_rate_hz = taskState_ == switch_input::Initializing ? -1.0 : cycleRateHz_;
        report.task_state = taskState_;
    }
    report.source = get_name();
    report.host = host_;
    report.process_id = static_cast<int32_t>(getpid());
    report.logger_priority = loggerPriority_;
    report.origination_time_sec = std::chrono::duration<double>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    report.event_driven_message_process_rate_hz = 0.0;
    report.recent_event_driven_cycle_rate_hz = 0.0;
    report.longest_event_driven_cycle_sec = -1.0;
    report.longest_recent_event_driven_cycle_sec = 0.0;
    try {
        if (healthOutput_) healthOutput_->publish(report);
    }
    catch (const std::exception& error) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Health publish failed: %s", error.what());
    }
}
