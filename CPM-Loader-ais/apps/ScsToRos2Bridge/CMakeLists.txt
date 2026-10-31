cmake_minimum_required(VERSION 3.16)

project(ScsToRos2Bridge LANGUAGES C CXX)

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
file(GLOB ROS2_PACKAGE_INCLUDES
    "${SSP_DIR}/ros2_sdk/include/*"
)

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
file(GLOB ROS2_ALL_LIBS
    "${SSP_DIR}/ros2_sdk/lib/*.so"
)

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

file(GLOB src_app_sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src_app/*.c"
)

file(GLOB src_nvm_sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src_nvm/*.c"
)

file(GLOB lps_weighing_sources CONFIGURE_DEPENDS
    "${SSP_DIR}/lps_weighing/src/*.c"
)

file(GLOB lps_cal_sources CONFIGURE_DEPENDS
    "${SSP_DIR}/lps_cal/src/*.c"
)

file(GLOB lps_cal_imu_sources CONFIGURE_DEPENDS
    "${SSP_DIR}/lps_cal/src/imu/*.c"
)

file(GLOB lps_cal_shared_sources CONFIGURE_DEPENDS
    "${SSP_DIR}/lps_cal/src/imu/_sharedutils/*.c"
)

file(GLOB toa_wl00_x86_sources CONFIGURE_DEPENDS
    "${SSP_DIR}/tipoff_assist/toa_wl00_x86_64-b/src/*"
)

file(GLOB toa_wl00_sources CONFIGURE_DEPENDS
    "${SSP_DIR}/tipoff_assist/toa_wl00/c_src/*"
)
file(GLOB variant_sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_APP_VARIANT}/*"
)

add_executable(ScsToRos2Bridge
    ${app_sources}
    ${lps_pass_tracker_sources}
    ${variant_sources}
    ${src_app_sources}
    ${src_nvm_sources}

   # ${lps_weighing_sources}

    # ${lps_cal_sources}
    # ${lps_cal_imu_sources}
    # ${lps_cal_shared_sources}

    # ${toa_wl00_x86_sources}
    # ${toa_wl00_sources}

    # "${SSP_DIR}/lps_common/src/LpsCommonLookUpTblUtility.c"
    # "${SSP_DIR}/lps_common/src/LpsCommonWeight.c"
    # "${SSP_DIR}/lps_common/src/cpm_filter.c"

    # "${SSP_DIR}/tipoff_assist/toa_wl00_inf/src/toa_wl00_model_if.c"

)

#
# AIS modules
#
file(GLOB CORETECH_AIS_MODULES
    LIST_DIRECTORIES TRUE
    "${AIS_CORETECH_CONTENT}/ais_*"
)
#misiing 208-216
#
# Includes
#
target_include_directories(ScsToRos2Bridge PRIVATE

    ${ROS2_PACKAGE_INCLUDES}
    ${ROS2_MODELS_INCLUDES}

    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/include"

    "${SSP_DIR}/CPM-Loader-ais"
    "${SSP_DIR}/CPM-Loader-ais/prod/common"
    "${SSP_DIR}/CPM-Loader-ais/prod/common/ros2wrapper"

    "${SSP_DIR}/lps_common/include"
    "${SSP_DIR}/lps_app_common/include"

    "${_lps_pass_tracker_dir}/include"

    "${SSP_DIR}/lps_weighing/include"
    "${SSP_DIR}/lps_weighing/src"

    "${SSP_DIR}/lps_cal/include"
    "${SSP_DIR}/lps_cal/src"
    "${SSP_DIR}/lps_cal/src/imu"
    "${SSP_DIR}/lps_cal/src/imu/_sharedutils"

    "${SSP_DIR}/tipoff_assist/toa_wl00_inf/include"
    "${SSP_DIR}/tipoff_assist/toa_wl00/c_src"
    "${SSP_DIR}/tipoff_assist/toa_wl00_x86_64-b/include"

    "${SSP_DIR}/libsl/include"
    "${SSP_DIR}/libsl/include_PostR2014a"

    "${SSP_DIR}/sss/include"

    "${TES_COMMON_DIR}/prod/common"
    "${TES_COMMON_DIR}/prod/common/chrono"

    "${SSP_DIR}/eta-ais/prod/common"

    "${SSP_DIR}/eta-ais/prod/coretech/include"
    "${SSP_DIR}/eta-ais/prod/coretech/hub/lib_module"

    "${SSP_DIR}/eta-ais/prod/machineCommon/content/include"
    "${SSP_DIR}/eta-ais/prod/machineCommon/content/prod/common/hub/lib_module"

    "${SSP_DIR}/eta-ais/prod/platformCommon/content/include"

    "${AIS_PC_SSP_CONTENT}/include/lib_a4/scl"
    "${AIS_PC_SSP_CONTENT}/include/lib_oel"
    "${AIS_PC_SSP_CONTENT}/include/lib_a4/hal"
    "${AIS_PC_SSP_CONTENT}/include/lib_scl_info"

    "${AIS_PC_CONTENT}/include"
    "${AIS_PC_CONTENT}/tgt_gcc_5.1.0_a6n2/lib_a4/hmpl/include"

    "${AIS_CORETECH_CONTENT}"
    "${AIS_CORETECH_CONTENT}/include"
    "${AIS_CORETECH_CONTENT}/generated"

    "${AIS_MC_CONTENT}/include"
    "${AIS_MC_CONTENT}/prod/common"
    "${AIS_MC_CONTENT}/prod/include"

    "${AIS_PLATFORM_COMMON_CONTENT}/include"

    ${CORETECH_AIS_MODULES}
)

#
# Link directories
#
target_link_directories(ScsToRos2Bridge PRIVATE

    "${SSP_DIR}/ros2_sdk/lib"
    "${SSP_DIR}/ros2_sdk/lib/aarch64-linux-gnu"

    "${SSP_DIR}/eta-ais/build-A7H4-adv/lib"
    "${SSP_DIR}/eta-ais/build-A7H4-adv/prod/machineCommon/content/prod/common/version"

    "${SSP_DIR}/ros2_models/lib/cpm_common_interfaces"
    "${SSP_DIR}/ros2_models/lib/job_mgr_interfaces"
    "${SSP_DIR}/ros2_models/lib/weigh_app_interfaces"

    "${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/usr/lib"

    "${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/usr/lib/aarch64-linux-gnu"

    "${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/opt/cat/ais/lib"

    "${SSP_DIR}/eta-ais/build-A7H4-adv/prod/platformCommon/content/ssp-linux-is7/tgt_gcc_arm64_guest/core_telematics/log"

    "${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/usr/lib"

    "${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/usr/lib/aarch64-linux-gnu"

    "${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/opt/cat/ais/lib"

    "${SSP_DIR}/eta-ais/build-A7H4-adv/prod/platformCommon/content/ssp-linux-is7/tgt_gcc_arm64_guest/lib_oel/oel"

    "${SSP_DIR}/eta-ais/build-A7H4-adv/prod/platformCommon/content/ssp-linux-is7/tgt_gcc_arm64_guest/lib_a4/hal"

    "${SSP_DIR}/eta-ais/build-A7H4-adv/prod/platformCommon/content/ssp-linux-is7/tgt_gcc_arm64_guest/lib_a4/scl"
)

target_link_libraries(ScsToRos2Bridge PRIVATE

    ais_task
    ais_config
    ais_log
    ais_channel
    ais_task_core
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

    AisPluginProcessor

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

    commTask

    "-Wl,--start-group"
    nvm
    hal_boot
    oel_u
    oel_rtos
    oel_rtos_posix
    oelTaskManager
    socketCanBase
    socketCanUtil
    "-Wl,--end-group"

    version

    ruby
    snappy
    lzma

    "-Wl,--start-group"
    ${ROS2_ALL_LIBS}
    "-Wl,--end-group"

    orocos-kdl
    urdfdom_model
    urdf_xml_parser

    Boost::filesystem
    Boost::serialization
    Boost::thread
    Boost::program_options
    Boost::system
    Boost::chrono
    Boost::date_time
    Boost::atomic

    ${CPM_COMMON_INTERFACE_LIBS}
    ${JOB_MGR_INTERFACE_LIBS}
    ${WEIGH_APP_INTERFACE_LIBS}

    ${CPM_LIBS}

    pthread
    dl
    rt
    numa

    yaml-cpp
    spdlog
    tinyxml2
    lz4
    dbg_log

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

target_link_options(ScsToRos2Bridge PRIVATE
    "-Wl,-rpath-link,${SSP_DIR}/ros2_sdk/lib"
    "-Wl,-rpath-link,${SSP_DIR}/ros2_sdk/lib/aarch64-linux-gnu"
    "-Wl,-rpath-link,${SSP_DIR}/eta-ais/build-A7H4-adv/lib"
    "-Wl,-rpath-link,${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/usr/lib/aarch64-linux-gnu"
    )

target_compile_definitions(ScsToRos2Bridge PRIVATE
    RAPIDJSON_HAS_STDSTRING=1
    AIS_SERIALIZATION_INCLUDE_BOOST_ARCHIVE
)

#
# Compiler flags
#
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang"
   AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

    target_compile_options(ScsToRos2Bridge PRIVATE
        -fpermissive
        -Wno-unused-function
        -Wno-deprecated-declarations
    )

endif()


set_target_properties(ScsToRos2Bridge PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
        #"${CMAKE_BINARY_DIR}/build_${PLATFORM}/bin"
        "${SSP_DIR}/eta-ais/build-A7H4-adv/bin"
)

add_custom_command(TARGET ScsToRos2Bridge POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E make_directory
            "${CMAKE_BINARY_DIR}/build_${PLATFORM}/lib"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SSP_DIR}/ros2_sdk/lib"
            "${CMAKE_BINARY_DIR}/build_${PLATFORM}/lib"
    
    COMMAND ${CMAKE_COMMAND} -E copy_directory      
            "${SSP_DIR}/eta-ais/build-A7H4-adv/lib"
            "${CMAKE_BINARY_DIR}/build_${PLATFORM}/lib"
)
message(STATUS "Build configuration completed successfully!")
