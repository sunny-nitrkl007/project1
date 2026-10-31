// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaUIDisplaySettings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_ui_display_settings.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_SETTINGS__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_SETTINGS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/lps_sa_ui_display_settings__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaUIDisplaySettings_keyboard_layout_setting
{
public:
  explicit Init_LpsSaUIDisplaySettings_keyboard_layout_setting(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::LpsSaUIDisplaySettings keyboard_layout_setting(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings::_keyboard_layout_setting_type arg)
  {
    msg_.keyboard_layout_setting = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplaySettings msg_;
};

class Init_LpsSaUIDisplaySettings_service_mode_enable_code
{
public:
  explicit Init_LpsSaUIDisplaySettings_service_mode_enable_code(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings & msg)
  : msg_(msg)
  {}
  Init_LpsSaUIDisplaySettings_keyboard_layout_setting service_mode_enable_code(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings::_service_mode_enable_code_type arg)
  {
    msg_.service_mode_enable_code = std::move(arg);
    return Init_LpsSaUIDisplaySettings_keyboard_layout_setting(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplaySettings msg_;
};

class Init_LpsSaUIDisplaySettings_weight_precision
{
public:
  explicit Init_LpsSaUIDisplaySettings_weight_precision(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings & msg)
  : msg_(msg)
  {}
  Init_LpsSaUIDisplaySettings_service_mode_enable_code weight_precision(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings::_weight_precision_type arg)
  {
    msg_.weight_precision = std::move(arg);
    return Init_LpsSaUIDisplaySettings_service_mode_enable_code(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplaySettings msg_;
};

class Init_LpsSaUIDisplaySettings_weight_units
{
public:
  explicit Init_LpsSaUIDisplaySettings_weight_units(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings & msg)
  : msg_(msg)
  {}
  Init_LpsSaUIDisplaySettings_weight_precision weight_units(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings::_weight_units_type arg)
  {
    msg_.weight_units = std::move(arg);
    return Init_LpsSaUIDisplaySettings_weight_precision(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplaySettings msg_;
};

class Init_LpsSaUIDisplaySettings_date_format
{
public:
  explicit Init_LpsSaUIDisplaySettings_date_format(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings & msg)
  : msg_(msg)
  {}
  Init_LpsSaUIDisplaySettings_weight_units date_format(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings::_date_format_type arg)
  {
    msg_.date_format = std::move(arg);
    return Init_LpsSaUIDisplaySettings_weight_units(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplaySettings msg_;
};

class Init_LpsSaUIDisplaySettings_time_format
{
public:
  explicit Init_LpsSaUIDisplaySettings_time_format(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings & msg)
  : msg_(msg)
  {}
  Init_LpsSaUIDisplaySettings_date_format time_format(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings::_time_format_type arg)
  {
    msg_.time_format = std::move(arg);
    return Init_LpsSaUIDisplaySettings_date_format(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplaySettings msg_;
};

class Init_LpsSaUIDisplaySettings_brightness
{
public:
  explicit Init_LpsSaUIDisplaySettings_brightness(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings & msg)
  : msg_(msg)
  {}
  Init_LpsSaUIDisplaySettings_time_format brightness(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings::_brightness_type arg)
  {
    msg_.brightness = std::move(arg);
    return Init_LpsSaUIDisplaySettings_time_format(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplaySettings msg_;
};

class Init_LpsSaUIDisplaySettings_language
{
public:
  explicit Init_LpsSaUIDisplaySettings_language(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings & msg)
  : msg_(msg)
  {}
  Init_LpsSaUIDisplaySettings_brightness language(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings::_language_type arg)
  {
    msg_.language = std::move(arg);
    return Init_LpsSaUIDisplaySettings_brightness(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplaySettings msg_;
};

class Init_LpsSaUIDisplaySettings_units
{
public:
  Init_LpsSaUIDisplaySettings_units()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaUIDisplaySettings_language units(::cpm_common_interfaces::msg::LpsSaUIDisplaySettings::_units_type arg)
  {
    msg_.units = std::move(arg);
    return Init_LpsSaUIDisplaySettings_language(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplaySettings msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::LpsSaUIDisplaySettings>()
{
  return cpm_common_interfaces::msg::builder::Init_LpsSaUIDisplaySettings_units();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_SETTINGS__BUILDER_HPP_
