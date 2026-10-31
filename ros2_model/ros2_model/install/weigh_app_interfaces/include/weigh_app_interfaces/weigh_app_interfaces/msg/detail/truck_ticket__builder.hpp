// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/TruckTicket.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/truck_ticket.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_TICKET__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_TICKET__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/truck_ticket__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_TruckTicket_retention_period
{
public:
  explicit Init_TruckTicket_retention_period(::weigh_app_interfaces::msg::TruckTicket & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::TruckTicket retention_period(::weigh_app_interfaces::msg::TruckTicket::_retention_period_type arg)
  {
    msg_.retention_period = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TruckTicket msg_;
};

class Init_TruckTicket_ticket_number
{
public:
  explicit Init_TruckTicket_ticket_number(::weigh_app_interfaces::msg::TruckTicket & msg)
  : msg_(msg)
  {}
  Init_TruckTicket_retention_period ticket_number(::weigh_app_interfaces::msg::TruckTicket::_ticket_number_type arg)
  {
    msg_.ticket_number = std::move(arg);
    return Init_TruckTicket_retention_period(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TruckTicket msg_;
};

class Init_TruckTicket_store_time_enabled
{
public:
  explicit Init_TruckTicket_store_time_enabled(::weigh_app_interfaces::msg::TruckTicket & msg)
  : msg_(msg)
  {}
  Init_TruckTicket_ticket_number store_time_enabled(::weigh_app_interfaces::msg::TruckTicket::_store_time_enabled_type arg)
  {
    msg_.store_time_enabled = std::move(arg);
    return Init_TruckTicket_ticket_number(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TruckTicket msg_;
};

class Init_TruckTicket_material_id_enabled
{
public:
  explicit Init_TruckTicket_material_id_enabled(::weigh_app_interfaces::msg::TruckTicket & msg)
  : msg_(msg)
  {}
  Init_TruckTicket_store_time_enabled material_id_enabled(::weigh_app_interfaces::msg::TruckTicket::_material_id_enabled_type arg)
  {
    msg_.material_id_enabled = std::move(arg);
    return Init_TruckTicket_store_time_enabled(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TruckTicket msg_;
};

class Init_TruckTicket_truck_id_enabled
{
public:
  explicit Init_TruckTicket_truck_id_enabled(::weigh_app_interfaces::msg::TruckTicket & msg)
  : msg_(msg)
  {}
  Init_TruckTicket_material_id_enabled truck_id_enabled(::weigh_app_interfaces::msg::TruckTicket::_truck_id_enabled_type arg)
  {
    msg_.truck_id_enabled = std::move(arg);
    return Init_TruckTicket_material_id_enabled(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TruckTicket msg_;
};

class Init_TruckTicket_truck_weight_enabled
{
public:
  explicit Init_TruckTicket_truck_weight_enabled(::weigh_app_interfaces::msg::TruckTicket & msg)
  : msg_(msg)
  {}
  Init_TruckTicket_truck_id_enabled truck_weight_enabled(::weigh_app_interfaces::msg::TruckTicket::_truck_weight_enabled_type arg)
  {
    msg_.truck_weight_enabled = std::move(arg);
    return Init_TruckTicket_truck_id_enabled(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TruckTicket msg_;
};

class Init_TruckTicket_bucket_weights_enabled
{
public:
  explicit Init_TruckTicket_bucket_weights_enabled(::weigh_app_interfaces::msg::TruckTicket & msg)
  : msg_(msg)
  {}
  Init_TruckTicket_truck_weight_enabled bucket_weights_enabled(::weigh_app_interfaces::msg::TruckTicket::_bucket_weights_enabled_type arg)
  {
    msg_.bucket_weights_enabled = std::move(arg);
    return Init_TruckTicket_truck_weight_enabled(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TruckTicket msg_;
};

class Init_TruckTicket_footer_line1
{
public:
  explicit Init_TruckTicket_footer_line1(::weigh_app_interfaces::msg::TruckTicket & msg)
  : msg_(msg)
  {}
  Init_TruckTicket_bucket_weights_enabled footer_line1(::weigh_app_interfaces::msg::TruckTicket::_footer_line1_type arg)
  {
    msg_.footer_line1 = std::move(arg);
    return Init_TruckTicket_bucket_weights_enabled(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TruckTicket msg_;
};

class Init_TruckTicket_header_line3
{
public:
  explicit Init_TruckTicket_header_line3(::weigh_app_interfaces::msg::TruckTicket & msg)
  : msg_(msg)
  {}
  Init_TruckTicket_footer_line1 header_line3(::weigh_app_interfaces::msg::TruckTicket::_header_line3_type arg)
  {
    msg_.header_line3 = std::move(arg);
    return Init_TruckTicket_footer_line1(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TruckTicket msg_;
};

class Init_TruckTicket_header_line2
{
public:
  explicit Init_TruckTicket_header_line2(::weigh_app_interfaces::msg::TruckTicket & msg)
  : msg_(msg)
  {}
  Init_TruckTicket_header_line3 header_line2(::weigh_app_interfaces::msg::TruckTicket::_header_line2_type arg)
  {
    msg_.header_line2 = std::move(arg);
    return Init_TruckTicket_header_line3(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TruckTicket msg_;
};

class Init_TruckTicket_header_line1
{
public:
  explicit Init_TruckTicket_header_line1(::weigh_app_interfaces::msg::TruckTicket & msg)
  : msg_(msg)
  {}
  Init_TruckTicket_header_line2 header_line1(::weigh_app_interfaces::msg::TruckTicket::_header_line1_type arg)
  {
    msg_.header_line1 = std::move(arg);
    return Init_TruckTicket_header_line2(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TruckTicket msg_;
};

class Init_TruckTicket_header_enabled
{
public:
  explicit Init_TruckTicket_header_enabled(::weigh_app_interfaces::msg::TruckTicket & msg)
  : msg_(msg)
  {}
  Init_TruckTicket_header_line1 header_enabled(::weigh_app_interfaces::msg::TruckTicket::_header_enabled_type arg)
  {
    msg_.header_enabled = std::move(arg);
    return Init_TruckTicket_header_line1(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TruckTicket msg_;
};

class Init_TruckTicket_num_copies
{
public:
  Init_TruckTicket_num_copies()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TruckTicket_header_enabled num_copies(::weigh_app_interfaces::msg::TruckTicket::_num_copies_type arg)
  {
    msg_.num_copies = std::move(arg);
    return Init_TruckTicket_header_enabled(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TruckTicket msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::TruckTicket>()
{
  return weigh_app_interfaces::msg::builder::Init_TruckTicket_num_copies();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_TICKET__BUILDER_HPP_
