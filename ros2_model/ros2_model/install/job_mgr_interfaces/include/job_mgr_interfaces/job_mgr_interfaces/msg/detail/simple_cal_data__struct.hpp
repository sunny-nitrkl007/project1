// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/SimpleCalData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/simple_cal_data.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__SimpleCalData __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__SimpleCalData __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SimpleCalData_
{
  using Type = SimpleCalData_<ContainerAllocator>;

  explicit SimpleCalData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->time_stamp = "";
      this->truck_wt = 0.0f;
      this->zeroed_truck_wt = 0.0f;
    }
  }

  explicit SimpleCalData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : time_stamp(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->time_stamp = "";
      this->truck_wt = 0.0f;
      this->zeroed_truck_wt = 0.0f;
    }
  }

  // field types and members
  using _time_stamp_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _time_stamp_type time_stamp;
  using _truck_wt_type =
    float;
  _truck_wt_type truck_wt;
  using _zeroed_truck_wt_type =
    float;
  _zeroed_truck_wt_type zeroed_truck_wt;

  // setters for named parameter idiom
  Type & set__time_stamp(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->time_stamp = _arg;
    return *this;
  }
  Type & set__truck_wt(
    const float & _arg)
  {
    this->truck_wt = _arg;
    return *this;
  }
  Type & set__zeroed_truck_wt(
    const float & _arg)
  {
    this->zeroed_truck_wt = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__SimpleCalData
    std::shared_ptr<job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__SimpleCalData
    std::shared_ptr<job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SimpleCalData_ & other) const
  {
    if (this->time_stamp != other.time_stamp) {
      return false;
    }
    if (this->truck_wt != other.truck_wt) {
      return false;
    }
    if (this->zeroed_truck_wt != other.zeroed_truck_wt) {
      return false;
    }
    return true;
  }
  bool operator!=(const SimpleCalData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SimpleCalData_

// alias to use template instance with default allocator
using SimpleCalData =
  job_mgr_interfaces::msg::SimpleCalData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA__STRUCT_HPP_
