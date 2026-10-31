// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/LoadRecordSubtotal.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/load_record_subtotal.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_SUBTOTAL__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_SUBTOTAL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'start_time'
// Member 'end_time'
#include "job_mgr_interfaces/msg/detail/load_record_time_stamp__struct.hpp"
// Member 'passes'
#include "job_mgr_interfaces/msg/detail/load_record_pass__struct.hpp"
// Member 'accuracy'
#include "job_mgr_interfaces/msg/detail/weigh_bkt_wt_accuracy__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__LoadRecordSubtotal __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__LoadRecordSubtotal __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LoadRecordSubtotal_
{
  using Type = LoadRecordSubtotal_<ContainerAllocator>;

  explicit LoadRecordSubtotal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : start_time(_init),
    end_time(_init),
    accuracy(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->truck_id = 0ul;
      this->truck_name = "";
      this->truck_target_weight_tonnes = 0.0f;
      this->target_proportion = 0;
      this->target_passes = 0;
      this->material_id = 0ul;
      this->material_name = "";
      this->material_density = 0.0f;
      this->custom_list_name1 = "";
      this->custom_list_name2 = "";
      this->custom_list_name3 = "";
      this->custom_list_name4 = "";
      this->tag1 = "";
      this->tag2 = "";
      this->tag3 = "";
      this->tag4 = "";
      this->icon_type = 0;
      this->zero_weight = 0.0f;
      this->cal_adjust = 0.0f;
      this->weight_tonnes = 0.0f;
    }
  }

  explicit LoadRecordSubtotal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : start_time(_alloc, _init),
    end_time(_alloc, _init),
    truck_name(_alloc),
    material_name(_alloc),
    custom_list_name1(_alloc),
    custom_list_name2(_alloc),
    custom_list_name3(_alloc),
    custom_list_name4(_alloc),
    tag1(_alloc),
    tag2(_alloc),
    tag3(_alloc),
    tag4(_alloc),
    accuracy(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->truck_id = 0ul;
      this->truck_name = "";
      this->truck_target_weight_tonnes = 0.0f;
      this->target_proportion = 0;
      this->target_passes = 0;
      this->material_id = 0ul;
      this->material_name = "";
      this->material_density = 0.0f;
      this->custom_list_name1 = "";
      this->custom_list_name2 = "";
      this->custom_list_name3 = "";
      this->custom_list_name4 = "";
      this->tag1 = "";
      this->tag2 = "";
      this->tag3 = "";
      this->tag4 = "";
      this->icon_type = 0;
      this->zero_weight = 0.0f;
      this->cal_adjust = 0.0f;
      this->weight_tonnes = 0.0f;
    }
  }

  // field types and members
  using _start_time_type =
    job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator>;
  _start_time_type start_time;
  using _end_time_type =
    job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator>;
  _end_time_type end_time;
  using _truck_id_type =
    uint32_t;
  _truck_id_type truck_id;
  using _truck_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _truck_name_type truck_name;
  using _truck_target_weight_tonnes_type =
    float;
  _truck_target_weight_tonnes_type truck_target_weight_tonnes;
  using _target_proportion_type =
    uint16_t;
  _target_proportion_type target_proportion;
  using _target_passes_type =
    uint16_t;
  _target_passes_type target_passes;
  using _material_id_type =
    uint32_t;
  _material_id_type material_id;
  using _material_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _material_name_type material_name;
  using _material_density_type =
    float;
  _material_density_type material_density;
  using _custom_list_name1_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _custom_list_name1_type custom_list_name1;
  using _custom_list_name2_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _custom_list_name2_type custom_list_name2;
  using _custom_list_name3_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _custom_list_name3_type custom_list_name3;
  using _custom_list_name4_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _custom_list_name4_type custom_list_name4;
  using _tag1_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tag1_type tag1;
  using _tag2_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tag2_type tag2;
  using _tag3_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tag3_type tag3;
  using _tag4_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tag4_type tag4;
  using _icon_type_type =
    uint8_t;
  _icon_type_type icon_type;
  using _zero_weight_type =
    float;
  _zero_weight_type zero_weight;
  using _cal_adjust_type =
    float;
  _cal_adjust_type cal_adjust;
  using _passes_type =
    std::vector<job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator>>>;
  _passes_type passes;
  using _weight_tonnes_type =
    float;
  _weight_tonnes_type weight_tonnes;
  using _accuracy_type =
    job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator>;
  _accuracy_type accuracy;

  // setters for named parameter idiom
  Type & set__start_time(
    const job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator> & _arg)
  {
    this->start_time = _arg;
    return *this;
  }
  Type & set__end_time(
    const job_mgr_interfaces::msg::LoadRecordTimeStamp_<ContainerAllocator> & _arg)
  {
    this->end_time = _arg;
    return *this;
  }
  Type & set__truck_id(
    const uint32_t & _arg)
  {
    this->truck_id = _arg;
    return *this;
  }
  Type & set__truck_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->truck_name = _arg;
    return *this;
  }
  Type & set__truck_target_weight_tonnes(
    const float & _arg)
  {
    this->truck_target_weight_tonnes = _arg;
    return *this;
  }
  Type & set__target_proportion(
    const uint16_t & _arg)
  {
    this->target_proportion = _arg;
    return *this;
  }
  Type & set__target_passes(
    const uint16_t & _arg)
  {
    this->target_passes = _arg;
    return *this;
  }
  Type & set__material_id(
    const uint32_t & _arg)
  {
    this->material_id = _arg;
    return *this;
  }
  Type & set__material_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->material_name = _arg;
    return *this;
  }
  Type & set__material_density(
    const float & _arg)
  {
    this->material_density = _arg;
    return *this;
  }
  Type & set__custom_list_name1(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->custom_list_name1 = _arg;
    return *this;
  }
  Type & set__custom_list_name2(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->custom_list_name2 = _arg;
    return *this;
  }
  Type & set__custom_list_name3(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->custom_list_name3 = _arg;
    return *this;
  }
  Type & set__custom_list_name4(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->custom_list_name4 = _arg;
    return *this;
  }
  Type & set__tag1(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tag1 = _arg;
    return *this;
  }
  Type & set__tag2(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tag2 = _arg;
    return *this;
  }
  Type & set__tag3(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tag3 = _arg;
    return *this;
  }
  Type & set__tag4(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tag4 = _arg;
    return *this;
  }
  Type & set__icon_type(
    const uint8_t & _arg)
  {
    this->icon_type = _arg;
    return *this;
  }
  Type & set__zero_weight(
    const float & _arg)
  {
    this->zero_weight = _arg;
    return *this;
  }
  Type & set__cal_adjust(
    const float & _arg)
  {
    this->cal_adjust = _arg;
    return *this;
  }
  Type & set__passes(
    const std::vector<job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<job_mgr_interfaces::msg::LoadRecordPass_<ContainerAllocator>>> & _arg)
  {
    this->passes = _arg;
    return *this;
  }
  Type & set__weight_tonnes(
    const float & _arg)
  {
    this->weight_tonnes = _arg;
    return *this;
  }
  Type & set__accuracy(
    const job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator> & _arg)
  {
    this->accuracy = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__LoadRecordSubtotal
    std::shared_ptr<job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__LoadRecordSubtotal
    std::shared_ptr<job_mgr_interfaces::msg::LoadRecordSubtotal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LoadRecordSubtotal_ & other) const
  {
    if (this->start_time != other.start_time) {
      return false;
    }
    if (this->end_time != other.end_time) {
      return false;
    }
    if (this->truck_id != other.truck_id) {
      return false;
    }
    if (this->truck_name != other.truck_name) {
      return false;
    }
    if (this->truck_target_weight_tonnes != other.truck_target_weight_tonnes) {
      return false;
    }
    if (this->target_proportion != other.target_proportion) {
      return false;
    }
    if (this->target_passes != other.target_passes) {
      return false;
    }
    if (this->material_id != other.material_id) {
      return false;
    }
    if (this->material_name != other.material_name) {
      return false;
    }
    if (this->material_density != other.material_density) {
      return false;
    }
    if (this->custom_list_name1 != other.custom_list_name1) {
      return false;
    }
    if (this->custom_list_name2 != other.custom_list_name2) {
      return false;
    }
    if (this->custom_list_name3 != other.custom_list_name3) {
      return false;
    }
    if (this->custom_list_name4 != other.custom_list_name4) {
      return false;
    }
    if (this->tag1 != other.tag1) {
      return false;
    }
    if (this->tag2 != other.tag2) {
      return false;
    }
    if (this->tag3 != other.tag3) {
      return false;
    }
    if (this->tag4 != other.tag4) {
      return false;
    }
    if (this->icon_type != other.icon_type) {
      return false;
    }
    if (this->zero_weight != other.zero_weight) {
      return false;
    }
    if (this->cal_adjust != other.cal_adjust) {
      return false;
    }
    if (this->passes != other.passes) {
      return false;
    }
    if (this->weight_tonnes != other.weight_tonnes) {
      return false;
    }
    if (this->accuracy != other.accuracy) {
      return false;
    }
    return true;
  }
  bool operator!=(const LoadRecordSubtotal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LoadRecordSubtotal_

// alias to use template instance with default allocator
using LoadRecordSubtotal =
  job_mgr_interfaces::msg::LoadRecordSubtotal_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_SUBTOTAL__STRUCT_HPP_
