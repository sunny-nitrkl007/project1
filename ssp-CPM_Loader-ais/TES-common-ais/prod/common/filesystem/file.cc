//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copyright hub/filesystem/file.cc
/// @ingroup hub_filesystem
/// @copyright Copyright (C) 2012
/// 
/// @brief This is the base file object in Hub -- it contains all of the routines that
/// you use for interacting with files.
///
/// @copyright National Robotics Engineering Center, Carnegie Mellon University
/// @copyright 10 40th Street, Pittsburgh, PA 15201
/// @copyright www.rec.ri.cmu.edu
/// 
/// @copyright Control Instructions (who can see this code):
/// @copyright NREC Confidential.  Not for public release unless permission granted
/// @copyright by program manager.
/// 
/// @copyright Usage Rights (who can use this code):
/// @copyright Usage allowed for all NREC programs with permissions from author and
/// @copyright program manager.
/// 
/// @copyright This notice must appear in all copies of this file and its derivatives.
/// 
/// History of Significant Contributions (don't put commit logs here):
///         2012-04-01    Dan Tascione <dtascion@rec.ri.cmu.edu>    Created file.
/// 
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include <hub/base/status_exception.hh>
#include <hub/base/byte_buffer.hh>

#include <filesystem/file.hh>

#include <hub/utility/string.hh>

#include <limits>
#include <list>

//
// Everything we do here is in the filesystem namespace.
//

using namespace hub::filesystem;

/*
 * ################################################################################################
 */

file::file() : path(""),
               is_file_open(false)
{
}

/*
 * ################################################################################################
 */

file::file (
             const path &source
           )
           :
           path(source),
           is_file_open(false)
{
}

/*
 * ################################################################################################
 */

file::file (
             const path &parent,
             const path &child
           )
           :
           path(parent, child),
           is_file_open(false)
{
}

/*
 * ################################################################################################
 */

file::file (
             const file &other
           )
           :
           path(other)
{
    *this = other;
}

/*
 * ################################################################################################
 */

file::~file()
{
    //
    // Close the file, if we need to.
    //

    if(is_file_open)
    {
        hub::base::close_file(handle);
        is_file_open = false;
    }
}

/*
 * ################################################################################################
 */

file& file::operator= (
                        const file &other
                      )
{
    //
    // Make sure we aren't copying right ontop of ourself, or things
    // will get very interesting.
    //

    if(this != &other)
    {
        //
        // Copy over the path.
        //

        path::operator=(other.str());

        //
        // If the file is already open, then we need to reopen
        // it here, to avoid weirdness with close semantics.
        //

        is_file_open = false;

        if(other.is_file_open)
        {
            open();
        }
    }

    return *this;
}

/*
 * ################################################################################################
 */

bool file::operator== (
                        const file& other
                      ) const
{
    return (
             is_file_open == other.is_file_open &&
             path::operator==(other)
           );
}

/*
 * ################################################################################################
 */

void file::open (
                  hub::base::access_flags flags,
                  hub::base::open_disposition disposition,
                  hub::base::caching_behavior behavior
                )
{
    if(is_file_open)
    {
        throw hub::base::status_exception("Tried to reopen an already open file, \"%s\".",
                                            c_str());
    }

    hub::base::create_file(handle, str(), flags, disposition, behavior);

    is_file_open = true;
}

/*
 * ################################################################################################
 */

void file::open_for_appending()
{
    //
    // Try to open the file -- always create it, even if it doesn't exist.
    //

    open(hub::base::access_read | hub::base::access_write, hub::base::disposition_open_always);

    //
    // Seek to the end, so that we can begin writing.
    //

    seek(hub::base::seek_end, 0);
}

/*
 * ################################################################################################
 */

void file::close()
{
    if(is_file_open == false)
    {
        throw hub::base::status_exception("Tried to close an already closed file, \"%s\".",
                                            c_str());
    }

    hub::base::close_file(handle);

    is_file_open = false;
}

/*
 * ################################################################################################
 */

void file::read (
                  void *destination,
                  size_t destination_size,
                  size_t &bytes_read
                )
{
    //
    // Make sure we are open.
    //

    if(is_file_open == false)
    {
        open(hub::base::access_read);
    }

    //
    // Read data from the handle.
    //

    hub::base::read_file(handle, destination, destination_size, bytes_read);
}

/*
 * ################################################################################################
 */

void file::write (
                   const void *source,
                   size_t source_size,
                   size_t &bytes_written
                 )
{
    //
    // Make sure we are open.
    //

    if(is_file_open == false)
    {
        open(hub::base::access_write);
    }

    //
    // Write out the buffer to the handle.
    //

    hub::base::write_file(handle, source, source_size, bytes_written);
}

/*
 * ################################################################################################
 */

std::string file::read_entirely()
{
    std::string result;

    read_entirely(result);

    return result;
}

/*
 * ################################################################################################
 */

void file::read_entirely (
                           std::string &destination
                         )
{
    //
    // Read in the file into the specified buffer.
    //

    hub::base::byte_buffer buffer;

    read_entirely(buffer);

    buffer.seek(hub::base::seek_start, 0);

    //
    // Make sure we aren't more than the 32-bit boundary.
    //

    uint64_t buffer_size = buffer.get_size();

    if(buffer_size >= std::numeric_limits<size_t>::max())
    {
        throw hub::base::status_exception("Tried to read a file larger than allowed with the "
                                            "read_entirely() API.");
    }

    //
    // Now, grab the buffer contents and put them into the string.
    //

    size_t bytes_read;

    const char *contents = (const char*) buffer.get_buffer_pointer(bytes_read, (size_t) buffer_size);

    destination.assign(contents, (size_t) buffer_size);
}

/*
 * ################################################################################################
 */

void file::read_entirely (
                           hub::base::abstract_buffer &destination
                         )
{
    //
    // Make sure the file is opened. Need to do this here,
    // because read() may never get called, and we want to
    // be consistent.
    //

    if(is_file_open == false)
    {
        open(hub::base::access_read);
    }

    //
    // How big is this file? Since the file is open, we can
    // figure this out simply by seeking around. This can save
    // a call to stat the file.
    //

    uint64_t original_position = hub::base::get_file_position(handle);

    hub::base::seek_file(handle, hub::base::seek_end, 0);

    uint64_t file_size = hub::base::get_file_position(handle);

    hub::base::seek_file(handle, hub::base::seek_start, original_position);

    //
    // Loop here, until we have read the complete contents of the file.
    //

    uint64_t offset = 0;

    while(offset < file_size)
    {
        //
        // Get a buffer pointer, as big as we can.
        //

        uint64_t bytes_left = file_size - offset;

        size_t buffer_size;

        void *buffer_pointer = destination.get_buffer_pointer(buffer_size, (size_t) bytes_left);

        //
        // Alright, let's try to read in as much as we can.
        //

        size_t bytes_read;

        read(buffer_pointer, buffer_size, bytes_read);

        //
        // If bytes read are zero, then I guess we assume we are done
        // reading? This shouldn't really happen normally, it should
        // only happen if something has gone awry (or, we are reading
        // from some special file on Unix that reports its size incorrectly).
        //

        if(bytes_read == 0)
            break;

        //
        // Advance the buffer size, so that it takes into account the data
        // we just read.
        //

        destination.write(buffer_pointer, bytes_read);

        //
        // Keep updating our overall offset.
        //

        offset += bytes_read;
    }
}

/*
 * ################################################################################################
 */

void file::write_entirely (
                            const std::string &content
                          )
{
    write_entirely((const void*) content.c_str(), (size_t) content.length());
}

/*
 * ################################################################################################
 */

void file::write_entirely (
                            hub::base::abstract_buffer &source
                          )
{
    //
    // Get access to the raw bytes.
    //

    size_t buffer_size;

    size_t bytes_left = (size_t) (source.get_size() - source.get_position());

    const void *bytes = source.get_buffer_pointer(buffer_size, bytes_left);

    //
    // Read everything in one giant chunk.
    //

    write_entirely(bytes, bytes_left);
}

/*
 * ################################################################################################
 */

void file::write_entirely (
                            const void *source,
                            size_t source_size
                          )
{
    //
    // Write the content out.
    //

    size_t bytes_written;

    write(source, source_size, bytes_written);

    //
    // Make sure we wrote out everything we wanted to.
    //

    if(bytes_written != source_size)
    {
        throw hub::base::status_exception("Short write (only %u bytes written out of %u total) for file \"%s\".", bytes_written, source_size, c_str());
    }
}

/*
 * ################################################################################################
 */

void file::seek (
                  hub::base::seek_direction direction,
                  uint64_t offset
                )
{
    if(is_file_open == false)
    {
        throw hub::base::status_exception("Tried to seek a closed file, \"%s\".", c_str());
    }

    hub::base::seek_file(handle, direction, offset);
}

/*
 * ################################################################################################
 */

uint64_t file::get_position()
{
    return hub::base::get_file_position(handle);
}

/*
 * ################################################################################################
 */

void file::set_file_size (
                           uint64_t new_size
                         )
{
    if(is_file_open == false)
    {
        throw hub::base::status_exception("Tried to truncate a closed file, \"%s\".", c_str());
    }

    hub::base::set_file_size(handle, new_size);
}

/*
 * ################################################################################################
 */

void file::flush()
{
    if(is_file_open == false)
    {
        throw hub::base::status_exception("Tried to flush a closed file, \"%s\".", c_str());
    }

    hub::base::flush_file(handle);
}

/*
 * ################################################################################################
 */

void file::lock (
                  uint64_t offset,
                  uint64_t size
                )
{
    return hub::base::lock_file(handle, offset, size);
}

/*
 * ################################################################################################
 */

void file::unlock (
                    uint64_t offset,
                    uint64_t size
                  )
{
    return hub::base::unlock_file(handle, offset, size);
}

/*
 * ################################################################################################
 */

void *file::map_into_memory (
                              uint64_t offset,
                              uint64_t size
                            )
{
    //
    // Easy, just redirect to the PA layer.
    //

    return hub::base::map_file_into_memory(handle, offset, size, handle.access_flags);
}

/*
 * ################################################################################################
 */

void file::unmap_from_memory (
                               void *address,
                               uint64_t size
                             )
{
    //
    // There isn't even anything specific to the file class for this
    // call.
    //

    hub::base::unmap_file_from_memory(address, size);
}
