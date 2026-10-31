// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/DataLinkData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/data_link_data.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'params'
#include "weigh_app_interfaces/msg/detail/data_link_param__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__DataLinkData __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__DataLinkData __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DataLinkData_
{
  using Type = DataLinkData_<ContainerAllocator>;

  explicit DataLinkData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit DataLinkData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _params_type =
    std::vector<weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator>>>;
  _params_type params;

  // setters for named parameter idiom
  Type & set__params(
    const std::vector<weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator>>> & _arg)
  {
    this->params = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::DataLinkData_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::DataLinkData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::DataLinkData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::DataLinkData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::DataLinkData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::DataLinkData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::DataLinkData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::DataLinkData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::DataLinkData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::DataLinkData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__DataLinkData
    std::shared_ptr<weigh_app_interfaces::msg::DataLinkData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__DataLinkData
    std::shared_ptr<weigh_app_interfaces::msg::DataLinkData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DataLinkData_ & other) const
  {
    if (this->params != other.params) {
      return false;
    }
    return true;
  }
  bool operator!=(const DataLinkData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DataLinkData_

// alias to use template instance with default allocator
using DataLinkData =
  weigh_app_interfaces::msg::DataLinkData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__STRUCT_HPP_
