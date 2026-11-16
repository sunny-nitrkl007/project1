#ifndef JOBMGRTIMEZONE_H_
#define JOBMGRTIMEZONE_H_

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include <clock_struct.h>

namespace jobmgr_data {

inline uint16_t dayOfCommonYear(uint8_t month, uint8_t dayOfMonth) {
    static const uint16_t cummulativeDaysBefore[] = {
        0,
        31,
        59,
        90,
        120,
        151,
        181,
        212,
        243,
        273,
        304,
        334
    };

    if ((month >= 1) && (month <= 12)) {
        return cummulativeDaysBefore[month-1] + dayOfMonth;
    }

    return 0;
}

inline std::string makeTZString(const tzone_tx_comm_struct& tzone) {
    std::ostringstream oss;

    oss << "LST";

    {
        int32_t offset = tzone.tzone_bias + tzone.std_info.std_bias;
        if (offset > 0) {
            oss << "-";
        }
        else {
            offset = -offset;
        }

        int32_t hours = offset / 60;
        oss << hours;

        int32_t minutes = offset % 60;
        if (minutes > 0) {
            oss << ":" << minutes;
        }
    }

    oss << "LDT";

    {
        int32_t offset = tzone.tzone_bias + tzone.dst_info.dst_bias;
        if (offset > 0) {
            oss << "-";
        }
        else {
            offset = -offset;
        }

        int32_t hours = offset / 60;
        oss << hours;

        int32_t minutes = offset % 60;
        if (minutes > 0) {
            oss << ":" << minutes;
        }
    }

    {
        oss << ",";
        if (0 == tzone.dst_info.dst_year) {
            oss << "M" << static_cast<unsigned>(tzone.dst_info.dst_month);
            oss << "." << static_cast<unsigned>(tzone.dst_info.dst_day_of_month);
            oss << "." << static_cast<unsigned>(tzone.dst_info.dst_day_of_week);
        }
        else {
            oss << "J" << static_cast<unsigned>(dayOfCommonYear(tzone.dst_info.dst_month, tzone.dst_info.dst_day_of_month));
        }
    }

    {
        if ((tzone.dst_info.dst_hour != 2) || (tzone.dst_info.dst_min != 0)) {
            oss << "/" << static_cast<unsigned>(tzone.dst_info.dst_hour);
            if (tzone.dst_info.dst_min != 0) {
                oss << ":" << static_cast<unsigned>(tzone.dst_info.dst_min);
            }
        }
    }

    {
        oss << ",";
        if (0 == tzone.std_info.std_year) {
            oss << "M" << static_cast<unsigned>(tzone.std_info.std_month);
            oss << "." << static_cast<unsigned>(tzone.std_info.std_day_of_month);
            oss << "." << static_cast<unsigned>(tzone.std_info.std_day_of_week);
        }
        else {
            oss << "J" << static_cast<unsigned>(dayOfCommonYear(tzone.std_info.std_month, tzone.std_info.std_day_of_month));
        }
    }

    {
        if ((tzone.std_info.std_hour != 2) || (tzone.std_info.std_min != 0)) {
            oss << "/" << static_cast<unsigned>(tzone.std_info.std_hour);
            if (tzone.std_info.std_min != 0) {
                oss << ":" << static_cast<unsigned>(tzone.std_info.std_min);
            }
        }
    }

    return oss.str();
}

inline bool setTZString(const std::string& tzStr) {
    bool result = false;
    constexpr int maxSize = 50;
    static char cstr[maxSize];
    auto n = std::snprintf(cstr, maxSize, "TZ=%s", tzStr.c_str());
    if ((n >= 0) && (n < maxSize)) {
        if (0 == putenv(cstr)) {
            result = true;
        }
    }
    tzset();
    return result;
}

inline int_16 decodeTimeZoneBias(uint8_t high, uint8_t low) {
    const int32_t value = (static_cast<int32_t>(high) << 8) | low;
    return static_cast<int_16>(value >= 0x8000 ? value - 0x10000 : value);
}

inline bool decodeTimeZone(const uint8_t* data, size_t size, tzone_tx_comm_struct& tzone) {
    if ((data == nullptr) || (size != 20) || (sizeof(tzone_tx_comm_struct) != 20)) {
        return false;
    }

    tzone.tzone_bias = decodeTimeZoneBias(data[1], data[2]);
    tzone.std_info.std_bias = decodeTimeZoneBias(data[3], data[4]);
    tzone.std_info.std_year = data[5];
    tzone.std_info.std_month = data[6];
    tzone.std_info.std_day_of_month = data[7];
    tzone.std_info.std_day_of_week = data[8];
    tzone.std_info.std_hour = data[9];
    tzone.std_info.std_min = data[10];
    tzone.dst_info.dst_bias = decodeTimeZoneBias(data[11], data[12]);
    tzone.dst_info.dst_year = data[13];
    tzone.dst_info.dst_month = data[14];
    tzone.dst_info.dst_day_of_month = data[15];
    tzone.dst_info.dst_day_of_week = data[16];
    tzone.dst_info.dst_hour = data[17];
    tzone.dst_info.dst_min = data[18];
    tzone.tzone_id = data[19];
    return true;
}

}

#endif
