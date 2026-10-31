#include <ais/serialization/TypeRestorer.h>
#include <ais/serialization/csvable.h>

#include "../OutboundMessageInterface.hpp"

extern "C"
{
    csvable *getCSVable(const void *blob, const unsigned int size)
    {
        TypeRestorer rest;
        return rest.restoreAltType<IoTHubCommsOutboundMessageInterface, csvable*>(blob, size);
    }
}

