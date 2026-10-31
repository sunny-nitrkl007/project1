// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/PartNumbers.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/part_numbers.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__PART_NUMBERS__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__PART_NUMBERS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/part_numbers__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_PartNumbers_equipment_id_set
{
public:
  explicit Init_PartNumbers_equipment_id_set(::weigh_app_interfaces::msg::PartNumbers & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::PartNumbers equipment_id_set(::weigh_app_interfaces::msg::PartNumbers::_equipment_id_set_type arg)
  {
    msg_.equipment_id_set = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

class Init_PartNumbers_ecm_serial_num_set
{
public:
  explicit Init_PartNumbers_ecm_serial_num_set(::weigh_app_interfaces::msg::PartNumbers & msg)
  : msg_(msg)
  {}
  Init_PartNumbers_equipment_id_set ecm_serial_num_set(::weigh_app_interfaces::msg::PartNumbers::_ecm_serial_num_set_type arg)
  {
    msg_.ecm_serial_num_set = std::move(arg);
    return Init_PartNumbers_equipment_id_set(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

class Init_PartNumbers_model_num_set
{
public:
  explicit Init_PartNumbers_model_num_set(::weigh_app_interfaces::msg::PartNumbers & msg)
  : msg_(msg)
  {}
  Init_PartNumbers_ecm_serial_num_set model_num_set(::weigh_app_interfaces::msg::PartNumbers::_model_num_set_type arg)
  {
    msg_.model_num_set = std::move(arg);
    return Init_PartNumbers_ecm_serial_num_set(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

class Init_PartNumbers_ecm_part_num_set
{
public:
  explicit Init_PartNumbers_ecm_part_num_set(::weigh_app_interfaces::msg::PartNumbers & msg)
  : msg_(msg)
  {}
  Init_PartNumbers_model_num_set ecm_part_num_set(::weigh_app_interfaces::msg::PartNumbers::_ecm_part_num_set_type arg)
  {
    msg_.ecm_part_num_set = std::move(arg);
    return Init_PartNumbers_model_num_set(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

class Init_PartNumbers_sw_group_description_set
{
public:
  explicit Init_PartNumbers_sw_group_description_set(::weigh_app_interfaces::msg::PartNumbers & msg)
  : msg_(msg)
  {}
  Init_PartNumbers_ecm_part_num_set sw_group_description_set(::weigh_app_interfaces::msg::PartNumbers::_sw_group_description_set_type arg)
  {
    msg_.sw_group_description_set = std::move(arg);
    return Init_PartNumbers_ecm_part_num_set(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

class Init_PartNumbers_sw_group_release_date_set
{
public:
  explicit Init_PartNumbers_sw_group_release_date_set(::weigh_app_interfaces::msg::PartNumbers & msg)
  : msg_(msg)
  {}
  Init_PartNumbers_sw_group_description_set sw_group_release_date_set(::weigh_app_interfaces::msg::PartNumbers::_sw_group_release_date_set_type arg)
  {
    msg_.sw_group_release_date_set = std::move(arg);
    return Init_PartNumbers_sw_group_description_set(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

class Init_PartNumbers_sw_group_part_num_set
{
public:
  explicit Init_PartNumbers_sw_group_part_num_set(::weigh_app_interfaces::msg::PartNumbers & msg)
  : msg_(msg)
  {}
  Init_PartNumbers_sw_group_release_date_set sw_group_part_num_set(::weigh_app_interfaces::msg::PartNumbers::_sw_group_part_num_set_type arg)
  {
    msg_.sw_group_part_num_set = std::move(arg);
    return Init_PartNumbers_sw_group_release_date_set(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

class Init_PartNumbers_product_id_num_set
{
public:
  explicit Init_PartNumbers_product_id_num_set(::weigh_app_interfaces::msg::PartNumbers & msg)
  : msg_(msg)
  {}
  Init_PartNumbers_sw_group_part_num_set product_id_num_set(::weigh_app_interfaces::msg::PartNumbers::_product_id_num_set_type arg)
  {
    msg_.product_id_num_set = std::move(arg);
    return Init_PartNumbers_sw_group_part_num_set(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

class Init_PartNumbers_ecm_serial_num
{
public:
  explicit Init_PartNumbers_ecm_serial_num(::weigh_app_interfaces::msg::PartNumbers & msg)
  : msg_(msg)
  {}
  Init_PartNumbers_product_id_num_set ecm_serial_num(::weigh_app_interfaces::msg::PartNumbers::_ecm_serial_num_type arg)
  {
    msg_.ecm_serial_num = std::move(arg);
    return Init_PartNumbers_product_id_num_set(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

class Init_PartNumbers_model_num
{
public:
  explicit Init_PartNumbers_model_num(::weigh_app_interfaces::msg::PartNumbers & msg)
  : msg_(msg)
  {}
  Init_PartNumbers_ecm_serial_num model_num(::weigh_app_interfaces::msg::PartNumbers::_model_num_type arg)
  {
    msg_.model_num = std::move(arg);
    return Init_PartNumbers_ecm_serial_num(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

class Init_PartNumbers_ecm_part_num
{
public:
  explicit Init_PartNumbers_ecm_part_num(::weigh_app_interfaces::msg::PartNumbers & msg)
  : msg_(msg)
  {}
  Init_PartNumbers_model_num ecm_part_num(::weigh_app_interfaces::msg::PartNumbers::_ecm_part_num_type arg)
  {
    msg_.ecm_part_num = std::move(arg);
    return Init_PartNumbers_model_num(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

class Init_PartNumbers_sw_group_description
{
public:
  explicit Init_PartNumbers_sw_group_description(::weigh_app_interfaces::msg::PartNumbers & msg)
  : msg_(msg)
  {}
  Init_PartNumbers_ecm_part_num sw_group_description(::weigh_app_interfaces::msg::PartNumbers::_sw_group_description_type arg)
  {
    msg_.sw_group_description = std::move(arg);
    return Init_PartNumbers_ecm_part_num(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

class Init_PartNumbers_sw_group_release_date
{
public:
  explicit Init_PartNumbers_sw_group_release_date(::weigh_app_interfaces::msg::PartNumbers & msg)
  : msg_(msg)
  {}
  Init_PartNumbers_sw_group_description sw_group_release_date(::weigh_app_interfaces::msg::PartNumbers::_sw_group_release_date_type arg)
  {
    msg_.sw_group_release_date = std::move(arg);
    return Init_PartNumbers_sw_group_description(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

class Init_PartNumbers_sw_group_part_num
{
public:
  explicit Init_PartNumbers_sw_group_part_num(::weigh_app_interfaces::msg::PartNumbers & msg)
  : msg_(msg)
  {}
  Init_PartNumbers_sw_group_release_date sw_group_part_num(::weigh_app_interfaces::msg::PartNumbers::_sw_group_part_num_type arg)
  {
    msg_.sw_group_part_num = std::move(arg);
    return Init_PartNumbers_sw_group_release_date(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

class Init_PartNumbers_equipment_id
{
public:
  explicit Init_PartNumbers_equipment_id(::weigh_app_interfaces::msg::PartNumbers & msg)
  : msg_(msg)
  {}
  Init_PartNumbers_sw_group_part_num equipment_id(::weigh_app_interfaces::msg::PartNumbers::_equipment_id_type arg)
  {
    msg_.equipment_id = std::move(arg);
    return Init_PartNumbers_sw_group_part_num(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

class Init_PartNumbers_product_id_num
{
public:
  Init_PartNumbers_product_id_num()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PartNumbers_equipment_id product_id_num(::weigh_app_interfaces::msg::PartNumbers::_product_id_num_type arg)
  {
    msg_.product_id_num = std::move(arg);
    return Init_PartNumbers_equipment_id(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PartNumbers msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::PartNumbers>()
{
  return weigh_app_interfaces::msg::builder::Init_PartNumbers_product_id_num();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__PART_NUMBERS__BUILDER_HPP_
