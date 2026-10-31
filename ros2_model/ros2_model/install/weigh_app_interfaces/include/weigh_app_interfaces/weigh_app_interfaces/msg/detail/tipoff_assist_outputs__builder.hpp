// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/TipoffAssistOutputs.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/tipoff_assist_outputs.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_OUTPUTS__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_OUTPUTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/tipoff_assist_outputs__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_TipoffAssistOutputs_min_secure_bucket_angle
{
public:
  explicit Init_TipoffAssistOutputs_min_secure_bucket_angle(::weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::TipoffAssistOutputs min_secure_bucket_angle(::weigh_app_interfaces::msg::TipoffAssistOutputs::_min_secure_bucket_angle_type arg)
  {
    msg_.min_secure_bucket_angle = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

class Init_TipoffAssistOutputs_unsecured_pfw_status
{
public:
  explicit Init_TipoffAssistOutputs_unsecured_pfw_status(::weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistOutputs_min_secure_bucket_angle unsecured_pfw_status(::weigh_app_interfaces::msg::TipoffAssistOutputs::_unsecured_pfw_status_type arg)
  {
    msg_.unsecured_pfw_status = std::move(arg);
    return Init_TipoffAssistOutputs_min_secure_bucket_angle(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

class Init_TipoffAssistOutputs_unsecured_payload_lower_bound_norm
{
public:
  explicit Init_TipoffAssistOutputs_unsecured_payload_lower_bound_norm(::weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistOutputs_unsecured_pfw_status unsecured_payload_lower_bound_norm(::weigh_app_interfaces::msg::TipoffAssistOutputs::_unsecured_payload_lower_bound_norm_type arg)
  {
    msg_.unsecured_payload_lower_bound_norm = std::move(arg);
    return Init_TipoffAssistOutputs_unsecured_pfw_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

class Init_TipoffAssistOutputs_unsecured_payload_upper_bound_norm
{
public:
  explicit Init_TipoffAssistOutputs_unsecured_payload_upper_bound_norm(::weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistOutputs_unsecured_payload_lower_bound_norm unsecured_payload_upper_bound_norm(::weigh_app_interfaces::msg::TipoffAssistOutputs::_unsecured_payload_upper_bound_norm_type arg)
  {
    msg_.unsecured_payload_upper_bound_norm = std::move(arg);
    return Init_TipoffAssistOutputs_unsecured_payload_lower_bound_norm(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

class Init_TipoffAssistOutputs_bucket_payload_target
{
public:
  explicit Init_TipoffAssistOutputs_bucket_payload_target(::weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistOutputs_unsecured_payload_upper_bound_norm bucket_payload_target(::weigh_app_interfaces::msg::TipoffAssistOutputs::_bucket_payload_target_type arg)
  {
    msg_.bucket_payload_target = std::move(arg);
    return Init_TipoffAssistOutputs_unsecured_payload_upper_bound_norm(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

class Init_TipoffAssistOutputs_payload_status_send_to_cpm
{
public:
  explicit Init_TipoffAssistOutputs_payload_status_send_to_cpm(::weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistOutputs_bucket_payload_target payload_status_send_to_cpm(::weigh_app_interfaces::msg::TipoffAssistOutputs::_payload_status_send_to_cpm_type arg)
  {
    msg_.payload_status_send_to_cpm = std::move(arg);
    return Init_TipoffAssistOutputs_bucket_payload_target(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

class Init_TipoffAssistOutputs_payload_send_to_cpm
{
public:
  explicit Init_TipoffAssistOutputs_payload_send_to_cpm(::weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistOutputs_payload_status_send_to_cpm payload_send_to_cpm(::weigh_app_interfaces::msg::TipoffAssistOutputs::_payload_send_to_cpm_type arg)
  {
    msg_.payload_send_to_cpm = std::move(arg);
    return Init_TipoffAssistOutputs_payload_status_send_to_cpm(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

class Init_TipoffAssistOutputs_spill_rate_out
{
public:
  explicit Init_TipoffAssistOutputs_spill_rate_out(::weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistOutputs_payload_send_to_cpm spill_rate_out(::weigh_app_interfaces::msg::TipoffAssistOutputs::_spill_rate_out_type arg)
  {
    msg_.spill_rate_out = std::move(arg);
    return Init_TipoffAssistOutputs_payload_send_to_cpm(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

class Init_TipoffAssistOutputs_error_code_out
{
public:
  explicit Init_TipoffAssistOutputs_error_code_out(::weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistOutputs_spill_rate_out error_code_out(::weigh_app_interfaces::msg::TipoffAssistOutputs::_error_code_out_type arg)
  {
    msg_.error_code_out = std::move(arg);
    return Init_TipoffAssistOutputs_spill_rate_out(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

class Init_TipoffAssistOutputs_current_weight_norm_error_out
{
public:
  explicit Init_TipoffAssistOutputs_current_weight_norm_error_out(::weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistOutputs_error_code_out current_weight_norm_error_out(::weigh_app_interfaces::msg::TipoffAssistOutputs::_current_weight_norm_error_out_type arg)
  {
    msg_.current_weight_norm_error_out = std::move(arg);
    return Init_TipoffAssistOutputs_error_code_out(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

class Init_TipoffAssistOutputs_pcs_weight_accuracy_out
{
public:
  explicit Init_TipoffAssistOutputs_pcs_weight_accuracy_out(::weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistOutputs_current_weight_norm_error_out pcs_weight_accuracy_out(::weigh_app_interfaces::msg::TipoffAssistOutputs::_pcs_weight_accuracy_out_type arg)
  {
    msg_.pcs_weight_accuracy_out = std::move(arg);
    return Init_TipoffAssistOutputs_current_weight_norm_error_out(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

class Init_TipoffAssistOutputs_payload_norm_stdev_out
{
public:
  explicit Init_TipoffAssistOutputs_payload_norm_stdev_out(::weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistOutputs_pcs_weight_accuracy_out payload_norm_stdev_out(::weigh_app_interfaces::msg::TipoffAssistOutputs::_payload_norm_stdev_out_type arg)
  {
    msg_.payload_norm_stdev_out = std::move(arg);
    return Init_TipoffAssistOutputs_pcs_weight_accuracy_out(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

class Init_TipoffAssistOutputs_weigh_status_out
{
public:
  explicit Init_TipoffAssistOutputs_weigh_status_out(::weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistOutputs_payload_norm_stdev_out weigh_status_out(::weigh_app_interfaces::msg::TipoffAssistOutputs::_weigh_status_out_type arg)
  {
    msg_.weigh_status_out = std::move(arg);
    return Init_TipoffAssistOutputs_payload_norm_stdev_out(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

class Init_TipoffAssistOutputs_arbitrated_payload_norm_error_out
{
public:
  explicit Init_TipoffAssistOutputs_arbitrated_payload_norm_error_out(::weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistOutputs_weigh_status_out arbitrated_payload_norm_error_out(::weigh_app_interfaces::msg::TipoffAssistOutputs::_arbitrated_payload_norm_error_out_type arg)
  {
    msg_.arbitrated_payload_norm_error_out = std::move(arg);
    return Init_TipoffAssistOutputs_weigh_status_out(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

class Init_TipoffAssistOutputs_tilt_pressure_out
{
public:
  explicit Init_TipoffAssistOutputs_tilt_pressure_out(::weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistOutputs_arbitrated_payload_norm_error_out tilt_pressure_out(::weigh_app_interfaces::msg::TipoffAssistOutputs::_tilt_pressure_out_type arg)
  {
    msg_.tilt_pressure_out = std::move(arg);
    return Init_TipoffAssistOutputs_arbitrated_payload_norm_error_out(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

class Init_TipoffAssistOutputs_tilt_sensitivity_out
{
public:
  Init_TipoffAssistOutputs_tilt_sensitivity_out()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TipoffAssistOutputs_tilt_pressure_out tilt_sensitivity_out(::weigh_app_interfaces::msg::TipoffAssistOutputs::_tilt_sensitivity_out_type arg)
  {
    msg_.tilt_sensitivity_out = std::move(arg);
    return Init_TipoffAssistOutputs_tilt_pressure_out(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistOutputs msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::TipoffAssistOutputs>()
{
  return weigh_app_interfaces::msg::builder::Init_TipoffAssistOutputs_tilt_sensitivity_out();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_OUTPUTS__BUILDER_HPP_
