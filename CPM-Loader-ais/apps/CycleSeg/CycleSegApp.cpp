#include <thread>
#include <chrono>

#include <ais/task/Task.h>
#include <ais/log/Logger.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <LIBINFO_WL_if.h>
#include <LIBINFO_WL_00_po.h>

#ifdef __cplusplus
}
#endif

#include "CycleSegApp.h"
#include <clock_proto.h>
#include <scl_prmsw.h>
#include <lps_sea_defs.h>

#define APP_REG_PUBLISH_PERIOD_SEC (10.0f)

/*
 * main() will call this function in order to get the task instance.
 */
task::AbstractTaskCore* task::getTaskImplementation(void) {
    static CycleSegApp thisTask("CycleSeg");
    return dynamic_cast<Task*>(&thisTask);
}

/*
 * Constructor
 */
CycleSegApp::CycleSegApp(const std::string& taskName) :
    task::Task(taskName),
    modelInitialized_(false),
    input_(),
    output_(),
    appRegInputChannel_(nullptr),
    appRegOutputChannel_(nullptr),
    autonomyConditionDiagnosticsTxInputChannel_(nullptr),
    appRegMap_(),
    appRegUpdateCount_(0),
    enableWriteVp3Record(false){
}

/*
 * Destructor
 */
CycleSegApp::~CycleSegApp() {
}

/*
 * AIS Task Initializer
 */
bool CycleSegApp::initialize() {
    uint16_t appNumber = 0;
    bool everythingOk = true;
    AIS_LOG_INFO("CycleSegApp::initialize");

    // These are the apps that we need to stay alive until we are done
    appRegMap_.clear();
    appRegMap_["VP3FileCreationApp"] = false;
    appRegMap_["BmiJ1939_CANB"] = false;     // Send reg req based on instance name to BmiJ1939
    appRegMap_["BmiJ1939_CANA"] = false;


    { // Read Config
        ConfigSection machineConfig;
        if (!getTaskParser().getSection("MachineSpecificConfig", machineConfig)) {
            AIS_LOG_ERROR("MachineSpecificConfig section not found.");
            everythingOk = false;
        }
        else if (!machineConfig.get("CycleSegAppNumber", appNumber)) {
            AIS_LOG_WARN("CycleSegAppNumber config not found.");
            everythingOk = false;
        }
    }

    // If we don't have an application number, log an error and run.
    // Returning true here to have cycle seg just log an error if is not supported, otherwise it would crash
    if ((0 == appNumber) || !everythingOk) {
        AIS_LOG_ERROR("CycleSeg not supported for this machine configuration.");
        return true;
    }

    // Initialize interfaces
    if (!task::InterfaceDb::bind("AppRegInput", appRegInputChannel_)) {
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("AppRegOutput", appRegOutputChannel_)) {
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("AutonomyConditionDiagnosticsTxChannelInput", autonomyConditionDiagnosticsTxInputChannel_)) {
        everythingOk = false;
    }

    // Initialize input processing
    if (!input_.initialize(appNumber, getTaskConfig())) {
        everythingOk = false;
    }

    // Initialize cycle segmentation
    LIBINFO_WL_00_po_init();
    modelInitialized_ = true;

    // Initialize output processing
    if (!output_.initialize()) {
        everythingOk = false;
    }

    return everythingOk;
}

/*
 * AIS Task Executive
 */
bool CycleSegApp::executive() {
    AIS_LOG_DEBUG("CycleSegApp::executive");

    if (!modelInitialized_)
        return true;

    /* Disable sending out vp3 files if SEA is not installed. We only check for
     * level2 (Pro) SEA because on AU2020 that is all we care about. On standalone,
     * we do not run the cycle seg app */
    if (nullptr != autonomyConditionDiagnosticsTxInputChannel_) {
        AutonomyConditionDiagnosticsTxInterface txData;
        while ( autonomyConditionDiagnosticsTxInputChannel_->get( txData ) )
        {
            for (const auto & element : txData.seaList){
                if (element.reason_code == LPS_SEA_REASON_CODE_245) {
                    enableWriteVp3Record = txData.checkSEAEnableStatus(element.status);
                    break;
                }
            }
        }
    }

    // Take care of app registration.
    if (nullptr != appRegInputChannel_) {
        AppReg data;
        while (appRegInputChannel_->get(data)) {
            if (data.IsMsgAddressedToMe(getTaskName())) {
                if (AppReg::APP_REG_RESP == data.GetMsgType()) {
                    const std::string& srcAppName = data.GetAppName();
                    auto search = appRegMap_.find(srcAppName);
                    if (search != appRegMap_.end()) {
                        // Found it.
                        AppReg::AppRegRet_t status = data.GetRegStatus();
                        if ((AppReg::APP_REG_APP_NAME_REGISTERED == status) ||
                                (AppReg::APP_REG_APP_NAME_ALREADY_REGISTERED == status)) {
                            AIS_LOG_NOTICE("Registered with %s", srcAppName.c_str());
                            search->second = true;
                        }
                        else {
                            search->second = false;
                        }
                    }
                }
            }
        }
    }

    // Handle periodic app registration if not already registered
    if  (nullptr != appRegOutputChannel_) {
        float maxUpdateCount = APP_REG_PUBLISH_PERIOD_SEC * static_cast<float>(getCycleRateHz());
        ++appRegUpdateCount_;
        if (appRegUpdateCount_ >= maxUpdateCount) {
            // Loop over each app to register with and send registration request
            for (const auto& kv : appRegMap_) {
                if (!kv.second) {
                    AppReg data;
                    data.SetAppRegAttr(getTaskName(), AppReg::APP_REG_STATE_ACTIVE, kv.first);
                    if (appRegOutputChannel_->publish(data)) {
                        AIS_LOG_NOTICE("Requesting to register with %s", kv.first.c_str());
                    }
                }
            }
        }
    }

    // Inputs
    input_.update();

    // Update cycle segmentation (0.120 second period)
    LIBINFO_WL_00_po_0();

    // Outputs - Skip VP3 records if NOT enabled
    output_.update(!enableWriteVp3Record);

    return true;
}

/*
 * AIS Task Cleanup
 */
void CycleSegApp::cleanup() {
    AIS_LOG_INFO("CycleSegApp::cleanup");

    // If the model was initialized.
    if (modelInitialized_) {
        // Keep running as long as we need to stay alive.
        float cycleRateHertz = static_cast<float>(getCycleRateHz());
        if (cycleRateHertz > 0) {
            uint32_t periodMicroseconds = static_cast<uint32_t>(1000000.f / cycleRateHertz);

            auto lastUpdateTime = std::chrono::steady_clock::now();

            do {
                // Wait until it is time to run
                std::this_thread::sleep_until(lastUpdateTime + std::chrono::microseconds(periodMicroseconds));

                // Get the update time
                lastUpdateTime = std::chrono::steady_clock::now();

                // Update
                executive();

                /* break out of loop, if the active segment id is
                 *  NOT key off engine off(27) AND NOT key off engine ON(28), which
                 *  means that key is back on and also the last key off segment has
                 *  been committed. So it is safe to continue shutting down.. */
                if ((27 != segment_active_segment_id) && (28 != segment_active_segment_id)) {
                    break;
                }

                AIS_LOG_INFO("keyswitch_override_flag set");

            } while (keyswitch_override_flag);
        }
    }


    if  (nullptr != appRegOutputChannel_) {
        // Loop over each app and unregister
        for (const auto& kv : appRegMap_) {
            AppReg data;
            data.SetAppRegAttr(getTaskName(), AppReg::APP_REG_STATE_INACTIVE, kv.first);
            appRegOutputChannel_->publish(data);
        }
    }
}
