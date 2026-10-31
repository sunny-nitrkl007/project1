/*
 * Hub
 * hub/filesystem/tests/filesystem_test.cc
 * Copyright 2012
 *
 * Tests out the filesystem namespace/library of Hub.
 *
 * National Robotics Engineering Center, Carnegie Mellon University
 * 10 40th Street, Pittsburgh, PA 15201
 * www.rec.ri.cmu.edu
 *
 * Control Instructions (who can see this code):
 * NREC Confidential.  Not for public release unless permission granted
 * by program manager.
 *
 * Usage Rights (who can use this code):
 * Usage allowed for all NREC programs with permissions from author and
 * program manager.
 *
 * This notice must appear in all copies of this file and its derivatives.
 *
 * History of Significant Contributions (don't put commit logs here):
 *     2012-04-01    Dan Tascione <dtascion@rec.ri.cmu.edu>    Created file.
 */

#include <hub/testing/unittests.hh>

#include <hub/base/platform/system_metrics.hh>
#include <hub/base/byte_buffer.hh>

#include <filesystem/journaled_file.hh>
#include <filesystem/file_buffer.hh>
#include <filesystem/lock_file.hh>
#include <filesystem/path.hh>



/**
 * Tests our file buffer input and out. This tests out our ability to read and
 * write data to file buffers.
 */
TEST(file_buffer_io)
{
    //
    // Write the first chunk of a file scoped, so we close
    // out properly.
    //

    {
        hub::filesystem::file_buffer output("test.buffer", hub::base::access_write | hub::base::access_read);

        output.truncate(16);

        //
        // Write out an unsigned integer.
        //

        size_t available_size;

        char *buffer = (char*) output.get_buffer_pointer(available_size, 4);

        CHECK_GREATER_THAN_OR_EQUAL(available_size, 4u);

        //
        // Next, write the integer out.
        //

        *((uint32_t*) &buffer[0]) = 0xcafefeed;

        output.write(buffer, 4);

        //
        // Seek and write a string.
        //

        buffer = (char*) output.get_buffer_pointer(available_size, 10);

        CHECK_GREATER_THAN_OR_EQUAL(available_size, 10u);

        strcpy(buffer, "Hello!");

        output.write(buffer, 10);

        //
        // Go back and overwrite the original bytes.
        //

        output.seek(hub::base::seek_start, 0);

        buffer = (char*) output.get_buffer_pointer(available_size, 4);

        CHECK_GREATER_THAN_OR_EQUAL(available_size, 4u);

        *((uint32_t*) &buffer[0]) = 0xfeedcafe;

        output.write(buffer, 4);
    }

    //
    // Next, we want to verify that the contents of the file
    // are what we expect them to be.
    //

    {
        hub::filesystem::path path("test.buffer");

        CHECK_EQUAL(path.get_size(), 16u);

        //
        // Open the file up in read mode.
        //

        hub::filesystem::file_buffer input("test.buffer", hub::base::access_read);

        //
        // Read the first four bytes. They should be the integer we
        // wrote out earlier.
        //

        uint32_t value;

        input.read(&value, sizeof(uint32_t));

        CHECK_EQUAL(value, 0xfeedcafeu);

        //
        // And then read the string out that we wrote.
        //

        char string[10];

        input.read(string, 8);

        CHECK_EQUAL(std::string(string), "Hello!");
    }

    //
    // Finally, clean up.
    //

    {
        hub::filesystem::path path("test.buffer");

        path.remove();
    }
}

/**
 * Tests out the lock file API, ensuring that it operates as intended.
 */
TEST(lock_file_test)
{
    //
    // Create the first reference to a lock file here.
    //

    hub::filesystem::lock_file file("test.hlockfile");

    //
    // Next, nested, we want to try and reacquire the lock file.
    //

    bool failed_to_acquire_lock = false;

    try
    {
        hub::filesystem::lock_file second_file("test.hlockfile", 0.2);
    }
    catch(const hub::base::status_exception&)
    {
        failed_to_acquire_lock = true;
    }

    //
    // Ensure we failed to acquire the lock.
    //

    CHECK_EQUAL(failed_to_acquire_lock, true);
}

/**
 * This tests that we can work on journaled files without issue.
 */
TEST(journaled_file_test)
{
    //
    // Create the file that we are going to write to...
    //

    {
        hub::filesystem::journaled_file file("test_journaled_file");

        file.open(hub::base::access_write);

        file.write_entirely("Hello, world!");

        //
        // Check to make sure the files exist that we think should
        // exist.
        //

        hub::filesystem::path journal_path("test_journaled_file.hjournal");

        CHECK_EQUAL(journal_path.exists(), true);

        //
        // Close it and make sure it exists, and the journaled path doesn't.
        //

        file.close();

        CHECK_EQUAL(journal_path.exists(), false);

        CHECK_EQUAL(file.exists(), true);
    }

    //
    // Now read it back in, and make sure we get what we expect!
    //

    {
        hub::filesystem::journaled_file file("test_journaled_file");

        file.open();

        std::string value = file.read_entirely();

        CHECK_EQUAL(value, "Hello, world!");

        //
        // Cleanup the file now.
        //

        file.close();

        file.remove();
    }
}

//
// Disable this unit test on Windows -- you need to run as Admin (!) to change
// a files owner, even to yourself.
//


/*
 * Entrance point.
 */
int main(void)
{
    return hub::testing::test_director::run_all_tests();
}
