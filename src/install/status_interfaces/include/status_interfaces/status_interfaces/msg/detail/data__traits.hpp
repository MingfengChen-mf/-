// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from status_interfaces:msg/Data.idl
// generated code does not contain a copyright notice

#ifndef STATUS_INTERFACES__MSG__DETAIL__DATA__TRAITS_HPP_
#define STATUS_INTERFACES__MSG__DETAIL__DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "status_interfaces/msg/detail/data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace status_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Data & msg,
  std::ostream & out)
{
  out << "{";
  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: data_group
  {
    if (msg.data_group.size() == 0) {
      out << "data_group: []";
    } else {
      out << "data_group: [";
      size_t pending_items = msg.data_group.size();
      for (auto item : msg.data_group) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Data & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }

  // member: data_group
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.data_group.size() == 0) {
      out << "data_group: []\n";
    } else {
      out << "data_group:\n";
      for (auto item : msg.data_group) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Data & msg, bool use_flow_style = false)
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

}  // namespace status_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use status_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const status_interfaces::msg::Data & msg,
  std::ostream & out, size_t indentation = 0)
{
  status_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use status_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const status_interfaces::msg::Data & msg)
{
  return status_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<status_interfaces::msg::Data>()
{
  return "status_interfaces::msg::Data";
}

template<>
inline const char * name<status_interfaces::msg::Data>()
{
  return "status_interfaces/msg/Data";
}

template<>
struct has_fixed_size<status_interfaces::msg::Data>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<status_interfaces::msg::Data>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<status_interfaces::msg::Data>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // STATUS_INTERFACES__MSG__DETAIL__DATA__TRAITS_HPP_
