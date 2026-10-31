// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/ProdMeasureSensorStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/prod_measure_sensor_status.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__PROD_MEASURE_SENSOR_STATUS__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__PROD_MEASURE_SENSOR_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/prod_measure_sensor_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_ProdMeasureSensorStatus_hyd_oil_temp
{
public:
  explicit Init_ProdMeasureSensorStatus_hyd_oil_temp(::cpm_common_interfaces::msg::ProdMeasureSensorStatus & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::ProdMeasureSensorStatus hyd_oil_temp(::cpm_common_interfaces::msg::ProdMeasureSensorStatus::_hyd_oil_temp_type arg)
  {
    msg_.hyd_oil_temp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::ProdMeasureSensorStatus msg_;
};

class Init_ProdMeasureSensorStatus_tilt_link_dc
{
public:
  explicit Init_ProdMeasureSensorStatus_tilt_link_dc(::cpm_common_interfaces::msg::ProdMeasureSensorStatus & msg)
  : msg_(msg)
  {}
  Init_ProdMeasureSensorStatus_hyd_oil_temp tilt_link_dc(::cpm_common_interfaces::msg::ProdMeasureSensorStatus::_tilt_link_dc_type arg)
  {
    msg_.tilt_link_dc = std::move(arg);
    return Init_ProdMeasureSensorStatus_hyd_oil_temp(msg_);
  }

private:
  ::cpm_common_interfaces::msg::ProdMeasureSensorStatus msg_;
};

class Init_ProdMeasureSensorStatus_tilt_cyl_re_pres
{
public:
  explicit Init_ProdMeasureSensorStatus_tilt_cyl_re_pres(::cpm_common_interfaces::msg::ProdMeasureSensorStatus & msg)
  : msg_(msg)
  {}
  Init_ProdMeasureSensorStatus_tilt_link_dc tilt_cyl_re_pres(::cpm_common_interfaces::msg::ProdMeasureSensorStatus::_tilt_cyl_re_pres_type arg)
  {
    msg_.tilt_cyl_re_pres = std::move(arg);
    return Init_ProdMeasureSensorStatus_tilt_link_dc(msg_);
  }

private:
  ::cpm_common_interfaces::msg::ProdMeasureSensorStatus msg_;
};

class Init_ProdMeasureSensorStatus_tilt_cyl_he_pres
{
public:
  explicit Init_ProdMeasureSensorStatus_tilt_cyl_he_pres(::cpm_common_interfaces::msg::ProdMeasureSensorStatus & msg)
  : msg_(msg)
  {}
  Init_ProdMeasureSensorStatus_tilt_cyl_re_pres tilt_cyl_he_pres(::cpm_common_interfaces::msg::ProdMeasureSensorStatus::_tilt_cyl_he_pres_type arg)
  {
    msg_.tilt_cyl_he_pres = std::move(arg);
    return Init_ProdMeasureSensorStatus_tilt_cyl_re_pres(msg_);
  }

private:
  ::cpm_common_interfaces::msg::ProdMeasureSensorStatus msg_;
};

class Init_ProdMeasureSensorStatus_tilt_sensor_config
{
public:
  explicit Init_ProdMeasureSensorStatus_tilt_sensor_config(::cpm_common_interfaces::msg::ProdMeasureSensorStatus & msg)
  : msg_(msg)
  {}
  Init_ProdMeasureSensorStatus_tilt_cyl_he_pres tilt_sensor_config(::cpm_common_interfaces::msg::ProdMeasureSensorStatus::_tilt_sensor_config_type arg)
  {
    msg_.tilt_sensor_config = std::move(arg);
    return Init_ProdMeasureSensorStatus_tilt_cyl_he_pres(msg_);
  }

private:
  ::cpm_common_interfaces::msg::ProdMeasureSensorStatus msg_;
};

class Init_ProdMeasureSensorStatus_lift_cyl_re_pres
{
public:
  explicit Init_ProdMeasureSensorStatus_lift_cyl_re_pres(::cpm_common_interfaces::msg::ProdMeasureSensorStatus & msg)
  : msg_(msg)
  {}
  Init_ProdMeasureSensorStatus_tilt_sensor_config lift_cyl_re_pres(::cpm_common_interfaces::msg::ProdMeasureSensorStatus::_lift_cyl_re_pres_type arg)
  {
    msg_.lift_cyl_re_pres = std::move(arg);
    return Init_ProdMeasureSensorStatus_tilt_sensor_config(msg_);
  }

private:
  ::cpm_common_interfaces::msg::ProdMeasureSensorStatus msg_;
};

class Init_ProdMeasureSensorStatus_lift_cyl_he_pres
{
public:
  explicit Init_ProdMeasureSensorStatus_lift_cyl_he_pres(::cpm_common_interfaces::msg::ProdMeasureSensorStatus & msg)
  : msg_(msg)
  {}
  Init_ProdMeasureSensorStatus_lift_cyl_re_pres lift_cyl_he_pres(::cpm_common_interfaces::msg::ProdMeasureSensorStatus::_lift_cyl_he_pres_type arg)
  {
    msg_.lift_cyl_he_pres = std::move(arg);
    return Init_ProdMeasureSensorStatus_lift_cyl_re_pres(msg_);
  }

private:
  ::cpm_common_interfaces::msg::ProdMeasureSensorStatus msg_;
};

class Init_ProdMeasureSensorStatus_lift_cyl_pos
{
public:
  explicit Init_ProdMeasureSensorStatus_lift_cyl_pos(::cpm_common_interfaces::msg::ProdMeasureSensorStatus & msg)
  : msg_(msg)
  {}
  Init_ProdMeasureSensorStatus_lift_cyl_he_pres lift_cyl_pos(::cpm_common_interfaces::msg::ProdMeasureSensorStatus::_lift_cyl_pos_type arg)
  {
    msg_.lift_cyl_pos = std::move(arg);
    return Init_ProdMeasureSensorStatus_lift_cyl_he_pres(msg_);
  }

private:
  ::cpm_common_interfaces::msg::ProdMeasureSensorStatus msg_;
};

class Init_ProdMeasureSensorStatus_lift_link_dc
{
public:
  Init_ProdMeasureSensorStatus_lift_link_dc()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ProdMeasureSensorStatus_lift_cyl_pos lift_link_dc(::cpm_common_interfaces::msg::ProdMeasureSensorStatus::_lift_link_dc_type arg)
  {
    msg_.lift_link_dc = std::move(arg);
    return Init_ProdMeasureSensorStatus_lift_cyl_pos(msg_);
  }

private:
  ::cpm_common_interfaces::msg::ProdMeasureSensorStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::ProdMeasureSensorStatus>()
{
  return cpm_common_interfaces::msg::builder::Init_ProdMeasureSensorStatus_lift_link_dc();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__PROD_MEASURE_SENSOR_STATUS__BUILDER_HPP_
