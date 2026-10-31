//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file hub/filesystem/file_transfer_pair.hh
/// @ingroup hub_filesystem
/// @copyright Copyright 2012
/// 
/// @brief A simple structure that allows you to define a file transfer
/// operation (typically, one file moving or copying to another).
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

#ifndef HUB_FILESYSTEM_FILE_TRANSFER_PAIR_H
#define HUB_FILESYSTEM_FILE_TRANSFER_PAIR_H

#include <hub/base/common.hh>
#include <hub/base/abstract_buffer.hh>

#include <filesystem/path.hh>

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Inside the shared filesystem namespace.
//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace hub
{
    namespace filesystem
    {
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This structure defines a pair of files that are involved in a
        /// simple operation (such as copying).
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        struct export_object file_transfer_pair
        {
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief The filename on the source.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            path source;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief The desired destination name.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            path destination;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Empty constructor.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            file_transfer_pair()
            {
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Convenience constructor.
            ///
            /// @param[in] desired_source path of source file
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            file_transfer_pair (
                                 const path &desired_source
                               )
                               :
                               source(desired_source),
                               destination(desired_source)
            {
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Convenience constructor.
            ///
            /// @param[in] desired_source path of soruce file
            /// @param[in] desired_destination path of destination file
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            file_transfer_pair (
                                 const path &desired_source,
                                 const path &desired_destination
                               )
                               :
                               source(desired_source),
                               destination(desired_destination)
            {
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Operator overloading for comparisons.
            ///
            /// @param[in] other file to be compared
            /// @return bool True if file_transfer_pair are the same; False otherwise
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            bool operator== (
                              const file_transfer_pair& other
                            ) const
            {
                return (
                         source == other.source &&
                         destination == other.destination
                       );
            }
        };

        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Defines a list of file transfer pairs.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        typedef std::vector<file_transfer_pair> file_transfer_pair_list;
    }
}

#endif
