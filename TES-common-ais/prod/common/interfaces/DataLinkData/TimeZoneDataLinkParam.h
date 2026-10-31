////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//     Class: TimeZoneDataLinkParam
//
// File Name: TimeZoneDataLinkParam.h
//
//  Abstract: Parse GPS Time Zone data fields from a sequence of data link bytes.
//            This class is a helper to class DataLinkParam.
//
////////////////////////////////////////////////////////
#ifndef TIMEZONEDATALINKPARAM_H
#define TIMEZONEDATALINKPARAM_H

#include "VarLengthDataLinkParam.h"
#include <cat_std_types.h>
#include <cstring>

class TimeZoneDataLinkParam : public VarLengthDataLinkParam
{
public:
    TimeZoneDataLinkParam(DataLinkParam& param) : VarLengthDataLinkParam(param) {}

    TimeZoneDataLinkParam(VarLengthParamBlock_t& paramValue) :
                VarLengthDataLinkParam(paramValue) {}

      ~TimeZoneDataLinkParam(){}

      static const unsigned_8 m_TimeZoneParamSize = 19;

      inline bool isSizeOk() const {
          return m_ParamValue.size() >= m_TimeZoneParamSize;
      }

      // This function returns the GPS UTC time zone offset parsed from the m_ParamValue byte sequence.
      unsigned_16 GetTimeZoneBiasUtc() const {
          if (isSizeOk()) {
              unsigned_16 timeZoneOffset;
              std::memcpy(&timeZoneOffset, &m_ParamValue[m_TimeZoneBiasUtcOffset], m_TimeZoneBiasUtcSize);
              return timeZoneOffset;
          }
          return 0;
      }

      // This function returns the GPS standard time zone offset parsed from the m_ParamValue byte sequence.
      unsigned_16 GetStandardTimeZoneBias() const {
          if (isSizeOk()) {
              unsigned_16 timeZoneOffset;
              std::memcpy(&timeZoneOffset, &m_ParamValue[m_StandardTimeZoneBiasOffset], m_StandardTimeZoneBiasSize);
              return timeZoneOffset;
          }
          return 0;
      }

      // This function returns the GPS standard time year parsed from the m_ParamValue byte sequence.
      unsigned_8 GetStandardTimeYear() const {
          return isSizeOk() ? m_ParamValue[m_StandardTimeYearOffset] : 0;
      }

      // This function returns the GPS standard time month parsed from the m_ParamValue byte sequence.
      unsigned_8 GetStandardTimeMonth() const {
          return isSizeOk() ? m_ParamValue[m_StandardTimeMonthOffset] : 0;
      }

      // This function returns the GPS standard time day of month parsed from the m_ParamValue byte sequence.
      unsigned_8 GetStandardTimeDayOfMonth() const {
          return isSizeOk() ? m_ParamValue[m_StandardTimeDayOfMonthOffset] : 0;
      }

      // This function returns the GPS UTC timestamp day parsed from the m_ParamValue byte sequence.
      unsigned_8 GetStandardTimeDayOfWeek() const {
          return isSizeOk() ? m_ParamValue[m_StandardTimeDayOfWeekOffset] : 0;
      }

      // This function returns the GPS UTC timestamp year parsed from the m_ParamValue byte sequence.
      unsigned_8 GetStandardTimeHour() const {
          return isSizeOk() ? m_ParamValue[m_StandardTimeHourOffset] : 0;
      }

      // This function returns the GPS UTC timestamp year parsed from the m_ParamValue byte sequence.
      unsigned_8 GetStandardTimeMinute() const {
          return isSizeOk() ? m_ParamValue[m_StandardTimeMinuteOffset] : 0;
      }

      // This function returns the GPS UTC timestamp seconds parsed from the m_ParamValue byte sequence.
      unsigned_16 GetDaylightTimeZoneBias() const {
          if (isSizeOk()) {
              unsigned_16 timeZoneOffset;
              std::memcpy(&timeZoneOffset, &m_ParamValue[m_DaylightTimeZoneBiasOffset], m_DaylightTimeZoneBiasSize);
              return timeZoneOffset;
          }
          return 0;
      }

      // This function returns the GPS UTC timestamp minutes parsed from the m_ParamValue byte sequence.
      unsigned_8 GetDaylightTimeYear() const {
          return isSizeOk() ? m_ParamValue[m_DaylightTimeYearOffset] : 0;
      }

      // This function returns the GPS UTC timestamp minutes parsed from the m_ParamValue byte sequence.
      unsigned_8 GetDaylightTimeMonth() const {
          return isSizeOk() ? m_ParamValue[m_DaylightTimeMonthOffset] : 0;
      }

      // This function returns the GPS UTC timestamp minutes parsed from the m_ParamValue byte sequence.
      unsigned_8 GetDaylightTimeDayOfMonth() const {
          return isSizeOk() ? m_ParamValue[m_DaylightTimeDayOfMonthOffset] : 0;
      }

      // This function returns the GPS UTC timestamp minutes parsed from the m_ParamValue byte sequence.
      unsigned_8 GetDaylightTimeDayOfWeek() const {
          return isSizeOk() ? m_ParamValue[m_DaylightTimeDayOfWeekOffset] : 0;
      }

      // This function returns the GPS UTC timestamp minutes parsed from the m_ParamValue byte sequence.
      unsigned_8 GetDaylightTimeHour() const {
          return isSizeOk() ? m_ParamValue[m_DaylightTimeHourOffset] : 0;
      }

      // This function returns the GPS UTC timestamp minutes parsed from the m_ParamValue byte sequence.
      unsigned_8 GetDaylightTimeMinute() const {
          return isSizeOk() ? m_ParamValue[m_DaylightTimeMinuteOffset] : 0;
      }

      // This function returns the GPS UTC timestamp minutes parsed from the m_ParamValue byte sequence.
      unsigned_8 GetTimeZoneDescriptionIndex() const {
          return isSizeOk() ? m_ParamValue[m_TimeZoneDescriptionIndexOffset] : 0;
      }

   private:
      const uint8_t m_TimeZoneBiasUtcOffset = 0;
      const uint8_t m_StandardTimeZoneBiasOffset = 2;
      const uint8_t m_StandardTimeYearOffset = 4;
      const uint8_t m_StandardTimeMonthOffset = 5;
      const uint8_t m_StandardTimeDayOfMonthOffset = 6;
      const uint8_t m_StandardTimeDayOfWeekOffset = 7;
      const uint8_t m_StandardTimeHourOffset = 8;
      const uint8_t m_StandardTimeMinuteOffset = 9;
      const uint8_t m_DaylightTimeZoneBiasOffset = 10;
      const uint8_t m_DaylightTimeYearOffset = 12;
      const uint8_t m_DaylightTimeMonthOffset = 13;
      const uint8_t m_DaylightTimeDayOfMonthOffset = 14;
      const uint8_t m_DaylightTimeDayOfWeekOffset = 15;
      const uint8_t m_DaylightTimeHourOffset = 16;
      const uint8_t m_DaylightTimeMinuteOffset = 17;
      const uint8_t m_TimeZoneDescriptionIndexOffset = 18;

      const uint8_t m_TimeZoneBiasUtcSize = 2;
      const uint8_t m_StandardTimeZoneBiasSize = 2;
      const uint8_t m_DaylightTimeZoneBiasSize = 2;

};
#endif //TIMEZONEDATALINKPARAM_H

