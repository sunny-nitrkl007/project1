#include <ais/serialization/TypeRestorer.h>
#include <ais/serialization/csvable.h>

#include "../InboundMessageInterface.hpp"

extern "C"
{
    csvable *getCSVable(const void *blob, const unsigned int size)
    {
        TypeRestorer rest;
        return rest.restoreAltType<IoTHubCommsInboundMessageInterface, csvable*>(blob, size);
    }
}

