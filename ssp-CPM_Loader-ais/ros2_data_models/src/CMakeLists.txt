cmake_minimum_required(VERSION 3.22)

project(ros2_data_models)

include(ExternalProject)
find_package(fastcdr REQUIRED)
message(STATUS "fastcdr_DIR=${fastcdr_DIR}")

get_filename_component(
    PROJECT_ROOT
    "${CMAKE_CURRENT_SOURCE_DIR}/../../"
    ABSOLUTE
)

set(INSTALL_DIR
    "${PROJECT_ROOT}/ros2_models"
)

# set(INSTALL_DIR
#     ${CMAKE_BINARY_DIR}/ros2_models
# )

ExternalProject_Add(
    cpm_common_interfaces
    SOURCE_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/cpm_common_interfaces

    BINARY_DIR
        ${CMAKE_BINARY_DIR}/build_cpm_common_interfaces

    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
        -DCMAKE_PREFIX_PATH=${INSTALL_DIR};${CMAKE_PREFIX_PATH}
        -DCMAKE_FIND_PACKAGE_PREFER_CONFIG=ON
        -Dfastcdr_DIR=${fastcdr_DIR}
)

ExternalProject_Add(
    job_mgr_interfaces
    SOURCE_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/job_mgr_interfaces

    BINARY_DIR
        ${CMAKE_BINARY_DIR}/build_job_mgr_interfaces

    DEPENDS
        cpm_common_interfaces

    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
        -DCMAKE_PREFIX_PATH=${INSTALL_DIR};${CMAKE_PREFIX_PATH}
        -DCMAKE_FIND_PACKAGE_PREFER_CONFIG=ON
        -Dfastcdr_DIR=${fastcdr_DIR}
)

ExternalProject_Add(
    weigh_app_interfaces
    SOURCE_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/weigh_app_interfaces

    BINARY_DIR
        ${CMAKE_BINARY_DIR}/build_weigh_app_interfaces

    DEPENDS
        job_mgr_interfaces

    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
        -DCMAKE_PREFIX_PATH=${INSTALL_DIR};${CMAKE_PREFIX_PATH}
        -DCMAKE_FIND_PACKAGE_PREFER_CONFIG=ON
        -Dfastcdr_DIR=${fastcdr_DIR}
)

#
# Convert ROS2 install tree to legacy CPM layout
#
add_custom_target(
    ros2_models_layout ALL
    DEPENDS weigh_app_interfaces

    COMMAND
        ${CMAKE_COMMAND}
        -DINSTALL_DIR=${INSTALL_DIR}
        -P ${CMAKE_CURRENT_SOURCE_DIR}/flatten_layout.cmake

    COMMENT "Converting ROS2 install layout to CPM layout"
)