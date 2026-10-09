#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/archive_exception.hpp>

#include "ROS2Logger.hpp"

#include <fileio/sha1_fstream.hpp>

#include "LpsSaJobMgrTasks.h"

namespace fs = boost::filesystem;

bool LpsSaJobMgrTasks::load() {
    bool success = false;
    tes_common_ais::sha1_ifstream ifs{ true }; // two_copy
    ifs.open(filePath_, std::ios_base::in | std::ios_base::binary);
    if (ifs) {
        // Read the file in
        try {
            boost::archive::binary_iarchive ia(ifs);
            ia >> *this;
           RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"Loaded job manager tasks from storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Could not deserialize job manager tasks from storage.");
           RCLCPP_ERROR_STREAM(ROS2Logger::Instance().GetLogger(),e.what());
        }
        catch (const std::exception& e) {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Could not deserialize job manager tasks from storage.");
           RCLCPP_ERROR_STREAM(ROS2Logger::Instance().GetLogger(),e.what());
        }
        catch (...) {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Could not deserialize job manager tasks from storage, unexpected error.");
        }

        ifs.close();

        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"Job manager tasks file was corrupt... fixed it.");
            }
            else {
               RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Job manager tasks file was corrupt... could not fix it.");
            }
        }
    }
    else {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Job manager configuration file could not be opened from storage.");
    }

    if (!success) {
        *this = LpsSaJobMgrTasks(filePath_, defaultTargetWeight_);
    }

    return success;
}

bool LpsSaJobMgrTasks::save() {
    bool success = false;

    // update the current targetType for the task before saving
    try {
        targetTypes_.at(loadIndex_) = getCurrentTaskLoad().targetType();
    } catch (const std::out_of_range& e) {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Index out of range");
    }

    tes_common_ais::sha1_ofstream ofs{ true }; // two_copy
    ofs.open(filePath_, std::ios_base::out | std::ios_base::binary);
    if (ofs) {
        // Read the file in
        try {
            boost::archive::binary_oarchive oa(ofs);
            oa << *this;
           RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"Saved job manager tasks to storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Could not serialize job manager tasks to storage.");
           RCLCPP_ERROR_STREAM(ROS2Logger::Instance().GetLogger(),e.what());
        }
        catch (const std::exception &e) {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Could not serialize job manager tasks to storage.");
           RCLCPP_ERROR_STREAM(ROS2Logger::Instance().GetLogger(),e.what());
        }
        catch (...) {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Could not serialize job manager tasks to storage, unexpected error.");
        }

        ofs.close();
    }
    else {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Job manager tasks could not be opened from storage.");
    }

    return success;
}
