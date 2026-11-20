#include "Breadcrumb.h"

#ifndef _BREADCRUMBKSEGMENT_H_
#define _BREADCRUMBSEGMENT_H_

struct BreadcrumbSegment : public Breadcrumb
{
    enum class Segment : uint8_t
    {
            DIG = 0x00,		
            TRAVEL_LOADED = 0x01,
            DUMP = 0x02,
            TRAVEL_EMPTY = 0x03,
            TRAVEL = 0x04,
            SWING_LOADED = 0x05,
            SWING_EMPTY = 0x06,
            SCRAPE = 0x07,
            SCRAPE_DUMP = 0x08,
            LOAD = 0x09,
            CARRY = 0x0A,
            STATIONARY_LIFT = 0x0B,
            SPREAD = 0x0C,
            RETURN = 0x0D,
            UNKNOWN = 0x0E,
            MISCELLANEOUS = 0x0F,
            MACHINE_IDLE = 0x10,
            STATIONARY_LOADED_HIGH_IDLE = 0x11,
            STATIONARY_LOADED_LOW_IDLE = 0x12,
            STATIONARY_EMPTY_HIGH_IDLE = 0x13,
            STATIONARY_EMPTY_LOW_IDLE = 0x14,
            LOADED_STOPPED = 0x15,
            EMPTY_STOPPED = 0x16,
            GRADE = 0x17,
            PARTIAL_DUMP = 0x18,
            BACK_DRAGGING = 0x19,
            KEY_ON_ENGINE_OFF = 0x1A,
            KEY_OFF_ENGINE_OFF = 0x1B,
            KEY_OFF_ENGINE_ON = 0x1C,
            FINISH_BLADING = 0x1D,
            HEAVY_BLADING = 0x1E,
            RIPPING_SCARIFYING = 0x1F,
            ROAD_MAINTENANCE = 0x20,
            DITCH_BUILDING = 0x21,
            DITCH_CLEANING = 0x22,
            SNOW_PLOWING = 0x23,
            SNOW_WING = 0x24,
            BLADE_SLOPE_WORK = 0x25,
            SIDE_SLOPE_WORK = 0x26,
            HAUL = 0x27,
            BLADING = 0x28,
            STOPPED = 0x29,
            NOT_USED_A = 0x80,                     // 0x80 .. 0xFF is for PID $F191 added 0x80
            NOT_USED_B = 0x81,
            DUMPING = 0x84,
            STOPPED_EMPTY = 0x85,
            TRAVELING_EMPTY = 0x86,
            STOPPED_LOADED = 0x87,
            TRAVELING_LOADED = 0x88,
            LOADING = 0x89,
            LOADING_LAST_PASS = 0x8A,
            FULLY_LOADED = 0x8B,
            RE_WEIGH_COMPLETE = 0x8C,
    };

    static std::string toString(Segment e)
    {
        const std::map<Segment, const char*> EnumStrings {		// 0x00 .. 0x7F is for PID $D0272F   0x80 .. 0xFF is for PID $F191 added 0x80
            { Segment::DIG,                         "DIG" },		
            { Segment::TRAVEL_LOADED,               "TRAVEL LOADED" },
            { Segment::DUMP,                        "DUMP" },
            { Segment::TRAVEL_EMPTY,                "TRAVEL EMPTY" },
            { Segment::TRAVEL,                      "TRAVEL" },
            { Segment::SWING_LOADED,                "SWING LOADED" },
            { Segment::SWING_EMPTY,                 "SWING EMPTY" },
            { Segment::SCRAPE,                      "SCRAPE" },
            { Segment::SCRAPE_DUMP,                 "SCRAPE DUMP" },
            { Segment::LOAD,                        "LOAD" },
            { Segment::CARRY,                       "CARRY" },
            { Segment::STATIONARY_LIFT,             "STATIONARY LIFT" },
            { Segment::SPREAD,                      "SPREAD" },
            { Segment::RETURN,                      "RETURN" },
            { Segment::UNKNOWN,                     "UNKNOWN" },
            { Segment::MISCELLANEOUS,               "MISCELLANEOUS" },
            { Segment::MACHINE_IDLE,                "MACHINE IDLE" },
            { Segment::STATIONARY_LOADED_HIGH_IDLE, "STATIONARY LOADED HIGH IDLE" },
            { Segment::STATIONARY_LOADED_LOW_IDLE,  "STATIONARY LOADED LOW IDLE" },
            { Segment::STATIONARY_EMPTY_HIGH_IDLE,  "STATIONARY EMPTY HIGH IDLE" },
            { Segment::STATIONARY_EMPTY_LOW_IDLE,   "STATIONARY EMPTY LOW IDLE" },
            { Segment::LOADED_STOPPED,              "LOADED STOPPED" },
            { Segment::EMPTY_STOPPED,               "EMPTY STOPPED" },
            { Segment::GRADE,                       "GRADE" },
            { Segment::PARTIAL_DUMP,                "PARTIAL DUMP" },
            { Segment::BACK_DRAGGING,               "BACK_DRAGGING" },
            { Segment::KEY_ON_ENGINE_OFF,           "KEY_ON_ENGINE_OFF" },
            { Segment::KEY_OFF_ENGINE_OFF,          "KEY_OFF_ENGINE_OFF" },
            { Segment::KEY_OFF_ENGINE_ON,           "KEY_OFF_ENGINE_ON" },
            { Segment::FINISH_BLADING,              "FINISH_BLADING" },
            { Segment::HEAVY_BLADING,               "HEAVY_BLADING" },
            { Segment::RIPPING_SCARIFYING,          "RIPPING_SCARIFYING" },
            { Segment::ROAD_MAINTENANCE,            "ROAD_MAINTENANCE" },
            { Segment::DITCH_BUILDING,              "DITCH_BUILDING" },
            { Segment::DITCH_CLEANING,              "DITCH_CLEANING" },
            { Segment::SNOW_PLOWING,                "SNOW_PLOWING" },
            { Segment::SNOW_WING,                   "SNOW_WING" },
            { Segment::BLADE_SLOPE_WORK,            "BLADE_SLOPE_WORK" },
            { Segment::SIDE_SLOPE_WORK,             "SIDE_SLOPE_WORK" },
            { Segment::HAUL,                        "HAUL" },
            { Segment::BLADING,                     "BLADING" },
            { Segment::STOPPED,                     "STOPPED" },

            { Segment::NOT_USED_A,                  "NOT USED A" },     // 0x80 .. 0xFF is for PID $F191 added 0x80
            { Segment::NOT_USED_B,                  "NOT USED B" },
            { Segment::DUMPING,                     "DUMPING" },
            { Segment::STOPPED_EMPTY,               "STOPPED EMPTY" },
            { Segment::TRAVELING_EMPTY,             "TRAVELING EMPTY" },
            { Segment::STOPPED_LOADED,              "STOPPED LOADED" },
            { Segment::TRAVELING_LOADED,            "TRAVELING LOADED" },
            { Segment::LOADING,                     "LOADING" },
            { Segment::LOADING_LAST_PASS,           "LOADING - LAST PASS" },
            { Segment::FULLY_LOADED,                "FULLY LOADED" },
            { Segment::RE_WEIGH_COMPLETE,           "RE-WEIGH COMPLETE" }
        };
        auto   it  = EnumStrings.find(e);
        return it == EnumStrings.end() ? "??????????" : it->second;
    }

   Segment segment;

    // Needed for serialization
    BreadcrumbSegment() = default;

    BreadcrumbSegment(GPSDataLinkParam::GpsPositionStatusType gpsStatus, float latitude, float longitude, uint32_t cycle,
                  Segment segment) :
        Breadcrumb{BreadcrumbType::SEGMENT, gpsStatus, latitude, longitude, cycle},
        segment{segment}
    {
    }

    template <class Archive>
    void serialize(Archive& ar, unsigned int version)
    {
        ar & boost::serialization::base_object<Breadcrumb>(*this);
        ar & segment;
    }

    void toJsonDerived(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const override
    {
        writer.Key("seg-id"), writer.Uint(static_cast<uint8_t>(segment));
        writer.Key("seg-name"), writer.String(toString(segment));
    }
};

BOOST_CLASS_EXPORT_KEY(BreadcrumbSegment)
BOOST_CLASS_VERSION(BreadcrumbSegment, 1)

#endif
