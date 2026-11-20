message(STATUS "Flattening ROS2 install layout...")

#
# Create target directories
#
file(MAKE_DIRECTORY "${INSTALL_DIR}/lib/cpm_common_interfaces")
file(MAKE_DIRECTORY "${INSTALL_DIR}/lib/job_mgr_interfaces")
file(MAKE_DIRECTORY "${INSTALL_DIR}/lib/weigh_app_interfaces")

#
# Flatten include structure
#
if(EXISTS "${INSTALL_DIR}/include/cpm_common_interfaces/cpm_common_interfaces")
    file(COPY
        "${INSTALL_DIR}/include/cpm_common_interfaces/cpm_common_interfaces/msg"
        DESTINATION
        "${INSTALL_DIR}/include/cpm_common_interfaces"
    )
endif()

if(EXISTS "${INSTALL_DIR}/include/job_mgr_interfaces/job_mgr_interfaces")
    file(COPY
        "${INSTALL_DIR}/include/job_mgr_interfaces/job_mgr_interfaces/msg"
        DESTINATION
        "${INSTALL_DIR}/include/job_mgr_interfaces"
    )
endif()

if(EXISTS "${INSTALL_DIR}/include/weigh_app_interfaces/weigh_app_interfaces")
    file(COPY
        "${INSTALL_DIR}/include/weigh_app_interfaces/weigh_app_interfaces/msg"
        DESTINATION
        "${INSTALL_DIR}/include/weigh_app_interfaces"
    )
endif()

#
# Remove duplicate nested folders
#
file(REMOVE_RECURSE
    "${INSTALL_DIR}/include/cpm_common_interfaces/cpm_common_interfaces"
)

file(REMOVE_RECURSE
    "${INSTALL_DIR}/include/job_mgr_interfaces/job_mgr_interfaces"
)

file(REMOVE_RECURSE
    "${INSTALL_DIR}/include/weigh_app_interfaces/weigh_app_interfaces"
)

#
# Move CPM libs
#
file(GLOB CPM_COMMON_LIBS
    "${INSTALL_DIR}/lib/libcpm_common_interfaces*"
)

foreach(lib ${CPM_COMMON_LIBS})
    get_filename_component(name "${lib}" NAME)
    file(RENAME
         "${lib}"
         "${INSTALL_DIR}/lib/cpm_common_interfaces/${name}")
endforeach()

file(GLOB JOB_LIBS
    "${INSTALL_DIR}/lib/libjob_mgr_interfaces*"
)

foreach(lib ${JOB_LIBS})
    get_filename_component(name "${lib}" NAME)
    file(RENAME
         "${lib}"
         "${INSTALL_DIR}/lib/job_mgr_interfaces/${name}")
endforeach()

file(GLOB WEIGH_LIBS
    "${INSTALL_DIR}/lib/libweigh_app_interfaces*"
)

foreach(lib ${WEIGH_LIBS})
    get_filename_component(name "${lib}" NAME)
    file(RENAME
         "${lib}"
         "${INSTALL_DIR}/lib/weigh_app_interfaces/${name}")
endforeach()

message(STATUS "CPM layout conversion complete")