// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from status_interfaces:msg/Data.idl
// generated code does not contain a copyright notice

#ifndef STATUS_INTERFACES__MSG__DETAIL__DATA__BUILDER_HPP_
#define STATUS_INTERFACES__MSG__DETAIL__DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "status_interfaces/msg/detail/data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace status_interfaces
{

namespace msg
{

namespace builder
{

class Init_Data_data_group
{
public:
  explicit Init_Data_data_group(::status_interfaces::msg::Data & msg)
  : msg_(msg)
  {}
  ::status_interfaces::msg::Data data_group(::status_interfaces::msg::Data::_data_group_type arg)
  {
    msg_.data_group = std::move(arg);
    return std::move(msg_);
  }

private:
  ::status_interfaces::msg::Data msg_;
};

class Init_Data_stamp
{
public:
  Init_Data_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Data_data_group stamp(::status_interfaces::msg::Data::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_Data_data_group(msg_);
  }

private:
  ::status_interfaces::msg::Data msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::status_interfaces::msg::Data>()
{
  return status_interfaces::msg::builder::Init_Data_stamp();
}

}  // namespace status_interfaces

#endif  // STATUS_INTERFACES__MSG__DETAIL__DATA__BUILDER_HPP_
