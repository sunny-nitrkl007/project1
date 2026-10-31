// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/J1939Name.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/j1939_name.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__J1939_NAME__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__J1939_NAME__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/j1939_name__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_J1939Name_manufacturer_code
{
public:
  explicit Init_J1939Name_manufacturer_code(::job_mgr_interfaces::msg::J1939Name & msg)
  : msg_(msg)
  {}
  ::job_mgr_interfaces::msg::J1939Name manufacturer_code(::job_mgr_interfaces::msg::J1939Name::_manufacturer_code_type arg)
  {
    msg_.manufacturer_code = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::J1939Name msg_;
};

class Init_J1939Name_ecu_instance
{
public:
  explicit Init_J1939Name_ecu_instance(::job_mgr_interfaces::msg::J1939Name & msg)
  : msg_(msg)
  {}
  Init_J1939Name_manufacturer_code ecu_instance(::job_mgr_interfaces::msg::J1939Name::_ecu_instance_type arg)
  {
    msg_.ecu_instance = std::move(arg);
    return Init_J1939Name_manufacturer_code(msg_);
  }

private:
  ::job_mgr_interfaces::msg::J1939Name msg_;
};

class Init_J1939Name_function_instance
{
public:
  explicit Init_J1939Name_function_instance(::job_mgr_interfaces::msg::J1939Name & msg)
  : msg_(msg)
  {}
  Init_J1939Name_ecu_instance function_instance(::job_mgr_interfaces::msg::J1939Name::_function_instance_type arg)
  {
    msg_.function_instance = std::move(arg);
    return Init_J1939Name_ecu_instance(msg_);
  }

private:
  ::job_mgr_interfaces::msg::J1939Name msg_;
};

class Init_J1939Name_function
{
public:
  explicit Init_J1939Name_function(::job_mgr_interfaces::msg::J1939Name & msg)
  : msg_(msg)
  {}
  Init_J1939Name_function_instance function(::job_mgr_interfaces::msg::J1939Name::_function_type arg)
  {
    msg_.function = std::move(arg);
    return Init_J1939Name_function_instance(msg_);
  }

private:
  ::job_mgr_interfaces::msg::J1939Name msg_;
};

class Init_J1939Name_vehicle_system_instance
{
public:
  explicit Init_J1939Name_vehicle_system_instance(::job_mgr_interfaces::msg::J1939Name & msg)
  : msg_(msg)
  {}
  Init_J1939Name_function vehicle_system_instance(::job_mgr_interfaces::msg::J1939Name::_vehicle_system_instance_type arg)
  {
    msg_.vehicle_system_instance = std::move(arg);
    return Init_J1939Name_function(msg_);
  }

private:
  ::job_mgr_interfaces::msg::J1939Name msg_;
};

class Init_J1939Name_vehicle_system
{
public:
  explicit Init_J1939Name_vehicle_system(::job_mgr_interfaces::msg::J1939Name & msg)
  : msg_(msg)
  {}
  Init_J1939Name_vehicle_system_instance vehicle_system(::job_mgr_interfaces::msg::J1939Name::_vehicle_system_type arg)
  {
    msg_.vehicle_system = std::move(arg);
    return Init_J1939Name_vehicle_system_instance(msg_);
  }

private:
  ::job_mgr_interfaces::msg::J1939Name msg_;
};

class Init_J1939Name_industry_group
{
public:
  Init_J1939Name_industry_group()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_J1939Name_vehicle_system industry_group(::job_mgr_interfaces::msg::J1939Name::_industry_group_type arg)
  {
    msg_.industry_group = std::move(arg);
    return Init_J1939Name_vehicle_system(msg_);
  }

private:
  ::job_mgr_interfaces::msg::J1939Name msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::J1939Name>()
{
  return job_mgr_interfaces::msg::builder::Init_J1939Name_industry_group();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__J1939_NAME__BUILDER_HPP_
