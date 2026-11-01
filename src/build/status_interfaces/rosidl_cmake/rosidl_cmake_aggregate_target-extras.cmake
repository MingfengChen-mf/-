# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target status_interfaces::status_interfaces
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${status_interfaces_TARGETS}.
if(status_interfaces_TARGETS AND NOT TARGET status_interfaces::status_interfaces)
  add_library(status_interfaces::status_interfaces INTERFACE IMPORTED)
  set_target_properties(status_interfaces::status_interfaces PROPERTIES
    INTERFACE_LINK_LIBRARIES "${status_interfaces_TARGETS}")
endif()
