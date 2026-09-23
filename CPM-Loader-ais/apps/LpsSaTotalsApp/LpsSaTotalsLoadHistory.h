#ifndef LPSSATOTALSLOADHISTORY_H
#define LPSSATOTALSLOADHISTORY_H

#include <cstdint>
#include <stdexcept>
#include <iterator>
#include <utility>
#include <chrono>

#include <boost/assert.hpp>
#include <boost/array.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/split_member.hpp>

#include <chrono/print.hpp>

#include <boost_helpers/boost_serialization_chrono.hpp>

#include "LpsSaTotalsPrinterInfo.h"

/*
 * Load History Storage
 */
struct LpsSaTotalsLoadHistoryStorage {
public:
    using Clock = std::chrono::system_clock;
    using TimePoint = Clock::time_point;
    using LocalTimeOffset = std::chrono::minutes;

    struct Load {
    public:
        Load(TimePoint storeTime,
                uint32_t truckId, uint32_t materialId,
                const std::string& truckName, const std::string& materialName,
                uint32_t passCount, float weightTonnes,
                const std::string& tag1, const std::string& tag2,
                const std::string& tag3, const std::string& tag4) :
            storeTime(storeTime),
            truckId(truckId),
            materialId(materialId),
            truckName(truckName),
            materialName(materialName),
            passCount(passCount),
            weightTonnes(weightTonnes),
            tag1(tag1),
            tag2(tag2),
            tag3(tag3),
            tag4(tag4) {}

        Load() : Load(TimePoint(), 0, 0, "", "", 0, 0.f, "", "", "", "") {}

        TimePoint storeTime;
        uint32_t truckId;
        uint32_t materialId;
        std::string truckName;
        std::string materialName;
        uint32_t passCount;
        float weightTonnes;
        std::string tag1;
        std::string tag2;
        std::string tag3;
        std::string tag4;

    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & storeTime;
            ar & truckId;
            ar & materialId;

            if (version >= 1) {
                ar & truckName;
                ar & materialName;
            }

            ar & passCount;
            ar & weightTonnes;

            if (version >= 2) {
                ar & tag1;
                ar & tag2;
                ar & tag3;
                ar & tag4;
            }
        }
    };

    class LoadBuffer {
    public:
        typedef uint32_t Size;

        static constexpr Size capacity = 300;

        class Iterator : std::iterator<std::input_iterator_tag, const Load, int32_t> {
        public:
            Iterator() : pBuffer_(nullptr), ii_(0) {}

            Iterator(const LoadBuffer& buffer) :
                pBuffer_(&buffer),
                ii_(0) {
                if (0 == buffer.size()) {
                    pBuffer_ = nullptr;
                }
            }

            Iterator(const Iterator&) = default; // copy
            Iterator(Iterator&&) = default; // move

            Iterator& operator=(const Iterator&) = default; // assign
            Iterator& operator=(Iterator&&) = default; // move assignment

            bool operator==(const Iterator& other) const {
                if (pBuffer_ == nullptr) {
                    return (other.pBuffer_ == nullptr);
                }
                else {
                    return (ii_ == other.ii_) && (pBuffer_ == other.pBuffer_);
                }
            }

            bool operator!=(const Iterator& other) const { return !(*this == other); }

            reference operator*() const {
                BOOST_ASSERT(pBuffer_ != nullptr);
                return (*pBuffer_)[ii_];
            }

            pointer operator->() const { return &(operator*()); }

            Iterator& operator++() {
                BOOST_ASSERT(pBuffer_ != nullptr);
                if (++ii_ >= pBuffer_->size()) {
                    // Make it the 'end'
                    pBuffer_ = nullptr;
                }
                return *this;
            }

            Iterator operator++(int) {
                Iterator tmp(*this);
                ++(*this);
                return tmp;
            }

        private:
            const LoadBuffer* pBuffer_;
            Size ii_;
        };

        //friend class Iterator;

        LoadBuffer() : begin_(), size_(), buffer_() {}

        Iterator begin() const { return Iterator(*this); }
        Iterator end() const { return Iterator(); }

        Size size() const {
            return size_;
        }

        Load& operator[](Size ii) {
            BOOST_ASSERT_MSG(ii < size(), "out of range");
            return buffer_[bufferindex(ii)];
        }

        const Load& operator[](Size ii) const {
            BOOST_ASSERT_MSG(ii < size(), "out of range");
            return buffer_[bufferindex(ii)];
        }

        Load& at(Size ii) {
            rangecheck(ii);
            return buffer_[bufferindex(ii)];
        }

        const Load& at(Size ii) const {
            rangecheck(ii);
            return buffer_[bufferindex(ii)];
        }

        Load& front() {
            return at(0);
        }

        const Load& front() const {
            return at(0);
        }

        Load& back() {
            return at(size_ - 1);
        }

        const Load& back() const {
            return at(size_ - 1);
        }

        void push_back(const Load& load) {
            if (full()) {
                buffer_[begin_] = load;
                ++begin_;
                if (begin_ >= capacity) {
                    begin_ = 0;
                }
            }
            else {
                buffer_[bufferindex(size_)] = load;
                ++size_;
            }
        }

        void push_back(Load&& load) {
            if (full()) {
                buffer_[begin_] = std::move(load);
                ++begin_;
                if (begin_ >= capacity) {
                    begin_ = 0;
                }
            }
            else {
                buffer_[bufferindex(size_)] = std::move(load);
                ++size_;
            }
        }

        bool empty() const {
            return (size_ == 0);
        }

        bool full() const {
            return (size_ == capacity);
        }

        void clear() {
            begin_ = size_ = 0;
        }

        Size max_size() const {
            return capacity;
        }

    private:
        Size begin_;
        Size size_;
        boost::array<Load, capacity> buffer_;

        Size bufferindex(Size ii) const {
            Size b = begin_ + ii;
            if (b < capacity) {
                return b;
            }
            else {
                return b - capacity;
            }
        }

        // check range (may be private because it is static)
        void rangecheck (Size ii) const {
            if (ii >= size()) {
                throw std::out_of_range("LoadBuffer: index out of range");
            }
        }

        friend class boost::serialization::access;

        template<class Archive>
        void save(Archive & ar, const unsigned int version) const {
            ar << begin_;
            ar << size_;
            ar << boost::serialization::make_array(buffer_.data(), buffer_.size());
        }

        template<class Archive>
        void load(Archive & ar, const unsigned int version) {
            ar >> begin_;
            ar >> size_;

            /*
             * Make sure the begin index is within array bounds
             * Make sure the size of the stored array is <= size of array
             */
            if ((begin_ < capacity) &&
                    (size_ <= capacity)) {
                ar >> boost::serialization::make_array(buffer_.data(), buffer_.size());
            }
            else {
                clear();
            }
        }

        BOOST_SERIALIZATION_SPLIT_MEMBER()
    };

    LoadBuffer loads;
    TimePoint resetTime;

    LpsSaTotalsLoadHistoryStorage() :
        loads(), resetTime(TimePoint::min()) {}

    inline void reset() {
        loads.clear();
        resetTime = Clock::now();
    }

    inline void addLoad(const Load& load) {
        loads.push_back(load);
        // If load history is not yet reset then change reset time to to first load time
        if (resetTime <= TimePoint::min()) {
        	resetTime = loads[0].storeTime;
        }
    }

    void addLoad(Load&& load) {
        loads.push_back(std::move(load));
    }

    inline bool isFull() const {
        return loads.full();
    }

    bool load(const boost::filesystem::path& filePath);
    bool save(const boost::filesystem::path& filePath) const;

    bool print(const boost::filesystem::path& filePath, const LpsSaTotalsPrinterInfo& printerInfo, bool daily) const;

    void toAscii(std::ostream& os, const LpsSaTotalsPrinterInfo* pPrinterInfo = nullptr, bool daily = false) const;

    friend std::ostream& operator<<(std::ostream& os, const LpsSaTotalsLoadHistoryStorage& o);

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & loads;
        ar & resetTime;
    }
};

BOOST_CLASS_VERSION(LpsSaTotalsLoadHistoryStorage, 0);
BOOST_CLASS_VERSION(LpsSaTotalsLoadHistoryStorage::Load, 2);
BOOST_CLASS_VERSION(LpsSaTotalsLoadHistoryStorage::LoadBuffer, 0);

#endif // LPSSATOTALSLOADHISTORY_H
