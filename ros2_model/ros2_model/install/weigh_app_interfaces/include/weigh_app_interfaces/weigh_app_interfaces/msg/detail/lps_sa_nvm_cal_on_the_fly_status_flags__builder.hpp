// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyStatusFlags.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_status_flags.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_STATUS_FLAGS__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_STATUS_FLAGS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_status_flags__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaNvmCalOnTheFlyStatusFlags_full_bkt_cal_done
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyStatusFlags_full_bkt_cal_done(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags full_bkt_cal_done(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags::_full_bkt_cal_done_type arg)
  {
    msg_.full_bkt_cal_done = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags msg_;
};

class Init_LpsSaNvmCalOnTheFlyStatusFlags_empty_bkt_cal_done
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyStatusFlags_empty_bkt_cal_done(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyStatusFlags_full_bkt_cal_done empty_bkt_cal_done(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags::_empty_bkt_cal_done_type arg)
  {
    msg_.empty_bkt_cal_done = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyStatusFlags_full_bkt_cal_done(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags msg_;
};

class Init_LpsSaNvmCalOnTheFlyStatusFlags_cal_in_progress
{
public:
  Init_LpsSaNvmCalOnTheFlyStatusFlags_cal_in_progress()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaNvmCalOnTheFlyStatusFlags_empty_bkt_cal_done cal_in_progress(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags::_cal_in_progress_type arg)
  {
    msg_.cal_in_progress = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyStatusFlags_empty_bkt_cal_done(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags>()
{
  return weigh_app_interfaces::msg::builder::Init_LpsSaNvmCalOnTheFlyStatusFlags_cal_in_progress();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_STATUS_FLAGS__BUILDER_HPP_
