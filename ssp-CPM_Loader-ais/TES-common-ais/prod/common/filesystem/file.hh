//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @copyright hub/filesystem/file.hh
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
///     2012-04-01    Dan Tascione <dtascion@rec.ri.cmu.edu>    Created file.
/// 
//////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HUB_FILESYSTEM_FILE_H
#define HUB_FILESYSTEM_FILE_H

#include <hub/base/common.hh>

#include <hub/base/platform/filesystem.hh>

#include <hub/base/status_exception.hh>
#include <hub/base/abstract_buffer.hh>
#include <hub/base/lexical_cast.hh>
#include <hub/base/access_flags.hh>

#include <filesystem/path.hh>

#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Inside the shared filesystem namespace.
//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace hub
{
    namespace filesystem
    {
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief The file class is a nice method for opening files and doing
        /// random (or memory mapped) I/O on them. It will automatically
        /// handle copy constructors and releasing resources when the object
        /// goes out of scope.
        /// File is built on the path object, extending it with I/O routines.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        class export_object file : public path
        {
        public:

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Empty constructor. Initializes a file object with no path.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            file();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Constructor. Initializes a new file object to the specified
            /// path.
            ///
            /// @param[in] path file path
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            file (
                   const path &path
                 );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Constructor. Initializes a new file object to the specified
            /// path, formed by appending child to parent.
            ///
            /// @param[in] parent parent file path
            /// @param[in] child child file path
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            file (
                   const path &parent,
                   const path &child
                 );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Copy constructor.
            ///
            /// @param[in] other file to be copied
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            file (
                   const file &other
                 );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Destructor. Closes any remaining open files and frees resources
            /// associated with this object.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            virtual ~file();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Opens this file. If the file is already open, this will throw an
            /// exception. If you let this file object fall out of scope, and the
            /// file is left open, then the file will be closed automatically.
            /// If this file is a directory, or if it does not exist, then this
            /// routine will most likely fail (depending on the host operating
            /// system).
            ///
            /// @param[in] flags access flags
            /// @param[in] disposition open disposition flags
            /// @param[in] behavior caching behavior flags
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            virtual void open (
                                hub::base::access_flags flags = hub::base::access_read,
                                hub::base::open_disposition disposition = hub::base::disposition_default,
                                hub::base::caching_behavior behavior = hub::base::caching_behavior_default
                              );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Opens this file in append mode. That is, you can write to the file, and you
            /// will write to the end of the file. If the file does not currently exist,
            /// it will be created.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            virtual void open_for_appending();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Closes this file. If the file is not open, this will throw an exception.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            virtual void close();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Reads a block of data into the given buffer (at most, size bytes).
            /// The amount of bytes actually read (which may be zero!) is returned in
            /// the bytes_read parameter.
            ///
            /// @param[out] destination pointer to output storage buffer
            /// @param[in] destination_size destination buffer size
            /// @param[out] bytes_read number of bytes read
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void read (
                        void *destination,
                        size_t destination_size,
                        size_t &bytes_read
                      );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Writes a block of data into the given buffer (at most, size bytes).
            /// The amount of bytes actually written (which may be zero!) is returned
            /// in the bytes_written parameter.
            ///
            /// @param[in] source pointer to buffer with data to write
            /// @param[in] source_size size of data to write
            /// @param[out] bytes_written number of bytes written
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void write (
                         const void *source,
                         size_t source_size,
                         size_t &bytes_written
                       );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Reads the given filename into a target string, and returns a copy
            /// of it. Consider using read_entirely() with a reference for performance
            /// critical situations.
            ///
            /// @return string with read data
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            std::string read_entirely();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Reads the given filename into the target string, completely.
            //
            /// @param[out] destination string with read data
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void read_entirely (
                                 std::string &destination
                               );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Reads the given filename into the target buffer, completely.
            /// Leaves the buffer position at the *start* of the content that was just loaded.
            /// This allows you to read_file() and then read a buffer, without any odd seeks.
            //
            /// @param[out] destination buff with read data
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void read_entirely (
                                 hub::base::abstract_buffer &destination
                               );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Reads the given file into the specific type. This is useful for when
            /// you know the file contains, say, a single number, and you want to read
            /// and cast that to that type in one line.
            ///
            /// @return read data in _return_type type
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            template<typename _return_type>
            _return_type read_entirely()
            {
                return hub::base::lexical_cast<_return_type>(read_entirely());
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Reads the given file into the specific type. This is useful for when
            /// you know the file contains, say, a single number, and you want to read
            /// and cast that to that type in one line.
            /// If there is an error reading (say, the file is empty) or converting (the
            /// type is not the type you expected), then the default value you supplied will
            /// be returned instead.
            ///
            /// @param[in] value default value to be returned
            /// @return read data in _return_type type if data read succesfully, value otherwise
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            template<typename _return_type>
            _return_type read_entirely_or_use_default (
                                                        const _return_type &value
                                                      )
            {
                /// We just check to see if there is an exception. If so, then we return
                /// the default value they passed in.
                try
                {
                    return hub::base::lexical_cast<_return_type>(read_entirely());
                }
                catch(const hub::base::status_exception&)
                {
                    return value;
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Writes the given content to this file, in its entirety. This will throw an exception
            /// if anything goes wrong during this process (including writing an insufficient amount
            /// of data out).
            ///
            /// @param[in] content content to be written
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void write_entirely (
                                  const std::string &content
                                );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Writes the given content to this file, in its entirety. This will throw an exception
            /// if anything goes wrong during this process (including writing an insufficient amount
            /// of data out).
            ///
            /// @param[in] source pointer to buffer to be written
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void write_entirely (
                                  hub::base::abstract_buffer &source
                                );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Writes the given content to this file, in its entirety. This will throw an exception
            /// if anything goes wrong during this process (including writing an insufficient amount
            /// of data out).
            //
            /// @param[in] data pointer to buffer with data to write
            /// @param[in] data_size size of data to write
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void write_entirely (
                                  const void *data,
                                  size_t data_size
                                );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Seeks to the given position (based on the direction specified) in this file.
            ///
            /// @param[in] direction direction to seek from: seek_start, seek_current or seek_end
            /// @param[in] offset offset from the seek direction
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void seek (
                        hub::base::seek_direction direction,
                        uint64_t offset
                      );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Get the current position of the read/write cursor for this file, as offset
            /// from the beginning of the file.
            ///
            /// @return current position
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            uint64_t get_position();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Truncates the given file to the specified size. This may decrease the size
            /// of the file, or expand it.
            ///
            /// @param[in] new_size new file size
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void set_file_size (
                                 uint64_t new_size
                               );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Flushes the given file, synchronzing its contents out to disk. This could
            /// block for some time, depending on the host operating system.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void flush();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Locks a range of bytes in this file. If you supply zero for length,
            /// then the entire file will be locked. The length may extend past
            /// the current file length.
            /// This API may be an exclusive lock on some operating systems, and on
            /// others it might be only advisory.
            ///
            /// @param[in] offset start position
            /// @param[in] size number of bytes to be locked
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void lock (
                        uint64_t offset = 0,
                        uint64_t size = 0
                      );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Unlock a range of bytes in this file.  If you supply zero
            /// for the length, then the entire file will be unlocked.
            ///
            /// @param[in] offset start position
            /// @param[in] size number of bytes to be unlocked
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void unlock (
                          uint64_t offset = 0,
                          uint64_t size = 0
                        );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Maps a view of this file into the active address space. Starts at the
            /// specified offset and goes on for size bytes. Pages are mapped with this
            /// file's declared access rights.
            /// When you are done with this view, make sure you unmap it.
            ///
            /// @param[in] offset start position
            /// @param[in] size number of bytes to be mapped
            /// @return a pointer to mapped page
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void *map_into_memory (
                                    uint64_t offset,
                                    uint64_t size
                                  );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Unmaps the view of memory at the given address. This must be called for every
            /// mapping you created with map_into_memory, and it must be called before you
            /// closing this parent handle. Mapped views are not cleaned up automatically.
            ///
            /// @param[in] address pointer to start address
            /// @param[in] size number of bytes to be unmapped
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void unmap_from_memory (
                                     void *address,
                                     uint64_t size
                                   );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Assignment operator. We need to do this to handle the case of copying
            /// an open file.
            ///
            /// @param[in] other file to be copied
            /// @return copied file
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            file& operator= (
                              const file &other
                            );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Operator overloading for comparisons.
            //
            /// @param[in] other file to be compared
            /// @return bool True if files are the same; False otherwise
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            bool operator== (
                              const file& other
                            ) const;

        protected:

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Is this file open (or do we at least think it is open)?
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            bool is_file_open;
            

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief A file handle, which is used for managing reads and writes.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            hub::base::file_handle handle;
        };
    }
}

#endif
