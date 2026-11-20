///////////////////////////////////////////////////////////////////////////////
/// @attention Copyright (C) 2019 Caterpillar Inc.  All Rights Reserved.
/// @attention Caterpillar: Confidential Yellow
///
/// @file      file.h
/// @brief     Common file utilities
///
///////////////////////////////////////////////////////////////////////////////

#include <boost/filesystem.hpp>

namespace ros2_nvm {
namespace filesystem {
namespace file {

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reads the provide filePath to a string without throwing
    /// @param filePath boost::filesystem::path of the file
    /// @param contents filePath read into a string
    /// @return true if successful, false otherwise
    ///////////////////////////////////////////////////////////////////////////////
    bool read(const boost::filesystem::path& filePath, std::string& contents);

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reads the provide filePath to a string without throwing
    /// @param filePath boost::filesystem::path of the file
    /// @param contents filePath read into a stringstream
    /// @return true if successful, false otherwise
    ///////////////////////////////////////////////////////////////////////////////
    bool read(const boost::filesystem::path& filePath, std::stringstream& contents);

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Writes to the provide filePath from a string without throwing,
    /// @param filePath boost::filesystem::path of the file
    /// @param contents string to write to filePath
    /// @param append overwrites the existing content if false
    /// @return true if successful, false otherwise
    ///////////////////////////////////////////////////////////////////////////////
    bool write(const boost::filesystem::path& filePath, const std::string& contents, bool append = false);

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Writes to the provide filePath from a string without throwing,
    /// @param filePath boost::filesystem::path of the file
    /// @param contents string vector to write to filePath (each line separated by enter)
    /// @param append overwrites the existing content if false
    /// @return true if successful, false otherwise
    ///////////////////////////////////////////////////////////////////////////////
    bool write(const boost::filesystem::path& filePath, const std::vector<std::string>& contents, bool append = false);

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes the provided file without throwing
    /// @param filePath boost::filesystem::path of the file to delete
    /// @return true if successful or the file doesn't exist, false otherwise
    ///////////////////////////////////////////////////////////////////////////////
    bool remove(const boost::filesystem::path& filePath);

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Copies a single file to dest without throwing
    /// @param sourceFile source directory and file name of the file
    /// @param dest destination of the file. If dest is an existing directory or has no filename (ends in /),
    ///             it is assumed to be directory and is created if it doesn't exist. Otherwise it is assumed to be a file.
    /// @param overwrite true to overwrite the file, false otherwise
    /// @return true if successful, false otherwise
    /////////////////////////////////////////////////////////////////////////////////////////////////
    bool copy(const boost::filesystem::path &sourceFile, const boost::filesystem::path &dest, bool overwrite = true);

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Check if a file exists
    /// @param filePath boost::filesystem::path of the file to check
    /// @return true if the file exists, false otherwise
    ///////////////////////////////////////////////////////////////////////////////
    bool exists(const boost::filesystem::path& filePath);

    /////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Checks if two files are identical
    /// @param filePath1 first file
    /// @param filePath2 second file
    /// @return true if both files exist and are identical, false otherwise
    /////////////////////////////////////////////////////////////////////////////////////////////////
    bool areIdentical(const boost::filesystem::path& filePath1, const boost::filesystem::path& filePath2);
}
}
}