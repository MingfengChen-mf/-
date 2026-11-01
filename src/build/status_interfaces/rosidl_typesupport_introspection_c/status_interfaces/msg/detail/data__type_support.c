// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from status_interfaces:msg/Data.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "status_interfaces/msg/detail/data__rosidl_typesupport_introspection_c.h"
#include "status_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "status_interfaces/msg/detail/data__functions.h"
#include "status_interfaces/msg/detail/data__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void status_interfaces__msg__Data__rosidl_typesupport_introspection_c__Data_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  status_interfaces__msg__Data__init(message_memory);
}

void status_interfaces__msg__Data__rosidl_typesupport_introspection_c__Data_fini_function(void * message_memory)
{
  status_interfaces__msg__Data__fini(message_memory);
}

size_t status_interfaces__msg__Data__rosidl_typesupport_introspection_c__size_function__Data__data_group(
  const void * untyped_member)
{
  (void)untyped_member;
  return 3;
}

const void * status_interfaces__msg__Data__rosidl_typesupport_introspection_c__get_const_function__Data__data_group(
  const void * untyped_member, size_t index)
{
  const float * member =
    (const float *)(untyped_member);
  return &member[index];
}

void * status_interfaces__msg__Data__rosidl_typesupport_introspection_c__get_function__Data__data_group(
  void * untyped_member, size_t index)
{
  float * member =
    (float *)(untyped_member);
  return &member[index];
}

void status_interfaces__msg__Data__rosidl_typesupport_introspection_c__fetch_function__Data__data_group(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    status_interfaces__msg__Data__rosidl_typesupport_introspection_c__get_const_function__Data__data_group(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void status_interfaces__msg__Data__rosidl_typesupport_introspection_c__assign_function__Data__data_group(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    status_interfaces__msg__Data__rosidl_typesupport_introspection_c__get_function__Data__data_group(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember status_interfaces__msg__Data__rosidl_typesupport_introspection_c__Data_message_member_array[2] = {
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(status_interfaces__msg__Data, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "data_group",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    3,  // array size
    false,  // is upper bound
    offsetof(status_interfaces__msg__Data, data_group),  // bytes offset in struct
    NULL,  // default value
    status_interfaces__msg__Data__rosidl_typesupport_introspection_c__size_function__Data__data_group,  // size() function pointer
    status_interfaces__msg__Data__rosidl_typesupport_introspection_c__get_const_function__Data__data_group,  // get_const(index) function pointer
    status_interfaces__msg__Data__rosidl_typesupport_introspection_c__get_function__Data__data_group,  // get(index) function pointer
    status_interfaces__msg__Data__rosidl_typesupport_introspection_c__fetch_function__Data__data_group,  // fetch(index, &value) function pointer
    status_interfaces__msg__Data__rosidl_typesupport_introspection_c__assign_function__Data__data_group,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers status_interfaces__msg__Data__rosidl_typesupport_introspection_c__Data_message_members = {
  "status_interfaces__msg",  // message namespace
  "Data",  // message name
  2,  // number of fields
  sizeof(status_interfaces__msg__Data),
  status_interfaces__msg__Data__rosidl_typesupport_introspection_c__Data_message_member_array,  // message members
  status_interfaces__msg__Data__rosidl_typesupport_introspection_c__Data_init_function,  // function to initialize message memory (memory has to be allocated)
  status_interfaces__msg__Data__rosidl_typesupport_introspection_c__Data_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t status_interfaces__msg__Data__rosidl_typesupport_introspection_c__Data_message_type_support_handle = {
  0,
  &status_interfaces__msg__Data__rosidl_typesupport_introspection_c__Data_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_status_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, status_interfaces, msg, Data)() {
  status_interfaces__msg__Data__rosidl_typesupport_introspection_c__Data_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!status_interfaces__msg__Data__rosidl_typesupport_introspection_c__Data_message_type_support_handle.typesupport_identifier) {
    status_interfaces__msg__Data__rosidl_typesupport_introspection_c__Data_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &status_interfaces__msg__Data__rosidl_typesupport_introspection_c__Data_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
