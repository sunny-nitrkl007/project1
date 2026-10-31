// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyDataChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_data_channel.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_CHANNEL__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_data_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaNvmCalOnTheFlyDataChannel_lps_sa_nvm_calibration_data_on_the_fly
{
public:
  Init_LpsSaNvmCalOnTheFlyDataChannel_lps_sa_nvm_calibration_data_on_the_fly()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel lps_sa_nvm_calibration_data_on_the_fly(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel::_lps_sa_nvm_calibration_data_on_the_fly_type arg)
  {
    msg_.lps_sa_nvm_calibration_data_on_the_fly = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel>()
{
  return weigh_app_interfaces::msg::builder::Init_LpsSaNvmCalOnTheFlyDataChannel_lps_sa_nvm_calibration_data_on_the_fly();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_CHANNEL__BUILDER_HPP_
