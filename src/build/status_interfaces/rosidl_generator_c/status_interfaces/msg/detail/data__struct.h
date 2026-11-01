// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from status_interfaces:msg/Data.idl
// generated code does not contain a copyright notice

#ifndef STATUS_INTERFACES__MSG__DETAIL__DATA__STRUCT_H_
#define STATUS_INTERFACES__MSG__DETAIL__DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/Data in the package status_interfaces.
typedef struct status_interfaces__msg__Data
{
  /// 记录时间戳
  builtin_interfaces__msg__Time stamp;
  /// 所需三维数组
  float data_group[3];
} status_interfaces__msg__Data;

// Struct for a sequence of status_interfaces__msg__Data.
typedef struct status_interfaces__msg__Data__Sequence
{
  status_interfaces__msg__Data * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} status_interfaces__msg__Data__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // STATUS_INTERFACES__MSG__DETAIL__DATA__STRUCT_H_
