#ifndef VP3ARCHIVECOMPATIBILITY_H
#define VP3ARCHIVECOMPATIBILITY_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <sys/time.h>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/wrapper.hpp>

namespace vp3 {
namespace archive {

// Standard Boost binary archives use native timeval widths, not the AIS x86 log shim.
struct TimeStamp
{
    time_t seconds = 0;
    suseconds_t microseconds = 0;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        if (version > 3) {
            throw std::runtime_error("Unsupported VP3 archive timestamp version");
        }
        ar & seconds;
        ar & microseconds;
        if (version == 1) {
            int discardedType = 0;
            ar & discardedType;
        }
    }
};

struct DatumAttributes
{
    virtual ~DatumAttributes() = default;

    TimeStamp originationTime;
    TimeStamp transmissionTime;
    unsigned int txSequenceNumber = 0;
    unsigned int loggerSequenceNumber = 0;
    TimeStamp loggedTime;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & originationTime;
        ar & transmissionTime;
        if (version > 0) {
            ar & txSequenceNumber;
            ar & loggerSequenceNumber;
            ar & loggedTime;
        }
    }
};

struct RecordStorage
{
    virtual ~RecordStorage() = default;

    std::uint16_t recordType = 0;
    std::string uidList;
    std::string rBlockData;
    std::uint16_t numberOfUIDs = 0;
    std::uint16_t sizeOfRecord = 0;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int)
    {
        ar & recordType;
        ar & uidList;
        ar & rBlockData;
        ar & numberOfUIDs;
        ar & sizeOfRecord;
    }
};

// Datum's other polymorphic bases and csvable are not serialized in the legacy archive.
struct Record : RecordStorage, boost::serialization::wrapper_traits<Record>
{
    DatumAttributes attributes;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int)
    {
        ar & attributes;
        ar & boost::serialization::base_object<RecordStorage>(*this);
    }
};

} // archive
} // vp3

BOOST_CLASS_VERSION(vp3::archive::TimeStamp, 3)
BOOST_CLASS_VERSION(vp3::archive::DatumAttributes, 1)
BOOST_CLASS_IMPLEMENTATION(vp3::archive::DatumAttributes, boost::serialization::object_class_info)
BOOST_CLASS_TRACKING(vp3::archive::DatumAttributes, boost::serialization::track_never)
BOOST_CLASS_VERSION(vp3::archive::RecordStorage, 1)

#endif
