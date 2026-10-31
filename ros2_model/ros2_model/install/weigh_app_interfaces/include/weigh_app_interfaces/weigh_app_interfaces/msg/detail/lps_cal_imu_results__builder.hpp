// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/LpsCalIMUResults.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_cal_imu_results.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_CAL_IMU_RESULTS__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_CAL_IMU_RESULTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/lps_cal_imu_results__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsCalIMUResults_empty_slow_lumped_weight_final
{
public:
  explicit Init_LpsCalIMUResults_empty_slow_lumped_weight_final(::weigh_app_interfaces::msg::LpsCalIMUResults & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::LpsCalIMUResults empty_slow_lumped_weight_final(::weigh_app_interfaces::msg::LpsCalIMUResults::_empty_slow_lumped_weight_final_type arg)
  {
    msg_.empty_slow_lumped_weight_final = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

class Init_LpsCalIMUResults_full_slow_lumped_weight_final
{
public:
  explicit Init_LpsCalIMUResults_full_slow_lumped_weight_final(::weigh_app_interfaces::msg::LpsCalIMUResults & msg)
  : msg_(msg)
  {}
  Init_LpsCalIMUResults_empty_slow_lumped_weight_final full_slow_lumped_weight_final(::weigh_app_interfaces::msg::LpsCalIMUResults::_full_slow_lumped_weight_final_type arg)
  {
    msg_.full_slow_lumped_weight_final = std::move(arg);
    return Init_LpsCalIMUResults_empty_slow_lumped_weight_final(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

class Init_LpsCalIMUResults_empty_slow_imu_offset_final
{
public:
  explicit Init_LpsCalIMUResults_empty_slow_imu_offset_final(::weigh_app_interfaces::msg::LpsCalIMUResults & msg)
  : msg_(msg)
  {}
  Init_LpsCalIMUResults_full_slow_lumped_weight_final empty_slow_imu_offset_final(::weigh_app_interfaces::msg::LpsCalIMUResults::_empty_slow_imu_offset_final_type arg)
  {
    msg_.empty_slow_imu_offset_final = std::move(arg);
    return Init_LpsCalIMUResults_full_slow_lumped_weight_final(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

class Init_LpsCalIMUResults_full_slow_imu_offset_final
{
public:
  explicit Init_LpsCalIMUResults_full_slow_imu_offset_final(::weigh_app_interfaces::msg::LpsCalIMUResults & msg)
  : msg_(msg)
  {}
  Init_LpsCalIMUResults_empty_slow_imu_offset_final full_slow_imu_offset_final(::weigh_app_interfaces::msg::LpsCalIMUResults::_full_slow_imu_offset_final_type arg)
  {
    msg_.full_slow_imu_offset_final = std::move(arg);
    return Init_LpsCalIMUResults_empty_slow_imu_offset_final(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

class Init_LpsCalIMUResults_empty_slow_lumped_weight_temp3
{
public:
  explicit Init_LpsCalIMUResults_empty_slow_lumped_weight_temp3(::weigh_app_interfaces::msg::LpsCalIMUResults & msg)
  : msg_(msg)
  {}
  Init_LpsCalIMUResults_full_slow_imu_offset_final empty_slow_lumped_weight_temp3(::weigh_app_interfaces::msg::LpsCalIMUResults::_empty_slow_lumped_weight_temp3_type arg)
  {
    msg_.empty_slow_lumped_weight_temp3 = std::move(arg);
    return Init_LpsCalIMUResults_full_slow_imu_offset_final(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

class Init_LpsCalIMUResults_empty_slow_lumped_weight_temp2
{
public:
  explicit Init_LpsCalIMUResults_empty_slow_lumped_weight_temp2(::weigh_app_interfaces::msg::LpsCalIMUResults & msg)
  : msg_(msg)
  {}
  Init_LpsCalIMUResults_empty_slow_lumped_weight_temp3 empty_slow_lumped_weight_temp2(::weigh_app_interfaces::msg::LpsCalIMUResults::_empty_slow_lumped_weight_temp2_type arg)
  {
    msg_.empty_slow_lumped_weight_temp2 = std::move(arg);
    return Init_LpsCalIMUResults_empty_slow_lumped_weight_temp3(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

class Init_LpsCalIMUResults_empty_slow_lumped_weight_temp1
{
public:
  explicit Init_LpsCalIMUResults_empty_slow_lumped_weight_temp1(::weigh_app_interfaces::msg::LpsCalIMUResults & msg)
  : msg_(msg)
  {}
  Init_LpsCalIMUResults_empty_slow_lumped_weight_temp2 empty_slow_lumped_weight_temp1(::weigh_app_interfaces::msg::LpsCalIMUResults::_empty_slow_lumped_weight_temp1_type arg)
  {
    msg_.empty_slow_lumped_weight_temp1 = std::move(arg);
    return Init_LpsCalIMUResults_empty_slow_lumped_weight_temp2(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

class Init_LpsCalIMUResults_empty_slow_imu_offset_temp3
{
public:
  explicit Init_LpsCalIMUResults_empty_slow_imu_offset_temp3(::weigh_app_interfaces::msg::LpsCalIMUResults & msg)
  : msg_(msg)
  {}
  Init_LpsCalIMUResults_empty_slow_lumped_weight_temp1 empty_slow_imu_offset_temp3(::weigh_app_interfaces::msg::LpsCalIMUResults::_empty_slow_imu_offset_temp3_type arg)
  {
    msg_.empty_slow_imu_offset_temp3 = std::move(arg);
    return Init_LpsCalIMUResults_empty_slow_lumped_weight_temp1(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

class Init_LpsCalIMUResults_empty_slow_imu_offset_temp2
{
public:
  explicit Init_LpsCalIMUResults_empty_slow_imu_offset_temp2(::weigh_app_interfaces::msg::LpsCalIMUResults & msg)
  : msg_(msg)
  {}
  Init_LpsCalIMUResults_empty_slow_imu_offset_temp3 empty_slow_imu_offset_temp2(::weigh_app_interfaces::msg::LpsCalIMUResults::_empty_slow_imu_offset_temp2_type arg)
  {
    msg_.empty_slow_imu_offset_temp2 = std::move(arg);
    return Init_LpsCalIMUResults_empty_slow_imu_offset_temp3(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

class Init_LpsCalIMUResults_empty_slow_imu_offset_temp1
{
public:
  explicit Init_LpsCalIMUResults_empty_slow_imu_offset_temp1(::weigh_app_interfaces::msg::LpsCalIMUResults & msg)
  : msg_(msg)
  {}
  Init_LpsCalIMUResults_empty_slow_imu_offset_temp2 empty_slow_imu_offset_temp1(::weigh_app_interfaces::msg::LpsCalIMUResults::_empty_slow_imu_offset_temp1_type arg)
  {
    msg_.empty_slow_imu_offset_temp1 = std::move(arg);
    return Init_LpsCalIMUResults_empty_slow_imu_offset_temp2(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

class Init_LpsCalIMUResults_full_slow_lumped_weight_temp3
{
public:
  explicit Init_LpsCalIMUResults_full_slow_lumped_weight_temp3(::weigh_app_interfaces::msg::LpsCalIMUResults & msg)
  : msg_(msg)
  {}
  Init_LpsCalIMUResults_empty_slow_imu_offset_temp1 full_slow_lumped_weight_temp3(::weigh_app_interfaces::msg::LpsCalIMUResults::_full_slow_lumped_weight_temp3_type arg)
  {
    msg_.full_slow_lumped_weight_temp3 = std::move(arg);
    return Init_LpsCalIMUResults_empty_slow_imu_offset_temp1(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

class Init_LpsCalIMUResults_full_slow_lumped_weight_temp2
{
public:
  explicit Init_LpsCalIMUResults_full_slow_lumped_weight_temp2(::weigh_app_interfaces::msg::LpsCalIMUResults & msg)
  : msg_(msg)
  {}
  Init_LpsCalIMUResults_full_slow_lumped_weight_temp3 full_slow_lumped_weight_temp2(::weigh_app_interfaces::msg::LpsCalIMUResults::_full_slow_lumped_weight_temp2_type arg)
  {
    msg_.full_slow_lumped_weight_temp2 = std::move(arg);
    return Init_LpsCalIMUResults_full_slow_lumped_weight_temp3(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

class Init_LpsCalIMUResults_full_slow_lumped_weight_temp1
{
public:
  explicit Init_LpsCalIMUResults_full_slow_lumped_weight_temp1(::weigh_app_interfaces::msg::LpsCalIMUResults & msg)
  : msg_(msg)
  {}
  Init_LpsCalIMUResults_full_slow_lumped_weight_temp2 full_slow_lumped_weight_temp1(::weigh_app_interfaces::msg::LpsCalIMUResults::_full_slow_lumped_weight_temp1_type arg)
  {
    msg_.full_slow_lumped_weight_temp1 = std::move(arg);
    return Init_LpsCalIMUResults_full_slow_lumped_weight_temp2(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

class Init_LpsCalIMUResults_full_slow_imu_offset_temp3
{
public:
  explicit Init_LpsCalIMUResults_full_slow_imu_offset_temp3(::weigh_app_interfaces::msg::LpsCalIMUResults & msg)
  : msg_(msg)
  {}
  Init_LpsCalIMUResults_full_slow_lumped_weight_temp1 full_slow_imu_offset_temp3(::weigh_app_interfaces::msg::LpsCalIMUResults::_full_slow_imu_offset_temp3_type arg)
  {
    msg_.full_slow_imu_offset_temp3 = std::move(arg);
    return Init_LpsCalIMUResults_full_slow_lumped_weight_temp1(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

class Init_LpsCalIMUResults_full_slow_imu_offset_temp2
{
public:
  explicit Init_LpsCalIMUResults_full_slow_imu_offset_temp2(::weigh_app_interfaces::msg::LpsCalIMUResults & msg)
  : msg_(msg)
  {}
  Init_LpsCalIMUResults_full_slow_imu_offset_temp3 full_slow_imu_offset_temp2(::weigh_app_interfaces::msg::LpsCalIMUResults::_full_slow_imu_offset_temp2_type arg)
  {
    msg_.full_slow_imu_offset_temp2 = std::move(arg);
    return Init_LpsCalIMUResults_full_slow_imu_offset_temp3(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

class Init_LpsCalIMUResults_full_slow_imu_offset_temp1
{
public:
  Init_LpsCalIMUResults_full_slow_imu_offset_temp1()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsCalIMUResults_full_slow_imu_offset_temp2 full_slow_imu_offset_temp1(::weigh_app_interfaces::msg::LpsCalIMUResults::_full_slow_imu_offset_temp1_type arg)
  {
    msg_.full_slow_imu_offset_temp1 = std::move(arg);
    return Init_LpsCalIMUResults_full_slow_imu_offset_temp2(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsCalIMUResults msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::LpsCalIMUResults>()
{
  return weigh_app_interfaces::msg::builder::Init_LpsCalIMUResults_full_slow_imu_offset_temp1();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_CAL_IMU_RESULTS__BUILDER_HPP_
