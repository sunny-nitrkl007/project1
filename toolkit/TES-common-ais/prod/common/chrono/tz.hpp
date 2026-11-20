#pragma once

#ifndef CHRONO_TZ_HPP_
#define CHRONO_TZ_HPP_

#include <string>
#include <sstream>
#include <cstdint>
#include <cstdlib>
#include <cstdio>

#include <clock_struct.h>
#include <interfaces/ShmClock/ShmClock.h>

namespace tes_common_ais {
    namespace {
        inline bool isLeapYear(uint32_t year) {
            bool itIs;
            if ((year % 4) != 0) {
                // Not the 4th year
                itIs = false;
            }
            else if ((year % 100) != 0) {
                // Not a century year
                itIs = true;
            }
            else if ((year % 400) != 0) {
                // Is a century year, but not the 4th century year
                itIs = false;
            }
            else {
                itIs = true;
            }

            return itIs;
        }

        inline uint16_t dayOfYear(uint32_t year, uint8_t month, uint8_t dayOfMonth) {
            static const uint16_t cummulativeDaysBefore[] = {
                0,   // days before January 1st
                31,  // days before February 1st
                59,  // days before March 1st
                90,  // days before April 1st
                120, // days before May 1st
                151, // days before June 1st
                181, // days before July 1st
                212, // days before August 1st
                243, // days before September 1st
                273, // days before October 1st
                304, // days before November 1st
                334  // days before December 1st
            };

            if ((month >= 1) && (month <= 12)) {
                if (month <= 2) {
                    return cummulativeDaysBefore[month-1] + dayOfMonth;
                }
                else /* month > 2 */ {
                    if (isLeapYear(year)) {
                        return cummulativeDaysBefore[month-1] + 1 + dayOfMonth;
                    }
                    else {
                        return cummulativeDaysBefore[month-1] + dayOfMonth;
                    }
                }
            }

            return 0;
        }

        inline uint16_t dayOfCommonYear(uint8_t month, uint8_t dayOfMonth) {
            static const uint16_t cummulativeDaysBefore[] = {
                0,   // days before January 1st
                31,  // days before February 1st
                59,  // days before March 1st
                90,  // days before April 1st
                120, // days before May 1st
                151, // days before June 1st
                181, // days before July 1st
                212, // days before August 1st
                243, // days before September 1st
                273, // days before October 1st
                304, // days before November 1st
                334  // days before December 1st
            };

            if ((month >= 1) && (month <= 12)) {
                return cummulativeDaysBefore[month-1] + dayOfMonth;
            }

            return 0;
        }
    }

    inline std::string makeTZString(const tzone_tx_comm_struct& tzone) {
        std::ostringstream oss;

        // std
        oss << "LST";

        // std offset [+|-]hh[:mm]
        {
            // std offset in minutes
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

        // dst
        oss << "LDT";

        // dst offset [+|-]hh[:mm]
        {
            // std offset in minutes
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

        // dst start Mm.w.d | Jn
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

        // dst start time hh[:mm]
        {
            if ((tzone.dst_info.dst_hour != 2) || (tzone.dst_info.dst_min != 0)) {
                oss << "/" << static_cast<unsigned>(tzone.dst_info.dst_hour);
                if (tzone.dst_info.dst_min != 0) {
                    oss << ":" << static_cast<unsigned>(tzone.dst_info.dst_min);
                }
            }
        }

         // dst end Mm.w.d | Jn
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

        // dst end time hh[:mm]
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
        tzset(); // initialize the tzname variable from the TZ environment variable
        return result;
    }

    inline bool setTZString(const tzone_tx_comm_struct& tzone) {
        std::string tzStr = tes_common_ais::makeTZString(tzone);
        return setTZString(tzStr);
    }

    inline bool get_tz_data(const tzone_tx_comm_struct &tx_comm_struct_in, unsigned_8 *const tz_data_out, size_t size) {
        constexpr size_t TzSize = sizeof(tzone_tx_comm_struct);
        bool ret = false;

        if (size == TzSize) {
            tz_data_out[1] = (unsigned_8)((0xFF00 & tx_comm_struct_in.tzone_bias) >> 8);
            tz_data_out[2] = (unsigned_8)(0x00FF & tx_comm_struct_in.tzone_bias);
            tz_data_out[3] = (unsigned_8)((0xFF00 & tx_comm_struct_in.std_info.std_bias) >> 8);
            tz_data_out[4] = (unsigned_8)(0x00FF & tx_comm_struct_in.std_info.std_bias);
            tz_data_out[5] = (unsigned_8)(0xFF & tx_comm_struct_in.std_info.std_year);
            tz_data_out[6] = (unsigned_8)(0xFF & tx_comm_struct_in.std_info.std_month);
            tz_data_out[7] = (unsigned_8)(0xFF & tx_comm_struct_in.std_info.std_day_of_month);
            tz_data_out[8] = (unsigned_8)(0xFF & tx_comm_struct_in.std_info.std_day_of_week);
            tz_data_out[9] = (unsigned_8)(0xFF & tx_comm_struct_in.std_info.std_hour);
            tz_data_out[10] = (unsigned_8)(0xFF & tx_comm_struct_in.std_info.std_min);
            tz_data_out[11] = (unsigned_8)((0xFF00 & tx_comm_struct_in.dst_info.dst_bias) >> 8);
            tz_data_out[12] = (unsigned_8)(0x00FF & tx_comm_struct_in.dst_info.dst_bias);
            tz_data_out[13] = (unsigned_8)(0xFF & tx_comm_struct_in.dst_info.dst_year);
            tz_data_out[14] = (unsigned_8)(0xFF & tx_comm_struct_in.dst_info.dst_month);
            tz_data_out[15] = (unsigned_8)(0xFF & tx_comm_struct_in.dst_info.dst_day_of_month);
            tz_data_out[16] = (unsigned_8)(0xFF & tx_comm_struct_in.dst_info.dst_day_of_week);
            tz_data_out[17] = (unsigned_8)(0xFF & tx_comm_struct_in.dst_info.dst_hour);
            tz_data_out[18] = (unsigned_8)(0xFF & tx_comm_struct_in.dst_info.dst_min);
            tz_data_out[19] = (unsigned_8)(0xFF & tx_comm_struct_in.tzone_id);
            ret = true;
        }
        return ret;
    }

    // Populates shmClock_out from provided tx_comm_struct_in.  Returns true if successful.
    inline bool get_tz_data(ShmClock &shmClock_out, const tzone_tx_comm_struct &tx_comm_struct_in) {
        constexpr size_t TzSize = sizeof(tzone_tx_comm_struct);
        bool ret = false;
        unsigned_8 tz_data[TzSize];

        if (get_tz_data(tx_comm_struct_in, tz_data, TzSize)) {
            shmClock_out.set_TZ(tz_data, TzSize);
            ret = true;
        }
        else {
            shmClock_out.set_TZ(tz_data, 0);
        }

        return ret;
    }

    inline bool get_tz_struct(const unsigned_8 *const tz_data_in, size_t size, tzone_tx_comm_struct &tx_comm_struct_out) {
        constexpr size_t TzSize = sizeof(tzone_tx_comm_struct);
        bool ret = false;

        if (size == TzSize) {
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

    // Populates tx_comm_struct_out from provided shmClock_in.  Returns true if successful.
    inline bool get_tz_struct(tzone_tx_comm_struct &tx_comm_struct_out, ShmClock &shmClock_in) {
        constexpr size_t TzSize = sizeof(tzone_tx_comm_struct);
        bool ret = false;

        unsigned_8 tz_data[TzSize];
        if(shmClock_in.get_TZ(tz_data) == TzSize) {
            if (get_tz_struct(tz_data, TzSize, tx_comm_struct_out)) {
                ret = true;
            }
        }
        
        return ret;
    }
}

#endif // CHRONO_TZ_HPP_
