cmake_minimum_required(VERSION 3.16)

project(VP3FileCreationApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Environment
#
if(NOT SSP_DIR AND DEFINED ENV{SSP_DIR})
    set(SSP_DIR "$ENV{SSP_DIR}")
endif()

if(NOT TES_COMMON_DIR AND DEFINED ENV{TES_COMMON_DIR})
    set(TES_COMMON_DIR "$ENV{TES_COMMON_DIR}")
endif()

message(STATUS "SSP_DIR       : ${SSP_DIR}")
message(STATUS "TES_COMMON_DIR: ${TES_COMMON_DIR}")

if(NOT SSP_DIR)
    message(FATAL_ERROR "Set SSP_DIR to the root of the SSP source tree")
endif()

#
# Dependencies
#
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

find_package(Boost REQUIRED COMPONENTS
    serialization
    filesystem
    system
)

find_package(Threads REQUIRED)

#
# Repository Root
#
get_filename_component(
    REPOSITORY_ROOT
    "${CMAKE_CURRENT_SOURCE_DIR}/../../.."
    ABSOLUTE
)

#
# cate_ros2 includes
#
file(GLOB CATE_ROS2_INCLUDE_ROOT
    "${SSP_DIR}/dependencies/cate_ros2*/include"
)

file(GLOB CATE_ROS2_INCLUDE_DIRS
    "${SSP_DIR}/dependencies/cate_ros2*/include/*"
)

#
# cate_ros2 libs
#
file(GLOB CATE_ROS2_LIB_DIR
    "${SSP_DIR}/dependencies/cate_ros2*/lib"
)

#
# ROS2 interface libraries
#
file(GLOB CPM_COMMON_INTERFACE_LIBS
    "${SSP_DIR}/ros2_models/lib/cpm_common_interfaces/lib*.so"
)

list(FILTER CPM_COMMON_INTERFACE_LIBS
     EXCLUDE REGEX ".*generator_py.*")

file(GLOB WEIGH_APP_INTERFACE_LIBS
    "${SSP_DIR}/ros2_models/lib/weigh_app_interfaces/lib*.so"
)

list(FILTER WEIGH_APP_INTERFACE_LIBS
     EXCLUDE REGEX ".*generator_py.*")

#
# Executable
#
add_executable(
    VP3FileCreationApp
    VP3FileCreationApp.cpp
)

#
# Includes
#
target_include_directories(VP3FileCreationApp PRIVATE

    ${Boost_INCLUDE_DIRS}

    ${CATE_ROS2_INCLUDE_ROOT}
    ${CATE_ROS2_INCLUDE_DIRS}

    "${SSP_DIR}/ros2_models/include"

    "${REPOSITORY_ROOT}/TES-common-ais/prod/common"

    "${REPOSITORY_ROOT}/CPM-Loader-ais/prod/common"

    "${REPOSITORY_ROOT}/CPM-Loader-ais/prod/common/ros2wrapper"
)

#
# Link directories
#
target_link_directories(VP3FileCreationApp PRIVATE

    ${CATE_ROS2_LIB_DIR}

    "${SSP_DIR}/ros2_models/lib/cpm_common_interfaces"

    "${SSP_DIR}/ros2_models/lib/weigh_app_interfaces"

    "${SSP_DIR}/dependencies/libyaml_0.2.5/lib"
)

#
# Libraries
#
target_link_libraries(VP3FileCreationApp PRIVATE

    rclcpp::rclcpp

    ${CPM_COMMON_INTERFACE_LIBS}
    ${WEIGH_APP_INTERFACE_LIBS}

    ${Boost_LIBRARIES}

    Threads::Threads

    pthread
)

#
# RPATH
#
foreach(_path
    ${CATE_ROS2_LIB_DIR}
    "${SSP_DIR}/ros2_models/lib/cpm_common_interfaces"
    "${SSP_DIR}/ros2_models/lib/weigh_app_interfaces"
    "${SSP_DIR}/dependencies/libyaml_0.2.5/lib"
)
    target_link_options(VP3FileCreationApp PRIVATE
        "-Wl,-rpath,${_path}"
        "-Wl,-rpath-link,${_path}"
    )
endforeach()

#
# Compiler options
#
target_compile_options(VP3FileCreationApp PRIVATE
    -fpermissive
    -Wno-unused-function
    -Wno-deprecated-declarations
)

#
# Output location
#
set_target_properties(VP3FileCreationApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
        "${SSP_DIR}/eta-ais/build-A7H4-adv/bin"
)

#
# Copy cate_ros2 runtime libraries
#
add_custom_command(
    TARGET VP3FileCreationApp POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E make_directory
            "${SSP_DIR}/eta-ais/build-A7H4-adv/lib"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SSP_DIR}/dependencies/cate_ros2_1.0.1/lib"
            "${SSP_DIR}/eta-ais/build-A7H4-adv/lib"
)

#
# Install
#
install(
    TARGETS VP3FileCreationApp
    RUNTIME DESTINATION bin
)

message(STATUS "VP3FileCreationApp configuration completed successfully")