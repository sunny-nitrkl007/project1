// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/AutonomyConditionDiagnosticsTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/autonomy_condition_diagnostics_tx_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__AUTONOMY_CONDITION_DIAGNOSTICS_TX_CHANNEL__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__AUTONOMY_CONDITION_DIAGNOSTICS_TX_CHANNEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'sea_list'
#include "cpm_common_interfaces/msg/detail/sea__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__AutonomyConditionDiagnosticsTxChannel __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__AutonomyConditionDiagnosticsTxChannel __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AutonomyConditionDiagnosticsTxChannel_
{
  using Type = AutonomyConditionDiagnosticsTxChannel_<ContainerAllocator>;

  explicit AutonomyConditionDiagnosticsTxChannel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->time_point_ns = 0ll;
      this->display_ethernet_bad = false;
      this->product_link_ethernet_bad = false;
    }
  }

  explicit AutonomyConditionDiagnosticsTxChannel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->time_point_ns = 0ll;
      this->display_ethernet_bad = false;
      this->product_link_ethernet_bad = false;
    }
  }

  // field types and members
  using _time_point_ns_type =
    int64_t;
  _time_point_ns_type time_point_ns;
  using _display_ethernet_bad_type =
    bool;
  _display_ethernet_bad_type display_ethernet_bad;
  using _product_link_ethernet_bad_type =
    bool;
  _product_link_ethernet_bad_type product_link_ethernet_bad;
  using _sea_list_type =
    std::vector<cpm_common_interfaces::msg::SEA_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cpm_common_interfaces::msg::SEA_<ContainerAllocator>>>;
  _sea_list_type sea_list;

  // setters for named parameter idiom
  Type & set__time_point_ns(
    const int64_t & _arg)
  {
    this->time_point_ns = _arg;
    return *this;
  }
  Type & set__display_ethernet_bad(
    const bool & _arg)
  {
    this->display_ethernet_bad = _arg;
    return *this;
  }
  Type & set__product_link_ethernet_bad(
    const bool & _arg)
  {
    this->product_link_ethernet_bad = _arg;
    return *this;
  }
  Type & set__sea_list(
    const std::vector<cpm_common_interfaces::msg::SEA_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cpm_common_interfaces::msg::SEA_<ContainerAllocator>>> & _arg)
  {
    this->sea_list = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__AutonomyConditionDiagnosticsTxChannel
    std::shared_ptr<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__AutonomyConditionDiagnosticsTxChannel
    std::shared_ptr<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AutonomyConditionDiagnosticsTxChannel_ & other) const
  {
    if (this->time_point_ns != other.time_point_ns) {
      return false;
    }
    if (this->display_ethernet_bad != other.display_ethernet_bad) {
      return false;
    }
    if (this->product_link_ethernet_bad != other.product_link_ethernet_bad) {
      return false;
    }
    if (this->sea_list != other.sea_list) {
      return false;
    }
    return true;
  }
  bool operator!=(const AutonomyConditionDiagnosticsTxChannel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AutonomyConditionDiagnosticsTxChannel_

// alias to use template instance with default allocator
using AutonomyConditionDiagnosticsTxChannel =
  cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__AUTONOMY_CONDITION_DIAGNOSTICS_TX_CHANNEL__STRUCT_HPP_
