///////////////////////////////////////////////////////////////////////////////
/// @file RosOutputInterface.h
/// @brief DDS-backed drop-in replacement for
///        interfaces::baseTypes::OutputInterface<T>. Matches its publish()
///        call signature exactly so call sites in JobMgr/WeighApp don't
///        change -- only the member's declared type does.
///
/// Header-only, same reason the real SCS OutputInterface<T> is header-only:
/// it's a template, instantiated once per real channel message type.
///
///   - One shared rclcpp::Node per app , each RosOutputInterface<T> just
///     creates its own publisher on that shared node.
///////////////////////////////////////////////////////////////////////////////
 
#ifndef _RosOutputInterface_h_
#define _RosOutputInterface_h_
 
#include <string>
 
#include "rclcpp/rclcpp.hpp"
 
namespace ros2_wrapper
{
 
template<typename T>
class RosOutputInterface
{
public:
    RosOutputInterface(const rclcpp::Node::SharedPtr& node, const std::string& topicName, size_t qosDepth = 1)
        : topicName_(topicName)
    {
        auto qos = rclcpp::QoS(rclcpp::KeepLast(1)).best_effort().durability_volatile();
        publisher_ = node->create_publisher<T>(topicName, qos);
    }
 
    // Same, with a full QoS profile, e.g. rclcpp::QoS(1).transient_local() for one-shot
    // data that a subscriber starting later must still receive.
    RosOutputInterface(const rclcpp::Node::SharedPtr& node, const std::string& topicName, const rclcpp::QoS& qos)
        : topicName_(topicName)
    {
        publisher_ = node->create_publisher<T>(topicName, qos);
    }
    // Matches interfaces::baseTypes::OutputInterface<T>::publish(const T&) --
    // same call syntax as the real SCS object it replaces.
    bool publish(const T& data)
    {
        try
        {
            publisher_->publish(data);
            return true;
        }
        catch (const std::exception&)
        {
            // Mirrors the real OutputInterface<T>::publish()
            return false;
        }
    }
 
    const std::string& topicName() const { return topicName_; }
 
private:
    typename rclcpp::Publisher<T>::SharedPtr publisher_;
    std::string topicName_;
};
 
} // namespace ros2_wrapper
 
#endif // _RosOutputInterface_h_