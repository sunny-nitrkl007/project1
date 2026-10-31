#include <ais/serialization/TypeRestorer.h>
#include <ais/serialization/Restorable.h>

#include "../OutboundMessageInterface.hpp"

extern "C"
{
    Restorable *getRestorable(const void *blob, const unsigned int size)
    {
        TypeRestorer rest;
        return rest.restoreAltType<IoTHubCommsOutboundMessageInterface, Restorable*>(blob, size);
    }
}

