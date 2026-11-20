cmake_minimum_required(VERSION 3.22)

project(nvm_filesystem)

set(COMMON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../")
message(STATUS "COMMON_DIR=${COMMON_DIR}")

add_library(nvm_filesystem SHARED
    nvm_directory.cpp
    file.cpp
    filelist.cpp
    nvm.cpp
)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
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

target_include_directories(nvm_filesystem
    PRIVATE
        "${COMMON_DIR}/CPM-Loader-ais/prod/common/ros2wrapper"
        "${COMMON_DIR}/ros2_models/include"
        "${COMMON_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${COMMON_DIR}"
        "${COMMON_DIR}/TES-common-ais/prod/common"
        "${COMMON_DIR}/eta-ais/prod/coretech"
        "${COMMON_DIR}/eta-ais/prod/coretech/generated"
        "${COMMON_DIR}/eta-ais/build-A7H4-adv/include"
        
)


target_link_libraries(nvm_filesystem PRIVATE
    Boost::filesystem
    Boost::serialization
    Boost::thread
    Boost::program_options
    Boost::system
    Boost::chrono
    Boost::date_time
    Boost::atomic
    rclcpp::rclcpp
)

set_target_properties(nvm_filesystem PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${COMMON_DIR}/eta-ais/build-A7H4-adv/lib"
)
