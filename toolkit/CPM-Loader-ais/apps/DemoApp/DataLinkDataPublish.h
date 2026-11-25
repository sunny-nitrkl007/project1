#ifndef DATALINKDATAPUBLISH_H_
#define DATALINKDATAPUBLISH_H_

#include <chrono>
#include <cstdint>
#include <deque>
#include <string>

#include "Ros2TaskWrapper.h"
#include <demo_app_interfaces/msg/demo_app_cycle.hpp>
#include <demo_app_interfaces/msg/demo_app_health.hpp>
#include <demo_app_interfaces/msg/demo_app_request_batch.hpp>

class DemoApp: public ros2_wrapper::Ros2TaskWrapper
{
public:
    DemoApp( const std::string& taskName );
    ~DemoApp() override;

    bool initialize() override;
    bool executive() override;
    void cleanup() override;
    void startExecutiveTimer() override;

private:
    using Clock = std::chrono::steady_clock;
    using RequestBatch = demo_app_interfaces::msg::DemoAppRequestBatch;
    using Cycle = demo_app_interfaces::msg::DemoAppCycle;
    using Health = demo_app_interfaces::msg::DemoAppHealth;

    rclcpp::Subscription<RequestBatch>::SharedPtr requestSubscription_;
    rclcpp::Publisher<Cycle>::SharedPtr cyclePublisher_;
    rclcpp::Publisher<Health>::SharedPtr healthPublisher_;
    rclcpp::TimerBase::SharedPtr healthTimer_;
    // Subscription and executive run on the same single-threaded executor.
    // Do not silently drop command batches until AIS overflow policy is verified.
    std::deque<RequestBatch> requests_;
    std::string sessionId_;
    std::string host_;
    std::string loggerThreshold_;
    uint64_t sequence_ = 0;
    uint64_t healthSequence_ = 0;
    uint64_t lateCycleCount_ = 0;
    uint64_t lastHealthCycleCount_ = 0;
    uint8_t state_ = Health::INITIALIZING;
    bool initialized_ = false;
    Clock::time_point lastCycleStart_;
    Clock::time_point lastHealthTime_;
    double cycleRate_ = 0.0;
    double longestCycle_ = 0.0;
    double longestRecentCycle_ = 0.0;

    uint32_t hyd_temp_value = 60;
    uint32_t sea_level_2 = 16;
    uint32_t production_measurement = 12;
    uint32_t total_fuel_used_ = 80000;
    uint32_t fuelPeriodCount_ = 12;



    float liftposition_;
    float liftposition_rate_;
    float tiltposition_;
    float tiltposition_rate_;
    float payload_;
    float payload_rate_;

    void CaptureDataLinkData(Cycle& cycle);
    void ReadDemoAppRosIn();
    void ReadPWM_API(weigh_app_interfaces::msg::DemoAppTxChannel& tx);
    void PublishHealth();

    void updateTotalFuel() {
        ++fuelPeriodCount_;
        if (fuelPeriodCount_ >= 12) {
            fuelPeriodCount_ = 0;
            total_fuel_used_ = total_fuel_used_ + 1;
        }
    }
};



#endif
