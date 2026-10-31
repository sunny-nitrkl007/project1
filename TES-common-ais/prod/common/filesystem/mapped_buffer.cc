//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file hub/filesystem/mapped_buffer.cc
/// @ingroup hub_filesystem
/// @copyright Copyright (C) 2012
///  
/// @brief An implementation of an abstract_buffer, used for reading file data
///  in a buffered fashion, through memory mapped I/O.
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
///     2012-11-26    Dan Tascione <dtascion@rec.ri.cmu.edu>    Created file.
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include <filesystem/mapped_buffer.hh>

#include <hub/utility/round.hh>

#include <hub/base/platform/system_metrics.hh>
#include <hub/base/status_exception.hh>

//
// Working entirely within the filesystem namepsace.
//

using namespace hub::filesystem;

/*
 * ################################################################################################
 */

mapped_buffer::mapped_buffer (
                               const file &target
                             )
                             :
                             parent_file(target),
                             internal_buffer(NULL),
                             buffer_available(0),
                             buffer_offset(0),
                             file_offset(0)
{
    initialize_buffer();
}

/*
 * ################################################################################################
 */

mapped_buffer::mapped_buffer (
                               const std::string &path
                             )
                             :
                             parent_file(path),
                             internal_buffer(NULL),
                             buffer_available(0),
                             buffer_offset(0),
                             file_offset(0)
{
    initialize_buffer();
}

/*
 * ################################################################################################
 */

mapped_buffer::~mapped_buffer()
{
    //
    // We need to make sure this view is unmapped, to clean up any existing file
    // handles properly.
    //

    unmap_buffer_pointer();
}

/*
 * ################################################################################################
 */

void mapped_buffer::initialize_buffer()
{
    //
    // Open the file, with read access.
    //

    parent_file.open(hub::base::access_read);

    file_size = parent_file.get_size();

    //
    // Cache system information, for mmap purposes.
    //

    hub::base::system_information system_information;

    hub::base::get_system_information(system_information);

    allocation_granularity = system_information.allocation_granularity;
}

/*
 * ################################################################################################
 */

void mapped_buffer::read (
                           void *destination,
                           size_t destination_size
                         )
{
    //
    // For this routine, we still use memory mapped I/O. We'll just
    // keep aquiring buffer pointers until we satisfy their destination
    // size request.
    //

    size_t available_size;

    char *pointer = (char*) get_buffer_pointer(available_size, destination_size);

    if(available_size < destination_size)
    {
        throw hub::base::status_exception("Tried to read %u bytes from a mapped buffer, but only %u "
                                            "bytes were available!", destination_size, available_size);
    }

    //
    // We got a valid pointer. Just do a quick memcpy() of the data
    // over.
    //

    memcpy(destination, pointer, destination_size);

    //
    // Seek ahead now, by the number of bytes we read, to keep all pointers
    // adjusted appropriately (and to remain within the mapped page if at
    // all possible).
    //

    seek(hub::base::seek_current, destination_size);
}

/*
 * ################################################################################################
 */

void mapped_buffer::write (
                            const void *source,
                            size_t source_size
                          )
{
    throw hub::base::status_exception("Access denied: You cannot write to a mapped buffer.");
}

/*
 * ################################################################################################
 */

void mapped_buffer::seek (
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

                unmap_buffer_pointer();
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

            if(offset >= file_offset && offset <= (file_offset + buffer_available))
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

                unmap_buffer_pointer();
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

            unmap_buffer_pointer();

            break;
        }
    }
}

/*
 * ################################################################################################
 */

void mapped_buffer::truncate (
                               uint64_t offset
                             )
{
    throw hub::base::status_exception("Tried to truncate a mapped buffer, but they are read only.");
}

/*
 * ################################################################################################
 */

void* mapped_buffer::get_buffer_pointer (
                                          size_t &buffer_size,
                                          size_t desired_size
                                        )
{
    //
    // Do we have bytes left in the buffer? If so, we can just return
    // that again.
    //

    size_t bytes_left = buffer_available - buffer_offset;

    if(bytes_left > 0 && bytes_left > desired_size)
    {
        buffer_size = bytes_left;

        return &internal_buffer[buffer_offset];
    }

    //
    // Unfortunately, we need to map pages on proper boundaries, which we might not be
    // on. Let's drop the file offset to the closest page boundary.
    //

    uint64_t old_file_offset = get_position();

    uint64_t new_file_offset = hub::utility::lower_to_previous_multiple (
                                                                          old_file_offset,
                                                                          allocation_granularity
                                                                        );

    //
    // If we already have data mapped in, unmap it now.
    //

    unmap_buffer_pointer();

    //
    // We set the file offset to be where we are mapping the base page in, but
    // the buffer offset is actually advanced some.
    //

    file_offset = new_file_offset;
    buffer_offset = (size_t) (old_file_offset - new_file_offset);

    //
    // Setup our new buffer sizes. We just say that we have at least the system allocation
    // granularity of buffer available, to avoid mapping in small amounts of data.
    //

    if(desired_size > 0)
    {
        buffer_available = (size_t) hub::utility::raise_to_next_multiple (
                                                                           desired_size,
                                                                           allocation_granularity
                                                                         );
    }
    else
    {
        //
        // They requested zero bytes, which is the default. Just give them back one page.
        //

        buffer_available = allocation_granularity;
    }

    //
    // Make sure we don't read off the edge of the file. Note the type difference,
    // so we don't use any casting or std::min(), which can cause some overflows.
    //

    if(old_file_offset > file_size || new_file_offset > file_size)
    {
        throw hub::base::status_exception("Tried to read off the edge of the mapped buffer for "
                                            "file \"%s\".", parent_file.c_str());
    }

    uint64_t file_size_left = file_size - file_offset;

    if(file_size_left < buffer_available)
        buffer_available = (size_t) file_size_left;

    //
    // Before we map this in, make sure buffer available is less than the desired
    // size. Otherwise, we need to throw an error here to be consistent.
    //

    if(buffer_available < desired_size)
    {
        throw hub::base::status_exception("Requested reading too many bytes from the mapped buffer "
                                            "for file \"%s\". Wanted %u, but only %u is available.",
                                            parent_file.c_str(), desired_size, buffer_available);
    }

    //
    // Map a view in, either with the desired size, or 32KB, and start from the
    // current file position. We need to do get_position() here to make sure that
    // we take into account any buffer offset.
    //

    internal_buffer = (char*) parent_file.map_into_memory(file_offset, buffer_available);

    //
    // Return the internal buffer and size we mapped.
    //

    buffer_size = buffer_available - buffer_offset;

    return &internal_buffer[buffer_offset];
}

/*
 * ################################################################################################
 */

void mapped_buffer::unmap_buffer_pointer()
{
    //
    // If we have an internal buffer, unmap the view now.
    //

    if(internal_buffer)
        parent_file.unmap_from_memory(internal_buffer, buffer_available);

    //
    // Reset all of the statistics.
    //

    internal_buffer = NULL;
    buffer_offset = 0;
    buffer_available = 0;
}

/*
 * ################################################################################################
 */

uint64_t mapped_buffer::get_position() const
{
    return file_offset + buffer_offset;
}

/*
 * ################################################################################################
 */

uint64_t mapped_buffer::get_size() const
{
    return file_size;
}
