//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file hub/filesystem/journaled_file.hh
/// @ingroup hub_filesystem
/// @copyright Copyright (C) 2012
///  
/// @brief A journaled file is a file object that allows you to open (or restore
/// contents in a fashion that should be safe, even in power loss.
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
///     2012-10-30    Dan Tascione <dtascion@rec.ri.cmu.edu>    Created file.
//////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HUB_FILESYSTEM_JOURNALED_FILE_H
#define HUB_FILESYSTEM_JOURNALED_FILE_H

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
        /// @brief This class allows you to read and write files in a journaled
        /// fashion. That is, it will write to a side file first, and then once
        /// the disk has reported it is safe, move the file to its new location.
        /// This allows you to safely do file I/O without needing to worry about
        /// what happens if the power goes out halfway through a file write.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        class export_object journaled_file : public file
        {
        public:

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Empty constructor. Initializes a file object with no path.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            journaled_file();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Constructor. Initializes a new file object to the specified
            /// path.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            journaled_file (
                             const path &path
                           );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Destructor. Commits any remaining changes before exiting.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            virtual ~journaled_file();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Opens this file. If the file is already open, this will throw an
            /// exception. If you let this file object fall out of scope, and the
            /// file is left open, then the file will be closed automatically.
            /// If this file is a directory, or if it does not exist, then this
            /// routine will most likely fail (depending on the host operating
            /// system).
            /// This open routine may do a journal recovery, depending on the state
            /// that the journaled file was left in.
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
            /// @brief Closes this file. If the file is not open, this will throw an exception.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            virtual void close();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Operator overloading for comparisons.
            //
            /// @param[in] other journaled_file to be compared
            /// @return bool True if journaled_files are the same; False otherwise
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            bool operator== (
                              const journaled_file& other
                            ) const;

        private:

            /// The access flags that this file was last opened with.
            hub::base::access_flags access_flags;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Get the path to the journal file for this journaled file. This may
            /// or may not exist.
            /// 
            /// @return path to the journal file
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            hub::filesystem::path get_journal_path() const;
        };
    }
}

#endif
