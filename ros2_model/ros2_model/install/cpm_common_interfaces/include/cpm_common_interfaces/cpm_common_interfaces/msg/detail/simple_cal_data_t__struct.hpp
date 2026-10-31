// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/SimpleCalDataT.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/simple_cal_data_t.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA_T__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA_T__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__SimpleCalDataT __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__SimpleCalDataT __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SimpleCalDataT_
{
  using Type = SimpleCalDataT_<ContainerAllocator>;

  explicit SimpleCalDataT_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->time_stamp = "";
      this->adjtruckweight = 0.0f;
      this->zeroed_truck_wt = 0.0f;
      this->new_data_flag = false;
    }
  }

  explicit SimpleCalDataT_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : time_stamp(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->time_stamp = "";
      this->adjtruckweight = 0.0f;
      this->zeroed_truck_wt = 0.0f;
      this->new_data_flag = false;
    }
  }

  // field types and members
  using _time_stamp_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _time_stamp_type time_stamp;
  using _adjtruckweight_type =
    float;
  _adjtruckweight_type adjtruckweight;
  using _zeroed_truck_wt_type =
    float;
  _zeroed_truck_wt_type zeroed_truck_wt;
  using _new_data_flag_type =
    bool;
  _new_data_flag_type new_data_flag;

  // setters for named parameter idiom
  Type & set__time_stamp(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->time_stamp = _arg;
    return *this;
  }
  Type & set__adjtruckweight(
    const float & _arg)
  {
    this->adjtruckweight = _arg;
    return *this;
  }
  Type & set__zeroed_truck_wt(
    const float & _arg)
  {
    this->zeroed_truck_wt = _arg;
    return *this;
  }
  Type & set__new_data_flag(
    const bool & _arg)
  {
    this->new_data_flag = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::SimpleCalDataT_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::SimpleCalDataT_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::SimpleCalDataT_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::SimpleCalDataT_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::SimpleCalDataT_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::SimpleCalDataT_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::SimpleCalDataT_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::SimpleCalDataT_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::SimpleCalDataT_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::SimpleCalDataT_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__SimpleCalDataT
    std::shared_ptr<cpm_common_interfaces::msg::SimpleCalDataT_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__SimpleCalDataT
    std::shared_ptr<cpm_common_interfaces::msg::SimpleCalDataT_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SimpleCalDataT_ & other) const
  {
    if (this->time_stamp != other.time_stamp) {
      return false;
    }
    if (this->adjtruckweight != other.adjtruckweight) {
      return false;
    }
    if (this->zeroed_truck_wt != other.zeroed_truck_wt) {
      return false;
    }
    if (this->new_data_flag != other.new_data_flag) {
      return false;
    }
    return true;
  }
  bool operator!=(const SimpleCalDataT_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SimpleCalDataT_

// alias to use template instance with default allocator
using SimpleCalDataT =
  cpm_common_interfaces::msg::SimpleCalDataT_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA_T__STRUCT_HPP_
