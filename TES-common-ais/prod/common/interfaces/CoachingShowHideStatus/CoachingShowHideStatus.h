#include <ais/serialization/Datum.h> // For Boost serialization
#include <ais/serialization/csvable.h>
#include <ais/log/AisLogger.h>
#include <xcp_server/db/XCPServerDb.hpp>
#include "interfaces/JSON/jsonable.h"

#ifndef _COACHINGSHOWHIDESTATUS_H_
#define _COACHINGSHOWHIDESTATUS_H_

using namespace xcp_server;

class CoachingShowHideStatusStorage : public csvable, public jsonable, public xcpable
{
public:

    bool coachingEnabled;
    bool coachingInstalled;
    bool coachingTempInstalled;
    uint16_t coachingTempTime;
    std::string internalMsn;
    bool machineInSafeState;
    bool mapSupported;
    bool practiceSupported;
    bool standAloneUiSupported;
    std::string operatorName;
    uint16_t countOfBadges;				// current count of the number of Tips with the badgeFlag set, for ACD to send to Display
    std::string softwareVersion;
    std::string langugeUrl;
    bool diagnosticActiveFlag;          // indicates if any datalink parameters are in DSI

    CoachingShowHideStatusStorage() :
        coachingEnabled{false},
        coachingInstalled{false},
        coachingTempInstalled{false},
        coachingTempTime{0},
        internalMsn{"NOT_SET"},
        machineInSafeState{false},
        mapSupported{false},
        practiceSupported{false},
        standAloneUiSupported{false},
        operatorName{0},
        countOfBadges{0},
        softwareVersion{0},
        langugeUrl{"/CPM/languages/appSpecifc_addstring_en.json"},   // default
        diagnosticActiveFlag{false}
    {}

    template <class Archive>
    void serialize(Archive& ar, unsigned int version)
    {
        ar & coachingEnabled;
        ar & coachingInstalled;
        ar & coachingTempInstalled;
        ar & coachingTempTime;
        ar & internalMsn;
        ar & machineInSafeState;
        ar & practiceSupported;
        ar & mapSupported;
        ar & operatorName;
        ar & countOfBadges;
        ar & softwareVersion;

        if (version >=2)
        {
            ar & standAloneUiSupported;
            ar & diagnosticActiveFlag;
        }
    }

    void toJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const override
    {
        writer.StartObject();

        writer.Key("internalMsn"), writer.String(internalMsn);

        writer.Key("coachingStatus");
        writer.StartObject();
        writer.Key("installed"), writer.tBool(coachingInstalled);
        writer.Key("enabled"), writer.tBool(coachingEnabled);
        writer.Key("tempInstalled"), writer.tBool(coachingTempInstalled);
        writer.Key("tempTime"), writer.Uint(coachingTempTime);
        writer.EndObject();

        writer.Key("machineInSafeState"), writer.tBool(machineInSafeState);
        writer.Key("operatorName"), writer.String(operatorName);
        writer.Key("countOfBadges"), writer.Uint(countOfBadges);
        writer.Key("softwareVersion"), writer.String(softwareVersion);

        writer.Key("practice");
        writer.StartObject();
        writer.Key("supported"), writer.tBool(practiceSupported);
        writer.EndObject();

        writer.Key("map");
        writer.StartObject();
        writer.Key("supported"), writer.tBool(mapSupported);
        writer.EndObject();
        writer.Key("standAloneUiSupported"), writer.tBool(standAloneUiSupported);
        writer.Key("diagnosticActiveFlag"), writer.tBool(diagnosticActiveFlag);
        writer.Key("addingLangugeUrl"), writer.String(langugeUrl);

        writer.EndObject();
    }

    void toCsv(CsvOutStream& out) const override
    {
        out("internalMsn", internalMsn);
        out("coachingInstalled", coachingInstalled);
        out("coachingEnabled", coachingEnabled);
        out("coachingTempInstalled", coachingTempInstalled);
        out("coachingTempTime", coachingTempTime);
        out("machineInSafeState", machineInSafeState);
        out("practiceSupported", practiceSupported);
        out("mapSupported", mapSupported);
    }

    uint32_t toXcp(ParameterDb& db, uint32_t startAddr) const override
    {
        uint32_t baseAddr = startAddr & 0xFFFF0000;
        uint32_t offset = startAddr & 0x0000FFFF;

        // startAddr +0 is count of recieved ShowHide scs object
        DB_PUSH_ADDR(static_cast<uint8_t>(coachingInstalled));  // startAddr + 1
        DB_PUSH_ADDR(static_cast<uint8_t>(coachingEnabled));    // startAddr + 2
        DB_PUSH_ADDR(static_cast<uint8_t>(machineInSafeState)); // startAddr + 3
        DB_PUSH_ADDR(static_cast<uint8_t>(practiceSupported));  // startAddr + 4
        DB_PUSH_ADDR(static_cast<uint8_t>(mapSupported));       // startAddr + 5
        DB_PUSH_ADDR(static_cast<uint32_t>(DB_PACK_32(internalMsn[0], internalMsn[1], internalMsn[2], internalMsn[3])));  // startAddr + 6
        DB_PUSH_ADDR(static_cast<uint32_t>(DB_PACK_32(internalMsn[4], internalMsn[5], internalMsn[6], internalMsn[7])));  // startAddr + 7
        DB_PUSH_ADDR(static_cast<uint8_t>(coachingTempInstalled)); // startAddr + 8
        DB_PUSH_ADDR(static_cast<uint32_t>(coachingTempTime));      // startAddr + 9
        DB_PUSH_ADDR(static_cast<uint8_t>(standAloneUiSupported)); // startAddr + A
        DB_PUSH_ADDR(static_cast<uint8_t>(diagnosticActiveFlag));  // startAddr + B

        // Return the next free address
        return baseAddr | offset;
    }

private:
};

typedef Datum<CoachingShowHideStatusStorage> CoachingShowHideStatus;

BOOST_CLASS_VERSION(CoachingShowHideStatusStorage, 2);
#endif


