// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from status_interfaces:msg/Data.idl
// generated code does not contain a copyright notice

#ifndef STATUS_INTERFACES__MSG__DETAIL__DATA__STRUCT_HPP_
#define STATUS_INTERFACES__MSG__DETAIL__DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__status_interfaces__msg__Data __attribute__((deprecated))
#else
# define DEPRECATED__status_interfaces__msg__Data __declspec(deprecated)
#endif

namespace status_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Data_
{
  using Type = Data_<ContainerAllocator>;

  explicit Data_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<float, 3>::iterator, float>(this->data_group.begin(), this->data_group.end(), 0.0f);
    }
  }

  explicit Data_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init),
    data_group(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<float, 3>::iterator, float>(this->data_group.begin(), this->data_group.end(), 0.0f);
    }
  }

  // field types and members
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _data_group_type =
    std::array<float, 3>;
  _data_group_type data_group;

  // setters for named parameter idiom
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__data_group(
    const std::array<float, 3> & _arg)
  {
    this->data_group = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    status_interfaces::msg::Data_<ContainerAllocator> *;
  using ConstRawPtr =
    const status_interfaces::msg::Data_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<status_interfaces::msg::Data_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<status_interfaces::msg::Data_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      status_interfaces::msg::Data_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<status_interfaces::msg::Data_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      status_interfaces::msg::Data_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<status_interfaces::msg::Data_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<status_interfaces::msg::Data_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<status_interfaces::msg::Data_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__status_interfaces__msg__Data
    std::shared_ptr<status_interfaces::msg::Data_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__status_interfaces__msg__Data
    std::shared_ptr<status_interfaces::msg::Data_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Data_ & other) const
  {
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->data_group != other.data_group) {
      return false;
    }
    return true;
  }
  bool operator!=(const Data_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Data_

// alias to use template instance with default allocator
using Data =
  status_interfaces::msg::Data_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace status_interfaces

#endif  // STATUS_INTERFACES__MSG__DETAIL__DATA__STRUCT_HPP_
