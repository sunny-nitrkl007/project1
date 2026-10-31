#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "job_mgr_interfaces::job_mgr_interfaces__rosidl_generator_py" for configuration ""
set_property(TARGET job_mgr_interfaces::job_mgr_interfaces__rosidl_generator_py APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(job_mgr_interfaces::job_mgr_interfaces__rosidl_generator_py PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NOCONFIG "job_mgr_interfaces::job_mgr_interfaces__rosidl_generator_c;job_mgr_interfaces::job_mgr_interfaces__rosidl_typesupport_c;cpm_common_interfaces::cpm_common_interfaces__rosidl_generator_c;cpm_common_interfaces::cpm_common_interfaces__rosidl_typesupport_fastrtps_c;cpm_common_interfaces::cpm_common_interfaces__rosidl_typesupport_introspection_c;cpm_common_interfaces::cpm_common_interfaces__rosidl_typesupport_c;cpm_common_interfaces::cpm_common_interfaces__rosidl_typesupport_fastrtps_cpp;cpm_common_interfaces::cpm_common_interfaces__rosidl_typesupport_introspection_cpp;cpm_common_interfaces::cpm_common_interfaces__rosidl_typesupport_cpp;cpm_common_interfaces::cpm_common_interfaces__rosidl_generator_py"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libjob_mgr_interfaces__rosidl_generator_py.so"
  IMPORTED_SONAME_NOCONFIG "libjob_mgr_interfaces__rosidl_generator_py.so"
  )

list(APPEND _cmake_import_check_targets job_mgr_interfaces::job_mgr_interfaces__rosidl_generator_py )
list(APPEND _cmake_import_check_files_for_job_mgr_interfaces::job_mgr_interfaces__rosidl_generator_py "${_IMPORT_PREFIX}/lib/libjob_mgr_interfaces__rosidl_generator_py.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
