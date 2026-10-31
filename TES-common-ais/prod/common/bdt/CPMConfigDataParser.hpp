#pragma once

#include <algorithm>
#include <map>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cctype>

#include "DataExtractor.hpp"
#include "EntryNameRecord.hpp"
#include "GidData.hpp"
#include "GidEncoding.hpp"

#ifndef BDT_CPMCONFIGDATAPARSER_HPP
#define BDT_CPMCONFIGDATAPARSER_HPP

namespace tes_common_ais {

    class CPMConfigDataParser
    {
    public:
        CPMConfigDataParser(uint16_t expectedFileType) :
            wasParseSuccessful_(false),
            fileType_(expectedFileType),
            maxNameLength_(0),
            maxNumberOfRecords_(0),
            recordIdNumber_(0xFFFFFFFF) {}

        const std::vector<EntryNameRecord>& getAllRecords() const {
            if (wasParseSuccessful_) {
                return entryNameRecords_;
            }
            else {
                throw std::logic_error(
                    "Don't call this function if Parse has not been "
                    "called or was unsuccessful");
            }
        }

        uint32_t getFileType() const {
            if (wasParseSuccessful_) {
                return fileType_;
            }
            else {
                throw std::logic_error(
                    "Don't call this function if Parse has not been "
                    "called or was unsuccessful");
            }
        }

        const std::vector<std::shared_ptr<const GidEncoding> >& getGidEncodings() const {
            return pOrderedGidEncodings_;
        }

        uint16_t getMaximumNameLength() const {
            if (wasParseSuccessful_) {
                return maxNameLength_;
            }
            else {
                throw std::logic_error(
                    "Don't call this function if Parse has not been "
                    "called or was unsuccessful");
            }
        }

        uint16_t getMaximumNumberOfRecords() const {
            if (wasParseSuccessful_) {
                return maxNumberOfRecords_;
            }
            else {
                throw std::logic_error(
                    "Don't call this function if Parse has not been "
                    "called or was unsuccessful");
            }
        }

        const EntryNameRecord getRecordByRecordIdNumber(uint32_t recordIdNumber) const {
            if (wasParseSuccessful_) {
                auto pred = [recordIdNumber](const EntryNameRecord& r) { return (r.getRecordIdNumber() == recordIdNumber); };
                std::vector<EntryNameRecord>::const_iterator found = std::find_if(entryNameRecords_.cbegin(), entryNameRecords_.cend(), pred);
                return *found; // BUG: What if it is not found?
            }
            else {
                throw std::logic_error(
                    "Don't call this function if Parse has not been "
                    "called or was unsuccessful");
            }
        }

        uint32_t getRecordIdNumber() const {
            if (wasParseSuccessful_) {
                return recordIdNumber_;
            }
            else {
                throw std::logic_error(
                    "Don't call this function if Parse has not been "
                    "called or was unsuccessful");
            }
        }

        bool parse(const std::vector<unsigned char>& data) {
            wasParseSuccessful_ = false;
            try {
                DataExtractor extractor(data);
                if (isValidOnBoardFileHeader(extractor)) {
                    if (isValidSiteConfigDataRecordBlock(extractor)) {
                        parseSiteConfigDataRecordBlock(extractor); // throws on parse error
                        wasParseSuccessful_ = true;
                    }
                }
            }
            catch (std::exception &e) {
                std::cerr << "CPMConfigDataBuilder::Parse | Exception message: " << e.what() << std::endl;
            }

            return wasParseSuccessful_;
        }

    private:
        unsigned int calculateDataBytes(unsigned int numberOfBits) const {
            return (((numberOfBits % 8) == 0) ? (numberOfBits / 8) : ((numberOfBits / 8) + 1));
        }

        // Throws on parse error
        bool isValidOnBoardFileHeader(DataExtractor &ex) const {
            bool isValidHeader = (0xB100 == ex.getMsbData<uint16_t>());
            bool isValidVersion = (0x0001 == ex.getMsbData<uint16_t>());

            // Skip reserved bytes
            ex.skipBytes(2);

            // What type of information record block?
            bool isValidFileContentsType = (fileType_ == ex.getMsbData<uint16_t>());

            // GID Format
            bool isValidDataRepresentationType = (0x0104 == ex.getMsbData<uint16_t>());
            bool isValidNumberOfSubFiles = (0x00000001 == ex.getMsbData<uint32_t>());

            return (
                isValidHeader &&
                isValidVersion &&
                isValidFileContentsType &&
                isValidDataRepresentationType &&
                isValidNumberOfSubFiles
            );
        }

        // Throws on parse error
        bool isValidSiteConfigDataRecordBlock(DataExtractor& ex) const {
            bool isValidBlockId = (fileType_ == ex.getMsbData<uint16_t>());
            bool isValidBlockVersion = (0x0001 == ex.getMsbData<uint16_t>());
            return (isValidBlockId && isValidBlockVersion);
        }

        // Throws on parse error
        void parseEntryNameRecordBlocks(DataExtractor& ex, uint16_t numRecordBlocks) {
            for (uint32_t blockIndex = 0; blockIndex < numRecordBlocks; blockIndex++) {
                const uint16_t blockId = ex.getMsbData<uint16_t>();
                if (0x4222 == blockId)
                {
                    uint32_t recordIdNumber = ex.getMsbData<uint32_t>();
                    uint16_t securityAccessLevel = ex.getMsbData<uint16_t>();
                    uint8_t securityVersion = (securityAccessLevel & 0xFF00) >> 8;
                    uint8_t readSecurityProtectionLevel = (securityAccessLevel & 0x00F0) >> 4;
                    uint8_t writeSecurityProtectionLevel = securityAccessLevel & 0x000F;
                    uint16_t numberOfSubFiles = ex.getMsbData<uint16_t>();
                    if (1 != numberOfSubFiles) { // SE.SYS.Perform.FRD00250: V1.2 Section 2.2.3.2.2
                        throw std::runtime_error("Must be exactly one GID Data Record Block present");
                    }
                    uint16_t nameLength = ex.getMsbData<uint16_t>();
                    std::string name = ex.getString(nameLength);

                    // Map from GID to GidData
                    std::map<uint32_t, GidData> gidData = parseGidDataRecordBlock(ex);

                    entryNameRecords_.push_back(EntryNameRecord(recordIdNumber, name, gidData, securityVersion,
                        readSecurityProtectionLevel, writeSecurityProtectionLevel));
                }
                else {
                    throw std::runtime_error("Invalid Entry Name Record Block ID");
                }
            }
        }

        std::map<uint32_t, GidData> parseGidDataRecordBlock(DataExtractor& ex) const {
            const uint16_t blockId = ex.getMsbData<uint16_t>();
            if (0x4021 == blockId) {
                ex.skipBytes(2); // Skip over Instance Number

                std::map<uint32_t, GidData> gidDatas; // <GID, GidData>

                for (const auto& pEncoding : pOrderedGidEncodings_) {
                    std::vector<unsigned char> data;

                    switch (pEncoding->getDataLengthType()) {

                    case GidEncoding::GidDataLengthType::FIXED:
                    case GidEncoding::GidDataLengthType::FIXED_WITH_BYTE_COUNT:
                        {
                            unsigned int byteCount = calculateDataBytes(pEncoding->getBitLength());
                            data = ex.getDataSubset(byteCount);
                        }
                        break;

                    case GidEncoding::GidDataLengthType::VARIABLE_WITH_BYTE_COUNT:
                        {
                            data.push_back(ex.getMsbData<unsigned char>());
                            std::vector<unsigned char> tempData = ex.getDataSubset(data[0]);
                            data.insert(data.end(), tempData.begin(), tempData.end());
                        }
                        break;

                    case GidEncoding::VARIABLE_DELIMITED:
                        {
                            data = parseGidDataVariableWithDelimiter(ex, pEncoding);
                        }
                        break;

                    default:
                        throw std::runtime_error("Unsupported Data Length Type");
                        break;
                    }

                    GidData gidData(pEncoding, data);
                    gidDatas.insert(std::make_pair(gidData.getGid(), gidData));
                }

                return gidDatas;
            }
            else {
                throw std::runtime_error("Invalid GID Data Record Block ID");
            }
        }

        std::vector<unsigned char> parseGidDataVariableWithDelimiter(DataExtractor& ex,
            const std::shared_ptr<const GidEncoding>& pEncoding) const {

            std::vector<unsigned char> data;

            switch (pEncoding->getDataType()) {
            
            case GidEncoding::GidDataType::ASCII_STRING:
                {
                    const std::vector<unsigned char> subStructure(pEncoding->getSubStructure());
                    data = parseGidDataVariableWithDelimiterASCII(ex, subStructure);
                }
                break;

            case GidEncoding::GidDataType::UNICODE_STRING:
                {
                    const std::vector<unsigned char> subStructure(pEncoding->getSubStructure());
                    data = ParseGidDataVariableWithDelimiterUnicode(ex, subStructure);
                }
                break;

            default:
                throw std::runtime_error("Unsupported data type for variable data length with delimiter");
                break;
            }

            return data;
        }

        std::vector<unsigned char> parseGidDataVariableWithDelimiterASCII(DataExtractor& ex, const std::vector<unsigned char>& subStructure) const {
            if (1 == subStructure.size()) {
                const unsigned char delimiter = subStructure[0];
                std::vector<unsigned char> data;
                unsigned char asciiCharacter;
                do
                {
                    asciiCharacter = ex.getMsbData<unsigned char>();
                    data.push_back(asciiCharacter);
                } while (delimiter != asciiCharacter);

                return data;
            }
            else {
                throw std::runtime_error("Invalid encoding for ASCII data type");
            }
        }

        std::vector<unsigned char> ParseGidDataVariableWithDelimiterUnicode(DataExtractor& ex, const std::vector<unsigned char>& subStructure) const {
            if (2 == subStructure.size()) {
                const uint16_t delimiter = (subStructure[0] << 8) | subStructure[1];
                std::vector<unsigned char> data;
                uint16_t testCharacter;
                do
                {
                    unsigned char firstByte = ex.getMsbData<unsigned char>();
                    unsigned char secondByte = ex.getMsbData<unsigned char>();
                    testCharacter = (firstByte << 8) | secondByte;

                    data.push_back(firstByte);
                    data.push_back(secondByte);
                } while (delimiter != testCharacter);

                return data;
            }
            else {
                throw std::runtime_error("Invalid encoding for Unicode data type");
            }
        }

        GidEncoding parseGidEncoding(DataExtractor &ex) const {
            const uint32_t gid = ex.getMsbData<uint32_t>();
            const uint8_t encodingVersion = ex.getMsbData<uint8_t>();
            if (0x02 != encodingVersion) {
                throw std::runtime_error("Unsupported GID Encoding Version. Only version 0x02 is supported.");
            }
            const uint8_t dataCharacteristics = ex.getMsbData<uint8_t>();
            const uint16_t dataLengthInBits = ex.getMsbData<uint16_t>();
            const uint8_t dataType = ex.getMsbData<uint8_t>();
            const uint8_t subStructureLengthInBytes = ex.getMsbData<uint8_t>();
            std::vector<unsigned char> subStructure(ex.getDataSubset(subStructureLengthInBytes));

            return GidEncoding(gid, encodingVersion,
                static_cast<GidEncoding::GidDsiDefinition>((dataCharacteristics & 0xE0) >> 5),
                static_cast<GidEncoding::GidDataOrder>((dataCharacteristics & 0x18) >> 3),
                static_cast<GidEncoding::GidDataLengthType>(dataCharacteristics & 0x07), dataLengthInBits,
                static_cast<GidEncoding::GidDataType>(dataType), subStructure);
        }

        // Throws on parse error
        void parseGidEncodingRecordBlock(DataExtractor &ex) {
            const uint16_t blockId = ex.getMsbData<uint16_t>();
            if (0x4026 == blockId) { // Global ID and Encoding Block
                uint16_t numberOfCombinations = ex.getMsbData<uint16_t>();
                while (numberOfCombinations > 0) {
                    auto pEncoding = std::make_shared<const GidEncoding>(parseGidEncoding(ex));
                    pOrderedGidEncodings_.push_back(pEncoding);
                    numberOfCombinations--;
                }
            }
            else {
                throw std::runtime_error("Invalid GID+Encoding Record Block ID");
            }
        }

        // Throws on parse error
        void parseSiteConfigDataRecordBlock(DataExtractor &ex) {
            recordIdNumber_ = ex.getMsbData<uint32_t>();
            const uint32_t blockSize = ex.getMsbData<uint32_t>();
            maxNumberOfRecords_ = ex.getMsbData<uint16_t>();
            maxNameLength_ = ex.getMsbData<uint16_t>();
            const uint16_t numSubFiles = ex.getMsbData<uint16_t>();

            // Do not enforce this, doesn't matter
            //(void)blockSize;

            // The block should be the size of the data buffer minus the on-board file block header size
            if (blockSize != (ex.getBufferSize() - 14)) {
                throw std::runtime_error(
                    "Actual BDT data buffer length does match block size extracted from buffer");
            }

            pOrderedGidEncodings_.clear();

            if (numSubFiles >= 1) {
                parseGidEncodingRecordBlock(ex); // throws on parse error
                if (numSubFiles >= 2) { // There might not be any records in the list yet
                    parseEntryNameRecordBlocks(ex, numSubFiles - 1); // throws on parse error
                }
            }
            else {
                throw std::runtime_error("At minimum, the GID+Encoding block (0x4026) must be present");
            }
        }

    public:
        bool wasParseSuccessful_;

    private:
        std::vector<EntryNameRecord> entryNameRecords_;

        uint16_t fileType_;

        uint16_t maxNameLength_;

        uint16_t maxNumberOfRecords_;

        std::vector<std::shared_ptr<const GidEncoding> > pOrderedGidEncodings_;

        uint32_t recordIdNumber_;
    };
}

#endif
