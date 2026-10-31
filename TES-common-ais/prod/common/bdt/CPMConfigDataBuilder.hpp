#pragma once

#include <algorithm>
#include <map>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cctype>
#include <memory>

#include "DataBuilder.hpp"
#include "EntryNameRecord.hpp"
#include "GidData.hpp"
#include "GidEncoding.hpp"

#ifndef BDT_CPMCONFIGDATABUILDER_HPP
#define BDT_CPMCONFIGDATABUILDER_HPP

namespace tes_common_ais {

    class CPMConfigDataBuilder
    {
    public:
        CPMConfigDataBuilder(uint16_t fileType) :
            wasBuildSuccessful_(false),
            fileType_(fileType) {
            if (0xC835 == fileType_) {
                maxNameLength_ = 14; // Operator Information
            }
            else {
                maxNameLength_ = 15;
            }
        }

        const std::vector<EntryNameRecord>& getAllRecords() const {
            return entryNameRecords_;
        }

        void addEntryNameRecord(EntryNameRecord&& entry) {
            entryNameRecords_.push_back(std::forward<EntryNameRecord>(entry));
        }

        uint32_t getFileType() const {
            return fileType_;
        }

        const std::vector<std::shared_ptr<const GidEncoding> >& getGidEncodings() const {
            return pOrderedGidEncodings_;
        }

        void addGidEncoding(const std::shared_ptr<const GidEncoding>& pEncoding) {
            pOrderedGidEncodings_.push_back(pEncoding);
        }

        void addGidEncoding(GidEncoding&& encoding) {
            pOrderedGidEncodings_.push_back(
                std::make_shared<const GidEncoding>(
                    std::forward<GidEncoding>(encoding)));
        }

        uint16_t getMaximumNameLength() const {
            return maxNameLength_;
        }

        bool build(std::vector<unsigned char>& data) {
            wasBuildSuccessful_ = false;
            try {
                DataBuilder builder(data);
                // Build header
                buildOnboardFileHeader(builder);
                buildSiteConfigDataRecordBlock(builder);
                wasBuildSuccessful_ = true;
            }
            catch (std::exception &e) {
                std::cerr << "CPMConfigDataBuilder::Build | Exception message: " << e.what() << std::endl;
            }
            return wasBuildSuccessful_;
        }

    private:
        void buildOnboardFileHeader(DataBuilder& b) const {
            b.putMsbData<uint16_t>(0xB100);
            b.putMsbData<uint16_t>(0x0001);
            b.putMsbData<uint16_t>(0xFFFF); // Reserved
            b.putMsbData<uint16_t>(fileType_); // File Type
            b.putMsbData<uint16_t>(0x0104); // Data Representation Type
            b.putMsbData<uint32_t>(0x00000001); // Number Of Sub Files
        }

        void buildSiteConfigDataRecordBlock(DataBuilder& b) const {
            size_t beginIndex = b.getCurrentEnd(); // Here is what the standard says

            b.putMsbData<uint16_t>(fileType_); // Block Id

            //size_t beginIndex = b.getCurrentEnd(); // Here is what ET does

            b.putMsbData<uint16_t>(0x0001); // Block Version
            b.putMsbData<uint32_t>(0xFFFFFFFF); // Record Id

            size_t blockSizeIndex = b.getCurrentEnd();
            b.putMsbData<uint32_t>(0x00000000); // Placeholder for block size

            b.putMsbData<uint16_t>(std::max<uint16_t>(500, entryNameRecords_.size())); // Maximum number of records

            b.putMsbData<uint16_t>(maxNameLength_); // Maximum name length

            b.putMsbData<uint16_t>(static_cast<uint16_t>(entryNameRecords_.size()) + 1); // Number of 4222 Blocks + one 4026 block

            buildGidEncodingRecordBlock(b);

            if (!entryNameRecords_.empty()) {
                buildEntryNameRecordBlocks(b);
            }

            // Back fill in the block size.
            size_t endIndex = b.getCurrentEnd();
            b.putMsbDataAt<uint32_t>(endIndex - beginIndex, blockSizeIndex);
        }

        void buildUtf8ResizeString(std::string &str,  size_t resize_len) const {

            if(str.size() <= resize_len) {
                // Sting length already less than resize length.
                return;
            }

            size_t resize_index = 0; // Byte index to count back to start last utf-8 code point.
            for (resize_index = resize_len; (resize_index > 0) && (0x80 == (0xc0 & str[resize_index])); resize_index--) {
                //  Moving the Resize Index to start of last codepoint within resize length.
            }

            // Resize string at last whole UTF-8 multi-byte character.

            str.resize(resize_index);
        }

        void buildEntryNameRecordBlocks(DataBuilder& b) const {
            uint16_t instance = 0;
            for (const auto& entry : entryNameRecords_) {
                b.putMsbData<uint16_t>(0x4222); // Block Id
                b.putMsbData<uint32_t>(entry.getRecordIdNumber()); // Record Number

                const uint16_t securityAccessLevel = (
                        ((static_cast<uint16_t>(entry.getSecurityVersion())              << 8) & 0xFF00) |
                        ((static_cast<uint16_t>(entry.getReadSecurityProtectionLevel())  << 4) & 0x00F0) |
                        ((static_cast<uint16_t>(entry.getWriteSecurityProtectionLevel()) << 0) & 0x000F)
                    );
                b.putMsbData<uint16_t>(securityAccessLevel); // Security Access Level
                b.putMsbData<uint16_t>(1); // Number of Sub-files

                std::string name = entry.getName();
                if (name.size() > maxNameLength_) {

                    buildUtf8ResizeString(name, maxNameLength_);
                }
                b.putMsbData<uint16_t>(static_cast<uint16_t>(name.size())); // Name Length
                b.putData(name);

                buildGidDataRecordBlock(b, entry, 0);
                instance++;
            }
        }

        void buildGidDataRecordBlock(DataBuilder& b, const EntryNameRecord& entry, uint16_t instance) const {
            b.putMsbData<uint16_t>(0x4021); // Block Id
            b.putMsbData<uint16_t>(instance); // Instance Number (just in case the receiving end can't count?)

            const std::map<uint32_t, GidData>& gidDatas = entry.getGidData();
            for (const auto& pEncoding : pOrderedGidEncodings_) {
                const GidData& data = gidDatas.at(pEncoding->getGid());
                b.putData(data.getRawData()); // Put in the raw encoding data
            }
        }
        
        void buildGidEncoding(DataBuilder& b, const std::shared_ptr<const GidEncoding>& pEncoding) const {
            b.putMsbData<uint32_t>(pEncoding->getGid()); // Gid

            const uint8_t encodingVersion = pEncoding->getEncodingVersion();
            if (0x02 != encodingVersion) {
                throw std::runtime_error("Unsupported GID Encoding Version. Only version 0x02 is supported.");
            }
            b.putMsbData<uint8_t>(encodingVersion); // Gid Encoding Version

            const uint8_t dataCharacteristics = (
                    ((static_cast<uint8_t>(pEncoding->getDsiDefinition())       << 5) & 0xE0) |
                    ((static_cast<uint8_t>(pEncoding->getDataOrderDefinition()) << 3) & 0x18) |
                    ((static_cast<uint8_t>(pEncoding->getDataLengthType())      << 0) & 0x07)
                );
            b.putMsbData<uint8_t>(dataCharacteristics); // Gid Encoding Characteristics

            b.putMsbData<uint16_t>(pEncoding->getBitLength()); // Length in Bits

            b.putMsbData<uint8_t>(pEncoding->getDataType()); // Data Type

            const std::vector<unsigned char>& subStructure = pEncoding->getSubStructure();
            b.putMsbData<uint8_t>(static_cast<uint8_t>(subStructure.size())); // Substructure Size in Bytes
            b.putDataSubset(subStructure); // Substructure
        }

        void buildGidEncodingRecordBlock(DataBuilder& b) const {
            b.putMsbData<uint16_t>(0x4026);
            b.putMsbData<uint16_t>(static_cast<uint16_t>(pOrderedGidEncodings_.size())); // Number of combinations.
            for (const auto& pEncoding : pOrderedGidEncodings_) {
                buildGidEncoding(b, pEncoding);
            }
        }

    public:
        bool wasBuildSuccessful_;

    private:
        std::vector<EntryNameRecord> entryNameRecords_;

        uint16_t fileType_;

        uint16_t maxNameLength_;

        std::vector<std::shared_ptr<const GidEncoding> > pOrderedGidEncodings_;
    };
}

#endif
