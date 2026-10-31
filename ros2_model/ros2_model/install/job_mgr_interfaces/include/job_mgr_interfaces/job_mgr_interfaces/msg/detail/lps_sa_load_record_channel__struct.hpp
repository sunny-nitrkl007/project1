// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/LpsSaLoadRecordChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/lps_sa_load_record_channel.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_LOAD_RECORD_CHANNEL__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_LOAD_RECORD_CHANNEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'subtotal'
// Member 'subtotals'
#include "job_mgr_interfaces/msg/detail/load_record_subtotal__struct.hpp"
// Member 'store_time'
#include "job_mgr_interfaces/msg/detail/load_record_time_stamp__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__LpsSaLoadRecordChannel __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__LpsSaLoadRecordChannel __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaLoadRecordChannel_
{
  using Type = LpsSaLoadRecordChannel_<ContainerAllocator>;

  explicit LpsSaLoadRecordChannel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : subtotal(_init),
    store_time(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->store_action = 0;
      this->ticket_number = 0ul;
      this->ticket_id = "";
      this->product_id = "";
      this->equipment_id = "";
      this->weight_interval = 0.0f;
      this->weight_decimal_precision = 0l;
      this->weight_units = 0l;
      this->recipe_name = "";
      this->target_type = 0;
      this->total_target_weight = 0.0f;
      this->current_subtotal_index = 0;
    }
  }

  explicit LpsSaLoadRecordChannel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : subtotal(_alloc, _init),
    ticket_id(_alloc),
    product_id(_alloc),
    equipment_id(_alloc),
    recipe_name(_alloc),
    store_time(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->store_action = 0;
      this->ticket_number = 0ul;
      this->ticket_id = "";
      this->product_id = "";
      this->equipment_id = "";
      this->weight_interval = 0.0f;
      this->weight_decimal_precision = 0l;
      this->weight_units = 0l;
      this->recipe_name = "";
      this->target_type = 0;
      this->total_target_weight = 0.0f;
      this->current_subtotal_index = 0;
    }
  }

  // field types and members
  using _store_action_type =
    uint8_t;
  _store_action_type store_action;
  using _subtotal_type =
    job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator>;
  _subtotal_type subtotal;
  using _subtotals_type =
    std::vector<job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator>>>;
  _subtotals_type subtotals;
  using _ticket_number_type =
    uint32_t;
  _ticket_number_type ticket_number;
  using _ticket_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _ticket_id_type ticket_id;
  using _product_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _product_id_type product_id;
  using _equipment_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _equipment_id_type equipment_id;
  using _weight_interval_type =
    float;
  _weight_interval_type weight_interval;
  using _weight_decimal_precision_type =
    int32_t;
  _weight_decimal_precision_type weight_decimal_precision;
  using _weight_units_type =
    int32_t;
  _weight_units_type weight_units;
  using _recipe_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _recipe_name_type recipe_name;
  using _target_type_type =
    uint8_t;
  _target_type_type target_type;
  using _total_target_weight_type =
    float;
  _total_target_weight_type total_target_weight;
  using _current_subtotal_index_type =
    uint16_t;
  _current_subtotal_index_type current_subtotal_index;
  using _store_time_type =
    job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator>;
  _store_time_type store_time;

  // setters for named parameter idiom
  Type & set__store_action(
    const uint8_t & _arg)
  {
    this->store_action = _arg;
    return *this;
  }
  Type & set__subtotal(
    const job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator> & _arg)
  {
    this->subtotal = _arg;
    return *this;
  }
  Type & set__subtotals(
    const std::vector<job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator>>> & _arg)
  {
    this->subtotals = _arg;
    return *this;
  }
  Type & set__ticket_number(
    const uint32_t & _arg)
  {
    this->ticket_number = _arg;
    return *this;
  }
  Type & set__ticket_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->ticket_id = _arg;
    return *this;
  }
  Type & set__product_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->product_id = _arg;
    return *this;
  }
  Type & set__equipment_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->equipment_id = _arg;
    return *this;
  }
  Type & set__weight_interval(
    const float & _arg)
  {
    this->weight_interval = _arg;
    return *this;
  }
  Type & set__weight_decimal_precision(
    const int32_t & _arg)
  {
    this->weight_decimal_precision = _arg;
    return *this;
  }
  Type & set__weight_units(
    const int32_t & _arg)
  {
    this->weight_units = _arg;
    return *this;
  }
  Type & set__recipe_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->recipe_name = _arg;
    return *this;
  }
  Type & set__target_type(
    const uint8_t & _arg)
  {
    this->target_type = _arg;
    return *this;
  }
  Type & set__total_target_weight(
    const float & _arg)
  {
    this->total_target_weight = _arg;
    return *this;
  }
  Type & set__current_subtotal_index(
    const uint16_t & _arg)
  {
    this->current_subtotal_index = _arg;
    return *this;
  }
  Type & set__store_time(
    const job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator> & _arg)
  {
    this->store_time = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t STORE_ACTION_AUTO =
    0u;
  static constexpr uint8_t STORE_ACTION_EXTERNAL =
    1u;
  static constexpr uint8_t STORE_ACTION_UI =
    2u;
  static constexpr uint8_t STORE_ACTION_TICKET_NOT_FOR_TRADE =
    3u;
  static constexpr uint8_t STORE_ACTION_TICKET_LEGAL_FOR_TRADE =
    4u;
  static constexpr uint8_t TARGET_TYPE_SINGLE =
    0u;
  static constexpr uint8_t TARGET_TYPE_SPLIT =
    1u;
  static constexpr uint8_t TARGET_TYPE_BATCH =
    2u;
  static constexpr uint8_t TARGET_TYPE_MIX =
    3u;
  static constexpr uint8_t TARGET_TYPE_BLEND_LOADS =
    4u;
  static constexpr uint8_t TARGET_TYPE_BLEND_WEIGHT =
    5u;

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::LpsSaLoadRecordChannel_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::LpsSaLoadRecordChannel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::LpsSaLoadRecordChannel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::LpsSaLoadRecordChannel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::LpsSaLoadRecordChannel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::LpsSaLoadRecordChannel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::LpsSaLoadRecordChannel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::LpsSaLoadRecordChannel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::LpsSaLoadRecordChannel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::LpsSaLoadRecordChannel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__LpsSaLoadRecordChannel
    std::shared_ptr<job_mgr_interfaces::msg::LpsSaLoadRecordChannel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__LpsSaLoadRecordChannel
    std::shared_ptr<job_mgr_interfaces::msg::LpsSaLoadRecordChannel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaLoadRecordChannel_ & other) const
  {
    if (this->store_action != other.store_action) {
      return false;
    }
    if (this->subtotal != other.subtotal) {
      return false;
    }
    if (this->subtotals != other.subtotals) {
      return false;
    }
    if (this->ticket_number != other.ticket_number) {
      return false;
    }
    if (this->ticket_id != other.ticket_id) {
      return false;
    }
    if (this->product_id != other.product_id) {
      return false;
    }
    if (this->equipment_id != other.equipment_id) {
      return false;
    }
    if (this->weight_interval != other.weight_interval) {
      return false;
    }
    if (this->weight_decimal_precision != other.weight_decimal_precision) {
      return false;
    }
    if (this->weight_units != other.weight_units) {
      return false;
    }
    if (this->recipe_name != other.recipe_name) {
      return false;
    }
    if (this->target_type != other.target_type) {
      return false;
    }
    if (this->total_target_weight != other.total_target_weight) {
      return false;
    }
    if (this->current_subtotal_index != other.current_subtotal_index) {
      return false;
    }
    if (this->store_time != other.store_time) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaLoadRecordChannel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaLoadRecordChannel_

// alias to use template instance with default allocator
using LpsSaLoadRecordChannel =
  job_mgr_interfaces::msg::LpsSaLoadRecordChannel_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaLoadRecordChannel_<ContainerAllocator>::STORE_ACTION_AUTO;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaLoadRecordChannel_<ContainerAllocator>::STORE_ACTION_EXTERNAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaLoadRecordChannel_<ContainerAllocator>::STORE_ACTION_UI;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaLoadRecordChannel_<ContainerAllocator>::STORE_ACTION_TICKET_NOT_FOR_TRADE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaLoadRecordChannel_<ContainerAllocator>::STORE_ACTION_TICKET_LEGAL_FOR_TRADE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaLoadRecordChannel_<ContainerAllocator>::TARGET_TYPE_SINGLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaLoadRecordChannel_<ContainerAllocator>::TARGET_TYPE_SPLIT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaLoadRecordChannel_<ContainerAllocator>::TARGET_TYPE_BATCH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaLoadRecordChannel_<ContainerAllocator>::TARGET_TYPE_MIX;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaLoadRecordChannel_<ContainerAllocator>::TARGET_TYPE_BLEND_LOADS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaLoadRecordChannel_<ContainerAllocator>::TARGET_TYPE_BLEND_WEIGHT;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_LOAD_RECORD_CHANNEL__STRUCT_HPP_
