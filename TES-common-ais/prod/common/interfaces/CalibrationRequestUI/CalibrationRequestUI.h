#ifndef CALIBRATIONREQUESTUI_H_
#define CALIBRATIONREQUESTUI_H_

#include <cstdint>

#include <ais/serialization/Datum.h> // For Boost serialization

class CalibrationRequestUIStorage
{
public:

    struct RequestData {
        RequestData() :
            CalId(0),
            HandshakeNumber(0),
            ControlBits(0),
            InputAction(0),
            InputActionCommand(0),
            CurrStep(0) {}

        uint16_t CalId;
        uint8_t HandshakeNumber;
        uint8_t ControlBits;
        uint16_t InputAction;
        uint8_t InputActionCommand;
        uint8_t CurrStep;
    };

    RequestData CalibParam;

    CalibrationRequestUIStorage() : CalibParam() {}

    template <class Archive>
    void serialize(Archive& ar, unsigned int version) {
        /* Archive Fields Here */
        ar & CalibParam.CalId;
        ar & CalibParam.ControlBits;
        ar & CalibParam.InputAction;
        ar & CalibParam.InputActionCommand;
        ar & CalibParam.CurrStep;

        if (version >= 2) {
            ar & CalibParam.HandshakeNumber;
        }
    }

    void toCsv(CsvOutStream& out) const {
        out("CalId", CalibParam.CalId);
        out("HandshakeNumber", CalibParam.HandshakeNumber);
        out("ControlBits", CalibParam.ControlBits);
        out("InputAction", CalibParam.InputAction);
        out("InputActionCommand", CalibParam.InputActionCommand);
        out("CurrStep", CalibParam.CurrStep);
    }

private:
    /* Add Fields Here */
};

typedef Datum<CalibrationRequestUIStorage> CalibrationRequestUI;

BOOST_CLASS_VERSION(CalibrationRequestUIStorage, 2);

#endif

