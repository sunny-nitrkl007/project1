#pragma once

#ifndef CHRONO_CONVERT_HPP_
#define CHRONO_CONVERT_HPP_

#include <cstdint>
#include <ctime>
#include <chrono>

namespace tes_common_ais {
    namespace {
        using SystemClock = std::chrono::system_clock;
        using SystemClockTimePoint = SystemClock::time_point;

        class UIDTimeEpoch {
        public:
            /*
             * It is unclear whether or not the UID time is leap second adjusted properly.
             * Is it atomic time (GPS) or astronomical time (UTC)?
             * The UID definition says that it is both UTC and GPS time, which is impossible.
             * The definition is taken to be UTC time (leap second adjusted) with the GPS
             * time epoch of 1/6/1980 00:00:00.
             */
            static constexpr std::tm epoch{
                0, // tm_sec
                0, // tm_min
                0, // tm_hour
                6, // tm_mday
                0, // tm_mon
                80, // tm_year
                -1, // tm_wday (unspecified)
                -1, // tm_yday (unspecified)
                -1 // tm_isdst (unspecified)
            };

            UIDTimeEpoch() :
                tm(epoch),
                tt(std::mktime(&tm)),
                tp(SystemClock::from_time_t(tt)) {}

            std::tm tm;
            std::time_t tt;
            SystemClockTimePoint tp;
        };

        static const UIDTimeEpoch uidTimeEpoch;
    }

    inline SystemClockTimePoint systemClockTimePointFromUidTime(uint32_t uidTime) {
        return uidTimeEpoch.tp + std::chrono::seconds{uidTime};
    }

    inline uint32_t systemClockTimePointToUidTime(SystemClockTimePoint tp = SystemClock::now()) {
        return std::chrono::duration_cast<std::chrono::seconds>(tp - uidTimeEpoch.tp).count();
    }
}

#endif // CHRONO_CONVERT_HPP_
