#ifndef WEIGH_TIMEZONE_H_
#define WEIGH_TIMEZONE_H_

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include <clock_struct.h>

namespace weigh_data {

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

inline bool setTZString(const tzone_tx_comm_struct& tzone) {
    std::string tzStr = makeTZString(tzone);
    return setTZString(tzStr);
}

inline bool get_tz_struct(const unsigned_8 *const tz_data_in, size_t size, tzone_tx_comm_struct &tx_comm_struct_out) {
    constexpr size_t TzSize = sizeof(tzone_tx_comm_struct);
    bool ret = false;

    if ((tz_data_in != nullptr) && (size == TzSize) && (TzSize >= 20)) {
        tx_comm_struct_out.tzone_bias = (unsigned_16)(((tz_data_in[1]) << 0x08) | (tz_data_in[2]));
        tx_comm_struct_out.std_info.std_bias = (unsigned_16)(((tz_data_in[3]) << 0x08) | (tz_data_in[4]));
        tx_comm_struct_out.std_info.std_year = tz_data_in[5];
        tx_comm_struct_out.std_info.std_month = tz_data_in[6];
        tx_comm_struct_out.std_info.std_day_of_month = tz_data_in[7];
        tx_comm_struct_out.std_info.std_day_of_week = tz_data_in[8];
        tx_comm_struct_out.std_info.std_hour = tz_data_in[9];
        tx_comm_struct_out.std_info.std_min = tz_data_in[10];
        tx_comm_struct_out.dst_info.dst_bias = (unsigned_16)(((tz_data_in[11]) << 0x08) | (tz_data_in[12]));
        tx_comm_struct_out.dst_info.dst_year = tz_data_in[13];
        tx_comm_struct_out.dst_info.dst_month = tz_data_in[14];
        tx_comm_struct_out.dst_info.dst_day_of_month = tz_data_in[15];
        tx_comm_struct_out.dst_info.dst_day_of_week = tz_data_in[16];
        tx_comm_struct_out.dst_info.dst_hour = tz_data_in[17];
        tx_comm_struct_out.dst_info.dst_min = tz_data_in[18];
        tx_comm_struct_out.tzone_id = tz_data_in[19];
        ret = true;
    }

    return ret;
}

inline bool decodeTimeZone(const std::array<uint8_t, 20>& data, tzone_tx_comm_struct& tzone) {
    constexpr size_t TzSize = sizeof(tzone_tx_comm_struct);
    if (TzSize != data.size()) {
        return false;
    }
    std::array<unsigned_8, TzSize> raw{};
    std::copy_n(data.begin(), std::min(data.size(), raw.size()), raw.begin());
    return get_tz_struct(raw.data(), raw.size(), tzone);
}

}

#endif
