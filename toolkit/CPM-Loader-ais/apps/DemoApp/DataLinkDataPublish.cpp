#include "DataLinkDataPublish.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "demo_sim_model_if.h"
#include "demo_sim_a6n2_po.h"
#include "demo_sim_a6n2.h"


#ifdef __cplusplus
}
#endif


#include <algorithm>
#include <utility>
#include <cstring>
#include <random>
#include <stdexcept>
#include <unistd.h>
extern demo_sim_a6n2_catParameters_si_RAM_t demo_sim_a6n2_catParameters_si_RAM;




DemoApp::DemoApp( const std::string& taskName ):
    Ros2TaskWrapper(taskName),
    liftposition_(10.f),
    liftposition_rate_(15.f), // Maximum Raise Speed
    tiltposition_(100.f),
    tiltposition_rate_(30.f), // Maximum Rack Speed
    payload_(8.f),
    payload_rate_(20.f) {}

/*
 Destructor
 */
DemoApp::~DemoApp() {
}

/******************************************************************************
FUNCTION NAME:Initialize
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
bool DemoApp::initialize( )
{
    const double rate = declare_parameter<double>("cycle_rate_hz", 50.0);
    if (rate != 50.0) {
        RCLCPP_ERROR(get_logger(), "Generated Demo model requires 50 Hz");
        return false;
    }
    loggerThreshold_ = declare_parameter<std::string>("logger_threshold", "error");
    ROS2Logger::Instance().SetLogLevel(loggerThreshold_);
    const std::string scheduler = declare_parameter<std::string>("scheduler", "SCHED_OTHER");
    const int64_t configuredPriority = declare_parameter<int64_t>("scheduler_priority", 0);
    if (configuredPriority < 0 || configuredPriority > 99) {
        RCLCPP_ERROR(get_logger(), "Scheduler priority must be between 0 and 99");
        return false;
    }
    const int priority = static_cast<int>(configuredPriority);
    int policy;
    if (scheduler == "SCHED_OTHER" && priority == 0) {
        policy = SCHED_OTHER;
    } else if ((scheduler == "SCHED_RR" || scheduler == "SCHED_FIFO") &&
               priority >= 1 && priority <= 99) {
        policy = scheduler == "SCHED_RR" ? SCHED_RR : SCHED_FIFO;
    } else {
        RCLCPP_ERROR(get_logger(), "Invalid scheduler/priority %s/%d", scheduler.c_str(), priority);
        return false;
    }
    sched_param param{};
    param.sched_priority = priority;
    const int error = pthread_setschedparam(pthread_self(), policy, &param);
    if (error != 0) {
        RCLCPP_ERROR(get_logger(), "Cannot apply scheduling: %s", std::strerror(error));
        return false;
    }
    char hostname[256]{};
    if (gethostname(hostname, sizeof(hostname) - 1) != 0) {
        throw std::runtime_error("Cannot obtain DemoApp hostname");
    }
    host_ = hostname;
    std::random_device random;
    sessionId_ = host_ + ":" + std::to_string(getpid()) + ":" +
        std::to_string(Clock::now().time_since_epoch().count()) + ":" + std::to_string(random());
    const auto commandsQos = rclcpp::QoS(rclcpp::KeepLast(20)).reliable().durability_volatile();
    requestSubscription_ = create_subscription<RequestBatch>("demo_app_requests", commandsQos,
        [this](RequestBatch::ConstSharedPtr batch) {
            requests_.push_back(*batch);
            if (requests_.size() == 21) {
                RCLCPP_WARN(get_logger(), "Demo request backlog exceeds legacy depth 20; no batches coalesced");
            }
        });
    cyclePublisher_ = create_publisher<Cycle>("demo_app_cycle",
        rclcpp::QoS(rclcpp::KeepLast(30)).reliable().durability_volatile());
    healthPublisher_ = create_publisher<Health>("demo_app_health",
        rclcpp::QoS(rclcpp::KeepLast(10)).reliable().durability_volatile());
    demo_sim_a6n2_work.demo_sim_a6n2_M.demo_sim_a6n2_catParameters_si_RAM_p = &demo_sim_a6n2_catParameters_si_RAM;

    demo_sim_a6n2_po_init();

    initialized_ = true;
    lastHealthTime_ = Clock::now();
    return true;
}

/******************************************************************************
FUNCTION NAME:executive
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
bool DemoApp::executive( )
{
    if (!initialized_) {
        return false;
    }
    const auto begin = Clock::now();
    if (sequence_ != 0) {
        const double elapsed = std::chrono::duration<double>(begin - lastCycleStart_).count();
        cycleRate_ = elapsed > 0.0 ? 1.0 / elapsed : 0.0;
    }
    lastCycleStart_ = begin;
    Cycle cycle;
    cycle.session_id = sessionId_;
    cycle.sequence = ++sequence_;
    CaptureDataLinkData(cycle);
    ReadDemoAppRosIn();
    ReadPWM_API(cycle.tx);
    cyclePublisher_->publish(cycle);
    const double duration = std::chrono::duration<double>(Clock::now() - begin).count();
    longestCycle_ = std::max(longestCycle_, duration);
    longestRecentCycle_ = std::max(longestRecentCycle_, duration);
    if (duration > 0.02) {
        ++lateCycleCount_;
    }
    return true;
}

/******************************************************************************
FUNCTION NAME:CaptureDataLinkData
DESCRIPTION: Capture raw demo values for bridge-owned legacy reconstruction
PARAMETER DESCRIPTION:
RETURN VALUE:none
*******************************************************************************/

void DemoApp::CaptureDataLinkData(Cycle& cycle)
{
    cycle.hydraulic_oil_temperature = hyd_temp_value;
    cycle.sea_level_installation = sea_level_2;
    cycle.production_measurement = production_measurement;
    cycle.engine_speed_pgn = {{0x00, 0x00, 0x00, 0x80, 0x3E, 0x00, 0x00, 0x00}};
    cycle.service_mode = 0x000C;
    updateTotalFuel();
    cycle.total_fuel_used = total_fuel_used_;
}

void DemoApp::ReadPWM_API(weigh_app_interfaces::msg::DemoAppTxChannel& txout1)
{
    pos_lift_desired = liftposition_;
    pos_lift_rate = liftposition_rate_;
    pos_tilt_desired = tiltposition_;
    pos_tilt_rate = tiltposition_rate_;
    payload_desired = payload_;
    payload_rate = payload_rate_;
    demo_sim_a6n2_po_0();

    {
        txout1.pres_lift_he_demo = angle_lift_het;   // Lift He Pressure (angle_lift_het = Lift He Pressure)
        txout1.pres_lift_re_demo = pres_lift_re;     // Lift Re pressure
        txout1.angle_lift_demo = angle_lift;
        txout1.angle_afe_demo = angle_AFE;
        txout1.angle_abc_demo = angle_ABC_supplement;
        txout1.liftposition = liftposition_;
        txout1.liftposition_rate = liftposition_rate_;
        txout1.tiltposition = tiltposition_;
        txout1.tiltposition_rate = tiltposition_rate_;
        txout1.payload = payload_;
        txout1.payload_rate = payload_rate_;
    }
}


void DemoApp::ReadDemoAppRosIn()
{
    using DemoAppReqstCommand = demo_app_interfaces::msg::DemoAppRequest;
    while (!requests_.empty()) {
        const RequestBatch request = std::move(requests_.front());
        requests_.pop_front();
        for (const auto& r : request.requests) {
            switch (r.command) {
            case (DemoAppReqstCommand::WRITE_LIFT_POSITION): {
                liftposition_ = r.arg;
                break;
            }
            case (DemoAppReqstCommand::WRITE_LIFT_POSITION_RATE): {
                liftposition_rate_ = r.arg;
                break;
            }
            case (DemoAppReqstCommand::WRITE_TILT_POSITION): {
                tiltposition_ = r.arg;
                break;
            }
            case (DemoAppReqstCommand::WRITE_TILT_POSITION_RATE): {
                tiltposition_rate_ = r.arg;
                break;
            }
            case (DemoAppReqstCommand::WRITE_PAYLOAD): {
                payload_ = r.arg;
                break;
            }
            case (DemoAppReqstCommand::WRITE_PAYLOAD_RATE): {
                payload_rate_ = r.arg;
                break;
            }
            case (DemoAppReqstCommand::DIG): {
                payload_rate_ = 20.f;
                payload_ = r.arg;
                tiltposition_ = 100.f;
                tiltposition_rate_ = 30.f; // Maximum Rack Speed
                liftposition_ = 10.f;
                liftposition_rate_ = 35.f; // Float Lower Speed
                break;
            }
            case (DemoAppReqstCommand::WRW): {
                liftposition_ = 90.f;
                liftposition_rate_ = 15.f; // Maximum Raise Speed
                break;
            }
            case (DemoAppReqstCommand::LLW): {
                liftposition_ = 45.f;
                liftposition_rate_ = 5.f; // Slow Raise Speed
                break;
            }
            case (DemoAppReqstCommand::DUMP): {
                tiltposition_ = 0.f;
                tiltposition_rate_ = 35.f; // Maximum Dump Speed
                break;
            }
            case (DemoAppReqstCommand::PDUMP): {
                payload_rate_ = 20.f;
                payload_ = r.arg;
                tiltposition_ = 65.f;
                tiltposition_rate_ = 35.f; // Maximum Dump Speed
                break;
            }
            case (DemoAppReqstCommand::CARRY): {
                tiltposition_ = 100.f;
                tiltposition_rate_ = 30.f; // Maximum Rack Speed
                liftposition_ = 10.f;
                liftposition_rate_ = 35.f; // Float Lower Speed
                break;
            }
            case (DemoAppReqstCommand::NONE):
            default: {
                break;
            }
            }
        }
    }
}

void DemoApp::startExecutiveTimer()
{
    if (!initialized_) {
        throw std::logic_error("DemoApp timer started before initialization");
    }
    createExecutiveTimer(50.0);
    healthTimer_ = create_wall_timer(std::chrono::seconds(1), [this]() { PublishHealth(); });
    state_ = Health::EXECUTIVE_RUNNING;
    PublishHealth();
}

void DemoApp::PublishHealth()
{
    if (!healthPublisher_) {
        return;
    }
    const auto now = Clock::now();
    const double elapsed = std::chrono::duration<double>(now - lastHealthTime_).count();
    Health health;
    health.session_id = sessionId_;
    health.report_sequence = ++healthSequence_;
    health.source = get_name();
    health.host = host_;
    health.process_id = static_cast<int32_t>(getpid());
    health.state = state_;
    health.logger_threshold = loggerThreshold_;
    health.intended_cycle_rate_hz = 50.0;
    health.cycle_rate_hz = sequence_ > lastHealthCycleCount_ ? cycleRate_ : 0.0;
    health.recent_executive_cycle_rate_hz = elapsed > 0.0 ?
        static_cast<double>(sequence_ - lastHealthCycleCount_) / elapsed : 0.0;
    health.longest_executive_cycle_sec = longestCycle_;
    health.longest_recent_executive_cycle_sec = longestRecentCycle_;
    health.total_executive_cycle_count = sequence_;
    health.total_executive_late_cycle_count = lateCycleCount_;
    // Inter-cycle non-executive time also includes subscription/health callbacks.
    // Leave the idle metric zero until the executor can measure actual idle time.
    health.executor_idle_time_sec = 0.0;
    healthPublisher_->publish(health);
    lastHealthTime_ = now;
    lastHealthCycleCount_ = sequence_;
    longestRecentCycle_ = 0.0;
}

void  DemoApp::cleanup( )
{
    state_ = Health::SHUTTING_DOWN;
    if (executiveTimer_) {
        executiveTimer_->cancel();
    }
    if (healthTimer_) {
        healthTimer_->cancel();
    }
    if (healthPublisher_ && rclcpp::ok()) {
        PublishHealth();
    }
    initialized_ = false;
    requests_.clear();
    requestSubscription_.reset();
    executiveTimer_.reset();
    healthTimer_.reset();
    cyclePublisher_.reset();
    healthPublisher_.reset();
    RCLCPP_INFO(get_logger(), "DemoApp::cleanup");
}
