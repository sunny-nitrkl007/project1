////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//     Class: GPSDataLinkParam
//
// File Name: GPSDataLinkParam.h
//
//  Abstract: Parse GPS data fields from a sequence of data link bytes.
//            This class is a helper to class DataLinkParam.
//
////////////////////////////////////////////////////////
#ifndef GPSDATALINKPARAM_H
#define GPSDATALINKPARAM_H

#include <cstring>
#include <cstdint>

#include <oel_pack.h>

#include "VarLengthDataLinkParam.h"
#include "DataLinkParam.h"

#define EARTH_RADIUS            6371009
/* Applying PID scaling and converting angles from degrees to radians for GPS coordinates.
  2**24 == 16777216 is the degree/bit scaling of data from PID
  NOTE: lat is expected to be 0..90
  NOTE: lon is expected to be 0..360
*/
#define CONV_LAT_TO_RADIANS(lat) ((90.0-lat)*M_PI/180.0);
#define CONV_LON_TO_RADIANS(lon) ((lon-360.0)*M_PI/180.0);

#define GPS_PARAM_DATA_INVALID -999.0
#define GPS_PARAM_INVALID -1

class GPSDataLinkParam : public VarLengthDataLinkParam
{
public:
    GPSDataLinkParam(DataLinkParam& param) : VarLengthDataLinkParam(param) {}

    GPSDataLinkParam(VarLengthParamBlock_t& paramValue) :
                VarLengthDataLinkParam(paramValue) {}

    ~GPSDataLinkParam() {}


    // These need to match the datalink definition for PID 0xF84D
    enum class GpsPositionStatusType : uint8_t {
        POSITION_VALID = 0,
        POSITION_INVALID = 1,
        POSITION_CALCULATION_INCOMPLETE = 2,
        POSITION_TYPE_NOT_AVAILABLE = 3
    };

    enum class GpsPositionCommand : uint8_t {
        POSITION_REQUEST = 0,
        START_POSITION_CALCULATION = 1,
        STOP_POSITION_CALCULATION = 2
    };

    static std::string toString(GPSDataLinkParam::GpsPositionStatusType e)
    {
        const std::map<GPSDataLinkParam::GpsPositionStatusType, const char*> EnumStrings {
            { GPSDataLinkParam::GpsPositionStatusType::POSITION_VALID,                     "Valid" },
            { GPSDataLinkParam::GpsPositionStatusType::POSITION_INVALID,                   "Invalid" },
            { GPSDataLinkParam::GpsPositionStatusType::POSITION_CALCULATION_INCOMPLETE,    "Incomplete" },
            { GPSDataLinkParam::GpsPositionStatusType::POSITION_TYPE_NOT_AVAILABLE,        "Not Available" }
        };
        auto   it  = EnumStrings.find(e);
        return it == EnumStrings.end() ? "--" : it->second;
    }

    static constexpr uint32_t m_Pid = 0xF84D;

    static constexpr uint8_t m_GpsParamSize = 14;
    static constexpr uint8_t m_GpsLatitudeSize = 3;
    static constexpr uint8_t m_GpsLongitudeSize = 3;
    typedef uint8_t GpsLatitude_t[m_GpsLatitudeSize];
    typedef uint8_t GpsLongitude_t[m_GpsLongitudeSize];

    inline bool isSizeOk() const {
        return m_ParamValue.size() >= m_GpsParamSize;
    }

    // This function sets the GPS postion command parsed from the m_ParamValue byte sequence.
    int8_t GetPositionCommand() const {
        return isSizeOk() ? m_ParamValue[m_PositionCommandOffset] : GPS_PARAM_INVALID;
    }

    // This function returns the GPS UTC timestamp seconds parsed from the m_ParamValue byte sequence.
    int8_t GetTimestampSeconds() const {
        return isSizeOk() ? m_ParamValue[m_SecondsOffset] : GPS_PARAM_INVALID;
    }

    // This function returns the GPS UTC timestamp minutes parsed from the m_ParamValue byte sequence.
    int8_t GetTimestampMinutes() const {
        return isSizeOk() ? m_ParamValue[m_MinutesOffset] : GPS_PARAM_INVALID;
    }

    // This function returns the GPS UTC timestamp hours parsed from the m_ParamValue byte sequence.
    int8_t GetTimestampHours() const {
        return isSizeOk() ? m_ParamValue[m_HoursOffset] : GPS_PARAM_INVALID;
    }

    // This function returns the GPS UTC timestamp month parsed from the m_ParamValue byte sequence.
    int8_t GetTimestampMonth() const {
        return isSizeOk() ? m_ParamValue[m_MonthOffset] : GPS_PARAM_INVALID;
    }

    // This function returns the GPS UTC timestamp day parsed from the m_ParamValue byte sequence.
    int8_t GetTimestampDay() const {
        return isSizeOk() ? m_ParamValue[m_DayOffset] : GPS_PARAM_INVALID;
    }

    // This function returns the GPS UTC timestamp year parsed from the m_ParamValue byte sequence.
    int8_t GetTimestampYear() const {
        return isSizeOk() ? m_ParamValue[m_YearOffset] : GPS_PARAM_INVALID;
    }

    // This function returns the GPS latitude parsed from the m_ParamValue byte sequence.
    bool GetGpsLatitude(GpsLatitude_t& latitude) const {
        if (isSizeOk()) {
            std::memcpy(latitude, &m_ParamValue[m_GpsLatitudeOffset], m_GpsLatitudeSize);
            return true;
        }
        return false;
    }

    // Get GPS latitude in degrees.
    // It needs to be double, otherwise resolution is lost
    // Range is 0:180 if pidF84DRange == true, -90:90 otherwise
    double GetGpsLatitude(bool pidF84DRange = false) const {
        if (isSizeOk()) {
            uint32_t temp;
            // The datalink definition does not specify the byte order.
            OEL_UNPACK_BE_24_NO_INCR((&m_ParamValue[m_GpsLatitudeOffset]), temp);
            double ret = ((double)temp * 180.0 / (double)(1UL<<24));
            if (pidF84DRange) {
                return ret;
            }
            else {
                return 90.0 - ret;
            }
        }
        return GPS_PARAM_DATA_INVALID;
    }

    // This function returns the GPS longitude parsed from the m_ParamValue byte sequence.
    bool GetGpsLongitude(GpsLongitude_t& longitude) const {
        if (isSizeOk()) {
            std::memcpy(longitude, &m_ParamValue[m_GpsLongitudeOffset], m_GpsLongitudeSize);
            return true;
        }
        return false;
    }

    // Get GPS longitude in degrees.
    // It needs to be double, otherwise resolution is lost
    // Range is 0:360 if pidF84DRange == true, -180:180 otherwise
    double GetGpsLongitude(bool pidF84DRange = false) const {
        if (isSizeOk()) {
            uint32_t temp;
            // The datalink definition does not specify the byte order.
            OEL_UNPACK_BE_24_NO_INCR((&m_ParamValue[m_GpsLongitudeOffset]), temp);
            double ret = ((double)temp * 360.0 / (double)(1UL<<24));
            if (pidF84DRange) {
                return ret;
            }
            else {
                return 180.0 - ret;
            }
        }
        return GPS_PARAM_DATA_INVALID;
    }

    // This function returns the GPS status parsed from the m_ParamValue byte sequence.
    GpsPositionStatusType GetGpsStatus() const {
        GpsPositionStatusType result = GpsPositionStatusType::POSITION_TYPE_NOT_AVAILABLE;  // default

        if (isSizeOk()) {
            if (m_ParamValue[m_PositionStatusOffset] < static_cast<uint8_t>(GpsPositionStatusType::POSITION_TYPE_NOT_AVAILABLE)) {
                result = static_cast<GpsPositionStatusType>(m_ParamValue[m_PositionStatusOffset]);
            }
        }

        return result;
    }

    // This function returns TRUE if TimeStamp is all 0xFFs, else return FALSE
    bool isNotValidTimestamp() const {
        if (isSizeOk()) {
            return std::equal(FF_s.begin(), FF_s.end(), m_ParamValue.begin() + 1);
        }
        return false;
    }

    // This function returns TRUE if Lat-Long is all 0xFFs, else return FALSE
    bool isNotValidLatLong() const {
        if (isSizeOk()) {
            return std::equal(FF_s.begin(), FF_s.end(), m_ParamValue.begin() + 8);
        }
        return false;
    }

    // This function return the distance in meters between the given GPS position and the current GPS position
    // If there is an error -999.0 is returned, else a positive # indicating a good result.
    double getDistanceMeters(double prevLat, double prevLong) const {
        if (isSizeOk()) {   // check both GPS object's size
            double dLat, dLon, distance;
            
            double curr_lat, curr_lon;
            double last_lat, last_lon;

            // Applying the scaling and convert from degrees to radians
            curr_lat = CONV_LAT_TO_RADIANS(GetGpsLatitude(false));
            curr_lon = CONV_LON_TO_RADIANS(GetGpsLongitude(true));
            last_lat = CONV_LAT_TO_RADIANS(prevLat);
            last_lon = CONV_LON_TO_RADIANS(prevLong);
            
                    
            // Taking the difference between latitudes and longitudes of two GPS positions 
            dLat  = last_lat - curr_lat;
            dLon  = last_lon - curr_lon;

            // Distance calculation
            distance = (double)(EARTH_RADIUS * sqrt(( dLat * dLat ) + (cos(curr_lat) * cos(last_lat) * dLon * dLon )));

            return distance;
        }

        return GPS_PARAM_DATA_INVALID;  // error number, picked negative number cause distance can't be negative
    }

    // Set GPS longitude in degrees.
    // It needs to be double, otherwise resolution is lost
    // Range is 0:360 if pidF84DRange == true, -180:180 otherwise
    void SetGpsLongitude(double longitude, bool pidF84DRange) {
        m_ParamValue.resize(m_GpsParamSize);
        if (!pidF84DRange) {
            longitude = 180.0 - longitude;
        }
        // Cap the range to avoid rounding errors
        if (longitude < 0.0) {
            longitude = 0.0;
        }
        else if (longitude > 360.0) {
            longitude = 360.0;
        }
        uint32_t temp = static_cast<uint32_t>(longitude / LongitudeDegreesPerBit);
        // The datalink definition does not specify the byte order.
        OEL_PACK_BE_24_NO_INCR((&m_ParamValue[m_GpsLongitudeOffset]), temp);
    }

    // Set GPS latitude in degrees.
    // It needs to be double, otherwise resolution is lost
    // Range is 0:180 if pidF84DRange == true, -90:90 otherwise
    void SetGpsLatitude(double latitude, bool pidF84DRange) {
        m_ParamValue.resize(m_GpsParamSize);
        if (!pidF84DRange) {
            latitude = 90.0 - latitude;
        }
        // Cap the range to avoid rounding errors
        if (latitude < 0.0) {
            latitude = 0.0;
        }
        else if (latitude > 180.0) {
            latitude = 180.0;
        }
        uint32_t temp = static_cast<uint32_t>(latitude / LatitudeDegreesPerBit);
        // The datalink definition does not specify the byte order.
        OEL_PACK_BE_24_NO_INCR((&m_ParamValue[m_GpsLatitudeOffset]), temp);
    }

    // This function sets the GPS status
    bool SetGpsStatus(GpsPositionStatusType gpsStatus) {
        m_ParamValue.resize(m_GpsParamSize);
        m_ParamValue[m_PositionStatusOffset] = static_cast<uint8_t>(gpsStatus);
        return true;
    }

    // This function sets the GPS postion command
    bool SetPositionCommand(GpsPositionCommand command) {
        m_ParamValue.resize(m_GpsParamSize);
        m_ParamValue[m_PositionCommandOffset] = static_cast<uint8_t>(command);
        return true;
    }

    // This function sets the GPS UTC timestamp seconds
    bool SetTimestampSeconds(uint8_t sec) {
        m_ParamValue.resize(m_GpsParamSize);
        if (sec < 60) {
            m_ParamValue[m_SecondsOffset] = sec;
            return false;
        }
        return false;
    }

    // This function sets the GPS UTC timestamp minutes
    bool SetTimestampMinutes(uint8_t min) {
        m_ParamValue.resize(m_GpsParamSize);
        if (min < 60) {
            m_ParamValue[m_MinutesOffset] = min;
            return false;
        }
        return false;
    }

    // This function sets the GPS UTC timestamp hours
    bool SetTimestampHours(uint8_t hour) {
        m_ParamValue.resize(m_GpsParamSize);
        if (hour < 24) {
            m_ParamValue[m_HoursOffset] = hour;
            return false;
        }
        return false;
    }

    // This function sets the GPS UTC timestamp month
    bool SetTimestampMonth(uint8_t mon) {
        m_ParamValue.resize(m_GpsParamSize);
        if (mon < 13) {
            m_ParamValue[m_MonthOffset] = mon;
            return false;
        }
        return false;
    }

    // This function sets the GPS UTC timestamp day
    bool SetTimestampDay(uint8_t mday) {
        m_ParamValue.resize(m_GpsParamSize);
        if (mday < 32) {
            m_ParamValue[m_DayOffset] = mday;
            return false;
        }
        return false;
    }

    // This function sets the GPS UTC timestamp year
    bool SetTimestampYear(uint8_t year) {
        m_ParamValue.resize(m_GpsParamSize);
        m_ParamValue[m_YearOffset] = year;
        return true;
    }

private:
    static constexpr auto LatitudeDegreesPerBit = 0.0000107288360596;
    static constexpr auto LongitudeDegreesPerBit = 0.0000214576721191;

    static constexpr uint8_t m_PositionCommandOffset = 0;
    static constexpr uint8_t m_SecondsOffset = 1;
    static constexpr uint8_t m_MinutesOffset = 2;
    static constexpr uint8_t m_HoursOffset = 3;
    static constexpr uint8_t m_MonthOffset = 4;
    static constexpr uint8_t m_DayOffset = 5;
    static constexpr uint8_t m_YearOffset = 6;
    static constexpr uint8_t m_PositionStatusOffset = 7;
    static constexpr uint8_t m_GpsLatitudeOffset = m_PositionStatusOffset + 1;
    static constexpr uint8_t m_GpsLongitudeOffset = m_GpsLatitudeOffset + m_GpsLatitudeSize;
    static constexpr uint8_t m_GpsStatusOffset = m_GpsLongitudeOffset + m_GpsLongitudeSize;

    // 0xFFs vector for comparison for Time and Lat-Long
    const std::vector<uint8_t> FF_s = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

};


#endif //GPSDATALINKPARAM_H
