// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaWeighRespChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_weigh_resp_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_RESP_CHANNEL__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_RESP_CHANNEL__STRUCT_HPP_

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

#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaWeighRespChannel __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaWeighRespChannel __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaWeighRespChannel_
{
  using Type = LpsSaWeighRespChannel_<ContainerAllocator>;

  explicit LpsSaWeighRespChannel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : command(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->app_name = "";
      this->app_request_id = 0ul;
      this->time_point_ns = 0ll;
      this->success = false;
      this->arg1 = "";
    }
  }

  explicit LpsSaWeighRespChannel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : app_name(_alloc),
    command(_alloc, _init),
    arg1(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->app_name = "";
      this->app_request_id = 0ul;
      this->time_point_ns = 0ll;
      this->success = false;
      this->arg1 = "";
    }
  }

  // field types and members
  using _app_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _app_name_type app_name;
  using _app_request_id_type =
    uint32_t;
  _app_request_id_type app_request_id;
  using _time_point_ns_type =
    int64_t;
  _time_point_ns_type time_point_ns;
  using _command_type =
    cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator>;
  _command_type command;
  using _success_type =
    bool;
  _success_type success;
  using _arg1_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _arg1_type arg1;

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
  Type & set__time_point_ns(
    const int64_t & _arg)
  {
    this->time_point_ns = _arg;
    return *this;
  }
  Type & set__command(
    const cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator> & _arg)
  {
    this->command = _arg;
    return *this;
  }
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__arg1(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->arg1 = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::LpsSaWeighRespChannel_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::LpsSaWeighRespChannel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaWeighRespChannel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaWeighRespChannel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaWeighRespChannel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaWeighRespChannel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaWeighRespChannel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaWeighRespChannel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaWeighRespChannel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaWeighRespChannel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaWeighRespChannel
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaWeighRespChannel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaWeighRespChannel
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaWeighRespChannel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaWeighRespChannel_ & other) const
  {
    if (this->app_name != other.app_name) {
      return false;
    }
    if (this->app_request_id != other.app_request_id) {
      return false;
    }
    if (this->time_point_ns != other.time_point_ns) {
      return false;
    }
    if (this->command != other.command) {
      return false;
    }
    if (this->success != other.success) {
      return false;
    }
    if (this->arg1 != other.arg1) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaWeighRespChannel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaWeighRespChannel_

// alias to use template instance with default allocator
using LpsSaWeighRespChannel =
  cpm_common_interfaces::msg::LpsSaWeighRespChannel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_RESP_CHANNEL__STRUCT_HPP_
