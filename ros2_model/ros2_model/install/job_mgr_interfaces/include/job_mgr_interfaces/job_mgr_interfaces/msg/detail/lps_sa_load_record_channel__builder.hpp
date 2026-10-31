// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/LpsSaLoadRecordChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/lps_sa_load_record_channel.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_LOAD_RECORD_CHANNEL__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_LOAD_RECORD_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/lps_sa_load_record_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaLoadRecordChannel_store_time
{
public:
  explicit Init_LpsSaLoadRecordChannel_store_time(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg)
  : msg_(msg)
  {}
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel store_time(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel::_store_time_type arg)
  {
    msg_.store_time = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel msg_;
};

class Init_LpsSaLoadRecordChannel_current_subtotal_index
{
public:
  explicit Init_LpsSaLoadRecordChannel_current_subtotal_index(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaLoadRecordChannel_store_time current_subtotal_index(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel::_current_subtotal_index_type arg)
  {
    msg_.current_subtotal_index = std::move(arg);
    return Init_LpsSaLoadRecordChannel_store_time(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel msg_;
};

class Init_LpsSaLoadRecordChannel_total_target_weight
{
public:
  explicit Init_LpsSaLoadRecordChannel_total_target_weight(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaLoadRecordChannel_current_subtotal_index total_target_weight(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel::_total_target_weight_type arg)
  {
    msg_.total_target_weight = std::move(arg);
    return Init_LpsSaLoadRecordChannel_current_subtotal_index(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel msg_;
};

class Init_LpsSaLoadRecordChannel_target_type
{
public:
  explicit Init_LpsSaLoadRecordChannel_target_type(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaLoadRecordChannel_total_target_weight target_type(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel::_target_type_type arg)
  {
    msg_.target_type = std::move(arg);
    return Init_LpsSaLoadRecordChannel_total_target_weight(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel msg_;
};

class Init_LpsSaLoadRecordChannel_recipe_name
{
public:
  explicit Init_LpsSaLoadRecordChannel_recipe_name(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaLoadRecordChannel_target_type recipe_name(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel::_recipe_name_type arg)
  {
    msg_.recipe_name = std::move(arg);
    return Init_LpsSaLoadRecordChannel_target_type(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel msg_;
};

class Init_LpsSaLoadRecordChannel_weight_units
{
public:
  explicit Init_LpsSaLoadRecordChannel_weight_units(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaLoadRecordChannel_recipe_name weight_units(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel::_weight_units_type arg)
  {
    msg_.weight_units = std::move(arg);
    return Init_LpsSaLoadRecordChannel_recipe_name(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel msg_;
};

class Init_LpsSaLoadRecordChannel_weight_decimal_precision
{
public:
  explicit Init_LpsSaLoadRecordChannel_weight_decimal_precision(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaLoadRecordChannel_weight_units weight_decimal_precision(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel::_weight_decimal_precision_type arg)
  {
    msg_.weight_decimal_precision = std::move(arg);
    return Init_LpsSaLoadRecordChannel_weight_units(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel msg_;
};

class Init_LpsSaLoadRecordChannel_weight_interval
{
public:
  explicit Init_LpsSaLoadRecordChannel_weight_interval(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaLoadRecordChannel_weight_decimal_precision weight_interval(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel::_weight_interval_type arg)
  {
    msg_.weight_interval = std::move(arg);
    return Init_LpsSaLoadRecordChannel_weight_decimal_precision(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel msg_;
};

class Init_LpsSaLoadRecordChannel_equipment_id
{
public:
  explicit Init_LpsSaLoadRecordChannel_equipment_id(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaLoadRecordChannel_weight_interval equipment_id(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel::_equipment_id_type arg)
  {
    msg_.equipment_id = std::move(arg);
    return Init_LpsSaLoadRecordChannel_weight_interval(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel msg_;
};

class Init_LpsSaLoadRecordChannel_product_id
{
public:
  explicit Init_LpsSaLoadRecordChannel_product_id(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaLoadRecordChannel_equipment_id product_id(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel::_product_id_type arg)
  {
    msg_.product_id = std::move(arg);
    return Init_LpsSaLoadRecordChannel_equipment_id(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel msg_;
};

class Init_LpsSaLoadRecordChannel_ticket_id
{
public:
  explicit Init_LpsSaLoadRecordChannel_ticket_id(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaLoadRecordChannel_product_id ticket_id(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel::_ticket_id_type arg)
  {
    msg_.ticket_id = std::move(arg);
    return Init_LpsSaLoadRecordChannel_product_id(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel msg_;
};

class Init_LpsSaLoadRecordChannel_ticket_number
{
public:
  explicit Init_LpsSaLoadRecordChannel_ticket_number(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaLoadRecordChannel_ticket_id ticket_number(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel::_ticket_number_type arg)
  {
    msg_.ticket_number = std::move(arg);
    return Init_LpsSaLoadRecordChannel_ticket_id(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel msg_;
};

class Init_LpsSaLoadRecordChannel_subtotals
{
public:
  explicit Init_LpsSaLoadRecordChannel_subtotals(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaLoadRecordChannel_ticket_number subtotals(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel::_subtotals_type arg)
  {
    msg_.subtotals = std::move(arg);
    return Init_LpsSaLoadRecordChannel_ticket_number(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel msg_;
};

class Init_LpsSaLoadRecordChannel_subtotal
{
public:
  explicit Init_LpsSaLoadRecordChannel_subtotal(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaLoadRecordChannel_subtotals subtotal(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel::_subtotal_type arg)
  {
    msg_.subtotal = std::move(arg);
    return Init_LpsSaLoadRecordChannel_subtotals(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel msg_;
};

class Init_LpsSaLoadRecordChannel_store_action
{
public:
  Init_LpsSaLoadRecordChannel_store_action()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaLoadRecordChannel_subtotal store_action(::job_mgr_interfaces::msg::LpsSaLoadRecordChannel::_store_action_type arg)
  {
    msg_.store_action = std::move(arg);
    return Init_LpsSaLoadRecordChannel_subtotal(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaLoadRecordChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::LpsSaLoadRecordChannel>()
{
  return job_mgr_interfaces::msg::builder::Init_LpsSaLoadRecordChannel_store_action();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_LOAD_RECORD_CHANNEL__BUILDER_HPP_
