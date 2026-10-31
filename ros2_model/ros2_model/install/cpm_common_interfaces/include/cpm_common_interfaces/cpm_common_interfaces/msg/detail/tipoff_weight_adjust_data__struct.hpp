// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/TipoffWeightAdjustData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/tipoff_weight_adjust_data.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__TIPOFF_WEIGHT_ADJUST_DATA__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__TIPOFF_WEIGHT_ADJUST_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__TipoffWeightAdjustData __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__TipoffWeightAdjustData __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TipoffWeightAdjustData_
{
  using Type = TipoffWeightAdjustData_<ContainerAllocator>;

  explicit TipoffWeightAdjustData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tip_off_weight1 = 0.0f;
      this->weigh_range_weight1 = 0.0f;
      this->tip_off_weight2 = 0.0f;
      this->weigh_range_weight2 = 0.0f;
      this->new_data_flag = false;
      this->reset = false;
    }
  }

  explicit TipoffWeightAdjustData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tip_off_weight1 = 0.0f;
      this->weigh_range_weight1 = 0.0f;
      this->tip_off_weight2 = 0.0f;
      this->weigh_range_weight2 = 0.0f;
      this->new_data_flag = false;
      this->reset = false;
    }
  }

  // field types and members
  using _tip_off_weight1_type =
    float;
  _tip_off_weight1_type tip_off_weight1;
  using _weigh_range_weight1_type =
    float;
  _weigh_range_weight1_type weigh_range_weight1;
  using _tip_off_weight2_type =
    float;
  _tip_off_weight2_type tip_off_weight2;
  using _weigh_range_weight2_type =
    float;
  _weigh_range_weight2_type weigh_range_weight2;
  using _new_data_flag_type =
    bool;
  _new_data_flag_type new_data_flag;
  using _reset_type =
    bool;
  _reset_type reset;

  // setters for named parameter idiom
  Type & set__tip_off_weight1(
    const float & _arg)
  {
    this->tip_off_weight1 = _arg;
    return *this;
  }
  Type & set__weigh_range_weight1(
    const float & _arg)
  {
    this->weigh_range_weight1 = _arg;
    return *this;
  }
  Type & set__tip_off_weight2(
    const float & _arg)
  {
    this->tip_off_weight2 = _arg;
    return *this;
  }
  Type & set__weigh_range_weight2(
    const float & _arg)
  {
    this->weigh_range_weight2 = _arg;
    return *this;
  }
  Type & set__new_data_flag(
    const bool & _arg)
  {
    this->new_data_flag = _arg;
    return *this;
  }
  Type & set__reset(
    const bool & _arg)
  {
    this->reset = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::TipoffWeightAdjustData_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::TipoffWeightAdjustData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::TipoffWeightAdjustData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::TipoffWeightAdjustData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::TipoffWeightAdjustData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::TipoffWeightAdjustData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::TipoffWeightAdjustData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::TipoffWeightAdjustData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::TipoffWeightAdjustData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::TipoffWeightAdjustData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__TipoffWeightAdjustData
    std::shared_ptr<cpm_common_interfaces::msg::TipoffWeightAdjustData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__TipoffWeightAdjustData
    std::shared_ptr<cpm_common_interfaces::msg::TipoffWeightAdjustData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TipoffWeightAdjustData_ & other) const
  {
    if (this->tip_off_weight1 != other.tip_off_weight1) {
      return false;
    }
    if (this->weigh_range_weight1 != other.weigh_range_weight1) {
      return false;
    }
    if (this->tip_off_weight2 != other.tip_off_weight2) {
      return false;
    }
    if (this->weigh_range_weight2 != other.weigh_range_weight2) {
      return false;
    }
    if (this->new_data_flag != other.new_data_flag) {
      return false;
    }
    if (this->reset != other.reset) {
      return false;
    }
    return true;
  }
  bool operator!=(const TipoffWeightAdjustData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TipoffWeightAdjustData_

// alias to use template instance with default allocator
using TipoffWeightAdjustData =
  cpm_common_interfaces::msg::TipoffWeightAdjustData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__TIPOFF_WEIGHT_ADJUST_DATA__STRUCT_HPP_
