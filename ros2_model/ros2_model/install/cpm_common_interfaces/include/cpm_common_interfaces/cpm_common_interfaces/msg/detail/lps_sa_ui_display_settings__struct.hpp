// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaUIDisplaySettings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_ui_display_settings.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_SETTINGS__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_SETTINGS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaUIDisplaySettings __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaUIDisplaySettings __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaUIDisplaySettings_
{
  using Type = LpsSaUIDisplaySettings_<ContainerAllocator>;

  explicit LpsSaUIDisplaySettings_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->units = 0;
      this->language = 0;
      this->brightness = 0;
      this->time_format = 0;
      this->date_format = 0;
      this->weight_units = 0l;
      this->weight_precision = 0l;
      this->service_mode_enable_code = 0;
      this->keyboard_layout_setting = 0;
    }
  }

  explicit LpsSaUIDisplaySettings_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->units = 0;
      this->language = 0;
      this->brightness = 0;
      this->time_format = 0;
      this->date_format = 0;
      this->weight_units = 0l;
      this->weight_precision = 0l;
      this->service_mode_enable_code = 0;
      this->keyboard_layout_setting = 0;
    }
  }

  // field types and members
  using _units_type =
    uint8_t;
  _units_type units;
  using _language_type =
    uint16_t;
  _language_type language;
  using _brightness_type =
    uint8_t;
  _brightness_type brightness;
  using _time_format_type =
    uint8_t;
  _time_format_type time_format;
  using _date_format_type =
    uint16_t;
  _date_format_type date_format;
  using _weight_units_type =
    int32_t;
  _weight_units_type weight_units;
  using _weight_precision_type =
    int32_t;
  _weight_precision_type weight_precision;
  using _service_mode_enable_code_type =
    uint16_t;
  _service_mode_enable_code_type service_mode_enable_code;
  using _keyboard_layout_setting_type =
    uint8_t;
  _keyboard_layout_setting_type keyboard_layout_setting;

  // setters for named parameter idiom
  Type & set__units(
    const uint8_t & _arg)
  {
    this->units = _arg;
    return *this;
  }
  Type & set__language(
    const uint16_t & _arg)
  {
    this->language = _arg;
    return *this;
  }
  Type & set__brightness(
    const uint8_t & _arg)
  {
    this->brightness = _arg;
    return *this;
  }
  Type & set__time_format(
    const uint8_t & _arg)
  {
    this->time_format = _arg;
    return *this;
  }
  Type & set__date_format(
    const uint16_t & _arg)
  {
    this->date_format = _arg;
    return *this;
  }
  Type & set__weight_units(
    const int32_t & _arg)
  {
    this->weight_units = _arg;
    return *this;
  }
  Type & set__weight_precision(
    const int32_t & _arg)
  {
    this->weight_precision = _arg;
    return *this;
  }
  Type & set__service_mode_enable_code(
    const uint16_t & _arg)
  {
    this->service_mode_enable_code = _arg;
    return *this;
  }
  Type & set__keyboard_layout_setting(
    const uint8_t & _arg)
  {
    this->keyboard_layout_setting = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t UNITS_METRIC =
    0u;
  static constexpr uint8_t UNITS_ENGLISH =
    1u;
  static constexpr uint16_t LANG_ENGLISH =
    0u;
  static constexpr uint16_t LANG_SPANISH =
    1u;
  static constexpr uint16_t LANG_FRENCH =
    2u;
  static constexpr uint16_t LANG_PORTUGUESE =
    3u;
  static constexpr uint16_t LANG_GERMAN =
    4u;
  static constexpr uint16_t LANG_NORWEGIAN =
    5u;
  static constexpr uint16_t LANG_SWEDISH =
    6u;
  static constexpr uint16_t LANG_FINNISH =
    7u;
  static constexpr uint16_t LANG_DUTCH =
    8u;
  static constexpr uint16_t LANG_DANISH =
    9u;
  static constexpr uint16_t LANG_ITALIAN =
    10u;
  static constexpr uint16_t LANG_GREEK =
    11u;
  static constexpr uint16_t LANG_TURKISH =
    12u;
  static constexpr uint16_t LANG_INDONESIAN =
    13u;
  static constexpr uint16_t LANG_RUSSIAN =
    14u;
  static constexpr uint16_t LANG_JAPANESE =
    15u;
  static constexpr uint16_t LANG_HUNGARIAN =
    16u;
  static constexpr uint16_t LANG_ICELANDIC =
    17u;
  static constexpr uint16_t LANG_ARABIC =
    18u;
  static constexpr uint16_t LANG_TRADITIONAL_CHINESE =
    19u;
  static constexpr uint16_t LANG_CZECH =
    20u;
  static constexpr uint16_t LANG_POLISH =
    21u;
  static constexpr uint16_t LANG_SIMPLIFIED_CHINESE =
    22u;
  static constexpr uint16_t LANG_THAI =
    23u;
  static constexpr uint16_t LANG_SLOVENIAN =
    24u;
  static constexpr uint16_t LANG_SLOVAKIAN =
    25u;
  static constexpr uint16_t LANG_ESTONIAN =
    26u;
  static constexpr uint16_t LANG_LATVIAN =
    27u;
  static constexpr uint16_t LANG_LITHUANIAN =
    28u;
  static constexpr uint16_t LANG_MALAYSIAN =
    29u;
  static constexpr uint16_t LANG_KOREAN =
    30u;
  static constexpr uint16_t LANG_PORTUGUESE_BRAZIL =
    31u;
  static constexpr uint16_t LANG_FARSI =
    32u;
  static constexpr uint16_t LANG_HEBREW =
    33u;
  static constexpr uint16_t LANG_SERBIAN =
    34u;
  static constexpr uint16_t LANG_CROATIAN =
    35u;
  static constexpr uint16_t LANG_BULGARIAN =
    36u;
  static constexpr uint16_t LANG_ROMANIAN =
    37u;
  static constexpr uint16_t LANG_VIETNAMESE =
    38u;
  static constexpr uint16_t LANG_MONGOLIAN =
    39u;
  static constexpr uint16_t LANG_MACEDONIAN =
    40u;
  static constexpr uint16_t LANG_BURMESE =
    41u;
  static constexpr uint16_t LANG_KHMER =
    42u;
  static constexpr uint16_t LANG_UKRAINIAN =
    43u;
  static constexpr uint16_t LANG_SPANISH_CASTILIAN_EAME =
    44u;
  static constexpr uint16_t LANG_FRENCH_EAME =
    45u;
  static constexpr uint16_t LANG_PORTUGUESE_EAME =
    46u;
  static constexpr uint16_t LANG_DUTCH_NETHERLANDS =
    47u;
  static constexpr uint16_t LANG_BURMESE_MYANMASA =
    48u;
  static constexpr uint16_t LANG_AFRIKAANS =
    49u;
  static constexpr uint16_t LANG_ALBANIAN =
    50u;
  static constexpr uint16_t LANG_ARMENIAN =
    51u;
  static constexpr uint16_t LANG_BOSNIAN =
    52u;
  static constexpr uint16_t LANG_DARI =
    53u;
  static constexpr uint16_t LANG_DUTCH_BELGIUM =
    54u;
  static constexpr uint16_t LANG_FRENCH_CANADIAN =
    55u;
  static constexpr uint16_t LANG_HINDI =
    56u;
  static constexpr uint16_t LANG_KAZAKH =
    57u;
  static constexpr uint16_t LANG_LAOTIAN =
    58u;
  static constexpr uint16_t LANG_SPANISH_LACD =
    59u;
  static constexpr uint16_t LANG_TAMIL =
    60u;
  static constexpr uint16_t LANG_TURKMEN =
    61u;
  static constexpr uint16_t LANG_URDU =
    62u;
  static constexpr uint8_t TIME_FORMAT_24HR =
    0u;
  static constexpr uint8_t TIME_FORMAT_12HR =
    1u;
  static constexpr uint16_t DATE_FORMAT_YYYY_MM_DD =
    1648u;
  static constexpr uint16_t DATE_FORMAT_MM_DD_YYYY =
    1649u;
  static constexpr uint16_t DATE_FORMAT_DD_MM_YYYY =
    1650u;
  static constexpr uint8_t KEYBOARD_QWERTY =
    0u;
  static constexpr uint8_t KEYBOARD_NATIVE =
    1u;
  static constexpr uint8_t KEYBOARD_MIXED =
    2u;

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::LpsSaUIDisplaySettings_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::LpsSaUIDisplaySettings_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaUIDisplaySettings_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaUIDisplaySettings_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaUIDisplaySettings_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaUIDisplaySettings_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaUIDisplaySettings_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaUIDisplaySettings_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaUIDisplaySettings_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaUIDisplaySettings_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaUIDisplaySettings
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaUIDisplaySettings_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaUIDisplaySettings
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaUIDisplaySettings_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaUIDisplaySettings_ & other) const
  {
    if (this->units != other.units) {
      return false;
    }
    if (this->language != other.language) {
      return false;
    }
    if (this->brightness != other.brightness) {
      return false;
    }
    if (this->time_format != other.time_format) {
      return false;
    }
    if (this->date_format != other.date_format) {
      return false;
    }
    if (this->weight_units != other.weight_units) {
      return false;
    }
    if (this->weight_precision != other.weight_precision) {
      return false;
    }
    if (this->service_mode_enable_code != other.service_mode_enable_code) {
      return false;
    }
    if (this->keyboard_layout_setting != other.keyboard_layout_setting) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaUIDisplaySettings_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaUIDisplaySettings_

// alias to use template instance with default allocator
using LpsSaUIDisplaySettings =
  cpm_common_interfaces::msg::LpsSaUIDisplaySettings_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaUIDisplaySettings_<ContainerAllocator>::UNITS_METRIC;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaUIDisplaySettings_<ContainerAllocator>::UNITS_ENGLISH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_ENGLISH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_SPANISH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_FRENCH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_PORTUGUESE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_GERMAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_NORWEGIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_SWEDISH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_FINNISH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_DUTCH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_DANISH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_ITALIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_GREEK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_TURKISH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_INDONESIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_RUSSIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_JAPANESE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_HUNGARIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_ICELANDIC;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_ARABIC;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_TRADITIONAL_CHINESE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_CZECH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_POLISH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_SIMPLIFIED_CHINESE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_THAI;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_SLOVENIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_SLOVAKIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_ESTONIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_LATVIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_LITHUANIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_MALAYSIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_KOREAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_PORTUGUESE_BRAZIL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_FARSI;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_HEBREW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_SERBIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_CROATIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_BULGARIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_ROMANIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_VIETNAMESE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_MONGOLIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_MACEDONIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_BURMESE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_KHMER;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_UKRAINIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_SPANISH_CASTILIAN_EAME;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_FRENCH_EAME;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_PORTUGUESE_EAME;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_DUTCH_NETHERLANDS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_BURMESE_MYANMASA;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_AFRIKAANS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_ALBANIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_ARMENIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_BOSNIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_DARI;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_DUTCH_BELGIUM;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_FRENCH_CANADIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_HINDI;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_KAZAKH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_LAOTIAN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_SPANISH_LACD;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_TAMIL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_TURKMEN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::LANG_URDU;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaUIDisplaySettings_<ContainerAllocator>::TIME_FORMAT_24HR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaUIDisplaySettings_<ContainerAllocator>::TIME_FORMAT_12HR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::DATE_FORMAT_YYYY_MM_DD;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::DATE_FORMAT_MM_DD_YYYY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaUIDisplaySettings_<ContainerAllocator>::DATE_FORMAT_DD_MM_YYYY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaUIDisplaySettings_<ContainerAllocator>::KEYBOARD_QWERTY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaUIDisplaySettings_<ContainerAllocator>::KEYBOARD_NATIVE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaUIDisplaySettings_<ContainerAllocator>::KEYBOARD_MIXED;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_SETTINGS__STRUCT_HPP_
