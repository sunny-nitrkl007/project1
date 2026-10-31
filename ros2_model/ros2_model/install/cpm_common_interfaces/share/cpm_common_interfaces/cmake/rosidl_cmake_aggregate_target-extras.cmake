# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target cpm_common_interfaces::cpm_common_interfaces
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${cpm_common_interfaces_TARGETS}.
if(cpm_common_interfaces_TARGETS AND NOT TARGET cpm_common_interfaces::cpm_common_interfaces)
  add_library(cpm_common_interfaces::cpm_common_interfaces INTERFACE IMPORTED)
  set_target_properties(cpm_common_interfaces::cpm_common_interfaces PROPERTIES
    INTERFACE_LINK_LIBRARIES "${cpm_common_interfaces_TARGETS}")
endif()
