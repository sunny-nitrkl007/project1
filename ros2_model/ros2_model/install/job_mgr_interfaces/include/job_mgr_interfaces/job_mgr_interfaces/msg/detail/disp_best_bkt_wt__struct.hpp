// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/DispBestBktWt.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/disp_best_bkt_wt.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__DISP_BEST_BKT_WT__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__DISP_BEST_BKT_WT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__DispBestBktWt __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__DispBestBktWt __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DispBestBktWt_
{
  using Type = DispBestBktWt_<ContainerAllocator>;

  explicit DispBestBktWt_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->val = 0.0f;
      this->is_ok = false;
    }
  }

  explicit DispBestBktWt_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->val = 0.0f;
      this->is_ok = false;
    }
  }

  // field types and members
  using _val_type =
    float;
  _val_type val;
  using _is_ok_type =
    bool;
  _is_ok_type is_ok;

  // setters for named parameter idiom
  Type & set__val(
    const float & _arg)
  {
    this->val = _arg;
    return *this;
  }
  Type & set__is_ok(
    const bool & _arg)
  {
    this->is_ok = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::DispBestBktWt_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::DispBestBktWt_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::DispBestBktWt_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::DispBestBktWt_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::DispBestBktWt_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::DispBestBktWt_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::DispBestBktWt_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::DispBestBktWt_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::DispBestBktWt_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::DispBestBktWt_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__DispBestBktWt
    std::shared_ptr<job_mgr_interfaces::msg::DispBestBktWt_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__DispBestBktWt
    std::shared_ptr<job_mgr_interfaces::msg::DispBestBktWt_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DispBestBktWt_ & other) const
  {
    if (this->val != other.val) {
      return false;
    }
    if (this->is_ok != other.is_ok) {
      return false;
    }
    return true;
  }
  bool operator!=(const DispBestBktWt_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DispBestBktWt_

// alias to use template instance with default allocator
using DispBestBktWt =
  job_mgr_interfaces::msg::DispBestBktWt_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__DISP_BEST_BKT_WT__STRUCT_HPP_
