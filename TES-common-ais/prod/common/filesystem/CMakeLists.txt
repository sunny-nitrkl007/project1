# Hub filesystem module - Modern CMake build

set(MODULE_NAME hub_filesystem)

# Source files
set(FILESYSTEM_SOURCES
    file.cc
    file_buffer.cc
    journaled_file.cc
    lock_file.cc
    path.cc
)

# Create library
add_library(${MODULE_NAME} ${FILESYSTEM_SOURCES})

# Link libraries
target_link_libraries(${MODULE_NAME}
    PUBLIC
        hub_base
        hub_utility
)

# Include directories
target_include_directories(${MODULE_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/generated>
        $<INSTALL_INTERFACE:include>
)

# Install library
install(TARGETS ${MODULE_NAME}
    EXPORT coretechTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install headers
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION include/coretech/hub/filesystem
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
    PATTERN "tests" EXCLUDE
)

# Unit tests
if(BUILD_TESTING)
    set(TEST_DIR tests)
    
    add_executable(hub_filesystem_unit_test ${TEST_DIR}/FileSystemUnitTest.cpp)
    target_link_libraries(hub_filesystem_unit_test
        hub_filesystem
        Boost::unit_test_framework
        Boost::filesystem
    )
    add_test(NAME hub_filesystem_unit_test COMMAND hub_filesystem_unit_test)
    install(TARGETS hub_filesystem_unit_test DESTINATION bin/tests)
    
    add_executable(hub_filesystem_lockfile_unit_test ${TEST_DIR}/LockFileUnitTest.cpp)
    target_link_libraries(hub_filesystem_lockfile_unit_test
        hub_filesystem
        Boost::unit_test_framework
        Boost::filesystem
    )
    add_test(NAME hub_filesystem_lockfile_unit_test COMMAND hub_filesystem_lockfile_unit_test)
    install(TARGETS hub_filesystem_lockfile_unit_test DESTINATION bin/tests)
endif()

# Add ais_filesystem library from extensions subdirectory
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/extensions/CMakeLists.txt)
    add_subdirectory(extensions)
endif()
