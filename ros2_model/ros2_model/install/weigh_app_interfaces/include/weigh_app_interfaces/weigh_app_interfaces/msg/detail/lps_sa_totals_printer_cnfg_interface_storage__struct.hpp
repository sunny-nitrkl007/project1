// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaTotalsPrinterCnfgInterfaceStorage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_totals_printer_cnfg_interface_storage.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG_INTERFACE_STORAGE__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG_INTERFACE_STORAGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'config'
#include "weigh_app_interfaces/msg/detail/lps_sa_totals_printer_cnfg__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfgInterfaceStorage __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfgInterfaceStorage __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaTotalsPrinterCnfgInterfaceStorage_
{
  using Type = LpsSaTotalsPrinterCnfgInterfaceStorage_<ContainerAllocator>;

  explicit LpsSaTotalsPrinterCnfgInterfaceStorage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : config(_init)
  {
    (void)_init;
  }

  explicit LpsSaTotalsPrinterCnfgInterfaceStorage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : config(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _config_type =
    weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg_<ContainerAllocator>;
  _config_type config;

  // setters for named parameter idiom
  Type & set__config(
    const weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg_<ContainerAllocator> & _arg)
  {
    this->config = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfgInterfaceStorage
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfgInterfaceStorage
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaTotalsPrinterCnfgInterfaceStorage_ & other) const
  {
    if (this->config != other.config) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaTotalsPrinterCnfgInterfaceStorage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaTotalsPrinterCnfgInterfaceStorage_

// alias to use template instance with default allocator
using LpsSaTotalsPrinterCnfgInterfaceStorage =
  weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG_INTERFACE_STORAGE__STRUCT_HPP_
