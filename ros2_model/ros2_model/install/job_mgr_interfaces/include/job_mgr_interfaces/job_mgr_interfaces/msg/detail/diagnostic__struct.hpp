// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/Diagnostic.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/diagnostic.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__DIAGNOSTIC__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__DIAGNOSTIC__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'jname'
#include "job_mgr_interfaces/msg/detail/j1939_name__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__Diagnostic __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__Diagnostic __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Diagnostic_
{
  using Type = Diagnostic_<ContainerAllocator>;

  explicit Diagnostic_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : jname(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->cid = 0;
      this->fmi = 0;
      this->wci = 0;
      this->annunc_value = 0;
      this->description = "";
      this->subsystem = 0;
      this->gps_time_sec_us = 0ll;
      this->service_hour_meter_sec = 0ul;
      this->occurrence_count = 0;
      this->category = 0;
      this->status = 0;
      this->last_occurrence_set = false;
      this->last_occ_duration = 0;
      this->pid = 0ul;
      this->worst_case_val = 0ul;
      this->event_trig_val = 0ul;
    }
  }

  explicit Diagnostic_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : description(_alloc),
    jname(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->cid = 0;
      this->fmi = 0;
      this->wci = 0;
      this->annunc_value = 0;
      this->description = "";
      this->subsystem = 0;
      this->gps_time_sec_us = 0ll;
      this->service_hour_meter_sec = 0ul;
      this->occurrence_count = 0;
      this->category = 0;
      this->status = 0;
      this->last_occurrence_set = false;
      this->last_occ_duration = 0;
      this->pid = 0ul;
      this->worst_case_val = 0ul;
      this->event_trig_val = 0ul;
    }
  }

  // field types and members
  using _id_type =
    uint16_t;
  _id_type id;
  using _cid_type =
    uint16_t;
  _cid_type cid;
  using _fmi_type =
    uint8_t;
  _fmi_type fmi;
  using _wci_type =
    uint8_t;
  _wci_type wci;
  using _annunc_value_type =
    uint8_t;
  _annunc_value_type annunc_value;
  using _description_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _description_type description;
  using _subsystem_type =
    uint16_t;
  _subsystem_type subsystem;
  using _gps_time_sec_us_type =
    int64_t;
  _gps_time_sec_us_type gps_time_sec_us;
  using _service_hour_meter_sec_type =
    uint32_t;
  _service_hour_meter_sec_type service_hour_meter_sec;
  using _occurrence_count_type =
    uint16_t;
  _occurrence_count_type occurrence_count;
  using _category_type =
    uint8_t;
  _category_type category;
  using _status_type =
    uint8_t;
  _status_type status;
  using _last_occurrence_set_type =
    bool;
  _last_occurrence_set_type last_occurrence_set;
  using _last_occ_duration_type =
    uint16_t;
  _last_occ_duration_type last_occ_duration;
  using _pid_type =
    uint32_t;
  _pid_type pid;
  using _worst_case_val_type =
    uint32_t;
  _worst_case_val_type worst_case_val;
  using _event_trig_val_type =
    uint32_t;
  _event_trig_val_type event_trig_val;
  using _jname_type =
    job_mgr_interfaces::msg::J1939Name_<ContainerAllocator>;
  _jname_type jname;

  // setters for named parameter idiom
  Type & set__id(
    const uint16_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__cid(
    const uint16_t & _arg)
  {
    this->cid = _arg;
    return *this;
  }
  Type & set__fmi(
    const uint8_t & _arg)
  {
    this->fmi = _arg;
    return *this;
  }
  Type & set__wci(
    const uint8_t & _arg)
  {
    this->wci = _arg;
    return *this;
  }
  Type & set__annunc_value(
    const uint8_t & _arg)
  {
    this->annunc_value = _arg;
    return *this;
  }
  Type & set__description(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->description = _arg;
    return *this;
  }
  Type & set__subsystem(
    const uint16_t & _arg)
  {
    this->subsystem = _arg;
    return *this;
  }
  Type & set__gps_time_sec_us(
    const int64_t & _arg)
  {
    this->gps_time_sec_us = _arg;
    return *this;
  }
  Type & set__service_hour_meter_sec(
    const uint32_t & _arg)
  {
    this->service_hour_meter_sec = _arg;
    return *this;
  }
  Type & set__occurrence_count(
    const uint16_t & _arg)
  {
    this->occurrence_count = _arg;
    return *this;
  }
  Type & set__category(
    const uint8_t & _arg)
  {
    this->category = _arg;
    return *this;
  }
  Type & set__status(
    const uint8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__last_occurrence_set(
    const bool & _arg)
  {
    this->last_occurrence_set = _arg;
    return *this;
  }
  Type & set__last_occ_duration(
    const uint16_t & _arg)
  {
    this->last_occ_duration = _arg;
    return *this;
  }
  Type & set__pid(
    const uint32_t & _arg)
  {
    this->pid = _arg;
    return *this;
  }
  Type & set__worst_case_val(
    const uint32_t & _arg)
  {
    this->worst_case_val = _arg;
    return *this;
  }
  Type & set__event_trig_val(
    const uint32_t & _arg)
  {
    this->event_trig_val = _arg;
    return *this;
  }
  Type & set__jname(
    const job_mgr_interfaces::msg::J1939Name_<ContainerAllocator> & _arg)
  {
    this->jname = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__Diagnostic
    std::shared_ptr<job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__Diagnostic
    std::shared_ptr<job_mgr_interfaces::msg::Diagnostic_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Diagnostic_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->cid != other.cid) {
      return false;
    }
    if (this->fmi != other.fmi) {
      return false;
    }
    if (this->wci != other.wci) {
      return false;
    }
    if (this->annunc_value != other.annunc_value) {
      return false;
    }
    if (this->description != other.description) {
      return false;
    }
    if (this->subsystem != other.subsystem) {
      return false;
    }
    if (this->gps_time_sec_us != other.gps_time_sec_us) {
      return false;
    }
    if (this->service_hour_meter_sec != other.service_hour_meter_sec) {
      return false;
    }
    if (this->occurrence_count != other.occurrence_count) {
      return false;
    }
    if (this->category != other.category) {
      return false;
    }
    if (this->status != other.status) {
      return false;
    }
    if (this->last_occurrence_set != other.last_occurrence_set) {
      return false;
    }
    if (this->last_occ_duration != other.last_occ_duration) {
      return false;
    }
    if (this->pid != other.pid) {
      return false;
    }
    if (this->worst_case_val != other.worst_case_val) {
      return false;
    }
    if (this->event_trig_val != other.event_trig_val) {
      return false;
    }
    if (this->jname != other.jname) {
      return false;
    }
    return true;
  }
  bool operator!=(const Diagnostic_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Diagnostic_

// alias to use template instance with default allocator
using Diagnostic =
  job_mgr_interfaces::msg::Diagnostic_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__DIAGNOSTIC__STRUCT_HPP_
