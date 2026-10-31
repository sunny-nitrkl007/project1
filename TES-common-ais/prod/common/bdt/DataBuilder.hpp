#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <type_traits>

#ifndef BDT_DATABUILDER_HPP
#define BDT_DATABUILDER_HPP

namespace tes_common_ais {

    class DataBuilder
    {
    public:
        DataBuilder(std::vector<unsigned char>& buffer) :
            buffer_(buffer) {}

        template <class T>
        inline void putLsbData(typename std::enable_if<std::is_integral<T>::value, T>::type data) {
            size_t valueSize = sizeof(T);
            for (size_t ii = 0; ii < valueSize; ii++) {
                buffer_.push_back(static_cast<unsigned char>((data >> (ii * 8)) & 0xFF));
            }
        }

        template <class T>
        inline void putMsbData(typename std::enable_if<std::is_integral<T>::value, T>::type data) {
            size_t valueSize = sizeof(T);
            for (size_t ii = 0; ii < valueSize; ii++) {
                buffer_.push_back(static_cast<unsigned char>((data >> ((valueSize - ii - 1) * 8)) & 0xFF));
            }
        }

        template <class T>
        inline void putLsbDataAt(typename std::enable_if<std::is_integral<T>::value, T>::type data, size_t index) {
            size_t valueSize = sizeof(T);
            for (size_t ii = 0; ii < valueSize; ii++) {
                buffer_[index + ii] = static_cast<unsigned char>((data >> (ii * 8)) & 0xFF);
            }
        }

        template <class T>
        inline void putMsbDataAt(typename std::enable_if<std::is_integral<T>::value, T>::type data, size_t index) {
            size_t valueSize = sizeof(T);
            for (size_t ii = 0; ii < valueSize; ii++) {
                buffer_[index + ii] = static_cast<unsigned char>((data >> ((valueSize - ii - 1) * 8)) & 0xFF);
            }
        }

        inline void putDataSubset(const std::vector<unsigned char>& data) {
            for (auto ch : data) {
                buffer_.push_back(ch);
            }
        }

        inline void putDataSubsetAt(const std::vector<unsigned char>& data, size_t index) {
            size_t valueSize = data.size();
            for (size_t ii = 0; ii < valueSize; ii++) {
                buffer_[index + ii] = data[ii];
            }
        }

        void putData(const std::string& data) {
            for (auto ch : data) {
                buffer_.push_back(ch);
            }
        }

        void putData(const std::vector<unsigned char>& data) {
            for (auto ch : data) {
                buffer_.push_back(ch);
            }
        }

        size_t getCurrentEnd() const {
            return buffer_.size();
        }

    private:
        std::vector<unsigned char>& buffer_;
    };

}

#endif
