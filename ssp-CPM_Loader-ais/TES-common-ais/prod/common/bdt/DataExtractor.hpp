#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#ifndef BDT_DATAEXTRACTOR_HPP
#define BDT_DATAEXTRACTOR_HPP

namespace tes_common_ais {

    class DataExtractor
    {
    public:
        DataExtractor(std::vector<unsigned char> const &buffer) :
            buffer_(buffer),
            currentIndex_(0) {}

        unsigned int getBufferSize() const {
            return buffer_.size();
        }

        std::vector<unsigned char> getDataSubset(unsigned int numBytesToExtract) {
            if (canExtractBytes(numBytesToExtract)) {
                std::vector<unsigned char> extractedData(&buffer_[currentIndex_],
                    &buffer_[currentIndex_] + numBytesToExtract);
                currentIndex_ += numBytesToExtract;
                return extractedData;
            }
            else {
                throw std::out_of_range("Cannot extract data subset.  Buffer too short.");
            }
        }

        template <typename T>
        inline T getLsbData() {
            unsigned int valueSize = sizeof(T);
            if (canExtractBytes(valueSize)) {
                T value = 0;
                for (unsigned int i = 0; i < valueSize; ++i) {
                    value |= buffer_[currentIndex_ + i] << (i * 8);
                }
                currentIndex_ += valueSize;
                return value;
            }
            else {
                throw std::out_of_range("Cannot extract value. Buffer too short.");
            }
        }

        template <typename T>
        inline T getMsbData() {
            unsigned int valueSize = sizeof(T);
            if (canExtractBytes(valueSize)) {
                T value = 0;
                for (unsigned int i = 0; i < valueSize; ++i) {
                    value |= buffer_[currentIndex_ + i] << ((valueSize - i - 1) * 8);
                }
                currentIndex_ += valueSize;
                return value;
            }
            else {
                throw std::out_of_range("Cannot extract value. Buffer too short.");
            }
        }

        std::string getString(unsigned int numBytesToExtract) {
            if (canExtractBytes(numBytesToExtract)) {
                std::vector<unsigned char>::const_iterator startItr = buffer_.begin() + currentIndex_;
                std::vector<unsigned char>::const_iterator endItr = buffer_.begin() + currentIndex_ + numBytesToExtract;
                std::string extractedString(startItr, endItr);
                currentIndex_ += numBytesToExtract;
                return extractedString;
            }
            else {
                throw std::out_of_range("Cannot extract string. Buffer too short.");
            }
        }

        void skipBytes(unsigned int numBytesToSkip) {
            if (canExtractBytes(numBytesToSkip)) {
                currentIndex_ += numBytesToSkip;
            }
            else {
                throw std::out_of_range("Cannot skip bytes. Buffer too short.");
            }
        }

    private:
        bool canExtractBytes(unsigned int bytesToExtract) const {
            return ((currentIndex_ + bytesToExtract) <= buffer_.size());
        }

        std::vector<unsigned char> const& buffer_;

        unsigned int currentIndex_;
    };

}

#endif
