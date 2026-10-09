#pragma once

#include <rclcpp/rclcpp.hpp>
#include <string>

class ROS2Logger
{
public:
    static ROS2Logger& Instance()
    {
        static ROS2Logger instance;
        return instance;
    }
    void SetFeatureName(const std::string& featureName)
    {
        m_logger = rclcpp::get_logger(featureName);
        rcutils_ret_t ret = rcutils_logging_set_logger_level(m_logger.get_name(),RCUTILS_LOG_SEVERITY_ERROR);
        if (ret != RCUTILS_RET_OK)
        {
            std::cerr << "Failed to set logger level for "<< m_logger.get_name() << std::endl;
        }
    }

    const rclcpp::Logger& GetLogger() const
    {
        return m_logger;
    }

private:
    ROS2Logger()
        : m_logger(rclcpp::get_logger("Default"))
    {
    }

    ROS2Logger(const ROS2Logger&) = delete;
    ROS2Logger& operator=(const ROS2Logger&) = delete;

    rclcpp::Logger m_logger;
};