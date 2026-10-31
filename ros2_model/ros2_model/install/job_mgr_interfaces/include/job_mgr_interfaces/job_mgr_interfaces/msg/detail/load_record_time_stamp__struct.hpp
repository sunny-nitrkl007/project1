// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/LoadRecordTimeStamp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/load_record_time_stamp.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_TIME_STAMP__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_TIME_STAMP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__LoadRecordTimeStamp __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__LoadRecordTimeStamp __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LoadRecordTimeStamp_
{
  using Type = LoadRecordTimeStamp_<ContainerAllocator>;

  explicit LoadRecordTimeStamp_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->utc_time_ns = 0ll;
      this->shm_time = 0ul;
    }
  }

  explicit LoadRecordTimeStamp_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->utc_time_ns = 0ll;
      this->shm_time = 0ul;
    }
  }

  // field types and members
  using _utc_time_ns_type =
    int64_t;
  _utc_time_ns_type utc_time_ns;
  using _shm_time_type =
    uint32_t;
  _shm_time_type shm_time;

  // setters for named parameter idiom
  Type & set__utc_time_ns(
    const int64_t & _arg)
  {
    this->utc_time_ns = _arg;
    return *this;
  }
  Type & set__shm_time(
    const uint32_t & _arg)
  {
    this->shm_time = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__LoadRecordTimeStamp
    std::shared_ptr<job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__LoadRecordTimeStamp
    std::shared_ptr<job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LoadRecordTimeStamp_ & other) const
  {
    if (this->utc_time_ns != other.utc_time_ns) {
      return false;
    }
    if (this->shm_time != other.shm_time) {
      return false;
    }
    return true;
  }
  bool operator!=(const LoadRecordTimeStamp_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LoadRecordTimeStamp_

// alias to use template instance with default allocator
using LoadRecordTimeStamp =
  job_mgr_interfaces::msg::LoadRecordTimeStamp_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_TIME_STAMP__STRUCT_HPP_
