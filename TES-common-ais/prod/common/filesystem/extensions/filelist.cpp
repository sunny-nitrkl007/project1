///////////////////////////////////////////////////////////////////////////////
/// @attention Copyright (C) 2019 Caterpillar Inc.  All Rights Reserved.
/// @attention Caterpillar: Confidential Yellow
///
/// @file      filelist.cpp
/// @brief     Common file utilities
///
///////////////////////////////////////////////////////////////////////////////

#include "ROS2Logger.hpp"
#include <boost/algorithm/string/trim.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>

#include "rclcpp/rclcpp.hpp"
#include <ais/util/taskUtils.hpp>
#include <hub/base/export.hh>
#include <hub/utility/string.hh>

#include "file.h"
#include "filelist.h"

namespace ros2_nvm {
namespace filesystem {
namespace filelist {

namespace fs = boost::filesystem;
namespace nvm_fs = ros2_nvm::filesystem;

///////////////////////////////////////////////////////////////////////////////
/// @brief Gets a list of files from the file in the provided location
/// @param fileListLocation boost::filesystem::path of the list of files
/// @return Contents of fileListLocation, with comments (#) and blank lines excluded
///////////////////////////////////////////////////////////////////////////////
export_object FileList get(const boost::filesystem::path& fileListLocation)
{
    FileList fileList;
    std::stringstream fileContents;

    if (file::read(fileListLocation, fileContents))
    {
        std::string filePath;
        auto homeDir = getHomeDirectory();
        while (std::getline(fileContents, filePath))
        {
            boost::trim(filePath);
            // Skip empty lines and comments
            if (!filePath.empty() && (filePath.at(0) != '#'))
            {
                // Replace ~/ with absolute path
                if (filePath.substr(0, 2) == "~/")
                {
                    filePath = homeDir + filePath.substr(1);
                }
                fileList.push_back(filePath);
            }
        }
    }
    return fileList;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Deletes a list of files from the file in the provided filePath
/// @param fileList List of files/directories to be deleted. The "*" wildcard is
///        supported for files.
/// @return list of the deleted files and dirs
///////////////////////////////////////////////////////////////////////////////
export_object FileList remove(const FileList& fileList)
{
    FileList filesRemoved;

    for (const auto& filePath : fileList)
    {
        // Check for wildcards
        std::string filePathStr{filePath.c_str()};
        if (filePathStr.find('*') != std::string::npos)
        {
            auto pos = filePathStr.find_last_of('/');
            if (pos == std::string::npos)
            {
                RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"filelist::remove: Unable to parse %s", filePathStr.c_str());
                continue;
            }
            fs::path dirPath{filePathStr.substr(0, pos)};
            if (!fs::is_directory(dirPath))
            {
                RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"filelist::remove: %s dir does not exist", dirPath.c_str());
                continue;
            }
            std::string filePattern{filePathStr.substr(pos + 1, std::string::npos)};
            boost::trim(filePattern);

            fs::directory_iterator end_iter;
            for(fs::directory_iterator dir_itr(dirPath); dir_itr != end_iter; ++dir_itr)
            {
                std::string fileName{dir_itr->path().filename().c_str()};

                if (hub::utility::does_string_match_wildcard(fileName, filePattern))
                {
                    if (file::remove(dir_itr->path()))
                    {
                        RCLCPP_DEBUG(ROS2Logger::Instance().GetLogger(),"Removed %s", dir_itr->path().c_str());
                        filesRemoved.push_back(dir_itr->path().c_str());
                    }
                    else
                    {
                        RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"filelist::remove: Unable to delete %s", dir_itr->path().c_str());
                    }
                }
            }
        }
        // Check for directory
        else if (fs::is_directory(filePath))
        {
            try
            {
                fs::remove_all(filePath);
                RCLCPP_DEBUG(ROS2Logger::Instance().GetLogger(),"Removed %s", filePath.c_str());
                filesRemoved.push_back(filePath);
            }
            catch (const fs::filesystem_error & e)
            {
                RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"filelist::remove: %s for filePath=%s", e.what(), filePath.c_str());
                continue;
            }
        }
        else if (fs::exists(filePath) && file::remove(filePath))
        {
            RCLCPP_DEBUG(ROS2Logger::Instance().GetLogger(),"Removed %s", filePath.c_str());
            filesRemoved.push_back(filePath);
        }
    }
    return filesRemoved;
}

}
}
}
