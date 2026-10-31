// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/SystemHardwareHealthStorage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/system_hardware_health_storage.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_STORAGE__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_STORAGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/system_hardware_health_storage__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'list_of_remaining_disk_space'
#include "weigh_app_interfaces/msg/detail/disk_space_remain__traits.hpp"
// Member 'ecm_hw_version'
#include "weigh_app_interfaces/msg/detail/ecm_version_info__traits.hpp"
// Member 'list_of_ethernet_stats'
#include "weigh_app_interfaces/msg/detail/ethernet_stats_type__traits.hpp"
// Member 'per_core_cpu_data'
#include "weigh_app_interfaces/msg/detail/core_usage__traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const SystemHardwareHealthStorage & msg,
  std::ostream & out)
{
  out << "{";
  // member: source_system
  {
    out << "source_system: ";
    rosidl_generator_traits::value_to_yaml(msg.source_system, out);
    out << ", ";
  }

  // member: total_system_memory_kb
  {
    out << "total_system_memory_kb: ";
    rosidl_generator_traits::value_to_yaml(msg.total_system_memory_kb, out);
    out << ", ";
  }

  // member: available_system_memory_kb
  {
    out << "available_system_memory_kb: ";
    rosidl_generator_traits::value_to_yaml(msg.available_system_memory_kb, out);
    out << ", ";
  }

  // member: list_of_remaining_disk_space
  {
    if (msg.list_of_remaining_disk_space.size() == 0) {
      out << "list_of_remaining_disk_space: []";
    } else {
      out << "list_of_remaining_disk_space: [";
      size_t pending_items = msg.list_of_remaining_disk_space.size();
      for (auto item : msg.list_of_remaining_disk_space) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: system_up_time_sec
  {
    out << "system_up_time_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.system_up_time_sec, out);
    out << ", ";
  }

  // member: load_avg1min
  {
    out << "load_avg1min: ";
    rosidl_generator_traits::value_to_yaml(msg.load_avg1min, out);
    out << ", ";
  }

  // member: load_avg5min
  {
    out << "load_avg5min: ";
    rosidl_generator_traits::value_to_yaml(msg.load_avg5min, out);
    out << ", ";
  }

  // member: load_avg15min
  {
    out << "load_avg15min: ";
    rosidl_generator_traits::value_to_yaml(msg.load_avg15min, out);
    out << ", ";
  }

  // member: core_temperatures_c
  {
    if (msg.core_temperatures_c.size() == 0) {
      out << "core_temperatures_c: []";
    } else {
      out << "core_temperatures_c: [";
      size_t pending_items = msg.core_temperatures_c.size();
      for (auto item : msg.core_temperatures_c) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: ecm_sw_version
  {
    out << "ecm_sw_version: ";
    rosidl_generator_traits::value_to_yaml(msg.ecm_sw_version, out);
    out << ", ";
  }

  // member: software_group_part_number
  {
    out << "software_group_part_number: ";
    rosidl_generator_traits::value_to_yaml(msg.software_group_part_number, out);
    out << ", ";
  }

  // member: software_group_description
  {
    out << "software_group_description: ";
    rosidl_generator_traits::value_to_yaml(msg.software_group_description, out);
    out << ", ";
  }

  // member: software_group_release_date
  {
    out << "software_group_release_date: ";
    rosidl_generator_traits::value_to_yaml(msg.software_group_release_date, out);
    out << ", ";
  }

  // member: ecm_hw_version
  {
    out << "ecm_hw_version: ";
    to_flow_style_yaml(msg.ecm_hw_version, out);
    out << ", ";
  }

  // member: eth0_tx_kbs
  {
    out << "eth0_tx_kbs: ";
    rosidl_generator_traits::value_to_yaml(msg.eth0_tx_kbs, out);
    out << ", ";
  }

  // member: eth0_rx_kbs
  {
    out << "eth0_rx_kbs: ";
    rosidl_generator_traits::value_to_yaml(msg.eth0_rx_kbs, out);
    out << ", ";
  }

  // member: eth1_tx_kbs
  {
    out << "eth1_tx_kbs: ";
    rosidl_generator_traits::value_to_yaml(msg.eth1_tx_kbs, out);
    out << ", ";
  }

  // member: eth1_rx_kbs
  {
    out << "eth1_rx_kbs: ";
    rosidl_generator_traits::value_to_yaml(msg.eth1_rx_kbs, out);
    out << ", ";
  }

  // member: list_of_ethernet_stats
  {
    if (msg.list_of_ethernet_stats.size() == 0) {
      out << "list_of_ethernet_stats: []";
    } else {
      out << "list_of_ethernet_stats: [";
      size_t pending_items = msg.list_of_ethernet_stats.size();
      for (auto item : msg.list_of_ethernet_stats) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: system_cpu_usage_percent
  {
    out << "system_cpu_usage_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.system_cpu_usage_percent, out);
    out << ", ";
  }

  // member: system_cpu_io_wait_percent
  {
    out << "system_cpu_io_wait_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.system_cpu_io_wait_percent, out);
    out << ", ";
  }

  // member: system_cpu_irq_percent
  {
    out << "system_cpu_irq_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.system_cpu_irq_percent, out);
    out << ", ";
  }

  // member: ecm_os_version
  {
    out << "ecm_os_version: ";
    rosidl_generator_traits::value_to_yaml(msg.ecm_os_version, out);
    out << ", ";
  }

  // member: per_core_cpu_data
  {
    if (msg.per_core_cpu_data.size() == 0) {
      out << "per_core_cpu_data: []";
    } else {
      out << "per_core_cpu_data: [";
      size_t pending_items = msg.per_core_cpu_data.size();
      for (auto item : msg.per_core_cpu_data) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: battery_voltage
  {
    out << "battery_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_voltage, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SystemHardwareHealthStorage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: source_system
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "source_system: ";
    rosidl_generator_traits::value_to_yaml(msg.source_system, out);
    out << "\n";
  }

  // member: total_system_memory_kb
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_system_memory_kb: ";
    rosidl_generator_traits::value_to_yaml(msg.total_system_memory_kb, out);
    out << "\n";
  }

  // member: available_system_memory_kb
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "available_system_memory_kb: ";
    rosidl_generator_traits::value_to_yaml(msg.available_system_memory_kb, out);
    out << "\n";
  }

  // member: list_of_remaining_disk_space
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.list_of_remaining_disk_space.size() == 0) {
      out << "list_of_remaining_disk_space: []\n";
    } else {
      out << "list_of_remaining_disk_space:\n";
      for (auto item : msg.list_of_remaining_disk_space) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: system_up_time_sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "system_up_time_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.system_up_time_sec, out);
    out << "\n";
  }

  // member: load_avg1min
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "load_avg1min: ";
    rosidl_generator_traits::value_to_yaml(msg.load_avg1min, out);
    out << "\n";
  }

  // member: load_avg5min
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "load_avg5min: ";
    rosidl_generator_traits::value_to_yaml(msg.load_avg5min, out);
    out << "\n";
  }

  // member: load_avg15min
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "load_avg15min: ";
    rosidl_generator_traits::value_to_yaml(msg.load_avg15min, out);
    out << "\n";
  }

  // member: core_temperatures_c
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.core_temperatures_c.size() == 0) {
      out << "core_temperatures_c: []\n";
    } else {
      out << "core_temperatures_c:\n";
      for (auto item : msg.core_temperatures_c) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: ecm_sw_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ecm_sw_version: ";
    rosidl_generator_traits::value_to_yaml(msg.ecm_sw_version, out);
    out << "\n";
  }

  // member: software_group_part_number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "software_group_part_number: ";
    rosidl_generator_traits::value_to_yaml(msg.software_group_part_number, out);
    out << "\n";
  }

  // member: software_group_description
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "software_group_description: ";
    rosidl_generator_traits::value_to_yaml(msg.software_group_description, out);
    out << "\n";
  }

  // member: software_group_release_date
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "software_group_release_date: ";
    rosidl_generator_traits::value_to_yaml(msg.software_group_release_date, out);
    out << "\n";
  }

  // member: ecm_hw_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ecm_hw_version:\n";
    to_block_style_yaml(msg.ecm_hw_version, out, indentation + 2);
  }

  // member: eth0_tx_kbs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "eth0_tx_kbs: ";
    rosidl_generator_traits::value_to_yaml(msg.eth0_tx_kbs, out);
    out << "\n";
  }

  // member: eth0_rx_kbs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "eth0_rx_kbs: ";
    rosidl_generator_traits::value_to_yaml(msg.eth0_rx_kbs, out);
    out << "\n";
  }

  // member: eth1_tx_kbs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "eth1_tx_kbs: ";
    rosidl_generator_traits::value_to_yaml(msg.eth1_tx_kbs, out);
    out << "\n";
  }

  // member: eth1_rx_kbs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "eth1_rx_kbs: ";
    rosidl_generator_traits::value_to_yaml(msg.eth1_rx_kbs, out);
    out << "\n";
  }

  // member: list_of_ethernet_stats
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.list_of_ethernet_stats.size() == 0) {
      out << "list_of_ethernet_stats: []\n";
    } else {
      out << "list_of_ethernet_stats:\n";
      for (auto item : msg.list_of_ethernet_stats) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: system_cpu_usage_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "system_cpu_usage_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.system_cpu_usage_percent, out);
    out << "\n";
  }

  // member: system_cpu_io_wait_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "system_cpu_io_wait_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.system_cpu_io_wait_percent, out);
    out << "\n";
  }

  // member: system_cpu_irq_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "system_cpu_irq_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.system_cpu_irq_percent, out);
    out << "\n";
  }

  // member: ecm_os_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ecm_os_version: ";
    rosidl_generator_traits::value_to_yaml(msg.ecm_os_version, out);
    out << "\n";
  }

  // member: per_core_cpu_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.per_core_cpu_data.size() == 0) {
      out << "per_core_cpu_data: []\n";
    } else {
      out << "per_core_cpu_data:\n";
      for (auto item : msg.per_core_cpu_data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: battery_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_voltage, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SystemHardwareHealthStorage & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace weigh_app_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use weigh_app_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::SystemHardwareHealthStorage>()
{
  return "weigh_app_interfaces::msg::SystemHardwareHealthStorage";
}

template<>
inline const char * name<weigh_app_interfaces::msg::SystemHardwareHealthStorage>()
{
  return "weigh_app_interfaces/msg/SystemHardwareHealthStorage";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::SystemHardwareHealthStorage>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::SystemHardwareHealthStorage>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<weigh_app_interfaces::msg::SystemHardwareHealthStorage>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_STORAGE__TRAITS_HPP_
