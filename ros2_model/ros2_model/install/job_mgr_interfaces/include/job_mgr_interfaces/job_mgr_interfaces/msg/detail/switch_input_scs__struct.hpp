// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/SwitchInputScs.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/switch_input_scs.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__SWITCH_INPUT_SCS__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__SWITCH_INPUT_SCS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'stg_values'
#include "job_mgr_interfaces/msg/detail/stg__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__SwitchInputScs __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__SwitchInputScs __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SwitchInputScs_
{
  using Type = SwitchInputScs_<ContainerAllocator>;

  explicit SwitchInputScs_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->stg_values.fill(job_mgr_interfaces::msg::STG_<ContainerAllocator>{_init});
    }
  }

  explicit SwitchInputScs_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stg_values(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->stg_values.fill(job_mgr_interfaces::msg::STG_<ContainerAllocator>{_alloc, _init});
    }
  }

  // field types and members
  using _stg_values_type =
    std::array<job_mgr_interfaces::msg::STG_<ContainerAllocator>, 4>;
  _stg_values_type stg_values;

  // setters for named parameter idiom
  Type & set__stg_values(
    const std::array<job_mgr_interfaces::msg::STG_<ContainerAllocator>, 4> & _arg)
  {
    this->stg_values = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::SwitchInputScs_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::SwitchInputScs_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::SwitchInputScs_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::SwitchInputScs_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::SwitchInputScs_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::SwitchInputScs_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::SwitchInputScs_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::SwitchInputScs_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::SwitchInputScs_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::SwitchInputScs_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__SwitchInputScs
    std::shared_ptr<job_mgr_interfaces::msg::SwitchInputScs_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__SwitchInputScs
    std::shared_ptr<job_mgr_interfaces::msg::SwitchInputScs_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SwitchInputScs_ & other) const
  {
    if (this->stg_values != other.stg_values) {
      return false;
    }
    return true;
  }
  bool operator!=(const SwitchInputScs_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SwitchInputScs_

// alias to use template instance with default allocator
using SwitchInputScs =
  job_mgr_interfaces::msg::SwitchInputScs_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__SWITCH_INPUT_SCS__STRUCT_HPP_
