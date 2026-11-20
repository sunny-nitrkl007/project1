#pragma once

#include <map>
#include <string>
#include <cstdint>

#include "GidData.hpp"

#ifndef BDT_ENTRYNAMERECORD_HPP
#define BDT_ENTRYNAMERECORD_HPP

namespace tes_common_ais {

    class EntryNameRecord
    {
    public:
        EntryNameRecord(uint32_t recordIdNumber, const std::string& name,
            const std::map<uint32_t, GidData>& gidData, uint8_t securityVersion,
            uint8_t readSecurityProtectionLevel, uint8_t writeSecurityProtectionLevel) :
            gidData_(gidData),
            name_(name),
            readSecurityProtectionLevel_(readSecurityProtectionLevel),
            recordIdNumber_(recordIdNumber),
            securityVersion_(securityVersion),
            writeSecurityProtectionLevel_(writeSecurityProtectionLevel) {}

        const std::map<uint32_t, GidData>& getGidData() const {
            return gidData_;
        }

        const std::string& getName() const {
            return name_;
        }

        uint8_t getReadSecurityProtectionLevel() const {
            return readSecurityProtectionLevel_;
        }

        uint32_t getRecordIdNumber() const {
            return recordIdNumber_;
        }

        uint8_t getSecurityVersion() const {
            return securityVersion_;
        }

        uint8_t getWriteSecurityProtectionLevel() const {
            return writeSecurityProtectionLevel_;
        }

    private:
        std::map<uint32_t, GidData> gidData_;

        std::string name_;

        uint8_t readSecurityProtectionLevel_;

        uint32_t recordIdNumber_;

        uint8_t securityVersion_;

        uint8_t writeSecurityProtectionLevel_;
    };

}

#endif
