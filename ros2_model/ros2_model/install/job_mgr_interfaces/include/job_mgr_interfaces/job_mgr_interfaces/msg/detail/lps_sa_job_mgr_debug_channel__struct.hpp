// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/LpsSaJobMgrDebugChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/lps_sa_job_mgr_debug_channel.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_DEBUG_CHANNEL__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_DEBUG_CHANNEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__LpsSaJobMgrDebugChannel __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__LpsSaJobMgrDebugChannel __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaJobMgrDebugChannel_
{
  using Type = LpsSaJobMgrDebugChannel_<ContainerAllocator>;

  explicit LpsSaJobMgrDebugChannel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_state = 0ul;
      this->tipoff_assist_activation_count = 0ul;
    }
  }

  explicit LpsSaJobMgrDebugChannel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_state = 0ul;
      this->tipoff_assist_activation_count = 0ul;
    }
  }

  // field types and members
  using _current_state_type =
    uint32_t;
  _current_state_type current_state;
  using _tipoff_assist_activation_count_type =
    uint32_t;
  _tipoff_assist_activation_count_type tipoff_assist_activation_count;

  // setters for named parameter idiom
  Type & set__current_state(
    const uint32_t & _arg)
  {
    this->current_state = _arg;
    return *this;
  }
  Type & set__tipoff_assist_activation_count(
    const uint32_t & _arg)
  {
    this->tipoff_assist_activation_count = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__LpsSaJobMgrDebugChannel
    std::shared_ptr<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__LpsSaJobMgrDebugChannel
    std::shared_ptr<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaJobMgrDebugChannel_ & other) const
  {
    if (this->current_state != other.current_state) {
      return false;
    }
    if (this->tipoff_assist_activation_count != other.tipoff_assist_activation_count) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaJobMgrDebugChannel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaJobMgrDebugChannel_

// alias to use template instance with default allocator
using LpsSaJobMgrDebugChannel =
  job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_DEBUG_CHANNEL__STRUCT_HPP_
