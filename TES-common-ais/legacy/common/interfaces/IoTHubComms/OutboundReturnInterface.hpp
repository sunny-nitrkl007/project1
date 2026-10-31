#ifndef IOTHUBCOMMS_OUTBOUNDRETURNINTERFACE_HPP
#define IOTHUBCOMMS_OUTBOUNDRETURNINTERFACE_HPP

#include <cstdint>
#include <type_traits>

#include <boost/serialization/version.hpp>

#include <ais/serialization/Datum.h>
#include <ais/serialization/csvable.h>

#include "OutboundMessageInterface.hpp"


/*
 * The interface storage class.
 */
class IoTHubCommsOutboundReturnInterfaceStorage : public csvable {
public:
    enum class ReturnState : uint8_t {
        STATE_INVALID = 0,
        TRANSMIT_ACKNOWLEDGE_SUCCESS = 1,     // Transmitted and Acknowledged by IOTHub
        QUEUED_SUCCESS = 2,                   // Queued for Later Transmission to IOTHub
        FILE_TYPE_NOT_SUPPORTED = 3,
        FILE_SIZE_EXCEEDED = 4,
        QUEUE_TIMEOUT = 5,
        CONNECTION_UNAVAILABLE = 6,
        HUB_NOT_INITIALIZED = 7,
        HUB_SUBSCRIPTION_NOT_AUTHORIZED = 8,
        HUB_CONNECT_SECURITY_FAILURE = 9,
        FATAL_ERROR = 10
    };

    static inline bool returnStateOk(ReturnState s) {
        return ((ReturnState::TRANSMIT_ACKNOWLEDGE_SUCCESS == s) || (ReturnState::QUEUED_SUCCESS == s));
    }

    IoTHubCommsOutboundReturnInterfaceStorage() = default;

    std::string appName; // Who is this in response to?
    uint32_t appRequestId; // This is from the originating outbound message request.
    uint32_t fileType;
    ReturnState returnState = ReturnState::STATE_INVALID;
    std::string messageId; // (optional) Will be populated if message transmitted with generateMessageId set to true

    inline bool returnStateOk() {
        return returnStateOk(returnState);
    }

    inline void setData(IoTHubCommsOutboundReturnInterfaceStorage&& data) {
        *this = std::move(data);
    }

    inline void initFromOutboundMessage(const IoTHubCommsOutboundMessageInterfaceStorage& req) {
        appName = req.appName;
        appRequestId = req.appRequestId;
        fileType = req.fileType;
        returnState = ReturnState::STATE_INVALID;
        messageId.clear();
    }

    void toCsv(CsvOutStream& out) const {
        // Not supported.
    }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & appName;
        ar & appRequestId;
        ar & fileType;
        ar & returnState;
        ar & messageId;
    }
};

/*
 * Datum template specialization.
 *   Defines a new specialization of the Datum class
 *   derived from the base 'storage' class.
 */
typedef Datum<IoTHubCommsOutboundReturnInterfaceStorage> IoTHubCommsOutboundReturnInterface;

BOOST_CLASS_VERSION(IoTHubCommsOutboundReturnInterfaceStorage, 1);

#endif
