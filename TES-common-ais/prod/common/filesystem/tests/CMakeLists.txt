#
# Hub
# CMakeLists.txt - The makefile for the filesystem test of Hub.
#
# Author:
#     Dan Tascione
#

#
# Record sources for the module.
#

set(SOURCE_FILES "filesystem_test.cc")

#
# Record headers for the module.
#

set(HEADER_FILES "")

#
# Install all of our tests into a separate folder. We don't want things cluttering
# up our bin folder.
#

hub_remap_unittest_targets()

#
# Define source groups to make the Visual Studio project look nicer.
#

source_group("Headers" FILES ${HEADER_FILES})
                   
#
# Create the shared library here.
#

add_executable(filesystem_test ${SOURCE_FILES} ${HEADER_FILES})

#
# Link against the parser library.
#

target_link_libraries(filesystem_test hub_base
                                      hub_filesystem
                                      hub_testing)

#
# For Visual Studio, put this entire object into the a nested folder.
#

set_property(TARGET filesystem_test PROPERTY FOLDER "tests")

#
# Let's add the tests to the project.
#

hub_register_unittest(filesystem_test)

