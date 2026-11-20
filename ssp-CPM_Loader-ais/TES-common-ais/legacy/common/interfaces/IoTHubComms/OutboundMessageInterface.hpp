#ifndef IOTHUBCOMMS_OUTBOUNDMESSAGEINTERFACE_HPP
#define IOTHUBCOMMS_OUTBOUNDMESSAGEINTERFACE_HPP

#include <cstdint>
#include <vector>
#include <atomic>

#include <boost/serialization/version.hpp>
#include <boost/serialization/vector.hpp>

#include <ais/serialization/Datum.h>
#include <ais/serialization/csvable.h>


/*
 * The interface storage class.
 */
class IoTHubCommsOutboundMessageInterfaceStorage : public csvable {
public:
    IoTHubCommsOutboundMessageInterfaceStorage() :
        appName(),
        appRequestId(0),
        fileType(0),
        messageContents(),
        correlationId(),
        generateMessageId(true),
        oneShot(false) {}

    std::string appName; // Who is sending the message?
    uint32_t appRequestId; // This gets sent back in the "Return" interface.
    uint32_t fileType;
    std::vector<uint8_t> messageContents;
    std::string correlationId; // (optional) Mobile Originated GUID set by onboard app in response to IOTHubMessageInbound.MessageID
    bool generateMessageId;
    bool oneShot;

    void toCsv(CsvOutStream& out) const {
        // Not supported.
    }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & appName;
        ar & appRequestId;
        ar & fileType;
        ar & messageContents;
        ar & correlationId;
        ar & generateMessageId;
        ar & oneShot;
    }

    static uint32_t getNextAppRequestId() {
        static std::atomic<uint32_t> nextAppRequestId(0);
        return nextAppRequestId++;
    }
};

/*
 * Datum template specialization.
 *   Defines a new specialization of the Datum class
 *   derived from the base 'storage' class.
 */
typedef Datum<IoTHubCommsOutboundMessageInterfaceStorage> IoTHubCommsOutboundMessageInterface;

BOOST_CLASS_VERSION(IoTHubCommsOutboundMessageInterfaceStorage, 1);

#endif
