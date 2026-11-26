cmake_minimum_required(VERSION 3.16)

#
# aisXcpServer (task XcpServerTask)
#
project(aisXcpServer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Environment variables
#
if(NOT SSP_DIR AND DEFINED ENV{SSP_DIR})
    set(SSP_DIR "$ENV{SSP_DIR}")
endif()

message(STATUS "SSP_DIR       : ${SSP_DIR}")

if(NOT SSP_DIR)
    message(FATAL_ERROR "Set SSP_DIR to the root of the SSP source tree")
endif()

#
# Target image staging directory
#
set(XCP_IMAGE_DIR
    "${SSP_DIR}/eta-ais/build-A7H4-adv"
    CACHE PATH "Target image staging directory")

set(XCP_TARGET_SYSROOT
    "${XCP_IMAGE_DIR}/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot"
    CACHE PATH "Target toolchain sysroot")

#
# ROS2
#
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

#
# Boost
#
find_package(Boost REQUIRED COMPONENTS
    filesystem
    system
)

#
# ROS2 include roots
#
set(ROS2_MODELS_INCLUDES
    "${SSP_DIR}/ros2_models/include"
)

#
# ROS2 interface libraries
#
file(GLOB CPM_COMMON_INTERFACE_LIBS
    "${SSP_DIR}/ros2_models/lib/cpm_common_interfaces/lib*.so"
)

list(FILTER CPM_COMMON_INTERFACE_LIBS
     EXCLUDE REGEX ".*generator_py.*")

file(GLOB JOB_MGR_INTERFACE_LIBS
    "${SSP_DIR}/ros2_models/lib/job_mgr_interfaces/lib*.so"
)

list(FILTER JOB_MGR_INTERFACE_LIBS
     EXCLUDE REGEX ".*generator_py.*")

file(GLOB WEIGH_APP_INTERFACE_LIBS
    "${SSP_DIR}/ros2_models/lib/weigh_app_interfaces/lib*.so"
)

list(FILTER WEIGH_APP_INTERFACE_LIBS
     EXCLUDE REGEX ".*generator_py.*")

#
# Sources
#
add_executable(aisXcpServer

    "${CMAKE_CURRENT_SOURCE_DIR}/xcp_server/XCPServer.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/xcp_server/XCPServer_mem.c"

    "${CMAKE_CURRENT_SOURCE_DIR}/xcp_server/db/XCPServerDb.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/xcp_server/linux/XCPHal.c"

    "${CMAKE_CURRENT_SOURCE_DIR}/XcpServerTask.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/xcpServerDb.cpp"
)

#
# Includes
#
target_include_directories(aisXcpServer PRIVATE

    ${ROS2_MODELS_INCLUDES}

    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/xcp_server"
    "${CMAKE_CURRENT_SOURCE_DIR}/xcp_server/linux"

    "${SSP_DIR}/CPM-Loader-ais/prod/common"
    "${SSP_DIR}/CPM-Loader-ais/prod/common/ros2wrapper"
)

#
# Link directories
#
target_link_directories(aisXcpServer PRIVATE

    "${SSP_DIR}/eta-ais/build-A7H4-adv/lib"

    "${SSP_DIR}/ros2_models/lib/cpm_common_interfaces"
    "${SSP_DIR}/ros2_models/lib/job_mgr_interfaces"
    "${SSP_DIR}/ros2_models/lib/weigh_app_interfaces"

    "${XCP_TARGET_SYSROOT}/usr/lib"

    "${XCP_TARGET_SYSROOT}/usr/lib/aarch64-linux-gnu"

    "${XCP_TARGET_SYSROOT}/opt/cat/ais/lib"
)

#
# Libraries
#
target_link_libraries(aisXcpServer PRIVATE

    #
    # Boost
    #
    Boost::filesystem
    Boost::system

    #
    # Generated ROS2 interfaces
    #
    ${CPM_COMMON_INTERFACE_LIBS}
    ${JOB_MGR_INTERFACE_LIBS}
    ${WEIGH_APP_INTERFACE_LIBS}

    yaml-cpp
    tinyxml2
    lz4

    #
    # Runtime
    #
    pthread
    dl
    rt
    numa

    #
    # ROS2 core
    #
    rclcpp::rclcpp
)

#
# Linker options
#
target_link_options(aisXcpServer PRIVATE

    "-Wl,-rpath-link,${SSP_DIR}/eta-ais/build-A7H4-adv/lib"

    "-Wl,-rpath-link,${XCP_TARGET_SYSROOT}/usr/lib"

    "-Wl,-rpath-link,${XCP_TARGET_SYSROOT}/usr/lib/aarch64-linux-gnu"
)

#
# Compiler options
#
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang"
   AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

    target_compile_options(aisXcpServer PRIVATE
        -fpermissive
        -Wno-unused-function
        -Wno-deprecated-declarations
    )

endif()

#
# Output directory
#
set_target_properties(aisXcpServer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
        "${XCP_IMAGE_DIR}/bin"
)

#
# Copy runtime libraries
#
add_custom_command(
    TARGET aisXcpServer POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E make_directory
        "${CMAKE_BINARY_DIR}/build_${PLATFORM}/lib"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SSP_DIR}/eta-ais/build-A7H4-adv/lib"
        "${CMAKE_BINARY_DIR}/build_${PLATFORM}/lib"
)

message(STATUS "aisXcpServer configuration completed successfully")