# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target weigh_app_interfaces::weigh_app_interfaces
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${weigh_app_interfaces_TARGETS}.
if(weigh_app_interfaces_TARGETS AND NOT TARGET weigh_app_interfaces::weigh_app_interfaces)
  add_library(weigh_app_interfaces::weigh_app_interfaces INTERFACE IMPORTED)
  set_target_properties(weigh_app_interfaces::weigh_app_interfaces PROPERTIES
    INTERFACE_LINK_LIBRARIES "${weigh_app_interfaces_TARGETS}")
endif()
