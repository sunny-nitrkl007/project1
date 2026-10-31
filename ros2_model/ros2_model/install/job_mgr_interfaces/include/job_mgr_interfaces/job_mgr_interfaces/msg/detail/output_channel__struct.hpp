// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/OutputChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/output_channel.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CHANNEL__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CHANNEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'commands'
#include "job_mgr_interfaces/msg/detail/output_cmd__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__OutputChannel __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__OutputChannel __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct OutputChannel_
{
  using Type = OutputChannel_<ContainerAllocator>;

  explicit OutputChannel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit OutputChannel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _commands_type =
    std::vector<job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator>>>;
  _commands_type commands;

  // setters for named parameter idiom
  Type & set__commands(
    const std::vector<job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<job_mgr_interfaces::msg::OutputCmd_<ContainerAllocator>>> & _arg)
  {
    this->commands = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::OutputChannel_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::OutputChannel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::OutputChannel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::OutputChannel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::OutputChannel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::OutputChannel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::OutputChannel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::OutputChannel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::OutputChannel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::OutputChannel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__OutputChannel
    std::shared_ptr<job_mgr_interfaces::msg::OutputChannel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__OutputChannel
    std::shared_ptr<job_mgr_interfaces::msg::OutputChannel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const OutputChannel_ & other) const
  {
    if (this->commands != other.commands) {
      return false;
    }
    return true;
  }
  bool operator!=(const OutputChannel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct OutputChannel_

// alias to use template instance with default allocator
using OutputChannel =
  job_mgr_interfaces::msg::OutputChannel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CHANNEL__STRUCT_HPP_
