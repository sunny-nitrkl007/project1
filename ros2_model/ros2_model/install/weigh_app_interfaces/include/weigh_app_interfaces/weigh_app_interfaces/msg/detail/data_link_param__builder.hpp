// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/DataLinkParam.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/data_link_param.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/data_link_param__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_DataLinkParam_var_length_param_dsi
{
public:
  explicit Init_DataLinkParam_var_length_param_dsi(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::DataLinkParam var_length_param_dsi(::weigh_app_interfaces::msg::DataLinkParam::_var_length_param_dsi_type arg)
  {
    msg_.var_length_param_dsi = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_var_length_param_type
{
public:
  explicit Init_DataLinkParam_var_length_param_type(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_var_length_param_dsi var_length_param_type(::weigh_app_interfaces::msg::DataLinkParam::_var_length_param_type_type arg)
  {
    msg_.var_length_param_type = std::move(arg);
    return Init_DataLinkParam_var_length_param_dsi(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_var_param_block
{
public:
  explicit Init_DataLinkParam_var_param_block(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_var_length_param_type var_param_block(::weigh_app_interfaces::msg::DataLinkParam::_var_param_block_type arg)
  {
    msg_.var_param_block = std::move(arg);
    return Init_DataLinkParam_var_length_param_type(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_last_value_vector
{
public:
  explicit Init_DataLinkParam_last_value_vector(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_var_param_block last_value_vector(::weigh_app_interfaces::msg::DataLinkParam::_last_value_vector_type arg)
  {
    msg_.last_value_vector = std::move(arg);
    return Init_DataLinkParam_var_param_block(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_last_good_value_eng
{
public:
  explicit Init_DataLinkParam_last_good_value_eng(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_last_value_vector last_good_value_eng(::weigh_app_interfaces::msg::DataLinkParam::_last_good_value_eng_type arg)
  {
    msg_.last_good_value_eng = std::move(arg);
    return Init_DataLinkParam_last_value_vector(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_last_value_eng
{
public:
  explicit Init_DataLinkParam_last_value_eng(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_last_good_value_eng last_value_eng(::weigh_app_interfaces::msg::DataLinkParam::_last_value_eng_type arg)
  {
    msg_.last_value_eng = std::move(arg);
    return Init_DataLinkParam_last_good_value_eng(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_last_value_f32
{
public:
  explicit Init_DataLinkParam_last_value_f32(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_last_value_eng last_value_f32(::weigh_app_interfaces::msg::DataLinkParam::_last_value_f32_type arg)
  {
    msg_.last_value_f32 = std::move(arg);
    return Init_DataLinkParam_last_value_eng(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_last_value_u16
{
public:
  explicit Init_DataLinkParam_last_value_u16(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_last_value_f32 last_value_u16(::weigh_app_interfaces::msg::DataLinkParam::_last_value_u16_type arg)
  {
    msg_.last_value_u16 = std::move(arg);
    return Init_DataLinkParam_last_value_f32(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_last_value_i16
{
public:
  explicit Init_DataLinkParam_last_value_i16(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_last_value_u16 last_value_i16(::weigh_app_interfaces::msg::DataLinkParam::_last_value_i16_type arg)
  {
    msg_.last_value_i16 = std::move(arg);
    return Init_DataLinkParam_last_value_u16(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_last_value_dsi
{
public:
  explicit Init_DataLinkParam_last_value_dsi(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_last_value_i16 last_value_dsi(::weigh_app_interfaces::msg::DataLinkParam::_last_value_dsi_type arg)
  {
    msg_.last_value_dsi = std::move(arg);
    return Init_DataLinkParam_last_value_i16(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_pid_data_received
{
public:
  explicit Init_DataLinkParam_pid_data_received(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_last_value_dsi pid_data_received(::weigh_app_interfaces::msg::DataLinkParam::_pid_data_received_type arg)
  {
    msg_.pid_data_received = std::move(arg);
    return Init_DataLinkParam_last_value_dsi(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_offset
{
public:
  explicit Init_DataLinkParam_offset(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_pid_data_received offset(::weigh_app_interfaces::msg::DataLinkParam::_offset_type arg)
  {
    msg_.offset = std::move(arg);
    return Init_DataLinkParam_pid_data_received(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_scaling
{
public:
  explicit Init_DataLinkParam_scaling(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_offset scaling(::weigh_app_interfaces::msg::DataLinkParam::_scaling_type arg)
  {
    msg_.scaling = std::move(arg);
    return Init_DataLinkParam_offset(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_units
{
public:
  explicit Init_DataLinkParam_units(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_scaling units(::weigh_app_interfaces::msg::DataLinkParam::_units_type arg)
  {
    msg_.units = std::move(arg);
    return Init_DataLinkParam_scaling(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_param_id
{
public:
  explicit Init_DataLinkParam_param_id(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_units param_id(::weigh_app_interfaces::msg::DataLinkParam::_param_id_type arg)
  {
    msg_.param_id = std::move(arg);
    return Init_DataLinkParam_units(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_sid
{
public:
  explicit Init_DataLinkParam_sid(::weigh_app_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_param_id sid(::weigh_app_interfaces::msg::DataLinkParam::_sid_type arg)
  {
    msg_.sid = std::move(arg);
    return Init_DataLinkParam_param_id(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_identifier_type
{
public:
  Init_DataLinkParam_identifier_type()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DataLinkParam_sid identifier_type(::weigh_app_interfaces::msg::DataLinkParam::_identifier_type_type arg)
  {
    msg_.identifier_type = std::move(arg);
    return Init_DataLinkParam_sid(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkParam msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::DataLinkParam>()
{
  return weigh_app_interfaces::msg::builder::Init_DataLinkParam_identifier_type();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__BUILDER_HPP_
