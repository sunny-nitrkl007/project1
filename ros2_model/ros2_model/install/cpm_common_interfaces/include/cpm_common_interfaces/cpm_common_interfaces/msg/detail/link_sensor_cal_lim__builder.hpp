// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/LinkSensorCalLim.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/link_sensor_cal_lim.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LINK_SENSOR_CAL_LIM__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LINK_SENSOR_CAL_LIM__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/link_sensor_cal_lim__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_LinkSensorCalLim_tilt_pos_sensor_full_dump_dc
{
public:
  explicit Init_LinkSensorCalLim_tilt_pos_sensor_full_dump_dc(::cpm_common_interfaces::msg::LinkSensorCalLim & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::LinkSensorCalLim tilt_pos_sensor_full_dump_dc(::cpm_common_interfaces::msg::LinkSensorCalLim::_tilt_pos_sensor_full_dump_dc_type arg)
  {
    msg_.tilt_pos_sensor_full_dump_dc = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LinkSensorCalLim msg_;
};

class Init_LinkSensorCalLim_tilt_pos_sensor_full_rack_dc
{
public:
  explicit Init_LinkSensorCalLim_tilt_pos_sensor_full_rack_dc(::cpm_common_interfaces::msg::LinkSensorCalLim & msg)
  : msg_(msg)
  {}
  Init_LinkSensorCalLim_tilt_pos_sensor_full_dump_dc tilt_pos_sensor_full_rack_dc(::cpm_common_interfaces::msg::LinkSensorCalLim::_tilt_pos_sensor_full_rack_dc_type arg)
  {
    msg_.tilt_pos_sensor_full_rack_dc = std::move(arg);
    return Init_LinkSensorCalLim_tilt_pos_sensor_full_dump_dc(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LinkSensorCalLim msg_;
};

class Init_LinkSensorCalLim_tilt_pos_sensor_dc
{
public:
  explicit Init_LinkSensorCalLim_tilt_pos_sensor_dc(::cpm_common_interfaces::msg::LinkSensorCalLim & msg)
  : msg_(msg)
  {}
  Init_LinkSensorCalLim_tilt_pos_sensor_full_rack_dc tilt_pos_sensor_dc(::cpm_common_interfaces::msg::LinkSensorCalLim::_tilt_pos_sensor_dc_type arg)
  {
    msg_.tilt_pos_sensor_dc = std::move(arg);
    return Init_LinkSensorCalLim_tilt_pos_sensor_full_rack_dc(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LinkSensorCalLim msg_;
};

class Init_LinkSensorCalLim_lift_pos_sensor_full_lower_dc
{
public:
  explicit Init_LinkSensorCalLim_lift_pos_sensor_full_lower_dc(::cpm_common_interfaces::msg::LinkSensorCalLim & msg)
  : msg_(msg)
  {}
  Init_LinkSensorCalLim_tilt_pos_sensor_dc lift_pos_sensor_full_lower_dc(::cpm_common_interfaces::msg::LinkSensorCalLim::_lift_pos_sensor_full_lower_dc_type arg)
  {
    msg_.lift_pos_sensor_full_lower_dc = std::move(arg);
    return Init_LinkSensorCalLim_tilt_pos_sensor_dc(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LinkSensorCalLim msg_;
};

class Init_LinkSensorCalLim_lift_pos_sensor_full_raise_dc
{
public:
  explicit Init_LinkSensorCalLim_lift_pos_sensor_full_raise_dc(::cpm_common_interfaces::msg::LinkSensorCalLim & msg)
  : msg_(msg)
  {}
  Init_LinkSensorCalLim_lift_pos_sensor_full_lower_dc lift_pos_sensor_full_raise_dc(::cpm_common_interfaces::msg::LinkSensorCalLim::_lift_pos_sensor_full_raise_dc_type arg)
  {
    msg_.lift_pos_sensor_full_raise_dc = std::move(arg);
    return Init_LinkSensorCalLim_lift_pos_sensor_full_lower_dc(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LinkSensorCalLim msg_;
};

class Init_LinkSensorCalLim_lift_pos_sensor_dc
{
public:
  Init_LinkSensorCalLim_lift_pos_sensor_dc()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LinkSensorCalLim_lift_pos_sensor_full_raise_dc lift_pos_sensor_dc(::cpm_common_interfaces::msg::LinkSensorCalLim::_lift_pos_sensor_dc_type arg)
  {
    msg_.lift_pos_sensor_dc = std::move(arg);
    return Init_LinkSensorCalLim_lift_pos_sensor_full_raise_dc(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LinkSensorCalLim msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::LinkSensorCalLim>()
{
  return cpm_common_interfaces::msg::builder::Init_LinkSensorCalLim_lift_pos_sensor_dc();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LINK_SENSOR_CAL_LIM__BUILDER_HPP_
