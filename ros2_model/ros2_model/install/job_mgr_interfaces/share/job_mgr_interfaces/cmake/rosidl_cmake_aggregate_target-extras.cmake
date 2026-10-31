# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target job_mgr_interfaces::job_mgr_interfaces
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${job_mgr_interfaces_TARGETS}.
if(job_mgr_interfaces_TARGETS AND NOT TARGET job_mgr_interfaces::job_mgr_interfaces)
  add_library(job_mgr_interfaces::job_mgr_interfaces INTERFACE IMPORTED)
  set_target_properties(job_mgr_interfaces::job_mgr_interfaces PROPERTIES
    INTERFACE_LINK_LIBRARIES "${job_mgr_interfaces_TARGETS}")
endif()
