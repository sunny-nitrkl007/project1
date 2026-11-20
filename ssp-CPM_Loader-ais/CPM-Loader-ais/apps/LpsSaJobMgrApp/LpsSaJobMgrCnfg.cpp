#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/archive_exception.hpp>

#include "ROS2Logger.hpp"

#include <fileio/sha1_fstream.hpp>

#include "LpsSaJobMgrCnfg.h"

namespace fs = boost::filesystem;

/*
 * Load configuration from storage
 */
bool LpsSaJobMgrCnfg::load(const fs::path& filePath) {
    bool success = false;
    tes_common_ais::sha1_ifstream ifs{ true }; // two_copy
    ifs.open(filePath.string(), std::ios_base::in | std::ios_base::binary);
    if (ifs) {
        // Read the file in
        try {
            boost::archive::binary_iarchive ia(ifs);
            ia >> *this;
           RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"Loaded job manager configuration from storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Could not deserialize job manager configuration from storage.");
           RCLCPP_ERROR_STREAM(ROS2Logger::Instance().GetLogger(),e.what());
            reset();
        }
        catch (const std::exception& e) {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Could not deserialize job manager configuration from storage.");
           RCLCPP_ERROR_STREAM(ROS2Logger::Instance().GetLogger(),e.what());
            reset();
        }
        catch (...) {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Could not deserialize job manager configuration from storage, unexpected error.");
            reset();
        }

        ifs.close();

        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"Job manager configuration file was corrupt... fixed it.");
            }
            else {
               RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Job manager configuration file was corrupt... could not fix it.");
            }
        }
    }
    else {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Job manager configuration file could not be opened from storage.");
    }

    return success;
}

/*
 * Save configuration to storage
 */
bool LpsSaJobMgrCnfg::save(const fs::path& filePath) const {
    bool success = false;
    tes_common_ais::sha1_ofstream ofs{ true }; // two_copy
    ofs.open(filePath.string(), std::ios_base::out | std::ios_base::binary);
    if (ofs) {
        // Read the file in
        try {
            boost::archive::binary_oarchive oa(ofs);
            oa << *this;
           RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"Saved job manager configuration to storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Could not serialize job manager configuration to storage.");
           RCLCPP_ERROR_STREAM(ROS2Logger::Instance().GetLogger(),e.what());
        }

        ofs.close();
    }
    else {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Job manager configuration could not be opened from storage.");
    }

    return success;
}
