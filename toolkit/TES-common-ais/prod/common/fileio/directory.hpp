#pragma once

#include <string>
#include <exception>
#include <boost/filesystem.hpp>

#include <ais/log/AisLogger.h>

#ifndef FILEIO_DIRECTORY_HPP
#define FILEIO_DIRECTORY_HPP

namespace tes_common_ais
{
namespace directory
{
namespace fs = boost::filesystem;

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @Create a string containing the full file path.  
/////////////////////////////////////////////////////////////////////////////////////////////////
inline std::string makeFilePath(const fs::path &path, const std::string &fileName) { return (path / fileName).string(); }

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @Create the provided path in NVM.  
///  Returns true if successful, false otherwise
/////////////////////////////////////////////////////////////////////////////////////////////////
inline bool create(const fs::path &path) {
    bool ret_val = false;
    try {
        if (!fs::exists(path) || !fs::is_directory(path)) {  // Check if the directory already exists
            fs::create_directories(path);
            AIS_LOG_NOTICE("path created: %s", path.string().c_str());
            ret_val = true;
        }
        ret_val = true;
    }
    catch (const fs::filesystem_error &e) {
        AIS_LOG_ERROR(e.what());
    }
    return ret_val;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @Copies all files and folders in the source to dest.  
///  Returns true if successful, false otherwise
/////////////////////////////////////////////////////////////////////////////////////////////////
inline bool copy(const fs::path &source, const fs::path &dest) {
    try {
        if (create(dest)) {
            if (fs::exists(source) && fs::is_directory(source)) {
                // Iterate through the source directory
                fs::directory_iterator file(source);
                for (fs::directory_iterator file(source); file != fs::directory_iterator(); ++file) {
                    try {
                        fs::path current(file->path());
                        if (fs::is_directory(current)) {
                            // Found directory: Recursion
                            if (!tes_common_ais::directory::copy(current, dest / current.filename())) {
                                return false;
                            }
                        }
                        else {
                            // Found file: Copy
                            fs::copy(current, dest / current.filename());
                        }
                    }
                    catch (fs::filesystem_error const & e){
                        std::cerr << e.what() << '\n';
                    }
                }
                return true;
            }
            else {
                AIS_LOG_ERROR("Unable to find %s", source.c_str());
            }
        }
        else {
            AIS_LOG_ERROR("Unable to create %s", dest.c_str());
        }
    }
    catch (const fs::filesystem_error &e) {
        AIS_LOG_ERROR(e.what());
    }
    return false;
}

} // namespace directory
}; // namespace tes_common_ais

#endif // FILEIO_DIRECTORY_HPP