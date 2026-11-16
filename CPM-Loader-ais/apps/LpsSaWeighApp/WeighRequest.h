#ifndef WEIGHREQUEST_H_
#define WEIGHREQUEST_H_

#include <atomic>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace weigh_data {

class Request {
public:
    enum class Command : uint8_t {
        NONE,
        WRITE_OVERLOAD_WARNING_ENABLE,
        WRITE_BUCKET_PAYLOAD_TARGET_WEIGHT,
        ZERO,
        RESET_BEST_BUCKET_WEIGHT,
        CAPTURE_CYLINDER_EXTENSION_REFERENCE,
        CLEAR_REWEIGH_WARNING,
        WRITE_WEIGH_RANGE,
        WRITE_CALIBRATION_WEIGHT,
        WRITE_MACHINE_PITCH_CAL_OFFSET,
        WRITE_HYD_OIL_TEMP_ENABLE,
        WRITE_AUDIBLE_WEIGHT_ENABLE,
        WRITE_LFT_SEALED,
        WRITE_LFT_SEALED_FLASH_ENABLE,
        WRITE_LIFT_POSITION_SENSOR_ID,
        WRITE_TILT_POSITION_SENSOR_ID,
        WRITE_LIFT_HE_PRESSURE_SENSOR_ID,
        WRITE_LIFT_RE_PRESSURE_SENSOR_ID,
        WRITE_HYDRAULIC_OIL_TEMP_SENSOR_ID,
        WRITE_PAYLOAD_OUT_OF_CAL,
        NOTIFY_TICKET_NUMBER_WRITE,
        PUBLISH_SERVICE_HISTORY,
        WRITE_WORK_TOOL_ID,
        PUBLISH_LIFT_SENSOR_CALIBRATION,
        PUBLISH_TILT_SENSOR_CALIBRATION,
        PUBLISH_WEIGH_CALIBRATION,
        PUBLISH_WEIGH_CONFIGURATION,
        PUBLISH_RECENT_WEIGH_RESULTS,
        WRITE_REWEIGH_MAX_PITCH,
        WRITE_REWEIGH_MIN_PITCH,
        WRITE_REWEIGH_MAX_ABS_ROLL,
        WRITE_REWEIGH_MIN_LIFT_CYL_VEL,
        WRITE_ADVANCED_CALIBRATION_ADJUSTMENT,
        RUN_TEST,
        RECORD_TEST,
        WRITE_IMU_COMP_ENABLE,
    };

    std::string appName;
    uint32_t appRequestId;
    Command command;

    struct {
        bool b;
        float f1;
        float f2;
        std::string s;
        uint32_t u;
        std::vector<std::pair<float, float>> map;
    } arg;

    Request() :
        appName(),
        appRequestId(0),
        command(Command::NONE),
        arg{ false, 0.f, 0.f, "", 0, {} } {}

    void reInit() {
        *this = Request();
    }

    static uint32_t getNextAppRequestId() {
        static std::atomic<uint32_t> nextAppRequestId(0);
        return nextAppRequestId++;
    }
};

using WeighReqstChannelCommand = Request::Command;
using LpsSaWeighReqstChannelStorage = Request;
using LpsSaWeighReqstChannel = Request;

}

#endif
