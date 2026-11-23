#ifndef VP3BRIDGESUPPORT_H
#define VP3BRIDGESUPPORT_H

#include <chrono>
#include <cstdint>
#include <deque>
#include <limits>
#include <string>
#include <type_traits>

namespace vp3_bridge
{
struct DrainState
{
    std::string appName = "VP3FileCreationApp";
    unsigned int timeoutMs = 1950000;
    bool inactive = false;

    bool acceptsRx(const std::string& destination) const { return destination == appName; }
    bool acceptsTx(const std::string& source, const std::string& destination) const
    {
        return source == appName && destination != appName;
    }
    void observe(uint8_t type, uint8_t state)
    {
        if (type == 0) {
            inactive = state == 1;
        }
    }
    bool waiting(std::chrono::milliseconds elapsed) const
    {
        return !inactive && elapsed.count() < timeoutMs;
    }
    bool valid() const { return !appName.empty() && timeoutMs >= 1950000; }
};

template<class T>
void enqueue(std::deque<T>& queue, const T& value)
{
    if (queue.size() == 20) {
        queue.pop_front();
    }
    queue.push_back(value);
}

template<class Message, class Record>
Message recordToRos(const Record& scs)
{
    Message ros;
    ros.record_type = scs.getRecordType();
    ros.uid_list.assign(scs.getUIDList().begin(), scs.getUIDList().end());
    ros.r_block_data.assign(scs.getRBlockData().begin(), scs.getRBlockData().end());
    ros.number_of_uids = scs.getNumberOfUIDs();
    ros.size_of_record = scs.getSizeOfRecord();
    ros.datum_attributes_valid = true;
    const auto origin = scs.attributes.originationTime.getTimeval();
    const auto transmission = scs.attributes.transmissionTime.getTimeval();
    const auto logged = scs.attributes.loggedTime.getTimeval();
    ros.origination_time_secs = origin.tv_sec;
    ros.origination_time_usecs = origin.tv_usec;
    ros.transmission_time_secs = transmission.tv_sec;
    ros.transmission_time_usecs = transmission.tv_usec;
    ros.transmission_sequence_number = scs.attributes.txSequenceNumber;
    ros.logger_sequence_number = scs.attributes.loggerSequenceNumber;
    ros.logged_time_secs = logged.tv_sec;
    ros.logged_time_usecs = logged.tv_usec;
    return ros;
}

template<class Message>
bool validAppReg(const Message& ros)
{
    return ros.msg_type <= 1 && ros.app_state <= 1 && ros.reg_status <= 6;
}

template<class Message>
struct AppRegLoader
{
    const Message& message;
    unsigned int field = 0;
    template<class T>
    AppRegLoader& operator&(T& value)
    {
        if constexpr (std::is_same<T, std::string>::value) {
            value = field == 1 ? message.app_name : message.dest_app_name;
        } else {
            value = static_cast<T>(field == 0 ? message.msg_type :
                    field == 2 ? message.app_state : message.reg_status);
        }
        ++field;
        return *this;
    }
};

template<class Scs, class Message>
Scs appRegToScs(const Message& ros)
{
    Scs scs;
    AppRegLoader<Message> loader{ros};
    scs.serialize(loader, 1);
    return scs;
}

template<class Scs, class Message>
bool transferToScs(const Message& ros, Scs& scs)
{
    using Fid = decltype(scs.fileAttr.FidSource);
    if (ros.fid_source > std::numeric_limits<Fid>::max() ||
            ros.fid_destination > std::numeric_limits<Fid>::max()) {
        return false;
    }
    scs.fileAttr.TelematicsFileNumber = ros.telematics_file_number;
    scs.fileAttr.SizeInBytes = ros.size_in_bytes;
    scs.fileAttr.Name = ros.name;
    scs.fileAttr.DirPath = ros.dir_path;
    scs.fileAttr.FidSource = static_cast<Fid>(ros.fid_source);
    scs.fileAttr.FidDestination = static_cast<Fid>(ros.fid_destination);
    return true;
}
}

#endif
