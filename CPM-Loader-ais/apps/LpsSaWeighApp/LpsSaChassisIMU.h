#ifndef LPSSACHASSISIMU_H_
#define LPSSACHASSISIMU_H_

#include <algorithm>

#include <std_t.h>
#include <oel_pack.h>

#include <ais/config/TaskParser.h>
#include <ais/config/ConfigSection.h>

#include <rclcpp/rclcpp.hpp>

#include <interfaces/DataLinkData/DataLinkParam.h>
#include "ROS2Logger.hpp"
#include <imu/imu.hpp>

#include "LpsSaIncludes.h"
#include "LpsSaWeighAppTestFixture.h"

namespace {
    namespace imu = tes_common_ais::imu;
}

#define LPS_SA_IMU_SENSOR_STATUS_OK (0)
#define LPS_SA_IMU_SENSOR_STATUS_DEGRADED (1)
#define LPS_SA_IMU_SENSOR_STATUS_ERROR (2)
#define LPS_SA_IMU_SENSOR_STATUS_NOT_AVAILABLE (3)
#define LPS_SA_IMU_SENSOR_STATUS_OUT_OF_RANGE (4)
#define LPS_SA_IMU_SENSOR_STATUS_COMM_FAULT (5)

class LpsSaChassisIMU {
public:
    static const imu::IMU::Config& defaultIMUConfig() {
        static const imu::IMU::Config config {
            0.02f, // Update period in seconds
            { // Bias config
                0.013245f, // Jerk Filter Factor (1.5 second time constant)
                0.013245f, // Angular Accel Filter Factor (1.5 second time constant)
                0.006263f, // Low pass filter factor for bias estimation (0.05 Hz, about 3 second time constant)
                0.1f, // Linear speed threshold to enable bias estimation (m/s)
                10.f, // Jerk threshold to enable bias estimation (m/s^3)
                2.f, // Angular acceleration threshold to enable bias estimation (rad/s^2)
                0.07f, // Angular velocity threshold to enable bias estimation (rad/s)
                0.3f // Time for conditions to be true before updating bias estimation (seconds)
            },
            1.f - 0.01f, // Angle Fusion (0.5 rad/s)
            0.672621f, // Roll Filter (10Hz)
            7.5f, // Pitch Notch Filter (rad/s, ~1.2 Hz)
            0.75f, // Pitch Notch Damping Ratio
            0.672621f, // Pitch Filter (10Hz)
            1.f - 0.058219f // Velocity Fusion (3 rad/s)
        };
        return config;
    }

    imu::IMU::Vector sensorLinAcc;
    uint_least8_t sensorLinAccStatus;
    bool sensorLinAccOk;

    imu::IMU::Vector sensorAngVel;
    uint_least8_t sensorAngVelStatus;
    bool sensorAngVelOk;

    imu::IMU::Vector refLinVel;
    bool refLinVelOk;

    bool inhibitBiasEstimation;

    imu::IMU imu;
    bool imuOk;

    LpsSaChassisIMU() :
        sensorLinAcc(),
        sensorLinAccStatus(LPS_SA_IMU_SENSOR_STATUS_NOT_AVAILABLE),
        sensorLinAccOk(false),
        sensorAngVel(),
        sensorAngVelStatus(LPS_SA_IMU_SENSOR_STATUS_NOT_AVAILABLE),
        sensorAngVelOk(false),
        refLinVel(),
        refLinVelOk(false),
        inhibitBiasEstimation(false),
        imu(),
        imuOk(false) {}

    bool init(rclcpp::Node& node) {
        imu::IMU::Config config = defaultIMUConfig();

        // All ChassisIMU and cycle-rate parameters are declared with defaults
        // matching LpsSaWeighApp.rb values. YAML overrides take effect here.
        // cycle_rate_hz is already declared in LpsSaWeighApp.cpp initialize();
        // read it directly without re-declaring.
        {
            double cycleRate_hz = node.get_parameter("cycle_rate_hz").as_double();
            if (cycleRate_hz > 0.0) {
                config.updatePeriodSeconds = static_cast<float>(1.0 / cycleRate_hz);
            }
        }

        // Declare ChassisIMU params with .rb defaults; YAML can override any of them.
        node.declare_parameter<double>("chassis_imu.bias_jerk_filter_factor",       0.013245);
        node.declare_parameter<double>("chassis_imu.bias_ang_accel_filter_factor",  0.013245);
        node.declare_parameter<double>("chassis_imu.bias_filter_factor",            0.006263);
        node.declare_parameter<double>("chassis_imu.bias_speed_threshold",          0.1);
        node.declare_parameter<double>("chassis_imu.bias_jerk_threshold",           10.0);
        node.declare_parameter<double>("chassis_imu.bias_ang_accel_threshold",      2.0);
        node.declare_parameter<double>("chassis_imu.bias_ang_vel_threshold",        0.07);
        node.declare_parameter<double>("chassis_imu.bias_debounce_time_seconds",    0.3);
        node.declare_parameter<double>("chassis_imu.ang_fusion_filter_factor",      1.0 - 0.01);
        node.declare_parameter<double>("chassis_imu.roll_filter_factor",            0.672621);
        node.declare_parameter<double>("chassis_imu.pitch_notch_frequency",         7.5);
        node.declare_parameter<double>("chassis_imu.pitch_notch_damping",           0.75);
        node.declare_parameter<double>("chassis_imu.pitch_filter_factor",           0.672621);
        node.declare_parameter<double>("chassis_imu.vel_fusion_filter_factor",      1.0 - 0.058219);

        config.bias.jerkFilterFactor      = static_cast<float>(node.get_parameter("chassis_imu.bias_jerk_filter_factor").as_double());
        config.bias.angAccelFilterFactor  = static_cast<float>(node.get_parameter("chassis_imu.bias_ang_accel_filter_factor").as_double());
        config.bias.biasFilterFactor      = static_cast<float>(node.get_parameter("chassis_imu.bias_filter_factor").as_double());
        config.bias.speedThreshold        = static_cast<float>(node.get_parameter("chassis_imu.bias_speed_threshold").as_double());
        config.bias.jerkThreshold         = static_cast<float>(node.get_parameter("chassis_imu.bias_jerk_threshold").as_double());
        config.bias.angAccelThreshold     = static_cast<float>(node.get_parameter("chassis_imu.bias_ang_accel_threshold").as_double());
        config.bias.angVelThreshold       = static_cast<float>(node.get_parameter("chassis_imu.bias_ang_vel_threshold").as_double());
        config.bias.debounceTimeSeconds   = static_cast<float>(node.get_parameter("chassis_imu.bias_debounce_time_seconds").as_double());
        config.angFusionFilterFactor      = static_cast<float>(node.get_parameter("chassis_imu.ang_fusion_filter_factor").as_double());
        config.rollFilterFactor           = static_cast<float>(node.get_parameter("chassis_imu.roll_filter_factor").as_double());
        config.pitchNotchFrequency        = static_cast<float>(node.get_parameter("chassis_imu.pitch_notch_frequency").as_double());
        config.pitchNotchDamping          = static_cast<float>(node.get_parameter("chassis_imu.pitch_notch_damping").as_double());
        config.pitchFilterFactor          = static_cast<float>(node.get_parameter("chassis_imu.pitch_filter_factor").as_double());
        config.velFusionFilterFactor      = static_cast<float>(node.get_parameter("chassis_imu.vel_fusion_filter_factor").as_double());

        /*
         * Default calibration rotation matrix
         * The chassis imu is mounted where Z-FWD, Y-RIGHT, X-UP.
         * We need the following rotation matrix to align it with the chassis.
         * [  0  0  1  ]
         * [  0  1  0  ]
         * [ -1  0  0  ]
         */
        const imu::IMU::RMatrix defaultCalMatrix {
            -imu::IMU::Vector::UnitZAxis,
            imu::IMU::Vector::UnitYAxis,
            imu::IMU::Vector::UnitXAxis,
        };


        // We should pull the config data from the ruby file, but just sticking with default for now.
        imu = imu::IMU(config, defaultCalMatrix);

        sensorLinAccStatus = LPS_SA_IMU_SENSOR_STATUS_OK;
        sensorLinAccOk = false;
        sensorAngVelStatus = LPS_SA_IMU_SENSOR_STATUS_OK;
        sensorAngVelOk = false;
        refLinVelOk = false;
        inhibitBiasEstimation = false;
        imuOk = false;

        return true;
    }

    void rxPGN61485(const uint8_t* rxBuf, uint8_t len, uint16_t dsi) {
        if ((nullptr != rxBuf) && (DataLinkParam::DSI_CODE_OK() == dsi) && (len >= 7)) {
            bool outOfRange = false;

            // Data Length:    2 bytes
            // Resolution: 0.01 m/s^2 per bit, Offset = -320 m/s^2
            // Data Range: -320 to 322.55 m/s^2
            // Operational Range:  Same as data range

            // This PGN is defined Z-UP, X-FORWARD, Y-LEFT
            imu::IMU::Vector v;
            uint16_t temp;

            // Unpack lateral acceleration
            OEL_UNPACK_LE_16(rxBuf, temp);

            if (temp > 64255) {
                outOfRange = true;
            }

            v.y() = (float)temp * 0.01f - 320.f;

            // Unpack longitudinal acceleration
            OEL_UNPACK_LE_16(rxBuf, temp);

            if (temp > 64255) {
                outOfRange = true;
            }

            v.x() = (float)temp * 0.01f - 320.f;

            // Unpack vertical acceleration
            OEL_UNPACK_LE_16(rxBuf, temp);

            if (temp > 64255) {
                outOfRange = true;
            }

            v.z() = (float)temp * 0.01f - 320.f;

            // Unpack the Figure of Merit
            uint8_t fom;
            OEL_UNPACK_LE_8_NO_INCR(rxBuf, fom);

            // Convert to Z-DOWN coordinate system
            v.y() *= -1.f;
            v.z() *= -1.f;

            // Linear acceleration is in m/s^2, Z-DOWN system
            sensorLinAcc = v;

            if (outOfRange) {
                sensorLinAccStatus = LPS_SA_IMU_SENSOR_STATUS_OUT_OF_RANGE;
                sensorLinAccOk = false;
            }
            else { // Check Figure of Merit
                uint8_t latAccFOM = (fom >> 0) & 0x03;
                uint8_t lonAccFOM = (fom >> 2) & 0x03;
                uint8_t vertAccFOM = (fom >> 4) & 0x03;
                uint8_t accFOM = std::max(std::max(latAccFOM, lonAccFOM), vertAccFOM);

                if (0 == accFOM) {
                    sensorLinAccStatus = LPS_SA_IMU_SENSOR_STATUS_OK;
                    sensorLinAccOk = true;
                }
                else if (1 == accFOM) {
                    sensorLinAccStatus = LPS_SA_IMU_SENSOR_STATUS_DEGRADED;
                    sensorLinAccOk = true;
                }
                else if (2 == accFOM) {
                    sensorLinAccStatus = LPS_SA_IMU_SENSOR_STATUS_ERROR;
                    sensorLinAccOk = false;
                }
                else {
                    sensorLinAccStatus = LPS_SA_IMU_SENSOR_STATUS_NOT_AVAILABLE;
                    sensorLinAccOk = false;
                }
            }
        }
        else {
            sensorLinAccStatus = LPS_SA_IMU_SENSOR_STATUS_COMM_FAULT;
            sensorLinAccOk = false;
        }
    }

    void rxPGN61482(const uint8_t* rxBuf, uint8_t len, uint16_t dsi) {
        if ((nullptr != rxBuf) && (DataLinkParam::DSI_CODE_OK() == dsi) && (len >= 7)) {
            bool outOfRange = false;

            // Data Length:    2 bytes
            // Resolution: 0.007 812 5 deg/s per bit, Offset = -250 deg/s
            // Data Range: -250 to 251.992 187 5 deg/s
            // Operational Range:  Same as data range

            // This PGN is defined Z-DOWN, X-FORWARD, Y-RIGHT
            imu::IMU::Vector v;
            uint16_t temp;

            // Unpack pitch rate
            OEL_UNPACK_LE_16(rxBuf, temp);

            if (temp > 64255) {
                outOfRange = true;
            }

            v.y() = (float)temp * 0.0078125f - 250.f;

            // Unpack roll rate
            OEL_UNPACK_LE_16(rxBuf, temp);

            if (temp > 64255) {
                outOfRange = true;
            }

            v.x() = (float)temp * 0.0078125f - 250.f;

            // Unpack yaw rate
            OEL_UNPACK_LE_16(rxBuf, temp);

            if (temp > 64255) {
                outOfRange = true;
            }

            v.z() = (float)temp * 0.0078125f - 250.f;

            // Unpack the Figure of Merit
            uint8_t fom;
            OEL_UNPACK_LE_8_NO_INCR(rxBuf, fom);

            // Convert from deg/s to rad/s
            v *= float(PI / 180);

            // Angular Velocity is in rad/s, Z-DOWN system
            sensorAngVel = v;

            if (outOfRange) {
                sensorAngVelStatus = LPS_SA_IMU_SENSOR_STATUS_OUT_OF_RANGE;
                sensorAngVelOk = false;
            }
            else { // Check Figure of Merit
                uint8_t pitchRateFOM = (fom >> 0) & 0x03;
                uint8_t rollRateFOM = (fom >> 2) & 0x03;
                uint8_t yawRateFOM = (fom >> 4) & 0x03;
                uint8_t rateFOM = std::max(std::max(pitchRateFOM, rollRateFOM), yawRateFOM);

                if (0 == rateFOM) {
                    sensorAngVelStatus = LPS_SA_IMU_SENSOR_STATUS_OK;
                    sensorAngVelOk = true;
                }
                else if (1 == rateFOM) {
                    sensorAngVelStatus = LPS_SA_IMU_SENSOR_STATUS_DEGRADED;
                    sensorAngVelOk = true;
                }
                else if (2 == rateFOM) {
                    sensorAngVelStatus = LPS_SA_IMU_SENSOR_STATUS_ERROR;
                    sensorAngVelOk = false;
                }
                else {
                    sensorAngVelStatus = LPS_SA_IMU_SENSOR_STATUS_NOT_AVAILABLE;
                    sensorAngVelOk = false;
                }
            }
        }
        else {
            sensorAngVelStatus = LPS_SA_IMU_SENSOR_STATUS_COMM_FAULT;
            sensorAngVelOk = false;
        }
    }

    void rxPIDF4FD(int16_t value, uint16_t dsi) {
        if (DataLinkParam::DSI_CODE_OK() == dsi) {
            imu::IMU::Vector v;
            // Datalink value is 0.0036 km/hr/bit, which is mm/s
            // We want m/s
            v.x() = (float)value * 0.001f;
            refLinVel = v;
            refLinVelOk = true;
        }
        else {
            refLinVelOk = false;
        }
    }

    /*
     * Receive Machine Idle Status and inhibit bias estimation if not idle
     */
    void rxPIDD10AB5(uint16_t value, uint16_t dsi) {
        /*
         * Machine idle statue = Not Idle
         * if
         * {
         *     Ground Speed != 0
         *     OR
         *     Actual Gear != Neutral
         *     OR
         *     Implement Operating Status != Inactive
         *     OR
         *     Calibration Status = Active
         * }
         */
        if ((DataLinkParam::DSI_CODE_OK() == dsi) &&
                (0x043A == value) /* Not Idle */) {
            inhibitBiasEstimation = true;
        }
        else {
            inhibitBiasEstimation = false;
        }
    }

    void update(LpsSaWeighAppTestFixture& testFixture) {

        // Support test fixture testpoints
        if (testFixture.tpIMUAcceleration(sensorLinAcc)) {
            sensorLinAccStatus = LPS_SA_IMU_SENSOR_STATUS_OK;
            sensorLinAccOk = true;
        }

        if (testFixture.tpIMUAngularVelocity(sensorAngVel)) {
            sensorAngVelStatus = LPS_SA_IMU_SENSOR_STATUS_OK;
            sensorAngVelOk = true;
        }

        // Make sure we are receiving the data.
        if (sensorLinAccOk && sensorAngVelOk) {
            if (refLinVelOk) {
                imu.update(sensorLinAcc, sensorAngVel, refLinVel, inhibitBiasEstimation);
            }
            else {
                // We should have a fault active in this case, but we can still limp along without knowing ground speed.
                imu.update(sensorLinAcc, sensorAngVel, imu::IMU::Vector(0.f, 0.f, 0.f), true);
            }
            imuOk = true;
        }
        else {
            // Something is broken, reset the processing
            imu.reset();
            imuOk = false;
        }
    }

protected:
private:
};

#endif /* LPSSACHASSISIMU_H_ */
