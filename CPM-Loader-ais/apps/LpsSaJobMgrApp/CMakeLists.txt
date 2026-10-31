cmake_minimum_required(VERSION 3.16)

project(LpsSaJobMgrApp LANGUAGES C CXX)

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

#
# Boost
#

#find_package(cate_ros2 REQUIRED)

find_package(Boost REQUIRED COMPONENTS
    filesystem
    serialization
    thread
    program_options
    system
    chrono
    date_time
    atomic
)

#
# ROS2 include roots
#

#CC
file(GLOB ROS2_PACKAGE_INCLUDES
    "${SSP_DIR}/ros2_sdk/include/*"
    #"${SSP_DIR}/ros2_sdk/include/*"
)
#CC

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
# Entire ROS2 SDK
#

#CC
file(GLOB ROS2_ALL_LIBS
    "${SSP_DIR}/ros2_sdk/lib/*.so"
    #"${SSP_DIR}/ros2_sdk/lib/*.so"
)
#CC

list(SORT ROS2_ALL_LIBS)

list(FILTER ROS2_ALL_LIBS
     EXCLUDE REGEX ".*generator_py.*")

list(FILTER ROS2_ALL_LIBS
     EXCLUDE REGEX ".*lttng.*")     
list(FILTER ROS2_ALL_LIBS EXCLUDE REGEX ".*/liblttng-.*")

message(STATUS "ROS2_ALL_LIBS=${ROS2_ALL_LIBS}")     

#
# LPS Pass Tracker
#
set(_lps_pass_tracker_dir
    "${SSP_DIR}/lps_pass_tracker"
)

foreach(_required_path
    "${SSP_DIR}/lps_common/include"
    "${SSP_DIR}/lps_app_common/include"
    "${_lps_pass_tracker_dir}/include"
    "${_lps_pass_tracker_dir}/src"
    "${TES_COMMON_DIR}/prod/common"
)
    if(NOT IS_DIRECTORY "${_required_path}")
        message(FATAL_ERROR
            "Required directory missing: ${_required_path}"
        )
    endif()
endforeach()

#
# Sources
#
file(GLOB app_sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB lps_pass_tracker_sources CONFIGURE_DEPENDS
    "${_lps_pass_tracker_dir}/src/*.c"
)

add_executable(LpsSaJobMgrApp
    ${app_sources}
    ${lps_pass_tracker_sources}
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
target_include_directories(LpsSaJobMgrApp PRIVATE

    ${ROS2_PACKAGE_INCLUDES}
    ${ROS2_MODELS_INCLUDES}

    "${SSP_DIR}/lps_common/include"
    "${SSP_DIR}/lps_app_common/include"

    "${_lps_pass_tracker_dir}/include"

    "${SSP_DIR}/lps_weighing/include"
    "${SSP_DIR}/lps_weighing/src"
    "${SSP_DIR}/CPM-Loader-ais/prod/common/ros2wrapper"

    "${TES_COMMON_DIR}/prod/common"

    "${SSP_DIR}/eta-ais/prod/common"

    "${AIS_PC_SSP_CONTENT}/include/lib_a4/scl"
    "${AIS_PC_SSP_CONTENT}/include/lib_oel"
    "${AIS_PC_SSP_CONTENT}/include/lib_a4/hal"
    "${AIS_PC_SSP_CONTENT}/include/lib_scl_info"

    "${AIS_CORETECH_CONTENT}"
    "${AIS_CORETECH_CONTENT}/include"
    "${AIS_CORETECH_CONTENT}/generated"

    "${AIS_MC_CONTENT}/include"
    "${AIS_MC_CONTENT}/prod/common"
    "${AIS_MC_CONTENT}/prod/include"

    "${AIS_PC_CONTENT}/include"

    "${AIS_PLATFORM_COMMON_CONTENT}/include"

    ${CORETECH_AIS_MODULES}

    "${SSP_DIR}/CPM-Loader-ais/prod/common"

    "${SSP_DIR}/eta-ais/prod/coretech/include"

    "${SSP_DIR}/eta-ais/prod/machineCommon/content/include"

    "${SSP_DIR}/eta-ais/prod/platformCommon/content/include"

    "${CMAKE_SOURCE_DIR}/include"
)

#
# Link directories
#
target_link_directories(LpsSaJobMgrApp PRIVATE

#CC

    "${SSP_DIR}/ros2_sdk/lib"
    "${SSP_DIR}/ros2_sdk/lib/aarch64-linux-gnu"
    # "${SSP_DIR}/ros2_sdk/lib"
    # "${SSP_DIR}/ros2_sdk/lib/aarch64-linux-gnu"
#CC
    "${SSP_DIR}/eta-ais/build-A7H4-adv/lib"

    "${SSP_DIR}/ros2_models/lib/cpm_common_interfaces"
    "${SSP_DIR}/ros2_models/lib/job_mgr_interfaces"
    "${SSP_DIR}/ros2_models/lib/weigh_app_interfaces"

    "${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/usr/lib"

    "${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/usr/lib/aarch64-linux-gnu"

    "${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/opt/cat/ais/lib"
)

target_link_libraries(LpsSaJobMgrApp PRIVATE

    #
    # AIS
    #
    #ais_task
    ais_config
    ais_log
    ais_channel
    #ais_task_core
    ais_simpleComms
    ais_time
    ais_heartbeat
    ais_executive
    ais_sigcatch
    ais_monitor
    ais_configSection
    ais_filesystem
    ais_interfaces
    ais_serialization

    #
    # Factory
    #
    AisPluginProcessor

    #
    # HUB
    #
    hub_base
    hub_filesystem
    hub_timesync
    hub_csv
    hub_serialization
    hub_utility
    hub_logging
    hub_hash
    hub_parser
    hub_comms
    hub_compression
    hub_debuglog
    hub_debuglog_utility

    #
    # Third-party
    #
    ruby
    snappy
    lzma

    #
    # Entire ROS2 SDK
    #
    -Wl,--start-group
    ${ROS2_ALL_LIBS}
    -Wl,--end-group

    orocos-kdl
    urdfdom_model
    urdf_xml_parser

    #
    # Boost
    #
    Boost::filesystem
    Boost::serialization
    Boost::thread
    Boost::program_options
    Boost::system
    Boost::chrono
    Boost::date_time
    Boost::atomic

    #
    # Generated ROS2 interfaces
    #
    ${CPM_COMMON_INTERFACE_LIBS}
    ${JOB_MGR_INTERFACE_LIBS}
    ${WEIGH_APP_INTERFACE_LIBS}

    #
    # CPM libs (if defined)
    #
    ${CPM_LIBS}

    #
    # Runtime
    #
    pthread
    dl
    rt
    numa

    yaml-cpp
    spdlog
    tinyxml2
    lz4

    #
    # ROS2 core
    #
    rclcpp
    rcl
    rcutils
    rmw
    rmw_implementation
    rcl_yaml_param_parser
    rcl_logging_interface
    rcl_interfaces__rosidl_typesupport_cpp
    rosidl_typesupport_cpp
    rosidl_runtime_c
    ament_index_cpp
    rcpputils
    libstatistics_collector
    statistics_msgs__rosidl_typesupport_cpp
    rosgraph_msgs__rosidl_typesupport_cpp
    type_description_interfaces__rosidl_typesupport_c
    std_msgs__rosidl_typesupport_cpp
)

target_link_options(LpsSaJobMgrApp PRIVATE
#CC

      "-Wl,-rpath-link,${SSP_DIR}/ros2_sdk/lib"
      "-Wl,-rpath-link,${SSP_DIR}/ros2_sdk/lib/aarch64-linux-gnu"
    # "-Wl,-rpath-link,${SSP_DIR}/ros2_sdk/lib"
    # "-Wl,-rpath-link,${SSP_DIR}/ros2_sdk/lib/aarch64-linux-gnu"
    #CC
    
    "-Wl,-rpath-link,${SSP_DIR}/eta-ais/build-A7H4-adv/lib"
    "-Wl,-rpath-link,${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/usr/lib/aarch64-linux-gnu"
    )

target_compile_definitions(LpsSaJobMgrApp PRIVATE
    RAPIDJSON_HAS_STDSTRING=1
    AIS_SERIALIZATION_INCLUDE_BOOST_ARCHIVE
)

#
# Compiler flags
#
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang"
   AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

    target_compile_options(LpsSaJobMgrApp PRIVATE
        -fpermissive
        -Wno-unused-function
        -Wno-deprecated-declarations
    )

endif()


set_target_properties(LpsSaJobMgrApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
        #"${CMAKE_BINARY_DIR}/build_${PLATFORM}/bin"
        "${SSP_DIR}/eta-ais/build-A7H4-adv/bin"
)

add_custom_command(TARGET LpsSaJobMgrApp POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E make_directory
            "${CMAKE_BINARY_DIR}/build_${PLATFORM}/lib"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
    #CC
    
            #"${SSP_DIR}/ros2_sdk/lib"
            "${SSP_DIR}/ros2_sdk/lib"
            #CC
            "${CMAKE_BINARY_DIR}/build_${PLATFORM}/lib"
    
    COMMAND ${CMAKE_COMMAND} -E copy_directory      
            "${SSP_DIR}/eta-ais/build-A7H4-adv/lib"
            "${CMAKE_BINARY_DIR}/build_${PLATFORM}/lib"
)
message(STATUS "Build configuration completed successfully!")
