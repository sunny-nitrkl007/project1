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
#include <exception>
#include <iostream>
#include <pthread.h>
#include <sched.h>
#include <string>
#include <thread>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "ROS2Logger.hpp"

namespace ros2_wrapper
{

enum class LifecyclePolicy
{
    Legacy,
    OrderlyShutdown
};

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
    template<typename AppT, bool UseReceivePump = false>
    static int run(int argc, char** argv)
    {
        std::string const rosLogDir = "/tmp/appdata/CPM/log";
        std::string const logFormat = "{date_time_with_ms} | {severity} | {file_name}:{line_number} | {message}";
        setenv("ROS_LOG_DIR", rosLogDir.c_str(), 1);
        setenv("RCUTILS_CONSOLE_OUTPUT_FORMAT", logFormat.c_str(), 1);
        setenv("ROS_AUTOMATIC_DISCOVERY_RANGE", "LOCALHOST", 0);

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

            if constexpr (UseReceivePump)
            {
                app->setReceivePump(
                    [executor]()
                    {
                        executor->spin_some();
                    });

                while (rclcpp::ok())
                {
                    executor->spin_some();
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }
            }
            else
            {
                executor->spin();
            }
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

    template<typename AppT>
    static int run(int argc, char** argv, LifecyclePolicy policy,
            const std::string& defaultIdentity = std::string())
    {
        if (policy != LifecyclePolicy::OrderlyShutdown) {
            return run<AppT>(argc, argv);
        }

        std::string const rosLogDir = "/tmp/appdata/CPM/log";
        std::string const logFormat = "{date_time_with_ms} | {severity} | {file_name}:{line_number} | {message}";
        setenv("ROS_LOG_DIR", rosLogDir.c_str(), 1);
        setenv("RCUTILS_CONSOLE_OUTPUT_FORMAT", logFormat.c_str(), 1);
        setenv("ROS_AUTOMATIC_DISCOVERY_RANGE", "LOCALHOST", 0);

        sigset_t signalSet;
        sigemptyset(&signalSet);
        sigaddset(&signalSet, SIGINT);
        sigaddset(&signalSet, SIGTERM);
        sigaddset(&signalSet, SIGQUIT);
        sigset_t previousSignalMask;
        if (pthread_sigmask(SIG_BLOCK, &signalSet, &previousSignalMask) != 0) {
            return 1;
        }
        struct SignalMaskRestorer {
            sigset_t& previousMask;
            ~SignalMaskRestorer() { pthread_sigmask(SIG_SETMASK, &previousMask, nullptr); }
        } signalMaskRestorer{previousSignalMask};

        std::vector<char*> rosArgv;
        bool argumentsValid = true;
        std::string const nodeName = parseLegacyInstanceName(argc, argv, rosArgv,
                defaultIdentity, true, &argumentsValid);
        if (!argumentsValid) {
            std::cerr << "Missing instance name\n";
            return 1;
        }
        int const rosArgc = static_cast<int>(rosArgv.size());
        ROS2Logger::Instance().SetFeatureName(nodeName);

        bool contextInitialized = false;
        std::atomic<bool> stopping{false};
        std::atomic<bool> signalThreadDone{false};
        std::shared_ptr<AppT> app;
        std::shared_ptr<rclcpp::executors::SingleThreadedExecutor> executor;
        std::thread signalThread;
        int result = 1;

        try {
            rclcpp::init(rosArgc, rosArgv.data(), rclcpp::InitOptions(),
                    rclcpp::SignalHandlerOptions::None);
            contextInitialized = true;
            app = std::make_shared<AppT>(nodeName);
            executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
            executor->add_node(app);
            signalThread = std::thread([&]() {
                unsigned int signalsCaught = 0;
                const timespec timeout{0, 100000000};
                while (!signalThreadDone.load()) {
                    const int signalNumber = sigtimedwait(&signalSet, nullptr, &timeout);
                    if (signalNumber == SIGINT || signalNumber == SIGTERM || signalNumber == SIGQUIT) {
                        if (++signalsCaught >= 3) {
                            std::_Exit(1);
                        }
                        stopping.store(true);
                    }
                }
            });

            const bool initialized = !stopping.load() && app->beforeInitialize() &&
                    !stopping.load() && app->initialize();
            if (initialized && !stopping.load()) {
                app->startExecutiveTimer();
                while (!stopping.load() && rclcpp::ok()) {
                    executor->spin_some(std::chrono::milliseconds(100));
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
                result = 0;
            }
            else if (!stopping.load()) {
                RCLCPP_ERROR(app->get_logger(), "Failed to initialize %s", nodeName.c_str());
            }
        }
        catch (const std::exception& error) {
            RCLCPP_ERROR(rclcpp::get_logger("Ros2TaskWrapper"), "%s", error.what());
        }
        catch (...) {
            RCLCPP_ERROR(rclcpp::get_logger("Ros2TaskWrapper"), "Unknown lifecycle exception");
        }

        if (app) {
            try {
                app->cleanup();
            }
            catch (const std::exception& error) {
                RCLCPP_ERROR(rclcpp::get_logger("Ros2TaskWrapper"), "Cleanup failed: %s", error.what());
                result = 1;
            }
            catch (...) {
                RCLCPP_ERROR(rclcpp::get_logger("Ros2TaskWrapper"), "Cleanup failed");
                result = 1;
            }
        }
        if (contextInitialized && rclcpp::ok()) {
            try {
                rclcpp::shutdown();
            }
            catch (...) {
                result = 1;
            }
        }
        signalThreadDone.store(true);
        if (signalThread.joinable()) {
            signalThread.join();
        }
        return result;
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
    
    static std::string parseLegacyInstanceName(int argc, char** argv, std::vector<char*>& rosArgv,
            const std::string& defaultIdentity = std::string(), bool validateInstance = false,
            bool* argumentsValid = nullptr)
    {
        std::string nodeName = defaultIdentity.empty() ? (argc > 0 ? argv[0] : "ros2_task") : defaultIdentity;
        rosArgv.push_back(argv[0]);

        for (int idx = 1; idx < argc; ++idx) {
            const std::string arg(argv[idx]);

            if ((arg == "--instance") || (arg == "--instanceName")) {
                if ((idx + 1) < argc) {
                    nodeName = argv[++idx];
                }
                else if (validateInstance && argumentsValid) {
                    *argumentsValid = false;
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
