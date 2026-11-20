cmake_minimum_required(VERSION 3.20)
project(SSP_CPM_Loader_AIS)


# ROS2 message generation
if(BUILD_TARGET STREQUAL "ros2_model")
    message(STATUS "Building ros2_model")
    add_subdirectory(ros2_data_models/src)
# Build filesystem library first
elseif(BUILD_TARGET STREQUAL "nvm")
    message(STATUS "Building nvm")
    add_subdirectory(
        TES-common-ais/prod/common/filesystem/extensions
    )
elseif(BUILD_TARGET STREQUAL "tes_apps")
    message(STATUS "Building tes_apps")
    add_subdirectory(
        TES-common-ais/apps
    )    
# Build existing applications
elseif(BUILD_TARGET STREQUAL "apps")
    message(STATUS "Building apps")
    add_subdirectory(
        CPM-Loader-ais/apps
    )
else()
    message(FATAL_ERROR "Unknown BUILD_TARGET=${BUILD_TARGET}")
endif()


