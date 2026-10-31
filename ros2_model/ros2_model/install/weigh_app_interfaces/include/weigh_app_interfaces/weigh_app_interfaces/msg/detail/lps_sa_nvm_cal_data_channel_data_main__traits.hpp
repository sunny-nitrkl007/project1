// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalDataChannelDataMain.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_data_channel_data_main.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_MAIN__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_MAIN__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_data_channel_data_main__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaNvmCalDataChannelDataMain & msg,
  std::ostream & out)
{
  out << "{";
  // member: raise_slow_empty_lift_heights
  {
    if (msg.raise_slow_empty_lift_heights.size() == 0) {
      out << "raise_slow_empty_lift_heights: []";
    } else {
      out << "raise_slow_empty_lift_heights: [";
      size_t pending_items = msg.raise_slow_empty_lift_heights.size();
      for (auto item : msg.raise_slow_empty_lift_heights) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: raise_slow_empty_pressures
  {
    if (msg.raise_slow_empty_pressures.size() == 0) {
      out << "raise_slow_empty_pressures: []";
    } else {
      out << "raise_slow_empty_pressures: [";
      size_t pending_items = msg.raise_slow_empty_pressures.size();
      for (auto item : msg.raise_slow_empty_pressures) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: lower_slow_empty_lift_heights
  {
    if (msg.lower_slow_empty_lift_heights.size() == 0) {
      out << "lower_slow_empty_lift_heights: []";
    } else {
      out << "lower_slow_empty_lift_heights: [";
      size_t pending_items = msg.lower_slow_empty_lift_heights.size();
      for (auto item : msg.lower_slow_empty_lift_heights) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: lower_slow_empty_pressures
  {
    if (msg.lower_slow_empty_pressures.size() == 0) {
      out << "lower_slow_empty_pressures: []";
    } else {
      out << "lower_slow_empty_pressures: [";
      size_t pending_items = msg.lower_slow_empty_pressures.size();
      for (auto item : msg.lower_slow_empty_pressures) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: raise_slow_full_lift_heights
  {
    if (msg.raise_slow_full_lift_heights.size() == 0) {
      out << "raise_slow_full_lift_heights: []";
    } else {
      out << "raise_slow_full_lift_heights: [";
      size_t pending_items = msg.raise_slow_full_lift_heights.size();
      for (auto item : msg.raise_slow_full_lift_heights) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: raise_slow_full_pressures
  {
    if (msg.raise_slow_full_pressures.size() == 0) {
      out << "raise_slow_full_pressures: []";
    } else {
      out << "raise_slow_full_pressures: [";
      size_t pending_items = msg.raise_slow_full_pressures.size();
      for (auto item : msg.raise_slow_full_pressures) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: lower_slow_full_lift_heights
  {
    if (msg.lower_slow_full_lift_heights.size() == 0) {
      out << "lower_slow_full_lift_heights: []";
    } else {
      out << "lower_slow_full_lift_heights: [";
      size_t pending_items = msg.lower_slow_full_lift_heights.size();
      for (auto item : msg.lower_slow_full_lift_heights) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: lower_slow_full_pressures
  {
    if (msg.lower_slow_full_pressures.size() == 0) {
      out << "lower_slow_full_pressures: []";
    } else {
      out << "lower_slow_full_pressures: [";
      size_t pending_items = msg.lower_slow_full_pressures.size();
      for (auto item : msg.lower_slow_full_pressures) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: raise_speed_empty_slow
  {
    out << "raise_speed_empty_slow: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_speed_empty_slow, out);
    out << ", ";
  }

  // member: raise_speed_empty_fast
  {
    out << "raise_speed_empty_fast: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_speed_empty_fast, out);
    out << ", ";
  }

  // member: raise_fast_delta_p_empty
  {
    out << "raise_fast_delta_p_empty: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_fast_delta_p_empty, out);
    out << ", ";
  }

  // member: raise_speed_full_slow
  {
    out << "raise_speed_full_slow: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_speed_full_slow, out);
    out << ", ";
  }

  // member: raise_speed_full_fast
  {
    out << "raise_speed_full_fast: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_speed_full_fast, out);
    out << ", ";
  }

  // member: raise_fast_delta_p_full
  {
    out << "raise_fast_delta_p_full: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_fast_delta_p_full, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaNvmCalDataChannelDataMain & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: raise_slow_empty_lift_heights
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.raise_slow_empty_lift_heights.size() == 0) {
      out << "raise_slow_empty_lift_heights: []\n";
    } else {
      out << "raise_slow_empty_lift_heights:\n";
      for (auto item : msg.raise_slow_empty_lift_heights) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: raise_slow_empty_pressures
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.raise_slow_empty_pressures.size() == 0) {
      out << "raise_slow_empty_pressures: []\n";
    } else {
      out << "raise_slow_empty_pressures:\n";
      for (auto item : msg.raise_slow_empty_pressures) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: lower_slow_empty_lift_heights
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.lower_slow_empty_lift_heights.size() == 0) {
      out << "lower_slow_empty_lift_heights: []\n";
    } else {
      out << "lower_slow_empty_lift_heights:\n";
      for (auto item : msg.lower_slow_empty_lift_heights) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: lower_slow_empty_pressures
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.lower_slow_empty_pressures.size() == 0) {
      out << "lower_slow_empty_pressures: []\n";
    } else {
      out << "lower_slow_empty_pressures:\n";
      for (auto item : msg.lower_slow_empty_pressures) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: raise_slow_full_lift_heights
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.raise_slow_full_lift_heights.size() == 0) {
      out << "raise_slow_full_lift_heights: []\n";
    } else {
      out << "raise_slow_full_lift_heights:\n";
      for (auto item : msg.raise_slow_full_lift_heights) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: raise_slow_full_pressures
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.raise_slow_full_pressures.size() == 0) {
      out << "raise_slow_full_pressures: []\n";
    } else {
      out << "raise_slow_full_pressures:\n";
      for (auto item : msg.raise_slow_full_pressures) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: lower_slow_full_lift_heights
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.lower_slow_full_lift_heights.size() == 0) {
      out << "lower_slow_full_lift_heights: []\n";
    } else {
      out << "lower_slow_full_lift_heights:\n";
      for (auto item : msg.lower_slow_full_lift_heights) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: lower_slow_full_pressures
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.lower_slow_full_pressures.size() == 0) {
      out << "lower_slow_full_pressures: []\n";
    } else {
      out << "lower_slow_full_pressures:\n";
      for (auto item : msg.lower_slow_full_pressures) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: raise_speed_empty_slow
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "raise_speed_empty_slow: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_speed_empty_slow, out);
    out << "\n";
  }

  // member: raise_speed_empty_fast
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "raise_speed_empty_fast: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_speed_empty_fast, out);
    out << "\n";
  }

  // member: raise_fast_delta_p_empty
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "raise_fast_delta_p_empty: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_fast_delta_p_empty, out);
    out << "\n";
  }

  // member: raise_speed_full_slow
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "raise_speed_full_slow: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_speed_full_slow, out);
    out << "\n";
  }

  // member: raise_speed_full_fast
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "raise_speed_full_fast: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_speed_full_fast, out);
    out << "\n";
  }

  // member: raise_fast_delta_p_full
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "raise_fast_delta_p_full: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_fast_delta_p_full, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaNvmCalDataChannelDataMain & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace weigh_app_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use weigh_app_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain>()
{
  return "weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain";
}

template<>
inline const char * name<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain>()
{
  return "weigh_app_interfaces/msg/LpsSaNvmCalDataChannelDataMain";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_MAIN__TRAITS_HPP_
