// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaJobMgrSubtotalInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_job_mgr_subtotal_info.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_SUBTOTAL_INFO__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_SUBTOTAL_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaJobMgrSubtotalInfo __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaJobMgrSubtotalInfo __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaJobMgrSubtotalInfo_
{
  using Type = LpsSaJobMgrSubtotalInfo_<ContainerAllocator>;

  explicit LpsSaJobMgrSubtotalInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->subtotal_command = "";
      this->current_step_number = 0;
      this->new_step_number = 0;
      this->target_weight = 0.0f;
      this->target_proportion = 0;
      this->target_passes = 0;
      this->material_id = 0ul;
      this->material_name = "";
      this->material_density = 0.0f;
      this->icon_type = 0;
    }
  }

  explicit LpsSaJobMgrSubtotalInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : subtotal_command(_alloc),
    material_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->subtotal_command = "";
      this->current_step_number = 0;
      this->new_step_number = 0;
      this->target_weight = 0.0f;
      this->target_proportion = 0;
      this->target_passes = 0;
      this->material_id = 0ul;
      this->material_name = "";
      this->material_density = 0.0f;
      this->icon_type = 0;
    }
  }

  // field types and members
  using _subtotal_command_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _subtotal_command_type subtotal_command;
  using _current_step_number_type =
    uint16_t;
  _current_step_number_type current_step_number;
  using _new_step_number_type =
    uint16_t;
  _new_step_number_type new_step_number;
  using _target_weight_type =
    float;
  _target_weight_type target_weight;
  using _target_proportion_type =
    uint16_t;
  _target_proportion_type target_proportion;
  using _target_passes_type =
    uint16_t;
  _target_passes_type target_passes;
  using _material_id_type =
    uint32_t;
  _material_id_type material_id;
  using _material_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _material_name_type material_name;
  using _material_density_type =
    float;
  _material_density_type material_density;
  using _icon_type_type =
    uint8_t;
  _icon_type_type icon_type;

  // setters for named parameter idiom
  Type & set__subtotal_command(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->subtotal_command = _arg;
    return *this;
  }
  Type & set__current_step_number(
    const uint16_t & _arg)
  {
    this->current_step_number = _arg;
    return *this;
  }
  Type & set__new_step_number(
    const uint16_t & _arg)
  {
    this->new_step_number = _arg;
    return *this;
  }
  Type & set__target_weight(
    const float & _arg)
  {
    this->target_weight = _arg;
    return *this;
  }
  Type & set__target_proportion(
    const uint16_t & _arg)
  {
    this->target_proportion = _arg;
    return *this;
  }
  Type & set__target_passes(
    const uint16_t & _arg)
  {
    this->target_passes = _arg;
    return *this;
  }
  Type & set__material_id(
    const uint32_t & _arg)
  {
    this->material_id = _arg;
    return *this;
  }
  Type & set__material_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->material_name = _arg;
    return *this;
  }
  Type & set__material_density(
    const float & _arg)
  {
    this->material_density = _arg;
    return *this;
  }
  Type & set__icon_type(
    const uint8_t & _arg)
  {
    this->icon_type = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaJobMgrSubtotalInfo
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaJobMgrSubtotalInfo
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaJobMgrSubtotalInfo_ & other) const
  {
    if (this->subtotal_command != other.subtotal_command) {
      return false;
    }
    if (this->current_step_number != other.current_step_number) {
      return false;
    }
    if (this->new_step_number != other.new_step_number) {
      return false;
    }
    if (this->target_weight != other.target_weight) {
      return false;
    }
    if (this->target_proportion != other.target_proportion) {
      return false;
    }
    if (this->target_passes != other.target_passes) {
      return false;
    }
    if (this->material_id != other.material_id) {
      return false;
    }
    if (this->material_name != other.material_name) {
      return false;
    }
    if (this->material_density != other.material_density) {
      return false;
    }
    if (this->icon_type != other.icon_type) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaJobMgrSubtotalInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaJobMgrSubtotalInfo_

// alias to use template instance with default allocator
using LpsSaJobMgrSubtotalInfo =
  cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_SUBTOTAL_INFO__STRUCT_HPP_
