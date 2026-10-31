// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/PartNumbers.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/part_numbers.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__PART_NUMBERS__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__PART_NUMBERS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__PartNumbers __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__PartNumbers __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PartNumbers_
{
  using Type = PartNumbers_<ContainerAllocator>;

  explicit PartNumbers_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->product_id_num = "";
      this->equipment_id = "";
      this->sw_group_part_num = "";
      this->sw_group_release_date = "";
      this->sw_group_description = "";
      this->ecm_part_num = "";
      this->model_num = "";
      this->ecm_serial_num = "";
      this->product_id_num_set = false;
      this->sw_group_part_num_set = false;
      this->sw_group_release_date_set = false;
      this->sw_group_description_set = false;
      this->ecm_part_num_set = false;
      this->model_num_set = false;
      this->ecm_serial_num_set = false;
      this->equipment_id_set = false;
    }
  }

  explicit PartNumbers_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : product_id_num(_alloc),
    equipment_id(_alloc),
    sw_group_part_num(_alloc),
    sw_group_release_date(_alloc),
    sw_group_description(_alloc),
    ecm_part_num(_alloc),
    model_num(_alloc),
    ecm_serial_num(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->product_id_num = "";
      this->equipment_id = "";
      this->sw_group_part_num = "";
      this->sw_group_release_date = "";
      this->sw_group_description = "";
      this->ecm_part_num = "";
      this->model_num = "";
      this->ecm_serial_num = "";
      this->product_id_num_set = false;
      this->sw_group_part_num_set = false;
      this->sw_group_release_date_set = false;
      this->sw_group_description_set = false;
      this->ecm_part_num_set = false;
      this->model_num_set = false;
      this->ecm_serial_num_set = false;
      this->equipment_id_set = false;
    }
  }

  // field types and members
  using _product_id_num_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _product_id_num_type product_id_num;
  using _equipment_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _equipment_id_type equipment_id;
  using _sw_group_part_num_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _sw_group_part_num_type sw_group_part_num;
  using _sw_group_release_date_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _sw_group_release_date_type sw_group_release_date;
  using _sw_group_description_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _sw_group_description_type sw_group_description;
  using _ecm_part_num_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _ecm_part_num_type ecm_part_num;
  using _model_num_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _model_num_type model_num;
  using _ecm_serial_num_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _ecm_serial_num_type ecm_serial_num;
  using _product_id_num_set_type =
    bool;
  _product_id_num_set_type product_id_num_set;
  using _sw_group_part_num_set_type =
    bool;
  _sw_group_part_num_set_type sw_group_part_num_set;
  using _sw_group_release_date_set_type =
    bool;
  _sw_group_release_date_set_type sw_group_release_date_set;
  using _sw_group_description_set_type =
    bool;
  _sw_group_description_set_type sw_group_description_set;
  using _ecm_part_num_set_type =
    bool;
  _ecm_part_num_set_type ecm_part_num_set;
  using _model_num_set_type =
    bool;
  _model_num_set_type model_num_set;
  using _ecm_serial_num_set_type =
    bool;
  _ecm_serial_num_set_type ecm_serial_num_set;
  using _equipment_id_set_type =
    bool;
  _equipment_id_set_type equipment_id_set;

  // setters for named parameter idiom
  Type & set__product_id_num(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->product_id_num = _arg;
    return *this;
  }
  Type & set__equipment_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->equipment_id = _arg;
    return *this;
  }
  Type & set__sw_group_part_num(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->sw_group_part_num = _arg;
    return *this;
  }
  Type & set__sw_group_release_date(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->sw_group_release_date = _arg;
    return *this;
  }
  Type & set__sw_group_description(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->sw_group_description = _arg;
    return *this;
  }
  Type & set__ecm_part_num(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->ecm_part_num = _arg;
    return *this;
  }
  Type & set__model_num(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->model_num = _arg;
    return *this;
  }
  Type & set__ecm_serial_num(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->ecm_serial_num = _arg;
    return *this;
  }
  Type & set__product_id_num_set(
    const bool & _arg)
  {
    this->product_id_num_set = _arg;
    return *this;
  }
  Type & set__sw_group_part_num_set(
    const bool & _arg)
  {
    this->sw_group_part_num_set = _arg;
    return *this;
  }
  Type & set__sw_group_release_date_set(
    const bool & _arg)
  {
    this->sw_group_release_date_set = _arg;
    return *this;
  }
  Type & set__sw_group_description_set(
    const bool & _arg)
  {
    this->sw_group_description_set = _arg;
    return *this;
  }
  Type & set__ecm_part_num_set(
    const bool & _arg)
  {
    this->ecm_part_num_set = _arg;
    return *this;
  }
  Type & set__model_num_set(
    const bool & _arg)
  {
    this->model_num_set = _arg;
    return *this;
  }
  Type & set__ecm_serial_num_set(
    const bool & _arg)
  {
    this->ecm_serial_num_set = _arg;
    return *this;
  }
  Type & set__equipment_id_set(
    const bool & _arg)
  {
    this->equipment_id_set = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::PartNumbers_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::PartNumbers_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::PartNumbers_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::PartNumbers_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::PartNumbers_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::PartNumbers_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::PartNumbers_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::PartNumbers_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::PartNumbers_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::PartNumbers_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__PartNumbers
    std::shared_ptr<weigh_app_interfaces::msg::PartNumbers_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__PartNumbers
    std::shared_ptr<weigh_app_interfaces::msg::PartNumbers_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PartNumbers_ & other) const
  {
    if (this->product_id_num != other.product_id_num) {
      return false;
    }
    if (this->equipment_id != other.equipment_id) {
      return false;
    }
    if (this->sw_group_part_num != other.sw_group_part_num) {
      return false;
    }
    if (this->sw_group_release_date != other.sw_group_release_date) {
      return false;
    }
    if (this->sw_group_description != other.sw_group_description) {
      return false;
    }
    if (this->ecm_part_num != other.ecm_part_num) {
      return false;
    }
    if (this->model_num != other.model_num) {
      return false;
    }
    if (this->ecm_serial_num != other.ecm_serial_num) {
      return false;
    }
    if (this->product_id_num_set != other.product_id_num_set) {
      return false;
    }
    if (this->sw_group_part_num_set != other.sw_group_part_num_set) {
      return false;
    }
    if (this->sw_group_release_date_set != other.sw_group_release_date_set) {
      return false;
    }
    if (this->sw_group_description_set != other.sw_group_description_set) {
      return false;
    }
    if (this->ecm_part_num_set != other.ecm_part_num_set) {
      return false;
    }
    if (this->model_num_set != other.model_num_set) {
      return false;
    }
    if (this->ecm_serial_num_set != other.ecm_serial_num_set) {
      return false;
    }
    if (this->equipment_id_set != other.equipment_id_set) {
      return false;
    }
    return true;
  }
  bool operator!=(const PartNumbers_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PartNumbers_

// alias to use template instance with default allocator
using PartNumbers =
  weigh_app_interfaces::msg::PartNumbers_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__PART_NUMBERS__STRUCT_HPP_
