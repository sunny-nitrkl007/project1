////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Caterpillar Inc.  All Rights Reserved.
//
//     Class: SecuritySystemCurrentSecurityIDParam
//
// File Name: SecuritySystemCurrentSecurityIDParam.h
//
//  Abstract: Parse Security System Current Security ID Information
//            (CAT EXT F0B2) fields from a sequence of data link bytes.
//            This class is a helper to class DataLinkParam.
//
////////////////////////////////////////////////////////
#ifndef SECURITYSYSTEMCURRENTSECURITYIDPARAM_H
#define SECURITYSYSTEMCURRENTSECURITYIDPARAM_H

#include <string>
#include <algorithm>

#include <oel_pack.h>

#include "VarLengthDataLinkParam.h"

class SecuritySystemCurrentSecurityIDParam : public VarLengthDataLinkParam
{
public:
    static constexpr auto ParameterName = "SecuritySystemCurrentSecurityID";
    static constexpr uint32_t CatExtId = 0xF0B2;

    // 2 for the extension id and 8 for required data and 1 for minimum id length
    static constexpr size_t m_DataLengthMinSize = 2 + 8 + 1;

    // === Constructors / Destructors ===
    SecuritySystemCurrentSecurityIDParam(DataLinkParam& param) : VarLengthDataLinkParam(param) {}

    SecuritySystemCurrentSecurityIDParam(VarLengthParamBlock_t& paramValue) :
                VarLengthDataLinkParam(paramValue) {}

    ~SecuritySystemCurrentSecurityIDParam(){}

    inline bool isSizeOk() const {
        return m_ParamValue.size() >= m_DataLengthMinSize;
    }

    //=== Set Accessor Functions ===
    //=== The following functions can be used to set the set the corresponding field

    inline void initialize() {
        m_ParamValue.resize(m_DataLengthMinSize);
        m_ParamValue[m_IDLengthOffset] = 1;
        m_ParamValue[m_IDDescriptionLengthOffset] = 0;
        m_ParamValue[m_IDOffset] = 0;
    }

    // Set ID to a single byte (min size)
    inline void setID(uint8_t id) {
        std::vector<uint8_t> idVector{id};
        setID(idVector);
    }

    inline void setID(int32_t id) {
        // Encode -1 as two's complement
        if (id < 0) {
            std::vector<uint8_t> idVector{ 0xFF, 0xFF, 0xFF, 0xFF };
            setID(idVector);
        }
        else {
            std::vector<uint8_t> idVector(4);
            OEL_PACK_BE_32_NO_INCR(idVector.data(), id);
            setID(idVector);
        }
    }

    inline bool setID(const std::vector<uint8_t>& id) {

        if (id.size() > 255) {
            return false;
        }

        if (!isSizeOk()) {
            initialize();
        }

        uint8_t newIdLength = id.size();

        if (newIdLength != m_ParamValue[m_IDLengthOffset]) {
            // ID length changed, need to move id description
            std::string idDescription;
            getIDDescription(idDescription);

            // Make sure we are big enough
            m_ParamValue.resize(m_DataLengthMinSize + newIdLength + idDescription.size() - 1);

            // Put in the new ID length
            m_ParamValue[m_IDLengthOffset] = newIdLength;

            // Put in the new ID
            std::copy(id.cbegin(), id.cend(), m_ParamValue.begin() + m_IDOffset);

            // Put in the old ID Description
            setIDDescription(idDescription);
        }
        else {
            // Make sure we are big enough
            m_ParamValue.resize(m_DataLengthMinSize + newIdLength + getIDDescriptionLength() - 1);

            // Put in the new ID length
            m_ParamValue[m_IDLengthOffset] = newIdLength;

            // Put in the new ID
            std::copy(id.cbegin(), id.cend(), m_ParamValue.begin() + m_IDOffset);
        }

        return true;
    }

    inline void setExpirationFlag(bool expires) {
        if (!isSizeOk()) {
            initialize();
        }
        if (expires) {
            m_ParamValue[m_ExpirationFlagOffset] |= m_ExpirationFlagBitmask;
        }
        else {
            m_ParamValue[m_ExpirationFlagOffset] &= ~m_ExpirationFlagBitmask;
        }
    }

    inline void setAccessLevel(uint8_t accessLevel) {
        if (!isSizeOk()) {
            initialize();
        }
        uint8_t temp = m_ParamValue[m_AccessLevelOffset] & ~m_AccessLevelBitmask;
        temp |= accessLevel & m_AccessLevelBitmask;
        m_ParamValue[m_AccessLevelOffset] = temp;
    }

    inline void setExpirationMonth(uint8_t month) {
        if (!isSizeOk()) {
            initialize();
        }
        m_ParamValue[m_ExpirationMonthOffset] = month;
    }

    inline void setExpirationDay(uint8_t day) {
        if (!isSizeOk()) {
            initialize();
        }
        m_ParamValue[m_ExpirationDayOffset] = day;
    }

    inline void setExpirationYear(uint8_t year) {
        if (!isSizeOk()) {
            initialize();
        }
        m_ParamValue[m_ExpirationYearOffset] = year;
    }

    inline bool setIDDescription(const std::string& idDescription) {
        if (idDescription.size() > 255) {
            return false;
        }

        if (!isSizeOk()) {
            initialize();
        }
        
        uint8_t size = idDescription.size();
        auto offset = m_IDOffset + getIDLength();
        m_ParamValue.resize(m_DataLengthMinSize + m_ParamValue[m_IDLengthOffset] - 1 + size);
        m_ParamValue[m_IDDescriptionLengthOffset] = size;
        std::copy(idDescription.cbegin(), idDescription.cend(), m_ParamValue.begin() + offset);
        return true;
    }

    //=== Get Accessor Functions ===
    //=== The following functions return the corresponding field parsed from the m_ParamValue byte sequence.
    inline bool getExpirationFlag() const {
        return isSizeOk() ? (0 != (m_ParamValue[m_ExpirationFlagOffset] & m_ExpirationFlagBitmask)) : false;
    }

    inline uint8_t getAccessLevel() const {
        return isSizeOk() ? (m_ParamValue[m_AccessLevelOffset] & m_AccessLevelBitmask) : 0;
    }

    inline uint8_t getExpirationMonth() const {
        return isSizeOk() ? m_ParamValue[m_ExpirationMonthOffset] : 0;
    }

    inline uint8_t getExpirationDay() const {
        return isSizeOk() ? m_ParamValue[m_ExpirationDayOffset] : 0;
    }

    inline uint8_t getExpirationYear() const {
        return isSizeOk() ? m_ParamValue[m_ExpirationYearOffset] : 0;
    }

    inline size_t getIDDescriptionLength() const {
        return isSizeOk() ? m_ParamValue[m_IDDescriptionLengthOffset] : 0;
    }

    inline size_t getIDLength() const {
        return isSizeOk() ? m_ParamValue[m_IDLengthOffset] : 0;
    }

    inline bool getID(std::vector<uint8_t>& id) const {
        auto idLength = getIDLength();
        if (idLength > 0) {
            if ((m_IDOffset + idLength) <= m_ParamValue.size()) {
                auto begin = m_ParamValue.cbegin() + m_IDOffset;
                auto end = begin + idLength;
                std::vector<uint8_t> temp(begin, end);
                id.swap(temp);
                return true;
            }
            else {
                return false;
            }
        }
        else {
            id.clear();
            return true;
        }
    }

    inline bool getIDDescription(std::string& idDescription) const {
        auto idLength = getIDLength();
        auto idDescriptionLength = getIDDescriptionLength();
        auto offset = m_IDOffset + idLength;
        if (idLength > 0 && (offset + idDescriptionLength) == m_ParamValue.size()) {
            // This gets the string as per the length specified in the datalink message.
            std::string temp1(reinterpret_cast<const char*>(m_ParamValue.data() + offset), idDescriptionLength);

            // This gets rid of 0x00 characters that might have been embedded in the datalink message.
            std::string temp2(temp1.c_str());

            // Stick the result in idDescription
            idDescription.swap(temp2);
            return true;
        }
        return false;
    }

/*
CATEXT $F0B2  SECURITY SYSTEM CURRENT SECURITY ID INFORMATION
Used to report the current Security ID and its related user information to the list of programmed Security IDs for the security system. See the J1939 Machine Security System Security ID Management Protocol document for more information.

Data Length:	
Priority:	6
Extended Data Page (EDP):	0
Data Page (DP)	0
PDU Format (PF):	239
PDU Specific (PS):	Destination Address
Transmission Rate:	As needed
Data Format:	$F0B2 + data below

Position	Length	Parameter
Byte 1	1 byte	Security ID Type
Byte 2, Bit 8	1 bit	Security ID Expiration Flag
Byte 2, Bits 7-1	7 bits	Security ID Access Level
Byte 3	1 byte	Security ID Expiration Month
Byte 4	1 byte	Security ID Expiration Day
Byte 5	1 byte	Security ID Expiration Year
Byte 6	1 byte	Security ID Length
Byte 7	1 byte	Security ID Description Length
Field 8	1-255 bytes	Security ID
Field 9	0-255 bytes	Security ID Description

   NOTE: the F0B2 response contains the PID:     ex: F0 B2 01 02 00 00 00 07 04 96 BC 5C 66 4A 88 CC %a 45 4B 45
         m_IDTypeOffset = 2 ..........................|
         m_ExpirationFlagOffset = 3......................|
         m_AccessLevelOffset = 3.........................|
         m_ExpirationMonthOffset = 4........................|
         m_ExpirationDayOffset = 5.............................|
         m_ExpirationYearOffset = 6...............................|
         m_IDLengthOffset = 7........................................|
         m_IDDescriptionLengthOffset = 8................................|
         m_IDOffset = 9....................................................|
*/

private:
    static constexpr size_t  m_IDTypeOffset = 2;
    static constexpr size_t  m_ExpirationFlagOffset = 3;
    static constexpr uint8_t m_ExpirationFlagBitmask = 0x80;
    static constexpr size_t  m_AccessLevelOffset = 3;
    static constexpr uint8_t m_AccessLevelBitmask = 0x7F;
    static constexpr size_t  m_ExpirationMonthOffset = 4;
    static constexpr size_t  m_ExpirationDayOffset = 5;
    static constexpr size_t  m_ExpirationYearOffset = 6;
    static constexpr size_t  m_IDLengthOffset = 7;
    static constexpr size_t  m_IDDescriptionLengthOffset = 8;
    static constexpr size_t  m_IDOffset = 9;
};
#endif //SECURITYSYSTEMCURRENTSECURITYIDPARAM_H
