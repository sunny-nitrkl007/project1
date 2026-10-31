#pragma once

#include <algorithm>
#include <string>
#include <exception>
#include <boost/filesystem.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "ROS2Logger.hpp"
#include "rclcpp/rclcpp.hpp"

#include "nvm_directory.h"
#include "sha1_fstream.hpp"

#ifndef NVM_FILESYSTEM_NVM_H
#define NVM_FILESYSTEM_NVM_H

namespace ros2_nvm {
namespace filesystem {
namespace file {

///////////////////////////////////////////////////////////////////////////////////////////////////
/// @Loads the nvmData object from NVM using two copy SHA-1.
///  Returns true if successful, false otherwise.
///  nvmData must either be POD or implement boost::serialize.
//////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline bool read(const boost::filesystem::path &path, const std::string &fileName, T &nvmData) {
    bool success = false;

    if (!fs::is_directory(path)) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: %s is not a directory", path.c_str());
        return success;
    }

    std::string filePath = nvm_dir::makeFilePath(path, fileName);

    sha1_ifstream ifs{true}; // Two copy
    ifs.open(filePath, std::ios_base::in | std::ios_base::binary);
    if (ifs) {
        // Read the file in
        try {
            boost::archive::binary_iarchive ia(ifs);
            ia &nvmData;
            RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: Successfully loaded the data from %s", filePath.c_str());
            success = true;
        }
        catch (const boost::archive::archive_exception &e) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: %s for filePath=%s", e.what(), filePath.c_str());
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Exception: %s",e.what());
        }
        catch (const std::exception &e) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: %s for filePath=%s", e.what(), filePath.c_str());
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Exception: %s",e.what());
        }
        catch (...) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: Unexpected error for filePath=%s", filePath.c_str());
        }
        ifs.close();
        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: %s was corrupt... fixed it.", filePath.c_str());
            } else {
                RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: %s was corrupt... could not fix it.", filePath.c_str());
            }
        }
    }
    else {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: %s could not be opened from storage.", filePath.c_str());
    }
    return success;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @Saves the provided nvmData to NVM using two copy SHA-1.
///  Returns true if successful, false otherwise.
///  nvmData must either be POD or implement boost::serialize.  It may also not be a literal.
/////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline bool store(const boost::filesystem::path &path, const std::string &fileName, const T &nvmData) {
    bool success = false;

    if (!nvm_dir::create(path)) {
        return success;
    }
    
    std::string filePath = nvm_dir::makeFilePath(path, fileName);

    sha1_ofstream ofs{true};  // Two copy
    ofs.open(filePath, std::ios_base::out | std::ios_base::binary);
    if (ofs) {
        // Write to the file
        try {
            boost::archive::binary_oarchive oa(ofs);
            oa &nvmData;
            RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"ros2_nvm::store: Successfully saved the data to %s", filePath.c_str());
            success = true;
        }
        catch (const boost::archive::archive_exception &e) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::store: %s for filePath=%s", e.what(), filePath.c_str());
        }
        catch (const std::exception &e) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::store: %s for filePath=%s", e.what(), filePath.c_str());
        }
        catch (...) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::store: Unexpected error for filePath=%s", filePath.c_str());
        }
        ofs.close();
    }
    else {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::store: %s could not be saved", filePath.c_str());
    }
    return success;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// @Loads the nvmData objects from NVM using two copy SHA-1.
///  Returns true if successful, false otherwise.
///  nvmData objects must either be POD or implement boost::serialize.
//////////////////////////////////////////////////////////////////////////////////////////////////
template <typename First, typename... Rest>
static bool read(const boost::filesystem::path& path, const std::string& fileName, First&& first, Rest&&... rest) {
    bool success = false;

    if (!fs::is_directory(path)) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: %s is not a directory", path.c_str());
        return success;
    }

    std::string filePath = nvm_dir::makeFilePath(path, fileName);

    sha1_ifstream ifs{true}; // Two copy
    ifs.open(filePath, std::ios_base::in | std::ios_base::binary);
    if (ifs) {
        // Read the file in
        try {
            boost::archive::binary_iarchive ia(ifs);
            ia & std::forward<First>(first);
            using expander = int[];
            (void)expander{0, (void(ia & std::forward<Rest>(rest)), 0)...};
            RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: Successfully loaded the data from %s", filePath.c_str());
            success = true;
        }
        catch (const boost::archive::archive_exception &e) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: %s for filePath=%s", e.what(), filePath.c_str());
        }
        catch (const std::exception &e) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: %s for filePath=%s", e.what(), filePath.c_str());
        }
        catch (...) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: Unexpected error for filePath=%s", filePath.c_str());
        }
        ifs.close();
        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: %s was corrupt... fixed it.", filePath.c_str());
            } else {
                RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: %s was corrupt... could not fix it.", filePath.c_str());
            }
        }
    }
    else {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::read: %s could not be opened from storage.", filePath.c_str());
    }
    return success;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @Saves the provided nvmData objects to NVM using two copy SHA-1.
///  Returns true if successful, false otherwise.
///  nvmData objects must either be POD or implement boost::serialize.  They may also not be a literal.
/////////////////////////////////////////////////////////////////////////////////////////////////
template <typename First, typename... Rest>
static bool store(const boost::filesystem::path& path, const std::string& fileName, First&& first, Rest&&... rest) {
    bool success = false;

    if (!nvm_dir::create(path)) {
        return success;
    }

    std::string filePath = nvm_dir::makeFilePath(path, fileName);

    sha1_ofstream ofs{true};  // Two copy
    ofs.open(filePath, std::ios_base::out | std::ios_base::binary);
    if (ofs) {
        // Write to the file
        try {
            boost::archive::binary_oarchive oa(ofs);
            oa & std::forward<First>(first);
            using expander = int[];
            (void)expander{0, (void(oa & std::forward<Rest>(rest)), 0)...};
            RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"ros2_nvm::store: Successfully saved the data to %s", filePath.c_str());
            success = true;
        }
        catch (const boost::archive::archive_exception &e) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::store: %s for filePath=%s", e.what(), filePath.c_str());
        }
        catch (const std::exception &e) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::store: %s for filePath=%s", e.what(), filePath.c_str());
        }
        catch (...) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::store: Unexpected error for filePath=%s", filePath.c_str());
        }
        ofs.close();
    }
    else {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ros2_nvm::store: %s could not be saved", filePath.c_str());
    }
    return success;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @Returns the number of nvm records stored in the provided path
///  Assumes that the path only contains nvm records and they are properly formed with 4 files each
/////////////////////////////////////////////////////////////////////////////////////////////////
export_object uint32_t count(const boost::filesystem::path &path);

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @Deletes the oldest nvm records stored in the provided path
///  Assumes that the path only contains nvm records and they are properly formed with 4 files each
/////////////////////////////////////////////////////////////////////////////////////////////////
export_object bool deleteOldest(const boost::filesystem::path &path);

}
}
}

#endif
