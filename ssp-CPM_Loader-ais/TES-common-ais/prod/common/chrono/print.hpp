#pragma once

#ifndef CHRONO_PRINT_HPP_
#define CHRONO_PRINT_HPP_

#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <cstdio>


namespace tes_common_ais {
    namespace {
        using SystemClock = std::chrono::system_clock;
        using SystemClockTimePoint = SystemClock::time_point;
        using Minutes = std::chrono::minutes;

        /*
         * LocalTimeOffsetOverride
         *  This provides a mechanism to override the system definition of local time offset
         *  for the purposes of these printing utilities, bypassing the systems definition and
         *  using a pure offset.  This means that DST rules are totally ignored for times
         *  that differ from the current DST mode.  However, on systems that do not properly
         *  support time zone and DST when it comes to making a local time (i.e. 'localtime')
         *  this is the easiest solution.
         */
        class LocalTimeOffsetOverride {
        public:
            static void clear() {
                getInstance().overridden = false;
            }

            static void set(Minutes localTimeOffset) {
                LocalTimeOffsetOverride& instance = getInstance();
                instance.offset = localTimeOffset;
                instance.overridden = true;
            }

            static bool get(Minutes& localTimeOffset) {
                LocalTimeOffsetOverride& instance = getInstance();
                if (instance.overridden) {
                    localTimeOffset = instance.offset;
                    return true;
                }
                return false;
            }

        private:
            bool overridden;
            Minutes offset;

            LocalTimeOffsetOverride() : overridden(false), offset(Minutes::zero()) {}

            static LocalTimeOffsetOverride& getInstance() {
                static LocalTimeOffsetOverride instance;
                return instance;
            }
        };
    }

    namespace date_time_formats {
        constexpr auto ISO_DATE_TIME = "%FT%T%z";
        constexpr auto ISO_DATE_TIME_LOCAL = "%FT%T";
        constexpr auto ISO_DATE_TIME_LOCAL_NO_T = "%F %T";
        constexpr auto ISO_TIME = "%T%z";
        constexpr auto ISO_TIME_LOCAL = "%T";

        constexpr auto HH_MM_24HR = "%R";

        constexpr auto YYYY_MM_DD_SLASH = "%Y/%m/%d";
        constexpr auto MM_DD_YYYY_SLASH = "%m/%d/%Y";
        constexpr auto DD_MM_YYYY_SLASH = "%d/%m/%Y";
        constexpr auto YY_MM_DD_SLASH = "%y/%m/%d";
        constexpr auto MM_DD_YY_SLASH = "%m/%d/%y";
        constexpr auto DD_MM_YY_SLASH = "%d/%m/%y";
        constexpr auto MM_DD_SLASH = "%m/%d";
        constexpr auto DD_MM_SLASH = "%d/%m";

        constexpr auto HH_MM_24HR_YYYY_MM_DD_SLASH = "%R %Y/%m/%d";
        constexpr auto HH_MM_24HR_MM_DD_YYYY_SLASH = "%R %m/%d/%Y";
        constexpr auto HH_MM_24HR_DD_MM_YYYY_SLASH = "%R %d/%m/%Y";
        constexpr auto HH_MM_24HR_YY_MM_DD_SLASH = "%R %y/%m/%d";
        constexpr auto HH_MM_24HR_MM_DD_YY_SLASH = "%R %m/%d/%y";
        constexpr auto HH_MM_24HR_DD_MM_YY_SLASH = "%R %d/%m/%y";
        constexpr auto HH_MM_24HR_MM_DD_SLASH = "%R %m/%d";
        constexpr auto HH_MM_24HR_DD_MM_SLASH = "%R %d/%m";

        constexpr auto YYYY_MM_DD_HYPHEN = "%Y-%m-%d";
        constexpr auto MM_DD_YYYY_HYPHEN = "%m-%d-%Y";
        constexpr auto DD_MM_YYYY_HYPHEN = "%d-%m-%Y";
        constexpr auto YY_MM_DD_HYPHEN = "%y-%m-%d";
        constexpr auto MM_DD_YY_HYPHEN = "%m-%d-%y";
        constexpr auto DD_MM_YY_HYPHEN = "%d-%m-%y";
        constexpr auto MM_DD_HYPHEN = "%m-%d";
        constexpr auto DD_MM_HYPHEN = "%d-%m";

        constexpr auto HH_MM_24HR_YYYY_MM_DD_HYPHEN = "%R %Y-%m-%d";
        constexpr auto HH_MM_24HR_MM_DD_YYYY_HYPHEN = "%R %m-%d-%Y";
        constexpr auto HH_MM_24HR_DD_MM_YYYY_HYPHEN = "%R %d-%m-%Y";
        constexpr auto HH_MM_24HR_YY_MM_DD_HYPHEN = "%R %y-%m-%d";
        constexpr auto HH_MM_24HR_MM_DD_YY_HYPHEN = "%R %m-%d-%y";
        constexpr auto HH_MM_24HR_DD_MM_YY_HYPHEN = "%R %d-%m-%y";
        constexpr auto HH_MM_24HR_MM_DD_HYPHEN = "%R %m-%d";
        constexpr auto HH_MM_24HR_DD_MM_HYPHEN = "%R %d-%m";

        constexpr auto YYYY_MM_DD_T_HH_MM_SS = "%Y%m%dT%H%M%S";
    }

    inline std::string putTime(const std::tm& tm, const char* format) {
        /*
         * Choosing 25 in order to be big enough to fit a typical
         * format with the included terminating character:
         * "YYYY-MM-DD HH:MM:SSZ\0"
         */
        std::vector<std::string::value_type> v(25);
        std::size_t n = std::strftime(v.data(), v.size(), format, &tm);
        while (0 == n) {
            v.resize(v.size() * 2);
            n = std::strftime(v.data(), v.size(), format, &tm);
        }
        return std::string(v.data(), n);
    }

    inline std::string putTime(SystemClockTimePoint tpUtc, const char* format) {
        std::time_t tt = SystemClock::to_time_t(tpUtc);
        std::tm tm;

        // Use thread-safe version of gmtime
        if (nullptr == gmtime_r(&tt, &tm)) {
            return "";
        }

        return putTime(tm, format);
    }

    /*
     * This will parse the time assuming it is UTC formatted as ISO8601
     *   %Y-%m-%dT%H:%M:%SZ (%FT%TZ)
     *   Microseconds and any other time zone designations are ignored.
     *   The '-'s must be present in the date portion.
     *   The ':'s must be present in the time portion.
     *   The 'Z' may or may not be present at the end.
     */
    inline SystemClockTimePoint getTimeISO8601UTC(const std::string& strUtc) {
        SystemClockTimePoint tp;
        std::tm tmUtc{}; // value-initialized (basically 0's)
        const char* in = strUtc.c_str();
        const char* out = strptime(in, "%FT%T", &tmUtc);
        // yyyy-mm-ddThh:mm:ss (19 characters)
        if ((nullptr == out) || ((out - in) != 19)) {
            // Failed to match all of the format string
            tp = SystemClockTimePoint::min();
        }
        else {
            /*
             * Build the time point from the tm struct
             *  'timegm' is Like 'mktime', but for when the tm struct
             *  represents Universal Time, not local time.
             */
            std::time_t tUtc = timegm(&tmUtc);
            //std::time_t tUtc = std::mktime(&tmUtc);
            if (-1 == tUtc) {
                // Failed to make a time
                tp = SystemClockTimePoint::min();
            }
            else {
                tp = SystemClock::from_time_t(tUtc);
            }
        }
        return tp;
    }

    /*
     * This will determine the local calendar time from a UTC time point
     */
    inline bool getCalendarTimeFromTimePoint(SystemClockTimePoint tpUtc, std::tm& tm) {
        std::time_t tt = SystemClock::to_time_t(tpUtc);

        // Use thread-safe version of gmtime
        if (nullptr == gmtime_r(&tt, &tm)) {
            return false;
        }

        return true;
    }

    /*
     * This will return the UTC time point from the passed UTC calendar date/time
     * As a side-effect, this will also normalize the passed UTC calendar date/time
     */
    inline SystemClockTimePoint getTimePointFromCalendarTime(std::tm& tmUtc) {
        SystemClockTimePoint tp;

        /*
         * Build the time point from the tm struct
         *  'timegm' is Like 'mktime', but for when the tm struct
         *  represents Universal Time, not local time.
         */
        std::time_t tUtc = timegm(&tmUtc);
        if (-1 == tUtc) {
            // Failed to make a time
            tp = SystemClockTimePoint::min();
        }
        else {
            tp = SystemClock::from_time_t(tUtc);
        }

        return tp;
    }

    /*
     * This will parse the date with the provided formatting
     * The result will be in a tm struct
     */
    inline bool parseDateTime(const std::string& str, std::tm& tmStruct, const char* format, int expectedLength) {
        if (nullptr == format) {
            return false;
        }

        std::tm tmTemp{}; // value-initialized (basically 0's)

        const char* in = str.c_str();

        const char* out = strptime(in, format, &tmTemp);

        if ((nullptr == out) || ((out - in) != expectedLength)) {
            return false;
        }

        tmStruct = tmTemp;
        return true;
    }

    /*
     * This will parse the date assuming it is formatted as ISO8601
     *   %Y-%m-%d (%F)
     * The result will be in a tm struct
     */
    inline bool parseDateISO8601(const std::string& str, std::tm& tmStruct) {
        // yyyy-mm-dd (10 characters)
        return parseDateTime(str, tmStruct, "%F", 10);
    }

    /*
     * This will parse the date/time assuming it is formatted as ISO8601
     *   %Y-%m-%dT%H:%M:%SZ (%FT%TZ)
     *   Microseconds and any other time zone designations are ignored.
     *   The '-'s must be present in the date portion.
     *   The ':'s must be present in the time portion.
     *   The time zone designation is ignored.
     * The result will be in a tm struct
     */
    inline bool parseDateTimeISO8601(const std::string& str, std::tm& tmStruct) {
        // yyyy-mm-ddThh:mm:ss (19 characters)
        return parseDateTime(str, tmStruct, "%FT%T", 19);
    }

    /*
     * This will parse the date/time assuming it is UTC formatted as specified
     */
    inline SystemClockTimePoint parseDateTime(const std::string& strUtc, const char* format, int expectedLength) {
        SystemClockTimePoint tp;
        std::tm tmUtc;

        if (parseDateTime(strUtc, tmUtc, format, expectedLength)) {
            tp = getTimePointFromCalendarTime(tmUtc);
        }
        else {
            tp = SystemClockTimePoint::min();
        }

        return tp;
    }

    /*
     * This will parse the date assuming it is UTC formatted as ISO8601
     *   %Y-%m-%d (%F)
     */
    inline SystemClockTimePoint parseDateISO8601(const std::string& strUtc) {
        SystemClockTimePoint tp;
        std::tm tmUtc;

        if (parseDateISO8601(strUtc, tmUtc)) {
            tp = getTimePointFromCalendarTime(tmUtc);
        }
        else {
            tp = SystemClockTimePoint::min();
        }

        return tp;
    }

    /*
     * This will parse the time assuming it is UTC formatted as ISO8601
     *   %Y-%m-%dT%H:%M:%SZ (%FT%TZ)
     *   Microseconds and any other time zone designations are ignored.
     *   The '-'s must be present in the date portion.
     *   The ':'s must be present in the time portion.
     *   The 'Z' may or may not be present at the end.
     */
    inline SystemClockTimePoint parseDateTimeISO8601(const std::string& strUtc) {
        SystemClockTimePoint tp;
        std::tm tmUtc;

        if (parseDateTimeISO8601(strUtc, tmUtc)) {
            tp = getTimePointFromCalendarTime(tmUtc);
        }
        else {
            tp = SystemClockTimePoint::min();
        }

        return tp;
    }

    /*
     * This version of putLocalTime uses the provided local time offset instead of the systems
     *  timezone conversion information.  The down-side of this is that the %z and %Z format
     *  specifiers will not work properly, so don't try it.
     *
     *  localTime = utcTime + localOffset
     */
    inline std::string putLocalTime(SystemClockTimePoint tpUtc, Minutes localTimeOffset, const char* format) {
        return putTime(tpUtc + localTimeOffset, format);
    }

    /*
     * This version of putLocalTime relies on the underlying system to know about the timezone
     *  conversion information, see tzset().  If it does not, you have to provide the local
     *  time offset with the other version of putLocalTime.
     */
    inline std::string putLocalTime(SystemClockTimePoint tpUtc, const char* format) {
        Minutes localTimeOffset;
        if (LocalTimeOffsetOverride::get(localTimeOffset)) {
            return putTime(tpUtc + localTimeOffset, format);
        }
        else {
            std::time_t tt = SystemClock::to_time_t(tpUtc);
            std::tm tm;

            // Use thread-safe version of localtime
            // Assumes tzset() has been called to initialize the tzname variable from the TZ environment variable
            if (nullptr == localtime_r(&tt, &tm)) {
                return "";
            }

            /*
             * Choosing 25 in order to be big enough to fit a typical
             * format with the included terminating character:
             * "YYYY-MM-DD HH:MM:SSZ\0"
             */
            std::vector<std::string::value_type> v(25);
            std::size_t n = std::strftime(v.data(), v.size(), format, &tm);
            while (0 == n) {
                v.resize(v.size() * 2);
                n = std::strftime(v.data(), v.size(), format, &tm);
            }
            return std::string(v.data(), n);
        }
    }

    /*
     * This will determine the local calendar time from a UTC time point
     */
    inline bool getLocalCalendarTimeFromTimePoint(const SystemClockTimePoint& tpUtc, std::tm& tmLocal) {
        Minutes localTimeOffset;
        if (LocalTimeOffsetOverride::get(localTimeOffset)) {
            return getCalendarTimeFromTimePoint(tpUtc + localTimeOffset, tmLocal);
        }
        else {
            std::time_t tt = SystemClock::to_time_t(tpUtc);

            // Use thread-safe version of localtime
            // Assumes tzset() has been called to initialize the tzname variable from the TZ environment variable
            if (nullptr == localtime_r(&tt, &tmLocal)) {
                return false;
            }

            return true;
        }
    }

    /*
     * This will return the UTC time point from the passed local calendar date/time
     * As a side-effect, this will also normalize the passed local calendar date/time
     */
    inline SystemClockTimePoint getTimePointFromLocalCalendarTime(std::tm& tmLocal) {
        SystemClockTimePoint tp;
        Minutes localTimeOffset;
        if (LocalTimeOffsetOverride::get(localTimeOffset)) {
            // Local time offset is overridden

            /*
             * Build the time point from the tm struct
             *  'timegm' is Like 'mktime', but for when the tm struct
             *  represents Universal Time, not local time.
             */
            std::time_t tLocal = timegm(&tmLocal);
            if (-1 == tLocal) {
                // Failed to make a time
                tp = SystemClockTimePoint::min();
            }
            else {
                tp = SystemClock::from_time_t(tLocal) - localTimeOffset;
            }
        }
        else {
            /*
             * Build the time point from the tm struct
             *  The tm struct represent local time.
             */
            std::time_t tUtc = std::mktime(&tmLocal);
            if (-1 == tUtc) {
                // Failed to make a time
                tp = SystemClockTimePoint::min();
            }
            else {
                tp = SystemClock::from_time_t(tUtc);
            }
        }

        return tp;
    }

    /*
     * This will parse the time assuming it is local time formatted as ISO8601
     *   %Y-%m-%dT%H:%M:%SZ (%FT%TZ)
     *   Microseconds and any other time zone designations are ignored.
     *   The '-'s must be present in the date portion.
     *   The ':'s must be present in the time portion.
     *   The time zone designation is ignored.
     */
    inline SystemClockTimePoint parseLocalDateTimeISO8601(const std::string& strLocal) {
        SystemClockTimePoint tp;
        std::tm tmLocal;

        if (parseDateTimeISO8601(strLocal, tmLocal)) {
            tp = getTimePointFromLocalCalendarTime(tmLocal);
        }
        else {
            tp = SystemClockTimePoint::min();
        }

        return tp;
    }

    /*
     * This will parse the date assuming it is local time formatted as ISO8601
     *   %Y-%m-%d (%F)
     */
    inline SystemClockTimePoint parseLocalDateISO8601(const std::string& strLocal) {
        SystemClockTimePoint tp;
        std::tm tmLocal;

        if (parseDateISO8601(strLocal, tmLocal)) {
            tp = getTimePointFromLocalCalendarTime(tmLocal);
        }
        else {
            tp = SystemClockTimePoint::min();
        }

        return tp;
    }

    /*
     * setEnvLocalTimeOffset - Sets the local time offset, in minutes, such that...
     *
     *  local = utc + offset
     *
     *  This actually just sets the TZ environment variable for this process to TZ=LOCAL+HH:MM:SS
     *  Calls to std::localtime after this will load the environment variable with tzset
     *
     *  This will probably only work with POSIX systems.
     */
    inline int setEnvLocalTimeOffset(Minutes offset) {
        static char cstr[20];

        if (offset.count() < 0) {
            offset *= -1;
            std::snprintf(cstr, sizeof(cstr)/sizeof(cstr[0]), "TZ=LOCAL+%02d:%02d:%02d",
                    static_cast<int>(std::chrono::duration_cast<std::chrono::hours>(offset).count()),
                    static_cast<int>(std::chrono::duration_cast<std::chrono::minutes>(offset % std::chrono::hours(1)).count()),
                    static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(offset % std::chrono::minutes(1)).count()));
        }
        else {
            std::snprintf(cstr, sizeof(cstr)/sizeof(cstr[0]), "TZ=LOCAL-%02d:%02d:%02d",
                    static_cast<int>(std::chrono::duration_cast<std::chrono::hours>(offset).count()),
                    static_cast<int>(std::chrono::duration_cast<std::chrono::minutes>(offset % std::chrono::hours(1)).count()),
                    static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(offset % std::chrono::minutes(1)).count()));
        }

        int rval = putenv(cstr);

        tzset(); // initialize the tzname variable from the TZ environment variable

        return rval;
    }

    /*
     * getEnvLocalTimeOffset - Gets the system local time offset, in minutes, such that...
     *
     *  local = utc + offset
     *
     *  This requires the timezone information to be known by the system, or for it to be
     *  in the TZ environment variable, which may not be the case depending on platform.
     */
    inline Minutes getEnvLocalTimeOffset(const SystemClockTimePoint& tp) {
        auto tp_time_t = SystemClock::to_time_t(tp);

        // Use thread-safe version of localtime
        // Assumes tzset() has been called to initialize the tzname variable from the TZ environment variable
        std::tm local;
        if (nullptr == localtime_r(&tp_time_t, &local)) {
            return std::chrono::minutes(0);
        }

        // Use thread-safe version of gmtime
        std::tm utc;
        if (nullptr == gmtime_r(&tp_time_t, &utc)) {
            return std::chrono::minutes(0);
        }

        /*
         * Treat utc as if it is a local time, with the same timezone and DST.
         *  This way, when it is converted back to a time_t using mktime, it is treated as
         *  a local time.
         */
        utc.tm_isdst = local.tm_isdst;

        // Difference the two times, as if they are both local times.
        double diff = std::difftime(std::mktime(&local), std::mktime(&utc));

        // Convert to std::chrono:minutes
        return std::chrono::minutes(static_cast<int>(diff/60.0));
    }

    inline Minutes getEnvLocalTimeOffset() {
        auto now = SystemClock::now();
        return getEnvLocalTimeOffset(now);
    }

    inline Minutes getLocalTimeOffset(const SystemClockTimePoint& tp) {
        Minutes localTimeOffset;
        if (LocalTimeOffsetOverride::get(localTimeOffset)) {
            // It is overridden
        }
        else {
            localTimeOffset = getEnvLocalTimeOffset(tp);
        }
        return localTimeOffset;
    }

    inline Minutes getLocalTimeOffset() {
        auto now = SystemClock::now();
        return getLocalTimeOffset(now);
    }

    inline void setLocalTimeOffsetOverride(Minutes localTimeOffset) {
        LocalTimeOffsetOverride::set(localTimeOffset);
    }

    inline void clearLocalTimeOffsetOverride() {
        LocalTimeOffsetOverride::clear();
    }

    inline SystemClockTimePoint getUTCStartOfLocalDay(const SystemClockTimePoint& tp) {
        Minutes localTimeOffset;
        if (LocalTimeOffsetOverride::get(localTimeOffset)) {
            // It is overridden

            // Add the local time offset to represent a local time
            std::time_t tt = std::chrono::system_clock::to_time_t(tp + localTimeOffset);

            // Convert from time since epoch (time_t) into a calendar time
            // Use thread-safe version of gmtime
            std::tm local;
            if (nullptr == gmtime_r(&tt, &local)) {
                // Fail
                return tp - std::chrono::hours(24);
            }

            // Zero out the hour to get to the start of the local calendar day
            local.tm_hour = 0;
            local.tm_min = 0;
            local.tm_sec = 0;

            // Convert from calendar time back to a time since epoch (time_t)
            tt = timegm(&local);
            if (tt < 0) {
                // Fail
                return tp - std::chrono::hours(24);
            }

            // Subtract the local time offset back off to represent a UTC time
            return std::chrono::system_clock::from_time_t(tt) - localTimeOffset;
        }
        else {
            std::time_t tt = std::chrono::system_clock::to_time_t(tp);

            // Convert from time since epoch (time_t) into a local calendar time
            // Use thread-safe version of localtime
            // Assumes tzset() has been called to initialize the tzname variable from the TZ environment variable
            std::tm local;
            if (nullptr == localtime_r(&tt, &local)) {
                // Fail
                return tp - std::chrono::hours(24);
            }

            // Zero out the hour to get to the start of the local calendar day
            local.tm_hour = 0;
            local.tm_min = 0;
            local.tm_sec = 0;

            // Convert from local calendar time back to a time since epoch (time_t)
            tt = std::mktime(&local);
            if (tt < 0) {
                // Fail
                return tp - std::chrono::hours(24);
            }

            return std::chrono::system_clock::from_time_t(tt);
        }
    }

    inline SystemClockTimePoint getUTCStartOfLocalDay() {
        auto now = SystemClock::now();
        return getUTCStartOfLocalDay(now);
    }
}

#endif // CHRONO_PRINT_HPP_
