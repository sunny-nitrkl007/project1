#ifndef PWMINPUTS_H_
#define PWMINPUTS_H_

#include <stdlib.h>
#include <stdio.h>
#include <cstdint>
#include <chrono>
#include <sys/time.h>
#include <fstream>
#include "ROS2Logger.hpp"

#define MAX_CH 4

#define CH_1_FILE_MODE_PWM  "echo 1 > /sys/class/tty/ttyS2/inputs/pwm_freq_stg_1/mode"
#define CH_2_FILE_MODE_PWM  "echo 1 > /sys/class/tty/ttyS2/inputs/pwm_freq_stg_2/mode"
#define CH_3_FILE_MODE_PWM  "echo 1 > /sys/class/tty/ttyS2/inputs/pwm_freq_stg_3/mode"
#define CH_4_FILE_MODE_PWM  "echo 1 > /sys/class/tty/ttyS2/inputs/pwm_freq_stg_4/mode"

#define PWM_ENABLE_FILE     "/sys/class/tty/ttyS2/inputs/coherent/enable"
#define PWM_DATA_FILE       "/sys/class/tty/ttyS2/inputs/coherent/data"
#define PWM_DEBUG_FILE       "/opt/Pwm_data.txt"

namespace weigh_data {

enum class PwmInputSwitchStatus : uint8_t {
    INACTIVE = 0,
    ACTIVE = 1,
    ERROR = 2,
    NORMAL = 3
};

enum class PwmInputTimeout : uint8_t {
    NOTIMEOUT = 0,
    TIMEOUT = 1
};

class PwmInputChannelsStorage
{
public:
     PwmInputChannelsStorage():
         PwmData(),
         PwmDataCurr(),
         PwmDataPrev() {}

    typedef struct PwmInput
    {
        long ActualTimeUs;
        int ExecTime;
        int DiffTime;
        unsigned int Exp;
        int Width[MAX_CH];
        int Period[MAX_CH];
        PwmInputSwitchStatus SwitchStatus[MAX_CH];
        PwmInputTimeout Timeout[MAX_CH];
        std::chrono::steady_clock::time_point timestamp;
    } PwmInputAttr_t;

    PwmInputAttr_t PwmData;

    bool initializeRead( )
    {
        system(CH_1_FILE_MODE_PWM);
        system(CH_2_FILE_MODE_PWM);
        system(CH_3_FILE_MODE_PWM);
        system(CH_4_FILE_MODE_PWM);

        return true;
    }

    void readPWMInputs( int t_us = 0 )
    {
        if (t_us <= 0) {
            auto us_between_samples = std::chrono::duration_cast<std::chrono::microseconds>(
                    PwmDataCurr.timestamp - PwmDataPrev.timestamp).count();

            if (t_us < us_between_samples) {
                for (unsigned int i = 0; i < sizeof(PwmData.Period)/sizeof(PwmData.Period[0]); ++i) {

                    {
                        float period_slope = float(PwmDataCurr.Period[i] - PwmDataPrev.Period[i]) / float(us_between_samples);
                        PwmData.Period[i] = PwmDataCurr.Period[i] - period_slope * t_us;
                    }

                    {
                        float width_slope = float(PwmDataCurr.Width[i] - PwmDataPrev.Width[i]) / float(us_between_samples);
                        PwmData.Width[i] = PwmDataCurr.Width[i] - width_slope * t_us;
                    }

                    if (PwmDataCurr.Timeout[i] == PwmInputTimeout::TIMEOUT) {
                        PwmData.Timeout[i] = PwmInputTimeout::TIMEOUT;
                        PwmData.SwitchStatus[i] = PwmDataCurr.SwitchStatus[i];
                    }
                    else if (PwmDataPrev.Timeout[i] == PwmInputTimeout::TIMEOUT) {
                        PwmData.Timeout[i] = PwmInputTimeout::TIMEOUT;
                        PwmData.SwitchStatus[i] = PwmDataPrev.SwitchStatus[i];
                    }
                    else {
                        PwmData.Timeout[i] = PwmInputTimeout::NOTIMEOUT;
                        PwmData.SwitchStatus[i] = PwmDataCurr.SwitchStatus[i];
                    }

                    PwmData.timestamp = PwmDataCurr.timestamp - std::chrono::microseconds(t_us);
                }
            }
            else {
                PwmData = PwmDataPrev;
            }
        }
        else {
            PwmData = PwmDataCurr;
        }
    }

    bool samplePWMInputs()
    {
        bool allOk = true;
        PwmInputAttr_t sample{};
        if (samplePWMInputs(sample)) {
            sample.timestamp = std::chrono::steady_clock::now();

            PwmDataPrev = PwmDataCurr;
            PwmDataCurr = sample;

            PwmData = PwmDataCurr;
        }
        else {
            allOk = false;
            RCLCPP_FATAL(ROS2Logger::Instance().GetLogger(), "Failed to read PWM Inputs data.");
        }

        return allOk;
    }

    std::chrono::steady_clock::time_point getLastSampleTime() const {
        return PwmDataCurr.timestamp;
    }

    int getLastSamplePeriod() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(PwmDataCurr.timestamp - PwmDataPrev.timestamp).count();
    }

private:
    PwmInputAttr_t PwmDataCurr;
    PwmInputAttr_t PwmDataPrev;

    static bool samplePWMInputs(PwmInputAttr_t& data) {
        bool allOk = true;
        int temp = 0;
        std::ifstream fin(PWM_DATA_FILE);
        if (fin) { fin >> data.Period[0]; } else { allOk = false; }

        if (fin) { fin >> data.Width[0]; } else { allOk = false; }

        if (fin) { fin >> temp; data.SwitchStatus[0] = static_cast<PwmInputSwitchStatus>(temp); } else { allOk = false; }

        if (fin) { fin >> temp; data.Timeout[0] = static_cast<PwmInputTimeout>(temp); } else { allOk = false; }

        if (fin) { fin >> data.Period[1]; } else { allOk = false; }

        if (fin) { fin >> data.Width[1]; } else { allOk = false; }

        if (fin) { fin >> temp; data.SwitchStatus[1] = static_cast<PwmInputSwitchStatus>(temp); } else { allOk = false; }

        if (fin) { fin >> temp; data.Timeout[1] = static_cast<PwmInputTimeout>(temp); } else { allOk = false; }

        if (fin) { fin >> data.Period[2]; } else { allOk = false; }

        if (fin) { fin >> data.Width[2]; } else { allOk = false; }

        if (fin) { fin >> temp; data.SwitchStatus[2] = static_cast<PwmInputSwitchStatus>(temp); } else { allOk = false; }

        if (fin) { fin >> temp; data.Timeout[2] = static_cast<PwmInputTimeout>(temp); } else { allOk = false; }

        if (fin) { fin >> data.Period[3]; } else { allOk = false; }

        if (fin) { fin >> data.Width[3]; } else { allOk = false; }

        if (fin) { fin >> temp; data.SwitchStatus[3] = static_cast<PwmInputSwitchStatus>(temp); } else { allOk = false; }

        if (fin) { fin >> temp; data.Timeout[3] = static_cast<PwmInputTimeout>(temp); } else { allOk = false; }

        allOk = allOk && !fin.fail();
        if (fin.is_open()) {
            fin.close();
        }

        return allOk;
    }
};

using PwmInputChannels = PwmInputChannelsStorage;
using PwmInputs = PwmInputChannelsStorage;

}

#endif
