#ifndef VP3RECORDVALUE_H
#define VP3RECORDVALUE_H

#include <cstdint>
#include <string>
#include <utility>

#include "VP3ArchiveCompatibility.h"

namespace vp3 {

struct RecordValue
{
    std::uint16_t recordType = 0;
    std::string uidList;
    std::string rBlockData;
    std::uint16_t numberOfUIDs = 0;
    std::uint16_t sizeOfRecord = 0;
    bool datumAttributesValid = false;
    archive::DatumAttributes attributes;

    template <class Message>
    static RecordValue fromMessage(const Message& message)
    {
        RecordValue value;
        value.recordType = message.record_type;
        value.uidList.assign(message.uid_list.begin(), message.uid_list.end());
        value.rBlockData.assign(message.r_block_data.begin(), message.r_block_data.end());
        value.numberOfUIDs = message.number_of_uids;
        value.sizeOfRecord = message.size_of_record;
        value.datumAttributesValid = message.datum_attributes_valid;
        value.attributes.originationTime.seconds = message.origination_time_secs;
        value.attributes.originationTime.microseconds = message.origination_time_usecs;
        value.attributes.transmissionTime.seconds = message.transmission_time_secs;
        value.attributes.transmissionTime.microseconds = message.transmission_time_usecs;
        value.attributes.txSequenceNumber = message.transmission_sequence_number;
        value.attributes.loggerSequenceNumber = message.logger_sequence_number;
        value.attributes.loggedTime.seconds = message.logged_time_secs;
        value.attributes.loggedTime.microseconds = message.logged_time_usecs;
        return value;
    }

    template <class Message>
    Message toMessage() const
    {
        Message message;
        message.record_type = recordType;
        message.uid_list.assign(uidList.begin(), uidList.end());
        message.r_block_data.assign(rBlockData.begin(), rBlockData.end());
        message.number_of_uids = numberOfUIDs;
        message.size_of_record = sizeOfRecord;
        message.datum_attributes_valid = datumAttributesValid;
        message.origination_time_secs = attributes.originationTime.seconds;
        message.origination_time_usecs = attributes.originationTime.microseconds;
        message.transmission_time_secs = attributes.transmissionTime.seconds;
        message.transmission_time_usecs = attributes.transmissionTime.microseconds;
        message.transmission_sequence_number = attributes.txSequenceNumber;
        message.logger_sequence_number = attributes.loggerSequenceNumber;
        message.logged_time_secs = attributes.loggedTime.seconds;
        message.logged_time_usecs = attributes.loggedTime.microseconds;
        return message;
    }

    static RecordValue fromArchive(const archive::Record& stored)
    {
        RecordValue value;
        value.recordType = stored.recordType;
        value.uidList = stored.uidList;
        value.rBlockData = stored.rBlockData;
        value.numberOfUIDs = stored.numberOfUIDs;
        value.sizeOfRecord = stored.sizeOfRecord;
        value.datumAttributesValid = true;
        value.attributes = stored.attributes;
        return value;
    }

    // Payload-only producers must not erase attributes restored from legacy NVM.
    void updateArchive(archive::Record& stored) const
    {
        stored.recordType = recordType;
        stored.uidList = uidList;
        stored.rBlockData = rBlockData;
        stored.numberOfUIDs = numberOfUIDs;
        stored.sizeOfRecord = sizeOfRecord;
        if (datumAttributesValid) stored.attributes = attributes;
    }
};

} // namespace vp3

#endif
