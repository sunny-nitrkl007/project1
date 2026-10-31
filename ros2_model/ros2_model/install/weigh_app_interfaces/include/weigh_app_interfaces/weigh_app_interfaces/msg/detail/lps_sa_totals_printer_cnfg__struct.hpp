// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaTotalsPrinterCnfg.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_totals_printer_cnfg.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'truck_ticket'
#include "weigh_app_interfaces/msg/detail/truck_ticket__struct.hpp"
// Member 'truck_report'
#include "weigh_app_interfaces/msg/detail/truck_report__struct.hpp"
// Member 'material_report'
#include "weigh_app_interfaces/msg/detail/material_report__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaTotalsPrinterCnfg_
{
  using Type = LpsSaTotalsPrinterCnfg_<ContainerAllocator>;

  explicit LpsSaTotalsPrinterCnfg_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : truck_ticket(_init),
    truck_report(_init),
    material_report(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->installed = false;
      this->leading_blank_lines = 0;
      this->trailing_blank_lines = 0;
      this->date_format = 0;
      this->date_separator = 0;
      this->udp_transfer_ip = "";
      this->udp_transfer_port = 0ul;
      this->udp_transfer_enabled = false;
    }
  }

  explicit LpsSaTotalsPrinterCnfg_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : truck_ticket(_alloc, _init),
    truck_report(_alloc, _init),
    material_report(_alloc, _init),
    udp_transfer_ip(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->installed = false;
      this->leading_blank_lines = 0;
      this->trailing_blank_lines = 0;
      this->date_format = 0;
      this->date_separator = 0;
      this->udp_transfer_ip = "";
      this->udp_transfer_port = 0ul;
      this->udp_transfer_enabled = false;
    }
  }

  // field types and members
  using _installed_type =
    bool;
  _installed_type installed;
  using _leading_blank_lines_type =
    uint8_t;
  _leading_blank_lines_type leading_blank_lines;
  using _trailing_blank_lines_type =
    uint8_t;
  _trailing_blank_lines_type trailing_blank_lines;
  using _date_format_type =
    uint16_t;
  _date_format_type date_format;
  using _date_separator_type =
    uint16_t;
  _date_separator_type date_separator;
  using _truck_ticket_type =
    weigh_app_interfaces::msg::TruckTicket_<ContainerAllocator>;
  _truck_ticket_type truck_ticket;
  using _truck_report_type =
    weigh_app_interfaces::msg::TruckReport_<ContainerAllocator>;
  _truck_report_type truck_report;
  using _material_report_type =
    weigh_app_interfaces::msg::MaterialReport_<ContainerAllocator>;
  _material_report_type material_report;
  using _udp_transfer_ip_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _udp_transfer_ip_type udp_transfer_ip;
  using _udp_transfer_port_type =
    uint32_t;
  _udp_transfer_port_type udp_transfer_port;
  using _udp_transfer_enabled_type =
    bool;
  _udp_transfer_enabled_type udp_transfer_enabled;

  // setters for named parameter idiom
  Type & set__installed(
    const bool & _arg)
  {
    this->installed = _arg;
    return *this;
  }
  Type & set__leading_blank_lines(
    const uint8_t & _arg)
  {
    this->leading_blank_lines = _arg;
    return *this;
  }
  Type & set__trailing_blank_lines(
    const uint8_t & _arg)
  {
    this->trailing_blank_lines = _arg;
    return *this;
  }
  Type & set__date_format(
    const uint16_t & _arg)
  {
    this->date_format = _arg;
    return *this;
  }
  Type & set__date_separator(
    const uint16_t & _arg)
  {
    this->date_separator = _arg;
    return *this;
  }
  Type & set__truck_ticket(
    const weigh_app_interfaces::msg::TruckTicket_<ContainerAllocator> & _arg)
  {
    this->truck_ticket = _arg;
    return *this;
  }
  Type & set__truck_report(
    const weigh_app_interfaces::msg::TruckReport_<ContainerAllocator> & _arg)
  {
    this->truck_report = _arg;
    return *this;
  }
  Type & set__material_report(
    const weigh_app_interfaces::msg::MaterialReport_<ContainerAllocator> & _arg)
  {
    this->material_report = _arg;
    return *this;
  }
  Type & set__udp_transfer_ip(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->udp_transfer_ip = _arg;
    return *this;
  }
  Type & set__udp_transfer_port(
    const uint32_t & _arg)
  {
    this->udp_transfer_port = _arg;
    return *this;
  }
  Type & set__udp_transfer_enabled(
    const bool & _arg)
  {
    this->udp_transfer_enabled = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t DATE_FORMAT_YYYY_MM_DD =
    1648u;
  static constexpr uint16_t DATE_FORMAT_MM_DD_YYYY =
    1649u;
  static constexpr uint16_t DATE_FORMAT_DD_MM_YYYY =
    1650u;
  static constexpr uint16_t DATE_FORMAT_YY_MM_DD =
    1651u;
  static constexpr uint16_t DATE_FORMAT_MM_DD_YY =
    1652u;
  static constexpr uint16_t DATE_FORMAT_DD_MM_YY =
    1653u;
  static constexpr uint16_t DATE_FORMAT_MM_DD =
    1654u;
  static constexpr uint16_t DATE_FORMAT_DD_MM =
    1655u;
  static constexpr uint16_t DATE_SEPARATOR_SLASH =
    1656u;
  static constexpr uint16_t DATE_SEPARATOR_HYPHEN =
    1657u;

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaTotalsPrinterCnfg_ & other) const
  {
    if (this->installed != other.installed) {
      return false;
    }
    if (this->leading_blank_lines != other.leading_blank_lines) {
      return false;
    }
    if (this->trailing_blank_lines != other.trailing_blank_lines) {
      return false;
    }
    if (this->date_format != other.date_format) {
      return false;
    }
    if (this->date_separator != other.date_separator) {
      return false;
    }
    if (this->truck_ticket != other.truck_ticket) {
      return false;
    }
    if (this->truck_report != other.truck_report) {
      return false;
    }
    if (this->material_report != other.material_report) {
      return false;
    }
    if (this->udp_transfer_ip != other.udp_transfer_ip) {
      return false;
    }
    if (this->udp_transfer_port != other.udp_transfer_port) {
      return false;
    }
    if (this->udp_transfer_enabled != other.udp_transfer_enabled) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaTotalsPrinterCnfg_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaTotalsPrinterCnfg_

// alias to use template instance with default allocator
using LpsSaTotalsPrinterCnfg =
  weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaTotalsPrinterCnfg_<ContainerAllocator>::DATE_FORMAT_YYYY_MM_DD;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaTotalsPrinterCnfg_<ContainerAllocator>::DATE_FORMAT_MM_DD_YYYY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaTotalsPrinterCnfg_<ContainerAllocator>::DATE_FORMAT_DD_MM_YYYY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaTotalsPrinterCnfg_<ContainerAllocator>::DATE_FORMAT_YY_MM_DD;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaTotalsPrinterCnfg_<ContainerAllocator>::DATE_FORMAT_MM_DD_YY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaTotalsPrinterCnfg_<ContainerAllocator>::DATE_FORMAT_DD_MM_YY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaTotalsPrinterCnfg_<ContainerAllocator>::DATE_FORMAT_MM_DD;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaTotalsPrinterCnfg_<ContainerAllocator>::DATE_FORMAT_DD_MM;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaTotalsPrinterCnfg_<ContainerAllocator>::DATE_SEPARATOR_SLASH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaTotalsPrinterCnfg_<ContainerAllocator>::DATE_SEPARATOR_HYPHEN;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG__STRUCT_HPP_
