// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaWeighTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_weigh_tx_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_TX_CHANNEL__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_TX_CHANNEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'payload'
#include "cpm_common_interfaces/msg/detail/payload__struct.hpp"
// Member 'lft_seal_status'
#include "cpm_common_interfaces/msg/detail/lft_seal_status__struct.hpp"
// Member 'lift_position'
#include "cpm_common_interfaces/msg/detail/lift_position__struct.hpp"
// Member 'lift_cyl_vel'
// Member 'lift_valve_command'
// Member 'tilt_valve_command'
#include "cpm_common_interfaces/msg/detail/float_io__struct.hpp"
// Member 'tilt_position'
#include "cpm_common_interfaces/msg/detail/tilt_position__struct.hpp"
// Member 'weigh_range'
#include "cpm_common_interfaces/msg/detail/weigh_range__struct.hpp"
// Member 'event_state'
#include "cpm_common_interfaces/msg/detail/acd_event_pop_up__struct.hpp"
// Member 'diag_state'
#include "cpm_common_interfaces/msg/detail/acd_diag_pop_up__struct.hpp"
// Member 'info_state'
#include "cpm_common_interfaces/msg/detail/acd_info_pop_up__struct.hpp"
// Member 'pid_data'
#include "cpm_common_interfaces/msg/detail/weigh_pid_data__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaWeighTxChannel __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaWeighTxChannel __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaWeighTxChannel_
{
  using Type = LpsSaWeighTxChannel_<ContainerAllocator>;

  explicit LpsSaWeighTxChannel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : payload(_init),
    lft_seal_status(_init),
    lift_position(_init),
    lift_cyl_vel(_init),
    tilt_position(_init),
    weigh_range(_init),
    lift_valve_command(_init),
    tilt_valve_command(_init),
    event_state(_init),
    diag_state(_init),
    info_state(_init),
    pid_data(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->time_point_ns = 0ll;
      this->dig_stat = 0l;
      this->cal_stat = 0l;
      this->dump_stat = 0l;
      this->best_bkt_wt_in_tonnes = 0.0f;
      this->warmup_lifts_required = 0;
      this->payload_calc_meth = 0;
      this->bkt_wt_latched_flag = false;
      this->latch_conditions_met = false;
      this->zero_available = false;
      this->flash_enabled = false;
      this->lift_position_sensor_id = "";
      this->tilt_position_sensor_id = "";
      this->lift_head_end_pressure_sensor_id = "";
      this->lift_rod_end_pressure_sensor_id = "";
      this->hydraulic_oil_temperature_sensor_id = "";
      this->imu_sensor_id = "";
      this->implement_serial_num = "";
      this->work_tool_id = "";
      this->indicator = 0l;
      this->cal_wt = 0.0f;
      this->lift_stalled = false;
      this->show_exclamation_point = false;
      this->excessive_pitch = false;
      this->bucket_fully_racked = false;
      this->zero_weight = 0.0f;
      this->simple_cal_adjust = 0.0f;
      this->engine_speed_rpm = 0;
      this->can11_message_timeout_flag = false;
      this->toa_anchored_zero_offset = 0.0f;
      this->toa_anchored_factor = 0.0f;
      this->toa_anchor_status = 0;
      this->payload_cal_in_progress = false;
      this->test_status = 0;
    }
  }

  explicit LpsSaWeighTxChannel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : payload(_alloc, _init),
    lft_seal_status(_alloc, _init),
    lift_position_sensor_id(_alloc),
    tilt_position_sensor_id(_alloc),
    lift_head_end_pressure_sensor_id(_alloc),
    lift_rod_end_pressure_sensor_id(_alloc),
    hydraulic_oil_temperature_sensor_id(_alloc),
    imu_sensor_id(_alloc),
    implement_serial_num(_alloc),
    work_tool_id(_alloc),
    lift_position(_alloc, _init),
    lift_cyl_vel(_alloc, _init),
    tilt_position(_alloc, _init),
    weigh_range(_alloc, _init),
    lift_valve_command(_alloc, _init),
    tilt_valve_command(_alloc, _init),
    event_state(_alloc, _init),
    diag_state(_alloc, _init),
    info_state(_alloc, _init),
    pid_data(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->time_point_ns = 0ll;
      this->dig_stat = 0l;
      this->cal_stat = 0l;
      this->dump_stat = 0l;
      this->best_bkt_wt_in_tonnes = 0.0f;
      this->warmup_lifts_required = 0;
      this->payload_calc_meth = 0;
      this->bkt_wt_latched_flag = false;
      this->latch_conditions_met = false;
      this->zero_available = false;
      this->flash_enabled = false;
      this->lift_position_sensor_id = "";
      this->tilt_position_sensor_id = "";
      this->lift_head_end_pressure_sensor_id = "";
      this->lift_rod_end_pressure_sensor_id = "";
      this->hydraulic_oil_temperature_sensor_id = "";
      this->imu_sensor_id = "";
      this->implement_serial_num = "";
      this->work_tool_id = "";
      this->indicator = 0l;
      this->cal_wt = 0.0f;
      this->lift_stalled = false;
      this->show_exclamation_point = false;
      this->excessive_pitch = false;
      this->bucket_fully_racked = false;
      this->zero_weight = 0.0f;
      this->simple_cal_adjust = 0.0f;
      this->engine_speed_rpm = 0;
      this->can11_message_timeout_flag = false;
      this->toa_anchored_zero_offset = 0.0f;
      this->toa_anchored_factor = 0.0f;
      this->toa_anchor_status = 0;
      this->payload_cal_in_progress = false;
      this->test_status = 0;
    }
  }

  // field types and members
  using _time_point_ns_type =
    int64_t;
  _time_point_ns_type time_point_ns;
  using _dig_stat_type =
    int32_t;
  _dig_stat_type dig_stat;
  using _cal_stat_type =
    int32_t;
  _cal_stat_type cal_stat;
  using _dump_stat_type =
    int32_t;
  _dump_stat_type dump_stat;
  using _best_bkt_wt_in_tonnes_type =
    float;
  _best_bkt_wt_in_tonnes_type best_bkt_wt_in_tonnes;
  using _warmup_lifts_required_type =
    uint16_t;
  _warmup_lifts_required_type warmup_lifts_required;
  using _payload_calc_meth_type =
    uint16_t;
  _payload_calc_meth_type payload_calc_meth;
  using _bkt_wt_latched_flag_type =
    bool;
  _bkt_wt_latched_flag_type bkt_wt_latched_flag;
  using _latch_conditions_met_type =
    bool;
  _latch_conditions_met_type latch_conditions_met;
  using _zero_available_type =
    bool;
  _zero_available_type zero_available;
  using _payload_type =
    cpm_common_interfaces::msg::Payload_<ContainerAllocator>;
  _payload_type payload;
  using _lft_seal_status_type =
    cpm_common_interfaces::msg::LftSealStatus_<ContainerAllocator>;
  _lft_seal_status_type lft_seal_status;
  using _flash_enabled_type =
    bool;
  _flash_enabled_type flash_enabled;
  using _lift_position_sensor_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _lift_position_sensor_id_type lift_position_sensor_id;
  using _tilt_position_sensor_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tilt_position_sensor_id_type tilt_position_sensor_id;
  using _lift_head_end_pressure_sensor_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _lift_head_end_pressure_sensor_id_type lift_head_end_pressure_sensor_id;
  using _lift_rod_end_pressure_sensor_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _lift_rod_end_pressure_sensor_id_type lift_rod_end_pressure_sensor_id;
  using _hydraulic_oil_temperature_sensor_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _hydraulic_oil_temperature_sensor_id_type hydraulic_oil_temperature_sensor_id;
  using _imu_sensor_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _imu_sensor_id_type imu_sensor_id;
  using _implement_serial_num_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _implement_serial_num_type implement_serial_num;
  using _work_tool_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _work_tool_id_type work_tool_id;
  using _lift_position_type =
    cpm_common_interfaces::msg::LiftPosition_<ContainerAllocator>;
  _lift_position_type lift_position;
  using _lift_cyl_vel_type =
    cpm_common_interfaces::msg::FloatIO_<ContainerAllocator>;
  _lift_cyl_vel_type lift_cyl_vel;
  using _tilt_position_type =
    cpm_common_interfaces::msg::TiltPosition_<ContainerAllocator>;
  _tilt_position_type tilt_position;
  using _weigh_range_type =
    cpm_common_interfaces::msg::WeighRange_<ContainerAllocator>;
  _weigh_range_type weigh_range;
  using _indicator_type =
    int32_t;
  _indicator_type indicator;
  using _cal_wt_type =
    float;
  _cal_wt_type cal_wt;
  using _lift_stalled_type =
    bool;
  _lift_stalled_type lift_stalled;
  using _lift_valve_command_type =
    cpm_common_interfaces::msg::FloatIO_<ContainerAllocator>;
  _lift_valve_command_type lift_valve_command;
  using _tilt_valve_command_type =
    cpm_common_interfaces::msg::FloatIO_<ContainerAllocator>;
  _tilt_valve_command_type tilt_valve_command;
  using _event_state_type =
    cpm_common_interfaces::msg::AcdEventPopUp_<ContainerAllocator>;
  _event_state_type event_state;
  using _diag_state_type =
    cpm_common_interfaces::msg::AcdDiagPopUp_<ContainerAllocator>;
  _diag_state_type diag_state;
  using _info_state_type =
    cpm_common_interfaces::msg::AcdInfoPopUp_<ContainerAllocator>;
  _info_state_type info_state;
  using _show_exclamation_point_type =
    bool;
  _show_exclamation_point_type show_exclamation_point;
  using _excessive_pitch_type =
    bool;
  _excessive_pitch_type excessive_pitch;
  using _bucket_fully_racked_type =
    bool;
  _bucket_fully_racked_type bucket_fully_racked;
  using _zero_weight_type =
    float;
  _zero_weight_type zero_weight;
  using _simple_cal_adjust_type =
    float;
  _simple_cal_adjust_type simple_cal_adjust;
  using _engine_speed_rpm_type =
    int16_t;
  _engine_speed_rpm_type engine_speed_rpm;
  using _pid_data_type =
    cpm_common_interfaces::msg::WeighPidData_<ContainerAllocator>;
  _pid_data_type pid_data;
  using _can11_message_timeout_flag_type =
    bool;
  _can11_message_timeout_flag_type can11_message_timeout_flag;
  using _toa_anchored_zero_offset_type =
    float;
  _toa_anchored_zero_offset_type toa_anchored_zero_offset;
  using _toa_anchored_factor_type =
    float;
  _toa_anchored_factor_type toa_anchored_factor;
  using _toa_anchor_status_type =
    uint8_t;
  _toa_anchor_status_type toa_anchor_status;
  using _payload_cal_in_progress_type =
    bool;
  _payload_cal_in_progress_type payload_cal_in_progress;
  using _test_status_type =
    uint8_t;
  _test_status_type test_status;

  // setters for named parameter idiom
  Type & set__time_point_ns(
    const int64_t & _arg)
  {
    this->time_point_ns = _arg;
    return *this;
  }
  Type & set__dig_stat(
    const int32_t & _arg)
  {
    this->dig_stat = _arg;
    return *this;
  }
  Type & set__cal_stat(
    const int32_t & _arg)
  {
    this->cal_stat = _arg;
    return *this;
  }
  Type & set__dump_stat(
    const int32_t & _arg)
  {
    this->dump_stat = _arg;
    return *this;
  }
  Type & set__best_bkt_wt_in_tonnes(
    const float & _arg)
  {
    this->best_bkt_wt_in_tonnes = _arg;
    return *this;
  }
  Type & set__warmup_lifts_required(
    const uint16_t & _arg)
  {
    this->warmup_lifts_required = _arg;
    return *this;
  }
  Type & set__payload_calc_meth(
    const uint16_t & _arg)
  {
    this->payload_calc_meth = _arg;
    return *this;
  }
  Type & set__bkt_wt_latched_flag(
    const bool & _arg)
  {
    this->bkt_wt_latched_flag = _arg;
    return *this;
  }
  Type & set__latch_conditions_met(
    const bool & _arg)
  {
    this->latch_conditions_met = _arg;
    return *this;
  }
  Type & set__zero_available(
    const bool & _arg)
  {
    this->zero_available = _arg;
    return *this;
  }
  Type & set__payload(
    const cpm_common_interfaces::msg::Payload_<ContainerAllocator> & _arg)
  {
    this->payload = _arg;
    return *this;
  }
  Type & set__lft_seal_status(
    const cpm_common_interfaces::msg::LftSealStatus_<ContainerAllocator> & _arg)
  {
    this->lft_seal_status = _arg;
    return *this;
  }
  Type & set__flash_enabled(
    const bool & _arg)
  {
    this->flash_enabled = _arg;
    return *this;
  }
  Type & set__lift_position_sensor_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->lift_position_sensor_id = _arg;
    return *this;
  }
  Type & set__tilt_position_sensor_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tilt_position_sensor_id = _arg;
    return *this;
  }
  Type & set__lift_head_end_pressure_sensor_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->lift_head_end_pressure_sensor_id = _arg;
    return *this;
  }
  Type & set__lift_rod_end_pressure_sensor_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->lift_rod_end_pressure_sensor_id = _arg;
    return *this;
  }
  Type & set__hydraulic_oil_temperature_sensor_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->hydraulic_oil_temperature_sensor_id = _arg;
    return *this;
  }
  Type & set__imu_sensor_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->imu_sensor_id = _arg;
    return *this;
  }
  Type & set__implement_serial_num(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->implement_serial_num = _arg;
    return *this;
  }
  Type & set__work_tool_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->work_tool_id = _arg;
    return *this;
  }
  Type & set__lift_position(
    const cpm_common_interfaces::msg::LiftPosition_<ContainerAllocator> & _arg)
  {
    this->lift_position = _arg;
    return *this;
  }
  Type & set__lift_cyl_vel(
    const cpm_common_interfaces::msg::FloatIO_<ContainerAllocator> & _arg)
  {
    this->lift_cyl_vel = _arg;
    return *this;
  }
  Type & set__tilt_position(
    const cpm_common_interfaces::msg::TiltPosition_<ContainerAllocator> & _arg)
  {
    this->tilt_position = _arg;
    return *this;
  }
  Type & set__weigh_range(
    const cpm_common_interfaces::msg::WeighRange_<ContainerAllocator> & _arg)
  {
    this->weigh_range = _arg;
    return *this;
  }
  Type & set__indicator(
    const int32_t & _arg)
  {
    this->indicator = _arg;
    return *this;
  }
  Type & set__cal_wt(
    const float & _arg)
  {
    this->cal_wt = _arg;
    return *this;
  }
  Type & set__lift_stalled(
    const bool & _arg)
  {
    this->lift_stalled = _arg;
    return *this;
  }
  Type & set__lift_valve_command(
    const cpm_common_interfaces::msg::FloatIO_<ContainerAllocator> & _arg)
  {
    this->lift_valve_command = _arg;
    return *this;
  }
  Type & set__tilt_valve_command(
    const cpm_common_interfaces::msg::FloatIO_<ContainerAllocator> & _arg)
  {
    this->tilt_valve_command = _arg;
    return *this;
  }
  Type & set__event_state(
    const cpm_common_interfaces::msg::AcdEventPopUp_<ContainerAllocator> & _arg)
  {
    this->event_state = _arg;
    return *this;
  }
  Type & set__diag_state(
    const cpm_common_interfaces::msg::AcdDiagPopUp_<ContainerAllocator> & _arg)
  {
    this->diag_state = _arg;
    return *this;
  }
  Type & set__info_state(
    const cpm_common_interfaces::msg::AcdInfoPopUp_<ContainerAllocator> & _arg)
  {
    this->info_state = _arg;
    return *this;
  }
  Type & set__show_exclamation_point(
    const bool & _arg)
  {
    this->show_exclamation_point = _arg;
    return *this;
  }
  Type & set__excessive_pitch(
    const bool & _arg)
  {
    this->excessive_pitch = _arg;
    return *this;
  }
  Type & set__bucket_fully_racked(
    const bool & _arg)
  {
    this->bucket_fully_racked = _arg;
    return *this;
  }
  Type & set__zero_weight(
    const float & _arg)
  {
    this->zero_weight = _arg;
    return *this;
  }
  Type & set__simple_cal_adjust(
    const float & _arg)
  {
    this->simple_cal_adjust = _arg;
    return *this;
  }
  Type & set__engine_speed_rpm(
    const int16_t & _arg)
  {
    this->engine_speed_rpm = _arg;
    return *this;
  }
  Type & set__pid_data(
    const cpm_common_interfaces::msg::WeighPidData_<ContainerAllocator> & _arg)
  {
    this->pid_data = _arg;
    return *this;
  }
  Type & set__can11_message_timeout_flag(
    const bool & _arg)
  {
    this->can11_message_timeout_flag = _arg;
    return *this;
  }
  Type & set__toa_anchored_zero_offset(
    const float & _arg)
  {
    this->toa_anchored_zero_offset = _arg;
    return *this;
  }
  Type & set__toa_anchored_factor(
    const float & _arg)
  {
    this->toa_anchored_factor = _arg;
    return *this;
  }
  Type & set__toa_anchor_status(
    const uint8_t & _arg)
  {
    this->toa_anchor_status = _arg;
    return *this;
  }
  Type & set__payload_cal_in_progress(
    const bool & _arg)
  {
    this->payload_cal_in_progress = _arg;
    return *this;
  }
  Type & set__test_status(
    const uint8_t & _arg)
  {
    this->test_status = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t TOA_ANCHOR_UNCHANGED =
    0u;
  static constexpr uint8_t TOA_ANCHOR_RESET =
    1u;
  static constexpr uint8_t TOA_ANCHOR_ACCEPTED =
    2u;
  static constexpr uint8_t TOA_ANCHOR_REJECTED =
    3u;
  static constexpr uint8_t TEST_INACTIVE =
    0u;
  static constexpr uint8_t TEST_TESTING =
    1u;
  static constexpr uint8_t TEST_RECORDING =
    2u;
  static constexpr uint8_t TEST_FAILED =
    3u;

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::LpsSaWeighTxChannel_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::LpsSaWeighTxChannel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaWeighTxChannel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaWeighTxChannel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaWeighTxChannel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaWeighTxChannel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaWeighTxChannel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaWeighTxChannel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaWeighTxChannel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaWeighTxChannel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaWeighTxChannel
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaWeighTxChannel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaWeighTxChannel
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaWeighTxChannel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaWeighTxChannel_ & other) const
  {
    if (this->time_point_ns != other.time_point_ns) {
      return false;
    }
    if (this->dig_stat != other.dig_stat) {
      return false;
    }
    if (this->cal_stat != other.cal_stat) {
      return false;
    }
    if (this->dump_stat != other.dump_stat) {
      return false;
    }
    if (this->best_bkt_wt_in_tonnes != other.best_bkt_wt_in_tonnes) {
      return false;
    }
    if (this->warmup_lifts_required != other.warmup_lifts_required) {
      return false;
    }
    if (this->payload_calc_meth != other.payload_calc_meth) {
      return false;
    }
    if (this->bkt_wt_latched_flag != other.bkt_wt_latched_flag) {
      return false;
    }
    if (this->latch_conditions_met != other.latch_conditions_met) {
      return false;
    }
    if (this->zero_available != other.zero_available) {
      return false;
    }
    if (this->payload != other.payload) {
      return false;
    }
    if (this->lft_seal_status != other.lft_seal_status) {
      return false;
    }
    if (this->flash_enabled != other.flash_enabled) {
      return false;
    }
    if (this->lift_position_sensor_id != other.lift_position_sensor_id) {
      return false;
    }
    if (this->tilt_position_sensor_id != other.tilt_position_sensor_id) {
      return false;
    }
    if (this->lift_head_end_pressure_sensor_id != other.lift_head_end_pressure_sensor_id) {
      return false;
    }
    if (this->lift_rod_end_pressure_sensor_id != other.lift_rod_end_pressure_sensor_id) {
      return false;
    }
    if (this->hydraulic_oil_temperature_sensor_id != other.hydraulic_oil_temperature_sensor_id) {
      return false;
    }
    if (this->imu_sensor_id != other.imu_sensor_id) {
      return false;
    }
    if (this->implement_serial_num != other.implement_serial_num) {
      return false;
    }
    if (this->work_tool_id != other.work_tool_id) {
      return false;
    }
    if (this->lift_position != other.lift_position) {
      return false;
    }
    if (this->lift_cyl_vel != other.lift_cyl_vel) {
      return false;
    }
    if (this->tilt_position != other.tilt_position) {
      return false;
    }
    if (this->weigh_range != other.weigh_range) {
      return false;
    }
    if (this->indicator != other.indicator) {
      return false;
    }
    if (this->cal_wt != other.cal_wt) {
      return false;
    }
    if (this->lift_stalled != other.lift_stalled) {
      return false;
    }
    if (this->lift_valve_command != other.lift_valve_command) {
      return false;
    }
    if (this->tilt_valve_command != other.tilt_valve_command) {
      return false;
    }
    if (this->event_state != other.event_state) {
      return false;
    }
    if (this->diag_state != other.diag_state) {
      return false;
    }
    if (this->info_state != other.info_state) {
      return false;
    }
    if (this->show_exclamation_point != other.show_exclamation_point) {
      return false;
    }
    if (this->excessive_pitch != other.excessive_pitch) {
      return false;
    }
    if (this->bucket_fully_racked != other.bucket_fully_racked) {
      return false;
    }
    if (this->zero_weight != other.zero_weight) {
      return false;
    }
    if (this->simple_cal_adjust != other.simple_cal_adjust) {
      return false;
    }
    if (this->engine_speed_rpm != other.engine_speed_rpm) {
      return false;
    }
    if (this->pid_data != other.pid_data) {
      return false;
    }
    if (this->can11_message_timeout_flag != other.can11_message_timeout_flag) {
      return false;
    }
    if (this->toa_anchored_zero_offset != other.toa_anchored_zero_offset) {
      return false;
    }
    if (this->toa_anchored_factor != other.toa_anchored_factor) {
      return false;
    }
    if (this->toa_anchor_status != other.toa_anchor_status) {
      return false;
    }
    if (this->payload_cal_in_progress != other.payload_cal_in_progress) {
      return false;
    }
    if (this->test_status != other.test_status) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaWeighTxChannel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaWeighTxChannel_

// alias to use template instance with default allocator
using LpsSaWeighTxChannel =
  cpm_common_interfaces::msg::LpsSaWeighTxChannel_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaWeighTxChannel_<ContainerAllocator>::TOA_ANCHOR_UNCHANGED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaWeighTxChannel_<ContainerAllocator>::TOA_ANCHOR_RESET;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaWeighTxChannel_<ContainerAllocator>::TOA_ANCHOR_ACCEPTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaWeighTxChannel_<ContainerAllocator>::TOA_ANCHOR_REJECTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaWeighTxChannel_<ContainerAllocator>::TEST_INACTIVE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaWeighTxChannel_<ContainerAllocator>::TEST_TESTING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaWeighTxChannel_<ContainerAllocator>::TEST_RECORDING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaWeighTxChannel_<ContainerAllocator>::TEST_FAILED;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_TX_CHANNEL__STRUCT_HPP_
