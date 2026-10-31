cmake_minimum_required(VERSION 3.20)

project(AIS_Project)




##############################################################################
# Environment / Directory Configuration
##############################################################################

set(TLD "${CMAKE_CURRENT_SOURCE_DIR}/..")

set(AIS_TLD "")
set(AIS_BUILD_TOOLS           "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/ais_build_tools/content")
message(WARNING "---- DIR --- ${AIS_BUILD_TOOLS}")
set(AIS_POSELIB_CONTENT       "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/positioningLib/content")
set(AIS_PLANNINGLIB_CONTENT   "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/planningLib/content")
set(AIS_DETECT_CONTENT        "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/detectCommon/content")
set(AIS_CT_CONTENT            "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/coretech")
set(AIS_CORETECH_CONTENT      "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/coretech")
set(AIS_MC_CONTENT            "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/machineCommon/content")
set(AIS_MACHINE_COMMON_CONTENT "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/machineCommon/content")
set(AIS_PC_CONTENT            "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/platformCommon/content")
set(AIS_PLATFORM_COMMON_CONTENT "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/platformCommon/content")
set(AIS_PLATFORM_COMMON_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/platformCommon/content")
set(AIS_OLM_CONTENT           "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/overlayManager/content")
set(AHS_DEPS_CONTENT          "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/ahs_dependencies/content")
set(AIS_AC_CONTENT            "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/astopCommon/content")
set(_1A_IC_CONTENT            "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/1A/1AInterfacesCommon")
set(_1A_SDD_CONTENT           "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/1A/1ASensorDriversDev")

set(CONFIG_SOURCE_DIR "${TLD}/config")

##############################################################################
# Platform Selection
##############################################################################

message(WARNING "PLATFORM=${PLATFORM}")
message(WARNING "ENV_PLATFORM=$ENV{PLATFORM}")

set(PLATFORM "$ENV{PLATFORM}")


#############################################################################
#Deploy setup
#############################################################################

set(DEPLOY_DIR
    "${CMAKE_BINARY_DIR}/build_${PLATFORM}"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    "${DEPLOY_DIR}/bin"
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    "${DEPLOY_DIR}/lib"
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    "${DEPLOY_DIR}/lib"
)
#############################################################################

if(PLATFORM STREQUAL "A7H4" OR PLATFORM STREQUAL "JTX2")

    set(AIS_PC_SSP_CONTENT
        "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/platformCommon/content/ssp-linux-is7")

    set(AIS_PC_TARGET_CONTENT
        "${AIS_PC_SSP_CONTENT}/tgt_gcc_arm64_guest")

    message(INFO " setting ---A7H4--- platform")    

else()

    set(AIS_PC_SSP_CONTENT
        "${CMAKE_CURRENT_SOURCE_DIR}/../../eta-ais/prod/platformCommon/content/ssp-linux-is6")

    set(AIS_PC_TARGET_CONTENT
        "${AIS_PC_SSP_CONTENT}/tgt_gcc_5.1.0_a6n2")

    message(INFO " setting ---A6--- platform")      

endif()

##############################################################################
# Additional Directories
##############################################################################

set(APP_PLATFORM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../platform")
set(TES_COMMON_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/../../TES-common-ais")
set(SSP_DIR          "${CMAKE_CURRENT_SOURCE_DIR}/../..")

message(STATUS "APP_PLATFORM_DIR      = ${APP_PLATFORM_DIR}")
message(STATUS "TES_COMMON_DIR        = ${TES_COMMON_DIR}")
message(STATUS "SSP_DIR               = ${SSP_DIR}")
message(STATUS "AIS_PC_SSP_CONTENT    = ${AIS_PC_SSP_CONTENT}")
message(STATUS "AIS_PC_TARGET_CONTENT = ${AIS_PC_TARGET_CONTENT}")

##############################################################################
# Global Compile Definitions
##############################################################################

if(PLATFORM STREQUAL "A7H4")
    add_compile_definitions(NO_PROTOBUF_SUPPORT)
endif()

##############################################################################
# Build Variables
##############################################################################

set(TARGET_APP_VARIANT "${ECM_VARIANT}")

##############################################################################
# Build Components
##############################################################################
# Equivalent of buildit(component, baseEnv["OS"])
# Add each component directory here.
##############################################################################

add_subdirectory(LpsSaWeighApp)
add_subdirectory(LpsSaJobMgrApp)
add_subdirectory(ScsToRos2Bridge)


###################################################
#Deploy
###################################################
file(GLOB ROS2_RUNTIME_LIBS
    "${SSP_DIR}/ros2_sdk/lib/*.so*"
)

add_custom_target(copy_runtime_libs ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory
            "${DEPLOY_DIR}/lib"

    COMMAND ${CMAKE_COMMAND} -E copy
            ${ROS2_RUNTIME_LIBS}
            "${DEPLOY_DIR}/lib"
)

add_dependencies(copy_runtime_libs
   LpsSaJobMgrApp
   LpsSaWeighApp
   ScsToRos2Bridge
)
#################################################

