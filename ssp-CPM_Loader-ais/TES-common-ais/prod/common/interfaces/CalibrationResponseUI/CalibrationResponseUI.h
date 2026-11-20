#ifndef CALIBRATIONRESPONEUI_H_
#define CALIBRATIONRESPONEUI_H_

#include <cstdint>
#include <vector>

#include <ais/serialization/Datum.h> // For Boost serialization
#include <boost/serialization/vector.hpp>

class CalibrationResponseUIStorage: public csvable
{
public:
    typedef union {
        struct {
            uint8_t CalibrationModeActiveStatus : 1;
            uint8_t CalibrationExecutionStatus : 1;
            uint8_t BusyStatus : 1;
            uint8_t Dontcare : 3;
            uint8_t OverallCompletionstatus : 2;
        } StatusStruct;
        unsigned char Status;
    } StatusGroup;

    uint16_t CalId;
    uint8_t HandshakeNumber;
    StatusGroup statusParams;
    uint16_t stepno;
    std::vector<uint16_t> activeWarningErrorVector;

    CalibrationResponseUIStorage() :
        CalId(0),
        HandshakeNumber(0),
        statusParams{{0}},
        stepno(0),
        activeWarningErrorVector() {}

    template <class Archive>
    void serialize(Archive& ar, unsigned int version) {
        ar & statusParams.Status;
        ar & stepno;
        ar & CalId;
        ar & activeWarningErrorVector;

        if (version >= 2) {
            ar & HandshakeNumber;
        }
    }

    void toCsv(CsvOutStream& out) const {
        out("CalId", CalId);
        out("HandshakeNumber", HandshakeNumber);
        out("Status", statusParams.Status);
        out("Step", stepno);
        out("numActiveWarningsEvents", activeWarningErrorVector.size());

        std::vector<unsigned short>::const_iterator it;
        for(it = activeWarningErrorVector.begin(); it != activeWarningErrorVector.end(); ++it) {
            out("Code", *it);
        }
    }

private:
    /* Add Fields Here */
};

typedef Datum<CalibrationResponseUIStorage> CalibrationResponseUI;

BOOST_CLASS_VERSION(CalibrationResponseUIStorage, 2);

#endif

