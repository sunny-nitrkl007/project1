//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file hub/filesystem/file_buffer.hh
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
///            2012-04-01    Dan Tascione <dtascion@rec.ri.cmu.edu>    Created file.
///  
///            2012-11-26    Dan Tascione <dtascion@rec.ri.cmu.edu>    Adjust to standard file I/O, memory
///                                                                    mapped I/O was causing crashes when
///                                                                    disks were yanked.
///  
//////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HUB_FILESYSTEM_FILE_BUFFER_H
#define HUB_FILESYSTEM_FILE_BUFFER_H

#include <hub/base/common.hh>
#include <hub/base/abstract_buffer.hh>

#include <filesystem/file.hh>

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Inside the shared filesystem namespace.
//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace hub
{
    namespace filesystem
    {
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This class implements the standard buffer interface used throughout Hub, as a means
        /// of accessing file data in a paged, buffered fashion. This can have some advantages to
        /// just working with a standard file read call, as you can read in buffered pages of data.
        /// The advantage over straight memory mapping, is you still have some control over when
        /// data is read in from disk.
        /// It is probably worth just implementing this with memory mapped I/O on the backend in
        /// the future, once we get that into the platform abstraction layer.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        class export_object file_buffer : public hub::base::abstract_buffer
        {
        public:

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Initializes a file buffer based on the supplied file. This will attempt
            /// to open the file with the desired access rights.
            /// You can specify the caching behavior (optionally) to file buffers. This can
            /// help indicate how you plan on accessing the file to improve performance
            /// in certain workloads.
            ///
            /// @param[in] target file
            /// @param[in] access_flags general access flags
            /// @param[in] open_disposition open dispositions
            /// @param[in] behavior file caching behaviors
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            file_buffer (
                          const file &target,
                          hub::base::access_flags access_flags = hub::base::access_read,
                          hub::base::open_disposition open_disposition = hub::base::disposition_default,
                          hub::base::caching_behavior behavior = hub::base::caching_behavior_default
                        );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Initializes a file buffer based on the supplied path. This will attempt
            /// to open the file with the desired access rights.
            /// You can specify the caching behavior (optionally) to file buffers. This can
            /// help indicate how you plan on accessing the file to improve performance
            /// in certain workloads.
            ///
            /// @param[in] target file path
            /// @param[in] access_flags general access flags
            /// @param[in] open_disposition open dispositions
            /// @param[in] behavior file caching behaviors
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            file_buffer (
                          const std::string &target,
                          hub::base::access_flags access_flags = hub::base::access_read,
                          hub::base::open_disposition open_disposition = hub::base::disposition_default,
                          hub::base::caching_behavior behavior = hub::base::caching_behavior_default
                        );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Destructor. Closes any open handles and releases any allocated memory.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            ~file_buffer();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Reads the given number of bytes from the buffer, copying them to the supplied
            /// pointer. If there is not enough room, then this routine will throw an exception.
            ///
            /// @param[out] destination pointer to output storage buffer
            /// @param[in] destination_size destination buffer size
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            virtual void read (
                                void *destination,
                                size_t destination_size
                              );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Writes the given number of bytes into the buffer, copying them from the supplied
            /// pointer. If there is not enough room in the buffer, then the buffer will be expanded
            /// automatically.
            //
            /// @param[in] source pointer to buffer with data to write
            /// @param[in] source_size size of data to write
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            virtual void write (
                                 const void *source,
                                 size_t source_size
                               );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Seeks to the specified position within the given file. This will affect all internal
            /// buffers and seek state.
            ///
            /// @param[in] direction direction to seek from: seek_start, seek_current or seek_end
            /// @param[in] offset offset from the seek direction
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            virtual void seek (
                                hub::base::seek_direction direction,
                                uint64_t offset
                              );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Get a pointer to the internal file buffer, for fast read/write access.
            /// This pointer will be located at the internal file offset. The only way to
            /// adjust the pointer is to seek.
            /// The number of bytes actually left in the buffer will be returned to you in
            /// the buffer size structure.
            ///
            /// @param[out] buffer_size buffer size remaining, will be the same as the desired size unless out of memory
            /// @param[in] desired_size desire buffer size
            /// @return void* pointer to the internal byte buffer
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            virtual void* get_buffer_pointer (
                                               size_t &buffer_size,
                                               size_t desired_size = abstract_buffer::default_desired_size
                                             );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Get the current position (within the source data stream) of this
            /// buffer. This position is referenced from the beginning of the buffer.
            ///
            /// @return current position
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            virtual uint64_t get_position() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Get the size of the content stored within this byte buffer.
            ///
            /// @return size of the content
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            virtual uint64_t get_size() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Truncates the byte buffer back to the current size. This adjusts the content
            /// size and offset, as necessary.
            ///
            /// @param[in] offset new buffer size
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            virtual void truncate (
                                    uint64_t offset
                                  );

        private:
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief A reference to the file handle we operate on.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            hub::filesystem::file parent_file;

            /// The internal buffer. When we read file data, we actually read
            /// it into this buffer, to keep from hitting the disk too often.
            char *internal_buffer;

            /// The bytes actually present in the buffer.
            size_t buffer_available;

            /// The offset into the buffer of where we are reading.
            size_t buffer_offset;

            /// The size of the buffer, as allocated on disk.
            size_t buffer_maximum_size;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief The estimated size of the file. We seed the file size on startup
            /// with the real size of the file, and advance it as the user calls
            /// write(). Some operating systems / filesystems do not update the
            /// real size until a call to close() or sync(), so we need to track
            /// that ourself.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            uint64_t file_size;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief The position in the file, so when we read more data, we know where
            /// to read it at.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            uint64_t file_offset;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief The stack buffer -- the internal buffer points to this stack by default.
            /// We only allocate a buffer if the user requested it.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            char stack_buffer[4096];

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Defines flags that indicate access rights of this file. This allows us to
            /// deny some operations preventively.
            hub::base::access_flags access_flags;
            //////////////////////////////////////////////////////////////////////////////////////////////////////

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Frees the internal buffer, unless it is still pointing at the stack buffer.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void free_buffer();
        };
    }
}

#endif
