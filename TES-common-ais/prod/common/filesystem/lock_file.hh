//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file hub/filesystem/lock_file.hh
/// @ingroup hub_filesystem
/// @copyright Copyright (C) 2012
/// 
/// @brief A common class used to provide safe file locking semantics, even
/// over network file systems (like NFS).
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
///     2013-08-21    Dan Tascione <dtascion@rec.ri.cmu.edu>    Created file.
//////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HUB_FILESYSTEM_LOCK_FILE_H
#define HUB_FILESYSTEM_LOCK_FILE_H

#include <hub/base/common.hh>
#include <hub/base/shared_ptr.hh>

#include <filesystem/file.hh>

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Inside the shared filesystem namespace.
//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace hub
{
    namespace filesystem
    {
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This class allows you to create a lock file object somewhere
        /// on the file system. It properly handles NFS caching effects, allowing
        /// it to be used in multi-system setups.
        /// This class is by default scoped; when the object falls out of
        /// scope, the object is destroyed. Therefore, this class will do I/O
        /// at various points in time during its lifetime.
        /// In case you crash while holding the lock, a timestamp is provided in
        /// the lock file itself. If the timestamp is too old when another project
        /// tries to acquire the lock, the lock breaks instantly. This implies
        /// NTP or some other time synchronization system should be running.
        /// Because we use time, it is advisable to call 'update()' periodically
        /// to refresh the state of the file for long operations (operations over
        /// 10 seconds in length).
        /// Please note that when using the lock_file API over NFS, it may still
        /// be necessary to flush the attribute cache of the files you are operating
        /// on, to make sure they are consistent. In general, delay opening the
        /// files you will be working on until you have successfully acquired
        /// a lock.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        class export_object lock_file
        {
        public:

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Empty constructor. Initializes a file object with no path.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            lock_file();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Initializes a lock file with the given path. The file will
            /// be initially locked. This will cause file I/O operations when
            /// adding files to disk.
            /// If you specify an acquire timeout, that is how many seconds this
            /// lock file will wait to attempt to acquire the lock. If it cannot
            /// acquire it within that timeout, it exits. Specifying -1 here
            /// indicates you wish to block forever.
            /// The reap timeout specifies the age of a lock file before it is
            /// destroyed and "broken".
            /// This construct can throw exceptions, if there is some low level
            /// file system error, or if the lock fails to acquire.
            ///
            /// @param[in] lock_base_path lock file path
            /// @param[in] acquire_timeout timeout to wait to acquire the lock
            /// @param[in] reap_timeout  age of a lock file before it is destroyed
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            lock_file (
                        const path &lock_base_path,
                        double acquire_timeout = -1.0,
                        double reap_timeout = 60.0
                      );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Destructor. Unlocks the file, if it is still locked.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            ~lock_file();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Check if file is locked
            ///
            /// @return true if this file is locked, false otherwise.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            bool is_locked() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Unlocks this lock file. This will cause file I/O when removing
            /// files from the disk.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void unlock();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief If this file is locked, this will refresh it, allowing you to
            /// make it known that you still hold the lock, to all other lock
            /// files attempting to reap it.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void refresh_lock();

        private:
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief The base path of the lock file.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            file base_path;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Locks this file, creating all necessary paths and files, and
            /// filling in the file with the latest timestamp.
            /// If you specify an acquire timeout, that is how many seconds this
            /// lock file will wait to attempt to acquire the lock. If it cannot
            /// acquire it within that timeout, it exits.
            /// The reap timeout specifies the age of a lock file before it is
            /// destroyed and "broken".
            ///
            /// @param[in] acquire_timeout timeout to wait to acquire the lock
            /// @param[in] reap_timeout  age of a lock file before it is destroyed
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void lock (
                        double acquire_timeout,
                        double reap_timeout
                      );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Looks at the lock, and understands if something has been holding
            /// it open for too long. If so, the lock is broken.
            ///
            /// @param[in] reap_timeout  age of a lock file before it is destroyed
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void try_break_lock (
                                  double reap_timeout
                                );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Refresh the path to a lockfile, updating timestamp
            ///
            /// @param[in] new_lock if true, create a new lock file, otherwise overwrite the existing one
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void refresh_path(bool new_lock=false);
        };

        typedef hub::base::shared_ptr<lock_file> lock_file_ptr;
    }
}

#endif
