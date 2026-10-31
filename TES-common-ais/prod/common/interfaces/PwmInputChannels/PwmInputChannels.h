/*******************************************************************************
** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: PwmOutputCh.h
DESCRIPTION:
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <sys/time.h>
#include <ais/serialization/Datum.h> // For Boost serialization
#include <ais/log/AisLogger.h>
#include <fstream>


/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

#ifndef _PwmInputChannels_h_
#define _PwmInputChannels_h_

#define MAX_CH 4

#define CH_1_FILE_MODE_PWM  "echo 1 > /sys/class/tty/ttyS2/inputs/pwm_freq_stg_1/mode"
#define CH_2_FILE_MODE_PWM  "echo 1 > /sys/class/tty/ttyS2/inputs/pwm_freq_stg_2/mode"
#define CH_3_FILE_MODE_PWM  "echo 1 > /sys/class/tty/ttyS2/inputs/pwm_freq_stg_3/mode"
#define CH_4_FILE_MODE_PWM  "echo 1 > /sys/class/tty/ttyS2/inputs/pwm_freq_stg_4/mode"

#define PWM_ENABLE_FILE     "/sys/class/tty/ttyS2/inputs/coherent/enable"
#define PWM_DATA_FILE       "/sys/class/tty/ttyS2/inputs/coherent/data"
#define PWM_DEBUG_FILE       "/opt/Pwm_data.txt"

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

class PwmInputChannelsStorage : public csvable
{  
public:  
     PwmInputChannelsStorage():
         PwmData(),
         PwmDataCurr(),
         PwmDataPrev() {}

    typedef struct PwmInput
    {
        long ActualTimeUs;	        // actual time in micro-seconds, wrapps around every 99,999
        int ExecTime;			// execution time in ms to create record
        int DiffTime;			// difference from previous actualTimeus, im micro-seconds
        unsigned int Exp;		// number of times timer expired since last read(), should always be 1
        int Width[MAX_CH];	        // pulse width in micro-seconds, range "0" .. "19999"
        int Period[MAX_CH];	        // pulse period in micro-seconds,range "0" .. "19999"
        PwmInputSwitchStatus SwitchStatus[MAX_CH];  // 0:inactive, 1:active, 2:error, 3:normal
        PwmInputTimeout Timeout[MAX_CH];       // 1:timeout, 0:not timedout
        std::chrono::steady_clock::time_point timestamp;  /* timestamp of last sampled input*/
    } PwmInputAttr_t;

    PwmInputAttr_t PwmData;

    /******************************************************************************
    FUNCTION initializeRead
    DESCRIPTION: Initialize the PWM Read. This must be called once in order to
                 read the PWM inputs
    PARAMETER DESCRIPTION:
    RETURN VALUE:
    *******************************************************************************/
    bool initializeRead( )
    {
        system(CH_1_FILE_MODE_PWM);
        system(CH_2_FILE_MODE_PWM);
        system(CH_3_FILE_MODE_PWM);
        system(CH_4_FILE_MODE_PWM);

        return true;
    }

    /* Read PWMinputs with argument t_us argument (optional)
     *    If t_us <= 0, current sample
     *    else, inputs at t_us microseconds ago from the last sampled data point
     */
    void readPWMInputs( int t_us = 0 )
    {
        if (t_us <= 0) {
            /* linear interpolation to get sample at t_us microseconds ago */
            auto us_between_samples = std::chrono::duration_cast<std::chrono::microseconds>(
                    PwmDataCurr.timestamp - PwmDataPrev.timestamp).count();

            if (t_us < us_between_samples) {
                for (unsigned int i = 0; i < sizeof(PwmData.Period)/sizeof(PwmData.Period[0]); ++i) {

                    { // Interpolate period
                        float period_slope = float(PwmDataCurr.Period[i] - PwmDataPrev.Period[i]) / float(us_between_samples);
                        PwmData.Period[i] = PwmDataCurr.Period[i] - period_slope * t_us;
                    }

                    { // Interpolate pulse width
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
                /* if looking for something that is older than the prev sample, return prev sample */
                PwmData = PwmDataPrev;
            }
        }
        else {
            /* current sample */
            PwmData = PwmDataCurr;
        }
    }

    /* Sample the pwm input driver */
    bool samplePWMInputs()
    {
        bool allOk = true;
        PwmInputAttr_t sample;
        if (samplePWMInputs(sample)) {
            // capture timestamp
            sample.timestamp = std::chrono::steady_clock::now();

            PwmDataPrev = PwmDataCurr;
            PwmDataCurr = sample;

            // Pre-load the PwmData with the most recent sample.
            PwmData = PwmDataCurr;
        }
        else {
            allOk = false;
            AIS_LOG_FATAL("Failed to read PWM Inputs data.");
        }

        return allOk;
    }

    std::chrono::steady_clock::time_point getLastSampleTime() const {
        return PwmDataCurr.timestamp;
    }

    int getLastSamplePeriod() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(PwmDataCurr.timestamp - PwmDataPrev.timestamp).count();
    }

    /******************************************************************************
    FUNCTION NAME:toCsv
    DESCRIPTION: Width and period is provided to CSV file
    PARAMETER DESCRIPTION:
    RETURN VALUE:
    *******************************************************************************/
    void toCsv(CsvOutStream& out) const
    {
        out("ActualTimeUs",  PwmData.ActualTimeUs);
        out("ExecTime",  PwmData.ExecTime);
        out("DiffTime",  PwmData.DiffTime);
        out("Exp",  PwmData.Exp);

        for (int i=0;i<MAX_CH;i++)
        {
            out("width",  PwmData.Width[i]);
            out("period",  PwmData.Period[i]);
            out("switch status",  static_cast<uint8_t>(PwmData.SwitchStatus[i]));
            out("timeout",  static_cast<uint8_t>(PwmData.Timeout[i]));
        }
    }

    /******************************************************************************
    FUNCTION NAME:serialize
    DESCRIPTION: Serialization is required for packing of the data
    PARAMETER DESCRIPTION:
    RETURN VALUE:
    *******************************************************************************/
    template <class Archive>
    void serialize(Archive &ar, unsigned int version)
    {
        /* Archive Fields Here */
        ar & PwmData.ActualTimeUs;	        // actual time in micro-seconds, wrapps around every 99,999
        ar & PwmData.ExecTime;			// execution time in ms to create record
        ar & PwmData.DiffTime;			// difference from previous actualTimeus, im micro-seconds
        ar & PwmData.Exp;		        // number of times timer expired since last read(), should always be 1

        for (int i=0;i<MAX_CH;i++)
        {
            ar & PwmData.Width[i];	               // pulse width in micro-seconds, range "0" .. "19999"
            ar & PwmData.Period[i];                // pulse period in micro-seconds,range "0" .. "19999"
            if (version >= 2) {
                ar & PwmData.SwitchStatus[i];
                ar & PwmData.Timeout[i];
            }
        }
    }

private:
    /* Add Fields Here */
    PwmInputAttr_t PwmDataCurr;
    PwmInputAttr_t PwmDataPrev;

    static bool samplePWMInputs(PwmInputAttr_t& data) {
        bool allOk = true;
        int temp;
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

        if (fin.is_open()) {
            fin.close();
        }

        return allOk;
    }
};  

typedef Datum<PwmInputChannelsStorage> PwmInputChannels;

BOOST_CLASS_VERSION(PwmInputChannelsStorage, 2);
#endif

