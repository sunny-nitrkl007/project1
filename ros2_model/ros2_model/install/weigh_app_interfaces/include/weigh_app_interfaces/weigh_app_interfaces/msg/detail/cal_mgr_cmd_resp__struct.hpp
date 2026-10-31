// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/CalMgrCmdResp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/cal_mgr_cmd_resp.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_RESP__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_RESP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'calibration_resp'
#include "weigh_app_interfaces/msg/detail/cal_mgr_calibration_resp__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__CalMgrCmdResp __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__CalMgrCmdResp __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CalMgrCmdResp_
{
  using Type = CalMgrCmdResp_<ContainerAllocator>;

  explicit CalMgrCmdResp_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : calibration_resp(_init)
  {
    (void)_init;
  }

  explicit CalMgrCmdResp_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : calibration_resp(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _calibration_resp_type =
    weigh_app_interfaces::msg::CalMgrCalibrationResp_<ContainerAllocator>;
  _calibration_resp_type calibration_resp;

  // setters for named parameter idiom
  Type & set__calibration_resp(
    const weigh_app_interfaces::msg::CalMgrCalibrationResp_<ContainerAllocator> & _arg)
  {
    this->calibration_resp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::CalMgrCmdResp_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::CalMgrCmdResp_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::CalMgrCmdResp_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::CalMgrCmdResp_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::CalMgrCmdResp_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::CalMgrCmdResp_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::CalMgrCmdResp_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::CalMgrCmdResp_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::CalMgrCmdResp_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::CalMgrCmdResp_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__CalMgrCmdResp
    std::shared_ptr<weigh_app_interfaces::msg::CalMgrCmdResp_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__CalMgrCmdResp
    std::shared_ptr<weigh_app_interfaces::msg::CalMgrCmdResp_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CalMgrCmdResp_ & other) const
  {
    if (this->calibration_resp != other.calibration_resp) {
      return false;
    }
    return true;
  }
  bool operator!=(const CalMgrCmdResp_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CalMgrCmdResp_

// alias to use template instance with default allocator
using CalMgrCmdResp =
  weigh_app_interfaces::msg::CalMgrCmdResp_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_RESP__STRUCT_HPP_
