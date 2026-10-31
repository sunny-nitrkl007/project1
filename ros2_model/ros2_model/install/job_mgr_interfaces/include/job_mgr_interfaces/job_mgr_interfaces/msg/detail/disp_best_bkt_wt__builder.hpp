// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/DispBestBktWt.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/disp_best_bkt_wt.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__DISP_BEST_BKT_WT__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__DISP_BEST_BKT_WT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/disp_best_bkt_wt__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_DispBestBktWt_is_ok
{
public:
  explicit Init_DispBestBktWt_is_ok(::job_mgr_interfaces::msg::DispBestBktWt & msg)
  : msg_(msg)
  {}
  ::job_mgr_interfaces::msg::DispBestBktWt is_ok(::job_mgr_interfaces::msg::DispBestBktWt::_is_ok_type arg)
  {
    msg_.is_ok = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::DispBestBktWt msg_;
};

class Init_DispBestBktWt_val
{
public:
  Init_DispBestBktWt_val()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DispBestBktWt_is_ok val(::job_mgr_interfaces::msg::DispBestBktWt::_val_type arg)
  {
    msg_.val = std::move(arg);
    return Init_DispBestBktWt_is_ok(msg_);
  }

private:
  ::job_mgr_interfaces::msg::DispBestBktWt msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::DispBestBktWt>()
{
  return job_mgr_interfaces::msg::builder::Init_DispBestBktWt_val();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__DISP_BEST_BKT_WT__BUILDER_HPP_
