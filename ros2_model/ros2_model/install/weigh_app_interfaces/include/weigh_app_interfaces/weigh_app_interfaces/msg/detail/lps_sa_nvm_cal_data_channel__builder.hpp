// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalDataChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_data_channel.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_data_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaNvmCalDataChannel_imu_cal_results
{
public:
  explicit Init_LpsSaNvmCalDataChannel_imu_cal_results(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannel & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannel imu_cal_results(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannel::_imu_cal_results_type arg)
  {
    msg_.imu_cal_results = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannel msg_;
};

class Init_LpsSaNvmCalDataChannel_lps_sa_nvm_calibration_data_debug
{
public:
  explicit Init_LpsSaNvmCalDataChannel_lps_sa_nvm_calibration_data_debug(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannel_imu_cal_results lps_sa_nvm_calibration_data_debug(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannel::_lps_sa_nvm_calibration_data_debug_type arg)
  {
    msg_.lps_sa_nvm_calibration_data_debug = std::move(arg);
    return Init_LpsSaNvmCalDataChannel_imu_cal_results(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannel msg_;
};

class Init_LpsSaNvmCalDataChannel_lps_sa_nvm_calibration_data_main
{
public:
  Init_LpsSaNvmCalDataChannel_lps_sa_nvm_calibration_data_main()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaNvmCalDataChannel_lps_sa_nvm_calibration_data_debug lps_sa_nvm_calibration_data_main(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannel::_lps_sa_nvm_calibration_data_main_type arg)
  {
    msg_.lps_sa_nvm_calibration_data_main = std::move(arg);
    return Init_LpsSaNvmCalDataChannel_lps_sa_nvm_calibration_data_debug(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::LpsSaNvmCalDataChannel>()
{
  return weigh_app_interfaces::msg::builder::Init_LpsSaNvmCalDataChannel_lps_sa_nvm_calibration_data_main();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL__BUILDER_HPP_
