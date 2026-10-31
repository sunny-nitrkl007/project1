// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalDataChannelDataDebug.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_data_channel_data_debug.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_DEBUG__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_DEBUG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_data_channel_data_debug__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaNvmCalDataChannelDataDebug_hyd_oil_type_index
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataDebug_hyd_oil_type_index(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug hyd_oil_type_index(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_hyd_oil_type_index_type arg)
  {
    msg_.hyd_oil_type_index = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

class Init_LpsSaNvmCalDataChannelDataDebug_cal_adjust_temp
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataDebug_cal_adjust_temp(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataDebug_hyd_oil_type_index cal_adjust_temp(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_cal_adjust_temp_type arg)
  {
    msg_.cal_adjust_temp = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataDebug_hyd_oil_type_index(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

class Init_LpsSaNvmCalDataChannelDataDebug_empty_bucket_weight_est
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataDebug_empty_bucket_weight_est(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataDebug_cal_adjust_temp empty_bucket_weight_est(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_empty_bucket_weight_est_type arg)
  {
    msg_.empty_bucket_weight_est = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataDebug_cal_adjust_temp(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

class Init_LpsSaNvmCalDataChannelDataDebug_full_temp
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataDebug_full_temp(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataDebug_empty_bucket_weight_est full_temp(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_full_temp_type arg)
  {
    msg_.full_temp = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataDebug_empty_bucket_weight_est(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

class Init_LpsSaNvmCalDataChannelDataDebug_empty_temp
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataDebug_empty_temp(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataDebug_full_temp empty_temp(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_empty_temp_type arg)
  {
    msg_.empty_temp = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataDebug_full_temp(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

class Init_LpsSaNvmCalDataChannelDataDebug_temp_slope
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataDebug_temp_slope(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataDebug_empty_temp temp_slope(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_temp_slope_type arg)
  {
    msg_.temp_slope = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataDebug_empty_temp(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

class Init_LpsSaNvmCalDataChannelDataDebug_cal_adjust
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataDebug_cal_adjust(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataDebug_temp_slope cal_adjust(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_cal_adjust_type arg)
  {
    msg_.cal_adjust = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataDebug_temp_slope(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

class Init_LpsSaNvmCalDataChannelDataDebug_zero_weight
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataDebug_zero_weight(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataDebug_cal_adjust zero_weight(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_zero_weight_type arg)
  {
    msg_.zero_weight = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataDebug_cal_adjust(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

class Init_LpsSaNvmCalDataChannelDataDebug_pcs_cal_weight
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataDebug_pcs_cal_weight(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataDebug_zero_weight pcs_cal_weight(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_pcs_cal_weight_type arg)
  {
    msg_.pcs_cal_weight = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataDebug_zero_weight(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

class Init_LpsSaNvmCalDataChannelDataDebug_pcs_vel_slope
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataDebug_pcs_vel_slope(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataDebug_pcs_cal_weight pcs_vel_slope(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_pcs_vel_slope_type arg)
  {
    msg_.pcs_vel_slope = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataDebug_pcs_cal_weight(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

class Init_LpsSaNvmCalDataChannelDataDebug_tilt_rack_stop_angle_inf_value
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataDebug_tilt_rack_stop_angle_inf_value(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataDebug_pcs_vel_slope tilt_rack_stop_angle_inf_value(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_tilt_rack_stop_angle_inf_value_type arg)
  {
    msg_.tilt_rack_stop_angle_inf_value = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataDebug_pcs_vel_slope(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

class Init_LpsSaNvmCalDataChannelDataDebug_tilt_dump_stop_angle_inf_value
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataDebug_tilt_dump_stop_angle_inf_value(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataDebug_tilt_rack_stop_angle_inf_value tilt_dump_stop_angle_inf_value(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_tilt_dump_stop_angle_inf_value_type arg)
  {
    msg_.tilt_dump_stop_angle_inf_value = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataDebug_tilt_rack_stop_angle_inf_value(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

class Init_LpsSaNvmCalDataChannelDataDebug_tilt_full_rack_dc_inf_value
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataDebug_tilt_full_rack_dc_inf_value(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataDebug_tilt_dump_stop_angle_inf_value tilt_full_rack_dc_inf_value(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_tilt_full_rack_dc_inf_value_type arg)
  {
    msg_.tilt_full_rack_dc_inf_value = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataDebug_tilt_dump_stop_angle_inf_value(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

class Init_LpsSaNvmCalDataChannelDataDebug_tilt_full_dump_dc_inf_value
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataDebug_tilt_full_dump_dc_inf_value(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataDebug_tilt_full_rack_dc_inf_value tilt_full_dump_dc_inf_value(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_tilt_full_dump_dc_inf_value_type arg)
  {
    msg_.tilt_full_dump_dc_inf_value = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataDebug_tilt_full_rack_dc_inf_value(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

class Init_LpsSaNvmCalDataChannelDataDebug_lift_full_raise_dc_inf_value
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataDebug_lift_full_raise_dc_inf_value(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataDebug_tilt_full_dump_dc_inf_value lift_full_raise_dc_inf_value(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_lift_full_raise_dc_inf_value_type arg)
  {
    msg_.lift_full_raise_dc_inf_value = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataDebug_tilt_full_dump_dc_inf_value(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

class Init_LpsSaNvmCalDataChannelDataDebug_lift_full_lower_dc_inf_value
{
public:
  Init_LpsSaNvmCalDataChannelDataDebug_lift_full_lower_dc_inf_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaNvmCalDataChannelDataDebug_lift_full_raise_dc_inf_value lift_full_lower_dc_inf_value(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug::_lift_full_lower_dc_inf_value_type arg)
  {
    msg_.lift_full_lower_dc_inf_value = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataDebug_lift_full_raise_dc_inf_value(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug>()
{
  return weigh_app_interfaces::msg::builder::Init_LpsSaNvmCalDataChannelDataDebug_lift_full_lower_dc_inf_value();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_DEBUG__BUILDER_HPP_
