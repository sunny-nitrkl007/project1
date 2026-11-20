#include <boost/serialization/export.hpp>
#include <ais/serialization/Datum.h>
#include <interfaces/DataLinkData/GPSDataLinkParam.h>
#include "interfaces/JSON/jsonable.h"

#ifndef _BREADCRUMB_H_
#define _BREADCRUMB_H_

struct Breadcrumb : public jsonable
{
    enum class BreadcrumbType : uint8_t
    {
        TIP,
        SEGMENT,
        GPS,
        OPERATOR,
        EID,
        CID,
        MACHINE,
        STATUS,
        UNDEFINED
    };

    static std::string toString(BreadcrumbType e)
    {
        const std::map<BreadcrumbType, const char*> EnumStrings {
            { BreadcrumbType::TIP,          "TIP" },
            { BreadcrumbType::SEGMENT,      "SEGMENT" },
            { BreadcrumbType::GPS,          "GPS" },
            { BreadcrumbType::OPERATOR,     "OPERATOR" },
            { BreadcrumbType::EID,          "EID" },
            { BreadcrumbType::CID,          "CID" },
            { BreadcrumbType::MACHINE,      "MACHINE" },
            { BreadcrumbType::STATUS,       "STATUS" },
            { BreadcrumbType::UNDEFINED,    "UNDEFINED" }
        };
        auto   it  = EnumStrings.find(e);
        return it == EnumStrings.end() ? "--" : it->second;
    }

    BreadcrumbType type;
    int64_t timeSecondsSinceEpoch{std::time(NULL)};
    GPSDataLinkParam::GpsPositionStatusType gpsStatus;
    float latitude;
    float longitude;
    uint32_t cycle;


    // Handle implementation specific fields in derived class
    virtual void toJsonDerived(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const = 0;

    // Needed for serialization
    Breadcrumb() = default;

    virtual ~Breadcrumb() = default;

    Breadcrumb(BreadcrumbType type, GPSDataLinkParam::GpsPositionStatusType gpsStatus, float latitude, float longitude, uint32_t cycle) :
        type{type},
        gpsStatus{gpsStatus},
        latitude{latitude},
        longitude{longitude},
        cycle{cycle}
    {
    }

    template <class Archive>
    void serialize(Archive& ar, unsigned int version)
    {
        ar & type;
        ar & timeSecondsSinceEpoch;
        ar & gpsStatus;
        ar & latitude;
        ar & longitude;

        if (version >=2)
        {
            ar & cycle;
        }
    }

    void toJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const override
    {
        writer.StartObject();

        writer.Key("type"), writer.String(toString(type));
        writer.Key("timeSecondsSinceEpoch"), writer.Int64(timeSecondsSinceEpoch);
        writer.Key("gpsStatus"), writer.String(GPSDataLinkParam::toString(gpsStatus));
        writer.Key("latitude"), writer.Double(latitude);
        writer.Key("longitude"), writer.Double(longitude);
        writer.Key("cycle"), writer.Double(cycle);

        // Print implementation specific fields in derived class
        toJsonDerived(writer);

        writer.EndObject();
    }
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Breadcrumb);

BOOST_CLASS_VERSION(Breadcrumb, 2);

#endif
