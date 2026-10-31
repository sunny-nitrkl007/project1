////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Caterpillar Inc.  All Rights Reserved.
//
//     Class: SecuritySystemCurrentKeyParam
//
// File Name: SecuritySystemCurrentKeyParam.h
//
//  Abstract: Parse Security System Current Key Information
//            (CAT EXT F06B) fields from a sequence of data link bytes.
//            This class is a helper to class DataLinkParam.
//
////////////////////////////////////////////////////////
#ifndef SECURITYSYSTEMCURRENTKEYPARAM_H
#define SECURITYSYSTEMCURRENTKEYPARAM_H

#include "VarLengthDataLinkParam.h"
#include <cat_std_types.h>
#include <cstring>

class SecuritySystemCurrentKeyParam : public VarLengthDataLinkParam
{
public:
    static constexpr auto ParameterName = "SecuritySystemCurrentKey";
    static constexpr uint32_t CatExtId = 0xF06B;
    static constexpr size_t m_DataLengthMinSize = 13; // Assumes Key Description field is empty
    static constexpr size_t m_KeyIDSize = 8;
    static constexpr size_t m_KeyDescriptionMaxSize = 30 - m_DataLengthMinSize;

    enum class KeyExpirationFlag : uint8_t
    {
        KeyDoesNotExpire = 0x00,
        KeyExpires,
        NotAvailable
    };

    enum class KeyAccessLevel : uint8_t
    {
        Master = 0x01,
        Operator,
    };

    typedef std::array<uint8_t, m_KeyIDSize> KeyID_t;


    // === Constructors / Destructors ===
    SecuritySystemCurrentKeyParam(DataLinkParam& param) : VarLengthDataLinkParam(param) {}

    SecuritySystemCurrentKeyParam(VarLengthParamBlock_t& paramValue) :
                VarLengthDataLinkParam(paramValue) {}

    ~SecuritySystemCurrentKeyParam(){}

    inline bool isSizeOk() const {
        return m_ParamValue.size() >= m_DataLengthMinSize;
    }

    //=== Set Accessor Functions ===
    //=== The following functions can be used to set the set the corresponding field

    // Range of -1 to 2,147,483,647 is supported
    inline void SetKeyID(int32_t keyID) {
        if (!isSizeOk()) {
            m_ParamValue.resize(m_DataLengthMinSize);
        }

        // Encode -1 as two's complement
        if (keyID < 0) {
            for (size_t i = 0; i < m_KeyIDSize; ++i) {
                m_ParamValue[m_KeyIDOffset + i] = 0xFF;
            }
        }
        else {
            // Clear out 4 MSBs
            for (int i = 0; i < 4; ++i) {
                m_ParamValue[m_KeyIDOffset + i] = 0;
            }
            // Encode keyID into 4 LSBs
            m_ParamValue[m_KeyIDOffset + 4] = keyID >> 24;
            m_ParamValue[m_KeyIDOffset + 5] = (keyID >> 16) & 0xFF;
            m_ParamValue[m_KeyIDOffset + 6] = (keyID >> 8)  & 0xFF;
            m_ParamValue[m_KeyIDOffset + 7] = keyID         & 0xFF;
        }
    }

    inline void SetKeyExpirationFlag(KeyExpirationFlag keyExpirationFlag) { 
        if (!isSizeOk()) {
            m_ParamValue.resize(m_DataLengthMinSize);
        }
        m_ParamValue[m_KeyExpirationFlagOffset] = static_cast <uint8_t>(keyExpirationFlag);
    }

    inline void SetKeyAccessLevel(uint8_t keyAccessLevel) {
        if (!isSizeOk()) {
            m_ParamValue.resize(m_DataLengthMinSize);
        }
        m_ParamValue[m_KeyAccessLevelOffset] = keyAccessLevel;
    }

    inline void SetKeyExpirationMonth(uint8_t month) {
        if (!isSizeOk()) {
            m_ParamValue.resize(m_DataLengthMinSize);
        }
        m_ParamValue[m_KeyExpirationMonthOffset] = month;
    }

    inline void SetKeyExpirationDay(uint8_t day) {
        if (!isSizeOk()) {
            m_ParamValue.resize(m_DataLengthMinSize);
        }
        m_ParamValue[m_KeyExpirationDayOffset] = day;
    }

    inline void SetKeyExpirationYear(uint8_t year) {
        if (!isSizeOk()) {
            m_ParamValue.resize(m_DataLengthMinSize);
        }
        m_ParamValue[m_KeyExpirationYearOffset] = year;
    }

    inline void SetKeyDescription(const std::string& keyDescription) {
        // Truncate string if necessary        
        std::string keyDescriptionTrunc = (keyDescription.size() > m_KeyDescriptionMaxSize) ? 
                                           keyDescription.substr(0, m_KeyDescriptionMaxSize) :
                                           keyDescription;

        auto descriptionSize = keyDescriptionTrunc.size();
        m_ParamValue.resize(m_DataLengthMinSize + descriptionSize);
        m_ParamValue[m_KeyDescriptionLengthOffset] = descriptionSize;
        for (size_t i = 0; i < descriptionSize; ++i) {
            m_ParamValue[m_KeyDescriptionOffset + i] = keyDescriptionTrunc[i];
        }
    }

    //=== Get Accessor Functions ===
    //=== The following functions return the corresponding field parsed from the m_ParamValue byte sequence.

    inline bool GetKeyID(KeyID_t &keyID) const {
        if (isSizeOk()) {
            std::copy(&m_ParamValue[m_KeyIDOffset], &m_ParamValue[m_KeyIDOffset], keyID.begin());
            return true;
        }
        return false;
    }

    // keyID will be in the range of -1 to 2,147,483,647
    inline bool GetKeyID(int32_t &keyID) const {
        if (isSizeOk()) {
            // Check if encoded as two's complement negative number
            if (((m_ParamValue[m_KeyIDOffset] & m_KeyIdSkipBitmask) == m_KeyIdSkipBitmask)) {
                keyID = -1;
            }
            else {
                // Convert least significant 4 bytes into an int32_t
                keyID = (m_ParamValue[m_KeyIDOffset + 4] << 24)  +
                        (m_ParamValue[m_KeyIDOffset + 5] << 16)  +
                        (m_ParamValue[m_KeyIDOffset + 6] << 8)   +
                         m_ParamValue[m_KeyIDOffset + 7];
            }
            return true;
        }
        return false;
    }

    inline KeyExpirationFlag GetKeyExpirationFlag() const {
        if (isSizeOk()) {
            uint8_t keyExpirationFlagRaw = ((m_ParamValue[m_KeyExpirationFlagOffset] & m_KeyExpirationFlagBitmask) >> m_KeyExpirationFlagBitshift);
            if (keyExpirationFlagRaw > static_cast<uint8_t>(KeyExpirationFlag::NotAvailable))
            {
                keyExpirationFlagRaw = static_cast<uint8_t>(KeyExpirationFlag::NotAvailable);
            }

            return static_cast<KeyExpirationFlag>(keyExpirationFlagRaw);
        }
        return KeyExpirationFlag::NotAvailable;
    }

    inline uint8_t GetKeyAccessLevel() const {
        return isSizeOk() ? (m_ParamValue[m_KeyAccessLevelOffset] & m_KeyAccessLevelBitmask) : 0;
    }

    inline uint8_t GetKeyExpirationMonth() const {
        return isSizeOk() ? m_ParamValue[m_KeyExpirationMonthOffset] : 0;
    }

    inline uint8_t GetKeyExpirationDay() const {
        return isSizeOk() ? m_ParamValue[m_KeyExpirationDayOffset] : 0;
    }

    inline uint8_t GetKeyExpirationYear() const {
        return isSizeOk() ? m_ParamValue[m_KeyExpirationYearOffset] : 0;
    }

    inline uint8_t GetKeyDescriptionLength() const {
        return isSizeOk() ? m_ParamValue[m_KeyDescriptionLengthOffset] : 0;
    }

    inline bool GetKeyDescription(std::string& keyDescription) const {
        uint8_t length = GetKeyDescriptionLength();
        auto size = m_ParamValue.size();
        if (size >= m_DataLengthMinSize) {
            size -= m_DataLengthMinSize;
            if (size < length) {
                length = size;
            }

            keyDescription.resize(length);
            for (size_t i = 0; i < length; ++i) {
                keyDescription[i] = m_ParamValue[i + m_KeyDescriptionOffset];
            }

            return true;
        }
        return false;
    }

private:
    static constexpr uint8_t m_KeyIdSkipBitmask = 0xFF;
    static constexpr uint8_t m_KeyIDOffset = 0;
    static constexpr uint8_t m_KeyExpirationFlagOffset = 8;
    static constexpr uint8_t m_KeyExpirationFlagBitmask = 0x80;  //TODO: Little or big endian?
    static constexpr uint8_t m_KeyExpirationFlagBitshift = 7;
    static constexpr uint8_t m_KeyAccessLevelOffset = 8;
    static constexpr uint8_t m_KeyAccessLevelBitmask = 0x7F;
    static constexpr uint8_t m_KeyExpirationMonthOffset = 9;
    static constexpr uint8_t m_KeyExpirationDayOffset = 10;
    static constexpr uint8_t m_KeyExpirationYearOffset = 11;
    static constexpr uint8_t m_KeyDescriptionLengthOffset = 12;
    static constexpr uint8_t m_KeyDescriptionOffset = 13;
};
#endif //SECURITYSYSTEMCURRENTKEYPARAM_H
