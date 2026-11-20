//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file hub/filesystem/file_buffer.cc
/// @ingroup hub_filesystem
/// @copyright Copyright (C) 2012
///  
/// @brief An implementation of an abstract_buffer, used for reading file data
/// in a buffered fashion.
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
///     2012-04-01    Dan Tascione <dtascion@rec.ri.cmu.edu>    Created file.
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include <filesystem/file_buffer.hh>

#include <hub/base/status_exception.hh>

#include <algorithm>

//
// Working entirely within the filesystem namepsace.
//

using namespace hub::filesystem;

/*
 * ################################################################################################
 */

file_buffer::file_buffer (
                           const file &target,
                           hub::base::access_flags buffer_access_flags,
                           hub::base::open_disposition open_disposition,
                           hub::base::caching_behavior behavior
                         )
                         :
                         parent_file(target),
                         buffer_available(0),
                         buffer_offset(0),
                         file_offset(0),
                         access_flags(buffer_access_flags)
{
    //
    // If they didn't specify at least read access, bail with an error.
    // We need it.
    //

    if((access_flags & hub::base::access_read) == 0)
    {
        throw hub::base::status_exception() << "File buffer objects must be opened with (at least) read access. The "
                                               "file \"" << target.str() << "\" was not.";
    }

    //
    // Setup buffer pointers.
    //

    internal_buffer = stack_buffer;
    buffer_maximum_size = sizeof(stack_buffer);

    //
    // Open the file, with the desired access, and cache the size.
    //

    parent_file.open(access_flags, open_disposition, behavior);

    file_size = parent_file.get_size();
}

/*
 * ################################################################################################
 */

file_buffer::file_buffer (
                           const std::string &target,
                           hub::base::access_flags buffer_access_flags,
                           hub::base::open_disposition open_disposition,
                           hub::base::caching_behavior behavior
                         )
                         :
                         parent_file(target),
                         buffer_available(0),
                         buffer_offset(0),
                         file_offset(0),
                         access_flags(buffer_access_flags)
{
    //
    // If they didn't specify at least read access, bail with an error.
    // We need it.
    //

    if((buffer_access_flags & hub::base::access_read) == 0)
    {
        throw hub::base::status_exception() << "File buffer objects must be opened with (at least) read access. The "
                                               "file \"" << target << "\" was not.";
    }

    //
    // Setup buffer pointers.
    //

    internal_buffer = stack_buffer;
    buffer_maximum_size = sizeof(stack_buffer);

    //
    // Open the file, with the desired access, and cache the size.
    //

    parent_file.open(access_flags, open_disposition, behavior);

    file_size = parent_file.get_size();
}

/*
 * ################################################################################################
 */

file_buffer::~file_buffer()
{
    free_buffer();
}

/*
 * ################################################################################################
 */

void file_buffer::free_buffer()
{
    //
    // If we aren't still pointing at the stack buffer, clean up.
    // We also reset a few internal variables, to make it more obvious
    // what happened.
    //

    if(internal_buffer != stack_buffer)
    {
        free(internal_buffer);

        internal_buffer = NULL;
    }
}

/*
 * ################################################################################################
 */

void file_buffer::read (
                         void *destination,
                         size_t destination_size
                       )
{
    //
    // Wipe out any buffer. You shouldn't really be mixing/matching
    // these routines anyway.
    //

    file_offset += buffer_offset;

    buffer_available = 0;
    buffer_offset = 0;

    //
    // Seek to where *we* think they are in the file.
    //

    parent_file.seek(hub::base::seek_start, file_offset);

    //
    // Read into the buffer.
    //

    size_t bytes_read;

    parent_file.read(destination, destination_size, bytes_read);

    file_offset += bytes_read;

    //
    // If we didn't get exactly the right number of bytes read,
    // then error out.
    //

    if(bytes_read != destination_size)
    {
        throw hub::base::status_exception() << "Failed to read exactly " << destination_size << " bytes (only read "
                                            << bytes_read << " bytes) from \"" << parent_file.str() << "\".";
    }
}

/*
 * ################################################################################################
 */

void file_buffer::write (
                          const void *source,
                          size_t source_size
                        )
{
    //
    // Make sure we are in write mode.
    //

    if((access_flags & hub::base::access_write) == 0)
    {
        throw hub::base::status_exception() << "Cannot write to the file \"" << parent_file.str() << ": The file "
                                               "was opened with read access only.";
    }

    //
    // Wipe out any buffer. They have to start over at this point.
    //

    file_offset += buffer_offset;

    buffer_available = 0;
    buffer_offset = 0;

    //
    // Seek to where they specified we should write to.
    //

    parent_file.seek(hub::base::seek_start, file_offset);

    //
    // Read into the buffer.
    //

    size_t bytes_written;

    parent_file.write(source, source_size, bytes_written);

    file_offset += bytes_written;

    //
    // Adjust the file size here. This is just a guess, but it should
    // be pretty accurate, assuming only one process is writing to this
    // buffer.
    //

    file_size = std::max(file_size, file_offset);

    //
    // If we didn't get exactly the right number of bytes written,
    // then error out.
    //

    if(bytes_written != source_size)
    {
        throw hub::base::status_exception() << "Failed to write exactly " << source_size << " bytes (only wrote "
                                            << bytes_written << " bytes) to \"" << parent_file.str() << "\".";
    }
}

/*
 * ################################################################################################
 */

void file_buffer::seek (
                         hub::base::seek_direction direction,
                         uint64_t offset
                       )
{
    //
    // How many bytes do we have left in the buffer?
    //

    uint64_t buffer_bytes_left = buffer_available - buffer_offset;

    //
    // Which direction do they want to seek in?
    //

    switch(direction)
    {
    case hub::base::seek_current:
        {
            //
            // Seek from the current position forward. If this takes us outside of
            // the file buffer range, then just seek straight up.
            //

            if(offset >= buffer_bytes_left)
            {
                //
                // Reset buffer and set new file position.
                //

                file_offset = file_offset + buffer_offset + offset;

                buffer_offset = 0;
                buffer_available = 0;
            }
            else
            {
                //
                // Easy case; just adjust the buffer offset. This is a safe
                // cast, because offset is less than buffer bytes left, so
                // we know we are a small number.
                //

                buffer_offset = (size_t) (buffer_offset + offset);
            }

            break;
        }

    case hub::base::seek_start:
        {

            //
            // Seek from the start position (aka, an absolute seek).
            //

            if(offset >= file_offset && offset < (file_offset + buffer_available))
            {
                //
                // We are still within range of the buffer. Just adjust the buffer
                // offset accordingly.
                //

                buffer_offset = (size_t) (offset - file_offset);
            }
            else
            {
                //
                // We are no longer within range of the buffer; invalidate it.
                //

                file_offset = offset;

                buffer_offset = 0;
                buffer_available = 0;
            }

            break;
        }

    case hub::base::seek_end:
        {
            //
            // Seek to the end position. Just assume that they are outside of
            // the buffer ranges and invalidate the read buffer.
            //

            uint64_t parent_file_size = parent_file.get_size();

            if(offset > parent_file_size)
                throw hub::base::status_exception("Tried to seek outside of the bounds of a file.");

            file_offset = parent_file_size - offset;

            buffer_offset = 0;
            buffer_available = 0;

            break;
        }
    }
}

/*
 * ################################################################################################
 */

void file_buffer::truncate (
                             uint64_t offset
                           )
{
    //
    // Make sure we are in write mode.
    //

    if((access_flags & hub::base::access_write) == 0)
    {
        throw hub::base::status_exception() << "Cannot truncate the file \"" << parent_file.str() << ": The file "
                                               "was opened with read access only.";
    }

    //
    // We are, good. Let's flush any buffers we have active.
    //

    buffer_available = 0;
    buffer_offset = 0;

    //
    // Now, adjust file pointers to the appropriate offset, if they are
    // too high.
    //

    if(offset < file_offset)
    {
        file_offset = offset;
    }

    //
    // And finally, call truncate on the file.
    //

    parent_file.set_file_size(offset);
}

/*
 * ################################################################################################
 */

void* file_buffer::get_buffer_pointer (
                                        size_t &buffer_size,
                                        size_t desired_size
                                      )
{
    //
    // Calculate how many bytes are left in the buffer.
    //

    size_t bytes_left = buffer_available - buffer_offset;

    //
    // Do we have bytes left in the buffer? If so, we can just return
    // that again.
    //

    if(bytes_left > 0 && bytes_left >= desired_size)
    {
        buffer_size = bytes_left;

        return &internal_buffer[buffer_offset];
    }

    //
    // Sanity check -- if they requested more bytes than our maximum
    // size, then we will resize to fit in their requested size!
    //
    // This is a good place to do this, since we are about to dump the
    // entire buffer anyway. ;)
    //

    if(desired_size > buffer_maximum_size)
    {
        //
        // Just set us equal plus a tiny bit of padding.
        // If they are requesting something so large, chances
        // are this is all they want.
        //

        buffer_maximum_size = desired_size + sizeof(stack_buffer);

        //
        // Reallocate the internal buffer now.
        //

        free_buffer();

        internal_buffer = (char*) malloc(buffer_maximum_size);
    }

    //
    // Seek to the current position in the file. Because we are already reading data
    // in, we want to invalidate the internal buffer and read as much as possible.
    //

    file_offset = get_position();
    buffer_available = 0;

    parent_file.seek(hub::base::seek_start, file_offset);

    //
    // In write mode, limit the how much we try to read in based
    // on the size of the file.
    //

    size_t bytes_to_read = buffer_maximum_size;

    if(access_flags & hub::base::access_write)
    {
        //
        // Because the file is open, we need to seek around to figure out
        // the real size of the file, rather than asking the filesystem for it.
        //

        parent_file.seek(hub::base::seek_end, 0);

        uint64_t parent_file_size = parent_file.get_position();

        parent_file.seek(hub::base::seek_start, file_offset);;

        //
        // How many bytes are left in this buffer? This determines how much
        // we can actually re-read.
        //

        uint64_t parent_bytes_left = parent_file_size - file_offset;

        if(desired_size > parent_bytes_left)
        {
            desired_size = (size_t) parent_bytes_left;
            bytes_to_read = (size_t) parent_bytes_left;
        }
    }

    //
    // Read in a chunk of data into our internal buffer.
    //

    size_t bytes_read;

    parent_file.read(internal_buffer, bytes_to_read, bytes_read);

    buffer_offset = 0;
    buffer_available = bytes_read;

    //
    // Double check to make sure we read all of the data the caller
    // wanted to read.
    //

    if(bytes_read < desired_size)
    {
        throw hub::base::status_exception() << "Requested a buffer size of " << bytes_to_read << " bytes, but only "
                                            << bytes_read << " bytes could be read from the base file \""
                                            << parent_file.str() << "\".";
    }

    //
    // Return the internal buffer and size left. If we are in write mode, return
    // the maximum buffer size. They use write() to confirm what size they
    // used was, and this avoids lots of spurious calls to get buffer pointers.
    //

    if(access_flags & hub::base::access_write)
    {
        buffer_size = buffer_maximum_size;
    }
    else
    {
        buffer_size = buffer_available;
    }

    return internal_buffer;
}

/*
 * ################################################################################################
 */

uint64_t file_buffer::get_position() const
{
    return file_offset + buffer_offset;
}

/*
 * ################################################################################################
 */

uint64_t file_buffer::get_size() const
{
    return file_size;
}
