///////////////////////////////////////////////////////////////////////////////
/// @file      FileSystemUnitTest.cpp
/// @author    Adrian Cojocari (adrian.cojocari@cat.com)
/// @date      Dec 21, 2022
/// @brief     A unit test for filesystem module.
///
/// @attention Copyright (C) Caterpillar Inc. All Rights Reserved.
///////////////////////////////////////////////////////////////////////////////

// unit testing
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Unit tests for filesystem"

#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
using boost::unit_test::test_suite;
using boost::unit_test::test_case;

#include <unitTest/TimeSyncUtils.hpp>

#include <hub/base/platform/system_metrics.hh>
#include <hub/base/byte_buffer.hh>

#include <filesystem/journaled_file.hh>
#include <filesystem/file_buffer.hh>
#include <filesystem/lock_file.hh>
#include <filesystem/path.hh>
#include <sys/mman.h>
#include <pwd.h>
#include <unistd.h>

BOOST_AUTO_TEST_SUITE(filesystemTestSuit)

std::string execCmd(const char* cmd, bool remove_new_line = false) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    // Remove unwanted \n
    if(remove_new_line)
    {
        result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
    }
    return result;
}

BOOST_AUTO_TEST_CASE(file_path_management)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_001] - Test to verify that paths are working properly. [end] covers: [SRS_HUB_0101, SRS_HUB_0119, SRS_HUB_0102, SRS_HUB_0201, SRS_HUB_0210, SRS_HUB_0211, SRS_HUB_0212, SRS_HUB_0213, SRS_HUB_0214, SRS_HUB_0218, SRS_HUB_0222, SRS_HUB_0223, SRS_HUB_0226]
    ///
    /// TEST STEPS
    /// Construct a path from a directory and file.
    /// Check that we can break the path up.
    /// Try to append a path.
    /// Check if the entire path is a name.
    /// Create a file from two paths
    /// Change file permisssions
    /// Remove created files
    ///
    /// EXPECTED RESULT: file and path should behave as expected
    hub::filesystem::path test_path("sample//directory\\", "/my_name.txt");

    BOOST_CHECK_EQUAL(test_path.str(), "sample/directory/my_name.txt");

    BOOST_CHECK_EQUAL(test_path.get_parent_path().str(), "sample/directory");
    BOOST_CHECK_EQUAL(test_path.get_name().str(), "my_name.txt");
    BOOST_CHECK_EQUAL(test_path.get_name_without_extension(), "my_name");
    BOOST_CHECK_EQUAL(test_path.get_extension(), "txt");

    test_path = test_path / "second";

    BOOST_CHECK_EQUAL(test_path.get_parent_path().str(), "sample/directory/my_name.txt");
    BOOST_CHECK_EQUAL(test_path.get_extension(), "");
    BOOST_CHECK_EQUAL(test_path.get_name_without_extension(), "second");
    BOOST_CHECK_EQUAL(test_path.get_name().str(), "second");

    test_path = hub::filesystem::path("my_name.txt");

    BOOST_CHECK_EQUAL(test_path.get_name().str(), "my_name.txt");
    BOOST_CHECK_EQUAL(test_path.get_extension(), "txt");
    BOOST_CHECK_EQUAL(test_path.get_name_without_extension(), "my_name");
    BOOST_CHECK_EQUAL(test_path.get_parent_path().str(), "");

    hub::filesystem::path testDir("/tmp/test");
    hub::filesystem::path testDirChild("test.file");
    BOOST_CHECK_EQUAL(testDir.change_permissions("777"), false);
    testDir.make_directories();
    BOOST_CHECK_EQUAL(testDir.change_permissions("777"), true);
    BOOST_CHECK_EQUAL(testDir.change_permissions("invalid"), false);
    hub::filesystem::file file(testDir, testDirChild);

    file.open(hub::base::access_read, hub::base::open_disposition::disposition_create_always);
    file.close();

    BOOST_CHECK_EQUAL(testDir.empty(), false);
    hub::filesystem::path testDir2("/tmp/test2");
    testDir.move(testDir2);
    
    hub::filesystem::directory_entry_list list = testDir2.enumerate_children();
    BOOST_CHECK_EQUAL(list[0].name, "test.file");
    
    testDir.remove_recursively();
    testDir2.remove_recursively();

}

BOOST_AUTO_TEST_CASE(path_normalization)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_002] - Tests out path normalization. [end] covers: [SRS_HUB_0201, SRS_HUB_0224, SRS_HUB_0227, SRS_HUB_0228]
    ///
    /// TEST STEPS
    /// Veryfiy a very invalid path.
    /// Verify a valid path.
    /// Verify a just somewhat valid path.
    ///
    /// EXPECTED RESULT: Paths should be correctly generated even if given params are invalid.
    hub::filesystem::path test_path("//test\\\\abc/ /\\whatever.txt/");

    BOOST_CHECK_EQUAL(test_path.str(), "/test/abc/ /whatever.txt");

    test_path = hub::filesystem::path("test/abc");

    BOOST_CHECK_EQUAL(test_path.str(), "test/abc");

    test_path = hub::filesystem::path("test//abc");

    BOOST_CHECK_EQUAL(test_path.str(), "test/abc");

    hub::filesystem::path testDir("/tmp/test");
    hub::filesystem::path testDirChild("test");
    hub::filesystem::path test_path1(testDir, testDirChild);
    BOOST_CHECK_EQUAL(test_path1.str(), "/tmp/test/test");

    test_path1.remove_recursively();
}

BOOST_AUTO_TEST_CASE(windows_cifs_paths)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_003] - Tests out Windows CIFS path handling.[end] covers: [SRS_HUB_0201, SRS_HUB_0224]
    ///
    /// TEST STEPS
    /// Veryfiy a normal path.
    /// Verify a share path.
    /// Verify a server name path.
    /// Verify a trailing slash path.
    ///
    /// EXPECTED RESULT: Paths should be correctly generated even if given params are invalid.

    hub::filesystem::path test_path("\\\\some_server\\some_windows_path\\folder");

    BOOST_CHECK_EQUAL(test_path.str(), "\\\\some_server\\some_windows_path/folder");

    test_path = hub::filesystem::path("\\\\some_server\\some_windows_path");

    BOOST_CHECK_EQUAL(test_path.str(), "\\\\some_server\\some_windows_path");

    test_path = hub::filesystem::path("\\\\some_server");

    BOOST_CHECK_EQUAL(test_path.str(), "\\\\some_server");

    test_path = hub::filesystem::path("\\\\some_server\\some_windows_path//");

    BOOST_CHECK_EQUAL(test_path.str(), "\\\\some_server\\some_windows_path");
}

BOOST_AUTO_TEST_CASE(root_path)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_004] - Tests that we can set the root path.[end] covers: [SRS_HUB_0201, SRS_HUB_0205]
    ///
    /// TEST STEPS
    /// Veryfiy a normal path with / set as path
    ///
    /// EXPECTED RESULT: Path should be correctly created.
    hub::filesystem::path root("/");
    
    BOOST_CHECK(root.is_directory());

    BOOST_CHECK_EQUAL(root.str(), "/");

}

BOOST_AUTO_TEST_CASE(absolute_path_checking)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_005] - Tests that our understanding of what an absolute path is, is correct.[end] covers: [SRS_HUB_0207; ]
    ///
    /// TEST STEPS
    /// Create an absolute path with an invalid argument
    /// Create an absolute path
    /// Create an absolute path with CIFS names
    ///
    /// EXPECTED RESULT: Absolute paths should be correctly generated only when given params are valid.

    hub::filesystem::path test_path("not_an_absolute_path");

    BOOST_CHECK_EQUAL(test_path.is_absolute_path(), false);

    test_path = hub::filesystem::path("/an_absolute_path");

    BOOST_CHECK_EQUAL(test_path.is_absolute_path(), true);

    test_path = hub::filesystem::path("\\\\some_server\\some_windows_path");

    BOOST_CHECK_EQUAL(test_path.is_absolute_path(), true);
}

BOOST_AUTO_TEST_CASE(relative_path_checking)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_006] - Tests out the ability to retrieve paths relative to other paths.[end] covers: [SRS_HUB_0209, SRS_HUB_0229]
    ///
    /// TEST STEPS
    /// -# Create two paths with same dir.
    /// -# Verify getting relative path from different levels and trees
    ///
    /// EXPECTED RESULT: Relative paths should be returned as expected for each case.

    hub::filesystem::path main_path("abc/dir1");

    hub::filesystem::path relative_path;

    hub::filesystem::path same_path("abc/dir1");

    relative_path = same_path.get_relative_path_from_path(main_path);

    BOOST_CHECK_EQUAL(relative_path.str(), "");

    bool exception = false;
    try
    {
        hub::filesystem::path relative_path1("../test");
        relative_path = same_path.get_relative_path_from_path(relative_path1);
    }
    catch(const std::exception& e)
    {
        BOOST_CHECK_EQUAL(e.what(), "You cannot currently find paths relative to other relative paths. Consider resolving the paths with get_absolute_path() or resolve_path() before calling this API. The paths were \"abc/dir1\" and \"../test\".");
        exception = true;
    }
    BOOST_CHECK(exception);

    hub::filesystem::path in_folder("abc/dir1/file1");

    relative_path = in_folder.get_relative_path_from_path(main_path);

    BOOST_CHECK_EQUAL(relative_path.str(), "file1");
    BOOST_CHECK_EQUAL(relative_path.c_str(), "file1");

    // Next, check moving down a level.
    hub::filesystem::path down_level("abc");

    relative_path = down_level.get_relative_path_from_path(main_path);

    BOOST_CHECK_EQUAL(relative_path.str(), "..");

    // Now back up to a different level.
    hub::filesystem::path new_directory("abc/dir2");

    relative_path = new_directory.get_relative_path_from_path(main_path);

    BOOST_CHECK_EQUAL(relative_path.str(), "../dir2");

    // Try a multi-level ascension.
    hub::filesystem::path multi_level("abc/dir2/second");

    relative_path = multi_level.get_relative_path_from_path(main_path);

    BOOST_CHECK_EQUAL(relative_path.str(), "../dir2/second");

    // And now, a totally different tree.
    hub::filesystem::path different_tree("def/dir1");

    relative_path = different_tree.get_relative_path_from_path(main_path);

    BOOST_CHECK_EQUAL(relative_path.str(), "../../def/dir1");

    // Test out leading slashes.
    main_path = hub::filesystem::path("/abc/dir1");

    hub::filesystem::path leading_slash("/abc/dir2");

    relative_path = leading_slash.get_relative_path_from_path(main_path);

    BOOST_CHECK_EQUAL(relative_path.str(), "../dir2");

    // Test out totally different leading slashes.
    main_path = hub::filesystem::path("/abc/dir1");

    hub::filesystem::path different_leading_slash("/def/dir2");

    relative_path = different_leading_slash.get_relative_path_from_path(main_path);

    BOOST_CHECK_EQUAL(relative_path.str(), "../../def/dir2");

    // Test out relative paths with leading slashes.
    main_path = hub::filesystem::path("/abc/dir1");

    hub::filesystem::path backwards_leading_slash("/abc/dir1/test.file");

    relative_path = backwards_leading_slash.get_relative_path_from_path(main_path);

    BOOST_CHECK_EQUAL(relative_path.str(), "test.file");

    // Try to go the opposite direction.
    main_path = hub::filesystem::path("first/second/third");

    relative_path = main_path.get_relative_path_from_path("first");

    BOOST_CHECK_EQUAL(relative_path, "second/third");

    // Try to go the opposite direction, again, with absolute paths this time.
    main_path = hub::filesystem::path("/first/second/third");

    relative_path = main_path.get_relative_path_from_path("/first");

    BOOST_CHECK_EQUAL(relative_path, "second/third");
}

BOOST_AUTO_TEST_CASE(file_existance)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_007] - Test to verify file removal and exists works properly. [end] covers: [SRS_HUB_0101, SRS_HUB_0117, SRS_HUB_0118, SRS_HUB_0203, SRS_HUB_0219, SRS_HUB_0231]
    ///
    /// TEST STEPS
    /// -# Create a file and check if it exists.
    /// -# Remove the file
    ///
    /// EXPECTED RESULT: file should be successfully removed

    hub::filesystem::file test_path("fake_path.txt");

    test_path.touch();

    BOOST_CHECK_EQUAL(test_path.exists(), true);

    hub::filesystem::file test_path_copy;

    test_path_copy = test_path;

    BOOST_CHECK_EQUAL((test_path_copy == test_path), true);

    test_path.remove();

    BOOST_CHECK_EQUAL(test_path.exists(), false);

    test_path_copy.remove_if_exists();

    BOOST_CHECK_EQUAL(test_path.exists(), false);
}

BOOST_AUTO_TEST_CASE(file_resizing)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_008] - Test to verify some basic file resizing.[end] covers: [SRS_HUB_0111, SRS_HUB_0202, SRS_HUB_0203, SRS_HUB_0231]
    ///
    /// TEST STEPS
    /// -# Open a file
    /// -# Set file size
    /// -# Remove the file
    ///
    /// EXPECTED RESULT: file should be successfully created resized and removed

    hub::filesystem::file test_path("filesystem_test.bin");

    test_path.open(hub::base::access_write);

    // Make sure we can resize the file high.
    test_path.set_file_size(8192);

    BOOST_CHECK_EQUAL(test_path.get_size(), 8192ULL);

    // And make sure we can resize it low.
    test_path.set_file_size(4096);

    BOOST_CHECK_EQUAL(test_path.get_size(), 4096ULL);

    // Delete the file now.
    test_path.close();

    test_path.remove_if_exists();
    BOOST_CHECK(!test_path.exists());
}

BOOST_AUTO_TEST_CASE(file_io)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_009] - Test to verify some basic file I/O.[end] covers: [SRS_HUB_0101, SRS_HUB_0103, SRS_HUB_0104, SRS_HUB_0106, SRS_HUB_0105, SRS_HUB_0109, SRS_HUB_0110, SRS_HUB_0112, SRS_HUB_0219]
    ///
    /// TEST STEPS
    /// -# Open a file in write mode, try to open it twice to retrieve a exception second time.
    /// -# Write out a value to file.
    /// -# Remove the file.
    /// -# Clone the file.
    /// -# Close a file, try to close it twice to retrieve a exception second time.
    /// -# Try to seek, truncate and flush a closed file, exception should be throwed.
    ///
    /// EXPECTED RESULT: File should be successfully opened, written, cloned, closed and deleted. Expected exceptions should be thrown.

    hub::filesystem::file writer("filesystem_test.bin");

    writer.open(hub::base::access_write);
    bool exception = false;
    try
    {
        writer.open(hub::base::access_write);
    }
    catch(const std::exception& e)
    {
        BOOST_CHECK_EQUAL(e.what(), "Tried to reopen an already open file, \"filesystem_test.bin\".");
        exception = true;
    }
    BOOST_CHECK(exception);

    double test_value = 6.1234567;

    size_t bytes_written;

    writer.write(&test_value, sizeof(test_value), bytes_written);

    BOOST_CHECK_EQUAL(bytes_written, sizeof(test_value));

    hub::filesystem::file reader = writer;

    BOOST_CHECK((reader == writer));

    reader.close();
    
    exception = false;
    try
    {
        reader.close();
    }
    catch(const std::exception& e)
    {
        BOOST_CHECK_EQUAL(e.what(), "Tried to close an already closed file, \"filesystem_test.bin\".");
        exception = true;
    }
    BOOST_CHECK(exception);

    reader.open();

    double read_value;

    size_t bytes_read;

    reader.read(&read_value, sizeof(read_value), bytes_read);

    BOOST_CHECK_EQUAL(bytes_read, sizeof(read_value));
    BOOST_CHECK_CLOSE(read_value, test_value, 0.00001);

    reader.close();

    reader.read(&read_value, sizeof(read_value), bytes_read);

    BOOST_CHECK_EQUAL(bytes_read, sizeof(read_value));
    BOOST_CHECK_CLOSE(read_value, test_value, 0.00001);

    writer.close();

    writer.open_for_appending();

    BOOST_CHECK_EQUAL(writer.get_position(), writer.get_size());

    writer.close();

    exception = false;
    try
    {
        writer.seek(hub::base::seek_direction::seek_start, 2);
    }
    catch(const std::exception& e)
    {
        BOOST_CHECK_EQUAL(e.what(), "Tried to seek a closed file, \"filesystem_test.bin\".");
        exception = true;
    }
    BOOST_CHECK(exception);

    exception = false;
    try
    {
        writer.set_file_size(2048);
    }
    catch(const std::exception& e)
    {
        BOOST_CHECK_EQUAL(e.what(), "Tried to truncate a closed file, \"filesystem_test.bin\".");
        exception = true;
    }
    BOOST_CHECK(exception);

    exception = false;
    try
    {
        writer.flush();
    }
    catch(const std::exception& e)
    {
        BOOST_CHECK_EQUAL(e.what(), "Tried to flush a closed file, \"filesystem_test.bin\".");
        exception = true;
    }
    BOOST_CHECK(exception);
    
    reader.close();
    writer.remove();

    hub::filesystem::path multiple_path("test_file:test_file1");
    hub::filesystem::path_list pathList = hub::filesystem::split_path_list(multiple_path.str());

    BOOST_CHECK_EQUAL(pathList[0].str(), "test_file");
    BOOST_CHECK_EQUAL(pathList[1].str(), "test_file1");
}

BOOST_AUTO_TEST_CASE(writing_strings_entirely)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_010] - Tests reading and writing a file in its entirety.[end] covers: [SRS_HUB_0101, SRS_HUB_0104, SRS_HUB_0107, SRS_HUB_0108, SRS_HUB_0115, SRS_HUB_0116, SRS_HUB_0219]
    ///
    /// TEST STEPS
    /// -# Fill in a string with content and write it out to a file.
    /// -# Read in the string from file.
    /// -# Make sure the strings match.
    /// -# Map the file into memory.
    /// -# Check with mincore that memory is mapped
    /// -# Read data from memory.
    /// -# Unmap from memory.
    /// -# Check with mincore that memory is unmapped
    /// -# Remove the files.
    ///
    /// EXPECTED RESULT: File should be successfully opened, written, mapped,unmaped and deleted.
  
    std::string original = "Hello, world! This is a test!";

    hub::filesystem::file file("test.file");

    file.write_entirely(original);

    file.close();

    std::string ondisk;

    file.read_entirely(ondisk);
    file.close();

    BOOST_CHECK_EQUAL(original, ondisk);

    //
    // Clean up.
    //
    file.open();

    auto address = static_cast<char*>(file.map_into_memory(0, 5));
    BOOST_CHECK_EQUAL(address[0], 'H');
    BOOST_CHECK_EQUAL(address[1], 'e');
    BOOST_CHECK_EQUAL(address[2], 'l');
    BOOST_CHECK_EQUAL(address[3], 'l');
    BOOST_CHECK_EQUAL(address[4], 'o');

    
    uint32_t pagesize = sysconf(_SC_PAGESIZE);
    uint32_t vec_size = (2 * pagesize - 1) / pagesize;
    u_char vec[vec_size];


    // mincore - determine whether pages are resident in memory - https://man7.org/linux/man-pages/man2/mincore.2.html
    int result = mincore(address, pagesize, vec);
    
    BOOST_CHECK_EQUAL(result, 0);

    file.unmap_from_memory(address, 5);

    result = mincore(address, pagesize, vec);

    BOOST_CHECK_EQUAL(result, -1);

    // ENOMEM : addr to addr + length contained unmapped memory.
    BOOST_CHECK_EQUAL(errno , ENOMEM);


    file.close();
    file.remove();
}

BOOST_AUTO_TEST_CASE(reading_entirely_with_default)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_011] - Tests verifies that we can read a non-existing and existing file, with a known default[end] covers: [SRS_HUB_0101, SRS_HUB_0123, SRS_HUB_0104, SRS_HUB_0107, SRS_HUB_0108, SRS_HUB_0122, SRS_HUB_0125, SRS_HUB_0219]
    ///
    /// TEST STEPS
    /// -# Write content to a file.
    /// -# Verify we can read it.
    /// -# Remove the file.
    /// -# ReRead the file again.
    ///
    /// EXPECTED RESULT: Read function should return data if value present or default value otherwise.
  
    std::string original = "Hello, world! This is a test!";

    hub::filesystem::file file("test.file");

    file.write_entirely(original);
    file.close();

    std::string ondisk = file.read_entirely_or_use_default<std::string>("No value present.");

    BOOST_CHECK_EQUAL(ondisk, original);

    file.close();
    file.remove();

    ondisk = file.read_entirely_or_use_default<std::string>("No value present.");
    BOOST_CHECK_EQUAL(ondisk, "No value present.");

    hub::filesystem::file file2("/tmp/test1.file");

    char test[] = "255";

    file2.write_entirely(&test, sizeof(test));

    file2.flush();

    file2.close();

    uint64_t data = file2.read_entirely<uint64_t>();

    BOOST_CHECK_EQUAL(data, 255);

    file2.remove();

    BOOST_CHECK(!file2.exists());
}

BOOST_AUTO_TEST_CASE(writing_buffers_entirely)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_012] - Tests writing out larger buffer. [end] covers: [SRS_HUB_0202, SRS_HUB_0124, SRS_HUB_0112, SRS_HUB_0121, SRS_HUB_0219]
    ///
    /// TEST STEPS
    /// -# Fill in a buffer with sequential numbers.
    /// -# Write buffer out to a file.
    /// -# Flush the file out.
    /// -# Close the file.
    /// -# Make sure buffers match
    ///
    /// EXPECTED RESULT: Written buffer should match with read one.
  
    hub::base::byte_buffer original;

    for(uint32_t index = 0; index < 8192; ++index)
        original.write(&index, sizeof(index));

    original.seek(hub::base::seek_start, 0);

    hub::filesystem::file file("test.file");

    file.write_entirely(original);

    //
    // Before we close, flush the file out. NFS requires this, or else
    // on some systems, reading back the contents will be different then
    // what we just wrote.
    //
    // Yes, this somewhat defeats the spirit of the test, which was to make
    // sure you could write/read successfully.
    //

    file.flush();

    file.close();

    hub::base::byte_buffer ondisk;

    file.read_entirely(ondisk);
    file.close();

    BOOST_CHECK_EQUAL(file.get_size(), original.get_size());

    BOOST_CHECK_EQUAL(file.get_size(), ondisk.get_size());

    BOOST_CHECK_EQUAL(original.get_size(), ondisk.get_size());

    BOOST_CHECK_EQUAL((original == ondisk), true);

    file.remove();

    BOOST_CHECK(!file.exists());
}

BOOST_AUTO_TEST_CASE(recursive_removal)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_013] - Tests recursive removal of files and directories.[end] covers: [SRS_HUB_0203, SRS_HUB_0220, SRS_HUB_0221]
    ///
    /// TEST STEPS
    /// -# Create a new directory.
    /// -# Create a file in that directory.
    /// -# Make sure everything exists.
    /// -# Remove the entire path, recursively.
    ///
    /// EXPECTED RESULT: Directory and files  createtion and removal should be should be successfull.

    hub::filesystem::file directory("some_path");
    hub::filesystem::file sub_directory("some_path/sub_folder");

    hub::filesystem::file first_file("some_path/test.txt");
    hub::filesystem::file second_file("some_path/sub_folder/test2.txt");

    sub_directory.make_directories();

    // try to make an existing directory to be sure that there is no error thrown
    sub_directory.make_directories();

    first_file.touch();
    second_file.touch();

    BOOST_CHECK_EQUAL(directory.exists(), true);
    BOOST_CHECK_EQUAL(sub_directory.exists(), true);
    BOOST_CHECK_EQUAL(first_file.exists(), true);
    BOOST_CHECK_EQUAL(second_file.exists(), true);

    directory.remove_recursively();

    BOOST_CHECK_EQUAL(directory.exists(), false);
    BOOST_CHECK_EQUAL(sub_directory.exists(), false);
    BOOST_CHECK_EQUAL(first_file.exists(), false);
    BOOST_CHECK_EQUAL(second_file.exists(), false);
}

BOOST_AUTO_TEST_CASE(make_directories)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_014] - Test to check making directories.[end] covers: [SRS_HUB_0203, SRS_HUB_0221, SRS_HUB_0120]
    ///
    /// TEST STEPS
    /// -# Create a new directory.
    /// -# Create a file in that directory.
    /// -# Make sure everything exists.
    /// -# Remove the entire path, recursively.
    ///
    /// EXPECTED RESULT: Directory should be succefully created even with invalid paramerters given.

    hub::filesystem::file broken_path("test//\\directories/sub/");

    BOOST_CHECK_EQUAL(broken_path.str(), "test/directories/sub");


    broken_path.make_directories();

    BOOST_CHECK_EQUAL(broken_path.exists(), true);


    hub::filesystem::file filename("test/directories\\sub2/whatever.txt");

    BOOST_CHECK_EQUAL(filename.str(), "test/directories/sub2/whatever.txt");

    filename.make_parent_directories();
    filename.touch();

    BOOST_CHECK_EQUAL(filename.exists(), true);

    hub::filesystem::file parent("test");

    hub::filesystem::file test_parent_copy(parent);

    BOOST_CHECK_EQUAL(parent.str(), test_parent_copy.str());

    parent.remove_recursively();
    test_parent_copy.remove_recursively();
}

BOOST_AUTO_TEST_CASE(absolute_paths)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_015] - Tests out retrieving absolute paths.[end] covers: [SRS_HUB_0206, SRS_HUB_0208, SRS_HUB_0215, SRS_HUB_0225, SRS_HUB_0230]
    ///
    /// TEST STEPS
    /// -# Create a new path.
    /// -# Get the absolute path to it.
    ///
    /// EXPECTED RESULT: Absolute path should behave as expected

    hub::filesystem::path local("test_file");

    local.touch();

    BOOST_CHECK(local.is_regular_file());

    hub::filesystem::path absolute = local.get_absolute_path();

    BOOST_CHECK(absolute.is_regular_file());

    hub::filesystem::path absolute_if_exists = local.get_absolute_path_if_exists();

    BOOST_CHECK_EQUAL(local.get_name().str(), absolute.get_name().str());

    // Make sure they are not the same, I guess.
    BOOST_CHECK_EQUAL(absolute_if_exists.str(), absolute.str());
    BOOST_CHECK((local != absolute));
    BOOST_CHECK(local.str().size() > 0u);
    BOOST_CHECK(absolute.str().size() > local.str().size());
    BOOST_CHECK(absolute < local);
    BOOST_CHECK(local > absolute);

    std::stringstream os;
    os << absolute;

    BOOST_CHECK_EQUAL(os.str(), absolute.str());

    local.remove();
}

BOOST_AUTO_TEST_CASE(file_resolution_test)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_016] - Tests resolving various paths locally, without using the underlying operating system[end] covers: [SRS_HUB_0201, SRS_HUB_0232]
    ///
    /// TEST STEPS
    /// -# Create different paths and resolve them.
    ///
    /// EXPECTED RESULT: resolve_path() should behave as expected.
    {
        hub::filesystem::path path("abc/../simple_sample.txt");

        BOOST_CHECK_EQUAL(path.resolve_path().str(), "simple_sample.txt");
    }

    {
        hub::filesystem::path path("abc/../def/simple_sample.txt");

        BOOST_CHECK_EQUAL(path.resolve_path().str(), "def/simple_sample.txt");
    }

    {
        hub::filesystem::path path("abc/./def/../../simple_sample.txt");

        BOOST_CHECK_EQUAL(path.resolve_path().str(), "simple_sample.txt");
    }

    {
        hub::filesystem::path path("abc/./def/../ghi/./simple_sample.txt");

        BOOST_CHECK_EQUAL(path.resolve_path().str(), "abc/ghi/simple_sample.txt");
    }

    // tests with almost absolute paths.
    {
        hub::filesystem::path path("/sample/../simple.txt");

        BOOST_CHECK_EQUAL(path.resolve_path().str(), "/simple.txt");
    }

    {
        hub::filesystem::path path("/sample/../../../abc/simple.txt");

        BOOST_CHECK_EQUAL(path.resolve_path().str(), "/abc/simple.txt");
    }

    {
        hub::filesystem::path path("/sample/.././def/../abc/./../ghi/simple.txt");

        BOOST_CHECK_EQUAL(path.resolve_path().str(), "/ghi/simple.txt");
    }

    {
        hub::filesystem::path path("/abc//def/../ghi/./simple.txt");

        BOOST_CHECK_EQUAL(path.resolve_path().str(), "/abc/ghi/simple.txt");
    }

    {
        hub::filesystem::path path("/filesystem/primary/major/../../secondary/major/simple.txt");

        BOOST_CHECK_EQUAL(path.resolve_path().str(), "/filesystem/secondary/major/simple.txt");
    }

    // Make sure that when we do illegal things, it catches them.
    {
        hub::filesystem::path path("abc/../../simple_sample.txt");

        BOOST_CHECK_THROW(path.resolve_path(), hub::base::status_exception);
    }

    {
        hub::filesystem::path path("../simple_sample.txt");

        BOOST_CHECK_THROW(path.resolve_path(), hub::base::status_exception);
    }
}

BOOST_AUTO_TEST_CASE(file_locking_test)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_017] - Tests locking different ranges of files.[end] covers: [SRS_HUB_0102, SRS_HUB_0113, SRS_HUB_0114, SRS_HUB_0219]
    ///
    /// TEST STEPS
    /// -# Create a test lock file and open it for writing.
    /// -# Lock the file with 50 bytes offset and a size of 200 bytes.
    /// -# Check if file is locked with lsof command
    /// EXPECTED RESULT: file should be locked
    /// -# Unlock 20 bytes with 50 offset.
    /// -# Check if file is still locked with lsof command.
    /// EXPECTED RESULT: file should be locked because there is still a blocked region.
    /// -# Unlock the file entirely.
    /// EXPECTED RESULT: file should be unlocked.
    /// -# Try to open a second file with same path, this should fail.
    /// EXPECTED RESULT: exception should be thrown.
    /// -# Unlock and clean the files.
    /// EXPECTED RESULT: test file should be removed.

    hub::filesystem::file lockfile_a("test_lock_file");

    lockfile_a.open(hub::base::access_write);

    int fd = open("test_lock_file", O_WRONLY);
     
    // In the context of lsof command, 'fd'w means that the file descriptor fd is opened for writing and extra W means the file is currently held by an exclusive lock
    std::string file_unlocked = std::to_string(fd) + std::string("w   REG");
    std::string file_locked = std::to_string(fd) + std::string("ww  REG");

    std::string result = execCmd("lsof test_lock_file | grep hub_files");
  
    BOOST_CHECK(result.find(file_unlocked) != std::string::npos);

    lockfile_a.lock(50, 200);
    result = execCmd("lsof test_lock_file | grep hub_files");
    BOOST_CHECK(result.find(file_locked) != std::string::npos);

    lockfile_a.unlock(50, 20);
    result = execCmd("lsof test_lock_file | grep hub_files");
    BOOST_CHECK(result.find(file_locked) != std::string::npos);

    lockfile_a.unlock();
    result = execCmd("lsof test_lock_file | grep hub_files");
    BOOST_CHECK(result.find(file_unlocked) != std::string::npos);

    bool fail_to_relock = false;
    try
    {
        hub::filesystem::file lockfile_b("test_lock_file");
        lockfile_b.open(hub::base::access_read);
        lockfile_b.lock();
    }
    catch(const hub::base::status_exception &e)
    {
        BOOST_CHECK_EQUAL(e.what(), "Failed to lock a range of bytes in a file: Bad file descriptor.");
        fail_to_relock = true;
    }
    BOOST_CHECK(fail_to_relock);

    lockfile_a.close();
    lockfile_a.remove();
    BOOST_CHECK(!lockfile_a.exists());
}

BOOST_AUTO_TEST_CASE(file_ownership_test)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_018] - Tests out changing file ownership. [end] covers: [SRS_HUB_0204, SRS_HUB_0216, SRS_HUB_0217]
    ///
    /// TEST STEPS
    /// -# Create the file that we will adjust permissions on.
    /// -# Change file owner.
    /// -# Remove file.
    ///
    /// EXPECTED RESULT: File owner should be succesfully changed.

    // This assumes we can set ownership on a file that we just created (which
    // might not actually be the case, but it's the easiest way we can test this
    // particular API).
    hub::filesystem::path local("/tmp/owned_file");

    struct stat info;

    local.touch();
    hub::base::path_status status = local.get_status();

    hub::base::sleep(1.0);

    local.touch();

    hub::base::path_status status1 = local.get_status();

    BOOST_CHECK(status.modification_time.get().seconds == (status1.modification_time.get().seconds - 1));
    
    stat("/tmp/owned_file", &info);  // Error check omitted

    struct passwd *pw = getpwuid(info.st_uid);

    BOOST_CHECK_EQUAL(std::string(pw->pw_name), "root");

    local.change_owner("bin");

    stat("/tmp/owned_file", &info); 
    pw = getpwuid(info.st_uid);

    BOOST_CHECK_EQUAL(std::string(pw->pw_name), "bin");

    local.remove();

    BOOST_CHECK(!local.exists());
}

BOOST_AUTO_TEST_CASE(file_open_behavior)
{
    /// @addtogroup test_hub_filesystem
    /// @test [TEST_HUB_FILESYSTEM_019] - Test opening a file with different flags. [end] covers: [SRS_HUB_0126, SRS_HUB_0127;]
    ///
    /// Try to open an inexisting file with disposition_create_new and access_write
    /// Write to file
    /// EXPECTED RESULT: File is created and data is successfully written
    /// Try to read from file
    /// EXPECTED RESULT: Exception is thrown
    /// Try to open an existing file with disposition_create_new
    /// EXPECTED RESULT: Exception is thrown
    /// Try to open an inexisting file with disposition_create_always and access_write
    /// Write to file
    /// EXPECTED RESULT: File is created and data is successfully written
    /// Try to open an existing file with disposition_open_always and check file size
    /// EXPECTED RESULT: File is opened and size is not modified
    /// Try to open an existing file with disposition_open_existing and check file size
    /// EXPECTED RESULT: File is opened and size is not modified
    /// Try to open an existing file with access_write, disposition_default and check file size
    /// EXPECTED RESULT: File is opened and size set to 0
    /// Write to file, open file with access_read, disposition_default and check file size
    /// EXPECTED RESULT: File is opened and size is not modified
    /// Try to open the file with access_read, disposition_create_always and check file size
    /// EXPECTED RESULT: File is opened and size set to 0
    /// Try to write to file
    /// EXPECTED RESULT: Exception is thrown
    /// Try to open an inexisting file with disposition_open_existing
    /// EXPECTED RESULT: Exception is thrown
    /// Try to open  file with disposition_open_always and access_read, access_write, access_execute flags set.
    /// Try to write and read back data from file
    /// EXPECTED RESULT: Data is written and read succesffully, data written matches with read data.

    hub::filesystem::file file("file");
    size_t bytes_written = 0;
    size_t bytes_read = 0;
    char write_buff[] = "test";
    char read_buff[255];
    bool exception = false;

    BOOST_CHECK(!file.exists());
    file.open(hub::base::access_write, hub::base::disposition_create_new);
    BOOST_CHECK(file.exists());

    file.write(write_buff, sizeof(write_buff), bytes_written);
    BOOST_CHECK_EQUAL(bytes_written, sizeof(write_buff));

    try
    {
        file.read(read_buff, sizeof(read_buff), bytes_read);
    }
    catch(const std::exception& e)
    {
        exception = true;
        BOOST_CHECK_EQUAL(e.what(), "Failed to read from a file: Bad file descriptor.");
    }
    BOOST_CHECK(exception);
    
    file.close();
    exception = false;
    try
    {
        file.open(hub::base::access_write, hub::base::disposition_create_new);
    }
    catch(const std::exception& e)
    {
        exception = true;
        BOOST_CHECK_EQUAL(e.what(), "Failed to open \"file\": File exists.");
    }
    BOOST_CHECK(exception);

    // clean up for next test
    file.remove();

    BOOST_CHECK(!file.exists());
    file.open(hub::base::access_write, hub::base::disposition_create_always);
    BOOST_CHECK(file.exists());

    file.write(write_buff, sizeof(write_buff), bytes_written);
    BOOST_CHECK_EQUAL(file.get_size(), sizeof(write_buff));
    file.close();

    file.open(hub::base::access_write, hub::base::disposition_open_always);
    BOOST_CHECK_EQUAL(file.get_size(), sizeof(write_buff));
    file.close();
    
    file.open(hub::base::access_write, hub::base::disposition_open_existing);
    BOOST_CHECK_EQUAL(file.get_size(), sizeof(write_buff));
    file.close();

    file.open(hub::base::access_write, hub::base::disposition_default);
    BOOST_CHECK_EQUAL(file.get_size(), 0);
    file.write(write_buff, sizeof(write_buff), bytes_written);
    BOOST_CHECK_EQUAL(file.get_size(), sizeof(write_buff));
    file.close();

    file.open(hub::base::access_read, hub::base::disposition_default);
    BOOST_CHECK_EQUAL(file.get_size(), sizeof(write_buff));
    file.close();

    file.open(hub::base::access_read, hub::base::disposition_create_always);
    BOOST_CHECK_EQUAL(file.get_size(), 0);

    exception = false;
    try
    {
        file.write(write_buff, sizeof(write_buff), bytes_written);
    }
    catch(const std::exception& e)
    {
        exception = true;
        BOOST_CHECK_EQUAL(e.what(), "Failed to write to a file: Bad file descriptor.");
    }
    BOOST_CHECK(exception);

    file.close();
    file.remove();

    exception = false;
    try
    {
        file.open(hub::base::access_write, hub::base::disposition_open_existing);
    }
    catch(const std::exception& e)
    {
        exception = true;
        BOOST_CHECK_EQUAL(e.what(), "Failed to open \"file\": No such file or directory.");
    }
    BOOST_CHECK(exception);

    file.open((hub::base::access_read | hub::base::access_write | hub::base::access_execute), hub::base::disposition_open_always);

    BOOST_CHECK(file.exists());
    file.write(write_buff, sizeof(write_buff), bytes_written);

    file.seek(hub::base::seek_start, 0);

    hub::base::sleep(1.0);
    file.read(read_buff, sizeof(read_buff), bytes_read);

    BOOST_CHECK_EQUAL(bytes_written, bytes_read);
    BOOST_CHECK_EQUAL(std::string(write_buff, bytes_written), std::string(read_buff, bytes_read));

    file.remove();
}

BOOST_AUTO_TEST_SUITE_END()