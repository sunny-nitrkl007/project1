// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/Machine.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/machine.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__MACHINE__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__MACHINE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__Machine __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__Machine __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Machine_
{
  using Type = Machine_<ContainerAllocator>;

  explicit Machine_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->app_number = 0;
      this->payload_ratio = 0.0f;
      this->payload_ratio_status = 0;
      this->payload_ratio_raw = 0.0f;
      this->payload_ratio_raw_status = 0;
      this->payload_weight = 0.0f;
      this->payload_weight_status = 0;
      this->payload_calc_method = 0;
      this->lift_valve_cmd = 0;
      this->tilt_valve_cmd = 0;
      this->bucket_angle = 0;
      this->lift_angle = 0.0f;
      this->tilt_lever_cmd = 0;
      this->tilt_cyl_pos = 0;
      this->impl_operation_status = 0;
      this->machine_idle_status = 0;
      this->dump_solenoid_percent = 0;
      this->rack_solenoid_percent = 0;
      this->lower_solenoid_percent = 0;
      this->raise_solenoid_percent = 0;
      this->brake_pedal_position = 0.0f;
      this->lift_cylinder_he_pressure = 0;
      this->lift_cylinder_re_pressure = 0;
      this->hydarulic_oil_temp = 0;
      this->bucket_payload = 0.0f;
      this->desired_gear = 0;
      this->ground_speed = 0;
      this->engine_speed = 0;
      this->torque_converter_speed = 0;
      this->keyswitch_state = 0;
      this->real_time = 0ul;
      this->real_time_status = 0;
      this->timezone_offset = 0;
      this->total_fuel_high_res = 0ul;
      this->total_fuel_low_res = 0ul;
      this->fuel_rate = 0;
      this->ard_fuel_rate = 0;
      this->service_hour_meter = 0ul;
      this->external_force_normalized = 0;
      this->gps_latitude = 0ul;
      this->gps_longitude = 0ul;
      this->gps_status = 0;
    }
  }

  explicit Machine_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->app_number = 0;
      this->payload_ratio = 0.0f;
      this->payload_ratio_status = 0;
      this->payload_ratio_raw = 0.0f;
      this->payload_ratio_raw_status = 0;
      this->payload_weight = 0.0f;
      this->payload_weight_status = 0;
      this->payload_calc_method = 0;
      this->lift_valve_cmd = 0;
      this->tilt_valve_cmd = 0;
      this->bucket_angle = 0;
      this->lift_angle = 0.0f;
      this->tilt_lever_cmd = 0;
      this->tilt_cyl_pos = 0;
      this->impl_operation_status = 0;
      this->machine_idle_status = 0;
      this->dump_solenoid_percent = 0;
      this->rack_solenoid_percent = 0;
      this->lower_solenoid_percent = 0;
      this->raise_solenoid_percent = 0;
      this->brake_pedal_position = 0.0f;
      this->lift_cylinder_he_pressure = 0;
      this->lift_cylinder_re_pressure = 0;
      this->hydarulic_oil_temp = 0;
      this->bucket_payload = 0.0f;
      this->desired_gear = 0;
      this->ground_speed = 0;
      this->engine_speed = 0;
      this->torque_converter_speed = 0;
      this->keyswitch_state = 0;
      this->real_time = 0ul;
      this->real_time_status = 0;
      this->timezone_offset = 0;
      this->total_fuel_high_res = 0ul;
      this->total_fuel_low_res = 0ul;
      this->fuel_rate = 0;
      this->ard_fuel_rate = 0;
      this->service_hour_meter = 0ul;
      this->external_force_normalized = 0;
      this->gps_latitude = 0ul;
      this->gps_longitude = 0ul;
      this->gps_status = 0;
    }
  }

  // field types and members
  using _app_number_type =
    uint16_t;
  _app_number_type app_number;
  using _payload_ratio_type =
    float;
  _payload_ratio_type payload_ratio;
  using _payload_ratio_status_type =
    uint16_t;
  _payload_ratio_status_type payload_ratio_status;
  using _payload_ratio_raw_type =
    float;
  _payload_ratio_raw_type payload_ratio_raw;
  using _payload_ratio_raw_status_type =
    uint16_t;
  _payload_ratio_raw_status_type payload_ratio_raw_status;
  using _payload_weight_type =
    float;
  _payload_weight_type payload_weight;
  using _payload_weight_status_type =
    uint16_t;
  _payload_weight_status_type payload_weight_status;
  using _payload_calc_method_type =
    uint16_t;
  _payload_calc_method_type payload_calc_method;
  using _lift_valve_cmd_type =
    int16_t;
  _lift_valve_cmd_type lift_valve_cmd;
  using _tilt_valve_cmd_type =
    int16_t;
  _tilt_valve_cmd_type tilt_valve_cmd;
  using _bucket_angle_type =
    int16_t;
  _bucket_angle_type bucket_angle;
  using _lift_angle_type =
    float;
  _lift_angle_type lift_angle;
  using _tilt_lever_cmd_type =
    int16_t;
  _tilt_lever_cmd_type tilt_lever_cmd;
  using _tilt_cyl_pos_type =
    uint16_t;
  _tilt_cyl_pos_type tilt_cyl_pos;
  using _impl_operation_status_type =
    uint16_t;
  _impl_operation_status_type impl_operation_status;
  using _machine_idle_status_type =
    uint16_t;
  _machine_idle_status_type machine_idle_status;
  using _dump_solenoid_percent_type =
    uint8_t;
  _dump_solenoid_percent_type dump_solenoid_percent;
  using _rack_solenoid_percent_type =
    uint8_t;
  _rack_solenoid_percent_type rack_solenoid_percent;
  using _lower_solenoid_percent_type =
    uint8_t;
  _lower_solenoid_percent_type lower_solenoid_percent;
  using _raise_solenoid_percent_type =
    uint8_t;
  _raise_solenoid_percent_type raise_solenoid_percent;
  using _brake_pedal_position_type =
    float;
  _brake_pedal_position_type brake_pedal_position;
  using _lift_cylinder_he_pressure_type =
    uint16_t;
  _lift_cylinder_he_pressure_type lift_cylinder_he_pressure;
  using _lift_cylinder_re_pressure_type =
    uint16_t;
  _lift_cylinder_re_pressure_type lift_cylinder_re_pressure;
  using _hydarulic_oil_temp_type =
    int16_t;
  _hydarulic_oil_temp_type hydarulic_oil_temp;
  using _bucket_payload_type =
    float;
  _bucket_payload_type bucket_payload;
  using _desired_gear_type =
    int16_t;
  _desired_gear_type desired_gear;
  using _ground_speed_type =
    int16_t;
  _ground_speed_type ground_speed;
  using _engine_speed_type =
    int16_t;
  _engine_speed_type engine_speed;
  using _torque_converter_speed_type =
    int16_t;
  _torque_converter_speed_type torque_converter_speed;
  using _keyswitch_state_type =
    uint16_t;
  _keyswitch_state_type keyswitch_state;
  using _real_time_type =
    uint32_t;
  _real_time_type real_time;
  using _real_time_status_type =
    uint8_t;
  _real_time_status_type real_time_status;
  using _timezone_offset_type =
    int16_t;
  _timezone_offset_type timezone_offset;
  using _total_fuel_high_res_type =
    uint32_t;
  _total_fuel_high_res_type total_fuel_high_res;
  using _total_fuel_low_res_type =
    uint32_t;
  _total_fuel_low_res_type total_fuel_low_res;
  using _fuel_rate_type =
    uint16_t;
  _fuel_rate_type fuel_rate;
  using _ard_fuel_rate_type =
    uint16_t;
  _ard_fuel_rate_type ard_fuel_rate;
  using _service_hour_meter_type =
    uint32_t;
  _service_hour_meter_type service_hour_meter;
  using _external_force_normalized_type =
    int16_t;
  _external_force_normalized_type external_force_normalized;
  using _gps_latitude_type =
    uint32_t;
  _gps_latitude_type gps_latitude;
  using _gps_longitude_type =
    uint32_t;
  _gps_longitude_type gps_longitude;
  using _gps_status_type =
    uint8_t;
  _gps_status_type gps_status;

  // setters for named parameter idiom
  Type & set__app_number(
    const uint16_t & _arg)
  {
    this->app_number = _arg;
    return *this;
  }
  Type & set__payload_ratio(
    const float & _arg)
  {
    this->payload_ratio = _arg;
    return *this;
  }
  Type & set__payload_ratio_status(
    const uint16_t & _arg)
  {
    this->payload_ratio_status = _arg;
    return *this;
  }
  Type & set__payload_ratio_raw(
    const float & _arg)
  {
    this->payload_ratio_raw = _arg;
    return *this;
  }
  Type & set__payload_ratio_raw_status(
    const uint16_t & _arg)
  {
    this->payload_ratio_raw_status = _arg;
    return *this;
  }
  Type & set__payload_weight(
    const float & _arg)
  {
    this->payload_weight = _arg;
    return *this;
  }
  Type & set__payload_weight_status(
    const uint16_t & _arg)
  {
    this->payload_weight_status = _arg;
    return *this;
  }
  Type & set__payload_calc_method(
    const uint16_t & _arg)
  {
    this->payload_calc_method = _arg;
    return *this;
  }
  Type & set__lift_valve_cmd(
    const int16_t & _arg)
  {
    this->lift_valve_cmd = _arg;
    return *this;
  }
  Type & set__tilt_valve_cmd(
    const int16_t & _arg)
  {
    this->tilt_valve_cmd = _arg;
    return *this;
  }
  Type & set__bucket_angle(
    const int16_t & _arg)
  {
    this->bucket_angle = _arg;
    return *this;
  }
  Type & set__lift_angle(
    const float & _arg)
  {
    this->lift_angle = _arg;
    return *this;
  }
  Type & set__tilt_lever_cmd(
    const int16_t & _arg)
  {
    this->tilt_lever_cmd = _arg;
    return *this;
  }
  Type & set__tilt_cyl_pos(
    const uint16_t & _arg)
  {
    this->tilt_cyl_pos = _arg;
    return *this;
  }
  Type & set__impl_operation_status(
    const uint16_t & _arg)
  {
    this->impl_operation_status = _arg;
    return *this;
  }
  Type & set__machine_idle_status(
    const uint16_t & _arg)
  {
    this->machine_idle_status = _arg;
    return *this;
  }
  Type & set__dump_solenoid_percent(
    const uint8_t & _arg)
  {
    this->dump_solenoid_percent = _arg;
    return *this;
  }
  Type & set__rack_solenoid_percent(
    const uint8_t & _arg)
  {
    this->rack_solenoid_percent = _arg;
    return *this;
  }
  Type & set__lower_solenoid_percent(
    const uint8_t & _arg)
  {
    this->lower_solenoid_percent = _arg;
    return *this;
  }
  Type & set__raise_solenoid_percent(
    const uint8_t & _arg)
  {
    this->raise_solenoid_percent = _arg;
    return *this;
  }
  Type & set__brake_pedal_position(
    const float & _arg)
  {
    this->brake_pedal_position = _arg;
    return *this;
  }
  Type & set__lift_cylinder_he_pressure(
    const uint16_t & _arg)
  {
    this->lift_cylinder_he_pressure = _arg;
    return *this;
  }
  Type & set__lift_cylinder_re_pressure(
    const uint16_t & _arg)
  {
    this->lift_cylinder_re_pressure = _arg;
    return *this;
  }
  Type & set__hydarulic_oil_temp(
    const int16_t & _arg)
  {
    this->hydarulic_oil_temp = _arg;
    return *this;
  }
  Type & set__bucket_payload(
    const float & _arg)
  {
    this->bucket_payload = _arg;
    return *this;
  }
  Type & set__desired_gear(
    const int16_t & _arg)
  {
    this->desired_gear = _arg;
    return *this;
  }
  Type & set__ground_speed(
    const int16_t & _arg)
  {
    this->ground_speed = _arg;
    return *this;
  }
  Type & set__engine_speed(
    const int16_t & _arg)
  {
    this->engine_speed = _arg;
    return *this;
  }
  Type & set__torque_converter_speed(
    const int16_t & _arg)
  {
    this->torque_converter_speed = _arg;
    return *this;
  }
  Type & set__keyswitch_state(
    const uint16_t & _arg)
  {
    this->keyswitch_state = _arg;
    return *this;
  }
  Type & set__real_time(
    const uint32_t & _arg)
  {
    this->real_time = _arg;
    return *this;
  }
  Type & set__real_time_status(
    const uint8_t & _arg)
  {
    this->real_time_status = _arg;
    return *this;
  }
  Type & set__timezone_offset(
    const int16_t & _arg)
  {
    this->timezone_offset = _arg;
    return *this;
  }
  Type & set__total_fuel_high_res(
    const uint32_t & _arg)
  {
    this->total_fuel_high_res = _arg;
    return *this;
  }
  Type & set__total_fuel_low_res(
    const uint32_t & _arg)
  {
    this->total_fuel_low_res = _arg;
    return *this;
  }
  Type & set__fuel_rate(
    const uint16_t & _arg)
  {
    this->fuel_rate = _arg;
    return *this;
  }
  Type & set__ard_fuel_rate(
    const uint16_t & _arg)
  {
    this->ard_fuel_rate = _arg;
    return *this;
  }
  Type & set__service_hour_meter(
    const uint32_t & _arg)
  {
    this->service_hour_meter = _arg;
    return *this;
  }
  Type & set__external_force_normalized(
    const int16_t & _arg)
  {
    this->external_force_normalized = _arg;
    return *this;
  }
  Type & set__gps_latitude(
    const uint32_t & _arg)
  {
    this->gps_latitude = _arg;
    return *this;
  }
  Type & set__gps_longitude(
    const uint32_t & _arg)
  {
    this->gps_longitude = _arg;
    return *this;
  }
  Type & set__gps_status(
    const uint8_t & _arg)
  {
    this->gps_status = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::Machine_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::Machine_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::Machine_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::Machine_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::Machine_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::Machine_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::Machine_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::Machine_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::Machine_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::Machine_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__Machine
    std::shared_ptr<weigh_app_interfaces::msg::Machine_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__Machine
    std::shared_ptr<weigh_app_interfaces::msg::Machine_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Machine_ & other) const
  {
    if (this->app_number != other.app_number) {
      return false;
    }
    if (this->payload_ratio != other.payload_ratio) {
      return false;
    }
    if (this->payload_ratio_status != other.payload_ratio_status) {
      return false;
    }
    if (this->payload_ratio_raw != other.payload_ratio_raw) {
      return false;
    }
    if (this->payload_ratio_raw_status != other.payload_ratio_raw_status) {
      return false;
    }
    if (this->payload_weight != other.payload_weight) {
      return false;
    }
    if (this->payload_weight_status != other.payload_weight_status) {
      return false;
    }
    if (this->payload_calc_method != other.payload_calc_method) {
      return false;
    }
    if (this->lift_valve_cmd != other.lift_valve_cmd) {
      return false;
    }
    if (this->tilt_valve_cmd != other.tilt_valve_cmd) {
      return false;
    }
    if (this->bucket_angle != other.bucket_angle) {
      return false;
    }
    if (this->lift_angle != other.lift_angle) {
      return false;
    }
    if (this->tilt_lever_cmd != other.tilt_lever_cmd) {
      return false;
    }
    if (this->tilt_cyl_pos != other.tilt_cyl_pos) {
      return false;
    }
    if (this->impl_operation_status != other.impl_operation_status) {
      return false;
    }
    if (this->machine_idle_status != other.machine_idle_status) {
      return false;
    }
    if (this->dump_solenoid_percent != other.dump_solenoid_percent) {
      return false;
    }
    if (this->rack_solenoid_percent != other.rack_solenoid_percent) {
      return false;
    }
    if (this->lower_solenoid_percent != other.lower_solenoid_percent) {
      return false;
    }
    if (this->raise_solenoid_percent != other.raise_solenoid_percent) {
      return false;
    }
    if (this->brake_pedal_position != other.brake_pedal_position) {
      return false;
    }
    if (this->lift_cylinder_he_pressure != other.lift_cylinder_he_pressure) {
      return false;
    }
    if (this->lift_cylinder_re_pressure != other.lift_cylinder_re_pressure) {
      return false;
    }
    if (this->hydarulic_oil_temp != other.hydarulic_oil_temp) {
      return false;
    }
    if (this->bucket_payload != other.bucket_payload) {
      return false;
    }
    if (this->desired_gear != other.desired_gear) {
      return false;
    }
    if (this->ground_speed != other.ground_speed) {
      return false;
    }
    if (this->engine_speed != other.engine_speed) {
      return false;
    }
    if (this->torque_converter_speed != other.torque_converter_speed) {
      return false;
    }
    if (this->keyswitch_state != other.keyswitch_state) {
      return false;
    }
    if (this->real_time != other.real_time) {
      return false;
    }
    if (this->real_time_status != other.real_time_status) {
      return false;
    }
    if (this->timezone_offset != other.timezone_offset) {
      return false;
    }
    if (this->total_fuel_high_res != other.total_fuel_high_res) {
      return false;
    }
    if (this->total_fuel_low_res != other.total_fuel_low_res) {
      return false;
    }
    if (this->fuel_rate != other.fuel_rate) {
      return false;
    }
    if (this->ard_fuel_rate != other.ard_fuel_rate) {
      return false;
    }
    if (this->service_hour_meter != other.service_hour_meter) {
      return false;
    }
    if (this->external_force_normalized != other.external_force_normalized) {
      return false;
    }
    if (this->gps_latitude != other.gps_latitude) {
      return false;
    }
    if (this->gps_longitude != other.gps_longitude) {
      return false;
    }
    if (this->gps_status != other.gps_status) {
      return false;
    }
    return true;
  }
  bool operator!=(const Machine_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Machine_

// alias to use template instance with default allocator
using Machine =
  weigh_app_interfaces::msg::Machine_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__MACHINE__STRUCT_HPP_
