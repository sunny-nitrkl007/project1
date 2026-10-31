#pragma once

#include <cstdint>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <string>

#ifndef BDT_GIDENCODING_HPP
#define BDT_GIDENCODING_HPP

namespace tes_common_ais {

    class GidEncoding
    {
    public:
        
        enum GidDsiDefinition {
            DSI_NOT_SUPPORTED = 0,
            LARGEST_32_VALUES = 1,     // e.g. CDL Unsigned
            SMALLEST_32_VALUES = 2,    // e.g. CDL Signed
            LARGEST_VALUES = 3,        // e.g. J1939 2-bit
            MOST_SIGNIFICANT_BYTE = 4  // e.g. J1939 1, 2, 3, or 4 byte
        };

        enum GidDataOrder {
            LSB_FIRST = 0,
            MSB_FIRST = 1,
            NONE = 2  // i.e. less than or equal to 1 byte
        };

        enum GidDataLengthType {
            FIXED = 0,
            FIXED_WITH_BYTE_COUNT = 1,
            VARIABLE_WITH_BYTE_COUNT = 2,  // First byte (MSB) contains data length in bytes
            VARIABLE_DELIMITED = 3         // Delimiter at end of data indicates end of data
        };

        enum GidDataType {
            ASCII_STRING = 1,    // ISO 8859 Latin-1
            UNICODE_STRING = 2,  // 2-byte
            SCALED_UNSIGNED_ZERO_OFFSET = 3,
            SCALED_UNSIGNED_NONZERO_OFFSET = 4,
            SCALED_SIGNED_ZERO_OFFSET = 5,
            SCALED_UNSIGNED_OVERRIDE_ZERO_OFFSET = 6,  // e.g. CDL Override
            SCALED_SIGNED_OVERRIDE_ZERO_OFFSET = 7,    // e.g. CDL Override
            STATE_LISTED_OVERRIDE = 8,                 // e.g. CDL Override
            STATE_MAPPED_OVERRIDE = 9,                 // e.g. CDL Override
            STATE_LISTED = 10,
            STATE_MAPPED = 11,
            BINARY = 12,
            ASCII_ENCODED_BINARY = 13,
            UNSIGNED_RADIX_ZERO_OFFSET = 14,
            SIGNED_RADIX_ZERO_OFFSET = 15,
            UNSIGNED_RADIX_NONZERO_OFFSET = 16,
            DATE_AND_TIME = 17,
            GLOBAL_IDENTIFIER = 18
        };

        GidEncoding(uint32_t gid, uint8_t encodingVersion, GidDsiDefinition dsiDefinition,
            GidDataOrder dataOrder, GidDataLengthType dataLengthType, uint16_t bitLength,
            GidDataType dataType, std::vector<unsigned char> const &subStructure) :
            bitLength_(bitLength),
            dataLengthType_(dataLengthType),
            dataOrder_(dataOrder),
            dataType_(dataType),
            dsiDefinition_(dsiDefinition),
            encodingVersion_(encodingVersion),
            gid_(gid),
            subStructure_(subStructure) {}

        uint16_t getBitLength() const {
            return bitLength_;
        }

        GidDataLengthType getDataLengthType() const {
            return dataLengthType_;
        }

        GidDataOrder getDataOrderDefinition() const {
            return dataOrder_;
        }

        GidDataType getDataType() const {
            return dataType_;
        }

        GidDsiDefinition getDsiDefinition() const {
            return dsiDefinition_;
        }

        uint8_t getEncodingVersion() const {
            return encodingVersion_;
        }

        uint32_t getGid() const {
            return gid_;
        }

        float getOffset() const {
            float offset = 0.f;

            switch (dataType_) {

            case(GidDataType::SCALED_UNSIGNED_NONZERO_OFFSET):
            {
                throw std::runtime_error("Offset decoding not supported.");
            }

            case(GidDataType::UNSIGNED_RADIX_NONZERO_OFFSET):
            {
                throw std::runtime_error("Offset decoding not supported.");
            }

            default:
                break;
            }

            return offset;
        }

        float getScaleFactor() const {
            static const float scaleFactors[] = {
                1.f, 0.005f, 0.01f, 0.05f, 0.1f, 0.125f, 0.25f, 0.4f, 0.43f, 0.5f, 2.f, 0.0015259f, 0.001f, 2.5f, 1.25f, 0.00390625f,
                0.015624f, 0.0625f, 0.00125f, 3.f, 0.0001f, 0.0036f, 0.000277778f, 0.00197f, 0.025f, 0.392f, 0.015f, 0.00000434f,
                4.f, 10.f, 0.0000001f, 0.00078125f, 0.001953125f, 0.0025f, 0.004f, 0.0078125f, 0.03125f, 1.525f, 5.f, 8.f, 16.f, 32.f,
                1000.f, 0.78125f, 0.000001f, 0.0005f, 0.002f, 2.4f, 0.010986328f, 0.2f, 0.00001f, 0.00006103515625f, 0.00051358f,
                0.3f, 0.0002f, 0.01220703125f, 0.02f, 0.01953125f, 0.078125f, 100.f, 0.36f, 0.015625f, 0.00003052f, 0.00012207f,
                0.04f, 0.0333333f, 0.0009765625f, 0.017f, 0.16f, 0.016f, 0.023f, 20.f
            };

            float scaleFactor = 1.f;

            switch(dataType_) {

            case(GidDataType::SCALED_UNSIGNED_ZERO_OFFSET):
            case(GidDataType::SCALED_SIGNED_ZERO_OFFSET):
            case(GidDataType::SCALED_UNSIGNED_OVERRIDE_ZERO_OFFSET):
            case(GidDataType::SCALED_SIGNED_OVERRIDE_ZERO_OFFSET):
            {
                uint8_t index = subStructure_[0];
                if (index < sizeof(scaleFactors) / sizeof(scaleFactors[0])) {
                    scaleFactor = scaleFactors[index];
                }
                break;
            }

            case(GidDataType::SCALED_UNSIGNED_NONZERO_OFFSET):
            {
                uint8_t index = subStructure_[0];
                if (index < sizeof(scaleFactors) / sizeof(scaleFactors[0])) {
                    scaleFactor = scaleFactors[index];
                }
                break;
            }

            case(GidDataType::UNSIGNED_RADIX_ZERO_OFFSET):
            case(GidDataType::SIGNED_RADIX_ZERO_OFFSET):
            {
                // Scale factor = 1/2^exp
                uint8_t exponent = subStructure_[0];
                scaleFactor = std::pow(2.f, -1.f*(float)exponent);
                break;
            }

            case(GidDataType::UNSIGNED_RADIX_NONZERO_OFFSET):
            {
                // Scale factor = 1/2^exp
                uint8_t exponent = subStructure_[0];
                scaleFactor = std::pow(2.f, -1.f*(float)exponent);
                break;
            }

            default:
                break;
            }

            return scaleFactor;
        }

        const std::vector<unsigned char>& getSubStructure() const {
            return subStructure_;
        }

        template<typename R>
        void encodeData(std::vector<unsigned char>& data, R value) const;

        template<typename R>
        R decodeData(const std::vector<unsigned char>& data) const;

    protected:
        uint32_t getEncodedNumericValue(const std::vector<unsigned char>& data) const {
            if (GidDataLengthType::FIXED != dataLengthType_) {
                throw std::runtime_error("Only fixed length numeric data is supported.");
            }

            uint16_t bitLength = bitLength_;

            if (0 != (bitLength % 8)) {
                throw std::runtime_error("Partial byte numeric data not supported.");
            }

            uint16_t byteLength = bitLength / 8;

            if (0 == byteLength) {
                throw std::runtime_error("0 byte numeric data is not supported.");
            }

            if (byteLength > 4) {
                throw std::runtime_error("Only up to 4 byte numeric data is supported.");
            }

            if (data.size() != byteLength) {
                throw std::runtime_error("Data vector size doesn't match byte length.");
            }

            uint32_t encodedValue = 0;

            if (GidDataOrder::LSB_FIRST == dataOrder_) {
                if (1 == byteLength) {
                    encodedValue += (((uint32_t)data[0]) << 0);
                }
                else if (2 == byteLength) {
                    encodedValue += (((uint32_t)data[0]) << 0);
                    encodedValue += (((uint32_t)data[1]) << 8);
                }
                else if (3 == byteLength) {
                    encodedValue += (((uint32_t)data[0]) << 0);
                    encodedValue += (((uint32_t)data[1]) << 8);
                    encodedValue += (((uint32_t)data[2]) << 16);
                }
                else {
                    encodedValue += (((uint32_t)data[0]) << 0);
                    encodedValue += (((uint32_t)data[1]) << 8);
                    encodedValue += (((uint32_t)data[2]) << 16);
                    encodedValue += (((uint32_t)data[3]) << 24);
                }
            }
            else if (GidDataOrder::MSB_FIRST == dataOrder_) {
                if (1 == byteLength) {
                    encodedValue += (((uint32_t)data[0]) << 0);
                }
                else if (2 == byteLength) {
                    encodedValue += (((uint32_t)data[1]) << 0);
                    encodedValue += (((uint32_t)data[0]) << 8);
                }
                else if (3 == byteLength) {
                    encodedValue += (((uint32_t)data[2]) << 0);
                    encodedValue += (((uint32_t)data[1]) << 8);
                    encodedValue += (((uint32_t)data[0]) << 16);
                }
                else {
                    encodedValue += (((uint32_t)data[3]) << 0);
                    encodedValue += (((uint32_t)data[2]) << 8);
                    encodedValue += (((uint32_t)data[1]) << 16);
                    encodedValue += (((uint32_t)data[0]) << 24);
                }
            }
            else if (GidDataOrder::NONE == dataOrder_) {
                if (byteLength != 1) {
                    throw std::runtime_error("Data order of NONE not supported for byte length > 1.");
                }

                encodedValue += (((uint32_t)data[0]) << 0);
            }
            else {
                throw std::runtime_error("Unsupported data order.");
            }

            return encodedValue;
        }

        void putEncodedNumericValue(std::vector<unsigned char>& data, uint32_t encodedValue) const {
            if (GidDataLengthType::FIXED != dataLengthType_) {
                throw std::runtime_error("Only fixed length numeric data is supported.");
            }

            uint16_t bitLength = bitLength_;

            if (0 != (bitLength % 8)) {
                throw std::runtime_error("Partial byte numeric data not supported.");
            }

            uint16_t byteLength = bitLength / 8;

            if (0 == byteLength) {
                throw std::runtime_error("0 byte numeric data is not supported.");
            }

            if (byteLength > 4) {
                throw std::runtime_error("Only up to 4 byte numeric data is supported.");
            }

            if (GidDataOrder::LSB_FIRST == dataOrder_) {
                if (1 == byteLength) {
                    data.push_back(static_cast<unsigned char>(encodedValue >> 0) & 0xFF);
                }
                else if (2 == byteLength) {
                    data.push_back(static_cast<unsigned char>(encodedValue >> 0) & 0xFF);
                    data.push_back(static_cast<unsigned char>(encodedValue >> 8) & 0xFF);
                }
                else if (3 == byteLength) {
                    data.push_back(static_cast<unsigned char>(encodedValue >> 0) & 0xFF);
                    data.push_back(static_cast<unsigned char>(encodedValue >> 8) & 0xFF);
                    data.push_back(static_cast<unsigned char>(encodedValue >> 16) & 0xFF);
                }
                else {
                    data.push_back(static_cast<unsigned char>(encodedValue >> 0) & 0xFF);
                    data.push_back(static_cast<unsigned char>(encodedValue >> 8) & 0xFF);
                    data.push_back(static_cast<unsigned char>(encodedValue >> 16) & 0xFF);
                    data.push_back(static_cast<unsigned char>(encodedValue >> 24) & 0xFF);
                }
            }
            else if (GidDataOrder::MSB_FIRST == dataOrder_) {
                if (1 == byteLength) {
                    data.push_back(static_cast<unsigned char>(encodedValue >> 0) & 0xFF);
                }
                else if (2 == byteLength) {
                    data.push_back(static_cast<unsigned char>(encodedValue >> 8) & 0xFF);
                    data.push_back(static_cast<unsigned char>(encodedValue >> 0) & 0xFF);
                }
                else if (3 == byteLength) {
                    data.push_back(static_cast<unsigned char>(encodedValue >> 16) & 0xFF);
                    data.push_back(static_cast<unsigned char>(encodedValue >> 8) & 0xFF);
                    data.push_back(static_cast<unsigned char>(encodedValue >> 0) & 0xFF);
                }
                else {
                    data.push_back(static_cast<unsigned char>(encodedValue >> 24) & 0xFF);
                    data.push_back(static_cast<unsigned char>(encodedValue >> 16) & 0xFF);
                    data.push_back(static_cast<unsigned char>(encodedValue >> 8) & 0xFF);
                    data.push_back(static_cast<unsigned char>(encodedValue >> 0) & 0xFF);
                }
            }
            else if (GidDataOrder::NONE == dataOrder_) {
                if (byteLength != 1) {
                    throw std::runtime_error("Data order of NONE not supported for byte length > 1.");
                }

                data.push_back(static_cast<unsigned char>(encodedValue >> 0) & 0xFF);
            }
            else {
                throw std::runtime_error("Unsupported data order.");
            }
        }

    private:
        uint16_t bitLength_;

        GidDataLengthType dataLengthType_;

        GidDataOrder dataOrder_;

        GidDataType dataType_;

        GidDsiDefinition dsiDefinition_;

        uint8_t encodingVersion_;

        uint32_t gid_;

        std::vector<unsigned char> subStructure_;
    };

    template<> inline
    void GidEncoding::encodeData<const std::string&>(std::vector<unsigned char>& data, const std::string& value) const {
        throw std::runtime_error("String encoding not yet supported.");
    }

    template<> inline
    void GidEncoding::encodeData<float>(std::vector<unsigned char>& data, float value) const {
        double scaledValue;
        bool signedEncoding;

        switch (dataType_) {

        case(GidDataType::SCALED_UNSIGNED_ZERO_OFFSET):
        case(GidDataType::SCALED_UNSIGNED_NONZERO_OFFSET):
        case(GidDataType::SCALED_UNSIGNED_OVERRIDE_ZERO_OFFSET):
        case(GidDataType::UNSIGNED_RADIX_ZERO_OFFSET):
        case(GidDataType::UNSIGNED_RADIX_NONZERO_OFFSET):
        {
            // The encoded value is unsigned
            float scaling = getScaleFactor();
            float offset = getOffset();
            scaledValue = std::round(((double)value / scaling) - offset);
            signedEncoding = false;
            break;
        }

        case(GidDataType::SCALED_SIGNED_ZERO_OFFSET):
        case(GidDataType::SCALED_SIGNED_OVERRIDE_ZERO_OFFSET):
        case(GidDataType::SIGNED_RADIX_ZERO_OFFSET):
        {
            float scaling = getScaleFactor();
            float offset = getOffset();
            scaledValue = std::round(((double)value / scaling) - offset);
            signedEncoding = true;
            break;
        }

        default:
            throw std::runtime_error("Unsupported data type for numeric data.");
            break;

        }

        uint32_t encodedValue;

        if (signedEncoding) {
            if ((scaledValue > INT32_MAX) || (scaledValue < INT32_MIN)) {
                throw std::runtime_error("Value is larger than the bit length can hold.");
            }

            auto temp = std::pow(2, bitLength_ - 1);
            int32_t maxValue = static_cast<int32_t>(temp - 1);
            int32_t minValue = static_cast<int32_t>(-temp);
            int32_t intValue = static_cast<int32_t>(scaledValue);

            if ((intValue > maxValue) || (intValue < minValue)) {
                throw std::runtime_error("Value is larger than the bit length can hold.");
            }

            encodedValue = *reinterpret_cast<uint32_t*>(&intValue);
        }
        else {
            if ((scaledValue > UINT32_MAX) || (scaledValue < 0UL)) {
                throw std::runtime_error("Value is larger than the bit length can hold.");
            }

            // Check size
            if ((bitLength_ < 32) && (scaledValue >= (1UL << bitLength_))) {
                throw std::runtime_error("Value is larger than the bit length can hold.");
            }

            encodedValue = static_cast<uint32_t>(scaledValue);
        }

        putEncodedNumericValue(data, encodedValue);
    }

    template<> inline
    void GidEncoding::encodeData<uint32_t>(std::vector<unsigned char>& data, uint32_t value) const {
        uint32_t encodedValue;

        switch (dataType_) {

        case(GidDataType::SCALED_UNSIGNED_ZERO_OFFSET):
        case(GidDataType::SCALED_UNSIGNED_OVERRIDE_ZERO_OFFSET):
        {
            uint8_t scalingIndex = subStructure_[0];
            if (0 != scalingIndex) {
                throw std::runtime_error("Non-zero scaling index not supported for uint32_t numeric data.");
            }
            encodedValue = value;
            break;
        }

        case(GidDataType::UNSIGNED_RADIX_ZERO_OFFSET):
        {
            uint8_t exponent = subStructure_[0];
            if (0 != exponent) {
                throw std::runtime_error("Non-zero exponent not supported for uint32_t numeric data.");
            }
            encodedValue = value;
            break;
        }

        case(GidDataType::GLOBAL_IDENTIFIER):
        {
            encodedValue = value;
            break;
        }

        default:
            throw std::runtime_error("Unsupported data type for uint32_t numeric data.");
            break;

        }

        // Check size
        if ((bitLength_ < 32) && (encodedValue >= (1UL << bitLength_))) {
            throw std::runtime_error("Value is larger than the bit length can hold.");
        }

        putEncodedNumericValue(data, encodedValue);
    }

    template<> inline
    std::string GidEncoding::decodeData<std::string>(const std::vector<unsigned char>& data) const {
        throw std::runtime_error("String decoding not yet supported.");
        return std::string("");
    }

    template<> inline
    float GidEncoding::decodeData<float>(const std::vector<unsigned char>& data) const {
        uint32_t encodedValue = getEncodedNumericValue(data);

        double finalValue = 0.0;

        switch (dataType_) {

        case(GidDataType::SCALED_UNSIGNED_ZERO_OFFSET):
        case(GidDataType::SCALED_UNSIGNED_NONZERO_OFFSET):
        case(GidDataType::SCALED_UNSIGNED_OVERRIDE_ZERO_OFFSET):
        case(GidDataType::UNSIGNED_RADIX_ZERO_OFFSET):
        case(GidDataType::UNSIGNED_RADIX_NONZERO_OFFSET):
        {
            // The encoded value is unsigned
            float scaling = getScaleFactor();
            float offset = getOffset();
            finalValue = ((double)encodedValue + offset) * scaling;
            break;
        }

        case(GidDataType::SCALED_SIGNED_ZERO_OFFSET):
        case(GidDataType::SCALED_SIGNED_OVERRIDE_ZERO_OFFSET):
        case(GidDataType::SIGNED_RADIX_ZERO_OFFSET):
        {
            // The encoded value is signed
            int32_t signedEncodedValue = *reinterpret_cast<int32_t*>(&encodedValue);
            float scaling = getScaleFactor();
            float offset = getOffset();
            finalValue = ((double)signedEncodedValue + offset) * scaling;
            break;
        }

        default:
            throw std::runtime_error("Unsupported data type for numeric data.");
            break;

        }

        return (float)finalValue;
    }

    template<> inline
    uint32_t GidEncoding::decodeData<uint32_t>(const std::vector<unsigned char>& data) const {
        uint32_t encodedValue = getEncodedNumericValue(data);

        uint32_t finalValue = 0;

        switch (dataType_) {

        case(GidDataType::SCALED_UNSIGNED_ZERO_OFFSET):
        case(GidDataType::SCALED_UNSIGNED_OVERRIDE_ZERO_OFFSET):
        {
            uint8_t scalingIndex = subStructure_[0];
            if (0 != scalingIndex) {
                throw std::runtime_error("Non-zero scaling index not supported for uint32_t numeric data.");
            }
            finalValue = encodedValue;
            break;
        }

        case(GidDataType::UNSIGNED_RADIX_ZERO_OFFSET):
        {
            uint8_t exponent = subStructure_[0];
            if (0 != exponent) {
                throw std::runtime_error("Non-zero exponent not supported for uint32_t numeric data.");
            }
            finalValue = encodedValue;
            break;
        }

        case(GidDataType::GLOBAL_IDENTIFIER):
        {
            finalValue = encodedValue;
            break;
        }

        default:
            throw std::runtime_error("Unsupported data type for uint32_t numeric data.");
            break;

        }

        return finalValue;
    }
}

#endif
