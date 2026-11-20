///////////////////////////////////////////////////////////////////////////////
/// @attention Copyright (C) 2019 Caterpillar Inc.  All Rights Reserved.
/// @attention Caterpillar: Confidential Yellow
///
/// @file      file.cpp
/// @brief     Common file utilities
///
///////////////////////////////////////////////////////////////////////////////

#include "ROS2Logger.hpp"
#include "nvm_directory.h"
#include "file.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <filesystem/file.hh>
#include <filesystem/path.hh>
#include <hub/base/export.hh>
#include <hub/base/status_exception.hh>

#include "rclcpp/rclcpp.hpp"

namespace fs = boost::filesystem;
namespace nvm_fs = ros2_nvm::filesystem;

namespace ros2_nvm {
namespace filesystem {
namespace file {

export_object bool remove(const fs::path& filePath)
{
    // Delete file if it exists
    hub::filesystem::file file(filePath.string());
    try
    {
        file.remove_if_exists();
    }
    catch (const hub::base::status_exception & e)
    {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"file::remove: %s for filePath=%s", e.what(), file.c_str());
        return false;
    }
    return true;
}

export_object bool read(const boost::filesystem::path& filePath, std::stringstream& contents)
{
    if (!nvm_fs::file::exists(filePath))
    {
        RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"file::read: %s not found", filePath.c_str());
        return false;
    }

    fs::ifstream inFile;

    try
    {
        inFile.open(filePath, std::ios_base::in);

        if(!inFile.good())
        {
           RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"file::read: Unable to read %s", filePath.c_str());
        }
        else
        {
            contents.clear();
            contents << inFile.rdbuf();
            inFile.close();
            return true;
        }
    }
    catch (const fs::filesystem_error & e)
    {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"file::read: %s for filePath=%s", e.what(), filePath.c_str());
    }
    return false;
}

export_object bool read(const fs::path& filePath, std::string& contents)
{
    std::stringstream ss;
    if (read(filePath, ss))
    {
        contents = ss.str();
        return true;
    }
    return false;
}

export_object bool write(const fs::path& filePath, const std::string& contents, bool append)
{
    hub::filesystem::file file(filePath.string());

    if (append)
    {
        file.open_for_appending();
    }

    try
    {
        file.write_entirely(contents);
        return true;
    }
    catch (const hub::base::status_exception & e)
    {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"file::write: %s for filePath=%s", e.what(), file.c_str());
    }
    return false;
}

export_object bool write(const boost::filesystem::path& filePath, const std::vector<std::string>& contents, bool append)
{
    hub::filesystem::file file(filePath.string());

    try
    {
        if (append)
        {
            file.open_for_appending();
        }

        size_t bytes_written;
        std::string newLine{"\n"};
        for (auto& line : contents)
        {
            file.write(line.c_str(), line.size(), bytes_written);
            file.write(newLine.c_str(), newLine.size(), bytes_written);
        }

        file.flush();

        return true;
    }
    catch (const hub::base::status_exception & e)
    {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"file::write: %s for filePath=%s", e.what(), file.c_str());
    }
    return false;
}

export_object bool copy(const boost::filesystem::path &sourceFile, const boost::filesystem::path &dest, bool overwrite)
{
    try
    {
        RCLCPP_DEBUG(ROS2Logger::Instance().GetLogger(),"file::copy: sourceFile=%s dest=%s", sourceFile.c_str(), dest.c_str());
        hub::filesystem::path srcPath(sourceFile.string());
        hub::filesystem::path destPath(dest.string());
        // Confirm sourceFile exists
        if (!srcPath.exists() || !srcPath.is_regular_file())
        {
            RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"file::copy: Unable to find %s or is not a file", srcPath.c_str());
            return false;
        }

        // Check if dest is a dir or a file
        fs::path dstDir;
        hub::filesystem::path destDir;
        hub::filesystem::file destFile;
        if ((destPath.exists() && destPath.is_directory()) || (dest.string().back() == '/'))
        {
            dstDir = dest;
            destDir = destPath;
            destFile = hub::filesystem::file (destDir, srcPath.get_name());
            RCLCPP_DEBUG(ROS2Logger::Instance().GetLogger(),"file::copy: dest %s is assumed to be a directory, destFile is %s", destPath.c_str(), destFile.c_str());
        }
        else
        {
            RCLCPP_DEBUG(ROS2Logger::Instance().GetLogger(),"file::copy: dest %s is assumed to be a file", dest.c_str());
            dstDir = dest.parent_path();
            destDir = destPath.get_parent_path();
            destFile = hub::filesystem::file (destDir,destPath.get_name());
        }

        // Create dest directory if it doesn't exist
        if (!nvm_dir::create(dstDir))
        {
            RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"file::copy: Unable to create %s", dstDir.string().c_str());
            return false; 
        }

        // Copy the source to dest
        if (destFile.exists()) {
            if (!overwrite) {
                RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"file::copy: File already exists and is not to be overwritten!");
                return false;
            }
        }
        // Use boost::filesystem to preserve permissions
        fs::copy_file(sourceFile, destFile.str(), overwrite ? boost::filesystem::copy_option::overwrite_if_exists : boost::filesystem::copy_option::fail_if_exists);
        RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"file::copy: Copy of %s to %s successful", sourceFile.c_str(), destFile.c_str());
        return true;
    }
    catch (const hub::base::status_exception &e)
    {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"file::copy: %s for sourceFile=%s dest=%s", e.what(), sourceFile.c_str(), dest.c_str());
    }
    return false;
}

export_object bool exists(const boost::filesystem::path& filePath)
{
    hub::filesystem::file file(filePath.string());
    if (!file.exists() || file.is_directory())
    {
        RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"file::exists: %s not found", file.c_str());
        return false;
    }
    return true;
}

export_object bool areIdentical(const boost::filesystem::path& filePath1, const boost::filesystem::path& filePath2)
{
    bool result = false;
    hub::filesystem::file frstFile(filePath1.string());
    hub::filesystem::file secndFile(filePath2.string());
    char* frstFileMapMemAddrs = nullptr;
    char* scndFileMapMemAddrs = nullptr;
    try
    {
        if (!frstFile.exists() || frstFile.is_directory() || !secndFile.exists() || secndFile.is_directory())
        {
            RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"file::areIdentical: %s or %s not found", frstFile.c_str(), secndFile.c_str());
            return false;
        }
        frstFile.open();
        secndFile.open();
        frstFileMapMemAddrs = static_cast<char*>(frstFile.map_into_memory(0, frstFile.get_size()));
        scndFileMapMemAddrs = static_cast<char*>(secndFile.map_into_memory(0, secndFile.get_size()));

        result = (frstFile.get_size() == secndFile.get_size() && std::equal(frstFileMapMemAddrs, frstFileMapMemAddrs + frstFile.get_size(), scndFileMapMemAddrs));
    }
    catch(const hub::base::status_exception& e)
    {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"file::areIdentical: Error:%s", e.what());
    }
    hub::base::unmap_file_from_memory(frstFileMapMemAddrs, frstFile.get_size());
    hub::base::unmap_file_from_memory(scndFileMapMemAddrs, secndFile.get_size());
    frstFile.close();
    secndFile.close();
    return result;
}

}
}
}
