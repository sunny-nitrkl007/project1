// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/LoadRecordSubtotal.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/load_record_subtotal.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_SUBTOTAL__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_SUBTOTAL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/load_record_subtotal__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_LoadRecordSubtotal_accuracy
{
public:
  explicit Init_LoadRecordSubtotal_accuracy(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  ::job_mgr_interfaces::msg::LoadRecordSubtotal accuracy(::job_mgr_interfaces::msg::LoadRecordSubtotal::_accuracy_type arg)
  {
    msg_.accuracy = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_weight_tonnes
{
public:
  explicit Init_LoadRecordSubtotal_weight_tonnes(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_accuracy weight_tonnes(::job_mgr_interfaces::msg::LoadRecordSubtotal::_weight_tonnes_type arg)
  {
    msg_.weight_tonnes = std::move(arg);
    return Init_LoadRecordSubtotal_accuracy(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_passes
{
public:
  explicit Init_LoadRecordSubtotal_passes(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_weight_tonnes passes(::job_mgr_interfaces::msg::LoadRecordSubtotal::_passes_type arg)
  {
    msg_.passes = std::move(arg);
    return Init_LoadRecordSubtotal_weight_tonnes(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_cal_adjust
{
public:
  explicit Init_LoadRecordSubtotal_cal_adjust(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_passes cal_adjust(::job_mgr_interfaces::msg::LoadRecordSubtotal::_cal_adjust_type arg)
  {
    msg_.cal_adjust = std::move(arg);
    return Init_LoadRecordSubtotal_passes(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_zero_weight
{
public:
  explicit Init_LoadRecordSubtotal_zero_weight(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_cal_adjust zero_weight(::job_mgr_interfaces::msg::LoadRecordSubtotal::_zero_weight_type arg)
  {
    msg_.zero_weight = std::move(arg);
    return Init_LoadRecordSubtotal_cal_adjust(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_icon_type
{
public:
  explicit Init_LoadRecordSubtotal_icon_type(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_zero_weight icon_type(::job_mgr_interfaces::msg::LoadRecordSubtotal::_icon_type_type arg)
  {
    msg_.icon_type = std::move(arg);
    return Init_LoadRecordSubtotal_zero_weight(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_tag4
{
public:
  explicit Init_LoadRecordSubtotal_tag4(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_icon_type tag4(::job_mgr_interfaces::msg::LoadRecordSubtotal::_tag4_type arg)
  {
    msg_.tag4 = std::move(arg);
    return Init_LoadRecordSubtotal_icon_type(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_tag3
{
public:
  explicit Init_LoadRecordSubtotal_tag3(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_tag4 tag3(::job_mgr_interfaces::msg::LoadRecordSubtotal::_tag3_type arg)
  {
    msg_.tag3 = std::move(arg);
    return Init_LoadRecordSubtotal_tag4(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_tag2
{
public:
  explicit Init_LoadRecordSubtotal_tag2(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_tag3 tag2(::job_mgr_interfaces::msg::LoadRecordSubtotal::_tag2_type arg)
  {
    msg_.tag2 = std::move(arg);
    return Init_LoadRecordSubtotal_tag3(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_tag1
{
public:
  explicit Init_LoadRecordSubtotal_tag1(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_tag2 tag1(::job_mgr_interfaces::msg::LoadRecordSubtotal::_tag1_type arg)
  {
    msg_.tag1 = std::move(arg);
    return Init_LoadRecordSubtotal_tag2(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_custom_list_name4
{
public:
  explicit Init_LoadRecordSubtotal_custom_list_name4(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_tag1 custom_list_name4(::job_mgr_interfaces::msg::LoadRecordSubtotal::_custom_list_name4_type arg)
  {
    msg_.custom_list_name4 = std::move(arg);
    return Init_LoadRecordSubtotal_tag1(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_custom_list_name3
{
public:
  explicit Init_LoadRecordSubtotal_custom_list_name3(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_custom_list_name4 custom_list_name3(::job_mgr_interfaces::msg::LoadRecordSubtotal::_custom_list_name3_type arg)
  {
    msg_.custom_list_name3 = std::move(arg);
    return Init_LoadRecordSubtotal_custom_list_name4(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_custom_list_name2
{
public:
  explicit Init_LoadRecordSubtotal_custom_list_name2(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_custom_list_name3 custom_list_name2(::job_mgr_interfaces::msg::LoadRecordSubtotal::_custom_list_name2_type arg)
  {
    msg_.custom_list_name2 = std::move(arg);
    return Init_LoadRecordSubtotal_custom_list_name3(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_custom_list_name1
{
public:
  explicit Init_LoadRecordSubtotal_custom_list_name1(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_custom_list_name2 custom_list_name1(::job_mgr_interfaces::msg::LoadRecordSubtotal::_custom_list_name1_type arg)
  {
    msg_.custom_list_name1 = std::move(arg);
    return Init_LoadRecordSubtotal_custom_list_name2(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_material_density
{
public:
  explicit Init_LoadRecordSubtotal_material_density(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_custom_list_name1 material_density(::job_mgr_interfaces::msg::LoadRecordSubtotal::_material_density_type arg)
  {
    msg_.material_density = std::move(arg);
    return Init_LoadRecordSubtotal_custom_list_name1(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_material_name
{
public:
  explicit Init_LoadRecordSubtotal_material_name(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_material_density material_name(::job_mgr_interfaces::msg::LoadRecordSubtotal::_material_name_type arg)
  {
    msg_.material_name = std::move(arg);
    return Init_LoadRecordSubtotal_material_density(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_material_id
{
public:
  explicit Init_LoadRecordSubtotal_material_id(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_material_name material_id(::job_mgr_interfaces::msg::LoadRecordSubtotal::_material_id_type arg)
  {
    msg_.material_id = std::move(arg);
    return Init_LoadRecordSubtotal_material_name(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_target_passes
{
public:
  explicit Init_LoadRecordSubtotal_target_passes(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_material_id target_passes(::job_mgr_interfaces::msg::LoadRecordSubtotal::_target_passes_type arg)
  {
    msg_.target_passes = std::move(arg);
    return Init_LoadRecordSubtotal_material_id(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_target_proportion
{
public:
  explicit Init_LoadRecordSubtotal_target_proportion(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_target_passes target_proportion(::job_mgr_interfaces::msg::LoadRecordSubtotal::_target_proportion_type arg)
  {
    msg_.target_proportion = std::move(arg);
    return Init_LoadRecordSubtotal_target_passes(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_truck_target_weight_tonnes
{
public:
  explicit Init_LoadRecordSubtotal_truck_target_weight_tonnes(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_target_proportion truck_target_weight_tonnes(::job_mgr_interfaces::msg::LoadRecordSubtotal::_truck_target_weight_tonnes_type arg)
  {
    msg_.truck_target_weight_tonnes = std::move(arg);
    return Init_LoadRecordSubtotal_target_proportion(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_truck_name
{
public:
  explicit Init_LoadRecordSubtotal_truck_name(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_truck_target_weight_tonnes truck_name(::job_mgr_interfaces::msg::LoadRecordSubtotal::_truck_name_type arg)
  {
    msg_.truck_name = std::move(arg);
    return Init_LoadRecordSubtotal_truck_target_weight_tonnes(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_truck_id
{
public:
  explicit Init_LoadRecordSubtotal_truck_id(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_truck_name truck_id(::job_mgr_interfaces::msg::LoadRecordSubtotal::_truck_id_type arg)
  {
    msg_.truck_id = std::move(arg);
    return Init_LoadRecordSubtotal_truck_name(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_end_time
{
public:
  explicit Init_LoadRecordSubtotal_end_time(::job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
  : msg_(msg)
  {}
  Init_LoadRecordSubtotal_truck_id end_time(::job_mgr_interfaces::msg::LoadRecordSubtotal::_end_time_type arg)
  {
    msg_.end_time = std::move(arg);
    return Init_LoadRecordSubtotal_truck_id(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

class Init_LoadRecordSubtotal_start_time
{
public:
  Init_LoadRecordSubtotal_start_time()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LoadRecordSubtotal_end_time start_time(::job_mgr_interfaces::msg::LoadRecordSubtotal::_start_time_type arg)
  {
    msg_.start_time = std::move(arg);
    return Init_LoadRecordSubtotal_end_time(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordSubtotal msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::LoadRecordSubtotal>()
{
  return job_mgr_interfaces::msg::builder::Init_LoadRecordSubtotal_start_time();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_SUBTOTAL__BUILDER_HPP_
