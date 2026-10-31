//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file hub/filesystem/path.hh
/// @ingroup hub_filesystem
/// @copyright Copyright 2012
///  
/// @brief This class manages paths. It allows you to construct child paths,
/// checks for their existence, and to manipulate them.
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
///     2012-10-28    Dan Tascione <dtascion@rec.ri.cmu.edu>    Created file.
//////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HUB_FILESYSTEM_PATH_H
#define HUB_FILESYSTEM_PATH_H

#include <hub/base/common.hh>

#include <hub/base/platform/filesystem.hh>

#include <sstream>
#include <vector>

#include <sys/stat.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Inside the shared filesystem namespace.
//////////////////////////////////////////////////////////////////////////////////////////////////////
namespace hub
{
    namespace filesystem
    {
        /// Files can return lists of children. They are returned with this type.
        typedef std::vector<hub::base::directory_entry> directory_entry_list;

        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief The path class is built around managing paths in the system (whether
        /// they point to files or directories).
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        class export_object path
        {
        public:

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Empty constructor. Initializes an empty path object.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            path();

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Constructor. Initializes a new path object to the specified
            /// path.
            /// 
            /// @param[in] source source path
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            path (
                   const std::string &source
                 );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Copy constructor.
            ///
            /// @param[in] other path to be copied
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            path (
                   const path &other
                 );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Constructor. Initializes a new path object to the specified
            /// path.
            /// 
            /// @param[in] source source path
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            path (
                   const char *source
                 );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Constructor. Initializes a new path object to a path that
            /// includes the two path objects appended to each other.
            /// 
            /// @param[in] parent  parent source path
            /// @param[in] child   child source path
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            path (
                   const path &parent,
                   const path &child
                 );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Get the size of the file as reported on disk.
            ///
            /// @return the size of this file, in bytes. 
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            uint64_t get_size() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Check if file exists
            ///
            //// @return true, if this file exists, false otherwise.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            bool exists() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief This will fill in bits of information (such as modification times, size, type) 
            /// from the file system.
            ///
            /// @return file status
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            hub::base::path_status get_status() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief This API will actually
            /// query the underlying filesystem to determine this, so it may block. It
            /// is simply a helper method built on top of get_status().
            ///
            /// @return true if this path points to a directory.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            bool is_directory() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief This API will actually
            /// query the underlying filesystem to determine this, so it may block. It
            /// is simply a helper method built on top of get_status().
            ///
            /// @return true if this path points to a file.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            bool is_regular_file() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief This API will
            /// try to guess if the path is absolute or not, as it might not exist
            /// on the filesystem yet. On Unix platforms, this might mean that the
            /// path begins with a slash, whereas on Windows, it would mean that the
            /// path specifes a drive letter.
            ///
            /// @return true if the path is an absolute path to file.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            bool is_absolute_path() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief If this path is a relative
            /// path, then this will return the full pathname. This relies on the base
            /// operating system to do the path resolution, and so it may block.
            ///
            /// @return the absolute path for this path.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            path get_absolute_path() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief This api get absolute path if it exists 
            ///
            /// @return the absolute path for this path, if it exists. If the path does
            /// not exist, then this will simply return this path, unresolved.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            path get_absolute_path_if_exists() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Get a relative path to this path, based on the other path. For example,
            /// if your path is /abc/dir1/output.txt, and the other path is /abc/dir2/output.txt,
            /// this will return ../dir1/output.txt.
            ///
            /// @return relative path to this path
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            path get_relative_path_from_path (
                                               const path &other
                                             ) const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Get parent path In other words, if your path is
            /// something like /etc/passwd, this will return /etc.
            ///
            /// @return the parent path for this path
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            path get_parent_path() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Finds the name for this path. This will be the last element in the
            /// path with a name (the opposite of get_parent_path). If there are no
            /// elements in the path, or just a single element, this will return a
            /// copy of the current path (essentially a no-op).
            ///
            /// @return path of the last element in the path, if there are no elements return current path
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            path get_name() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Get name of path, as if you called get_name(). If the name
            /// has an extension, that extension will be stripped off before being
            /// returned. For example, if you specify "/abc/output.txt", this will
            /// return the string "output".
            ///
            /// @return  the name of this path
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            std::string get_name_without_extension() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief  Get extension of this path
            ///
            /// @return the extension for this path, assuming it has one. If it doesn't,
            /// this will return an empty string. An extension is defined as everything
            /// from the final period in the path forward.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            std::string get_extension() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Resolves this path, replacing all instances of '.' and '..' with the
            /// appropriate directory layout. Consider using get_absolute_path() instead,
            /// as that will also resolve the '.' and '..' members.
            /// This API is useful for when you absolutely do not want to do any system
            /// calls, and instead want to resolve the path algorithmically.
            ///
            /// @return absolute path
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            path resolve_path() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Check if path is empty
            ///
            /// @return true if this path is empty (not set). This will be true
            /// if the path has no characters.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            bool empty() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Get path in string format
            ///
            /// @return the full path object, in string form.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            const std::string& str() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Get path in C-style string
            ///
            /// @return the full path object, as if it was a C-style string.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            const char* c_str() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Touches the file. If it does not yet exist, this will create it. It will
            /// contain zero bytes, initially. This only works if the file is closed; otherwise,
            /// it will throw an error.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void touch() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Changes the owner of the path to the specified username. This is platform-specific
            /// in how this will work (and how the username will be interpretted). Note that simply
            /// changing the owner may not be enough to grant access to a file, depending on how
            /// permissions on that file are set.
            ///
            /// @param[in] username user name
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void change_owner (
                                const std::string &username
                              ) const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Renames this file to the specified target. Follows the same rules as a conventional
            /// rename() on your operating system.
            ///
            /// @param[in] target new file destination
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void move (
                        const hub::filesystem::path &target
                      ) const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Deletes the path pointed to by this file. Throws an error if this
            /// file does not exist.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void remove() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Deletes the path pointed to by this file, if it exists. If it does
            /// not exist, this throws no error.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void remove_if_exists() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Removes all of the files in the given path, recursively, if they
            /// appear to exist. Also removes itself if self_remove_dir is set.
            ///
            /// @param[in] self_remove_dir true the remove itself, false otherwise
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void remove_recursively(bool self_remove_dir = true) const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Creates all of the directories (recursively, if necessary) that are
            /// represented by this path. This assumes that the entire path is a
            /// directory.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void make_directories() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Creates all of the parent directories of this file. This assumes the
            /// file is a filename, rather than a directory, as make_directories() does.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            void make_parent_directories() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Enumerate all child files.
            /// 
            /// @return a list of child files. If the given file is a directory,
            /// this will enumerate all of the immediately accessible children, and then
            /// return their names in a list.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            directory_entry_list enumerate_children() const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Change directory permissions to desired value
            ///
            /// @return true if success, false otherwise
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            bool change_permissions(std::string) const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Operator overloading for assignment.
            ///
            /// @param[in] other path to be copied
            /// @return copied path
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            path& operator= (
                              const path &other
                            );

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Operator overloading for comparisons.
            ///
            /// @param[in] other path to be compared
            /// @return true if path is smaller, false otherwise
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            bool operator< (
                             const path &other
                           ) const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Operator overloading for comparisons.
            ///
            /// @param[in] other path to be compared
            /// @return true if path is bigger, false otherwise
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            bool operator> (
                             const path &other
                           ) const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Operator overloading for comparisons.
            ///
            /// @param[in] other path to be compared
            /// @return true if path are equal, false otherwise
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            bool operator== (
                              const path &other
                            ) const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Operator overloading for comparisons.
            ///
            /// @param[in] other path to be compared
            /// @return true if path are different, false otherwise
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            bool operator!= (
                              const path &other
                            ) const;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Operator overloading for concatenating files.
            ///
            /// @param[in] other path to be concatenated
            /// @return concatenated path
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            path operator/ (
                             const path &other
                           ) const;

        private:
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief The full path of this file.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            std::string source_path;

            //////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @brief Normalizes the given path, removing any extra slashes in the string.
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            std::string normalize_path (
                                         const std::string &path
                                       ) const;
        };

        typedef std::vector<path> path_list;

        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Operator overload for paths, so that they can be used with the
        /// stringstream class without having to put in that extra .str()
        /// call.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        export_object std::ostream& operator<< (
                                                 std::ostream &out,
                                                 const path &other
                                               );

        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Get list of paths that was split from a string. This
        /// string is typically a colon-separated list of paths, such as an
        /// include path, or path variable list.
        ///
        /// @return list of paths
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        export_object path_list split_path_list (
                                                  const std::string &path_list
                                                );
    }
}

#endif
