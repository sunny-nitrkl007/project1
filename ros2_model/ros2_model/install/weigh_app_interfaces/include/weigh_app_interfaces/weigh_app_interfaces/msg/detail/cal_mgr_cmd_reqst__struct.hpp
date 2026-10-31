// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/CalMgrCmdReqst.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/cal_mgr_cmd_reqst.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_REQST__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_REQST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'calibration_request'
#include "weigh_app_interfaces/msg/detail/calibration_request__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__CalMgrCmdReqst __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__CalMgrCmdReqst __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CalMgrCmdReqst_
{
  using Type = CalMgrCmdReqst_<ContainerAllocator>;

  explicit CalMgrCmdReqst_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : calibration_request(_init)
  {
    (void)_init;
  }

  explicit CalMgrCmdReqst_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : calibration_request(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _calibration_request_type =
    weigh_app_interfaces::msg::CalibrationRequest_<ContainerAllocator>;
  _calibration_request_type calibration_request;

  // setters for named parameter idiom
  Type & set__calibration_request(
    const weigh_app_interfaces::msg::CalibrationRequest_<ContainerAllocator> & _arg)
  {
    this->calibration_request = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::CalMgrCmdReqst_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::CalMgrCmdReqst_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::CalMgrCmdReqst_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::CalMgrCmdReqst_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::CalMgrCmdReqst_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::CalMgrCmdReqst_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::CalMgrCmdReqst_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::CalMgrCmdReqst_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::CalMgrCmdReqst_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::CalMgrCmdReqst_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__CalMgrCmdReqst
    std::shared_ptr<weigh_app_interfaces::msg::CalMgrCmdReqst_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__CalMgrCmdReqst
    std::shared_ptr<weigh_app_interfaces::msg::CalMgrCmdReqst_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CalMgrCmdReqst_ & other) const
  {
    if (this->calibration_request != other.calibration_request) {
      return false;
    }
    return true;
  }
  bool operator!=(const CalMgrCmdReqst_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CalMgrCmdReqst_

// alias to use template instance with default allocator
using CalMgrCmdReqst =
  weigh_app_interfaces::msg::CalMgrCmdReqst_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_REQST__STRUCT_HPP_
