cmake_minimum_required(VERSION 3.16)

project(DemoApp LANGUAGES C CXX)

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

set(SL_CAL_INCLUDE_DIR "${SSP_DIR}/libsl/include" CACHE PATH "sl_cal headers")
set(SL_CAL_PLATFORM_INCLUDE_DIR "" CACHE PATH "Platform headers required by sl_cal sources")
set(DEMO_WEB_INSTALL_DIR "www" CACHE PATH "Web asset installation root")

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
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

file(GLOB WEIGH_APP_INTERFACE_LIBS
    "${SSP_DIR}/ros2_models/lib/weigh_app_interfaces/lib*.so"
)
list(FILTER WEIGH_APP_INTERFACE_LIBS
     EXCLUDE REGEX ".*generator_py.*")

file(GLOB DEMO_APP_INTERFACE_LIBS
    "${SSP_DIR}/ros2_models/lib/demo_app_interfaces/lib*.so"
)
list(FILTER DEMO_APP_INTERFACE_LIBS
     EXCLUDE REGEX ".*generator_py.*")

file(GLOB app_sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)
file(GLOB model_sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_executable(DemoApp
    ${app_sources}
    ${model_sources}
)

#
# Includes
#
target_include_directories(DemoApp PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    ${ROS2_MODELS_INCLUDES}
    "${SSP_DIR}/CPM-Loader-ais/prod/common/ros2wrapper"
    "${SSP_DIR}/CPM-Loader-ais/prod/common"
    "${SSP_DIR}/libsl/include_PostR2014a"
    "${SL_CAL_INCLUDE_DIR}"
    "${SSP_DIR}/lps_app_common/include"
)
if(SL_CAL_PLATFORM_INCLUDE_DIR)
    target_include_directories(DemoApp PRIVATE "${SL_CAL_PLATFORM_INCLUDE_DIR}")
endif()

#
# Link directories
#
target_link_directories(DemoApp PRIVATE

    "${SSP_DIR}/eta-ais/build-A7H4-adv/lib"
    "${SSP_DIR}/ros2_models/lib/cpm_common_interfaces"
    "${SSP_DIR}/ros2_models/lib/weigh_app_interfaces"
    "${SSP_DIR}/ros2_models/lib/demo_app_interfaces"
    "${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/usr/lib"
    "${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/usr/lib/aarch64-linux-gnu"
    "${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/opt/cat/ais/lib"
)

target_link_libraries(DemoApp PRIVATE
    ruby
    #
    # Generated ROS2 interfaces
    #
    ${CPM_COMMON_INTERFACE_LIBS}
    ${WEIGH_APP_INTERFACE_LIBS}
    ${DEMO_APP_INTERFACE_LIBS}
    #
    # CPM libs (if defined)
    #
    ${CPM_LIBS}

    #
    # Runtime
    #
    Threads::Threads
    m
    rclcpp::rclcpp
)

target_link_options(DemoApp PRIVATE
    "-Wl,-rpath-link,${SSP_DIR}/eta-ais/build-A7H4-adv/lib"
    "-Wl,-rpath-link,${SSP_DIR}/eta-ais/build-A7H4-adv/ext/sdk/ais-sdk-aarch64-a/amd64/host/usr/aarch64-linux-gnu/sysroot/usr/lib/aarch64-linux-gnu"
    )

#
# Compiler flags
#
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang"
   AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

    target_compile_options(DemoApp PRIVATE
        -fpermissive
        -Wno-unused-function
        -Wno-deprecated-declarations
    )

endif()

#
# sl_cal
#
if(TARGET sl_cal)
    target_link_libraries(DemoApp PRIVATE sl_cal)
else()
    file(GLOB sl_cal_sources CONFIGURE_DEPENDS "${SSP_DIR}/libsl/src/lib/sl_cal/*.c")
    if(sl_cal_sources AND NOT SL_CAL_LIBRARY)
        add_library(demo_sl_cal STATIC ${sl_cal_sources})
        target_include_directories(demo_sl_cal PRIVATE
            "${SL_CAL_INCLUDE_DIR}"
            "${SSP_DIR}/lps_app_common/include"
            "${SSP_DIR}/libsl/include_R2012B"
        )
        if(SL_CAL_PLATFORM_INCLUDE_DIR)
            target_include_directories(demo_sl_cal PRIVATE "${SL_CAL_PLATFORM_INCLUDE_DIR}")
        endif()
        target_link_libraries(DemoApp PRIVATE demo_sl_cal)
    else()
        find_library(SL_CAL_LIBRARY NAMES sl_cal HINTS "${SSP_DIR}/CPM-Loader-ais/lib")
        if(NOT SL_CAL_LIBRARY OR NOT EXISTS "${SL_CAL_LIBRARY}")
            message(FATAL_ERROR
                "Missing sl_cal: provide SL_CAL_LIBRARY pointing to a real target-compatible library, or restore ${SSP_DIR}/libsl/src/lib/sl_cal/*.c"
            )
        endif()
        target_link_libraries(DemoApp PRIVATE "${SL_CAL_LIBRARY}")
    endif()
endif()

set_target_properties(DemoApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
        "${SSP_DIR}/eta-ais/build-A7H4-adv/bin"
)

#
# Copy runtime libraries
#
add_custom_command(
    TARGET DemoApp POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E make_directory
            "${CMAKE_BINARY_DIR}/build_${PLATFORM}/lib"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SSP_DIR}/eta-ais/build-A7H4-adv/lib"
            "${CMAKE_BINARY_DIR}/build_${PLATFORM}/lib"
)

#
# Web assets
#
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/index.html" DESTINATION "${DEMO_WEB_INSTALL_DIR}/DemoApp")
foreach(asset_dir css images js)
    file(GLOB assets "${CMAKE_CURRENT_SOURCE_DIR}/${asset_dir}/*")
    install(FILES ${assets} DESTINATION "${DEMO_WEB_INSTALL_DIR}/DemoApp/${asset_dir}")
endforeach()

message(STATUS "Build configuration completed successfully!")
