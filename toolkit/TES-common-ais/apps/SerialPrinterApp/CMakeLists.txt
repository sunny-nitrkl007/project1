cmake_minimum_required(VERSION 3.16)

project(SerialPrinterApp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Environment variables
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

if(NOT TES_COMMON_DIR)
    message(FATAL_ERROR "Set TES_COMMON_DIR to the TES-common-ais source tree")
endif()

#
# Validate AIS variables
#
foreach(var
    AIS_PC_SSP_CONTENT
    AIS_CORETECH_CONTENT
    AIS_MC_CONTENT
    AIS_PC_CONTENT
    AIS_PLATFORM_COMMON_CONTENT
)
    if(NOT DEFINED ${var})
        message(FATAL_ERROR "${var} is not defined")
    endif()
endforeach()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem date_time)
find_package(Threads REQUIRED)

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

file(GLOB app_sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(SerialPrinterApp
    ${app_sources}
)

#
# AIS modules
#
file(GLOB CORETECH_AIS_MODULES
    LIST_DIRECTORIES TRUE
    "${AIS_CORETECH_CONTENT}/ais_*"
)

#
# Includes
#
target_include_directories(SerialPrinterApp PRIVATE
    ${ROS2_MODELS_INCLUDES}
    "${SSP_DIR}/CPM-Loader-ais/prod/common/ros2wrapper"
    "${SSP_DIR}/CPM-Loader-ais/prod/common"
    "${TES_COMMON_DIR}/prod/common"
    ${CORETECH_AIS_MODULES}
)

#
# Link directories
#
target_link_directories(SerialPrinterApp PRIVATE

    "${SSP_DIR}/eta-ais/build-A7H4-adv/lib"
    "${SSP_DIR}/ros2_models/lib/cpm_common_interfaces"
    "${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/usr/lib"
    "${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/usr/lib/aarch64-linux-gnu"
    "${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/opt/cat/ais/lib"
)

target_link_libraries(SerialPrinterApp PRIVATE
    ruby
    #
    # Generated ROS2 interfaces
    #
    ${CPM_COMMON_INTERFACE_LIBS}
    #
    # CPM libs (if defined)
    #
    ${CPM_LIBS}

    #
    # Boost / threading (IFlocker, std::async print worker)
    #
    Boost::filesystem
    Boost::date_time
    Threads::Threads

    #
    # Runtime
    #
    pthread
    rclcpp::rclcpp
)

target_link_options(SerialPrinterApp PRIVATE
    "-Wl,-rpath-link,${SSP_DIR}/eta-ais/build-A7H4-adv/lib"
    "-Wl,-rpath-link,${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/usr/lib/aarch64-linux-gnu"
    )

#
# Compiler flags
#
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang"
   AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

    target_compile_options(SerialPrinterApp PRIVATE
        -fpermissive
        -Wno-unused-function
        -Wno-deprecated-declarations
    )

endif()


set_target_properties(SerialPrinterApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
        "${SSP_DIR}/eta-ais/build-A7H4-adv/bin"
)

#
# Copy cate_ros2 runtime libraries
#
add_custom_command(
    TARGET SerialPrinterApp POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E make_directory
            "${SSP_DIR}/eta-ais/build-A7H4-adv/lib"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SSP_DIR}/dependencies/cate_ros2_1.0.1/lib"
            "${SSP_DIR}/eta-ais/build-A7H4-adv/lib"
)

message(STATUS "Build configuration completed successfully!")
