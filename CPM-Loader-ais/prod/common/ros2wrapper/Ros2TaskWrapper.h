///////////////////////////////////////////////////////////////////////////////
/// @file Ros2TaskWrapper.h
/// @brief Base class standing in for AIS task::Task's shape now that apps
///        inherit rclcpp::Node directly instead of task::Task. 
///////////////////////////////////////////////////////////////////////////////

#ifndef _Ros2TaskWrapper_h_
#define _Ros2TaskWrapper_h_

#include <chrono>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"

namespace ros2_wrapper
{

class Ros2TaskWrapper : public rclcpp::Node
{
public:
    explicit Ros2TaskWrapper(const std::string& nodeName) : rclcpp::Node(nodeName) {}
    ~Ros2TaskWrapper() override = default;

    // Same shape task::Task used to require of every app.
    virtual bool initialize() = 0;
    virtual bool executive() = 0;
    virtual void cleanup() = 0;

    
    virtual void startExecutiveTimer() = 0;

    // Optional hook for anything that must run before initialize() -- e.g.
    // WeighApp's parseTaskConfiguration(). Default: nothing extra needed.
    virtual bool beforeInitialize() { return true; }

    // Constructs AppT, drives it through beforeInitialize()+initialize(),
    // spins (default rclcpp signal handling) until shutdown, then cleanup().
    // Signal handling and RT scheduling are parked for now -- see
    // Ros2TaskWrapper_WITH_signal_and_scheduling.h backup when they're
    // ready to come back.
    template<typename AppT>
    static int run(int argc, char** argv)
    {
        std::vector<char*> rosArgv;
        std::string nodeName = parseLegacyInstanceName(argc, argv, rosArgv);
        int rosArgc = static_cast<int>(rosArgv.size());

        rclcpp::init(rosArgc, rosArgv.data());

        auto app = std::make_shared<AppT>(nodeName);

        bool initialized = app->beforeInitialize() && app->initialize();
        if (initialized) {
            app->startExecutiveTimer();
            rclcpp::spin(app);
        }
        else {
            RCLCPP_ERROR(app->get_logger(), "Failed to initialize %s", nodeName.c_str());
        }

        app->cleanup();
        if (rclcpp::ok()) {
            rclcpp::shutdown();
        }

        return initialized ? 0 : 1;
    }

protected:
    
    void createExecutiveTimer(double cycleRateHz)
    {
        if (cycleRateHz <= 0.0) {
            RCLCPP_WARN(get_logger(), "Invalid cycle rate %f, defaulting to 10 Hz", cycleRateHz);
            cycleRateHz = 10.0;
        }

        const auto period = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::duration<double>(1.0 / cycleRateHz));
        executiveTimer_ = create_wall_timer(period, [this]() {
            if (!executive()) {
                RCLCPP_ERROR(get_logger(), "%s executive failed", get_name());
            }
        });
    }

    // applyRealtimeScheduling() parked for now -- see
    // Ros2TaskWrapper_WITH_signal_and_scheduling.h backup.

    rclcpp::TimerBase::SharedPtr executiveTimer_;

private:
    
    static std::string parseLegacyInstanceName(int argc, char** argv, std::vector<char*>& rosArgv)
    {
        std::string nodeName = argc > 0 ? argv[0] : "ros2_task";
        rosArgv.push_back(argv[0]);

        for (int idx = 1; idx < argc; ++idx) {
            const std::string arg(argv[idx]);

            if ((arg == "--instance") || (arg == "--instanceName")) {
                if ((idx + 1) < argc) {
                    nodeName = argv[++idx];
                }
                continue;
            }

            const std::string instancePrefix = "--instance=";
            const std::string instanceNamePrefix = "--instanceName=";
            if (0 == arg.find(instancePrefix)) {
                nodeName = arg.substr(instancePrefix.size());
                continue;
            }
            if (0 == arg.find(instanceNamePrefix)) {
                nodeName = arg.substr(instanceNamePrefix.size());
                continue;
            }

            rosArgv.push_back(argv[idx]);
        }

        return nodeName;
    }

    // registerSignalHandling() parked for now -- see
    // Ros2TaskWrapper_WITH_signal_and_scheduling.h backup.
};

} // namespace ros2_wrapper

#endif // _Ros2TaskWrapper_h_
