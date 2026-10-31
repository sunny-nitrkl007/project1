// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaJobMgrReqstChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_job_mgr_reqst_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST_CHANNEL__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST_CHANNEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'command'
#include "cpm_common_interfaces/msg/detail/job_mgr_reqst_channel_command__struct.hpp"
// Member 'data_tipoff_trigger_type'
#include "cpm_common_interfaces/msg/detail/tip_off_trigger_type__struct.hpp"
// Member 'data_tipoff_mode'
#include "cpm_common_interfaces/msg/detail/tip_off_state__struct.hpp"
// Member 'data_subtotal_info'
#include "cpm_common_interfaces/msg/detail/lps_sa_job_mgr_subtotal_info__struct.hpp"
// Member 'requests'
#include "cpm_common_interfaces/msg/detail/lps_sa_job_mgr_reqst__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaJobMgrReqstChannel __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaJobMgrReqstChannel __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaJobMgrReqstChannel_
{
  using Type = LpsSaJobMgrReqstChannel_<ContainerAllocator>;

  explicit LpsSaJobMgrReqstChannel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : command(_init),
    data_tipoff_trigger_type(_init),
    data_tipoff_mode(_init),
    data_subtotal_info(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->app_name = "";
      this->app_request_id = 0ul;
      this->data_auto_store_pass_count = 0;
      this->data_task_number = 0;
      this->data_enabled = false;
      this->data_target_type = 0;
      this->data_subtotal_index = 0;
      this->data_total_target_weight = 0.0f;
    }
  }

  explicit LpsSaJobMgrReqstChannel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : app_name(_alloc),
    command(_alloc, _init),
    data_tipoff_trigger_type(_alloc, _init),
    data_tipoff_mode(_alloc, _init),
    data_subtotal_info(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->app_name = "";
      this->app_request_id = 0ul;
      this->data_auto_store_pass_count = 0;
      this->data_task_number = 0;
      this->data_enabled = false;
      this->data_target_type = 0;
      this->data_subtotal_index = 0;
      this->data_total_target_weight = 0.0f;
    }
  }

  // field types and members
  using _app_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _app_name_type app_name;
  using _app_request_id_type =
    uint32_t;
  _app_request_id_type app_request_id;
  using _command_type =
    cpm_common_interfaces::msg::JobMgrReqstChannelCommand_<ContainerAllocator>;
  _command_type command;
  using _data_tipoff_trigger_type_type =
    cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator>;
  _data_tipoff_trigger_type_type data_tipoff_trigger_type;
  using _data_tipoff_mode_type =
    cpm_common_interfaces::msg::TipOffState_<ContainerAllocator>;
  _data_tipoff_mode_type data_tipoff_mode;
  using _data_auto_store_pass_count_type =
    uint16_t;
  _data_auto_store_pass_count_type data_auto_store_pass_count;
  using _data_task_number_type =
    uint8_t;
  _data_task_number_type data_task_number;
  using _data_enabled_type =
    bool;
  _data_enabled_type data_enabled;
  using _data_target_type_type =
    uint8_t;
  _data_target_type_type data_target_type;
  using _data_subtotal_index_type =
    uint16_t;
  _data_subtotal_index_type data_subtotal_index;
  using _data_total_target_weight_type =
    float;
  _data_total_target_weight_type data_total_target_weight;
  using _data_subtotal_info_type =
    cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo_<ContainerAllocator>;
  _data_subtotal_info_type data_subtotal_info;
  using _requests_type =
    std::vector<cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator>>>;
  _requests_type requests;

  // setters for named parameter idiom
  Type & set__app_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->app_name = _arg;
    return *this;
  }
  Type & set__app_request_id(
    const uint32_t & _arg)
  {
    this->app_request_id = _arg;
    return *this;
  }
  Type & set__command(
    const cpm_common_interfaces::msg::JobMgrReqstChannelCommand_<ContainerAllocator> & _arg)
  {
    this->command = _arg;
    return *this;
  }
  Type & set__data_tipoff_trigger_type(
    const cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator> & _arg)
  {
    this->data_tipoff_trigger_type = _arg;
    return *this;
  }
  Type & set__data_tipoff_mode(
    const cpm_common_interfaces::msg::TipOffState_<ContainerAllocator> & _arg)
  {
    this->data_tipoff_mode = _arg;
    return *this;
  }
  Type & set__data_auto_store_pass_count(
    const uint16_t & _arg)
  {
    this->data_auto_store_pass_count = _arg;
    return *this;
  }
  Type & set__data_task_number(
    const uint8_t & _arg)
  {
    this->data_task_number = _arg;
    return *this;
  }
  Type & set__data_enabled(
    const bool & _arg)
  {
    this->data_enabled = _arg;
    return *this;
  }
  Type & set__data_target_type(
    const uint8_t & _arg)
  {
    this->data_target_type = _arg;
    return *this;
  }
  Type & set__data_subtotal_index(
    const uint16_t & _arg)
  {
    this->data_subtotal_index = _arg;
    return *this;
  }
  Type & set__data_total_target_weight(
    const float & _arg)
  {
    this->data_total_target_weight = _arg;
    return *this;
  }
  Type & set__data_subtotal_info(
    const cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo_<ContainerAllocator> & _arg)
  {
    this->data_subtotal_info = _arg;
    return *this;
  }
  Type & set__requests(
    const std::vector<cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator>>> & _arg)
  {
    this->requests = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaJobMgrReqstChannel
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaJobMgrReqstChannel
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaJobMgrReqstChannel_ & other) const
  {
    if (this->app_name != other.app_name) {
      return false;
    }
    if (this->app_request_id != other.app_request_id) {
      return false;
    }
    if (this->command != other.command) {
      return false;
    }
    if (this->data_tipoff_trigger_type != other.data_tipoff_trigger_type) {
      return false;
    }
    if (this->data_tipoff_mode != other.data_tipoff_mode) {
      return false;
    }
    if (this->data_auto_store_pass_count != other.data_auto_store_pass_count) {
      return false;
    }
    if (this->data_task_number != other.data_task_number) {
      return false;
    }
    if (this->data_enabled != other.data_enabled) {
      return false;
    }
    if (this->data_target_type != other.data_target_type) {
      return false;
    }
    if (this->data_subtotal_index != other.data_subtotal_index) {
      return false;
    }
    if (this->data_total_target_weight != other.data_total_target_weight) {
      return false;
    }
    if (this->data_subtotal_info != other.data_subtotal_info) {
      return false;
    }
    if (this->requests != other.requests) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaJobMgrReqstChannel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaJobMgrReqstChannel_

// alias to use template instance with default allocator
using LpsSaJobMgrReqstChannel =
  cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST_CHANNEL__STRUCT_HPP_
