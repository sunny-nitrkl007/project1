#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <memory>
#include <type_traits>

#include "GidEncoding.hpp"

#ifndef BDT_GIDDATA_HPP
#define BDT_GIDDATA_HPP

namespace tes_common_ais {

    class GidData
    {
    public:
        GidData(const std::shared_ptr<const GidEncoding>& pEncoding, const std::vector<unsigned char>& data) :
            data_(data), pEncoding_(pEncoding), gid_(pEncoding->getGid()) {}

        template <typename D>
        GidData(const std::shared_ptr<const GidEncoding>& pEncoding, D data) :
            pEncoding_(pEncoding), gid_(pEncoding->getGid()) {
            pEncoding_->encodeData<D>(data_, data);
        }

        const std::vector<unsigned char>& getRawData() const {
            return data_;
        }

        unsigned int getGid() const {
            return gid_;
        }

        const std::shared_ptr<const GidEncoding>& getGidEncoding() const {
            return pEncoding_;
        }

        template<typename R>
        R getData() const;

    private:
        std::vector<unsigned char> data_;

        std::shared_ptr<const GidEncoding> pEncoding_;

        unsigned int gid_;
    };

    template<> inline
    float GidData::getData<float>() const {
        return pEncoding_->decodeData<float>(data_);
    }

    template<> inline
    uint32_t GidData::getData<uint32_t>() const {
        return pEncoding_->decodeData<uint32_t>(data_);
    }

    template<> inline
    std::string GidData::getData<std::string>() const {
        return pEncoding_->decodeData<std::string>(data_);
    }

}

#endif
