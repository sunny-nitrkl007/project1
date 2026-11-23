#ifndef VP3RUNTIMERECORD_H
#define VP3RUNTIMERECORD_H

#include <array>
#include <limits>
#include <type_traits>
#include "VP3RecordValue.h"

namespace Record_Type { constexpr std::uint16_t STATUS = 5; }
namespace VP3RecordBuilder { using UidType = std::array<std::uint8_t, 13>; }

class VP3Record : public vp3::RecordValue
{
public:
    VP3Record() = default;
    explicit VP3Record(const vp3::RecordValue& value) : vp3::RecordValue(value) {}
    std::uint16_t getRecordType() const { return recordType; }
    const std::string& getUIDList() const { return uidList; }
    const std::string& getRBlockData() const { return rBlockData; }
    std::uint16_t getNumberOfUIDs() const { return numberOfUIDs; }
    std::uint16_t getSizeOfRecord() const { return sizeOfRecord; }
    void setRecordType(std::uint16_t type) { recordType = type; }

    template <class T>
    void add_data_to_record(const VP3RecordBuilder::UidType& uid, T value, bool msb = true)
    {
        static_assert(std::is_integral<T>::value, "Only integral header fields supported");
        reserveField(uid, sizeof(T));
        appendInteger(value, msb);
    }

    void add_timestamp(const VP3RecordBuilder::UidType& uid, std::uint32_t utc,
                       std::int16_t offset, std::uint32_t shm, bool msb = true)
    {
        reserveField(uid, 10);
        appendInteger(utc, msb);
        appendInteger(offset, msb);
        appendInteger(shm, msb);
    }

    void add_string_to_record(const VP3RecordBuilder::UidType& uid, const std::string& value)
    {
        reserveField(uid, value.size());
        rBlockData += value;
    }

private:
    void reserveField(const VP3RecordBuilder::UidType& uid, std::size_t size)
    {
        if (uid[1] != 0 || uid[2] != 10 ||
            size > std::numeric_limits<std::uint16_t>::max() - sizeOfRecord ||
            numberOfUIDs == std::numeric_limits<std::uint16_t>::max()) {
            throw std::invalid_argument("Invalid VP3 header field");
        }
        uidList.append(uid.begin(), uid.end());
        ++numberOfUIDs;
        sizeOfRecord += size;
    }

    template <class T>
    void appendInteger(T value, bool msb)
    {
        using Unsigned = typename std::make_unsigned<T>::type;
        const auto bits = static_cast<Unsigned>(value);
        for (std::size_t i = 0; i < sizeof(T); ++i) {
            const auto shift = (msb ? sizeof(T) - i - 1 : i) * 8;
            rBlockData.push_back(static_cast<char>((bits >> shift) & 0xff));
        }
    }
};

namespace VP3RecordBuilder {
inline VP3Record makeDefaultStatusRecord()
{
    VP3Record record;
    record.setRecordType(Record_Type::STATUS);
    record.add_timestamp({{0xAA,0,10,0x81,1,0,7,0x1B,10,0x13,0x0D,0,0x37}}, 0, 0, 0);
    record.add_string_to_record({{0xAA,0,10,0x81,1,0,0x28,0,32,3,0x19,0,0x37}}, std::string(32, '\0'));
    record.add_string_to_record({{0xAA,0,10,0x81,0x0D,0,0x0C,0,12,3,0x19,0,0x37}}, std::string(1, 11) + std::string(11, ' '));
    record.add_string_to_record({{0xAA,0,10,0x81,1,0,0x27,0,32,3,0x19,0,0x37}}, std::string(32, '\0'));
    record.add_data_to_record<std::uint16_t>({{0xAA,0,10,0x81,1,0,0x32,0,2,8,5,0,0x37}}, 0);
    return record;
}
}

#endif
