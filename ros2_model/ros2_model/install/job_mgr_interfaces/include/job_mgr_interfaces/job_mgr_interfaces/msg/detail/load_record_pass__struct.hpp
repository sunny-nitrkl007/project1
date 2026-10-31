// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/LoadRecordPass.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/load_record_pass.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_PASS__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_PASS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'time'
#include "job_mgr_interfaces/msg/detail/load_record_time_stamp__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__LoadRecordPass __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__LoadRecordPass __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LoadRecordPass_
{
  using Type = LoadRecordPass_<ContainerAllocator>;

  explicit LoadRecordPass_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : time(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->weight_tonnes = 0.0f;
      this->calc_method = 0;
    }
  }

  explicit LoadRecordPass_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : time(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->weight_tonnes = 0.0f;
      this->calc_method = 0;
    }
  }

  // field types and members
  using _weight_tonnes_type =
    float;
  _weight_tonnes_type weight_tonnes;
  using _calc_method_type =
    uint16_t;
  _calc_method_type calc_method;
  using _time_type =
    job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator>;
  _time_type time;

  // setters for named parameter idiom
  Type & set__weight_tonnes(
    const float & _arg)
  {
    this->weight_tonnes = _arg;
    return *this;
  }
  Type & set__calc_method(
    const uint16_t & _arg)
  {
    this->calc_method = _arg;
    return *this;
  }
  Type & set__time(
    const job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator> & _arg)
  {
    this->time = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__LoadRecordPass
    std::shared_ptr<job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__LoadRecordPass
    std::shared_ptr<job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LoadRecordPass_ & other) const
  {
    if (this->weight_tonnes != other.weight_tonnes) {
      return false;
    }
    if (this->calc_method != other.calc_method) {
      return false;
    }
    if (this->time != other.time) {
      return false;
    }
    return true;
  }
  bool operator!=(const LoadRecordPass_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LoadRecordPass_

// alias to use template instance with default allocator
using LoadRecordPass =
  job_mgr_interfaces::msg::LoadRecordPass_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_PASS__STRUCT_HPP_
