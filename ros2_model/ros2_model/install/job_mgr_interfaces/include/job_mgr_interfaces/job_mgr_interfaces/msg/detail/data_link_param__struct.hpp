// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/DataLinkParam.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/data_link_param.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__DataLinkParam __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__DataLinkParam __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DataLinkParam_
{
  using Type = DataLinkParam_<ContainerAllocator>;

  explicit DataLinkParam_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->param_id = 0ul;
      this->identifier_type = 0;
      this->pid_data_received = false;
      this->last_value_dsi = 0;
      this->last_good_value_u8 = 0;
      this->last_good_value_u16 = 0;
      this->last_value_eng = 0.0;
    }
  }

  explicit DataLinkParam_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->param_id = 0ul;
      this->identifier_type = 0;
      this->pid_data_received = false;
      this->last_value_dsi = 0;
      this->last_good_value_u8 = 0;
      this->last_good_value_u16 = 0;
      this->last_value_eng = 0.0;
    }
  }

  // field types and members
  using _param_id_type =
    uint32_t;
  _param_id_type param_id;
  using _identifier_type_type =
    uint8_t;
  _identifier_type_type identifier_type;
  using _pid_data_received_type =
    bool;
  _pid_data_received_type pid_data_received;
  using _last_value_dsi_type =
    uint16_t;
  _last_value_dsi_type last_value_dsi;
  using _last_good_value_u8_type =
    uint8_t;
  _last_good_value_u8_type last_good_value_u8;
  using _last_good_value_u16_type =
    uint16_t;
  _last_good_value_u16_type last_good_value_u16;
  using _last_value_eng_type =
    double;
  _last_value_eng_type last_value_eng;

  // setters for named parameter idiom
  Type & set__param_id(
    const uint32_t & _arg)
  {
    this->param_id = _arg;
    return *this;
  }
  Type & set__identifier_type(
    const uint8_t & _arg)
  {
    this->identifier_type = _arg;
    return *this;
  }
  Type & set__pid_data_received(
    const bool & _arg)
  {
    this->pid_data_received = _arg;
    return *this;
  }
  Type & set__last_value_dsi(
    const uint16_t & _arg)
  {
    this->last_value_dsi = _arg;
    return *this;
  }
  Type & set__last_good_value_u8(
    const uint8_t & _arg)
  {
    this->last_good_value_u8 = _arg;
    return *this;
  }
  Type & set__last_good_value_u16(
    const uint16_t & _arg)
  {
    this->last_good_value_u16 = _arg;
    return *this;
  }
  Type & set__last_value_eng(
    const double & _arg)
  {
    this->last_value_eng = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::DataLinkParam_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::DataLinkParam_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::DataLinkParam_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::DataLinkParam_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::DataLinkParam_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::DataLinkParam_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::DataLinkParam_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::DataLinkParam_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::DataLinkParam_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::DataLinkParam_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__DataLinkParam
    std::shared_ptr<job_mgr_interfaces::msg::DataLinkParam_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__DataLinkParam
    std::shared_ptr<job_mgr_interfaces::msg::DataLinkParam_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DataLinkParam_ & other) const
  {
    if (this->param_id != other.param_id) {
      return false;
    }
    if (this->identifier_type != other.identifier_type) {
      return false;
    }
    if (this->pid_data_received != other.pid_data_received) {
      return false;
    }
    if (this->last_value_dsi != other.last_value_dsi) {
      return false;
    }
    if (this->last_good_value_u8 != other.last_good_value_u8) {
      return false;
    }
    if (this->last_good_value_u16 != other.last_good_value_u16) {
      return false;
    }
    if (this->last_value_eng != other.last_value_eng) {
      return false;
    }
    return true;
  }
  bool operator!=(const DataLinkParam_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DataLinkParam_

// alias to use template instance with default allocator
using DataLinkParam =
  job_mgr_interfaces::msg::DataLinkParam_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__STRUCT_HPP_
