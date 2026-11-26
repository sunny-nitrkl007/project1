#ifndef DEMOHEALTHADAPTER_H
#define DEMOHEALTHADAPTER_H

#include <array>
#include <chrono>
#include <set>
#include <string>
#include <ais/interfaces/ProcessHealth/InterfaceTypes.h>
#include <demo_app_interfaces/msg/demo_app_health.hpp>
#include <rclcpp/rclcpp.hpp>

class DemoHealthAdapter
{
public:
    bool initialize(const rclcpp::Node::SharedPtr& node);
    bool executive();
    void cleanup() noexcept;

private:
    using Health = demo_app_interfaces::msg::DemoAppHealth;
    using Clock = std::chrono::steady_clock;
    void receive(const Health& health, const rclcpp::MessageInfo& info);
    bool accept(const Health& health, const rclcpp::MessageInfo& info);
    bool publish(const Health& health, bool stale);
    void invalidate();
    static std::string incarnation(int32_t pid);

    rclcpp::Node::SharedPtr node_;
    rclcpp::Subscription<Health>::SharedPtr input_;
    ProcessHealthOutput* output_ = nullptr;
    std::string host_;
    std::string executable_;
    std::string incarnation_;
    std::set<std::string> retiredSessions_;
    std::array<uint8_t, RMW_GID_STORAGE_SIZE> producer_{};
    Health last_;
    Clock::time_point received_;
    int64_t sourceTimestamp_ = 0;
    bool active_ = false;
    bool stopped_ = false;
};

#endif
