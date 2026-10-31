//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file hub/filesystem/mapped_buffer.hh
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

#ifndef HUB_FILESYSTEM_mapped_buffer_H
#define HUB_FILESYSTEM_mapped_buffer_H

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
        /// @brief Implementation of a standard buffer object, but using memory mapped I/O.
        /// This can have some performance benefits over using a standard file_buffer,
        /// which uses emulated mapped I/O.
        /// The downside is that if you are seeking over an unstable medium (say, a disk that
        /// can be pulled), this class can cause crashes due to the nature of memory mapping.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        class export_object mapped_buffer : public hub::base::abstract_buffer
        {
        public:

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Initializes a file buffer based on the supplied file. This will attempt
            /// to open the file with the desired access rights.
            ///
            /// @param[in] target target file
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            mapped_buffer (
                          const file &target
                        );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Initializes a file buffer based on the supplied path. This will attempt
            /// to open the file with the desired access rights.
            ///
            /// @param[in] path target file path
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            mapped_buffer (
                          const std::string &path
                        );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Destructor. Unmaps and internal views and closes all open
            /// file handles.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            ~mapped_buffer();

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
            ///
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
            /// @return buffer size
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

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief The internal buffer. When we read file data, we actually read
            /// it into this buffer, to keep from hitting the disk too often.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            char *internal_buffer;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief The bytes actually present in the buffer.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            size_t buffer_available;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief The offset into the buffer of where we are reading.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            size_t buffer_offset;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief The position in the file, so when we read more data, we know where to read it at.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            uint64_t file_offset;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief A cached copy of the file size. Since this file is read only, this should be fine to cache.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            uint64_t file_size;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Caches allocation granularity, for our mmap calls.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            uint32_t allocation_granularity;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Initializes the buffer and files in default values. This is called from
            /// all of our constructors.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void initialize_buffer();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Unmaps the internal_buffer, if it was previously mapped. This also resets
            /// all buffer offset/availability information.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void unmap_buffer_pointer();
        };
    }
}

#endif
