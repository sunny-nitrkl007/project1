// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/ShmClockInput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/shm_clock_input.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__SHM_CLOCK_INPUT__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__SHM_CLOCK_INPUT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/shm_clock_input__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_ShmClockInput_tzone_info
{
public:
  explicit Init_ShmClockInput_tzone_info(::cpm_common_interfaces::msg::ShmClockInput & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::ShmClockInput tzone_info(::cpm_common_interfaces::msg::ShmClockInput::_tzone_info_type arg)
  {
    msg_.tzone_info = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::ShmClockInput msg_;
};

class Init_ShmClockInput_utc_offset_min
{
public:
  explicit Init_ShmClockInput_utc_offset_min(::cpm_common_interfaces::msg::ShmClockInput & msg)
  : msg_(msg)
  {}
  Init_ShmClockInput_tzone_info utc_offset_min(::cpm_common_interfaces::msg::ShmClockInput::_utc_offset_min_type arg)
  {
    msg_.utc_offset_min = std::move(arg);
    return Init_ShmClockInput_tzone_info(msg_);
  }

private:
  ::cpm_common_interfaces::msg::ShmClockInput msg_;
};

class Init_ShmClockInput_utc_sec_us
{
public:
  explicit Init_ShmClockInput_utc_sec_us(::cpm_common_interfaces::msg::ShmClockInput & msg)
  : msg_(msg)
  {}
  Init_ShmClockInput_utc_offset_min utc_sec_us(::cpm_common_interfaces::msg::ShmClockInput::_utc_sec_us_type arg)
  {
    msg_.utc_sec_us = std::move(arg);
    return Init_ShmClockInput_utc_offset_min(msg_);
  }

private:
  ::cpm_common_interfaces::msg::ShmClockInput msg_;
};

class Init_ShmClockInput_shm_sec
{
public:
  Init_ShmClockInput_shm_sec()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ShmClockInput_utc_sec_us shm_sec(::cpm_common_interfaces::msg::ShmClockInput::_shm_sec_type arg)
  {
    msg_.shm_sec = std::move(arg);
    return Init_ShmClockInput_utc_sec_us(msg_);
  }

private:
  ::cpm_common_interfaces::msg::ShmClockInput msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::ShmClockInput>()
{
  return cpm_common_interfaces::msg::builder::Init_ShmClockInput_shm_sec();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__SHM_CLOCK_INPUT__BUILDER_HPP_
