#pragma once

#include <string>
#include <hub/base/export.hh>
#include <filesystem/path.hh>
#include <boost/filesystem.hpp>

#ifndef NVM_FILESYSTEM_DIR_H_
#define NVM_FILESYSTEM_DIR_H_


namespace ros2_nvm {
namespace filesystem {
namespace nvm_dir {

using PathList = std::vector<hub::filesystem::path>;

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Creates a string containing the full file path.
/// @param[in] path path/directory
/// @param[in] fileName file name
/// @return path / filename in a string
/////////////////////////////////////////////////////////////////////////////////////////////////
export_object inline std::string makeFilePath(const boost::filesystem::path &path, const std::string &fileName) { return (path / fileName).string(); }

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Creates the provided path in the file system
/// @param[in] path path/directory to be created
/// @param[in] perms file permissions flags, defaults to 0x755
/// @return true if successful, false otherwise
/////////////////////////////////////////////////////////////////////////////////////////////////
export_object bool create(const boost::filesystem::path &path, boost::filesystem::perms perms = boost::filesystem::perms::all_all ^ boost::filesystem::perms::group_write ^ boost::filesystem::perms::others_write);

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Copies all files and folders in the source to dest.
/// @param[in] source source directory of the files
/// @param[in] dest destination directory of the files
/// @param[in] overwrite true to overwrite a file if it is found, false otherwise (defaults to true) 
/// @return true if successful, false otherwise
/////////////////////////////////////////////////////////////////////////////////////////////////
bool copy(const boost::filesystem::path &source, const boost::filesystem::path &dest, bool overwrite = true);

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Moves all files and folders in the source to dest.
/// @param[in] source source directory of the files
/// @param[in] dest destination directory of the files
/// @return true if successful, false otherwise
/////////////////////////////////////////////////////////////////////////////////////////////////
bool move(const boost::filesystem::path &source, const boost::filesystem::path &dest);

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Deletes all contents in the provided path without deleting the path itself
/// @param[in] path path/directory to be cleared
/// @return true if successful, false otherwise
/////////////////////////////////////////////////////////////////////////////////////////////////
bool clear(const boost::filesystem::path &path);

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Deletes all contents in the provided path and the path itself
/// @param[in] path path/directory to be deleted
/// @return true if successful, false otherwise
/////////////////////////////////////////////////////////////////////////////////////////////////
bool remove(const boost::filesystem::path &path);

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Get a list of all files in the path that match the provided fileExtension.
///        Does not recursively search through the path
/// @param[in] path path/directory to search
/// @param[out] files list of full file paths of all files in path that end in fileExtension. Any existing contents will be cleared.
/// @param[in] fileExtension fileExtension to search for. If empty, all files will be returned. Wildcards are not supported.
/// @return true if successful, false otherwise
/////////////////////////////////////////////////////////////////////////////////////////////////
bool getFilePaths(const boost::filesystem::path &path, PathList& files, const std::string& fileExtension = "");

}
}
}

#endif
