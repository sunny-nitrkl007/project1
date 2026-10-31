// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/OutputCmd.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/output_cmd.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CMD__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CMD__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__OutputCmd __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__OutputCmd __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct OutputCmd_
{
  using Type = OutputCmd_<ContainerAllocator>;

  explicit OutputCmd_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->output_port = 0;
      this->initial_state = 0;
      this->state_change_duration = 0;
      this->final_state = 0;
      this->total_duration = 0l;
    }
  }

  explicit OutputCmd_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->output_port = 0;
      this->initial_state = 0;
      this->state_change_duration = 0;
      this->final_state = 0;
      this->total_duration = 0l;
    }
  }

  // field types and members
  using _output_port_type =
    uint8_t;
  _output_port_type output_port;
  using _initial_state_type =
    uint8_t;
  _initial_state_type initial_state;
  using _state_change_duration_type =
    uint8_t;
  _state_change_duration_type state_change_duration;
  using _final_state_type =
    uint8_t;
  _final_state_type final_state;
  using _total_duration_type =
    int32_t;
  _total_duration_type total_duration;

  // setters for named parameter idiom
  Type & set__output_port(
    const uint8_t & _arg)
  {
    this->output_port = _arg;
    return *this;
  }
  Type & set__initial_state(
    const uint8_t & _arg)
  {
    this->initial_state = _arg;
    return *this;
  }
  Type & set__state_change_duration(
    const uint8_t & _arg)
  {
    this->state_change_duration = _arg;
    return *this;
  }
  Type & set__final_state(
    const uint8_t & _arg)
  {
    this->final_state = _arg;
    return *this;
  }
  Type & set__total_duration(
    const int32_t & _arg)
  {
    this->total_duration = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__OutputCmd
    std::shared_ptr<job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__OutputCmd
    std::shared_ptr<job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const OutputCmd_ & other) const
  {
    if (this->output_port != other.output_port) {
      return false;
    }
    if (this->initial_state != other.initial_state) {
      return false;
    }
    if (this->state_change_duration != other.state_change_duration) {
      return false;
    }
    if (this->final_state != other.final_state) {
      return false;
    }
    if (this->total_duration != other.total_duration) {
      return false;
    }
    return true;
  }
  bool operator!=(const OutputCmd_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct OutputCmd_

// alias to use template instance with default allocator
using OutputCmd =
  job_mgr_interfaces::msg::OutputCmd_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CMD__STRUCT_HPP_
