// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/DataLinkParam.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/data_link_param.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__DataLinkParam __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__DataLinkParam __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DataLinkParam_
{
  using Type = DataLinkParam_<ContainerAllocator>;

  explicit DataLinkParam_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->identifier_type = 0;
      this->sid = 0ul;
      this->param_id = 0ul;
      this->units = 0;
      this->scaling = 0.0f;
      this->offset = 0.0f;
      this->pid_data_received = false;
      this->last_value_dsi = 0;
      this->last_value_i16 = 0;
      this->last_value_u16 = 0;
      this->last_value_f32 = 0.0f;
      this->last_value_eng = 0.0;
      this->last_good_value_eng = 0.0;
      this->var_length_param_type = 0;
      this->var_length_param_dsi = 0;
    }
  }

  explicit DataLinkParam_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->identifier_type = 0;
      this->sid = 0ul;
      this->param_id = 0ul;
      this->units = 0;
      this->scaling = 0.0f;
      this->offset = 0.0f;
      this->pid_data_received = false;
      this->last_value_dsi = 0;
      this->last_value_i16 = 0;
      this->last_value_u16 = 0;
      this->last_value_f32 = 0.0f;
      this->last_value_eng = 0.0;
      this->last_good_value_eng = 0.0;
      this->var_length_param_type = 0;
      this->var_length_param_dsi = 0;
    }
  }

  // field types and members
  using _identifier_type_type =
    uint8_t;
  _identifier_type_type identifier_type;
  using _sid_type =
    uint32_t;
  _sid_type sid;
  using _param_id_type =
    uint32_t;
  _param_id_type param_id;
  using _units_type =
    uint8_t;
  _units_type units;
  using _scaling_type =
    float;
  _scaling_type scaling;
  using _offset_type =
    float;
  _offset_type offset;
  using _pid_data_received_type =
    bool;
  _pid_data_received_type pid_data_received;
  using _last_value_dsi_type =
    uint16_t;
  _last_value_dsi_type last_value_dsi;
  using _last_value_i16_type =
    int16_t;
  _last_value_i16_type last_value_i16;
  using _last_value_u16_type =
    uint16_t;
  _last_value_u16_type last_value_u16;
  using _last_value_f32_type =
    float;
  _last_value_f32_type last_value_f32;
  using _last_value_eng_type =
    double;
  _last_value_eng_type last_value_eng;
  using _last_good_value_eng_type =
    double;
  _last_good_value_eng_type last_good_value_eng;
  using _last_value_vector_type =
    std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>;
  _last_value_vector_type last_value_vector;
  using _var_param_block_type =
    std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>;
  _var_param_block_type var_param_block;
  using _var_length_param_type_type =
    uint8_t;
  _var_length_param_type_type var_length_param_type;
  using _var_length_param_dsi_type =
    uint16_t;
  _var_length_param_dsi_type var_length_param_dsi;

  // setters for named parameter idiom
  Type & set__identifier_type(
    const uint8_t & _arg)
  {
    this->identifier_type = _arg;
    return *this;
  }
  Type & set__sid(
    const uint32_t & _arg)
  {
    this->sid = _arg;
    return *this;
  }
  Type & set__param_id(
    const uint32_t & _arg)
  {
    this->param_id = _arg;
    return *this;
  }
  Type & set__units(
    const uint8_t & _arg)
  {
    this->units = _arg;
    return *this;
  }
  Type & set__scaling(
    const float & _arg)
  {
    this->scaling = _arg;
    return *this;
  }
  Type & set__offset(
    const float & _arg)
  {
    this->offset = _arg;
    return *this;
  }
  Type & set__pid_data_received(
    const bool & _arg)
  {
    this->pid_data_received = _arg;
    return *this;
  }
  Type & set__last_value_dsi(
    const uint16_t & _arg)
  {
    this->last_value_dsi = _arg;
    return *this;
  }
  Type & set__last_value_i16(
    const int16_t & _arg)
  {
    this->last_value_i16 = _arg;
    return *this;
  }
  Type & set__last_value_u16(
    const uint16_t & _arg)
  {
    this->last_value_u16 = _arg;
    return *this;
  }
  Type & set__last_value_f32(
    const float & _arg)
  {
    this->last_value_f32 = _arg;
    return *this;
  }
  Type & set__last_value_eng(
    const double & _arg)
  {
    this->last_value_eng = _arg;
    return *this;
  }
  Type & set__last_good_value_eng(
    const double & _arg)
  {
    this->last_good_value_eng = _arg;
    return *this;
  }
  Type & set__last_value_vector(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->last_value_vector = _arg;
    return *this;
  }
  Type & set__var_param_block(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->var_param_block = _arg;
    return *this;
  }
  Type & set__var_length_param_type(
    const uint8_t & _arg)
  {
    this->var_length_param_type = _arg;
    return *this;
  }
  Type & set__var_length_param_dsi(
    const uint16_t & _arg)
  {
    this->var_length_param_dsi = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t IDENTIFIER_TYPE_PID =
    0u;
  static constexpr uint8_t IDENTIFIER_TYPE_PUBLIC_PGN =
    1u;
  static constexpr uint8_t IDENTIFIER_TYPE_CAT_EXT =
    2u;
  static constexpr uint8_t IDENTIFIER_TYPE_PROP_A_PGN =
    3u;
  static constexpr uint8_t IDENTIFIER_TYPE_SPN =
    4u;
  static constexpr uint8_t UNITS_NO_UNIT =
    0u;
  static constexpr uint8_t UNITS_KPA =
    1u;
  static constexpr uint8_t UNITS_KPA2 =
    2u;
  static constexpr uint8_t UNITS_DEG_C =
    3u;
  static constexpr uint8_t UNITS_KM_PER_HR =
    4u;
  static constexpr uint8_t UNITS_RPM =
    5u;
  static constexpr uint8_t UNITS_VOLTS =
    6u;
  static constexpr uint8_t UNITS_LITERS =
    7u;
  static constexpr uint8_t UNITS_PERCENT =
    8u;
  static constexpr uint8_t UNITS_LTRS_PER_HR =
    9u;
  static constexpr uint8_t UNITS_DEG =
    10u;
  static constexpr uint8_t UNITS_MM =
    11u;
  static constexpr uint8_t UNITS_MM2 =
    12u;
  static constexpr uint8_t UNITS_PULSES_PER_KM =
    13u;
  static constexpr uint8_t UNITS_KW =
    14u;
  static constexpr uint8_t UNITS_HRS =
    15u;
  static constexpr uint8_t UNITS_SEC =
    16u;
  static constexpr uint8_t UNITS_MS =
    17u;
  static constexpr uint8_t UNITS_NM =
    18u;
  static constexpr uint8_t UNITS_MIN =
    19u;
  static constexpr uint8_t UNITS_RPM_PER_SEC =
    20u;
  static constexpr uint8_t UNITS_METERS_PER_SEC =
    21u;
  static constexpr uint8_t UNITS_HZ =
    22u;
  static constexpr uint8_t UNITS_AMPS =
    23u;
  static constexpr uint8_t UNITS_NM3_PER_HOUR =
    24u;
  static constexpr uint8_t UNITS_MJ_PER_NM3 =
    25u;
  static constexpr uint8_t UNITS_OHMS =
    26u;
  static constexpr uint8_t UNITS_METERS_PER_SEC2 =
    27u;
  static constexpr uint8_t UNITS_KG_PER_HR =
    28u;
  static constexpr uint8_t VAR_LENGTH_PARAM_TYPE_NOT_APPLICABLE =
    0u;
  static constexpr uint8_t VAR_LENGTH_PARAM_TYPE_GPS =
    1u;
  static constexpr uint8_t VAR_LENGTH_PARAM_TYPE_SPL_PID_REV_DATA_BYTE_ORDER =
    2u;
  static constexpr uint8_t VAR_LENGTH_PARAM_TYPE_TIME_ZONE =
    3u;
  static constexpr uint8_t VAR_LENGTH_PARAM_TYPE_PRODUCT_ID =
    4u;
  static constexpr uint8_t VAR_LENGTH_PARAM_TYPE_PGN =
    5u;
  static constexpr uint8_t VAR_LENGTH_PARAM_TYPE_SPN =
    6u;
  static constexpr uint8_t VAR_LENGTH_PARAM_TYPE_SECURITY_SYSTEM_CURRENT_KEY =
    7u;
  static constexpr uint8_t VAR_LENGTH_PARAM_TYPE_SECURITY_SYSTEM_CURRENT_SECURITY_ID =
    8u;
  static constexpr uint8_t VAR_LENGTH_PARAM_TYPE_UNSUPPORTED =
    9u;
  static constexpr uint8_t VAR_LENGTH_PARAM_TYPE_CAT_EXT =
    10u;

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__DataLinkParam
    std::shared_ptr<weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__DataLinkParam
    std::shared_ptr<weigh_app_interfaces::msg::DataLinkParam_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DataLinkParam_ & other) const
  {
    if (this->identifier_type != other.identifier_type) {
      return false;
    }
    if (this->sid != other.sid) {
      return false;
    }
    if (this->param_id != other.param_id) {
      return false;
    }
    if (this->units != other.units) {
      return false;
    }
    if (this->scaling != other.scaling) {
      return false;
    }
    if (this->offset != other.offset) {
      return false;
    }
    if (this->pid_data_received != other.pid_data_received) {
      return false;
    }
    if (this->last_value_dsi != other.last_value_dsi) {
      return false;
    }
    if (this->last_value_i16 != other.last_value_i16) {
      return false;
    }
    if (this->last_value_u16 != other.last_value_u16) {
      return false;
    }
    if (this->last_value_f32 != other.last_value_f32) {
      return false;
    }
    if (this->last_value_eng != other.last_value_eng) {
      return false;
    }
    if (this->last_good_value_eng != other.last_good_value_eng) {
      return false;
    }
    if (this->last_value_vector != other.last_value_vector) {
      return false;
    }
    if (this->var_param_block != other.var_param_block) {
      return false;
    }
    if (this->var_length_param_type != other.var_length_param_type) {
      return false;
    }
    if (this->var_length_param_dsi != other.var_length_param_dsi) {
      return false;
    }
    return true;
  }
  bool operator!=(const DataLinkParam_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DataLinkParam_

// alias to use template instance with default allocator
using DataLinkParam =
  weigh_app_interfaces::msg::DataLinkParam_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::IDENTIFIER_TYPE_PID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::IDENTIFIER_TYPE_PUBLIC_PGN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::IDENTIFIER_TYPE_CAT_EXT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::IDENTIFIER_TYPE_PROP_A_PGN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::IDENTIFIER_TYPE_SPN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_NO_UNIT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_KPA;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_KPA2;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_DEG_C;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_KM_PER_HR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_RPM;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_VOLTS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_LITERS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_PERCENT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_LTRS_PER_HR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_DEG;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_MM;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_MM2;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_PULSES_PER_KM;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_KW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_HRS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_SEC;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_MS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_NM;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_MIN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_RPM_PER_SEC;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_METERS_PER_SEC;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_HZ;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_AMPS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_NM3_PER_HOUR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_MJ_PER_NM3;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_OHMS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_METERS_PER_SEC2;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::UNITS_KG_PER_HR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::VAR_LENGTH_PARAM_TYPE_NOT_APPLICABLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::VAR_LENGTH_PARAM_TYPE_GPS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::VAR_LENGTH_PARAM_TYPE_SPL_PID_REV_DATA_BYTE_ORDER;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::VAR_LENGTH_PARAM_TYPE_TIME_ZONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::VAR_LENGTH_PARAM_TYPE_PRODUCT_ID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::VAR_LENGTH_PARAM_TYPE_PGN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::VAR_LENGTH_PARAM_TYPE_SPN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::VAR_LENGTH_PARAM_TYPE_SECURITY_SYSTEM_CURRENT_KEY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::VAR_LENGTH_PARAM_TYPE_SECURITY_SYSTEM_CURRENT_SECURITY_ID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::VAR_LENGTH_PARAM_TYPE_UNSUPPORTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DataLinkParam_<ContainerAllocator>::VAR_LENGTH_PARAM_TYPE_CAT_EXT;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__STRUCT_HPP_
