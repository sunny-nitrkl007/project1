// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/SystemHardwareHealthStorage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/system_hardware_health_storage.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_STORAGE__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_STORAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/system_hardware_health_storage__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_SystemHardwareHealthStorage_battery_voltage
{
public:
  explicit Init_SystemHardwareHealthStorage_battery_voltage(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage battery_voltage(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_battery_voltage_type arg)
  {
    msg_.battery_voltage = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_per_core_cpu_data
{
public:
  explicit Init_SystemHardwareHealthStorage_per_core_cpu_data(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_battery_voltage per_core_cpu_data(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_per_core_cpu_data_type arg)
  {
    msg_.per_core_cpu_data = std::move(arg);
    return Init_SystemHardwareHealthStorage_battery_voltage(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_ecm_os_version
{
public:
  explicit Init_SystemHardwareHealthStorage_ecm_os_version(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_per_core_cpu_data ecm_os_version(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_ecm_os_version_type arg)
  {
    msg_.ecm_os_version = std::move(arg);
    return Init_SystemHardwareHealthStorage_per_core_cpu_data(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_system_cpu_irq_percent
{
public:
  explicit Init_SystemHardwareHealthStorage_system_cpu_irq_percent(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_ecm_os_version system_cpu_irq_percent(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_system_cpu_irq_percent_type arg)
  {
    msg_.system_cpu_irq_percent = std::move(arg);
    return Init_SystemHardwareHealthStorage_ecm_os_version(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_system_cpu_io_wait_percent
{
public:
  explicit Init_SystemHardwareHealthStorage_system_cpu_io_wait_percent(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_system_cpu_irq_percent system_cpu_io_wait_percent(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_system_cpu_io_wait_percent_type arg)
  {
    msg_.system_cpu_io_wait_percent = std::move(arg);
    return Init_SystemHardwareHealthStorage_system_cpu_irq_percent(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_system_cpu_usage_percent
{
public:
  explicit Init_SystemHardwareHealthStorage_system_cpu_usage_percent(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_system_cpu_io_wait_percent system_cpu_usage_percent(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_system_cpu_usage_percent_type arg)
  {
    msg_.system_cpu_usage_percent = std::move(arg);
    return Init_SystemHardwareHealthStorage_system_cpu_io_wait_percent(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_list_of_ethernet_stats
{
public:
  explicit Init_SystemHardwareHealthStorage_list_of_ethernet_stats(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_system_cpu_usage_percent list_of_ethernet_stats(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_list_of_ethernet_stats_type arg)
  {
    msg_.list_of_ethernet_stats = std::move(arg);
    return Init_SystemHardwareHealthStorage_system_cpu_usage_percent(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_eth1_rx_kbs
{
public:
  explicit Init_SystemHardwareHealthStorage_eth1_rx_kbs(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_list_of_ethernet_stats eth1_rx_kbs(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_eth1_rx_kbs_type arg)
  {
    msg_.eth1_rx_kbs = std::move(arg);
    return Init_SystemHardwareHealthStorage_list_of_ethernet_stats(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_eth1_tx_kbs
{
public:
  explicit Init_SystemHardwareHealthStorage_eth1_tx_kbs(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_eth1_rx_kbs eth1_tx_kbs(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_eth1_tx_kbs_type arg)
  {
    msg_.eth1_tx_kbs = std::move(arg);
    return Init_SystemHardwareHealthStorage_eth1_rx_kbs(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_eth0_rx_kbs
{
public:
  explicit Init_SystemHardwareHealthStorage_eth0_rx_kbs(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_eth1_tx_kbs eth0_rx_kbs(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_eth0_rx_kbs_type arg)
  {
    msg_.eth0_rx_kbs = std::move(arg);
    return Init_SystemHardwareHealthStorage_eth1_tx_kbs(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_eth0_tx_kbs
{
public:
  explicit Init_SystemHardwareHealthStorage_eth0_tx_kbs(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_eth0_rx_kbs eth0_tx_kbs(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_eth0_tx_kbs_type arg)
  {
    msg_.eth0_tx_kbs = std::move(arg);
    return Init_SystemHardwareHealthStorage_eth0_rx_kbs(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_ecm_hw_version
{
public:
  explicit Init_SystemHardwareHealthStorage_ecm_hw_version(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_eth0_tx_kbs ecm_hw_version(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_ecm_hw_version_type arg)
  {
    msg_.ecm_hw_version = std::move(arg);
    return Init_SystemHardwareHealthStorage_eth0_tx_kbs(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_software_group_release_date
{
public:
  explicit Init_SystemHardwareHealthStorage_software_group_release_date(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_ecm_hw_version software_group_release_date(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_software_group_release_date_type arg)
  {
    msg_.software_group_release_date = std::move(arg);
    return Init_SystemHardwareHealthStorage_ecm_hw_version(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_software_group_description
{
public:
  explicit Init_SystemHardwareHealthStorage_software_group_description(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_software_group_release_date software_group_description(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_software_group_description_type arg)
  {
    msg_.software_group_description = std::move(arg);
    return Init_SystemHardwareHealthStorage_software_group_release_date(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_software_group_part_number
{
public:
  explicit Init_SystemHardwareHealthStorage_software_group_part_number(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_software_group_description software_group_part_number(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_software_group_part_number_type arg)
  {
    msg_.software_group_part_number = std::move(arg);
    return Init_SystemHardwareHealthStorage_software_group_description(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_ecm_sw_version
{
public:
  explicit Init_SystemHardwareHealthStorage_ecm_sw_version(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_software_group_part_number ecm_sw_version(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_ecm_sw_version_type arg)
  {
    msg_.ecm_sw_version = std::move(arg);
    return Init_SystemHardwareHealthStorage_software_group_part_number(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_core_temperatures_c
{
public:
  explicit Init_SystemHardwareHealthStorage_core_temperatures_c(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_ecm_sw_version core_temperatures_c(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_core_temperatures_c_type arg)
  {
    msg_.core_temperatures_c = std::move(arg);
    return Init_SystemHardwareHealthStorage_ecm_sw_version(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_load_avg15min
{
public:
  explicit Init_SystemHardwareHealthStorage_load_avg15min(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_core_temperatures_c load_avg15min(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_load_avg15min_type arg)
  {
    msg_.load_avg15min = std::move(arg);
    return Init_SystemHardwareHealthStorage_core_temperatures_c(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_load_avg5min
{
public:
  explicit Init_SystemHardwareHealthStorage_load_avg5min(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_load_avg15min load_avg5min(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_load_avg5min_type arg)
  {
    msg_.load_avg5min = std::move(arg);
    return Init_SystemHardwareHealthStorage_load_avg15min(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_load_avg1min
{
public:
  explicit Init_SystemHardwareHealthStorage_load_avg1min(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_load_avg5min load_avg1min(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_load_avg1min_type arg)
  {
    msg_.load_avg1min = std::move(arg);
    return Init_SystemHardwareHealthStorage_load_avg5min(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_system_up_time_sec
{
public:
  explicit Init_SystemHardwareHealthStorage_system_up_time_sec(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_load_avg1min system_up_time_sec(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_system_up_time_sec_type arg)
  {
    msg_.system_up_time_sec = std::move(arg);
    return Init_SystemHardwareHealthStorage_load_avg1min(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_list_of_remaining_disk_space
{
public:
  explicit Init_SystemHardwareHealthStorage_list_of_remaining_disk_space(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_system_up_time_sec list_of_remaining_disk_space(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_list_of_remaining_disk_space_type arg)
  {
    msg_.list_of_remaining_disk_space = std::move(arg);
    return Init_SystemHardwareHealthStorage_system_up_time_sec(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_available_system_memory_kb
{
public:
  explicit Init_SystemHardwareHealthStorage_available_system_memory_kb(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_list_of_remaining_disk_space available_system_memory_kb(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_available_system_memory_kb_type arg)
  {
    msg_.available_system_memory_kb = std::move(arg);
    return Init_SystemHardwareHealthStorage_list_of_remaining_disk_space(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_total_system_memory_kb
{
public:
  explicit Init_SystemHardwareHealthStorage_total_system_memory_kb(::weigh_app_interfaces::msg::SystemHardwareHealthStorage & msg)
  : msg_(msg)
  {}
  Init_SystemHardwareHealthStorage_available_system_memory_kb total_system_memory_kb(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_total_system_memory_kb_type arg)
  {
    msg_.total_system_memory_kb = std::move(arg);
    return Init_SystemHardwareHealthStorage_available_system_memory_kb(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

class Init_SystemHardwareHealthStorage_source_system
{
public:
  Init_SystemHardwareHealthStorage_source_system()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SystemHardwareHealthStorage_total_system_memory_kb source_system(::weigh_app_interfaces::msg::SystemHardwareHealthStorage::_source_system_type arg)
  {
    msg_.source_system = std::move(arg);
    return Init_SystemHardwareHealthStorage_total_system_memory_kb(msg_);
  }

private:
  ::weigh_app_interfaces::msg::SystemHardwareHealthStorage msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::SystemHardwareHealthStorage>()
{
  return weigh_app_interfaces::msg::builder::Init_SystemHardwareHealthStorage_source_system();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_STORAGE__BUILDER_HPP_
