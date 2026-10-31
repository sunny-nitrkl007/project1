// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/J1939Name.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/j1939_name.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__J1939_NAME__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__J1939_NAME__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__J1939Name __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__J1939Name __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct J1939Name_
{
  using Type = J1939Name_<ContainerAllocator>;

  explicit J1939Name_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->industry_group = 0;
      this->vehicle_system = 0;
      this->vehicle_system_instance = 0;
      this->function = 0;
      this->function_instance = 0;
      this->ecu_instance = 0;
      this->manufacturer_code = 0;
    }
  }

  explicit J1939Name_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->industry_group = 0;
      this->vehicle_system = 0;
      this->vehicle_system_instance = 0;
      this->function = 0;
      this->function_instance = 0;
      this->ecu_instance = 0;
      this->manufacturer_code = 0;
    }
  }

  // field types and members
  using _industry_group_type =
    uint8_t;
  _industry_group_type industry_group;
  using _vehicle_system_type =
    uint8_t;
  _vehicle_system_type vehicle_system;
  using _vehicle_system_instance_type =
    uint8_t;
  _vehicle_system_instance_type vehicle_system_instance;
  using _function_type =
    uint8_t;
  _function_type function;
  using _function_instance_type =
    uint8_t;
  _function_instance_type function_instance;
  using _ecu_instance_type =
    uint8_t;
  _ecu_instance_type ecu_instance;
  using _manufacturer_code_type =
    uint16_t;
  _manufacturer_code_type manufacturer_code;

  // setters for named parameter idiom
  Type & set__industry_group(
    const uint8_t & _arg)
  {
    this->industry_group = _arg;
    return *this;
  }
  Type & set__vehicle_system(
    const uint8_t & _arg)
  {
    this->vehicle_system = _arg;
    return *this;
  }
  Type & set__vehicle_system_instance(
    const uint8_t & _arg)
  {
    this->vehicle_system_instance = _arg;
    return *this;
  }
  Type & set__function(
    const uint8_t & _arg)
  {
    this->function = _arg;
    return *this;
  }
  Type & set__function_instance(
    const uint8_t & _arg)
  {
    this->function_instance = _arg;
    return *this;
  }
  Type & set__ecu_instance(
    const uint8_t & _arg)
  {
    this->ecu_instance = _arg;
    return *this;
  }
  Type & set__manufacturer_code(
    const uint16_t & _arg)
  {
    this->manufacturer_code = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::J1939Name_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::J1939Name_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::J1939Name_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::J1939Name_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::J1939Name_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::J1939Name_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::J1939Name_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::J1939Name_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::J1939Name_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::J1939Name_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__J1939Name
    std::shared_ptr<job_mgr_interfaces::msg::J1939Name_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__J1939Name
    std::shared_ptr<job_mgr_interfaces::msg::J1939Name_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const J1939Name_ & other) const
  {
    if (this->industry_group != other.industry_group) {
      return false;
    }
    if (this->vehicle_system != other.vehicle_system) {
      return false;
    }
    if (this->vehicle_system_instance != other.vehicle_system_instance) {
      return false;
    }
    if (this->function != other.function) {
      return false;
    }
    if (this->function_instance != other.function_instance) {
      return false;
    }
    if (this->ecu_instance != other.ecu_instance) {
      return false;
    }
    if (this->manufacturer_code != other.manufacturer_code) {
      return false;
    }
    return true;
  }
  bool operator!=(const J1939Name_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct J1939Name_

// alias to use template instance with default allocator
using J1939Name =
  job_mgr_interfaces::msg::J1939Name_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__J1939_NAME__STRUCT_HPP_
