cmake_minimum_required(VERSION 3.8)
project(cpm_scs_bridge)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(cpm_common_interfaces REQUIRED)
find_package(job_mgr_interfaces REQUIRED)
find_package(weigh_app_interfaces REQUIRED)

# Real, already-converted, AIS-free wrapper layer (same pattern as
# direct_dds_test_adapter's AIS_REPO_COMMON):
#   CPM-Loader-ais/prod/common/ros2_wrapper/*.h
set(AIS_REPO_COMMON "${CMAKE_CURRENT_SOURCE_DIR}/../../../CPM-Loader-ais/prod/common")

# Unlike direct_dds_test_adapter, this node ALSO binds real SCS channels via
# task::InterfaceDb (ais/task/Task.h) -- it is the actual SCS-side consumer/
# producer for JobMgr/WeighApp's legacy-UI/hardware/DisplayApp-facing legs
# (see Development-Plan.txt Step 7.1/7.2). That's a closed, prebuilt AIS SDK
# not present in this checkout (same constraint already documented for
# LpsSaJobMgrApp/LpsSaWeighApp's own SConscript CPPPATH/LIBPATH). Point
# these at your real site-2 SDK install before building for target hardware:
set(AIS_SDK_ROOT "" CACHE PATH "Root of the real AIS SDK install (ais/task/Task.h, interfaces/<Channel>/*.h, libais_task, etc.) -- required to build this package for target hardware.")
set(AIS_SDK_LIB_DIR "" CACHE PATH "Directory containing the AIS SDK's prebuilt libraries (libais_task and friends).")

add_executable(cpm_scs_bridge_node
  src/main.cpp
  src/CpmScsBridgeApp.cpp
  src/JobMgrRelays.cpp
)
target_include_directories(cpm_scs_bridge_node PRIVATE
  include
  ${AIS_REPO_COMMON}
  ${AIS_SDK_ROOT}
)
if(AIS_SDK_LIB_DIR)
  target_link_directories(cpm_scs_bridge_node PRIVATE ${AIS_SDK_LIB_DIR})
endif()
# Real AIS SDK libraries (ais_task, and whichever libs the real
# interfaces/<Channel>/ headers require to link -- matches LpsSaJobMgrApp's
# own SConscript LIBS list). Left as a placeholder same as AIS_SDK_ROOT above.
target_link_libraries(cpm_scs_bridge_node
  # ais_task
)
ament_target_dependencies(cpm_scs_bridge_node
  rclcpp
  cpm_common_interfaces
  job_mgr_interfaces
  weigh_app_interfaces
)

install(TARGETS
  cpm_scs_bridge_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
