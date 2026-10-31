// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaWeighReqstChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_weigh_reqst_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_REQST_CHANNEL__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_REQST_CHANNEL__STRUCT_HPP_

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
#include "cpm_common_interfaces/msg/detail/weigh_reqst_channel_command__struct.hpp"
// Member 'arg_map'
#include "cpm_common_interfaces/msg/detail/float_pair__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaWeighReqstChannel __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaWeighReqstChannel __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaWeighReqstChannel_
{
  using Type = LpsSaWeighReqstChannel_<ContainerAllocator>;

  explicit LpsSaWeighReqstChannel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : command(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->app_name = "";
      this->app_request_id = 0ul;
      this->arg_b = false;
      this->arg_f1 = 0.0f;
      this->arg_f2 = 0.0f;
      this->arg_s = "";
      this->arg_u = 0ul;
    }
  }

  explicit LpsSaWeighReqstChannel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : app_name(_alloc),
    command(_alloc, _init),
    arg_s(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->app_name = "";
      this->app_request_id = 0ul;
      this->arg_b = false;
      this->arg_f1 = 0.0f;
      this->arg_f2 = 0.0f;
      this->arg_s = "";
      this->arg_u = 0ul;
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
    cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator>;
  _command_type command;
  using _arg_b_type =
    bool;
  _arg_b_type arg_b;
  using _arg_f1_type =
    float;
  _arg_f1_type arg_f1;
  using _arg_f2_type =
    float;
  _arg_f2_type arg_f2;
  using _arg_s_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _arg_s_type arg_s;
  using _arg_u_type =
    uint32_t;
  _arg_u_type arg_u;
  using _arg_map_type =
    std::vector<cpm_common_interfaces::msg::FloatPair_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cpm_common_interfaces::msg::FloatPair_<ContainerAllocator>>>;
  _arg_map_type arg_map;

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
    const cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator> & _arg)
  {
    this->command = _arg;
    return *this;
  }
  Type & set__arg_b(
    const bool & _arg)
  {
    this->arg_b = _arg;
    return *this;
  }
  Type & set__arg_f1(
    const float & _arg)
  {
    this->arg_f1 = _arg;
    return *this;
  }
  Type & set__arg_f2(
    const float & _arg)
  {
    this->arg_f2 = _arg;
    return *this;
  }
  Type & set__arg_s(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->arg_s = _arg;
    return *this;
  }
  Type & set__arg_u(
    const uint32_t & _arg)
  {
    this->arg_u = _arg;
    return *this;
  }
  Type & set__arg_map(
    const std::vector<cpm_common_interfaces::msg::FloatPair_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cpm_common_interfaces::msg::FloatPair_<ContainerAllocator>>> & _arg)
  {
    this->arg_map = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::LpsSaWeighReqstChannel_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::LpsSaWeighReqstChannel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaWeighReqstChannel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaWeighReqstChannel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaWeighReqstChannel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaWeighReqstChannel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaWeighReqstChannel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaWeighReqstChannel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaWeighReqstChannel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaWeighReqstChannel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaWeighReqstChannel
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaWeighReqstChannel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaWeighReqstChannel
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaWeighReqstChannel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaWeighReqstChannel_ & other) const
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
    if (this->arg_b != other.arg_b) {
      return false;
    }
    if (this->arg_f1 != other.arg_f1) {
      return false;
    }
    if (this->arg_f2 != other.arg_f2) {
      return false;
    }
    if (this->arg_s != other.arg_s) {
      return false;
    }
    if (this->arg_u != other.arg_u) {
      return false;
    }
    if (this->arg_map != other.arg_map) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaWeighReqstChannel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaWeighReqstChannel_

// alias to use template instance with default allocator
using LpsSaWeighReqstChannel =
  cpm_common_interfaces::msg::LpsSaWeighReqstChannel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_REQST_CHANNEL__STRUCT_HPP_
