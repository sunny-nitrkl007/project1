#ifndef JOBMGRLEGACYLOADRECORD_H_
#define JOBMGRLEGACYLOADRECORD_H_

#include <iostream>
#include <sys/time.h>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/wrapper.hpp>

namespace jobmgr_data {

struct LegacyDatumTimeStamp {
    timeval time{0, 0};

    template <class Archive>
    void serialize(Archive& ar, unsigned int version) {
        switch (version) {
        case 0:
        case 2:
        case 3:
            ar & time.tv_sec;
            ar & time.tv_usec;
            break;
        case 1: {
            ar & time.tv_sec;
            ar & time.tv_usec;
            int type = 0;
            ar & type;
            break;
        }
        default:
            std::cerr << "Unknown TimeStamp message version " << version << "\n";
            break;
        }
    }
};

struct LegacyDatumAttributes {
    LegacyDatumTimeStamp originationTime;
    LegacyDatumTimeStamp transmissionTime;
    unsigned int txSequenceNumber = 0;
    unsigned int loggerSequenceNumber = 0;
    LegacyDatumTimeStamp loggedTime;

    template <class Archive>
    void serialize(Archive& ar, unsigned int version) {
        ar & originationTime;
        ar & transmissionTime;
        if (version > 0) {
            ar & txSequenceNumber;
            ar & loggerSequenceNumber;
            ar & loggedTime;
        }
    }
};

// Ordinary binary_iarchive stores native timeval fields; this is not an x86 log reader.
template <class Storage>
class LegacyLoadRecordEnvelope : public Storage,
        public boost::serialization::wrapper_traits<LegacyLoadRecordEnvelope<Storage>> {
public:
    LegacyDatumAttributes attributes;

    template <class Archive>
    void serialize(Archive& ar, unsigned int) {
        ar & attributes;
        ar & boost::serialization::base_object<Storage>(*this);
    }
};

}

BOOST_CLASS_VERSION(jobmgr_data::LegacyDatumTimeStamp, 3)
BOOST_CLASS_VERSION(jobmgr_data::LegacyDatumAttributes, 1)
BOOST_CLASS_IMPLEMENTATION(jobmgr_data::LegacyDatumAttributes, boost::serialization::object_class_info)
BOOST_CLASS_TRACKING(jobmgr_data::LegacyDatumAttributes, boost::serialization::track_never)

#endif
