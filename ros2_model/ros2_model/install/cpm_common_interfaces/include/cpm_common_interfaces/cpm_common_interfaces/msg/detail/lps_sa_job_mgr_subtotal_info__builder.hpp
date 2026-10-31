// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaJobMgrSubtotalInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_job_mgr_subtotal_info.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_SUBTOTAL_INFO__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_SUBTOTAL_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/lps_sa_job_mgr_subtotal_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaJobMgrSubtotalInfo_icon_type
{
public:
  explicit Init_LpsSaJobMgrSubtotalInfo_icon_type(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo icon_type(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo::_icon_type_type arg)
  {
    msg_.icon_type = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo msg_;
};

class Init_LpsSaJobMgrSubtotalInfo_material_density
{
public:
  explicit Init_LpsSaJobMgrSubtotalInfo_material_density(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrSubtotalInfo_icon_type material_density(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo::_material_density_type arg)
  {
    msg_.material_density = std::move(arg);
    return Init_LpsSaJobMgrSubtotalInfo_icon_type(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo msg_;
};

class Init_LpsSaJobMgrSubtotalInfo_material_name
{
public:
  explicit Init_LpsSaJobMgrSubtotalInfo_material_name(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrSubtotalInfo_material_density material_name(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo::_material_name_type arg)
  {
    msg_.material_name = std::move(arg);
    return Init_LpsSaJobMgrSubtotalInfo_material_density(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo msg_;
};

class Init_LpsSaJobMgrSubtotalInfo_material_id
{
public:
  explicit Init_LpsSaJobMgrSubtotalInfo_material_id(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrSubtotalInfo_material_name material_id(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo::_material_id_type arg)
  {
    msg_.material_id = std::move(arg);
    return Init_LpsSaJobMgrSubtotalInfo_material_name(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo msg_;
};

class Init_LpsSaJobMgrSubtotalInfo_target_passes
{
public:
  explicit Init_LpsSaJobMgrSubtotalInfo_target_passes(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrSubtotalInfo_material_id target_passes(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo::_target_passes_type arg)
  {
    msg_.target_passes = std::move(arg);
    return Init_LpsSaJobMgrSubtotalInfo_material_id(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo msg_;
};

class Init_LpsSaJobMgrSubtotalInfo_target_proportion
{
public:
  explicit Init_LpsSaJobMgrSubtotalInfo_target_proportion(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrSubtotalInfo_target_passes target_proportion(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo::_target_proportion_type arg)
  {
    msg_.target_proportion = std::move(arg);
    return Init_LpsSaJobMgrSubtotalInfo_target_passes(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo msg_;
};

class Init_LpsSaJobMgrSubtotalInfo_target_weight
{
public:
  explicit Init_LpsSaJobMgrSubtotalInfo_target_weight(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrSubtotalInfo_target_proportion target_weight(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo::_target_weight_type arg)
  {
    msg_.target_weight = std::move(arg);
    return Init_LpsSaJobMgrSubtotalInfo_target_proportion(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo msg_;
};

class Init_LpsSaJobMgrSubtotalInfo_new_step_number
{
public:
  explicit Init_LpsSaJobMgrSubtotalInfo_new_step_number(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrSubtotalInfo_target_weight new_step_number(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo::_new_step_number_type arg)
  {
    msg_.new_step_number = std::move(arg);
    return Init_LpsSaJobMgrSubtotalInfo_target_weight(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo msg_;
};

class Init_LpsSaJobMgrSubtotalInfo_current_step_number
{
public:
  explicit Init_LpsSaJobMgrSubtotalInfo_current_step_number(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrSubtotalInfo_new_step_number current_step_number(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo::_current_step_number_type arg)
  {
    msg_.current_step_number = std::move(arg);
    return Init_LpsSaJobMgrSubtotalInfo_new_step_number(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo msg_;
};

class Init_LpsSaJobMgrSubtotalInfo_subtotal_command
{
public:
  Init_LpsSaJobMgrSubtotalInfo_subtotal_command()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaJobMgrSubtotalInfo_current_step_number subtotal_command(::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo::_subtotal_command_type arg)
  {
    msg_.subtotal_command = std::move(arg);
    return Init_LpsSaJobMgrSubtotalInfo_current_step_number(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo>()
{
  return cpm_common_interfaces::msg::builder::Init_LpsSaJobMgrSubtotalInfo_subtotal_command();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_SUBTOTAL_INFO__BUILDER_HPP_
