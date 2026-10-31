#include <string>
#include <exception>
#include <filesystem/path.hh>
#include <hub/base/status_exception.hh>

#include "rclcpp/rclcpp.hpp"
#include "ROS2Logger.hpp"
#include "nvm_directory.h"
#include <filesystem/file.hh>
#include <hub/base/iteration.hh>
#include <sstream>

namespace ros2_nvm {
namespace filesystem {
namespace nvm_dir {

namespace fs = boost::filesystem;

export_object bool create(const boost::filesystem::path &path, boost::filesystem::perms perms) {
    try {
        // Iterate back through parent paths to make sure that permissions are set correctly
        hub::filesystem::path fpath(path.string());
        fpath.make_directories();
        if (!fpath.exists()) 
        {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"nvm_dir::create: Failed to create %s", fpath.c_str());
            return false;
        }
        else 
        {
            RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"nvm_dir::create: %s created", fpath.c_str());    
        }

        // Set the permissions for the path
        std::stringstream prms {""};
        prms << std::oct << perms;
        fpath.change_permissions(prms.str());
        RCLCPP_DEBUG(ROS2Logger::Instance().GetLogger(),"nvm_dir::create: %s permissions set to \\%03o", path.c_str(), perms);

    }
    catch (const hub::base::status_exception& e) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"nvm_dir::create: Status_exception %s for path=%s", e.what(), path.c_str());
        return false;
    }
    return true;
}

export_object bool copy(const fs::path &source, const fs::path &dest, bool overwrite) {
    try {
        if (create(dest)) {
            hub::filesystem::path srcFPath(source.string());
            if (srcFPath.exists() && srcFPath.is_directory()) {
                // Iterate through the source directory
                hub::filesystem::directory_entry_list children = srcFPath.enumerate_children();
                hub_const_iterate_over(iterator, children, hub::filesystem::directory_entry_list) {
                    try {
                        const hub::base::directory_entry &entry = *iterator;
                        hub::base::path_type pathType = entry.type;
                        hub::filesystem::path srcAbsPath(srcFPath, entry.name);
                        hub::filesystem::path destAbsPath(hub::filesystem::path(dest.string()), entry.name);

                        if ((entry.type == hub::base::path_link) || (entry.type == hub::base::path_unknown)) {
                            // Update the source path and type in case of a symbolic link
                            srcAbsPath = srcAbsPath.get_absolute_path();
                            pathType = srcAbsPath.get_status().type;
                        }

                        if (pathType == hub::base::path_directory) {
                            // Found directory: Recursion
                            if (!nvm_dir::copy(srcAbsPath.str(), destAbsPath.str()))
                                return false;
                            destAbsPath.make_directories();
                        }
                        else {
                            // Found file: Copy
                            hub::filesystem::file srcAbsFPath(srcAbsPath);
                            hub::filesystem::file destAbsFPath(destAbsPath);
                            destAbsFPath.touch();
                            std::string content;
                            srcAbsFPath.read_entirely(content);
                            destAbsFPath.write_entirely(content);
                        }
                    }
                    catch (hub::base::status_exception const & e){
                        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"nvm_dir::copy: %s for source=%s dest=%s", e.what(), source.c_str(), dest.c_str());
                    }
                }
                return true;
            }
            else {
                RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"nvm_dir::copy: Unable to find %s", source.c_str());
            }
        }
        else {
            RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"nvm_dir::copy: Unable to create %s", dest.c_str());
        }
    }
    catch (const hub::base::status_exception &e) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"nvm_dir::copy: %s for source=%s dest=%s", e.what(), source.c_str(), dest.c_str());
    }
    return false;
}

export_object bool move(const boost::filesystem::path &source, const boost::filesystem::path &dest)
{
    try {
        if (fs::is_directory(dest) || create(dest)) {
            if (fs::exists(source) && fs::is_directory(source)) {
                // Iterate through the source directory
                for (fs::directory_iterator file(source); file != fs::directory_iterator(); ++file) {
                    try {
                        fs::path current(file->path());
                        if (fs::is_directory(current)) {
                            // Found directory: Recursion
                            if (!nvm_dir::move(current, dest / current.filename())) {
                                return false;
                            }
                        }
                        else {
                            // Found file: Copy
                            fs::rename(current, dest / current.filename());
                            RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"nvm_dir::move: %s moved to %s/%s successfully", current.c_str(), dest.c_str(), current.filename().c_str());
                        }
                    }
                    catch (fs::filesystem_error const & e){
                        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"nvm_dir::move: %s for source=%s dest=%s", e.what(), source.c_str(), dest.c_str());
                    }
                }
                return true;
            }
            else {
                RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"nvm_dir::move: Unable to find %s", source.c_str());
            }
        }
        else {
            RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"nvm_dir::move: Unable to create %s", dest.c_str());
        }
    }
    catch (const fs::filesystem_error &e) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"nvm_dir::copy: %s for source=%s dest=%s", e.what(), source.c_str(), dest.c_str());
    }
    return false;
}

export_object bool clear(const boost::filesystem::path &path)
{
    try {
        hub::filesystem::path fPath(path.string());
        fPath.remove_recursively(false);
        return true;
    }
    catch (const hub::base::status_exception &e) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"nvm_dir::clear: %s for path=%s", e.what(), path.c_str());
    }
    return false;
}

export_object bool remove(const boost::filesystem::path &path)
{
    try {
        fs::remove_all(path);
        RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"nvm_dir::remove: sucessful for path=%s", path.c_str());
        return true;
    }
    catch (const fs::filesystem_error &e) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"nvm_dir::remove: %s for path=%s", e.what(), path.c_str());
    }
    return false;
}

export_object bool getFilePaths(const boost::filesystem::path &path, PathList& files, const std::string& extension)
{
    // Strip leading period
    std::string fileExtension = extension;
    if (!fileExtension.empty() && (fileExtension.at(0) == '.'))
    {
        RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"Stripping leading . from %s", fileExtension.c_str());
        fileExtension.erase(0, 1);
    }
    files.clear();
    hub::filesystem::path fPath(path.string());
    try {
        if (!fPath.exists() || !fPath.is_directory()) {  // Check if the directory exists and is value
            RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"nvm_dir::getFilePaths: path does not exist or is not valid: %s", fPath.c_str());
            return false;
        }
        // Iterate through path
        hub::filesystem::directory_entry_list itemsList = fPath.enumerate_children();
        hub_const_iterate_over(iterator, itemsList, hub::filesystem::directory_entry_list) {
            const hub::base::directory_entry &entry = *iterator;
            // If it's a file, check it
            hub::filesystem::path filePath(fPath, entry.name);
            if (filePath.is_regular_file()) {
                // If the file matches the fileExtension, add to the list
                auto fileName = filePath.get_name().str();
                if (fileExtension.empty() || (filePath.get_extension() == fileExtension))
                {
                    RCLCPP_DEBUG(ROS2Logger::Instance().GetLogger(),"nvm_dir::getFilePaths: Adding %s to files", fileName.c_str());
                    files.push_back(filePath);
                }
                else
                {
                    RCLCPP_DEBUG(ROS2Logger::Instance().GetLogger(),"nvm_dir::getFilePaths: Skipping %s (doesn't match extension %s)", fileName.c_str(), fileExtension.c_str());
                }
            }
        }
    }
    catch (const hub::base::status_exception &e) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"nvm_dir::getFilePaths: %s for path=%s fileExtension=%s", e.what(), fPath.c_str(), fileExtension.c_str());
        return false;
    }

    // Order paths alphabetically
    std::sort(files.begin(), files.end());

    return true;
}

}
}
}
