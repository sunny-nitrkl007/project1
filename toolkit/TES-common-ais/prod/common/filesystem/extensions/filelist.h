///////////////////////////////////////////////////////////////////////////////
/// @attention Copyright (C) 2019 Caterpillar Inc.  All Rights Reserved.
/// @attention Caterpillar: Confidential Yellow
///
/// @file      filelist.h
/// @brief     Common file utilities
///
///////////////////////////////////////////////////////////////////////////////

#ifndef NVM_FILESYSTEM_FILELIST_H_
#define NVM_FILESYSTEM_FILELIST_H_

#include <boost/filesystem.hpp>

namespace ros2_nvm {
namespace filesystem {
namespace filelist {

    using FileList = std::vector<std::string>;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Gets a list of files from the file in the provided location
    /// @param fileListLocation boost::filesystem::path of the list of files
    /// @return Contents of fileListLocation, with comments (#) and blank lines excluded
    ///////////////////////////////////////////////////////////////////////////////
    FileList get(const boost::filesystem::path& fileListLocation);

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes a list of files from the file in the provided filePath
    /// @param fileList List of files/directories to be deleted. The "*" wildcard is
    ///        supported for files.
    /// @return list of the deleted files and dirs
    ///////////////////////////////////////////////////////////////////////////////
    FileList remove(const FileList& fileList);

    }
}
}

#endif
