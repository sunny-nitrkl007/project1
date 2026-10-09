///////////////////////////////////////////////////////////////////////////////
/// @file Ros2TaskWrapper.h
/// @brief Base class standing in for AIS task::Task's shape now that apps
///        inherit rclcpp::Node directly instead of task::Task. 
///////////////////////////////////////////////////////////////////////////////

#ifndef _Ros2TaskWrapper_h_
#define _Ros2TaskWrapper_h_

#include <atomic>
#include <chrono>
#include <cerrno>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <sched.h>
#include <string>
#include <thread>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "ROS2Logger.hpp"

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

    // Constructs AppT, drives it through the same lifecycle AIS Task used
    // to drive: signals registered up front, beforeInitialize()+initialize(),
    // spin until a shutdown signal , cleanup()
    // with communication still alive, then rclcpp::shutdown() as the last
    // step. Each app's main() becomes a one-line call to this.
    template<typename AppT>
    static int run(int argc, char** argv)
    {
        std::vector<char*> rosArgv;
        std::string nodeName = parseLegacyInstanceName(argc, argv, rosArgv);
        int rosArgc = static_cast<int>(rosArgv.size());

        ROS2Logger::Instance().SetFeatureName(nodeName);

        rclcpp::init(rosArgc, rosArgv.data());

        auto app = std::make_shared<AppT>(nodeName);

        auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
        executor->add_node(app);

        registerSignalHandling(executor);

        bool initialized = app->beforeInitialize() && app->initialize();
        if (initialized) {
            app->startExecutiveTimer();
            executor->spin();
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

    // Matches AIS TaskCore's sched_setscheduler(policy, priority) call --
    // same POSIX mechanism, invoked directly instead of through task::Task
    // reading it from .rb.
    bool applyRealtimeScheduling(int policy, int priority)
    {
        sched_param schedParam{};
        schedParam.sched_priority = priority;
        if (0 != pthread_setschedparam(pthread_self(), policy, &schedParam)) {
            RCLCPP_ERROR(get_logger(), "Failed to set scheduling policy %d / priority %d: %s",
                    policy, priority, std::strerror(errno));
            return false;
        }
        return true;
    }

    // Same as above, but takes the policy as a string -- matches the exact
    // values AIS .rb files use ("scheduler" => "SCHED_RR" etc.)
    bool applyRealtimeScheduling(const std::string& policyName, int priority)
    {
        int policy = SCHED_RR;
        if (policyName == "SCHED_RR") {
            policy = SCHED_RR;
        }
        else if (policyName == "SCHED_FIFO") {
            policy = SCHED_FIFO;
        }
        else if (policyName == "SCHED_OTHER") {
            policy = SCHED_OTHER;
        }
        else {
            RCLCPP_WARN(get_logger(), "Unrecognized scheduler policy '%s', defaulting to SCHED_RR",
                    policyName.c_str());
        }
        return applyRealtimeScheduling(policy, priority);
    }

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

    // Reproduces ais_task/ais/task/sigcatch.cpp exactly: block the exit
    // signals on every thread, hand them to one dedicated thread via
    // sigwait(). 1st/2nd signal interrupts the executor; 3rd forces an
    // immediate exit with no cleanup, matching AIS's documented behavior.
    static void registerSignalHandling(std::shared_ptr<rclcpp::Executor> executor)
    {
        sigset_t signalSet;
        sigemptyset(&signalSet);
        sigaddset(&signalSet, SIGINT);
        sigaddset(&signalSet, SIGTERM);
        sigaddset(&signalSet, SIGQUIT);
        pthread_sigmask(SIG_BLOCK, &signalSet, nullptr);

        std::thread signalThread([executor]() {
            static std::atomic<uint32_t> signalsCaught{0};
            constexpr uint32_t maxExitSignalsToCatch = 3;

            sigset_t waitSet;
            int signalNumber = 0;
            for (;;) {
                sigemptyset(&waitSet);
                sigaddset(&waitSet, SIGINT);
                sigaddset(&waitSet, SIGTERM);
                sigaddset(&waitSet, SIGQUIT);
                sigwait(&waitSet, &signalNumber);

                if (signalNumber == SIGINT || signalNumber == SIGTERM || signalNumber == SIGQUIT) {
                    if (++signalsCaught >= maxExitSignalsToCatch) {
                        std::exit(1);
                    }
                    executor->cancel();
                }
            }
        });
        signalThread.detach();
    }
};

} // namespace ros2_wrapper

#endif // _Ros2TaskWrapper_h_
