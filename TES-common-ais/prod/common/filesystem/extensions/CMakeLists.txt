cmake_minimum_required(VERSION 3.16)

# Module: ais_filesystem (hub/filesystem/extensions)
# This is built as a separate library from hub_filesystem

set(MODULE_NAME ais_filesystem)

# Source files
set(SOURCES
    dir.cpp
    file.cpp
    filelist.cpp
    nvm.cpp
)

# Create shared library
add_library(${MODULE_NAME} SHARED ${SOURCES})

# Include directories
target_include_directories(${MODULE_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CORETECH_INCLUDE_DESTINATION}>
)

# Link dependencies
target_link_libraries(${MODULE_NAME}
    PUBLIC
        hub_filesystem
        hub_base
)

# Set properties
set_target_properties(${MODULE_NAME} PROPERTIES
    CXX_STANDARD 17
)

# Install library
install(TARGETS ${MODULE_NAME}
    EXPORT ${MODULE_NAME}Targets
    LIBRARY DESTINATION ${CORETECH_LIB_DESTINATION}
    ARCHIVE DESTINATION ${CORETECH_LIB_DESTINATION}
    RUNTIME DESTINATION ${CORETECH_BIN_DESTINATION}
)

# Install headers
install(FILES
    dir.h
    file.h
    filelist.h
    iflocker.hpp
    nvm.h
    nvmStorage.hpp
    nvmStorageExample.hpp
    oflocker.hpp
    sha1_fstream.hpp
    DESTINATION ${CORETECH_INCLUDE_DESTINATION}/hub/filesystem/extensions
)

# Unit tests
if(BUILD_TESTING)
    # Common test libraries
    set(FILESYSTEM_TEST_LIBS
        ${MODULE_NAME}
        ais_log
        Boost::unit_test_framework
        Boost::filesystem
        Boost::thread
        hub_logging
    )
    
    # FileListTest (note: capitalization matters)
    add_executable(ais_filesystem_filelistTest
        test/FileListTest.cpp
    )
    target_link_libraries(ais_filesystem_filelistTest
        PRIVATE
            ${FILESYSTEM_TEST_LIBS}
    )
    install(TARGETS ais_filesystem_filelistTest
        RUNTIME DESTINATION ${CORETECH_BIN_DESTINATION}/tests
    )
    
    # FileTest
    add_executable(ais_filesystem_fileTest
        test/FileTest.cpp
    )
    target_link_libraries(ais_filesystem_fileTest
        PRIVATE
            ${FILESYSTEM_TEST_LIBS}
    )
    install(TARGETS ais_filesystem_fileTest
        RUNTIME DESTINATION ${CORETECH_BIN_DESTINATION}/tests
    )
    
    # DirTest
    add_executable(ais_filesystem_dirTest
        test/DirTest.cpp
    )
    target_link_libraries(ais_filesystem_dirTest
        PRIVATE
            ${FILESYSTEM_TEST_LIBS}
    )
    install(TARGETS ais_filesystem_dirTest
        RUNTIME DESTINATION ${CORETECH_BIN_DESTINATION}/tests
    )
    
    # DirTest2
    add_executable(ais_filesystem_dirTest2
        test/DirTest2.cpp
    )
    target_link_libraries(ais_filesystem_dirTest2
        PRIVATE
            ${FILESYSTEM_TEST_LIBS}
    )
    install(TARGETS ais_filesystem_dirTest2
        RUNTIME DESTINATION ${CORETECH_BIN_DESTINATION}/tests
    )
endif()
