set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
#sysroot from CPM ets build file
set(CMAKE_SYSROOT
    "/home/u_via/repo/ros2_model/sdk/aarch64-linux-gnu/sysroot"
)
 
#compiler
set(CMAKE_C_COMPILER
    "/usr/bin/aarch64-linux-gnu-gcc"
)
 
set(CMAKE_CXX_COMPILER
    "/usr/bin/aarch64-linux-gnu-g++"
)
 

set(ARM_ROS2_SDK
    "/home/u_via/repo/ros2_model/sdk/ros2_jazzy_sdk"
)
 
set(CMAKE_FIND_ROOT_PATH
    "${CMAKE_SYSROOT}"
    "${ARM_ROS2_SDK}"
)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
 
# Libraries/includes/packages must come from target roots

set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)