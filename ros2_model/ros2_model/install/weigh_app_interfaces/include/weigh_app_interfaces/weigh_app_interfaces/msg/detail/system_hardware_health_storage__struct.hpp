// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/SystemHardwareHealthStorage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/system_hardware_health_storage.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_STORAGE__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_STORAGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'list_of_remaining_disk_space'
#include "weigh_app_interfaces/msg/detail/disk_space_remain__struct.hpp"
// Member 'ecm_hw_version'
#include "weigh_app_interfaces/msg/detail/ecm_version_info__struct.hpp"
// Member 'list_of_ethernet_stats'
#include "weigh_app_interfaces/msg/detail/ethernet_stats_type__struct.hpp"
// Member 'per_core_cpu_data'
#include "weigh_app_interfaces/msg/detail/core_usage__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__SystemHardwareHealthStorage __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__SystemHardwareHealthStorage __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SystemHardwareHealthStorage_
{
  using Type = SystemHardwareHealthStorage_<ContainerAllocator>;

  explicit SystemHardwareHealthStorage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : ecm_hw_version(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->source_system = "";
      this->total_system_memory_kb = 0ul;
      this->available_system_memory_kb = 0ul;
      this->system_up_time_sec = 0.0;
      this->load_avg1min = 0.0;
      this->load_avg5min = 0.0;
      this->load_avg15min = 0.0;
      this->ecm_sw_version = "";
      this->software_group_part_number = "";
      this->software_group_description = "";
      this->software_group_release_date = "";
      this->eth0_tx_kbs = 0.0;
      this->eth0_rx_kbs = 0.0;
      this->eth1_tx_kbs = 0.0;
      this->eth1_rx_kbs = 0.0;
      this->system_cpu_usage_percent = 0.0;
      this->system_cpu_io_wait_percent = 0.0;
      this->system_cpu_irq_percent = 0.0;
      this->ecm_os_version = "";
      this->battery_voltage = 0.0;
    }
  }

  explicit SystemHardwareHealthStorage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : source_system(_alloc),
    ecm_sw_version(_alloc),
    software_group_part_number(_alloc),
    software_group_description(_alloc),
    software_group_release_date(_alloc),
    ecm_hw_version(_alloc, _init),
    ecm_os_version(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->source_system = "";
      this->total_system_memory_kb = 0ul;
      this->available_system_memory_kb = 0ul;
      this->system_up_time_sec = 0.0;
      this->load_avg1min = 0.0;
      this->load_avg5min = 0.0;
      this->load_avg15min = 0.0;
      this->ecm_sw_version = "";
      this->software_group_part_number = "";
      this->software_group_description = "";
      this->software_group_release_date = "";
      this->eth0_tx_kbs = 0.0;
      this->eth0_rx_kbs = 0.0;
      this->eth1_tx_kbs = 0.0;
      this->eth1_rx_kbs = 0.0;
      this->system_cpu_usage_percent = 0.0;
      this->system_cpu_io_wait_percent = 0.0;
      this->system_cpu_irq_percent = 0.0;
      this->ecm_os_version = "";
      this->battery_voltage = 0.0;
    }
  }

  // field types and members
  using _source_system_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _source_system_type source_system;
  using _total_system_memory_kb_type =
    uint32_t;
  _total_system_memory_kb_type total_system_memory_kb;
  using _available_system_memory_kb_type =
    uint32_t;
  _available_system_memory_kb_type available_system_memory_kb;
  using _list_of_remaining_disk_space_type =
    std::vector<weigh_app_interfaces::msg::DiskSpaceRemain_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<weigh_app_interfaces::msg::DiskSpaceRemain_<ContainerAllocator>>>;
  _list_of_remaining_disk_space_type list_of_remaining_disk_space;
  using _system_up_time_sec_type =
    double;
  _system_up_time_sec_type system_up_time_sec;
  using _load_avg1min_type =
    double;
  _load_avg1min_type load_avg1min;
  using _load_avg5min_type =
    double;
  _load_avg5min_type load_avg5min;
  using _load_avg15min_type =
    double;
  _load_avg15min_type load_avg15min;
  using _core_temperatures_c_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _core_temperatures_c_type core_temperatures_c;
  using _ecm_sw_version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _ecm_sw_version_type ecm_sw_version;
  using _software_group_part_number_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _software_group_part_number_type software_group_part_number;
  using _software_group_description_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _software_group_description_type software_group_description;
  using _software_group_release_date_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _software_group_release_date_type software_group_release_date;
  using _ecm_hw_version_type =
    weigh_app_interfaces::msg::EcmVersionInfo_<ContainerAllocator>;
  _ecm_hw_version_type ecm_hw_version;
  using _eth0_tx_kbs_type =
    double;
  _eth0_tx_kbs_type eth0_tx_kbs;
  using _eth0_rx_kbs_type =
    double;
  _eth0_rx_kbs_type eth0_rx_kbs;
  using _eth1_tx_kbs_type =
    double;
  _eth1_tx_kbs_type eth1_tx_kbs;
  using _eth1_rx_kbs_type =
    double;
  _eth1_rx_kbs_type eth1_rx_kbs;
  using _list_of_ethernet_stats_type =
    std::vector<weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator>>>;
  _list_of_ethernet_stats_type list_of_ethernet_stats;
  using _system_cpu_usage_percent_type =
    double;
  _system_cpu_usage_percent_type system_cpu_usage_percent;
  using _system_cpu_io_wait_percent_type =
    double;
  _system_cpu_io_wait_percent_type system_cpu_io_wait_percent;
  using _system_cpu_irq_percent_type =
    double;
  _system_cpu_irq_percent_type system_cpu_irq_percent;
  using _ecm_os_version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _ecm_os_version_type ecm_os_version;
  using _per_core_cpu_data_type =
    std::vector<weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator>>>;
  _per_core_cpu_data_type per_core_cpu_data;
  using _battery_voltage_type =
    double;
  _battery_voltage_type battery_voltage;

  // setters for named parameter idiom
  Type & set__source_system(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->source_system = _arg;
    return *this;
  }
  Type & set__total_system_memory_kb(
    const uint32_t & _arg)
  {
    this->total_system_memory_kb = _arg;
    return *this;
  }
  Type & set__available_system_memory_kb(
    const uint32_t & _arg)
  {
    this->available_system_memory_kb = _arg;
    return *this;
  }
  Type & set__list_of_remaining_disk_space(
    const std::vector<weigh_app_interfaces::msg::DiskSpaceRemain_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<weigh_app_interfaces::msg::DiskSpaceRemain_<ContainerAllocator>>> & _arg)
  {
    this->list_of_remaining_disk_space = _arg;
    return *this;
  }
  Type & set__system_up_time_sec(
    const double & _arg)
  {
    this->system_up_time_sec = _arg;
    return *this;
  }
  Type & set__load_avg1min(
    const double & _arg)
  {
    this->load_avg1min = _arg;
    return *this;
  }
  Type & set__load_avg5min(
    const double & _arg)
  {
    this->load_avg5min = _arg;
    return *this;
  }
  Type & set__load_avg15min(
    const double & _arg)
  {
    this->load_avg15min = _arg;
    return *this;
  }
  Type & set__core_temperatures_c(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->core_temperatures_c = _arg;
    return *this;
  }
  Type & set__ecm_sw_version(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->ecm_sw_version = _arg;
    return *this;
  }
  Type & set__software_group_part_number(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->software_group_part_number = _arg;
    return *this;
  }
  Type & set__software_group_description(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->software_group_description = _arg;
    return *this;
  }
  Type & set__software_group_release_date(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->software_group_release_date = _arg;
    return *this;
  }
  Type & set__ecm_hw_version(
    const weigh_app_interfaces::msg::EcmVersionInfo_<ContainerAllocator> & _arg)
  {
    this->ecm_hw_version = _arg;
    return *this;
  }
  Type & set__eth0_tx_kbs(
    const double & _arg)
  {
    this->eth0_tx_kbs = _arg;
    return *this;
  }
  Type & set__eth0_rx_kbs(
    const double & _arg)
  {
    this->eth0_rx_kbs = _arg;
    return *this;
  }
  Type & set__eth1_tx_kbs(
    const double & _arg)
  {
    this->eth1_tx_kbs = _arg;
    return *this;
  }
  Type & set__eth1_rx_kbs(
    const double & _arg)
  {
    this->eth1_rx_kbs = _arg;
    return *this;
  }
  Type & set__list_of_ethernet_stats(
    const std::vector<weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator>>> & _arg)
  {
    this->list_of_ethernet_stats = _arg;
    return *this;
  }
  Type & set__system_cpu_usage_percent(
    const double & _arg)
  {
    this->system_cpu_usage_percent = _arg;
    return *this;
  }
  Type & set__system_cpu_io_wait_percent(
    const double & _arg)
  {
    this->system_cpu_io_wait_percent = _arg;
    return *this;
  }
  Type & set__system_cpu_irq_percent(
    const double & _arg)
  {
    this->system_cpu_irq_percent = _arg;
    return *this;
  }
  Type & set__ecm_os_version(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->ecm_os_version = _arg;
    return *this;
  }
  Type & set__per_core_cpu_data(
    const std::vector<weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator>>> & _arg)
  {
    this->per_core_cpu_data = _arg;
    return *this;
  }
  Type & set__battery_voltage(
    const double & _arg)
  {
    this->battery_voltage = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::SystemHardwareHealthStorage_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::SystemHardwareHealthStorage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::SystemHardwareHealthStorage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::SystemHardwareHealthStorage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::SystemHardwareHealthStorage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::SystemHardwareHealthStorage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::SystemHardwareHealthStorage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::SystemHardwareHealthStorage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::SystemHardwareHealthStorage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::SystemHardwareHealthStorage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__SystemHardwareHealthStorage
    std::shared_ptr<weigh_app_interfaces::msg::SystemHardwareHealthStorage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__SystemHardwareHealthStorage
    std::shared_ptr<weigh_app_interfaces::msg::SystemHardwareHealthStorage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SystemHardwareHealthStorage_ & other) const
  {
    if (this->source_system != other.source_system) {
      return false;
    }
    if (this->total_system_memory_kb != other.total_system_memory_kb) {
      return false;
    }
    if (this->available_system_memory_kb != other.available_system_memory_kb) {
      return false;
    }
    if (this->list_of_remaining_disk_space != other.list_of_remaining_disk_space) {
      return false;
    }
    if (this->system_up_time_sec != other.system_up_time_sec) {
      return false;
    }
    if (this->load_avg1min != other.load_avg1min) {
      return false;
    }
    if (this->load_avg5min != other.load_avg5min) {
      return false;
    }
    if (this->load_avg15min != other.load_avg15min) {
      return false;
    }
    if (this->core_temperatures_c != other.core_temperatures_c) {
      return false;
    }
    if (this->ecm_sw_version != other.ecm_sw_version) {
      return false;
    }
    if (this->software_group_part_number != other.software_group_part_number) {
      return false;
    }
    if (this->software_group_description != other.software_group_description) {
      return false;
    }
    if (this->software_group_release_date != other.software_group_release_date) {
      return false;
    }
    if (this->ecm_hw_version != other.ecm_hw_version) {
      return false;
    }
    if (this->eth0_tx_kbs != other.eth0_tx_kbs) {
      return false;
    }
    if (this->eth0_rx_kbs != other.eth0_rx_kbs) {
      return false;
    }
    if (this->eth1_tx_kbs != other.eth1_tx_kbs) {
      return false;
    }
    if (this->eth1_rx_kbs != other.eth1_rx_kbs) {
      return false;
    }
    if (this->list_of_ethernet_stats != other.list_of_ethernet_stats) {
      return false;
    }
    if (this->system_cpu_usage_percent != other.system_cpu_usage_percent) {
      return false;
    }
    if (this->system_cpu_io_wait_percent != other.system_cpu_io_wait_percent) {
      return false;
    }
    if (this->system_cpu_irq_percent != other.system_cpu_irq_percent) {
      return false;
    }
    if (this->ecm_os_version != other.ecm_os_version) {
      return false;
    }
    if (this->per_core_cpu_data != other.per_core_cpu_data) {
      return false;
    }
    if (this->battery_voltage != other.battery_voltage) {
      return false;
    }
    return true;
  }
  bool operator!=(const SystemHardwareHealthStorage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SystemHardwareHealthStorage_

// alias to use template instance with default allocator
using SystemHardwareHealthStorage =
  weigh_app_interfaces::msg::SystemHardwareHealthStorage_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_STORAGE__STRUCT_HPP_
