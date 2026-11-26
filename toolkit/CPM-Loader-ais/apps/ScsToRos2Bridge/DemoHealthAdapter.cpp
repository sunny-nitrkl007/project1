#include "DemoHealthAdapter.h"
#include "ROS2Logger.hpp"
#include <ais/task/Task.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <limits>
#include <sstream>
#include <unistd.h>

std::string DemoHealthAdapter::incarnation(int32_t pid)
{
    std::ifstream file("/proc/" + std::to_string(pid) + "/stat");
    std::string stat;
    std::getline(file, stat);
    const auto end = stat.rfind(')');
    if (end == std::string::npos) {
        return {};
    }
    std::istringstream fields(stat.substr(end + 2));
    std::string value;
    for (int field = 3; field <= 22; ++field) {
        if (!(fields >> value) || (field == 3 && (value == "Z" || value == "X"))) {
            return {};
        }
    }
    return value;
}

bool DemoHealthAdapter::initialize(const rclcpp::Node::SharedPtr& node)
{
    node_ = node;
    char host[256]{};
    const char* catDir = std::getenv("CAT_DIR");
    if (!catDir || gethostname(host, sizeof(host) - 1) != 0 ||
        !task::InterfaceDb::bind("DemoProcessHealthOutput", output_)) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo health identity/configuration unavailable");
        return false;
    }
    host_ = host;
    char* resolved = realpath((std::string(catDir) + "/bin/DemoApp").c_str(), nullptr);
    if (!resolved) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo health requires installed DemoApp binary");
        return false;
    }
    executable_ = resolved;
    std::free(resolved);
    try {
        input_ = node_->create_subscription<Health>("demo_app_health",
            rclcpp::QoS(rclcpp::KeepLast(1)).reliable().durability_volatile(),
            [this](Health::ConstSharedPtr health, const rclcpp::MessageInfo& info) { receive(*health, info); });
    } catch (const std::exception& error) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo health initialization failed: %s", error.what());
        return false;
    }
    RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),
        "Demo executor idle/AIS sleep and event-thread metrics unmeasured; legacy fields use zero, not equivalence");
    return true;
}

bool DemoHealthAdapter::accept(const Health& health, const rclcpp::MessageInfo& info)
{
    const auto& metadata = info.get_rmw_message_info();
    const bool sameSession = !last_.session_id.empty() && health.session_id == last_.session_id;
    const bool terminal = sameSession && health.process_id == last_.process_id &&
        health.state == Health::SHUTTING_DOWN;
    const auto publishers = node_->count_publishers("demo_app_health");
    const auto now = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    if (metadata.source_timestamp <= 0 || metadata.source_timestamp > now ||
        now - metadata.source_timestamp > 2000000000LL ||
        (publishers != 1 && !(terminal && publishers == 0)) ||
        health.source != "DemoApp" || health.host != host_ || health.process_id <= 0 ||
        health.session_id.size() > 256 || health.report_sequence == 0 ||
        health.state > Health::UNKNOWN || health.intended_cycle_rate_hz != 50.0 ||
        health.total_executive_cycle_count > std::numeric_limits<unsigned int>::max() ||
        health.total_executive_late_cycle_count > health.total_executive_cycle_count ||
        health.longest_recent_executive_cycle_sec > health.longest_executive_cycle_sec ||
        health.executor_idle_time_sec != 0.0 ||
        logger::Priority::stringAsPriorityLevel(health.logger_threshold) == logger::Priority::none) {
        return false;
    }
    for (double metric : {health.cycle_rate_hz, health.recent_executive_cycle_rate_hz,
                         health.longest_executive_cycle_sec, health.longest_recent_executive_cycle_sec}) {
        if (!std::isfinite(metric) || metric < 0.0) {
            return false;
        }
    }
    const std::string prefix = host_ + ":" + std::to_string(health.process_id) + ":";
    if (health.session_id.compare(0, prefix.size(), prefix) != 0) {
        return false;
    }
    const std::string suffix = health.session_id.substr(prefix.size());
    const auto separator = suffix.find(':');
    if (separator == std::string::npos || separator == 0 || separator + 1 == suffix.size() ||
        suffix.find(':', separator + 1) != std::string::npos ||
        suffix.find_first_not_of("0123456789:") != std::string::npos) {
        return false;
    }
    std::array<uint8_t, RMW_GID_STORAGE_SIZE> gid;
    std::copy(metadata.publisher_gid.data, metadata.publisher_gid.data + gid.size(), gid.begin());
    if (retiredSessions_.count(health.session_id) ||
        std::all_of(gid.begin(), gid.end(), [](uint8_t byte) { return byte == 0; }) ||
        (sameSession && (gid != producer_ || health.process_id != last_.process_id ||
                        last_.state == Health::SHUTTING_DOWN))) {
        return false;
    }
    std::string current = incarnation_;
    if (!terminal) {
        char path[4096]{};
        const std::string proc = "/proc/" + std::to_string(health.process_id);
        const auto length = readlink((proc + "/exe").c_str(), path, sizeof(path) - 1);
        if (length <= 0 || std::string(path, static_cast<size_t>(length)) != executable_) {
            return false;
        }
        std::ifstream commandFile(proc + "/cmdline", std::ios::binary);
        char commandBytes[8192]{};
        commandFile.read(commandBytes, sizeof(commandBytes));
        if (!commandFile.eof()) {
            return false;
        }
        const std::string command(commandBytes, static_cast<size_t>(commandFile.gcount()));
        const char instanceBytes[] = "\0--instanceName=DemoApp\0";
        const std::string instance(instanceBytes, sizeof(instanceBytes) - 1);
        if (command.find(instance) == std::string::npos) {
            return false;
        }
        current = incarnation(health.process_id);
        if (current.empty()) {
            return false;
        }
    }
    if (sameSession) {
        if ((!terminal && (stopped_ || current != incarnation_)) ||
            health.report_sequence <= last_.report_sequence ||
            metadata.source_timestamp <= sourceTimestamp_ ||
            health.total_executive_cycle_count < last_.total_executive_cycle_count ||
            health.total_executive_late_cycle_count < last_.total_executive_late_cycle_count ||
            health.longest_executive_cycle_sec < last_.longest_executive_cycle_sec ||
            (health.state < last_.state && last_.state != Health::UNKNOWN) ||
            (health.total_executive_cycle_count == last_.total_executive_cycle_count &&
             (health.cycle_rate_hz != 0.0 || health.recent_executive_cycle_rate_hz != 0.0))) {
            return false;
        }
    } else if (!last_.session_id.empty()) {
        if (gid == producer_ || (health.process_id == last_.process_id && current == incarnation_) ||
            incarnation(last_.process_id) == incarnation_ || retiredSessions_.size() >= 1024) {
            return false;
        }
        invalidate();
        retiredSessions_.insert(last_.session_id);
    }
    incarnation_ = current;
    producer_ = gid;
    sourceTimestamp_ = metadata.source_timestamp;
    return true;
}

bool DemoHealthAdapter::publish(const Health& health, bool stale)
{
    ProcessHealthMessage report;
    report.source = health.source;
    report.host = health.host;
    report.processID = health.process_id;
    report.taskState = static_cast<task::TaskState>(stale ? Health::UNKNOWN : health.state);
    report.intendedCycleRate_hz = health.intended_cycle_rate_hz;
    report.cycleRate_hz = stale ? 0.0 : health.cycle_rate_hz;
    report.recentExecutiveCycleRate_hz = stale ? 0.0 : health.recent_executive_cycle_rate_hz;
    report.longestExecutiveThreadCycle_sec = health.longest_executive_cycle_sec;
    report.longestRecentExecutiveThreadCycle_sec = health.longest_recent_executive_cycle_sec;
    report.totalExecutiveCycleCount = static_cast<unsigned int>(health.total_executive_cycle_count);
    report.totalExecutiveLateCycleCount = static_cast<unsigned int>(health.total_executive_late_cycle_count);
    report.totalExecutiveSleepTime_sec = 0.0;
    report.eventDrivenMessageProcessRate_hz = 0.0;
    report.recentEventDrivenCycleRate_hz = 0.0;
    report.longestEventDrivenCycle_sec = 0.0;
    report.longestRecentEventDrivenCycle_sec = 0.0;
    report.loggerPriority.disableAll();
    report.loggerPriority.enableAll(logger::Priority::stringAsPriorityLevel(health.logger_threshold));
    report.setOriginationTime(commonNow());
    return output_->publish(report);
}

void DemoHealthAdapter::invalidate()
{
    if (active_) {
        active_ = false;
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo health expired/stopped; no healthy heartbeat synthesized");
        try {
            if (!publish(last_, true)) {
                RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo health unavailable publication failed");
            }
        } catch (const std::exception& error) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo health unavailable publication failed: %s", error.what());
        } catch (...) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo health unavailable publication failed");
        }
    }
}

void DemoHealthAdapter::receive(const Health& health, const rclcpp::MessageInfo& info)
{
    try {
        if (!accept(health, info)) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Invalid/replayed Demo health; adapter fails closed");
            invalidate();
            return;
        }
        last_ = health;
        received_ = Clock::now();
        stopped_ = health.state == Health::SHUTTING_DOWN;
        active_ = true;
        if (!publish(health, false)) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo health publication failed; awaiting next real report");
            invalidate();
        } else {
            active_ = !stopped_ && health.state != Health::UNKNOWN;
        }
    } catch (const std::exception& error) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo health failed: %s", error.what());
        invalidate();
    } catch (...) {
        invalidate();
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo health failed; awaiting next real report");
    }
}

bool DemoHealthAdapter::executive()
{
    try {
        if (!last_.session_id.empty() && !stopped_ && incarnation(last_.process_id) != incarnation_) {
            stopped_ = true;
            invalidate();
        } else if (active_ && (Clock::now() - received_ > std::chrono::seconds(2) ||
            node_->count_publishers("demo_app_health") != 1)) {
            invalidate();
        }
    } catch (const std::exception& error) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo health watchdog failed: %s", error.what());
        invalidate();
    } catch (...) {
        invalidate();
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo health watchdog failed");
    }
    return true;
}

void DemoHealthAdapter::cleanup() noexcept
{
    stopped_ = true;
    try {
        input_.reset();
        invalidate();
    } catch (...) {
        active_ = false;
    }
}
