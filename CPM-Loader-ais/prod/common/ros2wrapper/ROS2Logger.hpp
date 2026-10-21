#pragma once

#include <rclcpp/rclcpp.hpp>
#include <string>

// ---------------------------------------------------------------------------
// AIS → ROS2 severity-level mapping
//
// AIS            ROS2            Notes
// ─────────────────────────────────────────────────
// emerg          FATAL           1:1 — system unusable
// fatal          FATAL           1:1 — process abort
// alert          ERROR           Requires immediate attention, no ROS2 direct equivalent
// crit           ERROR           Critical condition, no ROS2 direct equivalent
// error          ERROR           1:1 — runtime error
// warn           WARN            1:1 — warning
// notice         WARN            Between warn and info, mapped up to WARN
// info           INFO            1:1 — informational
// debug          DEBUG           1:1 — developer diagnostic
// ---------------------------------------------------------------------------

class ROS2Logger
{
public:
    static ROS2Logger& Instance()
    {
        static ROS2Logger instance;
        return instance;
    }

    void SetFeatureName(const std::string& featureName,
                        RCUTILS_LOG_SEVERITY level = RCUTILS_LOG_SEVERITY_ERROR)
    {
        m_logger = rclcpp::get_logger(featureName);
        rcutils_ret_t ret = rcutils_logging_set_logger_level(m_logger.get_name(), level);
        if (ret != RCUTILS_RET_OK)
        {
            std::cerr << "Failed to set logger level for " << m_logger.get_name() << std::endl;
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