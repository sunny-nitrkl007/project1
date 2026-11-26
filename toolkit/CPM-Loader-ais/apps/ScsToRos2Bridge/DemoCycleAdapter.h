#ifndef DEMOCYCLEADAPTER_H
#define DEMOCYCLEADAPTER_H

#include <array>
#include <set>
#include <string>
#include <interfaces/DataLinkData/InterfaceTypes.h>
#include <interfaces/DemoAppReqstChannel/InterfaceTypes.h>
#include <interfaces/DemoAppTxChannel/InterfaceTypes.h>
#include <demo_app_interfaces/msg/demo_app_cycle.hpp>
#include <demo_app_interfaces/msg/demo_app_request_batch.hpp>
#include <rclcpp/rclcpp.hpp>

class DemoCycleAdapter
{
public:
    bool initialize(const rclcpp::Node::SharedPtr& node);
    bool executive();

private:
    bool initializeDataLinkData();
    void receive(const demo_app_interfaces::msg::DemoAppCycle& cycle,
                 const rclcpp::MessageInfo& info);
    bool accept(const demo_app_interfaces::msg::DemoAppCycle& cycle,
                const rclcpp::MessageInfo& info);
    static demo_app_interfaces::msg::DemoAppRequestBatch convertRequests(const DemoAppReqstChannel& scs);
    static DemoAppTxChannel convertTx(const weigh_app_interfaces::msg::DemoAppTxChannel& ros);

    rclcpp::Node::SharedPtr node_;
    rclcpp::Publisher<demo_app_interfaces::msg::DemoAppRequestBatch>::SharedPtr requestsOut_;
    rclcpp::Subscription<demo_app_interfaces::msg::DemoAppCycle>::SharedPtr cycleIn_;
    DemoAppReqstChannelInput* requestsIn_ = nullptr;
    DemoAppTxChannelOutput* txOut_ = nullptr;
    DataLinkDataOutput* dataOut_ = nullptr;
    DataLinkData data_;
    std::array<DataLinkParam, 6> params_;
    std::string session_;
    std::set<std::string> retiredSessions_;
    std::array<uint8_t, RMW_GID_STORAGE_SIZE> producer_{};
    uint64_t sequence_ = 0;
    bool failed_ = false;
};

#endif
