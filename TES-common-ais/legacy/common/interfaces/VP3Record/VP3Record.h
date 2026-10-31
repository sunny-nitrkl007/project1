#ifndef VP3RECORD_H_
#define VP3RECORD_H_

#include <array>
#include <algorithm>
#include <cstring>

#include <ais/serialization/csvable.h>
#include <ais/log/AisLogger.h>
#include <ais/serialization/Datum.h> // For Boost serialization

#include "UID_Descriptions.h"

class VP3RecordStorage: public csvable
{  
public:  
    VP3RecordStorage() /* Initialize Fields Here */:
    recordType_ (0),
    numberOfUIDs_(0),
    sizeOfRecord_(0)
    {}

    VP3RecordStorage(
       unsigned short recordType,
       const std::string& UIDList,
       const std::string& rBlockData):
    recordType_ (recordType),
    UIDList_ (UIDList),
    rBlockData_(rBlockData)
    {
        size_t entriesCount = 0;
        size_t headerSize = UIDList.size();
        size_t offset = 0;

        // Check the number of entries in the provided header
        while (offset < headerSize)
        {
            ++offset;  // Record id
            size_t length = UIDList.at(offset++) << 8;
            length += UIDList.at(offset++);

            // Todo: Maybe the UID's may be parsed to check if sizeOfRecord_ is ok
            // as an extra sanity check. May be done only if all records have the same
            // structure.

            offset += length;
            entriesCount++;
        }

        // Sanity Check
        if (offset == headerSize)
        {
            numberOfUIDs_ = entriesCount;
            sizeOfRecord_ = rBlockData.size();
        }
        else
        {
            AIS_LOG_ERROR("VP3RecordStorage: Bad header received!");
            numberOfUIDs_ = 0;
            sizeOfRecord_ = 0;
        }
    }

    void toCsv(CsvOutStream& out) const
    {
        out("RecordType", recordType_);
        out("UIDList", UIDList_);
        out("rBlockData", rBlockData_);
        out("numberOfUIDs", numberOfUIDs_);
        out("sizeOfRecord", sizeOfRecord_);
    }

    template <class Archive>
    void serialize(Archive &ar, unsigned int version)
    {
        /* Archive Fields Here */
        ar & recordType_;
        ar & UIDList_;
        ar & rBlockData_;
        ar & numberOfUIDs_;
        ar & sizeOfRecord_;
    }

    unsigned short getRecordType() const
    {
        return recordType_;
    }

    void setRecordType(unsigned short type)
    {
        recordType_ = type;
    }

    const std::string& getUIDList() const
    {
        return UIDList_;
    }

    unsigned short getSizeOfRecord() const
    {
        return sizeOfRecord_;
    }

    unsigned short getNumberOfUIDs() const
    {
        return numberOfUIDs_;
    }

    const std::string& getRBlockData() const
    {
        return rBlockData_;
    }

    void clearUIDList()
    {
        this->UIDList_.clear();
    }

    void clearSizeOfRecord()
    {
        this->sizeOfRecord_ = 0;
    }

    void clearNumOfUIDs()
    {
        this->numberOfUIDs_ = 0;
    }

    void clearRBlockData()
    {
        this->rBlockData_.clear();
    }
    /*******************************************************************************************************************
    Function : add_data_to_record
    Input : UID string, value of any data_type, is_lsb(flag)
    Is a <template> function which accepts and adds UID string, value to be put in record, is_lsb flag.
    Set is_lsb = false if the value of Record Data is in MSB.
    Calls data_to_string().
    NOTE: Should only be used to convert primitive types. Does not work on user defined types.
    ********************************************************************************************************************/
    template <typename T>
    void add_data_to_record(const std::string& uid, T value, bool isMsb = true) {
        add_data_to_record<T, std::string>(uid, value, isMsb);
    }

    template <typename T, typename I>
    void add_data_to_record(const I& uid, T value, bool isMsb = true) {
        if (isUIDSizeValid(uid)) {
            data_to_string(value, isMsb);
            UIDList_.append(uid.cbegin(), uid.cend());
            ++numberOfUIDs_;
        }
        else {
            AIS_LOG_FATAL("Invalid UID Size add_data: %d", uid.size());
        }
    }

    /*******************************************************************************************************************
     Function        : add_data_to_record
     Description     : Add UID string to a record.
                       NOTE: Should only be used to convert primitive types. Does not work on user defined types.
     Return Type     : void
     Argument [in]   : std::string UID - User ID String
                       template <typename T, size_t N> - template specifying data type T and record size N
                       bool isMsb - True if the value of Record Data is in MSB, else LSB
     Argument [out]  : None
     Argument [I/O]  : None
    ********************************************************************************************************************/

    template <typename T, size_t N>
    void add_data_to_record(const std::string& uid, T (&value)[N], bool isMsb = true) {
        if(isUIDSizeValid(uid)) {
            const unsigned int len = sizeof(value);
            char chunks[len];
            memcpy(chunks, (char*)&value, len);
            std::string temp = std::string(chunks,len);
            if((isMsb != false) && (len > 1)) {
                std::reverse(temp.begin(), temp.end());
            }
            rBlockData_ += temp;
            sizeOfRecord_ += len;
            UIDList_ += uid;
            ++numberOfUIDs_;
        }
        else {
            AIS_LOG_ERROR("Invalid UID Size add_data:%d", uid.size());
        }
    }

    /*******************************************************************************************************************
    Function : add_timestamp
    Input : UID string, utc_time, offset, smh, is_lsb(flag)
    Is a function which accepts and adds UID string, utc_time, offset, smh, is_lsb flag.
    utc_time, offset and smh are part of timestamp user defined packed structure.
    Set is_lsb = false if the value of Record Data is in MSB.
    Calls data_to_string().
    NOTE: Should only be used to convert timestamp type.
    ********************************************************************************************************************/
    void add_timestamp(const std::string& uid, unsigned int utcTime, short int offset, unsigned int smh, bool isMsb = true) {
        add_timestamp<std::string>(uid, utcTime, offset, smh, isMsb);
    }

    template <typename I>
    void add_timestamp(const I& uid, unsigned int utcTime, short int offset, unsigned int smh, bool isMsb = true) {
        if (isUIDSizeValid(uid)) {
            data_to_string(utcTime, isMsb);
            data_to_string(offset, isMsb);
            data_to_string(smh, isMsb);
            UIDList_.append(uid.cbegin(), uid.cend());
            ++numberOfUIDs_;
        }
        else {
            AIS_LOG_FATAL("Invalid UID Size add_timestamp: %d", uid.size());
        }
    }

    /*******************************************************************************************************************
    Function : add_string_to_record
    Input : UID string, value
    Is a function which accepts and adds UID string, value in string format.
    NOTE: Should only be used on value of string type.
    ********************************************************************************************************************/
    void add_string_to_record(const std::string& uid, const std::string& value) {
        add_string_to_record<std::string>(uid, value);
    }

    template <typename I>
    void add_string_to_record(const I& uid, const std::string& value) {
        if (isUIDSizeValid(uid)) {
            UIDList_.append(uid.cbegin(), uid.cend());
            ++numberOfUIDs_;
            rBlockData_ += value;
            sizeOfRecord_ += value.size();
        }
        else {
            AIS_LOG_FATAL("Invalid UID Size add_string: %d", uid.size());
        }
    }

private:
    /* Add Fields Here */
    unsigned short recordType_;
    std::string UIDList_;
    unsigned short numberOfUIDs_;
    std::string rBlockData_;
    unsigned short sizeOfRecord_;

    inline bool isUIDSizeValid(const std::string& uid) {
        return isUIDSizeValid<std::string>(uid);
    }

    template <typename I>
    inline bool isUIDSizeValid(const I& uid) {
        if (uid.size() < 3) {
            return false;
        }

        // Get size from UID
        unsigned int size = 0;
        size = ((unsigned int)uid[1] << 8) | (unsigned int)uid[2];

        // basic length check for all variations
        if (uid.size() != (size + 3)) {
            return false;
        }

        // specific for 0xAA format
        if (((uid[0] == 0xAA) || (uid[0] == 0xDD)) && (size != 10)) {
            return false;
        }

        return true;
    }


    /*******************************************************************************************************************
    Function : data_to_string
    Input : value of any data_type, is_lsb(flag)
    Is a <template> function which converts primitive types like int, char, float, double to string and adds it to record.
    NOTE: Should only be used to convert primitive types. Does not work on user defined types.
    ********************************************************************************************************************/
    template <typename T, typename std::enable_if<std::is_integral<T>::value, T>::type* = nullptr>
    inline void data_to_string(T data, bool isMsb) {
        auto valueSize = sizeof(T);
        if (isMsb) {
            for (size_t ii = 0; ii < valueSize; ++ii) {
                rBlockData_.push_back(static_cast<uint8_t>((data >> ((valueSize - ii - 1) * 8)) & 0xFF));
                ++sizeOfRecord_; // Why is this not just rBlockData_.length()
            }
        }
        else {
            for (size_t ii = 0; ii < valueSize; ++ii) {
                rBlockData_.push_back(static_cast<uint8_t>((data >> (ii * 8)) & 0xFF));
                ++sizeOfRecord_; // Why is this not just rBlockData_.length()
            }
        }
    }

    inline void data_to_string(uint8_t data) {
        rBlockData_.push_back(data);
        ++sizeOfRecord_;
    }

    inline void data_to_string(int8_t data) {
        rBlockData_.push_back(data);
        ++sizeOfRecord_;
    }

    inline void data_to_string(uint16_t data, bool isMsb) {
        if (isMsb) {
            rBlockData_.push_back(static_cast<uint8_t>((data >> 8) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 0) & 0xFF));
        }
        else {
            rBlockData_.push_back(static_cast<uint8_t>((data >> 0) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 8) & 0xFF));
        }
        sizeOfRecord_ += 2;
    }

    inline void data_to_string(int16_t data, bool isMsb) {
        if (isMsb) {
            rBlockData_.push_back(static_cast<uint8_t>((data >> 8) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 0) & 0xFF));
        }
        else {
            rBlockData_.push_back(static_cast<uint8_t>((data >> 0) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 8) & 0xFF));
        }
        sizeOfRecord_ += 2;
    }

    inline void data_to_string(uint32_t data, bool isMsb) {
        if (isMsb) {
            rBlockData_.push_back(static_cast<uint8_t>((data >> 24) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 16) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 8) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 0) & 0xFF));
        }
        else {
            rBlockData_.push_back(static_cast<uint8_t>((data >> 0) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 8) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 16) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 24) & 0xFF));
        }
        sizeOfRecord_ += 4;
    }

    inline void data_to_string(int32_t data, bool isMsb) {
        if (isMsb) {
            rBlockData_.push_back(static_cast<uint8_t>((data >> 24) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 16) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 8) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 0) & 0xFF));
        }
        else {
            rBlockData_.push_back(static_cast<uint8_t>((data >> 0) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 8) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 16) & 0xFF));
            rBlockData_.push_back(static_cast<uint8_t>((data >> 24) & 0xFF));
        }
        sizeOfRecord_ += 4;
    }

    inline void data_to_string(float data, bool isMsb) {
        const uint32_t* p = reinterpret_cast<uint32_t*>(&data);
        data_to_string(*p, isMsb);
    }

    inline void data_to_string(double data, bool isMsb) {
        const uint64_t* p = reinterpret_cast<uint64_t*>(&data);
        data_to_string(*p, isMsb);
    }
};  

typedef Datum<VP3RecordStorage> VP3Record;

BOOST_CLASS_VERSION(VP3RecordStorage, 1);

/*
 * Helpers for building VP3 records
 */
namespace VP3RecordBuilder {
    static constexpr std::size_t UidSize = 13;
    typedef std::array<uint8_t, UidSize> UidType;

    static constexpr UidType UID_LOAD_START_TIME() { return {{0xAA, 0x00, 0x0A, 0x81, 0x01, 0x00, 0x07, 0x13, 0x0A, 0x13, 0x0C, 0x00, 0x37}}; }
    static constexpr UidType UID_LOAD_END_TIME() { return {{ 0xAA, 0x00, 0x0A, 0x81, 0x01, 0x00, 0x07, 0x14, 0x0A, 0x13, 0x0C, 0x00, 0x37 }}; }

    inline VP3Record makeLoadRecord(uint32_t startTimeUtc, int16_t startLocalTimeOffset, uint32_t startShm,
            uint32_t endTimeUtc, int16_t endLocalTimeOffset, uint32_t endShm) {
        VP3Record vp3Record;
        vp3Record.setRecordType(Record_Type::LOAD);

        /* Start Time */
        vp3Record.add_timestamp(UID_LOAD_START_TIME(),
                startTimeUtc, startLocalTimeOffset, startShm, true /* MSB-First */);

        /* End Time */
        vp3Record.add_timestamp(UID_LOAD_END_TIME(),
                endTimeUtc, endLocalTimeOffset, endShm, true /* MSB-First */);

        return vp3Record;
    }

    static constexpr UidType UID_PAYLOAD_TIME_OFFSET() { return {{ 0xAA, 0x00, 0x0A, 0x81, 0x01, 0x00, 0x75, 0x15, 0x04, 0x15, 0x00, 0x00, 0x37 }}; }
    static constexpr UidType UID_PAYLOAD_CALC_METHOD() { return {{ 0xAA, 0x00, 0x0A, 0x00, 0x01, 0x1A, 0x78, 0x00, 0x02, 0x08, 0x00, 0x00, 0x37 }}; }
    static constexpr UidType UID_PAYLOAD_WEIGHT() { return {{ 0xAA, 0x00, 0x0A, 0x81, 0x01, 0x00, 0x4E, 0x00, 0x04, 0x15, 0x00, 0x00, 0x37 }}; }
    static constexpr UidType UID_PAYLOAD_LOAD_START_TIME() { return {{ 0xAA, 0x00, 0x0A, 0x81, 0x01, 0x00, 0x07, 0x15, 0x0A, 0x13, 0x0D, 0x00, 0x37 }}; }

    inline VP3Record makePayloadRecord(float timeOffset,
            uint16_t calcMethod,
            float weight,
            uint32_t loadStartTimeUtc, int16_t loadStartLocalTimeOffset, uint32_t loadStartShm) {
        VP3Record vp3Record;
        vp3Record.setRecordType(Record_Type::PAYLOAD);

        /* Start Time Offset (seconds) - float */
        vp3Record.add_data_to_record<float>(UID_PAYLOAD_TIME_OFFSET(),
                timeOffset, true /* MSB-First */);

        /* Payload Calculation Method - uint16_le */
        vp3Record.add_data_to_record<uint16_t>(UID_PAYLOAD_CALC_METHOD(),
                calcMethod, true /* MSB-First */);

        /* Payload Weight - float */
        vp3Record.add_data_to_record<float>(UID_PAYLOAD_WEIGHT(),
                weight, true /* MSB-First */);

        /* Load Record Start Time */
        vp3Record.add_timestamp(UID_PAYLOAD_LOAD_START_TIME(),
                loadStartTimeUtc, loadStartLocalTimeOffset, loadStartShm, true /* MSB-First */);

        return vp3Record;
    }

    static constexpr UidType UID_TRUCK_NAME() {return {{0xAA, 0x00, 0x0A, 0x81, 0x01, 0x01, 0xA1, 0x00, 0xFF, 0x03, 0x29, 0x00, 0x37}};}
    static constexpr UidType UID_MATERIAL_NAME() {return {{0xAA, 0x00, 0x0A, 0x81, 0x01, 0x01, 0xA0, 0x00, 0xFF, 0x03, 0x29, 0x00, 0x37}};}
    static constexpr UidType UID_STATUS_TAG1_NAME() {return {{0xAA, 0x00, 0x0A, 0x81, 0x01, 0x01, 0x9C, 0x00, 0xFF, 0x03, 0x29, 0x00, 0x37}};}
    static constexpr UidType UID_STATUS_TAG2_NAME() {return {{0xAA, 0x00, 0x0A, 0x81, 0x01, 0x01, 0x9D, 0x00, 0xFF, 0x03, 0x29, 0x00, 0x37}};}
    static constexpr UidType UID_STATUS_TAG3_NAME() {return {{0xAA, 0x00, 0x0A, 0x81, 0x01, 0x01, 0x9E, 0x00, 0xFF, 0x03, 0x29, 0x00, 0x37}};}
    static constexpr UidType UID_STATUS_TAG4_NAME() {return {{0xAA, 0x00, 0x0A, 0x81, 0x01, 0x01, 0x9F, 0x00, 0xFF, 0x03, 0x29, 0x00, 0x37}};}
    static constexpr UidType UID_MATERIAL_DENSITY() {return {{0xAA, 0x00, 0x0A, 0x81, 0x01, 0x00, 0x32, 0x00, 0x02, 0x08, 0x05, 0x00, 0x37}};}
    static constexpr UidType UID_MATERIAL_ID() {return {{0xAA, 0x00, 0x0A, 0x00, 0x01, 0x04, 0x62, 0x00, 0x04, 0x0D, 0x00, 0x00, 0x37}};}
    static constexpr UidType UID_TRUCK_ID() {return {{0xAA, 0x00, 0x0A, 0x00, 0x01, 0x04, 0x60, 0x00, 0x04, 0x0D, 0x00, 0x00, 0x37}};}
    static constexpr UidType UID_TRUCK_TICKET_NUMBER() {return {{0xAA, 0x00, 0x0A, 0x00, 0x03, 0x10, 0xBD, 0x00, 0x02, 0x08, 0x00, 0x00, 0x37}};}

    inline VP3Record makeLoadRecord(uint32_t startTimeUtc, int16_t startLocalTimeOffset, uint32_t startShm, uint32_t endTimeUtc,
            int16_t endLocalTimeOffset,uint32_t endShm, const std::string& truckName, uint32_t truckId, const std::string& materialName,
            uint32_t materialId, float materialDensity, const std::string& tag1, const std::string& tag2, const std::string& tag3,
            const std::string& tag4, uint32_t ticketNumber) {

        VP3Record vp3Record = makeLoadRecord(startTimeUtc, startLocalTimeOffset, startShm,
                endTimeUtc, endLocalTimeOffset, endShm);

        { /* Truck Description (Variable Length). Max size we allow = 250 characters */
            UidType uid = UID_TRUCK_NAME();
            std::string name(truckName, 0, 250);
            uid[8] = static_cast<uint8_t>(name.size());
            vp3Record.add_string_to_record(uid, name);
        }

        { /*  Material Description (Variable Length). Max size we allow = 100 characters  */
            UidType uid = UID_MATERIAL_NAME();
            std::string name(materialName, 0, 100);
            uid[8] = static_cast<uint8_t>(name.size());
            vp3Record.add_string_to_record(uid, name);
        }

        { /* Custom Tag 1. Max size we allow = 100 characters */
            UidType uid = UID_STATUS_TAG1_NAME();
            std::string tag(tag1, 0, 100);
            uid[8] = static_cast<uint8_t>(tag.size());
            vp3Record.add_string_to_record(uid, tag);
        }

        { /* Custom Tag 2. Max size we allow = 100 characters */
            UidType uid = UID_STATUS_TAG2_NAME();
            std::string tag(tag2, 0, 100);
            uid[8] = static_cast<uint8_t>(tag.size());
            vp3Record.add_string_to_record(uid, tag);
        }

        { /* Custom Tag 3. Max size we allow = 100 characters */
            UidType uid = UID_STATUS_TAG3_NAME();
            std::string tag(tag3, 0, 100);
            uid[8] = static_cast<uint8_t>(tag.size());
            vp3Record.add_string_to_record(uid, tag);
        }

        { /* Custom Tag 4. Max size we allow = 100 characters */
            UidType uid = UID_STATUS_TAG4_NAME();
            std::string tag(tag4, 0, 100);
            uid[8] = static_cast<uint8_t>(tag.size());
            vp3Record.add_string_to_record(uid, tag);
        }

        /* Loader Payload Material Density */
        vp3Record.add_data_to_record<>(UID_MATERIAL_DENSITY(), static_cast<uint16_t>(materialDensity), true /* MSB */);

        /* Material ID */
        vp3Record.add_data_to_record<>(UID_MATERIAL_ID(), materialId, false /* LSB */);

        /* Truck Payload ID*/
        vp3Record.add_data_to_record<>(UID_TRUCK_ID(), truckId, false /* LSB */);

        /* Onboard Payload Printer Truck Ticket Number */
        vp3Record.add_data_to_record<>(UID_TRUCK_TICKET_NUMBER(), static_cast<uint16_t>(ticketNumber), true);

        return vp3Record;
    }

    static constexpr uint8_t STATUS_TRUCK_NAME_SIZE() { return 32; }
    static constexpr uint8_t STATUS_MATERIAL_NAME_SIZE() { return 32; }
    static constexpr uint8_t OPERATOR_USER_DESCRIPTION_SIZE() { return 12; }

    static constexpr UidType UID_STATUS_TIME() { return {{ 0xAA, 0x00, 0x0A, 0x81, 0x01, 0x00, 0x07, 0x1B, 0x0A, 0x13, 0x0D, 0x00, 0x37 }}; }
    static constexpr UidType UID_STATUS_TRUCK_NAME() { return {{ 0xAA, 0x00, 0x0A, 0x81, 0x01, 0x00, 0x28, 0x00, STATUS_TRUCK_NAME_SIZE(), 0x03, 0x19, 0x00, 0x37 }}; }
    static constexpr UidType UID_STATUS_MATERIAL_NAME() { return {{ 0xAA, 0x00, 0x0A, 0x81, 0x01, 0x00, 0x27, 0x00, STATUS_MATERIAL_NAME_SIZE(), 0x03, 0x19, 0x00, 0x37 }}; }
    static constexpr UidType UID_STATUS_MATERIAL_DENSITY() { return {{ 0xAA, 0x00, 0x0A, 0x81, 0x01, 0x00, 0x32, 0x00, 0x02, 0x08, 0x05, 0x00, 0x37 }}; }
    static constexpr UidType UID_STATUS_OPERATOR_USER_DESCRIPTION() { return {{ 0xAA, 0x00, 0x0A, 0x81, 0x0D, 0x00, 0x0C, 0x00, OPERATOR_USER_DESCRIPTION_SIZE(), 0x03, 0x19, 0x00, 0x37 }}; }

    inline VP3Record makeStatusRecord(uint32_t timeUtc, int16_t localTimeOffset, uint32_t shm,
            const std::string& truckName,
            const std::string& materialName,
            float materialDensity,
            const std::string& operatorDescription) {
        VP3Record vp3Record;
        vp3Record.setRecordType(Record_Type::STATUS);

        /* Time */
        vp3Record.add_timestamp(UID_STATUS_TIME(),
                timeUtc, localTimeOffset, shm, true /* MSB-First */);

        /* Truck Name - Unicode string of 16 bytes, BE */
        {
            std::array<uint8_t, STATUS_TRUCK_NAME_SIZE()> encoded;
            auto len = truckName.length();
            for (unsigned inIdx = 0; inIdx < STATUS_TRUCK_NAME_SIZE()/2; ++inIdx) {

                // First byte of the utf16 encoded character
                unsigned outIdx = inIdx*2;
                encoded[outIdx] = 0x00;

                // Second byte of the utf16 encoded character
                ++outIdx;
                if (inIdx < len) {
                    encoded[outIdx] = static_cast<uint8_t>(truckName[inIdx]);
                }
                else {
                    encoded[outIdx] = 0x00;
                }
            }

            vp3Record.add_string_to_record(UID_STATUS_TRUCK_NAME(),
                    std::string(encoded.cbegin(), encoded.cend()));
        }

        /* Operator Name - First byte is length of description and rest is an ASCII string of 11 bytes*/
        {
           std::array<uint8_t, OPERATOR_USER_DESCRIPTION_SIZE()> encoded;
           auto len = operatorDescription.length();
           constexpr auto DescriptionLength = OPERATOR_USER_DESCRIPTION_SIZE() - 1;
           encoded[0] = DescriptionLength;
           unsigned outIdx = 1;
           for (unsigned inIdx = 0; inIdx < DescriptionLength; ++inIdx) {
               if (inIdx < len) {
                   encoded[outIdx] = static_cast<uint8_t>(operatorDescription[inIdx]);
               }
               else {
                   encoded[outIdx] = 0x20;
               }
               outIdx++;
           }
           vp3Record.add_string_to_record(UID_STATUS_OPERATOR_USER_DESCRIPTION(),
                   std::string(encoded.cbegin(), encoded.cend()));
       }

        /* Material Name - Unicode string of 32 bytes, BE */
        {
            std::array<uint8_t, STATUS_MATERIAL_NAME_SIZE()> encoded;
            auto len = materialName.length();
            for (unsigned inIdx = 0; inIdx < STATUS_MATERIAL_NAME_SIZE()/2; ++inIdx) {

                // First byte of the utf16 encoded character
                unsigned outIdx = inIdx*2;
                encoded[outIdx] = 0x00;

                // Second byte of the utf16 encoded character
                ++outIdx;
                if (inIdx < len) {
                    encoded[outIdx] = static_cast<uint8_t>(materialName[inIdx]);
                }
                else {
                    encoded[outIdx] = 0x00;
                }
            }

            vp3Record.add_string_to_record(UID_STATUS_MATERIAL_NAME(),
                    std::string(encoded.cbegin(), encoded.cend()));
        }

        /* Material Density - uint16_be */
        vp3Record.add_data_to_record<uint16_t>(UID_STATUS_MATERIAL_DENSITY(),
                static_cast<uint16_t>(materialDensity), true /* MSB-First */);

        return vp3Record;
    }
}


#endif

