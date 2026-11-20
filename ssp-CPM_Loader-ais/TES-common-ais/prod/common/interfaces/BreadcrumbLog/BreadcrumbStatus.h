#include "Breadcrumb.h"

#ifndef _BREADCRUMBSTATUS_H_
#define _BREADCRUMBSTATUS_H_

struct BreadcrumbStatus : public Breadcrumb
{
    enum class Type : uint8_t
    {
        RESET,
        SET_BREADCRUMB_RECORDS,
        SET_BREADCRUMB_GPS_TIME_SECONDS,
        SET_BREADCRUMB_GPS_DISTANCE_METERS,
        TIP_OFF_OPERATOR,
        TIP_ON_OPERATOR,
        TIP_ON_AUTOENABLE,
        TIP_AUTOENABLE_TIME,
        TUTORIAL_VIEWED,
        TIP_VIEWED,
        OPERATOR_ACTIVE,
        OPERATOR_INACTIVE,
        GPS_GOOD,
        GPS_BAD,
        CYCLE_END,
        DL_GOOD,
        DL_BAD,
    };

    static std::string toString(Type e)
    {
        const std::map<Type, const char*> EnumStrings {
            { Type::RESET,                        "Reset" },
            { Type::SET_BREADCRUMB_RECORDS,   "SetBreadcrumbRecords" },
            { Type::SET_BREADCRUMB_GPS_TIME_SECONDS,   "SetBreadcrumbGpsTimeSeconds" },
            { Type::SET_BREADCRUMB_GPS_DISTANCE_METERS,   "SetBreadcrumbGpsDistanceMeters" },
            { Type::TIP_OFF_OPERATOR,             "Disable" },
            { Type::TIP_ON_OPERATOR,              "Enable-Operator" },
            { Type::TIP_ON_AUTOENABLE,            "Enable-Auto" },
            { Type::TIP_AUTOENABLE_TIME,          "TipAutoEnableTime" },
            { Type::TUTORIAL_VIEWED,              "TutorialViewed" },
            { Type::TIP_VIEWED,                   "TipViewed" },
            { Type::OPERATOR_ACTIVE,              "Operator-ACTIVE" },
            { Type::OPERATOR_INACTIVE,            "Operator-INACTIVE" },
            { Type::GPS_GOOD,                     "GPS-GOOD" },
            { Type::GPS_BAD,                      "GPS-BAD" },
            { Type::CYCLE_END,                    "CYCLE-END" },
            { Type::DL_GOOD,                      "DL-GOOD" },
            { Type::DL_BAD,                       "DL-BAD" },
        };
        auto   it  = EnumStrings.find(e);
        return it == EnumStrings.end() ? "--" : it->second;
    }

    Type statusType;
    uint32_t value;

    // Needed for serialization
    BreadcrumbStatus() = default;

    BreadcrumbStatus(GPSDataLinkParam::GpsPositionStatusType gpsStatus, float latitude, float longitude, uint32_t cycle,
                  Type statusType, uint32_t value) :
        Breadcrumb{BreadcrumbType::STATUS, gpsStatus, latitude, longitude, cycle},
        statusType{statusType},
        value{value}
    {
    }

    template <class Archive>
    void serialize(Archive& ar, unsigned int version)
    {
        ar & boost::serialization::base_object<Breadcrumb>(*this);
        ar & statusType;
        ar & value;
    }

    void toJsonDerived(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const override
    {
        writer.Key("status"), writer.String(toString(statusType));
        writer.Key("value"), writer.Uint(value);
    }
};

BOOST_CLASS_EXPORT_KEY(BreadcrumbStatus)
BOOST_CLASS_VERSION(BreadcrumbStatus, 1)

#endif
