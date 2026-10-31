// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/TruckTicket.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/truck_ticket.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_TICKET__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_TICKET__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__TruckTicket __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__TruckTicket __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TruckTicket_
{
  using Type = TruckTicket_<ContainerAllocator>;

  explicit TruckTicket_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->num_copies = 0;
      this->header_enabled = false;
      this->header_line1 = "";
      this->header_line2 = "";
      this->header_line3 = "";
      this->footer_line1 = "";
      this->bucket_weights_enabled = false;
      this->truck_weight_enabled = false;
      this->truck_id_enabled = false;
      this->material_id_enabled = false;
      this->store_time_enabled = false;
      this->ticket_number = 0ul;
      this->retention_period = 0;
    }
  }

  explicit TruckTicket_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header_line1(_alloc),
    header_line2(_alloc),
    header_line3(_alloc),
    footer_line1(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->num_copies = 0;
      this->header_enabled = false;
      this->header_line1 = "";
      this->header_line2 = "";
      this->header_line3 = "";
      this->footer_line1 = "";
      this->bucket_weights_enabled = false;
      this->truck_weight_enabled = false;
      this->truck_id_enabled = false;
      this->material_id_enabled = false;
      this->store_time_enabled = false;
      this->ticket_number = 0ul;
      this->retention_period = 0;
    }
  }

  // field types and members
  using _num_copies_type =
    uint8_t;
  _num_copies_type num_copies;
  using _header_enabled_type =
    bool;
  _header_enabled_type header_enabled;
  using _header_line1_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _header_line1_type header_line1;
  using _header_line2_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _header_line2_type header_line2;
  using _header_line3_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _header_line3_type header_line3;
  using _footer_line1_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _footer_line1_type footer_line1;
  using _bucket_weights_enabled_type =
    bool;
  _bucket_weights_enabled_type bucket_weights_enabled;
  using _truck_weight_enabled_type =
    bool;
  _truck_weight_enabled_type truck_weight_enabled;
  using _truck_id_enabled_type =
    bool;
  _truck_id_enabled_type truck_id_enabled;
  using _material_id_enabled_type =
    bool;
  _material_id_enabled_type material_id_enabled;
  using _store_time_enabled_type =
    bool;
  _store_time_enabled_type store_time_enabled;
  using _ticket_number_type =
    uint32_t;
  _ticket_number_type ticket_number;
  using _retention_period_type =
    uint16_t;
  _retention_period_type retention_period;

  // setters for named parameter idiom
  Type & set__num_copies(
    const uint8_t & _arg)
  {
    this->num_copies = _arg;
    return *this;
  }
  Type & set__header_enabled(
    const bool & _arg)
  {
    this->header_enabled = _arg;
    return *this;
  }
  Type & set__header_line1(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->header_line1 = _arg;
    return *this;
  }
  Type & set__header_line2(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->header_line2 = _arg;
    return *this;
  }
  Type & set__header_line3(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->header_line3 = _arg;
    return *this;
  }
  Type & set__footer_line1(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->footer_line1 = _arg;
    return *this;
  }
  Type & set__bucket_weights_enabled(
    const bool & _arg)
  {
    this->bucket_weights_enabled = _arg;
    return *this;
  }
  Type & set__truck_weight_enabled(
    const bool & _arg)
  {
    this->truck_weight_enabled = _arg;
    return *this;
  }
  Type & set__truck_id_enabled(
    const bool & _arg)
  {
    this->truck_id_enabled = _arg;
    return *this;
  }
  Type & set__material_id_enabled(
    const bool & _arg)
  {
    this->material_id_enabled = _arg;
    return *this;
  }
  Type & set__store_time_enabled(
    const bool & _arg)
  {
    this->store_time_enabled = _arg;
    return *this;
  }
  Type & set__ticket_number(
    const uint32_t & _arg)
  {
    this->ticket_number = _arg;
    return *this;
  }
  Type & set__retention_period(
    const uint16_t & _arg)
  {
    this->retention_period = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::TruckTicket_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::TruckTicket_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::TruckTicket_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::TruckTicket_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::TruckTicket_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::TruckTicket_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::TruckTicket_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::TruckTicket_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::TruckTicket_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::TruckTicket_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__TruckTicket
    std::shared_ptr<weigh_app_interfaces::msg::TruckTicket_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__TruckTicket
    std::shared_ptr<weigh_app_interfaces::msg::TruckTicket_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TruckTicket_ & other) const
  {
    if (this->num_copies != other.num_copies) {
      return false;
    }
    if (this->header_enabled != other.header_enabled) {
      return false;
    }
    if (this->header_line1 != other.header_line1) {
      return false;
    }
    if (this->header_line2 != other.header_line2) {
      return false;
    }
    if (this->header_line3 != other.header_line3) {
      return false;
    }
    if (this->footer_line1 != other.footer_line1) {
      return false;
    }
    if (this->bucket_weights_enabled != other.bucket_weights_enabled) {
      return false;
    }
    if (this->truck_weight_enabled != other.truck_weight_enabled) {
      return false;
    }
    if (this->truck_id_enabled != other.truck_id_enabled) {
      return false;
    }
    if (this->material_id_enabled != other.material_id_enabled) {
      return false;
    }
    if (this->store_time_enabled != other.store_time_enabled) {
      return false;
    }
    if (this->ticket_number != other.ticket_number) {
      return false;
    }
    if (this->retention_period != other.retention_period) {
      return false;
    }
    return true;
  }
  bool operator!=(const TruckTicket_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TruckTicket_

// alias to use template instance with default allocator
using TruckTicket =
  weigh_app_interfaces::msg::TruckTicket_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_TICKET__STRUCT_HPP_
