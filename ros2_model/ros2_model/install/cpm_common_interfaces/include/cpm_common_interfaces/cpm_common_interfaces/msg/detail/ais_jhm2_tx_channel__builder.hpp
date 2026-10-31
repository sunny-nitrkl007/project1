// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/AisJhm2TxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/ais_jhm2_tx_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/ais_jhm2_tx_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_AisJhm2TxChannel_tipoff_weight_adjust_data
{
public:
  explicit Init_AisJhm2TxChannel_tipoff_weight_adjust_data(::cpm_common_interfaces::msg::AisJhm2TxChannel & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::AisJhm2TxChannel tipoff_weight_adjust_data(::cpm_common_interfaces::msg::AisJhm2TxChannel::_tipoff_weight_adjust_data_type arg)
  {
    msg_.tipoff_weight_adjust_data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::AisJhm2TxChannel msg_;
};

class Init_AisJhm2TxChannel_simplecal_data
{
public:
  Init_AisJhm2TxChannel_simplecal_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AisJhm2TxChannel_tipoff_weight_adjust_data simplecal_data(::cpm_common_interfaces::msg::AisJhm2TxChannel::_simplecal_data_type arg)
  {
    msg_.simplecal_data = std::move(arg);
    return Init_AisJhm2TxChannel_tipoff_weight_adjust_data(msg_);
  }

private:
  ::cpm_common_interfaces::msg::AisJhm2TxChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::AisJhm2TxChannel>()
{
  return cpm_common_interfaces::msg::builder::Init_AisJhm2TxChannel_simplecal_data();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__BUILDER_HPP_
