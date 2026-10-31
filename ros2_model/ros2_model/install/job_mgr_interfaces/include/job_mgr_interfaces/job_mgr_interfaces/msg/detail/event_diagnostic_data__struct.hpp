// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/EventDiagnosticData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/event_diagnostic_data.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__EVENT_DIAGNOSTIC_DATA__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__EVENT_DIAGNOSTIC_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'active_diagnostics'
#include "job_mgr_interfaces/msg/detail/diagnostic__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__EventDiagnosticData __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__EventDiagnosticData __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct EventDiagnosticData_
{
  using Type = EventDiagnosticData_<ContainerAllocator>;

  explicit EventDiagnosticData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->dnsname = "";
      this->payload_crc = 0ul;
      this->payload_last_update_time_us = 0ll;
      this->highest_warning_level = 0;
      this->highest_annunciation_level = 0;
      this->source = "";
    }
  }

  explicit EventDiagnosticData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : dnsname(_alloc),
    source(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->dnsname = "";
      this->payload_crc = 0ul;
      this->payload_last_update_time_us = 0ll;
      this->highest_warning_level = 0;
      this->highest_annunciation_level = 0;
      this->source = "";
    }
  }

  // field types and members
  using _dnsname_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _dnsname_type dnsname;
  using _active_diagnostics_type =
    std::vector<job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator>>>;
  _active_diagnostics_type active_diagnostics;
  using _payload_crc_type =
    uint32_t;
  _payload_crc_type payload_crc;
  using _payload_last_update_time_us_type =
    int64_t;
  _payload_last_update_time_us_type payload_last_update_time_us;
  using _highest_warning_level_type =
    uint8_t;
  _highest_warning_level_type highest_warning_level;
  using _highest_annunciation_level_type =
    uint8_t;
  _highest_annunciation_level_type highest_annunciation_level;
  using _source_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _source_type source;

  // setters for named parameter idiom
  Type & set__dnsname(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->dnsname = _arg;
    return *this;
  }
  Type & set__active_diagnostics(
    const std::vector<job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator>>> & _arg)
  {
    this->active_diagnostics = _arg;
    return *this;
  }
  Type & set__payload_crc(
    const uint32_t & _arg)
  {
    this->payload_crc = _arg;
    return *this;
  }
  Type & set__payload_last_update_time_us(
    const int64_t & _arg)
  {
    this->payload_last_update_time_us = _arg;
    return *this;
  }
  Type & set__highest_warning_level(
    const uint8_t & _arg)
  {
    this->highest_warning_level = _arg;
    return *this;
  }
  Type & set__highest_annunciation_level(
    const uint8_t & _arg)
  {
    this->highest_annunciation_level = _arg;
    return *this;
  }
  Type & set__source(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->source = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::EventDiagnosticData_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::EventDiagnosticData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::EventDiagnosticData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::EventDiagnosticData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::EventDiagnosticData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::EventDiagnosticData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::EventDiagnosticData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::EventDiagnosticData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::EventDiagnosticData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::EventDiagnosticData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__EventDiagnosticData
    std::shared_ptr<job_mgr_interfaces::msg::EventDiagnosticData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__EventDiagnosticData
    std::shared_ptr<job_mgr_interfaces::msg::EventDiagnosticData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EventDiagnosticData_ & other) const
  {
    if (this->dnsname != other.dnsname) {
      return false;
    }
    if (this->active_diagnostics != other.active_diagnostics) {
      return false;
    }
    if (this->payload_crc != other.payload_crc) {
      return false;
    }
    if (this->payload_last_update_time_us != other.payload_last_update_time_us) {
      return false;
    }
    if (this->highest_warning_level != other.highest_warning_level) {
      return false;
    }
    if (this->highest_annunciation_level != other.highest_annunciation_level) {
      return false;
    }
    if (this->source != other.source) {
      return false;
    }
    return true;
  }
  bool operator!=(const EventDiagnosticData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EventDiagnosticData_

// alias to use template instance with default allocator
using EventDiagnosticData =
  job_mgr_interfaces::msg::EventDiagnosticData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__EVENT_DIAGNOSTIC_DATA__STRUCT_HPP_
